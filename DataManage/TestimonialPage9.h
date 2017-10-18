#pragma once


// CTestimonialPage9 对话框

class CTestimonialPage9 : public CDialog
{
	DECLARE_DYNAMIC(CTestimonialPage9)

public:
	CTestimonialPage9(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTestimonialPage9();

// 对话框数据
	enum { IDD = IDD_TESTIMONIAL_PAGE9_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CGridCtrl  *m_pGrid;
	StBasTestimonialPage9 *m_pPage9Info;
	CFont  m_Font1, m_Font2, m_Font3;
	CModeParMng			*m_pModeParMng;
	CModeXmlAnalysis	*m_pModeXmlAnalysis;
	virtual BOOL OnInitDialog();
	void         DispalyPageInfo();
protected:
	virtual void OnOK();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void    AutoSize();

	void    DispalyModeStyle();
};
