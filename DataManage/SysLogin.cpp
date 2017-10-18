// SysLogin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataManage.h"
#include "SysLogin.h"


// CSysLogin �Ի���

IMPLEMENT_DYNAMIC(CSysLogin, CDialog)

CSysLogin::CSysLogin(CWnd* pParent /*=NULL*/)
	: CDialog(CSysLogin::IDD, pParent)
{

}

CSysLogin::~CSysLogin()
{
}

void CSysLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSysLogin, CDialog)
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CSysLogin ��Ϣ�������

BOOL CSysLogin::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_DMng.InitRoleTab();
	m_DMng.GetAllRole(&g_AllRoles);
	m_DMng.InitGroupTab();

	m_DMng.InitUserTab();

	LoadDefUserLogin();

	GetDlgItem(IDC_LOGUSERNAME_EDT)->SetWindowText(szDefUserName);
	GetDlgItem(IDC_LOGPASSWORD_EDT)->SetWindowText("123456");

	m_btn1.SubclassDlgItem(IDOK, this);
	m_btn1.DrawTransparent(TRUE);
	m_btn1.SetWindowText(_T(""));
	m_btn2.SubclassDlgItem(IDCANCEL, this);
	m_btn2.DrawTransparent(TRUE);
	m_btn2.SetWindowText(_T(""));




	m_fontMark1.CreateFont(TEXT_SIZE_MODE,0,0,0,200,0,0,0,134,3,2,1,2,_T("Arial"));			//��ͨ

	GetDlgItem(IDC_LOGUSERNAME_EDT)->SetFont(&m_fontMark1);
	GetDlgItem(IDC_LOGPASSWORD_EDT)->SetFont(&m_fontMark1);
	this->MoveWindow(0,0,1280,700);
	this->CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CSysLogin::LoadDefUserLogin()
{
	CString nFileName ;
	nFileName.Format("%s\\%s",g_WorkPath,USRMNG_USRCFG_FILENAME) ;
	//�����ϴε�¼���û�//
	memset(szDefUserName,0,50);
	GetPrivateProfileString("Def_HisUser","UserName","admin",szDefUserName,50,nFileName);
	WritePrivateProfileString("Def_HisUser","UserName", szDefUserName, nFileName);
}
void CSysLogin::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	if(LoginCheck())
	{
		CDialog::OnOK();
	}else
	{
		//CDialog::OnCancel();

	}
}

BOOL CSysLogin::LoginCheck()
{
	CString strLogName;
	CString strLogPwd;

	CString nFileName ;
	nFileName.Format("%s\\%s",g_WorkPath,USRMNG_USRCFG_FILENAME) ;

	GetDlgItem(IDC_LOGUSERNAME_EDT)->GetWindowText(strLogName);
	GetDlgItem(IDC_LOGPASSWORD_EDT)->GetWindowText(strLogPwd);

	strLogName = strLogName.TrimLeft();
	strLogName = strLogName.TrimRight();

	
	strLogPwd = strLogPwd.TrimLeft();
	strLogPwd = strLogPwd.TrimRight();
	if(strLogName.IsEmpty())
	{
		AfxMessageBox(_T("�������û���¼��!"));
		return FALSE;
	}
	
	if(m_DMng.GetCountUserLogName(strLogName.GetBuffer(0))<=0)
	{
		AfxMessageBox(_T("û�д��û�!"));
		return FALSE;
	}

	StHrUser  nUserInfo;
	m_DMng.GetOneUsrInfoLogName(strLogName.GetBuffer(0),&nUserInfo);

	if(strcmp(nUserInfo.szUserPwd,strLogPwd.GetBuffer(0)) !=0)
	{
		AfxMessageBox(_T("�û����벻��ȷ!"));
		return FALSE;
	}

	WritePrivateProfileString("Def_HisUser","UserName", strLogName.GetBuffer(0), nFileName);

	memcpy(&g_LoginUsrInfo,&nUserInfo,sizeof(StHrUser));
	memset(&g_CurSelDepart,0,sizeof(StHrGroup));

	ReGetAllGroupInfo();
	int i,nCount = 0;
	
	nCount = g_AllGroups.size();
	StHrGroup *pStHrGroup = NULL;
	for (i = 0;i<nCount;i++)
	{
		pStHrGroup = g_AllGroups.at(i);
		if(pStHrGroup == NULL)
		{
			continue;
		}

		if(pStHrGroup->nOid == g_LoginUsrInfo.nGroupOid)
		{
			memcpy(&g_CurSelDepart,pStHrGroup,sizeof(StHrGroup));
			break;
		}
	}

	if(i>=nCount && i>0)
	{
		if(g_GroupSelect<0 || g_GroupSelect >= nCount)
		{
			g_GroupSelect = 0;

		}
		memcpy(&g_CurSelDepart,g_AllGroups.at(g_GroupSelect),sizeof(StHrGroup));

		CString nFileName ;
		CString str;
		nFileName.Format("%s\\%s",g_WorkPath,USRMNG_USRCFG_FILENAME) ;
		str.Format(_T("%d"), g_GroupSelect);
		if(/*g_LoginUsrInfo.nUserType == user_admin*/1)
		{
			WritePrivateProfileString("Def_GroupSelect","GroupSelect", str, nFileName);
		}

	}
		
	return TRUE;

}

void CSysLogin::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	
	CBitmap bitmap; 

	bitmap.LoadBitmap(IDB_BITMAP1); //1300*801

	CBrush brush; 

	brush.CreatePatternBrush(&bitmap); 

	CBrush* pOldBrush = dc.SelectObject(&brush); 

	dc.Rectangle(0,0,1300,801); //��Щ�������Ե���ͼƬ���λ�úʹ�С

	dc.SelectObject(pOldBrush);
}

void CSysLogin::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	int BtnWidth = 80;
	int BtnHeight = 40;

	int EdtWidth = 238;
	int EdtHeight = 33;

	if(GetDlgItem(IDC_LOGUSERNAME_EDT)->GetSafeHwnd())
	{
		GetDlgItem(IDC_LOGUSERNAME_EDT)->MoveWindow(900,336 ,EdtWidth,EdtHeight);
	}
	if(GetDlgItem(IDC_LOGPASSWORD_EDT)->GetSafeHwnd())
	{
		GetDlgItem(IDC_LOGPASSWORD_EDT)->MoveWindow(900,395 ,EdtWidth,EdtHeight);
	}

	if(GetDlgItem(IDOK)->GetSafeHwnd())
	{
		GetDlgItem(IDOK)->MoveWindow(913,447 ,BtnWidth,BtnHeight);
	}
	if(GetDlgItem(IDCANCEL)->GetSafeHwnd())
	{
		GetDlgItem(IDCANCEL)->MoveWindow(1045,447 ,BtnWidth,BtnHeight);
	}
}

void CSysLogin::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	ReleaseRoles(&g_AllRoles);
	CDialog::OnCancel();
}
