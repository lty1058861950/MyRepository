// EditableListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "EditableListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditableListCtrl

const int CEditableListCtrl::m_nPaddingLeft = 5;
const COLORREF CEditableListCtrl::m_clrGridLine = DEF_COL_NAVAJOWHITE;

CEditableListCtrl::CEditableListCtrl()
{
	m_iItemEditing = -1;
	m_iSubItemEditing = -1;

	m_bEditable		 = FALSE;
	m_bAutoColor	 = TRUE;
	m_bEnableRClickMenu = TRUE;

	m_bEnableEditButton = FALSE;
	m_bEnableComboButton = FALSE;
	m_bEnableHotKey = TRUE;
}

CEditableListCtrl::~CEditableListCtrl()
{
}


BEGIN_MESSAGE_MAP(CEditableListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CEditableListCtrl)
	ON_WM_CREATE()
	ON_WM_MEASUREITEM_REFLECT()
	ON_NOTIFY_REFLECT_EX(NM_CLICK, OnClick)
	ON_WM_DESTROY()
	ON_WM_KILLFOCUS()
	ON_NOTIFY_REFLECT_EX(NM_RCLICK, OnRclick)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditableListCtrl message handlers

int CEditableListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: Add your specialized creation code here
		
	if(m_bEditable)
		AddItemForEdit();

	return 0;
}

void CEditableListCtrl::PreSubclassWindow() 
{
	ASSERT(IsWindow(m_hWnd));

	SetWindowLong(m_hWnd, GWL_STYLE, 
		WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_OWNERDRAWFIXED);

	if(!m_ComboBox.GetSafeHwnd())
	{
		m_ComboBox.Create(WS_CHILD | WS_VSCROLL |  CBS_DROPDOWN | CBS_AUTOHSCROLL, CRect(10, 10, 50, 200), this, 0);
		m_ComboBox.SetFont(this->GetFont());
	}

	if(!m_Edit.GetSafeHwnd())
	{
		
		m_Edit.Create(WS_CHILD | ES_AUTOHSCROLL | WS_BORDER | ES_WANTRETURN, CRect(0, 0, 100, 50), this, 0);
		m_Edit.SetFont(this->GetFont());
	}

	if(!m_EditButton.GetSafeHwnd())
	{
		m_EditButton.Create(_T("..."), WS_CHILD | BS_PUSHBUTTON, CRect(0, 0, 15, 10), this, Edit_Button_ID);
		m_EditButton.SetFont(this->GetFont());
	}

	if(!m_ComboButton.GetSafeHwnd())
	{
		m_ComboButton.Create(_T("..."), WS_CHILD | BS_PUSHBUTTON, CRect(0, 0, 15, 10), this, Combo_Button_ID);
		m_ComboButton.SetFont(this->GetFont());
	}

	if(!m_PopupMenu.GetSafeHmenu())
	{
		m_PopupMenu.CreatePopupMenu();
		m_PopupMenu.AppendMenu(MF_STRING, IDM_COPY_ITEM,		_T("复制"));
		m_PopupMenu.AppendMenu(MF_GRAYED, IDM_PASTE_ITEM,		_T("粘贴"));
		m_PopupMenu.AppendMenu(MF_SEPARATOR);
		m_PopupMenu.AppendMenu(MF_STRING, IDM_INSERT_ITEM,		_T("插入记录"));
		m_PopupMenu.AppendMenu(MF_STRING, IDM_DELETE_ITEM,		_T("删除选中记录"));
		m_PopupMenu.AppendMenu(MF_STRING, IDM_DELETE_ALL_ITEMS, _T("删除全部记录"));
	}

	if(!m_DeleteMenu.GetSafeHmenu())
	{
		m_DeleteMenu.CreatePopupMenu();
		m_DeleteMenu.AppendMenu(MF_STRING, IDM_DELETE_ITEM,		 _T("删除选中记录"));
		m_DeleteMenu.AppendMenu(MF_STRING, IDM_DELETE_ALL_ITEMS, _T("删除全部记录"));
	}

	if(!m_PasteMenu.GetSafeHmenu())
	{
		m_PasteMenu.CreatePopupMenu();
		m_PasteMenu.AppendMenu(MF_GRAYED, IDM_PASTE_ITEM, _T("粘贴"));
	}

	if(m_bEditable)
		AddItemForEdit();
}

void CEditableListCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	lpMeasureItemStruct->itemHeight = DEF_ITEM_HEIGHT;
}

void CEditableListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	HDC hDC				= lpDrawItemStruct->hDC;
	RECT rcItem			= lpDrawItemStruct->rcItem;
	DWORD dwItemState	= lpDrawItemStruct->itemState;
	DWORD dwItemAction	= lpDrawItemStruct->itemAction;
	DWORD dwItemID      = lpDrawItemStruct->itemID;
	DWORD dwItemData    = lpDrawItemStruct->itemData;

	SetBkMode(hDC, TRANSPARENT);

	HBRUSH hBrushCell = 0;
	COLORREF clrPen = m_clrGridLine;

	BOOL bSelect = dwItemState & ODS_SELECTED;

	/*if(!m_bAutoColor)
		rcItem.right -= 2;*/

	if(bSelect)
	{
		hBrushCell = CreateSolidBrush(GetSysColor(COLOR_BACKGROUND));
		::SetTextColor(hDC, DEF_COL_WHITE);
	}
	else if(m_bAutoColor)
	{
		if((dwItemID) % 2 == 0)
		{
			hBrushCell = CreateSolidBrush(DEF_COL_BLUE);		
			::SetTextColor(hDC, DEF_COL_BLACK);
		}

		else
		{
			hBrushCell = CreateSolidBrush(DEF_COL_WHITESMOKE);	
			::SetTextColor(hDC, DEF_COL_BLACK);
		}
	}
	else
	{
		hBrushCell = CreateSolidBrush(DEF_COL_WHITE);
		::SetTextColor(hDC, DEF_COL_BLACK);
		clrPen = DEF_COL_GREY;
	}

	FillRect(hDC, &rcItem, hBrushCell);
	DeleteObject(hBrushCell);

	HPEN hPen = CreatePen(PS_SOLID, 1, clrPen);
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

	if(IsItemPreEdit(dwItemID) || IsItemModified(dwItemID))
	{
		CString strText = GetItemText(dwItemID, 0);

		if(IsItemPreEdit(dwItemID))
		{
			DrawText(hDC, strText, strText.GetLength(), 
				&CRect(rcItem.left + m_nPaddingLeft, rcItem.top, rcItem.right, rcItem.bottom),
				DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS );
		}
		
		//Draw Item back color
		if(IsItemModified(dwItemID))
		{
			hBrushCell = CreateSolidBrush(DEF_COL_PALEGREEN);

			FillRect(hDC, &rcItem, hBrushCell);
			DeleteObject(hBrushCell);

			::SetTextColor(hDC, DEF_COL_BLACK);
			DrawText(hDC, strText, strText.GetLength(), 
				&CRect(rcItem.left + m_nPaddingLeft, rcItem.top, rcItem.right - 30, rcItem.bottom),
				DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS | DT_CENTER );
		}

		if(!m_bAutoColor)
		{
			CRect rc = rcItem;
			rc.right = 0;
			int nColumnCount = GetHeaderCtrl()->GetItemCount();
			for(int col = 0; col < nColumnCount; col++)
			{
				int width = GetColumnWidth(col);// - 1;
				rc.right += width;
			}

			MoveToEx(hDC, rc.left, rc.top, NULL);
			LineTo(hDC, rc.right, rc.top);
			LineTo(hDC, rc.right, rc.bottom);
			LineTo(hDC, rc.left, rc.bottom);
			LineTo(hDC, rc.left, rc.top);
		}
	}
	else
	{
		int posX = rcItem.left;
		int posY = rcItem.top;
		int height = rcItem.bottom - rcItem.top + 1;
		int nColumnCount = GetHeaderCtrl()->GetItemCount();
		for(int col = 0; col < nColumnCount; col++)
		{
			CString strText = GetItemText(dwItemID, col);
			int     width   = GetColumnWidth(col);
			/*if(!m_bAutoColor)
				width -= 1;*/

			//Draw Item back color
			DWORD dwItem = MAKEWORD(dwItemID, col);
			COLORREF clr;
			if(m_mapCellColor.Lookup(dwItem, clr) && !bSelect)
			{
				hBrushCell = CreateSolidBrush(clr);

				CRect rect(CPoint(posX, posY), CSize(width,height));
				FillRect(hDC, &rect, hBrushCell);
				DeleteObject(hBrushCell);
			}

			MoveToEx(hDC, posX, posY, NULL);
			LineTo(hDC, posX + width, posY);
			LineTo(hDC, posX + width, posY + height - 1);
			LineTo(hDC, posX, posY + height - 1);
			LineTo(hDC, posX, posY);

			DrawText(hDC, strText, strText.GetLength(), 
				&CRect(posX + m_nPaddingLeft, posY, posX + width, posY + height), 
				DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS );
			posX += width;
		}
	}

	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
}

BOOL CEditableListCtrl::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	if(!m_bEnableClick)
		return FALSE;

	LVHITTESTINFO	lvhtinfo;
	GetCursorPos(&lvhtinfo.pt);
	ScreenToClient(&lvhtinfo.pt);
	SubItemHitTest(&lvhtinfo);

	if(lvhtinfo.flags & LVHT_ONITEM)
	{
		BOOL bIsEditCell = IsEditCell(lvhtinfo.iItem, lvhtinfo.iSubItem);

		if(!m_bEditable && !bIsEditCell && !IsItemPreEdit(lvhtinfo.iItem))
			return FALSE;

		if(IsItemPreEdit(lvhtinfo.iItem) && (lvhtinfo.iItem == GetItemCount() - 1))
		{
			char szIndex[128] = {0};
			RemoveItemPreEdit(lvhtinfo.iItem);
			AddItemForEdit();
	
			if(m_bEditable)
				SetItemText(lvhtinfo.iItem, 0, itoa(GetItemCount() - 1, szIndex,10));

			::SendMessage(GetParent()->m_hWnd, ELM_ADD_ITEM_FRO_EDIT, (WPARAM)lvhtinfo.iItem, (LPARAM)lvhtinfo.iSubItem);
		}
		else
		{
			if(lvhtinfo.iSubItem > 0 || (bIsEditCell && lvhtinfo.iSubItem >= 0))
				BeginEdit(lvhtinfo.iItem, lvhtinfo.iSubItem);
		}	
	}
	else
	{
		EndEdit();
	}

	*pResult = 0;
	return TRUE;
}

void CEditableListCtrl::AddStringToList(DWORD key, const CString& str)
{
	void* pValue = 0;
	CStringArray* pStrArray = 0;
	if(!m_mapItemList.Lookup(key, pValue))	
	{
		pStrArray = new CStringArray();
		m_mapItemList.SetAt(key, pStrArray);
	}
	else
	{
		pStrArray = (CStringArray*)pValue;
	}

	pStrArray->Add(str);
}

void CEditableListCtrl::DeleteAllStringLists()
{
	POSITION pos = m_mapItemList.GetStartPosition();
	while(pos != 0)
	{
		DWORD	wKey = 0;
		void*   pValue = 0;
		m_mapItemList.GetNextAssoc(pos, wKey, pValue);
		
		// 这里必须要转换成 CStringArray*
		// delete pValue 会出错, 因为无法正确调用 CStringArray 的析构.
		CStringArray *pArr = (CStringArray*)pValue;
		pArr->RemoveAll();
		delete (CStringArray*)pArr;
	}
}

void CEditableListCtrl::ClearStringList(DWORD key)
{
	void* pValue = 0;
	CStringArray* pStrArray = 0;
	if(m_mapItemList.Lookup(key, pValue))	
	{
		pStrArray = (CStringArray*)pValue;
		pStrArray->RemoveAll();
	}
}

BOOL CEditableListCtrl::BindListToItem(int iSubItem, DWORD key)
{
	m_mapListBind.SetAt((void*)iSubItem, (void*)key);
	return true;
}

BOOL CEditableListCtrl::UnBindListToItem(int iSubItem)
{
	m_mapListBind.RemoveKey((void*)iSubItem);
	return TRUE;
}

void CEditableListCtrl::OnDestroy() 
{
	DeleteAllStringLists();
	CListCtrl::OnDestroy();
	// TODO: Add your message handler code here
}

void CEditableListCtrl::BeginEdit(int iItem, int iSubItem)
{
	/*if(!m_bEditable && !IsEditCell(iItem, iSubItem))
		return;*/

	EndEdit();
	
	m_iItemEditing = iItem;
	m_iSubItemEditing = iSubItem;

//	SetItemModified(iItem);

	if(::SendMessage(::GetParent(m_hWnd), ELM_CELL_EDIT_BEGIN, (WPARAM)iItem, (LPARAM)iSubItem) != 0)
	{
		m_iItemEditing = -1;
		m_iSubItemEditing = -1;
		return;
	}

	int nColumnCnt = GetHeaderCtrl()->GetItemCount();
	for(int col = 0; col < nColumnCnt; col++)
	{
		void* pValue = 0;
		if(m_mapListBind.Lookup((void*)col, pValue))
		{
			CString strItem = GetItemText(m_iItemEditing, col);
			if(strItem.IsEmpty())
			{
				m_mapItemList.Lookup((DWORD)pValue, pValue);
				CStringArray* pStrArray = (CStringArray*)pValue;
				SetItemText(m_iItemEditing, col, pStrArray->GetAt(0));
			}
		}
	}

	CRect rect;
	GetSubItemRect(m_iItemEditing, m_iSubItemEditing, LVIR_BOUNDS, rect);
	
	rect.top ++;
	if(m_iSubItemEditing == 0)
	{
		int nWidth = GetColumnWidth(0);
		rect.right = rect.left + nWidth;
	}

	CString strItem = GetItemText(iItem, iSubItem);

	void* pValue = 0;
	const int width = 25;
	if(m_mapListBind.Lookup((void*)m_iSubItemEditing, pValue))  // 使用 COMBO
	{
		if(!m_mapItemList.Lookup((DWORD)pValue, pValue))
			return;
			
		CStringArray* pStrArray = (CStringArray*)pValue;
		
		m_ComboBox.ResetContent(); 
		for(int i=0; i<pStrArray->GetSize(); i++)
		{
			m_ComboBox.AddString(pStrArray->GetAt(i));
		}

		CRect rcBtn, rcEdit;
		rcEdit = rect;
		if(m_bEnableComboButton)
		{
			rcEdit.right = rect.left + (rect.Width() - width);
			rcBtn.left = rect.left + (rect.Width() - width);
			rcBtn.top  = rect.top;
			rcBtn.right = rect.right;
			rcBtn.bottom = rect.bottom;

			m_ComboButton.MoveWindow(rcBtn);
			m_ComboButton.ShowWindow(SW_SHOW);
		}

		m_ComboBox.MoveWindow(rcEdit);
		m_ComboBox.ShowWindow(SW_SHOW);

		if(!IsComboEditColumn(m_iSubItemEditing))
		{
			m_ComboBox.ShowDropDown();

			if(strItem.IsEmpty())
				m_ComboBox.SetCurSel(0);
			else
				m_ComboBox.SelectString(-1, strItem);
		}
		else
		{
			//if(!m_bEnableButton)
			//	m_ComboBox.ShowDropDown();
			if(strItem.IsEmpty())
				m_ComboBox.SetCurSel(0);
			else
				m_ComboBox.SetWindowText(strItem);

			m_ComboBox.SetFocus();
		}
	}
	else														// 使用 EDIT
	{
		CRect rcBtn, rcEdit;

		rcEdit = rect;
		if(m_bEnableEditButton)
		{
			rcEdit.right = rect.left + (rect.Width() - width);
			rcBtn.left = rect.left + (rect.Width() - width);
			rcBtn.top  = rect.top;
			rcBtn.right = rect.right;
			rcBtn.bottom = rect.bottom;

			m_EditButton.MoveWindow(rcBtn);
			m_EditButton.ShowWindow(SW_SHOW);
		}

		m_Edit.MoveWindow(rcEdit);
		m_Edit.ShowWindow(SW_SHOW);
		m_Edit.SetWindowText(strItem);
		m_Edit.SetFocus();
		m_Edit.SetSel(0, -1);
	}
}

void CEditableListCtrl::EndEdit()
{
	if(m_iItemEditing == -1 || m_iSubItemEditing == -1)
		return;

	CString strItem;
	if(IsItemBindToList(m_iSubItemEditing))
	{
		int nCurSel = m_ComboBox.GetCurSel();
		if(nCurSel != CB_ERR)
			m_ComboBox.GetLBText(nCurSel, strItem);

		if(strItem.IsEmpty())
			m_ComboBox.GetWindowText(strItem);
	}
	else
	{
		if(!m_bEnableClick)
			return;
		m_Edit.GetWindowText(strItem);
	}
	
	SetItemText(m_iItemEditing, m_iSubItemEditing, strItem);
	
	if(m_ComboBox.GetDroppedState())
		m_ComboBox.ShowDropDown(FALSE);

	m_ComboBox.ShowWindow(SW_HIDE);
	m_Edit.ShowWindow(SW_HIDE);
	m_EditButton.ShowWindow(SW_HIDE);
	m_ComboButton.ShowWindow(SW_HIDE);
	
	::SendMessage(::GetParent(m_hWnd), ELM_CELL_EDIT_END, (WPARAM)m_iItemEditing, (LPARAM)m_iSubItemEditing);

	m_iItemEditing = -1;
	m_iSubItemEditing = -1;
}

BOOL CEditableListCtrl::IsItemBindToList(int iSubItem)
{
	void* pValue = 0;
	return m_mapListBind.Lookup((void*)iSubItem, pValue);
}


void CEditableListCtrl::OnKillFocus(CWnd* pNewWnd) 
{
	CListCtrl::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here

	if(pNewWnd && pNewWnd->GetParent() != this)
		EndEdit();
}

BOOL CEditableListCtrl::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	/* 如果设置了不启用子类的Menu，则将消息交由父类处理 */
	if(!m_bEnableRClickMenu) return FALSE;

	EndEdit();
	
	POINT	ptMouse;
	GetCursorPos(&ptMouse);

	LVHITTESTINFO	lvhtinfo;
	GetCursorPos(&lvhtinfo.pt);
	ScreenToClient(&lvhtinfo.pt);
	SubItemHitTest(&lvhtinfo);

	int nItemCount = GetItemCount();

	if((lvhtinfo.flags & LVHT_ONITEM) && lvhtinfo.iItem < nItemCount - 1 && m_bEditable)
		m_PopupMenu.TrackPopupMenu(TPM_LEFTALIGN, ptMouse.x, ptMouse.y, this);
	else if(lvhtinfo.iItem < 0 && m_bEditable)
		m_PasteMenu.TrackPopupMenu(TPM_LEFTALIGN, ptMouse.x,ptMouse.y, this);

	if((lvhtinfo.flags & LVHT_ONITEM) && lvhtinfo.iItem < nItemCount && !m_bEditable)
		m_DeleteMenu.TrackPopupMenu(TPM_LEFTALIGN, ptMouse.x, ptMouse.y, this);		

	*pResult = 0;
	return TRUE;
}

void CEditableListCtrl::DeleteRows()
{//从后往前删除

	if(m_iSubItemEditing != -1 && (m_Edit.IsWindowVisible() || m_ComboBox.IsWindowVisible()))
		return;

	int nIndex;

	if(!m_bEditable)
		nIndex = GetItemCount();
	else
		nIndex = GetItemCount_Child();

	while(nIndex >= 0)
	{
		if(GetItemState(nIndex, LVIS_SELECTED) & LVIS_SELECTED)
			DeleteItem(nIndex);

		nIndex--;
	}

	if(m_bEditable)
		UpdateListID();
}

BOOL CEditableListCtrl::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(HIWORD(wParam) == 0 && LOWORD(wParam) == IDM_DELETE_ITEM)
		DeleteRows();

	if(HIWORD(wParam) == 0 && LOWORD(wParam) == IDM_DELETE_ALL_ITEMS)
	{
		DeleteAllItems();
		if(m_bEditable)
			AddItemForEdit();
	}

	if(HIWORD(wParam) == 0 && LOWORD(wParam) == IDM_INSERT_ITEM && m_bEditable)
	{
		char szNum[32] = {0};
		int nIndex = GetFirstSelectedItem();
		InsertItem(nIndex, itoa(nIndex + 1, szNum, 10));
		UpdateListID();
	}

	if(HIWORD(wParam) == 0 && LOWORD(wParam) == IDM_COPY_ITEM && m_bEditable)
		CopyItemData();

	if(HIWORD(wParam) == 0 && LOWORD(wParam) == IDM_PASTE_ITEM && m_bEditable)
		PasteItemData();

	//if(HIWORD(wParam) == CBN_KILLFOCUS)
	//{
	//	//if(IsComboEditColumn(m_iSubItemEditing))
	//	//EndEdit();
	//}

	if(HIWORD(wParam) == CBN_CLOSEUP)
	{
		HWND hCombo = (HWND)lParam;
		int nCurSel = (int)::SendMessage(hCombo, CB_GETCURSEL, 0, 0);
		int nCount = (int)::SendMessage(hCombo, CB_GETCOUNT, 0, 0);

		CString strLastSelItemText = GetItemText(m_iItemEditing, m_iSubItemEditing);
		if(nCurSel == CB_ERR && !IsComboEditColumn(m_iSubItemEditing))
			::SendMessage(hCombo, CB_SELECTSTRING, -1, (LPARAM)(LPCTSTR)strLastSelItemText);
		EndEdit();

		return CListCtrl::OnCommand(wParam, lParam);
	}

	if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == Edit_Button_ID)
	{
		::SendMessage(GetParent()->m_hWnd, ELM_EDIT_BUTTON_CLICK, (WPARAM)m_iItemEditing, (LPARAM)m_iSubItemEditing);
		m_Edit.SetFocus();
		m_Edit.SetSel(0, -1);
	}

	if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == Combo_Button_ID)
	{
		::SendMessage(GetParent()->m_hWnd, ELM_COMBO_BUTTON_CLICK, (WPARAM)m_iItemEditing, (LPARAM)m_iSubItemEditing);
		m_ComboBox.SetFocus();
	}

	return CListCtrl::OnCommand(wParam, lParam);
}

int CEditableListCtrl::AddItemForEdit()
{
	int nCount = GetItemCount();
	InsertItem(nCount, DEF_EDIT_RECORD_INDICATOR_TEXT);
	SetItemPreEdit(nCount);
	return nCount;
}

void CEditableListCtrl::SetEditable(BOOL bEditable)
{
	// 传入参数与成员状态相同
	if((m_bEditable && bEditable) || (!m_bEditable && !bEditable))
		return;

	if(!bEditable)
	{
		int nCount = GetItemCount();
		ASSERT(nCount >= 1);
		DeleteItem(nCount - 1);		// 删除最后一条 "指示项"
	}
	else
	{
		AddItemForEdit();
	}

	EnableOnClick(bEditable);
	m_bEditable = bEditable;
}

void CEditableListCtrl::DeleteAllItems_Child()
{
	DeleteAllItems();

	if(IsEditable())
		AddItemForEdit();
}

int CEditableListCtrl::GetItemCount_Child()
{
	int nCount = GetItemCount();
	
	if(m_bEditable)
	{
		ASSERT(nCount >= 1);
	}

	return (m_bEditable ? nCount - 1 : nCount);
}

int CEditableListCtrl::GetFirstSelectedItem()
{
	int nCount = GetItemCount_Child();
	int i;
	for(i=0; i<nCount; i++)
		if(GetItemState(i, LVIS_SELECTED) & LVIS_SELECTED)
			break;

	return ((i == nCount) ? -1 : i);
}

void CEditableListCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	EndEdit();
	
	CListCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CEditableListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	EndEdit();

	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}

CString CEditableListCtrl::GetItemText2(int nItem, const CString& strTitle)
{
	int nCount = GetHeaderCtrl()->GetItemCount();
	int col;
	for(col=0; col < nCount; col++)
	{
		char szText[256] = {0};

		LVCOLUMN lvCol;
		lvCol.mask = LVCF_TEXT;
		lvCol.pszText = szText;
		lvCol.cchTextMax = 256;
		this->GetColumn(col, &lvCol);

		if(lstrcmp(lvCol.pszText, strTitle) == 0)
			break;
	}

	if(col == nCount)
	{
		ASSERT(FALSE);
		return "";
	}

	return GetItemText(nItem, col);
}

BOOL CEditableListCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	EndEdit();

	return CListCtrl::OnMouseWheel(nFlags, zDelta, pt);
}

void CEditableListCtrl::CopyItemData(int iItem)
{
	if(m_iSubItemEditing != -1 && (m_Edit.IsWindowVisible() || m_ComboBox.IsWindowVisible()))
		return;

	if(iItem != -1)
		SetItemState(iItem, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);

	COleDataSource* pSource = CopyTextFromList();
	if (!pSource)
		return;

	pSource->SetClipboard();
	m_PopupMenu.EnableMenuItem(IDM_PASTE_ITEM, MF_ENABLED);
	m_PasteMenu.EnableMenuItem(IDM_PASTE_ITEM, MF_ENABLED);
}

COleDataSource* CEditableListCtrl::CopyTextFromList()
{
	USES_CONVERSION;
	CSharedFile sf(GMEM_MOVEABLE | GMEM_DDESHARE | GMEM_ZEROINIT);

	int nHeader = this->GetHeaderCtrl()->GetItemCount();
	int nCount;
	if(m_bEditable)
		nCount = GetItemCount_Child();
	else
		nCount = GetItemCount();

	int nIndex	= 0;
	int iItem, iSubItem;

	CString str;
	for(iItem=0; iItem<nCount; iItem++)
	{
		if(GetItemState(iItem, LVIS_SELECTED) & LVIS_SELECTED)
		{
			if(m_bEditable)
				iSubItem = 1;
			else
				iSubItem = 0;

			str.Empty();
			for(;iSubItem<nHeader;iSubItem++)
			{
				//隐藏的列不复制
				if(GetColumnWidth(iSubItem) == 0)
					continue;

				CString strText = GetItemText(iItem, iSubItem);
				str += strText;
				if(iSubItem < nHeader - 1)
					str += _T("\t");
			}

			if(iItem < nCount - 1)
				str += _T("\r\n");

			sf.Write(T2A(str.GetBuffer(1)), str.GetLength());
			str.ReleaseBuffer();
		}
	}

	char c = '\0';
	sf.Write(&c, 1);

	DWORD dwLen = (DWORD) sf.GetLength();
	HGLOBAL hMem = sf.Detach();
	if(!hMem)
		return NULL;

	hMem = ::GlobalReAlloc(hMem, dwLen, GMEM_MOVEABLE | GMEM_DDESHARE | GMEM_ZEROINIT);
	if(!hMem)
		return NULL;

	COleDataSource* pSource = new COleDataSource();
	pSource->CacheGlobalData(CF_TEXT, hMem);

	return pSource;
}

BOOL CEditableListCtrl::PasteTextToGrid()
{
	if (!m_bEditable)
		return FALSE;

	COleDataObject obj;
	COleDataObject* pDataObject;
	if(obj.AttachClipboard())
		pDataObject = &obj;
	else
		return FALSE;

	if(!pDataObject->IsDataAvailable(CF_TEXT))
		return FALSE;

	HGLOBAL hmem = pDataObject->GetGlobalData(CF_TEXT);
	CMemFile sf((BYTE*) ::GlobalLock(hmem), (UINT)::GlobalSize(hmem));

	LPTSTR szBuffer = new TCHAR[::GlobalSize(hmem)];
	if (!szBuffer)
		return FALSE;

	sf.Read(szBuffer, (UINT)::GlobalSize(hmem));
	::GlobalUnlock(hmem);

	CString strText = szBuffer;
	delete szBuffer;

	strText.LockBuffer();
	CString strLine = strText;
	int nLine = 0;

	int nCount	= GetItemCount_Child();
	int nHeader = this->GetHeaderCtrl()->GetItemCount();
	int nSize	= this->strfindch((char*)(LPCTSTR)strLine, '\n') + 1;
	int nIndex	= 0;
	int nSelected = 0;
	int nLastPasteItem;
	nLastPasteItem = nCount;
	int iItem, iSubItem;

	for(iItem=0; iItem<nCount; iItem++)
	{
		if(nIndex >= nSize)
			return FALSE;

		if(GetItemState(iItem, LVIS_SELECTED) & LVIS_SELECTED)
		{
			CString strCol;
			int len = strLine.Find("\n");
			if(len != -1)
			{
				strCol = strLine.Left(len);
				strLine.Delete(0, len + 1);
			}
			else
				strCol = strLine;

			if(strCol.IsEmpty())
				continue;

			BOOL bEnd = FALSE;
			for(iSubItem = 1; iSubItem<nHeader; iSubItem++)
			{
				if(GetColumnWidth(iSubItem) == 0)
					continue;

				len = strCol.Find("\t");
				CString str;
				if(len != -1)
					str = strCol.Left(len);
				else
				{
					str = strCol;
					bEnd = TRUE;
				}

				SetItemText(iItem, iSubItem, str);

				if(!bEnd)
					strCol.Delete(0, len + 1);
				else
					break;
			}

			SetItemState(iItem, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
			nIndex++;
			nSelected++;
			nLastPasteItem = iItem + 1;
		}
	}

	if(nSize > nSelected)
	{
		for(iItem=0; iItem<(nSize - nSelected); iItem++)
		{
			if(nIndex >= nSize)
				return FALSE;

			CString strCol;
			int len = strLine.Find("\n");
			if(len != -1)
			{
				strCol = strLine.Left(len);
				strLine.Delete(0, len + 1);
			}
			else
				strCol = strLine;

			if(strCol.IsEmpty())
				continue;

			InsertItem(nLastPasteItem, "");

			BOOL bEnd = FALSE;
			for(iSubItem = 1; iSubItem<nHeader; iSubItem++)
			{
				if(GetColumnWidth(iSubItem) == 0)
					continue;

				len = strCol.Find("\t");
				CString str;
				if(len != -1)
					str = strCol.Left(len);
				else
				{
					str = strCol;
					bEnd = TRUE;
				}

				SetItemText(iItem, iSubItem, str);

				if(!bEnd)
					strCol.Delete(0, len + 1);
				else
					break;
			}

			SetItemState(nLastPasteItem, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
			nIndex++;
			nLastPasteItem++;
		}

		UpdateListID();
	}

	strText.UnlockBuffer();

	return TRUE;
}

int CEditableListCtrl::strfindch(char* str, char ch)
{
	int count = 0;

	if(strlen(str) < 1)
		return -1;

	char *p = str;

	while(*p != '\0')
	{
		if(*p == ch)
			count ++;
		p++;
	}
	return count;
}

void CEditableListCtrl::PasteItemData(int iItem)
{
	if(m_iSubItemEditing != -1 && (m_Edit.IsWindowVisible() || m_ComboBox.IsWindowVisible()))
		return;

	if(iItem != -1)
		SetItemState(iItem, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);

	PasteTextToGrid();
}

void CEditableListCtrl::UpdateListID()
{
	char szIndex[32] = {0};
	for(int nIndex = 0;nIndex<GetItemCount_Child();nIndex++)
	{
		SetItemText(nIndex, 0, itoa(nIndex + 1, szIndex, 10));
		Update(nIndex);
	}
}

void CEditableListCtrl::AddEditCell(int iItem, int iSubItem)
{
	if(iItem < 0 || iSubItem < 0)
		return;

	DWORD dwKey = MAKEWORD(iItem, iSubItem);

	LVCELLID lvCell;
	lvCell.iItem = iItem;
	lvCell.iSubItem = iSubItem;

	m_mapEditCellID.SetAt(dwKey, lvCell);
}

void CEditableListCtrl::RemoveEditCell(int iItem, int iSubItem)
{
	if(iItem < 0 || iSubItem < 0)
		return;

	DWORD dwKey = MAKEWORD(iItem, iSubItem);
	m_mapEditCellID.RemoveKey(dwKey);
}

BOOL CEditableListCtrl::IsEditCell(int iItem, int iSubItem)
{
	if(iItem < 0 || iSubItem < 0)
		return FALSE;

	DWORD dwKey = MAKEWORD(iItem, iSubItem);
	LVCELLID lvCell;
	return m_mapEditCellID.Lookup(dwKey, lvCell);
}

void CEditableListCtrl::AddComboEditColumn(int iSubItem)
{
	if(iSubItem < 0)
		return;
	
	if(!m_ComboEditList.Find(iSubItem))
		m_ComboEditList.AddTail(iSubItem);
}

void CEditableListCtrl::RemoveComboEditColumn(int iSubItem)
{
	if(iSubItem < 0 || m_ComboEditList.GetCount() < 1)
		return;

	POSITION pos = m_ComboEditList.Find(iSubItem);
	if(pos != NULL)
		m_ComboEditList.RemoveAt(pos);
}	

BOOL CEditableListCtrl::IsComboEditColumn(int iSubItem)
{
	if(iSubItem < 0 || m_ComboEditList.GetCount() < 1)
		return FALSE;

	POSITION pos = m_ComboEditList.Find(iSubItem);
	if(pos == NULL) 
		return FALSE;
	else
		return TRUE;
}

void CEditableListCtrl::SetItemColor(int iItem, int iSubItem, COLORREF clr)
{
	DWORD dwItem = MAKEWORD(iItem, iSubItem);
	m_mapCellColor.SetAt(dwItem, clr);
}

void CEditableListCtrl::ResetItemColor(int iItem, int iSubItem)
{
	DWORD dwItem = MAKEWORD(iItem, iSubItem);
	m_mapCellColor.RemoveKey(dwItem);
}

void CEditableListCtrl::SetItemTextColor(int iItem, int iSubItem, COLORREF clr)
{
	DWORD dwItem = MAKEWORD(iItem, iSubItem);
	m_mapTextColor.SetAt(dwItem, clr);
}

void CEditableListCtrl::ResetItemTextColor(int iItem, int iSubItem)
{
	DWORD dwItem = MAKEWORD(iItem, iSubItem);
	m_mapTextColor.RemoveKey(dwItem);
}

BOOL CEditableListCtrl::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(!m_bEnableHotKey)
		return CListCtrl::PreTranslateMessage(pMsg);

	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_DELETE)
			DeleteRows();

		if(IsCTRLpressed())
		{
			switch (pMsg->wParam)
			{
			case 'C':
				CopyItemData();
				break;
			case 'V':
				PasteItemData();
				break;
			default:
				break;
			}
		}	
	}

	return CListCtrl::PreTranslateMessage(pMsg);
}

CRect CEditableListCtrl::GetEditButtonRect()
{
	CRect rect;
	rect.SetRectEmpty();
	if(!m_EditButton.GetSafeHwnd())
		return rect;

	m_EditButton.GetWindowRect(&rect);

	return rect;
}

CRect CEditableListCtrl::GetComboButtonRect()
{
	CRect rect;
	rect.SetRectEmpty();
	if(!m_ComboButton.GetSafeHwnd())
		return rect;

	m_ComboButton.GetWindowRect(&rect);

	return rect;
}

CString CEditableListCtrl::GetEditText()
{
	CString strText;
	m_Edit.GetWindowText(strText);
	return strText;
}

CString CEditableListCtrl::GetComboText()
{
	CString strText;
	m_ComboBox.GetWindowText(strText);
	return strText;
}


//////////////////////////////////////////////////////////////////////////////////////////////
//VirtualListCtrl

CVirtualListCtrl::CVirtualListCtrl()
{
}

CVirtualListCtrl::~CVirtualListCtrl()
{
	for(int i=0; i<m_datas.GetSize(); i++)
		delete (CStringArray*)m_datas[i];
	m_datas.RemoveAll();
}


BEGIN_MESSAGE_MAP(CVirtualListCtrl, CEditableListCtrl)
//{{AFX_MSG_MAP(CVirtualListCtrl)
ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetdispinfo)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVirtualListCtrl message handlers
void CVirtualListCtrl::InsertItem_V(int iItem, const CString& str)
{
	int nCnt = this->GetHeaderCtrl()->GetItemCount();
	
	CStringArray* pStrArray = new CStringArray;
	pStrArray->Add(str);
	for(int i=1; i<nCnt; i++)
		pStrArray->Add("");
	m_datas.InsertAt(iItem, pStrArray, 1);
}

void CVirtualListCtrl::SetItemText_V(int iItem, int iSubItem, const CString& str)
{
	if(iItem >= m_datas.GetSize())
		return;
	if(iSubItem >= ((CStringArray*)m_datas[iItem])->GetSize())
		return;
	
	((CStringArray*)m_datas[iItem])->ElementAt(iSubItem) = str;
}

void CVirtualListCtrl::DeleteAllItems_V()
{
	this->SetItemCount(0);
	
	for(int i=0; i<m_datas.GetSize(); i++)
		delete (CStringArray*)m_datas[i];
	m_datas.RemoveAll();
}

void CVirtualListCtrl::RefreshDatas_V()
{
	this->SetItemCount(m_datas.GetSize());
}

void CVirtualListCtrl::OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	*pResult = 0;
	
	if(m_datas.GetSize() == 0)
		return;
	
	if(pDispInfo->item.mask & LVIF_TEXT)
	{
		int iItem = pDispInfo->item.iItem;
		int iSubItem = pDispInfo->item.iSubItem;
		if(iItem >= m_datas.GetSize())
			return;
		if(iSubItem >= ((CStringArray*)m_datas[iItem])->GetSize())
			return;
		
		lstrcpyn(pDispInfo->item.pszText, 
			((CStringArray*)m_datas[iItem])->GetAt(iSubItem), 
			pDispInfo->item.cchTextMax);
	}
}

void CVirtualListCtrl::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	CEditableListCtrl::PreSubclassWindow();
	
	SetWindowLong(m_hWnd, GWL_STYLE, WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_OWNERDRAWFIXED | LVS_OWNERDATA);
}

void CEditableListCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	

	if(IsComboEditColumn(m_iSubItemEditing))
	{
		LVHITTESTINFO	lvhtinfo;
		GetCursorPos(&lvhtinfo.pt);
		ScreenToClient(&lvhtinfo.pt);
		SubItemHitTest(&lvhtinfo);

		if(lvhtinfo.flags & LVHT_ONITEM)
		{
			if(lvhtinfo.iItem != m_iItemEditing || lvhtinfo.iSubItem != m_iSubItemEditing)
				EndEdit();
		}
		else
		{
			EndEdit();
		}
	}

	CListCtrl::OnLButtonDown(nFlags, point);
}
