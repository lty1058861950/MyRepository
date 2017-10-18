// ResetUsrPwd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataManage.h"
#include "ResetUsrPwd.h"

#include "SysLogin.h"
#include "MainFrm.h"
// CResetUsrPwd �Ի���

IMPLEMENT_DYNAMIC(CResetUsrPwd, CDialog)

CResetUsrPwd::CResetUsrPwd(CWnd* pParent /*=NULL*/)
	: CDialog(CResetUsrPwd::IDD, pParent)
{

}

CResetUsrPwd::~CResetUsrPwd()
{
}

void CResetUsrPwd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CResetUsrPwd, CDialog)
END_MESSAGE_MAP()


// CResetUsrPwd ��Ϣ�������

BOOL CResetUsrPwd::OnInitDialog()
{
	CDialog::OnInitDialog();

	//GetDlgItem(IDC_RESETPWD_NAME_EDT)->EnableWindow(FALSE);
	((CEdit*)GetDlgItem(IDC_RESETPWD_NAME_EDT))->SetReadOnly(TRUE);

	GetDlgItem(IDC_RESETPWD_NAME_EDT)->SetWindowText(g_LoginUsrInfo.szLoginName);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CResetUsrPwd::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���


	CString strEditPwd,strEditPwd1,strEditPwd2;
	GetDlgItem(IDC_RESETPWD_PWD_EDT)->GetWindowText(strEditPwd);
	GetDlgItem(IDC_RESETPWD_PWD1_EDT)->GetWindowText(strEditPwd1);
	GetDlgItem(IDC_RESETPWD_PWD2_EDT)->GetWindowText(strEditPwd2);

	if(strEditPwd.Trim().IsEmpty() || strEditPwd1.Trim().IsEmpty() ||strEditPwd2.Trim().IsEmpty())
	{
		AfxMessageBox(_T("���벻��Ϊ��"));
		return;
	}
	if(strEditPwd1 != strEditPwd2)
	{
		AfxMessageBox(_T("�������벻һ��!"));
		return;
	}

	if(strlen(strEditPwd2)>20)
	{
		CString strText;
		strText.Format("���볬����󳤶ȣ�������1-20����ĸ���ֵȷ���!");
		AfxMessageBox(strText);
		return;
	}
	if(g_LoginUsrInfo.szUserPwd == strEditPwd)
	{

		if(!m_DMng.ReSetUsrPwd(strEditPwd1.GetBuffer(0),g_LoginUsrInfo.szLoginName))
		{
			AfxMessageBox("�޸�����ʧ��!");
			return ;
		}
		MessageBox(_T("�����Ѹ���!�����µ�¼"),_T("��ʾ"),MB_OK);
		CDialog::OnOK();
		CSysLogin nDlg;
		if(nDlg.DoModal() != IDOK)
		{
			g_MainFram->Exit();
		}
	}else
	{
		AfxMessageBox(_T("���벻��ȷ!"));
		return;
	}
}
