// SelDate.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "SelDate.h"


// CSelDate 对话框

IMPLEMENT_DYNAMIC(CSelDate, CDialog)

CSelDate::CSelDate(CWnd* pParent /*=NULL*/)
	: CDialog(CSelDate::IDD, pParent)
{

}

CSelDate::~CSelDate()
{
}

void CSelDate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MONTHCALENDAR_DATE, m_SelDate);
}


BEGIN_MESSAGE_MAP(CSelDate, CDialog)
	ON_WM_SIZE()
	ON_NOTIFY(MCN_SELCHANGE, IDC_MONTHCALENDAR_DATE, &CSelDate::OnMcnSelchangeMonthcalendarDate)
END_MESSAGE_MAP()


// CSelDate 消息处理程序

BOOL CSelDate::OnInitDialog()
{
	CDialog::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSelDate::OnOK()
{
	
	memset(&m_stTime,0,sizeof(SYSTEMTIME));
	m_SelDate.GetCurSel(&m_stTime);

	CDialog::OnOK();
}
void CSelDate::OnSize(UINT nType, int cx, int cy)
{
	CRect rcMinRect;
	if(m_SelDate.GetSafeHwnd())
	{
		m_SelDate.GetMinReqRect(&rcMinRect);
		m_SelDate.SizeMinReq();

		//MoveWindow(rcMinRect);
	}
	

	CDialog::OnSize(nType, cx, cy);

}

void CSelDate::OnMcnSelchangeMonthcalendarDate(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);
	
	*pResult = 0;
}
