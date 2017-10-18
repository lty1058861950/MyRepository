#include "stdafx.h"
#include "BatchExportTask.h"

CBatchExportTask::CBatchExportTask(void)
{
	
	m_BatchTaskArray.clear();
}

CBatchExportTask::~CBatchExportTask(void)
{
	m_BatchTaskArray.clear();
}

BOOL CBatchExportTask::BatchSendTask(CString strDefFilePath)
{
	int i,nCount;
	CString strText, str;
	vector<CString> strErrorArray;
	StBasTask *pTaskInfo;
	
	CString	szGetName, str1, str2;
	nCount = m_BatchTaskArray.size();

	if(nCount > 0)
	{
		m_LoadOutTask.m_szDbPath = strDefFilePath; 

		szGetName.Format(_T("%s\\%s_%s"),strDefFilePath,g_LoginUsrInfo.szLoginName, GetDateTimeString2());
		if(GetFileAttributes(szGetName) == 0xFFFFFFFF)
		{
			CreateDirectory(szGetName,NULL);
		}
	}else
	{
		return FALSE;
	}

	for (i = 0;i<nCount;i++)
	{
		pTaskInfo = m_pStBasTaskInfo = m_BatchTaskArray.at(i);

		
		
		m_LoadOutTask.m_szTaskOutPath = szGetName;
		str1.Format("%s\\Task%02d", szGetName,i+1);
		if(GetFileAttributes(str1) == 0xFFFFFFFF)
		{
			CreateDirectory(str1,NULL);
		}

		str2.Format(_T("%s\\Task%02d.db"), str1, i+1);

		SingleSendTask(str2,strErrorArray);
	}
	m_LoadOutTask.SetBatchOutTask(szGetName,&g_LoginUsrInfo, &m_BatchTaskArray);

	strText.Format(_T("�����������!\n����·��=%s"), szGetName);
	strErrorArray.push_back(strText);

	strText=_T("");
	nCount = strErrorArray.size();
	for (i = 0;i<nCount;i++)
	{
		str.Format(_T("%d.%s\n"), i+1,strErrorArray.at(i));
		strText+=str;
	}
	strErrorArray.clear();
	AfxMessageBox(strText);
	return TRUE;
}

BOOL CBatchExportTask::SingleSendTask(CString szGetName, vector<CString> &strErrorArray)
{
	//CString strText;
	vector<CString> strTempArray;
	int i, nCount;
	m_pStBasTaskInfo->stTaskBaseInfo.nTaskStatus = Task_Runing;
	memset(m_pStBasTaskInfo->stTaskBaseInfo.szDownLoadDate, 0,sizeof(m_pStBasTaskInfo->stTaskBaseInfo.szDownLoadDate));
	strcpy(m_pStBasTaskInfo->stTaskBaseInfo.szDownLoadDate,GetDateTimeString());

	//������������//
	remove(szGetName.GetBuffer(0));
	m_LoadOutTask.m_szDbPath = szGetName; 
	m_SqliteDb.open(szGetName.GetBuffer(0));

	
	ExPortUsrInfo();
	ExPortModeInfo();
	ExPortTaskInfo();
	ExPortProdNumbelsInfo();

	m_SqliteDb.close();


	ModifyTheTask(m_pStBasTaskInfo,strTempArray);
	//g_MainFram->m_wndOutput.InsertErrorArrayText(strTempArray);
	nCount = strTempArray.size();
	for (i = 0;i<nCount;i++)
	{
		strErrorArray.push_back(strTempArray.at(i));
	}
	strTempArray.clear();
	return TRUE;
}



//���񵼳���������///
//1.�����û���Ϣ//
BOOL CBatchExportTask::ExPortUsrInfo()
{
	char szSQL[2048] = {0};
	sprintf(szSQL,_T("create table %s\
					 (OID          number(10)    PRIMARY KEY  not null,\
					  USER_XMLFILE     BOLB)"),
					 g_HrUser);
	m_SqliteDb.execDML(szSQL);
	

	vector<StHrUser *> nUserArry;
	if(m_DMng.GetAllUserToPad(&nUserArry))
	{
		int nCount = nUserArry.size();
		for(int i = 0;i<nCount;i++)
		{
			StHrUser *pUserInfo = NULL;
			pUserInfo = nUserArry.at(i);
			if(pUserInfo == NULL)
			{
				continue;
			}


			if(strcmp(pUserInfo->szLoginName, g_Admin) == 0)
			{
				delete pUserInfo;
				continue;
			}

			m_LoadOutTask.SetXmlLoadOutUsrInfo(pUserInfo);

			CStdioFile file;
			CFileException e;
			char strFilePath[256] = {0};
			char *strXmlFileInfo;

			m_LoadOutTask.GetCurModeXmlFileName(File_Xml_LoadOut_UsrInfo,strFilePath);
			if(!file.Open(strFilePath, CFile::modeNoTruncate | CFile::modeRead, &e))
			{
				char szMsg[128] = {0};
				e.GetErrorMessage(szMsg, 128);

				CString strErr;
				strErr.Format(_T("�����ݿ���־�ļ�ʧ�ܣ�ԭ��Ϊ: %s"), szMsg);
				AfxMessageBox(strErr);
				return FALSE;
			}
			int nSize = file.GetLength();
			strXmlFileInfo = new char[nSize+1];
			memset(strXmlFileInfo,0,nSize+1);

			file.Read((void*)strXmlFileInfo,nSize);
			file.Close();
			memset(szSQL,0,2048);
			sprintf(szSQL, "insert into %s(OID,USER_XMLFILE) values(%d,?)",g_HrUser,pUserInfo->nOid);
			m_SqliteDb.SqliteWriteBolb(szSQL,strXmlFileInfo,nSize);

			delete strXmlFileInfo;
			delete pUserInfo;
		}
		nUserArry.clear();

	}else
	{
		return FALSE;
	}
	
	return TRUE;
}


//2.����ģ����Ϣ//
BOOL CBatchExportTask::ExPortModeInfo()
{
	
	char szSQL[2048] = {0};
	//�ֶν��� �ֱ���ģ��ID ģ��Ļ�����Ϣ��ģ���������Ϣ��ģ��ļ�ֵ��Ϣ///
	sprintf(szSQL,_T("create table %s \
		(OID number(10)  PRIMARY KEY not null,\
		 MODE_INFOFILE BLOB,\
		 MODE_XMLFILE    BLOB)"),g_BasMode
					 );
	
	m_SqliteDb.execDML(szSQL);

	//ΪSqlite������ֵ��///
	/*memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("create table %s \
					 (MODE_ID VARCHAR2(20)  PRIMARY KEY not null,\
					 PROD_CODE VARCHAR2(100),\
					 HIS_XMLFILE    BLOB)"),g_AllTabName3[0]
	);

	m_SqliteDb.execDML(szSQL);*/

	//������ص�ģ��//
	
	int i,nModeCount = 0;
	nModeCount = m_pStBasTaskInfo->pArryTaskMode.size();
	vector<StBasTaskMode *> *pTaskModeArry = &m_pStBasTaskInfo->pArryTaskMode;
	if(nModeCount>=1)
	{
		for(i = 0;i<nModeCount;i++)
		{
			//����ÿ��ģ����Ϣ,��3����Ϣ ģ���������Ϣ��ģ�������Ϣ��ģ��ļ�ֵ��Ϣ//
			StBasTaskMode *pTaskMode = NULL;
			pTaskMode = pTaskModeArry->at(i);
			if(!CopyTaskMode(pTaskMode))
			{
				CString strText;
				strText.Format(_T("����ģ�� \"%s\" ʱ����"),pTaskMode->pModeInfo.szModeName);
				g_MainFram->m_wndOutput.InsertErrorText(strText);
			}
		}
	}else
	{
		return FALSE;
	}

	return TRUE;
}
//3.����������Ϣ//
BOOL CBatchExportTask::ExPortTaskInfo()
{

	char szSQL[2048] = {0};
	sprintf(szSQL,_T("create table %s(\
					 OID        number(10)    PRIMARY KEY  not null,\
					 TASK_INFOFILE        BOLB)"),g_BasTask
	);

	m_SqliteDb.execDML(szSQL);

	m_LoadOutTask.SetXmlLoadOutTaskInfo(m_pStBasTaskInfo);
	
	//д�����///
	CStdioFile file;
	CFileException e;
	char strFilePath[256] = {0};
	char *strXmlFileInfo;
	int nLen;

	m_LoadOutTask.GetCurModeXmlFileName(File_Xml_LoadOut_TaskInfo,strFilePath);
	if(!file.Open(strFilePath, CFile::modeNoTruncate | CFile::modeRead, &e))
	{
		char szMsg[128] = {0};
		e.GetErrorMessage(szMsg, 128);

		CString strErr;
		strErr.Format(_T("�����ݿ���־�ļ�ʧ�ܣ�ԭ��Ϊ: %s"), szMsg);
		AfxMessageBox(strErr);
		return FALSE;
	}
	nLen = file.GetLength();
	strXmlFileInfo = new char[nLen+1];
	memset(strXmlFileInfo,0,nLen+1);

	file.Read((void*)strXmlFileInfo,nLen);
	file.Close();
	memset(szSQL,0,2048);
	sprintf(szSQL, "insert into %s(OID,TASK_INFOFILE) values(%d,?)",g_BasTask,m_pStBasTaskInfo->stTaskBaseInfo.nOid);
	m_SqliteDb.SqliteWriteBolb(szSQL,strXmlFileInfo,nLen);
	delete strXmlFileInfo;
	return TRUE;
}
//4.�������� ��Ʒ���//
BOOL CBatchExportTask::ExPortProdNumbelsInfo()
{
	char szSQL[512] = {0};
	//1.�������������//
	sprintf(szSQL,_T("create table TST_RESULT_BASE (\
					 OID       number(10)    PRIMARY KEY  not null,\
					 TST_RESULT_BASE_FILE  BLOB)")
					 );

	m_SqliteDb.execDML(szSQL);

	//2.�������ݴ洢��
	memset(szSQL,0,512);
	sprintf(szSQL,_T("create table TST_DATA (\
					 OID       number(10)    PRIMARY KEY  not null,\
					 TST_DATA_FILE  BLOB)"));

	m_SqliteDb.execDML(szSQL);

	//�齨��������� ����XML�ļ�//

	vector<StTstResultAtta *> pArryTstResultBase;
	int nCodeCount,nModeCount,nPicNumCount;
	nCodeCount = m_pStBasTaskInfo->pArryTaskCode.size();
	nModeCount = m_pStBasTaskInfo->pArryTaskMode.size();
	nPicNumCount = m_pStBasTaskInfo->pArryTaskPicNum.size();

	StBasTaskBaseInfo   *pTaskBaseInfo = &m_pStBasTaskInfo->stTaskBaseInfo;
	StBasProduct        *pProductInfo = &m_pStBasTaskInfo->stProductInfo;
	StHrUpDepart        *pUpDepartInfo = &m_pStBasTaskInfo->stHrUpDepart;

	vector<StBasTaskCode *> *pArryTaskCode = &m_pStBasTaskInfo->pArryTaskCode;
	vector<StBasTaskMode *> *pArryTaskMode = &m_pStBasTaskInfo->pArryTaskMode;
	vector<StBasTaskPicNum *> *pArryTaskPicNum = &m_pStBasTaskInfo->pArryTaskPicNum;

	int i,j;
	int nOid = 1;
	for(i = 0;i<nCodeCount;i++)
	{
		StBasTaskCode *pTaskCode = NULL;
		pTaskCode = pArryTaskCode->at(i);
		for(j = 0;j<nModeCount;j++)
		{

			StTstResultAtta *pTstResultBase = new StTstResultAtta;
			memset(pTstResultBase,0,sizeof(StTstResultAtta));
			StBasTaskMode *pTaskMode = NULL;
			pTaskMode = pArryTaskMode->at(j);
			pTstResultBase->nOid = nOid++;
			pTstResultBase->nTaskOid = pTaskBaseInfo->nOid;
			strcpy(pTstResultBase->szProductName, pProductInfo->szProductName);
			strcpy(pTstResultBase->szProductNo, pProductInfo->szProductNo);
			pTstResultBase->nProductOid = pProductInfo->nOid;
			strcpy(pTstResultBase->szBatch, pTaskBaseInfo->szBatch);
			
			
			strcpy(pTstResultBase->szModel, pTaskBaseInfo->szModel);
			strcpy(pTstResultBase->szPhase, pTaskBaseInfo->szPhase);
			
			strcpy(pTstResultBase->szProductCode, pTaskCode->szCodeName);
			pTstResultBase->nDianshiTest = pTaskCode->nDianshiTest;

			pTstResultBase->nModeOid = pTaskMode->nModeOid;
			strcpy(pTstResultBase->szModeName, pTaskMode->szModeName);
			pTstResultBase->nModeType = pTaskMode->nModeType;
			pTstResultBase->nModeRowVar = pTaskMode->nModeRowvar;
			pTstResultBase->nFormula = pTaskMode->nFormula;
			
			
			pTstResultBase->nPicNumCount = nPicNumCount;
			strcpy(pTstResultBase->szCheckUser, pTaskBaseInfo->szCheckUser);

			pArryTstResultBase.push_back(pTstResultBase);

			//�����������ݴ洢��//
			memset(szSQL,0,512);
			sprintf(szSQL, "insert into TST_DATA(OID) values(%d)",pTstResultBase->nOid);
			m_SqliteDb.execDML(szSQL);
		}
	}

	m_LoadOutTask.SetXmlLoadOutTaskNumbelMode(&pArryTstResultBase);


	//д�����///
	CStdioFile file;
	CFileException e;
	char strFilePath[256] = {0};
	char *strXmlFileInfo;
	int nLen;

	m_LoadOutTask.GetCurModeXmlFileName(File_xml_LoadOut_TaskNumbelMode,strFilePath);
	if(!file.Open(strFilePath, CFile::modeNoTruncate | CFile::modeRead, &e))
	{
		char szMsg[128] = {0};
		e.GetErrorMessage(szMsg, 128);

		CString strErr;
		strErr.Format(_T("�����ݿ���־�ļ�ʧ�ܣ�ԭ��Ϊ: %s"), szMsg);
		AfxMessageBox(strErr);
		return FALSE;
	}
	nLen = file.GetLength();
	strXmlFileInfo = new char[nLen+1];
	memset(strXmlFileInfo,0,nLen+1);

	file.Read((void*)strXmlFileInfo,nLen);
	file.Close();
	memset(szSQL,0,512);
	sprintf(szSQL, "insert into TST_RESULT_BASE(OID,TST_RESULT_BASE_FILE) values(%d,?)",1);
	m_SqliteDb.SqliteWriteBolb(szSQL,strXmlFileInfo,nLen);
	delete strXmlFileInfo;

	//�ͷ�vector//
	int nSize = pArryTstResultBase.size();
	for (i = 0;i<nSize;i++)
	{
		delete pArryTstResultBase.at(i);
	}
	pArryTstResultBase.clear();
	return TRUE;
}
//5.����ģ�����ݱ�ṹ///
BOOL CBatchExportTask::ExPortModeTabStr(UINT nModeOid,CString strTabName)
{
	//�����Ƿ��Ѿ�����//
	BOOL nIs = FALSE;

	char szSQL[512] = {0};
	nIs = m_DMng.IsModeStrTabExists(nModeOid);
	
	if(nIs)//�Ѿ�����//
	{
		//����Sqlite���ݱ�ṹ//ModeDataTab0000000004
		//m_ShowTaskData.AutoBuildTabStruct(nTabName,&m_SqliteDb,0);
	}else//������//
	{
		//����Oracle���ݱ�ṹ//
		vector<StBasModeDesc> stModeDesArray;
		BOOL nError = FALSE;
		int i, nCount;
		CString strModeDescName = g_BasModeDesc;
		nError = AutoBuildTabStruct(strTabName,NULL,1, &stModeDesArray);
		//�ѱ��� ���浽��Ӧ���ݱ���//

		if(nError)
		{
			StBasModeSave nModeSave;
			memset(&nModeSave,0,sizeof(StBasModeSave));
			nModeSave.nModeOid = nModeOid;
			strcpy(nModeSave.szTabName,strTabName);
			strcpy(nModeSave.szCreateTime,GetDateTimeString());
			strcpy(nModeSave.szCreateUser,g_LoginUsrInfo.szLoginName);

			if(!m_DMng.AddNewModeSave(&nModeSave))
			{
				g_MainFram->m_wndOutput.InsertErrorText("����ģ�������ʱ����!");
			}
			nCount = stModeDesArray.size();
			
			m_DMng.DelModeAllField(nModeOid);
			StBasModeDesc  *pModeDesc;
			for (i = 0;i<nCount;i++)
			{
				pModeDesc = &stModeDesArray.at(i);
				pModeDesc->nOid= m_DMng.GetTabLeastOid(strModeDescName.GetBuffer(0));
				pModeDesc->nModeOid = nModeOid;
				pModeDesc->nModeSaveOid = nModeSave.nOid;
				strcpy(pModeDesc->szCreateTime,GetDateTimeString());
				strcpy(pModeDesc->szCreateUser,g_LoginUsrInfo.szLoginName);

				if(m_DMng.AddNewModeDesc(pModeDesc))
				{

				}
				
			}
			//����Sqlite���ݱ�ṹ//ModeDataTab0000000004
			//m_ShowTaskData.AutoBuildTabStruct(nTabName,&m_SqliteDb,0);
		}
		
	}
	return TRUE;
}
//��������ÿ��ģ��//
BOOL CBatchExportTask::CopyTaskMode(StBasTaskMode *pTaskMode)
{
	/*һ��ģ�嵼��Ҫ��������*/
	//1.����ģ�������Ϣ///
	//2.��ȡģ�������ļ�bolb���͵����� �浽Sqlite ///
	//3.��blob�ļ��洢������//
	//5.���ɼ�ֵ�ļ�//
	//4.��ȡ�����ļ� ��̬�������ݱ�ṹ//
		//��� ��ǰ��ṹOracle���Ƿ����//
		//a.�������� ����Sqlite��Oracle//
		//b.������   ����Sqlite//


	//1.//
	UINT nModeOid = pTaskMode->nModeOid;
	char szSQL[2048] = {0};
	StBasMode nModeInfo;
	CString strText;
	memset(&nModeInfo,0,sizeof(StBasMode));
	if(m_DMng.GetModeDataOid(nModeOid,&nModeInfo))//��ȡ���µ�ģ����Ϣ//
	{
		
		memset(szSQL,0,2048);
		sprintf(szSQL, "insert into %s(OID) values (%d)",
					   g_BasMode,nModeInfo.nOid);
		m_SqliteDb.execDML(szSQL);


		/*memset(szSQL,0,2048);
		sprintf(szSQL, "insert into %s(%s) values ('%s')",
			g_AllTabName3[0],g_ModeTab[0],nStrArry.GetAt(i*nLen));
		m_SqliteDb.execDML(szSQL);*/

		m_LoadOutTask.SetXmlLoadOutModeInfo(&nModeInfo);


		//д�����,ģ��Ļ�����Ϣ///
		CStdioFile file;
		CFileException e;
		char strFilePath[256] = {0};
		char *strXmlFileInfo;

		m_LoadOutTask.GetCurModeXmlFileName(File_Xml_LoadOut_ModeInfo,strFilePath);
		if(!file.Open(strFilePath, CFile::modeNoTruncate | CFile::modeRead, &e))
		{
			char szMsg[128] = {0};
			e.GetErrorMessage(szMsg, 128);

			CString strErr;
			strErr.Format(_T("�����ݿ���־�ļ�ʧ�ܣ�ԭ��Ϊ: %s"), szMsg);
			AfxMessageBox(strErr);
			return FALSE;
		}
		int nSize = file.GetLength();
		strXmlFileInfo = new char[nSize+1];
		memset(strXmlFileInfo,0,nSize+1);

		file.Read((void*)strXmlFileInfo,nSize);
		file.Close();
		
		

		//2.//

		memset(szSQL,0,2048);
		sprintf(szSQL,"update %s set MODE_XMLFILE=? where OID=%d",g_BasMode,nModeInfo.nOid);
		m_SqliteDb.SqliteWriteBolb(szSQL,nModeInfo.pXmlFile,nModeInfo.nModeSize);

		//��������ģ����ģ������//
		memset(pTaskMode->szModeName,0,sizeof(pTaskMode->szModeName));
		strcpy(pTaskMode->szModeName,nModeInfo.szModeName);
		pTaskMode->nModeType = nModeInfo.nModeType;
		pTaskMode->nModeRowvar = nModeInfo.nModeRowVar;
		/*if(!m_DMng.EditOldTaskMode(pTaskMode))
		{
			g_MainFram->m_wndOutput.InsertErrorText("��������ģ����ģ������ʱ����");
		}*/
		//3.���浽 ����ģ���� ��Ӧ�ֶ���//
		if(!m_DMng.UpdateTaskModeInfoFile(pTaskMode->nOid,strXmlFileInfo,nSize))
		{
			g_MainFram->m_wndOutput.InsertErrorText("����ģ����ϸ��Ϣʱ����");
		}

		if(nModeInfo.pXmlFile == NULL || nModeInfo.nModeSize<=0)
		{
			strText.Format(_T("\"%s\" ģ������Ϊ��!"),nModeInfo.szModeName);
			g_MainFram->m_wndOutput.InsertErrorText(strText);
		}else
		{
			memset(szSQL,0,2048);
			sprintf(szSQL, "update %s set MODE_INFOFILE=? where OID=%d",g_BasMode,nModeInfo.nOid);
			m_SqliteDb.SqliteWriteBolb(szSQL,strXmlFileInfo,nSize);
			if(!m_DMng.UpdateTaskModeXmlFile(pTaskMode->nOid,nModeInfo.pXmlFile,nModeInfo.nModeSize))
			{
				g_MainFram->m_wndOutput.InsertErrorText("��������ģ��������Ϣ�ǳ���");
			}
		}
		
		delete strXmlFileInfo;

		//4.����ģ�幫ʽ
		CString strFormulaFilePath;
		CString strAimDir;

		if(nModeInfo.nFormula)
		{
			strFormulaFilePath = BuildModeFormulaFilePath(g_WorkPath, &nModeInfo);
			strAimDir= BuildModeFormulaFilePath(m_LoadOutTask.m_szTaskOutPath.GetBuffer(0), &nModeInfo, 1);
			if(GetFileAttributes(strFormulaFilePath.GetBuffer(0)) == 0xffffffff)
			{
				strText.Format(_T("ģ�幫ʽ�ļ�������!ģ������=%s �ļ�����·��=%s"),nModeInfo.szModeName,
					strFormulaFilePath);
			}else
			{
				if (!CopyFile(strFormulaFilePath, strAimDir, 0))
				{
					strText.Format(_T("�ļ�����ʧ��, Դ�ļ�:%s, Ŀ���ļ�:%s"), 
						strFormulaFilePath,
						strAimDir);
					AfxMessageBox(strText);
					return FALSE;
				}
			}
		}
		
		

	}else
	{
		return FALSE;
	}


	
	
	//3.///
	CString strFilePath;
	CStdioFile file;
	CFileException e;
	strFilePath.Format("%s\\%s\\%s",
		g_WorkPath,PATH_XML_MODE_PAR_CFG,MD_XML_FILE_TAB_SRT_INFO);
	remove(strFilePath);
	if(!file.Open(strFilePath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite, &e))
	{
		char szMsg[128] = {0};
		e.GetErrorMessage(szMsg, 128);

		CString strErr;
		strErr.Format(_T("���ļ�ʧ�ܣ�ԭ��Ϊ: %s"), szMsg);
		AfxMessageBox(strErr);
		return FALSE;
	}
	if(nModeInfo.pXmlFile == NULL || nModeInfo.nModeSize == 0)
	{

	}else
	{
		file.WriteString(nModeInfo.pXmlFile);
	}
	
	file.Close();
	

	//���ɼ�ֵ�ļ� ��ģ��Ϊ��λ �ֶ� EXTREMUM_FILE///

	//m_ShowTaskData.CreateExclosureFile(m_CurTaskInfo,nModeID);

	//д�����,��Ʒģ��ļ�ֵ�ļ�///
	/*char *strXmlFileInfo;

	strFilePath.Format("%s\\%s\\%s",
		g_WorkPath,PATH_XML_MODE_PAR_CFG,MD_XML_FILE_TAB_HIS_INFO);
	if(!file.Open(strFilePath, CFile::modeNoTruncate | CFile::modeRead, &e))
	{
		char szMsg[128] = {0};
		e.GetErrorMessage(szMsg, 128);

		CString strErr;
		strErr.Format(_T("�����ݿ���־�ļ�ʧ�ܣ�ԭ��Ϊ: %s"), szMsg);
		AfxMessageBox(strErr);
		return FALSE;
	}
	int nSize = file.GetLength();
	strXmlFileInfo = new char[nSize+1];
	memset(strXmlFileInfo,0,nSize+1);

	file.Read((void*)strXmlFileInfo,nSize);
	file.Close();*/

	

	/*memset(szSQL,0,2048);
	sprintf(szSQL, "update %s set PROD_CODE='%s',HIS_XMLFILE=? where %s='%s'",
		g_AllTabName3[0],m_CurTaskInfo.ProdID,g_ModeTab[0],nModeInfo.ModeID);
	m_SqliteDb.SqliteWriteBolb(szSQL,strXmlFileInfo,nSize);
	delete strXmlFileInfo;*/

	//////
	strText.Format(_T("%s%.4d_%.4d"),g_TstData,nModeInfo.nGroupOid,nModeInfo.nOid);
	//4.//
	BOOL MStr = ExPortModeTabStr(nModeInfo.nOid,strText);
	if(!MStr)
	{
		g_MainFram->m_wndOutput.InsertErrorText("�������ݱ�ṹʧ��!");
	}
	nModeInfo.nInitTabSrt = 1;
	if(!m_DMng.EditOldMode(&nModeInfo))
	{
		g_MainFram->m_wndOutput.InsertErrorText("����ģ����Ϣʧ��!");
	}
	nModeInfo.Release();
	return MStr;
}




BOOL CBatchExportTask::AutoBuildTabStruct(CString nModeTabName,CppSQLite3DB *pSqlite,int Flags,vector<StBasModeDesc> *pStModeDesArray)
{
	g_MainFram->m_ModeParMng.ClearParamInfo();

	//m_ModeXmlAnalysis.m_pParMng = &m_ModeParMng;
	//1.��ȡģ��ṹ
	g_MainFram->m_ModeXmlAnalysis.GetXmlMdTabSrtInfo();
	g_MainFram->m_ModeXmlAnalysis.SetXmlMdTabHisInfo();
	//��̬�������ݿ��ṹ///
	int iRowNum = g_MainFram->m_ModeParMng.m_nDataCnt;

	StBasModeDesc nModeDesc;
	int nDateType = 0;

	//nModeID = "0000000001";
	//nModeID = _T("ModeDataTab")+nModeID;
	//����ģ��ĸ�����Ϣ//
	CString str,strText = "";
	str.Format(_T("%d"),iRowNum);
	//AfxMessageBox(str);
	StTabData    *pTabData = NULL;

	for (int i=0; i<iRowNum; i++)
	{
		memset(&nModeDesc, 0,sizeof(StBasModeDesc));
		pTabData = &g_MainFram->m_ModeParMng.m_stTabData[i];

		if(pTabData->iDataType == datatype_string)
		{
			strcpy(nModeDesc.szFieldName, pTabData->szDbColName);
			strcpy(nModeDesc.szDescxx, pTabData->szOutDataName);
			nModeDesc.nDateType = pTabData->iDataType;

			pStModeDesArray->push_back(nModeDesc);
			str.Format(_T("%s VARCHAR2(100),"),pTabData->szDbColName);
		}else if(pTabData->iDataType == datatype_num)
		{
			strcpy(nModeDesc.szFieldName, pTabData->szDbColName);
			strcpy(nModeDesc.szDescxx, pTabData->szOutDataName);
			nModeDesc.nDateType = pTabData->iDataType;

			pStModeDesArray->push_back(nModeDesc);
			str.Format(_T("%s NUMBER,"),pTabData->szDbColName);
		}else if(pTabData->iDataType == datatype_caluate)
		{
			strcpy(nModeDesc.szFieldName, pTabData->szDbColName);
			strcpy(nModeDesc.szDescxx, pTabData->szOutDataName);
			nModeDesc.nDateType = pTabData->iDataType;

			pStModeDesArray->push_back(nModeDesc);

			str.Format(_T("%s NUMBER,"),pTabData->szDbColName);
		}
		

		strText+=str;
	}

	char*szSQL = new char[2048+50*iRowNum];
	memset(szSQL,0,2048+50*iRowNum);
	sprintf(szSQL,_T("create table %s (\
					 OID            NUMBER(10) PRIMARY KEY not null,\
					 BELONG_MODEL   VARCHAR2(100),\
					 BELONG_MOMENT  VARCHAR2(100),\
					 PRODUCT_OID    NUMBER(10),\
					 PRODUCT_NO     VARCHAR2(100),\
					 PRODUCT_NAME   VARCHAR2(100),\
					 PRODUCT_CODE	VARCHAR2(100),\
					 PICNUM_OID     NUMBER(10),\
					 PICNUM_NO      VARCHAR2(100),\
					 PICNUM_NAME    VARCHAR2(100),\
					 TASK_OID	    NUMBER(10),\
					 TASK_NAME      VARCHAR2(100),\
					 SEND_DATE      DATE,\
					 FINISH_DATE    DATE,\
					 IMPORT_DATE    DATE,\
					 Def_Edit_3     VARCHAR2(100),\
					 Def_Edit_4     VARCHAR2(100),\
					 Def_Edit_5     VARCHAR2(100),\
					 Def_Edit_6     VARCHAR2(100),\
					 BASE_OID       NUMBER(10),\
					 ATTA_OID       NUMBER(10),\
					 %s\
					 DATA_XMLFILE   BLOB)"),nModeTabName,strText);
	if(Flags)
	{
		m_DMng.UpdateDataInfo(szSQL);
	}else
	{
		pSqlite->execDML(szSQL);
	}

	delete []szSQL;

	szSQL = new char[512];

	if(Flags)
	{

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.OID is '��������ID'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);
		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.BELONG_MODEL is '��Ʒ�ͺ�'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);
		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.BELONG_MOMENT is '���ƽ׶�'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);
		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.PRODUCT_OID is '��ƷOID'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);
		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.PRODUCT_NO is '��Ʒ����'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);
		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.PRODUCT_NAME is '��Ʒ����'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.PRODUCT_CODE is '��Ʒ���'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.PICNUM_OID is 'ͼ��Oid'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.PICNUM_NO is 'ͼ�Ŵ���'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.PICNUM_NAME is 'ͼ������'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.TASK_OID is '��������ID'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);
		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.TASK_NAME is '��������'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.SEND_DATE is '�·�ʱ��'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.FINISH_DATE is '���ʱ��'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.IMPORT_DATE is '����ʱ��'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.Def_Edit_3 is '������'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.Def_Edit_4 is '����'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.Def_Edit_5 is '������'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.Def_Edit_6 is '��������'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.BASE_OID is '���������OID'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);
		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.ATTA_OID is '�ṹ������OID'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		for (int i = 0;i<iRowNum;i++)
		{
			pTabData = &g_MainFram->m_ModeParMng.m_stTabData[i];
			memset(szSQL,0,512);
			sprintf(szSQL,_T("comment on column %s.%s is '%s'"),nModeTabName,pTabData->szDbColName,pTabData->szOutDataName);
			m_DMng.UpdateDataInfo(szSQL);
		}

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.DATA_XMLFILE is '�ɼ������ļ�'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);
	}

	delete []szSQL;
	return TRUE;
}