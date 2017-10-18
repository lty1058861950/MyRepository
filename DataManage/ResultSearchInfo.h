#pragma once


// CResultSearchInfo 对话框
class CResultSearchNew;
class CResultSearchInfo : public CDialog
{
	DECLARE_DYNAMIC(CResultSearchInfo)

public:
	CResultSearchInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CResultSearchInfo();

// 对话框数据
	enum { IDD = IDD_RESULT_SEARCH_INFO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CResultSearchNew   *m_pResultSearchNew;

	void        DisPalySearchInfo();
	BOOL        GetSearchInfo();

	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void     AutoSize();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
