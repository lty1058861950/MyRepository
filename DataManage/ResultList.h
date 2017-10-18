#pragma once
#include "mylistctrl\editablelistctrl.h"


// CResultList 对话框

class CResultSearchNew;
class CResultList : public CDialog
{
	DECLARE_DYNAMIC(CResultList)

public:
	CResultList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CResultList();

// 对话框数据
	enum { IDD = IDD_RESULT_LIST_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void     InitPageNumComBox();
	void     GetPageNumComBox();

	void     SetBtnStatus();
	void     AutoSize();
protected:
	virtual void OnOK();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CEditableListCtrl m_ResultList;
	int  m_ShowType;
	int  m_SmallType;
	StSearchSetInfo  m_stSearchSetInfo;
	CResultSearchNew  *m_pResultSearchNew;
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedFirstBtn();
	afx_msg void OnBnClickedGotoBtn();
	afx_msg void OnBnClickedTopBtn();
	afx_msg void OnBnClickedNextBtn();
	afx_msg void OnBnClickedLastBtn();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
};
