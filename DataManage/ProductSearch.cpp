// ProductSearch.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "ProductSearch.h"
#include "SelUserDlg.h"
#include "SelDate.h"


// CProductSearch 对话框

IMPLEMENT_DYNAMIC(CProductSearch, CDialog)

CProductSearch::CProductSearch(CWnd* pParent /*=NULL*/)
	: CDialog(CProductSearch::IDD, pParent)
{
	memset(&m_ProductSearch, 0 ,sizeof(StBasProduct));
}

CProductSearch::~CProductSearch()
{

}

void CProductSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProductSearch, CDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_SEARCH_BTN, &CProductSearch::OnBnClickedSearchBtn)
	ON_BN_CLICKED(IDC_BUTTON1, &CProductSearch::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CProductSearch::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CProductSearch::OnBnClickedButton3)
END_MESSAGE_MAP()


// CProductSearch 消息处理程序

BOOL CProductSearch::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	DisPalySearchInfo();
	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CProductSearch::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	OnBnClickedSearchBtn();
	//CDialog::OnOK();
}

void CProductSearch::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	AutoSize();
}


void CProductSearch::AutoSize()
{
	CRect Rect ;
	GetClientRect(&Rect);

	if (GetDlgItem(IDC_PROD_STATIC7)->GetSafeHwnd())
	{
		GetDlgItem(IDC_PROD_STATIC7)->MoveWindow(1,5,Rect.Width()-(1*2),Rect.Height()-(5*2));
	}

}

void CProductSearch::DisPalySearchInfo()
{
	CString strText;
	StBasProduct *pProductInfo = &m_ProductSearch;
	strText.Format(_T("%s"), pProductInfo->szProductNo);
	((CEdit*)GetDlgItem(IDC_PROD_CODE_EDT))->SetWindowText(strText);
	strText.Format(_T("%s"), pProductInfo->szProductName);
	((CEdit*)GetDlgItem(IDC_PROD_NAME_EDT))->SetWindowText(strText);

	strText.Format(_T("%s"), pProductInfo->szCreateBeginTime);
	((CEdit*)GetDlgItem(IDC_CREATE_BGNTIME_EDT))->SetWindowText(strText);
	strText.Format(_T("%s"), pProductInfo->szCreateEndTime);
	((CEdit *)GetDlgItem(IDC_CREATE_ENDTIME_EDT))->SetWindowText(strText);
	strText.Format(_T("%s"), pProductInfo->szCreateUser);
	((CEdit*)GetDlgItem(IDC_PROD_BUILDER_EDT))->SetWindowText(strText);
}

BOOL CProductSearch::GetSearchInfo()
{
	CString strText;
	StBasProduct *pProductInfo = &m_ProductSearch;
	((CEdit*)GetDlgItem(IDC_PROD_CODE_EDT))->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(pProductInfo->szProductNo,0,sizeof(pProductInfo->szProductNo));
	strcpy(pProductInfo->szProductNo,strText);

	((CEdit*)GetDlgItem(IDC_PROD_NAME_EDT))->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(pProductInfo->szProductName,0,sizeof(pProductInfo->szProductName));
	strcpy(pProductInfo->szProductName,strText);

	((CEdit*)GetDlgItem(IDC_CREATE_BGNTIME_EDT))->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(pProductInfo->szCreateBeginTime,0,sizeof(pProductInfo->szCreateBeginTime));
	strcpy(pProductInfo->szCreateBeginTime,strText);

	((CEdit*)GetDlgItem(IDC_CREATE_ENDTIME_EDT))->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(pProductInfo->szCreateEndTime,0,sizeof(pProductInfo->szCreateEndTime));
	strcpy(pProductInfo->szCreateEndTime,strText);


	((CEdit*)GetDlgItem(IDC_PROD_BUILDER_EDT))->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(pProductInfo->szCreateUser,0,sizeof(pProductInfo->szCreateUser));
	strcpy(pProductInfo->szCreateUser,strText);
	return TRUE;
}
void CProductSearch::OnBnClickedSearchBtn()
{
	// TODO: 在此添加控件通知处理程序代码

	CString strText;
	GetSearchInfo();

	g_pShowInfoList->m_ResultList.GetPageNumComBox();
	StSearchSetInfo *pSearchSetInfo = &g_pShowInfoList->m_ResultList.m_stSearchSetInfo;
	m_ProductSearch.nPerPageNum = pSearchSetInfo->nPerPageNum;
	//m_ProductSearch.nCurPage = 1;
	m_ProductSearch.nCurPage = pSearchSetInfo->nAimPage;

	if(m_ProductSearch.nCurPage <= 0)
	{
		m_ProductSearch.nCurPage = 1;
	}
	g_pShowInfoList->DisplayProdInfo(&m_ProductSearch);

}
//选择创建人//
void CProductSearch::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CSelUserDlg Dlg;
	CString strUserName;
	if(Dlg.DoModal() == IDOK)
	{
		strUserName = Dlg.m_SelUserName;
		GetDlgItem(IDC_PROD_BUILDER_EDT)->SetWindowText(strUserName);
	}
}

//选择创建开始时间//
void CProductSearch::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CSelDate Dlg;
	CString strBeginDate;
	SYSTEMTIME *pstTime = NULL;
	if(Dlg.DoModal() == IDOK)
	{
		pstTime = &Dlg.m_stTime;
		strBeginDate.Format(_T("%04d-%02d-%02d"),pstTime->wYear,pstTime->wMonth,pstTime->wDay);
		GetDlgItem(IDC_CREATE_BGNTIME_EDT)->SetWindowText(strBeginDate);
	}
}
//选择创建结束时间//
void CProductSearch::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CSelDate Dlg;
	CString strBeginDate;
	SYSTEMTIME *pstTime = NULL;
	if(Dlg.DoModal() == IDOK)
	{
		pstTime = &Dlg.m_stTime;
		strBeginDate.Format(_T("%04d-%02d-%02d"),pstTime->wYear,pstTime->wMonth,pstTime->wDay);
		GetDlgItem(IDC_CREATE_ENDTIME_EDT)->SetWindowText(strBeginDate);
	}
}
