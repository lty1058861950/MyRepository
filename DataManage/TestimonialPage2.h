#pragma once


// CTestimonialPage2 对话框

class CTestimonialPage2 : public CDialog
{
	DECLARE_DYNAMIC(CTestimonialPage2)

public:
	CTestimonialPage2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTestimonialPage2();

// 对话框数据
	enum { IDD = IDD_TESTIMONIAL_PAGE2_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void      DispalyPageInfo();
	CFont  m_Font1, m_Font2, m_Font3;
	StBasTestimonialPage2    *m_pPage2Info;
protected:
	virtual void OnOK();
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void    AutoSize();
};
