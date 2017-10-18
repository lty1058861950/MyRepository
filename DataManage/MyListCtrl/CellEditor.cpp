// CellEditor.cpp : implementation file
//

#include "stdafx.h"
#include "CellEditor.h"
#include "EditableListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCellEditor

CCellEditor::CCellEditor()
{
//	m_nNum = 0;
	m_NumberOnly = FALSE;
	m_IsDon      = FALSE;
	m_IsSub		 = FALSE;
}

CCellEditor::~CCellEditor()
{
}


BEGIN_MESSAGE_MAP(CCellEditor, CEdit)
	//{{AFX_MSG_MAP(CCellEditor)
	ON_WM_KILLFOCUS()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCellEditor message handlers

void CCellEditor::OnKillFocus(CWnd* pNewWnd) 
{
	CEdit::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	CEditableListCtrl *pList = (CEditableListCtrl*)GetParent();

	if(!pList->m_bEnableEditButton)
	{
		pList->EndEdit();
		return;
	}

	CRect rect = pList->GetEditButtonRect();
	POINT	ptMouse;
	GetCursorPos(&ptMouse);

	if(!rect.PtInRect(ptMouse))
		pList->EndEdit();
}

void CCellEditor::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	//if(nChar == VK_RETURN)
	//	((CEditableListCtrl*)GetParent())->EndEdit();

	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CCellEditor::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_NumberOnly)
	{
		if ((nChar >= '0' && nChar <= '9') || nChar == VK_BACK || nChar == VK_DELETE)
			CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
	else
		CEdit::OnChar(nChar, nRepCnt, nFlags);

}
