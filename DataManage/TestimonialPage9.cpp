// TestimonialPage9.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataManage.h"
#include "TestimonialPage9.h"
#include "ModeXmlStruct.h"

// CTestimonialPage9 �Ի���

IMPLEMENT_DYNAMIC(CTestimonialPage9, CDialog)

CTestimonialPage9::CTestimonialPage9(CWnd* pParent /*=NULL*/)
	: CDialog(CTestimonialPage9::IDD, pParent)
{

	m_pGrid = NULL;
}

CTestimonialPage9::~CTestimonialPage9()
{
	if(m_pGrid != NULL)
	{
		delete m_pGrid;
	}
}

void CTestimonialPage9::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTestimonialPage9, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CTestimonialPage9 ��Ϣ�������

BOOL CTestimonialPage9::OnInitDialog()
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

void CTestimonialPage9::DispalyPageInfo()
{
	StBasTestimonialPage9 *pPage9Info = m_pPage9Info;
	vector<StBasPage9ConnectTeleTime> *stConnectTele = &pPage9Info->stTstConnectTele;
	int i, pos, nRow;

	int nBegrow;
	CString str;
	str.Format(_T("%s"), pPage9Info->szTitle);
	GetDlgItem(IDC_STATIC1)->SetWindowText(str);

	DispalyModeStyle();

	//1.�豸�嵥//
	nBegrow = 3;
	nRow = stConnectTele->size();
	for (i = nBegrow;i< nRow+nBegrow; i++)
	{
		pos = 2;
		m_pGrid->SetItemText(i, pos++,stConnectTele->at(i-nBegrow).szBegEndTime);
		m_pGrid->SetItemText(i, pos++,stConnectTele->at(i-nBegrow).szTemp);
		m_pGrid->SetItemText(i, pos++,stConnectTele->at(i-nBegrow).szHumidity);
		m_pGrid->SetItemText(i, pos++,stConnectTele->at(i-nBegrow).szWorkStatus);
		m_pGrid->SetItemText(i, pos++,stConnectTele->at(i-nBegrow).szThisConnTele);
		m_pGrid->SetItemText(i, pos++,stConnectTele->at(i-nBegrow).szHisConnTele);
		m_pGrid->SetItemText(i, pos++,stConnectTele->at(i-nBegrow).szOperUser);
		m_pGrid->SetItemText(i, pos++,stConnectTele->at(i-nBegrow).szCheckUser);
	}
}
void CTestimonialPage9::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialog::OnOK();
}

void CTestimonialPage9::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	AutoSize();
}

void CTestimonialPage9::AutoSize()
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

void CTestimonialPage9::DispalyModeStyle()
{
	//�����ļ���  ָ��·��//
	CString str1, str2;
	str1.Format(_T("%s\\%s\\%s"), g_WorkPath, Report_Mode_Path, _T("TestimonialPage9.txt"));

	str2.Format(_T("%s\\%s\\%s"), g_WorkPath, PATH_XML_MODE_PAR_CFG, MD_XML_FILE_TAB_SRT_INFO);

	CopyFile(str1,str2,0);
	m_pModeParMng->ClearParamInfo();

	//1.��ȡģ��ṹ
	m_pModeXmlAnalysis->GetXmlMdTabSrtInfo();			
	m_pModeParMng->GetItemFlagFromData( );             //��ItemData��ȡItemFlag

	m_pGrid = InitGridCtrl_MUL(this,m_pModeParMng, m_pGrid);
	PostMessage(WM_SIZE);
}
