#pragma once
#include "mylistctrl\editablelistctrl.h"


// CSelDlg �Ի���

class CSelDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelDlg)

public:
	CSelDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSelDlg();

// �Ի�������
	enum { IDD = IDD_SEL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEditableListCtrl m_SrcList;
	CEditableListCtrl m_DecList;
	int               m_nType;

	void  ListCtrl_ClearAllColumn(CEditableListCtrl *pList);

	void  InitProductList(CString strProductNo);
	void  DisPalyProductSel();
	void  SaveSelProducts();
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	BOOL CheckItemSame(UINT OID);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedFindBtn();
	afx_msg void OnBnClickedAllSelBtn();
	afx_msg void OnBnClickedSingleSelBtn();
	afx_msg void OnBnClickedSingleDelBtn();
	afx_msg void OnBnClickedAllDelBtn();
};
