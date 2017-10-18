// TestimonialPage1.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "TestimonialPage1.h"


// CTestimonialPage1 对话框

IMPLEMENT_DYNAMIC(CTestimonialPage1, CDialog)

CTestimonialPage1::CTestimonialPage1(CWnd* pParent /*=NULL*/)
	: CDialog(CTestimonialPage1::IDD, pParent)
{

}

CTestimonialPage1::~CTestimonialPage1()
{
}

void CTestimonialPage1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTestimonialPage1, CDialog)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CTestimonialPage1 消息处理程序

BOOL CTestimonialPage1::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_Font1.CreateFont(32,0,0,0,FW_SEMIBOLD,0,0,0,134,3,2,1,2,_T("Arial"));	//大标题
	m_Font2.CreateFont(18,0,0,0,0,0,0,0,134,3,2,1,2,_T("Arial"));	//页数
	m_Font3.CreateFont(18,0,0,0,FW_SEMIBOLD,0,0,0,134,3,2,1,2,_T("Arial"));	//数据项

	GetDlgItem(IDC_STATIC1)->SetFont(&m_Font1);
	GetDlgItem(IDC_STATIC2)->SetFont(&m_Font2);
	GetDlgItem(IDC_STATIC3)->SetFont(&m_Font3);
	GetDlgItem(IDC_STATIC4)->SetFont(&m_Font3);
	GetDlgItem(IDC_STATIC5)->SetFont(&m_Font3);
	GetDlgItem(IDC_STATIC6)->SetFont(&m_Font3);
	GetDlgItem(IDC_STATIC7)->SetFont(&m_Font3);
	GetDlgItem(IDC_STATIC8)->SetFont(&m_Font3);



	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CTestimonialPage1::DispalyPageInfo()
{
	StBasTestimonialPage1 *pPage1Info = m_pPage1Info;

	CString str;
	str.Format(_T("%s"), pPage1Info->szTitle);
	GetDlgItem(IDC_STATIC1)->SetWindowText(str);

	str.Format(_T("共  %d  页"), pPage1Info->nPageNum);
	GetDlgItem(IDC_STATIC2)->SetWindowText(str);
	
	str.Format(_T("产品代号：%s"), pPage1Info->szProductNo);
	GetDlgItem(IDC_STATIC3)->SetWindowText(str);
	
	str.Format(_T("产品名称：%s"), pPage1Info->szProductName);
	GetDlgItem(IDC_STATIC4)->SetWindowText(str);
	
	str.Format(_T("出厂编号：%s"), pPage1Info->szProductCode);
	GetDlgItem(IDC_STATIC5)->SetWindowText(str);
	
	str.Format(_T("研制阶段：%s"), pPage1Info->szPhase);
	GetDlgItem(IDC_STATIC6)->SetWindowText(str);
	
	str.Format(_T("生产单位：%s"), pPage1Info->szProductionUnit);
	GetDlgItem(IDC_STATIC7)->SetWindowText(str);
	
	str.Format(_T("出厂日期：%s"), pPage1Info->szLeaveFactoryDate);
	GetDlgItem(IDC_STATIC8)->SetWindowText(str);
}
void CTestimonialPage1::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnOK();
}

void CTestimonialPage1::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	AutoSize();
}

void CTestimonialPage1::AutoSize()
{
	CString str;
	CRect Rect ;
	GetClientRect(&Rect) ;

	int nxshu = 4;
	int nB5Width = 257;
	int nB5Height = 182;

	int nTreeWidth = 250;
	int nBtnWidth = 80;
	int nBtnHeight = 30;


}

BOOL CTestimonialPage1::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDC *pDc = GetDC();

	CBrush rcBrush(RGB(255, 255, 255));

	//CRect rcRect1;
	//GetClientRect(&rcRect1);
	//ScreenToClient(&rcRect1);
	//pDc->FillRect(&rcRect1,&rcBrush);

	CRect rcRect;
	GetClientRect(&rcRect);
	//ScreenToClient(&rcRect);

	rcRect.left = rcRect.left+50;
	rcRect.right = rcRect.right-30;
	rcRect.top = rcRect.top+50;
	rcRect.bottom = rcRect.bottom-50;

	CPen  pen(PS_SOLID, 2, RGB(0, 0, 0));
	pDc->SelectObject(&pen);

	pDc->MoveTo(rcRect.left, rcRect.top);
	pDc->LineTo(rcRect.left, rcRect.bottom);
	pDc->LineTo(rcRect.right, rcRect.bottom);
	pDc->LineTo(rcRect.right, rcRect.top);
	pDc->LineTo(rcRect.left, rcRect.top);
	//pDc->Rectangle(&rcRect);

	ReleaseDC(pDC);


	return TRUE;
	//return CDialog::OnEraseBkgnd(pDC);
}
