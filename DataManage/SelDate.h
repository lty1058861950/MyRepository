#pragma once
#include "afxdtctl.h"


// CSelDate 对话框

class CSelDate : public CDialog
{
	DECLARE_DYNAMIC(CSelDate)

public:
	CSelDate(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSelDate();

// 对话框数据
	enum { IDD = IDD_SEL_DATE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	SYSTEMTIME m_stTime;
	CMonthCalCtrl m_SelDate;
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMcnSelchangeMonthcalendarDate(NMHDR *pNMHDR, LRESULT *pResult);
};
