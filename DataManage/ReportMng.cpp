// ReportMng.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "ReportMng.h"
#include "WordSrc\\WordOptFun.h"


// CReportMng 对话框

IMPLEMENT_DYNAMIC(CReportMng, CDialog)

CReportMng::CReportMng(CWnd* pParent /*=NULL*/)
	: CDialog(CReportMng::IDD, pParent)
{

}

CReportMng::~CReportMng()
{
}

void CReportMng::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_TEMPACTIVEXOCTRL1, m_Report);
}


BEGIN_MESSAGE_MAP(CReportMng, CDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUILD_REPORT_BTN, &CReportMng::OnBnClickedBuildReportBtn)
	ON_BN_CLICKED(IDC_BUTTON2, &CReportMng::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CReportMng::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CReportMng::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CReportMng::OnBnClickedButton5)
END_MESSAGE_MAP()


// CReportMng 消息处理程序

BOOL CReportMng::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CReportMng::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}

void CReportMng::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnCancel();
}

void CReportMng::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
}

void CReportMng::OnBnClickedBuildReportBtn()
{
	//m_Report.SetTableData(_T("tab3-OID is not null"));
	//m_Test2.SetTableData(_T("Tab3-TASK_ID = '0000000001'"));
	//m_Test2.SetTableData(_T(" OID !=0"));
	/*if (m_Test2.CreateReport("389-12#吊分离力设备A1(D20131003-A1)_389-12#吊分离力设备A1(D20131003-A1).docx","C:","1","127.0.0.1","9000",tempdatabase1,NULL,NULL) == 1)
	{
		AfxMessageBox("报告生成完成");
	}*/
	//设备编号 保存目录 是否打开 IP地址
	/*if (m_Report.CreateReport("Test_11_10_Test_11_10.xml","C:","1","127.0.0.1","","",NULL,NULL) == 1)
	{
		AfxMessageBox("报告生成完成");
	}*/
}

void CReportMng::OnBnClickedButton2()
{
	CString str, strFileName;
	int		ret, tick1,tick2;
	tick1 = GetTickCount();

	strFileName = _T("C:\\tt2.doc");
	ret = WordOpt_MakeReportRowVarDemo( strFileName.GetBuffer(0) ); 

	tick2 = GetTickCount()-tick1;
	str.Format("用时%d毫秒! ret=%d, 输出文件：%s", tick2, ret, strFileName.GetBuffer(0)); 
	AfxMessageBox(str);	
}

void CReportMng::OnBnClickedButton3()
{
	CString str, strFileName, strDesFile;
	int		ret, tick1,tick2;
	tick1 = GetTickCount();

	strFileName = _T("c:\\Mode2.doc");
	strDesFile  = _T("c:\\t_Mode2.doc");

	ret = WordOpt_MakeTabModeToTabData(strFileName.GetBuffer(0), strDesFile.GetBuffer(0));

	tick2 = GetTickCount()-tick1;
	str.Format("用时%d毫秒! ret=%d, 输出文件：%s", tick2, ret, strDesFile.GetBuffer(0)); 
	AfxMessageBox(str);	
}

void CReportMng::OnBnClickedButton4()
{
	CString str, strFileName, strDesFile;
	int		ret, tick1,tick2;
	tick1 = GetTickCount();

	strDesFile  = _T("c:\\t_ModeInfo_2.doc");
	strFileName  = _T("c:\\t_Mode2.doc");

	ret = WordOpt_MakeReportTabInfoDemo(strDesFile.GetBuffer(0),strFileName.GetBuffer(0));

	tick2 = GetTickCount()-tick1;
	str.Format("用时%d毫秒! ret=%d, 输出文件：%s", tick2, ret, strDesFile.GetBuffer(0)); 
	AfxMessageBox(str);	
}

void CReportMng::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
}
