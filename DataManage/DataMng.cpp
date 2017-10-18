#include "StdAfx.h"
#include "DataMng.h"
#include "COciOperation.h"
#include "DataManage.h"

#include "ModeXmlStruct.h"
CDataMng::CDataMng(void)
{
	nConnectStatus = FALSE;
}

CDataMng::~CDataMng(void)
{
}
//-----数据库操作函数接口------  

//-------------------------------------------------------------------------------------------

BOOL CDataMng::DeleteTableData( char *pTableName, BOOL DelTab)											//删除表中所有数据
{
	char			szSQL[256] = {0};
	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//插入目录树数据库
	if(DelTab)
	{
		sprintf(szSQL,"drop table %s",pTableName);
	}else
	{
		sprintf(szSQL, "delete from %s ", pTableName);

	}
	if(!g_pOrcOciDb->ExeSQL(OciSql, szSQL, SQL_UPDATE))
	{
		OciSql->Release();
		return FALSE;
	}

	OciSql->Release();

	return TRUE;
}


BOOL CDataMng::GetTableRowCount(char *pTableName, int &nCnt)
{					
	char			szSQL[1024] = {0};
	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	sprintf(szSQL, "select count(*) from %s ", pTableName);

	if(!g_pOrcOciDb->ExeSQL(OciSql, szSQL, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}	

	int     nLen = 0;
	CString str;
	
	while(OciSql->Fetch())
	{
		//1.
		str = OciSql->GetFieldValue(0, nLen);
		nCnt = atoi(str.GetBuffer(0));
		break;
	}
	
	OciSql->Release();

	return TRUE;	
}
CString CDataMng::GetFieldValue(char *szFile,COciSQLCursor	*OciSql)
{
	int nLen = 10;
	CString str = OciSql->GetFieldValue(szFile, nLen);
	if(str == _T("<NULL>"))
	{
		str = _T("");
	}
	return str;
}
BOOL CDataMng::QueryDataInfo(char *pTableName, CStringArray& ReturnVarArray,int nCol)
{
	char			szSQL[256] = {0};
	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	sprintf(szSQL, "select * from %s ",pTableName);

	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	int			nlen=10;
	CString		str;

	while(OciSql->Fetch())
	{
		int i = 0;
		for(i=0;i<nCol;i++)
		{
			str = OciSql->GetFieldValue(i, nlen);
			if(str == _T("<NULL>"))
			{
				str = _T("");
			}
			ReturnVarArray.Add(str);

		}
	}
	OciSql->Release();

	return TRUE;
}

BOOL CDataMng::GetDataInfo(char *szSQL, CStringArray& ReturnVarArray,int nCol)
{
	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);


	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	int			nlen=10;
	CString		str;

	while(OciSql->Fetch())
	{
		int i = 0;
		for(i=0;i<nCol;i++)
		{
			str = OciSql->GetFieldValue(i, nlen);
			//str = OciSql->GetFieldValue(_T("年龄"), nlen);
			if(str == _T("<NULL>"))
			{
				str = _T("");
			}
			ReturnVarArray.Add(str);

		}
	}
	OciSql->Release();

	return TRUE;

}

/*
CString  CDataMng::GetTabLeastID(CString nTabName,CString IDName)
{
	//先是获得表中所用项的ID号///
	char szSQL[256] = {0};
	sprintf(szSQL,_T("select %s from %s"),IDName,nTabName);
	int     nLen = 1;
	int i=0;
	CStringArray nStrArry;
	GetTableInfo(szSQL,nStrArry,nLen);
	for(i = 1;i<=nStrArry.GetCount();i++)
	{
		BOOL IsHave = TRUE;
		for(int j = 0;j<nStrArry.GetCount();j++)
		{
			if(i == atoi(nStrArry.GetAt(j)))
			{
				IsHave = FALSE;
			}
		}

		if(IsHave)
		{
			CString strID;
			strID.Format(_T("%d"),i);
			int nNum = strID.GetLength();
			for(int i = 0;i<g_IdLen-nNum;i++)
			{
				strID = _T("0")+strID;
			}
			return strID;
		}
	}

	CString strID;
	strID.Format(_T("%d"),i);
	int nNum = strID.GetLength();
	for(int i = 0;i<g_IdLen-nNum;i++)
	{
		strID = _T("0")+strID;
	}
	return strID;
}
*/

int CDataMng::GetTabLeastOid(char *szTableName)
{
	char szSQLMin[256] = {0},szSQLMax[256] = {0};

	sprintf(szSQLMin,_T("select MIN(%s) from %s"),"OID",szTableName);
	sprintf(szSQLMax,_T("select MAX(%s) from %s"),"OID",szTableName);
	int     nLen = 1;
	int i=0;
	CStringArray nStrArry;
	int nMinOid,nMaxOid ;
	GetDataInfo(szSQLMin,nStrArry,nLen);
	nMinOid = atoi(nStrArry.GetAt(0));
	nStrArry.RemoveAll();
	GetDataInfo(szSQLMax,nStrArry,nLen);
	nMaxOid = atoi(nStrArry.GetAt(0));

	

	if(nMinOid == nMaxOid)
	{
		//判断是否连续//
		if(nMinOid <=1)//连续的//
		{
			return nMaxOid+1;
		}else //不连续//
		{
			return 1;
		}
		
	}else
	{
		//判断是否连续//
		if(nMinOid <=1)//连续的//
		{
			return nMaxOid+1;
		}else //不连续//
		{
			return nMinOid-1;
		}
	}
	return nMinOid;
	
}
BOOL CDataMng::GetSeqId(char *szTableName,UINT &nCurID)
{
	char			szSQL[1024] = {0};
	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	sprintf(szSQL, "select %s from dual", szTableName);

	if(!g_pOrcOciDb->ExeSQL(OciSql, szSQL, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}	

	int     nLen = 0;
	CString str;

	while(OciSql->Fetch())
	{
		//1.
		str = OciSql->GetFieldValue(0, nLen);
		nCurID = atoi(str.GetBuffer(0));
		break;
	}

	OciSql->Release();


	return TRUE;

	
}
//-------------------------------------------------------------------------------------------
/*
BOOL CDataMng::GetTableInfo(char *szSQL, CStringArray& ReturnVarArray,int nCol)
{
	//char			szSQL[256] = {0};
	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	//sprintf(szSQL, "select * from %s ",pTableName);

	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	int			nlen=10;
	CString		str;

	while(OciSql->Fetch())
	{
		int i = 0;
		for(i=0;i<nCol;i++)
		{
			str = OciSql->GetFieldValue(i, nlen);
			//str = OciSql->GetFieldValue(_T("年龄"), nlen);
			if(str == _T("<NULL>"))
			{
				str = _T("");
			}
			ReturnVarArray.Add(str);

		}
	}
	OciSql->Release();

	return TRUE;
}
*/

//-------------------------------------------------------------------------------------------
/*
BOOL CDataMng::GetProdNameTableInfo(char *szSQL, CStringArray& ReturnVarArray,int nCol)
{
	//char			szSQL[256] = {0};
	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	//sprintf(szSQL, "select * from %s ",pTableName);

	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	int			nlen=10;
	CString		str;
	int nCount = 0;
	BOOL Is_Have = FALSE;

	ReturnVarArray.RemoveAll();
	while(OciSql->Fetch())
	{
		int i = 0,j;
		for(i=0;i<nCol;i++)
		{
			str = OciSql->GetFieldValue(i, nlen);
			//str = OciSql->GetFieldValue(_T("年龄"), nlen);
			if(str == _T("<NULL>"))
			{
				str = _T("");
			}


			Is_Have =FALSE;
			nCount = ReturnVarArray.GetCount();
			for (j = 0;j<nCount;j++)
			{
				if(ReturnVarArray.GetAt(j) == str)
				{
					Is_Have = TRUE;
					break;
				}

			}
			if(!Is_Have)
			{
				ReturnVarArray.Add(str);
			}
			
		}
	}
	OciSql->Release();

	return TRUE;
}
*/

/*
BOOL CDataMng::GetTableInfo(char *pTableName, CStringArray& ReturnVarArray,int *nCol,int len)
{
	char			szSQL[256] = {0};
	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	sprintf(szSQL, "select * from %s ",pTableName);

	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	int			nlen=10;
	CString		str;

	while(OciSql->Fetch())
	{
		int i = 0;
		for(i=0;i<len;i++)
		{
			str = OciSql->GetFieldValue(nCol[i], nlen);
			//str = OciSql->GetFieldValue(_T("年龄"), nlen);
			if(str == _T("<NULL>"))
			{
				str = _T("");
			}
			ReturnVarArray.Add(str);

		}
	}
	OciSql->Release();

	return TRUE;
}
*/

/*
BOOL CDataMng::InsertDataInfo(char *szSQL)
{	
	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);


	if(!g_pOrcOciDb->ExeSQL(OciSql, szSQL, SQL_UPDATE))
	{
		OciSql->Release();
		return FALSE;
	}
	OciSql->Release();

	return TRUE;
}
*/

BOOL CDataMng::UpdateDataInfo(char *szSQL) 								//更改测试细则名称
{	
	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	if(!g_pOrcOciDb->ExeSQL(OciSql, szSQL, SQL_UPDATE))
	{
		OciSql->Release();
		return FALSE;
	}

	OciSql->Release();

	return TRUE;
}

/*
BOOL CDataMng::DeleteDataInfo(char *szSQL) 								//更改测试细则名称
{	
	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	if(!g_pOrcOciDb->ExeSQL(OciSql, szSQL, SQL_UPDATE))
	{
		OciSql->Release();
		return FALSE;
	}

	OciSql->Release();

	return TRUE;
}
*/

BOOL CDataMng::UpdateOracleBlob(char *szSQL,char *FieldName,char *strFileInfo,int nlen)
{

	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	if(!g_pOrcOciDb->SetOracleTabBlob(OciSql,szSQL,FieldName,strFileInfo ,nlen))
	{
		OciSql->Release();
		return FALSE;
	}

	OciSql->Release();
	return TRUE;
}

BOOL CDataMng::GetTableBolbInfo(char *szSQL,char *FieldName,char *strFileInfo,int &nlen)
{
	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	if(!g_pOrcOciDb->GetOracleTabBlob(OciSql,szSQL,FieldName,strFileInfo ,nlen))
	{
		OciSql->Release();
		return FALSE;
	}
	OciSql->Release();

	return TRUE;
	
}
int CDataMng::GetRoleCount()
{
	int nRows = 0;
	CString strnRow;
	char szSQL[256] = {0};
	sprintf(szSQL,_T("%s"),g_HrRole);
	m_DMng.GetTableRowCount(szSQL, nRows);
	return nRows;

}
BOOL CDataMng::InitRoleTab()
{

	int nRows = 0;
	char szSQL[256] = {0,};
	
	if((nRows=GetRoleCount()) >=1)
	{
		return TRUE;
	}

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL, "insert into %s (OID, ROLE_NAME, ROLE_CODE)\
		values (1, '系统管理员', '111')",
		g_HrRole);
	UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL, "insert into %s (OID, ROLE_NAME, ROLE_CODE)\
		values (2, '高级用户', '333')",
		g_HrRole);
	UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL, "insert into %s (OID, ROLE_NAME, ROLE_CODE)\
		values (3, '普通用户', '444')",
		g_HrRole);
	UpdateDataInfo(szSQL);
	return TRUE;
}

BOOL CDataMng::GetAllRole(vector<StHrRole *> *pAllRole)
{
	int i,nRows = 0;

	ReleaseRoles(pAllRole);

	char szSQL[256] = {0};
	if( (nRows = GetRoleCount())<=0)
	{
		return TRUE;
	}

	memset(szSQL,0,256);
	sprintf(szSQL,_T("%s"),
		g_HrRole);
	CStringArray nStrArry;
	int nLen =g_HrRoleLen;
	if(QueryDataInfo(szSQL, nStrArry,nLen))
	{
		for(i = 0;i<nRows;i++)
		{
			StHrRole *pRoleInfo = new StHrRole;
			memset(pRoleInfo,0,sizeof(StHrRole));
			pRoleInfo->nOid = atoi(nStrArry.GetAt(i*nLen));
			strcpy(pRoleInfo->szRoleName,nStrArry.GetAt(i*nLen+1));
			strcpy(pRoleInfo->szRoleNo,nStrArry.GetAt(i*nLen+2));

			pAllRole->push_back(pRoleInfo);
		}

	}

	return TRUE;

}


BOOL CDataMng::InitUserTab()
{
	int nRows = 0;
	char szSQL[256] = {0,};

	if((nRows=GetCountUser()) >=1)
	{
		return TRUE;
	}

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL, "insert into %s (OID, LOGIN_NAME, USER_NAME, USER_PWD, ROLE_OID, GROUP_OID, USER_SIGNFILE, USER_LOGSTATE, USER_TYPE, CALL, EMAIL, PHONE, PADDEV_ID)\
		values (1, '%s', '管理员', '%s', 0, 0, null, 0, %d, null, null, null, 0)",
		g_HrUser, 
		g_Admin,g_ReSetDefPwd, user_admin);
	UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL, "insert into %s (OID, LOGIN_NAME, USER_NAME, USER_PWD, ROLE_OID, GROUP_OID, USER_SIGNFILE, USER_LOGSTATE, USER_TYPE, CALL, EMAIL, PHONE, PADDEV_ID)\
		values (2, 'user', '用户', '%s', 0, 1, null, 0, %d, null, null, null, 1)",
		g_HrUser, 
		g_ReSetDefPwd, user_normal);
	UpdateDataInfo(szSQL);
	return TRUE;

}
int  CDataMng::GetCountUserLogName(char *LogName)
{
	int nRows = 0;
	char szSQL[256] = {0};
	sprintf(szSQL,_T("%s where LOGIN_NAME='%s'"),g_HrUser,LogName);
	GetTableRowCount(szSQL, nRows);

	return nRows;
}

int  CDataMng::GetUserDataFromToDb(COciSQLCursor	*OciSql, StHrUser *pUserInfo)
{

	pUserInfo->nOid = atoi(GetFieldValue(_T("OID"),OciSql));
	strcpy(pUserInfo->szLoginName,GetFieldValue(_T("LOGIN_NAME"),OciSql));
	strcpy(pUserInfo->szUserName,GetFieldValue(_T("USER_NAME"),OciSql));
	strcpy(pUserInfo->szUserPwd,GetFieldValue(_T("USER_PWD"),OciSql));

	pUserInfo->nRoleOid = atoi(GetFieldValue(_T("ROLE_OID"),OciSql));
	pUserInfo->nGroupOid = atoi(GetFieldValue(_T("GROUP_OID"),OciSql));
	strcpy(pUserInfo->szGroupName,GetFieldValue(_T("GROUP_NAME"),OciSql));
	strcpy(pUserInfo->szUserSignfile,GetFieldValue(_T("USER_SIGNFILE"),OciSql));

	pUserInfo->nUserLogstate = atoi(GetFieldValue(_T("USER_LOGSTATE"),OciSql));
	pUserInfo->nUserType = atoi(GetFieldValue(_T("USER_TYPE"),OciSql));

	strcpy(pUserInfo->szCall,GetFieldValue(_T("CALL"),OciSql));
	strcpy(pUserInfo->szEmail,GetFieldValue(_T("EMAIL"),OciSql));
	strcpy(pUserInfo->szPhone,GetFieldValue(_T("PHONE"),OciSql));
	pUserInfo->nPadDevID = atoi(GetFieldValue(_T("PADDEV_ID"),OciSql));
	return 1;
}

BOOL CDataMng::GetOneUsrInfoLogName(char *LogName,StHrUser *pUserInfo)
{
	int nRows = 0;
	char szSQL1[1024] ={0,},szSQL2[1024] ={0,};
	sprintf(szSQL1, _T(" where LOGIN_NAME = '%s'"),LogName );
	if( (nRows = GetCountUser(szSQL1))<=0)
	{
		return FALSE;
	}

	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	memset(szSQL2,0,sizeof(szSQL2));
	sprintf(szSQL2, "select t1.*, t2.GROUP_NAME AS GROUP_NAME from %s t1 \
					left join %s t2 on t2.OID=t1.GROUP_OID where t1.LOGIN_NAME='%s' order by t1.USER_NAME",
					g_HrUser,g_HrGroup,LogName);

	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL2, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	while(OciSql->Fetch())
	{
		GetUserDataFromToDb(OciSql, pUserInfo);

	}
	OciSql->Release();

	return TRUE;
}
BOOL CDataMng::GetOneUsrInfoOid(UINT nUserOid,StHrUser *pUserInfo)//通过用户OID查找用户信息//
{
	
	int nRows = 0;
	char szSQL1[1024] ={0,},szSQL2[1024] ={0,};
	sprintf(szSQL1, _T(" where OID = %d"),nUserOid );
	if( (nRows = GetCountUser(szSQL1))<=0)
	{
		return FALSE;
	}

	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	memset(szSQL2,0,sizeof(szSQL2));
	sprintf(szSQL2, "select t1.*, t2.GROUP_NAME AS GROUP_NAME from %s t1 \
					left join %s t2 on t2.OID=t1.GROUP_OID where t1.OID=%d  order by t1.USER_NAME",
					g_HrUser,g_HrGroup,nUserOid);

	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL2, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	while(OciSql->Fetch())
	{
		GetUserDataFromToDb(OciSql, pUserInfo);

	}
	OciSql->Release();

	return TRUE;
}
int  CDataMng::GetCountUser(char *pTableName)
{
	int nRows = 0;
	CString strnRow;
	char szSQL[256] = {0};
	sprintf(szSQL,_T("%s %s"),g_HrUser,pTableName);
	m_DMng.GetTableRowCount(szSQL, nRows);
	return nRows;
	
}


BOOL CDataMng::GetAllUserToPad(vector<StHrUser *> *pUserArry)
{
	int nRows = 0;
	char szSQL1[1024] ={0,},szSQL2[1024] ={0,};
	if( (nRows = GetCountUser())<=0)
	{
		return FALSE;
	}

	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	memset(szSQL2,0,sizeof(szSQL2));
	sprintf(szSQL2, "select t1.*, t2.GROUP_NAME AS GROUP_NAME from %s t1 \
					left join %s t2 on t2.OID=t1.GROUP_OID order by t1.USER_NAME",
					g_HrUser,g_HrGroup);

	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL2, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	while(OciSql->Fetch())
	{
		StHrUser *pUserInfo = new StHrUser;
		memset(pUserInfo, 0,sizeof(StHrUser));
		GetUserDataFromToDb(OciSql, pUserInfo);

		pUserArry->push_back(pUserInfo);
	}
	OciSql->Release();

	return TRUE;
}
BOOL CDataMng::IsUserLogNameExists(char *LogName)//判断此用户登录名是否存在//
{
	int nRows = 0;
	char szSQL[256] = {0};
	sprintf(szSQL,_T("%s where LOGIN_NAME='%s'"),g_HrUser,LogName);
	GetTableRowCount(szSQL, nRows);
	return nRows>=1;
}
BOOL CDataMng::IsUserUserNameExists(char *UserName)//判断此用户中文名是否存在//
{
	int nRows = 0;
	char szSQL[256] = {0};
	sprintf(szSQL,_T("%s where USER_NAME='%s'"),g_HrUser,UserName);
	GetTableRowCount(szSQL, nRows);
	return nRows>=1;
}
BOOL CDataMng::AddNewUser(StHrUser *pStr)
{
	char szSQL[512] = {0};
	sprintf(szSQL, "insert into %s(OID,LOGIN_NAME,USER_NAME,USER_PWD,ROLE_OID,\
				   GROUP_OID,USER_SIGNFILE,USER_LOGSTATE,USER_TYPE,CALL,\
				   EMAIL,PHONE,PADDEV_ID) values (%s, '%s', '%s', '%s',%d, \
				   %d, '%s', %d, %d, '%s', '%s', '%s',%d)",
				   g_HrUser, 
				   Seq_User,pStr->szLoginName,pStr->szUserName,g_ReSetDefPwd,
				   pStr->nRoleOid,pStr->nGroupOid,pStr->szUserSignfile,pStr->nUserLogstate,pStr->nUserType,
				   pStr->szCall,pStr->szEmail,pStr->szPhone, pStr->nPadDevID);
	if(!UpdateDataInfo(szSQL))
	{
		return FALSE;
	}

	if(!GetSeqId(Seq_UserCurID,pStr->nOid))
	{
		return FALSE;
	}
	return TRUE;
}


BOOL CDataMng::EditOldUser(StHrUser *pStr)
{
	char szSQL[512] = {0};
	sprintf(szSQL, "update %s set LOGIN_NAME='%s',USER_NAME='%s',ROLE_OID=%d,GROUP_OID=%d,USER_SIGNFILE='%s',\
				   USER_LOGSTATE=%d,USER_TYPE=%d,CALL='%s',EMAIL='%s',PHONE='%s', PADDEV_ID=%d where \
				   OID=%d",
				   g_HrUser,
				   pStr->szLoginName,pStr->szUserName,pStr->nRoleOid,pStr->nGroupOid,pStr->szUserSignfile,
				   pStr->nUserLogstate,pStr->nUserType,pStr->szCall,pStr->szEmail,pStr->szPhone,
				   pStr->nPadDevID,pStr->nOid);

	return UpdateDataInfo(szSQL);

}

BOOL CDataMng::DelUser(char *szLoginName)
{
	char szSQL[256] = {0};//where 入校时间=to_date('2016-6-21','YYYY-MM-DD')//
	sprintf(szSQL, "delete from %s where LOGIN_NAME='%s'",
		g_HrUser,szLoginName);

	return UpdateDataInfo(szSQL);
}
BOOL CDataMng::ReSetUsrPwd(char *NetPwd,char *UsrLogName)
{
	char szSQL[256] = {0};
	sprintf(szSQL,"update %s set USER_PWD='%s' where LOGIN_NAME='%s'",
		g_HrUser,NetPwd,UsrLogName);
	if(!UpdateDataInfo(szSQL))
	{
		return FALSE;
	}
	return TRUE;
}

//交检部门
//================================================================================
//2017-03-01 liuty:add 交检部门模块函数pStUpDepart
int  CDataMng::GetUpDepartCount(char *pTableName)
{
	int nRows = 0;
	CString strnRow;
	char szSQL[256] = {0};
	sprintf(szSQL,_T("%s %s"),g_HrUpDepart,pTableName);
	m_DMng.GetTableRowCount(szSQL, nRows);
	return nRows;
}
int  CDataMng::GetUpDepartDataFromToDb(COciSQLCursor	*OciSql, StHrUpDepart *pStUpDepart)
{
	pStUpDepart->nOid = atoi(GetFieldValue(_T("OID"),OciSql));
	strcpy(pStUpDepart->szUpDepartName,GetFieldValue(_T("DEPART_NAME"),OciSql));
	strcpy(pStUpDepart->szUpDepartNo,GetFieldValue(_T("DEPART_NO"),OciSql));
	strcpy(pStUpDepart->szUpDepartType,GetFieldValue(_T("DEPART_TYPE"),OciSql));
	strcpy(pStUpDepart->szDescription,GetFieldValue(_T("DESCRIPTION"),OciSql));
	strcpy(pStUpDepart->szCall,GetFieldValue(_T("CALL"),OciSql));
	strcpy(pStUpDepart->szFaxs,GetFieldValue(_T("FAXS"),OciSql));
	strcpy(pStUpDepart->szAddress,GetFieldValue(_T("ADDRESS"),OciSql));
	pStUpDepart->nInvalid = atoi(GetFieldValue(_T("INVALID"),OciSql));

	return 1;
}

BOOL CDataMng::GetAllUpDepart(vector<StHrUpDepart > *pStHrUpDepartArry)
{
	int nRows = 0;
	char szSQL1[256] ={0},szSQL2[256] ={0};
	sprintf(szSQL1,_T(""));
	if( (nRows = GetUpDepartCount(szSQL1))<=0)
	{
		return FALSE;
	}


	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	memset(szSQL2,0,256);
	sprintf(szSQL2, "select * from %s %s ",g_HrUpDepart,szSQL1);

	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL2, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	while(OciSql->Fetch())
	{
		StHrUpDepart nStHrGroup;
		memset(&nStHrGroup,0,sizeof(StHrUpDepart));
		GetUpDepartDataFromToDb(OciSql, &nStHrGroup);
		pStHrUpDepartArry->push_back(nStHrGroup);

	}
	OciSql->Release();

	return TRUE;
}
BOOL CDataMng::GetOneUpDepartInfoOID(UINT OID,StHrUpDepart *pStUpDepart)//通过OID获取这个部门的所有信息//
{
	
	int nRows = 0;
	char szSQL1[256] ={0},szSQL2[256] ={0};
	sprintf(szSQL1,_T("where OID = %d"), OID);
	if( (nRows = GetUpDepartCount(szSQL1))<=0)
	{
		return FALSE;
	}


	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	memset(szSQL2,0,256);
	sprintf(szSQL2, "select * from %s %s ",g_HrUpDepart,szSQL1);

	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL2, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	while(OciSql->Fetch())
	{
		GetUpDepartDataFromToDb(OciSql, pStUpDepart);

	}
	OciSql->Release();

	return TRUE;
}

BOOL CDataMng::GetOneUpDepartInfoDepartName(char *szDepartName,StHrUpDepart *pStUpDepart)//通过交检部门名称获取这个部门的所有信息//
{
	int nRows = 0;
	char szSQL1[256] ={0},szSQL2[256] ={0};
	sprintf(szSQL1,_T("where DEPART_NAME = '%s'"), szDepartName);
	if( (nRows = GetUpDepartCount(szSQL1))<=0)
	{
		return FALSE;
	}


	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	memset(szSQL2,0,256);
	sprintf(szSQL2, "select * from %s %s ",g_HrUpDepart,szSQL1);

	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL2, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	while(OciSql->Fetch())
	{
		GetUpDepartDataFromToDb(OciSql, pStUpDepart);
	}
	OciSql->Release();

	return TRUE;
}
BOOL CDataMng::IsUpDepartExists(CString DepartName)////部门名称不能重复  判断部门是否存在//
{
	int nRows = 0;
	char szSQL[256] = {0};
	sprintf(szSQL,_T("%s where DEPART_NAME='%s'"),g_HrUpDepart,DepartName);
	GetTableRowCount(szSQL, nRows);
	return nRows>=1;
}


BOOL CDataMng::AddNewUpDepart(StHrUpDepart *pStUpDepart)
{
	char szSQL[512] = {0};
	sprintf(szSQL, "insert into %s(OID,DEPART_NAME,DEPART_NO,DEPART_TYPE,\
				   DESCRIPTION,CALL,FAXS,ADDRESS,INVALID) values (%s, '%s', '%s', \
				   '%s', '%s', '%s', '%s', '%s',%d)",
				   g_HrUpDepart, 
				   Seq_Depart,pStUpDepart->szUpDepartName,pStUpDepart->szUpDepartNo,
				   pStUpDepart->szUpDepartType,pStUpDepart->szDescription,pStUpDepart->szCall,
				   pStUpDepart->szFaxs,pStUpDepart->szAddress,Group_Valid);
	if(!UpdateDataInfo(szSQL))
	{
		return FALSE;
	}

	if(!GetSeqId(Seq_DepartCurID,pStUpDepart->nOid))
	{
		return FALSE;
	}
	return TRUE;
}
BOOL CDataMng::EditOldUpDepart(StHrUpDepart *pStUpDepart)
{
	char szSQL[512] = {0};
	sprintf(szSQL, "update %s set DEPART_NAME='%s',DEPART_NO='%s',\
				   DEPART_TYPE='%s',DESCRIPTION='%s',CALL='%s',FAXS='%s',ADDRESS='%s' where \
				   OID=%d",
				   g_HrUpDepart,
				   pStUpDepart->szUpDepartName,pStUpDepart->szUpDepartNo,pStUpDepart->szUpDepartType,
				   pStUpDepart->szDescription,pStUpDepart->szCall,pStUpDepart->szFaxs,pStUpDepart->szAddress,
				   pStUpDepart->nOid);

	return UpdateDataInfo(szSQL);
}
BOOL CDataMng::DelUpDepart(UINT nOid)
{
	char szSQL[256] = {0};
	sprintf(szSQL, "delete from %s where OID=%d",
		g_HrUpDepart,nOid);

	return UpdateDataInfo(szSQL);
}


BOOL CDataMng::InitGroupTab()
{
	int nRows = 0;
	char szSQL[256] = {0};

	if((nRows=GetGroupCount()) >=1)
	{
		return TRUE;
	}

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL, "insert into %s (OID, PID, GROUP_NAME, GROUP_NO, GROUP_TYPE, DESCRIPTION, CALL, FAXS, ADDRESS, INVALID)\
		values (1, 0, '检验处', 'NO000001', null, null, null, null, null, 1)",
				   g_HrGroup);
	UpdateDataInfo(szSQL);
	return TRUE;

}

int  CDataMng::GetGroupCount(char *pTableName)
{
	int nRows = 0;
	CString strnRow;
	char szSQL[256] = {0};
	sprintf(szSQL,_T("%s %s"),g_HrGroup,pTableName);
	m_DMng.GetTableRowCount(szSQL, nRows);
	return nRows;
}

BOOL  CDataMng::GetAllValidGroup(vector<StHrGroup *> *pStHrGroupArry)
{
	int nRows = 0;
	char szSQL1[256] ={0},szSQL2[256] ={0};
	sprintf(szSQL1,_T("where PID=%d and INVALID=%d"),0,Group_Valid);//上级部门ID//
	if( (nRows = GetGroupCount(szSQL1))<=0)
	{
		return FALSE;
	}


	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	memset(szSQL2,0,256);
	sprintf(szSQL2, "select * from %s %s ",g_HrGroup,szSQL1);

	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL2, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	while(OciSql->Fetch())
	{
		StHrGroup *pStHrGroup = new StHrGroup;
		memset(pStHrGroup,0,sizeof(StHrGroup));

		pStHrGroup->nOid = atoi(GetFieldValue(_T("OID"),OciSql));
		pStHrGroup->nPOid = atoi(GetFieldValue(_T("PID"),OciSql));
		strcpy(pStHrGroup->szGroupName,GetFieldValue(_T("GROUP_NAME"),OciSql));
		strcpy(pStHrGroup->szGroupNo,GetFieldValue(_T("GROUP_NO"),OciSql));
		strcpy(pStHrGroup->szGroupType,GetFieldValue(_T("GROUP_TYPE"),OciSql));
		strcpy(pStHrGroup->szDescription,GetFieldValue(_T("DESCRIPTION"),OciSql));
		strcpy(pStHrGroup->szCall,GetFieldValue(_T("CALL"),OciSql));
		strcpy(pStHrGroup->szFaxs,GetFieldValue(_T("FAXS"),OciSql));
		strcpy(pStHrGroup->szAddress,GetFieldValue(_T("ADDRESS"),OciSql));
		pStHrGroup->nInvalid = atoi(GetFieldValue(_T("INVALID"),OciSql));

		pStHrGroupArry->push_back(pStHrGroup);

	}
	OciSql->Release();

	return TRUE;

}

BOOL CDataMng::GetAllInvalidGroup(vector<StHrGroup *> *pStHrGroupArry)
{
	int nRows = 0;
	char szSQL1[256] ={0},szSQL2[256] ={0};
	sprintf(szSQL1,_T("where PID=%d and INVALID=%d"),0,Group_Invalid);//上级部门ID//
	if( (nRows = GetGroupCount(szSQL1))<=0)
	{
		return FALSE;
	}


	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	memset(szSQL2,0,256);
	sprintf(szSQL2, "select * from %s %s ",g_HrGroup,szSQL1);

	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL2, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	while(OciSql->Fetch())
	{
		StHrGroup *pStHrGroup = new StHrGroup;
		memset(pStHrGroup,0,sizeof(StHrGroup));

		pStHrGroup->nOid = atoi(GetFieldValue(_T("OID"),OciSql));
		pStHrGroup->nPOid = atoi(GetFieldValue(_T("PID"),OciSql));
		strcpy(pStHrGroup->szGroupName,GetFieldValue(_T("GROUP_NAME"),OciSql));
		strcpy(pStHrGroup->szGroupNo,GetFieldValue(_T("GROUP_NO"),OciSql));
		strcpy(pStHrGroup->szGroupType,GetFieldValue(_T("GROUP_TYPE"),OciSql));
		strcpy(pStHrGroup->szDescription,GetFieldValue(_T("DESCRIPTION"),OciSql));
		strcpy(pStHrGroup->szCall,GetFieldValue(_T("CALL"),OciSql));
		strcpy(pStHrGroup->szFaxs,GetFieldValue(_T("FAXS"),OciSql));
		strcpy(pStHrGroup->szAddress,GetFieldValue(_T("ADDRESS"),OciSql));
		pStHrGroup->nInvalid = atoi(GetFieldValue(_T("INVALID"),OciSql));

		pStHrGroupArry->push_back(pStHrGroup);

	}
	OciSql->Release();

	return TRUE;
}
//通过OID获取这个部门的所有信息//
BOOL CDataMng::GetOneGroupInfoOID(UINT OID,StHrGroup *pStr)
{
	int nRows = 0;
	char szSQL1[256] ={0},szSQL2[256] ={0};
	sprintf(szSQL1,_T("where OID=%d"),OID);//部门ID//
	if( (nRows = GetGroupCount(szSQL1))<=0)
	{
		return FALSE;
	}

	memset(szSQL2,0,256);
	sprintf(szSQL2,_T("%s %s"),
		g_HrGroup,szSQL1);

	CStringArray nStrArry;
	int nLen =g_DepartLen;
	if(QueryDataInfo(szSQL2, nStrArry,nLen))
	{
		pStr->nOid = atoi(nStrArry.GetAt(0));
		pStr->nPOid = atoi(nStrArry.GetAt(1));
		strcpy(pStr->szGroupName,nStrArry.GetAt(2));
		strcpy(pStr->szGroupNo,nStrArry.GetAt(3));
		strcpy(pStr->szGroupType ,nStrArry.GetAt(4));
		strcpy(pStr->szDescription ,nStrArry.GetAt(5));
		strcpy(pStr->szCall ,nStrArry.GetAt(6));
		strcpy(pStr->szFaxs ,nStrArry.GetAt(7));
		strcpy(pStr->szAddress ,nStrArry.GetAt(8));

	}

	return TRUE;
	
}

int CDataMng::GetOneGroupInfoName(char *szGroupName,StHrGroup *pStr)
{

	int nRows = 0;
	char szSQL1[256] ={0},szSQL2[256] ={0};
	sprintf(szSQL1,_T("where GROUP_NAME='%s'"),
		szGroupName);
	if( (nRows = GetGroupCount(szSQL1))<=0)
	{
		return FALSE;
	}

	memset(szSQL2,0,256);
	sprintf(szSQL2,_T("%s %s"),
		g_HrGroup,szSQL1);

	CStringArray nStrArry;
	int nLen =g_DepartLen;
	if(QueryDataInfo(szSQL2, nStrArry,nLen))
	{
		pStr->nOid = atoi(nStrArry.GetAt(0));
		pStr->nPOid = atoi(nStrArry.GetAt(1));
		strcpy(pStr->szGroupName,nStrArry.GetAt(2));
		strcpy(pStr->szGroupNo,nStrArry.GetAt(3));
		strcpy(pStr->szGroupType ,nStrArry.GetAt(4));
		strcpy(pStr->szDescription ,nStrArry.GetAt(5));
		strcpy(pStr->szCall ,nStrArry.GetAt(6));
		strcpy(pStr->szFaxs ,nStrArry.GetAt(7));
		strcpy(pStr->szAddress ,nStrArry.GetAt(8));

	}

	return TRUE;
}

////
BOOL CDataMng::IsDepartExists(CString DepartName, UINT pOid)
{
	int nRows = 0;
	char szSQL[256] = {0};
	sprintf(szSQL,_T("%s where PID=%d and GROUP_NAME='%s'"),g_HrGroup,pOid,DepartName);
	GetTableRowCount(szSQL, nRows);
	return nRows>=1;
}

BOOL CDataMng::AddNewGroup(StHrGroup *pStr)
{
	char szSQL[512] = {0};
	sprintf(szSQL, "insert into %s values (%s, %d, '%s', '%s', \
				   '%s', '%s', '%s', '%s', '%s',%d)",
				   g_HrGroup, 
				   Seq_Group,pStr->nPOid,pStr->szGroupName,pStr->szGroupNo,
				   pStr->szGroupType,pStr->szDescription,pStr->szCall,pStr->szFaxs,pStr->szAddress,Group_Valid);
	if(!UpdateDataInfo(szSQL))
	{
		return FALSE;
	}

	if(!GetSeqId(Seq_GroupCurID,pStr->nOid))
	{
		return FALSE;
	}
	return TRUE;
}
BOOL CDataMng::EditOldGroup(StHrGroup *pStr)
{
	char szSQL[512] = {0};
	sprintf(szSQL, "update %s set PID=%d,GROUP_NAME='%s',GROUP_NO='%s',\
				   GROUP_TYPE='%s',DESCRIPTION='%s',CALL='%s',FAXS='%s',ADDRESS='%s' where \
				   OID=%d",
				   g_HrGroup,
				   pStr->nPOid,pStr->szGroupName,pStr->szGroupNo,pStr->szGroupType,
				   pStr->szDescription,pStr->szCall,pStr->szFaxs,pStr->szAddress,
				   pStr->nOid);

	return UpdateDataInfo(szSQL);
}
BOOL CDataMng::DelGroup(UINT nOid)
{
	char szSQL[256] = {0};
	sprintf(szSQL, "update %s set INVALID=%d where OID=%d",
		g_HrGroup,Group_Invalid,nOid);

	return UpdateDataInfo(szSQL);
}

BOOL CDataMng::RecoveryGroup(UINT nGroupOid)
{
	char szSQL[512] = {0};
	sprintf(szSQL, "update %s set INVALID=%d where \
				   OID=%d",
				   g_HrGroup,Group_Valid,nGroupOid);

	return UpdateDataInfo(szSQL);
}

//任务基础表模块函数//
BOOL CDataMng::IsHrGroupSaveExists(UINT nGroupOid)//任务基础表是否存在//
{
	int nRows = 0;
	char szSQL[256] = {0};
	sprintf(szSQL,_T("%s where GROUP_OID=%d"),
		g_HrGroupSave,nGroupOid);
	GetTableRowCount(szSQL, nRows);
	return nRows>=1;
}

BOOL CDataMng::AddNewHrGroupSave(StHrGroupSave *pHrGroupSave)
{
	
	char szSQL[512] = {0};
	sprintf(szSQL, "insert into %s(OID,GROUP_OID,BASE_TAB,ATTA_TAB,CREATE_TIME,CREATE_USER)\
				   values (%s,%d,'%s','%s',to_date('%s','YYYY_MM_DD HH24:MI:SS'),'%s')",
				   g_HrGroupSave,
				   Seq_Group_Save,pHrGroupSave->nGroupOid,
				    pHrGroupSave->szBaseTabName,pHrGroupSave->szAttaTabName,pHrGroupSave->szCreateTime,pHrGroupSave->szCreateUser);

	if(!UpdateDataInfo(szSQL))
	{
		return FALSE;
	}

	if(!GetSeqId(Seq_Group_SaveCurID,pHrGroupSave->nOid))
	{
		return FALSE;
	}
	return TRUE;
}




int CDataMng::GetProdCount(char *pTableName/*=_T("")*/)
{
	int nRows = 0;
	char szSQL[4096] = {0,};
	sprintf(szSQL,_T("%s %s"),g_BasProduct,pTableName);
	m_DMng.GetTableRowCount(szSQL, nRows);

	return nRows;
}
int  CDataMng::GetProdCountGroup(UINT nGroupOid)//获取本部门的所有产品个数///
{
	int nRows = 0;
	char szSQL1[256] ={0,};
	sprintf(szSQL1,_T("where GROUP_OID=%d"),nGroupOid);//所属部门OID//
	nRows = GetProdCount(szSQL1);
	return nRows;
}
int  CDataMng::GetProdDataFromToDb(COciSQLCursor	*OciSql, StBasProduct *pProductInfo)
{
	pProductInfo->nOid = atoi(GetFieldValue(_T("OID"),OciSql));//产品OID
	strcpy(pProductInfo->szProductNo,GetFieldValue(_T("PRODUCT_NO"),OciSql));//产品代号
	strcpy(pProductInfo->szProductName,GetFieldValue(_T("PRODUCT_NAME"),OciSql));//产品名称
	pProductInfo->nPicNumType = atoi(GetFieldValue(_T("PICNUM_TYPE"),OciSql));//图号类型:0.无图号(普通产品),1.有图号(线缆)
	pProductInfo->nGroupOid = atoi(GetFieldValue(_T("GROUP_OID"),OciSql));//所在部门OID
	strcpy(pProductInfo->szGroupName,GetFieldValue(_T("GROUP_NAME"),OciSql));//所在部门

	strcpy(pProductInfo->szCreateTime,GetFieldValue(_T("CREATE_TIME"),OciSql));//创建时间
	strcpy(pProductInfo->szCreateUser,GetFieldValue(_T("CREATE_USER"),OciSql));//创建人
	return 1;
}
BOOL CDataMng::GetGroupProductInfo(UINT nGroupOid, vector<StBasProduct> *pArrayProduct)
{
	int nRows = 0;
	char szSQL1[4096] ={0,},szSQL2[4096] ={0,};
	CString str;
	
	sprintf(szSQL1,_T("where GROUP_OID=%d order by PRODUCT_NO"),nGroupOid);//所属部门OID//
	if( (nRows = GetProdCount(szSQL1))<=0)
	{
		return FALSE;
	}

	COciSQLCursor	*OciSql;
	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	memset(szSQL2,0,4096);
	sprintf(szSQL2,_T("select t1.*,t2.GROUP_NAME AS GROUP_NAME from %s t1 left join %s t2 on t1.GROUP_OID=t2.OID \
						  where t1.GROUP_OID=%d order by t1.PRODUCT_NO"),
						  g_BasProduct,g_HrGroup,nGroupOid);


	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL2, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	while(OciSql->Fetch())
	{
		StBasProduct stProductInfo;
		memset(&stProductInfo,0,sizeof(StBasProduct));

		GetProdDataFromToDb(OciSql, &stProductInfo);

		pArrayProduct->push_back(stProductInfo);
	}
	OciSql->Release();
	return TRUE;

}
BOOL CDataMng::GetGroupProductData(UINT GroupOid, StBasProduct *pProductSearch, 
						 vector<StBasProduct > *pArrayProduct)//通过模糊查询的方式 查询本部门的所有产品信息
{
	int i, nCount, nRows = 0;
	char szSQL1[4096] ={0},szSQL2[4096] ={0};
	
	CString strCount,strDate,str1,str2;
	CStringArray strArry1,strArry2;

	//1.产品代号
	if(strcmp(pProductSearch->szProductNo,_T("")) != 0)
	{

		str1.Format(_T("t1.PRODUCT_NO like '%%%s%%'"),pProductSearch->szProductNo);
		str2.Format(_T("PRODUCT_NO like '%%%s%%'"),pProductSearch->szProductNo);
		
		strArry1.Add(str1);
		strArry2.Add(str2);
	}

	//2.产品名称
	if(strcmp(pProductSearch->szProductName,_T("")) != 0)
	{

		str1.Format(_T("t1.PRODUCT_NAME like '%%%s%%'"),pProductSearch->szProductName);
		str2.Format(_T("PRODUCT_NAME like '%%%s%%'"),pProductSearch->szProductName);

		strArry1.Add(str1);
		strArry2.Add(str2);
	}


	//3.创建开始时间
	if(strcmp(pProductSearch->szCreateBeginTime,_T("")) != 0)
	{

		str1.Format(_T("t1.CREATE_TIME >= to_date('%s %s','YYYY_MM_DD HH24:MI:SS')"),
			pProductSearch->szCreateBeginTime,g_SearchBeginTime);
		str2.Format(_T("CREATE_TIME >= to_date('%s %s','YYYY_MM_DD HH24:MI:SS')"),
			pProductSearch->szCreateBeginTime,g_SearchBeginTime);

		strArry1.Add(str1);
		strArry2.Add(str2);
	}

	//4.创建结束时间
	if(strcmp(pProductSearch->szCreateEndTime,_T("")) != 0)
	{

		str1.Format(_T("t1.CREATE_TIME <= to_date('%s %s','YYYY_MM_DD HH24:MI:SS')"),
			pProductSearch->szCreateEndTime,g_SearchEndTime);
		str2.Format(_T("CREATE_TIME <= to_date('%s %s','YYYY_MM_DD HH24:MI:SS')"),
			pProductSearch->szCreateEndTime,g_SearchEndTime);

		strArry1.Add(str1);
		strArry2.Add(str2);
	}

	//5.创建人
	if(strcmp(pProductSearch->szCreateUser,_T("")) != 0)
	{

		str1.Format(_T("t1.CREATE_USER like '%%%s%%'"),pProductSearch->szCreateUser);
		str2.Format(_T("CREATE_USER like '%%%s%%'"),pProductSearch->szCreateUser);

		strArry1.Add(str1);
		strArry2.Add(str2);
	}


	//6.产品类型 In(1,1,1,1)
	int nPos = 0;
	CString strTypeEnum1 = _T(""), strTypeEnum2 = _T("");
	CString strTemp;
	int nTypeArray[10] = {0,};
	if(pProductSearch->bProductNormal >= Sel_Check)//通用模板 选中//
	{
		nTypeArray[nPos] = Product_normal;
		nPos++;

	}

	if(pProductSearch->bProductLine >= Sel_Check)//产品专用模板 选中//
	{
		nTypeArray[nPos] = Product_Line;
		nPos++;
	}

	if(nPos >=1)
	{
		strTypeEnum1.Format(_T(" t1.MODE_TYPE in("));
		strTypeEnum2.Format(_T(" MODE_TYPE in("));
	}
	for(i = 0; i<nPos; i++)
	{
		if(i>=(nPos-1))
		{
			strTemp.Format(_T("%d) "), nTypeArray[i]);
		}else
		{
			strTemp.Format(_T("%d, "), nTypeArray[i]);
		}

		strTypeEnum1+=strTemp;
		strTypeEnum2+=strTemp;
	}

	if(!strTypeEnum1.IsEmpty())
	{
		strArry1.Add(strTypeEnum1);
		strArry2.Add(strTypeEnum2);
	}

	nCount = strArry1.GetCount();
	
	if(nCount >=1)
	{
		strDate.Format(_T(" where t1.GROUP_OID=%d and "), GroupOid);
		strCount.Format(_T(" where GROUP_OID=%d and "), GroupOid);
	}else
	{
		strDate.Format(_T(" where t1.GROUP_OID=%d"), GroupOid);
		strCount.Format(_T(" where GROUP_OID=%d"), GroupOid);
	}
	
	for(i = 0;i<nCount;i++)
	{
		if(i>=nCount-1)
		{
			str1.Format(_T("%s"),strArry1.GetAt(i));
			str2.Format(_T("%s"),strArry2.GetAt(i));
		}else
		{
			str1.Format(_T("%s and "),strArry1.GetAt(i));
			str2.Format(_T("%s and "),strArry2.GetAt(i));
		}

		strDate+=str1;
		strCount+=str2;

	}


	
	sprintf(szSQL1,_T("%s"),strCount);
	if( (pProductSearch->nResultNum=nRows = GetProdCount(szSQL1))<=0)
	{
		return FALSE;
	}

	COciSQLCursor	*OciSql;
	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	memset(szSQL2,0,sizeof(szSQL2));
	
	sprintf(szSQL2,_T("select rownum AS RN, t1.*,t2.GROUP_NAME AS GROUP_NAME from %s t1 left join %s t2 on t1.GROUP_OID=t2.OID \
					  %s order by t1.PRODUCT_NO"),
					  g_BasProduct,g_HrGroup,strDate);

	int nBgnNum = 0, nEndNum = 0;
	nBgnNum = (pProductSearch->nPerPageNum*(pProductSearch->nCurPage-1));
	nEndNum = (pProductSearch->nPerPageNum*(pProductSearch->nCurPage));
	memset(szSQL1, 0, sizeof(szSQL1));
	if(pProductSearch->nPerPageNum == g_nSearchPerPageNum[All_Result])
	{
		sprintf(szSQL1, _T("%s"), szSQL2);
	}else
	{
		sprintf(szSQL1, _T("select * from( select * from(%s) where RN > %d) where RN <= %d"), szSQL2, nBgnNum, nEndNum);
	}
	
	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL1, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	while(OciSql->Fetch())
	{
		StBasProduct stProductInfo;
		memset(&stProductInfo,0,sizeof(StBasProduct));

		GetProdDataFromToDb(OciSql, &stProductInfo);


		pArrayProduct->push_back(stProductInfo);
	}
	OciSql->Release();
	return TRUE;
}

BOOL CDataMng::GetGroupPicNumProdInfo(UINT GroupOid,int nPicNumType,vector<StBasProduct > *pArrayProduct)
{
	int nRows = 0;
	CString str = g_strSelProdsSQL;
	int  nstrLen = g_strSelProdsSQL.GetLength();
	char *szSQL1 = new char[1024+nstrLen],   *szSQL2 = new char[1024+nstrLen];
	memset(szSQL1,0,sizeof(szSQL1));

	if(Sel_Product_OFF)
	{
		sprintf(szSQL1,_T("where GROUP_OID=%d and %s and PICNUM_TYPE=%d order by PRODUCT_NO"),GroupOid,str,nPicNumType);//所属部门OID//
	}else
	{
		sprintf(szSQL1,_T("where GROUP_OID=%d and PICNUM_TYPE=%d order by PRODUCT_NO"),GroupOid,nPicNumType);//所属部门OID//
	}
	
	if( (nRows = GetProdCount(szSQL1))<=0)
	{
		delete []szSQL1;
		delete []szSQL2;
		return FALSE;
	}

	COciSQLCursor	*OciSql;
	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	memset(szSQL2,0,sizeof(szSQL2));
	if(Sel_Product_OFF)
	{
		sprintf(szSQL2,_T("select t1.*,t2.GROUP_NAME AS GROUP_NAME from %s t1 left join %s t2 on t1.GROUP_OID=t2.OID \
						  where t1.GROUP_OID=%d and t1.%s and t1.PICNUM_TYPE=%d order by t1.PRODUCT_NO"),
						  g_BasProduct,g_HrGroup,GroupOid,str,nPicNumType);

	}else
	{
		sprintf(szSQL2,_T("select t1.*,t2.GROUP_NAME AS GROUP_NAME from %s t1 left join %s t2 on t1.GROUP_OID=t2.OID \
						  where t1.GROUP_OID=%d and t1.PICNUM_TYPE=%d order by t1.PRODUCT_NO"),
						  g_BasProduct,g_HrGroup,GroupOid,nPicNumType);

	}
	
	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL2, SQL_SELECT))
	{
		OciSql->Release();
		delete []szSQL1;
		delete []szSQL2;
		return FALSE;
	}

	while(OciSql->Fetch())
	{
		StBasProduct stProductInfo;
		memset(&stProductInfo,0,sizeof(StBasProduct));

		GetProdDataFromToDb(OciSql, &stProductInfo);

		
		pArrayProduct->push_back(stProductInfo);
	}
	OciSql->Release();
	delete []szSQL1;
	delete []szSQL2;
	return TRUE;
}




BOOL CDataMng::GetProdDataOid(UINT ProdOid,StBasProduct *pStBasProduct)
{

	int nRows = 0;
	char szSQL1[4096] ={0,},szSQL2[4096] ={0,};
	CString str;

	sprintf(szSQL1,_T("where OID=%d"),ProdOid);//所属部门OID//
	if( (nRows = GetProdCount(szSQL1))<=0)
	{
		return FALSE;
	}

	COciSQLCursor	*OciSql;
	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	memset(szSQL2,0,4096);
	sprintf(szSQL2,_T("select t1.*,t2.GROUP_NAME AS GROUP_NAME from %s t1 left join %s t2 on t1.GROUP_OID=t2.OID \
					  where t1.OID=%d"),
					  g_BasProduct,g_HrGroup,ProdOid);


	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL2, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	while(OciSql->Fetch())
	{
		GetProdDataFromToDb(OciSql, pStBasProduct);
	}
	OciSql->Release();
	return TRUE;


}

BOOL CDataMng::GetProdDataGroupOidProdNo(UINT GroupOid,char *szProductNo,StBasProduct *pStBasProduct)
{

	int nRows = 0;
	char szSQL1[4096] ={0,},szSQL2[4096] ={0,};
	CString str;

	sprintf(szSQL1,_T("where GROUP_OID=%d and PRODUCT_NO='%s'"),GroupOid,szProductNo);//所属部门OID//
	if( (nRows = GetProdCount(szSQL1))<=0)
	{
		return FALSE;
	}

	COciSQLCursor	*OciSql;
	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	memset(szSQL2,0,4096);
	sprintf(szSQL2,_T("select t1.*,t2.GROUP_NAME AS GROUP_NAME from %s t1 left join %s t2 on t1.GROUP_OID=t2.OID \
					  where t1.GROUP_OID=%d and t1.PRODUCT_NO='%s'"),
					  g_BasProduct,g_HrGroup,GroupOid,szProductNo);


	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL2, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	while(OciSql->Fetch())
	{
		GetProdDataFromToDb(OciSql, pStBasProduct);

	}
	OciSql->Release();
	return TRUE;

}
BOOL CDataMng::AddNewProd(StBasProduct *pStr)
{
	char szSQL[512] = {0};
	sprintf(szSQL, "insert into %s(OID,PRODUCT_NO,PRODUCT_NAME,PICNUM_TYPE,GROUP_OID,CREATE_TIME,CREATE_USER)\
				   values (%s,'%s','%s',%d,%d,to_date('%s','YYYY_MM_DD HH24:MI:SS'),'%s')",
				   g_BasProduct,
				   Seq_Product,pStr->szProductNo,pStr->szProductName,
				   pStr->nPicNumType,pStr->nGroupOid,pStr->szCreateTime,pStr->szCreateUser);

	if(!UpdateDataInfo(szSQL))
	{
		return FALSE;
	}

	if(!GetSeqId(Seq_ProductCurID,pStr->nOid))
	{
		return FALSE;
	}

	return TRUE;
}
//产品模块的函数///
BOOL CDataMng::IsProdExists(UINT GroupOid,char *szProductNo)
{
	int nRows = 0;
	char szSQL[256] = {0};
	sprintf(szSQL,_T("%s where PRODUCT_NO='%s' and GROUP_OID=%d"),
		g_BasProduct,szProductNo,GroupOid);
	GetTableRowCount(szSQL, nRows);
	return nRows>=1;
}
BOOL CDataMng::EditOldProd(StBasProduct *pStr)
{
	char szSQL[512] = {0};
	sprintf(szSQL, "update %s set PRODUCT_NO='%s',PRODUCT_NAME='%s',\
				   PICNUM_TYPE=%d,GROUP_OID=%d,CREATE_TIME=to_date('%s','YYYY_MM_DD HH24:MI:SS'),CREATE_USER='%s' where \
				   OID=%d",
				   g_BasProduct,
				   pStr->szProductNo,pStr->szProductName,pStr->nPicNumType,
				   pStr->nGroupOid,pStr->szCreateTime,pStr->szCreateUser,
				   pStr->nOid);

	return UpdateDataInfo(szSQL);
}
BOOL CDataMng::DelOldProd(UINT nOid)
{
	char szSQL[256] = {0};
	sprintf(szSQL, "delete from %s where OID=%d",
		g_BasProduct,nOid);
	if(UpdateDataInfo(szSQL))
	{
		return TRUE;
	}
	return FALSE;
}


BOOL CDataMng::DelAllProd(UINT nGroupOid)                                                    //删除全部产品
{
	char szSQL[256] = {0};
	sprintf(szSQL, "delete from %s where GROUP_OID=%d",
		g_BasProduct,nGroupOid);
	if(UpdateDataInfo(szSQL))
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CDataMng::DelAllProd_PicNum(UINT nGroupOid)												//删除全部图号信息
{
	char szSQL[256] = {0};
	sprintf(szSQL, "delete from %s where GROUP_OID=%d",
		g_BasProductPicNum,nGroupOid);
	if(UpdateDataInfo(szSQL))
	{
		return TRUE;
	}
	return FALSE;
}

int  CDataMng::GetPicNumCount(char *pTableName)
{
	int nRows = 0;
	char szSQL[256] = {0};
	sprintf(szSQL,_T("%s %s"),g_BasProductPicNum,pTableName);
	m_DMng.GetTableRowCount(szSQL, nRows);

	return nRows;
}
int  CDataMng::GetProdPicNumDataFromToDb(COciSQLCursor	*OciSql, StBasPicNum *pBasPicNum)
{

	pBasPicNum->nOid = atoi(GetFieldValue(_T("OID"),OciSql));//产品图号OID

	strcpy(pBasPicNum->szPicNumNo,GetFieldValue(_T("PICNUM_NO"),OciSql));//图号代号
	strcpy(pBasPicNum->szPicNumName,GetFieldValue(_T("PICNUM_NAME"),OciSql));//图号名称

	pBasPicNum->nProductOid = atoi(GetFieldValue(_T("PRODUCT_OID"),OciSql));//产品图号OID
	strcpy(pBasPicNum->szProductNo,GetFieldValue(_T("PRODUCT_NO"),OciSql));//产品代号
	strcpy(pBasPicNum->szProductName,GetFieldValue(_T("PRODUCT_NAME"),OciSql));//产品名称

	strcpy(pBasPicNum->szCreateTime,GetFieldValue(_T("CREATE_TIME"),OciSql));//创建时间
	strcpy(pBasPicNum->szCreateUser,GetFieldValue(_T("CREATE_USER"),OciSql));//创建人
	return 1;

}
BOOL CDataMng::GetProdPicNumData(UINT ProductOid,char *szPicNumNo,StBasPicNum *pBasPicNum)
{

	int nRows = 0;
	char szSQL1[4096] ={0,},szSQL2[4096] ={0,};
	CString str;

	sprintf(szSQL1,_T("where PRODUCT_OID=%d and PICNUM_NO='%s'"),ProductOid,szPicNumNo);//所属部门OID//
	if( (nRows = GetPicNumCount(szSQL1))<=0)
	{
		return FALSE;
	}

	COciSQLCursor	*OciSql;
	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	memset(szSQL2,0,4096);
	sprintf(szSQL2,_T("select t1.*,t2.PRODUCT_NO AS PRODUCT_NO,t2.PRODUCT_NAME AS PRODUCT_NAME\
					  from %s t1 left join %s t2 on t1.PRODUCT_OID=t2.OID \
					  where t1.PRODUCT_OID=%d and t1.PICNUM_NO='%s'"),
					  g_BasProductPicNum,g_BasProduct,ProductOid,szPicNumNo);


	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL2, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	while(OciSql->Fetch())
	{
		GetProdPicNumDataFromToDb(OciSql, pBasPicNum);
	}
	OciSql->Release();
	return TRUE;

}

BOOL CDataMng::GetPicNumDataFromOid(UINT PicNumOid,StBasPicNum *pBasPicNum)
{
	int nRows = 0;
	char szSQL1[4096] ={0,},szSQL2[4096] ={0,};
	CString str;

	sprintf(szSQL1,_T("where OID=%d"),PicNumOid);//所属部门OID//
	if( (nRows = GetPicNumCount(szSQL1))<=0)
	{
		return FALSE;
	}

	COciSQLCursor	*OciSql;
	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	memset(szSQL2,0,4096);
	sprintf(szSQL2,_T("select t1.*,t2.PRODUCT_NO AS PRODUCT_NO,t2.PRODUCT_NAME AS PRODUCT_NAME\
					  from %s t1 left join %s t2 on t1.PRODUCT_OID=t2.OID \
					  where t1.OID=%d"),
					  g_BasProductPicNum,g_BasProduct,PicNumOid);


	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL2, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	while(OciSql->Fetch())
	{
		GetProdPicNumDataFromToDb(OciSql, pBasPicNum);
	}
	OciSql->Release();
	return TRUE;
}

BOOL CDataMng::GetProductPicNumInfo(UINT ProdOid,vector<StBasPicNum> *pPicNumArray)
{

	int nRows = 0;
	char szSQL1[4096] ={0,},szSQL2[4096] ={0,};
	CString str;

	sprintf(szSQL1,_T("where PRODUCT_OID=%d"),ProdOid);//所属部门OID//
	if( (nRows = GetPicNumCount(szSQL1))<=0)
	{
		return FALSE;
	}

	COciSQLCursor	*OciSql;
	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	memset(szSQL2,0,4096);
	sprintf(szSQL2,_T("select t1.*,t2.PRODUCT_NO AS PRODUCT_NO,t2.PRODUCT_NAME AS PRODUCT_NAME\
					  from %s t1 left join %s t2 on t1.PRODUCT_OID=t2.OID \
					  where t1.PRODUCT_OID=%d"),
					  g_BasProductPicNum,g_BasProduct,ProdOid);


	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL2, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	while(OciSql->Fetch())
	{
		StBasPicNum stPicNumInfo;
		memset(&stPicNumInfo, 0, sizeof(StBasPicNum));
		GetProdPicNumDataFromToDb(OciSql, &stPicNumInfo);
	}
	OciSql->Release();
	return TRUE;
}


BOOL CDataMng::AddNewPicNum(StBasPicNum *pStrPicNum)
{
	char szSQL[512] = {0};
	sprintf(szSQL, "insert into %s(OID,PICNUM_NO,PICNUM_NAME,PRODUCT_OID,CREATE_TIME,CREATE_USER, GROUP_OID)\
				   values (%s,'%s','%s',%d,to_date('%s','YYYY_MM_DD HH24:MI:SS'),'%s', %d)",
				   g_BasProductPicNum,
				   Seq_PicNum,pStrPicNum->szPicNumNo,pStrPicNum->szPicNumName,pStrPicNum->nProductOid,
				   pStrPicNum->szCreateTime,pStrPicNum->szCreateUser,
					g_CurSelDepart.nOid			//组OID
				   );
	if(!UpdateDataInfo(szSQL))
	{
		return FALSE;
	}

	if(!GetSeqId(Seq_PicNumCurID,pStrPicNum->nOid))
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CDataMng::IsPicNumExists(UINT ProductOid,char *szPicNumNo)//判断此产品图号是否存在//
{
	int nRows = 0;
	char szSQL[256] = {0};
	sprintf(szSQL,_T("%s where PICNUM_NO='%s' and PRODUCT_OID=%d"),
		g_BasProductPicNum,szPicNumNo,ProductOid);
	GetTableRowCount(szSQL, nRows);
	return nRows>=1;
}

BOOL CDataMng::EditOldPicNum(StBasPicNum *pStrPicNum)
{
	char szSQL[512] = {0};
	sprintf(szSQL, "update %s set PICNUM_NO='%s',PICNUM_NAME='%s',PRODUCT_OID=%d,where OID=%d",
				   g_BasProductPicNum,
				   pStrPicNum->szPicNumNo,pStrPicNum->szPicNumName,pStrPicNum->nProductOid,
				   pStrPicNum->szCreateTime,pStrPicNum->szCreateUser,
				   pStrPicNum->nOid);

	return UpdateDataInfo(szSQL);
}
BOOL CDataMng::DelOldPicNum(UINT nPicNumOid)
{
	char szSQL[256] = {0};
	sprintf(szSQL, "delete from %s where OID=%d",
		g_BasProductPicNum,nPicNumOid);
	return UpdateDataInfo(szSQL);
}


///模板界面的 操作函数///

int  CDataMng::GetModeCount(char *pTableName/*=_T("")*/)////
{
	int nRows = 0;
	char szSQL[256] = {0,};
	sprintf(szSQL,_T("%s %s"),g_BasMode,pTableName);
	m_DMng.GetTableRowCount(szSQL, nRows);

	return nRows;

}

int  CDataMng::GetModeCountGroup(UINT GroupOid)//根据所属部门 获取模板个数//
{
	int nRows = 0;
	char szSQL1[256] ={0,};
	sprintf(szSQL1,_T("where GROUP_OID=%d"),GroupOid);//所属部门OID//
	nRows = GetModeCount(szSQL1);
	return nRows;
}
int  CDataMng::GetModeCountGroupType(UINT GroupOid,int nModeType)
{
	int nRows = 0;
	char szSQL1[256] ={0,};
	sprintf(szSQL1,_T("where GROUP_OID=%d and MODE_TYPE=%d"),GroupOid,nModeType);//所属部门OID//
	nRows = GetModeCount(szSQL1);
	return nRows;
}
int  CDataMng::GetModeDataFromToDb(COciSQLCursor	*OciSql, StBasMode *pModeInfo)
{

	pModeInfo->nOid = atoi(GetFieldValue(_T("OID"),OciSql));//1.模板OID
	strcpy(pModeInfo->szModeName,GetFieldValue(_T("MODE_NAME"),OciSql));//2.模板名称
	strcpy(pModeInfo->szModeVersion, GetFieldValue(_T("MODE_VERSION"), OciSql));//3.模板版本
	pModeInfo->nModeType = atoi(GetFieldValue(_T("MODE_TYPE"),OciSql));//4.模板类型:0.产品通用,1.产品专用,2.线缆专用,3.未启用
	pModeInfo->nModeRowVar = atoi(GetFieldValue(_T("MODE_ROWVAR"),OciSql));//5.模板行可变状态：0.不可变 1.行可变
	pModeInfo->nModeSize = atoi(GetFieldValue(_T("MODE_SIZE"),OciSql));//6.模板大小
	strcpy(pModeInfo->szModeTabName, GetFieldValue(_T("MODE_TABNAME"), OciSql));//7.模板数据表表名

	pModeInfo->nInitTabSrt = atoi(GetFieldValue(_T("INIT_TABSRT"),OciSql));//8.是否建立数据表结构：0.未建立 1.已建立
	pModeInfo->nGroupOid = atoi(GetFieldValue(_T("GROUP_OID"),OciSql));//9.所在部门OIDGROUP_NAME
	strcpy(pModeInfo->szGroupName, GetFieldValue(_T("GROUP_NAME"),OciSql));//9_1 部门名称
	pModeInfo->stProductInfo.nOid = atoi(GetFieldValue(_T("PRODUCT_OID"),OciSql));//10.适用产品OID
	strcpy(pModeInfo->stProductInfo.szProductNo, GetFieldValue(_T("PRODUCT_NO"), OciSql));//10_1.产品代号//

	strcpy(pModeInfo->szModel, GetFieldValue(_T("MODEL"), OciSql));//11.适用型号
	strcpy(pModeInfo->szPhase, GetFieldValue(_T("PHASE"), OciSql));//12.适用阶段
	strcpy(pModeInfo->szCreateTime, GetFieldValue(_T("CREATE_TIME"), OciSql));//13.模板创建时间
	strcpy(pModeInfo->szCreateUser, GetFieldValue(_T("CREATE_USER"), OciSql));//14.模板创建用户

	pModeInfo->nFormula = atoi(GetFieldValue(_T("FORMULA"), OciSql));//15.有无公式模板   2017-03-08 Liuty add
	

	return 1;
}
BOOL CDataMng::GetProdModeData(UINT ProdOid,vector<StBasMode> *pModeArry)
{

	int nRows = 0;
	char szSQL1[256] ={0},szSQL2[256] ={0};
	sprintf(szSQL1,_T("where PRODUCT_OID=%d order by MODE_NAME"),ProdOid);//所属部门OID//
	if( (nRows = GetModeCount(szSQL1))<=0)
	{
		return FALSE;
	}

	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	memset(szSQL2,0,256);
	sprintf(szSQL2,_T("select t1.*,t2.GROUP_NAME AS GROUP_NAME,t3.PRODUCT_NO AS PRODUCT_NO from %s t1 left join %s t2 on t1.GROUP_OID=t2.OID \
					  left join %s t3 on t1.PRODUCT_OID=t3.OID where t1.PRODUCT_OID=%d order by t1.MODE_NAME"),
					  g_BasMode,g_HrGroup,g_BasProduct,ProdOid);


	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL2, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	while(OciSql->Fetch())
	{
		StBasMode stModeInfo;
		memset(&stModeInfo,0,sizeof(StBasMode));
		GetModeDataFromToDb(OciSql, &stModeInfo);
		pModeArry->push_back(stModeInfo);
	}
	OciSql->Release();

	return TRUE;

}

BOOL CDataMng::GetGroupModeInfo(UINT GroupOid,StBasMode *pModeSearchInfo,vector<StBasMode> *pModeArry)
{

	int i, nCount, nRows = 0;
	char szSQL1[4096] ={0},szSQL2[4096] ={0};

	CString strCount,strDate,str1,str2;
	CStringArray strArry1,strArry2;
	//1.模板名称
	if(strcmp(pModeSearchInfo->szModeName,_T("")) != 0)
	{

		str1.Format(_T("t1.MODE_NAME like '%%%s%%'"),pModeSearchInfo->szModeName);
		str2.Format(_T("MODENAME like '%%%s%%'"),pModeSearchInfo->szModeName);

		strArry1.Add(str1);
		strArry2.Add(str2);
	}

	//2.产品代号//
	if(strcmp(pModeSearchInfo->stProductInfo.szProductNo,_T("")) != 0)
	{

		str1.Format(_T("t3.PRODUCT_NO like '%%%s%%'"),pModeSearchInfo->stProductInfo.szProductNo);
		str2.Format(_T("t3.PRODUCT_NO like '%%%s%%'"),pModeSearchInfo->stProductInfo.szProductNo);

		strArry1.Add(str1);
		strArry2.Add(str2);
	}


	//3.产品型号
	if(strcmp(pModeSearchInfo->szModel,_T("")) != 0)
	{

		str1.Format(_T("t1.MODEL like '%%%s%%'"),pModeSearchInfo->szModel);
		str2.Format(_T("MODEL like '%%%s%%'"),pModeSearchInfo->szModel);

		strArry1.Add(str1);
		strArry2.Add(str2);
	}


	//4.产品阶段
	if(strcmp(pModeSearchInfo->szPhase,_T("")) != 0)
	{

		str1.Format(_T("t1.PHASE like '%%%s%%'"),pModeSearchInfo->szPhase);
		str2.Format(_T("PHASE like '%%%s%%'"),pModeSearchInfo->szPhase);

		strArry1.Add(str1);
		strArry2.Add(str2);
	}



	//5.创建开始时间
	if(strcmp(pModeSearchInfo->szCreateBeginTime,_T("")) != 0)
	{

		str1.Format(_T("t1.CREATE_TIME >= to_date('%s %s','YYYY_MM_DD HH24:MI:SS')"),
			pModeSearchInfo->szCreateBeginTime,g_SearchBeginTime);
		str2.Format(_T("CREATE_TIME >= to_date('%s %s','YYYY_MM_DD HH24:MI:SS')"),
			pModeSearchInfo->szCreateBeginTime,g_SearchBeginTime);

		strArry1.Add(str1);
		strArry2.Add(str2);
	}

	//6.创建结束时间
	if(strcmp(pModeSearchInfo->szCreateEndTime,_T("")) != 0)
	{

		str1.Format(_T("t1.CREATE_TIME <= to_date('%s %s','YYYY_MM_DD HH24:MI:SS')"),
			pModeSearchInfo->szCreateEndTime,g_SearchEndTime);
		str2.Format(_T("CREATE_TIME <= to_date('%s %s','YYYY_MM_DD HH24:MI:SS')"),
			pModeSearchInfo->szCreateEndTime,g_SearchEndTime);

		strArry1.Add(str1);
		strArry2.Add(str2);
	}

	//7.创建人
	if(strcmp(pModeSearchInfo->szCreateUser,_T("")) != 0)
	{

		str1.Format(_T("t1.CREATE_USER like '%%%s%%'"),pModeSearchInfo->szCreateUser);
		str2.Format(_T("CREATE_USER like '%%%s%%'"),pModeSearchInfo->szCreateUser);

		strArry1.Add(str1);
		strArry2.Add(str2);
	}

	//8.模板类型 In(1,1,1,1)
	int nPos = 0;
	CString strTypeEnum1 = _T(""), strTypeEnum2 = _T("");
	CString strTemp;
	int nTypeArray[10] = {0,};
	if(pModeSearchInfo->bModeCurrency >= Sel_Check)//通用模板 选中//
	{
		nTypeArray[nPos] = Mode_Currency;
		nPos++;

	}

	if(pModeSearchInfo->bModeDedicated >= Sel_Check)//产品专用模板 选中//
	{
		nTypeArray[nPos] = Mode_Dedicated;
		nPos++;
	}

	if(pModeSearchInfo->bModeLineDed >= Sel_Check)//线缆专用模板 选中//
	{
		nTypeArray[nPos] = Mode_LineDed;
		nPos++;
	}

	if(pModeSearchInfo->bModeNotUse >= Sel_Check)//未启用模板 选中//
	{
		nTypeArray[nPos] = Mode_NotUse;
		nPos++;
	}

	if(nPos >=1)
	{
		strTypeEnum1.Format(_T(" t1.MODE_TYPE in("));
		strTypeEnum2.Format(_T(" MODE_TYPE in("));
	}
	for(i = 0; i<nPos; i++)
	{
		if(i>=(nPos-1))
		{
			strTemp.Format(_T("%d) "), nTypeArray[i]);
		}else
		{
			strTemp.Format(_T("%d, "), nTypeArray[i]);
		}

		strTypeEnum1+=strTemp;
		strTypeEnum2+=strTemp;
	}

	if(!strTypeEnum1.IsEmpty())
	{
		strArry1.Add(strTypeEnum1);
		strArry2.Add(strTypeEnum2);
	}

	//9.行可变属性 In(1,1);

	nPos = 0;
	strTypeEnum1 = _T(""), strTypeEnum2 = _T("");
	memset(nTypeArray, 0, sizeof(nTypeArray));
	if(pModeSearchInfo->bModeRowNoChange >= Sel_Check)//行不可变 选中//
	{
		nTypeArray[nPos] = ModeRow_NoChange;
		nPos++;

	}

	if(pModeSearchInfo->bModeRowChange >= Sel_Check)//行可变 选中//
	{
		nTypeArray[nPos] = ModeRow_Change;
		nPos++;
	}

	if(nPos >=1)
	{
		strTypeEnum1.Format(_T(" t1.MODE_ROWVAR in("));
		strTypeEnum2.Format(_T(" MODE_ROWVAR in("));
	}
	for(i = 0; i<nPos; i++)
	{
		if(i>=(nPos-1))
		{
			strTemp.Format(_T("%d) "), nTypeArray[i]);
		}else
		{
			strTemp.Format(_T("%d, "), nTypeArray[i]);
		}

		strTypeEnum1+=strTemp;
		strTypeEnum2+=strTemp;
	}

	if(!strTypeEnum1.IsEmpty())
	{
		strArry1.Add(strTypeEnum1);
		strArry2.Add(strTypeEnum2);
	}


	//10.是否已经初始化表结构 In(1,1)

	nPos = 0;
	strTypeEnum1 = _T(""), strTypeEnum2 = _T("");
	memset(nTypeArray, 0, sizeof(nTypeArray));
	if(pModeSearchInfo->bUnInitTabStr >= Sel_Check)//表结构未初始化 选中//
	{
		nTypeArray[nPos] = ModeTab_UnInit;
		nPos++;

	}

	if(pModeSearchInfo->bInitedTabSrt >= Sel_Check)//表结构已经初始化 选中//
	{
		nTypeArray[nPos] = ModeTab_Init;
		nPos++;
	}

	if(nPos >=1)
	{
		strTypeEnum1.Format(_T(" t1.INIT_TABSRT in("));
		strTypeEnum2.Format(_T(" INIT_TABSRT in("));
	}
	for(i = 0; i<nPos; i++)
	{
		if(i>=(nPos-1))
		{
			strTemp.Format(_T("%d) "), nTypeArray[i]);
		}else
		{
			strTemp.Format(_T("%d, "), nTypeArray[i]);
		}

		strTypeEnum1+=strTemp;
		strTypeEnum2+=strTemp;
	}

	if(!strTypeEnum1.IsEmpty())
	{
		strArry1.Add(strTypeEnum1);
		strArry2.Add(strTypeEnum2);
	}



	nCount = strArry1.GetCount();

	if(nCount >=1)
	{
		strDate.Format(_T(" where t1.GROUP_OID=%d and "), GroupOid);
		strCount.Format(_T(" where GROUP_OID=%d and "), GroupOid);
	}else
	{
		strDate.Format(_T(" where t1.GROUP_OID=%d"), GroupOid);
		strCount.Format(_T(" where GROUP_OID=%d"), GroupOid);
	}

	for(i = 0;i<nCount;i++)
	{
		if(i>=(nCount-1))
		{
			str1.Format(_T("%s"),strArry1.GetAt(i));
			str2.Format(_T("%s"),strArry2.GetAt(i));
		}else
		{
			str1.Format(_T("%s and "),strArry1.GetAt(i));
			str2.Format(_T("%s and "),strArry2.GetAt(i));
		}

		strDate+=str1;
		strCount+=str2;

	}


	memset(szSQL1,0,sizeof(szSQL1));
	sprintf(szSQL1,_T(" %s t1 left join %s t2 on t1.GROUP_OID=t2.OID \
					  left join %s t3 on t1.PRODUCT_OID=t3.OID %s"),g_BasMode,g_HrGroup,g_BasProduct,strDate);
	if(!m_DMng.GetTableRowCount(szSQL1, nRows))
	{
		return FALSE;
	}

	if( (pModeSearchInfo->nResultNum = nRows) <=0)
	{
		return FALSE;
	}

	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	memset(szSQL2,0,sizeof(szSQL2));
	sprintf(szSQL2,_T("select rownum AS RN,t1.*,t2.GROUP_NAME AS GROUP_NAME,t3.PRODUCT_NO AS PRODUCT_NO from %s t1 left join %s t2 on t1.GROUP_OID=t2.OID \
					  left join %s t3 on t1.PRODUCT_OID=t3.OID %s order by t1.MODE_NAME"),
					  g_BasMode,g_HrGroup,g_BasProduct,strDate);


	int nBgnNum = 0, nEndNum = 0;
	nBgnNum = (pModeSearchInfo->nPerPageNum*(pModeSearchInfo->nCurPage-1));
	nEndNum = (pModeSearchInfo->nPerPageNum*(pModeSearchInfo->nCurPage));
	memset(szSQL1, 0, sizeof(szSQL1));
	if(pModeSearchInfo->nPerPageNum == g_nSearchPerPageNum[All_Result])
	{
		sprintf(szSQL1, _T("%s"), szSQL2);
	}else
	{
		sprintf(szSQL1, _T("select * from( select * from(%s) where RN > %d) where RN <= %d"), szSQL2, nBgnNum, nEndNum);
	}

	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL1, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	while(OciSql->Fetch())
	{
		StBasMode stModeInfo;
		memset(&stModeInfo,0,sizeof(StBasMode));
		GetModeDataFromToDb(OciSql, &stModeInfo);
		pModeArry->push_back(stModeInfo);
	}
	OciSql->Release();

	return TRUE;

}

BOOL CDataMng::GetGroupModeTypeData(UINT GroupOid,int nModeType,vector<StBasMode > *pModeArry)
{
	int nRows = 0;
	char szSQL1[256] ={0,},szSQL2[256] ={0,};
	sprintf(szSQL1,_T("where GROUP_OID=%d and MODE_TYPE=%d order by MODE_NAME"),GroupOid,nModeType);//所属部门OID//
	if( (nRows = GetModeCount(szSQL1))<=0)
	{
		return FALSE;
	}

	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	memset(szSQL2,0,256);
	sprintf(szSQL2,_T("select t1.*,t2.GROUP_NAME AS GROUP_NAME,t3.PRODUCT_NO AS PRODUCT_NO from %s t1 left join %s t2 on t1.GROUP_OID=t2.OID \
					  left join %s t3 on t1.PRODUCT_OID=t3.OID where t1.GROUP_OID=%d and t1.MODE_TYPE=%d order by t1.MODE_NAME"),
					  g_BasMode,g_HrGroup,g_BasProduct,GroupOid,nModeType);

	//sprintf(szSQL2, "select OID,MODE_NAME,MODE_TYPE,MODE_ROWVAR from %s %s",g_BasMode,szSQL1);

	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL2, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	while(OciSql->Fetch())
	{
		StBasMode stModeInfo;
		memset(&stModeInfo,0,sizeof(StBasMode));
		
		GetModeDataFromToDb(OciSql, &stModeInfo);
		
		pModeArry->push_back(stModeInfo);
	}
	OciSql->Release();

	return TRUE;
}

BOOL CDataMng::GetModeDataOid(UINT ModeOid,StBasMode *pModeInfo)//通过Oid获得模板的信息
{

	int nRows = 0;
	char szSQL1[256] ={0,},szSQL2[256] ={0,};
	sprintf(szSQL1,_T("where OID=%d"),ModeOid);//所属部门OID//
	if( (nRows = GetModeCount(szSQL1))<=0)
	{
		return FALSE;
	}

	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取

	memset(szSQL2,0,256);
	sprintf(szSQL2,_T("select t1.*,t2.GROUP_NAME AS GROUP_NAME,t3.PRODUCT_NO AS PRODUCT_NO from %s t1 left join %s t2 on t1.GROUP_OID=t2.OID \
					  left join %s t3 on t1.PRODUCT_OID=t3.OID where t1.OID=%d"),
					  g_BasMode,g_HrGroup,g_BasProduct,ModeOid);

	//sprintf(szSQL2, "select OID,MODE_NAME,MODE_TYPE,MODE_ROWVAR from %s %s",g_BasMode,szSQL1);

	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL2, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	while(OciSql->Fetch())
	{
		GetModeDataFromToDb(OciSql, pModeInfo);
		GetModeXmlFile(pModeInfo->nOid,&pModeInfo->pXmlFile,pModeInfo->nModeSize);//16.获取XML模板文件

	}
	OciSql->Release();
	return TRUE;

}


BOOL CDataMng::AddNewMode(StBasMode *pStr)
{
	char szSQL[512] = {0};
	sprintf(szSQL, "insert into %s(OID,MODE_NAME,MODE_VERSION,MODE_TYPE,MODE_ROWVAR,\
				   MODE_SIZE,MODE_TABNAME,INIT_TABSRT,GROUP_OID,\
				   PRODUCT_OID,MODEL,PHASE,CREATE_TIME,CREATE_USER,FORMULA)\
				   values (%s,'%s','%s',%d,%d,  %d,'%s',%d,%d,%d,'%s','%s',to_date('%s','YYYY_MM_DD HH24:MI:SS'),'%s',%d)",
				   g_BasMode,
				   Seq_Mode,pStr->szModeName,pStr->szModeVersion,pStr->nModeType,pStr->nModeRowVar,pStr->nModeSize,
				   pStr->szModeTabName,pStr->nInitTabSrt,pStr->nGroupOid,pStr->stProductInfo.nOid,
				   pStr->szModel,pStr->szPhase,pStr->szCreateTime,pStr->szCreateUser,pStr->nFormula);
	
	if(!UpdateDataInfo(szSQL))
	{
		return FALSE;
	}

	if(!GetSeqId(Seq_ModeCurID,pStr->nOid))
	{
		return FALSE;
	}

	CString strText;
	strText = GetModeTabName(pStr);
	memset(pStr->szModeTabName,0,sizeof(pStr->szModeTabName));
	strcpy(pStr->szModeTabName,strText);

	if(!EditOldMode(pStr))
	{
		return FALSE;
	}
	return TRUE;
}
//判断本部门此产品下这个模板是否存在//
BOOL CDataMng::IsGroupProdModeExists(UINT GroupOid,UINT ProductOid,char *szModeName)
{
	int nRows = 0;
	char szSQL[256] = {0};
	sprintf(szSQL,_T("%s where MODE_NAME='%s' and GROUP_OID=%d and PRODUCT_OID=%d"),
		g_BasMode,szModeName,GroupOid,ProductOid);
	GetTableRowCount(szSQL, nRows);
	return nRows>=1;

}
BOOL CDataMng::EditOldMode(StBasMode *pStr)
{
	char szSQL[512] = {0};
	sprintf(szSQL, "update %s set MODE_NAME='%s',MODE_VERSION='%s',MODE_TYPE=%d,MODE_ROWVAR=%d,\
				   MODE_SIZE=%d,MODE_TABNAME='%s',INIT_TABSRT=%d,GROUP_OID=%d,PRODUCT_OID=%d,\
				   MODEL='%s',PHASE='%s',\
				   CREATE_TIME=to_date('%s','YYYY_MM_DD HH24:MI:SS'),CREATE_USER='%s',FORMULA=%d where \
				   OID=%d",
				   g_BasMode,
				   pStr->szModeName,pStr->szModeVersion,pStr->nModeType,pStr->nModeRowVar,pStr->nModeSize,
				   pStr->szModeTabName,pStr->nInitTabSrt,pStr->nGroupOid,pStr->stProductInfo.nOid,
				   pStr->szModel,pStr->szPhase,pStr->szCreateTime,pStr->szCreateUser,pStr->nFormula,pStr->nOid);

	return UpdateDataInfo(szSQL);


}
BOOL CDataMng::DelOldMode(UINT ModeOid)
{
	char szSQL[256] = {0};
	sprintf(szSQL, "delete from %s where OID=%d",
		g_BasMode,ModeOid);
	return UpdateDataInfo(szSQL);
}


BOOL CDataMng::UpdateModeXmlFile(UINT nModeOid, char *strFileInfo,int nLen)
{
	if(nModeOid<=0)
	{
		return FALSE;
	}

	char szSQL[256] = {0};
	sprintf(szSQL,"update %s set MODE_XMLFILE=empty_blob() where OID=%d",
		g_BasMode,nModeOid);

	if(!UpdateDataInfo(szSQL))
	{
		AfxMessageBox(_T("置空失败!"));
		return FALSE;
	}
	if(strFileInfo == NULL || nLen == 0)
	{
		AfxMessageBox(_T("模板配置文件为空!"));
		return TRUE;
	}
	memset(szSQL,0,256);
	sprintf(szSQL, "select MODE_XMLFILE from %s where OID=%d for update",
		g_BasMode,nModeOid);

	if(!UpdateOracleBlob(szSQL,"MODE_XMLFILE",strFileInfo,nLen))
	{
		AfxMessageBox(_T("写入失败!"));
		return FALSE;
	}
	return TRUE;
}


BOOL CDataMng::GetModeXmlFile(UINT nModeOid, char **strFileInfo,int &nLen)
{
	char szSQL[256] = {0};
	CString strFilePath;

	CStdioFile file;
	CFileException e;
	memset(szSQL,0,256);
	if(nModeOid<=0)
	{
		return FALSE;
	}
	//sprintf(szSQL, "update LTYTESTTABLE5 set XMLFILE='dsfgdfg' where ID='0000000001'");
	sprintf(szSQL, "select MODE_XMLFILE from %s where OID=%d",g_BasMode,nModeOid);

	nLen = 0;

	m_DMng.GetTableBolbInfo(szSQL,"MODE_XMLFILE",NULL,nLen);
	*strFileInfo = new char[nLen+1];
	
	memset(*strFileInfo,0,nLen+1);
	if(!m_DMng.GetTableBolbInfo(szSQL,"MODE_XMLFILE",*strFileInfo,nLen))
	{
		AfxMessageBox(_T("获取失败!"));
		return FALSE;
	}

	
	strFilePath.Format("%s\\%s\\%s",
		g_WorkPath,PATH_XML_MODE_PAR_CFG,MD_XML_FILE_TAB_SRT_INFO);
	remove(strFilePath);

	CString str = *strFileInfo;
	if(strcmp("<NULL>",*strFileInfo) == 0 || strcmp("<EMPTY_BLOB>",*strFileInfo) == 0)
	{
		nLen = 0;
		delete *strFileInfo;
		*strFileInfo = NULL;
		return TRUE;

	}
	if(!file.Open(strFilePath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite, &e))
	{
		char szMsg[128] = {0};
		e.GetErrorMessage(szMsg, 128);

		CString strErr;
		strErr.Format(_T("打开数据库日志文件失败，原因为: %s"), szMsg);
		//MessageBox(NULL, NULL, strErr,MB_ICONERROR|MB_OK);
		return FALSE;
	}


	file.Write(*strFileInfo,nLen);
	file.Close();

	return TRUE;

}

//模板结构表模块函数//
BOOL CDataMng::IsModeStrTabExists(UINT nModeOid)//检查模板结构表是否存在//
{
	int nRows = 0;
	char szSQL[256] = {0};
	sprintf(szSQL,_T("%s where MODE_OID=%d"),
		g_BasModeSave,nModeOid);
	GetTableRowCount(szSQL, nRows);
	return nRows>=1;
}

BOOL CDataMng::AddNewModeSave(StBasModeSave *pModeSave)
{
	char szSQL[512] = {0};
	sprintf(szSQL, "insert into %s(OID,MODE_OID,TAB_NAME,CREATE_TIME,CREATE_USER)\
				   values (%s,%d,'%s',to_date('%s','YYYY_MM_DD HH24:MI:SS'),'%s')",
				  g_BasModeSave,
				   Seq_Mode_Save,pModeSave->nModeOid,
				   pModeSave->szTabName,pModeSave->szCreateTime,pModeSave->szCreateUser);

	if(!UpdateDataInfo(szSQL))
	{
		return FALSE;
	}

	if(!GetSeqId(Seq_Mode_SaveCurID,pModeSave->nOid))
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CDataMng::GetAllModeSave(vector<StBasModeSave *> *pModeSaveArray)
{
	int nRows = 0;
	char szSQL[256] = {0};
	sprintf(szSQL,_T("%s"),g_BasModeSave);
	GetTableRowCount(szSQL, nRows);
	if(nRows <=0 )
	{
		return FALSE;
	}
	

	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("select * from %s"), g_BasModeSave);

	if(!g_pOrcOciDb->ExeSQL(OciSql, szSQL, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}	

	int     nLen = 0;
	CString str;

	while(OciSql->Fetch())
	{
		StBasModeSave *pModeSave = new StBasModeSave;
		memset(pModeSave,0,sizeof(StBasModeSave));

		pModeSave->nOid = atoi(GetFieldValue(_T("OID"),OciSql));
		pModeSave->nModeOid = atoi(GetFieldValue(_T("MODE_OID"),OciSql));
		strcpy(pModeSave->szTabName,GetFieldValue(_T("TAB_NAME"),OciSql));
		strcpy(pModeSave->szCreateTime,GetFieldValue(_T("CREATE_TIME"),OciSql));
		strcpy(pModeSave->szCreateUser,GetFieldValue(_T("CREATE_USER"),OciSql));

		pModeSaveArray->push_back(pModeSave);
	}

	OciSql->Release();

	return TRUE;	


}

BOOL CDataMng::DelOldModeSave(UINT nModeOid)
{
	char szSQL[256] = {0};
	sprintf(szSQL, "delete from %s where MODE_OID=%d",
		g_BasModeSave,nModeOid);
	return UpdateDataInfo(szSQL);
}
int CDataMng::GetDataCount(char *szTabName)
{
	int nRows = 0;
	m_DMng.GetTableRowCount(szTabName, nRows);
	return nRows;
}


//模板表字段的描述//
BOOL CDataMng::AddNewModeDesc(StBasModeDesc *pModeDesc)
{
	char szSQL[1024] = {0};
	sprintf(szSQL, "insert into %s(OID,MODE_OID,MODE_SAVE_OID,FIELD_NAME,DATA_TYPE,\
				   DESCXX,CREATE_TIME,CREATE_USER)\
				   values (%d,%d,%d,'%s',%d,'%s',to_date('%s','YYYY_MM_DD HH24:MI:SS'),'%s')",
				   g_BasModeDesc,
				   pModeDesc->nOid,pModeDesc->nModeOid,pModeDesc->nModeSaveOid,pModeDesc->szFieldName,pModeDesc->nDateType,
				   pModeDesc->szDescxx,pModeDesc->szCreateTime,pModeDesc->szCreateUser);

	if(!UpdateDataInfo(szSQL))
	{
		return FALSE;
	}
	return TRUE;

}
BOOL CDataMng::DelModeAllField(UINT nModeOid)
{
	char szSQL[256] = {0};
	sprintf(szSQL, "delete from %s where MODE_OID=%d",
		g_BasModeDesc,nModeOid);
	return UpdateDataInfo(szSQL);
}



int CDataMng::GetTaskCount(char *pTableName)
{
	int nRows = 0;
	char szSQL[256] = {0};
	sprintf(szSQL,_T("%s %s"),g_BasTask,pTableName);
	m_DMng.GetTableRowCount(szSQL, nRows);

	return nRows;

}
int  CDataMng::GetTaskCountGroup(UINT nGroupOid)//获取本部门的所有任务个数//
{
	int     i,nCount = 0,nTaskCount = 0;
	vector<StBasProduct> nArrayProduct;
	
	if(!m_DMng.GetGroupProductInfo (nGroupOid,&nArrayProduct))
	{
		return nTaskCount;
	}

	nCount = nArrayProduct.size();
	int nRows = 0;
	UINT ProdOid = 0;
	char szSQL1[256] ={0,};
	for (i = 0; i<nCount ;i++)
	{
		nRows = 0;
		ProdOid = nArrayProduct.at(i).nOid;
		sprintf(szSQL1,_T("where PRODUCT_OID=%d"),ProdOid);
		nRows = GetTaskCount(szSQL1);
		nTaskCount+=nRows;
	}
	nArrayProduct.clear();
	return nTaskCount;
}
int  CDataMng::GetTaskCountGroupStatus(UINT nGroupOid, int nTaskStatus)//获取本部门的某个状态的任务//
{

	int     i,nCount = 0,nTaskCount = 0;
	vector<StBasProduct> nArrayProduct;

	if(!m_DMng.GetGroupProductInfo (nGroupOid,&nArrayProduct))
	{
		return nTaskCount;
	}

	nCount = nArrayProduct.size();
	int nRows = 0;
	UINT ProdOid = 0;
	char szSQL1[256] ={0,};
	for (i = 0; i<nCount ;i++)
	{
		nRows = 0;
		ProdOid = nArrayProduct.at(i).nOid;
		sprintf(szSQL1,_T("where PRODUCT_OID=%d and TASK_STATUS=%d"),ProdOid,nTaskStatus);
		nRows = GetTaskCount(szSQL1);
		nTaskCount+=nRows;
	}
	nArrayProduct.clear();
	return nTaskCount;
	
}

int  CDataMng::GetTaskDataFromToDb(COciSQLCursor	*OciSql, StBasTask *pTaskInfo)
{
	pTaskInfo->stTaskBaseInfo.nOid = atoi(GetFieldValue(_T("OID"),OciSql));//任务OID
	strcpy(pTaskInfo->stTaskBaseInfo.szTaskName,GetFieldValue(_T("TASK_NAME"),OciSql));//任务名称
	strcpy(pTaskInfo->stTaskBaseInfo.szProjectNo,GetFieldValue(_T("PROJECT_NO"),OciSql));//检验单号
	pTaskInfo->stTaskBaseInfo.nTaskStatus = atoi(GetFieldValue(_T("TASK_STATUS"),OciSql));//任务状态
	pTaskInfo->stTaskBaseInfo.nTaskType = atoi(GetFieldValue(_T("TASK_TYPE"),OciSql));//任务类型
	strcpy(pTaskInfo->stTaskBaseInfo.szModel,GetFieldValue(_T("MODEL"),OciSql));//型号
	strcpy(pTaskInfo->stTaskBaseInfo.szPhase,GetFieldValue(_T("PHASE"),OciSql));//阶段
	pTaskInfo->stProductInfo.nOid = atoi(GetFieldValue(_T("PRODUCT_OID"),OciSql));//产品OID
	strcpy(pTaskInfo->stProductInfo.szProductName,GetFieldValue(_T("PRODUCT_NAME"),OciSql));//产品名称
	strcpy(pTaskInfo->stProductInfo.szProductNo,GetFieldValue(_T("PRODUCT_NO"),OciSql));//产品代号

	strcpy(pTaskInfo->stTaskBaseInfo.szProductCode,GetFieldValue(_T("PRODUCT_CODE"),OciSql));//产品编号
	pTaskInfo->stTaskBaseInfo.nCodeNumber = atoi(GetFieldValue(_T("CODE_COUNT"),OciSql));//数量
	strcpy(pTaskInfo->stTaskBaseInfo.szBatch,GetFieldValue(_T("BATCH"),OciSql));//批次号
	pTaskInfo->stHrUpDepart.nOid = atoi(GetFieldValue(_T("DEPART_OID"),OciSql));//交检部门
	strcpy(pTaskInfo->stHrUpDepart.szUpDepartName,GetFieldValue(_T("DEPART_NAME"),OciSql));//交检部门

	strcpy(pTaskInfo->stTaskBaseInfo.szUpUser,GetFieldValue(_T("UP_USER"),OciSql));//交检人
	strcpy(pTaskInfo->stTaskBaseInfo.szUpDate,GetFieldValue(_T("UP_DATE"),OciSql));//交检日期
	strcpy(pTaskInfo->stTaskBaseInfo.szSendDate,GetFieldValue(_T("SEND_DATE"),OciSql));//派工日期
	strcpy(pTaskInfo->stTaskBaseInfo.szCheckLeader,GetFieldValue(_T("CHECK_LEADER"),OciSql));//检验组长
	strcpy(pTaskInfo->stTaskBaseInfo.szCheckUser,GetFieldValue(_T("CHECK_USER"),OciSql));//检验员姓名
	strcpy(pTaskInfo->stTaskBaseInfo.szTechUser,GetFieldValue(_T("TECH_USER"),OciSql));//工艺员
	pTaskInfo->stTaskBaseInfo.nArmyTest = atoi(GetFieldValue(_T("ARMY_TEST"),OciSql));//军检
	pTaskInfo->stTaskBaseInfo.nDianShiNum = atoi(GetFieldValue(_T("DIANSHI_NUM"),OciSql));//典试数量

	strcpy(pTaskInfo->stTaskBaseInfo.szAccording1,GetFieldValue(_T("ACCORDING1"),OciSql));//验收依据1
	strcpy(pTaskInfo->stTaskBaseInfo.szAccording2,GetFieldValue(_T("ACCORDING2"),OciSql));//验收依据2
	strcpy(pTaskInfo->stTaskBaseInfo.szAccording3,GetFieldValue(_T("ACCORDING3"),OciSql));//验收依据3
	strcpy(pTaskInfo->stTaskBaseInfo.szAccording4,GetFieldValue(_T("ACCORDING4"),OciSql));//验收依据4
	strcpy(pTaskInfo->stTaskBaseInfo.szAccording5,GetFieldValue(_T("ACCORDING5"),OciSql));//验收依据5
	strcpy(pTaskInfo->stTaskBaseInfo.szTaskRemark,GetFieldValue(_T("TASK_REMARK"),OciSql));//备注
	strcpy(pTaskInfo->stTaskBaseInfo.szPlanBegTime,GetFieldValue(_T("PLAN_BEGTIME"),OciSql));//计划开始时间
	strcpy(pTaskInfo->stTaskBaseInfo.szPlanEndTime,GetFieldValue(_T("PLAN_ENDTIME"),OciSql));//计划结束时间
	strcpy(pTaskInfo->stTaskBaseInfo.szRealBegTime,GetFieldValue(_T("REAL_BEGTIME"),OciSql));//实际开始时间
	strcpy(pTaskInfo->stTaskBaseInfo.szRealEndTime,GetFieldValue(_T("REAL_ENDTIME"),OciSql));//实际结束时间

	strcpy(pTaskInfo->stTaskBaseInfo.szDownLoadDate,GetFieldValue(_T("DOWNLOAD_DATE"),OciSql));//任务下载时间
	strcpy(pTaskInfo->stTaskBaseInfo.szFinishDate,GetFieldValue(_T("FINISH_DATE"),OciSql));//任务完成时间
	strcpy(pTaskInfo->stTaskBaseInfo.szImportDate,GetFieldValue(_T("IMPORT_DATE"),OciSql));//数据导入时间
	strcpy(pTaskInfo->stTaskBaseInfo.szCreateDate,GetFieldValue(_T("CREATE_TIME"),OciSql));//任务创建时间
	strcpy(pTaskInfo->stTaskBaseInfo.szCreateUser,GetFieldValue(_T("CREATE_USER"),OciSql));//任务创建人

	pTaskInfo->stTaskBaseInfo.nGroupOid = atoi(GetFieldValue(_T("GROUP_OID"),OciSql));//所属部门
	strcpy(pTaskInfo->stTaskBaseInfo.szGroupName,GetFieldValue(_T("GROUP_NAME"),OciSql));//所属部门名称

	return 1;
}
BOOL CDataMng::GetProductTaskInfo(UINT ProdOid,vector<StBasTask *> *pArrayTask)
{
	int nRows = 0;
	char szSQL1[1024] ={0,},szSQL2[1024] ={0};
	sprintf(szSQL1,_T("where PRODUCT_OID=%d order by TASK_NAME"),ProdOid);
	if( (nRows = GetTaskCount(szSQL1))<=0)
	{
		return TRUE;
	}

	
	COciSQLCursor	*OciSql;
	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	memset(szSQL2,0,1024);
	sprintf(szSQL2,_T("select t1.*,t2.GROUP_NAME AS GROUP_NAME, t3.PRODUCT_NO AS PRODUCT_NO,t3.PRODUCT_NAME AS PRODUCT_NAME,\
					  t4.DEPART_NAME AS DEPART_NAME \
					  from %s t1 left join %s t2 on t1.GROUP_OID=t2.OID \
					  left join %s t3 on t1.PRODUCT_OID=t3.OID \
					  left join %s t4 on t1.DEPART_OID = t4.OID \
					  where t1.PRODUCT_OID=%d order by t1.TASK_NAME"),
					  g_BasTask,g_HrGroup,g_BasProduct,g_HrUpDepart,ProdOid);

	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL2, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	while(OciSql->Fetch())
	{
		StBasTask *pTask = new StBasTask;
		pTask->Release();
		GetTaskDataFromToDb(OciSql,pTask);
		pArrayTask->push_back(pTask);
	}
	OciSql->Release();
	
	return TRUE;

}

BOOL CDataMng::GetProductTaskStatusInfo(UINT ProdOid,int nTaskStatus,vector<StBasTask *> *pArrayTask)
{
	int nRows = 0;
	char szSQL1[1024] ={0,},szSQL2[1024] ={0,};
	sprintf(szSQL1,_T("where PRODUCT_OID=%d and TASK_STATUS=%d order by TASK_NAME"),
		ProdOid,nTaskStatus);//所属部门OID//
	if( (nRows = GetTaskCount(szSQL1))<=0)
	{
		return TRUE;
	}

	COciSQLCursor	*OciSql;
	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	memset(szSQL2,0,1024);
	sprintf(szSQL2,_T("select t1.*,t2.GROUP_NAME AS GROUP_NAME, t3.PRODUCT_NO AS PRODUCT_NO,t3.PRODUCT_NAME AS PRODUCT_NAME,\
					  t4.DEPART_NAME AS DEPART_NAME \
					  from %s t1 left join %s t2 on t1.GROUP_OID=t2.OID \
					  left join %s t3 on t1.PRODUCT_OID=t3.OID \
					  left join %s t4 on t1.DEPART_OID = t4.OID \
					  where t1.PRODUCT_OID=%d and t1.TASK_STATUS=%d order by t1.TASK_NAME"),
					  g_BasTask,g_HrGroup,g_BasProduct,g_HrUpDepart,ProdOid,nTaskStatus);

	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL2, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	while(OciSql->Fetch())
	{
		StBasTask *pTask = new StBasTask;
		pTask->Release();

		GetTaskDataFromToDb(OciSql,pTask);
		pArrayTask->push_back(pTask);
	}
	OciSql->Release();

	return TRUE;
}
BOOL CDataMng::IsStatusProdTaskExists(int nTaskStatus,UINT ProductOid)//判断当前产品下有此状态的任务//
{
	int nRows = 0;
	char szSQL[256] = {0};
	sprintf(szSQL,_T("%s where TASK_STATUS=%d and PRODUCT_OID=%d"),
		g_BasTask,nTaskStatus,ProductOid);
	GetTableRowCount(szSQL, nRows);
	return nRows>=1;
}

BOOL CDataMng::GetGroupTaskInfo(UINT nGroupOid, StBasTask *pTaskSearchInfo,vector<StBasTask> *pArrayTask)//模糊查询 任务//nGroupOid是所属部门 与交检部门无关
{

	int i, nCount,nRows = 0;
	char szSQL1[4096] ={0,},szSQL2[4096] ={0,};
	StBasTaskBaseInfo *pTaskBaseInfo = &pTaskSearchInfo->stTaskBaseInfo;
	StBasProduct *pProductInfo = &pTaskSearchInfo->stProductInfo;
	StHrUpDepart *pUpDepartInfo = &pTaskSearchInfo->stHrUpDepart;

	CString strCount,strData,str1,str2;
	CStringArray strArry1,strArry2;	


	//1.任务名称
	if(strcmp(pTaskBaseInfo->szTaskName,_T("")) != 0)
	{

		str1.Format(_T("t1.TASK_NAME like '%%%s%%'"),pTaskBaseInfo->szTaskName);
		str2.Format(_T("t1.TASK_NAME like '%%%s%%'"),pTaskBaseInfo->szTaskName);

		strArry1.Add(str1);
		strArry2.Add(str2);
	}

	//2.产品代号//
	if(strcmp(pProductInfo->szProductNo,_T("")) != 0)
	{

		str1.Format(_T("t3.PRODUCT_NO like '%%%s%%'"),pProductInfo->szProductNo);
		str2.Format(_T("t3.PRODUCT_NO like '%%%s%%'"),pProductInfo->szProductNo);

		strArry1.Add(str1);
		strArry2.Add(str2);
	}

	//3.产品批次号
	if(strcmp(pTaskBaseInfo->szBatch,_T("")) != 0)
	{

		str1.Format(_T("t1.BATCH like '%%%s%%'"),pTaskBaseInfo->szBatch);
		str2.Format(_T("t1.BATCH like '%%%s%%'"),pTaskBaseInfo->szBatch);

		strArry1.Add(str1);
		strArry2.Add(str2);
	}

	//4.产品名称
	if(strcmp(pProductInfo->szProductName,_T("")) != 0)
	{

		str1.Format(_T("t3.PRODUCT_NAME like '%%%s%%'"),pProductInfo->szProductName);
		str2.Format(_T("t3.PRODUCT_NAME like '%%%s%%'"),pProductInfo->szProductName);

		strArry1.Add(str1);
		strArry2.Add(str2);
	}

	//4.产品型号
	if(strcmp(pTaskBaseInfo->szModel,_T("")) != 0)
	{

		str1.Format(_T("t1.MODEL like '%%%s%%'"),pTaskBaseInfo->szModel);
		str2.Format(_T("t1.MODEL like '%%%s%%'"),pTaskBaseInfo->szModel);

		strArry1.Add(str1);
		strArry2.Add(str2);
	}


	//5.产品阶段
	if(strcmp(pTaskBaseInfo->szPhase,_T("")) != 0)
	{

		str1.Format(_T("t1.PHASE like '%%%s%%'"),pTaskBaseInfo->szPhase);
		str2.Format(_T("t1.PHASE like '%%%s%%'"),pTaskBaseInfo->szPhase);

		strArry1.Add(str1);
		strArry2.Add(str2);
	}

	//6.交检部门
	if(strcmp(pUpDepartInfo->szUpDepartName,_T("")) != 0)
	{

		str1.Format(_T("t4.DEPART_NAME like '%%%s%%'"),pUpDepartInfo->szUpDepartName);
		str2.Format(_T("t4.DEPART_NAME like '%%%s%%'"),pUpDepartInfo->szUpDepartName);

		strArry1.Add(str1);
		strArry2.Add(str2);
	}

	//7.检验组长
	if(strcmp(pTaskBaseInfo->szCheckLeader,_T("")) != 0)
	{

		str1.Format(_T("t1.CHECK_LEADER like '%%%s%%'"),pTaskBaseInfo->szCheckLeader);
		str2.Format(_T("t1.CHECK_LEADER like '%%%s%%'"),pTaskBaseInfo->szCheckLeader);

		strArry1.Add(str1);
		strArry2.Add(str2);
	}

	//8.检验员姓名
	if(strcmp(pTaskBaseInfo->szCheckUser,_T("")) != 0)
	{

		str1.Format(_T("t1.CHECK_USER like '%%%s%%'"),pTaskBaseInfo->szCheckUser);
		str2.Format(_T("t1.CHECK_USER like '%%%s%%'"),pTaskBaseInfo->szCheckUser);

		strArry1.Add(str1);
		strArry2.Add(str2);
	}



	//9.创建开始时间
	if(strcmp(pTaskBaseInfo->szCreateBeginTime,_T("")) != 0)
	{

		str1.Format(_T("t1.CREATE_TIME >= to_date('%s %s','YYYY_MM_DD HH24:MI:SS')"),
			pTaskBaseInfo->szCreateBeginTime,g_SearchBeginTime);
		str2.Format(_T("t1.CREATE_TIME >= to_date('%s %s','YYYY_MM_DD HH24:MI:SS')"),
			pTaskBaseInfo->szCreateBeginTime,g_SearchBeginTime);

		strArry1.Add(str1);
		strArry2.Add(str2);
	}

	//10.创建结束时间
	if(strcmp(pTaskBaseInfo->szCreateEndTime,_T("")) != 0)
	{

		str1.Format(_T("t1.CREATE_TIME <= to_date('%s %s','YYYY_MM_DD HH24:MI:SS')"),
			pTaskBaseInfo->szCreateEndTime,g_SearchEndTime);
		str2.Format(_T("t1.CREATE_TIME <= to_date('%s %s','YYYY_MM_DD HH24:MI:SS')"),
			pTaskBaseInfo->szCreateEndTime,g_SearchEndTime);

		strArry1.Add(str1);
		strArry2.Add(str2);
	}

	//11.创建人
	if(strcmp(pTaskBaseInfo->szCreateUser,_T("")) != 0)
	{

		str1.Format(_T("t1.CREATE_USER like '%%%s%%'"),pTaskBaseInfo->szCreateUser);
		str2.Format(_T("t1.CREATE_USER like '%%%s%%'"),pTaskBaseInfo->szCreateUser);

		strArry1.Add(str1);
		strArry2.Add(str2);
	}

	//12.派工开始时间
	if(strcmp(pTaskBaseInfo->szSendBeginTime,_T("")) != 0)
	{

		str1.Format(_T("t1.SEND_DATE >= to_date('%s %s','YYYY_MM_DD HH24:MI:SS')"),
			pTaskBaseInfo->szSendBeginTime,g_SearchBeginTime);
		str2.Format(_T("t1.SEND_DATE >= to_date('%s %s','YYYY_MM_DD HH24:MI:SS')"),
			pTaskBaseInfo->szSendBeginTime,g_SearchBeginTime);

		strArry1.Add(str1);
		strArry2.Add(str2);
	}

	//13.派工结束时间
	if(strcmp(pTaskBaseInfo->szSendEndTime,_T("")) != 0)
	{

		str1.Format(_T("t1.SEND_DATE <= to_date('%s %s','YYYY_MM_DD HH24:MI:SS')"),
			pTaskBaseInfo->szSendEndTime,g_SearchEndTime);
		str2.Format(_T("t1.SEND_DATE <= to_date('%s %s','YYYY_MM_DD HH24:MI:SS')"),
			pTaskBaseInfo->szSendEndTime,g_SearchEndTime);

		strArry1.Add(str1);
		strArry2.Add(str2);
	}

	//14.执行开始时间
	if(strcmp(pTaskBaseInfo->szDownLoadBeginTime,_T("")) != 0)
	{

		str1.Format(_T("t1.DOWNLOAD_DATE >= to_date('%s %s','YYYY_MM_DD HH24:MI:SS')"),
			pTaskBaseInfo->szDownLoadBeginTime,g_SearchBeginTime);
		str2.Format(_T("t1.DOWNLOAD_DATE >= to_date('%s %s','YYYY_MM_DD HH24:MI:SS')"),
			pTaskBaseInfo->szDownLoadBeginTime,g_SearchBeginTime);

		strArry1.Add(str1);
		strArry2.Add(str2);
	}

	//15.执行结束时间
	if(strcmp(pTaskBaseInfo->szDownLoadEndTime,_T("")) != 0)
	{

		str1.Format(_T("t1.DOWNLOAD_DATE <= to_date('%s %s','YYYY_MM_DD HH24:MI:SS')"),
			pTaskBaseInfo->szDownLoadEndTime,g_SearchEndTime);
		str2.Format(_T("t1.DOWNLOAD_DATE <= to_date('%s %s','YYYY_MM_DD HH24:MI:SS')"),
			pTaskBaseInfo->szDownLoadEndTime,g_SearchEndTime);

		strArry1.Add(str1);
		strArry2.Add(str2);
	}

	//16.完成开始时间
	if(strcmp(pTaskBaseInfo->szFinishBeginTime,_T("")) != 0)
	{

		str1.Format(_T("t1.FINISH_DATE >= to_date('%s %s','YYYY_MM_DD HH24:MI:SS')"),
			pTaskBaseInfo->szFinishBeginTime,g_SearchBeginTime);
		str2.Format(_T("t1.FINISH_DATE >= to_date('%s %s','YYYY_MM_DD HH24:MI:SS')"),
			pTaskBaseInfo->szFinishBeginTime,g_SearchBeginTime);

		strArry1.Add(str1);
		strArry2.Add(str2);
	}

	//17.完成结束时间
	if(strcmp(pTaskBaseInfo->szFinishEndTime,_T("")) != 0)
	{

		str1.Format(_T("t1.FINISH_DATE <= to_date('%s %s','YYYY_MM_DD HH24:MI:SS')"),
			pTaskBaseInfo->szFinishEndTime,g_SearchEndTime);
		str2.Format(_T("t1.FINISH_DATE <= to_date('%s %s','YYYY_MM_DD HH24:MI:SS')"),
			pTaskBaseInfo->szFinishEndTime,g_SearchEndTime);

		strArry1.Add(str1);
		strArry2.Add(str2);
	}


	//8.任务的状态 In(1,1,1,1,1)
	int nPos = 0;
	CString strTypeEnum1 = _T(""), strTypeEnum2 = _T("");
	CString strTemp;
	int nTypeArray[10] = {0,};
	if(pTaskBaseInfo->bTaskInit >= Sel_Check)//新任务 选中//
	{
		nTypeArray[nPos] = Task_Init;
		nPos++;

	}

	if(pTaskBaseInfo->bTaskOk >= Sel_Check)//已派工 选中//
	{
		nTypeArray[nPos] = Task_OK;
		nPos++;
	}

	if(pTaskBaseInfo->bTaskRuning >= Sel_Check)//执行中 选中//
	{
		nTypeArray[nPos] = Task_Runing;
		nPos++;
	}

	if(pTaskBaseInfo->bTaskFinish >= Sel_Check)//已完成 选中//
	{
		nTypeArray[nPos] = Task_Finish;
		nPos++;
	}

	if(nPos >=1)
	{
		strTypeEnum1.Format(_T(" t1.TASK_STATUS in("));
		strTypeEnum2.Format(_T(" t1.TASK_STATUS in("));
	}
	for(i = 0; i<nPos; i++)
	{
		if(i>=(nPos-1))
		{
			strTemp.Format(_T("%d) "), nTypeArray[i]);
		}else
		{
			strTemp.Format(_T("%d, "), nTypeArray[i]);
		}

		strTypeEnum1+=strTemp;
		strTypeEnum2+=strTemp;
	}

	if(!strTypeEnum1.IsEmpty())
	{
		strArry1.Add(strTypeEnum1);			//数据集个数
		strArry2.Add(strTypeEnum2);			//数据集信息
	}

	//9.是否军检 In(1,1);
	

	nPos = 0;
	strTypeEnum1 = _T(""), strTypeEnum2 = _T("");
	memset(nTypeArray, 0, sizeof(nTypeArray));

	switch(pTaskBaseInfo->nArmyTest)
	{
	case Army_Not:
		{
			nTypeArray[nPos] = Army_Not;
			nPos++;
		}
		break;
	case Army_Yes:
		{
			nTypeArray[nPos] = Army_Yes;
			nPos++;
		}
		break;
	default :
		{
			nTypeArray[nPos] = Army_Not;
			nPos++;
			nTypeArray[nPos] = Army_Yes;
			nPos++;
		}
		break;
	}

	if(nPos >=1)
	{
		strTypeEnum1.Format(_T(" t1.ARMY_TEST in("));
		strTypeEnum2.Format(_T(" t1.ARMY_TEST in("));
	}
	for(i = 0; i<nPos; i++)
	{
		if(i>=(nPos-1))
		{
			strTemp.Format(_T("%d) "), nTypeArray[i]);
		}else
		{
			strTemp.Format(_T("%d, "), nTypeArray[i]);
		}

		strTypeEnum1+=strTemp;
		strTypeEnum2+=strTemp;
	}

	if(!strTypeEnum1.IsEmpty())
	{
		strArry1.Add(strTypeEnum1);
		strArry2.Add(strTypeEnum2);
	}

	//10.任务的类型 In(1,1);
	nPos = 0;
	strTypeEnum1 = _T(""), strTypeEnum2 = _T("");
	memset(nTypeArray, 0, sizeof(nTypeArray));
	if(pTaskBaseInfo->bTaskTest >= Sel_Check)//检验 选中//
	{
		nTypeArray[nPos] = Task_Test;
		nPos++;

	}

	if(pTaskBaseInfo->bTaskReTest >= Sel_Check)//复验 选中//
	{
		nTypeArray[nPos] = Task_ReTest;
		nPos++;
	}

	if(pTaskBaseInfo->bTaskHelpReTest >= Sel_Check)//外协复验 选中//
	{
		nTypeArray[nPos] = Task_HelpReTest;
		nPos++;
	}

	if(nPos >=1)
	{
		strTypeEnum1.Format(_T(" t1.TASK_TYPE in("));
		strTypeEnum2.Format(_T(" t1.TASK_TYPE in("));
	}
	for(i = 0; i<nPos; i++)
	{
		if(i>=(nPos-1))
		{
			strTemp.Format(_T("%d) "), nTypeArray[i]);
		}else
		{
			strTemp.Format(_T("%d, "), nTypeArray[i]);
		}

		strTypeEnum1+=strTemp;
		strTypeEnum2+=strTemp;
	}

	if(!strTypeEnum1.IsEmpty())
	{
		strArry1.Add(strTypeEnum1);
		strArry2.Add(strTypeEnum2);
	}


	//组建测试条件
	nCount = strArry1.GetCount();

	if(nCount >=1)
	{
		strData.Format(_T(" where t1.GROUP_OID=%d and "), nGroupOid);
		strCount.Format(_T(" where t1.GROUP_OID=%d and "), nGroupOid);
	}else
	{
		strData.Format(_T(" where t1.GROUP_OID=%d"), nGroupOid);
		strCount.Format(_T(" where t1.GROUP_OID=%d"), nGroupOid);
	}

	for(i = 0;i<nCount;i++)
	{
		if(i>=(nCount-1))
		{
			str1.Format(_T("%s"),strArry1.GetAt(i));
			str2.Format(_T("%s"),strArry2.GetAt(i));
		}else
		{
			str1.Format(_T("%s and "),strArry1.GetAt(i));
			str2.Format(_T("%s and "),strArry2.GetAt(i));
		}

		strData+=str1;		//条件:  Where *
		strCount+=str2;		//条件:  Where *

	}


	//统计结果个数
	memset(szSQL1,0,sizeof(szSQL1));
	sprintf(szSQL1,_T("%s t1 left join %s t2 on t1.GROUP_OID=t2.OID \
					  left join %s t3 on t1.PRODUCT_OID=t3.OID \
					  left join %s t4 on t1.DEPART_OID = t4.OID %s"),g_BasTask,g_HrGroup,g_BasProduct,g_HrUpDepart,strData);

	if(!m_DMng.GetTableRowCount(szSQL1, nRows))
	{
		return FALSE;
	}

	if( (pTaskBaseInfo->nResultNum = nRows) <=0)
	{
		return FALSE;
	}


	//获取测试结果信息
	COciSQLCursor	*OciSql;
	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	//t1=任务表    (t1.GROUP_OID == t2.OID) && (t1.PRODUCT_OID == t3.OID) && (t1.DEPART_OID == t4.OID)  
	//t2=组表      
	//t3=产品表
	//t4=交检部门
	memset(szSQL2,0,sizeof(szSQL2));
	sprintf(szSQL2,_T("select rownum AS RN,t1.*,t2.GROUP_NAME AS GROUP_NAME, t3.PRODUCT_NO AS PRODUCT_NO,t3.PRODUCT_NAME AS PRODUCT_NAME,\
					  t4.DEPART_NAME AS DEPART_NAME \
					  from %s t1 left join %s t2 on t1.GROUP_OID=t2.OID \
					  left join %s t3 on t1.PRODUCT_OID=t3.OID \
					  left join %s t4 on t1.DEPART_OID = t4.OID \
					  %s order by t1.TASK_NAME"),
					  g_BasTask,g_HrGroup,g_BasProduct,g_HrUpDepart,strData);
	

	int nBgnNum = 0, nEndNum = 0;
	nBgnNum = (pTaskBaseInfo->nPerPageNum*(pTaskBaseInfo->nCurPage-1));
	nEndNum = (pTaskBaseInfo->nPerPageNum*(pTaskBaseInfo->nCurPage));
	memset(szSQL1, 0, sizeof(szSQL1));
	if(pTaskBaseInfo->nPerPageNum == g_nSearchPerPageNum[All_Result])
	{
		sprintf(szSQL1, _T("%s"), szSQL2);
	}else
	{
		sprintf(szSQL1, _T("select * from( select * from(%s) where RN > %d) where RN <= %d"), szSQL2, nBgnNum, nEndNum);
	}


	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL1, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	while(OciSql->Fetch())
	{
		StBasTask  nTaskInfo;
		nTaskInfo.Release();
		GetTaskDataFromToDb(OciSql,&nTaskInfo);
		pArrayTask->push_back(nTaskInfo);

	}
	OciSql->Release();

	return TRUE;
}

BOOL CDataMng::GetTaskDataOid(UINT nTaskOid,StBasTask *pStTaskInfo)//通过Oid获得任务的信息
{

	int nRows = 0;
	char szSQL1[1024] ={0,},szSQL2[1024] ={0,};
	sprintf(szSQL1,_T("where OID=%d"),
		nTaskOid);//所属部门OID//
	if( (nRows = GetTaskCount(szSQL1))<=0)
	{
		return TRUE;
	}

	COciSQLCursor	*OciSql;
	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	memset(szSQL2,0,1024);
	sprintf(szSQL2,_T("select t1.*,t2.GROUP_NAME AS GROUP_NAME, t3.PRODUCT_NO AS PRODUCT_NO,t3.PRODUCT_NAME AS PRODUCT_NAME,\
					  t4.DEPART_NAME AS DEPART_NAME \
					  from %s t1 left join %s t2 on t1.GROUP_OID=t2.OID \
					  left join %s t3 on t1.PRODUCT_OID=t3.OID \
					  left join %s t4 on t1.DEPART_OID = t4.OID \
					  where t1.OID=%d"),
					  g_BasTask,g_HrGroup,g_BasProduct,g_HrUpDepart,nTaskOid);

	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL2, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	while(OciSql->Fetch())
	{
		GetTaskDataFromToDb(OciSql,pStTaskInfo);
	}
	OciSql->Release();

	return TRUE;
}

BOOL CDataMng::GetTaskDataProdOidTaskName(UINT nProdOid,char *szTaskName, StBasTask *pStTaskInfo)//通过产品OID和任务名称获取任务信息//
{
	int nRows = 0;
	char szSQL1[1024] ={0,},szSQL2[1024] ={0,};
	sprintf(szSQL1,_T("where PRODUCT_OID=%d and TASK_NAME='%s'"),
		nProdOid, szTaskName);//所属部门OID//
	if( (nRows = GetTaskCount(szSQL1))<=0)
	{
		return TRUE;
	}

	COciSQLCursor	*OciSql;
	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	memset(szSQL2,0,1024);
	sprintf(szSQL2,_T("select t1.*,t2.GROUP_NAME AS GROUP_NAME, t3.PRODUCT_NO AS PRODUCT_NO,t3.PRODUCT_NAME AS PRODUCT_NAME,\
					  t4.DEPART_NAME AS DEPART_NAME \
					  from %s t1 left join %s t2 on t1.GROUP_OID=t2.OID \
					  left join %s t3 on t1.PRODUCT_OID=t3.OID \
					  left join %s t4 on t1.DEPART_OID = t4.OID \
					  where t1.PRODUCT_OID=%d and TASK_NAME='%s'"),
					  g_BasTask,g_HrGroup,g_BasProduct,g_HrUpDepart,nProdOid, szTaskName);

	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL2, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	while(OciSql->Fetch())
	{
		GetTaskDataFromToDb(OciSql,pStTaskInfo);
	}
	OciSql->Release();

	return TRUE;
}

BOOL CDataMng::AddNewTask(StBasTask *pTaskInfo)
{
	char szSQL[4096] = {0,};
	sprintf(szSQL, "insert into %s(OID,TASK_NAME,PROJECT_NO,TASK_STATUS,TASK_TYPE,\
				   MODEL,PHASE,PRODUCT_OID,PRODUCT_CODE,CODE_COUNT,\
				   BATCH,DEPART_OID,UP_USER,UP_DATE,SEND_DATE,\
				   CHECK_LEADER,CHECK_USER,TECH_USER,ARMY_TEST,DIANSHI_NUM,\
				   ACCORDING1,ACCORDING2,ACCORDING3,ACCORDING4,ACCORDING5,\
				   TASK_REMARK,PLAN_BEGTIME,PLAN_ENDTIME,REAL_BEGTIME,REAL_ENDTIME,\
				   DOWNLOAD_DATE,FINISH_DATE,IMPORT_DATE,CREATE_TIME,CREATE_USER, GROUP_OID)\
				   values (%s,'%s','%s',%d,%d,\
				   '%s','%s',%d,'%s',%d,\
				   '%s',%d,'%s',to_date('%s','YYYY_MM_DD HH24:MI:SS'),to_date('%s','YYYY_MM_DD HH24:MI:SS'),\
				   '%s','%s','%s',%d,%d,\
				   '%s','%s','%s','%s','%s',\
				   '%s',to_date('%s','YYYY_MM_DD HH24:MI:SS'),to_date('%s','YYYY_MM_DD HH24:MI:SS'),\
				   to_date('%s','YYYY_MM_DD HH24:MI:SS'),to_date('%s','YYYY_MM_DD HH24:MI:SS'),\
				   to_date('%s','YYYY_MM_DD HH24:MI:SS'),to_date('%s','YYYY_MM_DD HH24:MI:SS'),\
				   to_date('%s','YYYY_MM_DD HH24:MI:SS'),to_date('%s','YYYY_MM_DD HH24:MI:SS'),'%s', %d)",
				   g_BasTask,
				   Seq_Task,pTaskInfo->stTaskBaseInfo.szTaskName,pTaskInfo->stTaskBaseInfo.szProjectNo,pTaskInfo->stTaskBaseInfo.nTaskStatus,pTaskInfo->stTaskBaseInfo.nTaskType,
				   pTaskInfo->stTaskBaseInfo.szModel,pTaskInfo->stTaskBaseInfo.szPhase,pTaskInfo->stProductInfo.nOid,pTaskInfo->stTaskBaseInfo.szProductCode,pTaskInfo->stTaskBaseInfo.nCodeNumber,
				   pTaskInfo->stTaskBaseInfo.szBatch,pTaskInfo->stHrUpDepart.nOid,pTaskInfo->stTaskBaseInfo.szUpUser,pTaskInfo->stTaskBaseInfo.szUpDate,pTaskInfo->stTaskBaseInfo.szSendDate,
				   pTaskInfo->stTaskBaseInfo.szCheckLeader,pTaskInfo->stTaskBaseInfo.szCheckUser,pTaskInfo->stTaskBaseInfo.szTechUser,pTaskInfo->stTaskBaseInfo.nArmyTest,pTaskInfo->stTaskBaseInfo.nDianShiNum,
				   pTaskInfo->stTaskBaseInfo.szAccording1,pTaskInfo->stTaskBaseInfo.szAccording2,pTaskInfo->stTaskBaseInfo.szAccording3,pTaskInfo->stTaskBaseInfo.szAccording4,pTaskInfo->stTaskBaseInfo.szAccording5,
				   pTaskInfo->stTaskBaseInfo.szTaskRemark,pTaskInfo->stTaskBaseInfo.szPlanBegTime,pTaskInfo->stTaskBaseInfo.szPlanEndTime,pTaskInfo->stTaskBaseInfo.szRealBegTime,pTaskInfo->stTaskBaseInfo.szRealEndTime,
				   pTaskInfo->stTaskBaseInfo.szDownLoadDate,pTaskInfo->stTaskBaseInfo.szFinishDate,pTaskInfo->stTaskBaseInfo.szImportDate,pTaskInfo->stTaskBaseInfo.szCreateDate,
				   pTaskInfo->stTaskBaseInfo.szCreateUser,pTaskInfo->stTaskBaseInfo.nGroupOid);

	if(!UpdateDataInfo(szSQL))
	{
		return FALSE;
	}

	if(!GetSeqId(Seq_TaskCurID,pTaskInfo->stTaskBaseInfo.nOid))
	{
		return FALSE;
	}
	return TRUE;

}
//判断本产品某系列下这个任务是否存在//
BOOL CDataMng::IsProductTaskExists(UINT ProductOid,char *szTaskName)
{
	int nRows = 0;
	char szSQL[256] = {0};
	sprintf(szSQL,_T("%s where TASK_NAME='%s' and PRODUCT_OID=%d"),
		g_BasTask,szTaskName,ProductOid);
	GetTableRowCount(szSQL, nRows);
	return nRows>=1;

}
BOOL CDataMng::EditOldTask(StBasTask *pTaskInfo)
{
	StBasTaskBaseInfo *pTaskBaseInfo = &pTaskInfo->stTaskBaseInfo;
	StBasProduct      *pProductInfo = &pTaskInfo->stProductInfo;
	StHrUpDepart      *pUpDepartInfo = &pTaskInfo->stHrUpDepart;
	char szSQL[4096] = {0,};
	sprintf(szSQL, "update %s set TASK_NAME='%s',PROJECT_NO='%s',TASK_STATUS=%d,TASK_TYPE=%d,\
				   MODEL='%s',PHASE='%s',PRODUCT_OID=%d,PRODUCT_CODE='%s',CODE_COUNT=%d,BATCH='%s',\
				   DEPART_OID=%d,UP_USER='%s',UP_DATE=to_date('%s','YYYY_MM_DD HH24:MI:SS'),\
				   SEND_DATE=to_date('%s','YYYY_MM_DD HH24:MI:SS'),CHECK_LEADER='%s',\
				   CHECK_USER='%s',TECH_USER='%s',ARMY_TEST=%d,DIANSHI_NUM=%d,ACCORDING1='%s',\
				   ACCORDING2='%s',ACCORDING3='%s',ACCORDING4='%s',ACCORDING5='%s',TASK_REMARK='%s',\
				   PLAN_BEGTIME=to_date('%s','YYYY_MM_DD HH24:MI:SS'),\
				   PLAN_ENDTIME=to_date('%s','YYYY_MM_DD HH24:MI:SS'),\
				   REAL_BEGTIME=to_date('%s','YYYY_MM_DD HH24:MI:SS'),\
				   REAL_ENDTIME=to_date('%s','YYYY_MM_DD HH24:MI:SS'),\
				   DOWNLOAD_DATE=to_date('%s','YYYY_MM_DD HH24:MI:SS'),\
				   FINISH_DATE=to_date('%s','YYYY_MM_DD HH24:MI:SS'),\
				   IMPORT_DATE=to_date('%s','YYYY_MM_DD HH24:MI:SS'),\
				   CREATE_TIME=to_date('%s','YYYY_MM_DD HH24:MI:SS'),\
				   CREATE_USER='%s', GROUP_OID=%d \
				   where \
				   OID=%d",
				   g_BasTask,
				   pTaskBaseInfo->szTaskName,pTaskBaseInfo->szProjectNo,pTaskBaseInfo->nTaskStatus,pTaskBaseInfo->nTaskType,
				   pTaskBaseInfo->szModel,pTaskBaseInfo->szPhase,pProductInfo->nOid,pTaskBaseInfo->szProductCode,
				   pTaskBaseInfo->nCodeNumber,pTaskBaseInfo->szBatch,pUpDepartInfo->nOid,pTaskBaseInfo->szUpUser,
				   pTaskBaseInfo->szUpDate,pTaskBaseInfo->szSendDate,pTaskBaseInfo->szCheckLeader,pTaskBaseInfo->szCheckUser,
				   pTaskBaseInfo->szTechUser,pTaskBaseInfo->nArmyTest,pTaskBaseInfo->nDianShiNum,pTaskBaseInfo->szAccording1,
				   pTaskBaseInfo->szAccording2,pTaskBaseInfo->szAccording3,pTaskBaseInfo->szAccording4,pTaskBaseInfo->szAccording5,
				   pTaskBaseInfo->szTaskRemark,pTaskBaseInfo->szPlanBegTime,pTaskBaseInfo->szPlanEndTime,
				   pTaskBaseInfo->szRealBegTime,pTaskBaseInfo->szRealEndTime,pTaskBaseInfo->szDownLoadDate,
				   pTaskBaseInfo->szFinishDate,pTaskBaseInfo->szImportDate,pTaskBaseInfo->szCreateDate,
				   pTaskBaseInfo->szCreateUser,pTaskBaseInfo->nGroupOid,
				   pTaskBaseInfo->nOid);

	return UpdateDataInfo(szSQL);
}
BOOL CDataMng::DelOldTask(UINT nTaskOid)
{
	char szSQL[256] = {0};
	sprintf(szSQL, "delete from %s where OID=%d",
		g_BasTask,nTaskOid);
	return UpdateDataInfo(szSQL);

}

//----------------------------------------------------------------------------------
BOOL CDataMng::DelAllTask(UINT nGroupOid)												//删除所有任务
{
	char szSQL[256] = {0};
	sprintf(szSQL, "delete from %s where GROUP_OID=%d",
		g_BasTask, nGroupOid);
	if(UpdateDataInfo(szSQL))
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CDataMng::DelAllTask_AllCode(UINT nGroupOid)										//删除任务所有编号
{
	char szSQL[256] = {0};
	sprintf(szSQL, "delete from %s where GROUP_OID=%d",
		g_BasTaskCode,nGroupOid);
	if(UpdateDataInfo(szSQL))
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CDataMng::DelAllTask_ALLMode(UINT nGroupOid)										//删除任务所有模板
{
	char szSQL[256] = {0};
	sprintf(szSQL, "delete from %s where GROUP_OID=%d",
		g_BasTaskMode,nGroupOid);
	if(UpdateDataInfo(szSQL))
	{
		return TRUE;
	}
	return FALSE;
}
BOOL CDataMng::DelAllTask_ALLPicNum(UINT nGroupOid)										//删除所有任务图号信息
{
	char szSQL[256] = {0};
	sprintf(szSQL, "delete from %s where GROUP_OID=%d",
		g_BasTaskPicNum,nGroupOid);
	if(UpdateDataInfo(szSQL))
	{
		return TRUE;
	}
	return FALSE;
}
//---------------------------------------------------------------------------------

int CDataMng::GetTaskCodeCount(char *pTableName)
{
	int nRows = 0;
	char szSQL[256] = {0};
	sprintf(szSQL,_T("%s %s"),g_BasTaskCode,pTableName);
	m_DMng.GetTableRowCount(szSQL, nRows);

	return nRows;
}
int  CDataMng::GetTaskCodeDataFromToDb(COciSQLCursor	*OciSql, StBasTaskCode *pTaskCode)
{
	pTaskCode->nOid = atoi(GetFieldValue(_T("OID"),OciSql));//任务编号表OID
	pTaskCode->nTaskOid = atoi(GetFieldValue(_T("TASK_OID"),OciSql));//任务OID
	pTaskCode->nCodeIndex = atoi(GetFieldValue(_T("CODE_INDEX"),OciSql));//任务内编号顺序从1开始
	pTaskCode->nDianshiTest = atoi(GetFieldValue(_T("DIANSHI_TEST"),OciSql));//是否典试
	strcpy(pTaskCode->szCodeName,GetFieldValue(_T("CODE_NAME"),OciSql));//编号名称

	return 1;
}
BOOL CDataMng::GetTaskCodeData(StBasTask *pTaskInfo,UINT nTaskOid)
{
	pTaskInfo->ReleaseCode();
	vector<StBasTaskCode *> *pArryTaskCode = &pTaskInfo->pArryTaskCode;
	int nRows = 0;
	char szSQL1[1024] ={0,},szSQL2[1024] ={0,};
	sprintf(szSQL1,_T("where TASK_OID=%d order by CODE_INDEX"),nTaskOid);
	if( (nRows = GetTaskCodeCount(szSQL1))<=0)
	{
		return FALSE;
	}
	
	COciSQLCursor	*OciSql;
	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	memset(szSQL2,0,sizeof(szSQL2));
	sprintf(szSQL2,_T("select * from %s %s"),
					  g_BasTaskCode,szSQL1);

	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL2, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	while(OciSql->Fetch())
	{
		StBasTaskCode *pTaskCode = new StBasTaskCode;
		memset(pTaskCode, 0, sizeof(StBasTaskCode));
		GetTaskCodeDataFromToDb(OciSql,pTaskCode);
		pArryTaskCode->push_back(pTaskCode);
	}
	OciSql->Release();

	return TRUE;

}
BOOL CDataMng::AddNewTaskCode(StBasTaskCode *pTaskCode)
{
	char szSQL[512] = {0};

	pTaskCode->nOid = m_DMng.GetTabLeastOid(g_BasTaskCode);
	sprintf(szSQL, "insert into %s(OID,TASK_OID,CODE_INDEX,DIANSHI_TEST,CODE_NAME,GROUP_OID)\
				   values (%d,%d,%d,%d,'%s',%d)",
				   g_BasTaskCode,
				   pTaskCode->nOid,pTaskCode->nTaskOid,pTaskCode->nCodeIndex,
				   pTaskCode->nDianshiTest,pTaskCode->szCodeName,
				   g_CurSelDepart.nOid	//组OID
				   );

	if(!UpdateDataInfo(szSQL))
	{
		return FALSE;
	}

	/*if(!GetSeqId(Seq_Task_CodeCurID,pTaskCode->nOid))
	{
		return FALSE;
	}*/
	return TRUE;
}

BOOL CDataMng::IsTaskCodeExists(UINT nTaskOid,char *szCodeName)//判断本任务下这个编号是否存在//
{
	int nRows = 0;
	char szSQL[256] = {0};
	sprintf(szSQL,_T("%s where CODE_NAME='%s' and TASK_OID=%d"),
		g_BasTaskCode,szCodeName,nTaskOid);
	GetTableRowCount(szSQL, nRows);
	return nRows>=1;

}
BOOL CDataMng::EditOldTaskCode(StBasTaskCode *pTaskCode)//主要修改 CODE_INDEX 顺序//
{
	char szSQL[512] = {0};
	sprintf(szSQL, "update %s set TASK_OID=%d,CODE_INDEX=%d where \
				   OID=%d",
				   g_BasTaskCode,
				   pTaskCode->nTaskOid,pTaskCode->nCodeIndex,pTaskCode->nOid);

	return UpdateDataInfo(szSQL);
}
BOOL CDataMng::DelOldTaskCode(UINT nTaskOid,char *szCodeName)
{
	char szSQL[256] = {0};
	sprintf(szSQL, "delete from %s where TASK_OID=%d and CODE_NAME='%s'",
		g_BasTaskCode,nTaskOid,szCodeName);
	return UpdateDataInfo(szSQL);
}
BOOL CDataMng::DelAllTaskCode(UINT nTaskOid)
{
	char szSQL[256] = {0};
	sprintf(szSQL, "delete from %s where TASK_OID=%d",
		g_BasTaskCode,nTaskOid);
	return UpdateDataInfo(szSQL);
}
int  CDataMng::GetTaskModeCount(char *pTableName)
{
	int nRows = 0;
	char szSQL[256] = {0};
	sprintf(szSQL,_T("%s %s"),g_BasTaskMode,pTableName);
	m_DMng.GetTableRowCount(szSQL, nRows);

	return nRows;
}
int  CDataMng::GetTaskModeDataFromToDb(COciSQLCursor	*OciSql, StBasTaskMode *pTaskMode)
{
	pTaskMode->nOid = atoi(GetFieldValue(_T("OID"),OciSql));//任务编号表OID
	pTaskMode->nTaskOid = atoi(GetFieldValue(_T("TASK_OID"),OciSql));//任务OID
	pTaskMode->nModeIndex = atoi(GetFieldValue(_T("MODE_INDEX"),OciSql));//任务内模板顺序从1开始
	pTaskMode->nModeOid = atoi(GetFieldValue(_T("MODE_OID"),OciSql));//模板OID
	strcpy(pTaskMode->szModeName, GetFieldValue(_T("MODE_NAME"),OciSql)); //模板名称
	pTaskMode->nModeType = atoi(GetFieldValue(_T("MODE_TYPE"),OciSql));//模板OID
	pTaskMode->nModeRowvar = atoi(GetFieldValue(_T("MODE_ROWVAR"),OciSql));//模板OID
	pTaskMode->nFormula = atoi(GetFieldValue(_T("FORMULA"),OciSql));//模板OID

	return 1;
}
BOOL CDataMng::GetTaskModeData(StBasTask *pTaskInfo,UINT nTaskOid)
{
	pTaskInfo->ReleaseMode();
	vector<StBasTaskMode *> *pArryTaskMode = &pTaskInfo->pArryTaskMode;
	int nRows = 0;
	char szSQL1[1024] ={0,},szSQL2[1024] ={0,};
	sprintf(szSQL1,_T("where TASK_OID=%d order by MODE_INDEX"),nTaskOid);
	if( (nRows = GetTaskModeCount(szSQL1))<=0)
	{
		return TRUE;
	}

	COciSQLCursor	*OciSql;
	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	memset(szSQL2,0,sizeof(szSQL2));
	sprintf(szSQL2,_T("select t1.*,t2.* from %s t1 left join %s t2 on t2.OID=t1.MODE_OID %s"),
		g_BasTaskMode,g_BasMode,szSQL1);

	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL2, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	while(OciSql->Fetch())
	{
		StBasTaskMode *pTaskMode = new StBasTaskMode;
		memset(pTaskMode, 0, sizeof(StBasTaskMode));
		GetTaskModeDataFromToDb(OciSql,pTaskMode);
		pArryTaskMode->push_back(pTaskMode);
	}
	OciSql->Release();

	return TRUE;
}
BOOL CDataMng::AddNewTaskMode(StBasTaskMode *pTaskMode)
{
	pTaskMode->nOid = m_DMng.GetTabLeastOid(g_BasTaskMode);
	char szSQL[512] = {0};
	sprintf(szSQL, "insert into %s(OID,TASK_OID,MODE_INDEX,MODE_OID, GROUP_OID)\
				   values (%d,%d,%d,%d,%d)",
				   g_BasTaskMode,
				   pTaskMode->nOid,pTaskMode->nTaskOid,pTaskMode->nModeIndex,
				   pTaskMode->nModeOid,
				   g_CurSelDepart.nOid	//组OID
				   );

	if(!UpdateDataInfo(szSQL))
	{
		return FALSE;
	}

	/*if(!GetSeqId(Seq_Task_ModeCurID,pTaskMode->nOid))
	{
		return FALSE;
	}*/
	return TRUE;
}

BOOL CDataMng::DelAllTaskMode(UINT nTaskOid)
{
	char szSQL[256] = {0};
	sprintf(szSQL, "delete from %s where TASK_OID=%d",
		g_BasTaskMode,nTaskOid);
	return UpdateDataInfo(szSQL);
}

BOOL CDataMng::UpdateTaskModeInfoFile(UINT nTaskModeOid,char *strFileInfo,int nLen)
{
	if(nTaskModeOid<=0)
	{
		return FALSE;
	}
	char szSQL[256] = {0};
	sprintf(szSQL,"update %s set MODE_INFOFILE=empty_blob() where OID=%d",
		g_BasTaskMode,nTaskModeOid);

	if(!UpdateDataInfo(szSQL))
	{
		AfxMessageBox(_T("置空失败!"));
		return FALSE;
	}
	memset(szSQL,0,256);
	sprintf(szSQL, "select MODE_INFOFILE from %s where OID=%d for update",
		g_BasTaskMode,nTaskModeOid);

	if(!UpdateOracleBlob(szSQL,"MODE_INFOFILE",strFileInfo,nLen))
	{
		AfxMessageBox(_T("写入失败!"));
		return FALSE;
	}
	return TRUE;
}
BOOL CDataMng::GetTaskModeInfoFile(UINT nTaskOid,UINT nModeOid, char **strFileInfo,int &nLen)
{
	return TRUE;
}

BOOL CDataMng::UpdateTaskModeXmlFile(UINT nTaskModeOid, char *strFileInfo,int nLen)
{
	if(nTaskModeOid<=0)
	{
		return FALSE;
	}
	char szSQL[256] = {0};
	sprintf(szSQL,"update %s set MODE_XMLFILE=empty_blob() where OID=%d",
		g_BasTaskMode,nTaskModeOid);

	if(!UpdateDataInfo(szSQL))
	{
		AfxMessageBox(_T("置空失败!"));
		return FALSE;
	}
	memset(szSQL,0,256);
	sprintf(szSQL, "select MODE_XMLFILE from %s where OID=%d for update",
		g_BasTaskMode,nTaskModeOid);

	if(!UpdateOracleBlob(szSQL,"MODE_XMLFILE",strFileInfo,nLen))
	{
		AfxMessageBox(_T("写入失败!"));
		return FALSE;
	}
	return TRUE;
}
BOOL CDataMng::GetTaskModeXmlFile(UINT nTaskOid,UINT nModeOid, char **strFileInfo,int &nLen)
{
	return TRUE;
}
int  CDataMng::GetTaskPicNumCount(char *pTableName)
{
	int nRows = 0;
	char szSQL[256] = {0};
	sprintf(szSQL,_T("%s %s"),g_BasTaskPicNum,pTableName);
	m_DMng.GetTableRowCount(szSQL, nRows);

	return nRows;

}

int  CDataMng::GetTaskPicNumDataFromToDb(COciSQLCursor	*OciSql, StBasTaskPicNum *pTaskPicNum)
{
	
	pTaskPicNum->nOid = atoi(GetFieldValue(_T("OID"),OciSql));//任务编号表OID
	pTaskPicNum->nTaskOid = atoi(GetFieldValue(_T("TASK_OID"),OciSql));//任务OID
	pTaskPicNum->nPicNumIndex = atoi(GetFieldValue(_T("PICNUM_INDEX"),OciSql));//任务内图号顺序从1开始
	pTaskPicNum->nPicNumOid = atoi(GetFieldValue(_T("PICNUM_OID"),OciSql));//图号Oid
	strcpy(pTaskPicNum->szPicNumNo, GetFieldValue(_T("PICNUM_NO"),OciSql)); //产品图号名称
	strcpy(pTaskPicNum->szPicNumName, GetFieldValue(_T("PICNUM_NAME"),OciSql)); //产品图号代号

	return 1;
}
BOOL CDataMng::GetTaskPicNumData(StBasTask *pTaskInfo,UINT nTaskOid)
{
	pTaskInfo->ReleasePicNum();
	vector<StBasTaskPicNum *> *pPicNumArry = &pTaskInfo->pArryTaskPicNum;
	int nRows = 0;
	char szSQL1[1024] ={0,},szSQL2[1024] ={0,};
	sprintf(szSQL1,_T("where TASK_OID=%d order by PICNUM_INDEX"),nTaskOid);
	if( (nRows = GetTaskPicNumCount(szSQL1))<=0)
	{
		return FALSE;
	}

	COciSQLCursor	*OciSql;
	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	memset(szSQL2,0,sizeof(szSQL2));
	sprintf(szSQL2,_T("select t1.*, t2.* from %s t1 left join %s t2 on t1.PICNUM_OID= t2.OID %s"),
		g_BasTaskPicNum,g_BasProductPicNum, szSQL1);

	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL2, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	while(OciSql->Fetch())
	{
		StBasTaskPicNum *pTaskPicNum = new StBasTaskPicNum;
		memset(pTaskPicNum, 0, sizeof(StBasTaskPicNum));
		GetTaskPicNumDataFromToDb(OciSql,pTaskPicNum);
		pPicNumArry->push_back(pTaskPicNum);
	}
	OciSql->Release();
	return TRUE;
}

BOOL CDataMng::AddNewTaskPicNum(StBasTaskPicNum *pTaskPicNum)
{
	//ztedit for 2017-03-23 %s->%d
	pTaskPicNum->nOid = m_DMng.GetTabLeastOid(g_BasTaskPicNum);
	char szSQL[512] = {0};
	sprintf(szSQL, "insert into %s(OID,TASK_OID,PICNUM_INDEX,PICNUM_OID,GROUP_OID)\
				   values (%d,%d,%d,%d,%d)",
				   g_BasTaskPicNum,
				   pTaskPicNum->nOid,pTaskPicNum->nTaskOid,pTaskPicNum->nPicNumIndex,
				   pTaskPicNum->nPicNumOid,
				   g_CurSelDepart.nOid			//组OID
				   );

	if(!UpdateDataInfo(szSQL))
	{
		return FALSE;
	}

	/*if(!GetSeqId(Seq_Task_PicNumCurID,pTaskPicNum->nOid))
	{
		return FALSE;
	}*/
	return TRUE;
}
BOOL CDataMng::DelAllTaskPicNum(UINT nTaskOid)
{
	char szSQL[256] = {0};
	sprintf(szSQL, "delete from %s where TASK_OID=%d",
		g_BasTaskPicNum,nTaskOid);
	return UpdateDataInfo(szSQL);
}

int CDataMng::GetTstResultCountTaskName(char *szTabName)
{
	int nRows = 0;
	char szSQL[256] = {0};
	sprintf(szSQL,_T("%s"),szTabName);
	m_DMng.GetTableRowCount(szSQL, nRows);
	return nRows;
}
int CDataMng::GetTaskResultDataDataFromToDb(COciSQLCursor	*OciSql, StTstResultBaseNew *pTaskBaseData)  //通过一个数据集获取一项结果数据
{
	StBasTaskBaseInfo *pTaskBaseInfo = &pTaskBaseData->stTaskInfo.stTaskBaseInfo;
	StBasProduct      *pProductInfo = &pTaskBaseData->stTaskInfo.stProductInfo;
	StHrUpDepart      *pUpDepartInfo = &pTaskBaseData->stTaskInfo.stHrUpDepart;

	pTaskBaseData->nOid = atoi(GetFieldValue(_T("OID"),OciSql));//任务编号表OID
	strcpy(pTaskBaseInfo->szSendDate, GetFieldValue(_T("SEND_DATE"),OciSql)); //产品图号代号
	strcpy(pTaskBaseInfo->szImportDate, GetFieldValue(_T("IMPORT_DATE"),OciSql)); //产品图号代号
	strcpy(pTaskBaseInfo->szTaskName, GetFieldValue(_T("TASK_NAME"),OciSql)); //产品图号代号
	strcpy(pProductInfo->szProductNo, GetFieldValue(_T("PRODUCT_NO"),OciSql)); //产品图号代号
	strcpy(pProductInfo->szProductName, GetFieldValue(_T("PRODUCT_NAME"),OciSql)); //产品图号代号
	strcpy(pTaskBaseInfo->szCheckUser, GetFieldValue(_T("CHECK_USER"),OciSql)); //产品图号代号


	return 1;

}
BOOL CDataMng::GetGroupTstResultBaseData(StBasTask *pResultSearchInfo, vector<StTstResultBaseNew> *stTstResultBaseDataArray)
{
	StBasTaskBaseInfo *pSearchTaskBaseInfo = &pResultSearchInfo->stTaskBaseInfo;
	StBasProduct      *pSearchProduct = &pResultSearchInfo->stProductInfo;
	//数据量过大 使用分页查找的方法//
	CString strNum,strResultTabName;
	strResultTabName.Format(_T("%s%.4d"),g_ResultBase,pSearchTaskBaseInfo->nGroupOid);
	if(!IsHrGroupSaveExists(pSearchTaskBaseInfo->nGroupOid))
	{
		return FALSE;
	}
	int i,nCount;
	int nRows = 0;
	char szSQL1[1024] ={0},szSQL2[1024] ={0};

	CString str,str1;
	CStringArray strArry;
	if(strcmp(pSearchTaskBaseInfo->szTaskName,_T("")) != 0)
	{

		str1.Format(_T("t1.task_name like '%%%s%%'"),pSearchTaskBaseInfo->szTaskName);
		strArry.Add(str1);
	}

	if(strcmp(pSearchProduct->szProductNo,_T("")) != 0)
	{

		str1.Format(_T("t1.PRODUCT_NO like '%%%s%%'"),pSearchProduct->szProductNo);
		strArry.Add(str1);
	}

	

	if(strcmp(pSearchTaskBaseInfo->szSendBeginTime,_T("")) != 0)
	{

		str1.Format(_T("t1.SEND_DATE >= to_date('%s','YYYY_MM_DD')"),pSearchTaskBaseInfo->szSendBeginTime);
		strArry.Add(str1);
	}

	if(strcmp(pSearchTaskBaseInfo->szSendEndTime,_T("")) != 0)
	{

		str1.Format(_T("t1.SEND_DATE <= to_date('%s','YYYY_MM_DD')"),pSearchTaskBaseInfo->szSendEndTime);
		strArry.Add(str1);
	}


	nCount = strArry.GetCount();
	if(nCount>=1)
	{
		str.Format(_T(" where "));
	}
	for(i = 0;i<nCount;i++)
	{
		if(i>=nCount-1)
		{
			str1.Format(_T("%s"),strArry.GetAt(i));
		}else
		{
			str1.Format(_T("%s and "),strArry.GetAt(i));
		}

		str+=str1;

	}

	memset(szSQL1,0,sizeof(szSQL1));
	sprintf(szSQL1,_T("%s t1 %s"),
		strResultTabName,str);
	if( (pSearchTaskBaseInfo->nResultNum = nRows = GetTstResultCountTaskName(szSQL1))<=0)
	{
		return FALSE;
	}

	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	memset(szSQL2,0,sizeof(szSQL2));
	sprintf(szSQL2, "select rownum AS RN,t1.* from %s t1 %s",
		strResultTabName,str);

	//分页操作//
	int nBgnNum = 0, nEndNum = 0;
	nBgnNum = (pSearchTaskBaseInfo->nPerPageNum*(pSearchTaskBaseInfo->nCurPage-1));
	nEndNum = (pSearchTaskBaseInfo->nPerPageNum*(pSearchTaskBaseInfo->nCurPage));
	memset(szSQL1, 0, sizeof(szSQL1));
	if(pSearchTaskBaseInfo->nPerPageNum == g_nSearchPerPageNum[All_Result])
	{
		sprintf(szSQL1, _T("%s"), szSQL2);
	}else
	{
		sprintf(szSQL1, _T("select * from( select * from(%s) where RN > %d) where RN <= %d"), szSQL2, nBgnNum, nEndNum);
	}


	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL1, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	stTstResultBaseDataArray->clear();
	while(OciSql->Fetch())
	{
		StTstResultBaseNew stTaskBaseData;
		stTaskBaseData.Release();
		GetTaskResultDataDataFromToDb(OciSql,&stTaskBaseData);
		stTstResultBaseDataArray->push_back(stTaskBaseData);
	}
	OciSql->Release();
	return TRUE;
}
BOOL  CDataMng::GetTaskTstResultBaseData(StBasTask *pResultSearchInfo, vector<StTstResultBaseNew> *stTstResultBaseDataArray)
{
	StBasTaskBaseInfo *pSearchTaskBaseInfo = &pResultSearchInfo->stTaskBaseInfo;
	StBasProduct      *pSearchProduct = &pResultSearchInfo->stProductInfo;

	CString strNum,strResultTabName;
	UINT nGroupOid = pSearchTaskBaseInfo->nGroupOid;
	UINT nTaskOid = pSearchTaskBaseInfo->nOid;
	strResultTabName.Format(_T("%s%.4d"),g_ResultBase,nGroupOid);

	if(!IsHrGroupSaveExists(nGroupOid))
	{
		return FALSE;
	}
	int i,nCount;
	int nRows = 0;
	char szSQL1[1024] ={0},szSQL2[1024] ={0};
	sprintf(szSQL1,_T("%s where TASK_OID=%d"),strResultTabName,nTaskOid);
	if( (nRows = GetTstResultCountTaskName(szSQL1))<=0)
	{
		return FALSE;
	}
	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);



	CString str,str1;
	CStringArray strArry;

	if(strcmp(pSearchTaskBaseInfo->szSendBeginTime,_T("")) != 0)
	{

		str1.Format(_T("t1.SEND_DATE >= to_date('%s','YYYY_MM_DD')"),pSearchTaskBaseInfo->szSendBeginTime);
		strArry.Add(str1);
	}

	if(strcmp(pSearchTaskBaseInfo->szSendEndTime,_T("")) != 0)
	{

		str1.Format(_T("t1.SEND_DATE <= to_date('%s','YYYY_MM_DD')"),pSearchTaskBaseInfo->szSendEndTime);
		strArry.Add(str1);
	}


	nCount = strArry.GetCount();
	for(i = 0;i<nCount;i++)
	{

		str1.Format(_T("%s and "),strArry.GetAt(i));

		str+=str1;

	}


	//读取
	sprintf(szSQL2, "select t1.* from %s t1 \
					where %s t1.TASK_OID=%d ",
					strResultTabName,str,nTaskOid);

	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL2, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	stTstResultBaseDataArray->clear();
	while(OciSql->Fetch())
	{
		StTstResultBaseNew stTaskBaseData;
		stTaskBaseData.Release();
		GetTaskResultDataDataFromToDb(OciSql,&stTaskBaseData);
		stTstResultBaseDataArray->push_back(stTaskBaseData);
	}
	OciSql->Release();

	
	return TRUE;
}






int CDataMng::GetTaskResultDataDataFromToDb(COciSQLCursor	*OciSql, StTstResultAtta *pResultAttachData)  //通过一个数据集获取一项结果数据
{
	pResultAttachData->nOid = atoi(GetFieldValue("OID",OciSql));
	pResultAttachData->nTaskOid = atoi(GetFieldValue("TASK_OID",OciSql));//02.任务Oid
	strcpy(pResultAttachData->szTaskName,GetFieldValue("TASK_NAME",OciSql));//02.任务名称
	pResultAttachData->nModeOid = atoi(GetFieldValue("MODE_OID",OciSql)); //03.模板Oid
	pResultAttachData->nProductOid = atoi(GetFieldValue("PRODUCT_OID",OciSql));//04.产品代号Oid
	strcpy(pResultAttachData->szProductName,GetFieldValue("PRODUCT_NAME",OciSql));
	strcpy(pResultAttachData->szProductNo,GetFieldValue("PRODUCT_NO",OciSql));
	strcpy(pResultAttachData->szModel,GetFieldValue("MODEL",OciSql));
	strcpy(pResultAttachData->szPhase,GetFieldValue("PHASE",OciSql));
	strcpy(pResultAttachData->szProductCode,GetFieldValue("PRODUCT_CODE",OciSql));
	strcpy(pResultAttachData->szModeName,GetFieldValue("MODE_NAME",OciSql));

	pResultAttachData->nModeType = atoi(GetFieldValue("MODE_TYPE",OciSql));
	pResultAttachData->nModeRowVar = atoi(GetFieldValue("MODE_ROWVAR",OciSql));
	pResultAttachData->nDianshiTest = atoi(GetFieldValue("DIANSHI_TEST",OciSql));
	pResultAttachData->nPicNumCount = atoi(GetFieldValue("PICNUM_COUNT",OciSql));
	pResultAttachData->nPercent = atoi(GetFieldValue("PERCENT",OciSql));
	pResultAttachData->bFinished = atoi(GetFieldValue("FINISHED",OciSql));


	strcpy(pResultAttachData->szFinishedTime,GetFieldValue("FINISHED_TIME",OciSql));
	strcpy(pResultAttachData->szCheckUser,GetFieldValue("CHECK_USER",OciSql));
	strcpy(pResultAttachData->szSendDate,GetFieldValue("SEND_DATE",OciSql));
	strcpy(pResultAttachData->szImportDate,GetFieldValue("IMPORT_DATE",OciSql));
	pResultAttachData->nBaseOid = atoi(GetFieldValue("BASE_OID",OciSql));

	return 1;
}
//多条件综合查询结果数据//
BOOL CDataMng::GetGroupTstResultAttachData(StBasTask *pResultSearchInfo,vector<StTstResultAtta> *pStResultAttaArray)
{
	
	StBasTaskBaseInfo *pTaskBaseInfo = &pResultSearchInfo->stTaskBaseInfo;
	StBasProduct      *pProductInfo = &pResultSearchInfo->stProductInfo;
	StHrUpDepart      *pUpDepartInfo = &pResultSearchInfo->stHrUpDepart;


	UINT nGroupOid = pTaskBaseInfo->nGroupOid;
	CString strNum,strResultTabName;
	strResultTabName.Format(_T("%s%.4d"),g_ResultAtta,nGroupOid);
	if(!IsHrGroupSaveExists(nGroupOid))
	{
		return FALSE;
	}
	int i,nCount;
	int nRows = 0;
	char szSQL1[4096] ={0,};
	char szSQL2[4096] ={0,};


	CString str,str1;
	CStringArray strArry;
	if(strcmp(pTaskBaseInfo->szTaskName,_T("")) != 0)
	{

		str1.Format(_T("t1.task_name like '%%%s%%'"),pTaskBaseInfo->szTaskName);
		strArry.Add(str1);
	}

	if(strcmp(pProductInfo->szProductNo,_T("")) != 0)
	{

		str1.Format(_T("t1.PRODUCT_NO like '%%%s%%'"),pProductInfo->szProductNo);
		strArry.Add(str1);
	}

	if(strcmp(pProductInfo->szProductName,_T("")) != 0)
	{

		str1.Format(_T("t1.PRODUCT_NAME like '%%%s%%'"),pProductInfo->szProductName);
		strArry.Add(str1);
	}

	if(strcmp(pTaskBaseInfo->szProductCode,_T("")) != 0)
	{

		str1.Format(_T("t1.PRODUCT_CODE like '%%%s%%'"),pTaskBaseInfo->szProductCode);
		strArry.Add(str1);
	}
	if(strcmp(pTaskBaseInfo->szSendBeginTime,_T("")) != 0)
	{

		str1.Format(_T("t1.SEND_DATE >= to_date('%s','YYYY_MM_DD')"),pTaskBaseInfo->szSendBeginTime);
		strArry.Add(str1);
	}

	if(strcmp(pTaskBaseInfo->szSendEndTime,_T("")) != 0)
	{

		str1.Format(_T("t1.SEND_DATE <= to_date('%s','YYYY_MM_DD')"),pTaskBaseInfo->szSendEndTime);
		strArry.Add(str1);
	}


	nCount = strArry.GetCount();
	if(nCount>=1)
	{
		str.Format(_T(" where "));
	}
	for(i = 0;i<nCount;i++)
	{
		if(i>=nCount-1)
		{
			str1.Format(_T("%s"),strArry.GetAt(i));
		}else
		{
			str1.Format(_T("%s and "),strArry.GetAt(i));
		}

		str+=str1;

	}



	sprintf(szSQL1,_T(" %s t1 %s"),strResultTabName,str);
	if(!m_DMng.GetTableRowCount(szSQL1, nRows))
	{
		return FALSE;
	}
	if( (pTaskBaseInfo->nResultNum = nRows)<=0)
	{
		return FALSE;
	}

	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	memset(szSQL2, 0,sizeof(szSQL2));
	sprintf(szSQL2, "select rownum AS RN,t1.* from %s",szSQL1);

	//分页操作//
	int nBgnNum = 0, nEndNum = 0;
	nBgnNum = (pTaskBaseInfo->nPerPageNum*(pTaskBaseInfo->nCurPage-1));
	nEndNum = (pTaskBaseInfo->nPerPageNum*(pTaskBaseInfo->nCurPage));
	memset(szSQL1, 0, sizeof(szSQL1));
	if(pTaskBaseInfo->nPerPageNum == g_nSearchPerPageNum[All_Result])
	{
		sprintf(szSQL1, _T("%s"), szSQL2);
	}else
	{
		sprintf(szSQL1, _T("select * from( select * from(%s) where RN > %d) where RN <= %d"), szSQL2, nBgnNum, nEndNum);
	}


	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL1, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	while(OciSql->Fetch())
	{
		StTstResultAtta nResultAtta;
		memset(&nResultAtta, 0,sizeof(StTstResultAtta));
		GetTaskResultDataDataFromToDb(OciSql,&nResultAtta);
		pStResultAttaArray->push_back(nResultAtta);
	}
	OciSql->Release();

	return TRUE;
}
BOOL  CDataMng::GetTstResultAttaBaseOid(UINT nGroupOid,UINT nBaseOid,
										 vector<StTstResultAtta> *pStResultAttaArray)
{
	CString strNum,strResultTabName;
	strResultTabName.Format(_T("%s%.4d"),g_ResultAtta,nGroupOid);
	if(!IsHrGroupSaveExists(nGroupOid))
	{
		return FALSE;
	}

	int nRows = 0;
	char szSQL1[256] ={0};
	sprintf(szSQL1,_T(" %s where BASE_OID=%d"),strResultTabName,nBaseOid);
	if(!m_DMng.GetTableRowCount(szSQL1, nRows))
	{
		return FALSE;
	}
	if( nRows<=0)
	{
		return FALSE;
	}

	char			szSQL[256] = {0};
	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	sprintf(szSQL, "select * from %s ",szSQL1);

	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	CString		str,str1;



	StTstResultAtta *pTstResultInfo;

	while(OciSql->Fetch())
	{
		StTstResultAtta nResultAtta;
		memset(&nResultAtta, 0,sizeof(StTstResultAtta));

		pTstResultInfo = &nResultAtta;
		pTstResultInfo->nOid = atoi(GetFieldValue("OID",OciSql));
		pTstResultInfo->nTaskOid = atoi(GetFieldValue("TASK_OID",OciSql));//02.任务Oid
		strcpy(pTstResultInfo->szTaskName,GetFieldValue("TASK_NAME",OciSql));//02.任务名称
		pTstResultInfo->nModeOid = atoi(GetFieldValue("MODE_OID",OciSql)); //03.模板Oid
		pTstResultInfo->nProductOid = atoi(GetFieldValue("PRODUCT_OID",OciSql));//04.产品代号Oid
		strcpy(pTstResultInfo->szProductName,GetFieldValue("PRODUCT_NAME",OciSql));
		strcpy(pTstResultInfo->szProductNo,GetFieldValue("PRODUCT_NO",OciSql));
		strcpy(pTstResultInfo->szModel,GetFieldValue("MODEL",OciSql));
		strcpy(pTstResultInfo->szPhase,GetFieldValue("PHASE",OciSql));
		strcpy(pTstResultInfo->szProductCode,GetFieldValue("PRODUCT_CODE",OciSql));
		strcpy(pTstResultInfo->szModeName,GetFieldValue("MODE_NAME",OciSql));

		pTstResultInfo->nModeType = atoi(GetFieldValue("MODE_TYPE",OciSql));
		pTstResultInfo->nModeRowVar = atoi(GetFieldValue("MODE_ROWVAR",OciSql));
		pTstResultInfo->nDianshiTest = atoi(GetFieldValue("DIANSHI_TEST",OciSql));
		pTstResultInfo->nPicNumCount = atoi(GetFieldValue("PICNUM_COUNT",OciSql));
		pTstResultInfo->nPercent = atoi(GetFieldValue("PERCENT",OciSql));
		pTstResultInfo->bFinished = atoi(GetFieldValue("FINISHED",OciSql));


		strcpy(pTstResultInfo->szFinishedTime,GetFieldValue("FINISHED_TIME",OciSql));
		strcpy(pTstResultInfo->szCheckUser,GetFieldValue("CHECK_USER",OciSql));
		strcpy(pTstResultInfo->szSendDate,GetFieldValue("SEND_DATE",OciSql));
		strcpy(pTstResultInfo->szImportDate,GetFieldValue("IMPORT_DATE",OciSql));
		pTstResultInfo->nBaseOid = atoi(GetFieldValue("BASE_OID",OciSql));

		pStResultAttaArray->push_back(nResultAtta);
	}
	OciSql->Release();

	return TRUE;
}

BOOL  CDataMng::GetTstResultAttaBaseOidAndProductCode(
	UINT nGroupOid,UINT nBaseOid,char *szProductCode,vector<StTstResultAtta> *pStResultAttaArray)
{
	CString strNum,strResultTabName;
	strResultTabName.Format(_T("%s%.4d"),g_ResultAtta,nGroupOid);
	if(!IsHrGroupSaveExists(nGroupOid))
	{
		return FALSE;
	}
	
	int nRows = 0;
	char szSQL1[256] ={0};
	sprintf(szSQL1,_T(" %s where BASE_OID=%d and PRODUCT_CODE='%s'"),strResultTabName,nBaseOid,szProductCode);
	if(!m_DMng.GetTableRowCount(szSQL1, nRows))
	{
		return FALSE;
	}
	if( nRows<=0)
	{
		return FALSE;
	}

	char			szSQL[256] = {0};
	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	sprintf(szSQL, "select * from %s ",szSQL1);

	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}

	CString		str,str1;



	StTstResultAtta *pTstResultInfo;
	
	while(OciSql->Fetch())
	{
		StTstResultAtta nResultAtta;
		memset(&nResultAtta, 0,sizeof(StTstResultAtta));

		pTstResultInfo = &nResultAtta;
		pTstResultInfo->nOid = atoi(GetFieldValue("OID",OciSql));
		pTstResultInfo->nTaskOid = atoi(GetFieldValue("TASK_OID",OciSql));//02.任务Oid
		pTstResultInfo->nModeOid = atoi(GetFieldValue("MODE_OID",OciSql)); //03.模板Oid
		pTstResultInfo->nProductOid = atoi(GetFieldValue("PRODUCT_OID",OciSql));//04.产品代号Oid
		strcpy(pTstResultInfo->szProductName,GetFieldValue("PRODUCT_NAME",OciSql));
		strcpy(pTstResultInfo->szProductNo,GetFieldValue("PRODUCT_NO",OciSql));
		strcpy(pTstResultInfo->szModel,GetFieldValue("MODEL",OciSql));
		strcpy(pTstResultInfo->szPhase,GetFieldValue("PHASE",OciSql));
		strcpy(pTstResultInfo->szProductCode,GetFieldValue("PRODUCT_CODE",OciSql));
		strcpy(pTstResultInfo->szModeName,GetFieldValue("MODE_NAME",OciSql));

		pTstResultInfo->nModeType = atoi(GetFieldValue("MODE_TYPE",OciSql));
		pTstResultInfo->nModeRowVar = atoi(GetFieldValue("MODE_ROWVAR",OciSql));
		pTstResultInfo->nDianshiTest = atoi(GetFieldValue("DIANSHI_TEST",OciSql));
		pTstResultInfo->nPicNumCount = atoi(GetFieldValue("PICNUM_COUNT",OciSql));
		pTstResultInfo->nPercent = atoi(GetFieldValue("PERCENT",OciSql));
		pTstResultInfo->bFinished = atoi(GetFieldValue("FINISHED",OciSql));


		strcpy(pTstResultInfo->szFinishedTime,GetFieldValue("FINISHED_TIME",OciSql));
		strcpy(pTstResultInfo->szCheckUser,GetFieldValue("CHECK_USER",OciSql));
		strcpy(pTstResultInfo->szSendDate,GetFieldValue("SEND_DATE",OciSql));
		strcpy(pTstResultInfo->szImportDate,GetFieldValue("IMPORT_DATE",OciSql));
		pTstResultInfo->nBaseOid = atoi(GetFieldValue("BASE_OID",OciSql));

		pStResultAttaArray->push_back(nResultAtta);
	}
	OciSql->Release();

	return TRUE;
}
BOOL CDataMng::GetTstResultOid(UINT nGroupOid,UINT nAttaOid, StTstResultAtta *pTstResultInfo)
{
	//数据量过大 使用分页查找的方法//
	CString strNum,strResultTabName;
	strResultTabName.Format(_T("%s%.4d"),g_ResultAtta,nGroupOid);

	if(!IsHrGroupSaveExists(nGroupOid))
	{
		return FALSE;
	}
	int nRows = 0;
	char szSQL1[256] ={0},szSQL2[256] ={0};
	sprintf(szSQL1,_T("%s where OID=%d"),strResultTabName,nAttaOid);
	if( (nRows = GetTstResultCountTaskName(szSQL1))<=0)
	{
		return FALSE;
	}

	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//读取
	sprintf(szSQL2, "select * from %s ",szSQL1);

	if (!g_pOrcOciDb->ExeSQL(OciSql, szSQL2, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}



	while(OciSql->Fetch())
	{
		pTstResultInfo->nOid = atoi(GetFieldValue("OID",OciSql));
		pTstResultInfo->nTaskOid = atoi(GetFieldValue("TASK_OID",OciSql));//02.任务Oid
		strcpy(pTstResultInfo->szTaskName, GetFieldValue("TASK_NAME",OciSql));//02.任务名称
		pTstResultInfo->nModeOid = atoi(GetFieldValue("MODE_OID",OciSql)); //03.模板Oid
		pTstResultInfo->nProductOid = atoi(GetFieldValue("PRODUCT_OID",OciSql));//04.产品代号Oid
		strcpy(pTstResultInfo->szProductName,GetFieldValue("PRODUCT_NAME",OciSql));
		strcpy(pTstResultInfo->szProductNo,GetFieldValue("PRODUCT_NO",OciSql));
		strcpy(pTstResultInfo->szModel,GetFieldValue("MODEL",OciSql));
		strcpy(pTstResultInfo->szPhase,GetFieldValue("PHASE",OciSql));
		strcpy(pTstResultInfo->szProductCode,GetFieldValue("PRODUCT_CODE",OciSql));
		strcpy(pTstResultInfo->szModeName,GetFieldValue("MODE_NAME",OciSql));

		pTstResultInfo->nModeType = atoi(GetFieldValue("MODE_TYPE",OciSql));
		pTstResultInfo->nModeRowVar = atoi(GetFieldValue("MODE_ROWVAR",OciSql));
		pTstResultInfo->nDianshiTest = atoi(GetFieldValue("DIANSHI_TEST",OciSql));
		pTstResultInfo->nPicNumCount = atoi(GetFieldValue("PICNUM_COUNT",OciSql));
		pTstResultInfo->nPercent = atoi(GetFieldValue("PERCENT",OciSql));
		pTstResultInfo->bFinished = atoi(GetFieldValue("FINISHED",OciSql));


		strcpy(pTstResultInfo->szFinishedTime,GetFieldValue("FINISHED_TIME",OciSql));
		strcpy(pTstResultInfo->szCheckUser,GetFieldValue("CHECK_USER",OciSql));
		strcpy(pTstResultInfo->szSendDate,GetFieldValue("SEND_DATE",OciSql));
		strcpy(pTstResultInfo->szImportDate,GetFieldValue("IMPORT_DATE",OciSql));
		pTstResultInfo->nBaseOid = atoi(GetFieldValue("BASE_OID",OciSql));

	}
	OciSql->Release();

	return TRUE;

}
BOOL  CDataMng::GetAttaXmlFile(UINT nGroupOid,UINT nAttaOid)
{
	CString strNum,strResultTabName;
	strResultTabName.Format(_T("%s%.4d"),g_ResultAtta,nGroupOid);

	if(!IsHrGroupSaveExists(nGroupOid))
	{
		return FALSE;
	}
	int nRows = 0;
	char szSQL1[256] ={0},szSQL2[256] ={0};
	sprintf(szSQL1,_T("%s where OID=%d"),strResultTabName,nAttaOid);
	if( (nRows = GetTstResultCountTaskName(szSQL1))<=0)
	{
		return FALSE;
	}

	char szSQL[256] = {0};
	char *strFileInfo = NULL;
	int  nLen;
	CString strFilePath;

	CStdioFile file;
	CFileException e;
	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL, "select MODE_XMLFILE from %s where OID=%d",strResultTabName,nAttaOid);

	nLen = 0;

	m_DMng.GetTableBolbInfo(szSQL,"MODE_XMLFILE",NULL,nLen);
	strFileInfo = new char[nLen+1];

	memset(strFileInfo,0,nLen+1);
	if(!m_DMng.GetTableBolbInfo(szSQL,"MODE_XMLFILE",strFileInfo,nLen))
	{
		AfxMessageBox(_T("获取失败!"));
		return FALSE;
	}


	strFilePath.Format("%s\\%s\\%s",
		g_WorkPath,PATH_XML_MODE_PAR_CFG,MD_XML_FILE_TAB_SRT_INFO);
	remove(strFilePath);

	if(strcmp("<NULL>",strFileInfo) == 0)
	{
		nLen = 0;
		delete strFileInfo;
		strFileInfo = NULL;
		return TRUE;

	}
	if(!file.Open(strFilePath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite, &e))
	{
		char szMsg[128] = {0};
		e.GetErrorMessage(szMsg, 128);

		CString strErr;
		strErr.Format(_T("打开数据库日志文件失败，原因为: %s"), szMsg);
		//MessageBox(NULL, NULL, strErr,MB_ICONERROR|MB_OK);
		return FALSE;
	}


	file.Write(strFileInfo,nLen);
	file.Close();

	delete strFileInfo;
	strFileInfo = NULL;

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL, "select DATA_XMLFILE from %s where OID=%d",strResultTabName,nAttaOid);

	nLen = 0;

	m_DMng.GetTableBolbInfo(szSQL,"DATA_XMLFILE",NULL,nLen);
	strFileInfo = new char[nLen+1];

	memset(strFileInfo,0,nLen+1);
	if(!m_DMng.GetTableBolbInfo(szSQL,"DATA_XMLFILE",strFileInfo,nLen))
	{
		AfxMessageBox(_T("获取失败!"));
		return FALSE;
	}


	strFilePath.Format("%s\\%s\\%s",
		g_WorkPath,PATH_XML_MODE_PAR_CFG,MD_XML_FILE_TAB_OUT_INFO);
	remove(strFilePath);

	if(strcmp("<NULL>",strFileInfo) == 0)
	{
		nLen = 0;
		delete strFileInfo;
		strFileInfo = NULL;
		return TRUE;

	}
	if(!file.Open(strFilePath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite, &e))
	{
		char szMsg[128] = {0};
		e.GetErrorMessage(szMsg, 128);

		CString strErr;
		strErr.Format(_T("打开数据库日志文件失败，原因为: %s"), szMsg);
		//MessageBox(NULL, NULL, strErr,MB_ICONERROR|MB_OK);
		return FALSE;
	}


	file.Write(strFileInfo,nLen);
	file.Close();


	delete strFileInfo;
	strFileInfo = NULL;

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL, "select TASK_XMLFILE from %s where OID=%d",strResultTabName,nAttaOid);

	nLen = 0;

	m_DMng.GetTableBolbInfo(szSQL,"TASK_XMLFILE",NULL,nLen);
	strFileInfo = new char[nLen+1];

	memset(strFileInfo,0,nLen+1);
	if(!m_DMng.GetTableBolbInfo(szSQL,"TASK_XMLFILE",strFileInfo,nLen))
	{
		AfxMessageBox(_T("获取失败!"));
		return FALSE;
	}


	strFilePath.Format("%s\\%s\\%s",
		g_WorkPath,PATH_XML_LOADOUT_TASK_CFG,File_Xml_LoadOut_TaskInfo);
	remove(strFilePath);

	if(strcmp("<NULL>",strFileInfo) == 0)
	{
		nLen = 0;
		delete strFileInfo;
		strFileInfo = NULL;
		return TRUE;

	}
	if(!file.Open(strFilePath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite, &e))
	{
		char szMsg[128] = {0};
		e.GetErrorMessage(szMsg, 128);

		CString strErr;
		strErr.Format(_T("打开数据库日志文件失败，原因为: %s"), szMsg);
		//MessageBox(NULL, NULL, strErr,MB_ICONERROR|MB_OK);
		return FALSE;
	}


	file.Write(strFileInfo,nLen);
	file.Close();

	delete strFileInfo;
	strFileInfo = NULL;

	return TRUE;
}

//3.结果数据删除
BOOL  CDataMng::DelBaseData(UINT nGroupOid,UINT nBaseOid)//任务基础表//
{
	CString strResultTabName;
	strResultTabName.Format(_T("%s%.4d"),g_ResultBase,nGroupOid);
	//1.删除任务基础
	char szSQL[256] ={0};
	sprintf(szSQL,_T("delete from %s where OID=%d"),strResultTabName,nBaseOid);
	if(UpdateDataInfo(szSQL))
	{
		//2.删除结果附件
		DelAttaData(nGroupOid,nBaseOid);
	}
	
	return TRUE;
}
BOOL  CDataMng::DelAttaData(UINT nGroupOid,UINT nBaseOid,UINT nAttaOid)//结果附件表//
{
	CString strResultTabName;
	strResultTabName.Format(_T("%s%.4d"),g_ResultAtta,nGroupOid);
	//1.删除结果附件
	char szSQL[256] ={0};
	if(nBaseOid>0)
	{
		sprintf(szSQL,_T("delete from %s where BASE_OID=%d"),strResultTabName,nBaseOid);
	}else
	{
		sprintf(szSQL,_T("delete from %s where OID=%d"),strResultTabName,nAttaOid);
	}
	
	if(UpdateDataInfo(szSQL))
	{
		//2.删除模板数据
		DelModeData(nGroupOid,nBaseOid,nAttaOid);
	}
	
	return TRUE;
}
BOOL  CDataMng::DelModeData(UINT nGroupOid,UINT nBaseOid, UINT nAttaOid)//模板数据表//
{
	//1.删除模板数据
	//遍历模板存储表获取表名，一个一个的筛选//
	vector<StBasModeSave *> ArrayModeSave;
	int i,nCount;
	char szSQL[256];
	if(GetAllModeSave(&ArrayModeSave))
	{
		nCount = ArrayModeSave.size();
		for (i = 0;i<nCount;i++)
		{
			memset(szSQL,0,sizeof(szSQL));
			if(nBaseOid > 0)
			{
				sprintf(szSQL,_T("delete from %s where BASE_OID=%d"),ArrayModeSave.at(i)->szTabName,nBaseOid);
			}else
			{
				sprintf(szSQL,_T("delete from %s where ATTA_OID=%d"),ArrayModeSave.at(i)->szTabName,nAttaOid);
			}

			if(UpdateDataInfo(szSQL))
			{

			}else
			{

			}
		}
	}

	return TRUE;

}

//zt add 导入任务的2中方式
BOOL CDataMng::GetMesProductCount(int &nCnt)
{
	char			szSQL[1024] = {0};
	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	sprintf(szSQL, "select count(*) from %s where (product_no is not null)", TAB_VIEW_MES_INSTITUTE);

	if(!g_pOrcOciDb->ExeSQL(OciSql, szSQL, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}	

	int     nLen = 0;
	CString str;

	while(OciSql->Fetch())
	{
		//1.
		str = OciSql->GetFieldValue(0, nLen);
		nCnt = atoi(str.GetBuffer(0));
		break;
	}

	OciSql->Release();

	return TRUE;
}

BOOL  CDataMng::GetProductCodeFromProductBarCode(char *szProductBarCode, char *szProductCode)
{
	int		nCnt, pos, nLen, splictPos = 0, sumLen;
	int     nArrayLen[10] = {0,};
	int		nPos[10] = {0,};
	CString str;

	str = szProductBarCode;
	pos  = 0;
	nCnt = 0;
	nLen = strlen(str.GetBuffer(0));
	sumLen = 0;
	while (nLen != 0)
	{
		splictPos = str.Find('/');
		if (splictPos != -1)
		{

			nPos[nCnt] = splictPos + sumLen;

			nArrayLen[nCnt] = nLen-splictPos-1;

			sumLen = sumLen + splictPos+1;

			str = str.Right(nLen-splictPos-1);
			nCnt++;
			nLen = strlen(str.GetBuffer(0));
		}
		else
		{
			break;
		}
	}

	if (nCnt == 2)
	{
		memcpy(szProductCode, szProductBarCode+nPos[0]+1, nPos[1]-nPos[0]-1);
	}
	else if (nCnt == 3)
	{
		memcpy(szProductCode, szProductBarCode+nPos[1]+1, nPos[2]-nPos[1]-1);
	}

	return TRUE;
}

BOOL  CDataMng::GetMesProductInfo(int &nCnt, CListCtrl *pList)
{
	char			szSQL[1024] = {0};
	COciSQLCursor	*OciSql;

	OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);

	//sprintf(szSQL, "select t.OID, t.PROJECT_NO, t.PRODUCT_NO, t.PRODUCT_NAME, t.MODEL_NO, t.PHASE, t.DIANSHI_QTY from %s t where (t.PRODUCT_NO is not null)", TAB_VIEW_MES_INSTITUTE);

	sprintf(szSQL, "select t.oid, t.PRODUCT_NO , t2.PRODUCT_BARCODE, t2.PRODUCT_NO as \"图号代号\" , t2.PRODUCT_NAME as \"图号名称\",  t.PROJECT_NO, t.PRODUCT_NAME, t.MODEL_NO, t.PHASE, t.DIANSHI_QTY \
				   from VIEW_CHK_INSTITUTE_TEST t, VIEW_CHK_PRODUCT_LIST t2 	\
				   where (t.PRODUCT_NO is not null) and (t2.PRODUCT_BARCODE is not null) and t.oid = t2.MASTEROID \
				   order by t.PRODUCT_NO, t.OID, t2.PRODUCT_NO, t2.PRODUCT_BARCODE");

	if(!g_pOrcOciDb->ExeSQL(OciSql, szSQL, SQL_SELECT))
	{
		OciSql->Release();
		return FALSE;
	}	

	int     nLen = 0;
	int     nPos = 0;
	int     i, nColPos = 0;
	CString str, str1;
	int     splictPos;
	char    szProductBarCode[100], szProductCode[100];

	pList->DeleteAllItems();
	nPos = 0; 
	while(OciSql->Fetch())
	{
		//序号
		str.Format("%d",nPos+1);
		pList->InsertItem(nPos, str);

		nColPos = 1;
		//1.

		for (i=0; i<10; i++)
		{
			str = OciSql->GetFieldValue(i, nLen);

			if (i == 1)
			{
				pList->SetItemText(nPos, nColPos++, str);

				//产品代号_数据处理
				splictPos = str.Find('/');
				if (splictPos != -1)
				{
					str = str.Left(splictPos);
				}
				pList->SetItemText(nPos, 4, str);
			}
			else if (i == 2)
			{
				pList->SetItemText(nPos, nColPos++, str);

				//产品编号数据处理
				memset(szProductBarCode, 0, 100);
				memset(szProductCode, 0, 100);
				strcpy(szProductBarCode, str.GetBuffer(0));
				GetProductCodeFromProductBarCode(szProductBarCode, szProductCode);

				str = szProductCode;
				pList->SetItemText(nPos, 5, str);

				nColPos = nColPos+2;
			}
			else
			{
				pList->SetItemText(nPos, nColPos++, str);
			}
		}

		nPos++;
	}

	OciSql->Release();

	nCnt = nPos;

	return TRUE;
}