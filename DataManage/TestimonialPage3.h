#pragma once


// CTestimonialPage3 �Ի���

class CTestimonialPage3 : public CDialog
{
	DECLARE_DYNAMIC(CTestimonialPage3)

public:
	CTestimonialPage3(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTestimonialPage3();

// �Ի�������
	enum { IDD = IDD_TESTIMONIAL_PAGE3_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	StBasTestimonialPage3  *m_pPage3Info;
	CFont  m_Font1, m_Font2, m_Font3;
	void      DispalyPageInfo();
protected:
	virtual void OnOK();
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void    AutoSize();
};
