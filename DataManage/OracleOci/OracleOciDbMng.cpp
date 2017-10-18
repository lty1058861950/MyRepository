#include "StdAfx.h"
#include "OracleOciDbMng.h"
#include "..\MainFrm.h"

OracleOciDbMng::OracleOciDbMng()
{
	remove(m_WorkPath);
	GetCurrentDirectory(256,m_WorkPath);
	m_InitState = 0;
}

OracleOciDbMng::~OracleOciDbMng()
{
}

CString OracleOciDbMng::GetDateTimeString()
{
	SYSTEMTIME systime;
	CString szTime;
	GetLocalTime(&systime);		
	//szTime.Format("%04d-%02d-%02d ��%d %02d:%02d:%02d:%02d",systime.wYear,systime.wMonth,systime.wDay,systime.wDayOfWeek,
	//	systime.wHour,systime.wMinute,systime.wSecond,systime.wMilliseconds);
	szTime.Format("%04d-%02d-%02d %02d:%02d:%02d",systime.wYear,systime.wMonth,systime.wDay,
		systime.wHour,systime.wMinute,systime.wSecond);
	return szTime;
}
BOOL OracleOciDbMng::ConnectOracle(char *DBSource,char *DBName,char *DBPwd)
{
	if(!InitOci((char*)(LPCTSTR)DBSource,(char*)(LPCTSTR)DBName,(char*)(LPCTSTR)DBPwd))
	{
		return FALSE;
	}

	m_OciOpt.Init(m_OciDatabase, m_OciConn);
	return TRUE;
}
BOOL OracleOciDbMng::ColseOracle()
{
	m_OciOpt.FreeOciSQLCur();
	ReleaseOci();		//�Ͽ����ݿ�����
	m_OciOpt.Init(NULL, NULL);
	m_OciOpt.Release();
	return TRUE;
}
BOOL OracleOciDbMng::InitOci(char *svr_name, char *user_name, char *pwd)
{
	try
	{
		m_OciDatabase = COciDatabase::CreateInstance();
		m_OciDatabase->InitDatabase();

		m_OciConn = m_OciDatabase->CreateConnectionInstance();
		m_OciConn->Connect(svr_name, user_name, pwd);

		m_DBLogEvent = CreateEvent(NULL, FALSE, TRUE, NULL);
	}
	catch (COciException e)
	{
		CString strErr;
		CString strMsg;
		char szErr[256] = {0};
		char szLog[256] = {0};

		sprintf(szLog, "%s\\db.log", m_WorkPath);
		e.ShowExceptionInfo(szErr, szLog, 1);

		strErr.Format(_T("���ݿ��ʼ��ʧ�ܣ�ԭ��Ϊ��\n%s"), szErr);
		strMsg.Format(_T("[%s]\n%s\n"), GetDateTimeString(), strErr);
		WaitForSingleObject(m_DBLogEvent, INFINITE);
		WriteDBLog(DbLog_File, strMsg);
		SetEvent(m_DBLogEvent);
		
		if(m_InitState == 0)
		{
			m_InitText.Add(strMsg);
		}else
		{
			g_MainFram->m_wndOutput.InsertErrorText(strMsg);
		}
		//MessageBox(strErr,NULL, MB_ICONERROR,MB_OK);
		//g_MainFram->m_wndOutput.InsertErrorText(strMsg);
		//MessageBox(NULL, strMsg, NULL,MB_ICONERROR|MB_OK);
		return FALSE;
	}

	return TRUE;
}

BOOL OracleOciDbMng::ReleaseOci()
{
	if(m_OciConn != NULL)
		m_OciConn->DisConnect();

	if(m_OciDatabase != NULL)
		m_OciDatabase->Release();

	if(m_DBLogEvent != INVALID_HANDLE_VALUE)
		CloseHandle(m_DBLogEvent);

	return TRUE;
}
BOOL OracleOciDbMng::ExeSQL(COciSQLCursor *OciSQL, char *szSQL, int nExeType)
{
	//ִ��SQL��������׳��쳣
	try
	{
		switch(nExeType)
		{
		case SQL_SELECT:
			OciSQL->PrepareSQLStatement(szSQL);
			OciSQL->Execute(0);
			OciSQL->ReleaseQueryResult();
			OciSQL->AllocAndGetQueryResult();
			break;
		case SQL_UPDATE:
			OciSQL->PrepareSQLStatement(szSQL);
			OciSQL->Execute(0);
			OciSQL->Commit();
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

		strErr.Format(_T("ִ��SQL��䣺\n%s\n���ִ���ԭ��Ϊ��\n%s"), szSQL, szErr);

		strMsg.Format(_T("[%s]\n%s\n"), GetDateTimeString(), strErr);
		WaitForSingleObject(m_DBLogEvent, INFINITE);
		WriteDBLog(DbLog_File, strMsg);
		SetEvent(m_DBLogEvent);

		MessageBox(NULL, strMsg, NULL,MB_ICONERROR|MB_OK);
		return FALSE;
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//����ORACLE BLOB�ֶ�.
//szUpdateField:�����ֶ�
//data:���ݣ�nSize:����
//////////////////////////////////////////////////////////////////////////

BOOL OracleOciDbMng::SetOracleTabBlob(COciSQLCursor *OciSQL,char* szSql,char * szUpdateField,char* data ,int nSize)
{	
	//SQL�����ѭ:select **Field from **Tab where **guid = ** for update ��ʽ

	try 
	{
		OciSQL->PrepareSQLStatement(szSql);
		OciSQL->Execute(0);

		//�����ڴ�ռ�
		OciSQL->AllocAndGetQueryResult();
		if(OciSQL->Fetch())
		{

			OciSQL->SetBlobData(szUpdateField, data, nSize);
		}	
		//�ύ����
		OciSQL->Commit();
		//�ͷ�
		OciSQL->CloseQuery();

		return TRUE;

	}
	catch (COciException e)
	{
		CString strErr;
		CString strMsg;
		char szErr[256] = {0};
		char szLog[256] = {0};

		//		sprintf(szLog, "%s\\%s", g_strWordPath, DB_ERR_LOG);
		e.ShowExceptionInfo(szErr, szLog, 1);

		strErr.Format(_T("ִ��SQL��䣺\n%s\n���ִ���ԭ��Ϊ��\n%s"), szSql, szErr);

		strMsg.Format(_T("[%s]\n%s\n"), GetDateTimeString(), strErr);
		WaitForSingleObject(m_DBLogEvent, INFINITE);
		WriteDBLog(DbLog_File, strMsg);
		SetEvent(m_DBLogEvent);

		MessageBox(NULL, NULL, strErr,MB_ICONERROR|MB_OK);
		return FALSE;
	}

	return -1 ;	
}

//////////////////////////////////////////////////////////////////////////
//��ȡORACLE BLOB�ֶ�.
//szUpdateField:�����ֶ�
//data:���ݣ�nSize:����
//////////////////////////////////////////////////////////////////////////
BOOL OracleOciDbMng::GetOracleTabBlob(COciSQLCursor *OciSQL,char* szSql,char * szUpdateField,char* data ,int &nSize)
{	
	//SQL�����ѭ:select **Field from **Tab where **guid = ** for update ��ʽ

	try 
	{
		OciSQL->PrepareSQLStatement(szSql);
		OciSQL->Execute(0);

		//�����ڴ�ռ�
		OciSQL->AllocAndGetQueryResult();
		if(OciSQL->Fetch())
		{
			if(data)
			{
				memcpy(data,OciSQL->GetBlobData(szUpdateField,nSize),nSize);
			}else
			{
				OciSQL->GetBlobData(szUpdateField,nSize);
			}

		}	
		//�ύ����
		OciSQL->Commit();
		//�ͷ�
		OciSQL->CloseQuery();

		return TRUE;

	}
	catch (COciException e)
	{
		CString strErr;
		CString strMsg;
		char szErr[256] = {0};
		char szLog[256] = {0};

		//		sprintf(szLog, "%s\\%s", g_strWordPath, DB_ERR_LOG);
		e.ShowExceptionInfo(szErr, szLog, 1);

		strErr.Format(_T("ִ��SQL��䣺\n%s\n���ִ���ԭ��Ϊ��\n%s"), szSql, szErr);

		strMsg.Format(_T("[%s]\n%s\n"), GetDateTimeString(), strErr);
		WaitForSingleObject(m_DBLogEvent, INFINITE);
		WriteDBLog(DbLog_File, strMsg);
		SetEvent(m_DBLogEvent);

		MessageBox(NULL, NULL, strErr,MB_ICONERROR|MB_OK);
		return FALSE;
	}

	return -1 ;	
}

BOOL OracleOciDbMng::WriteDBLog(CString strFileName, CString strMsg)
{
	
	CStdioFile file;
	CFileException e;
	CString strFilePath;
	CString strWrite;

	strFilePath.Format("%s\\%s", m_WorkPath, strFileName);
	if(!file.Open(strFilePath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite, &e))
	{
		char szMsg[128] = {0};
		e.GetErrorMessage(szMsg, 128);

		CString strErr;
		strErr.Format(_T("�����ݿ���־�ļ�ʧ�ܣ�ԭ��Ϊ: %s"), szMsg);
		MessageBox(NULL, NULL, strErr,MB_ICONERROR|MB_OK);
		return FALSE;
	}
	file.SeekToEnd();
	file.WriteString(strMsg);
	file.Close();
	
	return TRUE;
}
