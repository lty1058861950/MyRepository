#if !defined(AFX_CELLEDITOR_H__DDA84945_E30A_474C_A4FA_79B9B268E92F__INCLUDED_)
#define AFX_CELLEDITOR_H__DDA84945_E30A_474C_A4FA_79B9B268E92F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CellEditor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCellEditor window
class CCellEditor : public CEdit
{
// Construction
public:
	CCellEditor();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCellEditor)
	//}}AFX_VIRTUAL

// Implementation
public:
//	int m_nNum;
	BOOL	m_NumberOnly;
	BOOL    m_IsDon;
	BOOL    m_IsSub;
	virtual ~CCellEditor();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCellEditor)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CELLEDITOR_H__DDA84945_E30A_474C_A4FA_79B9B268E92F__INCLUDED_)
