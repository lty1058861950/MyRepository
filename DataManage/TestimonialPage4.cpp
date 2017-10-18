// TestimonialPage4.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "TestimonialPage4.h"


// CTestimonialPage4 对话框

IMPLEMENT_DYNAMIC(CTestimonialPage4, CDialog)

CTestimonialPage4::CTestimonialPage4(CWnd* pParent /*=NULL*/)
	: CDialog(CTestimonialPage4::IDD, pParent)
{
	m_ShowType = Page4_Type2;
}

CTestimonialPage4::~CTestimonialPage4()
{
}

void CTestimonialPage4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTestimonialPage4, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CTestimonialPage4 消息处理程序

BOOL CTestimonialPage4::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_Font1.CreateFont(32,0,0,0,FW_SEMIBOLD,0,0,0,134,3,2,1,2,_T("Arial"));	//大标题
	m_Font2.CreateFont(18,0,0,0,FW_SEMIBOLD,0,0,0,134,3,2,1,2,_T("宋体"));	//页数
	m_Font3.CreateFont(16,0,0,0,0,0,0,0,134,3,2,1,2,_T("宋体"));	//数据项

	GetDlgItem(IDC_STATIC1)->SetFont(&m_Font2);
	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CTestimonialPage4::DispalyPageInfo()
{
	StBasTestimonialPage4 *pPage4Info = m_pPage4Info;
	CString str;
	str.Format(_T("%s"), pPage4Info->szTitle);
	GetDlgItem(IDC_STATIC1)->SetWindowText(str);
}
BOOL CTestimonialPage4::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	StBasTestimonialPage4 *pPage4Info = m_pPage4Info;
	CDC *pDc = GetDC();

	int i, nCount;
	int nNum1 = 3; 
	CRect rcRect;
	GetClientRect(&rcRect);
	//ScreenToClient(&rcRect);
	if(pPage4Info->nShowType == Page4_Type1)
	{
		nNum1 = 3;
	}else if(pPage4Info->nShowType == Page4_Type2)
	{
		nNum1 = 4;
	}else if(pPage4Info->nShowType == Page4_Type3)
	{
		nNum1 = 4;
	}
	/*CString str;

	str.Format(_T("%d"), pPage4Info->nShowType);
	GetDlgItem(IDC_STATIC1)->SetWindowText(str);*/
	rcRect.left = rcRect.left+50;
	rcRect.right = rcRect.right-30;
	rcRect.top = rcRect.top+50;
	rcRect.bottom = rcRect.bottom-50;

	int nNum = rcRect.Height()%nNum1;
	if(nNum >0)
	{
		rcRect.bottom = rcRect.bottom-nNum;
	}

	CPen  pen(PS_SOLID, 1, RGB(0, 0, 0));
	pDc->SelectObject(&pen);

	pDc->MoveTo(rcRect.left, rcRect.top);
	pDc->LineTo(rcRect.left, rcRect.bottom);
	pDc->LineTo(rcRect.right, rcRect.bottom);
	pDc->LineTo(rcRect.right, rcRect.top);
	pDc->LineTo(rcRect.left, rcRect.top);

	int nCellHeight = rcRect.Height()/nNum1;
	nCount = nNum1;
	for (i = 0;i<nCount-1;i++)
	{
		pDc->MoveTo(rcRect.left, rcRect.top+(nCellHeight)*(i+2));
		pDc->LineTo(rcRect.right, rcRect.top+(nCellHeight)*(i+2));
	}

	if(pPage4Info->nShowType == Page4_Type1)
	{
		
	}else if(pPage4Info->nShowType == Page4_Type2)
	{

	}else if(pPage4Info->nShowType == Page4_Type3)
	{

	}
	//pDc->Rectangle(&rcRect);

	ReleaseDC(pDC);
	return TRUE;
	//return CDialog::OnEraseBkgnd(pDC);
}

void CTestimonialPage4::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnOK();
}

void CTestimonialPage4::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	AutoSize();
}

void CTestimonialPage4::AutoSize()
{
	CString str;
	CRect Rect ;
	GetClientRect(&Rect) ;


	int nBtnWidth = 80;
	int nBtnHeight = 30;


	int nStaticWidth = Rect.Width()-(100*2);
	int nLeftpos = (Rect.Width()/2- nStaticWidth/2);


	if(GetDlgItem(IDC_STATIC1)->GetSafeHwnd())
	{
		GetDlgItem(IDC_STATIC1)->MoveWindow(nLeftpos, 5+10, nStaticWidth, 30);
	}

}
