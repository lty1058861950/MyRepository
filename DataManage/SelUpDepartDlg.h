#pragma once
#include "mylistctrl\editablelistctrl.h"


// CSelUpDepartDlg 对话框

class CSelUpDepartDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelUpDepartDlg)

public:
	CSelUpDepartDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSelUpDepartDlg();

// 对话框数据
	enum { IDD = IDD_SEL_UPDEPART_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEditableListCtrl m_DepartList;
	CString  m_UpDepartName;
	virtual BOOL OnInitDialog();
	void    DisplayUpDepartList();
	void    InsertUpDepartToList(StHrUpDepart *pUpDepartInfo);
protected:
	virtual void OnOK();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
};
