
//��Ŀ���÷���:
//��Ŀ -> ���� -> C/C++ ����     -> ���Ӱ���Ŀ¼: D:\oracle\ora92\oci\include
//��Ŀ -> ���� -> ������ -> ���� -> ���ӿ�Ŀ¼:   D:\oracle\ora92\oci\lib\msvc
//��Ŀ -> ���� -> ������ -> ���� -> ����������:   oci.lib
#if !defined(AFX_OCI_OPERATION_INCLUDED)
#define AFX_OCI_OPERATION_INCLUDED


#include "afxmt.h"
#ifndef OCI_ORACLE
#include <oci.h>
#endif

class COciException;
class COciConnection;
class COciSQLCursor;


////////////////////////////////////////////////////////////////
// class COciDatabase

#define MAX_CONN_NUM	20

class COciDatabase
{
	friend COciException;
	friend COciConnection;
	friend COciSQLCursor;

protected:
	COciDatabase();

public:
	~COciDatabase();

public:
	static COciDatabase* CreateInstance();

public:
	
	void			InitDatabase();
	void			Release();

	COciConnection* GetConnectionInstance(int iIndex);
	COciConnection* CreateConnectionInstance();
	int				GetConnectionCount() const { return m_nConnCount; }

	COciSQLCursor*  CreateSQLCursorInstance(const COciConnection* pConnObj);
	COciSQLCursor*  CreateSQLCursorInstance(int iConnIndex);

	OCIEnv*         GetOCIEnvHandlePtr() const { return m_p_oci_env; }

private:
	
	bool			 m_bInit;
	int				 m_nConnCount;
	COciConnection** m_ppConnections;

private:
	OCIEnv*			m_p_oci_env;		// OCI environment handle
	OCIError*		m_p_oci_err;		// OCI error handle
	OCIServer*		m_p_oci_srv;		// OCI server handle

};




///////////////////////////////////////////////////////////////////////
// class COciException

#define MSG_EXCEPTION_SIZE	512
#define FILE_PATH_LENGTH	128
class COciException : public COciDatabase               
{
	friend COciConnection;
	friend COciSQLCursor;

public:
	COciException(const COciException& objExcetption);
	COciException(const char* szErrMsg, const char* szFile = NULL, const int nLine = 0);
	
private:
	COciException(const OCIError* p_oci_err, int nStatus = OCI_SUCCESS, const char* szFile = NULL, const int nLine = 0);
	

public:
	~COciException();

public:
	void ShowExceptionInfo();
	void ShowExceptionInfo(char* szSQLStatement, char* szFile, int nLine);

private:

	int				m_nStatus;						// OCIErrorGet() �ķ���ֵ
	int				m_nErrCode;

	char			m_szMsg[MSG_EXCEPTION_SIZE];

	int				m_nLine;
	char			m_szFile[FILE_PATH_LENGTH];
};





///////////////////////////////////////////////////////////////////////
// class COciConnection

class COciConnection : public COciDatabase
{
	friend COciDatabase;

public:
	~COciConnection();

private:
	COciConnection(const COciDatabase& db);

public:
	void Connect(const char* db_svr_name, const char* username, const char* password);
	void DisConnect();

	bool IsConnected() const { return m_bConnected; }

private:
	
	OCISvcCtx*		m_p_oci_svc;		// OCI service context handle
	OCISession*		m_p_oci_sess;		// OCI user session handle
	OCIDescribe*	m_p_oci_desc;		// OCI describe handle
	OCITrans*		m_p_oci_trans;		// OCI transaction handle

	bool			m_bConnected;
};





/////////////////////////////////////////////////////////////////////////
// class COciSQLCursor

#define SQL_STATEMENT_UPDATE		1
#define SQL_STATEMENT_DELETE		2	
#define SQL_STATEMENT_DELETE_ALL	3
#define SQL_STATEMENT_INSERT		4

#define STR_NULL					"<NULL>"
#define STR_EMPTY_BLOB				"<EMPTY_BLOB>"

#define OUT_BUF_SIZE	1024

#define VAR_INT		1
#define VAR_VCHAR	2

class COciSQLCursor : public COciDatabase
{
	typedef struct tagLocatorBinder
	{
		int				iIndex;
		OCILobLocator*	lobl;

		char			szFieldName[128];
		bool			bAlloc;
	}LocatorBinder;

	friend COciDatabase;

public:
	~COciSQLCursor();
	
private:
	COciSQLCursor(const COciDatabase& db);

public:

	void	PrepareSQLStatement(const char* pszSQLStatement) const;
	
	long	GetSQLQueryType() const;		// ������ PrepareSQLStatement ����������
	char*	GetSQLQueryTypeName() const;	// ������ PrepareSQLStatement ����������

	void	Execute(int times = 0)  const;
	
	bool	AllocAndGetQueryResult();
	void	ReleaseQueryResult();
	
	void	Release() { delete this; }

	void	OpenSQLStatement(const char* pszSQLStatement);
	void	OpenTable(const char* pszTableName);
	void	CloseQuery();

	long	GetColumnCount() const { return m_nColumnCount; }
	long	GetColumnType(int iColIndex)  const;
	char*	GetColumnTypeName(int iColIndex)  const;
	char*	GetColumnName(int iColIndex)  const;
	long	GetColumnSize(int iColIndex)  const;
	long	GetColumnScale(int iColIndex)  const;
	long	GetColumnIndexByName(const char* szFieldName)  const;

	bool	Fetch(int nRows = 1) const;
	
	bool	MovePrev()  const;	// �д��Ľ� Scrollable Cursor
	bool	MoveNext()  const;	// �д��Ľ�	Scrollable Cursor
	bool	MoveFirst() const;	// �д��Ľ�	Scrollable Cursor
	bool	MoveLast()  const;	// �д��Ľ�	Scrollable Cursor

	long	GetRecordsCount() const; // �д��Ľ� Scrollable Cursor	
	
	bool	IsFieldNull(int iFieldIndex) const;
	bool	IsFieldNull(const char* szFieldName) const;
	
	int		GetValueInt(int iFieldIndex) const;
	int		GetValueInt(const char* szFieldName) const;

	char*	GetValueString(int iFieldIndex) const;
	char*	GetValueString(const char* szFieldName) const;

	double	GetValueDouble(int iFieldIndex) const;
	double	GetValueDouble(const char* szFieldName) const;

	double  GetValueNumber(int iFieldIndex) const;
	double  GetValueNumber(const char* szFieldName) const;

	char*	GetValueDate(int iFieldIndex) const;
	char*   GetValueDate(const char* szFieldName) const;

	char*	GetBlobData(int iFieldIndex, int& nLen) const;
	char*	GetBlobData(const char* szFieldName, int& nLen) const;

	char*	GetFieldValue(int iFieldIndex, int& nLen) const;
	char*	GetFieldValue(const char* szFieldName, int& nLen) const;

	void	Commit(bool bRollback = true) const;
	
	

	void	SetFieldValue(int iFieldIndex, const char* szValue);


	void	SetValueInt(int iFieldIndex, int value);
	void	SetValueInt(const char* szFieldName, int value);

	void	SetValueDouble(int iFieldIndex, double value);
	void	SetValueDouble(const char* szFieldName, double value);

	void	SetValueString(int iFieldIndex, const char* value);
	void	SetValueString(const char* szFieldName, const char* value);

	void	SetValueNumber(int iFieldIndex, double value);
	void	SetValueNumber(const char* szFieldName, double value);

	void	SetValueNull(int iFieldIndex);
	void	SetValueNull(const char* szFieldName);
	
	void	SetBlobData(int iFieldIndex, const char* pData, int nLen);
	void	SetBlobData(const char* szFieldName, const char* pData, int nLen);

	void	SetValueDate(int iFieldIndex, const char* date);
	void	SetValueDate(const char* szFieldName, const char* date);
	//����ֵ
	void    SetStrValue(int iIndex, const char* szValue, int& nSize);
	void    SetIntValue(int iIndex, int& nValue);
	void    SetFltValue(int iIndex, float& nValue);
	void    SetDlbValue(int iIndex, double& nValue);
	void    SetUIntValue(int iIndex, unsigned int& nValue);
	void    SetLDlbValue(int iIndex, long double& nValue);
	void    SetBlbValue(int iIndex, const unsigned char* szValue, int& nSize);
	

	void	AddNew() { m_bUpdateAddNew = true; }
	void	UpdateTable();
	
	void	UpdateBlobDatas();

	void	DeleteCurrentRecord();
	void	DeleteAllRecords();
	void    RealseLob();

	
	bool	IsAlloc() const { return m_bQueryAlloc; }
	

		
	

	

	
	
	void    BindByPos(int pos, void* value, int size, int type, void* indicator = NULL);
	void    BindByName(const char* name, void* value, int size, int type, void* indicator = NULL);

	void	DefineByPos(int pos, void* value, int size, void* indicator, int type);

	bool	GetColumnDescription();

	
private:
	char*	SQL_OCI_UPDATE();
	char*	SQL_OCI_DELETE();
	char*	SQL_OCI_DELETE_ALL();
	char*	SQL_OCI_INSERT();
	char*	CreateSQLStatement(int iSQLType);
	char*	CreateQueryCondition(char szCondition[], int nLen);

	long	_GetColumnType(int iColIndex) const;
	long	_GetColumnSize(int iColIndex) const;
	long	_GetColumnScale(int iColIndex) const;
	char*	_GetColumnName(int iColIndex) const;
	long	_GetColumnCount() ;

private:
	
	OCISvcCtx*		m_p_oci_svc;		// OCI service context handle
	OCIStmt*		m_p_oci_stmt;		// OCI statement handle
	OCIParam*		m_p_oci_param;		// OCI param handle
	OCILobLocator*  m_p_oci_lobl;       // lob locator

	LocatorBinder*	m_p_binder;			// BLOB ָʾ�����������ŵİ�

	void**			m_ppNewValuesBuf;	// �洢���������ֶε�ֵ

	bool			m_bQueryAlloc;		// �Ƿ�ִ���˷���ռ����
	
	bool			m_bUpdateAddNew;	// �Ƿ���������ֶθ���

	void**			m_ppBuffers;		// ���ڴ洢�����ֶε�ֵ
	signed short*	m_pNullIndicators;  // ָʾ�����ֶ��Ƿ�Ϊ��
	OCIDefine**		m_pp_oci_defs;		// �����ֶεİ����
	
	int				m_nColumnCount;		// SELECT ��ѯ��ı���Ϣ
	long*			m_pColTypes;		// SELECT ��ѯ��ı���Ϣ
	long*			m_pColSizes;		// SELECT ��ѯ��ı���Ϣ
	long*			m_pColScales;		// SELECT ��ѯ��ı���Ϣ
	char**			m_ppColNames;		// SELECT ��ѯ��ı���Ϣ
	
	mutable	int		m_nBlobCount;		// BLOB �ֶε�����
	mutable char*	m_pBlobBuffer;		// �洢 BLOB �� BUFFER

	mutable char	m_szOutput[OUT_BUF_SIZE];  // ���ڸ�������ַ��������

	mutable	char	m_szTableName[128];
};

//��OCI�ļ򵥷�װ	lix

#ifndef SQL_TYPE
#	define SQL_TYPE
#	define SELECT	0
#	define UPDATE	1
#endif

#define OCI_MB_FALSE		_T("������ʾ")
#define OCI_SQL_CUR_COUNT	5

#include <deque>
class COciOperation
{
public:
	COciOperation();
	~COciOperation();

	COciDatabase	*m_OciDatabase;
	COciConnection	*m_OciConn;
	std::deque<COciSQLCursor *> m_SqlCur;

	void PushData(COciSQLCursor *OciSQL);
	BOOL PopData(COciSQLCursor **OciSQL);
	int  GetDataSize();

	BOOL Init(const char *svr_name, const char *user_name, const char *pwd);
	void Init(COciDatabase *db, COciConnection * conn);
	BOOL Release();

	BOOL InitOciSQLCur();
	BOOL FreeOciSQLCur();
	BOOL AddOciSQLCur();
	COciSQLCursor* GetSQLCursor();
	BOOL ReleaseSQLCur(COciSQLCursor *OciSql);

	BOOL Execute(COciSQLCursor *OciSQL, const char *szSQL, int type = SELECT);
	BOOL WriteDBLog(const CString& strFileName, const CString& strMsg);
	int  GetRecordsCount();
	void ShowErrorMessage(LPCTSTR szText) { MessageBox(NULL, szText, OCI_MB_FALSE, MB_OK+MB_ICONERROR); }
	static CString GetTimeString();

protected:
	COciSQLCursor* CreateOciSQLCursor();
	void SetBuf(const char *szSQL);
	void ClearBuf()
	{
		if(m_sql != NULL)
		{
			//delete[] m_sql;
			free(m_sql);
			m_sql = NULL;
		}
	}

	char		    *m_sql;
	HANDLE			 m_DBLogEvent;
	int				 m_RecordsCount;
	CCriticalSection m_cs;
};

#endif //AFX_OCI_OPERATION_INCLUDED