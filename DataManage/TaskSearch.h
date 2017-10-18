#pragma once


// CTaskSearch 对话框

class CTaskSearch : public CDialog
{
	DECLARE_DYNAMIC(CTaskSearch)

public:
	CTaskSearch(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTaskSearch();

// 对话框数据
	enum { IDD = IDD_TASK_SEARCH_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	StBasTask  m_TaskSearchInfo;
	CRect m_rcRect1_1, m_rcRect1_2, m_rcRect1_3;
	CRect m_rcRect2_1, m_rcRect2_2, m_rcRect2_3;
	CRect m_rcRect3_1, m_rcRect3_2, m_rcRect3_3;
	CRect m_rcRect4_1, m_rcRect4_2, m_rcRect4_3;
	CRect m_rcRect5_1, m_rcRect5_2, m_rcRect5_3;
	CRect m_rcRect6_1, m_rcRect6_2, m_rcRect6_3;
	CRect m_rcRect7_1, m_rcRect7_2, m_rcRect7_3;
	CRect m_rcRect8_1, m_rcRect8_2, m_rcRect8_3;

	virtual BOOL OnInitDialog();
	void    DisplaySearchInfo();
	void    ShowTaskTypeStatus(int nShowHide);
	void    GetSearchInfo();						//获取查询条件
	int     CheckSearchTime( );                     //检测查询时间是否合法
	int     CheckDateBegSmallEnd(char *pBegTime, char *pEndTime);

	void    InitComBox();
	void     AutoSize();
protected:
	virtual void OnOK();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedTaskSearchBtn();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedSelUpDepartBtn();
	afx_msg void OnBnClickedSelProdnoBtn();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
};
