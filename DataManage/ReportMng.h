#pragma once
//#include "tempactivexoctrl1.h"


// CReportMng 对话框

class CReportMng : public CDialog
{
	DECLARE_DYNAMIC(CReportMng)

public:
	CReportMng(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CReportMng();

// 对话框数据
	enum { IDD = IDD_REPORT_MNG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//CTempactivexoctrl1 m_Report;
	afx_msg void OnBnClickedBuildReportBtn();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
};
