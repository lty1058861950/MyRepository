// ResultSearchInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "ResultSearchInfo.h"
#include "SelDate.h"
#include "SelProductDlg.h"

// CResultSearchInfo 对话框

IMPLEMENT_DYNAMIC(CResultSearchInfo, CDialog)

CResultSearchInfo::CResultSearchInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CResultSearchInfo::IDD, pParent)
{
	m_pResultSearchNew = NULL;
}

CResultSearchInfo::~CResultSearchInfo()
{
}

void CResultSearchInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CResultSearchInfo, CDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, &CResultSearchInfo::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CResultSearchInfo::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CResultSearchInfo::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CResultSearchInfo::OnBnClickedButton4)
END_MESSAGE_MAP()


// CResultSearchInfo 消息处理程序

BOOL CResultSearchInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//DisPalySearchInfo();
	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CResultSearchInfo::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	OnBnClickedButton1();
	CDialog::OnOK();
}

void CResultSearchInfo::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	AutoSize();
}

void  CResultSearchInfo::AutoSize()
{
	CRect Rect ;
	GetClientRect(&Rect) ;
	int nBtnWidth = 80;
	int nBtnHeight = 30;
	if (GetDlgItem(IDC_STATIC1)->GetSafeHwnd())
	{
		GetDlgItem(IDC_STATIC1)->MoveWindow(0,1,Rect.Width(),Rect.Height()-1*2);
	}

	if (GetDlgItem(IDC_BUTTON1)->GetSafeHwnd())
	{
		GetDlgItem(IDC_BUTTON1)->MoveWindow(Rect.right-(nBtnWidth+20),Rect.bottom-(nBtnHeight+30),nBtnWidth,nBtnHeight);
	}
}

void CResultSearchInfo::DisPalySearchInfo()
{
	StBasTask *pSearchInfo = &m_pResultSearchNew->m_ResultSearchInfo;

	CString strText;
	strText.Format(_T("%s"), pSearchInfo->stTaskBaseInfo.szTaskName);
	((CEdit*)GetDlgItem(IDC_EDIT1))->SetWindowText(strText);

	strText.Format(_T("%s"), pSearchInfo->stProductInfo.szProductNo);
	((CEdit*)GetDlgItem(IDC_EDIT2))->SetWindowText(strText);
	strText.Format(_T("%s"), pSearchInfo->stTaskBaseInfo.szSendBeginTime);
	((CEdit *)GetDlgItem(IDC_EDIT3))->SetWindowText(strText);
	strText.Format(_T("%s"), pSearchInfo->stTaskBaseInfo.szSendEndTime);
	((CEdit*)GetDlgItem(IDC_EDIT4))->SetWindowText(strText);

	strText.Format(_T("%s"), pSearchInfo->stTaskBaseInfo.szProductCode);
	((CEdit*)GetDlgItem(IDC_EDIT5))->SetWindowText(strText);
}

BOOL CResultSearchInfo::GetSearchInfo()
{
	
	CString strText;
	StBasTask *pSearchInfo = &m_pResultSearchNew->m_ResultSearchInfo;
	

	((CEdit*)GetDlgItem(IDC_EDIT1))->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(pSearchInfo->stTaskBaseInfo.szTaskName,0,sizeof(pSearchInfo->stTaskBaseInfo.szTaskName));
	strcpy(pSearchInfo->stTaskBaseInfo.szTaskName,strText);

	((CEdit*)GetDlgItem(IDC_EDIT2))->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(pSearchInfo->stProductInfo.szProductNo,0,sizeof(pSearchInfo->stProductInfo.szProductNo));
	strcpy(pSearchInfo->stProductInfo.szProductNo,strText);


	((CEdit*)GetDlgItem(IDC_EDIT3))->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(pSearchInfo->stTaskBaseInfo.szSendBeginTime,0,sizeof(pSearchInfo->stTaskBaseInfo.szSendBeginTime));
	strcpy(pSearchInfo->stTaskBaseInfo.szSendBeginTime,strText);

	((CEdit*)GetDlgItem(IDC_EDIT4))->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(pSearchInfo->stTaskBaseInfo.szSendEndTime,0,sizeof(pSearchInfo->stTaskBaseInfo.szSendEndTime));
	strcpy(pSearchInfo->stTaskBaseInfo.szSendEndTime,strText);
	

	((CEdit*)GetDlgItem(IDC_EDIT5))->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(pSearchInfo->stTaskBaseInfo.szProductCode,0,sizeof(pSearchInfo->stTaskBaseInfo.szProductCode));
	strcpy(pSearchInfo->stTaskBaseInfo.szProductCode,strText);
	return TRUE;
}

//查询按钮//
void CResultSearchInfo::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	CResultList *pResList = NULL;
	StSearchSetInfo *pSearchSetInfo = NULL;
	int nResultSearchType = m_pResultSearchNew->m_ResultSearchInfo.stTaskBaseInfo.nResultType;

	switch(nResultSearchType)
	{
	case Task_DarkSearch://基于任务 模糊查询//
		{
			pResList = &m_pResultSearchNew->m_ResultTaskBase;
		}
		break; 
	case Task_ExactSearch://基于任务精确查找//
		{
			pResList = NULL;


		}
		break;
	case Result_Search:
		{
			pResList = &m_pResultSearchNew->m_ResultAttach;

		}
		break;
	}


	if(pResList == NULL)
	{
		m_pResultSearchNew->m_ResultSearchInfo.stTaskBaseInfo.nPerPageNum = g_nSearchPerPageNum[All_Result];
	}else
	{
		pResList->GetPageNumComBox();//获取页数和目标页//
		//对获取的页数进行处理//
		pSearchSetInfo = &pResList->m_stSearchSetInfo;
		m_pResultSearchNew->m_ResultSearchInfo.stTaskBaseInfo.nPerPageNum = pSearchSetInfo->nPerPageNum;
		m_pResultSearchNew->m_ResultSearchInfo.stTaskBaseInfo.nCurPage = pSearchSetInfo->nAimPage;
		if(m_pResultSearchNew->m_ResultSearchInfo.stTaskBaseInfo.nCurPage <= 0)
		{
			m_pResultSearchNew->m_ResultSearchInfo.stTaskBaseInfo.nCurPage = 1;
		}
	}


	int nFlg = 0;
	nFlg = m_pResultSearchNew->SearchResultData();

	if(nFlg == 2)
	{
		m_pResultSearchNew->m_ResultSearchInfo.stTaskBaseInfo.nCurPage = 1;
		m_pResultSearchNew->SearchResultData();
	}

}
//选择产品代号//
void CResultSearchInfo::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CSelProductDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		GetDlgItem(IDC_EDIT2)->SetWindowText(dlg.m_strProductNo);
		//GetDlgItem(IDC_PRODNAME_EDT)->SetWindowText(dlg.m_strProductName);
	}

}
//选择任务下发开始日期//
void CResultSearchInfo::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CSelDate Dlg;
	CString strBeginDate;
	SYSTEMTIME *pstTime = NULL;
	if(Dlg.DoModal() == IDOK)
	{
		pstTime = &Dlg.m_stTime;
		strBeginDate.Format(_T("%04d-%02d-%02d"),pstTime->wYear,pstTime->wMonth,pstTime->wDay);
		GetDlgItem(IDC_EDIT3)->SetWindowText(strBeginDate);
	}
}
//选择任务下发结束日期//
void CResultSearchInfo::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CSelDate Dlg;
	CString strBeginDate;
	SYSTEMTIME *pstTime = NULL;
	if(Dlg.DoModal() == IDOK)
	{
		pstTime = &Dlg.m_stTime;
		strBeginDate.Format(_T("%04d-%02d-%02d"),pstTime->wYear,pstTime->wMonth,pstTime->wDay);
		GetDlgItem(IDC_EDIT4)->SetWindowText(strBeginDate);
	}
}
