// DlgMdLoadIn.cpp : implementation file
//

#include "stdafx.h"
#include "DlgMdLoadIn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMdLoadIn dialog

CDlgMdLoadIn::CDlgMdLoadIn(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMdLoadIn::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMdLoadIn)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgMdLoadIn::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMdLoadIn)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMdLoadIn, CDialog)
	//{{AFX_MSG_MAP(CDlgMdLoadIn)
	ON_BN_CLICKED(IDC_BTN_PATH, OnBtnPath)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMdLoadIn message handlers

BOOL CDlgMdLoadIn::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	if (m_nType == 1)
	{
		this->SetWindowText("导入");
		GetDlgItem(IDC_BTN_PATH)->SetWindowText("Open...");
	}
	else if (m_nType == 2)
	{
		this->SetWindowText("导出");
		GetDlgItem(IDC_BTN_PATH)->SetWindowText("Save...");
	}
	else if (m_nType == 3)
	{
		this->SetWindowText("添加附件");
		GetDlgItem(IDC_BTN_PATH)->SetWindowText("Open...");
	}

	
	GetDlgItem(IDC_LOADXLS_PATH_EDT)->SetWindowText(m_strPath);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMdLoadIn::OnBtnPath() 
{
	// TODO: Add your control notification handler code here
	CFileDialog *lpszOpenFile;    //定义一个CfileDialog对象
	
	/*
	if (m_IsOpen != 0)
	{
		lpszOpenFile = new CFileDialog(TRUE,"","",OFN_FILEMUSTEXIST |OFN_HIDEREADONLY , "文件类型(*.xls;*.xlsx)|*.xls;*.xlsx||");//生成一个对话框
	}
	else
	{
		lpszOpenFile = new CFileDialog(FALSE,"","",OFN_FILEMUSTEXIST |OFN_HIDEREADONLY , "文件类型(*.xlsx;*.xls)|*.xlsx;*.xls||");//生成一个对话框
	}
	*/
	if (m_nType == 1)
	{
		lpszOpenFile = new CFileDialog(TRUE,"","",OFN_FILEMUSTEXIST |OFN_HIDEREADONLY , "文件类型(*.xls;*.xlsx)|*.xls;*.xlsx||");//生成一个对话框
	}
	else if (m_nType == 2)
	{
		lpszOpenFile = new CFileDialog(FALSE,"","",OFN_FILEMUSTEXIST |OFN_HIDEREADONLY , "文件类型(*.xlsx;*.xls)|*.xlsx;*.xls||");//生成一个对话框
	}
	else if (m_nType == 3)
	{
		lpszOpenFile = new CFileDialog(TRUE,"","",OFN_FILEMUSTEXIST |OFN_HIDEREADONLY , "文件类型(*.*)|*.*||");//生成一个对话框
	}
	
	
	if(lpszOpenFile->DoModal() == IDOK)//假如点击对话框确定按钮
	{
		CString	szGetName;
		szGetName = lpszOpenFile->GetPathName();	//得到打开文件的路径
		//SetWindowText(szGetName);					//在窗口标题上显示路径	
		GetDlgItem(IDC_LOADXLS_PATH_EDT)->SetWindowText(szGetName);
	}
	
	delete lpszOpenFile;	//释放分配的对话框
}

void CDlgMdLoadIn::OnOK() 
{
	// TODO: Add extra validation here

	CString str;
	GetDlgItem(IDC_LOADXLS_PATH_EDT)->GetWindowText(str);
	if (strlen(str.GetBuffer(0)) == 0)
	{
		AfxMessageBox(_T("文件名不能为空!"));
		return;
	}
	
	CDialog::OnOK();
}

void CDlgMdLoadIn::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	GetDlgItem(IDC_LOADXLS_PATH_EDT)->GetWindowText(m_strPath);
}
