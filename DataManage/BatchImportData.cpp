#include "stdafx.h"
#include "BatchImportData.h"

CBatchImportData::CBatchImportData(void)
{
}

CBatchImportData::~CBatchImportData(void)
{
}


BOOL CBatchImportData::BatchTaskDataImport()
{
	int i, nCount;
	CString strPath;
	vector<CString> strErrorArray;
	nCount = m_BatchTaskDataArray.size();
	for (i = 0;i<nCount;i++)
	{
		 m_pStBaseInfo = m_BatchTaskDataArray.at(i);
		 strPath = m_TaskDataFilePath.at(i);

		SingleTaskDataImport(strPath,strErrorArray);
	}
	return TRUE;
}
BOOL CBatchImportData::SingleTaskDataImport(CString strDataFilePath,vector<CString> &strErrorArray)//单个进行处理//
{
	int ret = 0;
	int i, nCount;
	vector<CString> strTempArray;
	//数据导入流程//
	m_LoadOutTask.ClearAllData();//清空上一次数据//
	m_LoadOutTask.m_szDbPath = strDataFilePath;///
	

	//1.任务信息表导入
	ret = ImPortTaskInfo();
	if(!ret)
	{
		return FALSE;
	}

	StBasTask *pTaskInfo = &m_LoadOutTask.m_CurTaskInfo;
	pTaskInfo->stTaskBaseInfo.nTaskStatus = Task_Finish;
	memset(pTaskInfo->stTaskBaseInfo.szFinishDate, 0,sizeof(pTaskInfo->stTaskBaseInfo.szFinishDate));
	strcpy(pTaskInfo->stTaskBaseInfo.szFinishDate, m_pStBaseInfo->stTaskBaseInfo.szFinishDate);

	//2.数据表导入
	ret = ImPortTestData();
	if(!ret)
	{
		return FALSE;
	}

	

	
	//开始更新导出的状态//
	ModifyTheTask(pTaskInfo,strTempArray);
	//g_MainFram->m_wndOutput.InsertErrorArrayText(strTempArray);
	
	nCount = strTempArray.size();
	for (i = 0;i<nCount;i++)
	{
		strErrorArray.push_back(strTempArray.at(i));
	}
	strTempArray.clear();
	return TRUE;
}

BOOL CBatchImportData::ImPortTestData()
{
	m_LoadOutTask.GetAllTaskNumbelMode();//所有任务项//
	m_LoadOutTask.GetAllModeInfo();//所有模板信息//

	
	int nCount = m_LoadOutTask.m_ArrayTaskNumbelMode.size();
	//任务基础表是否存在不存在就自动创建//
	if(!IsTstResultExists(g_CurSelDepart.nOid))
	{
		return FALSE;
	}

	//任务基础表插入一条新数据//
	StTstResultBase nTstResultBase;
	if(!AddTstResultBase(&nTstResultBase))
	{
		return FALSE;
	}
	for (int i = 0;i<nCount;i++)
	{
		//遍历数据表，找到对应的模板 产品编号，任务项一条一条的导入///
		m_LoadOutTask.m_pCurTaskNumbelMode=m_LoadOutTask.m_ArrayTaskNumbelMode.at(i);
		m_LoadOutTask.GetModeInfoAndXmlFile(m_LoadOutTask.m_pCurTaskNumbelMode->nModeOid,
			m_LoadOutTask.m_pCurTaskNumbelMode->szModeName);//切换到当前模板//
		m_LoadOutTask.GetTestDataFromDb();//获取当前任务项的数据//


		//ztadd for V1.1.0_2017-04-05
		//数据解密处理
		DoDecFromTestDataXmlFile(  );    //执行解密_对测试结果数据XML文件
		


		//任务结果附件表插入一条新数据//
		m_LoadOutTask.m_pCurTaskNumbelMode->nBaseOid = nTstResultBase.nOid;
		strcpy(m_LoadOutTask.m_pCurTaskNumbelMode->szSendDate,nTstResultBase.szSendDate);
		strcpy(m_LoadOutTask.m_pCurTaskNumbelMode->szImportDate,nTstResultBase.szImportDate);
		strcpy(m_LoadOutTask.m_pCurTaskNumbelMode->szTaskName,nTstResultBase.szTaskName);
		AddTstResultData(m_LoadOutTask.m_pCurTaskNumbelMode,g_CurSelDepart.nOid);
		AnalysisData();//解析当前任务数据，并存储到Oracle数据库中//

	}
	
	return TRUE;
}
//更新任务的基本信息//
BOOL CBatchImportData::ImPortTaskInfo()
{
	//导入数据流程//
	m_LoadOutTask.GetCurTaskInfo();//当前任务的信息//

	if(m_LoadOutTask.m_CurTaskInfo.stTaskBaseInfo.nOid != m_pStBaseInfo->stTaskBaseInfo.nOid)
	{
		CString strText;
		strText.Format("数据导入检查到:\n当前选中的任务(%s)与要导入的任务(%s)不相符合!",
					   m_pStBaseInfo->stTaskBaseInfo.szTaskName,m_LoadOutTask.m_CurTaskInfo.stTaskBaseInfo.szTaskName);
		AfxMessageBox(strText);
		return FALSE;
	}
	return TRUE;
}

//这是一条结果//
int CBatchImportData::AnalysisData()
{

	CArray<TestDataStr,TestDataStr> nDataArray;
	CArray<StBasAttachment,StBasAttachment> nExclosureArray;
	int i,nCount,nRet = 0;
	nRet = m_LoadOutTask.AnalysisData(nDataArray,nExclosureArray);//获取当前任务项的数据//
	if(!nRet)
	{
		//return 0;
	}
	char szSQl[2048] = {0};
	
	StBasTask *pTask = NULL;
	pTask = &m_LoadOutTask.m_CurTaskInfo;
	StBasMode *pMode = NULL;
	pMode = &m_LoadOutTask.m_CurModeInfo;
	StTstResultAtta *pCurTaskNumbelMode = NULL;
	pCurTaskNumbelMode = m_LoadOutTask.m_pCurTaskNumbelMode;


	//检查模板的行可变属性//
	if(pMode->nModeRowVar == ModeRow_Change)
	{
		//有图号//
		////插入之前要判断是否有重复数据  防止误操作2次导入////
		int Num,nPicNumCount,nRow = 0;
		nPicNumCount = pTask->pArryTaskPicNum.size();
		vector<StBasTaskPicNum *> *pArryTaskPicNum = &pTask->pArryTaskPicNum;
		StBasTaskPicNum *pTaskPicNum ;

		nCount = nDataArray.GetCount();
		if(nCount>=1 && nPicNumCount > 0)
		{
			Num = nCount/nPicNumCount;
			for (i = 0;i<nPicNumCount;i++)
			{
				pTaskPicNum = pArryTaskPicNum->at(i);
				if(pTaskPicNum == NULL)
				{
					continue;
				}
				CString strOIDName = "OID";
				CString DataField = "DATA_XMLFILE";
				UINT nDataOid = m_DMng.GetTabLeastOid(pMode->szModeTabName);
				CString strWhere;
				int nRow = 0;
				strWhere.Format(_T(" where BELONG_MODEL='%s' and BELONG_MOMENT='%s' and PRODUCT_OID=%d\
								   and PICNUM_OID=%d and PRODUCT_CODE='%s' and TASK_OID=%d and SEND_DATE=to_date('%s','YYYY_MM_DD HH24:MI:SS')\
								   and BASE_OID=%d and ATTA_OID=%d"),
								   pTask->stTaskBaseInfo.szModel,pTask->stTaskBaseInfo.szPhase,pTask->stProductInfo.nOid,
									pTaskPicNum->nPicNumOid,
								   pCurTaskNumbelMode->szProductCode,pTask->stTaskBaseInfo.nOid,pTask->stTaskBaseInfo.szSendDate,
								   pCurTaskNumbelMode->nBaseOid,pCurTaskNumbelMode->nOid);


				memset(szSQl,0,sizeof(szSQl));
				sprintf(szSQl,"%s %s",
							  pMode->szModeTabName,
							  strWhere);
				m_DMng.GetTableRowCount(szSQl,nRow);


				if(nRow>=1)
				{

					CString strText;
					strText.Format("产品编号:%s,模板:%s,图号:%s 数据已经存在! 已更新",
						pCurTaskNumbelMode->szProductCode,pCurTaskNumbelMode->szModeName,pTaskPicNum->szPicNumName);
					g_MainFram->m_wndOutput.InsertErrorText(strText);

					memset(szSQl,0,sizeof(szSQl));
					sprintf(szSQl,_T("update %s set PRODUCT_NO='%s', PRODUCT_NAME='%s',\
									 PICNUM_NO='%s',PICNUM_NAME='%s',\
									 IMPORT_DATE=to_date('%s','YYYY_MM_DD hh24:MI:SS'),TASK_NAME='%s',\
									 FINISH_DATE=to_date('%s','YYYY_MM_DD hh24:MI:SS'),DEF_EDIT_3='%s',\
									 DEF_EDIT_4='%s',DEF_EDIT_5='%s',DEF_EDIT_6='%s' %s"),
									 pMode->szModeTabName,
									 pTask->stProductInfo.szProductNo,
									 pTask->stProductInfo.szProductName,
									 pTaskPicNum->szPicNumNo,
									 pTaskPicNum->szPicNumName,
									 pCurTaskNumbelMode->szImportDate,
									 pTask->stTaskBaseInfo.szTaskName,
									 pTask->stTaskBaseInfo.szFinishDate,
									 pCurTaskNumbelMode->szCheckUser,
									 "",
									 "",
									 pCurTaskNumbelMode->szFinishedTime,
									 strWhere);
				}else
				{
					UINT nDataOid = m_DMng.GetTabLeastOid(pMode->szModeTabName);
					memset(szSQl,0,sizeof(szSQl));
					sprintf(szSQl,"insert into %s(OID,BELONG_MODEL,BELONG_MOMENT,PRODUCT_OID,PRODUCT_NO,\
								  PRODUCT_NAME,PICNUM_OID,PICNUM_NO,\
								  PICNUM_NAME,PRODUCT_CODE,TASK_OID,TASK_NAME,SEND_DATE,FINISH_DATE,\
								  IMPORT_DATE,DEF_EDIT_3,DEF_EDIT_4,DEF_EDIT_5,DEF_EDIT_6,BASE_OID,ATTA_OID) values (%d,'%s','%s',%d,'%s',  '%s',%d,'%s',%d,'%s',  \
								  '%s','%s',%d,'%s',to_date('%s','YYYY_MM_DD hh24:MI:SS'),to_date('%s','YYYY_MM_DD hh24:MI:SS'),\
								  to_date('%s','YYYY_MM_DD hh24:MI:SS'),'%s','%s','%s','%s',%d,%d)",
								  pMode->szModeTabName,
								  nDataOid,pTask->stTaskBaseInfo.szModel,pTask->stTaskBaseInfo.szPhase,pTask->stProductInfo.nOid,pTask->stProductInfo.szProductNo,
								  pTask->stProductInfo.szProductName,
								  pTaskPicNum->nPicNumOid,
								  pTaskPicNum->szPicNumNo,pTaskPicNum->szPicNumName,pCurTaskNumbelMode->szProductCode,
								  pTask->stTaskBaseInfo.nOid, pTask->stTaskBaseInfo.szTaskName,pTask->stTaskBaseInfo.szSendDate, 
								  pTask->stTaskBaseInfo.szFinishDate,pCurTaskNumbelMode->szImportDate,
								  pCurTaskNumbelMode->szCheckUser,"","",pCurTaskNumbelMode->szFinishedTime,
								  pCurTaskNumbelMode->nBaseOid,pCurTaskNumbelMode->nOid);

					strWhere.Format(_T(" where %s=%d"),strOIDName,nDataOid);
				}

				//分批导入数据，字段太多，防止申请内存太少 漏掉数据//

				if(nCount>=1)
				{
					if(!m_DMng.UpdateDataInfo(szSQl))
					{
						CString strText;
						strText.Format("产品编号:%s,模板:%s 数据保存失败!",
							pCurTaskNumbelMode->szProductCode,pCurTaskNumbelMode->szModeName);
						g_MainFram->m_wndOutput.InsertErrorText(strText);
						return 0;
					}
				}else if(nCount<=0)
				{
					CString strText;
					strText.Format("产品编号:%s,模板:%s 采集数据为空!",
						pCurTaskNumbelMode->szProductCode,pCurTaskNumbelMode->szModeName);
					g_MainFram->m_wndOutput.InsertErrorText(strText);
					return 0;
				}

				int j,nNum = 0;
				CString strSQL = "";
				for(j = 0;j<Num;j++)
				{
					//组建SQL语句//为了保证SQL语句不要太长，分批导入 10 项一次///
					CString str = "";
					if(nNum >= 10)
					{
						memset(szSQl,0,sizeof(szSQl));
						sprintf(szSQl,"update %s set %s %s", 
							pMode->szModeTabName,strSQL,strWhere);
						if(!m_DMng.UpdateDataInfo(szSQl))
						{
							CString strText;
							strText.Format("产品编号:%s,模板:%s 数据保存失败!",
								pCurTaskNumbelMode->szProductCode,pCurTaskNumbelMode->szModeName);
							g_MainFram->m_wndOutput.InsertErrorText(strText);
							return 0;
						}
						nNum  =0;
						strSQL = "";
					}

					nNum++;
					if(nDataArray.GetAt(i*Num+j).iDataType == datatype_string)
					{
						str.Format("%s='%s'",nDataArray.GetAt(i*Num+j).Name,nDataArray.GetAt(i*Num+j).Data);
					}else if(nDataArray.GetAt(i*Num+j).iDataType == datatype_num || nDataArray.GetAt(i*Num+j).iDataType == datatype_caluate)
					{
						str.Format(_T("%s=%f"), nDataArray.GetAt(i*Num+j).Name,atof(nDataArray.GetAt(i*Num+j).Data));
					}
					
					if(nNum ==1)
					{
						strSQL += str;
					}else
					{
						strSQL += (","+str);
					}
					//AfxMessageBox(nDataArray.GetAt(i).Data);
				}

				if(nNum)
				{
					memset(szSQl,0,sizeof(szSQl));
					sprintf(szSQl,"update %s set %s %s", 
						pMode->szModeTabName,strSQL,strWhere);
					if(!m_DMng.UpdateDataInfo(szSQl))
					{
						CString strText;
						strText.Format("产品编号:%s,模板:%s 数据保存失败!",
							pCurTaskNumbelMode->szProductCode,pCurTaskNumbelMode->szModeName);
						g_MainFram->m_wndOutput.InsertErrorText(strText);
						return 0;
					}
					nNum  =0;
				}


				//将采集的数据文件保存到数据库中//
				if(nCount>=1)
				{
					CStdioFile file;
					CFileException e;
					char *strFileInfo;
					char szSQl[1024];

					CString strPath;
					strPath.Format( _T("%s//%s//%s"),
						g_WorkPath, 
						PATH_XML_MODE_PAR_CFG, 
						MD_XML_FILE_TAB_OUT_INFO);
					if(!file.Open(strPath, CFile::modeNoTruncate | CFile::modeRead, &e))
					{
						char szMsg[128] = {0};
						e.GetErrorMessage(szMsg, 128);

						CString strErr;
						strErr.Format(_T("打开数据库日志文件失败，原因为: %s"), szMsg);
						g_MainFram->m_wndOutput.InsertErrorText(strErr);
						return FALSE;
					}
					UINT nLen = file.GetLength();

					strFileInfo = new char[nLen+1];
					memset(strFileInfo, 0, nLen+1);
					file.Read((void*)strFileInfo,nLen);
					file.Close();

					if(!strFileInfo || !nLen)
					{
						return 0;
					}
					memset(szSQl,0,sizeof(szSQl));
					sprintf(szSQl,"update %s set %s=empty_blob() %s",
						pMode->szModeTabName,DataField,strWhere);

					if(!m_DMng.UpdateDataInfo(szSQl))
					{
						g_MainFram->m_wndOutput.InsertErrorText(_T("置空失败"));
						return 0;
					}
					memset(szSQl,0,sizeof(szSQl));
					sprintf(szSQl, "select %s from %s %s for update",
						DataField,pMode->szModeTabName,strWhere);

					if(!m_DMng.UpdateOracleBlob(szSQl,DataField.GetBuffer(0),strFileInfo,nLen))
					{
						g_MainFram->m_wndOutput.InsertErrorText(_T("写入失败"));
						return 0;
					}
				}


			}
		}
		
		

	}else
	{
		////插入之前要判断是否有重复数据  防止误操作2次导入////
		CString strOIDName = "OID";
		CString DataField = "DATA_XMLFILE";
		CString strWhere;
		int nRow = 0;
		strWhere.Format(_T(" where BELONG_MODEL='%s' and BELONG_MOMENT='%s' and PRODUCT_OID=%d\
			and PRODUCT_CODE='%s' and TASK_OID=%d and SEND_DATE=to_date('%s','YYYY_MM_DD HH24:MI:SS')\
			and BASE_OID=%d and ATTA_OID=%d"),
			pTask->stTaskBaseInfo.szModel,pTask->stTaskBaseInfo.szPhase,pTask->stProductInfo.nOid,
			pCurTaskNumbelMode->szProductCode,pTask->stTaskBaseInfo.nOid,pTask->stTaskBaseInfo.szSendDate,
			pCurTaskNumbelMode->nBaseOid,pCurTaskNumbelMode->nOid);
		memset(szSQl,0,sizeof(szSQl));
		sprintf(szSQl,"%s %s",
					  pMode->szModeTabName,
					  strWhere);
		m_DMng.GetTableRowCount(szSQl,nRow);
		if(nRow>=1)
		{

			CString strText;
			strText.Format("产品编号:%s,模板:%s 数据已经存在! 已更新.",
				pCurTaskNumbelMode->szProductCode,pCurTaskNumbelMode->szModeName);
			g_MainFram->m_wndOutput.InsertErrorText(strText);
			memset(szSQl,0,sizeof(szSQl));
			sprintf(szSQl,_T("update %s set PRODUCT_NO='%s', PRODUCT_NAME='%s',\
							 IMPORT_DATE=to_date('%s','YYYY_MM_DD hh24:MI:SS'),TASK_NAME='%s',\
							 FINISH_DATE=to_date('%s','YYYY_MM_DD hh24:MI:SS'),DEF_EDIT_3='%s',\
							 DEF_EDIT_4='%s',DEF_EDIT_5='%s',DEF_EDIT_6='%s'%s"),
							 pMode->szModeTabName,
							 pTask->stProductInfo.szProductNo,
							 pTask->stProductInfo.szProductName,
							 pCurTaskNumbelMode->szImportDate,
							 pTask->stTaskBaseInfo.szTaskName,
							 pTask->stTaskBaseInfo.szFinishDate,
							 pCurTaskNumbelMode->szCheckUser,
							 "",
							 "",
							 pCurTaskNumbelMode->szFinishedTime,
							 strWhere);
			
		}else
		{
			UINT nDataOid = m_DMng.GetTabLeastOid(pMode->szModeTabName);
			memset(szSQl,0,sizeof(szSQl));
			sprintf(szSQl,"insert into %s(OID,BELONG_MODEL,BELONG_MOMENT,PRODUCT_OID,PRODUCT_NO,\
						  PRODUCT_NAME,PRODUCT_CODE,TASK_OID,TASK_NAME,SEND_DATE,FINISH_DATE,\
						  IMPORT_DATE,DEF_EDIT_3,DEF_EDIT_4,DEF_EDIT_5,DEF_EDIT_6,\
						  BASE_OID,ATTA_OID) values (%d,'%s','%s',%d,'%s',  '%s','%s',%d,'%s',\
						  to_date('%s','YYYY_MM_DD hh24:MI:SS'),to_date('%s','YYYY_MM_DD hh24:MI:SS'),\
						  to_date('%s','YYYY_MM_DD hh24:MI:SS'),'%s',  \
						  '%s','%s','%s',%d,%d)",
						  pMode->szModeTabName,
						  nDataOid,pTask->stTaskBaseInfo.szModel,pTask->stTaskBaseInfo.szPhase,pTask->stProductInfo.nOid,pTask->stProductInfo.szProductNo,
						  pTask->stProductInfo.szProductName,pCurTaskNumbelMode->szProductCode,
						  pTask->stTaskBaseInfo.nOid, pTask->stTaskBaseInfo.szTaskName, pTask->stTaskBaseInfo.szSendDate,
						  pTask->stTaskBaseInfo.szFinishDate,pCurTaskNumbelMode->szImportDate,
						  pCurTaskNumbelMode->szCheckUser,"","",pCurTaskNumbelMode->szFinishedTime,
						  pCurTaskNumbelMode->nBaseOid,pCurTaskNumbelMode->nOid);

			strWhere.Format(_T(" where %s=%d"),strOIDName,nDataOid);
		}

		
		



		//分批导入数据，字段太多，防止申请内存太少 漏掉数据//
		nCount = nDataArray.GetCount();
		if(nCount>=1)
		{
			if(!m_DMng.UpdateDataInfo(szSQl))
			{
				CString strText;
				strText.Format("产品编号:%s,模板:%s 数据保存失败!",
					pCurTaskNumbelMode->szProductCode,pCurTaskNumbelMode->szModeName);
				g_MainFram->m_wndOutput.InsertErrorText(strText);
				return 0;
			}
		}else if(nCount<=0)
		{
			CString strText;
			strText.Format("产品编号:%s,模板:%s 采集数据为空!",
				pCurTaskNumbelMode->szProductCode,pCurTaskNumbelMode->szModeName);
			g_MainFram->m_wndOutput.InsertErrorText(strText);
			return 0;
		}

		int nNum = 0;
		CString strSQL = "";
		for(i = 0;i<nCount;i++)
		{
			//组建SQL语句//为了保证SQL语句不要太长，分批导入 10 项一次///
			CString str = "";
			if(nNum >= 10)
			{
				memset(szSQl,0,sizeof(szSQl));
				sprintf(szSQl,"update %s set %s %s", 
					pMode->szModeTabName,strSQL,strWhere);
				if(!m_DMng.UpdateDataInfo(szSQl))
				{
					CString strText;
					strText.Format("产品编号:%s,模板:%s 数据保存失败!",
						pCurTaskNumbelMode->szProductCode,pCurTaskNumbelMode->szModeName);
					g_MainFram->m_wndOutput.InsertErrorText(strText);
					return 0;
				}
				nNum  =0;
				strSQL = "";
			}

			nNum++;

		
			if(nDataArray.GetAt(i).iDataType == datatype_string)
			{
				str.Format("%s='%s'",nDataArray.GetAt(i).Name,nDataArray.GetAt(i).Data);
			}else if(nDataArray.GetAt(i).iDataType == datatype_num || nDataArray.GetAt(i).iDataType == datatype_caluate)
			{
				str.Format(_T("%s=%f"), nDataArray.GetAt(i).Name,atof(nDataArray.GetAt(i).Data));
			}
			//if()
			//str.Format("%s='%s'",nDataArray.GetAt(i).Name,nDataArray.GetAt(i).Data);

			if(nNum ==1)
			{
				strSQL += str;
			}else
			{
				strSQL += (","+str);
			}
			//AfxMessageBox(nDataArray.GetAt(i).Data);
		}

		if(nNum)
		{
			memset(szSQl,0,sizeof(szSQl));
			sprintf(szSQl,"update %s set %s %s", 
				pMode->szModeTabName,strSQL,strWhere);
			if(!m_DMng.UpdateDataInfo(szSQl))
			{
				CString strText;
				strText.Format("产品编号:%s,模板:%s 数据保存失败!",
					pCurTaskNumbelMode->szProductCode,pCurTaskNumbelMode->szModeName);
				g_MainFram->m_wndOutput.InsertErrorText(strText);
				return 0;
			}
			nNum  =0;
		}


		if(nCount>=1)
		{
			CStdioFile file;
			CFileException e;
			char *strFileInfo;

			CString strPath;
			strPath.Format( _T("%s//%s//%s"),
				g_WorkPath, 
				PATH_XML_MODE_PAR_CFG, 
				MD_XML_FILE_TAB_OUT_INFO);
			if(!file.Open(strPath, CFile::modeNoTruncate | CFile::modeRead, &e))
			{
				char szMsg[128] = {0};
				e.GetErrorMessage(szMsg, 128);

				CString strErr;
				strErr.Format(_T("打开数据库日志文件失败，原因为: %s"), szMsg);
				g_MainFram->m_wndOutput.InsertErrorText(strErr);
				return FALSE;
			}
			UINT nLen = file.GetLength();

			strFileInfo = new char[nLen+1];
			memset(strFileInfo, 0, nLen+1);
			file.Read((void*)strFileInfo,nLen);
			file.Close();

			if(!strFileInfo || !nLen)
			{
				return 0;
			}
			memset(szSQl,0,sizeof(szSQl));
			sprintf(szSQl,"update %s set %s=empty_blob() %s",
				pMode->szModeTabName,DataField,strWhere);

			if(!m_DMng.UpdateDataInfo(szSQl))
			{
				g_MainFram->m_wndOutput.InsertErrorText(_T("置空失败"));
				return 0;
			}
			memset(szSQl,0,sizeof(szSQl));
			sprintf(szSQl, "select %s from %s %s for update",
				DataField,pMode->szModeTabName,strWhere);

			if(!m_DMng.UpdateOracleBlob(szSQl,DataField.GetBuffer(0),strFileInfo,nLen))
			{
				g_MainFram->m_wndOutput.InsertErrorText(_T("写入失败"));
				return 0;
			}
		}
	}
	

	
	

	//2.开始导入附件，从默认路径下将附件copy 到指定文件夹下 任务名\\产品名_编号_模板名\\文件名//
	                  //将附件信息更新到数据库中//

	CString strInPath;
	CString strInDepartPath;
	CString strInTaskPath;
	CString strInProdPath;

	strInPath.Format( _T("%s\\%s"), g_WorkPath,ExclosureFile_Path);
	if(GetFileAttributes(strInPath.GetBuffer(0)) == 0xFFFFFFFF)
		CreateDirectory(strInPath.GetBuffer(0), NULL);


	strInDepartPath.Format( _T("%s\\%s"), strInPath,g_CurSelDepart.szGroupName);
	if(GetFileAttributes(strInDepartPath.GetBuffer(0)) == 0xFFFFFFFF)
		CreateDirectory(strInDepartPath.GetBuffer(0), NULL);

	strInTaskPath.Format( _T("%s\\%s"), strInDepartPath,pTask->stTaskBaseInfo.szTaskName);
	if(GetFileAttributes(strInTaskPath.GetBuffer(0)) == 0xFFFFFFFF)
		CreateDirectory(strInTaskPath.GetBuffer(0), NULL);

	strInProdPath.Format( _T("%s\\%s_%s_%s"), strInTaskPath, 
		pTask->stProductInfo.szProductNo, pCurTaskNumbelMode->szProductCode, pCurTaskNumbelMode->szModeName);
	if(GetFileAttributes(strInProdPath.GetBuffer(0)) == 0xFFFFFFFF)
		CreateDirectory(strInProdPath.GetBuffer(0), NULL);

	


	CString strOutPath = m_LoadOutTask.m_szDbPath;
	CString strOutProdPath;

	int nPos = strOutPath.ReverseFind('\\');
	strOutPath = strOutPath.Left(nPos);
	//strOutPath.Format( _T("%s\\OutApp"), g_WorkPath);
	//if(GetFileAttributes(strOutPath.GetBuffer(0)) == 0xFFFFFFFF)
	//{
	//	CString strText;
	//	strText.Format("未检测到这个路径:\n%s\n没有附件信息",strOutPath);
	//	//AfxMessageBox(strText);
	//	//return 0;
	//}
	strOutProdPath.Format( _T("%s\\%s_%s_%s"), strOutPath, 
		pTask->stProductInfo.szProductNo, pCurTaskNumbelMode->szProductCode, pCurTaskNumbelMode->szModeName);
	if(GetFileAttributes(strOutProdPath.GetBuffer(0)) == 0xFFFFFFFF)
	{
		CString strText;
		strText.Format("未检测到这个路径:\n%s\n没有附件信息",strOutProdPath);
		g_MainFram->m_wndOutput.InsertErrorText(strText);
		return 0;
	}

	CString strAttaTab;
	strAttaTab.Format(_T("%s%.4d"),g_ResultAtta,g_CurSelDepart.nOid);
	nCount = 0;
	nCount = nExclosureArray.GetCount();
	for(i = 0;i<nCount;i++)
	{
		
/*
		int nRow = 0;
		memset(szSQl,0,1024);
		sprintf(szSQl,"%s where MODEL='%s' and PHASE='%s' and PRODUCT_OID=%d and SERIES_OID=%d \
					  and MODE_OID=%d and TASK_OID=%d \
					  and DATA_INDEX=%d and DATA_DESC='%s'",
					  strAttaTab,
					  g_ExclosureTab[1],SQLText(pTask->ProdType),g_ExclosureTab[2],SQLText(pTask->ProdMoment),
					  g_ExclosureTab[3],SQLText(pTask->ProdName),g_ExclosureTab[4],SQLText(pCurTaskNumbelMode->ProdNumbel),
					  g_ExclosureTab[5],SQLText(pMode->ModeID),g_ExclosureTab[6],SQLText(pTask->TaskID),
					  g_ExclosureTab[7],SQLText(nExclosureArray.GetAt(i).ModeNum),
					  g_ExclosureTab[8],SQLText(nExclosureArray.GetAt(i).ModeDesc));

		m_DMng.GetTableRowCount(szSQl,nRow);
		if(nRow>=1)
		{

			CString strText;
			strText.Format("产品编号:%s,模板名:%s\n\
						   模板的第 %d 个单元格,标识为 \"%s(D数字_行_列)\"附件已经存在!",
				pCurTaskNumbelMode->ProdNumbel,pCurTaskNumbelMode->ModeName,
				nExclosureArray.GetAt(i).ModeNum,
				nExclosureArray.GetAt(i).ModeDesc);
			AfxMessageBox(strText);
			continue;
		}
*/
		CString strInAppFileName;
		CString strOutAppFileName;
		strInAppFileName.Format( _T("%s\\%s_%s_%s_%s"), strInProdPath, 
			pTask->stProductInfo.szProductNo, pCurTaskNumbelMode->szProductCode, pCurTaskNumbelMode->szModeName,
			nExclosureArray.GetAt(i).Exclosure_OldName);
		strOutAppFileName.Format( _T("%s\\%s"), strOutProdPath, 
			nExclosureArray.GetAt(i).Exclosure_Name);
		if(GetFileAttributes(strOutAppFileName.GetBuffer(0)) == 0xFFFFFFFF)
		{
			CString strText;
			strText.Format("没找到这个文件:\n%s\n没有附件信息",strOutAppFileName);
			g_MainFram->m_wndOutput.InsertErrorText(strText);
			continue;
		}
		CopyFile(strOutAppFileName, strInAppFileName.GetBuffer(0),  0);

		DoDecFromAppFile(strInAppFileName.GetBuffer(0));             //执行解密_对附件文件
	}

	return 1;
}
int CBatchImportData::IsTstResultExists(UINT nGroupOid)//判断任务基础表是否存在//
{

	//检查表是否已经存在//
	BOOL nIs = FALSE;
	CString strAttaTabName,strBaseTabName, strEncolsureName;
	strAttaTabName.Format(_T("%s%.4d"),g_ResultAtta,nGroupOid);
	strBaseTabName.Format(_T("%s%.4d"),g_ResultBase,nGroupOid);
	strEncolsureName.Format(_T("%s%.4d"), g_Enclosure, nGroupOid);

	char szSQL[512] = {0};
	nIs = m_DMng.IsHrGroupSaveExists(nGroupOid);

	if(nIs)//已经存在//
	{
		
	}else//不存在//
	{
		
		BOOL nError = FALSE;
		nError = AutoCreateHrGroupSaveTab(strBaseTabName,strAttaTabName);
		//把表名 保存到相应数据表中//

		if(nError)
		{
			StHrGroupSave nHrGroupSave;
			memset(&nHrGroupSave,0,sizeof(StBasModeSave));
			nHrGroupSave.nGroupOid = nGroupOid;
			strcpy(nHrGroupSave.szBaseTabName,strBaseTabName);
			strcpy(nHrGroupSave.szAttaTabName,strAttaTabName);
			strcpy(nHrGroupSave.szCreateTime,GetDateTimeString());
			strcpy(nHrGroupSave.szCreateUser,g_LoginUsrInfo.szLoginName);

			if(!m_DMng.AddNewHrGroupSave(&nHrGroupSave))
			{
				AfxMessageBox(_T("Oracle创建任务基础表失败!"));
			}
		}
	}
	return 1;
}
BOOL CBatchImportData::AddTstResultBase(StTstResultBase *pStTstResultBase)
{
	//导入时检查此项检查是否存在//
	CString strTabName;
	strTabName.Format(_T("%s%.4d"),g_ResultBase,g_CurSelDepart.nOid);
	StBasTask *pTaskInfo = &m_LoadOutTask.m_CurTaskInfo;
	StBasTaskBaseInfo *pTaskBaseInfo = &pTaskInfo->stTaskBaseInfo;
	StBasProduct      *pProductInfo = &pTaskInfo->stProductInfo;
	StHrUpDepart      *pUpDepartInfo = &pTaskInfo->stHrUpDepart;

	char szSQl[4096*2];
	memset(pStTstResultBase,0,sizeof(StTstResultBase));
	pStTstResultBase->nOid = m_DMng.GetTabLeastOid(strTabName.GetBuffer(0));

	pStTstResultBase->nTaskOid = pTaskInfo->stTaskBaseInfo.nOid;
	strcpy(pStTstResultBase->szSendDate,pTaskInfo->stTaskBaseInfo.szSendDate);
	strcpy(pStTstResultBase->szTaskName,pTaskInfo->stTaskBaseInfo.szTaskName);
	strcpy(pStTstResultBase->szImportDate,GetDateTimeString());
	strcpy(pTaskInfo->stTaskBaseInfo.szImportDate,pStTstResultBase->szImportDate);
	strcpy(pStTstResultBase->szCheckUser,pTaskInfo->stTaskBaseInfo.szCheckUser);


	pStTstResultBase->nProductOid = pTaskInfo->stProductInfo.nOid;
	strcpy(pStTstResultBase->szProductNo,pTaskInfo->stProductInfo.szProductNo);


	int nRow = 0;
	memset(szSQl,0,sizeof(szSQl));
	sprintf(szSQl,"%s where TASK_OID=%d and SEND_DATE=to_date('%s','YYYY_MM_DD HH24:MI:SS')",
		strTabName,
		pStTstResultBase->nTaskOid,
		pStTstResultBase->szSendDate);
	m_DMng.GetTableRowCount(szSQl,nRow);
	if(nRow>=1)
	{
		//若存在  获取OID//
		char szSQL2[1024];
		memset(szSQL2,0,sizeof(szSQL2));

		COciSQLCursor	*OciSql;
		OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);
		sprintf(szSQL2,_T("select OID from %s %s"),strTabName,szSQl);
		if(!g_pOrcOciDb->ExeSQL(OciSql, szSQL2, SQL_SELECT))
		{
			OciSql->Release();
			return FALSE;
		}	
		while(OciSql->Fetch())
		{
			pStTstResultBase->nOid = atoi(m_DMng.GetFieldValue(_T("OID"),OciSql));
		}
		OciSql->Release();


		memset(szSQl,0,sizeof(szSQl));
		sprintf(szSQl,"update %s set TASK_NAME='%s',PROJECT_NO='%s',TASK_STATUS=%d,TASK_TYPE=%d,MODEL='%s',\
					  PHASE='%s',PRODUCT_OID=%d,PRODUCT_NO='%s',PRODUCT_NAME='%s',PRODUCT_CODE='%s',\
					  CODE_COUNT=%d,BATCH='%s',DEPART_OID=%d,DEPART_NAME='%s',UP_USER='%s',\
					  \
					  UP_DATE=to_date('%s','YYYY_MM_DD HH24:MI:SS'),\
					  TECH_USER='%s',CHECK_LEADER='%s',CHECK_USER='%s',\
					  DOWNLOAD_DATE=to_date('%s','YYYY_MM_DD HH24:MI:SS'),\
					  FINISH_DATE=to_date('%s','YYYY_MM_DD HH24:MI:SS'),\
					  IMPORT_DATE=to_date('%s','YYYY_MM_DD HH24:MI:SS'),ARMY_TEST=%d,DIANSHI_NUM=%d,\
					  ACCORDING1='%s',ACCORDING2='%s',\
					  \
					  ACCORDING3='%s',ACCORDING4='%s',ACCORDING5='%s',\
					  TASK_REMARK='%s', \
					  PLAN_BEGTIME=to_date('%s','YYYY_MM_DD HH24:MI:SS'),\
					  \
					  PLAN_ENDTIME=to_date('%s','YYYY_MM_DD HH24:MI:SS'),\
					  REAL_BEGTIME=to_date('%s','YYYY_MM_DD HH24:MI:SS'),\
					  REAL_ENDTIME=to_date('%s','YYYY_MM_DD HH24:MI:SS'),\
					  CREATE_TIME=to_date('%s','YYYY_MM_DD HH24:MI:SS'),\
					  CREATE_USER='%s',\
					  \
					  GROUP_OID=%d,\
					  GROUP_NAME='%s' where TASK_OID=%d and \
					  SEND_DATE=to_date('%s','YYYY_MM_DD HH24:MI:SS')",
					  strTabName,
					  pTaskBaseInfo->szTaskName,pTaskBaseInfo->szProjectNo,pTaskBaseInfo->nTaskStatus,pTaskBaseInfo->nTaskType,pTaskBaseInfo->szModel,
					  pTaskBaseInfo->szPhase,pProductInfo->nOid,pProductInfo->szProductNo,pProductInfo->szProductName,pTaskBaseInfo->szProductCode,
					  pTaskBaseInfo->nCodeNumber,pTaskBaseInfo->szBatch,pUpDepartInfo->nOid,pUpDepartInfo->szUpDepartName,pTaskBaseInfo->szUpUser,
					  pTaskBaseInfo->szUpDate, pTaskBaseInfo->szTechUser,pTaskBaseInfo->szCheckLeader,pTaskBaseInfo->szCheckUser,pTaskBaseInfo->szDownLoadDate,
					  pTaskBaseInfo->szFinishDate,
					  pStTstResultBase->szImportDate, pTaskBaseInfo->nArmyTest,pTaskBaseInfo->nDianShiNum,pTaskBaseInfo->szAccording1,pTaskBaseInfo->szAccording2,
					  pTaskBaseInfo->szAccording3, pTaskBaseInfo->szAccording4,pTaskBaseInfo->szAccording5,pTaskBaseInfo->szTaskRemark,pTaskBaseInfo->szPlanBegTime,
					  pTaskBaseInfo->szPlanEndTime, pTaskBaseInfo->szRealBegTime,pTaskBaseInfo->szRealEndTime,pTaskBaseInfo->szCreateDate,pTaskBaseInfo->szCheckUser,
					  pTaskBaseInfo->nGroupOid, pTaskBaseInfo->szGroupName,
					  pTaskBaseInfo->nOid,  pStTstResultBase->szSendDate);

		CString strText;
		strText.Format("任务名称:%s,下发时间:%s 数据已经存在!已更新",
			pStTstResultBase->szTaskName,pStTstResultBase->szSendDate);
		g_MainFram->m_wndOutput.InsertErrorText(strText);

	}else
	{
		memset(szSQl,0,sizeof(szSQl));
		sprintf(szSQl,"insert into %s(OID,TASK_OID,TASK_NAME,PROJECT_NO,TASK_STATUS,\
					  TASK_TYPE,MODEL,PHASE,PRODUCT_OID,PRODUCT_NO,\
					  PRODUCT_NAME,PRODUCT_CODE,CODE_COUNT,BATCH,DEPART_OID,\
					  DEPART_NAME,UP_USER,UP_DATE,TECH_USER,CHECK_LEADER,\
					  CHECK_USER,SEND_DATE,DOWNLOAD_DATE,FINISH_DATE,IMPORT_DATE,ARMY_TEST,\
					  DIANSHI_NUM,ACCORDING1,ACCORDING2,ACCORDING3,ACCORDING4,\
					  ACCORDING5,TASK_REMARK,PLAN_BEGTIME,PLAN_ENDTIME,REAL_BEGTIME,\
					  REAL_ENDTIME,CREATE_TIME,CREATE_USER,GROUP_OID,GROUP_NAME) \
					  values (%d,%d,'%s','%s',%d,\
					  %d,'%s','%s',%d,'%s',  '%s','%s',%d,'%s',%d,\
					  '%s','%s',to_date('%s','YYYY_MM_DD HH24:MI:SS'),'%s','%s',\
					  '%s',to_date('%s','YYYY_MM_DD HH24:MI:SS'),to_date('%s','YYYY_MM_DD HH24:MI:SS'),to_date('%s','YYYY_MM_DD HH24:MI:SS'),to_date('%s','YYYY_MM_DD HH24:MI:SS'),%d,\
					  %d,'%s','%s','%s','%s',   '%s','%s',to_date('%s','YYYY_MM_DD HH24:MI:SS'),to_date('%s','YYYY_MM_DD HH24:MI:SS'),to_date('%s','YYYY_MM_DD HH24:MI:SS'),\
					  to_date('%s','YYYY_MM_DD HH24:MI:SS'),to_date('%s','YYYY_MM_DD HH24:MI:SS'),'%s', %d,'%s')",
					  strTabName,
					  pStTstResultBase->nOid,pTaskBaseInfo->nOid, pTaskBaseInfo->szTaskName,pTaskBaseInfo->szProjectNo,pTaskBaseInfo->nTaskStatus,
					  pTaskBaseInfo->nTaskType,pTaskBaseInfo->szModel,pTaskBaseInfo->szPhase,pProductInfo->nOid,pProductInfo->szProductNo,
					  pProductInfo->szProductName,pTaskBaseInfo->szProductCode,pTaskBaseInfo->nCodeNumber,pTaskBaseInfo->szBatch,pUpDepartInfo->nOid,
					  pUpDepartInfo->szUpDepartName,pTaskBaseInfo->szUpUser,pTaskBaseInfo->szUpDate, pTaskBaseInfo->szTechUser,pTaskBaseInfo->szCheckLeader,
					  pTaskBaseInfo->szCheckUser,pTaskBaseInfo->szSendDate,pTaskBaseInfo->szDownLoadDate,pTaskBaseInfo->szFinishDate,pStTstResultBase->szImportDate, pTaskBaseInfo->nArmyTest,
					  pTaskBaseInfo->nDianShiNum,pTaskBaseInfo->szAccording1,pTaskBaseInfo->szAccording2,pTaskBaseInfo->szAccording3, pTaskBaseInfo->szAccording4,
					  pTaskBaseInfo->szAccording5,pTaskBaseInfo->szTaskRemark,pTaskBaseInfo->szPlanBegTime,pTaskBaseInfo->szPlanEndTime, pTaskBaseInfo->szRealBegTime,
					  pTaskBaseInfo->szRealEndTime,pTaskBaseInfo->szCreateDate,pTaskBaseInfo->szCheckUser,pTaskBaseInfo->nGroupOid, pTaskBaseInfo->szGroupName);
	}

	if(!m_DMng.UpdateDataInfo(szSQl))
	{
		CString strText;
		strText.Format("插入任务基础表失败!任务名称:%s,下发时间:%s",
			pStTstResultBase->szTaskName,pStTstResultBase->szSendDate);
		g_MainFram->m_wndOutput.InsertErrorText(strText);
		return FALSE;
	}
	return TRUE;
}
int CBatchImportData::AutoCreateHrGroupSaveTab(CString strBaseTabName,CString strAttaTabName)
{
	char szSQL[2048];
	//1.创建任务基础表//
	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("create table %s (\
					 OID           NUMBER(10) not null,\
					 TASK_OID      NUMBER(10),\
					 TASK_NAME     VARCHAR2(100),\
					 PROJECT_NO    VARCHAR2(100),\
					 TASK_STATUS   NUMBER,\
					 TASK_TYPE     NUMBER,\
					 MODEL         VARCHAR2(100),\
					 PHASE	      VARCHAR2(100),\
					 PRODUCT_OID   NUMBER(10),\
					 PRODUCT_NO    VARCHAR2(100),\
					 PRODUCT_NAME  VARCHAR2(100),\
					 PRODUCT_CODE  VARCHAR2(100),\
					 CODE_COUNT    NUMBER,\
					 BATCH         VARCHAR2(20),\
					 DEPART_OID    NUMBER(10),\
					 DEPART_NAME   VARCHAR2(100),\
					 UP_USER       VARCHAR(20),\
					 UP_DATE	      DATE,\
					 TECH_USER     VARCHAR(20),\
					 CHECK_LEADER  VARCHAR2(20),\
					 CHECK_USER	  VARCHAR2(20),\
					 SEND_DATE     DATE,\
					 DOWNLOAD_DATE DATE,\
					 FINISH_DATE   DATE,\
					 IMPORT_DATE   DATE,\
					 ARMY_TEST	  NUMBER,\
					 DIANSHI_NUM	  NUMBER,\
					 ACCORDING1	  VARCHAR2(200),\
					 ACCORDING2	  VARCHAR2(200),\
					 ACCORDING3	  VARCHAR2(200),\
					 ACCORDING4	  VARCHAR2(200),\
					 ACCORDING5	  VARCHAR2(200),\
					 TASK_REMARK	  VARCHAR2(300),\
					 PLAN_BEGTIME	DATE,\
					 PLAN_ENDTIME	DATE,\
					 REAL_BEGTIME	DATE,\
					 REAL_ENDTIME	DATE,\
					 CREATE_TIME	DATE,\
					 CREATE_USER	VARCHAR2(20),\
					 GROUP_OID	NUMBER(10),\
					 GROUP_NAME  VARCHAR(100)\
					 )"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.OID is '测试结果基础表OID'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.TASK_OID is '任务Oid'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.TASK_NAME is '任务名称'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.PROJECT_NO is '检验单号'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.TASK_STATUS is '任务状态'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.TASK_TYPE is '任务类型'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.MODEL is '产品类型'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.PHASE is '阶段'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.PRODUCT_OID is '产品OID'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.PRODUCT_NO is '产品代号'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.PRODUCT_NAME is '产品名称'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.PRODUCT_CODE is '产品编号简写'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.CODE_COUNT is '编号数量'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.BATCH is '产品批次'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.DEPART_OID is '交检部门OID'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.DEPART_NAME is '交检部门名称'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.UP_USER is '交检人'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.UP_DATE is '交检日期'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.TECH_USER is '工艺员'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.CHECK_LEADER is '检验组长'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.CHECK_USER is '检验员姓名'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.SEND_DATE is '派工时间'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.DOWNLOAD_DATE is '下载时间'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.FINISH_DATE is '完成时间'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.IMPORT_DATE is '导入时间'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.ARMY_TEST is '是否军检'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.DIANSHI_NUM is '典试数量'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.ACCORDING1 is '检验依据1'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.ACCORDING2 is '检验依据2'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.ACCORDING3 is '检验依据3'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.ACCORDING4 is '检验依据4'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.ACCORDING5 is '检验依据5'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.TASK_REMARK is '任务备注'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.PLAN_BEGTIME is '计划开始时间'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.PLAN_ENDTIME is '计划结束时间'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.REAL_BEGTIME is '实际开始时间'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.REAL_ENDTIME is '实际结束时间'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.CREATE_TIME is '任务创建时间'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.CREATE_USER is '任务创建人'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.GROUP_OID is '所属部门OID'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.GROUP_NAME is '所属部门名称'"),strBaseTabName);
	m_DMng.UpdateDataInfo(szSQL);


	//2.创建结果附件表///
	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("create table %s (\
					 OID            NUMBER(10) PRIMARY KEY not null,\
					 TASK_OID	    NUMBER(10),\
					 TASK_NAME     VARCHAR2(100),\
					 PRODUCT_OID	NUMBER(10),\
					 PRODUCT_NO	    VARCHAR2(100),\
					 PRODUCT_NAME	VARCHAR2(100),\
					 MODEL	        VARCHAR2(100),\
					 PHASE	        VARCHAR2(100),\
					 PRODUCT_CODE	VARCHAR2(100),\
					 DIANSHI_TEST	NUMBER,\
					 MODE_OID	    NUMBER(10),\
					 MODE_NAME	    VARCHAR2(100),\
					 MODE_TYPE	    NUMBER,\
					 MODE_ROWVAR	NUMBER,\
					 PICNUM_COUNT	NUMBER,\
					 PERCENT	    NUMBER,\
					 FINISHED	    NUMBER,\
					 FINISHED_TIME	VARCHAR2(20),\
					 CHECK_USER	    VARCHAR2(20),\
					 SEND_DATE      DATE,\
					 IMPORT_DATE    DATE,\
					 BASE_OID       NUMBER(10),\
					 MODE_XMLFILE   BLOB,\
					 DATA_XMLFILE   BLOB,\
					 TASK_XMLFILE BLOB)"),strAttaTabName);

	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.OID is '测试结果基础表OID'"),strAttaTabName);
	m_DMng.UpdateDataInfo(szSQL);
	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.TASK_OID is '任务Oid'"),strAttaTabName);
	m_DMng.UpdateDataInfo(szSQL);
	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.TASK_NAME is '任务名称'"),strAttaTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.PRODUCT_OID is '产品代号Oid'"),strAttaTabName);
	m_DMng.UpdateDataInfo(szSQL);
	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.PRODUCT_NAME is '产品名称'"),strAttaTabName);
	m_DMng.UpdateDataInfo(szSQL);
	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.PRODUCT_NO is '产品代号'"),strAttaTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.MODEL is '产品型号'"),strAttaTabName);
	m_DMng.UpdateDataInfo(szSQL);
	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.PHASE is '产品阶段'"),strAttaTabName);
	m_DMng.UpdateDataInfo(szSQL);
	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.PRODUCT_CODE is '编号名称'"),strAttaTabName);
	m_DMng.UpdateDataInfo(szSQL);
	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.DIANSHI_TEST is '是否典试'"),strAttaTabName);
	m_DMng.UpdateDataInfo(szSQL);
	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.MODE_OID is '模板Oid'"),strAttaTabName);
	m_DMng.UpdateDataInfo(szSQL);
	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.MODE_NAME is '模板名称'"),strAttaTabName);
	m_DMng.UpdateDataInfo(szSQL);
	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.MODE_TYPE is '模板类型:0.产品通用,1.产品专用,2.线缆专用,3.未启用'"),strAttaTabName);
	m_DMng.UpdateDataInfo(szSQL);
	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.MODE_ROWVAR is '模板行可变状态：0.不可变 1.行可变'"),strAttaTabName);
	m_DMng.UpdateDataInfo(szSQL);
	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.PICNUM_COUNT is '图号数量'"),strAttaTabName);
	m_DMng.UpdateDataInfo(szSQL);
	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.PERCENT is '完成进度(百分比)'"),strAttaTabName);
	m_DMng.UpdateDataInfo(szSQL);
	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.FINISHED is '完成状态'"),strAttaTabName);
	m_DMng.UpdateDataInfo(szSQL);
	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.FINISHED_TIME is '完成时间'"),strAttaTabName);
	m_DMng.UpdateDataInfo(szSQL);
	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.CHECK_USER is '检查人'"),strAttaTabName);
	m_DMng.UpdateDataInfo(szSQL);
	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.SEND_DATE is '任务下发时间'"),strAttaTabName);
	m_DMng.UpdateDataInfo(szSQL);
	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.IMPORT_DATE is '任务导入时间'"),strAttaTabName);
	m_DMng.UpdateDataInfo(szSQL);
	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.BASE_OID is '任务基础表的OID'"),strAttaTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.MODE_XMLFILE is '模板的配置文件'"),strAttaTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.DATA_XMLFILE is '采集数据文件'"),strAttaTabName);
	m_DMng.UpdateDataInfo(szSQL);

	memset(szSQL,0,sizeof(szSQL));
	sprintf(szSQL,_T("comment on column %s.TASK_XMLFILE is '任务的详细信息包括图号信息'"),strAttaTabName);
	m_DMng.UpdateDataInfo(szSQL);


	//3.创建附件表///

	return 1;


}
BOOL CBatchImportData::AddTstResultData(StTstResultAtta *pStTstResult,UINT nGroupOid)//将数据索引插入任务基础表//
{
	CString strTabName;
	CString strWhere;
	CString ModeField = _T("MODE_XMLFILE"),DataField = _T("DATA_XMLFILE"),TaskXmlFile = _T("TASK_XMLFILE");
	strTabName.Format(_T("%s%.4d"),g_ResultAtta,nGroupOid);

	char szSQl[1024];
	int nRow = 0;
	pStTstResult->nOid = m_DMng.GetTabLeastOid(strTabName.GetBuffer(0));


	strWhere.Format(_T(" where MODEL %s and PHASE %s and PRODUCT_OID=%d\
					   and PRODUCT_CODE='%s'and MODE_OID=%d and TASK_OID=%d and SEND_DATE=to_date('%s','YYYY_MM_DD HH24:MI:SS')"),
					   SQLText(pStTstResult->szModel),SQLText(pStTstResult->szPhase),pStTstResult->nProductOid,pStTstResult->szProductCode,
					   pStTstResult->nModeOid,pStTstResult->nTaskOid,pStTstResult->szSendDate);
	memset(szSQl,0,sizeof(szSQl));
	sprintf(szSQl,"%s %s",
		strTabName,
		strWhere);
	m_DMng.GetTableRowCount(szSQl,nRow);
	if(nRow>=1)
	{
		//若存在  获取OID//
		char szSQL2[1024];
		memset(szSQL2,0,sizeof(szSQL2));

		COciSQLCursor	*OciSql;
		OciSql = g_pOrcOciDb->m_OciDatabase->CreateSQLCursorInstance(g_pOrcOciDb->m_OciConn);
		sprintf(szSQL2,_T("select OID from %s %s"),strTabName,strWhere);
		if(!g_pOrcOciDb->ExeSQL(OciSql, szSQL2, SQL_SELECT))
		{
			OciSql->Release();
			return FALSE;
		}	
		while(OciSql->Fetch())
		{
			pStTstResult->nOid = atoi(m_DMng.GetFieldValue(_T("OID"),OciSql));
		}
		OciSql->Release();
		strWhere.Format(_T("where OID=%d"),pStTstResult->nOid);

		memset(szSQl,0,sizeof(szSQl));
		sprintf(szSQl,"update %s set TASK_NAME='%s',PRODUCT_NAME='%s',PRODUCT_NO='%s',\
					  PRODUCT_CODE='%s',MODE_NAME='%s',MODE_TYPE=%d, MODE_ROWVAR=%d,PICNUM_COUNT=%d,\
					  DIANSHI_TEST=%d,PERCENT=%d,FINISHED=%d,FINISHED_TIME='%s',\
					  CHECK_USER='%s',IMPORT_DATE=to_date('%s','YYYY_MM_DD HH24:MI:SS') %s",
					  strTabName,
					  pStTstResult->szTaskName,pStTstResult->szProductName,pStTstResult->szProductNo,
					  pStTstResult->szProductCode,pStTstResult->szModeName,pStTstResult->nModeType,pStTstResult->nModeRowVar,pStTstResult->nPicNumCount,
					  pStTstResult->nDianshiTest,pStTstResult->nPercent,pStTstResult->bFinished,pStTstResult->szFinishedTime,pStTstResult->szCheckUser,
					  pStTstResult->szImportDate,strWhere);
		
	}else
	{
		memset(szSQl,0,sizeof(szSQl));
		sprintf(szSQl,"insert into %s(OID,TASK_OID,MODE_OID,PRODUCT_OID,\
					  PRODUCT_NAME,PRODUCT_NO,MODEL,PHASE,\
					  PRODUCT_CODE,MODE_NAME,MODE_TYPE, MODE_ROWVAR,PICNUM_COUNT,\
					  DIANSHI_TEST,PERCENT,FINISHED,FINISHED_TIME,CHECK_USER,SEND_DATE,IMPORT_DATE,BASE_OID,TASK_NAME) \
					  values (%d,%d,%d,%d,'%s','%s','%s','%s',  \
					  '%s','%s',%d,%d,%d,  %d,%d,%d,'%s','%s', to_date('%s','YYYY_MM_DD HH24:MI:SS'), to_date('%s','YYYY_MM_DD HH24:MI:SS'),%d,'%s')",
					  strTabName,
					  pStTstResult->nOid,pStTstResult->nTaskOid,pStTstResult->nModeOid,pStTstResult->nProductOid,
					  pStTstResult->szProductName,pStTstResult->szProductNo,pStTstResult->szModel,pStTstResult->szPhase,
					  pStTstResult->szProductCode,pStTstResult->szModeName,pStTstResult->nModeType,pStTstResult->nModeRowVar,pStTstResult->nPicNumCount,
					  pStTstResult->nDianshiTest,pStTstResult->nPercent,pStTstResult->bFinished,pStTstResult->szFinishedTime,pStTstResult->szCheckUser,
					  pStTstResult->szSendDate,pStTstResult->szImportDate,pStTstResult->nBaseOid,pStTstResult->szTaskName);
		strWhere.Format(_T("where OID=%d"),pStTstResult->nOid);

	}
	



	
	if(!m_DMng.UpdateDataInfo(szSQl))
	{
		CString strText;
		strText.Format("插入任务基础表失败!产品编号:%s,模板:%s",
			pStTstResult->szProductCode,pStTstResult->szModeName);
		g_MainFram->m_wndOutput.InsertErrorText(strText);
		return FALSE;
	}else
	{
		//将采集的数据文件保存到数据库中//
		
		CStdioFile file;
		CFileException e;
		char *strFileInfo;
		char szSQl[1024];

		CString strPath;
		strPath.Format( _T("%s//%s//%s"),
			g_WorkPath, 
			PATH_XML_MODE_PAR_CFG, 
			MD_XML_FILE_TAB_OUT_INFO);
		if(!file.Open(strPath, CFile::modeNoTruncate | CFile::modeRead, &e))
		{
			char szMsg[128] = {0};
			e.GetErrorMessage(szMsg, 128);

			CString strErr;
			strErr.Format(_T("打开数据库日志文件失败，原因为: %s"), szMsg);
			g_MainFram->m_wndOutput.InsertErrorText(strErr);
			return FALSE;
		}
		UINT nLen = file.GetLength();

		strFileInfo = new char[nLen+1];
		memset(strFileInfo, 0, nLen+1);
		file.Read((void*)strFileInfo,nLen);
		file.Close();

		if(!strFileInfo || !nLen)
		{
			return 0;
		}
		memset(szSQl,0,sizeof(szSQl));
		sprintf(szSQl,"update %s set %s=empty_blob() %s",
			strTabName,DataField,strWhere);

		if(!m_DMng.UpdateDataInfo(szSQl))
		{
			g_MainFram->m_wndOutput.InsertErrorText(_T("置空失败"));
			return 0;
		}
		memset(szSQl,0,sizeof(szSQl));
		sprintf(szSQl, "select %s from %s %s for update",
			DataField,strTabName,strWhere);

		if(!m_DMng.UpdateOracleBlob(szSQl,DataField.GetBuffer(0),strFileInfo,nLen))
		{
			g_MainFram->m_wndOutput.InsertErrorText(_T("写入失败"));
			return 0;
		}

		delete strFileInfo;
		strFileInfo = NULL;



		strPath.Format( _T("%s//%s//%s"),
			g_WorkPath, 
			PATH_XML_MODE_PAR_CFG, 
			MD_XML_FILE_TAB_SRT_INFO);
		if(!file.Open(strPath, CFile::modeNoTruncate | CFile::modeRead, &e))
		{
			char szMsg[128] = {0};
			e.GetErrorMessage(szMsg, 128);

			CString strErr;
			strErr.Format(_T("打开数据库日志文件失败，原因为: %s"), szMsg);
			g_MainFram->m_wndOutput.InsertErrorText(strErr);
			return FALSE;
		}
		nLen = 0;
		nLen = file.GetLength();

		strFileInfo = new char[nLen+1];
		memset(strFileInfo, 0, nLen+1);
		file.Read((void*)strFileInfo,nLen);
		file.Close();

		if(!strFileInfo || !nLen)
		{
			return 0;
		}
		memset(szSQl,0,sizeof(szSQl));
		sprintf(szSQl,"update %s set %s=empty_blob() %s",
			strTabName,ModeField,strWhere);

		if(!m_DMng.UpdateDataInfo(szSQl))
		{
			g_MainFram->m_wndOutput.InsertErrorText(_T("置空失败"));
			return 0;
		}
		memset(szSQl,0,sizeof(szSQl));
		sprintf(szSQl, "select %s from %s %s for update",
			ModeField,strTabName,strWhere);

		if(!m_DMng.UpdateOracleBlob(szSQl,ModeField.GetBuffer(0),strFileInfo,nLen))
		{
			g_MainFram->m_wndOutput.InsertErrorText(_T("写入失败"));
			return 0;
		}

		delete strFileInfo;
		strFileInfo = NULL;


		strPath.Format( _T("%s//%s//%s"),
			g_WorkPath, 
			PATH_XML_LOADOUT_TASK_CFG, 
			File_Xml_LoadOut_TaskInfo);
		if(!file.Open(strPath, CFile::modeNoTruncate | CFile::modeRead, &e))
		{
			char szMsg[128] = {0};
			e.GetErrorMessage(szMsg, 128);

			CString strErr;
			strErr.Format(_T("打开数据库日志文件失败，原因为: %s"), szMsg);
			g_MainFram->m_wndOutput.InsertErrorText(strErr);
			return FALSE;
		}
		nLen = 0;
		nLen = file.GetLength();

		strFileInfo = new char[nLen+1];
		memset(strFileInfo, 0, nLen+1);
		file.Read((void*)strFileInfo,nLen);
		file.Close();

		if(!strFileInfo || !nLen)
		{
			return 0;
		}
		memset(szSQl,0,sizeof(szSQl));
		sprintf(szSQl,"update %s set %s=empty_blob() %s",
			strTabName,TaskXmlFile,strWhere);

		if(!m_DMng.UpdateDataInfo(szSQl))
		{
			g_MainFram->m_wndOutput.InsertErrorText(_T("置空失败"));
			return 0;
		}
		memset(szSQl,0,sizeof(szSQl));
		sprintf(szSQl, "select %s from %s %s for update",
			TaskXmlFile,strTabName,strWhere);

		if(!m_DMng.UpdateOracleBlob(szSQl,TaskXmlFile.GetBuffer(0),strFileInfo,nLen))
		{
			g_MainFram->m_wndOutput.InsertErrorText(_T("写入失败"));
			return 0;
		}

		delete strFileInfo;
		strFileInfo = NULL;



	}

	//将模板配置文件保存  以及产品图号生成文件保存//

	return TRUE;
}


//ztadd for V1.1.0_2017-04-05
//====================================================================================
BOOL  CBatchImportData::DoDecFromTestDataXmlFile(  )    //执行解密_对测试结果数据XML文件
{

	CString strPath;
	strPath.Format( _T("%s//%s//%s"),
		g_WorkPath, 
		PATH_XML_MODE_PAR_CFG, 
		MD_XML_FILE_TAB_OUT_INFO);

	int       bFileExist = 1;
	char      szFileName[MAX_PATH]= {0,};

	strcpy(szFileName, strPath.GetBuffer(0));

	bFileExist = PubFun_IsFileExist(szFileName);

	if ( (g_bAddEncOrDec != 0) && (bFileExist != 0) )
	{
		//执行数据解密
		g_MainFram->m_DataEncDec.DoFileHexToAsc(szFileName, 0);

		g_MainFram->m_DataEncDec.DoFileEncryptOrDecry(szFileName, typeDoDecry, 0);
	}
	else
	{
		return 0;
	}

	return 1;
}

BOOL CBatchImportData::DoDecFromAppFile(char *szFileName)             //执行解密_对附件文件
{
	int ret;

	if (g_bAddEncOrDec != 0)
	{
		Sleep(1000);

		ret = g_MainFram->m_DataEncDec.DoFileEncryptOrDecry(szFileName, typeDoDecry, 1);
		if (ret == 0)
		{
			AfxMessageBox( _T("文件加解密数据处理失败!") );
		}

	}
	return 1;
}