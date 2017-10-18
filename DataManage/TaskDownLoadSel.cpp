// TaskDownSel.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "TaskDownLoadSel.h"


// CTaskDownSel 对话框

IMPLEMENT_DYNAMIC(CTaskDownLoadSel, CDialog)

CTaskDownLoadSel::CTaskDownLoadSel(CWnd* pParent /*=NULL*/)
	: CDialog(CTaskDownLoadSel::IDD, pParent)
{

}

CTaskDownLoadSel::~CTaskDownLoadSel()
{
}

void CTaskDownLoadSel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_TaskDownLoadSelList);
}


BEGIN_MESSAGE_MAP(CTaskDownLoadSel, CDialog)
	ON_WM_SIZE()
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CTaskDownLoadSel::OnNMClickList1)
END_MESSAGE_MAP()


// CTaskDownSel 消息处理程序

BOOL CTaskDownLoadSel::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CTaskDownLoadSel::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnOK();
}

void CTaskDownLoadSel::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	AutoSize();
}

void CTaskDownLoadSel::AutoSize()
{
	CRect Rect ;
	GetClientRect(&Rect);

	int nBtnWidth = 60;
	int nBtnHeight = 25;


	//产品模块//
	if(GetDlgItem(IDC_STATIC1)->GetSafeHwnd())
	{
		GetDlgItem(IDC_STATIC1)->MoveWindow(0,5,Rect.Width()-(0*2),Rect.Height()-(5*2));
	}

	if(m_TaskDownLoadSelList.GetSafeHwnd())
	{
		m_TaskDownLoadSelList.MoveWindow(3,5+20,Rect.Width()-(3*2),
			Rect.Height()-((5+20+10)));
	}

}


void CTaskDownLoadSel::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
