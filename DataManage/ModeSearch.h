#pragma once


// CModeSearch 对话框

class CModeSearch : public CDialog
{
	DECLARE_DYNAMIC(CModeSearch)

public:
	CModeSearch(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CModeSearch();

// 对话框数据
	enum { IDD = IDD_MODE_SEARCH_BTN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	StBasMode  m_ModeSearchInfo;

	void       InitComBox();
	void       DisplaySearchInfo();
	void       GetSearchInfo();
	virtual BOOL OnInitDialog();
	void  AutoSize();
protected:
	virtual void OnOK();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedSearchBtn();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedSelProdBtn();
};
