// TaskFuction.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "TaskFuction.h"
#include "SelUserDlg.h"
#include "TaskDownUpLoad.h"


// CTaskFuction 对话框

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


// CTaskFuction 消息处理程序

BOOL CTaskFuction::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CTaskFuction::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}

void CTaskFuction::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
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
					GetDlgItem(IDC_TASK_ADD_BTN)->MoveWindow(10+(nBtnWidth+10)*0,1,nBtnWidth,nBtnHeight);//添加任务//
				}
				if (GetDlgItem(IDC_TASK_EDT_BTN)->GetSafeHwnd())
				{
					GetDlgItem(IDC_TASK_EDT_BTN)->MoveWindow(10+(nBtnWidth+10)*1,1,nBtnWidth,nBtnHeight);//更改任务//
				}
				if (GetDlgItem(IDC_TASK_DEL_BTN)->GetSafeHwnd())
				{
					GetDlgItem(IDC_TASK_DEL_BTN)->MoveWindow(10+(nBtnWidth+10)*2,1,nBtnWidth,nBtnHeight);//删除任务//
				}


				if(GetDlgItem(IDC_BUTTON3)->GetSafeHwnd())
				{
					GetDlgItem(IDC_BUTTON3)->MoveWindow(Rect.Width()-(10+(nBtnWidth+10)*2),1,nBtnWidth,nBtnHeight);//任务检测//
				}
				if (GetDlgItem(IDC_TASK_SEND_BTN)->GetSafeHwnd())
				{
					GetDlgItem(IDC_TASK_SEND_BTN)->MoveWindow(Rect.Width()-(10+(nBtnWidth+10)*1),1,nBtnWidth,nBtnHeight);//派工任务//
				}
				
			}
			break;
		case Task_OK:
			{
				if (GetDlgItem(IDC_TASK_DEL_BTN)->GetSafeHwnd())
				{
					GetDlgItem(IDC_TASK_DEL_BTN)->MoveWindow(10+(nBtnWidth+10)*0,1,nBtnWidth,nBtnHeight);//删除任务//
				}



				if (GetDlgItem(IDC_BUTTON1)->GetSafeHwnd())
				{
					GetDlgItem(IDC_BUTTON1)->MoveWindow(Rect.Width()-(10+(nBtnWidth+10)*3),1,nBtnWidth,nBtnHeight);//取消任务//
				}
				if (GetDlgItem(IDC_BUTTON2)->GetSafeHwnd())
				{
					GetDlgItem(IDC_BUTTON2)->MoveWindow(Rect.Width()-(10+(nBtnWidth+10)*2),1,nBtnWidth,nBtnHeight);//更改派工//
				}
				
				if(GetDlgItem(IDC_BUTTON6)->GetSafeHwnd())
				{
					GetDlgItem(IDC_BUTTON6)->MoveWindow(Rect.Width()-(10+(nBtnWidth+10)*1),1,nBtnWidth,nBtnHeight);//任务下载//
				}
			}
			break;
		case Task_Runing:
			{
				if (GetDlgItem(IDC_TASK_DEL_BTN)->GetSafeHwnd())
				{
					GetDlgItem(IDC_TASK_DEL_BTN)->MoveWindow(10+(nBtnWidth+10)*0,1,nBtnWidth,nBtnHeight);//删除任务//
				}

				
				if (GetDlgItem(IDC_BUTTON1)->GetSafeHwnd())
				{
					GetDlgItem(IDC_BUTTON1)->MoveWindow(Rect.Width()-(10+(nBtnWidth+10)*3),1,nBtnWidth,nBtnHeight);//取消任务//
				}
				if (GetDlgItem(IDC_BUTTON2)->GetSafeHwnd())
				{
					GetDlgItem(IDC_BUTTON2)->MoveWindow(Rect.Width()-(10+(nBtnWidth+10)*2),1,nBtnWidth,nBtnHeight);//更改派工//
				}
				if(GetDlgItem(IDC_BUTTON5)->GetSafeHwnd())
				{
					GetDlgItem(IDC_BUTTON5)->MoveWindow(Rect.Width()-(10+(nBtnWidth+10)*1),1,nBtnWidth,nBtnHeight);//结果上传//
				}

			}
			break;
		case Task_Finish:
			{
				if (GetDlgItem(IDC_TASK_DEL_BTN)->GetSafeHwnd())
				{
					GetDlgItem(IDC_TASK_DEL_BTN)->MoveWindow(10+(nBtnWidth+10)*0,1,nBtnWidth,nBtnHeight);//删除任务//
				}
				if (GetDlgItem(IDC_BUTTON4)->GetSafeHwnd())
				{
					GetDlgItem(IDC_BUTTON4)->MoveWindow(Rect.Width()-(10+(nBtnWidth+10)*1),1,nBtnWidth,nBtnHeight);//派工任务//
				}
			

			}
			break;
		case Task_All:
			{
				if (GetDlgItem(IDC_TASK_ADD_BTN)->GetSafeHwnd())
				{
					GetDlgItem(IDC_TASK_ADD_BTN)->MoveWindow(10+(nBtnWidth+10)*2,1,nBtnWidth,nBtnHeight);//添加任务//
				}
				if (GetDlgItem(IDC_TASK_EDT_BTN)->GetSafeHwnd())
				{
					GetDlgItem(IDC_TASK_EDT_BTN)->MoveWindow(10+(nBtnWidth+10)*1,1,nBtnWidth,nBtnHeight);//更改任务//
				}
				if (GetDlgItem(IDC_TASK_DEL_BTN)->GetSafeHwnd())
				{
					GetDlgItem(IDC_TASK_DEL_BTN)->MoveWindow(10+(nBtnWidth+10)*0,1,nBtnWidth,nBtnHeight);//删除任务//
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
	// TODO: 在此添加控件通知处理程序代码
	int ret = 0, i, nCount;
	CString strText, str;
	vector<CString> strErrorArray;
	CTaskMng  nTaskMng;//检查任务//
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
	// TODO: 在此添加控件通知处理程序代码

	CEditableListCtrl *pList2 = &g_pShowInfoList->m_ResultList.m_ResultList;

	
	CString strText, str;
	vector<CString> strErrorArray;

	int nIndex, i,nCount, ret = 0;
	nIndex = pList2->GetFirstSelectedItem();
	nCount = pList2->GetItemCount();
	if(nIndex < 0 || nIndex >= nCount)
		return;

	UINT nTaskOid = pList2->GetItemData(nIndex);
	CTaskMng  nTaskMng;//检查任务//
	

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

//派工//
void CTaskFuction::OnBnClickedTaskSendBtn()
{
	// TODO: 在此添加控件通知处理程序代码
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


	//获取被选中的行//
	vector<StBasTask> stTaskArray;
	UINT nTaskOid = 0;

	nCount = pList->GetItemCount();
	for ( i = 0; i< nCount; i++)
	{
		if((pList->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED) /*|| if(pList->GetCheck(i)*/)
		{
			str.Format(_T("选中了 %d \n"), i+1);
			strText+= str;
			nTaskOid = pList->GetItemData(i);
			StBasTask  nTaskInfo;
			nTaskInfo.Release();
			if(m_DMng.GetTaskDataOid(nTaskOid, &nTaskInfo))
			{
				nTaskInfo.stTaskBaseInfo.nListIndex = i;

				//1.//获取任务产品编号//
				if(m_DMng.GetTaskCodeData(&nTaskInfo,nTaskInfo.stTaskBaseInfo.nOid))
				{
				}
				//2.//获取任务模板数据//
				if(m_DMng.GetTaskModeData(&nTaskInfo,nTaskInfo.stTaskBaseInfo.nOid))
				{
				}
				//3.//获取任务产品图号数据//
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
	//1.检查任务的合法性 完整性

	//AfxMessageBox(strText);
	//2.派工给人  选择人员  修改任务的派工时间和检验组长(暂定派工人)
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
	strText.Format(_T("将任务"));
	for( i = 0; i< nCount; i++)
	{
		str.Format(_T("\"%s\"\n"), stTaskArray.at(i).stTaskBaseInfo.szTaskName);
		strText += str;
	}

	str.Format(_T("派发给 %s \n"), strUserName);
	strText+=str;
	if(MessageBox(strText,_T("提示"),MB_OKCANCEL|MB_ICONQUESTION) == IDOK)
	{
		for( i = 0; i< nCount; i++)
		{
			// 任务状态//
			stTaskArray.at(i).stTaskBaseInfo.nTaskStatus = Task_OK;

			//派发时间//
			memset(stTaskArray.at(i).stTaskBaseInfo.szSendDate, 0, sizeof(stTaskArray.at(i).stTaskBaseInfo.szSendDate));
			strcpy(stTaskArray.at(i).stTaskBaseInfo.szSendDate, GetDateTimeString());

			//检查员姓名//
			memset(stTaskArray.at(i).stTaskBaseInfo.szCheckUser, 0, sizeof(stTaskArray.at(i).stTaskBaseInfo.szCheckUser));
			strcpy(stTaskArray.at(i).stTaskBaseInfo.szCheckUser, strUserName);

			//检验组长//
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
		str.Format(_T("派发完成!"));
		strText+=str;

		strErrorArray.clear();
		AfxMessageBox(strText);

	}
	stTaskArray.clear();

	//strText = _T("");
	

}


//取消任务//
void CTaskFuction::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码//

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
	//获取被选中的行//
	vector<StBasTask> stTaskArray;
	UINT nTaskOid = 0;

	nCount = pList->GetItemCount();
	for ( i = 0; i< nCount; i++)
	{
		if((pList->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED) /*|| if(pList->GetCheck(i)*/)
		{
			str.Format(_T("选中了 %d \n"), i+1);
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
	strText.Format(_T("将任务"));
	for( i = 0; i< nCount; i++)
	{
		str.Format(_T("\"%s\"\n"), stTaskArray.at(i).stTaskBaseInfo.szTaskName);
		strText += str;
	}

	str.Format(_T("取消派工\n"));
	strText+=str;
	if(MessageBox(strText,_T("提示"),MB_OKCANCEL|MB_ICONQUESTION) == IDOK)
	{
		for( i = 0; i< nCount; i++)
		{
			// 任务状态//
			stTaskArray.at(i).stTaskBaseInfo.nTaskStatus = Task_Init;

			//派发时间//
			memset(stTaskArray.at(i).stTaskBaseInfo.szSendDate, 0, sizeof(stTaskArray.at(i).stTaskBaseInfo.szSendDate));
			//strcpy(stTaskArray.at(i).stTaskBaseInfo.szSendDate, GetDateTimeString());

			//下载时间
			memset(stTaskArray.at(i).stTaskBaseInfo.szDownLoadDate, 0, sizeof(stTaskArray.at(i).stTaskBaseInfo.szDownLoadDate));

			//检查员姓名//
			memset(stTaskArray.at(i).stTaskBaseInfo.szCheckUser, 0, sizeof(stTaskArray.at(i).stTaskBaseInfo.szCheckUser));
			//strcpy(stTaskArray.at(i).stTaskBaseInfo.szCheckUser, strUserName);

			//检验组长//
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

		str.Format(_T("任务取消完成!"));
		strText+=str;
		strErrorArray.clear();
		AfxMessageBox(strText);
	}

	stTaskArray.clear();
}
//变更派工//
void CTaskFuction::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedTaskSendBtn();//再次调用 派工操作//
}

//任务检测
void CTaskFuction::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	int i, nCount = 0;
	CString strText, str, str1;
	CEditableListCtrl *pList = &g_pShowInfoList->m_ResultList.m_ResultList;
	int nIndex;
	nIndex = pList->GetFirstSelectedItem();
	nCount = pList->GetItemCount();
	if(nIndex < 0 || nIndex >= nCount)
		return;


	//获取被选中的行//
	vector<StBasTask> stTaskArray;
	UINT nTaskOid = 0;

	nCount = pList->GetItemCount();
	for ( i = 0; i< nCount; i++)
	{
		if((pList->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED) /*|| if(pList->GetCheck(i)*/)
		{
			str.Format(_T("选中了 %d \n"), i+1);
			strText+= str;
			nTaskOid = pList->GetItemData(i);
			StBasTask  nTaskInfo;
			nTaskInfo.Release();
			if(m_DMng.GetTaskDataOid(nTaskOid, &nTaskInfo))
			{
				nTaskInfo.stTaskBaseInfo.nListIndex = i;
				//1.//获取任务产品编号//
				if(m_DMng.GetTaskCodeData(&nTaskInfo,nTaskInfo.stTaskBaseInfo.nOid))
				{
				}
				//2.//获取任务模板数据//
				if(m_DMng.GetTaskModeData(&nTaskInfo,nTaskInfo.stTaskBaseInfo.nOid))
				{
				}
				//3.//获取任务产品图号数据//
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
			str1.Format(_T("任务=%s 检测通过!\n"), stTaskArray.at(i).stTaskBaseInfo.szTaskName);
			strText+=str1;
			strText+=_T("\n");
		}else
		{
			str1.Format(_T("任务=%s 检测失败!\n"), stTaskArray.at(i).stTaskBaseInfo.szTaskName);
			str1+=str;
			strText+=str1;
			strText+=_T("\n");
		}
	}
	stTaskArray.clear();

	AfxMessageBox(strText);
}

//任务下载
void CTaskFuction::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码//
	CTaskDownUpLoad dlg;
	dlg.m_ShowType =  Task_DownLoad;
	dlg.DoModal();
}

//结果上传//
void CTaskFuction::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	CTaskDownUpLoad dlg;
	dlg.m_ShowType =  Task_UpLoad;
	dlg.DoModal();
}

//任务多次执行//
void CTaskFuction::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码

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


	//获取被选中的行//
	vector<StBasTask> stTaskArray;
	UINT nTaskOid = 0;

	nCount = pList->GetItemCount();
	for ( i = 0; i< nCount; i++)
	{
		if((pList->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED) /*|| if(pList->GetCheck(i)*/)
		{
			str.Format(_T("选中了 %d \n"), i+1);
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
	strText.Format(_T("将任务"));
	for( i = 0; i< nCount; i++)
	{
		str.Format(_T("\"%s\"\n"), stTaskArray.at(i).stTaskBaseInfo.szTaskName);
		strText += str;
	}

	str.Format(_T("进行二次下发\n"));
	strText+=str;
	if(MessageBox(strText,_T("提示"),MB_OKCANCEL|MB_ICONQUESTION) == IDOK)
	{
		for( i = 0; i< nCount; i++)
		{
			// 任务状态//
			stTaskArray.at(i).stTaskBaseInfo.nTaskStatus = Task_Init;

			//派发时间//
			memset(stTaskArray.at(i).stTaskBaseInfo.szSendDate, 0, sizeof(stTaskArray.at(i).stTaskBaseInfo.szSendDate));

			//检查员姓名//
			memset(stTaskArray.at(i).stTaskBaseInfo.szCheckUser, 0, sizeof(stTaskArray.at(i).stTaskBaseInfo.szCheckUser));

			//检验组长//
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

		str.Format(_T("二次下发完成!"));
		strText+=str;
		strErrorArray.clear();

		AfxMessageBox(strText);
	}

	stTaskArray.clear();
}
