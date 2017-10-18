// OutputBar.h : interface of the COutputBar class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTPUTBAR_H__9DB1F792_723D_4E34_BA85_BB812EEE755D__INCLUDED_)
#define AFX_OUTPUTBAR_H__9DB1F792_723D_4E34_BA85_BB812EEE755D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "GridCtrl_src/GridCtrl.h"
#include "mylistctrl\editablelistctrl.h"
#endif // _MSC_VER > 1000

class COutputBar : public CBCGPDockingControlBar
{
public:
	COutputBar();

// Attributes
	
private:
	BOOL InitGridRadiate();			//π„≤•ΩÁ√Ê
	void InitGridCtrl();
protected:
	CBCGPTabWnd	m_wndTabs;

	

// Operations
public:
	CListCtrl	m_wndList1;
	CListCtrl	m_wndList2;
	CListCtrl	m_wndList3;
	CFont       m_fontMark1;
	void        InitOutList();
	void        InsertErrorText(CString strText);
	void        InsertErrorArrayText(vector<CString> &strErrorArray);
public:
	CGridCtrl*	m_pGrid;
	//CGridCtrl*	m_wndList2;

public:
	//void DispLayInfo(CString szInfo);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COutputBar();

// Generated message map functions
protected:
	//{{AFX_MSG(COutputBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTPUTBAR_H__9DB1F792_723D_4E34_BA85_BB812EEE755D__INCLUDED_)
