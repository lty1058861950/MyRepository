// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__A7F8AB8D_D344_48E1_9E23_D59EC6F16451__INCLUDED_)
#define AFX_MAINFRM_H__A7F8AB8D_D344_48E1_9E23_D59EC6F16451__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "WorkspaceBar.h"
#include "WorkspaceBar2.h"
#include "OutputBar.h"
#include "ResetUsrPwd.h"
//#include "DataManageView.h"
#include "DataEncDec.h"

#define CFrameWnd CBCGPFrameWnd

//extern CDataManageView *g_DtMngView;

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	COutputBar		m_wndOutput;

public:  // control bar embedded members
	CBCGPMenuBar			m_wndMenuBar;
	CBCGPToolBar			m_wndToolBar;
	CBCGPStatusBar			m_wndStatusBar;
	CWorkspaceBar		    m_wndWorkSpace;


	CModeParMng			m_ModeParMng;
	CModeXmlAnalysis	m_ModeXmlAnalysis;
	CExcelOptFun		m_ExcelOptFun;

	CDataEncDec			m_DataEncDec;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarReset(WPARAM,LPARAM);
	afx_msg void OnAppLook(UINT id);
	afx_msg void OnUpdateAppLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()


	UINT	m_nAppLook;
public:
	afx_msg void OnMenuUsrMng();
	afx_msg void OnMenuChangePwd();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMenuDepartMng();
	afx_msg void OnClose();
	        void Exit();
	afx_msg void OnUpdateMenuUsrMng(CCmdUI *pCmdUI);
	afx_msg void OnMenuModeMmg();

	afx_msg void OnMenuMesTaskLoadIn();
	afx_msg void OnMenuExcelTaskLoadIn();
	afx_msg void OnMenuTaskMng();

	afx_msg void OnMenuTaskSearch();
	afx_msg void OnMenuResultSearch();

	afx_msg void OnMenuResultSum();
	afx_msg void OnCurdepartMenu();
	afx_msg void OnTaskDataLoadin();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnBatchOutTaskMenu();
	afx_msg void OnBatchSelProductMenu();
	afx_msg void OnUpdateCurdepartMenu(CCmdUI *pCmdUI);
	afx_msg void OnReportSetMenu();
	afx_msg void OnUpdateMenuDepartMng(CCmdUI *pCmdUI);
	afx_msg void OnAddTaskMenu();
	afx_msg void OnModeComputeMenu();
	afx_msg void OnUpdateMenuModeMmg(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAddTaskMenu(CCmdUI *pCmdUI);
	afx_msg void OnUpdateModeComputeMenu(CCmdUI *pCmdUI);
	afx_msg void OnUpdateReportSetMenu(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuExcelTaskLoadIn(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuMesTaskLoadIn(CCmdUI *pCmdUI);
	afx_msg void OnTestimonialMenu();
	afx_msg void OnUpdateTestimonialMenu(CCmdUI *pCmdUI);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__A7F8AB8D_D344_48E1_9E23_D59EC6F16451__INCLUDED_)
