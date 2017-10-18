// TestimonialPage2.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "TestimonialPage2.h"


// CTestimonialPage2 对话框

IMPLEMENT_DYNAMIC(CTestimonialPage2, CDialog)

CTestimonialPage2::CTestimonialPage2(CWnd* pParent /*=NULL*/)
	: CDialog(CTestimonialPage2::IDD, pParent)
{

}

CTestimonialPage2::~CTestimonialPage2()
{
}

void CTestimonialPage2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTestimonialPage2, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CTestimonialPage2 消息处理程序

BOOL CTestimonialPage2::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_Font1.CreateFont(32,0,0,0,FW_SEMIBOLD,0,0,0,134,3,2,1,2,_T("Arial"));	//大标题
	m_Font2.CreateFont(18,0,0,0,FW_SEMIBOLD,0,0,0,134,3,2,1,2,_T("宋体"));	//页数
	m_Font3.CreateFont(16,0,0,0,0,0,0,0,134,3,2,1,2,_T("宋体"));	//数据项

	GetDlgItem(IDC_STATIC1)->SetFont(&m_Font2);
	GetDlgItem(IDC_STATIC2)->SetFont(&m_Font3);

	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CTestimonialPage2::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnOK();
}

void CTestimonialPage2::DispalyPageInfo()
{
	StBasTestimonialPage2 *pPage2Info = m_pPage2Info;
	CString str, str1;
	int i, nCount;
	str.Format(_T("%s"), pPage2Info->szTitle);
	GetDlgItem(IDC_STATIC1)->SetWindowText(str);

	str = _T("");
	nCount = pPage2Info->nCount;
	for (i = 0;i<nCount;i++)
	{
		str1.Format(_T("%d.%s\n\n"),i+1, pPage2Info->szRules[i]);
		str+=str1;
	}
	GetDlgItem(IDC_STATIC2)->SetWindowText(str);

}
BOOL CTestimonialPage2::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDC *pDc = GetDC();

	CRect rcRect;
	GetClientRect(&rcRect);
	//ScreenToClient(&rcRect);

	rcRect.left = rcRect.left+50;
	rcRect.right = rcRect.right-30;
	rcRect.top = rcRect.top+50;
	rcRect.bottom = rcRect.bottom-50;

	CPen  pen(PS_SOLID, 1, RGB(0, 0, 0));
	pDc->SelectObject(&pen);

	pDc->MoveTo(rcRect.left, rcRect.top);
	pDc->LineTo(rcRect.left, rcRect.bottom);
	pDc->LineTo(rcRect.right, rcRect.bottom);
	pDc->LineTo(rcRect.right, rcRect.top);
	pDc->LineTo(rcRect.left, rcRect.top);

	/*DrawText(hDC, strText, strText.GetLength(), 
	&CRect(rcItem.left + m_nPaddingLeft, rcItem.top, rcItem.right, rcItem.bottom),
	DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS );
	DrawText(pDc->m_hDC,)*/
	//pDc->Rectangle(&rcRect);

	ReleaseDC(pDC);
	return TRUE;
	return CDialog::OnEraseBkgnd(pDC);
}

void CTestimonialPage2::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: 在此处添加消息处理程序代码
	AutoSize();
}
void CTestimonialPage2::AutoSize()
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
		GetDlgItem(IDC_STATIC1)->MoveWindow(nLeftpos, 5+100, nStaticWidth, 30);
	}
	

	if(GetDlgItem(IDC_STATIC2)->GetSafeHwnd())
	{
		GetDlgItem(IDC_STATIC2)->MoveWindow(nLeftpos, 5+100+50, nStaticWidth, Rect.Height()-(5+100+50+50+50));
	}


}
