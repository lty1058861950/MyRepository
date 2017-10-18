#pragma once
#include ".\mylistctrl\editablelistctrl.h"


// CSelProductDlg �Ի���

class CSelProductDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelProductDlg)

public:
	CSelProductDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSelProductDlg();

// �Ի�������
	enum { IDD = IDD_SEL_PRODUCT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEditableListCtrl m_ProdList;
	StBasProduct      m_SearchInfo;
	CString           m_strProductNo;
	CString           m_strProductName;
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void    AutoSize();
	
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOkSelBtn();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
};
