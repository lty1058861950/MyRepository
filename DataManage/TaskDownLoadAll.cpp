// TaskDownLoadAll.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "TaskDownLoadAll.h"


// CTaskDownLoadAll 对话框

IMPLEMENT_DYNAMIC(CTaskDownLoadAll, CDialog)

CTaskDownLoadAll::CTaskDownLoadAll(CWnd* pParent /*=NULL*/)
	: CDialog(CTaskDownLoadAll::IDD, pParent)
{

}

CTaskDownLoadAll::~CTaskDownLoadAll()
{
}

void CTaskDownLoadAll::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_TaskDownLoadList);
}


BEGIN_MESSAGE_MAP(CTaskDownLoadAll, CDialog)
	ON_WM_SIZE()
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CTaskDownLoadAll::OnNMClickList1)
END_MESSAGE_MAP()


// CTaskDownLoadAll 消息处理程序

BOOL CTaskDownLoadAll::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CString strText;
	int nPadID = g_LoginUsrInfo.nPadDevID;
	CString strUserName = g_LoginUsrInfo.szUserName;
	strText.Format(_T("检验员姓名: %s    PAD设备号: %d "), strUserName, nPadID);
	GetDlgItem(IDC_STATIC4)->SetWindowText(strText);
	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CTaskDownLoadAll::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnOK();
}

void CTaskDownLoadAll::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	AutoSize();
}

void CTaskDownLoadAll::AutoSize()
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

	if(GetDlgItem(IDC_STATIC4)->GetSafeHwnd())
	{
		GetDlgItem(IDC_STATIC4)->MoveWindow(2,5+20,Rect.Width()-(2*2),20);
	}
	if(m_TaskDownLoadList.GetSafeHwnd())
	{
		m_TaskDownLoadList.MoveWindow(3,5+20+20+5,Rect.Width()-(3*2),
			Rect.Height()-(5+20+10+20+5));
	}

}
void CTaskDownLoadAll::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

