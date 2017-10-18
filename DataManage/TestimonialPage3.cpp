// TestimonialPage3.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataManage.h"
#include "TestimonialPage3.h"


// CTestimonialPage3 �Ի���

IMPLEMENT_DYNAMIC(CTestimonialPage3, CDialog)

CTestimonialPage3::CTestimonialPage3(CWnd* pParent /*=NULL*/)
	: CDialog(CTestimonialPage3::IDD, pParent)
{

}

CTestimonialPage3::~CTestimonialPage3()
{
}

void CTestimonialPage3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTestimonialPage3, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CTestimonialPage3 ��Ϣ�������

BOOL CTestimonialPage3::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_Font1.CreateFont(32,0,0,0,FW_SEMIBOLD,0,0,0,134,3,2,1,2,_T("Arial"));	//�����
	m_Font2.CreateFont(18,0,0,0,FW_SEMIBOLD,0,0,0,134,3,2,1,2,_T("����"));	//ҳ��
	m_Font3.CreateFont(16,0,0,0,0,0,0,0,134,3,2,1,2,_T("����"));	//������

	GetDlgItem(IDC_STATIC1)->SetFont(&m_Font2);

	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CTestimonialPage3::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialog::OnOK();
}

void CTestimonialPage3::DispalyPageInfo()
{
	StBasTestimonialPage3 *pPage3Info = m_pPage3Info;
	CString str;
	str.Format(_T("%s"), pPage3Info->szTitle);
	GetDlgItem(IDC_STATIC1)->SetWindowText(str);

}
BOOL CTestimonialPage3::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDC *pDc = GetDC();
	StBasTestimonialPage3 *pPage3Info = m_pPage3Info;
	int i,nCount = pPage3Info->nCount;

	CRect rcRect;
	CString str;
	GetClientRect(&rcRect);
	////
	int nWidth1 = 50, nWidth3 = 80;

	//ScreenToClient(&rcRect);

	rcRect.left = rcRect.left+50;
	rcRect.right = rcRect.right-30;
	rcRect.top = rcRect.top+50;
	rcRect.bottom = rcRect.bottom-50;

	if(nCount<=12)
	{
		nCount = 12;
	}

	int nNum = rcRect.Height()%(nCount+1);
	if(nNum>0)
	{
		rcRect.bottom = rcRect.bottom-nNum;
	}

	//CBrush  rcBrush(RGB(255, 255, 255));
	CPen  pen(PS_SOLID, 1, RGB(0, 0, 0));
	pDc->SelectObject(&pen);
	pDc->SelectObject(&m_Font2);
	//pDc->SelectObject(&rcBrush);

	pDc->MoveTo(rcRect.left, rcRect.top);
	pDc->LineTo(rcRect.left, rcRect.bottom);
	pDc->LineTo(rcRect.right, rcRect.bottom);
	pDc->LineTo(rcRect.right, rcRect.top);
	pDc->LineTo(rcRect.left, rcRect.top);

	int nLpos = rcRect.left+nWidth1;
	int nRpos = rcRect.right-nWidth3;
	pDc->MoveTo(nLpos, rcRect.top);
	pDc->LineTo(nLpos, rcRect.bottom);
	pDc->MoveTo(nRpos, rcRect.top);
	pDc->LineTo(nRpos, rcRect.bottom);

	SetBkMode(pDc->m_hDC, TRANSPARENT);//�������屳��͸��//

	int nCellHeight = rcRect.Height()/(nCount+1);
	int nBpos;

	//���//
	str.Format(_T("���"));
	DrawText(pDc->m_hDC, str, str.GetLength(), 
		&CRect(rcRect.left, rcRect.top, rcRect.left+nWidth1, rcRect.top+nCellHeight),
		DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS );

	//����//
	str.Format(_T("��                ��"));
	DrawText(pDc->m_hDC, str, str.GetLength(), 
		&CRect(rcRect.left+nWidth1, rcRect.top, rcRect.right-nWidth3, rcRect.top+nCellHeight),
		DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS );
	//ҳ��//
	str.Format(_T("ҳ��"));
	DrawText(pDc->m_hDC, str, str.GetLength(), 
		&CRect(rcRect.right-nWidth3, rcRect.top, rcRect.right, rcRect.top+nCellHeight),
		DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS );

	
	

	for (i = 0;i<nCount;i++)
	{
		nBpos = rcRect.top+nCellHeight*(i+1);
		pDc->MoveTo(rcRect.left, nBpos);
		pDc->LineTo(rcRect.right, nBpos);

		str.Format(_T("%d"), i+1);
		DrawText(pDc->m_hDC, str, str.GetLength(), 
			&CRect(rcRect.left, nBpos, rcRect.left+nWidth1, nBpos+nCellHeight),
			DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS );

		DrawText(pDc->m_hDC, pPage3Info->szRules[i], strlen(pPage3Info->szRules[i]), 
			&CRect(rcRect.left+nWidth1+5, nBpos, rcRect.right-nWidth3, nBpos+nCellHeight),
			DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS );

		//ҳ��//
		str.Format(_T("%d"), pPage3Info->nPageNums[i]);
		DrawText(pDc->m_hDC, str, str.GetLength(), 
			&CRect(rcRect.right-nWidth3, nBpos, rcRect.right, nBpos+nCellHeight),
			DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS );
	}
	
	//pDc->Rectangle(&rcRect);

	ReleaseDC(pDC);

	return TRUE;
	//return CDialog::OnEraseBkgnd(pDC);
}

void CTestimonialPage3::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	AutoSize();
}
void CTestimonialPage3::AutoSize()
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