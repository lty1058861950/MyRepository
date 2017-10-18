// ProductInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataManage.h"
#include "ProductInfo.h"


// CProductInfo �Ի���

IMPLEMENT_DYNAMIC(CProductInfo, CDialog)

CProductInfo::CProductInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CProductInfo::IDD, pParent)
{
	m_pCurProdInfo = NULL;
}

CProductInfo::~CProductInfo()
{
}

void CProductInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProductInfo, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CProductInfo ��Ϣ�������

BOOL CProductInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CProductInfo::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialog::OnOK();
}

void CProductInfo::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	AutoSize();
}

void CProductInfo::AutoSize()
{
	CRect Rect ;
	GetClientRect(&Rect);
	
	int nStaticWidth = 60;
	int nStaticHeight = 30;
	int nEditWidth = 150;
	int nEditHeight = 20;

	if (GetDlgItem(IDC_PROD_STATIC7)->GetSafeHwnd())
	{
		GetDlgItem(IDC_PROD_STATIC7)->MoveWindow(1,5,Rect.Width()-(1*2),Rect.Height()-(5*2));
	}

}

void CProductInfo::DisPlayProductInfo()
{
	if(m_pCurProdInfo == NULL)
		return;
	CString strText;
	strText.Format(_T("%s"), m_pCurProdInfo->szProductNo);
	((CEdit*)GetDlgItem(IDC_PROD_CODE_EDT))->SetWindowText(strText);
	strText.Format(_T("%s"), m_pCurProdInfo->szProductName);
	((CEdit*)GetDlgItem(IDC_PROD_NAME_EDT))->SetWindowText(strText);

	strText = GetProductType(m_pCurProdInfo->nPicNumType);
	((CEdit*)GetDlgItem(IDC_PROD_PICNUM_EDT))->SetWindowText(strText);
	strText.Format(_T("%s"), m_pCurProdInfo->szCreateTime);
	((CEdit*)GetDlgItem(IDC_CREATE_BGNTIME_EDT))->SetWindowText(strText);
	strText.Format(_T("%s"), m_pCurProdInfo->szCreateUser);
	((CEdit*)GetDlgItem(IDC_PROD_BUILDER_EDT))->SetWindowText(strText);

	//SetPicNumTypeComText(m_CurProdInfo.nPicNumType);
	//SetSeriesTypeComText(m_CurProdInfo.nSeriesType);

}

void  CProductInfo::GetProdInfo()
{
	if(m_pCurProdInfo == NULL)
		return;
	CString strText;
	((CEdit*)GetDlgItem(IDC_PROD_CODE_EDT))->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(m_pCurProdInfo->szProductNo,0,sizeof(m_pCurProdInfo->szProductNo));
	strcpy(m_pCurProdInfo->szProductNo,strText);

	
	((CEdit*)GetDlgItem(IDC_PROD_NAME_EDT))->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(m_pCurProdInfo->szProductName,0,sizeof(m_pCurProdInfo->szProductName));
	strcpy(m_pCurProdInfo->szProductName,strText);


}