
/*
 *  [注意] 尽量在头文件中避免使用 STL 内容, 可以最大限度的
 *         保证模块与应用程序的兼容性。
 */

#pragma warning (disable : 4311)	
#pragma warning (disable : 4966)

#include "StdAfx.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdio>
#include "COciOperation.h"
#pragma comment (lib, "oci.lib")

using namespace std;

static void ShowMessage(const char* szMsg);


/////////////////////////////////////////////////////////////////
//															   //
//			Class COciDatabase Implementation				   //
//															   //
/////////////////////////////////////////////////////////////////

COciDatabase::COciDatabase()
{
	m_bInit = false;
	
	m_p_oci_env		= NULL;
	m_p_oci_err		= NULL;
	m_p_oci_srv		= NULL;
	
	m_ppConnections = NULL;	
}

COciDatabase::~COciDatabase()
{

}

COciDatabase* COciDatabase::CreateInstance()
{
	return new COciDatabase();
}

void COciDatabase::Release()
{
	if(!m_bInit)
	{
		delete this;
		return;
	}

	if(m_ppConnections != NULL)
	{
		for(int i=0; i<m_nConnCount; i++)
		{
			delete m_ppConnections[i];
		}
	
		delete m_ppConnections;
		m_ppConnections = NULL;
	}
	
	OCIHandleFree(this->m_p_oci_srv, OCI_HTYPE_SERVER);
	OCIHandleFree(this->m_p_oci_err, OCI_HTYPE_ERROR);
	OCIHandleFree(this->m_p_oci_env, OCI_HTYPE_ENV);

	delete this;
}

void COciDatabase::InitDatabase()
{
	if(m_bInit)
		throw COciException("InitDatabase() 只能够执行一次!\n", __FILE__, __LINE__);

	// 初始化 env 句柄
	// [2008 - 05 - 16] 如果 mode = OCI_SHARED | OCJ_THREADED 发现程序无故退出。

	ub4   mode   = OCI_OBJECT | OCI_THREADED;
	sword result = OCIEnvCreate(&m_p_oci_env, mode, 0, 0, 0, 0, 0, 0);
	if(result != OCI_SUCCESS)
		throw COciException("OCIEnvCreate() 函数执行失败!\n", __FILE__, __LINE__);

	// 为 server 句柄分配空间
	result = OCIHandleAlloc ((dvoid *)m_p_oci_env, (dvoid **)&m_p_oci_srv,
      OCI_HTYPE_SERVER, 0, (dvoid **) 0);
	if(result != OCI_SUCCESS)
		throw COciException("OCIHandleAlloc() 函数执行失败!\n", __FILE__, __LINE__);

    // 为 error 句柄分配空间  
	result = OCIHandleAlloc ((dvoid *)m_p_oci_env, (dvoid **)&m_p_oci_err,
      OCI_HTYPE_ERROR, 0, (dvoid **) 0);
	if(result != OCI_SUCCESS)
		throw COciException("OCIHandleAlloc() 函数执行失败!\n", __FILE__, __LINE__);

	// 分配连接池空间
	m_ppConnections = new COciConnection* [MAX_CONN_NUM];
	if(m_ppConnections == NULL)
		throw COciException("为连接池申请内存空间失败!\n", __FILE__, __LINE__);

	memset(m_ppConnections, 0, MAX_CONN_NUM);
	m_nConnCount = 0;

	m_bInit = true;
}


COciConnection* COciDatabase::GetConnectionInstance(int iIndex)
{
	if(iIndex >= MAX_CONN_NUM || m_ppConnections[iIndex] == NULL)
		throw COciException("传入的连接索引号无效!\n", __FILE__, __LINE__);

	return m_ppConnections[iIndex];
}

COciConnection* COciDatabase::CreateConnectionInstance()
{
	if(m_nConnCount >= MAX_CONN_NUM)
		throw COciException("已经存在最大的连接对象数量, 无法继续创建!\n", __FILE__, __LINE__);
	
	COciConnection* pConnObj = new COciConnection(*this);
	if(pConnObj == NULL)
		throw COciException("创建数据库连接对象失败!\n", __FILE__, __LINE__);

	m_ppConnections[m_nConnCount] = pConnObj;

	m_nConnCount++;

	return pConnObj;
}

// 以连接对象的指针方式创建游标对象
COciSQLCursor* COciDatabase::CreateSQLCursorInstance(const COciConnection* pConnObj)
{
	if(m_nConnCount == 0)
		throw COciException("当前没有创建任何连接对象!\n", __FILE__, __LINE__);

	int i;
	for(i=0; i<m_nConnCount; i++)
	{
		if(m_ppConnections[i] == pConnObj)
			break;
	}

	if(pConnObj == NULL || i == m_nConnCount)
		throw COciException("传入的连接对象无效!\n", __FILE__, __LINE__);

	COciSQLCursor* pCursorObj = new COciSQLCursor(*this);
	if(pCursorObj == NULL)
		throw COciException("创建游标对象失败!\n", __FILE__, __LINE__);

	 // 一定要初始化游标对象的 m_p_oci_svc 成员。
	pCursorObj->m_p_oci_svc = pConnObj->m_p_oci_svc;


	return pCursorObj;
}

// 以索引方式创建游标对象
COciSQLCursor*  COciDatabase::CreateSQLCursorInstance(int iConnIndex)
{
	if(m_nConnCount == 0)
		throw COciException("当前没有创建任何连接对象!\n", __FILE__, __LINE__);

	if(iConnIndex >= m_nConnCount || m_ppConnections[iConnIndex] == NULL)
		throw COciException("传入的连接对象无效!\n", __FILE__, __LINE__);

	COciSQLCursor* pCursorObj = new COciSQLCursor(*this);
	if(pCursorObj == NULL)
		throw COciException("创建游标对象失败!\n", __FILE__, __LINE__);

	 // 一定要初始化游标对象的 m_p_oci_svc 成员。
	pCursorObj->m_p_oci_svc = m_ppConnections[iConnIndex] ->m_p_oci_svc;

	return pCursorObj;
}












/////////////////////////////////////////////////////////////////
//															   //
//			Class COciException Implementation				   //
//															   //
/////////////////////////////////////////////////////////////////

COciException::COciException(const COciException& objException)
{
	m_nStatus	= objException.m_nStatus;
	m_nErrCode	= objException.m_nErrCode;
	memset(m_szMsg, 0, MSG_EXCEPTION_SIZE);
	strcpy(m_szMsg, objException.m_szMsg);

	m_nLine = objException.m_nLine;
	memset(m_szFile, 0, FILE_PATH_LENGTH);
	strcpy(m_szFile, objException.m_szFile);

	m_p_oci_env = objException.m_p_oci_env;
	m_p_oci_err = objException.m_p_oci_err;
}


COciException::COciException(const OCIError* p_oci_err, int nStatus /*=OCI_SUCCESS*/, const char* szFile /*=NULL*/, const int nLine /*=0*/)
{
	m_nLine = nLine;
	memset(m_szFile, 0, FILE_PATH_LENGTH);
	if(szFile != NULL)
		strcpy(m_szFile, szFile);

	memset(m_szMsg, 0, MSG_EXCEPTION_SIZE);

	m_p_oci_err = (OCIError*)p_oci_err;
	m_nStatus  = nStatus;
	m_nErrCode = 0;

	switch(m_nStatus)
	{
	case OCI_SUCCESS:
		sprintf(m_szMsg, "%s\n", "OCI_SUCCESS");
		break;

	case OCI_SUCCESS_WITH_INFO:
		sprintf(m_szMsg, "%s\n", "OCI_SUCCESS_WITH_INFO");
		break;

	case OCI_NO_DATA:
		sprintf(m_szMsg, "%s\n", "OCI_NO_DATA");
		break;

	case OCI_ERROR:
		OCIErrorGet(m_p_oci_err, (ub4)1, (text*)NULL, &m_nErrCode, 
			(text*)m_szMsg, (ub4)sizeof(m_szMsg), (ub4)OCI_HTYPE_ERROR);
		break;

	case OCI_INVALID_HANDLE:
		sprintf(m_szMsg, "%s\n", "OCI_INVALID_HANDLE");
		break;

	case OCI_STILL_EXECUTING:
		sprintf(m_szMsg, "%s\n", "OCI_STILL_EXECUTING");
		break;

	case OCI_CONTINUE:
		sprintf(m_szMsg, "%s\n", "OCI_CONTINUE");
		break;
	}
}

COciException::COciException(const char* szErrMsg, const char* szFile /*=NULL*/, const int nLine /*=0*/)
{
	m_nLine = nLine;

	memset(m_szMsg, 0, MSG_EXCEPTION_SIZE);
	if(szErrMsg != NULL)
		strcpy(m_szMsg, szErrMsg);

	memset(m_szFile, 0, FILE_PATH_LENGTH);
	if(szFile != NULL)
		strcpy(m_szFile, szFile);

}

COciException::~COciException()
{

}

void COciException::ShowExceptionInfo()
{
	char szErrorBuf[512] = {0};
	if(strstr(m_szMsg, "ORA-00001") != NULL)
	{
		//return;
	}
	sprintf(szErrorBuf, "OCI\n[描述]: %s", m_szMsg);
	
	/*
	if(strlen(m_szFile) != 0)
		sprintf(&szErrorBuf[strlen(szErrorBuf)], "[文件]: %s\n", m_szFile);
	
	if(m_nLine != 0)
		sprintf(&szErrorBuf[strlen(szErrorBuf)], "[行号]: %d\n", m_nLine);
	*/
	strcat(szErrorBuf, "\n");

	ShowMessage(szErrorBuf);
}

void COciException::ShowExceptionInfo(char* szSQLStatement, char* szFile, int nLine)
{
// 	fstream file;
// 	file.open("oci_exceptions.txt", ios::out | ios::app);
// 	if(file.fail())
// 	{
// 		cout << "open file oci_exceptions.txt failed!" << endl;
// 		return;
// 	}
// 
 	strcpy(szSQLStatement, m_szMsg);
// 
// 	time_t now = time(NULL);
// 	file << "Exception at: " << asctime(localtime(&now)) << m_szMsg << szSQLStatement << endl;
// 	file << "File: " << szFile << endl;
// 	file << "Line: " << nLine << endl;
// 	file << endl;
// 	
// 	file.close();
	
}











/////////////////////////////////////////////////////////////////
//															   //
//			Class COciConnection Implementation				   //
//															   //
/////////////////////////////////////////////////////////////////


COciConnection::COciConnection(const COciDatabase& db)
{
	this->m_p_oci_env   = db.m_p_oci_env;
	this->m_p_oci_err   = db.m_p_oci_err;
	this->m_p_oci_srv   = db.m_p_oci_srv;
	
	this->m_p_oci_svc   = NULL;
	this->m_p_oci_sess  = NULL;
	this->m_p_oci_trans = NULL;
	this->m_p_oci_desc  = NULL;

	this->m_bConnected = false;
}

COciConnection::~COciConnection()
{
	if(m_bConnected)
		DisConnect();
}

void COciConnection::Connect(const char* db_svr_name, const char* username, const char* password)
{
	if(db_svr_name == NULL)
		throw COciException("传入的数据库服务名称为空.\n", __FILE__, __LINE__);

	if(username == NULL)
		throw COciException("传入的用户名称为空.\n", __FILE__, __LINE__);

	if(password == NULL)
		throw COciException("传入的密码为空.\n", __FILE__, __LINE__);

	sword result = OCIServerAttach(this->m_p_oci_srv, this->m_p_oci_err, (text*)db_svr_name, (sb4)strlen(db_svr_name), OCI_DEFAULT);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);
	
	result = OCIHandleAlloc(this->m_p_oci_env, (dvoid**)&this->m_p_oci_svc, OCI_HTYPE_SVCCTX, 0, 0);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);
	
	result = OCIAttrSet(this->m_p_oci_svc, OCI_HTYPE_SVCCTX, this->m_p_oci_srv, 0, OCI_ATTR_SERVER, this->m_p_oci_err);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);

	result = OCIHandleAlloc(this->m_p_oci_env, (dvoid**)&m_p_oci_sess, OCI_HTYPE_SESSION, 0, 0);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);

	result = OCIAttrSet(this->m_p_oci_sess, OCI_HTYPE_SESSION, (dvoid*)username, (ub4)strlen(username), OCI_ATTR_USERNAME, this->m_p_oci_err);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);

	result = OCIAttrSet(this->m_p_oci_sess, OCI_HTYPE_SESSION, (dvoid*)password, (ub4)strlen(password), OCI_ATTR_PASSWORD, this->m_p_oci_err);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);

	result = OCIHandleAlloc(this->m_p_oci_env, (dvoid**)&this->m_p_oci_desc, OCI_HTYPE_DESCRIBE, 0, 0);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);
	
	result = OCISessionBegin(this->m_p_oci_svc, this->m_p_oci_err, this->m_p_oci_sess, OCI_CRED_RDBMS, OCI_DEFAULT);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);

	result = OCIAttrSet(this->m_p_oci_svc, OCI_HTYPE_SVCCTX, this->m_p_oci_sess, 0, OCI_ATTR_SESSION, this->m_p_oci_err);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);

	result = OCIHandleAlloc(this->m_p_oci_env, (dvoid**)&this->m_p_oci_trans, OCI_HTYPE_TRANS, 0, 0);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);

	result = OCIAttrSet(this->m_p_oci_svc, OCI_HTYPE_SVCCTX, this->m_p_oci_trans, 0, OCI_ATTR_TRANS, this->m_p_oci_err);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);

	m_bConnected = true;
}

void COciConnection::DisConnect()
{
	if(!m_bConnected)
		return;

	sword result = OCISessionEnd(this->m_p_oci_svc, this->m_p_oci_err, this->m_p_oci_sess, (ub4)OCI_DEFAULT);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);

	result = OCIServerDetach(this->m_p_oci_srv, this->m_p_oci_err, (ub4)OCI_DEFAULT);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);

	result = OCIHandleFree(this->m_p_oci_trans, OCI_HTYPE_TRANS);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);

	result = OCIHandleFree(this->m_p_oci_sess, OCI_HTYPE_SESSION);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);

	result = OCIHandleFree(this->m_p_oci_svc, OCI_HTYPE_SVCCTX);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);

	result = OCIHandleFree(this->m_p_oci_desc, OCI_HTYPE_DESCRIBE);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);
	
	m_bConnected = false;
}










/////////////////////////////////////////////////////////////////
//															   //
//			Class COciSQLCursor Implementation				   //
//															   //
/////////////////////////////////////////////////////////////////


COciSQLCursor::COciSQLCursor(const COciDatabase& db)
{
	this->m_p_oci_env = db.m_p_oci_env;
	this->m_p_oci_err = db.m_p_oci_err;
	this->m_p_oci_srv = db.m_p_oci_srv;

	m_p_oci_svc			= NULL;
	m_p_oci_stmt		= NULL;
	m_p_oci_param		= NULL;
	m_pp_oci_defs		= NULL;

	m_p_binder			= NULL;

	m_nBlobCount		= 0;
	m_pBlobBuffer		= NULL;

	m_pNullIndicators	= NULL;

	m_ppNewValuesBuf	= NULL;
	m_ppBuffers			= NULL;

	m_nColumnCount		= 0;
	m_pColScales		= NULL;
	m_pColSizes			= NULL;
	m_pColTypes			= NULL;
	m_ppColNames		= NULL;

	m_bUpdateAddNew		= false;
	m_bQueryAlloc		= false;

	sword result = OCIHandleAlloc(this->m_p_oci_env, (dvoid**)&this->m_p_oci_stmt, OCI_HTYPE_STMT, 0, 0);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);

}

COciSQLCursor::~COciSQLCursor()
{
	ReleaseQueryResult();
	sword result = OCIHandleFree(this->m_p_oci_stmt, OCI_HTYPE_STMT);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);
}

void  COciSQLCursor::PrepareSQLStatement(const char* pszSQLStatement) const
{
	if(pszSQLStatement == NULL)
		throw COciException("传入的字符串不可以为空!\n", __FILE__, __LINE__);

	sword result = OCIStmtPrepare(this->m_p_oci_stmt, this->m_p_oci_err, (text*)pszSQLStatement,
		(ub4)strlen(pszSQLStatement), OCI_NTV_SYNTAX, OCI_DEFAULT);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);
}


/******************************************************************************************

GetSQLQueryType() 函数的可能返回值:

#define  OCI_STMT_SELECT  1                              // select statement
#define  OCI_STMT_UPDATE  2                              // update statement
#define  OCI_STMT_DELETE  3                              // delete statement
#define  OCI_STMT_INSERT  4                              // Insert Statement
#define  OCI_STMT_CREATE  5                              // create statement
#define  OCI_STMT_DROP    6                              // drop statement
#define  OCI_STMT_ALTER   7                              // alter statement 
#define  OCI_STMT_BEGIN   8								 // begin ... (pl/sql statement)
#define  OCI_STMT_DECLARE 9								 // declare .. (pl/sql statement )

********************************************************************************************/
long COciSQLCursor::GetSQLQueryType() const
{
	unsigned short  query_type = 0;
	sword result = OCIAttrGet(this->m_p_oci_stmt, OCI_HTYPE_STMT, (ub2*)&query_type, 
		NULL, OCI_ATTR_STMT_TYPE, this->m_p_oci_err);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);

	return (long)query_type;
}

char* COciSQLCursor::GetSQLQueryTypeName() const
{
	long lQueryType = GetSQLQueryType();
	
	memset(m_szOutput, 0, OUT_BUF_SIZE);

	switch(lQueryType)
	{
	case OCI_STMT_SELECT:  sprintf(m_szOutput, "SELECT" );  break;
	case OCI_STMT_UPDATE:  sprintf(m_szOutput, "UPDATE" );  break;                             
	case OCI_STMT_DELETE:  sprintf(m_szOutput, "DELETE" );  break; 
	case OCI_STMT_INSERT:  sprintf(m_szOutput, "INSERT" );  break;
	case OCI_STMT_CREATE:  sprintf(m_szOutput, "CREATE" );  break;
	case OCI_STMT_DROP:    sprintf(m_szOutput, "DROP"   );  break;
	case OCI_STMT_ALTER:   sprintf(m_szOutput, "ALTER"  );  break;
	case OCI_STMT_BEGIN:   sprintf(m_szOutput, "BEGIN"  );  break;
	case OCI_STMT_DECLARE: sprintf(m_szOutput, "DECLARE");  break;
	default:			   sprintf(m_szOutput, "UNKNOWN");  break;
	}
	
	return m_szOutput;
}


// 1> 对于 select 语句参数为 0
// 2> 对于其他类型的语句, 参数必须为 1 以上。
void COciSQLCursor::Execute(int times /*=0*/) const
{
	if(GetSQLQueryType() == OCI_STMT_SELECT) // 对于 SELECT 类型查询语句, 必须为 0。
	{
		if(times != 0)
			times = 0;
	}
	else									 // 其他类型语句至少为 1。
	{
		if(times <= 0)
			times = 1;
	}

	/*
	if(GetSQLQueryType() != OCI_STMT_SELECT) // 创建事务
	{
		sword result = OCITransStart(this->m_p_oci_svc, this->m_p_oci_err, 60, OCI_TRANS_NEW);
		if(result != OCI_SUCCESS)
			throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);	
	}
	*/
	
	// 注意 OCISnapshot 描述符。
	sword result = OCIStmtExecute(this->m_p_oci_svc, this->m_p_oci_stmt, this->m_p_oci_err,
		(ub4)times, 0, NULL, NULL, OCI_DEFAULT );
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);	
}

void COciSQLCursor::OpenSQLStatement(const char* pszSQLStatement)
{
	if(pszSQLStatement == NULL)
		throw COciException("传入的字符串不可以为空!\n", __FILE__, __LINE__);
	
	memset(m_szTableName, 0, 128);
	int  nLen = (int)strlen(pszSQLStatement);
	char szTemp[1024] = {0};
	for(int k = 0; k<nLen; k++)
		szTemp[k] = toupper(pszSQLStatement[k]);
	char* pszFrom = strstr(szTemp, "FROM");
	char* pszWhere = strstr(szTemp, "WHERE");
	if(pszWhere != NULL)
	{
		strncpy(m_szTableName, pszFrom + 4, pszWhere - (pszFrom + 4) );
	}
	else
	{
		strcpy(m_szTableName, pszFrom + 4);
	}


	char szSQL[1024] = {0};
	sprintf(szSQL, "%s FOR UPDATE", pszSQLStatement);

	PrepareSQLStatement(szSQL);
	
	if(GetSQLQueryType() != OCI_STMT_SELECT)
		throw COciException("必须使用 Select 类型的查询语句!\n", __FILE__, __LINE__);
	
	Execute();
	
	AllocAndGetQueryResult();
}

void COciSQLCursor::OpenTable(const char* pszTableName)
{
	if(pszTableName == NULL)
		throw COciException("传入的字符串不可以为空!\n", __FILE__, __LINE__);

	char szBuf[256] = {0};
	sprintf(szBuf, "SELECT * FROM %s", pszTableName);

	OpenSQLStatement(szBuf);
}

void COciSQLCursor::CloseQuery()
{
	ReleaseQueryResult();
}



char* COciSQLCursor::GetColumnTypeName(int iColIndex) const
{
	long lType = GetColumnType(iColIndex);

	memset(m_szOutput, 0, OUT_BUF_SIZE);

	switch(lType)
	{
	case SQLT_AFC:
	case SQLT_VCS:
	case SQLT_CHR:
		sprintf(m_szOutput, "VARCHAR2");
		break;
	case SQLT_DAT:
		sprintf(m_szOutput, "DATE");
		break;
	case SQLT_INT:
		sprintf(m_szOutput, "INTEGER");
		break;
	case SQLT_UIN:
		sprintf(m_szOutput, "UNSIGNED INTEGER");
		break;
	case SQLT_FLT:
		sprintf(m_szOutput, "FLOAT");
		break;
	case SQLT_BLOB:
	case SQLT_BIN:
		sprintf(m_szOutput, "BLOB");
		break;
	case SQLT_NUM:
		sprintf(m_szOutput, "NUMBER");
		break;
	default:
		sprintf(m_szOutput, "UNKNOWN");
		break;
	}

	return m_szOutput;
}


long COciSQLCursor::GetColumnType(int iColIndex) const
{
	return m_pColTypes[iColIndex];
}

long COciSQLCursor::GetColumnSize(int iColIndex) const
{
	return m_pColSizes[iColIndex];
}

long COciSQLCursor::GetColumnScale(int iColIndex) const
{
	return m_pColScales[iColIndex];
}

char* COciSQLCursor::GetColumnName(int iColIndex)  const
{
	return m_ppColNames[iColIndex];
}

long COciSQLCursor::GetColumnIndexByName(const char* szFieldName) const 
{
	if(szFieldName == NULL)
		throw COciException("传入的字段名称不能为空!\n", __FILE__, __LINE__);

	long nColumnCount = GetColumnCount();
	long i;
	for(i= 0; i<nColumnCount; i++)
	{
		if(stricmp(GetColumnName(i), szFieldName) == 0)
			break;
	}

	if(i == nColumnCount)
		throw COciException("传入的字段名称无效!\n", __FILE__, __LINE__);

	return i;
}

bool COciSQLCursor::Fetch(int nRows /*= 1*/) const
{
	sword result = OCIStmtFetch(this->m_p_oci_stmt, this->m_p_oci_err, (ub4)nRows, 
		OCI_FETCH_NEXT, OCI_DEFAULT);
	
	if(result == OCI_NO_DATA)
		return false;

	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);	

	return true;
}


bool COciSQLCursor::IsFieldNull(int iFieldIndex) const
{
	if(!m_bQueryAlloc)
		throw COciException("没有查询结果!\n", __FILE__, __LINE__);

	if(m_pNullIndicators == NULL)
		throw COciException("查询结果丢失!\n", __FILE__, __LINE__);

	if(m_pNullIndicators[iFieldIndex] == -1)
		return true;

	return false;
}

bool COciSQLCursor::IsFieldNull(const char* szFieldName) const
{
	long index = GetColumnIndexByName(szFieldName);
	return IsFieldNull(index);
}


int	COciSQLCursor::GetValueInt(int iFieldIndex) const
{
	if(!m_bQueryAlloc)
		throw COciException("没有查询结果!\n", __FILE__, __LINE__);

	if(m_ppBuffers == NULL)
		throw COciException("查询结果丢失!\n", __FILE__, __LINE__);

	if(IsFieldNull(iFieldIndex))
		return 0;

	return *(int*)m_ppBuffers[iFieldIndex];
}

int COciSQLCursor::GetValueInt(const char* szFieldName) const
{
	long index = GetColumnIndexByName(szFieldName);
	return GetValueInt(index);
}

char* COciSQLCursor::GetValueString(int iFieldIndex) const
{
	if(!m_bQueryAlloc)
		throw COciException("没有查询结果!\n", __FILE__, __LINE__);

	if(m_ppBuffers == NULL)
		throw COciException("查询结果丢失!\n", __FILE__, __LINE__);

	memset(m_szOutput, 0, OUT_BUF_SIZE);
	
	if(IsFieldNull(iFieldIndex))
	{
		sprintf(m_szOutput, STR_NULL);
		return m_szOutput;
	}

	char* pszBuf = (char*)m_ppBuffers[iFieldIndex];

	for(int i=0; i<OUT_BUF_SIZE - 1; i++)
	{
		if(pszBuf[i] == 0)
			break;

		m_szOutput[i] = pszBuf[i];
	}

	return m_szOutput;
}

char* COciSQLCursor::GetValueString(const char* szFieldName) const
{
	int index = GetColumnIndexByName(szFieldName);
	return GetValueString(index);
}

double COciSQLCursor::GetValueDouble(int iFieldIndex) const
{
	if(!m_bQueryAlloc)
		throw COciException("没有查询结果!\n", __FILE__, __LINE__);

	if(m_ppBuffers == NULL)
		throw COciException("查询结果丢失!\n", __FILE__, __LINE__);

	if(IsFieldNull(iFieldIndex))
		return 0;

	return *(double*) m_ppBuffers[iFieldIndex];
}


double COciSQLCursor::GetValueDouble(const char* szFieldName) const
{
	int index = GetColumnIndexByName(szFieldName);
	return GetValueDouble(index);
}

double COciSQLCursor::GetValueNumber(int iFieldIndex) const
{
	if(!m_bQueryAlloc)
		throw COciException("没有查询结果!\n", __FILE__, __LINE__);

	if(m_ppBuffers == NULL)
		throw COciException("查询结果丢失!\n", __FILE__, __LINE__);

	if(IsFieldNull(iFieldIndex))
		return 0;

	double	value = 0;

	sword result = OCINumberToReal(this->m_p_oci_err, (OCINumber*)m_ppBuffers[iFieldIndex],
		(uword)sizeof(double), (dvoid*)&value);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result,  __FILE__, __LINE__);

	return value;
}

double COciSQLCursor::GetValueNumber(const char* szFieldName) const
{
	int index = GetColumnIndexByName(szFieldName);
	return GetValueNumber(index);
}

char* COciSQLCursor::GetValueDate(int iFieldIndex) const
{
	if(!m_bQueryAlloc)
		throw COciException("没有查询结果!\n", __FILE__, __LINE__);

	if(m_ppBuffers == NULL)
		throw COciException("查询结果丢失!\n", __FILE__, __LINE__);

	memset(m_szOutput, 0, OUT_BUF_SIZE);
	if(IsFieldNull(iFieldIndex))
	{
		strcpy(m_szOutput, STR_NULL);
		return m_szOutput;
	}

	const oratext* fmt = (oratext*)"yyyy-mm-dd hh24:mi:ss";
	int nLen = OUT_BUF_SIZE;
	sword result = OCIDateToText(this->m_p_oci_err, (OCIDate*)m_ppBuffers[iFieldIndex],
		fmt, (int)strlen((char*)fmt), NULL, 0, (ub4*)&nLen, (oratext*)m_szOutput);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result,  __FILE__, __LINE__);

	return m_szOutput;
}

char*  COciSQLCursor::GetValueDate(const char* szFieldName) const
{
	int index = GetColumnIndexByName(szFieldName);
	return GetValueDate(index);
}

char* COciSQLCursor::GetFieldValue(int iFieldIndex, int& nLen) const
{
	long lType = GetColumnType(iFieldIndex);
	
	memset(m_szOutput, 0, OUT_BUF_SIZE);
	
	switch(lType)
	{
	case SQLT_INT:	// Type Integer
		sprintf(m_szOutput, "%d", GetValueInt(iFieldIndex));
		nLen = (int)strlen(m_szOutput);
		break;

	case SQLT_NUM:	// Type Number
		sprintf(m_szOutput, "%0.11g", GetValueNumber(iFieldIndex));
		nLen = (int)strlen(m_szOutput);
		break;

	case SQLT_FLT:	// Type Float / Double
		sprintf(m_szOutput, "%g", GetValueNumber(iFieldIndex));
		nLen = (int)strlen(m_szOutput);
		break;

	case SQLT_AFC:	// Type Ansi fixed char
	case SQLT_VCS:  // Type variable character string
	case SQLT_CHR:  // Type Oracle character string
		GetValueString(iFieldIndex);
		nLen = (int)strlen(m_szOutput);
		break;
		
	case SQLT_BLOB:
		return GetBlobData(iFieldIndex, nLen);

	case SQLT_DAT:
		GetValueDate(iFieldIndex);
		nLen = (int)strlen(m_szOutput);
		break;

	default:
		char szOut[128] = {0};
		sprintf(szOut, "不支持的数据类型: %d.\n" , lType);
		throw COciException(szOut, __FILE__, __LINE__);
	}

	return m_szOutput;
}


char* COciSQLCursor::GetFieldValue(const char* szFieldName, int& nLen) const
{
	int index = GetColumnIndexByName(szFieldName);
	return GetFieldValue(index, nLen);
}

char* COciSQLCursor::GetBlobData(const char* szFieldName, int& nLen) const
{
	long index = GetColumnIndexByName(szFieldName);
	return GetBlobData(index, nLen);
}

char* COciSQLCursor::GetBlobData(int iFieldIndex, int& nLen) const
{	
	nLen = 0;

	if(m_p_binder == NULL)
		throw COciException("还没有进行 BlobLocator 与字段的绑定操作.\n", __FILE__, __LINE__);

	int i;
	for(i=0; i<m_nBlobCount; i++)
	{
		if(m_p_binder[i].iIndex == iFieldIndex)
			break;
	}

	if(i == m_nBlobCount)
		throw COciException("传入的字段索引号无效!\n", __FILE__, __LINE__);

	
	if(m_pBlobBuffer != NULL)
	{
		delete [] m_pBlobBuffer;
		m_pBlobBuffer = NULL;
	}

	if(IsFieldNull(iFieldIndex))
	{
		nLen = (int)strlen(STR_NULL);
		m_pBlobBuffer = new char[nLen + 1];
		memset(m_pBlobBuffer, 0, nLen + 1);
		strcpy(m_pBlobBuffer, STR_NULL);
		return m_pBlobBuffer;
	}
	
	sword result = 0;

	result = OCILobOpen(this->m_p_oci_svc, this->m_p_oci_err, m_p_binder[i].lobl, OCI_LOB_READONLY);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);

	nLen = 0;
	result = OCILobGetLength(this->m_p_oci_svc, this->m_p_oci_err, m_p_binder[i].lobl, (ub4*)&nLen);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);
	
	if(nLen == 0)
	{
		nLen = (int)strlen(STR_EMPTY_BLOB);
		m_pBlobBuffer = new char[nLen + 1];
		memset(m_pBlobBuffer, 0, nLen + 1);
		strcpy(m_pBlobBuffer, STR_EMPTY_BLOB);
		
		result = OCILobClose(this->m_p_oci_svc, this->m_p_oci_err, m_p_binder[i].lobl);
		return m_pBlobBuffer;
	}

	m_pBlobBuffer = new char[nLen + 1];
	memset(m_pBlobBuffer, 0, nLen + 1);

	result = OCILobRead(this->m_p_oci_svc, this->m_p_oci_err, m_p_binder[i].lobl, (ub4*)&nLen, 1, 
		m_pBlobBuffer, nLen, 0, 0, 0, SQLCS_IMPLICIT);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);	

	result = OCILobClose(this->m_p_oci_svc, this->m_p_oci_err, m_p_binder[i].lobl);
	return m_pBlobBuffer;
}

void COciSQLCursor::Commit(bool bRollback /*= true*/) const
{
	sword result = OCITransCommit(this->m_p_oci_svc, this->m_p_oci_err, (ub4)0);
	if(result != OCI_SUCCESS)
	{
		if(bRollback)
		{
			result = OCITransRollback(this->m_p_oci_svc, this->m_p_oci_err, (ub4)0);
			if(result != OCI_SUCCESS)
				throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);	
		}
		else
		{
			throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);
		}
	}	
}



void  COciSQLCursor::UpdateTable()
{
	char* szSQL = NULL;
	
	if(m_bUpdateAddNew)
	{
		szSQL = CreateSQLStatement(SQL_STATEMENT_INSERT);
	}
	else
	{
		szSQL = CreateSQLStatement(SQL_STATEMENT_UPDATE);
	}

	m_bUpdateAddNew = false;
	PrepareSQLStatement(szSQL);
	Execute();
	Commit();
}












void COciSQLCursor::SetValueInt(int iFieldIndex, int value)
{
	this->m_ppNewValuesBuf[iFieldIndex] = new int;
	memcpy(this->m_ppNewValuesBuf[iFieldIndex], &value, sizeof(int));
}

void COciSQLCursor::SetValueInt(const char* szFieldName, int value)
{
	int index = GetColumnIndexByName(szFieldName);
	SetValueInt(index, value);
}

void COciSQLCursor::SetValueDouble(int iFieldIndex, double value)
{
	this->m_ppNewValuesBuf[iFieldIndex] = new double;
	memcpy(this->m_ppNewValuesBuf[iFieldIndex], &value, sizeof(double));
}

void COciSQLCursor::SetValueDouble(const char* szFieldName, double value)
{
	int index = GetColumnIndexByName(szFieldName);
	SetValueDouble(index, value);
}

void COciSQLCursor::SetValueString(int iFieldIndex, const char* value)
{
	size_t len = strlen(value);
	this->m_ppNewValuesBuf[iFieldIndex] = new char[len + 1];
	memset(this->m_ppNewValuesBuf[iFieldIndex], 0, len+1);
	strcpy((char*)this->m_ppNewValuesBuf[iFieldIndex], value);
}


void COciSQLCursor::SetValueString(const char* szFieldName, const char* value)
{
	int index = GetColumnIndexByName(szFieldName);
	SetValueString(index, value);
}

void COciSQLCursor::SetValueNumber(int iFieldIndex, double value)
{
	this->m_ppNewValuesBuf[iFieldIndex] = new double;
	memcpy(this->m_ppNewValuesBuf[iFieldIndex], &value, sizeof(double));
}

void COciSQLCursor::SetValueNumber(const char* szFieldName, double value)
{
	int index = GetColumnIndexByName(szFieldName);
	SetValueNumber(index, value);
}

void COciSQLCursor::SetValueNull(int iFieldIndex)
{
	this->m_ppNewValuesBuf[iFieldIndex] = (void*)(long)0xFFFFFFFF;
}

void COciSQLCursor::SetValueNull(const char* szFieldName)
{
	int index = GetColumnIndexByName(szFieldName);
	SetValueNull(index);
}

void COciSQLCursor::SetBlobData(int iFieldIndex, const char* pData, int nLen)
{
	if(pData == NULL)
	{
		SetValueNull(iFieldIndex);
		return;
	}

	if(m_p_binder == NULL)
		throw COciException("还没有进行 BlobLocator 与字段的绑定操作.\n", __FILE__, __LINE__);

	int i;
	for(i=0; i<m_nBlobCount; i++)
	{
		if(m_p_binder[i].iIndex == iFieldIndex)
			break;
	}

	if(i == m_nBlobCount)
		throw COciException("传入的字段索引号无效!\n", __FILE__, __LINE__);

	sword result = OCILobOpen(this->m_p_oci_svc, this->m_p_oci_err, m_p_binder[i].lobl, OCI_LOB_READWRITE);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);

	int len = nLen;
	result = OCILobWrite(this->m_p_oci_svc, this->m_p_oci_err, 
		m_p_binder[i].lobl, (ub4*)&len, 1, (void*)pData, len, OCI_ONE_PIECE, 0, 0, 0, SQLCS_IMPLICIT);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);

	result = OCILobClose(this->m_p_oci_svc, this->m_p_oci_err, m_p_binder[i].lobl);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);
}


void COciSQLCursor::SetBlobData(const char* szFieldName, const char* pData, int nLen)
{
	int index = GetColumnIndexByName(szFieldName);
	SetBlobData(index, pData, nLen);
}

void COciSQLCursor::SetValueDate(int iFieldIndex, const char* date)
{
	throw COciException("SetFieldValue 尚未实现!", __FILE__, __LINE__);
}

void COciSQLCursor::SetValueDate(const char* szFieldName, const char* date)
{
	int index = GetColumnIndexByName(szFieldName);
	SetValueDate(index, date);
}

void COciSQLCursor::SetFieldValue(int iFieldIndex, const char* szValue)
{
	throw COciException("SetFieldValue 尚未实现!", __FILE__, __LINE__);
}
//设置串型数据
void COciSQLCursor::SetStrValue(int iIndex, const char* szValue, int& nSize)
{
	OCIBind* pBind = 0;

	sword result = OCIBindByPos(this->m_p_oci_stmt, &pBind, this->m_p_oci_err, iIndex, (dvoid*)szValue, (sb4)nSize, SQLT_CHR, NULL, NULL, NULL, 0, NULL, (ub4)OCI_DEFAULT);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);
}

//设置整型数据
void COciSQLCursor::SetIntValue(int iIndex, int& nValue)
{
	OCIBind* pBind = 0;

	sword result = OCIBindByPos(this->m_p_oci_stmt, &pBind, this->m_p_oci_err, iIndex, (dvoid*)&nValue, (sb4)sizeof(int), SQLT_INT, NULL, NULL, NULL, 0, NULL, (ub4)OCI_DEFAULT);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);
}

//设置单精度浮点型数据
void COciSQLCursor::SetFltValue(int iIndex, float& nValue)
{
	OCIBind* pBind = 0;

	sword result = OCIBindByPos(this->m_p_oci_stmt, &pBind, this->m_p_oci_err, iIndex, (dvoid*)&nValue, (sb4)sizeof(float), SQLT_FLT, NULL, NULL, NULL, 0, NULL, (ub4)OCI_DEFAULT);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);
}

//设置双精度浮点数
void COciSQLCursor::SetDlbValue(int iIndex, double& nValue)
{
	OCIBind* pBind = 0;

	sword result = OCIBindByPos(this->m_p_oci_stmt, &pBind, this->m_p_oci_err, iIndex, (dvoid*)&nValue, (sb4)sizeof(double), SQLT_FLT, NULL, NULL, NULL, 0, NULL, (ub4)OCI_DEFAULT);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);
}

//设置无符号整型值
void COciSQLCursor::SetUIntValue(int iIndex, unsigned int& nValue)
{
	OCIBind* pBind = 0;

	sword result = OCIBindByPos(this->m_p_oci_stmt, &pBind, this->m_p_oci_err, iIndex, (dvoid*)&nValue, (sb4)sizeof(unsigned int), SQLT_UIN, NULL, NULL, NULL, 0, NULL, (ub4)OCI_DEFAULT);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);
}

//设置长双精度型值
void COciSQLCursor::SetLDlbValue(int iIndex, long double& nValue)
{
	OCIBind* pBind = 0;

	sword result = OCIBindByPos(this->m_p_oci_stmt, &pBind, this->m_p_oci_err, iIndex, (dvoid*)&nValue, (sb4)sizeof(long double), SQLT_FLT, NULL, NULL, NULL, 0, NULL, (ub4)OCI_DEFAULT);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);
}

//设置Blob型值
void COciSQLCursor::SetBlbValue(int iIndex, const unsigned char* szValue, int& nSize)
{
	OCIBind* pBind = 0;
	
	//初始化lob locator
	sword result = OCIDescriptorAlloc((dvoid*)this->m_p_oci_env, (dvoid**)&m_p_oci_lobl, (ub4)OCI_DTYPE_LOB, 0, 0);
	if(result != OCI_SUCCESS)
		throw COciException("创建Lob对象失败!!!", __FILE__, __LINE__);

	//创建临时lob对象
	ub4 lobEmpty = 0;
	result = OCILobCreateTemporary(this->m_p_oci_svc, this->m_p_oci_err, m_p_oci_lobl, (ub2)0, SQLCS_IMPLICIT, OCI_TEMP_BLOB, OCI_ATTR_NOCACHE, OCI_DURATION_SESSION);//OCIAttrSet(m_p_oci_lobl, OCI_DTYPE_LOB, (dvoid*)&lobEmpty, 0, OCI_ATTR_LOBEMPTY, this->m_p_oci_err);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);
	
	//打开对象
	result = OCILobOpen(this->m_p_oci_svc, this->m_p_oci_err, m_p_oci_lobl, OCI_LOB_READWRITE);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);

	//将数据写入lob对象
	result = OCILobWriteAppend(this->m_p_oci_svc, this->m_p_oci_err, m_p_oci_lobl, (ub4*)&nSize, (void*)szValue, nSize, OCI_ONE_PIECE, NULL, NULL, 0, 0);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);

	//关闭lob对象
	result = OCILobClose(this->m_p_oci_svc, this->m_p_oci_err, m_p_oci_lobl);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);
	
	//绑定需要设置的项
	result = OCIBindByPos(this->m_p_oci_stmt, &pBind, this->m_p_oci_err, iIndex, (dvoid*)&m_p_oci_lobl, (sb4)nSize, SQLT_BLOB, 0, 0, 0, 0, 0, (ub4)OCI_DEFAULT);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);
}

//释放lob对象
void COciSQLCursor::RealseLob()
{
	sword result = OCIDescriptorFree(m_p_oci_lobl, OCI_DTYPE_LOB);

	if(result != OCI_SUCCESS)
		throw COciException("释放Lob对象失败!!!", __FILE__, __LINE__);

	m_p_oci_lobl = 0;
}




































void COciSQLCursor::DeleteCurrentRecord()
{
	char* szSQL = CreateSQLStatement(SQL_STATEMENT_DELETE);
	
	PrepareSQLStatement(szSQL);
	Execute();
	Commit();
}

void COciSQLCursor::DeleteAllRecords()
{
	char* szSQL = CreateSQLStatement(SQL_STATEMENT_DELETE_ALL);

	PrepareSQLStatement(szSQL);
	Execute();
	Commit();
}



bool  COciSQLCursor::AllocAndGetQueryResult()
{
	if(m_bQueryAlloc)
		throw COciException("错误, 上一次操作没有清空内存!\n", __FILE__, __LINE__);

	int nColumnCount = _GetColumnCount();

	m_pp_oci_defs	  = new OCIDefine* [nColumnCount];	// 输出定义
	m_ppBuffers		  = new void*	   [nColumnCount];  // 记录
	m_ppNewValuesBuf  = new void*	   [nColumnCount];  // 存储更新数据的BUFFER
	m_pNullIndicators = new short	   [nColumnCount];  // 空指示符

	m_p_binder		  = new LocatorBinder[nColumnCount];

	
	memset(m_pp_oci_defs,	  0, nColumnCount);
	memset(m_ppBuffers,		  0, nColumnCount);
	memset(m_pNullIndicators, 0, nColumnCount);
	
	memset(m_p_binder,		  0, nColumnCount);

	//[注意] 针对 void** 类型的用于存储指针列表的指针, 使用 memset
	//       无法成功的为各个指针元素初始化为 NULL, 必须使用循环。
	//memset(m_ppNewValuesBuf,  0, nColumnCount);
	for(int k=0; k<nColumnCount; k++)
		m_ppNewValuesBuf[k] = NULL;


	m_pColTypes		  = new long	   [m_nColumnCount];  // 类型
	m_pColSizes		  = new long	   [m_nColumnCount];  // 大小
	m_pColScales	  = new long	   [m_nColumnCount];  // 小数位数
	m_ppColNames	  = new char*	   [m_nColumnCount];  // 字段名称
	
	int i;
	for(i=0; i<m_nColumnCount; i++)
	{
		m_pColTypes[i]  = _GetColumnType(i);
		m_pColSizes[i]  = _GetColumnSize(i);
		m_pColScales[i] = _GetColumnScale(i);

		int nLen = (int)strlen(_GetColumnName(i));
		m_ppColNames[i] = new char[nLen + 1];
		memset(m_ppColNames[i], 0, nLen + 1);
		strcpy(m_ppColNames[i], _GetColumnName(i));
	}




	sword result = 0;

	m_nBlobCount = 0;		  // 通过循环, 得到表中 BLOB 类型字段的数量	

 	for(i=0; i<nColumnCount; i++)
	{
		switch(m_pColTypes[i])
		{
		case SQLT_INT:	// Type Integer
			m_ppBuffers[i] = new signed int;
			result = OCIDefineByPos(this->m_p_oci_stmt, &this->m_pp_oci_defs[i], this->m_p_oci_err, i+1,
				(dvoid*)(signed int*)this->m_ppBuffers[i], (sb4)sizeof(signed int), (ub2)m_pColTypes[i] /*SQL_INT ?*/, 
				(dvoid*)&this->m_pNullIndicators[i], 0, 0, OCI_DEFAULT);
			if(result != OCI_SUCCESS)
				throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);	

			break;

		case SQLT_NUM:	// Type Number
			m_ppBuffers[i] = (OCINumber*) new OCINumber;
			result = OCIDefineByPos(this->m_p_oci_stmt, &this->m_pp_oci_defs[i], this->m_p_oci_err, i+1,
				(dvoid*)this->m_ppBuffers[i], sizeof(OCINumber), SQLT_VNU /*SQL_NUM ?*/,
				(dvoid*)&this->m_pNullIndicators[i], 0, 0, OCI_DEFAULT);
			if(result != OCI_SUCCESS)
				throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);	

			break;

		case SQLT_FLT:	// Type Float / Double
			m_ppBuffers[i] = new double;
			result = OCIDefineByPos(this->m_p_oci_stmt, &this->m_pp_oci_defs[i], this->m_p_oci_err, i+1,
				(dvoid*)this->m_ppBuffers[i], (ub4)sizeof(double), SQLT_FLT,
				(dvoid*)&this->m_pNullIndicators[i], 0, 0, OCI_DEFAULT);
			if(result != OCI_SUCCESS)
				throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);	

			break;

		case SQLT_AFC:	// Type Ansi fixed char
		case SQLT_VCS:  // Type variable character string
		case SQLT_CHR:  // Type Oracle character string
			m_ppBuffers[i] = (char*) new char[m_pColSizes[i] + 1];
			memset(m_ppBuffers[i], 0, m_pColSizes[i] + 1);
			result = OCIDefineByPos(this->m_p_oci_stmt, &this->m_pp_oci_defs[i], this->m_p_oci_err, i+1,
				(dvoid*)this->m_ppBuffers[i], m_pColSizes[i] + 1, SQLT_STR,
				(dvoid*)&this->m_pNullIndicators[i], 0, 0, OCI_DEFAULT);
			if(result != OCI_SUCCESS)
				throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);	

			break;
		
		case SQLT_DAT:
			m_ppBuffers[i] = (OCIDate*) new OCIDate;
			result = OCIDefineByPos(this->m_p_oci_stmt, &this->m_pp_oci_defs[i], this->m_p_oci_err, i+1,
				(dvoid*)this->m_ppBuffers[i], sizeof(OCIDate), SQLT_ODT  ,
				(dvoid*)&this->m_pNullIndicators[i], 0, 0, OCI_DEFAULT);
			if(result != OCI_SUCCESS)
				throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);	
			break;

		case SQLT_BLOB: // Type binary lob
			
			strcpy(this->m_p_binder[m_nBlobCount].szFieldName, GetColumnName(i));
			this->m_p_binder[m_nBlobCount].bAlloc = true;
			this->m_p_binder[m_nBlobCount].iIndex = i;
			result = OCIDescriptorAlloc(this->m_p_oci_env, (dvoid**)&this->m_p_binder[m_nBlobCount].lobl,
				OCI_DTYPE_LOB, 0, 0);
			if(result != OCI_SUCCESS)
				throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);	

			result = OCIDefineByPos(this->m_p_oci_stmt, &this->m_pp_oci_defs[i], this->m_p_oci_err, i+1,
				(dvoid*)&this->m_p_binder[m_nBlobCount].lobl, 0, SQLT_BLOB,
				(dvoid*)&this->m_pNullIndicators[i], 0, 0, OCI_DEFAULT);
			if(result != OCI_SUCCESS)
				throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);	
			
			m_nBlobCount++;
			break;

		default:
			
			break;
		}
	}

	m_bQueryAlloc = true;
	return true;
}

void  COciSQLCursor::ReleaseQueryResult()
{
	if(!m_bQueryAlloc)
		return;

	if(m_pBlobBuffer != NULL)
	{
		delete []m_pBlobBuffer;
		m_pBlobBuffer = NULL;
	}

	if(m_p_binder != NULL)
	{
		for(int i=0; i<m_nBlobCount; i++)
		{
			sword result = OCIDescriptorFree(this->m_p_binder[i].lobl, OCI_DTYPE_LOB);
			if(result != OCI_SUCCESS)
				throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);	
		}
	
		delete []m_p_binder;
		m_p_binder = NULL;
		m_nBlobCount = 0;
	}

	if(m_pColTypes != NULL )
	{
		int nColumnCount = GetColumnCount();
		for(int i=0; i<nColumnCount; i++)
		{
			switch(m_pColTypes[i])
			{
			case SQLT_INT:
			case SQLT_NUM:
			case SQLT_FLT:
			case SQLT_DAT:
				delete m_ppBuffers[i];
				//if(m_ppNewValuesBuf[i] != NULL)
			
				delete m_ppNewValuesBuf[i];
				
				break;

			case SQLT_AFC:	// Type Ansi fixed char
			case SQLT_VCS:  // Type variable character string
			case SQLT_CHR:  // Type Oracle character string
				delete []m_ppBuffers[i];
				delete []m_ppNewValuesBuf[i];

				break;

			case SQLT_BLOB:
				
				delete []m_ppNewValuesBuf[i];

				break;
			}
		}
	}
	

	if(	m_ppNewValuesBuf != NULL)
	{
		delete []m_ppNewValuesBuf;
		m_ppNewValuesBuf = NULL;
	}
	

	if(m_pp_oci_defs != NULL)
	{
		delete []m_pp_oci_defs;
		m_pp_oci_defs = NULL;
	}

	if(m_ppBuffers != NULL)
	{
		delete []m_ppBuffers;
		m_ppBuffers = NULL;
	}

	if(m_ppColNames != NULL)
	{
		for(int i=0; i<m_nColumnCount; i++)
			delete []m_ppColNames[i];
		delete []m_ppColNames;
		m_ppColNames = NULL;
	}

	if(m_pColTypes != NULL)
	{
		delete []m_pColTypes;
		m_pColTypes = NULL;
	}

	if(m_pColSizes != NULL)
	{
		delete []m_pColSizes;
		m_pColSizes = NULL;
	}

	if(m_pColScales != NULL)
	{
		delete []m_pColScales;
		m_pColScales = NULL;
	}

	if(m_pNullIndicators != NULL)
	{
		delete []m_pNullIndicators;
		m_pNullIndicators = NULL;
	}

	m_bQueryAlloc = false;
}






/////////////////////////////////////////////////////////////////////
//  尚待改进的函数

long COciSQLCursor::GetRecordsCount() const
{
	throw COciException("GetRecordsCount() 函数尚待改进!(Scrollable Cursor)", __FILE__, __LINE__);
	
	long nRowCount = 0;
	sword result = OCIAttrGet(this->m_p_oci_stmt, OCI_HTYPE_STMT, &nRowCount,
		0, OCI_ATTR_ROW_COUNT, this->m_p_oci_err);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);	

	return nRowCount;
}

bool COciSQLCursor::MovePrev() const
{
	throw COciException("MovePrev() 函数尚待改进!(Scrollable Cursor)", __FILE__, __LINE__);

	sword result = OCIStmtFetch2(this->m_p_oci_stmt, this->m_p_oci_err, (ub4)1, 
		OCI_FETCH_PRIOR, 0, OCI_DEFAULT);
	
	if(result == OCI_NO_DATA)
		return false;

	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);	

	return true;
}

bool COciSQLCursor::MoveNext() const
{
	throw COciException("MoveNext() 函数尚待改进!(Scrollable Cursor)", __FILE__, __LINE__);

	sword result = OCIStmtFetch2(this->m_p_oci_stmt, this->m_p_oci_err, (ub4)1, 
		OCI_FETCH_NEXT, 0, OCI_DEFAULT);
	
	if(result == OCI_NO_DATA)
		return false;

	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);	
	
	return true;
}

bool COciSQLCursor::MoveFirst() const
{
	throw COciException("MoveFirst() 函数尚待改进!(Scrollable Cursor)", __FILE__, __LINE__);

	sword result = OCIStmtFetch2(this->m_p_oci_stmt, this->m_p_oci_err, (ub4)1, 
		OCI_FETCH_FIRST, 0, OCI_DEFAULT);
	
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);	

	return true;
}

bool COciSQLCursor::MoveLast() const
{
	throw COciException("MoveLast() 函数尚待改进!(Scrollable Cursor)", __FILE__, __LINE__);

	sword result = OCIStmtFetch2(this->m_p_oci_stmt, this->m_p_oci_err, (ub4)1, 
		OCI_FETCH_LAST, 0, OCI_DEFAULT);

	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);	

	return true;
}



void  COciSQLCursor::UpdateBlobDatas()
{
	throw COciException("UpdateBlobDatas() 函数尚待改进!", __FILE__, __LINE__);

	char szSQLStatement[1024] = {0};
	sprintf(szSQLStatement, "SELECT ");

	bool bBlobFieldChanges = false;

	int i;
	for(i=0; i<m_nBlobCount; i++)
	{
		if(m_ppNewValuesBuf[m_p_binder[i].iIndex] == NULL)  // 没有设置 BLOB 值
			continue;

		if((long)m_ppNewValuesBuf[m_p_binder[i].iIndex] == 0xFFFFFFFF) // 设置 BLOB 字段为 NULL
			continue;

		bBlobFieldChanges = true;

		sprintf(&szSQLStatement[strlen(szSQLStatement)], "%s,", m_p_binder[i].szFieldName);
	}

	if(!bBlobFieldChanges)
		return ;

	

	void** ppNewValuesBufPrev = m_ppNewValuesBuf;
	ReleaseQueryResult();

	szSQLStatement[strlen(szSQLStatement) - 1] = ' ';
	sprintf(&szSQLStatement[strlen(szSQLStatement)], " FROM %s ", m_szTableName);

	char szCondition[1024] = {0};
	CreateQueryCondition(szCondition, 1024);

	strcat(szSQLStatement, szCondition);

	PrepareSQLStatement(szSQLStatement);
	Execute();
	AllocAndGetQueryResult();
	Fetch();

	for(i=0; i<m_nBlobCount; i++)
	{
		int nLen = (int)strlen((char*)ppNewValuesBufPrev[m_p_binder[i].iIndex]);

		sword result = OCILobWrite(this->m_p_oci_svc, this->m_p_oci_err, m_p_binder[i].lobl, 
			(ub4*)&nLen, 1, (void*)ppNewValuesBufPrev[m_p_binder[i].iIndex], nLen, OCI_ONE_PIECE, 0, 0, 0, SQLCS_IMPLICIT);
		if(result != OCI_SUCCESS)
			throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);
	}

	Commit();

	/*
	for(int i=0; i<nColumnCount; i++)
	{
		switch(m_pColTypes[i])
		{
		case SQLT_INT:
		case SQLT_NUM:
		case SQLT_FLT:
			delete ppNewValuesBufPrev[i];
			break;

		case SQLT_AFC:	// Type Ansi fixed char
		case SQLT_VCS:  // Type variable character string
		case SQLT_CHR:  // Type Oracle character string
			delete []ppNewValuesBufPrev[i];
			break;

		case SQLT_BLOB:
			delete []ppNewValuesBufPrev[i];
			break;
		}
	}

	delete []ppNewValuesBufPrev;
	*/
}




void  COciSQLCursor::BindByPos(int pos, void* value, int size, int type, void* indicator)
{
	OCIBind *pBind;	
	sword result ;
	switch(type)
	{
	case VAR_VCHAR:
		result = OCIBindByPos(m_p_oci_stmt,&pBind,m_p_oci_err,pos,(text*)value,size,
			SQLT_STR,NULL,NULL,NULL,0, NULL, (ub4)OCI_DEFAULT);
		if(result != OCI_SUCCESS)
			throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);
		break;
	case VAR_INT:
		result = OCIBindByPos(m_p_oci_stmt,&pBind,m_p_oci_err,pos,(text*)value,size,
			SQLT_NUM,NULL,NULL,NULL,0, NULL, (ub4)OCI_DEFAULT);
		if(result != OCI_SUCCESS)
			throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);
		break;
	}
	//尚待改进
}

void COciSQLCursor::BindByName(const char* name, void* value, int size, int type, void* indicator)
{
	OCIBind *pBind;
	sword result ;
	switch(type)
	{
	case VAR_VCHAR:
		result = OCIBindByName(m_p_oci_stmt,&pBind,m_p_oci_err,(text*)name,(sb4)strlen(name),
			(dvoid*)value,(sb4)size,SQLT_STR,NULL,NULL,NULL,0, NULL, (ub4)OCI_DEFAULT);
		if(result != OCI_SUCCESS)
			throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);
		break;
	case VAR_INT:
		result = OCIBindByName(m_p_oci_stmt,&pBind,m_p_oci_err,(text*)name,(sb4)strlen(name),
			(dvoid*)value,(sb4)size,SQLT_NUM,NULL,NULL,NULL,0, NULL, (ub4)OCI_DEFAULT);
		if(result != OCI_SUCCESS)
			throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);
		break;
	}
//		throw COciException("接口尚未实现!", __FILE__, __LINE__);	
	//尚待改进
}

void COciSQLCursor::DefineByPos(int pos, void* value, int size, void* indicator, int type)
{
	throw COciException("接口尚未实现!", __FILE__, __LINE__);
	return;
	OCIDefine* pDef;
	sword result = OCIDefineByPos(m_p_oci_stmt,&pDef,m_p_oci_err,(ub4)pos,(text*)value,(sb4)size,
			SQLT_STR,NULL,NULL, NULL, (ub4)OCI_DEFAULT);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);
	//尚待改进
}


bool COciSQLCursor::GetColumnDescription()
{
	throw COciException("接口尚未实现!", __FILE__, __LINE__);
	return true;
}




////////////////////////////////////////////////////////////////
//  Private

// [注意] 浮点数的精度控制问题需要改进!!!!!!!!!!!!!!!!!
char*	COciSQLCursor::SQL_OCI_UPDATE()
{
	char szSQLStatement[1024] = {0};
	sprintf(szSQLStatement, "UPDATE %s SET ", m_szTableName);

	bool bFieldsUpdate = false;			// 检测是否存在更新字段的标记

	for(int i=0; i<GetColumnCount(); i++)
	{
		if(m_ppNewValuesBuf[i] == NULL) // 没有更新!
			continue;
		
		bFieldsUpdate = true;

		if((int)m_ppNewValuesBuf[i] == 0xFFFFFFFF)  // NULL
		{
			sprintf(&szSQLStatement[strlen(szSQLStatement)], "%s = NULL,", 
					GetColumnName(i));
			continue;
		}

		switch(GetColumnType(i))
		{
		case SQLT_AFC: 
		case SQLT_VCS:
		case SQLT_CHR:  //strings
			{
				sprintf(&szSQLStatement[strlen(szSQLStatement)], "%s = '%s',", 
					GetColumnName(i), (char*)m_ppNewValuesBuf[i]);
				break;
			}
		
		case SQLT_NUM:
			{
				
				if(GetColumnScale(i) == 0)
				{
					sprintf(&szSQLStatement[strlen(szSQLStatement)], "%s = %.0f,", 
						GetColumnName(i), *(double*)m_ppNewValuesBuf[i]);
				}
				else
				{
					char szFloat[64] = {0};
					sprintf(szFloat, "%.32f", *(double*)m_ppNewValuesBuf[i]);
					char* pszPoint = strchr(szFloat, '.');
					int nScale = GetColumnScale(i);
					szFloat[pszPoint + nScale + 1 - szFloat] = 0;
					sprintf(&szSQLStatement[strlen(szSQLStatement)], "%s = %s,",GetColumnName(i), szFloat);
				}
				break;
			
			}
		case SQLT_FLT:
			{
				//[注意] Scale 问题
				//sprintf(&szSQLStatement[strlen(szSQLStatement)], "%s = %d ", 
				//	GetColumnName(i), *(double*)m_ppNewValuesBuf[i]);
				sprintf(&szSQLStatement[strlen(szSQLStatement)], "%s = %f,", 
					GetColumnName(i), *(double*)m_ppNewValuesBuf[i]);
				break;
			}

		case SQLT_INT:
			{
				sprintf(&szSQLStatement[strlen(szSQLStatement)], "%s = %d,", 
					GetColumnName(i), *(int*)m_ppNewValuesBuf[i]);
				break;
			}
		case SQLT_BLOB:
			{
				break;
			}
		}
	}

	szSQLStatement[strlen(szSQLStatement) - 1] = '\0';

	if(!bFieldsUpdate)
		throw COciException("并没有对任何字段进行更新!\n", __FILE__, __LINE__);

	char szCondition[512] = {0};
	strcat(szSQLStatement, CreateQueryCondition(szCondition, 512));

	memset(m_szOutput, 0, OUT_BUF_SIZE);
	strcpy(m_szOutput, szSQLStatement);
	return m_szOutput;
}

char* COciSQLCursor::SQL_OCI_DELETE()
{
	char szSQLStatement[1024] = {0};
	sprintf(szSQLStatement, "DELETE FROM %s ", m_szTableName);

	char szCondition[512] = {0};
	CreateQueryCondition(szCondition, 512);

	memset(m_szOutput, 0, OUT_BUF_SIZE);
	sprintf(m_szOutput, "%s%s", szSQLStatement, szCondition);
	return m_szOutput;
}

char* COciSQLCursor::SQL_OCI_DELETE_ALL()
{
	memset(m_szOutput, 0, OUT_BUF_SIZE);
	sprintf(m_szOutput, "DELETE FROM %s", m_szTableName);
	return m_szOutput;
}

char* COciSQLCursor::SQL_OCI_INSERT()
{
	char szSQLStatement[1024] = {0};
	sprintf(szSQLStatement, "INSERT INTO %s (", m_szTableName);

	char szValues[1024] = {0};
	sprintf(szValues, " VALUES (" );

	bool bFieldsUpdate = false;

	for(int i=0; i<GetColumnCount(); i++)
	{
		if(m_ppNewValuesBuf[i] == NULL && GetColumnType(i) != SQLT_BLOB)
			continue;

		bFieldsUpdate = true;


		sprintf(&szSQLStatement[strlen(szSQLStatement)], "%s,", GetColumnName(i));



		if((int)m_ppNewValuesBuf[i] == 0xFFFFFFFF)  // NULL
		{
			sprintf(&szValues[strlen(szValues)], "NULL,");
			continue;
		}

		switch(GetColumnType(i))
		{
		case SQLT_AFC: 
		case SQLT_VCS:
		case SQLT_CHR:  //strings
			{
				sprintf(&szValues[strlen(szValues)], "'%s',", (char*)m_ppNewValuesBuf[i]);
				break;
			}
		
		case SQLT_NUM:
			{
				if(GetColumnScale(i) == 0)
				{
					sprintf(&szValues[strlen(szValues)], "%.0f,", *(double*)m_ppNewValuesBuf[i]);
				}
				else
				{
					char szFloat[64] = {0};
					sprintf(szFloat, "%.32f", *(double*)m_ppNewValuesBuf[i]);
					char* pszPoint = strchr(szFloat, '.');
					int nScale = GetColumnScale(i);
					szFloat[pszPoint + nScale + 1 - szFloat] = 0;
					sprintf(&szValues[strlen(szValues)], "%s,", szFloat);
				}
				break;
			}
		case SQLT_FLT:
			{
				
				sprintf(&szValues[strlen(szValues)], "%f,", *(double*)m_ppNewValuesBuf[i]);
				break;
			}

		case SQLT_INT:
			{
				sprintf(&szValues[strlen(szValues)], "%d,", *(int*)m_ppNewValuesBuf[i]);
				break;
			}
		case SQLT_BLOB:
			{
				sprintf(&szValues[strlen(szValues)], "empty_blob(),");
				break;
			}
		}

	}

	if(!bFieldsUpdate)
		throw COciException("并没有对任何字段进行更新!\n", __FILE__, __LINE__);

	szSQLStatement[strlen(szSQLStatement) - 1] = ')';
	szValues[strlen(szValues) - 1] = ')';
	
	memset(m_szOutput, 0, OUT_BUF_SIZE);
	sprintf(m_szOutput, "%s%s", szSQLStatement, szValues);
	return m_szOutput;
}

// [注意] 浮点数的精度控制问题需要改进!!!!!!!!!!!!!!!!!
char* COciSQLCursor::CreateQueryCondition(char szCondition[], int nLen)
{
	memset(szCondition, 0, nLen);

	for(int i = 0; i<GetColumnCount(); i++)
	{
		if(IsFieldNull(i))
		{
			if(i == 0)
			{
				sprintf(&szCondition[strlen(szCondition)], "WHERE %s IS NULL ", 
					GetColumnName(i));
			}
			else
			{
				sprintf(&szCondition[strlen(szCondition)], "AND %s IS NULL ", 
					GetColumnName(i));
			}

			continue;
		}

		switch(GetColumnType(i))
		{
		case SQLT_AFC: 
		case SQLT_VCS:
		case SQLT_CHR:  //strings
			{
				if(i == 0)
				{
					sprintf(&szCondition[strlen(szCondition)], "WHERE %s = '%s' ", 
						GetColumnName(i), (char*)m_ppBuffers[i]);
					
				}
				else
				{
					sprintf(&szCondition[strlen(szCondition)], "AND %s = '%s' ", 
						GetColumnName(i), (char*)m_ppBuffers[i]);
				}
				break;
			}
		
		case SQLT_NUM:  // Scale 的问题!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			{
				if(i == 0)
				{
					//sprintf(&szSQLStatement[strlen(szSQLStatement)], "WHERE %s = %f ", 
					//	GetColumnName(i), GetValueNumber(i));
					sprintf(&szCondition[strlen(szCondition)], "WHERE %s = %g ", 
						GetColumnName(i), GetValueNumber(i));
				}
				else
				{
					//sprintf(&szSQLStatement[strlen(szSQLStatement)], "AND %s = %f ", 
					//	GetColumnName(i), GetValueNumber(i));
					sprintf(&szCondition[strlen(szCondition)], "WHERE %s = %g ", 
						GetColumnName(i), GetValueNumber(i));
				}
				break;
			}
		
		
		case SQLT_FLT:	// Scale 的问题!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			{
				if(i == 0)
				{
					//sprintf(&szSQLStatement[strlen(szSQLStatement)], "WHERE %s = %f ", 
					//	GetColumnName(i), *(double*)m_ppBuffers[i]);
					sprintf(&szCondition[strlen(szCondition)], "WHERE %s = %g ", 
						GetColumnName(i), GetValueNumber(i));
					
				}
				else
				{
					//sprintf(&szSQLStatement[strlen(szSQLStatement)], "AND %s = %f ", 
					//	GetColumnName(i), *(double*)m_ppBuffers[i]);
					sprintf(&szCondition[strlen(szCondition)], "WHERE %s = %g ", 
						GetColumnName(i), GetValueNumber(i));
				}
				break;
			}

		case SQLT_INT:
			{
				if(i == 0)
				{
					sprintf(&szCondition[strlen(szCondition)], "WHERE %s = %d ", 
						GetColumnName(i), *(int*)m_ppBuffers[i]);
					
				}
				else
				{
					sprintf(&szCondition[strlen(szCondition)], "AND %s = %d ", 
						GetColumnName(i), *(int*)m_ppBuffers[i]);
				}
				break;
			}
		case SQLT_BLOB:
			{
				break;
			}
		}
	}

	return szCondition;
}


char* COciSQLCursor::CreateSQLStatement(int iSQLType)
{
	switch(iSQLType)
	{
	case SQL_STATEMENT_UPDATE:
		{
			SQL_OCI_UPDATE();
			break;
		}
	case SQL_STATEMENT_DELETE:
		{
			SQL_OCI_DELETE();
			break;
		}
	case SQL_STATEMENT_DELETE_ALL:
		{
			SQL_OCI_DELETE_ALL();
			break;
		}
	case SQL_STATEMENT_INSERT:
		{
			SQL_OCI_INSERT();
			break;
		}
	}

	printf("\n\n SQL 语句测试: %s\n\n", m_szOutput);

	return m_szOutput;
}

//  SQL 操作初始化应用
char* COciSQLCursor::_GetColumnName(int iColIndex) const
{
	iColIndex++;	// 注意, OCIAttrGet 中的操作是从1开始的。

	unsigned char* pszColName = NULL;
	long	       nLen = 0;

	sword result = OCIParamGet(this->m_p_oci_stmt, OCI_HTYPE_STMT, this->m_p_oci_err, 
		(dvoid**)&this->m_p_oci_param, iColIndex);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);	

	result = OCIAttrGet(this->m_p_oci_param, OCI_DTYPE_PARAM, (dvoid**)&pszColName, (ub4*)&nLen,
		OCI_ATTR_NAME, this->m_p_oci_err);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);	

	memset(m_szOutput, 0, OUT_BUF_SIZE);
	for(int i=0; i<nLen; i++)
		m_szOutput[i] = pszColName[i];
	m_szOutput[nLen] = 0;
	return m_szOutput;
}

// 在 SQL 操作初始化中使用
long COciSQLCursor::_GetColumnSize(int iColIndex) const
{
	iColIndex++;	// 注意, OCIAttrGet 中的操作是从1开始的。

	long	nColSize = 0;
	
	sword result = OCIParamGet(this->m_p_oci_stmt, OCI_HTYPE_STMT, this->m_p_oci_err, 
		(dvoid**)&this->m_p_oci_param, (ub4)iColIndex);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);	

	result = OCIAttrGet(this->m_p_oci_param, OCI_DTYPE_PARAM, (dvoid*)&nColSize, 0, 
		OCI_ATTR_DATA_SIZE, this->m_p_oci_err);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);	

	return nColSize;
}

// 在 SQL 操作初始化中使用
long COciSQLCursor::_GetColumnScale(int iColIndex) const
{
	iColIndex++;	// 注意, OCIAttrGet 中的操作是从1开始的。

	long	nColScale = 0;

	sword result = OCIParamGet(this->m_p_oci_stmt, OCI_HTYPE_STMT, this->m_p_oci_err,
		(dvoid**)&this->m_p_oci_param, iColIndex);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);	

	result = OCIAttrGet(this->m_p_oci_param, OCI_DTYPE_PARAM, (dvoid*)&nColScale, 0,
		OCI_ATTR_SCALE, this->m_p_oci_err);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);	

	return nColScale;
}

//  SQL操作初始化应用
long COciSQLCursor::_GetColumnType(int iColIndex) const
{
	iColIndex++;	// 注意, OCIAttrGet 中的操作是从1开始的。

	long type = 0;
	
	sword result = OCIParamGet(this->m_p_oci_stmt, OCI_HTYPE_STMT, this->m_p_oci_err, 
		(dvoid**)&this->m_p_oci_param, iColIndex);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);	

	result = OCIAttrGet(this->m_p_oci_param, OCI_DTYPE_PARAM, (dvoid*)&type, 0, 
		OCI_ATTR_DATA_TYPE, this->m_p_oci_err);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);	

	return type;
}

long COciSQLCursor::_GetColumnCount() 
{
	m_nColumnCount = 0;
	sword result = OCIAttrGet(this->m_p_oci_stmt, OCI_HTYPE_STMT, &m_nColumnCount,
		0, OCI_ATTR_PARAM_COUNT, this->m_p_oci_err);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);	

	return m_nColumnCount;
}





static void ShowMessage(const char* szMsg)
{
#ifdef _CONSOLE
	printf(szMsg);
#else
//	MessageBox(NULL, szMsg, "GLOBAL:ShowMessage", MB_OK);
#endif
}


/*
void  COciSQLCursor::WriteTest()
{
	sword result = 0;
	
	char* select = "SELECT * FROM TESTTABLE FOR UPDATE";
		
	OCILobLocator* lobl = NULL;

	
	result = OCIStmtPrepare(this->m_p_oci_stmt, this->m_p_oci_err, (text*)select,
		(ub4)strlen(select), OCI_NTV_SYNTAX, OCI_DEFAULT);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);

	result = OCIStmtExecute(this->m_p_oci_svc, this->m_p_oci_stmt, this->m_p_oci_err, 0, 0, 0, 0, OCI_DEFAULT);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);
	

	result = OCIDescriptorAlloc(this->m_p_oci_env, (dvoid**)&lobl, OCI_DTYPE_LOB, 0, 0);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);


	OCIDefine* def = NULL;
	result = OCIDefineByPos(this->m_p_oci_stmt, &def, this->m_p_oci_err, 3, (dvoid*)&lobl, 0, SQLT_BLOB,
		0, 0, 0, OCI_DEFAULT);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);
	
	Fetch();

	//result = OCILobOpen(this->m_p_oci_svc, this->m_p_oci_err, lobl, OCI_LOB_READWRITE);
	//if(result != OCI_SUCCESS)
	//	throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);

	const char* data = "abcd0987654321";
	int   len = strlen(data);
	result = OCILobWrite(this->m_p_oci_svc, this->m_p_oci_err, lobl, (ub4*)&len, 1, (void*)data, len, OCI_ONE_PIECE, 0, 0, 0, SQLCS_IMPLICIT);
	if(result != OCI_SUCCESS)
		throw COciException(this->m_p_oci_err, result, __FILE__, __LINE__);
}
*/


//对OCI的简单封装	lix
COciOperation::COciOperation()
{
	m_OciDatabase = NULL;
	
	m_OciConn = NULL;

	m_DBLogEvent = INVALID_HANDLE_VALUE;

	m_RecordsCount = 0;

	m_sql = NULL;
}

COciOperation::~COciOperation()
{
	Release();
}

BOOL COciOperation::Init(const char *svr_name, const char *user_name, const char *pwd)
{
	try
	{
		m_OciDatabase = COciDatabase::CreateInstance();
		m_OciDatabase->InitDatabase();
		
		m_OciConn = m_OciDatabase->CreateConnectionInstance();
		m_OciConn->Connect(svr_name, user_name, pwd);
		m_DBLogEvent = CreateEvent(NULL, FALSE, TRUE, NULL);
		InitOciSQLCur();
	}
	catch (COciException e)
	{
		m_OciDatabase = NULL;
		m_OciConn = NULL;

		CString strErr;
		char szErr[256] = {0};
		char szLog[256] = {0};
		
		//sprintf(szLog, "%s\\db.log", m_WorkPath);
		e.ShowExceptionInfo(szErr, szLog, 1);
		
		strErr.Format(_T("数据库初始化失败，原因为：\n%s"), szErr);
		ShowErrorMessage(strErr);
		return FALSE;
	}
	
	return TRUE;
}

void COciOperation::Init(COciDatabase *db, COciConnection * conn) 
{ 
	m_OciDatabase = db; 
	m_OciConn = conn;

	if(db != NULL && conn != NULL)
	{
		m_DBLogEvent = CreateEvent(NULL, FALSE, TRUE, NULL); 
		InitOciSQLCur();
	}
}

BOOL COciOperation::Release()
{
	FreeOciSQLCur();

	if(m_OciConn != NULL)
	{
		m_OciConn->DisConnect();
		m_OciConn = NULL;
	}

	if(m_OciDatabase != NULL)
	{
		m_OciDatabase->Release();
		m_OciDatabase = NULL;
	}

	if(m_DBLogEvent != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_DBLogEvent);
		m_DBLogEvent = INVALID_HANDLE_VALUE;
	}

	ClearBuf();

	return TRUE;
}

COciSQLCursor* COciOperation::CreateOciSQLCursor()
{
	if(m_OciConn == NULL || m_OciDatabase == NULL)
		return NULL;

	try
	{
		return m_OciDatabase->CreateSQLCursorInstance(m_OciConn);
	}
	catch (COciException e)
	{		
		CString strErr;
		char szErr[256] = {0};
		char szLog[256] = {0};
		
		e.ShowExceptionInfo(szErr, szLog, 1);
		
		strErr.Format(_T("创建OciSQLCursor失败，原因为：\n%s"), szErr);
		ShowErrorMessage(strErr);
		return NULL;
	}

	return NULL;
}

void COciOperation::PushData(COciSQLCursor *OciSQL)
{
	if(OciSQL == NULL)
		return;

	m_cs.Lock();

	m_SqlCur.push_back(OciSQL);

	m_cs.Unlock();
}

BOOL COciOperation::PopData(COciSQLCursor **OciSQL)
{
	m_cs.Lock();

	if(m_SqlCur.empty())
	{
		m_cs.Unlock();
		return FALSE;
	}

	*OciSQL = m_SqlCur.front();
	m_SqlCur.pop_front();

	m_cs.Unlock();
	return TRUE;
}

int COciOperation::GetDataSize()
{
	m_cs.Lock();

	int nSize = m_SqlCur.size();

	m_cs.Unlock();

	return nSize;
}

BOOL COciOperation::InitOciSQLCur()
{
	for(int i=0; i<OCI_SQL_CUR_COUNT; i++)
	{
		COciSQLCursor *OciSQL = CreateOciSQLCursor();
		PushData(OciSQL);
	}

	return TRUE;
}

BOOL COciOperation::FreeOciSQLCur()
{
	COciSQLCursor *OciSQL = NULL;
	while(PopData(&OciSQL))
		OciSQL->Release();
	return TRUE;
}

BOOL COciOperation::AddOciSQLCur()
{
	COciSQLCursor *OciSQL = CreateOciSQLCursor();
	PushData(OciSQL);
	return TRUE;
}

COciSQLCursor* COciOperation::GetSQLCursor()
{
	COciSQLCursor *OciSQL = NULL;
	while(!PopData(&OciSQL))
		AddOciSQLCur();

	return OciSQL;
}

BOOL COciOperation::ReleaseSQLCur(COciSQLCursor *OciSql)
{
	OciSql->ReleaseQueryResult();
	PushData(OciSql);
	return TRUE;
}

BOOL COciOperation::Execute(COciSQLCursor *OciSQL, const char *szSQL, int type/* = SELECT*/)
{
	if(OciSQL == NULL || szSQL == NULL || strlen(szSQL) == 0)
		return FALSE;

	//执行SQL语句出错后抛出异常
	try
	{
		switch(type)
		{
		case SELECT:
			OciSQL->PrepareSQLStatement(szSQL);
			OciSQL->Execute(0);
			OciSQL->ReleaseQueryResult();
			OciSQL->AllocAndGetQueryResult();
			SetBuf(szSQL);
			break;
		case UPDATE:
			OciSQL->PrepareSQLStatement(szSQL);
			OciSQL->Execute(0);
			OciSQL->Commit();
			ClearBuf();
			break;
		default:
			break;
		}
	}
	catch (COciException e)
	{
		CString strErr;
		CString strMsg;
		char szErr[256] = {0};
		char szLog[256] = {0};
		
//		sprintf(szLog, "%s\\%s", g_strWordPath, DB_ERR_LOG);
		e.ShowExceptionInfo(szErr, szLog, 1);
		
		strErr.Format(_T("执行SQL语句：\n%s\n出现错误，原因为：\n%s"), szSQL, szErr);
		
		strMsg.Format("[%s]\n%s\n", GetTimeString(), strErr);
		WaitForSingleObject(m_DBLogEvent, INFINITE);
		WriteDBLog("db.log", strMsg);
		SetEvent(m_DBLogEvent);
		
		ShowErrorMessage(strErr);
		return FALSE;
	}

	return TRUE;
}

void COciOperation::SetBuf(const char *szSQL)
{
	return;

	if(m_sql == NULL)
		m_sql = (char*)malloc(strlen(szSQL) + 1);
	else if(strlen(szSQL) > sizeof(m_sql))
		m_sql = (char*)realloc(m_sql, strlen(szSQL) + 1);

	memset(m_sql, 0, sizeof(m_sql));
	memcpy(m_sql, szSQL, strlen(szSQL));
}

int COciOperation::GetRecordsCount()
{//Oci自带的GetRecordsCount函数尚未完善，只能通过SQL语句来获取记录集数量

	if(m_sql == NULL || strlen(m_sql) == 0)
		return 0;

	m_RecordsCount = 0;
	COciSQLCursor *OciSQL = GetSQLCursor();
	if(OciSQL == NULL)
		return 0;
	
	int size = strlen(m_sql) + 64;
	char *szCnt = new char[size];
	memset(szCnt, 0, sizeof(szCnt));
	sprintf(szCnt, _T("SELECT COUNT(*) FROM (%s) A"), m_sql);
	
	if(!Execute(OciSQL, szCnt))
		goto exit;
	
	int len;
	char *pData;
	if (OciSQL->Fetch())
	{
		pData = OciSQL->GetFieldValue(0, len);
	}
	
	m_RecordsCount = atoi(pData);

exit:
	ReleaseSQLCur(OciSQL);
	delete[] szCnt;
	
	return m_RecordsCount;
}

BOOL COciOperation::WriteDBLog(const CString& strFileName, const CString& strMsg)
{
	CStdioFile file;
	CFileException e;
	CString strFilePath;
	CString strWrite;

	char szPath[256] = {0};
	GetCurrentDirectory(256, szPath);
	
	strFilePath.Format("%s\\%s", szPath, strFileName);
	if(!file.Open(strFilePath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite, &e))
	{
		char szMsg[128] = {0};
		e.GetErrorMessage(szMsg, 128);
		
		CString strErr;
		strErr.Format(_T("打开数据库日志文件失败，原因为: %s"), szMsg);
		ShowErrorMessage(strErr);
		return FALSE;
	}
	
	//Write String;
	file.SeekToEnd();
	file.WriteString(strMsg);
	
	file.Close();
	return TRUE;
}

CString COciOperation::GetTimeString()
{
	CString strTime;
	SYSTEMTIME st;
	GetLocalTime(&st);
	strTime.Format("%04d-%02d-%02d %02d:%02d:%02d", st.wYear, st.wMonth, st.wDay,
		st.wHour, st.wMinute, st.wSecond);
	return strTime;
}