#pragma once


// CTestimonialPage4 对话框

class CTestimonialPage4 : public CDialog
{
	DECLARE_DYNAMIC(CTestimonialPage4)

public:
	CTestimonialPage4(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTestimonialPage4();

// 对话框数据
	enum { IDD = IDD_TESTIMONIAL_PAGE4_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	StBasTestimonialPage4  *m_pPage4Info;
	int    m_ShowType;
	CFont  m_Font1, m_Font2, m_Font3;
	void     DispalyPageInfo();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
protected:
	virtual void OnOK();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void    AutoSize();
};
