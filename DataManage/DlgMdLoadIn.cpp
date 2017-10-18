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
		this->SetWindowText("����");
		GetDlgItem(IDC_BTN_PATH)->SetWindowText("Open...");
	}
	else if (m_nType == 2)
	{
		this->SetWindowText("����");
		GetDlgItem(IDC_BTN_PATH)->SetWindowText("Save...");
	}
	else if (m_nType == 3)
	{
		this->SetWindowText("��Ӹ���");
		GetDlgItem(IDC_BTN_PATH)->SetWindowText("Open...");
	}

	
	GetDlgItem(IDC_LOADXLS_PATH_EDT)->SetWindowText(m_strPath);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMdLoadIn::OnBtnPath() 
{
	// TODO: Add your control notification handler code here
	CFileDialog *lpszOpenFile;    //����һ��CfileDialog����
	
	/*
	if (m_IsOpen != 0)
	{
		lpszOpenFile = new CFileDialog(TRUE,"","",OFN_FILEMUSTEXIST |OFN_HIDEREADONLY , "�ļ�����(*.xls;*.xlsx)|*.xls;*.xlsx||");//����һ���Ի���
	}
	else
	{
		lpszOpenFile = new CFileDialog(FALSE,"","",OFN_FILEMUSTEXIST |OFN_HIDEREADONLY , "�ļ�����(*.xlsx;*.xls)|*.xlsx;*.xls||");//����һ���Ի���
	}
	*/
	if (m_nType == 1)
	{
		lpszOpenFile = new CFileDialog(TRUE,"","",OFN_FILEMUSTEXIST |OFN_HIDEREADONLY , "�ļ�����(*.xls;*.xlsx)|*.xls;*.xlsx||");//����һ���Ի���
	}
	else if (m_nType == 2)
	{
		lpszOpenFile = new CFileDialog(FALSE,"","",OFN_FILEMUSTEXIST |OFN_HIDEREADONLY , "�ļ�����(*.xlsx;*.xls)|*.xlsx;*.xls||");//����һ���Ի���
	}
	else if (m_nType == 3)
	{
		lpszOpenFile = new CFileDialog(TRUE,"","",OFN_FILEMUSTEXIST |OFN_HIDEREADONLY , "�ļ�����(*.*)|*.*||");//����һ���Ի���
	}
	
	
	if(lpszOpenFile->DoModal() == IDOK)//�������Ի���ȷ����ť
	{
		CString	szGetName;
		szGetName = lpszOpenFile->GetPathName();	//�õ����ļ���·��
		//SetWindowText(szGetName);					//�ڴ��ڱ�������ʾ·��	
		GetDlgItem(IDC_LOADXLS_PATH_EDT)->SetWindowText(szGetName);
	}
	
	delete lpszOpenFile;	//�ͷŷ���ĶԻ���
}

void CDlgMdLoadIn::OnOK() 
{
	// TODO: Add extra validation here

	CString str;
	GetDlgItem(IDC_LOADXLS_PATH_EDT)->GetWindowText(str);
	if (strlen(str.GetBuffer(0)) == 0)
	{
		AfxMessageBox(_T("�ļ�������Ϊ��!"));
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
