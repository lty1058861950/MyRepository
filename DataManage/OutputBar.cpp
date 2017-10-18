// OutputBar.cpp : implementation of the COutputBar class
//

#include "stdafx.h"
#include "DataManage.h"
#include "OutputBar.h"
#include "OracleOci\\OracleOciDbMng.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int nBorderSize = 1;

/////////////////////////////////////////////////////////////////////////////
// COutputBar

BEGIN_MESSAGE_MAP(COutputBar, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(COutputBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputBar construction/destruction

COutputBar::COutputBar()
{
	// TODO: add one-time construction code here
	m_pGrid = NULL;
}

COutputBar::~COutputBar()
{

	if (m_pGrid != NULL)
	{
		delete m_pGrid;
		m_pGrid = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////
// COutputBar message handlers

int COutputBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rectDummy;
	rectDummy.SetRectEmpty ();

	// Create tabs window:
	if (!m_wndTabs.Create (CBCGPTabWnd::STYLE_FLAT, rectDummy, this, 1))
	{
		TRACE0("Failed to create output tab window\n");
		return -1;      // fail to create
	}

	// Create list windows.
	// TODO: create your own window here:
	/*const DWORD dwViewStyle =	
		LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;*/
	const DWORD dwViewStyle =	
		LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;
	
	CRect rectDummy2(1,1,100,100);
	if (!m_wndList1.Create (dwViewStyle, rectDummy2, &m_wndTabs, 1002) ||
		!m_wndList2.Create (dwViewStyle, rectDummy2, &m_wndTabs, 1003) ||
		!m_wndList3.Create (dwViewStyle, rectDummy2, &m_wndTabs, 1004)  )
	{
		TRACE0("Failed to create output view\n");
		return -1;      // fail to create
	}

	m_fontMark1.CreateFont(12,0,0,0,200,0,0,0,134,3,2,1,2,_T("Arial"));			//普通
	InitOutList();


	//InitGridRadiate();
	//InitGridCtrl();
	// Attach list windows to tab:
	m_wndTabs.AddTab (&m_wndList1, _T("Output 1"), -1);
	m_wndTabs.AddTab (&m_wndList2, _T("Output 2"), -1);
	m_wndTabs.AddTab (&m_wndList3, _T("Output 3"), -1);


	/*m_OutPutInfoList.Create(IDD_OUTPUT_INFO_DLG,this);
	m_OutPutInfoList.ShowWindow(SW_SHOW);*/

	return 0;
}

BOOL COutputBar::InitGridRadiate()
{
	CWnd *pWnd;
	pWnd = this; //	pWnd = GetDlgItem(IDC_STATIC_AREA);

	if(m_pGrid != NULL)
	{
		delete m_pGrid;
		m_pGrid = NULL;
	}

	if(m_pGrid == NULL)
	{
		m_pGrid = new CGridCtrl(0,0,0,0);
		CRect rc;
		GetClientRect(&rc);
		m_pGrid->Create(rc, pWnd, IDC_GRID, WS_CHILD|WS_VISIBLE);
		m_pGrid->SetEditable(TRUE);


		m_pGrid->SetTextColor(GRID_TEXT_COLOR);

		m_pGrid->SetTextBkColor(GRID_TEXT_BK_COLOR);

		m_pGrid->SetBkColor(GRID_BK_COLOR);

		m_pGrid->SetGridColor( MY_GRID_LINE_COLOR );

		m_pGrid->SetTitleTipBackClr( RGB(128,128,128) );
		m_pGrid->SetTitleTipTextClr( RGB(255,255,255) );
	}
	return TRUE;
}

void COutputBar::InitGridCtrl()
{
	CWnd *pWnd;
	int nRowCnt, nColCnt;
	int  row,col;
	int	 nDataPos;
	CString       str, str2;

	nRowCnt = 30; 
	nColCnt = 20;

	pWnd = this; //	pWnd = GetDlgItem(IDC_STATIC_AREA);

	if(m_pGrid != NULL)
	{
		delete m_pGrid;
		m_pGrid = NULL;
	}

	if(m_pGrid == NULL)
	{
		m_pGrid = new CGridCtrl();
		CRect rc;
		GetClientRect(&rc);
		m_pGrid->Create(rc, pWnd, IDC_GRID, WS_CHILD|WS_VISIBLE);
		m_pGrid->SetEditable(TRUE);

		m_pGrid->SetTextColor(GRID_TEXT_COLOR);

		m_pGrid->SetTextBkColor(GRID_TEXT_BK_COLOR);

		m_pGrid->SetBkColor(GRID_BK_COLOR);

		m_pGrid->SetGridColor( MY_GRID_LINE_COLOR );

		m_pGrid->SetTitleTipBackClr( RGB(128,128,128) );
		m_pGrid->SetTitleTipTextClr( RGB(255,255,255) );

		try
		{
			m_pGrid->SetRowCount(nRowCnt+1);
			m_pGrid->SetColumnCount(nColCnt+1);
			m_pGrid->SetFixedRowCount(1);
			m_pGrid->SetFixedColumnCount(1);
		}
		catch (CMemoryException* e)
		{
			e->ReportError();
			e->Delete();
		}

		CFont fontMark;
		//fontMark.CreateFont(14,0,0,0,200,0,0,0,134,3,2,1,2,_T("Arial"));			//普通
		fontMark.CreateFont(14,0,0,0,FW_SEMIBOLD,0,0,0,134,3,2,1,2,_T("Arial"));	//加粗
		m_pGrid->SetFont(&fontMark);

		nDataPos = 0;
		for(row=0; row<m_pGrid->GetRowCount(); row++)
		{
			for(col=0; col<m_pGrid->GetColumnCount(); col++)
			{
				GV_ITEM Item;
				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = row;
				Item.col = col;

				if(row==0 && col==0)
				{
					Item.nFormat = DT_WORDBREAK|DT_VCENTER|DT_CENTER;//;
					Item.strText.Format(" ");
				}
				else if(row < 1)
				{
					Item.nFormat = DT_WORDBREAK|DT_VCENTER|DT_CENTER;//|DT_VCENTER;
					Item.strText.Format("%C", col+0x40);
				}
				else if(col <1)
				{
					Item.nFormat = DT_WORDBREAK|DT_VCENTER|DT_CENTER;//|DT_VCENTER;
					Item.strText.Format("%d", row);
				}
				else
				{

				}

				m_pGrid->SetItem(&Item);

				m_pGrid->SetItemState(row,col, m_pGrid->GetItemState(row,col) | GVIS_READONLY);

			}
			m_pGrid->Invalidate();
		}

		m_pGrid->AutoSize();
		m_pGrid->AutoSizeRows();      //自动设置行高

		//---------------------------------------------------------
		for(col=0; col<m_pGrid->GetColumnCount(); col++)
		{
			if (col == 0)
			{
				m_pGrid->SetColumnWidth(col, 40);
			}
			else
			{
				m_pGrid->SetColumnWidth(col, 100);
			}		
		}

		for(row=0; row<m_pGrid->GetRowCount(); row++)
		{
			if(row ==0)
			{
				m_pGrid->SetRowHeight(row, 30);
			}else
			{
				m_pGrid->SetRowHeight(row, 40);
			}

		}


		//设置第一行，第一列颜色
		//---------------------------------------------------------
		for(col=0; col<m_pGrid->GetColumnCount(); col++)
		{	
			m_pGrid->SetItemBkColour(0, col, MY_TABLE_HEAD_COLOR);
		}

		for(row=1; row<m_pGrid->GetRowCount(); row++)
		{	
			m_pGrid->SetItemBkColour(row, 0, MY_TABLE_HEAD_COLOR);
		}
	}

}

void COutputBar::InitOutList()
{
	int     i;
	CString	str;
	int     iColNum; 
	char	ItemName[20][30] = {"序号","时间","输出信息"};
	int     ItemLen[20]      = {80,150,1024};

	iColNum = 3;

	m_wndList1.ModifyStyle(LVS_TYPEMASK,LVS_REPORT);
	m_wndList1.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP|LVS_EX_FULLROWSELECT);
	m_wndList1.SetFont(&m_fontMark1);
	for (i=0; i<iColNum; i++)
	{
		str.Format("%s", ItemName[i]);
		m_wndList1.InsertColumn(i, str,   LVCFMT_LEFT, ItemLen[i]);	
	}

	int nCount = g_pOrcOciDb->m_InitText.GetCount();

	for (i =0 ;i<nCount;i++)
	{
		InsertErrorText(g_pOrcOciDb->m_InitText.GetAt(i));
	}

}


void COutputBar::InsertErrorText(CString strText)
{
	int Index,nCount = m_wndList1.GetItemCount();
	CString str;
	if(nCount>Max_Log_Item)
	{
		m_wndList1.DeleteAllItems();
	}

	nCount = m_wndList1.GetItemCount();

	str.Format(_T("%d"),nCount+1);
	Index = m_wndList1.InsertItem(nCount,str);
	m_wndList1.SetItemText(Index,1,GetDateTimeString());
	m_wndList1.SetItemText(Index,2,strText);
	CSize size(0,100) ;
	m_wndList1.Scroll(size) ;
}

void COutputBar::InsertErrorArrayText(vector<CString> &strErrorArray)
{
	int i, nCount;
	nCount = strErrorArray.size();
	for (i = 0;i<nCount;i++)
	{
		InsertErrorText(strErrorArray.at(i));
	}
}
/*
void COutputBar::DispLayInfo(CString szInfo)
{
	CString szIndex("1");

	m_pRadiate->InsertRow("",1);
	m_pRadiate->SetRowHeight(1,25);

	m_pRadiate->SetItemText(1,0,szIndex);
	m_pRadiate->SetItemText(1,1,szInfo);

	m_pRadiate->DeleteRow(m_pRadiate->GetRowCount()-1);

	for (int iRow=1;iRow<m_pRadiate->GetRowCount();iRow++)
	{
		CString sztext;
		sztext.Format("%d",iRow);
		m_pRadiate->SetItemText(iRow,0,sztext);
	}	
	m_pRadiate->Refresh();
}

*/
void COutputBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	// Tab control should cover a whole client area:
	m_wndTabs.SetWindowPos (NULL, -1, -1, cx, cy,
		SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);

	/*CRect rcRect;
	GetClientRect(&rcRect);
	if(m_OutPutInfoList.GetSafeHwnd())
	{
		m_OutPutInfoList.MoveWindow(0,0,rcRect.Width(),rcRect.Height());
	}*/
	
}

void COutputBar::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
	// TODO: 在此处添加消息处理程序代码
}
