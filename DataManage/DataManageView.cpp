// DataManageView.cpp : implementation of the CDataManageView class
//

#include "stdafx.h"
#include "DataManage.h"

#include "DataManageDoc.h"
#include "DataManageView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
CDataManageView *g_DtMngView = NULL;
/////////////////////////////////////////////////////////////////////////////
// CDataManageView

IMPLEMENT_DYNCREATE(CDataManageView, CFormView)

BEGIN_MESSAGE_MAP(CDataManageView, CFormView)
	//{{AFX_MSG_MAP(CDataManageView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	ON_WM_CONTEXTMENU()
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataManageView construction/destruction

CDataManageView::CDataManageView()
	: CFormView(CDataManageView::IDD)
{
	//{{AFX_DATA_INIT(CDataManageView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here
	g_DtMngView = this;
	m_uMenuSelRow = 0;
	m_uMenuSelCol = 0;
}

CDataManageView::~CDataManageView()
{
	int i = 0;
	m_ShowInfoList.DestroyWindow();

	m_ReportMng.DestroyWindow();

	m_ResultSearch.DestroyWindow();
	m_ResultSearchNew.DestroyWindow();

	m_ExcelOptFun2.DeleteItemInfo();
	m_ModeParMng2.DeleteItemInfo();
}

void CDataManageView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataManageView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CDataManageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	
	return CFormView::PreCreateWindow(cs);
}

void CDataManageView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	
	m_ModeParMng2.NewItemInfo();
	m_ExcelOptFun2.NewItemInfo();
	m_ModeXmlAnalysis2.m_pParMng = &m_ModeParMng2;


	//m_UsrMng.Create(IDD_USERMENAGE_DLG,this);

	//m_ProdMng.Create(IDD_PRODMNG_DLG,this);
	//m_DepartMng.Create(IDD_DEPARTMNG_DLG,this);

	//m_HisExtremum.Create(IDD_HIS_EXTREMUM_DLG,this);

	//m_ModeMng.Create(IDD_MODEMNG_DLG,this);

	//m_TaskMng.Create(IDD_TASK_MNG_DLG,this);

	//m_TaskLoadOut.Create(IDD_TASK_LOADOUT_DLG,this);
	//m_TaskLoadIn.Create(IDD_TASK_LOADIN_DLG,this);
	
	m_ShowInfoList.m_ShowModeInfo.m_ShowModeStyle.m_pModeParMng = &m_ModeParMng2;
	m_ShowInfoList.m_ShowModeInfo.m_ShowModeStyle.m_pExcelOptFun = &m_ExcelOptFun2;
	m_ShowInfoList.m_ShowModeInfo.m_ShowModeStyle.m_pModeXmlAnalysis = &m_ModeXmlAnalysis2;

	m_ShowInfoList.m_ShowTaskInfo.m_ShowTaskData.m_pModeParMng = &m_ModeParMng2;
	m_ShowInfoList.m_ShowTaskInfo.m_ShowTaskData.m_pModeXmlAnalysis = &m_ModeXmlAnalysis2;

	m_ShowInfoList.Create(IDD_SHOWLIST_DLG,this);

	m_ReportMng.Create(IDD_REPORT_MNG,this);
	
	m_ResultSearch.Create(IDD_RESULT_SEARCH_DLG,this);
	m_ResultSearchNew.Create(IDD_RESULT_SEARCH_NEW_DLG, this);
	

	
	
	
}

/////////////////////////////////////////////////////////////////////////////
// CDataManageView printing

void CDataManageView::OnFilePrintPreview() 
{
	BCGPPrintPreview (this);
}

BOOL CDataManageView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return BCGPPreparePrinting (this, pInfo);
}

void CDataManageView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDataManageView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CDataManageView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CDataManageView diagnostics

#ifdef _DEBUG
void CDataManageView::AssertValid() const
{
	CFormView::AssertValid();
}

void CDataManageView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CDataManageDoc* CDataManageView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDataManageDoc)));
	return (CDataManageDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDataManageView message handlers

void CDataManageView::OnContextMenu(CWnd*, CPoint point)
{
	//theApp.ShowPopupMenu (IDR_CONTEXT_MENU, point, this);
}
void CDataManageView::ChangeViewMode(int nMenuSelRow, int nMenuSelCol)
{
	m_uMenuSelRow = nMenuSelRow;
	m_uMenuSelCol = nMenuSelCol;
	//用户管理//
	//m_UsrMng.ShowWindow(SW_HIDE);

	//基础信息管理//
	//m_ProdMng.ShowWindow(SW_HIDE);
	//m_DepartMng.ShowWindow(SW_HIDE);

	//m_HisExtremum.ShowWindow(SW_HIDE);

	//m_ModeMng.ShowWindow(SW_HIDE);
	
	//m_TaskMng.ShowWindow(SW_HIDE);
	//m_TaskLoadOut.ShowWindow(SW_HIDE);
	//m_TaskLoadIn.ShowWindow(SW_HIDE);
	m_ResultSearch.ShowWindow(SW_HIDE);
	m_ResultSearchNew.ShowWindow(SW_HIDE);
	m_ReportMng.ShowWindow(SW_HIDE);
	m_ShowInfoList.ShowWindow(SW_HIDE);
	
	AdjustSize();
}
void CDataManageView::AdjustSize()
{
	CRect Rect ;
	GetClientRect(&Rect) ;
	int iBord=1 ;
	int iHeight = 50;


	if (GetDlgItem(IDD_DATAMANAGE_STATIC1)->GetSafeHwnd())
	{
		GetDlgItem(IDD_DATAMANAGE_STATIC1)->MoveWindow((Rect.left+Rect.Width()/2)-50,10,100,30);
	}
	switch(m_uMenuSelRow)
	{
	case 0:
		{
			switch(m_uMenuSelCol)
			{
			case 0:
				{
					if(IsWindow(m_ShowInfoList.m_hWnd))
					{
						m_ShowInfoList.MoveWindow(iBord,0,Rect.Width(),Rect.Height());
						m_ShowInfoList.ShowWindow(SW_SHOW);
					}
					break;
				}
			}
		}
		break;
	case 1:
		{
			switch (m_uMenuSelCol)
			{
			case 1:
				{
					/*if (IsWindow(m_UsrMng.m_hWnd))
					{
						m_UsrMng.MoveWindow(iBord,0,Rect.Width(),Rect.Height());
						m_UsrMng.ShowWindow(SW_SHOW);
					}*/
				}
				break;
			}
		}
		break;
	case 2:
		{
			switch (m_uMenuSelCol)
			{
			case 1:
				{
					/*if(IsWindow(m_ProdMng.m_hWnd))
					{
						m_ProdMng.MoveWindow(iBord,0,Rect.Width(),Rect.Height());
						m_ProdMng.ShowWindow(SW_SHOW);
					}*/
				}
				break;
			case 2:
				{
					/*if (IsWindow(m_DepartMng.m_hWnd))
					{
						m_DepartMng.MoveWindow(iBord,0,Rect.Width(),Rect.Height());
						m_DepartMng.ShowWindow(SW_SHOW);
					}*/
				}
				break;
			}
		}
		break;
	
	case 3:
		{
			switch (m_uMenuSelCol)
			{
			case 1:
				{
					
				}
				break;
			}
		}
		break;
	case 4:
		{
			switch (m_uMenuSelCol)
			{
			case 1:
				{
					/*if (IsWindow(m_HisExtremum.m_hWnd))
					{
						m_HisExtremum.MoveWindow(iBord,0,Rect.Width(),Rect.Height());
						m_HisExtremum.ShowWindow(SW_SHOW);
					}*/
				}
				break;
			}
		}
		break;
	case 5:
		{
			switch (m_uMenuSelCol)
			{
			case 1:
				{
					/*if (IsWindow(m_TaskMng.m_hWnd))
					{
						m_TaskMng.MoveWindow(iBord,0,Rect.Width(),Rect.Height());
						m_TaskMng.ShowWindow(SW_SHOW);
					}*/
				}
				break;
			case 2:
				{
				}
				break;
			case 3:
				{
					/*if (IsWindow(m_TaskLoadOut.m_hWnd))
					{
						m_TaskLoadOut.MoveWindow(iBord,0,Rect.Width(),Rect.Height());
						m_TaskLoadOut.ShowWindow(SW_SHOW);
					}*/
				}
				break;
			case 4:
				{
					/*if (IsWindow(m_TaskLoadIn.m_hWnd))
					{
						m_TaskLoadIn.MoveWindow(iBord,0,Rect.Width(),Rect.Height());
						m_TaskLoadIn.ShowWindow(SW_SHOW);
					}*/
				}
				break;
			}
		}
		break;
	case 6:
		{
			switch (m_uMenuSelCol)
			{
			case 1:
				{
					if (IsWindow(m_ResultSearch.m_hWnd))
					{
						m_ResultSearch.MoveWindow(iBord,0,Rect.Width(),Rect.Height());
						m_ResultSearch.ShowWindow(SW_HIDE);
					}
					if (IsWindow(m_ResultSearchNew.m_hWnd))
					{
						m_ResultSearchNew.MoveWindow(iBord,0,Rect.Width(),Rect.Height());
						m_ResultSearchNew.ShowWindow(SW_SHOW);
					}

				}
				break;
			}
		}
		break;
	case 7:
		{
			switch(m_uMenuSelCol)
			{
			case 3:
				{
					if(IsWindow(m_ReportMng.m_hWnd))
					{
						m_ReportMng.MoveWindow(iBord,0,Rect.Width(),Rect.Height());
						m_ReportMng.ShowWindow(SW_SHOW);
					}
				}
			}
		}
		break;

	}
	
	
}

void CDataManageView::OnSize(UINT nType, int cx, int cy)
{
	
	CFormView::OnSize(nType, cx, cy);
	AdjustSize();
}

void CDataManageView::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	int i = 0;
	
	
	CFormView::OnClose();
}
