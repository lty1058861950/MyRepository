// CellCombo.cpp : 实现文件
//

#include "stdafx.h"
#include "CellCombo.h"
#include "EditableListCtrl.h"

// CCellCombo

IMPLEMENT_DYNAMIC(CCellCombo, CComboBox)

CCellCombo::CCellCombo()
{

}

CCellCombo::~CCellCombo()
{
}


BEGIN_MESSAGE_MAP(CCellCombo, CComboBox)
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()



// CCellCombo 消息处理程序



void CCellCombo::OnKillFocus(CWnd* pNewWnd)
{
	// TODO: 在此处添加消息处理程序代码
	CComboBox::OnKillFocus(pNewWnd);

	CEditableListCtrl *pList = (CEditableListCtrl*)GetParent();

	POINT ptMouse;
	GetCursorPos(&ptMouse);

	CRect rcThis;
	GetWindowRect(&rcThis);

	if(!pList->m_bEnableComboButton && !rcThis.PtInRect(ptMouse))
	{
		pList->EndEdit();
		return;
	}

	CRect rect = pList->GetComboButtonRect();
	if(!rect.PtInRect(ptMouse) && !rcThis.PtInRect(ptMouse))
		pList->EndEdit();
}
