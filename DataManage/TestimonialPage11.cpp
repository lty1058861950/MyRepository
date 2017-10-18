// TestimonialPage11.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "TestimonialPage11.h"
#include "ModeXmlStruct.h"

// CTestimonialPage11 对话框

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


// CTestimonialPage11 消息处理程序

BOOL CTestimonialPage11::OnInitDialog()
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

	//1.设备清单//
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
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnOK();
}

void CTestimonialPage11::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
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
	//拷贝文件到  指定路径//
	CString str1, str2;
	str1.Format(_T("%s\\%s\\%s"), g_WorkPath, Report_Mode_Path, _T("TestimonialPage11.txt"));

	str2.Format(_T("%s\\%s\\%s"), g_WorkPath, PATH_XML_MODE_PAR_CFG, MD_XML_FILE_TAB_SRT_INFO);

	CopyFile(str1,str2,0);
	m_pModeParMng->ClearParamInfo();

	//1.获取模板结构
	m_pModeXmlAnalysis->GetXmlMdTabSrtInfo();			
	m_pModeParMng->GetItemFlagFromData( );             //从ItemData获取ItemFlag

	m_pGrid = InitGridCtrl_MUL(this,m_pModeParMng, m_pGrid);
	PostMessage(WM_SIZE);
}
