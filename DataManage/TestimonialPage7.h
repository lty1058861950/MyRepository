#pragma once


// CTestimonialPage7 �Ի���

class CTestimonialPage7 : public CDialog
{
	DECLARE_DYNAMIC(CTestimonialPage7)

public:
	CTestimonialPage7(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTestimonialPage7();

// �Ի�������
	enum { IDD = IDD_TESTIMONIAL_PAGE7_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CGridCtrl  *m_pGrid;
	StBasTestimonialPage7 *m_pPage7Info;
	CFont  m_Font1, m_Font2, m_Font3;
	CModeParMng			*m_pModeParMng;
	CModeXmlAnalysis	*m_pModeXmlAnalysis;
	void         DispalyPageInfo();
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
