#pragma once
#include "mylistctrl\editablelistctrl.h"


// CAdjustmentDlg 对话框

class CAdjustmentDlg : public CDialog
{
	DECLARE_DYNAMIC(CAdjustmentDlg)

public:
	CAdjustmentDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAdjustmentDlg();

// 对话框数据
	enum { IDD = IDD_ADJUSTMENT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEditableListCtrl m_List;
	int             m_CreateType;
	StTstResultAtta *m_pStCreateReportAtta;
	vector<StTstResultAtta> m_ResultAttaArray;
	vector<StTstResultAtta> m_CreateReportArray;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	virtual BOOL OnInitDialog();
	void        DisPlayResultAttach();
	void        InseartAttachToList(StTstResultAtta *pTstResultAtta);
	void        AutoSize();
protected:
	virtual void OnOK();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
