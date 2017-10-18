#pragma once
#include "afxcmn.h"
#include "TestimonialPage1.h"
#include "TestimonialPage2.h"
#include "TestimonialPage3.h"
#include "TestimonialPage4.h"
#include "TestimonialPage5.h"
#include "TestimonialPage6.h"
#include "TestimonialPage7.h"
#include "TestimonialPage8.h"
#include "TestimonialPage9.h"
#include "TestimonialPage10.h"
#include "TestimonialPage11.h"

// CTestimonialMng 对话框

class CTestimonialMng : public CDialog
{
	DECLARE_DYNAMIC(CTestimonialMng)

public:
	CTestimonialMng(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTestimonialMng();

// 对话框数据
	enum { IDD = IDD_TESTIMONIAL_MNG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CTestimonialPage1  m_Page1;
	CTestimonialPage2  m_Page2;
	CTestimonialPage3  m_Page3;
	CTestimonialPage4  m_Page4;
	CTestimonialPage5  m_Page5;
	CTestimonialPage6  m_Page6;
	CTestimonialPage7  m_Page7;
	CTestimonialPage8  m_Page8;
	CTestimonialPage9  m_Page9;
	CTestimonialPage10  m_Page10;
	CTestimonialPage11  m_Page11;

	virtual BOOL OnInitDialog();
	void    AutoSize();
	void    InitTestimomialTree();

	void    InitTestimomialInfo(StBasTestimonial *pStTestimonialInfo = NULL);
	void    DisPlayPagesInfo();
protected:
	virtual void OnOK();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CTreeCtrl m_TestTree;
	CImageList	m_TreeImgList;
	StBasTestimonial  m_StrTestimonialInfo;
	afx_msg void OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
};
