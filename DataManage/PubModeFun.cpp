#pragma once
#include "StdAfx.h"

//�û�����ģ��//
//��ȡ�û������ı�//
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

//���첿��ģ��ȫ�ֺ���//
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
		strText.Format(_T("�˲��� \"%s\" �Ѿ�����"),pUpDepartInfo->szUpDepartName);
		AfxMessageBox(strText);
		return FALSE;
	}

	if(m_DMng.AddNewUpDepart(pUpDepartInfo))
	{
		strText.Format(_T("��Ӳ��ųɹ�! \n��������=%s"), pUpDepartInfo->szUpDepartName);
		AfxMessageBox(strText);
		return TRUE;
	}else
	{
		strText.Format(_T("��Ӳ���ʧ��! \n��������=%s"), pUpDepartInfo->szUpDepartName);
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
	strText.Format(_T("ȷ��ɾ���˲�����? \n��������=%s"), pUpDepartInfo->szUpDepartName);
	if(MessageBox(NULL,strText,_T("��ʾ"),MB_OKCANCEL|MB_ICONQUESTION) != IDOK)
	{
		return FALSE;
	}
	
	if(m_DMng.DelUpDepart(pUpDepartInfo->nOid))
	{
		strText.Format(_T("ɾ�����ųɹ�! \n��������=%s"), pUpDepartInfo->szUpDepartName);
		AfxMessageBox(strText);
		return TRUE;
	}else
	{
		strText.Format(_T("ɾ������ʧ��! \n��������=%s"), pUpDepartInfo->szUpDepartName);
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
	//����Ʒ�����Ƿ��ظ�//

	CString strText;
	if(m_DMng.IsUpDepartExists(pUpDepartInfo->szUpDepartName))
	{
		//�ж��ǲ����Լ�///
		StBasProduct nProdInfo;
		memset(&nProdInfo,0,sizeof(StBasProduct));
		if(m_DMng.GetOneUpDepartInfoOID(pUpDepartInfo->nOid,pUpDepartInfo))
		{
			if(nProdInfo.nOid != pUpDepartInfo->nOid)
			{

				strText.Format(_T("�˲��� \"%s\" �Ѿ�����"),pUpDepartInfo->szUpDepartName);
				AfxMessageBox(strText);
				return FALSE;
			}
		}

	}

	if(m_DMng.EditOldUpDepart(pUpDepartInfo))
	{
		strText.Format(_T("�޸Ĳ��ųɹ�! \n��������=%s"), pUpDepartInfo->szUpDepartName);
		AfxMessageBox(strText);
	}else
	{
		strText.Format(_T("�޸Ĳ���ʧ��! \n��������=%s"), pUpDepartInfo->szUpDepartName);
		AfxMessageBox(strText);
		return FALSE;
	}
	return TRUE;
}



//��Ʒģ��ȫ�ֺ���///
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
		strText.Format(_T("��Ӳ�Ʒ�ɹ�! \n��Ʒ����=%s"), pProdInfo->szProductNo);
		AfxMessageBox(strText);
		return TRUE;
	}else
	{
		strText.Format(_T("��Ӳ�Ʒʧ��! \n��Ʒ����=%s"), pProdInfo->szProductNo);
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
	strText.Format(_T("ȷ��ɾ���˲�Ʒ��? \n��Ʒ����=%s"), pProdInfo->szProductNo);
	//ɾ��һ���Ʒ��Ҫ���� ����///
	if(MessageBox(NULL,strText,_T("��ʾ"),MB_OKCANCEL|MB_ICONQUESTION) != IDOK)
	{
		return FALSE;
	}
	//1.��Ʒ����Ӧ��ģ�� ������δ����״̬
	//2.����д˲�Ʒ������������������� �����û���ʾ

	//3.ɾ�� ���ݿ������  ɾ�����ڵ� ��տؼ�������

	if(m_DMng.DelOldProd(pProdInfo->nOid))
	{
		strText.Format(_T("ɾ����Ʒ�ɹ�! \n��Ʒ����=%s"), pProdInfo->szProductNo);
		AfxMessageBox(strText);
		return TRUE;
	}else
	{
		strText.Format(_T("ɾ����Ʒʧ��! \n��Ʒ����=%s"), pProdInfo->szProductNo);
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
	//����Ʒ�����Ƿ��ظ�//

	CString strText;
	if(m_DMng.IsProdExists(pProdInfo->nGroupOid,pProdInfo->szProductNo))
	{
		//�ж��ǲ����Լ�///
		StBasProduct nProdInfo;
		memset(&nProdInfo,0,sizeof(StBasProduct));
		if(m_DMng.GetProdDataGroupOidProdNo(pProdInfo->nGroupOid,pProdInfo->szProductNo,&nProdInfo))
		{
			if(nProdInfo.nOid != pProdInfo->nOid)
			{
				
				strText.Format(_T("�˲�Ʒ \"%s\" �Ѿ�����"),pProdInfo->szProductNo);
				AfxMessageBox(strText);
				return FALSE;
			}
		}

	}

	if(m_DMng.EditOldProd(pProdInfo))
	{
		strText.Format(_T("�޸Ĳ�Ʒ�ɹ�! \n��Ʒ����=%s"), pProdInfo->szProductNo);
		AfxMessageBox(strText);
	}else
	{
		strText.Format(_T("�޸Ĳ�Ʒʧ��! \n��Ʒ����=%s"), pProdInfo->szProductNo);
		AfxMessageBox(strText);
		return FALSE;
	}
	return TRUE;
}


//ģ��ģ��ȫ�ֺ���///
//��ȡģ�������ı�///
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

//��ȡģ����пɱ�����///
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

//��ȡģ���С���ַ���///
CString GetModeSizeText(int nModeSize)
{
	int nLen = nModeSize;
	CString strText;
	if(nLen<1024)
	{
		strText.Format(_T("%d �ֽ�"),nLen);
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

//��ȡģ���Ƿ��ʼ��///
CString GetModeInitStr(int nInitTabSrt)
{
	CString strText;
	if(nInitTabSrt>=1)
	{
		strText.Format(_T("��"));
	}else
	{
		strText.Format(_T("��"));
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

//�齨ģ�����ݱ�����
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

//���һ����ģ��
BOOL  AddTheMode(StBasMode *pModeInfo)
{
	CString strText;
	if(pModeInfo == NULL)
	{
		return FALSE;
	}

	//1.����Ʒ�Ƿ����//
	//����Ʒ�����Ƿ��ظ�//
	UINT nGroupOid = g_CurSelDepart.nOid;
	CString strProductNo = pModeInfo->stProductInfo.szProductNo;
	if(pModeInfo->nModeType == Mode_Dedicated)
	{
		if(m_DMng.IsProdExists(nGroupOid,strProductNo.GetBuffer(0)))
		{
			//������///
			StBasProduct *pProdInfo = &pModeInfo->stProductInfo;
			memset(pProdInfo,0,sizeof(StBasProduct));
			if(!m_DMng.GetProdDataGroupOidProdNo(nGroupOid,strProductNo.GetBuffer(0),pProdInfo))
			{
				strText.Format(_T("��ȡ��Ʒ��Ϣʧ��! ��Ʒ����=%s"), strProductNo);
				AfxMessageBox(strText);
				return FALSE;
			}


		}else
		{
			//��������///
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
				strText.Format(_T("��Ӳ�Ʒʧ��! ��Ʒ����=%s"), pProdInfo->szProductNo);
				AfxMessageBox(strText);
				return FALSE;
			}
			AddNewProductToConfig(pProdInfo);
		}
	}else
	{
		//������ǲ�Ʒר������, ��ղ�Ʒ��������Ϣ///
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
		strText.Format(_T("���ģ��ɹ�! \nģ������=%s"), pModeInfo->szModeName);
		AfxMessageBox(strText);
		return TRUE;
	}else
	{
		strText.Format(_T("���ģ��ʧ��! \nģ������=%s"), pModeInfo->szModeName);
		AfxMessageBox(strText);
	}
	return FALSE;
}

//�޸����ģ��
BOOL  ModifyTheMode(StBasMode *pModeInfo)
{
	CString strText;
	if(pModeInfo == NULL)
	{
		return FALSE;
	}

	//1.����Ʒ�Ƿ����//
	//����Ʒ�����Ƿ��ظ�//
	UINT nGroupOid = g_CurSelDepart.nOid;
	CString strProductNo = pModeInfo->stProductInfo.szProductNo;
	if(pModeInfo->nModeType == Mode_Dedicated)
	{
		if(m_DMng.IsProdExists(nGroupOid,strProductNo.GetBuffer(0)))
		{
			//������///
			StBasProduct *pProdInfo = &pModeInfo->stProductInfo;
			memset(pProdInfo,0,sizeof(StBasProduct));
			if(!m_DMng.GetProdDataGroupOidProdNo(nGroupOid,strProductNo.GetBuffer(0),pProdInfo))
			{
				strText.Format(_T("��ȡ��Ʒ��Ϣʧ��! ��Ʒ����=%s"), strProductNo);
				AfxMessageBox(strText);
				return FALSE;
			}


		}else
		{
			//��������///
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
				strText.Format(_T("��Ӳ�Ʒʧ��! ��Ʒ����=%s"), pProdInfo->szProductNo);
				AfxMessageBox(strText);
				return FALSE;
			}
			AddNewProductToConfig(pProdInfo);
		}
	}else
	{
		//������ǲ�Ʒר������, ��ղ�Ʒ��������Ϣ///
		StBasProduct *pProdInfo = &pModeInfo->stProductInfo;
		memset(pProdInfo, 0, sizeof(StBasProduct));
		memset(pModeInfo->szModel, 0, sizeof(pModeInfo->szModel));
		memset(pModeInfo->szPhase, 0, sizeof(pModeInfo->szPhase));
	}


	if(m_DMng.EditOldMode(pModeInfo))
	{
		strText.Format(_T("�޸�ģ��ɹ�! \nģ������=%s"), pModeInfo->szModeName);
		AfxMessageBox(strText);
	}else
	{
		strText.Format(_T("�޸�ģ��ʧ��! \nģ������=%s"), pModeInfo->szModeName);
		AfxMessageBox(strText);
		return FALSE;
	}

	return TRUE;
}


//ɾ�����ģ��
BOOL DelTheMode(StBasMode *pModeInfo)
{
	//ɾ��������Ҫ��鼸��//
	//1.�������״̬ ����� ������ ����ɾ��//
	//2.��� ��ǰ����� �����ű�����б��///
	//3.��� ��ǰ�����  ����ģ��������ģ��///

	if(pModeInfo->nOid <= 0)
	{
		return FALSE;
	}
	CString strText;
	strText.Format(_T("ȷ��ɾ�����ģ����? \nģ������=%s"), pModeInfo->szModeName);
	if(MessageBox(NULL, strText,_T("��ʾ"),MB_OKCANCEL|MB_ICONQUESTION) != IDOK)
	{
		return FALSE;
	}

	if(m_DMng.DelOldMode(pModeInfo->nOid))
	{
		strText.Format(_T("ɾ��ģ��ɹ�! \nģ������=%s"), pModeInfo->szModeName);
		AfxMessageBox(strText);
		return TRUE;
	}else
	{
		strText.Format(_T("ɾ��ģ��ʧ��! \nģ������=%s"), pModeInfo->szModeName);
		AfxMessageBox(strText);
	}
	return TRUE;
}
//����ģ��ȫ�ֺ���//
//��ȡ��������//
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

//��ȡ����״̬�ı�///
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

//��ȡ�����Ƿ����///
CString GetTaskArmyText(int nArmyTest)
{
	CString strText;
	if(nArmyTest>=1)
	{
		strText.Format(_T("��"));
	}else
	{
		strText.Format(_T("��"));
	}
	return strText;
}

//��ȡ��Ʒ����Ƿ����///
CString GetDianshiText(int nDianTest)
{
	CString strText;
	if(nDianTest>=1)
	{
		strText.Format(_T("��"));
	}else
	{
		strText.Format(_T("��"));
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

//���һ������
BOOL AddNewTask(StBasTask *pTaskInfo,vector<CString> &strErrorArray)
{
	strErrorArray.clear();
	CString strText;
	if(pTaskInfo == NULL)
	{
		return FALSE;
	}

	//1.����Ʒ�Ƿ����//
	//����Ʒ�����Ƿ��ظ�//
	UINT nGroupOid = g_CurSelDepart.nOid;
	CString strProductNo = pTaskInfo->stProductInfo.szProductNo;
	if(m_DMng.IsProdExists(nGroupOid,strProductNo.GetBuffer(0)))
	{
		//������///
		StBasProduct *pProdInfo = &pTaskInfo->stProductInfo;
		memset(pProdInfo,0,sizeof(StBasProduct));
		if(!m_DMng.GetProdDataGroupOidProdNo(nGroupOid,strProductNo.GetBuffer(0),pProdInfo))
		{
			strText.Format(_T("��ȡ��Ʒ��Ϣʧ��! ��Ʒ����=%s"), strProductNo);
			strErrorArray.push_back(strText);
			//AfxMessageBox(strText);
			return FALSE;
		}
		

	}else
	{
		//��������///
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
			strText.Format(_T("��Ӳ�Ʒʧ��! ��Ʒ����=%s"), pProdInfo->szProductNo);
			strErrorArray.push_back(strText);
			//AfxMessageBox(strText);
			return FALSE;
		}else
		{
			strText.Format(_T("��Ӳ�Ʒ�ɹ�! ��Ʒ����=%s"), pProdInfo->szProductNo);
			strErrorArray.push_back(strText);
		}
		AddNewProductToConfig(pProdInfo);
	}

	//2.��齻�첿���Ƿ����

	CString strDepartName = pTaskInfo->stHrUpDepart.szUpDepartName;
	if(m_DMng.IsUpDepartExists(strDepartName.GetBuffer(0)))
	{
		//������///
		StHrUpDepart *pUpDepartInfo = &pTaskInfo->stHrUpDepart;
		memset(pUpDepartInfo,0,sizeof(StHrUpDepart));
		if(!m_DMng.GetOneUpDepartInfoDepartName(strDepartName.GetBuffer(0),pUpDepartInfo))
		{
			strText.Format(_T("��ȡ���첿����Ϣʧ��! ��������=%s"), strDepartName);
			strErrorArray.push_back(strText);
			//AfxMessageBox(strText);
			return FALSE;
		}


	}else
	{
		//��������///
		StHrUpDepart *pUpDepartInfo = &pTaskInfo->stHrUpDepart;
		
		if(!m_DMng.AddNewUpDepart(pUpDepartInfo))
		{
			strText.Format(_T("��ӽ��첿��ʧ��! ��������=%s"), pUpDepartInfo->szUpDepartName);
			strErrorArray.push_back(strText);
			//AfxMessageBox(strText);
			return FALSE;
		}else
		{
			strText.Format(_T("��ӽ��첿�ųɹ�! ��������=%s"), pUpDepartInfo->szUpDepartName);
			strErrorArray.push_back(strText);
		}
		ReGetAllDepartInfo();
	}

	//------------------------------

	if(m_DMng.IsProductTaskExists(pTaskInfo->stProductInfo.nOid,pTaskInfo->stTaskBaseInfo.szTaskName))
	{
		strText.Format(_T("������ \"%s\" �Ѿ�����"),pTaskInfo->stTaskBaseInfo.szTaskName);
		strErrorArray.push_back(strText);
		//AfxMessageBox(strText);
		return FALSE;
	}
	strcpy(pTaskInfo->stTaskBaseInfo.szCreateUser, g_LoginUsrInfo.szUserName);
	strcpy(pTaskInfo->stTaskBaseInfo.szCreateDate, GetDateTimeString());
	pTaskInfo->stTaskBaseInfo.nGroupOid = nGroupOid;
	if(!m_DMng.AddNewTask(pTaskInfo))
	{
		strText.Format(_T("�������ʧ��! \n��������=%s"), pTaskInfo->stTaskBaseInfo.szTaskName);
		strErrorArray.push_back(strText);
		//AfxMessageBox(strText);
		return FALSE;
	}else
	{
		strText.Format(_T("�������ɹ�! \n��������=%s"), pTaskInfo->stTaskBaseInfo.szTaskName);
		strErrorArray.push_back(strText);
		//AfxMessageBox(strText);
	}

	if(/*pTaskInfo->stTaskBaseInfo.nModifyType == Task_ModifyAll*/1)
	{
		//��� �����Ʒ��� ģ�� ͼ��//
		int i, nCount;
		//ɾ�����ݿ���//
		if(!m_DMng.DelAllTaskMode(pTaskInfo->stTaskBaseInfo.nOid))
		{
			strText.Format(_T("������ݿ�������ģ��ʧ��! \n��������=%s"), pTaskInfo->stTaskBaseInfo.szTaskName);
			strErrorArray.push_back(strText);
		}
		if(!m_DMng.DelAllTaskCode(pTaskInfo->stTaskBaseInfo.nOid))
		{
			strText.Format(_T("������ݿ��б��ʧ��! \n��������=%s"), pTaskInfo->stTaskBaseInfo.szTaskName);
			strErrorArray.push_back(strText);
		}
		if(!m_DMng.DelAllTaskPicNum(pTaskInfo->stTaskBaseInfo.nOid))
		{
			strText.Format(_T("������ݿ���ͼ��ʧ��! \n��������=%s"), pTaskInfo->stTaskBaseInfo.szTaskName);
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
//�޸ı�������//
BOOL ModifyTheTask(StBasTask *pTaskInfo,vector<CString> &strErrorArray)
{

	strErrorArray.clear();
	UINT nGroupOid;
	CString strText,strProductNo;
	if(pTaskInfo == NULL)
	{
		return FALSE;
	}
	
	//1.����Ʒ�Ƿ����//
	//����Ʒ�����Ƿ��ظ�//
	nGroupOid = g_CurSelDepart.nOid;
	strProductNo = pTaskInfo->stProductInfo.szProductNo;
	if(m_DMng.IsProdExists(nGroupOid,strProductNo.GetBuffer(0)))
	{
		//������///
		StBasProduct *pProdInfo = &pTaskInfo->stProductInfo;
		memset(pProdInfo,0,sizeof(StBasProduct));
		if(!m_DMng.GetProdDataGroupOidProdNo(nGroupOid,strProductNo.GetBuffer(0),pProdInfo))
		{
			strText.Format(_T("��ȡ��Ʒ��Ϣʧ��! ��Ʒ����=%s"), strProductNo);
			strErrorArray.push_back(strText);
			//AfxMessageBox(strText);
			return FALSE;
		}


	}else
	{
		//��������///
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
			strText.Format(_T("��Ӳ�Ʒʧ��! ��Ʒ����=%s"), pProdInfo->szProductNo);
			//AfxMessageBox(strText);
			strErrorArray.push_back(strText);
			return FALSE;
		}else
		{
			strText.Format(_T("��Ӳ�Ʒ�ɹ�! ��Ʒ����=%s"), pProdInfo->szProductNo);
			strErrorArray.push_back(strText);
		}
		AddNewProductToConfig(pProdInfo);
	}

	//2.��齻�첿���Ƿ����

	CString strDepartName = pTaskInfo->stHrUpDepart.szUpDepartName;
	if(m_DMng.IsUpDepartExists(strDepartName.GetBuffer(0)))
	{
		//������///
		StHrUpDepart *pUpDepartInfo = &pTaskInfo->stHrUpDepart;
		memset(pUpDepartInfo,0,sizeof(StHrUpDepart));
		if(!m_DMng.GetOneUpDepartInfoDepartName(strDepartName.GetBuffer(0),pUpDepartInfo))
		{
			strText.Format(_T("��ȡ���첿����Ϣʧ��! ��������=%s"), strDepartName);
			strErrorArray.push_back(strText);
			//AfxMessageBox(strText);
			return FALSE;
		}


	}else
	{
		//��������///
		StHrUpDepart *pUpDepartInfo = &pTaskInfo->stHrUpDepart;

		if(!m_DMng.AddNewUpDepart(pUpDepartInfo))
		{
			strText.Format(_T("��ӽ��첿��ʧ��! ��������=%s"), pUpDepartInfo->szUpDepartName);
			strErrorArray.push_back(strText);
			//AfxMessageBox(strText);
			return FALSE;
		}else
		{
			strText.Format(_T("��ӽ��첿�ųɹ�! ��������=%s"), pUpDepartInfo->szUpDepartName);
			strErrorArray.push_back(strText);
		}
		ReGetAllDepartInfo();
	}

	//------------------------------


	if(m_DMng.IsProductTaskExists(pTaskInfo->stProductInfo.nOid,pTaskInfo->stTaskBaseInfo.szTaskName))
	{
		//�ж��ǲ����Լ�///
		StBasTask nTaskInfo;
		nTaskInfo.Release();
		if(m_DMng.GetTaskDataProdOidTaskName(pTaskInfo->stProductInfo.nOid,pTaskInfo->stTaskBaseInfo.szTaskName,&nTaskInfo))
		{
			if(nTaskInfo.stProductInfo.nOid != pTaskInfo->stProductInfo.nOid)
			{

				strText.Format(_T("������ \"%s\" �Ѿ�����"),pTaskInfo->stTaskBaseInfo.szTaskName);
				strErrorArray.push_back(strText);
				//AfxMessageBox(strText);
				return FALSE;
			}
		}

	}

	if(m_DMng.EditOldTask(pTaskInfo))
	{
		strText.Format(_T("�޸�����ɹ�! \n��������=%s"), pTaskInfo->stTaskBaseInfo.szTaskName);
		strErrorArray.push_back(strText);
		//AfxMessageBox(strText);
	}else
	{
		strText.Format(_T("�޸�����ʧ��! \n��������=%s"), pTaskInfo->stTaskBaseInfo.szTaskName);
		strErrorArray.push_back(strText);
		//AfxMessageBox(strText);
		return FALSE;
	}

	if(pTaskInfo->stTaskBaseInfo.nModifyType == Task_ModifyAll)
	{
		//��� �����Ʒ��� ģ�� ͼ��//
		int i, nCount;
		//ɾ�����ݿ���//
		if(!m_DMng.DelAllTaskMode(pTaskInfo->stTaskBaseInfo.nOid))
		{
			strText.Format(_T("������ݿ�������ģ��ʧ��! \n��������=%s"), pTaskInfo->stTaskBaseInfo.szTaskName);
			strErrorArray.push_back(strText);
		}
		if(!m_DMng.DelAllTaskCode(pTaskInfo->stTaskBaseInfo.nOid))
		{
			strText.Format(_T("������ݿ��б��ʧ��! \n��������=%s"), pTaskInfo->stTaskBaseInfo.szTaskName);
			strErrorArray.push_back(strText);
		}
		if(!m_DMng.DelAllTaskPicNum(pTaskInfo->stTaskBaseInfo.nOid))
		{
			strText.Format(_T("������ݿ���ͼ��ʧ��! \n��������=%s"), pTaskInfo->stTaskBaseInfo.szTaskName);
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
//ɾ����������
BOOL DelTheTask(StBasTask *pTaskInfo)
{
	//ɾ��������Ҫ��鼸��//
	//1.�������״̬ ����� ������ ����ɾ��//
	//2.��� ��ǰ����� �����ű�����б��///
	//3.��� ��ǰ�����  ����ģ��������ģ��///

	if(pTaskInfo->stTaskBaseInfo.nOid <= 0)
	{
		return FALSE;
	}
	CString strText;
	strText.Format(_T("ȷ��ɾ�����������? \n��������=%s"), pTaskInfo->stTaskBaseInfo.szTaskName);
	if(MessageBox(NULL, strText,_T("��ʾ"),MB_OKCANCEL|MB_ICONQUESTION) != IDOK)
	{
		return FALSE;
	}

	if(m_DMng.DelOldTask(pTaskInfo->stTaskBaseInfo.nOid))
	{
		strText.Format(_T("ɾ������ɹ�! \n��������=%s"), pTaskInfo->stTaskBaseInfo.szTaskName);
		AfxMessageBox(strText);
		return TRUE;
	}else
	{
		strText.Format(_T("ɾ������ʧ��! \n��������=%s"), pTaskInfo->stTaskBaseInfo.szTaskName);
		AfxMessageBox(strText);
	}
	return TRUE;
}

//��������Ƿ�ϸ�//
BOOL CheckTheTask(StBasTask *pTaskInfo, CString &strWarning/*��ʾ��Ϣ*/)
{
	strWarning = _T("");
	CString strText;
	BOOL  nReturnVar = TRUE;
	//�������⣢	����Ϸ��Լ�⣺
	//1. "��������" ����Ϊ�� 
	//2. "��Ʒ����" ����Ϊ��
	//3. ������Ա�������Ϸ��Լ�⣬����Ϊ�ա�
	//4. �����첿�ţ�����Ϊ�ա�
	//5. ����Ʒ��š��������������ø�����ȣ���Ϊ�㡣
	//6. ��Ʒģ�������Ϊ�㣬ģ�岻Ϊ�ա�

	//����//
	//1.���κ�   ����Ϊ�գ�
	//2.��������   ����ȫΪ��

	int i, pos = 1;
	StBasTaskBaseInfo *pTaskBaseInfo = &pTaskInfo->stTaskBaseInfo;
	StBasProduct      *pProductInfo = &pTaskInfo->stProductInfo;
	StHrUpDepart      *pUpDepart = &pTaskInfo->stHrUpDepart;

	vector<StBasTaskMode *> *pArryTaskMode = &pTaskInfo->pArryTaskMode;
	//1.
	if(strcmp(pTaskBaseInfo->szTaskName, _T("")) == 0)
	{
		strText.Format(_T("%d.�������Ʋ���Ϊ��!\n"), pos++);
		strWarning+=strText;
		nReturnVar = FALSE;
	}

	//2.
	if(strcmp(pProductInfo->szProductNo, _T("")) == 0)
	{
		strText.Format(_T("%d.��Ʒ���Ų���Ϊ��!\n"), pos++);
		strWarning+=strText;
		nReturnVar = FALSE;
	}

	//3.
	/*if(strcmp(pTaskBaseInfo->szCheckUser, _T("")) == 0)
	{
		strText.Format(_T("%d.����Ա��������Ϊ��!\n"), pos++);
		strWarning+=strText;
		nReturnVar = FALSE;
	}*/

	//4.
	if(strcmp(pUpDepart->szUpDepartName, _T("")) == 0)
	{
		strText.Format(_T("%d.���첿�Ų���Ϊ��!\n"), pos++);
		strWarning+=strText;
		nReturnVar = FALSE;
	}

	//5.
	int nNum = pTaskInfo->pArryTaskCode.size();

	int nRows = pTaskBaseInfo->nCodeNumber;

	if(nNum !=nRows)
	{
		strText.Format(_T("%d.����Ҫ���� %d ���Ʒ��ʵ��ѡ���� %d ��!\n"),pos++,nRows,nNum);
		strWarning+=strText;
		nReturnVar = FALSE;
	}

	//6.
	int nModeCount = pTaskInfo->pArryTaskMode.size();
	int nModeOid = 0;
	if(nModeCount<=0)
	{
		strText.Format(_T("%d.������û��ѡ���κ�ģ��!\n"),pos++);
		strWarning+=strText;
		nReturnVar = FALSE;
	}

	char *strXmlFile = NULL;
	int  nLen;
	//7.//���ģ���Ƿ�Ϊ��//
	for(i = 0;i< nModeCount;i++)
	{
		nLen = 0;
		strXmlFile = NULL;
		nModeOid = pArryTaskMode->at(i)->nModeOid;
		m_DMng.GetModeXmlFile(nModeOid,&strXmlFile,nLen);//16.��ȡXMLģ���ļ�

		if(nLen>0 || strXmlFile != NULL)
		{
			delete []strXmlFile;
		}else
		{
			strText.Format(_T("%d.ģ��=%s, ����Ϊ��!\n"),pos++, pArryTaskMode->at(i)->szModeName);
			strWarning+=strText;
			nReturnVar = FALSE;
		}
		
	}

	
	return nReturnVar;
}