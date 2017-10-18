#if !defined(AFX_MYLISTCTRL_H__8894B0C3_A8F9_4981_A514_0B45015A7067__INCLUDED_)
#define AFX_MYLISTCTRL_H__8894B0C3_A8F9_4981_A514_0B45015A7067__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyListCtrl.h : header file
//
#include "CellEditor.h"
#include "EditableListCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl window

class CMyListCtrl : public CEditableListCtrl //CListCtrl
{
// Construction
public:
	CMyListCtrl();

// Attributes
public:
	int m_type;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyListCtrl)
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct); 
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLISTCTRL_H__8894B0C3_A8F9_4981_A514_0B45015A7067__INCLUDED_)
