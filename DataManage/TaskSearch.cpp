// TaskSearch.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataManage.h"
#include "TaskSearch.h"
#include "SelUserDlg.h"
#include "SelDate.h"
#include "SelUpDepartDlg.h"
#include "SelProductDlg.h"


// CTaskSearch �Ի���

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


// CTaskSearch ��Ϣ�������

BOOL CTaskSearch::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
/*
	GetDlgItem(IDC_TASK_INFO_STATIC26)->GetWindowRect(&m_rcRect1_1);//������ʼ����:
	GetDlgItem(IDC_EDIT1)->GetWindowRect(&m_rcRect1_2);

	GetDlgItem(IDC_TASK_INFO_STATIC28)->GetWindowRect(&m_rcRect2_1);//������������:
	GetDlgItem(IDC_EDIT2)->GetWindowRect(&m_rcRect2_2);

	GetDlgItem(IDC_TASK_INFO_STATIC21)->GetWindowRect(&m_rcRect3_1);//�ɹ���ʼ����:
	GetDlgItem(IDC_SEND_DATE_EDT)->GetWindowRect(&m_rcRect3_2);

	GetDlgItem(IDC_TASK_INFO_STATIC29)->GetWindowRect(&m_rcRect4_1);//�ɹ���������:
	GetDlgItem(IDC_EDIT4)->GetWindowRect(&m_rcRect4_2);

	GetDlgItem(IDC_TASK_INFO_STATIC22)->GetWindowRect(&m_rcRect5_1);//ִ�п�ʼ����:
	GetDlgItem(IDC_EDIT5)->GetWindowRect(&m_rcRect5_2);

	GetDlgItem(IDC_TASK_INFO_STATIC30)->GetWindowRect(&m_rcRect6_1);//ִ�н�������:
	GetDlgItem(IDC_EDIT6)->GetWindowRect(&m_rcRect6_2);

	GetDlgItem(IDC_TASK_INFO_STATIC25)->GetWindowRect(&m_rcRect7_1);// ��ɿ�ʼ����:
	GetDlgItem(IDC_EDIT7)->GetWindowRect(&m_rcRect7_2);

	GetDlgItem(IDC_TASK_INFO_STATIC31)->GetWindowRect(&m_rcRect8_1);//��ɽ�������:
	GetDlgItem(IDC_EDIT8)->GetWindowRect(&m_rcRect8_2);


	ScreenToClient(&m_rcRect1_1);ScreenToClient(&m_rcRect1_2);//������ʼ����:
	ScreenToClient(&m_rcRect2_1);ScreenToClient(&m_rcRect2_2);//������������:
	ScreenToClient(&m_rcRect3_1);ScreenToClient(&m_rcRect3_2);//�ɹ���ʼ����:
	ScreenToClient(&m_rcRect4_1);ScreenToClient(&m_rcRect4_2);//�ɹ���������:
	ScreenToClient(&m_rcRect5_1);ScreenToClient(&m_rcRect5_2);//ִ�п�ʼ����:
	ScreenToClient(&m_rcRect6_1);ScreenToClient(&m_rcRect6_2);//ִ�н�������:
	ScreenToClient(&m_rcRect7_1);ScreenToClient(&m_rcRect7_2);//��ɿ�ʼ����:
	ScreenToClient(&m_rcRect8_1);ScreenToClient(&m_rcRect8_2);//��ɽ�������:
*/

	//2017-03-10:
	GetDlgItem(IDC_TASK_INFO_STATIC21)->GetWindowRect(&m_rcRect1_1);//�ɹ���ʼ����:
	GetDlgItem(IDC_SEND_DATE_EDT)->GetWindowRect(&m_rcRect1_2);
	GetDlgItem(IDC_BUTTON4)->GetWindowRect(&m_rcRect1_3);

	GetDlgItem(IDC_TASK_INFO_STATIC29)->GetWindowRect(&m_rcRect2_1);//�ɹ���������:
	GetDlgItem(IDC_EDIT4)->GetWindowRect(&m_rcRect2_2);
	GetDlgItem(IDC_BUTTON5)->GetWindowRect(&m_rcRect2_3);


	GetDlgItem(IDC_TASK_INFO_STATIC22)->GetWindowRect(&m_rcRect3_1);//ִ�п�ʼ����:
	GetDlgItem(IDC_EDIT5)->GetWindowRect(&m_rcRect3_2);
	GetDlgItem(IDC_BUTTON6)->GetWindowRect(&m_rcRect3_3);

	GetDlgItem(IDC_TASK_INFO_STATIC30)->GetWindowRect(&m_rcRect4_1);//ִ�н�������:
	GetDlgItem(IDC_EDIT6)->GetWindowRect(&m_rcRect4_2);
	GetDlgItem(IDC_BUTTON7)->GetWindowRect(&m_rcRect4_3);

	GetDlgItem(IDC_TASK_INFO_STATIC25)->GetWindowRect(&m_rcRect5_1);// ��ɿ�ʼ����:
	GetDlgItem(IDC_EDIT7)->GetWindowRect(&m_rcRect5_2);
	GetDlgItem(IDC_BUTTON8)->GetWindowRect(&m_rcRect5_3);

	GetDlgItem(IDC_TASK_INFO_STATIC31)->GetWindowRect(&m_rcRect6_1);//��ɽ�������:
	GetDlgItem(IDC_EDIT8)->GetWindowRect(&m_rcRect6_2);
	GetDlgItem(IDC_BUTTON9)->GetWindowRect(&m_rcRect6_3);

	ScreenToClient(&m_rcRect1_1);ScreenToClient(&m_rcRect1_2);ScreenToClient(&m_rcRect1_3);//�ɹ���ʼ����:
	ScreenToClient(&m_rcRect2_1);ScreenToClient(&m_rcRect2_2);ScreenToClient(&m_rcRect2_3);//�ɹ���������:
	ScreenToClient(&m_rcRect3_1);ScreenToClient(&m_rcRect3_2);ScreenToClient(&m_rcRect3_3);//ִ�п�ʼ����:
	ScreenToClient(&m_rcRect4_1);ScreenToClient(&m_rcRect4_2);ScreenToClient(&m_rcRect4_3);//ִ�н�������:
	ScreenToClient(&m_rcRect5_1);ScreenToClient(&m_rcRect5_2);ScreenToClient(&m_rcRect5_3);//��ɿ�ʼ����:
	ScreenToClient(&m_rcRect6_1);ScreenToClient(&m_rcRect6_2);ScreenToClient(&m_rcRect6_3);//��ɽ�������:


	
	InitComBox();

	DisplaySearchInfo();
	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CTaskSearch::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialog::OnOK();
}

void CTaskSearch::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
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
				//if(GetDlgItem(IDC_TASK_INFO_STATIC26)->GetSafeHwnd())//������ʼ����:
				//{
				//	GetDlgItem(IDC_TASK_INFO_STATIC26)->MoveWindow(m_rcRect1_1);
				//}
				//if(GetDlgItem(IDC_EDIT1)->GetSafeHwnd())//������ʼ����:
				//{
				//	GetDlgItem(IDC_EDIT1)->MoveWindow(m_rcRect1_2);
				//}
				//
				//if(GetDlgItem(IDC_TASK_INFO_STATIC28)->GetSafeHwnd())//������������:
				//{
				//	GetDlgItem(IDC_TASK_INFO_STATIC28)->MoveWindow(m_rcRect2_1);
				//}
				//if(GetDlgItem(IDC_EDIT2)->GetSafeHwnd())//������������:
				//{
				//	GetDlgItem(IDC_EDIT2)->MoveWindow(m_rcRect2_2);
				//}
			}
			break;
		case Task_OK:
			{
				if(GetDlgItem(IDC_TASK_INFO_STATIC21)->GetSafeHwnd())// �ɹ���ʼ����:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC21)->MoveWindow(m_rcRect1_1);
				}
				if(GetDlgItem(IDC_SEND_DATE_EDT)->GetSafeHwnd())// �ɹ���ʼ����:
				{
					GetDlgItem(IDC_SEND_DATE_EDT)->MoveWindow(m_rcRect1_2);
				}
				if(GetDlgItem(IDC_BUTTON4)->GetSafeHwnd())// �ɹ���ʼ����:
				{
					GetDlgItem(IDC_BUTTON4)->MoveWindow(m_rcRect1_3);
				}

				if(GetDlgItem(IDC_TASK_INFO_STATIC29)->GetSafeHwnd())// �ɹ���������:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC29)->MoveWindow(m_rcRect2_1);
				}
				if(GetDlgItem(IDC_EDIT4)->GetSafeHwnd())// �ɹ���������:
				{
					GetDlgItem(IDC_EDIT4)->MoveWindow(m_rcRect2_2);
				}
				if(GetDlgItem(IDC_BUTTON5)->GetSafeHwnd())// �ɹ���ʼ����:
				{
					GetDlgItem(IDC_BUTTON5)->MoveWindow(m_rcRect2_3);
				}

			}
			break;
		case  Task_Runing:
			{
				/*
				if(GetDlgItem(IDC_TASK_INFO_STATIC21)->GetSafeHwnd())//�ɹ���ʼ����:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC21)->MoveWindow(m_rcRect1_1);
				}
				if(GetDlgItem(IDC_SEND_DATE_EDT)->GetSafeHwnd())//�ɹ���ʼ����:
				{
					GetDlgItem(IDC_SEND_DATE_EDT)->MoveWindow(m_rcRect1_2);
				}

				if(GetDlgItem(IDC_TASK_INFO_STATIC29)->GetSafeHwnd())//�ɹ���������:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC29)->MoveWindow(m_rcRect2_1);
				}
				if(GetDlgItem(IDC_EDIT4)->GetSafeHwnd())//�ɹ���������:
				{
					GetDlgItem(IDC_EDIT4)->MoveWindow(m_rcRect2_2);
				}
*/
				if(GetDlgItem(IDC_TASK_INFO_STATIC22)->GetSafeHwnd())//ִ�п�ʼ����:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC22)->MoveWindow(m_rcRect1_1);
				}
				if(GetDlgItem(IDC_EDIT5)->GetSafeHwnd())//ִ�п�ʼ����:
				{
					GetDlgItem(IDC_EDIT5)->MoveWindow(m_rcRect1_2);
				}
				if(GetDlgItem(IDC_BUTTON6)->GetSafeHwnd())// ִ�п�ʼ����:
				{
					GetDlgItem(IDC_BUTTON6)->MoveWindow(m_rcRect1_3);
				}


				if(GetDlgItem(IDC_TASK_INFO_STATIC30)->GetSafeHwnd())//ִ�н�������:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC30)->MoveWindow(m_rcRect2_1);
				}
				if(GetDlgItem(IDC_EDIT6)->GetSafeHwnd())//ִ�н�������:
				{
					GetDlgItem(IDC_EDIT6)->MoveWindow(m_rcRect2_2);
				}
				if(GetDlgItem(IDC_BUTTON7)->GetSafeHwnd())// ִ�н�������:
				{
					GetDlgItem(IDC_BUTTON7)->MoveWindow(m_rcRect2_3);
				}

			}
			break;
		case  Task_Finish:
			{
				if(GetDlgItem(IDC_TASK_INFO_STATIC22)->GetSafeHwnd())//ִ�п�ʼ����:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC22)->MoveWindow(m_rcRect1_1);
				}
				if(GetDlgItem(IDC_EDIT5)->GetSafeHwnd())//ִ�п�ʼ����:
				{
					GetDlgItem(IDC_EDIT5)->MoveWindow(m_rcRect1_2);
				}
				if(GetDlgItem(IDC_BUTTON6)->GetSafeHwnd())// ִ�п�ʼ����:
				{
					GetDlgItem(IDC_BUTTON6)->MoveWindow(m_rcRect1_3);
				}


				if(GetDlgItem(IDC_TASK_INFO_STATIC30)->GetSafeHwnd())//ִ�н�������:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC30)->MoveWindow(m_rcRect2_1);
				}
				if(GetDlgItem(IDC_EDIT6)->GetSafeHwnd())//ִ�н�������:
				{
					GetDlgItem(IDC_EDIT6)->MoveWindow(m_rcRect2_2);
				}
				if(GetDlgItem(IDC_BUTTON7)->GetSafeHwnd())// ִ�н�������:
				{
					GetDlgItem(IDC_BUTTON7)->MoveWindow(m_rcRect2_3);
				}


				if(GetDlgItem(IDC_TASK_INFO_STATIC25)->GetSafeHwnd())// ��ɿ�ʼ����:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC25)->MoveWindow(m_rcRect3_1);
				}
				if(GetDlgItem(IDC_EDIT7)->GetSafeHwnd())// ��ɿ�ʼ����:
				{
					GetDlgItem(IDC_EDIT7)->MoveWindow(m_rcRect3_2);
				}
				if(GetDlgItem(IDC_BUTTON8)->GetSafeHwnd())// ��ɿ�ʼ����:
				{
					GetDlgItem(IDC_BUTTON8)->MoveWindow(m_rcRect3_3);
				}

				if(GetDlgItem(IDC_TASK_INFO_STATIC31)->GetSafeHwnd())//��ɽ�������:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC31)->MoveWindow(m_rcRect4_1);
				}
				if(GetDlgItem(IDC_EDIT8)->GetSafeHwnd())//��ɽ�������:
				{
					GetDlgItem(IDC_EDIT8)->MoveWindow(m_rcRect4_2);
				}
				if(GetDlgItem(IDC_BUTTON9)->GetSafeHwnd())// ��ɽ�������:
				{
					GetDlgItem(IDC_BUTTON9)->MoveWindow(m_rcRect4_3);
				}


			}
			break;
		default:
			{/*
				if(GetDlgItem(IDC_TASK_INFO_STATIC21)->GetSafeHwnd())//�ɹ���ʼ����:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC21)->MoveWindow(m_rcRect1_1);
				}
				if(GetDlgItem(IDC_SEND_DATE_EDT)->GetSafeHwnd())//�ɹ���ʼ����:
				{
					GetDlgItem(IDC_SEND_DATE_EDT)->MoveWindow(m_rcRect1_2);
				}

				if(GetDlgItem(IDC_TASK_INFO_STATIC29)->GetSafeHwnd())//�ɹ���������:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC29)->MoveWindow(m_rcRect2_1);
				}
				if(GetDlgItem(IDC_EDIT4)->GetSafeHwnd())//�ɹ���������:
				{
					GetDlgItem(IDC_EDIT4)->MoveWindow(m_rcRect2_2);
				}

				if(GetDlgItem(IDC_TASK_INFO_STATIC22)->GetSafeHwnd())//ִ�п�ʼ����:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC22)->MoveWindow(m_rcRect3_1);
				}
				if(GetDlgItem(IDC_EDIT5)->GetSafeHwnd())//ִ�п�ʼ����:
				{
					GetDlgItem(IDC_EDIT5)->MoveWindow(m_rcRect3_2);
				}

				if(GetDlgItem(IDC_TASK_INFO_STATIC30)->GetSafeHwnd())//ִ�н�������:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC30)->MoveWindow(m_rcRect4_1);
				}
				if(GetDlgItem(IDC_EDIT6)->GetSafeHwnd())//ִ�н�������:
				{
					GetDlgItem(IDC_EDIT6)->MoveWindow(m_rcRect4_2);
				}

				if(GetDlgItem(IDC_TASK_INFO_STATIC25)->GetSafeHwnd())// ��ɿ�ʼ����:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC25)->MoveWindow(m_rcRect5_1);
				}
				if(GetDlgItem(IDC_EDIT7)->GetSafeHwnd())// ��ɿ�ʼ����:
				{
					GetDlgItem(IDC_EDIT7)->MoveWindow(m_rcRect5_2);
				}

				if(GetDlgItem(IDC_TASK_INFO_STATIC31)->GetSafeHwnd())//��ɽ�������:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC31)->MoveWindow(m_rcRect6_1);
				}
				if(GetDlgItem(IDC_EDIT8)->GetSafeHwnd())//��ɽ�������:
				{
					GetDlgItem(IDC_EDIT8)->MoveWindow(m_rcRect6_2);
				}
				*/
				//2017-03-10
				if(GetDlgItem(IDC_TASK_INFO_STATIC22)->GetSafeHwnd())//ִ�п�ʼ����:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC22)->MoveWindow(m_rcRect1_1);
				}
				if(GetDlgItem(IDC_EDIT5)->GetSafeHwnd())//ִ�п�ʼ����:
				{
					GetDlgItem(IDC_EDIT5)->MoveWindow(m_rcRect1_2);
				}
				if(GetDlgItem(IDC_BUTTON6)->GetSafeHwnd())// ִ�п�ʼ����:
				{
					GetDlgItem(IDC_BUTTON6)->MoveWindow(m_rcRect1_3);
				}


				if(GetDlgItem(IDC_TASK_INFO_STATIC30)->GetSafeHwnd())//ִ�н�������:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC30)->MoveWindow(m_rcRect2_1);
				}
				if(GetDlgItem(IDC_EDIT6)->GetSafeHwnd())//ִ�н�������:
				{
					GetDlgItem(IDC_EDIT6)->MoveWindow(m_rcRect2_2);
				}
				if(GetDlgItem(IDC_BUTTON7)->GetSafeHwnd())// ִ�н�������:
				{
					GetDlgItem(IDC_BUTTON7)->MoveWindow(m_rcRect2_3);
				}


				if(GetDlgItem(IDC_TASK_INFO_STATIC25)->GetSafeHwnd())// ��ɿ�ʼ����:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC25)->MoveWindow(m_rcRect3_1);
				}
				if(GetDlgItem(IDC_EDIT7)->GetSafeHwnd())// ��ɿ�ʼ����:
				{
					GetDlgItem(IDC_EDIT7)->MoveWindow(m_rcRect3_2);
				}
				if(GetDlgItem(IDC_BUTTON8)->GetSafeHwnd())// ��ɿ�ʼ����:
				{
					GetDlgItem(IDC_BUTTON8)->MoveWindow(m_rcRect3_3);
				}

				if(GetDlgItem(IDC_TASK_INFO_STATIC31)->GetSafeHwnd())//��ɽ�������:
				{
					GetDlgItem(IDC_TASK_INFO_STATIC31)->MoveWindow(m_rcRect4_1);
				}
				if(GetDlgItem(IDC_EDIT8)->GetSafeHwnd())//��ɽ�������:
				{
					GetDlgItem(IDC_EDIT8)->MoveWindow(m_rcRect4_2);
				}
				if(GetDlgItem(IDC_BUTTON9)->GetSafeHwnd())// ��ɽ�������:
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

	pComBo->AddString(_T("��"));
	pComBo->AddString(_T("��"));
	pComBo->AddString(_T("ȫ��"));
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
	GetDlgItem(IDC_EDIT1)->SetWindowText(strText);//������ʼ����:
	strText.Format(_T("%s"), m_TaskSearchInfo.stTaskBaseInfo.szCreateEndTime);
	GetDlgItem(IDC_EDIT2)->SetWindowText(strText);//������������:

	strText.Format(_T("%s"), m_TaskSearchInfo.stTaskBaseInfo.szSendBeginTime);
	GetDlgItem(IDC_SEND_DATE_EDT)->SetWindowText(strText);//�ɹ���ʼ����:
	strText.Format(_T("%s"), m_TaskSearchInfo.stTaskBaseInfo.szSendEndTime);
	GetDlgItem(IDC_EDIT4)->SetWindowText(strText);//�ɹ���������:

	strText.Format(_T("%s"), m_TaskSearchInfo.stTaskBaseInfo.szDownLoadBeginTime);
	GetDlgItem(IDC_EDIT5)->SetWindowText(strText);//ִ�п�ʼ����:
	strText.Format(_T("%s"), m_TaskSearchInfo.stTaskBaseInfo.szDownLoadEndTime);
	GetDlgItem(IDC_EDIT6)->SetWindowText(strText);//ִ�н�������:

	strText.Format(_T("%s"), m_TaskSearchInfo.stTaskBaseInfo.szFinishBeginTime);
	GetDlgItem(IDC_EDIT7)->SetWindowText(strText);// ��ɿ�ʼ����:
	strText.Format(_T("%s"), m_TaskSearchInfo.stTaskBaseInfo.szFinishEndTime);
	GetDlgItem(IDC_EDIT8)->SetWindowText(strText);//��ɽ�������:

	int i = 0;
	CComboBox *pComBox = NULL;
	//�Ƿ����//
	i = m_TaskSearchInfo.stTaskBaseInfo.nArmyTest;
	if(i< Army_Not || i> Army_All)
	{
		i = Army_All;
	}
	pComBox = ((CComboBox *)GetDlgItem(IDC_COMBO2));
	pComBox->SetCurSel(i);

	//����״̬//
	i = m_TaskSearchInfo.stTaskBaseInfo.nTaskStatus;
	if( i< Task_Init || i> Task_All)
	{
		i = Task_All;
	}
	pComBox = ((CComboBox *)GetDlgItem(IDC_COMBO3));
	pComBox->SetCurSel(i);
	/*
	
	if(m_TaskSearchInfo.stTaskBaseInfo.bTaskInit >= 1)//������//
	{
		i = 1;
	}else
	{
		i = 0;
	}
	((CButton *)GetDlgItem(IDC_CHECK1))->SetCheck(i);

	if(m_TaskSearchInfo.stTaskBaseInfo.bTaskOk >= 1)//���ɹ�//
	{
		i = 1;
	}else
	{
		i = 0;
	}
	((CButton *)GetDlgItem(IDC_CHECK2))->SetCheck(i);

	if(m_TaskSearchInfo.stTaskBaseInfo.bTaskRuning >= 1)//ִ����//
	{
		i = 1;
	}else
	{
		i = 0;
	}
	((CButton *)GetDlgItem(IDC_CHECK3))->SetCheck(i);

	if(m_TaskSearchInfo.stTaskBaseInfo.bTaskFinish >= 1)//�����//
	{
		i = 1;
	}else
	{
		i = 0;
	}
	((CButton *)GetDlgItem(IDC_CHECK4))->SetCheck(i);

*/
	//��������
	
	if(m_TaskSearchInfo.stTaskBaseInfo.bTaskTest >= 1)//����//
	{
		i = 1;
	}else
	{
		i = 0;
	}
	((CButton *)GetDlgItem(IDC_CHECK5))->SetCheck(i);

	if(m_TaskSearchInfo.stTaskBaseInfo.bTaskReTest >= 1)//����//
	{
		i = 1;
	}else
	{
		i = 0;
	}
	((CButton *)GetDlgItem(IDC_CHECK6))->SetCheck(i);

	if(m_TaskSearchInfo.stTaskBaseInfo.bTaskHelpReTest >= 1)//��Э����//
	{
		i = 1;
	}else
	{
		i = 0;
	}
	((CButton *)GetDlgItem(IDC_CHECK7))->SetCheck(i);

	//��������//
	int nTaskStatus = m_TaskSearchInfo.stTaskBaseInfo.nTaskStatus;
	if(GetDlgItem(IDC_TASK_INFO_STATIC26)->GetSafeHwnd())
	{

		switch(nTaskStatus)
		{
		case Task_Init:
			{
				GetDlgItem(IDC_TASK_INFO_STATIC26)->ShowWindow(SW_HIDE);//������ʼ����:
				GetDlgItem(IDC_EDIT1)->ShowWindow(SW_HIDE);
				
				GetDlgItem(IDC_TASK_INFO_STATIC28)->ShowWindow(SW_HIDE);//������������:
				GetDlgItem(IDC_EDIT2)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_TASK_INFO_STATIC21)->ShowWindow(SW_HIDE);//�ɹ���ʼ����:
				GetDlgItem(IDC_SEND_DATE_EDT)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_HIDE);
				
				GetDlgItem(IDC_TASK_INFO_STATIC29)->ShowWindow(SW_HIDE);//�ɹ���������:
				GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_TASK_INFO_STATIC22)->ShowWindow(SW_HIDE);//ִ�п�ʼ����:
				GetDlgItem(IDC_EDIT5)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON6)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_TASK_INFO_STATIC30)->ShowWindow(SW_HIDE);//ִ�н�������:
				GetDlgItem(IDC_EDIT6)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON7)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_TASK_INFO_STATIC25)->ShowWindow(SW_HIDE);// ��ɿ�ʼ����:
				GetDlgItem(IDC_EDIT7)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON8)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_TASK_INFO_STATIC31)->ShowWindow(SW_HIDE);//��ɽ�������:
				GetDlgItem(IDC_EDIT8)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON9)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_COMBO3)->ShowWindow(SW_HIDE);//����״̬//

				GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);//������//
				GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);//���ɹ�//
				GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);//ִ����//
				GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);//�����//
				ShowTaskTypeStatus(SW_HIDE);
				GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);////
				GetDlgItem(IDC_CHECK5)->ShowWindow(SW_HIDE);//����//
				GetDlgItem(IDC_CHECK6)->ShowWindow(SW_HIDE);//����//
				GetDlgItem(IDC_CHECK7)->ShowWindow(SW_HIDE);//��Э����//
				PostMessage(WM_SIZE);
			}
			break;
		case Task_OK:
			{
				GetDlgItem(IDC_TASK_INFO_STATIC26)->ShowWindow(SW_HIDE);//������ʼ����:
				GetDlgItem(IDC_EDIT1)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_TASK_INFO_STATIC28)->ShowWindow(SW_HIDE);//������������:
				GetDlgItem(IDC_EDIT2)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_TASK_INFO_STATIC21)->ShowWindow(SW_SHOW);//�ɹ���ʼ����:
				GetDlgItem(IDC_SEND_DATE_EDT)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_TASK_INFO_STATIC29)->ShowWindow(SW_SHOW);//�ɹ���������:
				GetDlgItem(IDC_EDIT4)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_TASK_INFO_STATIC22)->ShowWindow(SW_HIDE);//ִ�п�ʼ����:
				GetDlgItem(IDC_EDIT5)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON6)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_TASK_INFO_STATIC30)->ShowWindow(SW_HIDE);//ִ�н�������:
				GetDlgItem(IDC_EDIT6)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON7)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_TASK_INFO_STATIC25)->ShowWindow(SW_HIDE);// ��ɿ�ʼ����:
				GetDlgItem(IDC_EDIT7)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON8)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_TASK_INFO_STATIC31)->ShowWindow(SW_HIDE);//��ɽ�������:
				GetDlgItem(IDC_EDIT8)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON9)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_COMBO3)->ShowWindow(SW_HIDE);//����״̬//

				GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);//������//
				GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);//���ɹ�//
				GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);//ִ����//
				GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);//�����//
				ShowTaskTypeStatus(SW_HIDE);
				GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);////
				GetDlgItem(IDC_CHECK5)->ShowWindow(SW_HIDE);//����//
				GetDlgItem(IDC_CHECK6)->ShowWindow(SW_HIDE);//����//
				GetDlgItem(IDC_CHECK7)->ShowWindow(SW_HIDE);//��Э����//
				PostMessage(WM_SIZE);
			}
			break;
		case  Task_Runing:
			{
				GetDlgItem(IDC_TASK_INFO_STATIC26)->ShowWindow(SW_HIDE);//������ʼ����:
				GetDlgItem(IDC_EDIT1)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_TASK_INFO_STATIC28)->ShowWindow(SW_HIDE);//������������:
				GetDlgItem(IDC_EDIT2)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_TASK_INFO_STATIC21)->ShowWindow(SW_HIDE);//�ɹ���ʼ����:
				GetDlgItem(IDC_SEND_DATE_EDT)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_TASK_INFO_STATIC29)->ShowWindow(SW_HIDE);//�ɹ���������:
				GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_TASK_INFO_STATIC22)->ShowWindow(SW_SHOW);//ִ�п�ʼ����:
				GetDlgItem(IDC_EDIT5)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BUTTON6)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_TASK_INFO_STATIC30)->ShowWindow(SW_SHOW);//ִ�н�������:
				GetDlgItem(IDC_EDIT6)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BUTTON7)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_TASK_INFO_STATIC25)->ShowWindow(SW_HIDE);// ��ɿ�ʼ����:
				GetDlgItem(IDC_EDIT7)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON8)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_TASK_INFO_STATIC31)->ShowWindow(SW_HIDE);//��ɽ�������:
				GetDlgItem(IDC_EDIT8)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON9)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_COMBO3)->ShowWindow(SW_HIDE);//����״̬//

				GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);//������//
				GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);//���ɹ�//
				GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);//ִ����//
				GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);//�����//
				ShowTaskTypeStatus(SW_HIDE);
				GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);////
				GetDlgItem(IDC_CHECK5)->ShowWindow(SW_HIDE);//����//
				GetDlgItem(IDC_CHECK6)->ShowWindow(SW_HIDE);//����//
				GetDlgItem(IDC_CHECK7)->ShowWindow(SW_HIDE);//��Э����//
				PostMessage(WM_SIZE);
			}
			break;
		case  Task_Finish:
			{
				GetDlgItem(IDC_TASK_INFO_STATIC26)->ShowWindow(SW_HIDE);//������ʼ����:
				GetDlgItem(IDC_EDIT1)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_TASK_INFO_STATIC28)->ShowWindow(SW_HIDE);//������������:
				GetDlgItem(IDC_EDIT2)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_TASK_INFO_STATIC21)->ShowWindow(SW_HIDE);//�ɹ���ʼ����:
				GetDlgItem(IDC_SEND_DATE_EDT)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_TASK_INFO_STATIC29)->ShowWindow(SW_HIDE);//�ɹ���������:
				GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_TASK_INFO_STATIC22)->ShowWindow(SW_SHOW);//ִ�п�ʼ����:
				GetDlgItem(IDC_EDIT5)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BUTTON6)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_TASK_INFO_STATIC30)->ShowWindow(SW_SHOW);//ִ�н�������:
				GetDlgItem(IDC_EDIT6)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BUTTON7)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_TASK_INFO_STATIC25)->ShowWindow(SW_SHOW);// ��ɿ�ʼ����:
				GetDlgItem(IDC_EDIT7)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BUTTON8)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_TASK_INFO_STATIC31)->ShowWindow(SW_SHOW);//��ɽ�������:
				GetDlgItem(IDC_EDIT8)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BUTTON9)->ShowWindow(SW_SHOW);


				GetDlgItem(IDC_COMBO3)->ShowWindow(SW_HIDE);//����״̬//

				GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);//������//
				GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);//���ɹ�//
				GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);//ִ����//
				GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);//�����//
				ShowTaskTypeStatus(SW_HIDE);

				GetDlgItem(IDC_STATIC2)->ShowWindow(TRUE);////
				GetDlgItem(IDC_CHECK5)->ShowWindow(TRUE);//����//
				GetDlgItem(IDC_CHECK6)->ShowWindow(TRUE);//����//
				GetDlgItem(IDC_CHECK7)->ShowWindow(TRUE);//��Э����//

				PostMessage(WM_SIZE);
			}
			break;
		default:
			{
				GetDlgItem(IDC_TASK_INFO_STATIC26)->ShowWindow(SW_HIDE);//������ʼ����:
				GetDlgItem(IDC_EDIT1)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_TASK_INFO_STATIC28)->ShowWindow(SW_HIDE);//������������:
				GetDlgItem(IDC_EDIT2)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_TASK_INFO_STATIC21)->ShowWindow(SW_HIDE);//�ɹ���ʼ����:
				GetDlgItem(IDC_SEND_DATE_EDT)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_TASK_INFO_STATIC29)->ShowWindow(SW_HIDE);//�ɹ���������:
				GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_HIDE);

				GetDlgItem(IDC_TASK_INFO_STATIC22)->ShowWindow(SW_SHOW);//ִ�п�ʼ����:
				GetDlgItem(IDC_EDIT5)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BUTTON6)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_TASK_INFO_STATIC30)->ShowWindow(SW_SHOW);//ִ�н�������:
				GetDlgItem(IDC_EDIT6)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BUTTON7)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_TASK_INFO_STATIC25)->ShowWindow(SW_SHOW);// ��ɿ�ʼ����:
				GetDlgItem(IDC_EDIT7)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BUTTON8)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_TASK_INFO_STATIC31)->ShowWindow(SW_SHOW);//��ɽ�������:
				GetDlgItem(IDC_EDIT8)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BUTTON9)->ShowWindow(SW_SHOW);

				GetDlgItem(IDC_COMBO3)->ShowWindow(SW_SHOW);//����״̬//

				GetDlgItem(IDC_CHECK1)->EnableWindow(TRUE);//������//
				GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);//���ɹ�//
				GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);//ִ����//
				GetDlgItem(IDC_CHECK4)->EnableWindow(TRUE);//�����//
				ShowTaskTypeStatus(SW_SHOW);


				GetDlgItem(IDC_STATIC2)->ShowWindow(TRUE);////
				GetDlgItem(IDC_CHECK5)->ShowWindow(TRUE);//����//
				GetDlgItem(IDC_CHECK6)->ShowWindow(TRUE);//����//
				GetDlgItem(IDC_CHECK7)->ShowWindow(TRUE);//��Э����//

				PostMessage(WM_SIZE);
			}
			break;

		}

	}
	
}
void CTaskSearch::ShowTaskTypeStatus(int nShowHide)
{
	GetDlgItem(IDC_STATIC1)->ShowWindow(nShowHide);////
	GetDlgItem(IDC_CHECK1)->ShowWindow(nShowHide);//������//
	GetDlgItem(IDC_CHECK2)->ShowWindow(nShowHide);//���ɹ�//
	GetDlgItem(IDC_CHECK3)->ShowWindow(nShowHide);//ִ����//
	GetDlgItem(IDC_CHECK4)->ShowWindow(nShowHide);//�����//

	
}
void CTaskSearch::GetSearchInfo()
{
	
	CString strText;
	//strText.Format(_T("%s"), m_TaskSearchInfo.stTaskBaseInfo.szTaskName);

	//1_1 ��������
	GetDlgItem(IDC_TASK_NAME_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(m_TaskSearchInfo.stTaskBaseInfo.szTaskName, 0, sizeof(m_TaskSearchInfo.stTaskBaseInfo.szTaskName));
	strcpy(m_TaskSearchInfo.stTaskBaseInfo.szTaskName, strText);

	//1_2 ��Ʒ����
	GetDlgItem(IDC_PRODUCT_NO_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(m_TaskSearchInfo.stProductInfo.szProductNo, 0, sizeof(m_TaskSearchInfo.stProductInfo.szProductNo));
	strcpy(m_TaskSearchInfo.stProductInfo.szProductNo, strText);

	//1_3 ���κ�
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


	//2_1 �ͺ�����
	GetDlgItem(IDC_MODEL_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(m_TaskSearchInfo.stTaskBaseInfo.szModel, 0, sizeof(m_TaskSearchInfo.stTaskBaseInfo.szModel));
	strcpy(m_TaskSearchInfo.stTaskBaseInfo.szModel, strText);

	//2_2 �׶�
	GetDlgItem(IDC_PHASE_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(m_TaskSearchInfo.stTaskBaseInfo.szPhase, 0, sizeof(m_TaskSearchInfo.stTaskBaseInfo.szPhase));
	strcpy(m_TaskSearchInfo.stTaskBaseInfo.szPhase, strText);

	//2_3 ���첿��
	GetDlgItem(IDC_UP_DEPART_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(m_TaskSearchInfo.stHrUpDepart.szUpDepartName, 0, sizeof(m_TaskSearchInfo.stHrUpDepart.szUpDepartName));
	strcpy(m_TaskSearchInfo.stHrUpDepart.szUpDepartName, strText);

	//3_1 �����鳤
	GetDlgItem(IDC_LEADER_EDT)->GetWindowText(strText);
	memset(m_TaskSearchInfo.stTaskBaseInfo.szCheckLeader, 0, sizeof(m_TaskSearchInfo.stTaskBaseInfo.szCheckLeader));
	strcpy(m_TaskSearchInfo.stTaskBaseInfo.szCheckLeader, strText);

	//3_2 ����Ա
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

	GetDlgItem(IDC_EDIT1)->GetWindowText(strText);//������ʼ����:
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(m_TaskSearchInfo.stTaskBaseInfo.szCreateBeginTime, 0, sizeof(m_TaskSearchInfo.stTaskBaseInfo.szCreateBeginTime));
	strcpy(m_TaskSearchInfo.stTaskBaseInfo.szCreateBeginTime, strText);

	GetDlgItem(IDC_EDIT2)->GetWindowText(strText);//������������:
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(m_TaskSearchInfo.stTaskBaseInfo.szCreateEndTime, 0, sizeof(m_TaskSearchInfo.stTaskBaseInfo.szCreateEndTime));
	strcpy(m_TaskSearchInfo.stTaskBaseInfo.szCreateEndTime, strText);

	GetDlgItem(IDC_SEND_DATE_EDT)->GetWindowText(strText);//�ɹ���ʼ����:
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(m_TaskSearchInfo.stTaskBaseInfo.szSendBeginTime, 0, sizeof(m_TaskSearchInfo.stTaskBaseInfo.szSendBeginTime));
	strcpy(m_TaskSearchInfo.stTaskBaseInfo.szSendBeginTime, strText);

	GetDlgItem(IDC_EDIT4)->GetWindowText(strText);//�ɹ���������:
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(m_TaskSearchInfo.stTaskBaseInfo.szSendEndTime, 0, sizeof(m_TaskSearchInfo.stTaskBaseInfo.szSendEndTime));
	strcpy(m_TaskSearchInfo.stTaskBaseInfo.szSendEndTime, strText);

	GetDlgItem(IDC_EDIT5)->GetWindowText(strText);//ִ�п�ʼ����:
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(m_TaskSearchInfo.stTaskBaseInfo.szDownLoadBeginTime, 0, sizeof(m_TaskSearchInfo.stTaskBaseInfo.szDownLoadBeginTime));
	strcpy(m_TaskSearchInfo.stTaskBaseInfo.szDownLoadBeginTime, strText);

	GetDlgItem(IDC_EDIT6)->GetWindowText(strText);//ִ�н�������:
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(m_TaskSearchInfo.stTaskBaseInfo.szDownLoadEndTime, 0, sizeof(m_TaskSearchInfo.stTaskBaseInfo.szDownLoadEndTime));
	strcpy(m_TaskSearchInfo.stTaskBaseInfo.szDownLoadEndTime, strText);

	strText.Format(_T("%s"), m_TaskSearchInfo.stTaskBaseInfo.szFinishBeginTime);
	GetDlgItem(IDC_EDIT7)->GetWindowText(strText);// ��ɿ�ʼ����:
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(m_TaskSearchInfo.stTaskBaseInfo.szFinishBeginTime, 0, sizeof(m_TaskSearchInfo.stTaskBaseInfo.szFinishBeginTime));
	strcpy(m_TaskSearchInfo.stTaskBaseInfo.szFinishBeginTime, strText);

	GetDlgItem(IDC_EDIT8)->GetWindowText(strText);//��ɽ�������:
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(m_TaskSearchInfo.stTaskBaseInfo.szFinishEndTime, 0, sizeof(m_TaskSearchInfo.stTaskBaseInfo.szFinishEndTime));
	strcpy(m_TaskSearchInfo.stTaskBaseInfo.szFinishEndTime, strText);

	int i = 0;
	CComboBox *pComBox = NULL;
	//�Ƿ����//
	pComBox = ((CComboBox *)GetDlgItem(IDC_COMBO2));
	i = pComBox->GetCurSel();
	if(i< Army_Not || i> Army_All)
	{
		i = Army_All;
	}
	m_TaskSearchInfo.stTaskBaseInfo.nArmyTest = i;


	//����״̬//


	/*
	//������
	i = ((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck();
	m_TaskSearchInfo.stTaskBaseInfo.bTaskInit = i;

	//���ɹ�//
	i = ((CButton *)GetDlgItem(IDC_CHECK2))->GetCheck();
	m_TaskSearchInfo.stTaskBaseInfo.bTaskOk = i;

	//ִ����//
	i = ((CButton *)GetDlgItem(IDC_CHECK3))->GetCheck();
	m_TaskSearchInfo.stTaskBaseInfo.bTaskRuning = i;

	//�����//
	i = ((CButton *)GetDlgItem(IDC_CHECK4))->GetCheck();
	m_TaskSearchInfo.stTaskBaseInfo.bTaskFinish = i;
*/
	//2017-03-10��
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

	//��������
	//����//
	i = ((CButton *)GetDlgItem(IDC_CHECK5))->GetCheck();
	m_TaskSearchInfo.stTaskBaseInfo.bTaskTest = i;

	//����//
	i = ((CButton *)GetDlgItem(IDC_CHECK6))->GetCheck();
	m_TaskSearchInfo.stTaskBaseInfo.bTaskReTest = i;

	//��Э����//
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


int CTaskSearch::CheckSearchTime( )                    //����ѯʱ���Ƿ�Ϸ�
{

	char     *pBegTime, *pEndTime;
	int      bFlag = 1;
	


	//1.�ɹ�
	//------------------------------------------------------------------------
	pBegTime = m_TaskSearchInfo.stTaskBaseInfo.szSendBeginTime;	//�ɹ���ʼ����:
	pEndTime = m_TaskSearchInfo.stTaskBaseInfo.szSendEndTime;	//�ɹ���������:

	bFlag = CheckDateBegSmallEnd(pBegTime, pEndTime);
	if (bFlag == 0)
	{
		AfxMessageBox("Err,�ɹ���ʼʱ����ڽ���ʱ��!");
		return 0;
	}


	//2.ִ��
	//------------------------------------------------------------------------
	pBegTime = m_TaskSearchInfo.stTaskBaseInfo.szDownLoadBeginTime;	//ִ�п�ʼ����:
	pEndTime = m_TaskSearchInfo.stTaskBaseInfo.szDownLoadEndTime;	//ִ�н�������:

	bFlag = CheckDateBegSmallEnd(pBegTime, pEndTime);
	if (bFlag == 0)
	{
		AfxMessageBox("Err,ִ�п�ʼʱ����ڽ���ʱ��!");
		return 0;
	}

	//3.���
	//------------------------------------------------------------------------
	pBegTime = m_TaskSearchInfo.stTaskBaseInfo.szFinishBeginTime;	//ִ�п�ʼ����:
	pEndTime = m_TaskSearchInfo.stTaskBaseInfo.szFinishEndTime;		//ִ�н�������:

	bFlag = CheckDateBegSmallEnd(pBegTime, pEndTime);
	if (bFlag == 0)
	{
		AfxMessageBox("Err,��ɿ�ʼʱ����ڽ���ʱ��!");
		return 0;
	}

	return 1;
}

void CTaskSearch::OnBnClickedTaskSearchBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetSearchInfo();

	int  bFlag = 0;
	bFlag = CheckSearchTime();		//���ʱ���Ƿ�Ϸ�
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

//ѡ������鳤//
void CTaskSearch::OnBnClickedButton2()
{  
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSelUserDlg Dlg;
	CString strUserName;
	if(Dlg.DoModal() == IDOK)
	{
		strUserName = Dlg.m_SelUserName;
		GetDlgItem(IDC_LEADER_EDT)->SetWindowText(strUserName);
	}

}
//ѡ�����Ա//
void CTaskSearch::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSelUserDlg Dlg;
	CString strUserName;
	if(Dlg.DoModal() == IDOK)
	{
		strUserName = Dlg.m_SelUserName;
		GetDlgItem(IDC_CHECK_USER_EDT)->SetWindowText(strUserName);
	}
}
//ѡ�񽻼첿��//
void CTaskSearch::OnBnClickedSelUpDepartBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strUpDepartName;
	CSelUpDepartDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		strUpDepartName = dlg.m_UpDepartName;
		GetDlgItem(IDC_UP_DEPART_EDT)->SetWindowText(strUpDepartName);
	}
}
//ѡ���Ʒ����//
void CTaskSearch::OnBnClickedSelProdnoBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSelProductDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		GetDlgItem(IDC_PRODUCT_NO_EDT)->SetWindowText(dlg.m_strProductNo);
	}
}

//ѡ���ɹ���ʼʱ��//
void CTaskSearch::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
//ѡ���ɹ�����ʱ��//
void CTaskSearch::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

//ѡ��ִ�п�ʼʱ��//
void CTaskSearch::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
//ѡ��ִ�н���ʱ��//
void CTaskSearch::OnBnClickedButton7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
//ѡ����ɿ�ʼʱ��//
void CTaskSearch::OnBnClickedButton8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
//ѡ����ɽ���ʱ��//
void CTaskSearch::OnBnClickedButton9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
