// ShowUsr.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataManage.h"
#include "ShowUsr.h"
#include "UserMenage.h"

// CShowUsr �Ի���

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


// CShowUsr ��Ϣ�������//

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
	this->SetWindowText(_T("����û�"));

	GetDlgItem(IDC_SHOWUSR_RESETPWND_BTN)->ShowWindow(SW_HIDE);
}
void CShowUsr::SetContrlStateEdit()
{
	this->SetWindowText(_T("�޸��û���Ϣ"));
	GetDlgItem(IDOK)->SetWindowText(_T("����"));

	
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
	//�������ű� ���벿������//
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
    //�û�����//
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
	
	//PAD�� ��ʼ��//
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

	//1.���Ϸ���//
	if(strUsrLogName.IsEmpty())
	{
		AfxMessageBox(_T("�û���¼������Ϊ��!"));
		return FALSE;
	}
	if(strUsrName.IsEmpty())
	{
		AfxMessageBox(_T("�û���������Ϊ��!"));
		return FALSE;
	}

	
	int nRows = 0;
	
	//2.����¼�� �Ƿ����//
	if((nRows = m_DMng.IsUserLogNameExists(strUsrLogName.GetBuffer(0)) >= 1))
	{
		CString strText;
		strText.Format(_T("��¼��\" %s \"�ѱ�ռ��!"),strUsrLogName);
		AfxMessageBox(strText);
		return FALSE;
	}
	//3.��������� �Ƿ����//
	if((nRows = m_DMng.IsUserUserNameExists(strUsrName.GetBuffer(0)) >= 1))
	{
		CString strText;
		strText.Format(_T("�û�����\" %s \"�ѱ�ռ��!"),strUsrName);
		AfxMessageBox(strText);
		return FALSE;
	}

	strcpy(pUsrInfo->szLoginName,strUsrLogName);
	strcpy(pUsrInfo->szUserName,strUsrName);

	int nIndex,nCount;

	
	//����//
	CComboBox *pDepart = (CComboBox*)GetDlgItem(IDC_SHOWUSR_DEPART_COMBO);
	nIndex = pDepart->GetCurSel();
	nCount = pDepart->GetCount();
	if(nIndex <0 || nIndex >= nCount)
	{

	}else
	{
		pUsrInfo->nGroupOid = pDepart->GetItemData(nIndex);
	}
	//�û�����//
	int nUserType;
	nUserType = ((CComboBox*)GetDlgItem(IDC_SHOWUSR_TYPE_COMBO))->GetCurSel();
	pUsrInfo->nUserType = nUserType;
	//PAD��//
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
	//�û���¼���Ʋ��ܸ�//
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
	
	//����//
	CComboBox *pDepart = (CComboBox*)GetDlgItem(IDC_SHOWUSR_DEPART_COMBO);
	nIndex = pDepart->GetCurSel();
	nCount = pDepart->GetCount();
	if(nIndex <0 || nIndex >= nCount)
	{

	}else
	{
		pUsrInfo->nGroupOid = pDepart->GetItemData(nIndex);
	}
	//�û�����//
	int nUserType;
	nUserType = ((CComboBox*)GetDlgItem(IDC_SHOWUSR_TYPE_COMBO))->GetCurSel();
	pUsrInfo->nUserType = nUserType;

	//PAD��//
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
	case 1://���//
		{
			StHrUser nUsrInfo;
			if(CheckInfoAdd(&nUsrInfo))
			{
				if(m_pUsrMng->AddNewUsr(&nUsrInfo))
				{
					CDialog::OnOK();
					AfxMessageBox(_T("�û���ӳɹ�!"));
				}else
				{
					AfxMessageBox(_T("�û����ʧ��!"));
				}
			}
		}
		break;
	case 2://�޸�//
		{
			StHrUser nUsrInfo;
			if(CheckInfoEdit(&nUsrInfo))
			{
				if(m_pUsrMng->EditOneUsr(&nUsrInfo))
				{
					CDialog::OnOK();
					AfxMessageBox(_T("�û���Ϣ�޸ĳɹ�!"));
				}else
				{
					AfxMessageBox(_T("�û��޸���Ϣʧ��!"));
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
		AfxMessageBox("����������!");
	}
}



