#pragma once


// CTestimonialPage10 �Ի���

class CTestimonialPage10 : public CDialog
{
	DECLARE_DYNAMIC(CTestimonialPage10)

public:
	CTestimonialPage10(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTestimonialPage10();

// �Ի�������
	enum { IDD = IDD_TESTIMONIAL_PAGE10_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CGridCtrl  *m_pGrid;
	StBasTestimonialPage10 *m_pPage10Info;
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
