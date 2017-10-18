#pragma once


// CTestimonialPage6 �Ի���

class CTestimonialPage6 : public CDialog
{
	DECLARE_DYNAMIC(CTestimonialPage6)

public:
	CTestimonialPage6(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTestimonialPage6();

// �Ի�������
	enum { IDD = IDD_TESTIMONIAL_PAGE6_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CGridCtrl  *m_pGrid;
	StBasTestimonialPage6 *m_pPage6Info;
	CFont  m_Font1, m_Font2, m_Font3;
	CModeParMng			*m_pModeParMng;
	CModeXmlAnalysis	*m_pModeXmlAnalysis;
	void      DispalyPageInfo();

	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void    DispalyModeStyle();
	void    AutoSize();
	void    InitGridCtrl();
	//void    InitGridCtrl_MUL( );
};
