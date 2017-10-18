// TestimonialPage11.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataManage.h"
#include "TestimonialPage11.h"
#include "ModeXmlStruct.h"

// CTestimonialPage11 �Ի���

IMPLEMENT_DYNAMIC(CTestimonialPage11, CDialog)

CTestimonialPage11::CTestimonialPage11(CWnd* pParent /*=NULL*/)
	: CDialog(CTestimonialPage11::IDD, pParent)
{
	m_pGrid = NULL;
}

CTestimonialPage11::~CTestimonialPage11()
{
	if(m_pGrid != NULL)
	{
		delete m_pGrid;
	}
}

void CTestimonialPage11::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTestimonialPage11, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CTestimonialPage11 ��Ϣ�������

BOOL CTestimonialPage11::OnInitDialog()
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

void CTestimonialPage11::DispalyPageInfo()
{
	StBasTestimonialPage11 *pPage11Info = m_pPage11Info;
	vector<StBasPage11SpecialRecord> *stTstSpecialRecord = &pPage11Info->stTstSpecialRecord;
	int i, pos, nRow;

	int nBegrow;
	CString str;
	str.Format(_T("%s"), pPage11Info->szTitle);
	GetDlgItem(IDC_STATIC1)->SetWindowText(str);

	DispalyModeStyle();

	//1.�豸�嵥//
	nBegrow = 3;
	nRow = stTstSpecialRecord->size();
	for (i = nBegrow;i< nRow+nBegrow; i++)
	{
		pos = 2;
		m_pGrid->SetItemText(i, pos++,stTstSpecialRecord->at(i-nBegrow).szRecordText);
		m_pGrid->SetItemText(i, pos++,stTstSpecialRecord->at(i-nBegrow).szUnit);
		m_pGrid->SetItemText(i, pos++,stTstSpecialRecord->at(i-nBegrow).szUser);
		m_pGrid->SetItemText(i, pos++,stTstSpecialRecord->at(i-nBegrow).szDate);
	}
}

void CTestimonialPage11::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialog::OnOK();
}

void CTestimonialPage11::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	AutoSize();
}

void CTestimonialPage11::AutoSize()
{
	CString str;
	CRect Rect ;
	GetClientRect(&Rect) ;
	ScreenToClient(&Rect);


	int nBtnWidth = 80;
	int nBtnHeight = 30;


	int nStaticWidth = Rect.Width()-(100*2);
	int nLeftpos = (Rect.Width()/2- nStaticWidth/2);


	if(GetDlgItem(IDC_STATIC1)->GetSafeHwnd())
	{
		GetDlgItem(IDC_STATIC1)->MoveWindow(nLeftpos, 5+10, nStaticWidth, 30);
	}

	if(m_pGrid->GetSafeHwnd())
	{
		m_pGrid->MoveWindow(5, 5+10+40, Rect.Width()-(5*2), Rect.Height()-(5+10+40+10));
	}
}

void CTestimonialPage11::DispalyModeStyle()
{
	//�����ļ���  ָ��·��//
	CString str1, str2;
	str1.Format(_T("%s\\%s\\%s"), g_WorkPath, Report_Mode_Path, _T("TestimonialPage11.txt"));

	str2.Format(_T("%s\\%s\\%s"), g_WorkPath, PATH_XML_MODE_PAR_CFG, MD_XML_FILE_TAB_SRT_INFO);

	CopyFile(str1,str2,0);
	m_pModeParMng->ClearParamInfo();

	//1.��ȡģ��ṹ
	m_pModeXmlAnalysis->GetXmlMdTabSrtInfo();			
	m_pModeParMng->GetItemFlagFromData( );             //��ItemData��ȡItemFlag

	m_pGrid = InitGridCtrl_MUL(this,m_pModeParMng, m_pGrid);
	PostMessage(WM_SIZE);
}
