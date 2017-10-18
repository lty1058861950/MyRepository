// ShowUsr.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "ShowUsr.h"
#include "UserMenage.h"

// CShowUsr 对话框

IMPLEMENT_DYNAMIC(CShowUsr, CDialog)

CShowUsr::CShowUsr(CWnd* pParent /*=NULL*/)
	: CDialog(CShowUsr::IDD, pParent)
{

}

CShowUsr::CShowUsr(int ShowType,CUserMenage* pUsrMng,CWnd* pParent /*=NULL*/)
: CDialog(CShowUsr::IDD, pParent),m_ShowType(ShowType),m_pUsrMng(pUsrMng)
{

}

CShowUsr::~CShowUsr()
{

}

void CShowUsr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CShowUsr, CDialog)
	ON_BN_CLICKED(IDC_SHOWUSR_RESETPWND_BTN, &CShowUsr::OnBnClickedShowusrResetpwndBtn)
END_MESSAGE_MAP()


// CShowUsr 消息处理程序//

BOOL CShowUsr::OnInitDialog()
{
	CDialog::OnInitDialog();
	switch(m_ShowType)
	{
	case 1:
		{
			SetContrlStateAdd();
			InitComBoxs();
			InitContrlInfoAdd();
		}
		break;
	case 2:
		{
			SetContrlStateEdit();
			InitComBoxs();
			InitContrlInfoEdit();
		}
		break;
	}

	return TRUE; 
}

void CShowUsr::SetContrlStateAdd()
{
	this->SetWindowText(_T("添加用户"));

	GetDlgItem(IDC_SHOWUSR_RESETPWND_BTN)->ShowWindow(SW_HIDE);
}
void CShowUsr::SetContrlStateEdit()
{
	this->SetWindowText(_T("修改用户信息"));
	GetDlgItem(IDOK)->SetWindowText(_T("保存"));

	
	((CEdit*)GetDlgItem(IDC_SHOWUSR_LOGNAME_EDT))->SetReadOnly(TRUE);
	
	
	if(m_pUsrMng->m_CurUserInfo.nUserType == user_admin)
	{
		GetDlgItem(IDC_SHOWUSR_DEPART_COMBO)->EnableWindow(FALSE);
		GetDlgItem(IDC_SHOWUSR_TYPE_COMBO)->EnableWindow(FALSE);
	}

	if(g_LoginUsrInfo.nUserType == user_admin)
	{
		GetDlgItem(IDC_SHOWUSR_RESETPWND_BTN)->ShowWindow(SW_SHOW);
	}else
	{
		GetDlgItem(IDC_SHOWUSR_RESETPWND_BTN)->ShowWindow(SW_HIDE);
	}
	

}


void CShowUsr::InitContrlInfoAdd()
{

}
void CShowUsr::InitContrlInfoEdit()
{
	StHrUser *pUserInfo = &m_pUsrMng->m_CurUserInfo;

	CString strText;
	//GetDlgItem(IDC_SHOWUSR_USRID_EDT)->SetWindowText(strText);//1
	GetDlgItem(IDC_SHOWUSR_LOGNAME_EDT)->SetWindowText(pUserInfo->szLoginName);//2
	GetDlgItem(IDC_SHOWUSR_NAME_EDT)->SetWindowText(pUserInfo->szUserName);//3
	//GetDlgItem(IDC_SHOWUSR_USRID_EDT)->SetWindowText(strText);//4
	
	SetUserDepart(pUserInfo->nGroupOid);//5
	SerUserType(pUserInfo->nUserType);//6
	SerUserPadID(pUserInfo->nPadDevID);//7
	
	GetDlgItem(IDC_SHOWUSR_SIGNFILE_EDT)->SetWindowText(pUserInfo->szUserSignfile);//7
	GetDlgItem(IDC_SHOWUSR_CALL_EDT)->SetWindowText(pUserInfo->szCall);//8
	GetDlgItem(IDC_SHOWUSR_EMAIL_EDT)->SetWindowText(pUserInfo->szEmail);//9
	GetDlgItem(IDC_SHOWUSR_PHONE_EDT)->SetWindowText(pUserInfo->szPhone);//10
}
void CShowUsr::InitComBoxs()
{
	int i,nCount;
	CString strText;
	//遍历部门表 插入部门名称//
	CComboBox *pComDepart = ((CComboBox*)GetDlgItem(IDC_SHOWUSR_DEPART_COMBO));

	if(pComDepart->GetSafeHwnd())
	{
		pComDepart->ResetContent();
		
		vector<StHrGroup *> *pGroupAll = &g_AllGroups;
		nCount = pGroupAll->size();
		for(i = 0;i<nCount;i++)
		{
			pComDepart->AddString(pGroupAll->at(i)->szGroupName);
			pComDepart->SetItemData(i,pGroupAll->at(i)->nOid);

		}
	}
	
	int nUserType = m_pUsrMng->m_CurUserInfo.nUserType;
    //用户类型//
	if(GetDlgItem(IDC_SHOWUSR_TYPE_COMBO)->GetSafeHwnd())
	{
		//int nCount = m_UsrTypeName.GetCount();
		if(nUserType == user_admin)
		{
			((CComboBox*)GetDlgItem(IDC_SHOWUSR_TYPE_COMBO))->AddString(g_UserType[user_admin]);
		}else
		{
			for( i=user_normal;i< user_admin;i++)
			{
				((CComboBox*)GetDlgItem(IDC_SHOWUSR_TYPE_COMBO))->AddString( g_UserType[i]);
			}
		}
		
		((CComboBox*)GetDlgItem(IDC_SHOWUSR_TYPE_COMBO))->SetCurSel(0);
	}
	
	//PAD号 初始化//
	nCount = g_PadCount;
	if(GetDlgItem(IDC_COMBO1)->GetSafeHwnd())
	{
		
		for( i=0;i<=nCount;i++)
		{
			strText.Format(_T("%d"), i);
			((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(strText);
		}
		((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);
	}
}

void  CShowUsr::SetUserDepart(UINT nGroupOid)
{
	CComboBox* pComBox = (CComboBox*)GetDlgItem(IDC_SHOWUSR_DEPART_COMBO);
	int nCount = pComBox->GetCount();
	CString strComT;
	int i = 0;
	UINT nOid;
	for(i = 0;i<nCount;i++)
	{
		nOid = pComBox->GetItemData(i);
		if(nGroupOid == nOid)
		{
			pComBox->SetCurSel(i);
			return;
		}
	}
	
}
void  CShowUsr::SerUserType(int nUserType)
{
	CComboBox* pComBox = (CComboBox*)GetDlgItem(IDC_SHOWUSR_TYPE_COMBO);
	int nCount = pComBox->GetCount();
	CString strComT;
	
	if(nUserType == user_admin)
	{
		pComBox->SetCurSel(0);
	}else
	{
		if(nUserType>= 0&& nUserType<nCount)
		{
			pComBox->SetCurSel(nUserType);
		}
	}
	
}
void  CShowUsr::SerUserPadID(int nPadDevID)
{
	CComboBox* pComBox = (CComboBox*)GetDlgItem(IDC_COMBO1);
	int nCount = pComBox->GetCount();
	CString strComT;
	if(nPadDevID>= 0&& nPadDevID<nCount)
	{
		pComBox->SetCurSel(nPadDevID);
	}
}

BOOL CShowUsr::CheckInfoAdd(StHrUser *pUsrInfo)
{
	/////
	memset(pUsrInfo,0,sizeof(StHrUser));
	CString strUsrLogName,strUsrName;
	GetDlgItem(IDC_SHOWUSR_LOGNAME_EDT)->GetWindowText(strUsrLogName);
	GetDlgItem(IDC_SHOWUSR_NAME_EDT)->GetWindowText(strUsrName);

	strUsrLogName = strUsrLogName.TrimLeft();
	strUsrLogName = strUsrLogName.TrimRight();
	strUsrName = strUsrName.TrimLeft();
	strUsrName = strUsrName.TrimRight();

	//1.检查合法性//
	if(strUsrLogName.IsEmpty())
	{
		AfxMessageBox(_T("用户登录名不能为空!"));
		return FALSE;
	}
	if(strUsrName.IsEmpty())
	{
		AfxMessageBox(_T("用户姓名不能为空!"));
		return FALSE;
	}

	
	int nRows = 0;
	
	//2.检查登录名 是否可用//
	if((nRows = m_DMng.IsUserLogNameExists(strUsrLogName.GetBuffer(0)) >= 1))
	{
		CString strText;
		strText.Format(_T("登录名\" %s \"已被占用!"),strUsrLogName);
		AfxMessageBox(strText);
		return FALSE;
	}
	//3.检查中文名 是否可用//
	if((nRows = m_DMng.IsUserUserNameExists(strUsrName.GetBuffer(0)) >= 1))
	{
		CString strText;
		strText.Format(_T("用户姓名\" %s \"已被占用!"),strUsrName);
		AfxMessageBox(strText);
		return FALSE;
	}

	strcpy(pUsrInfo->szLoginName,strUsrLogName);
	strcpy(pUsrInfo->szUserName,strUsrName);

	int nIndex,nCount;

	
	//部门//
	CComboBox *pDepart = (CComboBox*)GetDlgItem(IDC_SHOWUSR_DEPART_COMBO);
	nIndex = pDepart->GetCurSel();
	nCount = pDepart->GetCount();
	if(nIndex <0 || nIndex >= nCount)
	{

	}else
	{
		pUsrInfo->nGroupOid = pDepart->GetItemData(nIndex);
	}
	//用户类型//
	int nUserType;
	nUserType = ((CComboBox*)GetDlgItem(IDC_SHOWUSR_TYPE_COMBO))->GetCurSel();
	pUsrInfo->nUserType = nUserType;
	//PAD号//
	int PadID = 0;
	PadID = ((CComboBox *)GetDlgItem(IDC_COMBO1))->GetCurSel();
	pUsrInfo->nPadDevID = PadID;


	CString strUsrSignFile,strUsrCall,strUsrEmail,strUsrPhone;
	GetDlgItem(IDC_SHOWUSR_SIGNFILE_EDT)->GetWindowText(strUsrSignFile);
	GetDlgItem(IDC_SHOWUSR_CALL_EDT)->GetWindowText(strUsrCall);
	GetDlgItem(IDC_SHOWUSR_EMAIL_EDT)->GetWindowText(strUsrEmail);
	GetDlgItem(IDC_SHOWUSR_PHONE_EDT)->GetWindowText(strUsrPhone);

	strUsrSignFile = strUsrSignFile.TrimLeft();
	strUsrSignFile = strUsrSignFile.TrimRight();
	strUsrCall = strUsrCall.TrimLeft();
	strUsrCall = strUsrCall.TrimRight();
	strUsrEmail = strUsrEmail.TrimLeft();
	strUsrEmail = strUsrEmail.TrimRight();
	strUsrPhone = strUsrPhone.TrimLeft();
	strUsrPhone = strUsrPhone.TrimRight();

	strcpy(pUsrInfo->szUserSignfile,strUsrSignFile);
	strcpy(pUsrInfo->szCall,strUsrCall);
	strcpy(pUsrInfo->szEmail,strUsrEmail);
	strcpy(pUsrInfo->szPhone,strUsrPhone);
	return TRUE;

}
BOOL CShowUsr::CheckInfoEdit(StHrUser *pUsrInfo)
{

	CString strLoginName,strUserName;
	//用户登录名称不能改//
	GetDlgItem(IDC_SHOWUSR_LOGNAME_EDT)->GetWindowText(strLoginName);
	if(m_DMng.GetCountUserLogName(strLoginName.GetBuffer(0))<=0)
	{
		return FALSE;
	}

	if(!m_DMng.GetOneUsrInfoLogName(strLoginName.GetBuffer(0),pUsrInfo))
	{
		return FALSE;
	}

	GetDlgItem(IDC_SHOWUSR_NAME_EDT)->GetWindowText(strUserName);
	strUserName = strUserName.TrimLeft();
	strUserName = strUserName.TrimRight();
	strcpy(pUsrInfo->szUserName,strUserName);

	int nIndex,nCount;
	
	//部门//
	CComboBox *pDepart = (CComboBox*)GetDlgItem(IDC_SHOWUSR_DEPART_COMBO);
	nIndex = pDepart->GetCurSel();
	nCount = pDepart->GetCount();
	if(nIndex <0 || nIndex >= nCount)
	{

	}else
	{
		pUsrInfo->nGroupOid = pDepart->GetItemData(nIndex);
	}
	//用户类型//
	int nUserType;
	nUserType = ((CComboBox*)GetDlgItem(IDC_SHOWUSR_TYPE_COMBO))->GetCurSel();
	pUsrInfo->nUserType = nUserType;

	//PAD号//
	int PadID = 0;
	PadID = ((CComboBox *)GetDlgItem(IDC_COMBO1))->GetCurSel();
	pUsrInfo->nPadDevID = PadID;

	CString strUsrSignFile,strUsrCall,strUsrEmail,strUsrPhone;
	GetDlgItem(IDC_SHOWUSR_SIGNFILE_EDT)->GetWindowText(strUsrSignFile);
	GetDlgItem(IDC_SHOWUSR_CALL_EDT)->GetWindowText(strUsrCall);
	GetDlgItem(IDC_SHOWUSR_EMAIL_EDT)->GetWindowText(strUsrEmail);
	GetDlgItem(IDC_SHOWUSR_PHONE_EDT)->GetWindowText(strUsrPhone);

	strUsrSignFile = strUsrSignFile.TrimLeft();
	strUsrSignFile = strUsrSignFile.TrimRight();
	strUsrCall = strUsrCall.TrimLeft();
	strUsrCall = strUsrCall.TrimRight();
	strUsrEmail = strUsrEmail.TrimLeft();
	strUsrEmail = strUsrEmail.TrimRight();
	strUsrPhone = strUsrPhone.TrimLeft();
	strUsrPhone = strUsrPhone.TrimRight();

	strcpy(pUsrInfo->szUserSignfile,strUsrSignFile);
	strcpy(pUsrInfo->szCall,strUsrCall);
	strcpy(pUsrInfo->szEmail,strUsrEmail);
	strcpy(pUsrInfo->szPhone,strUsrPhone);
	return TRUE;
}
void CShowUsr::OnOK()
{
	switch(m_ShowType)
	{
	case 1://添加//
		{
			StHrUser nUsrInfo;
			if(CheckInfoAdd(&nUsrInfo))
			{
				if(m_pUsrMng->AddNewUsr(&nUsrInfo))
				{
					CDialog::OnOK();
					AfxMessageBox(_T("用户添加成功!"));
				}else
				{
					AfxMessageBox(_T("用户添加失败!"));
				}
			}
		}
		break;
	case 2://修改//
		{
			StHrUser nUsrInfo;
			if(CheckInfoEdit(&nUsrInfo))
			{
				if(m_pUsrMng->EditOneUsr(&nUsrInfo))
				{
					CDialog::OnOK();
					AfxMessageBox(_T("用户信息修改成功!"));
				}else
				{
					AfxMessageBox(_T("用户修改信息失败!"));
				}

			}
		}
		break;
	}
	//CDialog::OnOK();
}


void CShowUsr::OnBnClickedShowusrResetpwndBtn()
{
	CEditableListCtrl *pList = &(m_pUsrMng->m_UsrMngList);
	int SelIndex = pList->GetFirstSelectedItem();

	if(SelIndex<0 ||SelIndex>=pList->GetItemCount())
		return;
	CString strTextLogName;
	strTextLogName=pList->GetItemText(SelIndex,1);

	if(m_DMng.ReSetUsrPwd(g_ReSetDefPwd,strTextLogName.GetBuffer(0)))
	{
		AfxMessageBox("密码已重置!");
	}
}



