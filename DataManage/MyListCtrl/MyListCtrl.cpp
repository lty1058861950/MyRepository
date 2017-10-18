// MyListCtrl.cpp : implementation file
//

#include "StdAfx.h"
#include "MyListCtrl.h"
/*
#include "../DataTest.h"
#include "../DataTestDoc.h"
#include "../DataTestView.h"
*/

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//extern CDataTestView *g_pMainFrame;

//×¢Òâ£ºListCtrl Style ÊôÐÔÑ¡ ICO

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl

CMyListCtrl::CMyListCtrl()
{
}

CMyListCtrl::~CMyListCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CMyListCtrl)	
	ON_WM_MEASUREITEM_REFLECT()
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl message handlers

void CMyListCtrl::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	if (m_type == 1)
	{
		//g_pMainFrame->m_wndTab.m_pDlgInfFun2->ShowListCtrlMenu();
	}
	else if (m_type == 2)
	{
		//g_pMainFrame->m_wndTab.m_pDlgInfFun3->ShowListCtrlMenu();
	}

	*pResult = 0;
}

void CMyListCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	lpMeasureItemStruct->itemHeight = 20;
}
