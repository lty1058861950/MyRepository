#if !defined(AFX_EDITABLELISTCTRL_H__525BC59B_08C9_46B8_A764_DF88579B5FCC__INCLUDED_)
#define AFX_EDITABLELISTCTRL_H__525BC59B_08C9_46B8_A764_DF88579B5FCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditableListCtrl.h : header file
//
#include "afxole.h"
#include "afxadv.h"
#include "afxconv.h"
#include <afxtempl.h>

#define RECORD_STATE_PRE_EDIT		0x4000
#define RECORD_STATE_MODIFIED		0x2000

#define DEF_ITEM_HEIGHT				22						//列宽
#define MODE_EDIT_ALL				1

#define DEF_COL_BLUE				RGB(177,235,248)
#define DEF_COL_WHITESMOKE			RGB(240,240,240)
#define DEF_COL_GREEN				RGB(128, 255, 128)
#define DEF_COL_YELLOW				RGB(255, 246, 143)
#define DEF_COL_RED					RGB(255,0,0)
#define DEF_COL_RRED                RGB(255,211,211)
#define DEF_COL_BLACK				RGB(0,0,0)
#define DEF_COL_WHITE				RGB(255,255,255)
#define DEF_COL_NAVAJOWHITE			RGB(236, 233, 216)
#define DEF_COL_GREY				RGB(192,192,192)
#define DEF_COL_APPLEGREEN			RGB(199, 237, 204)
#define DEF_COL_PALEGREEN			RGB(124, 205, 124)

#define DEF_EDIT_RECORD_INDICATOR_TEXT	_T("点击编辑新记录...")

#define Edit_Button_ID					0x1000
#define Combo_Button_ID					0x1001

#define ELM_CELL_EDIT_BEGIN			WM_USER + 100
#define ELM_CELL_EDIT_END			WM_USER + 101
#define ELM_DELETE_ITEM				WM_USER + 102
#define ELM_EDIT_BUTTON_CLICK		WM_USER + 103
#define ELM_COMBO_BUTTON_CLICK		WM_USER + 104
#define ELM_ADD_ITEM_FRO_EDIT		WM_USER + 105

typedef struct tagLVCELLID
{
	int iItem;
	int iSubItem;
	
	bool operator==(const tagLVCELLID &cell) const
	{
		return  iItem == cell.iItem &&
				iSubItem == cell.iSubItem;
	}

}LVCELLID;

#include "CellEditor.h"
#include "CellCombo.h"
/////////////////////////////////////////////////////////////////////////////
// CEditableListCtrl window

class CEditableListCtrl : public CListCtrl
{
	friend class CCellEditor;
	friend class CCellCombo;

// Construction
public:
	CEditableListCtrl();

	// Operations
	void SetEditable(BOOL bEditable = TRUE);
	BOOL IsEditable() const { return m_bEditable; }

	void RemoveItemModified(int iItem) { SetItemData(iItem, GetItemData(iItem) & ~RECORD_STATE_MODIFIED); }
	void SetItemModified(int iItem)    { SetItemData(iItem, GetItemData(iItem) | RECORD_STATE_MODIFIED); }
	BOOL IsItemModified(int iItem)     { return (GetItemData(iItem) & RECORD_STATE_MODIFIED); }

	void RemoveItemPreEdit(int iItem)  { SetItemData(iItem, GetItemData(iItem) & ~RECORD_STATE_PRE_EDIT); SetItemText(iItem, 0, _T("")); }
	void SetItemPreEdit(int iItem)     { SetItemData(iItem, GetItemData(iItem) | RECORD_STATE_PRE_EDIT); }
	BOOL IsItemPreEdit(int iItem)	   { return (GetItemData(iItem) & RECORD_STATE_PRE_EDIT); }

	void UpdateListID();
	void DeleteRows();
	void DeleteAllItems_Child();

	int  AddItemForEdit();
	int  GetItemCount_Child();
	int  GetFirstSelectedItem();

	//如果不想调用该类的右键Menu，可调用次函数将bEnable设为false
	void EnableRClickMenu(BOOL bEnable = FALSE) { m_bEnableRClickMenu = bEnable; }
	void EnableOnClick(BOOL bEnable = FALSE)    { m_bEnableClick = bEnable; }
	void EnableHotKey(BOOL bEnable = FALSE)		{ m_bEnableHotKey = bEnable; }

	// 无法重载父类的 GetItemText
	CString GetItemText2(int nItem, const CString& strTitle);

	//复制粘贴
	void CopyItemData(int iItem = -1);
	void PasteItemData(int iItem = -1);
	COleDataSource* CopyTextFromList();
	BOOL PasteTextToGrid();
	int  strfindch(char* str, char ch);

	//comboBox
	void AddStringToList(DWORD key, const CString& str);
	void DeleteAllStringLists();
	void ClearStringList(DWORD key);

	BOOL BindListToItem(int iSubItem, DWORD key);
	BOOL UnBindListToItem(int iSubItem);
	BOOL IsItemBindToList(int iSubItem);

	void AddComboEditColumn(int iSubItem);
	void RemoveComboEditColumn(int iSubItem);
	void RemoveAllComboEditColumn() { m_ComboEditList.RemoveAll(); }
	BOOL IsComboEditColumn(int iSubItem);

	//是否在Edit里启用Button
	void  EnableEditButton(BOOL bEnable) { m_bEnableEditButton = bEnable; }
	CRect GetEditButtonRect();

	//是否在Combo里启用Button
	void  EnableComboButton(BOOL bEnable) { m_bEnableComboButton = bEnable; }
	CRect GetComboButtonRect();

	//Edit	
	void SetNumOnly(BOOL bNum)      { m_Edit.m_NumberOnly = bNum; }

	//添加可编辑的单元格，调用这些方法，SetEditable()必须为False
	void AddEditCell(int iItem, int iSubItem);
	void RemoveEditCell(int iItem, int iSubItem);
	void RemoveAllEditCell() { m_mapEditCellID.RemoveAll(); }
	BOOL IsEditCell(int iItem, int iSubItem);

	CString GetEditText();
	void SetEditText(LPCSTR lpText) { m_Edit.SetWindowText(lpText); }

	CString GetComboText();
	void SetComboText(LPCSTR lpText) { m_ComboBox.SetWindowText(lpText);}

	//Color
	void SetAutoItemColor(BOOL bUse = TRUE, BOOL bBkColor = FALSE) 
	{ 
		m_bAutoColor = bUse; 
		if(!bBkColor)
			SetBkColor(DEF_COL_WHITE);
		else
			SetBkColor(GetSysColor(COLOR_3DSHADOW));
	}

	void SetItemTextColor(int iItem, int iSubItem, COLORREF clr);
	void ResetItemTextColor(int iItem, int iSubItem);
	void ResetAllItemTextColor() { m_mapTextColor.RemoveAll(); }

	void SetItemColor(int iItem, int iSubItem, COLORREF clr);
	void ResetItemColor(int iItem, int iSubItem);
	void ResetAllItemColor() { m_mapCellColor.RemoveAll(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditableListCtrl)
	protected:
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct );
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	CCellCombo		m_ComboBox;
	CCellEditor     m_Edit;
	CButton			m_EditButton;
	CButton			m_ComboButton;

	virtual ~CEditableListCtrl();
	virtual void BeginEdit(int iItem, int iSubItem);
	virtual void EndEdit();

protected:
	CMenu			m_PopupMenu;
	CMenu			m_DeleteMenu;
	CMenu			m_PasteMenu;		
		
	int				m_iItemEditing;
	int				m_iSubItemEditing;
	int				m_iSubItemNumberOnly1;
	int				m_iSubItemNumberOnly2;
	int				m_nEditMode;

	BOOL			m_bEditable;
	BOOL			m_bAutoColor;
	BOOL			m_bEnableRClickMenu;
	BOOL			m_bEnableClick;
	BOOL            m_bEnableEditButton;
	BOOL            m_bEnableComboButton;
	BOOL			m_bEnableHotKey;

	const static int m_nPaddingLeft;
	const static COLORREF m_clrGridLine;

	CMapPtrToPtr	m_mapListBind;
	CMap<DWORD, DWORD, void*, void*>		m_mapItemList;		// Ptr of CStringArray
	CMap<DWORD, DWORD, LVCELLID, LVCELLID&> m_mapEditCellID;
	CMap<DWORD, DWORD, COLORREF, COLORREF>	m_mapCellColor;
	CMap<DWORD, DWORD, COLORREF, COLORREF>	m_mapTextColor;
	
	CList<int, int> m_ComboEditList;

	enum eMenuOptions { IDM_DELETE_ITEM = 100,
						IDM_DELETE_ALL_ITEMS,
						IDM_INSERT_ITEM,
						IDM_COPY_ITEM,
						IDM_PASTE_ITEM
	};

	// Generated message map functions
protected:
	//{{AFX_MSG(CEditableListCtrl)
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);	
	afx_msg void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct); 
	afx_msg BOOL OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg BOOL OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

/////////////////////////////////////////////////////////////////////////////

class CVirtualListCtrl : public CEditableListCtrl
{
	// Construction
public:
	CVirtualListCtrl();
	
	// Attributes
public:
	
	// Operations
public:
	void InsertItem_V(int iItem, const CString& str);
	void SetItemText_V(int iItem, int iSubItem, const CString& str);
	void DeleteAllItems_V();
	void RefreshDatas_V();
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVirtualListCtrl)
protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	virtual ~CVirtualListCtrl();
	
protected:
	CPtrArray	m_datas;
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CVirtualListCtrl)
	afx_msg void OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITABLELISTCTRL_H__525BC59B_08C9_46B8_A764_DF88579B5FCC__INCLUDED_)
