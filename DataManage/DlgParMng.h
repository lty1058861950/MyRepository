#if !defined(AFX_DLGPARMNG_H__0517B792_C9C2_4D8A_B908_96CD7883BBD6__INCLUDED_)
#define AFX_DLGPARMNG_H__0517B792_C9C2_4D8A_B908_96CD7883BBD6__INCLUDED_

#include "afxole.h"
#include "MyListCtrl/EditableListCtrl.h"
#include "ShowModeStyle.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgParMng.h : header file
//

class CShowModeStyle;
/////////////////////////////////////////////////////////////////////////////
// CDlgParMng dialog
class CDlgParMng : public CDialog
{
// Construction
public:
	CDlgParMng(CWnd* pParent = NULL);   // standard constructor

public:
	int    m_nNum;
	int    m_TreeRect;
	CRect  m_PressRect;
	int    m_PressFlag;

	int			m_Type;
	int			m_TableType;
	CImageList	m_TreeImgList;


	CExcelOptFun	 *pXls; 
	CModeParMng		 *pPar;
	CModeXmlAnalysis *pXml;
	int           *m_bTabCheck;
	StBasMode      *m_pCurModeInfo;
	CShowModeStyle  *m_pShowModeStyle;
public:
	void InitImageList();
	void AdjustOnSize( );

	void MyListCtrl_DeleteAllRowCol( ); 

	void InitSysInfo( );


// Dialog Data
	//{{AFX_DATA(CDlgParMng)
	enum { IDD = IDD_SHOWMODEPAR_DLG };
	CEditableListCtrl	m_ListCtrl;
	CTreeCtrl	m_TreeCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgParMng)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgParMng)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBtnLoadIn();
	afx_msg void OnBtnLoadOut();
	afx_msg void OnBtnLoadStruct();
	virtual void OnOK();
	afx_msg void OnClickTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnParCheck();
	afx_msg void OnBtnSaveAll();

	BOOL    SaveModeXmlToDb();//Liuty//
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnLoadOutSrt();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPARMNG_H__0517B792_C9C2_4D8A_B908_96CD7883BBD6__INCLUDED_)
