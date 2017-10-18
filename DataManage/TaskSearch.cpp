// TaskSearch.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "TaskSearch.h"
#include "SelUserDlg.h"
#include "SelDate.h"
#include "SelUpDepartDlg.h"
#include "SelProductDlg.h"


// CTaskSearch 对话框

IMPLEMENT_DYNAMIC(CTaskSearch, CDialog)

CTaskSearch::CTaskSearch(CWnd* pParent /*=NULL*/)
	: CDialog(CTaskSearch::IDD, pParent)
{
	m_TaskSearchInfo.Release();
	m_TaskSearchInfo.stTaskBaseInfo.nTaskStatus = Task_All;
}

CTaskSearch::~CTaskSearch()
{
}

void CTaskSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTaskSearch, CDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_TASK_SEARCH_BTN, &CTaskSearch::OnBnClickedTaskSearchBtn)
	ON_BN_CLICKED(IDC_BUTTON2, &CTaskSearch::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTaskSearch::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_SEL_UP_DEPART_BTN, &CTaskSearch::OnBnClickedSelUpDepartBtn)
	ON_BN_CLICKED(IDC_SEL_PRODNO_BTN, &CTaskSearch::OnBnClickedSelProdnoBtn)
	ON_BN_CLICKED(IDC_BUTTON4, &CTaskSearch::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CTaskSearch::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CTaskSearch::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CTaskSearch::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CTaskSearch::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CTaskSearch::OnBnClickedButton9)
END_MESSAGE_MAP()


// CTaskSearch 消息处理程序

BOOL CTaskSearch::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
/*
	GetDlgItem(IDC_TASK_INFO_STATIC26)->GetWindowRect(&m_rcRect1_1);//创建开始日期:
	GetDlgItem(IDC_EDIT1)->GetWindowRect(&m_rcRect1_2);

	GetDlgItem(IDC_TASK_INFO_STATIC28)->GetWindowRect(&m_rcRect2_1);//创建结束日期:
	GetDlgItem(IDC_EDIT2)->GetWindowRect(&m_rcRect2_2);

	GetDlgItem(IDC_TASK_INFO_STATIC21)->GetWindowRect(&m_rcRect3_1);//派工开始日期:
	GetDlgItem(IDC_SEND_DATE_EDT)->GetWindowRect(&m_rcRect3_2);

	GetDlgItem(IDC_TASK_INFO_STATIC29)->GetWindowRect(&m_rcRect4_1);//派工结束日期:
	GetDlgItem(IDC_EDIT4)->GetWindowRect(&m_rcRect4_2);

	GetDlgItem(IDC_TASK_INFO_STATIC22)->GetWindowRect(&m_rcRect5_1);//执行开始日期:
	GetDlgItem(IDC_EDIT5)->GetWindowRect(&m_rcRect5_2);

	GetDlgItem(IDC_TASK_INFO_STATIC30)->GetWindowRect(&m_rcRect6_1);//执行结束日期:
	GetDlgItem(IDC_EDIT6)->GetWindowRect(&m_rcRect6_2);

	GetDlgItem(IDC_TASK_INFO_STATIC25)->GetWindowRect(&m_rcRect7_1);// 完成开始日期:
	GetDlgItem(IDC_EDIT7)->GetWindowRect(&m_rcRect7_2);

	GetDlgItem(IDC_TASK_INFO_STATIC31)->GetWindowRect(&m_rcRect8_1);//完成结束日期:
	GetDlgItem(IDC_EDIT8)->GetWindowRect(&m_rcRect8_2);


	ScreenToClient(&m_rcRect1_1);ScreenToClient(&m_rcRect1_2);//创建开始日期:
	ScreenToClient(&m_rcRect2_1);ScreenToClient(&m_rcRect2_2);//创建结束日期:
	ScreenToClient(&m_rcRect3_1);ScreenToClient(&m_rcRect3_2);//派工开始日期:
	ScreenToClient(&m_rcRect4_1);ScreenToClient(&m_rcRect4_2);//派工结束日期:
	ScreenToClient(&m_rcRect5_1);ScreenToClient(&m_rcRect5_2);//执行开始日期:
	ScreenToClient(&m_rcRect6_1);ScreenToClient(&m_rcRect6_2);//执行结束日期:
	ScreenToClient(&m_rcRect7_1);ScreenToClient(&m_rcRect7_2);//完成开始日期:
	ScreenToClient(&m_rcRect8_1);ScreenToClient(&m_rcRect8_2);//完成结束日期:
*/

	//2017-03-10:
	GetDlgItem(IDC_TASK_INFO_STATIC21)->GetWindowRect(&m_rcRect1_1);//派工开始日期:
	GetDlgItem(IDC_SEND_DATE_EDT)->GetWindowRect(&m_rcRect1_2);
	GetDlgItem(IDC_BUTTON4)->GetWindowRect(&m_rcRect1_3);

	GetDlgItem(IDC_TASK_INFO_STATIC29)->GetWindowRect(&m_rcRect2_1);//派工结束日期:
	GetDlgItem(IDC_EDIT4)->GetWindowRect(&m_rcRect2_2);
	GetDlgItem(IDC_BUTTON5)->GetWindowRect(&m_rcRect2_3);


	GetDlgItem(IDC_TASK_INFO_STATIC22)->GetWindowRect(&m_rcRect3_1);//执行开始日期:
	GetDlgItem(IDC_EDIT5)->GetWindowRect(&m_rcRect3_2);
	GetDlgItem(IDC_BUTTON6)->GetWindowRect(&m_rcRect3_3);

	GetDlgItem(IDC_TASK_INFO_STATIC30)->GetWindowRect(&m_rcRect4_1);//执行结束日期:
	GetDlgItem(IDC_EDIT6)->GetWindowRect(&m_rcRect4_2);
	GetDlgItem(IDC_BUTTON7)->GetWindowRect(&m_rcRect4_3);

	GetDlgItem(IDC_TASK_INFO_STATIC25)->GetWindowRect(&m_rcRect5_1);// 完成开始日期:
	GetDlgItem(IDC_EDIT7)->GetWindowRect(&m_rcRect5_2);
	GetDlgItem(IDC_BUTTON8)->GetWindowRect(&m_rcRect5_3);

	GetDlgItem(IDC_TASK_INFO_STATIC31)->GetWindowRect(&m_rcRect6_1);//完成结束日期:
	GetDlgItem(IDC_EDIT8)->GetWindowRect(&m_rcRect6_2);
	GetDlgItem(IDC_BUTTON9)->GetWindowRect(&m_rcRect6_3);

	ScreenToClient(&m_rcRect1_1);ScreenToClient(&m_rcRect1_2);ScreenToClient(&m_rcRect1_3);//派工开始日期:
	ScreenToClient(&m_rcRect2_1);ScreenToClient(&m_rcRect2_2);ScreenToClient(&m_rcRect2_3);//派工结束日期:
	ScreenToClient(&m_rcRect3_1);ScreenToClient(&m_rcRect3_2);ScreenToClient(&m_rcRect3_3);//执行开始日期:
	ScreenToClient(&m_rcRect4_1);ScreenToClient(&m_rcRect4_2);ScreenToClient(&m_rcRect4_3);//执行结束日期:
	ScreenToClient(&m_rcRect5_1);ScreenToClient(&m_rcRect5_2);ScreenToClient(&m_rcRect5_3);//完成开始日期:
	ScreenToClient(&m_rcRect6_1);ScreenToClient(&m_rcRect6_2);ScreenToClient(&m_rcRect6_3);//完成结束日期:


	
	InitComBox();

	DisplaySearchInfo();
	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CTaskSearch::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnOK();
}

void CTaskSearch::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	AutoSize();
}

void CTaskSearch::AutoSize()
{
	CRect Rect ;
	GetClientRect(&Rect) ;
	int nBtmWidth = 80;
	int nBtnHeight = 30;
	int npos = 950;

	if (GetDlgItem(IDC_TASK_INFO_STATIC1)->GetSafeHwnd())
	{
		GetDlgItem(IDC_TASK_INFO_STATIC1)->MoveWindow(1,5,Rect.Width()-(1*2),Rect.Height()-(5*2));
	}
	if (GetDlgItem(IDC_TASK_SEARCH_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_TASK_SEARCH_BTN)->MoveWindow(npos-80/*Rect.right-(nBtmWidth+50)*/,80/*Rect.bottom-(nBtnHeight+30)*/,nBtmWidth,nBtnHeight);
	}

	
	int nTaskStatus = m_TaskSearchInfo.stTaskBaseInfo.nTaskStatus;
	if(GetDlgItem(IDC_TASK_INFO_STATIC26)->GetSafeHwnd())
	{
		
		switch(nTaskStatus)
		{
		case Task_Init:
			{
				//if(GetDlgItem(IDC_TASK_INFO_STATIC26)->GetSafeHwnd())//创建开始日期:
				//{
				//	GetDlgItem(IDC_TASK_INFO_STATIC26)->MoveWindow(m_rcRect1_1);
				//}
				//if(GetDlgItem(IDC_EDIT1)->GetSafeHwnd())//创建开始日期:
				//{
				//	GetDlgItem(IDC_EDIT1)->MoveWindow(m_rcRect1_2);
				//}
				//
				//if(GetDlgItem(IDC_TASK_INFO_STATIC28)->GetSafeHwnd())//创建结束日期:
				//{
				//	GetDlgItem(IDC_TASK_INFO_STATIC28)->MoveWindow(m_rcRect2_1);
				//}
				//if(GetDlgItem(IDC_EDIT2)->GetSafeHwnd())//创建结束日期:
				//{
				//	GetDlgItem(IDC_EDIT2)->MoveWindow(m_rcRect2_2);
				//}
			}
			break;
		case Task_OK:
			{
				if(GetDlgItem(IDC_TASK_INFO_STATIC21)->GetSafeHwnd())// 派工开始日期:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC21)->MoveWindow(m_rcRect1_1);
				}
				if(GetDlgItem(IDC_SEND_DATE_EDT)->GetSafeHwnd())// 派工开始日期:
				{
					GetDlgItem(IDC_SEND_DATE_EDT)->MoveWindow(m_rcRect1_2);
				}
				if(GetDlgItem(IDC_BUTTON4)->GetSafeHwnd())// 派工开始日期:
				{
					GetDlgItem(IDC_BUTTON4)->MoveWindow(m_rcRect1_3);
				}

				if(GetDlgItem(IDC_TASK_INFO_STATIC29)->GetSafeHwnd())// 派工结束日期:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC29)->MoveWindow(m_rcRect2_1);
				}
				if(GetDlgItem(IDC_EDIT4)->GetSafeHwnd())// 派工结束日期:
				{
					GetDlgItem(IDC_EDIT4)->MoveWindow(m_rcRect2_2);
				}
				if(GetDlgItem(IDC_BUTTON5)->GetSafeHwnd())// 派工开始日期:
				{
					GetDlgItem(IDC_BUTTON5)->MoveWindow(m_rcRect2_3);
				}

			}
			break;
		case  Task_Runing:
			{
				/*
				if(GetDlgItem(IDC_TASK_INFO_STATIC21)->GetSafeHwnd())//派工开始日期:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC21)->MoveWindow(m_rcRect1_1);
				}
				if(GetDlgItem(IDC_SEND_DATE_EDT)->GetSafeHwnd())//派工开始日期:
				{
					GetDlgItem(IDC_SEND_DATE_EDT)->MoveWindow(m_rcRect1_2);
				}

				if(GetDlgItem(IDC_TASK_INFO_STATIC29)->GetSafeHwnd())//派工结束日期:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC29)->MoveWindow(m_rcRect2_1);
				}
				if(GetDlgItem(IDC_EDIT4)->GetSafeHwnd())//派工结束日期:
				{
					GetDlgItem(IDC_EDIT4)->MoveWindow(m_rcRect2_2);
				}
*/
				if(GetDlgItem(IDC_TASK_INFO_STATIC22)->GetSafeHwnd())//执行开始日期:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC22)->MoveWindow(m_rcRect1_1);
				}
				if(GetDlgItem(IDC_EDIT5)->GetSafeHwnd())//执行开始日期:
				{
					GetDlgItem(IDC_EDIT5)->MoveWindow(m_rcRect1_2);
				}
				if(GetDlgItem(IDC_BUTTON6)->GetSafeHwnd())// 执行开始日期:
				{
					GetDlgItem(IDC_BUTTON6)->MoveWindow(m_rcRect1_3);
				}


				if(GetDlgItem(IDC_TASK_INFO_STATIC30)->GetSafeHwnd())//执行结束日期:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC30)->MoveWindow(m_rcRect2_1);
				}
				if(GetDlgItem(IDC_EDIT6)->GetSafeHwnd())//执行结束日期:
				{
					GetDlgItem(IDC_EDIT6)->MoveWindow(m_rcRect2_2);
				}
				if(GetDlgItem(IDC_BUTTON7)->GetSafeHwnd())// 执行结束日期:
				{
					GetDlgItem(IDC_BUTTON7)->MoveWindow(m_rcRect2_3);
				}

			}
			break;
		case  Task_Finish:
			{
				if(GetDlgItem(IDC_TASK_INFO_STATIC22)->GetSafeHwnd())//执行开始日期:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC22)->MoveWindow(m_rcRect1_1);
				}
				if(GetDlgItem(IDC_EDIT5)->GetSafeHwnd())//执行开始日期:
				{
					GetDlgItem(IDC_EDIT5)->MoveWindow(m_rcRect1_2);
				}
				if(GetDlgItem(IDC_BUTTON6)->GetSafeHwnd())// 执行开始日期:
				{
					GetDlgItem(IDC_BUTTON6)->MoveWindow(m_rcRect1_3);
				}


				if(GetDlgItem(IDC_TASK_INFO_STATIC30)->GetSafeHwnd())//执行结束日期:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC30)->MoveWindow(m_rcRect2_1);
				}
				if(GetDlgItem(IDC_EDIT6)->GetSafeHwnd())//执行结束日期:
				{
					GetDlgItem(IDC_EDIT6)->MoveWindow(m_rcRect2_2);
				}
				if(GetDlgItem(IDC_BUTTON7)->GetSafeHwnd())// 执行结束日期:
				{
					GetDlgItem(IDC_BUTTON7)->MoveWindow(m_rcRect2_3);
				}


				if(GetDlgItem(IDC_TASK_INFO_STATIC25)->GetSafeHwnd())// 完成开始日期:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC25)->MoveWindow(m_rcRect3_1);
				}
				if(GetDlgItem(IDC_EDIT7)->GetSafeHwnd())// 完成开始日期:
				{
					GetDlgItem(IDC_EDIT7)->MoveWindow(m_rcRect3_2);
				}
				if(GetDlgItem(IDC_BUTTON8)->GetSafeHwnd())// 完成开始日期:
				{
					GetDlgItem(IDC_BUTTON8)->MoveWindow(m_rcRect3_3);
				}

				if(GetDlgItem(IDC_TASK_INFO_STATIC31)->GetSafeHwnd())//完成结束日期:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC31)->MoveWindow(m_rcRect4_1);
				}
				if(GetDlgItem(IDC_EDIT8)->GetSafeHwnd())//完成结束日期:
				{
					GetDlgItem(IDC_EDIT8)->MoveWindow(m_rcRect4_2);
				}
				if(GetDlgItem(IDC_BUTTON9)->GetSafeHwnd())// 完成结束日期:
				{
					GetDlgItem(IDC_BUTTON9)->MoveWindow(m_rcRect4_3);
				}


			}
			break;
		default:
			{/*
				if(GetDlgItem(IDC_TASK_INFO_STATIC21)->GetSafeHwnd())//派工开始日期:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC21)->MoveWindow(m_rcRect1_1);
				}
				if(GetDlgItem(IDC_SEND_DATE_EDT)->GetSafeHwnd())//派工开始日期:
				{
					GetDlgItem(IDC_SEND_DATE_EDT)->MoveWindow(m_rcRect1_2);
				}

				if(GetDlgItem(IDC_TASK_INFO_STATIC29)->GetSafeHwnd())//派工结束日期:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC29)->MoveWindow(m_rcRect2_1);
				}
				if(GetDlgItem(IDC_EDIT4)->GetSafeHwnd())//派工结束日期:
				{
					GetDlgItem(IDC_EDIT4)->MoveWindow(m_rcRect2_2);
				}

				if(GetDlgItem(IDC_TASK_INFO_STATIC22)->GetSafeHwnd())//执行开始日期:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC22)->MoveWindow(m_rcRect3_1);
				}
				if(GetDlgItem(IDC_EDIT5)->GetSafeHwnd())//执行开始日期:
				{
					GetDlgItem(IDC_EDIT5)->MoveWindow(m_rcRect3_2);
				}

				if(GetDlgItem(IDC_TASK_INFO_STATIC30)->GetSafeHwnd())//执行结束日期:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC30)->MoveWindow(m_rcRect4_1);
				}
				if(GetDlgItem(IDC_EDIT6)->GetSafeHwnd())//执行结束日期:
				{
					GetDlgItem(IDC_EDIT6)->MoveWindow(m_rcRect4_2);
				}

				if(GetDlgItem(IDC_TASK_INFO_STATIC25)->GetSafeHwnd())// 完成开始日期:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC25)->MoveWindow(m_rcRect5_1);
				}
				if(GetDlgItem(IDC_EDIT7)->GetSafeHwnd())// 完成开始日期:
				{
					GetDlgItem(IDC_EDIT7)->MoveWindow(m_rcRect5_2);
				}

				if(GetDlgItem(IDC_TASK_INFO_STATIC31)->GetSafeHwnd())//完成结束日期:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC31)->MoveWindow(m_rcRect6_1);
				}
				if(GetDlgItem(IDC_EDIT8)->GetSafeHwnd())//完成结束日期:
				{
					GetDlgItem(IDC_EDIT8)->MoveWindow(m_rcRect6_2);
				}
				*/
				//2017-03-10
				if(GetDlgItem(IDC_TASK_INFO_STATIC22)->GetSafeHwnd())//执行开始日期:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC22)->MoveWindow(m_rcRect1_1);
				}
				if(GetDlgItem(IDC_EDIT5)->GetSafeHwnd())//执行开始日期:
				{
					GetDlgItem(IDC_EDIT5)->MoveWindow(m_rcRect1_2);
				}
				if(GetDlgItem(IDC_BUTTON6)->GetSafeHwnd())// 执行开始日期:
				{
					GetDlgItem(IDC_BUTTON6)->MoveWindow(m_rcRect1_3);
				}


				if(GetDlgItem(IDC_TASK_INFO_STATIC30)->GetSafeHwnd())//执行结束日期:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC30)->MoveWindow(m_rcRect2_1);
				}
				if(GetDlgItem(IDC_EDIT6)->GetSafeHwnd())//执行结束日期:
				{
					GetDlgItem(IDC_EDIT6)->MoveWindow(m_rcRect2_2);
				}
				if(GetDlgItem(IDC_BUTTON7)->GetSafeHwnd())// 执行结束日期:
				{
					GetDlgItem(IDC_BUTTON7)->MoveWindow(m_rcRect2_3);
				}


				if(GetDlgItem(IDC_TASK_INFO_STATIC25)->GetSafeHwnd())// 完成开始日期:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC25)->MoveWindow(m_rcRect3_1);
				}
				if(GetDlgItem(IDC_EDIT7)->GetSafeHwnd())// 完成开始日期:
				{
					GetDlgItem(IDC_EDIT7)->MoveWindow(m_rcRect3_2);
				}
				if(GetDlgItem(IDC_BUTTON8)->GetSafeHwnd())// 完成开始日期:
				{
					GetDlgItem(IDC_BUTTON8)->MoveWindow(m_rcRect3_3);
				}

				if(GetDlgItem(IDC_TASK_INFO_STATIC31)->GetSafeHwnd())//完成结束日期:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC31)->MoveWindow(m_rcRect4_1);
				}
				if(GetDlgItem(IDC_EDIT8)->GetSafeHwnd())//完成结束日期:
				{
					GetDlgItem(IDC_EDIT8)->MoveWindow(m_rcRect4_2);
				}
				if(GetDlgItem(IDC_BUTTON9)->GetSafeHwnd())// 完成结束日期:
				{
					GetDlgItem(IDC_BUTTON9)->MoveWindow(m_rcRect4_3);
				}

			}
			break;

		}

	}

}
void CTaskSearch::InitComBox()
{

	CComboBox *pComBo;
	pComBo = (CComboBox*)GetDlgItem(IDC_COMBO2);
	pComBo->ResetContent();

	pComBo->AddString(_T("否"));
	pComBo->AddString(_T("是"));
	pComBo->AddString(_T("全部"));
	pComBo->SetCurSel(3);



	int i;
	pComBo = (CComboBox*)GetDlgItem(IDC_COMBO3);
	pComBo->ResetContent();

	for( i = Task_Init;i<=Task_All ;i++)
	{
		pComBo->AddString(g_TaskState[i]);
	}
	
	pComBo->SetCurSel(Task_All);

}
void CTaskSearch::DisplaySearchInfo()
{
	CString strText;
	strText.Format(_T("%s"), m_TaskSearchInfo.stTaskBaseInfo.szTaskName);
	GetDlgItem(IDC_TASK_NAME_EDT)->SetWindowText(strText);

	strText.Format(_T("%s"), m_TaskSearchInfo.stProductInfo.szProductNo);
	GetDlgItem(IDC_PRODUCT_NO_EDT)->SetWindowText(strText);

	strText.Format(_T("%s"), m_TaskSearchInfo.stProductInfo.szProductName);
	GetDlgItem(IDC_PRODUCT_NAME_EDT)->SetWindowText(strText);

	strText.Format(_T("%s"), m_TaskSearchInfo.stTaskBaseInfo.szModel);
	GetDlgItem(IDC_MODEL_EDT)->SetWindowText(strText);

	strText.Format(_T("%s"), m_TaskSearchInfo.stTaskBaseInfo.szPhase);
	GetDlgItem(IDC_PHASE_EDT)->SetWindowText(strText);

	strText.Format(_T("%s"), m_TaskSearchInfo.stHrUpDepart.szUpDepartName);
	GetDlgItem(IDC_UP_DEPART_EDT)->SetWindowText(strText);

	strText.Format(_T("%s"), m_TaskSearchInfo.stTaskBaseInfo.szCheckLeader);
	GetDlgItem(IDC_LEADER_EDT)->SetWindowText(strText);

	strText.Format(_T("%s"), m_TaskSearchInfo.stTaskBaseInfo.szCheckUser);
	GetDlgItem(IDC_CHECK_USER_EDT)->SetWindowText(strText);

	strText.Format(_T("%s"), m_TaskSearchInfo.stTaskBaseInfo.szCreateUser);
	GetDlgItem(IDC_CREATE_USER_EDT)->SetWindowText(strText);

	strText.Format(_T("%s"), m_TaskSearchInfo.stTaskBaseInfo.szCreateBeginTime);
	GetDlgItem(IDC_EDIT1)->SetWindowText(strText);//创建开始日期:
	strText.Format(_T("%s"), m_TaskSearchInfo.stTaskBaseInfo.szCreateEndTime);
	GetDlgItem(IDC_EDIT2)->SetWindowText(strText);//创建结束日期:

	strText.Format(_T("%s"), m_TaskSearchInfo.stTaskBaseInfo.szSendBeginTime);
	GetDlgItem(IDC_SEND_DATE_EDT)->SetWindowText(strText);//派工开始日期:
	strText.Format(_T("%s"), m_TaskSearchInfo.stTaskBaseInfo.szSendEndTime);
	GetDlgItem(IDC_EDIT4)->SetWindowText(strText);//派工结束日期:

	strText.Format(_T("%s"), m_TaskSearchInfo.stTaskBaseInfo.szDownLoadBeginTime);
	GetDlgItem(IDC_EDIT5)->SetWindowText(strText);//执行开始日期:
	strText.Format(_T("%s"), m_TaskSearchInfo.stTaskBaseInfo.szDownLoadEndTime);
	GetDlgItem(IDC_EDIT6)->SetWindowText(strText);//执行结束日期:

	strText.Format(_T("%s"), m_TaskSearchInfo.stTaskBaseInfo.szFinishBeginTime);
	GetDlgItem(IDC_EDIT7)->SetWindowText(strText);// 完成开始日期:
	strText.Format(_T("%s"), m_TaskSearchInfo.stTaskBaseInfo.szFinishEndTime);
	GetDlgItem(IDC_EDIT8)->SetWindowText(strText);//完成结束日期:

	int i = 0;
	CComboBox *pComBox = NULL;
	//是否军检//
	i = m_TaskSearchInfo.stTaskBaseInfo.nArmyTest;
	if(i< Army_Not || i> Army_All)
	{
		i = Army_All;
	}
	pComBox = ((CComboBox *)GetDlgItem(IDC_COMBO2));
	pComBox->SetCurSel(i);

	//任务状态//
	i = m_TaskSearchInfo.stTaskBaseInfo.nTaskStatus;
	if( i< Task_Init || i> Task_All)
	{
		i = Task_All;
	}
	pComBox = ((CComboBox *)GetDlgItem(IDC_COMBO3));
	pComBox->SetCurSel(i);
	/*
	
	if(m_TaskSearchInfo.stTaskBaseInfo.bTaskInit >= 1)//新任务//
	{
		i = 1;
	}else
	{
		i = 0;
	}
	((CButton *)GetDlgItem(IDC_CHECK1))->SetCheck(i);

	if(m_TaskSearchInfo.stTaskBaseInfo.bTaskOk >= 1)//已派工//
	{
		i = 1;
	}else
	{
		i = 0;
	}
	((CButton *)GetDlgItem(IDC_CHECK2))->SetCheck(i);

	if(m_TaskSearchInfo.stTaskBaseInfo.bTaskRuning >= 1)//执行中//
	{
		i = 1;
	}else
	{
		i = 0;
	}
	((CButton *)GetDlgItem(IDC_CHECK3))->SetCheck(i);

	if(m_TaskSearchInfo.stTaskBaseInfo.bTaskFinish >= 1)//已完成//
	{
		i = 1;
	}else
	{
		i = 0;
	}
	((CButton *)GetDlgItem(IDC_CHECK4))->SetCheck(i);

*/
	//任务类型
	
	if(m_TaskSearchInfo.stTaskBaseInfo.bTaskTest >= 1)//验收//
	{
		i = 1;
	}else
	{
		i = 0;
	}
	((CButton *)GetDlgItem(IDC_CHECK5))->SetCheck(i);

	if(m_TaskSearchInfo.stTaskBaseInfo.bTaskReTest >= 1)//复验//
	{
		i = 1;
	}else
	{
		i = 0;
	}
	((CButton *)GetDlgItem(IDC_CHECK6))->SetCheck(i);

	if(m_TaskSearchInfo.stTaskBaseInfo.bTaskHelpReTest >= 1)//外协复验//
	{
		i = 1;
	}else
	{
		i = 0;
	}
	((CButton *)GetDlgItem(IDC_CHECK7))->SetCheck(i);

	//控制隐藏//
	int nTaskStatus = m_TaskSearchInfo.stTaskBaseInfo.nTaskStatus;
	if(GetDlgItem(IDC_TASK_INFO_STATIC26)->GetSafeHwnd())
	{

		switch(nTaskStatus)
		{
		case Task_Init:
			{
				GetDlgItem(IDC_TASK_INFO_STATIC26)->ShowWindow(SW_HIDE);//创建开始日期:
				GetDlgItem(IDC_EDIT1)->ShowWindow(SW_HIDE);
				
				GetDlgItem(IDC_TASK_INFO_STATIC28)->ShowWindow(SW_HIDE);//创建结束日期:
				GetDlgItem(IDC_EDIT2)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_TASK_INFO_STATIC21)->ShowWindow(SW_HIDE);//派工开始日期:
				GetDlgItem(IDC_SEND_DATE_EDT)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_HIDE);
				
				GetDlgItem(IDC_TASK_INFO_STATIC29)->ShowWindow(SW_HIDE);//派工结束日期:
				GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_TASK_INFO_STATIC22)->ShowWindow(SW_HIDE);//执行开始日期:
				GetDlgItem(IDC_EDIT5)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON6)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_TASK_INFO_STATIC30)->ShowWindow(SW_HIDE);//执行结束日期:
				GetDlgItem(IDC_EDIT6)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON7)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_TASK_INFO_STATIC25)->ShowWindow(SW_HIDE);// 完成开始日期:
				GetDlgItem(IDC_EDIT7)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON8)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_TASK_INFO_STATIC31)->ShowWindow(SW_HIDE);//完成结束日期:
				GetDlgItem(IDC_EDIT8)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON9)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_COMBO3)->ShowWindow(SW_HIDE);//任务状态//

				GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);//新任务//
				GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);//已派工//
				GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);//执行中//
				GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);//已完成//
				ShowTaskTypeStatus(SW_HIDE);
				GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);////
				GetDlgItem(IDC_CHECK5)->ShowWindow(SW_HIDE);//验收//
				GetDlgItem(IDC_CHECK6)->ShowWindow(SW_HIDE);//复查//
				GetDlgItem(IDC_CHECK7)->ShowWindow(SW_HIDE);//外协复查//
				PostMessage(WM_SIZE);
			}
			break;
		case Task_OK:
			{
				GetDlgItem(IDC_TASK_INFO_STATIC26)->ShowWindow(SW_HIDE);//创建开始日期:
				GetDlgItem(IDC_EDIT1)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_TASK_INFO_STATIC28)->ShowWindow(SW_HIDE);//创建结束日期:
				GetDlgItem(IDC_EDIT2)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_TASK_INFO_STATIC21)->ShowWindow(SW_SHOW);//派工开始日期:
				GetDlgItem(IDC_SEND_DATE_EDT)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_TASK_INFO_STATIC29)->ShowWindow(SW_SHOW);//派工结束日期:
				GetDlgItem(IDC_EDIT4)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_TASK_INFO_STATIC22)->ShowWindow(SW_HIDE);//执行开始日期:
				GetDlgItem(IDC_EDIT5)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON6)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_TASK_INFO_STATIC30)->ShowWindow(SW_HIDE);//执行结束日期:
				GetDlgItem(IDC_EDIT6)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON7)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_TASK_INFO_STATIC25)->ShowWindow(SW_HIDE);// 完成开始日期:
				GetDlgItem(IDC_EDIT7)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON8)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_TASK_INFO_STATIC31)->ShowWindow(SW_HIDE);//完成结束日期:
				GetDlgItem(IDC_EDIT8)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON9)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_COMBO3)->ShowWindow(SW_HIDE);//任务状态//

				GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);//新任务//
				GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);//已派工//
				GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);//执行中//
				GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);//已完成//
				ShowTaskTypeStatus(SW_HIDE);
				GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);////
				GetDlgItem(IDC_CHECK5)->ShowWindow(SW_HIDE);//验收//
				GetDlgItem(IDC_CHECK6)->ShowWindow(SW_HIDE);//复查//
				GetDlgItem(IDC_CHECK7)->ShowWindow(SW_HIDE);//外协复查//
				PostMessage(WM_SIZE);
			}
			break;
		case  Task_Runing:
			{
				GetDlgItem(IDC_TASK_INFO_STATIC26)->ShowWindow(SW_HIDE);//创建开始日期:
				GetDlgItem(IDC_EDIT1)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_TASK_INFO_STATIC28)->ShowWindow(SW_HIDE);//创建结束日期:
				GetDlgItem(IDC_EDIT2)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_TASK_INFO_STATIC21)->ShowWindow(SW_HIDE);//派工开始日期:
				GetDlgItem(IDC_SEND_DATE_EDT)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_TASK_INFO_STATIC29)->ShowWindow(SW_HIDE);//派工结束日期:
				GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_TASK_INFO_STATIC22)->ShowWindow(SW_SHOW);//执行开始日期:
				GetDlgItem(IDC_EDIT5)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BUTTON6)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_TASK_INFO_STATIC30)->ShowWindow(SW_SHOW);//执行结束日期:
				GetDlgItem(IDC_EDIT6)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BUTTON7)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_TASK_INFO_STATIC25)->ShowWindow(SW_HIDE);// 完成开始日期:
				GetDlgItem(IDC_EDIT7)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON8)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_TASK_INFO_STATIC31)->ShowWindow(SW_HIDE);//完成结束日期:
				GetDlgItem(IDC_EDIT8)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON9)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_COMBO3)->ShowWindow(SW_HIDE);//任务状态//

				GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);//新任务//
				GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);//已派工//
				GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);//执行中//
				GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);//已完成//
				ShowTaskTypeStatus(SW_HIDE);
				GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);////
				GetDlgItem(IDC_CHECK5)->ShowWindow(SW_HIDE);//验收//
				GetDlgItem(IDC_CHECK6)->ShowWindow(SW_HIDE);//复查//
				GetDlgItem(IDC_CHECK7)->ShowWindow(SW_HIDE);//外协复查//
				PostMessage(WM_SIZE);
			}
			break;
		case  Task_Finish:
			{
				GetDlgItem(IDC_TASK_INFO_STATIC26)->ShowWindow(SW_HIDE);//创建开始日期:
				GetDlgItem(IDC_EDIT1)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_TASK_INFO_STATIC28)->ShowWindow(SW_HIDE);//创建结束日期:
				GetDlgItem(IDC_EDIT2)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_TASK_INFO_STATIC21)->ShowWindow(SW_HIDE);//派工开始日期:
				GetDlgItem(IDC_SEND_DATE_EDT)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_TASK_INFO_STATIC29)->ShowWindow(SW_HIDE);//派工结束日期:
				GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_TASK_INFO_STATIC22)->ShowWindow(SW_SHOW);//执行开始日期:
				GetDlgItem(IDC_EDIT5)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BUTTON6)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_TASK_INFO_STATIC30)->ShowWindow(SW_SHOW);//执行结束日期:
				GetDlgItem(IDC_EDIT6)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BUTTON7)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_TASK_INFO_STATIC25)->ShowWindow(SW_SHOW);// 完成开始日期:
				GetDlgItem(IDC_EDIT7)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BUTTON8)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_TASK_INFO_STATIC31)->ShowWindow(SW_SHOW);//完成结束日期:
				GetDlgItem(IDC_EDIT8)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BUTTON9)->ShowWindow(SW_SHOW);


				GetDlgItem(IDC_COMBO3)->ShowWindow(SW_HIDE);//任务状态//

				GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);//新任务//
				GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);//已派工//
				GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);//执行中//
				GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);//已完成//
				ShowTaskTypeStatus(SW_HIDE);

				GetDlgItem(IDC_STATIC2)->ShowWindow(TRUE);////
				GetDlgItem(IDC_CHECK5)->ShowWindow(TRUE);//验收//
				GetDlgItem(IDC_CHECK6)->ShowWindow(TRUE);//复查//
				GetDlgItem(IDC_CHECK7)->ShowWindow(TRUE);//外协复查//

				PostMessage(WM_SIZE);
			}
			break;
		default:
			{
				GetDlgItem(IDC_TASK_INFO_STATIC26)->ShowWindow(SW_HIDE);//创建开始日期:
				GetDlgItem(IDC_EDIT1)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_TASK_INFO_STATIC28)->ShowWindow(SW_HIDE);//创建结束日期:
				GetDlgItem(IDC_EDIT2)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_TASK_INFO_STATIC21)->ShowWindow(SW_HIDE);//派工开始日期:
				GetDlgItem(IDC_SEND_DATE_EDT)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_TASK_INFO_STATIC29)->ShowWindow(SW_HIDE);//派工结束日期:
				GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_TASK_INFO_STATIC22)->ShowWindow(SW_SHOW);//执行开始日期:
				GetDlgItem(IDC_EDIT5)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BUTTON6)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_TASK_INFO_STATIC30)->ShowWindow(SW_SHOW);//执行结束日期:
				GetDlgItem(IDC_EDIT6)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BUTTON7)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_TASK_INFO_STATIC25)->ShowWindow(SW_SHOW);// 完成开始日期:
				GetDlgItem(IDC_EDIT7)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BUTTON8)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_TASK_INFO_STATIC31)->ShowWindow(SW_SHOW);//完成结束日期:
				GetDlgItem(IDC_EDIT8)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BUTTON9)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_COMBO3)->ShowWindow(SW_SHOW);//任务状态//

				GetDlgItem(IDC_CHECK1)->EnableWindow(TRUE);//新任务//
				GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);//已派工//
				GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);//执行中//
				GetDlgItem(IDC_CHECK4)->EnableWindow(TRUE);//已完成//
				ShowTaskTypeStatus(SW_SHOW);


				GetDlgItem(IDC_STATIC2)->ShowWindow(TRUE);////
				GetDlgItem(IDC_CHECK5)->ShowWindow(TRUE);//验收//
				GetDlgItem(IDC_CHECK6)->ShowWindow(TRUE);//复查//
				GetDlgItem(IDC_CHECK7)->ShowWindow(TRUE);//外协复查//

				PostMessage(WM_SIZE);
			}
			break;

		}

	}
	
}
void CTaskSearch::ShowTaskTypeStatus(int nShowHide)
{
	GetDlgItem(IDC_STATIC1)->ShowWindow(nShowHide);////
	GetDlgItem(IDC_CHECK1)->ShowWindow(nShowHide);//新任务//
	GetDlgItem(IDC_CHECK2)->ShowWindow(nShowHide);//已派工//
	GetDlgItem(IDC_CHECK3)->ShowWindow(nShowHide);//执行中//
	GetDlgItem(IDC_CHECK4)->ShowWindow(nShowHide);//已完成//

	
}
void CTaskSearch::GetSearchInfo()
{
	
	CString strText;
	//strText.Format(_T("%s"), m_TaskSearchInfo.stTaskBaseInfo.szTaskName);

	//1_1 任务名称
	GetDlgItem(IDC_TASK_NAME_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(m_TaskSearchInfo.stTaskBaseInfo.szTaskName, 0, sizeof(m_TaskSearchInfo.stTaskBaseInfo.szTaskName));
	strcpy(m_TaskSearchInfo.stTaskBaseInfo.szTaskName, strText);

	//1_2 产品代号
	GetDlgItem(IDC_PRODUCT_NO_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(m_TaskSearchInfo.stProductInfo.szProductNo, 0, sizeof(m_TaskSearchInfo.stProductInfo.szProductNo));
	strcpy(m_TaskSearchInfo.stProductInfo.szProductNo, strText);

	//1_3 批次号
	GetDlgItem(IDC_BATCH_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(m_TaskSearchInfo.stTaskBaseInfo.szBatch, 0, sizeof(m_TaskSearchInfo.stTaskBaseInfo.szBatch));
	strcpy(m_TaskSearchInfo.stTaskBaseInfo.szBatch, strText);

	
	GetDlgItem(IDC_PRODUCT_NAME_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(m_TaskSearchInfo.stProductInfo.szProductName, 0, sizeof(m_TaskSearchInfo.stProductInfo.szProductName));
	strcpy(m_TaskSearchInfo.stProductInfo.szProductName, strText);


	//2_1 型号名称
	GetDlgItem(IDC_MODEL_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(m_TaskSearchInfo.stTaskBaseInfo.szModel, 0, sizeof(m_TaskSearchInfo.stTaskBaseInfo.szModel));
	strcpy(m_TaskSearchInfo.stTaskBaseInfo.szModel, strText);

	//2_2 阶段
	GetDlgItem(IDC_PHASE_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(m_TaskSearchInfo.stTaskBaseInfo.szPhase, 0, sizeof(m_TaskSearchInfo.stTaskBaseInfo.szPhase));
	strcpy(m_TaskSearchInfo.stTaskBaseInfo.szPhase, strText);

	//2_3 交检部门
	GetDlgItem(IDC_UP_DEPART_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(m_TaskSearchInfo.stHrUpDepart.szUpDepartName, 0, sizeof(m_TaskSearchInfo.stHrUpDepart.szUpDepartName));
	strcpy(m_TaskSearchInfo.stHrUpDepart.szUpDepartName, strText);

	//3_1 检验组长
	GetDlgItem(IDC_LEADER_EDT)->GetWindowText(strText);
	memset(m_TaskSearchInfo.stTaskBaseInfo.szCheckLeader, 0, sizeof(m_TaskSearchInfo.stTaskBaseInfo.szCheckLeader));
	strcpy(m_TaskSearchInfo.stTaskBaseInfo.szCheckLeader, strText);

	//3_2 检验员
	GetDlgItem(IDC_CHECK_USER_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(m_TaskSearchInfo.stTaskBaseInfo.szCheckUser, 0, sizeof(m_TaskSearchInfo.stTaskBaseInfo.szCheckUser));
	strcpy(m_TaskSearchInfo.stTaskBaseInfo.szCheckUser, strText);

	
	GetDlgItem(IDC_CREATE_USER_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(m_TaskSearchInfo.stTaskBaseInfo.szCreateUser, 0, sizeof(m_TaskSearchInfo.stTaskBaseInfo.szCreateUser));
	strcpy(m_TaskSearchInfo.stTaskBaseInfo.szCreateUser, strText);

	GetDlgItem(IDC_EDIT1)->GetWindowText(strText);//创建开始日期:
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(m_TaskSearchInfo.stTaskBaseInfo.szCreateBeginTime, 0, sizeof(m_TaskSearchInfo.stTaskBaseInfo.szCreateBeginTime));
	strcpy(m_TaskSearchInfo.stTaskBaseInfo.szCreateBeginTime, strText);

	GetDlgItem(IDC_EDIT2)->GetWindowText(strText);//创建结束日期:
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(m_TaskSearchInfo.stTaskBaseInfo.szCreateEndTime, 0, sizeof(m_TaskSearchInfo.stTaskBaseInfo.szCreateEndTime));
	strcpy(m_TaskSearchInfo.stTaskBaseInfo.szCreateEndTime, strText);

	GetDlgItem(IDC_SEND_DATE_EDT)->GetWindowText(strText);//派工开始日期:
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(m_TaskSearchInfo.stTaskBaseInfo.szSendBeginTime, 0, sizeof(m_TaskSearchInfo.stTaskBaseInfo.szSendBeginTime));
	strcpy(m_TaskSearchInfo.stTaskBaseInfo.szSendBeginTime, strText);

	GetDlgItem(IDC_EDIT4)->GetWindowText(strText);//派工结束日期:
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(m_TaskSearchInfo.stTaskBaseInfo.szSendEndTime, 0, sizeof(m_TaskSearchInfo.stTaskBaseInfo.szSendEndTime));
	strcpy(m_TaskSearchInfo.stTaskBaseInfo.szSendEndTime, strText);

	GetDlgItem(IDC_EDIT5)->GetWindowText(strText);//执行开始日期:
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(m_TaskSearchInfo.stTaskBaseInfo.szDownLoadBeginTime, 0, sizeof(m_TaskSearchInfo.stTaskBaseInfo.szDownLoadBeginTime));
	strcpy(m_TaskSearchInfo.stTaskBaseInfo.szDownLoadBeginTime, strText);

	GetDlgItem(IDC_EDIT6)->GetWindowText(strText);//执行结束日期:
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(m_TaskSearchInfo.stTaskBaseInfo.szDownLoadEndTime, 0, sizeof(m_TaskSearchInfo.stTaskBaseInfo.szDownLoadEndTime));
	strcpy(m_TaskSearchInfo.stTaskBaseInfo.szDownLoadEndTime, strText);

	strText.Format(_T("%s"), m_TaskSearchInfo.stTaskBaseInfo.szFinishBeginTime);
	GetDlgItem(IDC_EDIT7)->GetWindowText(strText);// 完成开始日期:
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(m_TaskSearchInfo.stTaskBaseInfo.szFinishBeginTime, 0, sizeof(m_TaskSearchInfo.stTaskBaseInfo.szFinishBeginTime));
	strcpy(m_TaskSearchInfo.stTaskBaseInfo.szFinishBeginTime, strText);

	GetDlgItem(IDC_EDIT8)->GetWindowText(strText);//完成结束日期:
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(m_TaskSearchInfo.stTaskBaseInfo.szFinishEndTime, 0, sizeof(m_TaskSearchInfo.stTaskBaseInfo.szFinishEndTime));
	strcpy(m_TaskSearchInfo.stTaskBaseInfo.szFinishEndTime, strText);

	int i = 0;
	CComboBox *pComBox = NULL;
	//是否军检//
	pComBox = ((CComboBox *)GetDlgItem(IDC_COMBO2));
	i = pComBox->GetCurSel();
	if(i< Army_Not || i> Army_All)
	{
		i = Army_All;
	}
	m_TaskSearchInfo.stTaskBaseInfo.nArmyTest = i;


	//任务状态//


	/*
	//新任务
	i = ((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck();
	m_TaskSearchInfo.stTaskBaseInfo.bTaskInit = i;

	//已派工//
	i = ((CButton *)GetDlgItem(IDC_CHECK2))->GetCheck();
	m_TaskSearchInfo.stTaskBaseInfo.bTaskOk = i;

	//执行中//
	i = ((CButton *)GetDlgItem(IDC_CHECK3))->GetCheck();
	m_TaskSearchInfo.stTaskBaseInfo.bTaskRuning = i;

	//已完成//
	i = ((CButton *)GetDlgItem(IDC_CHECK4))->GetCheck();
	m_TaskSearchInfo.stTaskBaseInfo.bTaskFinish = i;
*/
	//2017-03-10：
	pComBox = ((CComboBox *)GetDlgItem(IDC_COMBO3));
	i = pComBox->GetCurSel();
	if(i< Task_Init || i> Task_All)
	{
		i = Task_All;
	}

	//m_TaskSearchInfo.stTaskBaseInfo.nTaskStatus = i;
	switch(i)
	{
	case Task_Init:
		{
			m_TaskSearchInfo.stTaskBaseInfo.bTaskInit = Sel_Check;
			m_TaskSearchInfo.stTaskBaseInfo.bTaskOk = UnSel_Check;
			m_TaskSearchInfo.stTaskBaseInfo.bTaskRuning = UnSel_Check;
			m_TaskSearchInfo.stTaskBaseInfo.bTaskFinish = UnSel_Check;
		}
		break;
	case Task_OK:
		{
			m_TaskSearchInfo.stTaskBaseInfo.bTaskInit = UnSel_Check;
			m_TaskSearchInfo.stTaskBaseInfo.bTaskOk = Sel_Check;
			m_TaskSearchInfo.stTaskBaseInfo.bTaskRuning = UnSel_Check;
			m_TaskSearchInfo.stTaskBaseInfo.bTaskFinish = UnSel_Check;
		}
		break;
	case Task_Runing:
		{
			m_TaskSearchInfo.stTaskBaseInfo.bTaskInit = UnSel_Check;
			m_TaskSearchInfo.stTaskBaseInfo.bTaskOk = UnSel_Check;
			m_TaskSearchInfo.stTaskBaseInfo.bTaskRuning = Sel_Check;
			m_TaskSearchInfo.stTaskBaseInfo.bTaskFinish = UnSel_Check;
		}
		break;
	case Task_Finish:
		{
			m_TaskSearchInfo.stTaskBaseInfo.bTaskInit = UnSel_Check;
			m_TaskSearchInfo.stTaskBaseInfo.bTaskOk = UnSel_Check;
			m_TaskSearchInfo.stTaskBaseInfo.bTaskRuning = UnSel_Check;
			m_TaskSearchInfo.stTaskBaseInfo.bTaskFinish = Sel_Check;
		}
		break;
	default:
		{
			m_TaskSearchInfo.stTaskBaseInfo.bTaskInit = Sel_Check;
			m_TaskSearchInfo.stTaskBaseInfo.bTaskOk = Sel_Check;
			m_TaskSearchInfo.stTaskBaseInfo.bTaskRuning = Sel_Check;
			m_TaskSearchInfo.stTaskBaseInfo.bTaskFinish = Sel_Check;
		}
	}

	//任务类型
	//验收//
	i = ((CButton *)GetDlgItem(IDC_CHECK5))->GetCheck();
	m_TaskSearchInfo.stTaskBaseInfo.bTaskTest = i;

	//复验//
	i = ((CButton *)GetDlgItem(IDC_CHECK6))->GetCheck();
	m_TaskSearchInfo.stTaskBaseInfo.bTaskReTest = i;

	//外协复验//
	i = ((CButton *)GetDlgItem(IDC_CHECK7))->GetCheck();
	m_TaskSearchInfo.stTaskBaseInfo.bTaskHelpReTest = i;

}

int CTaskSearch::CheckDateBegSmallEnd(char *pBegTime, char *pEndTime)
{
	char     szTime1[30] = {0,};
	char     szTime2[30] = {0,};
	int      nNum1, nNum2;

	if ( (strlen(pBegTime) > 0) && (strlen(pBegTime) > 0) )
	{
		memset(szTime1, 0, 30);
		memset(szTime2, 0, 30);
		memcpy(szTime1+0, (char*)(pBegTime+0), 4);
		memcpy(szTime1+4, (char*)(pBegTime+5), 2);
		memcpy(szTime1+6, (char*)(pBegTime+8), 2);

		memcpy(szTime2+0, (char*)(pEndTime+0), 4);
		memcpy(szTime2+4, (char*)(pEndTime+5), 2);
		memcpy(szTime2+6, (char*)(pEndTime+8), 2);

		nNum1 = atoi(szTime1);
		nNum2 = atoi(szTime2);
		if (nNum1 > nNum2)
		{
			return 0;
		}
	}

	return 1;
}


int CTaskSearch::CheckSearchTime( )                    //检测查询时间是否合法
{

	char     *pBegTime, *pEndTime;
	int      bFlag = 1;
	


	//1.派工
	//------------------------------------------------------------------------
	pBegTime = m_TaskSearchInfo.stTaskBaseInfo.szSendBeginTime;	//派工开始日期:
	pEndTime = m_TaskSearchInfo.stTaskBaseInfo.szSendEndTime;	//派工结束日期:

	bFlag = CheckDateBegSmallEnd(pBegTime, pEndTime);
	if (bFlag == 0)
	{
		AfxMessageBox("Err,派工开始时间大于结束时间!");
		return 0;
	}


	//2.执行
	//------------------------------------------------------------------------
	pBegTime = m_TaskSearchInfo.stTaskBaseInfo.szDownLoadBeginTime;	//执行开始日期:
	pEndTime = m_TaskSearchInfo.stTaskBaseInfo.szDownLoadEndTime;	//执行结束日期:

	bFlag = CheckDateBegSmallEnd(pBegTime, pEndTime);
	if (bFlag == 0)
	{
		AfxMessageBox("Err,执行开始时间大于结束时间!");
		return 0;
	}

	//3.完成
	//------------------------------------------------------------------------
	pBegTime = m_TaskSearchInfo.stTaskBaseInfo.szFinishBeginTime;	//执行开始日期:
	pEndTime = m_TaskSearchInfo.stTaskBaseInfo.szFinishEndTime;		//执行结束日期:

	bFlag = CheckDateBegSmallEnd(pBegTime, pEndTime);
	if (bFlag == 0)
	{
		AfxMessageBox("Err,完成开始时间大于结束时间!");
		return 0;
	}

	return 1;
}

void CTaskSearch::OnBnClickedTaskSearchBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	GetSearchInfo();

	int  bFlag = 0;
	bFlag = CheckSearchTime();		//检测时间是否合法
	if (bFlag == 0)
	{
		return;
	}

	g_pShowInfoList->m_ResultList.GetPageNumComBox();
	StSearchSetInfo *pSearchSetInfo = &g_pShowInfoList->m_ResultList.m_stSearchSetInfo;
	m_TaskSearchInfo.stTaskBaseInfo.nPerPageNum = pSearchSetInfo->nPerPageNum;
	//m_TaskSearchInfo.stTaskBaseInfo.nCurPage = 1;
	m_TaskSearchInfo.stTaskBaseInfo.nCurPage = pSearchSetInfo->nAimPage;

	if(m_TaskSearchInfo.stTaskBaseInfo.nCurPage <= 0)
	{
		m_TaskSearchInfo.stTaskBaseInfo.nCurPage = 1;
	}
	bFlag = g_pShowInfoList->DisPlayTaskInfo(&m_TaskSearchInfo);
	if (bFlag == 0)
	{
		m_TaskSearchInfo.stTaskBaseInfo.nCurPage = 1;
		g_pShowInfoList->DisPlayTaskInfo(&m_TaskSearchInfo);
	}

}

//选择检验组长//
void CTaskSearch::OnBnClickedButton2()
{  
	// TODO: 在此添加控件通知处理程序代码
	CSelUserDlg Dlg;
	CString strUserName;
	if(Dlg.DoModal() == IDOK)
	{
		strUserName = Dlg.m_SelUserName;
		GetDlgItem(IDC_LEADER_EDT)->SetWindowText(strUserName);
	}

}
//选择检验员//
void CTaskSearch::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CSelUserDlg Dlg;
	CString strUserName;
	if(Dlg.DoModal() == IDOK)
	{
		strUserName = Dlg.m_SelUserName;
		GetDlgItem(IDC_CHECK_USER_EDT)->SetWindowText(strUserName);
	}
}
//选择交检部门//
void CTaskSearch::OnBnClickedSelUpDepartBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strUpDepartName;
	CSelUpDepartDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		strUpDepartName = dlg.m_UpDepartName;
		GetDlgItem(IDC_UP_DEPART_EDT)->SetWindowText(strUpDepartName);
	}
}
//选择产品代号//
void CTaskSearch::OnBnClickedSelProdnoBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	CSelProductDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		GetDlgItem(IDC_PRODUCT_NO_EDT)->SetWindowText(dlg.m_strProductNo);
	}
}

//选择派工开始时间//
void CTaskSearch::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CSelDate Dlg;
	CString strBeginDate;
	SYSTEMTIME *pstTime = NULL;
	if(Dlg.DoModal() == IDOK)
	{
		pstTime = &Dlg.m_stTime;
		strBeginDate.Format(_T("%04d-%02d-%02d"),pstTime->wYear,pstTime->wMonth,pstTime->wDay);
		GetDlgItem(IDC_SEND_DATE_EDT)->SetWindowText(strBeginDate);
	}

}
//选择派工结束时间//
void CTaskSearch::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	CSelDate Dlg;
	CString strBeginDate;
	SYSTEMTIME *pstTime = NULL;
	if(Dlg.DoModal() == IDOK)
	{
		pstTime = &Dlg.m_stTime;
		strBeginDate.Format(_T("%04d-%02d-%02d"),pstTime->wYear,pstTime->wMonth,pstTime->wDay);
		GetDlgItem(IDC_EDIT4)->SetWindowText(strBeginDate);
	}
}

//选择执行开始时间//
void CTaskSearch::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	CSelDate Dlg;
	CString strBeginDate;
	SYSTEMTIME *pstTime = NULL;
	if(Dlg.DoModal() == IDOK)
	{
		pstTime = &Dlg.m_stTime;
		strBeginDate.Format(_T("%04d-%02d-%02d"),pstTime->wYear,pstTime->wMonth,pstTime->wDay);
		GetDlgItem(IDC_EDIT5)->SetWindowText(strBeginDate);
	}
}
//选择执行结束时间//
void CTaskSearch::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	CSelDate Dlg;
	CString strBeginDate;
	SYSTEMTIME *pstTime = NULL;
	if(Dlg.DoModal() == IDOK)
	{
		pstTime = &Dlg.m_stTime;
		strBeginDate.Format(_T("%04d-%02d-%02d"),pstTime->wYear,pstTime->wMonth,pstTime->wDay);
		GetDlgItem(IDC_EDIT6)->SetWindowText(strBeginDate);
	}
}
//选择完成开始时间//
void CTaskSearch::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	CSelDate Dlg;
	CString strBeginDate;
	SYSTEMTIME *pstTime = NULL;
	if(Dlg.DoModal() == IDOK)
	{
		pstTime = &Dlg.m_stTime;
		strBeginDate.Format(_T("%04d-%02d-%02d"),pstTime->wYear,pstTime->wMonth,pstTime->wDay);
		GetDlgItem(IDC_EDIT7)->SetWindowText(strBeginDate);
	}
}
//选择完成结束时间//
void CTaskSearch::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	CSelDate Dlg;
	CString strBeginDate;
	SYSTEMTIME *pstTime = NULL;
	if(Dlg.DoModal() == IDOK)
	{
		pstTime = &Dlg.m_stTime;
		strBeginDate.Format(_T("%04d-%02d-%02d"),pstTime->wYear,pstTime->wMonth,pstTime->wDay);
		GetDlgItem(IDC_EDIT8)->SetWindowText(strBeginDate);
	}
}
