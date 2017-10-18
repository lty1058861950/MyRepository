// TaskMng.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "TaskMng.h"

#include "LoadTaskInfo.h"
#include "LoadMesTask.h"
#include "MainFrm.h"

// CTaskMng 对话框
IMPLEMENT_DYNAMIC(CTaskMng, CDialog)

CTaskMng::CTaskMng(CWnd* pParent /*=NULL*/)
	: CDialog(CTaskMng::IDD, pParent)
{
	m_ShowType = View_Task;
	m_ShowTaskInfo.m_CurTaskInfo.Release();
}

CTaskMng::~CTaskMng()
{
}

void CTaskMng::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTaskMng, CDialog)
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


// CTaskMng 消息处理程序

BOOL CTaskMng::OnInitDialog()
{
	CDialog::OnInitDialog();


	m_ShowTaskInfo.m_ShowTaskData.m_pModeParMng = &g_MainFram->m_ModeParMng;
	m_ShowTaskInfo.m_ShowTaskData.m_pModeXmlAnalysis = &g_MainFram->m_ModeXmlAnalysis;

	m_ShowTaskInfo.m_ShowType = m_ShowType;
	m_ShowTaskInfo.Create(IDD_SHOWTASKINFO_DLG,this);
	m_ShowTaskInfo.ShowWindow(SW_SHOW);
	m_ShowTaskInfo.DisplayTaskInfo();

	CString strText;
	CString strTaskName = m_ShowTaskInfo.m_CurTaskInfo.stTaskBaseInfo.szTaskName;
	switch(m_ShowType)
	{
	case Add_NewTask:
		{
			this->SetWindowText(_T("添加一项任务"));
			
		}
		break;
	case Modify_Task:
		{
			strText.Format(_T("正在修改任务(任务名称=%s)"),strTaskName);
			this->SetWindowText(strText);
			//1.产品代号不可选
			((CEdit *)m_ShowTaskInfo.GetDlgItem(IDC_PRODUCTNO_EDT))->SetReadOnly(TRUE);
			((CEdit *)m_ShowTaskInfo.GetDlgItem(IDC_PRODNAME_EDT))->SetReadOnly(TRUE);
			(m_ShowTaskInfo.GetDlgItem(IDC_SEL_PRODUCTNO_BTN))->EnableWindow(FALSE);
			
		}
		break;
	case View_Task:
		{
			strText.Format(_T("任务名称=%s"), strTaskName);
			this->SetWindowText(strText);

			//1.产品代号不可选
			((CEdit *)m_ShowTaskInfo.GetDlgItem(IDC_PRODUCTNO_EDT))->SetReadOnly(TRUE);
			((CEdit *)m_ShowTaskInfo.GetDlgItem(IDC_PRODNAME_EDT))->SetReadOnly(TRUE);
			(m_ShowTaskInfo.GetDlgItem(IDC_SEL_PRODUCTNO_BTN))->EnableWindow(FALSE);
			m_ShowTaskInfo.GetDlgItem(IDC_SEL_UPDEPART_BTN)->EnableWindow(FALSE);
			m_ShowTaskInfo.GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
			m_ShowTaskInfo.GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);


			m_ShowTaskInfo.m_TaskCfg.GetDlgItem(IDC_NUMBELMNG_BTN)->EnableWindow(FALSE);
			m_ShowTaskInfo.m_TaskCfg.GetDlgItem(IDC_TASKMODEMNG_BTN)->EnableWindow(FALSE);
			m_ShowTaskInfo.m_TaskCfg.GetDlgItem(IDC_TASKPICNUM_BTN)->EnableWindow(FALSE);
			//m_ShowTaskInfo.GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
		}
		break;
	}

	//MoveWindow(0,0,1366,768);
	MoveWindow(0,0,1280,700);
	CenterWindow();
	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

//删除某个节点下的所有子节点///
void CTaskMng::DelTreeChildItem(CTreeCtrl *pTree,HTREEITEM hItem)
{
	if(!hItem)
		return;
	HTREEITEM hChildItem = NULL;
	while((hChildItem = pTree->GetChildItem(hItem)) != NULL)
	{
		pTree->DeleteItem(hChildItem);
	}
}
void CTaskMng::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	AutoSize();
	
}

void CTaskMng::AutoSize()
{
	CRect Rect ;
	GetClientRect(&Rect) ;

	if (m_ShowTaskInfo.GetSafeHwnd())
	{
		m_ShowTaskInfo.MoveWindow(1,1,Rect.Width()-(1*2),Rect.Height()-(1*2));
	}

}

void CTaskMng::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnOK();
}

void CTaskMng::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnCancel();
}
