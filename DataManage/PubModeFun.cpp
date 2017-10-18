#pragma once
#include "StdAfx.h"

//用户管理模块//
//获取用户类型文本//
CString GetUserTypeText(int nUserType)
{
	int i;
	CString strText = _T("");

	if ( (nUserType >=user_normal) && (nUserType<= user_admin) )
	{
		strText.Format(_T("%s"), g_UserType[nUserType]);
	}

	return strText;	
}

//交检部门模块全局函数//
BOOL AddNewUpDepart(StHrUpDepart *pUpDepartInfo)
{
	CString strText;
	if(pUpDepartInfo == NULL)
	{
		return FALSE;
	}

	int ret = 0;
	if(ret = m_DMng.IsUpDepartExists(pUpDepartInfo->szUpDepartName))
	{
		strText.Format(_T("此部门 \"%s\" 已经存在"),pUpDepartInfo->szUpDepartName);
		AfxMessageBox(strText);
		return FALSE;
	}

	if(m_DMng.AddNewUpDepart(pUpDepartInfo))
	{
		strText.Format(_T("添加部门成功! \n部门名称=%s"), pUpDepartInfo->szUpDepartName);
		AfxMessageBox(strText);
		return TRUE;
	}else
	{
		strText.Format(_T("添加部门失败! \n部门名称=%s"), pUpDepartInfo->szUpDepartName);
		AfxMessageBox(strText);
	}
	return FALSE;
}

BOOL DelTheUpDepart(StHrUpDepart *pUpDepartInfo)
{
	if(pUpDepartInfo == NULL)
	{
		return FALSE;
	}
	CString strText;
	strText.Format(_T("确定删除此部门吗? \n部门名称=%s"), pUpDepartInfo->szUpDepartName);
	if(MessageBox(NULL,strText,_T("提示"),MB_OKCANCEL|MB_ICONQUESTION) != IDOK)
	{
		return FALSE;
	}
	
	if(m_DMng.DelUpDepart(pUpDepartInfo->nOid))
	{
		strText.Format(_T("删除部门成功! \n部门名称=%s"), pUpDepartInfo->szUpDepartName);
		AfxMessageBox(strText);
		return TRUE;
	}else
	{
		strText.Format(_T("删除部门失败! \n部门名称=%s"), pUpDepartInfo->szUpDepartName);
		AfxMessageBox(strText);
	}
	return FALSE;
}

BOOL ModifyTheUpDepart(StHrUpDepart *pUpDepartInfo)
{
	if(pUpDepartInfo == NULL)
	{
		return FALSE;
	}
	//检查产品代号是否重复//

	CString strText;
	if(m_DMng.IsUpDepartExists(pUpDepartInfo->szUpDepartName))
	{
		//判断是不是自己///
		StBasProduct nProdInfo;
		memset(&nProdInfo,0,sizeof(StBasProduct));
		if(m_DMng.GetOneUpDepartInfoOID(pUpDepartInfo->nOid,pUpDepartInfo))
		{
			if(nProdInfo.nOid != pUpDepartInfo->nOid)
			{

				strText.Format(_T("此部门 \"%s\" 已经存在"),pUpDepartInfo->szUpDepartName);
				AfxMessageBox(strText);
				return FALSE;
			}
		}

	}

	if(m_DMng.EditOldUpDepart(pUpDepartInfo))
	{
		strText.Format(_T("修改部门成功! \n部门名称=%s"), pUpDepartInfo->szUpDepartName);
		AfxMessageBox(strText);
	}else
	{
		strText.Format(_T("修改部门失败! \n部门名称=%s"), pUpDepartInfo->szUpDepartName);
		AfxMessageBox(strText);
		return FALSE;
	}
	return TRUE;
}



//产品模块全局函数///
CString GetProductType(int nPicNumType)
{
	CString strText;
	if(nPicNumType>=Product_normal || nPicNumType <=Product_Line)
	{
		strText.Format(_T("%s"), g_ProdPicNumType[nPicNumType]);
	}else
	{
		strText.Format(_T(""));
	}
	return strText;
}
BOOL AddNewProd(StBasProduct *pProdInfo)
{
	CString strText;
	if(pProdInfo == NULL)
	{
		return FALSE;
	}

	strcpy(pProdInfo->szCreateUser, g_LoginUsrInfo.szUserName);
	strcpy(pProdInfo->szCreateTime, GetDateTimeString());
	if(m_DMng.AddNewProd(pProdInfo))
	{
		AddNewProductToConfig(pProdInfo);
		strText.Format(_T("添加产品成功! \n产品代号=%s"), pProdInfo->szProductNo);
		AfxMessageBox(strText);
		return TRUE;
	}else
	{
		strText.Format(_T("添加产品失败! \n产品代号=%s"), pProdInfo->szProductNo);
		AfxMessageBox(strText);
	}
	return FALSE;
}
BOOL DelTheProd(StBasProduct *pProdInfo)
{
	if(pProdInfo == NULL)
	{
		return FALSE;
	}
	CString strText;
	strText.Format(_T("确定删除此产品吗? \n产品代号=%s"), pProdInfo->szProductNo);
	//删除一项产品需要做的 步骤///
	if(MessageBox(NULL,strText,_T("提示"),MB_OKCANCEL|MB_ICONQUESTION) != IDOK)
	{
		return FALSE;
	}
	//1.产品所对应的模板 将处于未分类状态
	//2.如果有此产品导出的任务或其他任务 给出用户提示

	//3.删除 数据库的数据  删除树节点 清空控件的内容

	if(m_DMng.DelOldProd(pProdInfo->nOid))
	{
		strText.Format(_T("删除产品成功! \n产品代号=%s"), pProdInfo->szProductNo);
		AfxMessageBox(strText);
		return TRUE;
	}else
	{
		strText.Format(_T("删除产品失败! \n产品代号=%s"), pProdInfo->szProductNo);
		AfxMessageBox(strText);
	}
	return FALSE;
}

BOOL ModifyTheProd(StBasProduct *pProdInfo)
{
	if(pProdInfo == NULL)
	{
		return FALSE;
	}
	//检查产品代号是否重复//

	CString strText;
	if(m_DMng.IsProdExists(pProdInfo->nGroupOid,pProdInfo->szProductNo))
	{
		//判断是不是自己///
		StBasProduct nProdInfo;
		memset(&nProdInfo,0,sizeof(StBasProduct));
		if(m_DMng.GetProdDataGroupOidProdNo(pProdInfo->nGroupOid,pProdInfo->szProductNo,&nProdInfo))
		{
			if(nProdInfo.nOid != pProdInfo->nOid)
			{
				
				strText.Format(_T("此产品 \"%s\" 已经存在"),pProdInfo->szProductNo);
				AfxMessageBox(strText);
				return FALSE;
			}
		}

	}

	if(m_DMng.EditOldProd(pProdInfo))
	{
		strText.Format(_T("修改产品成功! \n产品代号=%s"), pProdInfo->szProductNo);
		AfxMessageBox(strText);
	}else
	{
		strText.Format(_T("修改产品失败! \n产品代号=%s"), pProdInfo->szProductNo);
		AfxMessageBox(strText);
		return FALSE;
	}
	return TRUE;
}


//模板模块全局函数///
//获取模板类型文本///
CString GetModeType(int nModeType)
{
	CString strText;
	if(nModeType>=Mode_Currency || nModeType <=Mode_NotUse)
	{
		strText.Format(_T("%s"), g_ModeType[nModeType]);
	}else
	{
		strText.Format(_T(""));
	}
	return strText;
}

//获取模板的行可变属性///
CString GetModeRowVar(int nModeRowVar)
{
	CString strText;
	if(nModeRowVar>=ModeRow_NoChange || nModeRowVar <=ModeRow_Change)
	{
		strText.Format(_T("%s"), g_ModeRowVal[nModeRowVar]);
	}else
	{
		strText.Format(_T(""));
	}
	return strText;
}

//获取模板大小的字符串///
CString GetModeSizeText(int nModeSize)
{
	int nLen = nModeSize;
	CString strText;
	if(nLen<1024)
	{
		strText.Format(_T("%d 字节"),nLen);
	}else
	{
		if(nLen >1024*1024)
		{
			if(nLen >1024*1024*1024)
			{
				double nSize = nLen/1024*1024.0;
				strText.Format(_T("%.2lf GB"),nSize);
			}else
			{
				double nSize = nLen/1024*1024.0;
				strText.Format(_T("%.2lf MB"),nSize);
			}
		}else
		{
			double nSize = nLen/1024.0;
			strText.Format(_T("%.2lf KB"),nSize);
		}
	}
	return strText;
}

//获取模板是否初始化///
CString GetModeInitStr(int nInitTabSrt)
{
	CString strText;
	if(nInitTabSrt>=1)
	{
		strText.Format(_T("是"));
	}else
	{
		strText.Format(_T("否"));
	}
	return strText;
}

int GetModeType(char *szModeType)
{
	int i = 0;
	for(i = Mode_Currency;i<= Mode_NotUse;i++)
	{
		if(strcmp(g_ModeType[i],szModeType) == 0)
		{
			break;
		}
	}

	return i;
}
int GetModeRowVar(char *szModeRowVar)
{
	int i = 0;
	for(i = ModeRow_NoChange;i<=ModeRow_Change;i++)
	{
		if(strcmp(g_ModeRowVal[i],szModeRowVar) == 0)
		{
			break;
		}
	}
	return i;
}

//组建模板数据表名称
CString GetModeTabName(StBasMode *pModeInfo)
{
	CString strText;
	if(pModeInfo->nGroupOid <=0 || pModeInfo->nOid <=0)
	{
		strText.Format(_T(""));
	}else
	{
		strText.Format(_T("%s%.4d_%.4d"),g_TstData,pModeInfo->nGroupOid,pModeInfo->nOid);
	}
	
	return strText;
}

//添加一个新模板
BOOL  AddTheMode(StBasMode *pModeInfo)
{
	CString strText;
	if(pModeInfo == NULL)
	{
		return FALSE;
	}

	//1.检查产品是否存在//
	//检查产品代号是否重复//
	UINT nGroupOid = g_CurSelDepart.nOid;
	CString strProductNo = pModeInfo->stProductInfo.szProductNo;
	if(pModeInfo->nModeType == Mode_Dedicated)
	{
		if(m_DMng.IsProdExists(nGroupOid,strProductNo.GetBuffer(0)))
		{
			//若存在///
			StBasProduct *pProdInfo = &pModeInfo->stProductInfo;
			memset(pProdInfo,0,sizeof(StBasProduct));
			if(!m_DMng.GetProdDataGroupOidProdNo(nGroupOid,strProductNo.GetBuffer(0),pProdInfo))
			{
				strText.Format(_T("获取产品信息失败! 产品代号=%s"), strProductNo);
				AfxMessageBox(strText);
				return FALSE;
			}


		}else
		{
			//若不存在///
			StBasProduct *pProdInfo = &pModeInfo->stProductInfo;
			//strcpy(pProdInfo->szProductNo, pTaskInfo->stProductInfo->szProductNo);
			//strcpy(pProdInfo->szProductName, pTaskInfo->stProductInfo->szProductName);
			pProdInfo->nGroupOid = nGroupOid;
			if(1)
			{
				pProdInfo->nPicNumType = Product_normal;
			}

			strcpy(pProdInfo->szCreateTime, GetDateTimeString());
			strcpy(pProdInfo->szCreateUser, g_LoginUsrInfo.szUserName);
			if(!m_DMng.AddNewProd(pProdInfo))
			{
				strText.Format(_T("添加产品失败! 产品代号=%s"), pProdInfo->szProductNo);
				AfxMessageBox(strText);
				return FALSE;
			}
			AddNewProductToConfig(pProdInfo);
		}
	}else
	{
		//如果不是产品专用类型, 清空产品的所有信息///
		StBasProduct *pProdInfo = &pModeInfo->stProductInfo;
		memset(pProdInfo, 0, sizeof(StBasProduct));
		memset(pModeInfo->szModel, 0, sizeof(pModeInfo->szModel));
		memset(pModeInfo->szPhase, 0, sizeof(pModeInfo->szPhase));
	}
	
	pModeInfo->nGroupOid = nGroupOid;
	strcpy(pModeInfo->szCreateUser, g_LoginUsrInfo.szUserName);
	strcpy(pModeInfo->szCreateTime, GetDateTimeString());
	if(m_DMng.AddNewMode(pModeInfo))
	{
		strText.Format(_T("添加模板成功! \n模板名称=%s"), pModeInfo->szModeName);
		AfxMessageBox(strText);
		return TRUE;
	}else
	{
		strText.Format(_T("添加模板失败! \n模板名称=%s"), pModeInfo->szModeName);
		AfxMessageBox(strText);
	}
	return FALSE;
}

//修改这个模板
BOOL  ModifyTheMode(StBasMode *pModeInfo)
{
	CString strText;
	if(pModeInfo == NULL)
	{
		return FALSE;
	}

	//1.检查产品是否存在//
	//检查产品代号是否重复//
	UINT nGroupOid = g_CurSelDepart.nOid;
	CString strProductNo = pModeInfo->stProductInfo.szProductNo;
	if(pModeInfo->nModeType == Mode_Dedicated)
	{
		if(m_DMng.IsProdExists(nGroupOid,strProductNo.GetBuffer(0)))
		{
			//若存在///
			StBasProduct *pProdInfo = &pModeInfo->stProductInfo;
			memset(pProdInfo,0,sizeof(StBasProduct));
			if(!m_DMng.GetProdDataGroupOidProdNo(nGroupOid,strProductNo.GetBuffer(0),pProdInfo))
			{
				strText.Format(_T("获取产品信息失败! 产品代号=%s"), strProductNo);
				AfxMessageBox(strText);
				return FALSE;
			}


		}else
		{
			//若不存在///
			StBasProduct *pProdInfo = &pModeInfo->stProductInfo;
			//strcpy(pProdInfo->szProductNo, pTaskInfo->stProductInfo->szProductNo);
			//strcpy(pProdInfo->szProductName, pTaskInfo->stProductInfo->szProductName);
			pProdInfo->nGroupOid = nGroupOid;
			if(1)
			{
				pProdInfo->nPicNumType = Product_normal;
			}

			strcpy(pProdInfo->szCreateTime, GetDateTimeString());
			strcpy(pProdInfo->szCreateUser, g_LoginUsrInfo.szLoginName);
			if(!m_DMng.AddNewProd(pProdInfo))
			{
				strText.Format(_T("添加产品失败! 产品代号=%s"), pProdInfo->szProductNo);
				AfxMessageBox(strText);
				return FALSE;
			}
			AddNewProductToConfig(pProdInfo);
		}
	}else
	{
		//如果不是产品专用类型, 清空产品的所有信息///
		StBasProduct *pProdInfo = &pModeInfo->stProductInfo;
		memset(pProdInfo, 0, sizeof(StBasProduct));
		memset(pModeInfo->szModel, 0, sizeof(pModeInfo->szModel));
		memset(pModeInfo->szPhase, 0, sizeof(pModeInfo->szPhase));
	}


	if(m_DMng.EditOldMode(pModeInfo))
	{
		strText.Format(_T("修改模板成功! \n模板名称=%s"), pModeInfo->szModeName);
		AfxMessageBox(strText);
	}else
	{
		strText.Format(_T("修改模板失败! \n模板名称=%s"), pModeInfo->szModeName);
		AfxMessageBox(strText);
		return FALSE;
	}

	return TRUE;
}


//删除这个模板
BOOL DelTheMode(StBasMode *pModeInfo)
{
	//删除任务是要检查几项//
	//1.检查任务状态 已完成 导出的 不能删除//
	//2.清空 当前任务的 任务编号表的所有编号///
	//3.清空 当前任务的  任务模板表的所有模板///

	if(pModeInfo->nOid <= 0)
	{
		return FALSE;
	}
	CString strText;
	strText.Format(_T("确定删除这个模板吗? \n模板名称=%s"), pModeInfo->szModeName);
	if(MessageBox(NULL, strText,_T("提示"),MB_OKCANCEL|MB_ICONQUESTION) != IDOK)
	{
		return FALSE;
	}

	if(m_DMng.DelOldMode(pModeInfo->nOid))
	{
		strText.Format(_T("删除模板成功! \n模板名称=%s"), pModeInfo->szModeName);
		AfxMessageBox(strText);
		return TRUE;
	}else
	{
		strText.Format(_T("删除模板失败! \n模板名称=%s"), pModeInfo->szModeName);
		AfxMessageBox(strText);
	}
	return TRUE;
}
//任务模块全局函数//
//获取任务类型//
CString GetTaskType(int nTaskType)
{
	CString strText;
	if(nTaskType>=Task_Test || nTaskType <=Task_HelpReTest)
	{
		strText.Format(_T("%s"), g_TaskType[nTaskType]);
	}else
	{
		strText.Format(_T(""));
	}
	return strText;
}

//获取任务状态文本///
CString GetTaskStatus(int nTaskStatus)
{
	CString strText;
	if(nTaskStatus>=Task_Init || nTaskStatus <=Task_Finish)
	{
		strText.Format(_T("%s"), g_TaskState[nTaskStatus]);
	}else
	{
		strText.Format(_T(""));
	}
	return strText;
}

//获取任务是否军检///
CString GetTaskArmyText(int nArmyTest)
{
	CString strText;
	if(nArmyTest>=1)
	{
		strText.Format(_T("是"));
	}else
	{
		strText.Format(_T("否"));
	}
	return strText;
}

//获取产品编号是否典试///
CString GetDianshiText(int nDianTest)
{
	CString strText;
	if(nDianTest>=1)
	{
		strText.Format(_T("是"));
	}else
	{
		strText.Format(_T("否"));
	}
	return strText;
}

BOOL SetTaskTypeComBoText(int nTaskType, CComboBox *pComBo)
{
	CString strText;
	int i;
	if(nTaskType < Task_Test || nTaskType >Task_HelpReTest)
	{
		return FALSE;
	}
	for (i = 0;i<pComBo->GetCount();i++)
	{
		pComBo->GetLBText(i,strText);
		if(g_TaskType[nTaskType] == strText)
		{
			pComBo->SetCurSel(i);
			return TRUE;
		}
	}

	//pComBo->SetWindowText("");
	return FALSE;
}

BOOL SetArmyTestComBoText(int nTaskType, CComboBox *pComBo)
{
	if(nTaskType <0 || nTaskType >1)
	{
		nTaskType = 0;
	}

	pComBo->SetCurSel(nTaskType);

	return TRUE;
}

//添加一项任务
BOOL AddNewTask(StBasTask *pTaskInfo,vector<CString> &strErrorArray)
{
	strErrorArray.clear();
	CString strText;
	if(pTaskInfo == NULL)
	{
		return FALSE;
	}

	//1.检查产品是否存在//
	//检查产品代号是否重复//
	UINT nGroupOid = g_CurSelDepart.nOid;
	CString strProductNo = pTaskInfo->stProductInfo.szProductNo;
	if(m_DMng.IsProdExists(nGroupOid,strProductNo.GetBuffer(0)))
	{
		//若存在///
		StBasProduct *pProdInfo = &pTaskInfo->stProductInfo;
		memset(pProdInfo,0,sizeof(StBasProduct));
		if(!m_DMng.GetProdDataGroupOidProdNo(nGroupOid,strProductNo.GetBuffer(0),pProdInfo))
		{
			strText.Format(_T("获取产品信息失败! 产品代号=%s"), strProductNo);
			strErrorArray.push_back(strText);
			//AfxMessageBox(strText);
			return FALSE;
		}
		

	}else
	{
		//若不存在///
		StBasProduct *pProdInfo = &pTaskInfo->stProductInfo;
		//strcpy(pProdInfo->szProductNo, pTaskInfo->stProductInfo->szProductNo);
		//strcpy(pProdInfo->szProductName, pTaskInfo->stProductInfo->szProductName);
		pProdInfo->nGroupOid = nGroupOid;
		if(1)
		{
			pProdInfo->nPicNumType = Product_normal;
		}
		
		strcpy(pProdInfo->szCreateTime, GetDateTimeString());
		strcpy(pProdInfo->szCreateUser, g_LoginUsrInfo.szUserName);
		if(!m_DMng.AddNewProd(pProdInfo))
		{
			strText.Format(_T("添加产品失败! 产品代号=%s"), pProdInfo->szProductNo);
			strErrorArray.push_back(strText);
			//AfxMessageBox(strText);
			return FALSE;
		}else
		{
			strText.Format(_T("添加产品成功! 产品代号=%s"), pProdInfo->szProductNo);
			strErrorArray.push_back(strText);
		}
		AddNewProductToConfig(pProdInfo);
	}

	//2.检查交检部门是否存在

	CString strDepartName = pTaskInfo->stHrUpDepart.szUpDepartName;
	if(m_DMng.IsUpDepartExists(strDepartName.GetBuffer(0)))
	{
		//若存在///
		StHrUpDepart *pUpDepartInfo = &pTaskInfo->stHrUpDepart;
		memset(pUpDepartInfo,0,sizeof(StHrUpDepart));
		if(!m_DMng.GetOneUpDepartInfoDepartName(strDepartName.GetBuffer(0),pUpDepartInfo))
		{
			strText.Format(_T("获取交检部门信息失败! 部门名称=%s"), strDepartName);
			strErrorArray.push_back(strText);
			//AfxMessageBox(strText);
			return FALSE;
		}


	}else
	{
		//若不存在///
		StHrUpDepart *pUpDepartInfo = &pTaskInfo->stHrUpDepart;
		
		if(!m_DMng.AddNewUpDepart(pUpDepartInfo))
		{
			strText.Format(_T("添加交检部门失败! 部门名称=%s"), pUpDepartInfo->szUpDepartName);
			strErrorArray.push_back(strText);
			//AfxMessageBox(strText);
			return FALSE;
		}else
		{
			strText.Format(_T("添加交检部门成功! 部门名称=%s"), pUpDepartInfo->szUpDepartName);
			strErrorArray.push_back(strText);
		}
		ReGetAllDepartInfo();
	}

	//------------------------------

	if(m_DMng.IsProductTaskExists(pTaskInfo->stProductInfo.nOid,pTaskInfo->stTaskBaseInfo.szTaskName))
	{
		strText.Format(_T("此任务 \"%s\" 已经存在"),pTaskInfo->stTaskBaseInfo.szTaskName);
		strErrorArray.push_back(strText);
		//AfxMessageBox(strText);
		return FALSE;
	}
	strcpy(pTaskInfo->stTaskBaseInfo.szCreateUser, g_LoginUsrInfo.szUserName);
	strcpy(pTaskInfo->stTaskBaseInfo.szCreateDate, GetDateTimeString());
	pTaskInfo->stTaskBaseInfo.nGroupOid = nGroupOid;
	if(!m_DMng.AddNewTask(pTaskInfo))
	{
		strText.Format(_T("添加任务失败! \n任务名称=%s"), pTaskInfo->stTaskBaseInfo.szTaskName);
		strErrorArray.push_back(strText);
		//AfxMessageBox(strText);
		return FALSE;
	}else
	{
		strText.Format(_T("添加任务成功! \n任务名称=%s"), pTaskInfo->stTaskBaseInfo.szTaskName);
		strErrorArray.push_back(strText);
		//AfxMessageBox(strText);
	}

	if(/*pTaskInfo->stTaskBaseInfo.nModifyType == Task_ModifyAll*/1)
	{
		//添加 任务产品编号 模板 图号//
		int i, nCount;
		//删除数据库中//
		if(!m_DMng.DelAllTaskMode(pTaskInfo->stTaskBaseInfo.nOid))
		{
			strText.Format(_T("清空数据库中任务模板失败! \n任务名称=%s"), pTaskInfo->stTaskBaseInfo.szTaskName);
			strErrorArray.push_back(strText);
		}
		if(!m_DMng.DelAllTaskCode(pTaskInfo->stTaskBaseInfo.nOid))
		{
			strText.Format(_T("清空数据库中编号失败! \n任务名称=%s"), pTaskInfo->stTaskBaseInfo.szTaskName);
			strErrorArray.push_back(strText);
		}
		if(!m_DMng.DelAllTaskPicNum(pTaskInfo->stTaskBaseInfo.nOid))
		{
			strText.Format(_T("清空数据库中图号失败! \n任务名称=%s"), pTaskInfo->stTaskBaseInfo.szTaskName);
			strErrorArray.push_back(strText);
		}

		nCount = pTaskInfo->pArryTaskMode.size();
		for (i = 0;i<nCount;i++)
		{
			pTaskInfo->pArryTaskMode.at(i)->nTaskOid = pTaskInfo->stTaskBaseInfo.nOid;
			if(m_DMng.AddNewTaskMode(pTaskInfo->pArryTaskMode.at(i)))
			{

			}
		}

		nCount = pTaskInfo->pArryTaskCode.size();
		for (i = 0;i<nCount;i++)
		{
			pTaskInfo->pArryTaskCode.at(i)->nTaskOid = pTaskInfo->stTaskBaseInfo.nOid;
			if(m_DMng.AddNewTaskCode(pTaskInfo->pArryTaskCode.at(i)))
			{

			}
		}

		nCount = pTaskInfo->pArryTaskPicNum.size();
		for (i = 0;i<nCount;i++)
		{
			pTaskInfo->pArryTaskPicNum.at(i)->nTaskOid = pTaskInfo->stTaskBaseInfo.nOid;
			if(m_DMng.AddNewTaskPicNum(pTaskInfo->pArryTaskPicNum.at(i)))
			{

			}
		}
		

	}
	

	return TRUE;
}
//修改本次任务//
BOOL ModifyTheTask(StBasTask *pTaskInfo,vector<CString> &strErrorArray)
{

	strErrorArray.clear();
	UINT nGroupOid;
	CString strText,strProductNo;
	if(pTaskInfo == NULL)
	{
		return FALSE;
	}
	
	//1.检查产品是否存在//
	//检查产品代号是否重复//
	nGroupOid = g_CurSelDepart.nOid;
	strProductNo = pTaskInfo->stProductInfo.szProductNo;
	if(m_DMng.IsProdExists(nGroupOid,strProductNo.GetBuffer(0)))
	{
		//若存在///
		StBasProduct *pProdInfo = &pTaskInfo->stProductInfo;
		memset(pProdInfo,0,sizeof(StBasProduct));
		if(!m_DMng.GetProdDataGroupOidProdNo(nGroupOid,strProductNo.GetBuffer(0),pProdInfo))
		{
			strText.Format(_T("获取产品信息失败! 产品代号=%s"), strProductNo);
			strErrorArray.push_back(strText);
			//AfxMessageBox(strText);
			return FALSE;
		}


	}else
	{
		//若不存在///
		StBasProduct *pProdInfo = &pTaskInfo->stProductInfo;
		//strcpy(pProdInfo->szProductNo, pTaskInfo->stProductInfo->szProductNo);
		//strcpy(pProdInfo->szProductName, pTaskInfo->stProductInfo->szProductName);
		pProdInfo->nGroupOid = nGroupOid;
		if(1)
		{
			pProdInfo->nPicNumType = Product_normal;
		}

		strcpy(pProdInfo->szCreateTime, GetDateTimeString());
		strcpy(pProdInfo->szCreateUser, g_LoginUsrInfo.szUserName);
		if(!m_DMng.AddNewProd(pProdInfo))
		{
			strText.Format(_T("添加产品失败! 产品代号=%s"), pProdInfo->szProductNo);
			//AfxMessageBox(strText);
			strErrorArray.push_back(strText);
			return FALSE;
		}else
		{
			strText.Format(_T("添加产品成功! 产品代号=%s"), pProdInfo->szProductNo);
			strErrorArray.push_back(strText);
		}
		AddNewProductToConfig(pProdInfo);
	}

	//2.检查交检部门是否存在

	CString strDepartName = pTaskInfo->stHrUpDepart.szUpDepartName;
	if(m_DMng.IsUpDepartExists(strDepartName.GetBuffer(0)))
	{
		//若存在///
		StHrUpDepart *pUpDepartInfo = &pTaskInfo->stHrUpDepart;
		memset(pUpDepartInfo,0,sizeof(StHrUpDepart));
		if(!m_DMng.GetOneUpDepartInfoDepartName(strDepartName.GetBuffer(0),pUpDepartInfo))
		{
			strText.Format(_T("获取交检部门信息失败! 部门名称=%s"), strDepartName);
			strErrorArray.push_back(strText);
			//AfxMessageBox(strText);
			return FALSE;
		}


	}else
	{
		//若不存在///
		StHrUpDepart *pUpDepartInfo = &pTaskInfo->stHrUpDepart;

		if(!m_DMng.AddNewUpDepart(pUpDepartInfo))
		{
			strText.Format(_T("添加交检部门失败! 部门名称=%s"), pUpDepartInfo->szUpDepartName);
			strErrorArray.push_back(strText);
			//AfxMessageBox(strText);
			return FALSE;
		}else
		{
			strText.Format(_T("添加交检部门成功! 部门名称=%s"), pUpDepartInfo->szUpDepartName);
			strErrorArray.push_back(strText);
		}
		ReGetAllDepartInfo();
	}

	//------------------------------


	if(m_DMng.IsProductTaskExists(pTaskInfo->stProductInfo.nOid,pTaskInfo->stTaskBaseInfo.szTaskName))
	{
		//判断是不是自己///
		StBasTask nTaskInfo;
		nTaskInfo.Release();
		if(m_DMng.GetTaskDataProdOidTaskName(pTaskInfo->stProductInfo.nOid,pTaskInfo->stTaskBaseInfo.szTaskName,&nTaskInfo))
		{
			if(nTaskInfo.stProductInfo.nOid != pTaskInfo->stProductInfo.nOid)
			{

				strText.Format(_T("此任务 \"%s\" 已经存在"),pTaskInfo->stTaskBaseInfo.szTaskName);
				strErrorArray.push_back(strText);
				//AfxMessageBox(strText);
				return FALSE;
			}
		}

	}

	if(m_DMng.EditOldTask(pTaskInfo))
	{
		strText.Format(_T("修改任务成功! \n任务名称=%s"), pTaskInfo->stTaskBaseInfo.szTaskName);
		strErrorArray.push_back(strText);
		//AfxMessageBox(strText);
	}else
	{
		strText.Format(_T("修改任务失败! \n任务名称=%s"), pTaskInfo->stTaskBaseInfo.szTaskName);
		strErrorArray.push_back(strText);
		//AfxMessageBox(strText);
		return FALSE;
	}

	if(pTaskInfo->stTaskBaseInfo.nModifyType == Task_ModifyAll)
	{
		//添加 任务产品编号 模板 图号//
		int i, nCount;
		//删除数据库中//
		if(!m_DMng.DelAllTaskMode(pTaskInfo->stTaskBaseInfo.nOid))
		{
			strText.Format(_T("清空数据库中任务模板失败! \n任务名称=%s"), pTaskInfo->stTaskBaseInfo.szTaskName);
			strErrorArray.push_back(strText);
		}
		if(!m_DMng.DelAllTaskCode(pTaskInfo->stTaskBaseInfo.nOid))
		{
			strText.Format(_T("清空数据库中编号失败! \n任务名称=%s"), pTaskInfo->stTaskBaseInfo.szTaskName);
			strErrorArray.push_back(strText);
		}
		if(!m_DMng.DelAllTaskPicNum(pTaskInfo->stTaskBaseInfo.nOid))
		{
			strText.Format(_T("清空数据库中图号失败! \n任务名称=%s"), pTaskInfo->stTaskBaseInfo.szTaskName);
			strErrorArray.push_back(strText);
		}

		nCount = pTaskInfo->pArryTaskMode.size();
		for (i = 0;i<nCount;i++)
		{
			if(m_DMng.AddNewTaskMode(pTaskInfo->pArryTaskMode.at(i)))
			{

			}
		}

		nCount = pTaskInfo->pArryTaskCode.size();
		for (i = 0;i<nCount;i++)
		{
			if(m_DMng.AddNewTaskCode(pTaskInfo->pArryTaskCode.at(i)))
			{

			}
		}

		nCount = pTaskInfo->pArryTaskPicNum.size();
		for (i = 0;i<nCount;i++)
		{
			if(m_DMng.AddNewTaskPicNum(pTaskInfo->pArryTaskPicNum.at(i)))
			{

			}
		}


	}
	return TRUE;
}
//删除本次任务
BOOL DelTheTask(StBasTask *pTaskInfo)
{
	//删除任务是要检查几项//
	//1.检查任务状态 已完成 导出的 不能删除//
	//2.清空 当前任务的 任务编号表的所有编号///
	//3.清空 当前任务的  任务模板表的所有模板///

	if(pTaskInfo->stTaskBaseInfo.nOid <= 0)
	{
		return FALSE;
	}
	CString strText;
	strText.Format(_T("确定删除这个任务吗? \n任务名称=%s"), pTaskInfo->stTaskBaseInfo.szTaskName);
	if(MessageBox(NULL, strText,_T("提示"),MB_OKCANCEL|MB_ICONQUESTION) != IDOK)
	{
		return FALSE;
	}

	if(m_DMng.DelOldTask(pTaskInfo->stTaskBaseInfo.nOid))
	{
		strText.Format(_T("删除任务成功! \n任务名称=%s"), pTaskInfo->stTaskBaseInfo.szTaskName);
		AfxMessageBox(strText);
		return TRUE;
	}else
	{
		strText.Format(_T("删除任务失败! \n任务名称=%s"), pTaskInfo->stTaskBaseInfo.szTaskName);
		AfxMessageBox(strText);
	}
	return TRUE;
}

//检测任务是否合格//
BOOL CheckTheTask(StBasTask *pTaskInfo, CString &strWarning/*提示信息*/)
{
	strWarning = _T("");
	CString strText;
	BOOL  nReturnVar = TRUE;
	//＂任务检测＂	任务合法性检测：
	//1. "任务名称" 不能为空 
	//2. "产品代号" 不能为空
	//3. ＂检验员姓名＂合法性检测，不能为空。
	//4. ＂交检部门＂不能为空。
	//5. “产品编号”数量，与编号配置个数相等，不为零。
	//6. 产品模板个数不为零，模板不为空。

	//其他//
	//1.批次号   不能为空，
	//2.检验依据   不能全为空

	int i, pos = 1;
	StBasTaskBaseInfo *pTaskBaseInfo = &pTaskInfo->stTaskBaseInfo;
	StBasProduct      *pProductInfo = &pTaskInfo->stProductInfo;
	StHrUpDepart      *pUpDepart = &pTaskInfo->stHrUpDepart;

	vector<StBasTaskMode *> *pArryTaskMode = &pTaskInfo->pArryTaskMode;
	//1.
	if(strcmp(pTaskBaseInfo->szTaskName, _T("")) == 0)
	{
		strText.Format(_T("%d.任务名称不能为空!\n"), pos++);
		strWarning+=strText;
		nReturnVar = FALSE;
	}

	//2.
	if(strcmp(pProductInfo->szProductNo, _T("")) == 0)
	{
		strText.Format(_T("%d.产品代号不能为空!\n"), pos++);
		strWarning+=strText;
		nReturnVar = FALSE;
	}

	//3.
	/*if(strcmp(pTaskBaseInfo->szCheckUser, _T("")) == 0)
	{
		strText.Format(_T("%d.检验员姓名不能为空!\n"), pos++);
		strWarning+=strText;
		nReturnVar = FALSE;
	}*/

	//4.
	if(strcmp(pUpDepart->szUpDepartName, _T("")) == 0)
	{
		strText.Format(_T("%d.交检部门不能为空!\n"), pos++);
		strWarning+=strText;
		nReturnVar = FALSE;
	}

	//5.
	int nNum = pTaskInfo->pArryTaskCode.size();

	int nRows = pTaskBaseInfo->nCodeNumber;

	if(nNum !=nRows)
	{
		strText.Format(_T("%d.任务要求检查 %d 项产品，实际选择了 %d 项!\n"),pos++,nRows,nNum);
		strWarning+=strText;
		nReturnVar = FALSE;
	}

	//6.
	int nModeCount = pTaskInfo->pArryTaskMode.size();
	int nModeOid = 0;
	if(nModeCount<=0)
	{
		strText.Format(_T("%d.此任务没有选择任何模板!\n"),pos++);
		strWarning+=strText;
		nReturnVar = FALSE;
	}

	char *strXmlFile = NULL;
	int  nLen;
	//7.//检查模板是否为空//
	for(i = 0;i< nModeCount;i++)
	{
		nLen = 0;
		strXmlFile = NULL;
		nModeOid = pArryTaskMode->at(i)->nModeOid;
		m_DMng.GetModeXmlFile(nModeOid,&strXmlFile,nLen);//16.获取XML模板文件

		if(nLen>0 || strXmlFile != NULL)
		{
			delete []strXmlFile;
		}else
		{
			strText.Format(_T("%d.模板=%s, 配置为空!\n"),pos++, pArryTaskMode->at(i)->szModeName);
			strWarning+=strText;
			nReturnVar = FALSE;
		}
		
	}

	
	return nReturnVar;
}