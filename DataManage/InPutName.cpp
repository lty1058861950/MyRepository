// InPutName.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataManage.h"
#include "InPutName.h"


// CInPutName �Ի���

IMPLEMENT_DYNAMIC(CInPutName, CDialog)

CInPutName::CInPutName(InputInfo *pInputInfo,CWnd* pParent /*=NULL*/)
	: CDialog(CInPutName::IDD, pParent),m_pInputInfo(pInputInfo)
{

}

CInPutName::~CInPutName()
{
}

void CInPutName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInPutName, CDialog)
	ON_BN_CLICKED(IDC_RADIO3, &CInPutName::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CInPutName::OnBnClickedRadio4)
END_MESSAGE_MAP()


// CInPutName ��Ϣ�������

void CInPutName::InitWindowText()
{
	SetWindowText(m_pInputInfo->WindowText);
	GetDlgItem(IDC_INPUT_NAME_STATIC1)->SetWindowText(m_pInputInfo->NameStatic);
	GetDlgItem(IDC_INPUT_NAME_STATIC2)->SetWindowText(m_pInputInfo->CodeStatic);
	GetDlgItem(IDC_INPUT_CODE_EDT)->SetWindowText(m_pInputInfo->OutCode);
	GetDlgItem(IDC_INPUT_NAME_EDT)->SetWindowText(m_pInputInfo->OutName);

	switch(m_pInputInfo->Type)
	{

	case Add_Mode:
		{
			(GetDlgItem(IDC_RADIO3))->ShowWindow(SW_HIDE);
			(GetDlgItem(IDC_RADIO4))->ShowWindow(SW_HIDE);
			//ģ������//
			GetDlgItem(IDC_INPUT_NAME_STATIC2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_INPUT_CODE_EDT)->ShowWindow(SW_HIDE);
		}
		break;
	
	}
	
}
BOOL CInPutName::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitWindowText();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CInPutName::OnOK()
{
	if(CheckName(m_pInputInfo->Type))
	{
		CDialog::OnOK();
	}else
	{
		
	}
	
}
BOOL CInPutName::CheckName(int nType)
{
	GetDlgItem(IDC_INPUT_CODE_EDT)->GetWindowText(m_pInputInfo->OutCode);
	m_pInputInfo->OutCode = m_pInputInfo->OutCode.TrimLeft();
	m_pInputInfo->OutCode = m_pInputInfo->OutCode.TrimRight();
	GetDlgItem(IDC_INPUT_NAME_EDT)->GetWindowText(m_pInputInfo->OutName);
	m_pInputInfo->OutName = m_pInputInfo->OutName.TrimLeft();
	m_pInputInfo->OutName = m_pInputInfo->OutName.TrimRight();
	
	
	int nRows = 0;
	char szSQL[512] = {0};

	switch(nType)
	{
	case Add_Mode:  //[����]
		{
			if (m_pInputInfo->OutName.IsEmpty())
			{
				AfxMessageBox("��������Ʋ���Ϊ��!");
				return FALSE;
			}
			//����������Ʋ��ظ�//
			//sprintf(szSQL,_T("%s where %s%s"),g_AllTabName2[3],g_TaskTab[1],SQLText(m_pInputInfo->OutName));
			
			break;
		}
		
	}
	return TRUE;
}
void CInPutName::OnBnClickedRadio3()//��ͼ���Ƿ�ѡ��//
{
	if(((CButton *)GetDlgItem(IDC_RADIO3))->GetCheck())//��ͼ��//
	{
		((CButton *)GetDlgItem(IDC_RADIO1))->EnableWindow(TRUE);
		((CButton *)GetDlgItem(IDC_RADIO2))->EnableWindow(TRUE);
	}
}

void CInPutName::OnBnClickedRadio4()
{
	if(((CButton *)GetDlgItem(IDC_RADIO4))->GetCheck())//��ͼ��//
	{
		((CButton *)GetDlgItem(IDC_RADIO1))->EnableWindow(FALSE);
		((CButton *)GetDlgItem(IDC_RADIO2))->EnableWindow(FALSE);

		((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(FALSE);
		((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(TRUE);
	}
}
