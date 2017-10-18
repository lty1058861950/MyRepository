#pragma once


// CTestimonialPage8 对话框

class CTestimonialPage8 : public CDialog
{
	DECLARE_DYNAMIC(CTestimonialPage8)

public:
	CTestimonialPage8(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTestimonialPage8();

// 对话框数据
	enum { IDD = IDD_TESTIMONIAL_PAGE8_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CGridCtrl  *m_pGrid;
	StBasTestimonialPage8 *m_pPage8Info;
	CFont  m_Font1, m_Font2, m_Font3;
	CModeParMng			*m_pModeParMng;
	CModeXmlAnalysis	*m_pModeXmlAnalysis;

	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void     AutoSize();
	void     DispalyPageInfo();
	void     DispalyModeStyle();
	void     InitGridCtrl_MUL( );
};
