// ModeMng.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "ModeMng.h"
#include "MainFrm.h"
// CModeMng 对话框

IMPLEMENT_DYNAMIC(CModeMng, CDialog)

CModeMng::CModeMng(CWnd* pParent /*=NULL*/)
	: CDialog(CModeMng::IDD, pParent)
{
	m_ShowType = View_Mode;
}

CModeMng::~CModeMng()
{
	
}

void CModeMng::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModeMng, CDialog)
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


// CModeMng 消息处理程序

BOOL CModeMng::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ShowModeInfo.m_ShowModeStyle.m_pModeParMng = &g_MainFram->m_ModeParMng;
	m_ShowModeInfo.m_ShowModeStyle.m_pExcelOptFun = &g_MainFram->m_ExcelOptFun;
	m_ShowModeInfo.m_ShowModeStyle.m_pModeXmlAnalysis = &g_MainFram->m_ModeXmlAnalysis;

	m_ShowModeInfo.m_ShowType = m_ShowType;
	m_ShowModeInfo.Create(IDD_SHOWMODEINFO_DLG,this);
	m_ShowModeInfo.ShowWindow(SW_SHOW);
	m_ShowModeInfo.DisPalyModeInfo();
	
	CString strText;
	switch(m_ShowType)
	{
	case Add_NewMode:
		{
			this->SetWindowText(_T("添加一个模板"));
			m_ShowModeInfo.GetDlgItem(IDOK)->SetWindowText(_T("确定"));
			m_ShowModeInfo.GetDlgItem(IDCANCEL)->SetWindowText(_T("取消"));
		}
		break;
	case Modify_Mode:
		{
			strText.Format(_T("正在修改模板(模板名称=%s)"),m_ShowModeInfo.m_CurModeInfo.szModeName);
			this->SetWindowText(strText);
			m_ShowModeInfo.GetDlgItem(IDOK)->SetWindowText(_T("保存"));
			m_ShowModeInfo.GetDlgItem(IDCANCEL)->SetWindowText(_T("取消"));
		}
		break;
	case View_Mode:
		{
			strText.Format(_T("模板名称=%s"), m_ShowModeInfo.m_CurModeInfo.szModeName);
			this->SetWindowText(strText);
			m_ShowModeInfo.GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
			m_ShowModeInfo.GetDlgItem(IDCANCEL)->SetWindowText(_T("退出"));
		}
		break;
	}


	MoveWindow(0,0,774,500);
	CenterWindow();

	PostMessage(WM_SIZE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CModeMng::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	AutoSize();

	// TODO: 在此处添加消息处理程序代码
}

void CModeMng::AutoSize()
{
	CRect Rect ;
	GetClientRect(&Rect) ;

	int nBtnWidth = 80;
	int nBtnHeight = 30;
	
	if (m_ShowModeInfo.GetSafeHwnd())
	{
		m_ShowModeInfo.MoveWindow(0,0,Rect.Width(),Rect.Height());
	}
}


void CModeMng::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnOK();
}

void CModeMng::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnCancel();
}
