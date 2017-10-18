// ModeSearch.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "ModeSearch.h"
#include "SelUserDlg.h"
#include "SelDate.h"
#include "SelProductDlg.h"

// CModeSearch 对话框

IMPLEMENT_DYNAMIC(CModeSearch, CDialog)

CModeSearch::CModeSearch(CWnd* pParent /*=NULL*/)
	: CDialog(CModeSearch::IDD, pParent)
{
	memset(&m_ModeSearchInfo, 0, sizeof(StBasMode));
}

CModeSearch::~CModeSearch()
{
}

void CModeSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModeSearch, CDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_SEARCH_BTN, &CModeSearch::OnBnClickedSearchBtn)
	ON_BN_CLICKED(IDC_BUTTON2, &CModeSearch::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CModeSearch::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CModeSearch::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_SEL_PROD_BTN, &CModeSearch::OnBnClickedSelProdBtn)
END_MESSAGE_MAP()


// CModeSearch 消息处理程序

BOOL CModeSearch::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	InitComBox();
	DisplaySearchInfo();
	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CModeSearch::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}

void CModeSearch::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	AutoSize();
}


void CModeSearch::AutoSize()
{
	CRect Rect ;
	GetClientRect(&Rect) ;
	

	if (GetDlgItem(IDC_SHOWMODEINFO_STATIC10)->GetSafeHwnd())
	{
		GetDlgItem(IDC_SHOWMODEINFO_STATIC10)->MoveWindow(1,5,Rect.Width()-(1*2),Rect.Height()-(5*2));
	}

}
void CModeSearch::InitComBox()
{
	CString strText;
	CComboBox *pComBox;

	pComBox = ((CComboBox *)GetDlgItem(IDC_COMBO1));//表结构是否初始化//
	pComBox->ResetContent();
	pComBox->AddString(_T("未使用"));
	pComBox->AddString(_T("已使用"));
	pComBox->AddString(_T("全部"));
	pComBox->SetCurSel(0);
	
	int i = 0;
	pComBox = ((CComboBox *)GetDlgItem(IDC_COMBO4));//行属性是否可变//
	pComBox->ResetContent();
	for(i = ModeRow_NoChange;i<=ModeRow_Change;i++)
	{
		strText.Format(_T("%s"), g_ModeRowVal[i]);
		pComBox->AddString(strText);
	}
	pComBox->AddString(_T("全部"));
	pComBox->SetCurSel(0);
	
}
void CModeSearch::DisplaySearchInfo()
{
	CString strText;
	StBasMode *pModeSearchInfo = &m_ModeSearchInfo;

	//1.模板名称
	strText.Format(_T("%s"), pModeSearchInfo->szModeName);
	((CEdit*)GetDlgItem(IDC_SHOWMODEINFO_NAME_EDT))->SetWindowText(strText);

	//2.产品代号
	strText.Format(_T("%s"), pModeSearchInfo->stProductInfo.szProductNo);
	((CEdit*)GetDlgItem(IDC_SHOWMODEINFO_PRODID_EDT))->SetWindowText(strText);


	//3.产品型号
	strText.Format(_T("%s"), pModeSearchInfo->szModel);
	((CEdit*)GetDlgItem(IDC_SHOWMODEINFO_PRODMODEL_EDT))->SetWindowText(strText);

	//4.产品阶段
	strText.Format(_T("%s"), pModeSearchInfo->szPhase);
	((CEdit*)GetDlgItem(IDC_SHOWMODEINFO_PRODPHASE_EDT))->SetWindowText(strText);
	//5.创建人
	strText.Format(_T("%s"), pModeSearchInfo->szCreateUser);
	((CEdit*)GetDlgItem(IDC_SHOWMODEINFO_BUILDUSR_EDT))->SetWindowText(strText);


	//6.创建开始时间
	strText.Format(_T("%s"), pModeSearchInfo->szCreateBeginTime);
	((CEdit*)GetDlgItem(IDC_MODE_CREATE_BGNTIME_EDT))->SetWindowText(strText);
	//7.创建结束时间
	strText.Format(_T("%s"), pModeSearchInfo->szCreateEndTime);
	((CEdit*)GetDlgItem(IDC_MODE_CREATE_ENDTIME_EDT))->SetWindowText(strText);


	 //8.通用模板
	int i = 0;
	if(pModeSearchInfo->bModeCurrency >= 1)
	{
		i = 1;
	}else
	{
		i = 0;
	}
	((CButton *)GetDlgItem(IDC_CHECK1))->SetCheck(i);

	//9.产品专用 
	if(pModeSearchInfo->bModeDedicated >= 1)
	{
		i = 1;
	}else
	{
		i = 0;
	}
	((CButton *)GetDlgItem(IDC_CHECK2))->SetCheck(i);

	//10.线缆专用
	if(pModeSearchInfo->bModeLineDed >= 1)
	{
		i = 1;
	}else
	{
		i = 0;
	}
	((CButton *)GetDlgItem(IDC_CHECK3))->SetCheck(i);

	//11.未启用
	if(pModeSearchInfo->bModeNotUse >= 1)
	{
		i = 1;
	}else
	{
		i = 0;
	}
	((CButton *)GetDlgItem(IDC_CHECK4))->SetCheck(i);


	//12.行不可变 
	int nModeRow = pModeSearchInfo->nModeRowVar;
	if(nModeRow < 0 || nModeRow > ModeRow_All)
	{
		pModeSearchInfo->nModeRowVar = nModeRow = ModeRow_All;
		
	}
	CComboBox *pComBox;
	pComBox = ((CComboBox *)GetDlgItem(IDC_COMBO4));//行属性是否可变//
	pComBox->SetCurSel(nModeRow);

	
	////12.行不可变 
	//if(pModeSearchInfo->bModeRowNoChange >= 1)
	//{
	//	i = 1;
	//}else
	//{
	//	i = 0;
	//}
	//((CButton *)GetDlgItem(IDC_CHECK5))->SetCheck(i);

	////13.行可变  
	//if(pModeSearchInfo->bModeRowChange >= 1)
	//{
	//	i = 1;
	//}else
	//{
	//	i = 0;
	//}
	//((CButton *)GetDlgItem(IDC_CHECK7))->SetCheck(i);


	//14.已初始化表结构
	int nInitModeTab = pModeSearchInfo->nInitTabSrt;
	pComBox = ((CComboBox *)GetDlgItem(IDC_COMBO1));//表结构是否初始化//
	if(nInitModeTab < ModeTab_UnInit || nInitModeTab > ModeTab_All)
	{
		pModeSearchInfo->nInitTabSrt = nInitModeTab = ModeTab_All;
	}
	pComBox->SetCurSel(nInitModeTab);


	////14.已初始化表结构
	//if(pModeSearchInfo->bInitedTabSrt >= 1)
	//{
	//	i = 1;
	//}else
	//{
	//	i = 0;
	//}
	//((CButton *)GetDlgItem(IDC_CHECK8))->SetCheck(i);

	////15.未初始化表结构
	//if(pModeSearchInfo->bUnInitTabStr >= 1)
	//{
	//	i = 1;
	//}else
	//{
	//	i = 0;
	//}
	//((CButton *)GetDlgItem(IDC_CHECK9))->SetCheck(i);


}
void CModeSearch::GetSearchInfo()
{

	CString strText;
	StBasMode *pModeSearchInfo = &m_ModeSearchInfo;
	//1.模板名称
	((CEdit*)GetDlgItem(IDC_SHOWMODEINFO_NAME_EDT))->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(pModeSearchInfo->szModeName,0,sizeof(pModeSearchInfo->szModeName));
	strcpy(pModeSearchInfo->szModeName,strText);
	//2.产品代号
	((CEdit*)GetDlgItem(IDC_SHOWMODEINFO_PRODID_EDT))->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(pModeSearchInfo->stProductInfo.szProductNo,0,sizeof(pModeSearchInfo->stProductInfo.szProductNo));
	strcpy(pModeSearchInfo->stProductInfo.szProductNo,strText);
	//3.产品型号
	((CEdit*)GetDlgItem(IDC_SHOWMODEINFO_PRODMODEL_EDT))->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(pModeSearchInfo->szModel,0,sizeof(pModeSearchInfo->szModel));
	strcpy(pModeSearchInfo->szModel,strText);
	//4.产品阶段
	((CEdit*)GetDlgItem(IDC_SHOWMODEINFO_PRODPHASE_EDT))->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(pModeSearchInfo->szPhase,0,sizeof(pModeSearchInfo->szPhase));
	strcpy(pModeSearchInfo->szPhase,strText);

	//5.创建人
	((CEdit*)GetDlgItem(IDC_SHOWMODEINFO_BUILDUSR_EDT))->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(pModeSearchInfo->szCreateUser,0,sizeof(pModeSearchInfo->szCreateUser));
	strcpy(pModeSearchInfo->szCreateUser,strText);


	//6.创建开始时间
	((CEdit*)GetDlgItem(IDC_MODE_CREATE_BGNTIME_EDT))->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(pModeSearchInfo->szCreateBeginTime,0,sizeof(pModeSearchInfo->szCreateBeginTime));
	strcpy(pModeSearchInfo->szCreateBeginTime,strText);
	//7.创建结束时间
	((CEdit*)GetDlgItem(IDC_MODE_CREATE_ENDTIME_EDT))->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	memset(pModeSearchInfo->szCreateEndTime,0,sizeof(pModeSearchInfo->szCreateEndTime));
	strcpy(pModeSearchInfo->szCreateEndTime,strText);


	//8.通用模板
	int i = 0;
	i = ((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck();
	pModeSearchInfo->bModeCurrency = i;

	//9.产品专用 
	i = ((CButton *)GetDlgItem(IDC_CHECK2))->GetCheck();
	pModeSearchInfo->bModeDedicated = i;

	//10.线缆专用
	i = ((CButton *)GetDlgItem(IDC_CHECK3))->GetCheck();
	pModeSearchInfo->bModeLineDed = i;

	//11.未启用
	i = ((CButton *)GetDlgItem(IDC_CHECK4))->GetCheck();
	pModeSearchInfo->bModeNotUse = i;


	CComboBox *pComBox;
	int nInitModeTab;
	pComBox = ((CComboBox *)GetDlgItem(IDC_COMBO1));//表结构是否初始化//
	nInitModeTab = pComBox->GetCurSel();
	if(nInitModeTab < ModeTab_UnInit || nInitModeTab > ModeTab_All)
	{
		pModeSearchInfo->nInitTabSrt = nInitModeTab = ModeTab_All;
	}
	
	switch(nInitModeTab)
	{
	case ModeTab_UnInit:
		{
			pModeSearchInfo->bUnInitTabStr = Sel_Check;
			pModeSearchInfo->bInitedTabSrt = UnSel_Check;
		}
		break;
	case ModeTab_Init:
		{
			pModeSearchInfo->bUnInitTabStr = UnSel_Check;
			pModeSearchInfo->bInitedTabSrt = Sel_Check;
		}
		break;
	case ModeTab_All:
		{
			pModeSearchInfo->bUnInitTabStr = Sel_Check;
			pModeSearchInfo->bInitedTabSrt = Sel_Check;
		}
		break;
	}

	pComBox = ((CComboBox *)GetDlgItem(IDC_COMBO4));//行属性是否可变//
	int nModeRow = pComBox->GetCurSel();
	if(nModeRow < ModeRow_NoChange || nModeRow > ModeRow_All)
	{
		pModeSearchInfo->nModeRowVar = nModeRow = ModeRow_All;

	}

	switch(nModeRow)
	{
	case ModeRow_NoChange:
		{
			pModeSearchInfo->bModeRowChange = UnSel_Check;
			pModeSearchInfo->bModeRowNoChange = Sel_Check;
		}
		break;
	case ModeRow_Change:
		{
			pModeSearchInfo->bModeRowChange = Sel_Check;
			pModeSearchInfo->bModeRowNoChange = UnSel_Check;
		}
		break;
	case ModeRow_All:
		{
			pModeSearchInfo->bModeRowChange = Sel_Check;
			pModeSearchInfo->bModeRowNoChange = Sel_Check;
		}
		break;
	}


	////12.行不可变 
	//i = ((CButton *)GetDlgItem(IDC_CHECK5))->GetCheck();
	//pModeSearchInfo->bModeRowNoChange = i;


	////13.行可变  
	//i = ((CButton *)GetDlgItem(IDC_CHECK7))->GetCheck();
	//pModeSearchInfo->bModeRowChange = i;


	////14.已初始化表结构
	//i = ((CButton *)GetDlgItem(IDC_CHECK8))->GetCheck();
	//pModeSearchInfo->bInitedTabSrt = i;

	////15.未初始化表结构
	//i = ((CButton *)GetDlgItem(IDC_CHECK9))->GetCheck();
	//pModeSearchInfo->bUnInitTabStr = i;

}

void CModeSearch::OnBnClickedSearchBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	GetSearchInfo();

	g_pShowInfoList->m_ResultList.GetPageNumComBox();
	StSearchSetInfo *pSearchSetInfo = &g_pShowInfoList->m_ResultList.m_stSearchSetInfo;
	m_ModeSearchInfo.nPerPageNum = pSearchSetInfo->nPerPageNum;
	//m_ModeSearchInfo.nCurPage = 1;
	m_ModeSearchInfo.nCurPage = pSearchSetInfo->nAimPage;

	if(m_ModeSearchInfo.nCurPage <= 0)
	{
		m_ModeSearchInfo.nCurPage = 1;
	}

	g_pShowInfoList->DisplayModeInfo(&m_ModeSearchInfo);


}
//选择创建人//
void CModeSearch::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CSelUserDlg Dlg;
	CString strUserName;
	if(Dlg.DoModal() == IDOK)
	{
		strUserName = Dlg.m_SelUserName;
		GetDlgItem(IDC_SHOWMODEINFO_BUILDUSR_EDT)->SetWindowText(strUserName);
	}
}
//选择创建开始时间//
void CModeSearch::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CSelDate Dlg;
	CString strBeginDate;
	SYSTEMTIME *pstTime = NULL;
	if(Dlg.DoModal() == IDOK)
	{
		pstTime = &Dlg.m_stTime;
		strBeginDate.Format(_T("%04d-%02d-%02d"),pstTime->wYear,pstTime->wMonth,pstTime->wDay);
		GetDlgItem(IDC_MODE_CREATE_BGNTIME_EDT)->SetWindowText(strBeginDate);
	}
}
//选择创建结束时间//
void CModeSearch::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CSelDate Dlg;
	CString strBeginDate;
	SYSTEMTIME *pstTime = NULL;
	if(Dlg.DoModal() == IDOK)
	{
		pstTime = &Dlg.m_stTime;
		strBeginDate.Format(_T("%04d-%02d-%02d"),pstTime->wYear,pstTime->wMonth,pstTime->wDay);
		GetDlgItem(IDC_MODE_CREATE_ENDTIME_EDT)->SetWindowText(strBeginDate);
	}
}

void CModeSearch::OnBnClickedSelProdBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	CSelProductDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		GetDlgItem(IDC_SHOWMODEINFO_PRODID_EDT)->SetWindowText(dlg.m_strProductNo);
	}
}
