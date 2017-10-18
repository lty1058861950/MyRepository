#pragma once


// CTestimonialPage1 对话框

class CTestimonialPage1 : public CDialog
{
	DECLARE_DYNAMIC(CTestimonialPage1)

public:
	CTestimonialPage1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTestimonialPage1();

// 对话框数据
	enum { IDD = IDD_TESTIMONIAL_PAGE1_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CFont  m_Font1, m_Font2, m_Font3;
	StBasTestimonialPage1 *m_pPage1Info;

	void    DispalyPageInfo();
	virtual BOOL OnInitDialog();
protected:
	
	virtual void OnOK();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void    AutoSize();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
