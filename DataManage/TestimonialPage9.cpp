// TestimonialPage9.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "TestimonialPage9.h"
#include "ModeXmlStruct.h"

// CTestimonialPage9 对话框

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


// CTestimonialPage9 消息处理程序

BOOL CTestimonialPage9::OnInitDialog()
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

	//1.设备清单//
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
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnOK();
}

void CTestimonialPage9::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
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
	//拷贝文件到  指定路径//
	CString str1, str2;
	str1.Format(_T("%s\\%s\\%s"), g_WorkPath, Report_Mode_Path, _T("TestimonialPage9.txt"));

	str2.Format(_T("%s\\%s\\%s"), g_WorkPath, PATH_XML_MODE_PAR_CFG, MD_XML_FILE_TAB_SRT_INFO);

	CopyFile(str1,str2,0);
	m_pModeParMng->ClearParamInfo();

	//1.获取模板结构
	m_pModeXmlAnalysis->GetXmlMdTabSrtInfo();			
	m_pModeParMng->GetItemFlagFromData( );             //从ItemData获取ItemFlag

	m_pGrid = InitGridCtrl_MUL(this,m_pModeParMng, m_pGrid);
	PostMessage(WM_SIZE);
}
