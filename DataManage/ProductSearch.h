#pragma once


// CProductSearch 对话框

class CProductSearch : public CDialog
{
	DECLARE_DYNAMIC(CProductSearch)

public:
	CProductSearch(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CProductSearch();

// 对话框数据
	enum { IDD = IDD_PRODUCT_SEARCH_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	StBasProduct m_ProductSearch;
	virtual BOOL OnInitDialog();
	void        DisPalySearchInfo();
	BOOL        GetSearchInfo();
	void     AutoSize();

protected:
	virtual void OnOK();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedSearchBtn();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
