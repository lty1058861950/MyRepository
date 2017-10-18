#pragma once
#include "GridCtrl_src/GridCtrl.h"

// CTestimonialPage5 �Ի���

class CTestimonialPage5 : public CDialog
{
	DECLARE_DYNAMIC(CTestimonialPage5)

public:
	CTestimonialPage5(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTestimonialPage5();

// �Ի�������
	enum { IDD = IDD_TESTIMONIAL_PAGE5_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CGridCtrl  *m_pGrid;
	StBasTestimonialPage5 *m_pPage5Info;
	CFont  m_Font1, m_Font2, m_Font3;

	CModeParMng			*m_pModeParMng;
	CModeXmlAnalysis	*m_pModeXmlAnalysis;
	void      DispalyPageInfo();
	void      GetPageInfo();
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void    AutoSize();

	void    DispalyModeStyle();
	void    InitGridCtrl();
};
