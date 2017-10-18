#pragma once


// CTestimonialPage11 对话框

class CTestimonialPage11 : public CDialog
{
	DECLARE_DYNAMIC(CTestimonialPage11)

public:
	CTestimonialPage11(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTestimonialPage11();

// 对话框数据
	enum { IDD = IDD_TESTIMONIAL_PAGE11_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CGridCtrl  *m_pGrid;
	StBasTestimonialPage11 *m_pPage11Info;
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
