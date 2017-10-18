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

	strText.Format(_T("导出任务完毕!\n导出路径=%s"), szGetName);
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

	//导出任务流程//
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



//任务导出函数集合///
//1.导出用户信息//
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
				strErr.Format(_T("打开数据库日志文件失败，原因为: %s"), szMsg);
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


//2.导出模板信息//
BOOL CBatchExportTask::ExPortModeInfo()
{
	
	char szSQL[2048] = {0};
	//字段解释 分别是模板ID 模板的基本信息、模板的配置信息、模板的极值信息///
	sprintf(szSQL,_T("create table %s \
		(OID number(10)  PRIMARY KEY not null,\
		 MODE_INFOFILE BLOB,\
		 MODE_XMLFILE    BLOB)"),g_BasMode
					 );
	
	m_SqliteDb.execDML(szSQL);

	//为Sqlite创建极值表///
	/*memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("create table %s \
					 (MODE_ID VARCHAR2(20)  PRIMARY KEY not null,\
					 PROD_CODE VARCHAR2(100),\
					 HIS_XMLFILE    BLOB)"),g_AllTabName3[0]
	);

	m_SqliteDb.execDML(szSQL);*/

	//查找相关的模板//
	
	int i,nModeCount = 0;
	nModeCount = m_pStBasTaskInfo->pArryTaskMode.size();
	vector<StBasTaskMode *> *pTaskModeArry = &m_pStBasTaskInfo->pArryTaskMode;
	if(nModeCount>=1)
	{
		for(i = 0;i<nModeCount;i++)
		{
			//处理每个模板信息,共3种信息 模板的配置信息、模板基本信息、模板的极值信息//
			StBasTaskMode *pTaskMode = NULL;
			pTaskMode = pTaskModeArry->at(i);
			if(!CopyTaskMode(pTaskMode))
			{
				CString strText;
				strText.Format(_T("导出模板 \"%s\" 时出错"),pTaskMode->pModeInfo.szModeName);
				g_MainFram->m_wndOutput.InsertErrorText(strText);
			}
		}
	}else
	{
		return FALSE;
	}

	return TRUE;
}
//3.导出任务信息//
BOOL CBatchExportTask::ExPortTaskInfo()
{

	char szSQL[2048] = {0};
	sprintf(szSQL,_T("create table %s(\
					 OID        number(10)    PRIMARY KEY  not null,\
					 TASK_INFOFILE        BOLB)"),g_BasTask
	);

	m_SqliteDb.execDML(szSQL);

	m_LoadOutTask.SetXmlLoadOutTaskInfo(m_pStBasTaskInfo);
	
	//写入表中///
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
		strErr.Format(_T("打开数据库日志文件失败，原因为: %s"), szMsg);
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
//4.导出任务 产品编号//
BOOL CBatchExportTask::ExPortProdNumbelsInfo()
{
	char szSQL[512] = {0};
	//1.创建任务详情表//
	sprintf(szSQL,_T("create table TST_RESULT_BASE (\
					 OID       number(10)    PRIMARY KEY  not null,\
					 TST_RESULT_BASE_FILE  BLOB)")
					 );

	m_SqliteDb.execDML(szSQL);

	//2.创建数据存储表
	memset(szSQL,0,512);
	sprintf(szSQL,_T("create table TST_DATA (\
					 OID       number(10)    PRIMARY KEY  not null,\
					 TST_DATA_FILE  BLOB)"));

	m_SqliteDb.execDML(szSQL);

	//组建任务详情表 生成XML文件//

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

			//逐条创建数据存储表//
			memset(szSQL,0,512);
			sprintf(szSQL, "insert into TST_DATA(OID) values(%d)",pTstResultBase->nOid);
			m_SqliteDb.execDML(szSQL);
		}
	}

	m_LoadOutTask.SetXmlLoadOutTaskNumbelMode(&pArryTstResultBase);


	//写入表中///
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
		strErr.Format(_T("打开数据库日志文件失败，原因为: %s"), szMsg);
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

	//释放vector//
	int nSize = pArryTstResultBase.size();
	for (i = 0;i<nSize;i++)
	{
		delete pArryTstResultBase.at(i);
	}
	pArryTstResultBase.clear();
	return TRUE;
}
//5.导出模板数据表结构///
BOOL CBatchExportTask::ExPortModeTabStr(UINT nModeOid,CString strTabName)
{
	//检查表是否已经存在//
	BOOL nIs = FALSE;

	char szSQL[512] = {0};
	nIs = m_DMng.IsModeStrTabExists(nModeOid);
	
	if(nIs)//已经存在//
	{
		//创建Sqlite数据表结构//ModeDataTab0000000004
		//m_ShowTaskData.AutoBuildTabStruct(nTabName,&m_SqliteDb,0);
	}else//不存在//
	{
		//创建Oracle数据表结构//
		vector<StBasModeDesc> stModeDesArray;
		BOOL nError = FALSE;
		int i, nCount;
		CString strModeDescName = g_BasModeDesc;
		nError = AutoBuildTabStruct(strTabName,NULL,1, &stModeDesArray);
		//把表名 保存到相应数据表中//

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
				g_MainFram->m_wndOutput.InsertErrorText("保存模板表名称时出错!");
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
			//创建Sqlite数据表结构//ModeDataTab0000000004
			//m_ShowTaskData.AutoBuildTabStruct(nTabName,&m_SqliteDb,0);
		}
		
	}
	return TRUE;
}
//单独处理每个模板//
BOOL CBatchExportTask::CopyTaskMode(StBasTaskMode *pTaskMode)
{
	/*一个模板导出要做的事情*/
	//1.拷贝模板基本信息///
	//2.读取模板配置文件bolb类型的数据 存到Sqlite ///
	//3.将blob文件存储到本地//
	//5.生成极值文件//
	//4.读取本地文件 动态创建数据表结构//
		//检查 当前表结构Oracle中是否存在//
		//a.若不存在 创建Sqlite和Oracle//
		//b.若存在   创建Sqlite//


	//1.//
	UINT nModeOid = pTaskMode->nModeOid;
	char szSQL[2048] = {0};
	StBasMode nModeInfo;
	CString strText;
	memset(&nModeInfo,0,sizeof(StBasMode));
	if(m_DMng.GetModeDataOid(nModeOid,&nModeInfo))//获取最新的模板信息//
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


		//写入表中,模板的基本信息///
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
			strErr.Format(_T("打开数据库日志文件失败，原因为: %s"), szMsg);
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

		//更新任务模板表的模板属性//
		memset(pTaskMode->szModeName,0,sizeof(pTaskMode->szModeName));
		strcpy(pTaskMode->szModeName,nModeInfo.szModeName);
		pTaskMode->nModeType = nModeInfo.nModeType;
		pTaskMode->nModeRowvar = nModeInfo.nModeRowVar;
		/*if(!m_DMng.EditOldTaskMode(pTaskMode))
		{
			g_MainFram->m_wndOutput.InsertErrorText("更新任务模板表的模板属性时出错");
		}*/
		//3.保存到 任务模板表的 相应字段里//
		if(!m_DMng.UpdateTaskModeInfoFile(pTaskMode->nOid,strXmlFileInfo,nSize))
		{
			g_MainFram->m_wndOutput.InsertErrorText("保存模板详细信息时出错");
		}

		if(nModeInfo.pXmlFile == NULL || nModeInfo.nModeSize<=0)
		{
			strText.Format(_T("\"%s\" 模板数据为空!"),nModeInfo.szModeName);
			g_MainFram->m_wndOutput.InsertErrorText(strText);
		}else
		{
			memset(szSQL,0,2048);
			sprintf(szSQL, "update %s set MODE_INFOFILE=? where OID=%d",g_BasMode,nModeInfo.nOid);
			m_SqliteDb.SqliteWriteBolb(szSQL,strXmlFileInfo,nSize);
			if(!m_DMng.UpdateTaskModeXmlFile(pTaskMode->nOid,nModeInfo.pXmlFile,nModeInfo.nModeSize))
			{
				g_MainFram->m_wndOutput.InsertErrorText("保存任务模板配置信息是出错");
			}
		}
		
		delete strXmlFileInfo;

		//4.导出模板公式
		CString strFormulaFilePath;
		CString strAimDir;

		if(nModeInfo.nFormula)
		{
			strFormulaFilePath = BuildModeFormulaFilePath(g_WorkPath, &nModeInfo);
			strAimDir= BuildModeFormulaFilePath(m_LoadOutTask.m_szTaskOutPath.GetBuffer(0), &nModeInfo, 1);
			if(GetFileAttributes(strFormulaFilePath.GetBuffer(0)) == 0xffffffff)
			{
				strText.Format(_T("模板公式文件不存在!模板名称=%s 文件所在路径=%s"),nModeInfo.szModeName,
					strFormulaFilePath);
			}else
			{
				if (!CopyFile(strFormulaFilePath, strAimDir, 0))
				{
					strText.Format(_T("文件复制失败, 源文件:%s, 目标文件:%s"), 
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
		strErr.Format(_T("打开文件失败，原因为: %s"), szMsg);
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
	

	//生成极值文件 以模板为单位 字段 EXTREMUM_FILE///

	//m_ShowTaskData.CreateExclosureFile(m_CurTaskInfo,nModeID);

	//写入表中,产品模板的极值文件///
	/*char *strXmlFileInfo;

	strFilePath.Format("%s\\%s\\%s",
		g_WorkPath,PATH_XML_MODE_PAR_CFG,MD_XML_FILE_TAB_HIS_INFO);
	if(!file.Open(strFilePath, CFile::modeNoTruncate | CFile::modeRead, &e))
	{
		char szMsg[128] = {0};
		e.GetErrorMessage(szMsg, 128);

		CString strErr;
		strErr.Format(_T("打开数据库日志文件失败，原因为: %s"), szMsg);
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
		g_MainFram->m_wndOutput.InsertErrorText("生成数据表结构失败!");
	}
	nModeInfo.nInitTabSrt = 1;
	if(!m_DMng.EditOldMode(&nModeInfo))
	{
		g_MainFram->m_wndOutput.InsertErrorText("更新模板信息失败!");
	}
	nModeInfo.Release();
	return MStr;
}




BOOL CBatchExportTask::AutoBuildTabStruct(CString nModeTabName,CppSQLite3DB *pSqlite,int Flags,vector<StBasModeDesc> *pStModeDesArray)
{
	g_MainFram->m_ModeParMng.ClearParamInfo();

	//m_ModeXmlAnalysis.m_pParMng = &m_ModeParMng;
	//1.获取模板结构
	g_MainFram->m_ModeXmlAnalysis.GetXmlMdTabSrtInfo();
	g_MainFram->m_ModeXmlAnalysis.SetXmlMdTabHisInfo();
	//动态创建数据库表结构///
	int iRowNum = g_MainFram->m_ModeParMng.m_nDataCnt;

	StBasModeDesc nModeDesc;
	int nDateType = 0;

	//nModeID = "0000000001";
	//nModeID = _T("ModeDataTab")+nModeID;
	//更新模板的附加信息//
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
		sprintf(szSQL,_T("comment on column %s.OID is '数据主键ID'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);
		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.BELONG_MODEL is '产品型号'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);
		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.BELONG_MOMENT is '研制阶段'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);
		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.PRODUCT_OID is '产品OID'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);
		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.PRODUCT_NO is '产品代号'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);
		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.PRODUCT_NAME is '产品名称'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.PRODUCT_CODE is '产品编号'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.PICNUM_OID is '图号Oid'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.PICNUM_NO is '图号代号'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.PICNUM_NAME is '图号名称'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.TASK_OID is '所属任务ID'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);
		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.TASK_NAME is '任务名称'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.SEND_DATE is '下发时间'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.FINISH_DATE is '完成时间'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.IMPORT_DATE is '导入时间'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.Def_Edit_3 is '测试人'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.Def_Edit_4 is '检验'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.Def_Edit_5 is '军代表'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.Def_Edit_6 is '测试日期'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.BASE_OID is '任务基础表OID'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);
		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.ATTA_OID is '结构附件表OID'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		for (int i = 0;i<iRowNum;i++)
		{
			pTabData = &g_MainFram->m_ModeParMng.m_stTabData[i];
			memset(szSQL,0,512);
			sprintf(szSQL,_T("comment on column %s.%s is '%s'"),nModeTabName,pTabData->szDbColName,pTabData->szOutDataName);
			m_DMng.UpdateDataInfo(szSQL);
		}

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.DATA_XMLFILE is '采集数据文件'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);
	}

	delete []szSQL;
	return TRUE;
}