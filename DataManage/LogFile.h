//Í·ÎÄ¼þ LogFile.h

#ifndef _LOGFILE_H
#define _LOGFILE_H

#include <sys/stat.h>
#include <fcntl.h>
#include <io.h>
#include <afxmt.h>

//#define MAX_ROW 5000

class CLogFile
{
public:
	void Disable();
	void Enable();
	CLogFile( char *pDirectory = NULL );
	~CLogFile();
	void WriteLogFile(const char* fmt, ... );
	
	void WriteLogFileLn(const char* fmt, ... );

	void SetLogDirectory( CString strDirectory );

	int  m_MAX_ROW;

protected:
	int NewLogFile(); 
	BOOL IsChangeDay();
	CString GetCurntTime();
	
private:
	int		m_filehandle;
	int		m_row;
	int		m_dirnum;
	int		m_filenum;
	BOOL	m_needlog;
	char	m_sContent[1024*8];//*1024];
	CString m_strContent;
	CString m_sCurtTime;
	CString m_sYestady;
	CString m_sToday;
	CString m_sCurtDir;
	CString m_sLogDir;
	CString m_sLogDayDir;
	CCriticalSection m_cs;
	CString m_log_directory;
};


#endif