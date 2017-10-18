#include "stdafx.h"
#include "LoadOutTaskXmlAnalysis.h"
#include "ModeXmlStruct.h"
/*
#ifndef GLOB_QUEUE_DEFINE 
//Ȩ���û��� �ֶ���//
char *g_UsrTab[] = {"OID","LOGIN_NAME","USER_NAME","USER_PWD","ROLE_OID","GROUP_OID",
"USER_SIGNFILE","USER_LOGSTATE","USER_TYPE","CALL","EMAIL","PHONE"};

char *g_DepartTab[] = {"OID","PID","GROUP_NAME","GROUP_NO","GROUP_TYPE",
"DESCRIPTION","CALL","FAXS","ADDRESS"};

char *g_ProdTab[] = {"OID","PRODUCT_NO","PRODUCT_NAME","SERIES_TYPE","PICNUM_TYPE","GROUP_OID","CREATE_TIME","CREATE_USER"};
char *g_SeriesTab[] = {"OID","SERIES_NAME","PRODUCT_OID","PRODUCT_NO","CREATE_TIME","CREATE_USER"};
char *g_PicNumTab[]  = {"OID","PICNUM_NO","PICNUM_NAME","PRODUCT_OID","PRODUCT_NO","CREATE_TIME","CREATE_USER"};
char *g_ModeTab[] = {"OID","MODE_NAME","MODE_VERSION","MODE_TYPE","MODE_ROWVAR",
"MODE_SIZE","MODE_TABNAME","INIT_TABSRT","GROUP_OID","PRODUCT_OID",
"PRODUCT_NO","MODEL","PHASE","CREATE_TIME","CREATE_USER",
"MODE_XMLFILE"};
char *g_TaskTab[] = {"OID","TASK_NAME","PROJECT_NO","TASK_STATUS","TASK_TYPE",
"MODEL","PHASE","PRODUCT_OID","PRODUCT_NAME","PRODUCT_NO",
"SERIES_OID","SERIES_NAME","PRODUCT_CODE","CODE_COUNT","BATCH",
"UP_DEPART","UP_USER","UP_DATE","SEND_DATE","CHECK_LEADER",
"CHECK_USER","TECH_USER","ARMY_TEST","DIANSHI_NUM","ACCORDING1",
"ACCORDING2","ACCORDING3","ACCORDING4","ACCORDING5","TASK_REMARK",
"PLAN_BEGTIME","PLAN_ENDTIME","REAL_BEGTIME","REAL_ENDTIME"};

char *g_TstResultTab[] = {"OID","TASK_OID","MODE_OID","PRODUCT_OID","SERIES_OID",
"PRODUCT_NAME","PRODUCT_NO","SERIES_NAME","MODEL","PHASE",
"PRODUCT_CODE","MODE_NAME","MODE_TYPE","MODE_ROWVAR","PICNUM_COUNT",
"DIANSHI_TEST","PERCENT","FINISHED","FINISHED_TIME","CHECK_USER"};


int g_HrRoleLen = 3;
int g_UsrLen = 12;
int g_DepartLen = 9;
int g_ProdLen = 8;
int g_SeriesLen = 6;
int g_PicNumLen = 7;
int g_ModeLen = 15;
int g_ModeSaveLen = 5;
int g_TaskLen = 34;
int g_TaskCodeLen = 5;
int g_TaskModeLen = 7;
int g_TaskPicNumLen = 6;

int g_TstResultLen = 20;


char g_ModeRowVal[2][20] = {"���ɱ�","�пɱ�"};
char g_ModeType[4][20] = {"ͨ��ģ��","��Ʒר��","����ר��","δ����"};

char g_TaskState[7][10] = {"��ʼ","ȷ��","ִ����","�����","����ֹ"};
char g_TaskType[3][10] = { "����","����","��Э����"};
#define GLOB_QUEUE_DEFINE
#endif
*/
static void GetSysDateString(char *cDate)
{
	CTime	t = CTime::GetCurrentTime();
	int		year	= t.GetYear();
	int		month	= t.GetMonth();
	int		day		= t.GetDay();
	CString strTime;

	strTime.Format("%04d-%02d-%02d",year,month,day);
	strcpy(cDate, strTime.GetBuffer(0));
	return;
}

static void GetSysTimeString(char *cTime)
{
	CTime	t = CTime::GetCurrentTime();
	int		hour	= t.GetHour();
	int		minute	= t.GetMinute();
	int		second	= t.GetSecond();
	CString strTime;

	strTime.Format("%02d:%02d:%02d",hour,minute,second);
	strcpy(cTime, strTime.GetBuffer(0));
	return;
}

static void SetXmlRootInfoLoad(TiXmlElement *pRootInfo)
{	
	char Date[24] = {0}; 
	char Time[24] = {0};
	GetSysDateString(Date);
	GetSysTimeString(Time);
	pRootInfo->SetAttribute("Version", DECL_LOAD_VERSION);
	pRootInfo->SetAttribute("Date", Date);
	pRootInfo->SetAttribute("Time", Time);
}
LoadOutTaskXmlAnalysis::LoadOutTaskXmlAnalysis(void)
{
	m_CurTaskInfo.Release();
	m_szDbPath.Format(_T("%s\\%s"),g_WorkPath,Sqlite_TaskDbFile_Path);
}

LoadOutTaskXmlAnalysis::~LoadOutTaskXmlAnalysis(void)
{
	
	ClearAllData();

}

void LoadOutTaskXmlAnalysis::ClearAllData()
{
	m_CurTaskInfo.Release();

	int i,nSize = 0;
	nSize = m_ArrayUsrInfo.size();
	for (i = 0;i<nSize;i++)
	{
		delete m_ArrayUsrInfo.at(i);
	}
	m_ArrayUsrInfo.clear();

	nSize = m_ArrayModeInfo.size();
	for (i = 0;i<nSize;i++)
	{
		m_ArrayModeInfo.at(i)->Release();
		delete m_ArrayModeInfo.at(i);
	}
	m_ArrayModeInfo.clear();

	nSize = m_ArrayTaskNumbelMode.size();
	for (i = 0;i<nSize;i++)
	{
		delete m_ArrayTaskNumbelMode.at(i);
	}
	m_ArrayTaskNumbelMode.clear();
}
int LoadOutTaskXmlAnalysis::GetCurModeXmlFileName(char *pFileName, char *pPathName)
{
	CString		str, strPath;

	strPath = PATH_XML_LOADOUT_TASK_CFG;

	//	
	str.Format("%s\\%s\\%s", 
		g_WorkPath, 
		strPath,
		pFileName);

	strcpy(pPathName, str.GetBuffer(0));

	return 1;
}

int LoadOutTaskXmlAnalysis::WriteFileToLocal(char *pFilePath,char*FileData,int nLen)
{
	CStdioFile file;
	CFileException e;
	if(!file.Open(pFilePath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite, &e))
	{
		char szMsg[128] = {0};
		e.GetErrorMessage(szMsg, 128);

		CString strErr;
		strErr.Format(_T("�� %s �ļ�ʧ�ܣ�ԭ��Ϊ: %s"),pFilePath, szMsg);
		MessageBox(NULL,strErr, "��ʾ",MB_ICONERROR|MB_OK);
		return 0;
	}
	file.Write(FileData,nLen);
	file.Close();
	return 1;
}
int LoadOutTaskXmlAnalysis::ReadFileFromLocal(char *pFilePath,char **FileData,int &nLen)
{
	CStdioFile file;
	CFileException e;
	if(!file.Open(pFilePath, CFile::modeNoTruncate | CFile::modeRead, &e))
	{
		char szMsg[128] = {0};
		e.GetErrorMessage(szMsg, 128);

		CString strErr;
		strErr.Format(_T("�����ݿ���־�ļ�ʧ�ܣ�ԭ��Ϊ: %s"), szMsg);
		AfxMessageBox(strErr);
		return 0;
	}
	nLen = file.GetLength();
	*FileData = new char[nLen+1];
	memset(*FileData,0,nLen+1);

	file.Read(*FileData,nLen);
	file.Close();

	return 1;
}
int LoadOutTaskXmlAnalysis::DelSrtHisDataFile()
{
	CString strPath;
	strPath.Format( _T("%s//%s//%s"),
		g_WorkPath, 
		PATH_XML_MODE_PAR_CFG, 
		MD_XML_FILE_TAB_OUT_INFO);

	remove(strPath);

	strPath.Format( _T("%s//%s//%s"),
		g_WorkPath, 
		PATH_XML_MODE_PAR_CFG, 
		MD_XML_FILE_TAB_SRT_INFO);

	remove(strPath);
	strPath.Format( _T("%s//%s//%s"),
		g_WorkPath, 
		PATH_XML_MODE_PAR_CFG, 
		MD_XML_FILE_TAB_HIS_INFO);

	remove(strPath);
	return 1;
}
int LoadOutTaskXmlAnalysis::SetXmlLoadOutUsrInfo(StHrUser *pUsrInfo)
{
	char      szFileName[512] = {0,};

	GetCurModeXmlFileName(File_Xml_LoadOut_UsrInfo, szFileName);
	remove(szFileName);

	//int i,j;
	//����XML�ļ�ͷ----------------------------------------------------------------------------
	TiXmlDocument	doc;
	TiXmlDeclaration* pDec = new TiXmlDeclaration(DECL_LOAD_VERSION, DECL_LOAD_ENCODING, DECL_LOAD_STANDALONE);
	doc.LinkEndChild(pDec);
	TiXmlElement* pRootInfo = new TiXmlElement("RootInfo");
	doc.LinkEndChild(pRootInfo);	
	SetXmlRootInfoLoad(pRootInfo);
	//-----------------------------------------------------------------------------------------
	TiXmlElement	*pTabSrtRoot, *pTempRoot; 
	TiXmlElement    *pTempElem1;
	
	//����ģ��ṹ��Ϣ Set
	pTabSrtRoot = new TiXmlElement("TaskLoadOutUsrInfo");
	pRootInfo->LinkEndChild(pTabSrtRoot);

	//1.1_TabItemData
	pTempRoot = new TiXmlElement("UsrTabItemData");
	

	

	int pos;
	char szUserFields[15][20] = {
		_T("OID"), _T("LOGIN_NAME"), _T("USER_NAME"), _T("USER_PWD"), _T("ROLE_OID"),
		_T("GROUP_OID"), _T("GROUP_NAME"), _T("USER_SIGNFILE"), _T("USER_LOGSTATE"), _T("USER_TYPE"),
		_T("CALL"), _T("EMAIL"), _T("PHONE"), _T("PADDEV_ID")};
	pTempElem1 = new TiXmlElement("ItemRoot1");

	pos = 0;
	pTempElem1->SetAttribute(szUserFields[pos++], pUsrInfo->nOid);
	pTempElem1->SetAttribute(szUserFields[pos++], pUsrInfo->szLoginName);
	pTempElem1->SetAttribute(szUserFields[pos++], pUsrInfo->szUserName);
	pTempElem1->SetAttribute(szUserFields[pos++], pUsrInfo->szUserPwd);
	pTempElem1->SetAttribute(szUserFields[pos++], pUsrInfo->nRoleOid);

	pTempElem1->SetAttribute(szUserFields[pos++], pUsrInfo->nGroupOid);
	pTempElem1->SetAttribute(szUserFields[pos++], pUsrInfo->szGroupName);
	pTempElem1->SetAttribute(szUserFields[pos++], pUsrInfo->szUserSignfile);
	pTempElem1->SetAttribute(szUserFields[pos++], pUsrInfo->nUserLogstate);
	pTempElem1->SetAttribute(szUserFields[pos++], pUsrInfo->nUserType);

	pTempElem1->SetAttribute(szUserFields[pos++], pUsrInfo->szCall);
	pTempElem1->SetAttribute(szUserFields[pos++], pUsrInfo->szEmail);
	pTempElem1->SetAttribute(szUserFields[pos++], pUsrInfo->szPhone);
	pTempElem1->SetAttribute(szUserFields[pos++], pUsrInfo->nPadDevID);

	pTempRoot->SetAttribute("TabRowCnt", 1);
	pTempRoot->SetAttribute("TabColCnt", pos);
	pTabSrtRoot->LinkEndChild(pTempRoot);

	pTempRoot->LinkEndChild(pTempElem1);
	
	doc.SaveFile(szFileName);
	return 1;
}
int LoadOutTaskXmlAnalysis::GetXmlLoadOutUsrInfo(StHrUser *pUsrInfo)
{
	char      szFileName[MAX_PATH] = {0,};

	GetCurModeXmlFileName(File_Xml_LoadOut_UsrInfo, szFileName);

	//------------------------------------------------------------------------------
	TiXmlDocument   doc( szFileName );
	TiXmlElement	* pRootInfo;
	if (!doc.LoadFile())
	{
		return 0;
	}
	pRootInfo = doc.RootElement();
	TiXmlElement	*pRoot, *pRootType, *pRoot1;
	int				Layer1, Layer2, Layer3;
	CString			strTemp, str;
	int             nRowNum = 0;
	int             nColNum = 0;
	int             nRowPos=0, nColPos=0;
	int             nCount=0;



	Layer1 = 0;
	Layer2 = 0;
	Layer3 = 0;

	if (pRootInfo)
	{
		//  ----------------------------------------------------------------------
		pRoot= pRootInfo->FirstChildElement("TaskLoadOutUsrInfo");
		if (pRoot)
		{
			//2.1 �������
			pRootType = pRoot->FirstChildElement("UsrTabItemData");

			if (pRootType)
			{
				//1.
				strTemp = pRootType->Attribute("TabColCnt");
				nCount = atoi(strTemp.GetBuffer(0));

				//��һ��
				pRoot1 = pRootType->FirstChildElement("ItemRoot1");		
				if (pRoot1)
				{
					int pos;
					char szUserFields[15][20] = {
						_T("OID"), _T("LOGIN_NAME"), _T("USER_NAME"), _T("USER_PWD"), _T("ROLE_OID"),
						_T("GROUP_OID"), _T("GROUP_NAME"), _T("USER_SIGNFILE"), _T("USER_LOGSTATE"), _T("USER_TYPE"),
						_T("CALL"), _T("EMAIL"), _T("PHONE"), _T("PADDEV_ID")};

					pos = 0;
					pUsrInfo->nOid = atoi(pRoot1->Attribute(szUserFields[pos++]));
					strcpy(pUsrInfo->szLoginName, pRoot1->Attribute(szUserFields[pos++]));
					strcpy(pUsrInfo->szUserName, pRoot1->Attribute(szUserFields[pos++]));
					strcpy(pUsrInfo->szUserPwd, pRoot1->Attribute(szUserFields[pos++]));
					pUsrInfo->nRoleOid = atoi(pRoot1->Attribute(szUserFields[pos++]));

					pUsrInfo->nGroupOid = atoi(pRoot1->Attribute(szUserFields[pos++]));
					strcpy(pUsrInfo->szGroupName, pRoot1->Attribute(szUserFields[pos++]));
					strcpy(pUsrInfo->szUserSignfile, pRoot1->Attribute(szUserFields[pos++]));
					pUsrInfo->nUserLogstate = atoi(pRoot1->Attribute(szUserFields[pos++]));
					pUsrInfo->nUserType = atoi(pRoot1->Attribute(szUserFields[pos++]));

					strcpy(pUsrInfo->szCall, pRoot1->Attribute(szUserFields[pos++]));
					strcpy(pUsrInfo->szEmail, pRoot1->Attribute(szUserFields[pos++]));
					strcpy(pUsrInfo->szPhone, pRoot1->Attribute(szUserFields[pos++]));
					pUsrInfo->nPadDevID = atoi(pRoot1->Attribute(szUserFields[pos++]));
				}
			}
		}

	}//if pRootInfo
	return 1;
}
int LoadOutTaskXmlAnalysis::GetAllUsrInfo()
{

	/////
	//��ȡ���ݿ��� ģ��Ļ�����Ϣ  ȫ��������////

	char *szSQL = "select USER_XMLFILE from HR_USER";
	/*ReadBlobStr ArrayData[10];*/

	vector <void *> ArrayData;
	char nFilePath[256] = {0};

	
	int nCount = 0;
	m_SqliteDb.open(m_szDbPath.GetBuffer(0));
	m_SqliteDb.SqliteReadBolb(szSQL,ArrayData,nCount);

	m_SqliteDb.close();

	for (int i = 0 ;i<nCount;i++ )
	{
		StHrUser *pUsrInfo = new StHrUser;
		memset(pUsrInfo,0,sizeof(StHrUser));

		ReadBlobStr * pData = (ReadBlobStr*)ArrayData[i];
		//AfxMessageBox(pData->nData);
		//�����ݴ洢������,///
		
		GetCurModeXmlFileName(File_Xml_LoadOut_UsrInfo,nFilePath);
		remove(nFilePath);

		WriteFileToLocal(nFilePath,pData->nData,pData->nLen);
		GetXmlLoadOutUsrInfo(pUsrInfo);
		m_ArrayUsrInfo.push_back(pUsrInfo);

		delete []pData->nData;
		pData->nData = NULL;
		delete pData;
		pData = NULL;
	}
	ArrayData.clear();
	return 1;
}
int LoadOutTaskXmlAnalysis::GetCurLogUsrInfo(char *UsrLogName,char *UsrPwd)
{

	int i,nSize = m_ArrayUsrInfo.size();

	//��ʼѰ�ҵ�ǰ��¼���û���ID������֤�û������ƺ������Ƿ���ȷ///
	for (i = 0;i<nSize;i++)
	{
		if(strcmp(m_ArrayUsrInfo.at(i)->szLoginName, UsrLogName) == 0)
		{
			//�ж��û������Ƿ���ȷ//
			if(strcmp(m_ArrayUsrInfo.at(i)->szUserPwd, UsrPwd) != 0)
			{
				AfxMessageBox("���벻��ȷ!");
				return 0;
			}
			memcpy(&m_CurLogUsrInfo,m_ArrayUsrInfo.at(i),sizeof(StHrUser));
			//����ǰ��¼���û���Ϣ ���Ƶ� m_CurUsrInfo//
			break;
		}
	}

	if(i>=nSize)
	{
		CString strErr;
		strErr.Format("û�д��û� \"%s\" ",UsrLogName);
		AfxMessageBox(strErr);
		return 0;
	}
	return 1;
}
int LoadOutTaskXmlAnalysis::SetXmlLoadOutModeInfo(StBasMode *pModeInfo)
{
	char      szFileName[512] = {0,};

	GetCurModeXmlFileName(File_Xml_LoadOut_ModeInfo, szFileName);
	remove(szFileName);
	
	//int i,j;
	//����XML�ļ�ͷ----------------------------------------------------------------------------
	TiXmlDocument	doc;
	TiXmlDeclaration* pDec = new TiXmlDeclaration(DECL_LOAD_VERSION, DECL_LOAD_ENCODING, DECL_LOAD_STANDALONE);
	doc.LinkEndChild(pDec);
	TiXmlElement* pRootInfo = new TiXmlElement("RootInfo");
	doc.LinkEndChild(pRootInfo);	
	SetXmlRootInfoLoad(pRootInfo);
	//-----------------------------------------------------------------------------------------
	TiXmlElement	*pTabSrtRoot, *pTempRoot; 
	TiXmlElement    *pTempElem1;

	//����ģ��ṹ��Ϣ Set
	pTabSrtRoot = new TiXmlElement("TaskLoadOutModeInfo");
	pRootInfo->LinkEndChild(pTabSrtRoot);

	//1.1_TabItemData
	pTempRoot = new TiXmlElement("ModeTabItemData");
	
	pTempElem1 = new TiXmlElement("ItemRoot1");
	
	int pos;
	char szModeFields[20][20] = {
		_T("OID"), _T("MODE_NAME"), _T("MODE_VERSION"), _T("MODE_TYPE"), _T("MODE_ROWVAR"),
		_T("MODE_SIZE"), _T("MODE_TABNAME"), _T("INIT_TABSRT"), _T("GROUP_OID"), _T("GROUP_NAME"),
		_T("PRODUCT_OID"),_T("PRODUCT_NO"), _T("PRODUCT_NAME"), _T("MODEL"), _T("PHASE"),
		_T("CREATE_TIME"),_T("CREATE_USER"), _T("FORMULA")};

	pos = 0;
	pTempElem1->SetAttribute(szModeFields[pos++], pModeInfo->nOid);//1.ģ��OID
	pTempElem1->SetAttribute(szModeFields[pos++], pModeInfo->szModeName);//2.ģ������
	pTempElem1->SetAttribute(szModeFields[pos++], pModeInfo->szModeVersion);//3.ģ��汾
	pTempElem1->SetAttribute(szModeFields[pos++], pModeInfo->nModeType);//4.ģ������:0.��Ʒͨ��,1.��Ʒר��,2.����ר��,3.δ����
	pTempElem1->SetAttribute(szModeFields[pos++], pModeInfo->nModeRowVar);//5.ģ���пɱ�״̬��0.���ɱ� 1.�пɱ�

	pTempElem1->SetAttribute(szModeFields[pos++], pModeInfo->nModeSize);//6.ģ���С
	pTempElem1->SetAttribute(szModeFields[pos++], pModeInfo->szModeTabName);//7.ģ�����ݱ����
	pTempElem1->SetAttribute(szModeFields[pos++], pModeInfo->nInitTabSrt);//8.�Ƿ������ݱ�ṹ��0.δ���� 1.�ѽ���
	pTempElem1->SetAttribute(szModeFields[pos++], pModeInfo->nGroupOid);//9.���ڲ���OID
	pTempElem1->SetAttribute(szModeFields[pos++], pModeInfo->szGroupName);

	pTempElem1->SetAttribute(szModeFields[pos++], pModeInfo->stProductInfo.nOid);//10.���ò�ƷOID
	pTempElem1->SetAttribute(szModeFields[pos++], pModeInfo->stProductInfo.szProductNo);
	pTempElem1->SetAttribute(szModeFields[pos++], pModeInfo->stProductInfo.szProductName);
	pTempElem1->SetAttribute(szModeFields[pos++], pModeInfo->szModel);//11.�����ͺ�
	pTempElem1->SetAttribute(szModeFields[pos++], pModeInfo->szPhase);//12.���ý׶�

	pTempElem1->SetAttribute(szModeFields[pos++], pModeInfo->szCreateTime);//13.ģ�崴��ʱ��
	pTempElem1->SetAttribute(szModeFields[pos++], pModeInfo->szCreateUser);//14.ģ�崴���û�
	pTempElem1->SetAttribute(szModeFields[pos++], pModeInfo->nFormula);//15.��ʽģ��
	

	pTempRoot->SetAttribute("TabRowCnt", 1);
	pTempRoot->SetAttribute("TabColCnt", pos);
	pTabSrtRoot->LinkEndChild(pTempRoot);
	pTempRoot->LinkEndChild(pTempElem1);
	doc.SaveFile(szFileName);
	return 1;
}
int LoadOutTaskXmlAnalysis::GetXmlLoadOutModeInfo(StBasMode *pModeInfo)
{
	char      szFileName[MAX_PATH] = {0,};

	GetCurModeXmlFileName(File_Xml_LoadOut_ModeInfo, szFileName);

	//------------------------------------------------------------------------------
	TiXmlDocument   doc( szFileName );
	TiXmlElement	* pRootInfo;
	if (!doc.LoadFile())
	{
		return 0;
	}
	pRootInfo = doc.RootElement();
	TiXmlElement	*pRoot, *pRootType, *pRoot1;
	int				Layer1, Layer2, Layer3;
	CString			strTemp, str;
	int             nRowNum = 0;
	int             nColNum = 0;
	int             nRowPos=0, nColPos=0;
	int             nCount=0;



	Layer1 = 0;
	Layer2 = 0;
	Layer3 = 0;

	if (pRootInfo)
	{
		//  ----------------------------------------------------------------------
		pRoot= pRootInfo->FirstChildElement("TaskLoadOutModeInfo");
		if (pRoot)
		{
			//2.1 �������
			pRootType = pRoot->FirstChildElement("ModeTabItemData");

			if (pRootType)
			{
				//1.
				strTemp = pRootType->Attribute("TabColCnt");
				nCount = atoi(strTemp.GetBuffer(0));

				//��һ��
				pRoot1 = pRootType->FirstChildElement("ItemRoot1");		
				if (pRoot1)
				{
					int pos;
					char szModeFields[20][20] = {
						_T("OID"), _T("MODE_NAME"), _T("MODE_VERSION"), _T("MODE_TYPE"), _T("MODE_ROWVAR"),
						_T("MODE_SIZE"), _T("MODE_TABNAME"), _T("INIT_TABSRT"), _T("GROUP_OID"), _T("GROUP_NAME"),
						_T("PRODUCT_OID"),_T("PRODUCT_NO"), _T("PRODUCT_NAME"), _T("MODEL"), _T("PHASE"),
						_T("CREATE_TIME"),_T("CREATE_USER"),_T("FORMULA")};

					pos = 0;
					pModeInfo->nOid = atoi(pRoot1->Attribute(szModeFields[pos++]));//1.ģ��OID
					strcpy(pModeInfo->szModeName, pRoot1->Attribute(szModeFields[pos++]));//2.ģ������
					strcpy(pModeInfo->szModeVersion, pRoot1->Attribute(szModeFields[pos++]));//3.ģ��汾
					pModeInfo->nModeType = atoi(pRoot1->Attribute(szModeFields[pos++]));//4.ģ������:0.��Ʒͨ��,1.��Ʒר��,2.����ר��,3.δ����
					pModeInfo->nModeRowVar = atoi(pRoot1->Attribute(szModeFields[pos++]));//5.ģ���пɱ�״̬��0.���ɱ� 1.�пɱ�

					pModeInfo->nModeSize = atoi(pRoot1->Attribute(szModeFields[pos++]));//6.ģ���С
					strcpy(pModeInfo->szModeTabName, pRoot1->Attribute(szModeFields[pos++]));//7.ģ�����ݱ����
					pModeInfo->nInitTabSrt = atoi(pRoot1->Attribute(szModeFields[pos++]));//8.�Ƿ������ݱ�ṹ��0.δ���� 1.�ѽ���
					pModeInfo->nGroupOid = atoi(pRoot1->Attribute(szModeFields[pos++]));//9.���ڲ���OID
					strcpy(pModeInfo->szGroupName, pRoot1->Attribute(szModeFields[pos++]));

					pModeInfo->stProductInfo.nOid = atoi(pRoot1->Attribute(szModeFields[pos++]));//10.���ò�ƷOID
					strcpy(pModeInfo->stProductInfo.szProductNo, pRoot1->Attribute(szModeFields[pos++]));
					strcpy(pModeInfo->stProductInfo.szProductName, pRoot1->Attribute(szModeFields[pos++]));
					strcpy(pModeInfo->szModel, pRoot1->Attribute(szModeFields[pos++]));//11.�����ͺ�
					strcpy(pModeInfo->szPhase, pRoot1->Attribute(szModeFields[pos++]));//12.���ý׶�

					strcpy(pModeInfo->szCreateTime, pRoot1->Attribute(szModeFields[pos++]));//13.ģ�崴��ʱ��
					strcpy(pModeInfo->szCreateUser, pRoot1->Attribute(szModeFields[pos++]));//14.ģ�崴���û�
					pModeInfo->nFormula = atoi(pRoot1->Attribute(szModeFields[pos++]));//15.��ʽģ��


				}
			}
		}

	}//if pRootInfo
	return 1;
}
int LoadOutTaskXmlAnalysis::GetAllModeInfo()
{
	//��ȡ���ݿ��� ģ��Ļ�����Ϣ  ȫ��������////

	char *szSQL = "select MODE_INFOFILE from BAS_MODE";
	/*ReadBlobStr ArrayData[10];*/

	vector <void *> ArrayData;
	char nFilePath[256] = {0};
	
	
	int nCount = 0;
	m_SqliteDb.open(m_szDbPath.GetBuffer(0));
	m_SqliteDb.SqliteReadBolb(szSQL,ArrayData,nCount);

	m_SqliteDb.close();

	if(nCount<=0)
	{
		AfxMessageBox(_T("û���κ�ģ����Ϣ"));
		return 0;
	}

	for (int i = 0 ;i<nCount;i++ )
	{
		ReadBlobStr * pData = (ReadBlobStr*)ArrayData[i];
		StBasMode *pModeInfo = new StBasMode;
		memset( pModeInfo,0,sizeof(StBasMode));
		//AfxMessageBox(pData->nData);
		//�����ݴ洢������,///
		
		GetCurModeXmlFileName(File_Xml_LoadOut_ModeInfo,nFilePath);
		remove(nFilePath);

		WriteFileToLocal(nFilePath,pData->nData,pData->nLen);
		GetXmlLoadOutModeInfo(pModeInfo);
		m_ArrayModeInfo.push_back(pModeInfo);

		delete []pData->nData;
		pData->nData = NULL;
		delete pData;
		pData = NULL;
	}
	ArrayData.clear();
	return 1;

}
int LoadOutTaskXmlAnalysis::GetModeInfoAndXmlFile(UINT nModeOid, char *szModeName)
{
	int i,nSize  = m_ArrayModeInfo.size();
	DelSrtHisDataFile();
	//��ʼѰ��ģ���ID///
	for (i = 0;i<nSize;i++)
	{
		if(m_ArrayModeInfo.at(i)->nOid == nModeOid)
		{
			//����ǰģ����Ϣ ���Ƶ� m_CurModeInfo//
			memcpy(&m_CurModeInfo,m_ArrayModeInfo.at(i),sizeof(StBasMode));
			break;
		}
	}

	if(i>=nSize)
	{
		CString strErr;
		strErr.Format("���ݿ���û���ҵ� \"%s\" ģ��",szModeName);
		AfxMessageBox(strErr);
		return 0;
	}

	//������д�� ָ��·����//�����������ļ� 1.ģ�������ļ� 2.ģ�������ļ�
	
	char szSQL[256] = {0};
	sprintf(szSQL,"select MODE_XMLFILE from BAS_MODE where OID=%d",m_CurModeInfo.nOid);

	vector <void *> ArrayData;
	int nCount = 0;
	m_SqliteDb.open(m_szDbPath.GetBuffer(0));
	m_SqliteDb.SqliteReadBolb(szSQL,ArrayData,nCount);//�������ļ�������//

	m_SqliteDb.close();

	for (int i = 0 ;i<nCount;i++ )
	{
		ReadBlobStr * pData = (ReadBlobStr*)ArrayData[i];
		
		//�����ݴ洢������,///
		if(i==0)
		{
			CString strPath;
			strPath.Format( _T("%s//%s//%s"),
				g_WorkPath, 
				PATH_XML_MODE_PAR_CFG, 
				MD_XML_FILE_TAB_SRT_INFO);

			WriteFileToLocal(strPath.GetBuffer(0), pData->nData, pData->nLen);
		}
		delete []pData->nData;
		pData->nData = NULL;
		delete pData;
		pData = NULL;
	}
	ArrayData.clear();

	//��ȡ��ʷ��ֵ�ļ�///

	/*char *Data = NULL;
	int nLen = 0;

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,"select HIS_XMLFILE from DATA_HIS_MNG where %s='%s'",g_ModeTab[0],nModeID);
	m_SqliteDb.open(Sqlite_TaskDbFile_Path);
	m_SqliteDb.SqliteReadBolb(szSQL,&Data,nLen);//�������ļ�������//
	m_SqliteDb.close();

	if(Data||nLen)
	{
		CString strPath;
		strPath.Format( _T("%s//%s//%s"),
			g_WorkPath, 
			PATH_XML_MODE_PAR_CFG, 
			MD_XML_FILE_TAB_HIS_INFO);

		WriteFileToLocal(strPath.GetBuffer(0), Data, nLen);
	}*/

	GetTestDataFromDb();//�������ļ�������//
	
	
	return 1;
}
int LoadOutTaskXmlAnalysis::SetXmlLoadOutTaskInfo(StBasTask *pTaskInfo)
{
	char      szFileName[512] = {0,};

	GetCurModeXmlFileName(File_Xml_LoadOut_TaskInfo, szFileName);
	remove(szFileName);

	//int i,j;
	//����XML�ļ�ͷ----------------------------------------------------------------------------
	TiXmlDocument	doc;
	TiXmlDeclaration* pDec = new TiXmlDeclaration(DECL_LOAD_VERSION, DECL_LOAD_ENCODING, DECL_LOAD_STANDALONE);
	doc.LinkEndChild(pDec);
	TiXmlElement* pRootInfo = new TiXmlElement("RootInfo");
	doc.LinkEndChild(pRootInfo);	
	SetXmlRootInfoLoad(pRootInfo);
	//-----------------------------------------------------------------------------------------
	TiXmlElement	*pTabSrtRoot, *pTempRoot1,*pTempRoot2,*pTempRoot3; 
	TiXmlElement    *pTempElem1,*pTempElem2,*pTempElem3;

	StBasTaskBaseInfo *pTaskBaseInfo = &pTaskInfo->stTaskBaseInfo;
	StBasProduct      *pProductInfo = &pTaskInfo->stProductInfo;
	StHrUpDepart      *pUpDepartInfo = &pTaskInfo->stHrUpDepart;

	//����ģ��ṹ��Ϣ Set
	pTabSrtRoot = new TiXmlElement("TaskLoadOutTaskInfo");
	pRootInfo->LinkEndChild(pTabSrtRoot);

	//1.�������ϸ��Ϣ
	pTempRoot1 = new TiXmlElement("TaskTabItemData");
	

	char szTaskFields[40][20] = {
		_T("OID"), _T("TASK_NAME"), _T("PROJECT_NO"), _T("TASK_STATUS"), _T("TASK_TYPE"),
		_T("MODEL"), _T("PHASE"), _T("PRODUCT_OID"), _T("PRODUCT_NO"), _T("PRODUCT_NAME"),
		_T("PRODUCT_CODE"), _T("CODE_COUNT"), _T("BATCH"), _T("DEPART_OID"), _T("DEPART_NAME"), 
		_T("UP_USER"), _T("UP_DATE"), _T("SEND_DATE"), _T("CHECK_LEADER"), _T("CHECK_USER"),
		_T("TECH_USER"), _T("ARMY_TEST"), _T("DIANSHI_NUM"), _T("ACCORDING1"), _T("ACCORDING2"),
		_T("ACCORDING3"), _T("ACCORDING4"), _T("ACCORDING5"), _T("TASK_REMARK"), _T("PLAN_BEGTIME"),
		_T("PLAN_ENDTIME"),_T("REAL_BEGTIME"),_T("REAL_ENDTIME"),_T("DOWNLOAD_DATE"),_T("FINISH_DATE"),
		_T("CREATE_TIME"),_T("CREATE_USER"),_T("GROUP_OID"),_T("GROUP_NAME")};
	int pos = 0;
	pTempElem1 = new TiXmlElement("ItemRoot1");
	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->nOid);
	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->szTaskName);
	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->szProjectNo);
	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->nTaskStatus);
	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->nTaskType);

	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->szModel);
	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->szPhase);
	pTempElem1->SetAttribute(szTaskFields[pos++], pProductInfo->nOid);
	pTempElem1->SetAttribute(szTaskFields[pos++], pProductInfo->szProductNo);
	pTempElem1->SetAttribute(szTaskFields[pos++], pProductInfo->szProductName);

	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->szProductCode);
	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->nCodeNumber);
	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->szBatch);
	pTempElem1->SetAttribute(szTaskFields[pos++], pUpDepartInfo->nOid);//���첿��//
	pTempElem1->SetAttribute(szTaskFields[pos++], pUpDepartInfo->szUpDepartName);

	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->szUpUser);
	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->szUpDate);
	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->szSendDate);
	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->szCheckLeader);
	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->szCheckUser);

	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->szTechUser);
	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->nArmyTest);
	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->nDianShiNum);
	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->szAccording1);
	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->szAccording2);

	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->szAccording3);
	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->szAccording4);
	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->szAccording5);
	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->szTaskRemark);
	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->szPlanBegTime);

	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->szPlanEndTime);
	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->szRealBegTime);
	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->szRealEndTime);
	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->szDownLoadDate);
	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->szFinishDate);

	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->szCreateDate);
	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->szCreateUser);
	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->nGroupOid);//��������//
	pTempElem1->SetAttribute(szTaskFields[pos++], pTaskBaseInfo->szGroupName);


	pTempRoot1->SetAttribute("TabRowCnt", 1);
	pTempRoot1->SetAttribute("TabColCnt", pos);
	pTabSrtRoot->LinkEndChild(pTempRoot1);

	pTempRoot1->LinkEndChild(pTempElem1);

	//�����Ʒ��ű�//
	vector<StBasTaskCode *> *pArryTaskCode = &pTaskInfo->pArryTaskCode;
	int i,nCodeCount = pArryTaskCode->size();
	CString strText;
	pTempRoot2 = new TiXmlElement("TaskCodeInfo");
	pTempRoot2->SetAttribute("TabRowCnt", nCodeCount);
	pTempRoot2->SetAttribute("TabColCnt", 5);
	pTabSrtRoot->LinkEndChild(pTempRoot2);

	StBasTaskCode* pTaskCode = NULL;
	for(i = 0; i<nCodeCount;i++)
	{
		pTaskCode = NULL;
		pTaskCode = pArryTaskCode->at(i);
		if(pTaskCode == NULL)
		{
			continue;
		}
		strText.Format(_T("ItemRoot%d"),i+1);
		pTempElem2 = new TiXmlElement(strText);

		pTempElem2->SetAttribute(_T("OID"), pTaskCode->nOid);
		pTempElem2->SetAttribute(_T("TASK_OID"), pTaskCode->nTaskOid);
		pTempElem2->SetAttribute(_T("CODE_INDEX"), pTaskCode->nCodeIndex);
		pTempElem2->SetAttribute(_T("DIANSHI_TEST"), pTaskCode->nDianshiTest);
		pTempElem2->SetAttribute(_T("CODE_NAME"), pTaskCode->szCodeName);
		pTempRoot2->LinkEndChild(pTempElem2);
	}
	

	//�����Ʒͼ�ű�//

	vector<StBasTaskPicNum *> *pArryTaskPicNum = &pTaskInfo->pArryTaskPicNum;
	int nPicNumCount = pArryTaskPicNum->size();
	
	pTempRoot3 = new TiXmlElement("TaskPicNumInfo");
	pTempRoot3->SetAttribute("TabRowCnt", nPicNumCount);
	pTempRoot3->SetAttribute("TabColCnt", 6);
	pTabSrtRoot->LinkEndChild(pTempRoot3);

	StBasTaskPicNum* pTaskPicNum = NULL;
	for(i = 0; i<nPicNumCount;i++)
	{
		pTaskPicNum = NULL;
		pTaskPicNum = pArryTaskPicNum->at(i);
		if(pTaskPicNum == NULL)
		{
			continue;
		}
		strText.Format(_T("ItemRoot%d"),i+1);
		pTempElem3 = new TiXmlElement(strText);

		pTempElem3->SetAttribute(_T("OID"), pTaskPicNum->nOid);
		pTempElem3->SetAttribute(_T("TASK_OID"), pTaskPicNum->nTaskOid);
		pTempElem3->SetAttribute(_T("PICNUM_INDEX"), pTaskPicNum->nPicNumIndex);
		pTempElem3->SetAttribute(_T("PICNUM_OID"), pTaskPicNum->nPicNumOid);
		pTempElem3->SetAttribute(_T("PICNUM_NO"), pTaskPicNum->szPicNumNo);
		pTempElem3->SetAttribute(_T("PICNUM_NAME"), pTaskPicNum->szPicNumName);
		pTempRoot3->LinkEndChild(pTempElem3);
	}

	doc.SaveFile(szFileName);


	return 1;
}

int LoadOutTaskXmlAnalysis::UpdateTaskInfoToDb()
{
	char      szFileName[512] = {0,};

	char *Data = NULL;
	int len = 0;

	GetCurModeXmlFileName(File_Xml_LoadOut_TaskInfo, szFileName);
	remove(szFileName);
	SetXmlLoadOutTaskInfo(&m_CurTaskInfo);
	ReadFileFromLocal(szFileName,&Data,len);

	if(!Data||!len)
	{
		AfxMessageBox("����������������Ϊ��!");
		return 0;
	}

	//���µ�ǰ�ṹ�����ļ�//
	char szSQL[256] = {0};
	sprintf(szSQL,"update BAS_TASK set TASK_INFOFILE=? where OID=%d",
		m_CurTaskInfo.stTaskBaseInfo.nOid);
	m_SqliteDb.open(m_szDbPath.GetBuffer(0));
	m_SqliteDb.SqliteWriteBolb(szSQL,Data,len);
	m_SqliteDb.close();
	delete []Data;
	return 1;
}
int LoadOutTaskXmlAnalysis::GetXmlLoadOutTaskInfo(StBasTask *pTaskInfo)
{
	char      szFileName[MAX_PATH] = {0,};

	GetCurModeXmlFileName(File_Xml_LoadOut_TaskInfo, szFileName);
	remove(szFileName);
	//�Ƚ����ݿ��������ϢXML�ļ���ȡ�������ļ�����///

	char *szSQL = "select TASK_INFOFILE from BAS_TASK";
	char *Data;
	int nLen;
	m_SqliteDb.open(m_szDbPath.GetBuffer(0));
	m_SqliteDb.SqliteReadBolb(szSQL,&Data,nLen);
	m_SqliteDb.close();
	if(!Data || !nLen)
	{
		AfxMessageBox(_T("������ϢΪ��"));
		return 0;
	}

	WriteFileToLocal(szFileName,Data,nLen);

	delete Data;

	
	pTaskInfo->ReleaseCode();
	pTaskInfo->ReleasePicNum();
	pTaskInfo->ReleaseBase();
	

	StBasTaskBaseInfo *pTaskBaseInfo = &pTaskInfo->stTaskBaseInfo;
	StBasProduct      *pProductInfo = &pTaskInfo->stProductInfo;
	StHrUpDepart      *pUpDepartInfo = &pTaskInfo->stHrUpDepart;


	//------------------------------------------------------------------------------
	TiXmlDocument   doc( szFileName );
	TiXmlElement	* pRootInfo;
	if (!doc.LoadFile())
	{
		return 0;
	}
	pRootInfo = doc.RootElement();
	TiXmlElement	*pRoot, *pRootType, *pRoot1;
	int				Layer1, Layer2, Layer3;
	CString			strTemp, str;
	int             nRowNum = 0;
	int             nColNum = 0;
	int             nRowPos=0, nColPos=0;
	int             nCount=0;




	Layer1 = 0;
	Layer2 = 0;
	Layer3 = 0;

	if (pRootInfo)
	{
		//  ----------------------------------------------------------------------
		pRoot= pRootInfo->FirstChildElement("TaskLoadOutTaskInfo");
		if (pRoot)
		{
			// 1.�����������Ϣ
			pRootType = pRoot->FirstChildElement("TaskTabItemData");

			if (pRootType)
			{
				//1.
				strTemp = pRootType->Attribute("TabColCnt");
				nCount = atoi(strTemp.GetBuffer(0));

				//��һ��
				pRoot1 = pRootType->FirstChildElement("ItemRoot1");		
				if (pRoot1)
				{
					//for (int i = 0;i<len;i++)
					//{
					//	strTemp = pRoot1->Attribute(Fields[i]);	//����״̬
					//	//AfxMessageBox(strTemp);
					//}

					
						
					
					char szTaskFields[40][20] = {
					_T("OID"), _T("TASK_NAME"), _T("PROJECT_NO"), _T("TASK_STATUS"), _T("TASK_TYPE"),
					_T("MODEL"), _T("PHASE"), _T("PRODUCT_OID"), _T("PRODUCT_NO"), _T("PRODUCT_NAME"),
					_T("PRODUCT_CODE"), _T("CODE_COUNT"), _T("BATCH"), _T("DEPART_OID"), _T("DEPART_NAME"), 
					_T("UP_USER"), _T("UP_DATE"), _T("SEND_DATE"), _T("CHECK_LEADER"), _T("CHECK_USER"),
					_T("TECH_USER"), _T("ARMY_TEST"), _T("DIANSHI_NUM"), _T("ACCORDING1"), _T("ACCORDING2"),
					_T("ACCORDING3"), _T("ACCORDING4"), _T("ACCORDING5"), _T("TASK_REMARK"), _T("PLAN_BEGTIME"),
					_T("PLAN_ENDTIME"),_T("REAL_BEGTIME"),_T("REAL_ENDTIME"),_T("DOWNLOAD_DATE"),_T("FINISH_DATE"),
					_T("CREATE_TIME"),_T("CREATE_USER"),_T("GROUP_OID"),_T("GROUP_NAME")};
					int pos = 0;

					pTaskBaseInfo->nOid = atoi(pRoot1->Attribute(szTaskFields[pos++]));
					strcpy(pTaskBaseInfo->szTaskName, pRoot1->Attribute(szTaskFields[pos++]));
					strcpy(pTaskBaseInfo->szProjectNo, pRoot1->Attribute(szTaskFields[pos++]));
					pTaskBaseInfo->nTaskStatus = atoi(pRoot1->Attribute(szTaskFields[pos++]));
					pTaskBaseInfo->nTaskType = atoi(pRoot1->Attribute(szTaskFields[pos++]));

					strcpy(pTaskBaseInfo->szModel, pRoot1->Attribute(szTaskFields[pos++]));
					strcpy(pTaskBaseInfo->szPhase, pRoot1->Attribute(szTaskFields[pos++]));
					pProductInfo->nOid = atoi(pRoot1->Attribute(szTaskFields[pos++]));
					strcpy(pProductInfo->szProductNo, pRoot1->Attribute(szTaskFields[pos++]));
					strcpy(pProductInfo->szProductName, pRoot1->Attribute(szTaskFields[pos++]));
					
					strcpy(pTaskBaseInfo->szProductCode, pRoot1->Attribute(szTaskFields[pos++]));
					pTaskBaseInfo->nCodeNumber = atoi(pRoot1->Attribute(szTaskFields[pos++]));
					strcpy(pTaskBaseInfo->szBatch, pRoot1->Attribute(szTaskFields[pos++]));
					pUpDepartInfo->nOid = atoi(pRoot1->Attribute(szTaskFields[pos++]));//���첿��OID//
					strcpy(pUpDepartInfo->szUpDepartName, pRoot1->Attribute(szTaskFields[pos++]));//���첿�� ����//

					strcpy(pTaskBaseInfo->szUpUser, pRoot1->Attribute(szTaskFields[pos++]));
					strcpy(pTaskBaseInfo->szUpDate, pRoot1->Attribute(szTaskFields[pos++]));
					strcpy(pTaskBaseInfo->szSendDate, pRoot1->Attribute(szTaskFields[pos++]));
					strcpy(pTaskBaseInfo->szCheckLeader, pRoot1->Attribute(szTaskFields[pos++]));
					strcpy(pTaskBaseInfo->szCheckUser, pRoot1->Attribute(szTaskFields[pos++]));

					strcpy(pTaskBaseInfo->szTechUser, pRoot1->Attribute(szTaskFields[pos++]));
					pTaskBaseInfo->nArmyTest = atoi(pRoot1->Attribute(szTaskFields[pos++]));
					pTaskBaseInfo->nDianShiNum = atoi(pRoot1->Attribute(szTaskFields[pos++]));
					strcpy(pTaskBaseInfo->szAccording1, pRoot1->Attribute(szTaskFields[pos++]));
					strcpy(pTaskBaseInfo->szAccording2, pRoot1->Attribute(szTaskFields[pos++]));

					strcpy(pTaskBaseInfo->szAccording3, pRoot1->Attribute(szTaskFields[pos++]));
					strcpy(pTaskBaseInfo->szAccording4, pRoot1->Attribute(szTaskFields[pos++]));
					strcpy(pTaskBaseInfo->szAccording5, pRoot1->Attribute(szTaskFields[pos++]));
					strcpy(pTaskBaseInfo->szTaskRemark, pRoot1->Attribute(szTaskFields[pos++]));
					strcpy(pTaskBaseInfo->szPlanBegTime, pRoot1->Attribute(szTaskFields[pos++]));

					strcpy(pTaskBaseInfo->szPlanEndTime, pRoot1->Attribute(szTaskFields[pos++]));
					strcpy(pTaskBaseInfo->szRealBegTime, pRoot1->Attribute(szTaskFields[pos++]));
					strcpy(pTaskBaseInfo->szRealEndTime, pRoot1->Attribute(szTaskFields[pos++]));
					strcpy(pTaskBaseInfo->szDownLoadDate, pRoot1->Attribute(szTaskFields[pos++]));
					strcpy(pTaskBaseInfo->szFinishDate, pRoot1->Attribute(szTaskFields[pos++]));

					strcpy(pTaskBaseInfo->szCreateDate, pRoot1->Attribute(szTaskFields[pos++]));
					strcpy(pTaskBaseInfo->szCreateUser, pRoot1->Attribute(szTaskFields[pos++]));
					pTaskBaseInfo->nGroupOid = atoi(pRoot1->Attribute(szTaskFields[pos++]));
					strcpy(pTaskBaseInfo->szGroupName, pRoot1->Attribute(szTaskFields[pos++]));
					
				}
			}

			//�ڶ���  �����Ʒ���//

			vector<StBasTaskCode *> *pArryTaskCode = &pTaskInfo->pArryTaskCode;
			CString strText;
			int i;
			pRootType = pRoot->FirstChildElement("TaskCodeInfo");
			if (pRootType)
			{
				//1.
				strTemp = pRootType->Attribute("TabRowCnt");
				nCount = atoi(strTemp.GetBuffer(0));
				
				for (i = 0;i< nCount;i++)
				{
					strText.Format(_T("ItemRoot%d"),i+1);
					//2.
					pRoot1 = pRootType->FirstChildElement(strText);		
					if (pRoot1)
					{
						StBasTaskCode *pTaskCode = new StBasTaskCode;
						memset(pTaskCode,0,sizeof(StBasTaskCode));
						
						pTaskCode->nOid = atoi(pRoot1->Attribute(_T("OID")));
						pTaskCode->nTaskOid = atoi(pRoot1->Attribute(_T("TASK_OID")));
						pTaskCode->nCodeIndex = atoi(pRoot1->Attribute(_T("CODE_INDEX")));
						pTaskCode->nDianshiTest = atoi(pRoot1->Attribute(_T("DIANSHI_TEST")));
						strcpy(pTaskCode->szCodeName, pRoot1->Attribute(_T("CODE_NAME")));
						pArryTaskCode->push_back(pTaskCode);
					}
				}
				
			}
			//������  �����Ʒͼ��//

			vector<StBasTaskPicNum *> *pArryTaskPicNum = &pTaskInfo->pArryTaskPicNum;
			pRootType = pRoot->FirstChildElement("TaskPicNumInfo");
			if (pRootType)
			{
				//1.
				strTemp = pRootType->Attribute("TabRowCnt");
				nCount = atoi(strTemp.GetBuffer(0));
				
				for (i = 0;i< nCount;i++)
				{
					strText.Format(_T("ItemRoot%d"),i+1);
					//2.
					pRoot1 = pRootType->FirstChildElement(strText);		
					if (pRoot1)
					{
						StBasTaskPicNum *pTaskPicNum = new StBasTaskPicNum;
						memset(pTaskPicNum,0,sizeof(StBasTaskPicNum));

						pTaskPicNum->nOid = atoi(pRoot1->Attribute(_T("OID")));
						pTaskPicNum->nTaskOid = atoi(pRoot1->Attribute(_T("TASK_OID")));
						pTaskPicNum->nPicNumIndex = atoi(pRoot1->Attribute(_T("PICNUM_INDEX")));
						pTaskPicNum->nPicNumOid = atoi(pRoot1->Attribute(_T("PICNUM_OID")));
						strcpy(pTaskPicNum->szPicNumNo, pRoot1->Attribute(_T("PICNUM_NO")));
						strcpy(pTaskPicNum->szPicNumName, pRoot1->Attribute(_T("PICNUM_NAME")));
						pArryTaskPicNum->push_back(pTaskPicNum);
					}
				}
				
			}
		}

	}//if pRootInfo
	return 1;
}

int LoadOutTaskXmlAnalysis::GetCurTaskInfo()
{
	GetXmlLoadOutTaskInfo(&m_CurTaskInfo);
	return 1;
}

int LoadOutTaskXmlAnalysis::GetCurTaskInfoLoad(StBasTask *pTaskInfo)//�ӱ���·���»�ȡ������Ϣ//
{
	char      szFileName[MAX_PATH] = {0,};

	GetCurModeXmlFileName(File_Xml_LoadOut_TaskInfo, szFileName);
	pTaskInfo->ReleaseCode();
	pTaskInfo->ReleasePicNum();
	pTaskInfo->ReleaseBase();

	//�ж��ļ�������? �ļ������Ƿ�Ϊ��

	if(GetFileAttributes(szFileName) == 0xFFFFFFFF)
	{
		return 0;
	}

	StBasTaskBaseInfo *pTaskBaseInfo = &pTaskInfo->stTaskBaseInfo;
	StBasProduct      *pProductInfo = &pTaskInfo->stProductInfo;
	StHrUpDepart      *pUpDepartInfo = &pTaskInfo->stHrUpDepart;

	//------------------------------------------------------------------------------
	TiXmlDocument   doc( szFileName );
	TiXmlElement	* pRootInfo;
	if (!doc.LoadFile())
	{
		return 0;
	}
	pRootInfo = doc.RootElement();
	TiXmlElement	*pRoot, *pRootType, *pRoot1;
	int				Layer1, Layer2, Layer3;
	CString			strTemp, str;
	int             nRowNum = 0;
	int             nColNum = 0;
	int             nRowPos=0, nColPos=0;
	int             nCount=0;




	Layer1 = 0;
	Layer2 = 0;
	Layer3 = 0;

	if (pRootInfo)
	{
		//  ----------------------------------------------------------------------
		pRoot= pRootInfo->FirstChildElement("TaskLoadOutTaskInfo");
		if (pRoot)
		{
			// 1.�����������Ϣ
			pRootType = pRoot->FirstChildElement("TaskTabItemData");

			if (pRootType)
			{
				//1.
				strTemp = pRootType->Attribute("TabColCnt");
				nCount = atoi(strTemp.GetBuffer(0));

				//��һ��
				pRoot1 = pRootType->FirstChildElement("ItemRoot1");		
				if (pRoot1)
				{
					char szTaskFields[40][20] = {
						_T("OID"), _T("TASK_NAME"), _T("PROJECT_NO"), _T("TASK_STATUS"), _T("TASK_TYPE"),
						_T("MODEL"), _T("PHASE"), _T("PRODUCT_OID"), _T("PRODUCT_NO"), _T("PRODUCT_NAME"),
						_T("PRODUCT_CODE"), _T("CODE_COUNT"), _T("BATCH"), _T("DEPART_OID"), _T("DEPART_NAME"), 
						_T("UP_USER"), _T("UP_DATE"), _T("SEND_DATE"), _T("CHECK_LEADER"), _T("CHECK_USER"),
						_T("TECH_USER"), _T("ARMY_TEST"), _T("DIANSHI_NUM"), _T("ACCORDING1"), _T("ACCORDING2"),
						_T("ACCORDING3"), _T("ACCORDING4"), _T("ACCORDING5"), _T("TASK_REMARK"), _T("PLAN_BEGTIME"),
						_T("PLAN_ENDTIME"),_T("REAL_BEGTIME"),_T("REAL_ENDTIME"),_T("DOWNLOAD_DATE"),_T("FINISH_DATE"),
						_T("CREATE_TIME"),_T("CREATE_USER"),_T("GROUP_OID"),_T("GROUP_NAME")};
						int pos = 0;

						pTaskBaseInfo->nOid = atoi(pRoot1->Attribute(szTaskFields[pos++]));
						strcpy(pTaskBaseInfo->szTaskName, pRoot1->Attribute(szTaskFields[pos++]));
						strcpy(pTaskBaseInfo->szProjectNo, pRoot1->Attribute(szTaskFields[pos++]));
						pTaskBaseInfo->nTaskStatus = atoi(pRoot1->Attribute(szTaskFields[pos++]));
						pTaskBaseInfo->nTaskType = atoi(pRoot1->Attribute(szTaskFields[pos++]));

						strcpy(pTaskBaseInfo->szModel, pRoot1->Attribute(szTaskFields[pos++]));
						strcpy(pTaskBaseInfo->szPhase, pRoot1->Attribute(szTaskFields[pos++]));
						pProductInfo->nOid = atoi(pRoot1->Attribute(szTaskFields[pos++]));
						strcpy(pProductInfo->szProductNo, pRoot1->Attribute(szTaskFields[pos++]));
						strcpy(pProductInfo->szProductName, pRoot1->Attribute(szTaskFields[pos++]));

						strcpy(pTaskBaseInfo->szProductCode, pRoot1->Attribute(szTaskFields[pos++]));
						pTaskBaseInfo->nCodeNumber = atoi(pRoot1->Attribute(szTaskFields[pos++]));
						strcpy(pTaskBaseInfo->szBatch, pRoot1->Attribute(szTaskFields[pos++]));
						pUpDepartInfo->nOid = atoi(pRoot1->Attribute(szTaskFields[pos++]));//���첿��OID//
						strcpy(pUpDepartInfo->szUpDepartName, pRoot1->Attribute(szTaskFields[pos++]));//���첿�� ����//

						strcpy(pTaskBaseInfo->szUpUser, pRoot1->Attribute(szTaskFields[pos++]));
						strcpy(pTaskBaseInfo->szUpDate, pRoot1->Attribute(szTaskFields[pos++]));
						strcpy(pTaskBaseInfo->szSendDate, pRoot1->Attribute(szTaskFields[pos++]));
						strcpy(pTaskBaseInfo->szCheckLeader, pRoot1->Attribute(szTaskFields[pos++]));
						strcpy(pTaskBaseInfo->szCheckUser, pRoot1->Attribute(szTaskFields[pos++]));

						strcpy(pTaskBaseInfo->szTechUser, pRoot1->Attribute(szTaskFields[pos++]));
						pTaskBaseInfo->nArmyTest = atoi(pRoot1->Attribute(szTaskFields[pos++]));
						pTaskBaseInfo->nDianShiNum = atoi(pRoot1->Attribute(szTaskFields[pos++]));
						strcpy(pTaskBaseInfo->szAccording1, pRoot1->Attribute(szTaskFields[pos++]));
						strcpy(pTaskBaseInfo->szAccording2, pRoot1->Attribute(szTaskFields[pos++]));

						strcpy(pTaskBaseInfo->szAccording3, pRoot1->Attribute(szTaskFields[pos++]));
						strcpy(pTaskBaseInfo->szAccording4, pRoot1->Attribute(szTaskFields[pos++]));
						strcpy(pTaskBaseInfo->szAccording5, pRoot1->Attribute(szTaskFields[pos++]));
						strcpy(pTaskBaseInfo->szTaskRemark, pRoot1->Attribute(szTaskFields[pos++]));
						strcpy(pTaskBaseInfo->szPlanBegTime, pRoot1->Attribute(szTaskFields[pos++]));

						strcpy(pTaskBaseInfo->szPlanEndTime, pRoot1->Attribute(szTaskFields[pos++]));
						strcpy(pTaskBaseInfo->szRealBegTime, pRoot1->Attribute(szTaskFields[pos++]));
						strcpy(pTaskBaseInfo->szRealEndTime, pRoot1->Attribute(szTaskFields[pos++]));
						strcpy(pTaskBaseInfo->szDownLoadDate, pRoot1->Attribute(szTaskFields[pos++]));
						strcpy(pTaskBaseInfo->szFinishDate, pRoot1->Attribute(szTaskFields[pos++]));

						strcpy(pTaskBaseInfo->szCreateDate, pRoot1->Attribute(szTaskFields[pos++]));
						strcpy(pTaskBaseInfo->szCreateUser, pRoot1->Attribute(szTaskFields[pos++]));
						pTaskBaseInfo->nGroupOid = atoi(pRoot1->Attribute(szTaskFields[pos++]));
						strcpy(pTaskBaseInfo->szGroupName, pRoot1->Attribute(szTaskFields[pos++]));


				}
			}

			//�ڶ���  �����Ʒ���//

			vector<StBasTaskCode *> *pArryTaskCode = &pTaskInfo->pArryTaskCode;
			CString strText;
			int i;
			pRootType = pRoot->FirstChildElement("TaskCodeInfo");
			if (pRootType)
			{
				//1.
				strTemp = pRootType->Attribute("TabRowCnt");
				nCount = atoi(strTemp.GetBuffer(0));
				
				for (i = 0;i< nCount;i++)
				{
					strText.Format(_T("ItemRoot%d"),i+1);
					//2.
					pRoot1 = pRootType->FirstChildElement(strText);		
					if (pRoot1)
					{
						StBasTaskCode *pTaskCode = new StBasTaskCode;
						memset(pTaskCode,0,sizeof(StBasTaskCode));

						pTaskCode->nOid = atoi(pRoot1->Attribute(_T("OID")));
						pTaskCode->nTaskOid = atoi(pRoot1->Attribute(_T("TASK_OID")));
						pTaskCode->nCodeIndex = atoi(pRoot1->Attribute(_T("CODE_INDEX")));
						pTaskCode->nDianshiTest = atoi(pRoot1->Attribute(_T("DIANSHI_TEST")));
						strcpy(pTaskCode->szCodeName, pRoot1->Attribute(_T("CODE_NAME")));
						pArryTaskCode->push_back(pTaskCode);
					}
				}

			}
			//������  �����Ʒͼ��//

			vector<StBasTaskPicNum *> *pArryTaskPicNum = &pTaskInfo->pArryTaskPicNum;
			pRootType = pRoot->FirstChildElement("TaskPicNumInfo");
			if (pRootType)
			{
				//1.
				strTemp = pRootType->Attribute("TabRowCnt");
				nCount = atoi(strTemp.GetBuffer(0));

				for (i = 0;i< nCount;i++)
				{
					strText.Format(_T("ItemRoot%d"),i+1);
					//2.
					pRoot1 = pRootType->FirstChildElement(strText);		
					if (pRoot1)
					{
						StBasTaskPicNum *pTaskPicNum = new StBasTaskPicNum;
						memset(pTaskPicNum,0,sizeof(StBasTaskPicNum));

						pTaskPicNum->nOid = atoi(pRoot1->Attribute(_T("OID")));
						pTaskPicNum->nTaskOid = atoi(pRoot1->Attribute(_T("TASK_OID")));
						pTaskPicNum->nPicNumIndex = atoi(pRoot1->Attribute(_T("PICNUM_INDEX")));
						pTaskPicNum->nPicNumOid = atoi(pRoot1->Attribute(_T("PICNUM_OID")));
						strcpy(pTaskPicNum->szPicNumNo, pRoot1->Attribute(_T("PICNUM_NO")));
						strcpy(pTaskPicNum->szPicNumName, pRoot1->Attribute(_T("PICNUM_NAME")));
						pArryTaskPicNum->push_back(pTaskPicNum);
					}
				}

			}
		}

	}//if pRootInfo
	return 1;
}
int LoadOutTaskXmlAnalysis::GetCurTaskInfoLoad()//�ӱ���·���»�ȡ//
{
	GetCurTaskInfoLoad(&m_CurTaskInfo);
	return 1;
}
int LoadOutTaskXmlAnalysis::SetXmlLoadOutTaskNumbelMode(vector<StTstResultAtta *> *pArryTstResultBase)
{
	char      szFileName[512] = {0,};

	GetCurModeXmlFileName(File_xml_LoadOut_TaskNumbelMode, szFileName);
	remove(szFileName);

	int i;
	//����XML�ļ�ͷ----------------------------------------------------------------------------
	TiXmlDocument	doc;
	TiXmlDeclaration* pDec = new TiXmlDeclaration(DECL_LOAD_VERSION, DECL_LOAD_ENCODING, DECL_LOAD_STANDALONE);
	doc.LinkEndChild(pDec);
	TiXmlElement* pRootInfo = new TiXmlElement("RootInfo");
	doc.LinkEndChild(pRootInfo);	
	SetXmlRootInfoLoad(pRootInfo);
	//-----------------------------------------------------------------------------------------
	TiXmlElement	*pTabSrtRoot, *pTempRoot; 
	TiXmlElement    *pTempElem1;

	//����ģ��ṹ��Ϣ Set
	pTabSrtRoot = new TiXmlElement("TaskLoadOutTaskNumbelMode");
	pRootInfo->LinkEndChild(pTabSrtRoot);

	//1.����������ű�
	int nTaskCount = pArryTstResultBase->size();
	CString strText;
	pTempRoot = new TiXmlElement("TaskNumbelModeTabItemData");

	pTempRoot->SetAttribute("TabRowCnt", nTaskCount);
	pTabSrtRoot->LinkEndChild(pTempRoot);

	StTstResultAtta *pTstResultBase = NULL;

	char szResultAttaFields[20][20] = {
		"OID","TASK_OID","MODE_OID","PRODUCT_OID","PRODUCT_NO","BATCH",
		"PRODUCT_NAME","PRODUCT_CODE","MODEL","PHASE","MODE_NAME",
		"MODE_TYPE","MODE_ROWVAR","FORMULA","PICNUM_COUNT","DIANSHI_TEST","PERCENT",
		"FINISHED","FINISHED_TIME","CHECK_USER"};
	int pos =0;
	for (i = 0;i<nTaskCount;i++)
	{
		pTstResultBase = NULL;
		pTstResultBase = pArryTstResultBase->at(i);
		if(pTstResultBase == NULL)
		{
			continue;
		}

		pos = 0;
		strText.Format(_T("ItemRoot%d"),i+1);
		pTempElem1 = new TiXmlElement(strText);
		pTempElem1->SetAttribute(szResultAttaFields[pos++], pTstResultBase->nOid);
		pTempElem1->SetAttribute(szResultAttaFields[pos++],  pTstResultBase->nTaskOid);
		pTempElem1->SetAttribute(szResultAttaFields[pos++],  pTstResultBase->nModeOid);
		pTempElem1->SetAttribute(szResultAttaFields[pos++],  pTstResultBase->nProductOid);
		pTempElem1->SetAttribute(szResultAttaFields[pos++],  pTstResultBase->szProductNo);
		pTempElem1->SetAttribute(szResultAttaFields[pos++],  pTstResultBase->szBatch);

		pTempElem1->SetAttribute(szResultAttaFields[pos++],  pTstResultBase->szProductName);
		pTempElem1->SetAttribute(szResultAttaFields[pos++],  pTstResultBase->szProductCode);
		pTempElem1->SetAttribute(szResultAttaFields[pos++],  pTstResultBase->szModel);
		pTempElem1->SetAttribute(szResultAttaFields[pos++],  pTstResultBase->szPhase);
		pTempElem1->SetAttribute(szResultAttaFields[pos++],  pTstResultBase->szModeName);

		pTempElem1->SetAttribute(szResultAttaFields[pos++],  pTstResultBase->nModeType);
		pTempElem1->SetAttribute(szResultAttaFields[pos++],  pTstResultBase->nModeRowVar);
		pTempElem1->SetAttribute(szResultAttaFields[pos++],  pTstResultBase->nFormula);
		pTempElem1->SetAttribute(szResultAttaFields[pos++],  pTstResultBase->nPicNumCount);
		pTempElem1->SetAttribute(szResultAttaFields[pos++],  pTstResultBase->nDianshiTest);
		pTempElem1->SetAttribute(szResultAttaFields[pos++],  pTstResultBase->nPercent);

		pTempElem1->SetAttribute(szResultAttaFields[pos++],  pTstResultBase->bFinished);
		pTempElem1->SetAttribute(szResultAttaFields[pos++],  pTstResultBase->szFinishedTime);
		pTempElem1->SetAttribute(szResultAttaFields[pos++],  pTstResultBase->szCheckUser);
		pTempRoot->LinkEndChild(pTempElem1);
	}
	
	
	doc.SaveFile(szFileName);



	return 1;
}

int LoadOutTaskXmlAnalysis::GetXmlLoadOutTaskNumbelMode(vector<StTstResultAtta *> *pArryTstResultBase)
{

	char      szFileName[MAX_PATH] = {0,};

	GetCurModeXmlFileName(File_xml_LoadOut_TaskNumbelMode, szFileName);
	remove(szFileName);

	//�Ƚ����ݿ��XML�ļ���ȡ�������ļ�����///

	char *szSQL = "select TST_RESULT_BASE_FILE from TST_RESULT_BASE";
	char *Data = NULL;
	int nLen=0;
	m_SqliteDb.open(m_szDbPath.GetBuffer(0));
	m_SqliteDb.SqliteReadBolb(szSQL,&Data,nLen);
	m_SqliteDb.close();

	if(!Data || !nLen)
	{
		AfxMessageBox(_T("û���κμ������"));
		return 0;
	}
	WriteFileToLocal(szFileName,Data,nLen);
	delete Data;

	//------------------------------------------------------------------------------
	TiXmlDocument   doc( szFileName );
	TiXmlElement	* pRootInfo;
	if (!doc.LoadFile())
	{
		return 0;
	}
	pRootInfo = doc.RootElement();
	TiXmlElement	*pRoot, *pRootType, *pRoot1;
	int				Layer1, Layer2, Layer3;
	CString			strTemp, str;
	int             nRowNum = 0;
	int             nColNum = 0;
	int             nRowPos=0, nColPos=0;
	int             nCount=0;



	Layer1 = 0;
	Layer2 = 0;
	Layer3 = 0;

	if (pRootInfo)
	{
		//  ----------------------------------------------------------------------
		pRoot= pRootInfo->FirstChildElement("TaskLoadOutTaskNumbelMode");
		if (pRoot)
		{
			//2.1 �������
			pRootType = pRoot->FirstChildElement("TaskNumbelModeTabItemData");

			if (pRootType)
			{
				//1.
				strTemp = pRootType->Attribute("TabRowCnt");
				nCount = atoi(strTemp.GetBuffer(0));

				CString strText;
					
				
				int i, nSize = 0;
				nSize = pArryTstResultBase->size();
				for (i = 0;i<nSize;i++)
				{
					delete pArryTstResultBase->at(i);
				}
				pArryTstResultBase->clear();
				
				
				char szResultAttaFields[20][20] = {
					"OID","TASK_OID","MODE_OID","PRODUCT_OID","PRODUCT_NO","BATCH",
					"PRODUCT_NAME","PRODUCT_CODE","MODEL","PHASE","MODE_NAME",
					"MODE_TYPE","MODE_ROWVAR","FORMULA","PICNUM_COUNT","DIANSHI_TEST","PERCENT",
					"FINISHED","FINISHED_TIME","CHECK_USER"};
					int pos =0;

				for (int i = 0;i<nCount;i++)
				{
					StTstResultAtta *pTstResultBase = new StTstResultAtta;
					memset(pTstResultBase,0,sizeof(StTstResultAtta));
					//��һ��
					strText.Format("ItemRoot%d",i+1);
					pRoot1 = pRootType->FirstChildElement(strText);
					if (pRoot1)
					{
						pos = 0;
						pTstResultBase->nOid = atoi(pRoot1->Attribute(szResultAttaFields[pos++]));
						pTstResultBase->nTaskOid = atoi(pRoot1->Attribute(szResultAttaFields[pos++]));
						pTstResultBase->nModeOid = atoi(pRoot1->Attribute(szResultAttaFields[pos++]));
						pTstResultBase->nProductOid = atoi(pRoot1->Attribute(szResultAttaFields[pos++]));
						strcpy(pTstResultBase->szProductNo, pRoot1->Attribute(szResultAttaFields[pos++]));
						strcpy(pTstResultBase->szBatch, pRoot1->Attribute(szResultAttaFields[pos++]));

						strcpy(pTstResultBase->szProductName, pRoot1->Attribute(szResultAttaFields[pos++]));
						strcpy(pTstResultBase->szProductCode, pRoot1->Attribute(szResultAttaFields[pos++]));
						strcpy(pTstResultBase->szModel, pRoot1->Attribute(szResultAttaFields[pos++]));
						strcpy(pTstResultBase->szPhase, pRoot1->Attribute(szResultAttaFields[pos++]));
						strcpy(pTstResultBase->szModeName, pRoot1->Attribute(szResultAttaFields[pos++]));

						pTstResultBase->nModeType = atoi(pRoot1->Attribute(szResultAttaFields[pos++]));
						pTstResultBase->nModeRowVar = atoi(pRoot1->Attribute(szResultAttaFields[pos++]));
						pTstResultBase->nFormula = atoi(pRoot1->Attribute(szResultAttaFields[pos++]));

						pTstResultBase->nPicNumCount = atoi(pRoot1->Attribute(szResultAttaFields[pos++]));
						pTstResultBase->nDianshiTest = atoi(pRoot1->Attribute(szResultAttaFields[pos++]));
						pTstResultBase->nPercent = atoi(pRoot1->Attribute(szResultAttaFields[pos++]));

						pTstResultBase->bFinished = atoi(pRoot1->Attribute(szResultAttaFields[pos++]));
						strcpy(pTstResultBase->szFinishedTime, pRoot1->Attribute(szResultAttaFields[pos++]));
						strcpy(pTstResultBase->szCheckUser, pRoot1->Attribute(szResultAttaFields[pos++]));
						pArryTstResultBase->push_back(pTstResultBase);
					}
				}
					
				
			}
		}

	}//if pRootInfo

	int nSize = pArryTstResultBase->size();
	if(nSize != nCount)
	{
		//AfxMessageBox("");
	}
	return nSize;
}
int LoadOutTaskXmlAnalysis::GetAllTaskNumbelMode()
{
	return GetXmlLoadOutTaskNumbelMode(&m_ArrayTaskNumbelMode);
	
	
}
int LoadOutTaskXmlAnalysis::UpdateTaskNumbelToDb()
{
	char      szFileName[512] = {0,};

	char *Data = NULL;
	int len = 0;

	GetCurModeXmlFileName(File_xml_LoadOut_TaskNumbelMode, szFileName);
	remove(szFileName);
	SetXmlLoadOutTaskNumbelMode(&m_ArrayTaskNumbelMode);
	ReadFileFromLocal(szFileName,&Data,len);

	if(!Data||!len)
	{
		AfxMessageBox("����������������Ϊ��!");
		return 0;
	}

	//���µ�ǰ�ṹ�����ļ�//
	char szSQL[256] = {0};
	sprintf(szSQL,"update TST_RESULT_BASE set TST_RESULT_BASE_FILE=? where OID=1");
	m_SqliteDb.open(m_szDbPath.GetBuffer(0));
	m_SqliteDb.SqliteWriteBolb(szSQL,Data,len);
	m_SqliteDb.close();
	delete []Data;
	return 1;
}
int LoadOutTaskXmlAnalysis::GetCurTaskNumbelMode(char *ProdNumbel,UINT nModeOid)
{
	int nCount = m_ArrayTaskNumbelMode.size();
	if(nCount <= 0 )
	{
		AfxMessageBox("��ǰ������Ϊ 0 ");
		return 0;
	}
	int i;
	for (i = 0;i<nCount;i++)
	{
		if(strcmp(m_ArrayTaskNumbelMode.at(i)->szProductCode, ProdNumbel) == 0 && 
			m_ArrayTaskNumbelMode.at(i)->nModeOid == nModeOid)
		{
			m_pCurTaskNumbelMode = m_ArrayTaskNumbelMode.at(i);
			break;
		}
	}

	if(i>=nCount)
	{
		AfxMessageBox("δ�ҵ���ǰ��������!");
		return 0;
	}
	return 1;
}

int LoadOutTaskXmlAnalysis::SaveTestDataToDb()
{
	//char      szFileName[MAX_PATH] = {0,};

	char *Data = NULL;
	int len = 0;
	CString strPath;
	strPath.Format( _T("%s//%s//%s"),
		g_WorkPath, 
		PATH_XML_MODE_PAR_CFG, 
		MD_XML_FILE_TAB_OUT_INFO);
	ReadFileFromLocal(strPath.GetBuffer(0),&Data,len);
	if(!Data || !len)
	{
		return 1;
	}
	if(strcmp(m_pCurTaskNumbelMode->szModeName, m_CurModeInfo.szModeName) != 0 )
	{
		AfxMessageBox("��ǰ�洢�����ݺ͵�ǰѡ�е�ģ�岻����!");
		delete []Data;
		return 0;
	}
	//���µ�ǰ�ṹ�����ļ�//
	char szSQL[256] = {0};
	sprintf(szSQL,"update TST_DATA set TST_DATA_FILE=? where OID=%d",
		m_pCurTaskNumbelMode->nOid);
	m_SqliteDb.open(m_szDbPath.GetBuffer(0));
	m_SqliteDb.SqliteWriteBolb(szSQL,Data,len);
	m_SqliteDb.close();
	delete []Data;
	return 1;
}
int LoadOutTaskXmlAnalysis::GetTestDataFromDb()
{
	if(strcmp(m_pCurTaskNumbelMode->szModeName, m_CurModeInfo.szModeName) !=0)
	{
		CString strText;
		strText.Format("��ǰ��ȡ�Ľ�����ݺ͵�ǰѡ�е�ģ�岻����!\n\
					   ��ǰѡ�е���:\"%s\",��ȡ��������:\"%s\" ",
					   m_CurModeInfo.szModeName,m_pCurTaskNumbelMode->szModeName);
		AfxMessageBox(strText);
		return 0;
	}

	char szSQL[256] = {0};
	char *Data = NULL;
	int len = 0;
	sprintf(szSQL,"select TST_DATA_FILE from TST_DATA where OID=%d",
		m_pCurTaskNumbelMode->nOid);
	m_SqliteDb.open(m_szDbPath.GetBuffer(0));
	m_SqliteDb.SqliteReadBolb(szSQL,&Data,len);
	m_SqliteDb.close();

	if(!Data || !len)
	{
		delete Data;//ztedit_2017-02-14
		Data = NULL;
		len = 0;
		return 0;
	}

	CString strPath;
	strPath.Format( _T("%s//%s//%s"),
		g_WorkPath, 
		PATH_XML_MODE_PAR_CFG, 
		MD_XML_FILE_TAB_OUT_INFO);

	remove(strPath.GetBuffer(0));
	WriteFileToLocal(strPath.GetBuffer(0), Data, len);
	delete Data;




	return 1;
}



int LoadOutTaskXmlAnalysis::SetBatchOutTask( CString szDefPath,
StHrUser *pUserInfo, vector<StBasTask *> *pBatchTaskArray)
{
	//��������ṹ//
	char      szFileName[512] = {0,};
	CString str,str1,str2;

	str = szDefPath;
	memset(szFileName,0,sizeof(szFileName));
	sprintf(szFileName,_T("%s\\%s"),str,Mul_Task_FileName);
	remove(szFileName);

	int i;
	//����XML�ļ�ͷ----------------------------------------------------------------------------
	TiXmlDocument	doc;
	TiXmlDeclaration* pDec = new TiXmlDeclaration(DECL_LOAD_VERSION, DECL_LOAD_ENCODING, DECL_LOAD_STANDALONE);
	doc.LinkEndChild(pDec);
	TiXmlElement* pRootInfo = new TiXmlElement("RootInfo");
	doc.LinkEndChild(pRootInfo);	
	SetXmlRootInfoLoad(pRootInfo);
	//-----------------------------------------------------------------------------------------
	TiXmlElement	*pTempRoot; 
	TiXmlElement    *pTempElem1;

	//����ģ��ṹ��Ϣ Set
	
	//1.1_TabItemData
	pTempRoot = new TiXmlElement("MulTaskListDown");
	pRootInfo->LinkEndChild(pTempRoot);


	int nTaskCount = pBatchTaskArray->size();
	pTempRoot->SetAttribute("Count", nTaskCount);//�������
	pTempRoot->SetAttribute("CheckUser", pUserInfo->szUserName);//����Ա����
	pTempRoot->SetAttribute("PadDevId", pUserInfo->nPadDevID);//�豸ID
	pTempRoot->SetAttribute("TaskDownTime", GetDateTimeString());//��������ʱ��

	CString strText;
	StBasTask *pTaskInfo = NULL;
	strText.Format("ItemRoot1");
	for(i = 0;i<nTaskCount;i++)//��һ�� ���ж��ٸ�����//
	{
		pTaskInfo = pBatchTaskArray->at(i);
		pTempElem1 = new TiXmlElement(strText);
		str1.Format(_T("%d"),i+1);
		pTempElem1->SetAttribute("Index1", str1);  //1	���
		str1.Format(_T("Task%02d"),i+1);
		pTempElem1->SetAttribute("FOLD_NAME", str1);//2	�ļ�������
		
		str2.Format(_T("%s\\%s"),str,str1);
		if(GetFileAttributes(str2.GetBuffer(0)) == 0xFFFFFFFF)
		{
			CreateDirectory(str2.GetBuffer(0),NULL);
		}
		str1.Format(_T("Task%02d.db"),i+1); //3	�ļ�����
		pTempElem1->SetAttribute("FILE_NAME", str1);
		
		str1.Format(_T("%d"),pTaskInfo->stTaskBaseInfo.nOid);//4	����OID	OID	
		pTempElem1->SetAttribute("OID", str1);
		str1.Format(_T("%s"),pTaskInfo->stTaskBaseInfo.szTaskName);//5	��������
		pTempElem1->SetAttribute("TASK_NAME", str1);

		str1.Format(_T("%s"),pTaskInfo->stProductInfo.szProductName);//6	��Ʒ����
		pTempElem1->SetAttribute("PROJECT_NO", str1);

		str1.Format(_T("%s"),pTaskInfo->stProductInfo.szProductNo);//7	��Ʒ����
		pTempElem1->SetAttribute("PRODUCT_NO", str1);

		str1.Format(_T("%s"),pTaskInfo->stTaskBaseInfo.szBatch);//8	��Ʒ���κ�
		pTempElem1->SetAttribute("BATCH", str1);

		str1.Format(_T("%d"),pTaskInfo->stTaskBaseInfo.nCodeNumber);//9	��Ʒ�������
		pTempElem1->SetAttribute("CODE_COUNT", str1);

		str1.Format(_T("%s"),pTaskInfo->stTaskBaseInfo.szModel);//10	��Ʒ�ͺ�
		pTempElem1->SetAttribute("MODEL", str1);
		str1.Format(_T("%s"),pTaskInfo->stTaskBaseInfo.szPhase);//11	�׶�
		pTempElem1->SetAttribute("PHASE", str1);

		str1.Format(_T("%s"),pTaskInfo->stHrUpDepart.szUpDepartName);//12	���첿��
		pTempElem1->SetAttribute("UP_DEPART", str1);
		
		str1.Format(_T("%s"),pTaskInfo->stTaskBaseInfo.szCheckLeader);//13	�����鳤��
		pTempElem1->SetAttribute("CHECK_LEADER", str1);

		str1.Format(_T("%s"),pTaskInfo->stTaskBaseInfo.szCheckUser);//14	����Ա������
		pTempElem1->SetAttribute("CHECK_USER", str1);

		str1.Format(_T("%d"),pTaskInfo->stTaskBaseInfo.nArmyTest);//15	�Ƿ����
		pTempElem1->SetAttribute("ARMY", str1);

		str1.Format(_T("%s"),pTaskInfo->stTaskBaseInfo.szCreateDate);//16	����ʱ��
		pTempElem1->SetAttribute("CREATE_TIME", str1);

		str1.Format(_T("%s"),pTaskInfo->stTaskBaseInfo.szCreateUser);//17	������
		pTempElem1->SetAttribute("CREATE_USER", str1);

		str1.Format(_T("%s"),pTaskInfo->stTaskBaseInfo.szSendDate);//18	�ɹ�ʱ��
		pTempElem1->SetAttribute("SEND_DATE", str1);

		str1.Format(_T("%s"),pTaskInfo->stTaskBaseInfo.szDownLoadDate);//19	����ʱ��
		pTempElem1->SetAttribute("DOWNLOAD_DATE", str1);

		str1.Format(_T("%s"),pTaskInfo->stTaskBaseInfo.szFinishDate);//20	�������ʱ��
		pTempElem1->SetAttribute("FINISHED_DATE", str1);

		pTempRoot->LinkEndChild(pTempElem1);
	}

	doc.SaveFile(szFileName);
	return 1;

}
int LoadOutTaskXmlAnalysis::GetBatchOutTask(CString szDefPath,StHrUser *pUserInfo, vector<StBasTask *> *pBatchTaskArray)
{
	char      szFileName[MAX_PATH] = {0,};

	memset(szFileName, 0,sizeof(szFileName));
	sprintf(szFileName,_T("%s"),szDefPath);

	//------------------------------------------------------------------------------
	TiXmlDocument   doc( szFileName );
	TiXmlElement	* pRootInfo;
	if (!doc.LoadFile())
	{
		return 0;
	}
	pRootInfo = doc.RootElement();
	TiXmlElement	*pRootType, *pRoot1;
	int				Layer1, Layer2, Layer3;
	CString			strTemp, str;
	int             nRowNum = 0;
	int             nColNum = 0;
	int             nRowPos=0, nColPos=0;
	int             nCount=0;



	Layer1 = 0;
	Layer2 = 0;
	Layer3 = 0;

	if (pRootInfo)
	{
		//  ----------------------------------------------------------------------
	
			//2.1 �������
			pRootType = pRootInfo->FirstChildElement("MulTaskDataUp");

			if (pRootType)
			{
				//1.
				strTemp = pRootType->Attribute("Count");
				nCount = atoi(strTemp.GetBuffer(0));
				//2.����Ա����
				strTemp = pRootType->Attribute("CheckUser");
				strcpy(pUserInfo->szUserName, strTemp);

				//3.PAD�豸ID
				strTemp = pRootType->Attribute("PadDevId");
				pUserInfo->nPadDevID = atoi(strTemp.GetBuffer(0));

				//4.PAD�ϴ�ʱ��
				strTemp = pRootType->Attribute("PadUpTime");
				strcpy(pUserInfo->szPadUpTime, strTemp.GetBuffer(0));

				int pos;
				char szTaskOutFields[25][20] = {
					_T("Index1"), _T("FOLD_NAME"), _T("FILE_NAME"), _T("OID"), _T("TASK_NAME"),
					_T("PRODUCT_NO"), _T("BATCH"), _T("CODE_COUNT"), _T("PROJECT_NO"), _T("MODEL"),
					_T("PHASE"), _T("UP_DEPART"), _T("CHECK_LEADER"), _T("CHECK_USER"),_T("ARMY"),
					_T("CREATE_TIME"),_T("CREATE_USER"), _T("SEND_DATE"), _T("DOWNLOAD_DATE"), _T("FINISHED_TIME")};

				//��һ��
				pRoot1 = pRootType->FirstChildElement("ItemRoot1");		
				if (pRoot1)
				{
					
					for (pRoot1; pRoot1; pRoot1=pRoot1->NextSiblingElement("ItemRoot1"))
					{
						

							pos = 0;
							StBasTask *pTaskInfo = new StBasTask;
							pTaskInfo->Release();

							StBasTaskBaseInfo *pTaskBaseInfo = &pTaskInfo->stTaskBaseInfo;
							StBasProduct      *pProductInfo = &pTaskInfo->stProductInfo;
							StHrUpDepart      *pHrUpDepart = &pTaskInfo->stHrUpDepart;

							pTaskBaseInfo->nIndex = atoi(pRoot1->Attribute(szTaskOutFields[pos++]));
							strcpy(pTaskBaseInfo->szFoldName, pRoot1->Attribute(szTaskOutFields[pos++]));
							strcpy(pTaskBaseInfo->szFileName, pRoot1->Attribute(szTaskOutFields[pos++]));


							pTaskBaseInfo->nOid = atoi(pRoot1->Attribute(szTaskOutFields[pos++]));
							strcpy(pTaskBaseInfo->szTaskName, pRoot1->Attribute(szTaskOutFields[pos++]));
							strcpy(pProductInfo->szProductNo, pRoot1->Attribute(szTaskOutFields[pos++]));
							strcpy(pTaskBaseInfo->szBatch, pRoot1->Attribute(szTaskOutFields[pos++]));
							pTaskBaseInfo->nCodeNumber = atoi(pRoot1->Attribute(szTaskOutFields[pos++]));


							strcpy(pProductInfo->szProductName, pRoot1->Attribute(szTaskOutFields[pos++]));
							strcpy(pTaskBaseInfo->szModel, pRoot1->Attribute(szTaskOutFields[pos++]));
							strcpy(pTaskBaseInfo->szPhase, pRoot1->Attribute(szTaskOutFields[pos++]));


							strcpy(pHrUpDepart->szUpDepartName, pRoot1->Attribute(szTaskOutFields[pos++]));
							strcpy(pTaskBaseInfo->szCheckLeader, pRoot1->Attribute(szTaskOutFields[pos++]));
							strcpy(pTaskBaseInfo->szCheckUser, pRoot1->Attribute(szTaskOutFields[pos++]));
							pTaskBaseInfo->nArmyTest = atoi(pRoot1->Attribute(szTaskOutFields[pos++]));

							strcpy(pTaskBaseInfo->szCreateDate, pRoot1->Attribute(szTaskOutFields[pos++]));
							strcpy(pTaskBaseInfo->szCreateUser, pRoot1->Attribute(szTaskOutFields[pos++]));
							strcpy(pTaskBaseInfo->szSendDate, pRoot1->Attribute(szTaskOutFields[pos++]));
							strcpy(pTaskBaseInfo->szDownLoadDate, pRoot1->Attribute(szTaskOutFields[pos++]));
							strcpy(pTaskBaseInfo->szFinishDate, pRoot1->Attribute(szTaskOutFields[pos++]));
							



							pBatchTaskArray->push_back(pTaskInfo);
					}		

					
					
				}
			}

	}//if pRootInfo
	return 1;
}

//����ĳ����Ʒ ��� ģ������Ӧ�����ݣ��ݴ浽nDataArray//
int LoadOutTaskXmlAnalysis::AnalysisData(CArray<TestDataStr,TestDataStr> &nDataArray,
										 CArray<StBasAttachment,StBasAttachment> &nExclosureArray)
{
	char      szFileName[MAX_PATH] = {0,};
	CString strPath;
	sprintf(szFileName, _T("%s//%s//%s"),
		g_WorkPath, 
		PATH_XML_MODE_PAR_CFG, 
		MD_XML_FILE_TAB_OUT_INFO);

	//------------------------------------------------------------------------------//
	TiXmlDocument   doc( szFileName );
	TiXmlElement	* pRootInfo;
	if (!doc.LoadFile())
	{
		return 0;
	}
	pRootInfo = doc.RootElement();
	//------------------------------------------------------------------------------//

	TiXmlElement	*pRoot, *pRootType, *pRoot1;
	CString			strTemp, str;
	int             nRowNum = 0;
	int             nColNum = 0;
	int             nRowPos=0, nColPos=0;
	int             nCount=0;

	TestDataStr nData;


	if (pRootInfo)
	{
		//  ----------------------------------------------------------------------
		pRoot= pRootInfo->FirstChildElement(MD_XML_CFG_TAB_OUT_INFO);
		if (pRoot)
		{
			//2.1 �������
			pRootType = pRoot->FirstChildElement(MD_XML_ROOT_OUT_TEST_DATA);

			if (pRootType)
			{
				//1.
				strTemp = pRootType->Attribute(MD_XML_ATTR_COUNT_ROOT);
				nCount = atoi(strTemp.GetBuffer(0));

				//��һ��
				pRoot1 = pRootType->FirstChildElement(MD_XML_ATTR_ROOT_1);		
				if (pRoot1)
				{
					nDataArray.RemoveAll();
					for (pRoot1; pRoot1; pRoot1=pRoot1->NextSiblingElement(MD_XML_ATTR_ROOT_1))
					{

						memset(&nData,0,sizeof(TestDataStr));
						//�������
						//1.
						strTemp = pRoot1->Attribute("Index1");		//��������(���)///
						nData.Index = atoi(strTemp.GetBuffer(0));
						//2.
						strTemp = pRoot1->Attribute("NAME");		//���ݿ��ֶ���
						strcpy(nData.Name, strTemp.GetBuffer(0));
						//3.
						strTemp = pRoot1->Attribute("DESC");		//��������
						strcpy(nData.Desc, strTemp.GetBuffer(0));

						//4.
						strTemp = pRoot1->Attribute("DataType");		//��������
						nData.iDataType = atoi(strTemp.GetBuffer(0));


						//5.
						strTemp = pRoot1->Attribute("OutData");		//���Խ������
						strcpy(nData.Data, strTemp.GetBuffer(0));		
						//6.
						strTemp = pRoot1->Attribute("TestUsr");	//������Ա
						strcpy(nData.CheckUsr, strTemp.GetBuffer(0));
						//7.
						strTemp = pRoot1->Attribute("TestTime");	//����ʱ��
						strcpy(nData.CheckTime, strTemp.GetBuffer(0));
						nDataArray.Add(nData);

					}		
				}
			}


			StBasAttachment nExclosure;
			//2.2 ������Ϣ
			//---------------------------------------------------------------------------
			pRootType = pRoot->FirstChildElement(MD_XML_ROOT_OUT_APP_DATA);

			if (pRootType)
			{
				//1.
				strTemp = pRootType->Attribute(MD_XML_ATTR_COUNT_ROOT);
				nCount = atoi(strTemp.GetBuffer(0));

				//��һ��
				pRoot1 = pRootType->FirstChildElement(MD_XML_ATTR_ROOT_1);		
				if (pRoot1)
				{
					nExclosureArray.RemoveAll();
					for (pRoot1; pRoot1; pRoot1=pRoot1->NextSiblingElement(MD_XML_ATTR_ROOT_1))
					{

						//�������
						memset(&nExclosure,0,sizeof(StBasAttachment));
						//1.
						strTemp = pRoot1->Attribute(MD_XML_ST_APP_APPENDIX_TYPE);
						nExclosure.nDataType = atoi(strTemp.GetBuffer(0));
						//2.
						strTemp = pRoot1->Attribute(MD_XML_ST_APP_SRC_FILE_NAME);
						strcpy(nExclosure.Exclosure_OldName, strTemp.GetBuffer(0));
						//3.
						strTemp = pRoot1->Attribute(MD_XML_ST_APP_DES_FILE_NAME);
						strcpy(nExclosure.Exclosure_Name, strTemp.GetBuffer(0));
						//4.
						strTemp = pRoot1->Attribute(MD_XML_ST_APP_TAB_DATA_POS);
						nExclosure.nModeCellOrder = atoi(strTemp.GetBuffer(0));
						//5.
						strTemp = pRoot1->Attribute(MD_XML_ST_DATA_NAME);
						strcpy(nExclosure.ModeDesc, strTemp.GetBuffer(0));
						//6.
						strTemp = pRoot1->Attribute(MD_XML_ST_APP_UP_USR);
						strcpy(nExclosure.BUILDUSR, strTemp.GetBuffer(0));
						//7.
						strTemp = pRoot1->Attribute(MD_XML_ST_APP_UP_TIME);	
						strcpy(nExclosure.BUILDTime, strTemp.GetBuffer(0));
						nExclosureArray.Add(nExclosure);

					}		
				}
			}


		}//if pRoot

	}//if pRootInfo

	return 1;
}
