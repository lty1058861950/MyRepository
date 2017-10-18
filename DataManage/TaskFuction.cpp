// TaskFuction.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataManage.h"
#include "TaskFuction.h"
#include "SelUserDlg.h"
#include "TaskDownUpLoad.h"


// CTaskFuction �Ի���

IMPLEMENT_DYNAMIC(CTaskFuction, CDialog)

CTaskFuction::CTaskFuction(CWnd* pParent /*=NULL*/)
	: CDialog(CTaskFuction::IDD, pParent)
{
	m_pTaskSearchInfo = NULL;
}

CTaskFuction::~CTaskFuction()
{
}

void CTaskFuction::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTaskFuction, CDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_TASK_ADD_BTN, &CTaskFuction::OnBnClickedTaskAddBtn)
	ON_BN_CLICKED(IDC_TASK_EDT_BTN, &CTaskFuction::OnBnClickedTaskEdtBtn)
	ON_BN_CLICKED(IDC_TASK_DEL_BTN, &CTaskFuction::OnBnClickedTaskDelBtn)
	ON_BN_CLICKED(IDC_TASK_SEND_BTN, &CTaskFuction::OnBnClickedTaskSendBtn)
	ON_BN_CLICKED(IDC_BUTTON1, &CTaskFuction::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTaskFuction::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTaskFuction::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON6, &CTaskFuction::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON5, &CTaskFuction::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &CTaskFuction::OnBnClickedButton4)
END_MESSAGE_MAP()


// CTaskFuction ��Ϣ�������

BOOL CTaskFuction::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CTaskFuction::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialog::OnOK();
}

void CTaskFuction::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	AutoSize();
}

void CTaskFuction::AutoSize()
{
	CRect Rect ;
	GetClientRect(&Rect) ;

	int nBtnWidth = 80;
	int nBtnHeight = 30;

	int nTaskStatus = 0;
	if(m_pTaskSearchInfo != NULL)
	{
		nTaskStatus = m_pTaskSearchInfo->stTaskBaseInfo.nTaskStatus;
		switch(nTaskStatus)
		{
		case Task_Init:
			{
				if (GetDlgItem(IDC_TASK_ADD_BTN)->GetSafeHwnd())
				{
					GetDlgItem(IDC_TASK_ADD_BTN)->MoveWindow(10+(nBtnWidth+10)*0,1,nBtnWidth,nBtnHeight);//�������//
				}
				if (GetDlgItem(IDC_TASK_EDT_BTN)->GetSafeHwnd())
				{
					GetDlgItem(IDC_TASK_EDT_BTN)->MoveWindow(10+(nBtnWidth+10)*1,1,nBtnWidth,nBtnHeight);//��������//
				}
				if (GetDlgItem(IDC_TASK_DEL_BTN)->GetSafeHwnd())
				{
					GetDlgItem(IDC_TASK_DEL_BTN)->MoveWindow(10+(nBtnWidth+10)*2,1,nBtnWidth,nBtnHeight);//ɾ������//
				}


				if(GetDlgItem(IDC_BUTTON3)->GetSafeHwnd())
				{
					GetDlgItem(IDC_BUTTON3)->MoveWindow(Rect.Width()-(10+(nBtnWidth+10)*2),1,nBtnWidth,nBtnHeight);//������//
				}
				if (GetDlgItem(IDC_TASK_SEND_BTN)->GetSafeHwnd())
				{
					GetDlgItem(IDC_TASK_SEND_BTN)->MoveWindow(Rect.Width()-(10+(nBtnWidth+10)*1),1,nBtnWidth,nBtnHeight);//�ɹ�����//
				}
				
			}
			break;
		case Task_OK:
			{
				if (GetDlgItem(IDC_TASK_DEL_BTN)->GetSafeHwnd())
				{
					GetDlgItem(IDC_TASK_DEL_BTN)->MoveWindow(10+(nBtnWidth+10)*0,1,nBtnWidth,nBtnHeight);//ɾ������//
				}



				if (GetDlgItem(IDC_BUTTON1)->GetSafeHwnd())
				{
					GetDlgItem(IDC_BUTTON1)->MoveWindow(Rect.Width()-(10+(nBtnWidth+10)*3),1,nBtnWidth,nBtnHeight);//ȡ������//
				}
				if (GetDlgItem(IDC_BUTTON2)->GetSafeHwnd())
				{
					GetDlgItem(IDC_BUTTON2)->MoveWindow(Rect.Width()-(10+(nBtnWidth+10)*2),1,nBtnWidth,nBtnHeight);//�����ɹ�//
				}
				
				if(GetDlgItem(IDC_BUTTON6)->GetSafeHwnd())
				{
					GetDlgItem(IDC_BUTTON6)->MoveWindow(Rect.Width()-(10+(nBtnWidth+10)*1),1,nBtnWidth,nBtnHeight);//��������//
				}
			}
			break;
		case Task_Runing:
			{
				if (GetDlgItem(IDC_TASK_DEL_BTN)->GetSafeHwnd())
				{
					GetDlgItem(IDC_TASK_DEL_BTN)->MoveWindow(10+(nBtnWidth+10)*0,1,nBtnWidth,nBtnHeight);//ɾ������//
				}

				
				if (GetDlgItem(IDC_BUTTON1)->GetSafeHwnd())
				{
					GetDlgItem(IDC_BUTTON1)->MoveWindow(Rect.Width()-(10+(nBtnWidth+10)*3),1,nBtnWidth,nBtnHeight);//ȡ������//
				}
				if (GetDlgItem(IDC_BUTTON2)->GetSafeHwnd())
				{
					GetDlgItem(IDC_BUTTON2)->MoveWindow(Rect.Width()-(10+(nBtnWidth+10)*2),1,nBtnWidth,nBtnHeight);//�����ɹ�//
				}
				if(GetDlgItem(IDC_BUTTON5)->GetSafeHwnd())
				{
					GetDlgItem(IDC_BUTTON5)->MoveWindow(Rect.Width()-(10+(nBtnWidth+10)*1),1,nBtnWidth,nBtnHeight);//����ϴ�//
				}

			}
			break;
		case Task_Finish:
			{
				if (GetDlgItem(IDC_TASK_DEL_BTN)->GetSafeHwnd())
				{
					GetDlgItem(IDC_TASK_DEL_BTN)->MoveWindow(10+(nBtnWidth+10)*0,1,nBtnWidth,nBtnHeight);//ɾ������//
				}
				if (GetDlgItem(IDC_BUTTON4)->GetSafeHwnd())
				{
					GetDlgItem(IDC_BUTTON4)->MoveWindow(Rect.Width()-(10+(nBtnWidth+10)*1),1,nBtnWidth,nBtnHeight);//�ɹ�����//
				}
			

			}
			break;
		case Task_All:
			{
				if (GetDlgItem(IDC_TASK_ADD_BTN)->GetSafeHwnd())
				{
					GetDlgItem(IDC_TASK_ADD_BTN)->MoveWindow(10+(nBtnWidth+10)*2,1,nBtnWidth,nBtnHeight);//�������//
				}
				if (GetDlgItem(IDC_TASK_EDT_BTN)->GetSafeHwnd())
				{
					GetDlgItem(IDC_TASK_EDT_BTN)->MoveWindow(10+(nBtnWidth+10)*1,1,nBtnWidth,nBtnHeight);//��������//
				}
				if (GetDlgItem(IDC_TASK_DEL_BTN)->GetSafeHwnd())
				{
					GetDlgItem(IDC_TASK_DEL_BTN)->MoveWindow(10+(nBtnWidth+10)*0,1,nBtnWidth,nBtnHeight);//ɾ������//
				}
			}
			break;
		}
	}

	/*if (GetDlgItem(IDC_TASK_ADD_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_TASK_ADD_BTN)->MoveWindow(10+(nBtnWidth+10)*0,1,nBtnWidth,nBtnHeight);
	}
	if (GetDlgItem(IDC_TASK_DEL_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_TASK_DEL_BTN)->MoveWindow(10+(nBtnWidth+10)*1,1,nBtnWidth,nBtnHeight);
	}
	if (GetDlgItem(IDC_TASK_EDT_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_TASK_EDT_BTN)->MoveWindow(10+(nBtnWidth+10)*2,1,nBtnWidth,nBtnHeight);
	}
	

	if (GetDlgItem(IDC_TASK_SEND_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_TASK_SEND_BTN)->MoveWindow(10+(nBtnWidth+10)*3,1,nBtnWidth,nBtnHeight);
	}
	if (GetDlgItem(IDC_BUTTON1)->GetSafeHwnd())
	{
		GetDlgItem(IDC_BUTTON1)->MoveWindow(10+(nBtnWidth+10)*4,1,nBtnWidth,nBtnHeight);
	}
	if (GetDlgItem(IDC_BUTTON2)->GetSafeHwnd())
	{
		GetDlgItem(IDC_BUTTON2)->MoveWindow(10+(nBtnWidth+10)*5,1,nBtnWidth,nBtnHeight);
	}*/
}

void CTaskFuction::OnBnClickedTaskAddBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ret = 0, i, nCount;
	CString strText, str;
	vector<CString> strErrorArray;
	CTaskMng  nTaskMng;//�������//
	nTaskMng.m_ShowType = Add_NewTask;
	if(nTaskMng.DoModal() == IDOK)
	{

		StBasTask *pTaskInfo = &nTaskMng.m_ShowTaskInfo.m_CurTaskInfo;
		
		ret = AddNewTask(pTaskInfo,strErrorArray);
		if(ret == 1)
		{
			g_pShowInfoList->InsertOneTaskToList(pTaskInfo);
			g_pLeftTree->InitGuideTree();
			g_MainFram->m_wndOutput.InsertErrorArrayText(strErrorArray);
		}else
		{
			g_MainFram->m_wndOutput.InsertErrorArrayText(strErrorArray);
			nCount = strErrorArray.size();
			for (i = 0;i<nCount;i++)
			{
				str.Format(_T("%d.%s\n"), i+1, strErrorArray.at(i));
				strText+=str;
			}
			AfxMessageBox(strText);
			
		}
	}

}

void CTaskFuction::OnBnClickedTaskEdtBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CEditableListCtrl *pList2 = &g_pShowInfoList->m_ResultList.m_ResultList;

	
	CString strText, str;
	vector<CString> strErrorArray;

	int nIndex, i,nCount, ret = 0;
	nIndex = pList2->GetFirstSelectedItem();
	nCount = pList2->GetItemCount();
	if(nIndex < 0 || nIndex >= nCount)
		return;

	UINT nTaskOid = pList2->GetItemData(nIndex);
	CTaskMng  nTaskMng;//�������//
	

	StBasTask *pTaskInfo = &nTaskMng.m_ShowTaskInfo.m_CurTaskInfo;
	pTaskInfo->Release();
	if(!m_DMng.GetTaskDataOid(nTaskOid,pTaskInfo))
	{
		return;
	}
	nTaskMng.m_ShowType = Modify_Task;
	if(nTaskMng.DoModal() == IDOK)
	{
		//nTaskMng.m_ShowTaskInfo.GetChangeTaskInfo();
		ret = ModifyTheTask(pTaskInfo,strErrorArray);
		if(ret == 1)
		{
			g_pShowInfoList->ModifyOneTaskToList(nIndex,pTaskInfo);
		}
		g_MainFram->m_wndOutput.InsertErrorArrayText(strErrorArray);
		nCount = strErrorArray.size();
		for (i = 0;i<nCount;i++)
		{
			str.Format(_T("%d.%s\n"), i+1, strErrorArray.at(i));
			strText+=str;
		}
		AfxMessageBox(strText);
		strErrorArray.clear();
	}
}

void CTaskFuction::OnBnClickedTaskDelBtn()
{
	CEditableListCtrl *pList2 = &g_pShowInfoList->m_ResultList.m_ResultList;

	int nIndex, nCount, ret = 0;

	nIndex = pList2->GetFirstSelectedItem();
	nCount = pList2->GetItemCount();
	if(nIndex < 0 || nIndex >= nCount)
		return;

	UINT nTaskOid = pList2->GetItemData(nIndex);
	StBasTask stTaskInfo;
	stTaskInfo.Release();
	if(!m_DMng.GetTaskDataOid(nTaskOid,&stTaskInfo))
	{
		return;
	}
	ret = DelTheTask(&stTaskInfo);

	if(ret == 1)
	{
		pList2->DeleteItem(nIndex);
	}
}

//�ɹ�//
void CTaskFuction::OnBnClickedTaskSendBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i, nCount = 0;
	int nRight = 0;
	CString strText, strError,str;
	vector<CString> strErrorArray;
	vector<CString> strTempArray;
	CEditableListCtrl *pList = &g_pShowInfoList->m_ResultList.m_ResultList;
	int nIndex;
	nIndex = pList->GetFirstSelectedItem();
	nCount = pList->GetItemCount();
	if(nIndex < 0 || nIndex >= nCount)
		return;


	//��ȡ��ѡ�е���//
	vector<StBasTask> stTaskArray;
	UINT nTaskOid = 0;

	nCount = pList->GetItemCount();
	for ( i = 0; i< nCount; i++)
	{
		if((pList->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED) /*|| if(pList->GetCheck(i)*/)
		{
			str.Format(_T("ѡ���� %d \n"), i+1);
			strText+= str;
			nTaskOid = pList->GetItemData(i);
			StBasTask  nTaskInfo;
			nTaskInfo.Release();
			if(m_DMng.GetTaskDataOid(nTaskOid, &nTaskInfo))
			{
				nTaskInfo.stTaskBaseInfo.nListIndex = i;

				//1.//��ȡ�����Ʒ���//
				if(m_DMng.GetTaskCodeData(&nTaskInfo,nTaskInfo.stTaskBaseInfo.nOid))
				{
				}
				//2.//��ȡ����ģ������//
				if(m_DMng.GetTaskModeData(&nTaskInfo,nTaskInfo.stTaskBaseInfo.nOid))
				{
				}
				//3.//��ȡ�����Ʒͼ������//
				if(m_DMng.GetTaskPicNumData(&nTaskInfo,nTaskInfo.stTaskBaseInfo.nOid))
				{
				}


				if(CheckTheTask(&nTaskInfo, str))
				{
					stTaskArray.push_back(nTaskInfo);
				}else
				{
					strError+=str;
					nRight = 1;
				}
				
			}
		}
	}
	
	if(nRight)
	{
		AfxMessageBox(strError);
		stTaskArray.clear();
		return;

	}
	//1.�������ĺϷ��� ������

	//AfxMessageBox(strText);
	//2.�ɹ�����  ѡ����Ա  �޸�������ɹ�ʱ��ͼ����鳤(�ݶ��ɹ���)
	CSelUserDlg Dlg;
	CString strUserName, strLeaderName = g_LoginUsrInfo.szUserName;
	if(Dlg.DoModal() == IDOK)
	{
		strUserName = Dlg.m_SelUserName;
		//AfxMessageBox(strUserName);
	}else
	{
		stTaskArray.clear();
		return;
	}

	nCount = stTaskArray.size();
	strText.Format(_T("������"));
	for( i = 0; i< nCount; i++)
	{
		str.Format(_T("\"%s\"\n"), stTaskArray.at(i).stTaskBaseInfo.szTaskName);
		strText += str;
	}

	str.Format(_T("�ɷ��� %s \n"), strUserName);
	strText+=str;
	if(MessageBox(strText,_T("��ʾ"),MB_OKCANCEL|MB_ICONQUESTION) == IDOK)
	{
		for( i = 0; i< nCount; i++)
		{
			// ����״̬//
			stTaskArray.at(i).stTaskBaseInfo.nTaskStatus = Task_OK;

			//�ɷ�ʱ��//
			memset(stTaskArray.at(i).stTaskBaseInfo.szSendDate, 0, sizeof(stTaskArray.at(i).stTaskBaseInfo.szSendDate));
			strcpy(stTaskArray.at(i).stTaskBaseInfo.szSendDate, GetDateTimeString());

			//���Ա����//
			memset(stTaskArray.at(i).stTaskBaseInfo.szCheckUser, 0, sizeof(stTaskArray.at(i).stTaskBaseInfo.szCheckUser));
			strcpy(stTaskArray.at(i).stTaskBaseInfo.szCheckUser, strUserName);

			//�����鳤//
			memset(stTaskArray.at(i).stTaskBaseInfo.szCheckLeader, 0, sizeof(stTaskArray.at(i).stTaskBaseInfo.szCheckLeader));
			strcpy(stTaskArray.at(i).stTaskBaseInfo.szCheckLeader, strLeaderName);

			if(ModifyTheTask(&stTaskArray.at(i),strTempArray))
			{
				g_pShowInfoList->ModifyOneTaskToList(stTaskArray.at(i).stTaskBaseInfo.nListIndex,&stTaskArray.at(i));
			}

			nCount = strTempArray.size();
			for (i = 0;i<nCount;i++)
			{
				strErrorArray.push_back(strTempArray.at(i));
			}
			strTempArray.clear();

		}
		
		stTaskArray.clear();
		nCount = strErrorArray.size();
		for (i= 0;i<nCount;i++)
		{
			str.Format(_T("%d.%s\n"), i+1, strErrorArray.at(i));
			strText+=str;
		}
		str.Format(_T("�ɷ����!"));
		strText+=str;

		strErrorArray.clear();
		AfxMessageBox(strText);

	}
	stTaskArray.clear();

	//strText = _T("");
	

}


//ȡ������//
void CTaskFuction::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������//

	int i, nCount = 0;
	CString strText, str;
	vector<CString> strErrorArray;
	vector<CString> strTempArray;
	CEditableListCtrl *pList = &g_pShowInfoList->m_ResultList.m_ResultList;
	int nIndex;
	nIndex = pList->GetFirstSelectedItem();
	nCount = pList->GetItemCount();
	if(nIndex < 0 || nIndex >= nCount)
		return;
	//��ȡ��ѡ�е���//
	vector<StBasTask> stTaskArray;
	UINT nTaskOid = 0;

	nCount = pList->GetItemCount();
	for ( i = 0; i< nCount; i++)
	{
		if((pList->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED) /*|| if(pList->GetCheck(i)*/)
		{
			str.Format(_T("ѡ���� %d \n"), i+1);
			strText+= str;
			nTaskOid = pList->GetItemData(i);
			StBasTask  nTaskInfo;
			nTaskInfo.Release();
			if(m_DMng.GetTaskDataOid(nTaskOid, &nTaskInfo))
			{
				nTaskInfo.stTaskBaseInfo.nListIndex = i;
				stTaskArray.push_back(nTaskInfo);
			}
		}
	}


	nCount = stTaskArray.size();
	strText.Format(_T("������"));
	for( i = 0; i< nCount; i++)
	{
		str.Format(_T("\"%s\"\n"), stTaskArray.at(i).stTaskBaseInfo.szTaskName);
		strText += str;
	}

	str.Format(_T("ȡ���ɹ�\n"));
	strText+=str;
	if(MessageBox(strText,_T("��ʾ"),MB_OKCANCEL|MB_ICONQUESTION) == IDOK)
	{
		for( i = 0; i< nCount; i++)
		{
			// ����״̬//
			stTaskArray.at(i).stTaskBaseInfo.nTaskStatus = Task_Init;

			//�ɷ�ʱ��//
			memset(stTaskArray.at(i).stTaskBaseInfo.szSendDate, 0, sizeof(stTaskArray.at(i).stTaskBaseInfo.szSendDate));
			//strcpy(stTaskArray.at(i).stTaskBaseInfo.szSendDate, GetDateTimeString());

			//����ʱ��
			memset(stTaskArray.at(i).stTaskBaseInfo.szDownLoadDate, 0, sizeof(stTaskArray.at(i).stTaskBaseInfo.szDownLoadDate));

			//���Ա����//
			memset(stTaskArray.at(i).stTaskBaseInfo.szCheckUser, 0, sizeof(stTaskArray.at(i).stTaskBaseInfo.szCheckUser));
			//strcpy(stTaskArray.at(i).stTaskBaseInfo.szCheckUser, strUserName);

			//�����鳤//
			memset(stTaskArray.at(i).stTaskBaseInfo.szCheckLeader, 0, sizeof(stTaskArray.at(i).stTaskBaseInfo.szCheckLeader));
			//strcpy(stTaskArray.at(i).stTaskBaseInfo.szCheckLeader, strLeaderName);

			if(ModifyTheTask(&stTaskArray.at(i),strTempArray))
			{
				g_pShowInfoList->ModifyOneTaskToList(stTaskArray.at(i).stTaskBaseInfo.nListIndex,&stTaskArray.at(i));
			}
			nCount = strTempArray.size();
			for (i = 0;i<nCount;i++)
			{
				strErrorArray.push_back(strTempArray.at(i));
			}

			strTempArray.clear();

		}

		stTaskArray.clear();

		nCount = strErrorArray.size();
		for (i = 0;i<nCount;i++)
		{
			str.Format(_T("%d.%s\n"), i+1, strErrorArray.at(i));
			strText+=str;
		}

		str.Format(_T("����ȡ�����!"));
		strText+=str;
		strErrorArray.clear();
		AfxMessageBox(strText);
	}

	stTaskArray.clear();
}
//����ɹ�//
void CTaskFuction::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnBnClickedTaskSendBtn();//�ٴε��� �ɹ�����//
}

//������
void CTaskFuction::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i, nCount = 0;
	CString strText, str, str1;
	CEditableListCtrl *pList = &g_pShowInfoList->m_ResultList.m_ResultList;
	int nIndex;
	nIndex = pList->GetFirstSelectedItem();
	nCount = pList->GetItemCount();
	if(nIndex < 0 || nIndex >= nCount)
		return;


	//��ȡ��ѡ�е���//
	vector<StBasTask> stTaskArray;
	UINT nTaskOid = 0;

	nCount = pList->GetItemCount();
	for ( i = 0; i< nCount; i++)
	{
		if((pList->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED) /*|| if(pList->GetCheck(i)*/)
		{
			str.Format(_T("ѡ���� %d \n"), i+1);
			strText+= str;
			nTaskOid = pList->GetItemData(i);
			StBasTask  nTaskInfo;
			nTaskInfo.Release();
			if(m_DMng.GetTaskDataOid(nTaskOid, &nTaskInfo))
			{
				nTaskInfo.stTaskBaseInfo.nListIndex = i;
				//1.//��ȡ�����Ʒ���//
				if(m_DMng.GetTaskCodeData(&nTaskInfo,nTaskInfo.stTaskBaseInfo.nOid))
				{
				}
				//2.//��ȡ����ģ������//
				if(m_DMng.GetTaskModeData(&nTaskInfo,nTaskInfo.stTaskBaseInfo.nOid))
				{
				}
				//3.//��ȡ�����Ʒͼ������//
				if(m_DMng.GetTaskPicNumData(&nTaskInfo,nTaskInfo.stTaskBaseInfo.nOid))
				{
				}
				stTaskArray.push_back(nTaskInfo);
			}
		}
	}


	strText = _T("");
	nCount = stTaskArray.size();
	for( i = 0; i< nCount; i++)
	{
		if(CheckTheTask(&stTaskArray.at(i), str))
		{
			str1.Format(_T("����=%s ���ͨ��!\n"), stTaskArray.at(i).stTaskBaseInfo.szTaskName);
			strText+=str1;
			strText+=_T("\n");
		}else
		{
			str1.Format(_T("����=%s ���ʧ��!\n"), stTaskArray.at(i).stTaskBaseInfo.szTaskName);
			str1+=str;
			strText+=str1;
			strText+=_T("\n");
		}
	}
	stTaskArray.clear();

	AfxMessageBox(strText);
}

//��������
void CTaskFuction::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������//
	CTaskDownUpLoad dlg;
	dlg.m_ShowType =  Task_DownLoad;
	dlg.DoModal();
}

//����ϴ�//
void CTaskFuction::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTaskDownUpLoad dlg;
	dlg.m_ShowType =  Task_UpLoad;
	dlg.DoModal();
}

//������ִ��//
void CTaskFuction::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	int i, nCount = 0;
	CString strText, str;
	vector<CString> strTempArray;
	vector<CString> strErrorArray;
	CEditableListCtrl *pList = &g_pShowInfoList->m_ResultList.m_ResultList;
	int nIndex;
	nIndex = pList->GetFirstSelectedItem();
	nCount = pList->GetItemCount();
	if(nIndex < 0 || nIndex >= nCount)
		return;


	//��ȡ��ѡ�е���//
	vector<StBasTask> stTaskArray;
	UINT nTaskOid = 0;

	nCount = pList->GetItemCount();
	for ( i = 0; i< nCount; i++)
	{
		if((pList->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED) /*|| if(pList->GetCheck(i)*/)
		{
			str.Format(_T("ѡ���� %d \n"), i+1);
			strText+= str;
			nTaskOid = pList->GetItemData(i);
			StBasTask  nTaskInfo;
			nTaskInfo.Release();
			if(m_DMng.GetTaskDataOid(nTaskOid, &nTaskInfo))
			{
				nTaskInfo.stTaskBaseInfo.nListIndex = i;
				stTaskArray.push_back(nTaskInfo);
			}
		}
	}

	nCount = stTaskArray.size();
	strText.Format(_T("������"));
	for( i = 0; i< nCount; i++)
	{
		str.Format(_T("\"%s\"\n"), stTaskArray.at(i).stTaskBaseInfo.szTaskName);
		strText += str;
	}

	str.Format(_T("���ж����·�\n"));
	strText+=str;
	if(MessageBox(strText,_T("��ʾ"),MB_OKCANCEL|MB_ICONQUESTION) == IDOK)
	{
		for( i = 0; i< nCount; i++)
		{
			// ����״̬//
			stTaskArray.at(i).stTaskBaseInfo.nTaskStatus = Task_Init;

			//�ɷ�ʱ��//
			memset(stTaskArray.at(i).stTaskBaseInfo.szSendDate, 0, sizeof(stTaskArray.at(i).stTaskBaseInfo.szSendDate));

			//���Ա����//
			memset(stTaskArray.at(i).stTaskBaseInfo.szCheckUser, 0, sizeof(stTaskArray.at(i).stTaskBaseInfo.szCheckUser));

			//�����鳤//
			memset(stTaskArray.at(i).stTaskBaseInfo.szCheckLeader, 0, sizeof(stTaskArray.at(i).stTaskBaseInfo.szCheckLeader));

			if(ModifyTheTask(&stTaskArray.at(i),strTempArray))
			{
				g_pShowInfoList->ModifyOneTaskToList(stTaskArray.at(i).stTaskBaseInfo.nListIndex,&stTaskArray.at(i));
			}

			nCount = strTempArray.size();
			for (i = 0;i<nCount;i++)
			{
				strErrorArray.push_back(strTempArray.at(i));
			}
			strTempArray.clear();
		}
		stTaskArray.clear();
		nCount = strErrorArray.size();

		for (i = 0;i<nCount;i++)
		{
			str.Format(_T("%d.%s\n"), i+1, strErrorArray.at(i));
			strText+=str;
		}

		str.Format(_T("�����·����!"));
		strText+=str;
		strErrorArray.clear();

		AfxMessageBox(strText);
	}

	stTaskArray.clear();
}
