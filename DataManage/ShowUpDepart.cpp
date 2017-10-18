// ShowUpDepart.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataManage.h"
#include "ShowUpDepart.h"


// CShowUpDepart �Ի���

IMPLEMENT_DYNAMIC(CShowUpDepart, CDialog)

CShowUpDepart::CShowUpDepart(CWnd* pParent /*=NULL*/)
	: CDialog(CShowUpDepart::IDD, pParent)
{
	m_ShowType = UpDepart_View;
	m_pUpDepart = NULL;
}

CShowUpDepart::~CShowUpDepart()
{
}

void CShowUpDepart::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CShowUpDepart, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CShowUpDepart ��Ϣ�������

BOOL CShowUpDepart::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	switch(m_ShowType)
	{
	case UpDepart_Add:
		{
			this->GetDlgItem(IDOK)->SetWindowText(_T("ȷ��"));
			this->GetDlgItem(IDCANCEL)->SetWindowText(_T("ȡ��"));
		}
		break;
	case UpDepart_Modify:
		{
			this->GetDlgItem(IDOK)->SetWindowText(_T("����"));
			this->GetDlgItem(IDCANCEL)->SetWindowText(_T("ȡ��"));
		}
		break;
	case UpDepart_View:
		{
			this->GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
			this->GetDlgItem(IDCANCEL)->SetWindowText(_T("�˳�"));
		}
		break;
	}
	DisPalyUpDepartInfo();


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CShowUpDepart::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	int ret = 0;
	ret = GetUpDepartInfo();
	if(ret <= 0)
	{
		return;
	}else
	{
		switch(m_ShowType)
		{
		case UpDepart_Add:
			{
				AddNewUpDepart(m_pUpDepart);
			}
			break;
		case UpDepart_Modify:
			{
				ModifyTheUpDepart(m_pUpDepart);
			}
			break;
		}
	}

	CDialog::OnOK();
}

void CShowUpDepart::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialog::OnCancel();
}

void CShowUpDepart::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
}

void CShowUpDepart::DisPalyUpDepartInfo()
{
	StHrUpDepart *pUpDepartInfo = m_pUpDepart;
	CString strText;
	strText.Format(_T("%s"), pUpDepartInfo->szUpDepartName);
	GetDlgItem(IDC_EDIT1)->SetWindowText(strText);
	strText.Format(_T("%s"), pUpDepartInfo->szUpDepartNo);
	GetDlgItem(IDC_EDIT4)->SetWindowText(strText);
	strText.Format(_T("%s"), pUpDepartInfo->szUpDepartType);
	GetDlgItem(IDC_EDIT5)->SetWindowText(strText);
	strText.Format(_T("%s"), pUpDepartInfo->szCall);
	GetDlgItem(IDC_EDIT6)->SetWindowText(strText);
	strText.Format(_T("%s"), pUpDepartInfo->szFaxs);
	GetDlgItem(IDC_EDIT7)->SetWindowText(strText);
	strText.Format(_T("%s"), pUpDepartInfo->szAddress);
	GetDlgItem(IDC_EDIT8)->SetWindowText(strText);
	strText.Format(_T("%s"), pUpDepartInfo->szDescription);
	GetDlgItem(IDC_EDIT9)->SetWindowText(strText);
}
int CShowUpDepart::GetUpDepartInfo()
{
	StHrUpDepart *pUpDepartInfo = m_pUpDepart;
	CString strText, str;
	
	GetDlgItem(IDC_EDIT1)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	if(strText.IsEmpty())
	{
		str.Format(_T("�������Ʋ�����Ϊ��ֵ!"));
		AfxMessageBox(str);
		return 0;
	}
	memset(pUpDepartInfo->szUpDepartName, 0, sizeof(pUpDepartInfo->szUpDepartName));
	strcpy(pUpDepartInfo->szUpDepartName, strText);
	
	GetDlgItem(IDC_EDIT4)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(pUpDepartInfo->szUpDepartNo, 0, sizeof(pUpDepartInfo->szUpDepartNo));
	strcpy(pUpDepartInfo->szUpDepartNo, strText);

	GetDlgItem(IDC_EDIT5)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(pUpDepartInfo->szUpDepartType, 0, sizeof(pUpDepartInfo->szUpDepartType));
	strcpy(pUpDepartInfo->szUpDepartType, strText);
	
	GetDlgItem(IDC_EDIT6)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(pUpDepartInfo->szCall, 0, sizeof(pUpDepartInfo->szCall));
	strcpy(pUpDepartInfo->szCall, strText);
	
	GetDlgItem(IDC_EDIT7)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(pUpDepartInfo->szFaxs, 0, sizeof(pUpDepartInfo->szFaxs));
	strcpy(pUpDepartInfo->szFaxs, strText);
	
	GetDlgItem(IDC_EDIT8)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(pUpDepartInfo->szAddress, 0, sizeof(pUpDepartInfo->szAddress));
	strcpy(pUpDepartInfo->szAddress, strText);
	
	GetDlgItem(IDC_EDIT9)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(pUpDepartInfo->szDescription, 0, sizeof(pUpDepartInfo->szDescription));
	strcpy(pUpDepartInfo->szDescription, strText);

	return 1;
}
