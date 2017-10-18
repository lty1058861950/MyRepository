#pragma once
#include "COciOperation.h"

#define SQL_SELECT 1
#define SQL_UPDATE 2

#define DbLog_File  _T("db.log")

class OracleOciDbMng
{
public:
	OracleOciDbMng();
	~OracleOciDbMng();
public:
public:
	CStringArray    m_InitText;
	int             m_InitState;

	COciDatabase	*m_OciDatabase;
	COciConnection	*m_OciConn;
	COciOperation   m_OciOpt;
	char            m_WorkPath[512];
	HANDLE			m_DBLogEvent;

	BOOL ConnectOracle(char *DBSource,char *DBName,char *DBPwd);
	BOOL InitOci(char *svr_name, char *user_name, char *pwd);
	BOOL ColseOracle();
	BOOL ReleaseOci();
	BOOL ExeSQL(COciSQLCursor *OciSQL, char *szSQL, int nExeType);
	BOOL SetOracleTabBlob(COciSQLCursor *OciSQL,char* szSql,
		char * szUpdateField,char* data ,int nSize);
	BOOL GetOracleTabBlob(COciSQLCursor *OciSQL,char* szSql,
		char * szGetField,char* data ,int &nSize);
	BOOL WriteDBLog(CString strFileName, CString strMsg);
	CString GetDateTimeString();
};
