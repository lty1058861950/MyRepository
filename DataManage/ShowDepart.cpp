// ShowDepart.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataManage.h"
#include "ShowDepart.h"


// CShowDepart �Ի���

IMPLEMENT_DYNAMIC(CShowDepart, CDialog)

CShowDepart::CShowDepart(CWnd* pParent /*=NULL*/)
	: CDialog(CShowDepart::IDD, pParent)
{

}

CShowDepart::CShowDepart(int ShowType,CDepartMng* pDepartMng,CString PDID,CString DID,CWnd* pParent /*=NULL*/)
: CDialog(CShowDepart::IDD, pParent), m_ShowType(ShowType), m_pDepartMng(pDepartMng),
	m_PDID(PDID),m_DID(DID)
{

}
CShowDepart::~CShowDepart()
{
}

void CShowDepart::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHOWDEPART_USR_LIST, m_ShowDepartUsrList);
}


BEGIN_MESSAGE_MAP(CShowDepart, CDialog)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_SHOWDEPART_ADDUSR_BTN, &CShowDepart::OnBnClickedShowdepartAddusrBtn)
	ON_BN_CLICKED(IDC_SHOWDEPART_DELUSR_BTN, &CShowDepart::OnBnClickedShowdepartDelusrBtn)
END_MESSAGE_MAP()


// CShowDepart ��Ϣ�������

BOOL CShowDepart::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	switch(m_ShowType)
	{
	case 1:
		{
			InitContrlStateAdd();
			InitContrlInfoAdd();
		}
		break;
	case 2:
		{
			InitContrlStateEdit();
			InitContrlInfoEdit();
		}
		break;
	}

	GetDlgItem(IDC_SHOWDEPART_USR_LIST)->ShowWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CShowDepart::InitContrlStateAdd()
{
	this->SetWindowText(_T("��Ӳ���"));

	m_ShowDepartUsrList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_GRIDLINES);
	m_ShowDepartUsrList.InsertColumn(0, _T("���"),LVCFMT_CENTER, 50);
	m_ShowDepartUsrList.InsertColumn(1, _T("��¼��"),LVCFMT_CENTER, 100);
	m_ShowDepartUsrList.InsertColumn(2, _T("�û�ID"),LVCFMT_CENTER, 100);
}
void CShowDepart::InitContrlStateEdit()
{
	this->SetWindowText(_T("�޸Ĳ�����Ϣ"));
	GetDlgItem(IDOK)->SetWindowText(_T("����"));
	m_ShowDepartUsrList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_GRIDLINES);
	m_ShowDepartUsrList.InsertColumn(0, _T("���"),LVCFMT_CENTER, 50);
	m_ShowDepartUsrList.InsertColumn(1, _T("��¼��"),LVCFMT_CENTER, 100);
	m_ShowDepartUsrList.InsertColumn(2, _T("�û�ID"),LVCFMT_CENTER, 100);
}
void CShowDepart::InitContrlInfoAdd()
{

}
void CShowDepart::InitContrlInfoEdit()
{

	StHrGroup *pDepartInfo = &m_pDepartMng->m_CurSelDepart;

	CString strText;
	GetDlgItem(IDC_SHOWDEPART_CODE_EDT)->SetWindowText(pDepartInfo->szGroupNo);
	GetDlgItem(IDC_SHOWDEPART_NAME_EDT)->SetWindowText(pDepartInfo->szGroupName);
	GetDlgItem(IDC_SHOWDEPART_TYPE_EDT)->SetWindowText(pDepartInfo->szGroupType);
	GetDlgItem(IDC_SHOWDEPART_PHONE_EDT)->SetWindowText(pDepartInfo->szCall);
	GetDlgItem(IDC_SHOWDEPART_FAXES_EDT)->SetWindowText(pDepartInfo->szFaxs);
	GetDlgItem(IDC_SHOWDEPART_ADDRESS_EDT)->SetWindowText(pDepartInfo->szAddress);
	GetDlgItem(IDC_SHOWDEPART_DESCRIBE_EDT)->SetWindowText(pDepartInfo->szDescription);

	CEditableListCtrl *pDepartUsrList = &m_pDepartMng->m_CurDepartUsrList;

	int nCount = pDepartUsrList->GetItemCount();
	for(int i = 0;i<nCount;i++)
	{
		strText = pDepartUsrList->GetItemText(i,0);
		m_ShowDepartUsrList.InsertItem(i,strText);

		strText=pDepartUsrList->GetItemText(i,1);
		m_ShowDepartUsrList.SetItemText(i,1,strText);
		strText=pDepartUsrList->GetItemText(i,2);
		m_ShowDepartUsrList.SetItemText(i,2,strText);
	}

}


BOOL CShowDepart::CheckInfoAdd(StHrGroup *pDepartInfo)
{
	memset(pDepartInfo,0,sizeof(StHrGroup));
	CString strDepartCode,strDepartName,strDepartType;
	GetDlgItem(IDC_SHOWDEPART_NAME_EDT)->GetWindowText(strDepartName);
	GetDlgItem(IDC_SHOWDEPART_CODE_EDT)->GetWindowText(strDepartCode);
	GetDlgItem(IDC_SHOWDEPART_TYPE_EDT)->GetWindowText(strDepartType);


	strDepartName = strDepartName.TrimLeft();
	strDepartName = strDepartName.TrimRight();
	strDepartCode = strDepartCode.TrimLeft();
	strDepartCode = strDepartCode.TrimRight();
	strDepartType = strDepartType.TrimLeft();
	strDepartType = strDepartType.TrimRight();
	
	if(strDepartName.IsEmpty())
	{
		AfxMessageBox(_T("�������Ʋ���Ϊ��!"));
		return FALSE;
	}

	
	pDepartInfo->nPOid = m_pDepartMng->m_CurSelDepart.nOid;
	strcpy(pDepartInfo->szGroupName,strDepartName);
	strcpy(pDepartInfo->szGroupNo,strDepartCode);
	strcpy(pDepartInfo->szGroupType,strDepartType);


	//1.��鵱ǰ�������Ӳ��ŵ����� �Ƿ�ռ��//
	if(m_DMng.IsDepartExists(strDepartName,pDepartInfo->nPOid))
	{
		CString strText;
		strText.Format(_T("��������\" %s \"�ѱ�ռ��!"),strDepartName);
		AfxMessageBox(strText);
		return FALSE;
	}

	CString strDepartPhone,strDepartFaxs,strDepartAddress,strDepartDescribe;
	GetDlgItem(IDC_SHOWDEPART_PHONE_EDT)->GetWindowText(strDepartPhone);
	GetDlgItem(IDC_SHOWDEPART_FAXES_EDT)->GetWindowText(strDepartFaxs);
	GetDlgItem(IDC_SHOWDEPART_ADDRESS_EDT)->GetWindowText(strDepartAddress);
	GetDlgItem(IDC_SHOWDEPART_DESCRIBE_EDT)->GetWindowText(strDepartDescribe);


	strDepartPhone = strDepartPhone.TrimLeft();
	strDepartPhone = strDepartPhone.TrimRight();
	strDepartFaxs = strDepartFaxs.TrimLeft();
	strDepartFaxs = strDepartFaxs.TrimRight();
	strDepartAddress = strDepartAddress.TrimLeft();
	strDepartAddress = strDepartAddress.TrimRight();
	strDepartDescribe = strDepartDescribe.TrimLeft();
	strDepartDescribe = strDepartDescribe.TrimRight();

	strcpy(pDepartInfo->szDescription,strDepartDescribe);
	strcpy(pDepartInfo->szCall,strDepartPhone);
	strcpy(pDepartInfo->szFaxs,strDepartFaxs);
	strcpy(pDepartInfo->szAddress,strDepartAddress);
	return TRUE;
}
BOOL CShowDepart::CheckInfoEdit(StHrGroup *pDepartInfo)
{

	memset(pDepartInfo,0,sizeof(StHrGroup));
	CString strDepartCode,strDepartName,strDepartType;
	GetDlgItem(IDC_SHOWDEPART_NAME_EDT)->GetWindowText(strDepartName);
	GetDlgItem(IDC_SHOWDEPART_CODE_EDT)->GetWindowText(strDepartCode);
	GetDlgItem(IDC_SHOWDEPART_TYPE_EDT)->GetWindowText(strDepartType);


	strDepartName = strDepartName.TrimLeft();
	strDepartName = strDepartName.TrimRight();
	strDepartCode = strDepartCode.TrimLeft();
	strDepartCode = strDepartCode.TrimRight();
	strDepartType = strDepartType.TrimLeft();
	strDepartType = strDepartType.TrimRight();

	if(strDepartName.IsEmpty())
	{
		AfxMessageBox(_T("�������Ʋ���Ϊ��!"));
		return FALSE;
	}

	memcpy(pDepartInfo,&m_pDepartMng->m_CurSelDepart,sizeof(StHrGroup));

	memset(pDepartInfo->szGroupName,0,sizeof(pDepartInfo->szGroupName));
	strcpy(pDepartInfo->szGroupName,strDepartName);
	memset(pDepartInfo->szGroupNo,0,sizeof(pDepartInfo->szGroupNo));
	strcpy(pDepartInfo->szGroupNo,strDepartCode);
	memset(pDepartInfo->szGroupType,0,sizeof(pDepartInfo->szGroupType));
	strcpy(pDepartInfo->szGroupType,strDepartType);


	//1.��鵱ǰ�������Ӳ��ŵ����� �Ƿ�ռ��//
	if(m_DMng.IsDepartExists(strDepartName,pDepartInfo->nPOid))
	{
		StHrGroup nDepartInfo;
		memset(&nDepartInfo,0,sizeof(StHrGroup));
		if(m_DMng.GetOneGroupInfoName(strDepartName.GetBuffer(0),&nDepartInfo))
		{
			if(pDepartInfo->nOid != nDepartInfo.nOid)
			{
				CString strText;
				strText.Format(_T("��������\" %s \"�ѱ�ռ��!"),strDepartName);
				AfxMessageBox(strText);
				return FALSE;
			}
			
		}
		
	}

	CString strDepartPhone,strDepartFaxs,strDepartAddress,strDepartDescribe;
	GetDlgItem(IDC_SHOWDEPART_PHONE_EDT)->GetWindowText(strDepartPhone);
	GetDlgItem(IDC_SHOWDEPART_FAXES_EDT)->GetWindowText(strDepartFaxs);
	GetDlgItem(IDC_SHOWDEPART_ADDRESS_EDT)->GetWindowText(strDepartAddress);
	GetDlgItem(IDC_SHOWDEPART_DESCRIBE_EDT)->GetWindowText(strDepartDescribe);


	strDepartPhone = strDepartPhone.TrimLeft();
	strDepartPhone = strDepartPhone.TrimRight();
	strDepartFaxs = strDepartFaxs.TrimLeft();
	strDepartFaxs = strDepartFaxs.TrimRight();
	strDepartAddress = strDepartAddress.TrimLeft();
	strDepartAddress = strDepartAddress.TrimRight();
	strDepartDescribe = strDepartDescribe.TrimLeft();
	strDepartDescribe = strDepartDescribe.TrimRight();

	memset(pDepartInfo->szDescription,0,sizeof(pDepartInfo->szDescription));
	strcpy(pDepartInfo->szDescription,strDepartDescribe);
	memset(pDepartInfo->szCall,0,sizeof(pDepartInfo->szCall));
	strcpy(pDepartInfo->szCall,strDepartPhone);
	memset(pDepartInfo->szFaxs,0,sizeof(pDepartInfo->szFaxs));
	strcpy(pDepartInfo->szFaxs,strDepartFaxs);
	memset(pDepartInfo->szAddress,0,sizeof(pDepartInfo->szAddress));
	strcpy(pDepartInfo->szAddress,strDepartAddress);
	return TRUE;
}



void CShowDepart::OnBnClickedShowdepartAddusrBtn()
{
	
}

void CShowDepart::OnBnClickedShowdepartDelusrBtn()
{
	
}

void CShowDepart::OnOK()
{
	switch(m_ShowType)
	{
	case 1:
		{
			StHrGroup nDepartInfo;
			if(CheckInfoAdd(&nDepartInfo))
			{
				if(m_pDepartMng->AddNewDepart(&nDepartInfo))
				{
					CDialog::OnOK();
					AfxMessageBox(_T("������ӳɹ�!"));
				}else
				{
					AfxMessageBox(_T("�������ʧ��!"));
				}
			}
		}
		break;
	case 2:
		{
			StHrGroup nDepartInfo;
			if(CheckInfoEdit(&nDepartInfo))
			{
				if(m_pDepartMng->EditOneDepart(&nDepartInfo))
				{
					CDialog::OnOK();
					AfxMessageBox(_T("������Ϣ�޸ĳɹ�!"));
				}else
				{
					AfxMessageBox(_T("������Ϣ�޸�ʧ��!"));
				}
			}
		}
		break;
	}
	
}
