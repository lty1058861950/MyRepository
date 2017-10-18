
//实现代码 LogFile.cpp
#include "stdafx.h"
#include "LogFile.h"
#include <direct.h>

//static char log_directory[]="ivr_log";

CLogFile::CLogFile( char *pDirectory )
{
	m_row = 0;
	m_filehandle = 0;
	m_dirnum = 0;
	m_filenum = 0;
	m_sCurtTime = _T("");
	m_sToday = _T("");
	m_sYestady = _T("");
	m_sCurtDir = _T("");
	m_sLogDir = _T("");
	if (pDirectory == NULL)
	{
		m_log_directory = _T("ivr_log");
	}
	else
	{
		m_log_directory = (CString) pDirectory;
	}

	m_MAX_ROW = 5000;



	m_needlog = FALSE;
	GetCurrentDirectory(_MAX_PATH,m_sCurtDir.GetBuffer(_MAX_PATH));
	m_sCurtDir.ReleaseBuffer();

	CString sDirName;
	CFileFind f;
	BOOL bHasLogDir = FALSE;
	BOOL bFind = f.FindFile(m_sCurtDir + "\\*.*");
	while (bFind)
	{
		bFind = f.FindNextFile();
		if (f.IsDots()) continue;
		if (f.IsDirectory())
		{
			sDirName = f.GetFileName();
			sDirName.MakeLower();
			if (sDirName == (CString)m_log_directory)
			{
				bHasLogDir = TRUE;
				break;
			}
		}
	}

	m_sLogDir = m_sCurtDir + (CString)"\\" + (CString)m_log_directory;
	if (!bHasLogDir)
	{
		_mkdir(m_sLogDir);
	}
	CString strTime = GetCurntTime ();
	m_sToday = strTime.Mid(0,10);
}

CLogFile::~CLogFile()
{
	_close(m_filehandle);
}

int CLogFile::NewLogFile()
{
	CString strLogfileName;
	if (m_filenum > 0)
	{
		_close(m_filehandle);
	}
	strLogfileName = m_sLogDayDir + (CString)"\\" + m_sCurtTime + (CString)".txt";
	if((m_filehandle=_open(strLogfileName,_O_WRONLY| _O_CREAT|O_TRUNC, _S_IREAD | _S_IWRITE)) == -1)
	{
		printf("cannot create log file:%s\n",strLogfileName);
		return -1;
	}
	m_filenum++;
	return 0;
}

BOOL CLogFile::IsChangeDay()
{
	m_sCurtTime = GetCurntTime();
	m_sToday = m_sCurtTime.Mid(0,10);
	if (m_sToday != m_sYestady)
	{
		m_sYestady = m_sToday;
		m_sLogDayDir = m_sLogDir + (CString)"\\" + m_sToday;
		_mkdir(m_sLogDayDir);
		return TRUE;
	}
	return FALSE;
}

void CLogFile::WriteLogFile(const char* fmt, ... )
{
	//return;

	if (m_needlog)
	{
		m_cs.Lock();
		if (m_row >= m_MAX_ROW || IsChangeDay())
		{
			if (NewLogFile() == -1)
			{
				m_cs.Unlock();
				return;
			}
			m_row = 0;
		}
		
		va_list v_args;
		va_start(v_args,fmt);
		vsprintf( m_sContent, fmt, v_args );
		va_end( v_args );
		
		CString strTime;
		CTime cTime = CTime::GetCurrentTime();
		strTime = _T("20") + cTime.Format("%y-%m-%d %H:%M:%S");

		/*
		char sTime[32];
		time_t now = time(NULL);
		tm *tm_time = localtime(&now); //注意，localtime非线程安全
		strftime(sTime,sizeof(sTime),"20%y-%m-%d %H:%M:%S",tm_time);
		*/

		m_strContent = (CString)"[" + strTime + (CString)"]" + (CString)m_sContent + "\n";
		_write(m_filehandle,m_strContent,m_strContent.GetLength());
		m_row++;
		m_cs.Unlock();
	}
}


void CLogFile::WriteLogFileLn(const char* fmt, ... )
{
	//return;

	if (m_needlog)
	{
		m_cs.Lock();
		if (m_row >= m_MAX_ROW || IsChangeDay())
		{
			if (NewLogFile() == -1)
			{
				m_cs.Unlock();
				return;
			}
			m_row = 0;
		}
		
		va_list v_args;
		va_start(v_args,fmt);
		vsprintf( m_sContent, fmt, v_args );
		va_end( v_args );
		
		CString strTime;
		CTime cTime = CTime::GetCurrentTime();
		strTime = _T("20") + cTime.Format("%y-%m-%d %H:%M:%S");

		/*
		char sTime[32];
		time_t now = time(NULL);
		tm *tm_time = localtime(&now); //注意，localtime非线程安全
		strftime(sTime,sizeof(sTime),"20%y-%m-%d %H:%M:%S",tm_time);
		*/

		m_strContent = (CString)"[" + strTime + (CString)"]\n" + (CString)m_sContent + "\n";
		_write(m_filehandle,m_strContent,m_strContent.GetLength());
		m_row++;
		m_cs.Unlock();
	}
}


CString CLogFile::GetCurntTime()
{
	CString strTime;
	CTime cTime = CTime::GetCurrentTime();
	strTime = _T("20") + cTime.Format("%y-%m-%d-%H-%M-%S");
	return strTime;
}

void CLogFile::Enable()
{
	m_needlog = TRUE;
}

void CLogFile::Disable()
{
	m_needlog = FALSE;
}

void CLogFile::SetLogDirectory( CString strDirectory )
{
	m_log_directory = strDirectory;
}