// ResetUsrPwd.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "ResetUsrPwd.h"

#include "SysLogin.h"
#include "MainFrm.h"
// CResetUsrPwd 对话框

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


// CResetUsrPwd 消息处理程序

BOOL CResetUsrPwd::OnInitDialog()
{
	CDialog::OnInitDialog();

	//GetDlgItem(IDC_RESETPWD_NAME_EDT)->EnableWindow(FALSE);
	((CEdit*)GetDlgItem(IDC_RESETPWD_NAME_EDT))->SetReadOnly(TRUE);

	GetDlgItem(IDC_RESETPWD_NAME_EDT)->SetWindowText(g_LoginUsrInfo.szLoginName);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CResetUsrPwd::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类


	CString strEditPwd,strEditPwd1,strEditPwd2;
	GetDlgItem(IDC_RESETPWD_PWD_EDT)->GetWindowText(strEditPwd);
	GetDlgItem(IDC_RESETPWD_PWD1_EDT)->GetWindowText(strEditPwd1);
	GetDlgItem(IDC_RESETPWD_PWD2_EDT)->GetWindowText(strEditPwd2);

	if(strEditPwd.Trim().IsEmpty() || strEditPwd1.Trim().IsEmpty() ||strEditPwd2.Trim().IsEmpty())
	{
		AfxMessageBox(_T("密码不能为空"));
		return;
	}
	if(strEditPwd1 != strEditPwd2)
	{
		AfxMessageBox(_T("两次密码不一致!"));
		return;
	}

	if(strlen(strEditPwd2)>20)
	{
		CString strText;
		strText.Format("密码超过最大长度，请输入1-20个字母数字等符号!");
		AfxMessageBox(strText);
		return;
	}
	if(g_LoginUsrInfo.szUserPwd == strEditPwd)
	{

		if(!m_DMng.ReSetUsrPwd(strEditPwd1.GetBuffer(0),g_LoginUsrInfo.szLoginName))
		{
			AfxMessageBox("修改密码失败!");
			return ;
		}
		MessageBox(_T("密码已更改!请重新登录"),_T("提示"),MB_OK);
		CDialog::OnOK();
		CSysLogin nDlg;
		if(nDlg.DoModal() != IDOK)
		{
			g_MainFram->Exit();
		}
	}else
	{
		AfxMessageBox(_T("密码不正确!"));
		return;
	}
}
