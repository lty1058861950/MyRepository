// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "DataManage.h"
#include "DepartMng.h"
#include "MainFrm.h"

#include "UserMenage.h"
#include "ProdMng.h"
#include "ModeMng.h"
#include "TaskMng.h"
#include "LoadMesTask.h"
#include "LoadTaskInfo.h"

#include "CurDepartSel.h"
#include "ReportMode.h"
#include "SelDlg.h"
#include "UpDepart.h"
#include "TaskDownUpLoad.h"
#include "TestimonialMng.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
CMainFrame *g_MainFram = NULL;

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)


BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_VIEW_CUSTOMIZE, OnViewCustomize)
	ON_REGISTERED_MESSAGE(BCGM_RESETTOOLBAR, OnToolbarReset)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_2000, ID_VIEW_APPLOOK_WIN7, OnAppLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_2000, ID_VIEW_APPLOOK_WIN7, OnUpdateAppLook)
	ON_COMMAND(ID_MENU_USR_MNG, &CMainFrame::OnMenuUsrMng)//�û�����//
	ON_UPDATE_COMMAND_UI(ID_MENU_USR_MNG, &CMainFrame::OnUpdateMenuUsrMng)
	ON_COMMAND(ID_MENU_CHANGE_PWD, &CMainFrame::OnMenuChangePwd)//�޸�����//
	ON_WM_SIZE()
	ON_COMMAND(ID_MENU_DEPART_MNG, &CMainFrame::OnMenuDepartMng)//���첿�Ź���//
	ON_UPDATE_COMMAND_UI(ID_MENU_DEPART_MNG, &CMainFrame::OnUpdateMenuDepartMng)
	ON_COMMAND(ID_CURDEPART_MENU, &CMainFrame::OnCurdepartMenu)//��ǰ����ѡ��//
	ON_UPDATE_COMMAND_UI(ID_CURDEPART_MENU, &CMainFrame::OnUpdateCurdepartMenu)
	ON_COMMAND(ID_BATCH_SEL_PRODUCT_MENU, &CMainFrame::OnBatchSelProductMenu)//�Զ����Ʒѡ��//
	ON_WM_CLOSE()
	
	ON_COMMAND(ID_MENU_MODE_MMG, &CMainFrame::OnMenuModeMmg)//��Ӽ����¼ģ��//
	ON_UPDATE_COMMAND_UI(ID_MENU_MODE_MMG, &CMainFrame::OnUpdateMenuModeMmg)////
	ON_COMMAND(ID_MODE_COMPUTE_MENU, &CMainFrame::OnModeComputeMenu)//��ʽģ������//
	ON_UPDATE_COMMAND_UI(ID_MODE_COMPUTE_MENU, &CMainFrame::OnUpdateModeComputeMenu)
	ON_COMMAND(ID_REPORT_SET_MENU, &CMainFrame::OnReportSetMenu)//����ģ������//
	ON_UPDATE_COMMAND_UI(ID_REPORT_SET_MENU, &CMainFrame::OnUpdateReportSetMenu)

	ON_COMMAND(ID_ADD_TASK_MENU, &CMainFrame::OnAddTaskMenu)//�½���������//
	ON_UPDATE_COMMAND_UI(ID_ADD_TASK_MENU, &CMainFrame::OnUpdateAddTaskMenu)
	ON_COMMAND(ID_MENU_MES_TASK_LOAD_IN, &CMainFrame::OnMenuMesTaskLoadIn)//MES��������//
	ON_UPDATE_COMMAND_UI(ID_MENU_MES_TASK_LOAD_IN, &CMainFrame::OnUpdateMenuMesTaskLoadIn)

	ON_COMMAND(ID_MENU_EXCEL_TASK_LOAD_IN, &CMainFrame::OnMenuExcelTaskLoadIn)//Excel��������//
	ON_UPDATE_COMMAND_UI(ID_MENU_EXCEL_TASK_LOAD_IN, &CMainFrame::OnUpdateMenuExcelTaskLoadIn)

	ON_COMMAND(ID_BATCH_OUT_TASK_MENU, &CMainFrame::OnBatchOutTaskMenu)//���񵼳�//
	ON_COMMAND(ID_TASK_DATA_LOADIN, &CMainFrame::OnTaskDataLoadin)//���ݵ���//
	
	ON_COMMAND(ID_MENU_TASK_SEARCH, &CMainFrame::OnMenuTaskSearch)//��������Ľ����ѯ//
	ON_COMMAND(ID_MENU_RESULT_SEARCH, &CMainFrame::OnMenuResultSearch)//�����ѯ//
	ON_COMMAND(ID_MENU_RESULT_SUM, &CMainFrame::OnMenuResultSum)//�������ͳ��//
	ON_COMMAND(ID_MENU_TASK_MNG, &CMainFrame::OnMenuTaskMng) //�������//
	
	ON_WM_TIMER()
	ON_WM_CONTEXTMENU()
	
	ON_COMMAND(ID_TESTIMONIAL_MENU, &CMainFrame::OnTestimonialMenu)
	ON_UPDATE_COMMAND_UI(ID_TESTIMONIAL_MENU, &CMainFrame::OnUpdateTestimonialMenu)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_nAppLook = theApp.GetInt (_T("ApplicationLook"), ID_VIEW_APPLOOK_2007);
	g_MainFram = this;
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CBCGPToolBar::EnableQuickCustomization ();

	// Menu will not take the focus on activation:
	CBCGPPopupMenu::SetForceMenuFocus (FALSE);

	if (!m_wndMenuBar.Create (this))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}

	m_wndMenuBar.SetBarStyle(m_wndMenuBar.GetBarStyle() | CBRS_SIZE_DYNAMIC);

	// Detect color depth. 256 color toolbars can be used in the
	// high or true color modes only (bits per pixel is > 8):
	CClientDC dc (this);
	BOOL bIsHighColor = dc.GetDeviceCaps (BITSPIXEL) > 8;

	UINT uiToolbarHotID = bIsHighColor ? IDR_MAINFRAME : 0;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME, 0, 0, FALSE, 0, 0, uiToolbarHotID))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// Load control bar icons:
	CBCGPToolBarImages imagesWorkspace;
	imagesWorkspace.SetImageSize (CSize (16, 16));
	imagesWorkspace.SetTransparentColor (RGB (255, 0, 255));
	imagesWorkspace.Load (IDB_WORKSPACE);
	imagesWorkspace.SmoothResize(globalData.GetRibbonImageScale());

	CString strCurDepart;
	strCurDepart.Format(_T("��ǰ����:%s"),g_CurSelDepart.szGroupName);
	m_wndStatusBar.SetPaneWidth(3,200);
	m_wndStatusBar.SetPaneTextColor(3,RGB(0,0,0));
	m_wndStatusBar.SetPaneText(3,strCurDepart);

	if (!m_wndWorkSpace.Create (strCurDepart, this, CRect (0, 0, 200, 200),
		TRUE, ID_VIEW_WORKSPACE,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Workspace bar\n");
		return -1;      // fail to create
	}

	m_wndWorkSpace.SetIcon (imagesWorkspace.ExtractIcon (0), FALSE);


	if (!m_wndOutput.Create (_T("�����Ϣ"), this, CRect (0, 0, 150, 150),
		TRUE /* Has gripper */, ID_VIEW_OUTPUT,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create output bar\n");
		return -1;      // fail to create
	}

	m_wndOutput.SetIcon (imagesWorkspace.ExtractIcon (2), FALSE);

	m_wndToolBar.SetWindowText (_T("Standard"));
	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndWorkSpace.EnableDocking(CBRS_ALIGN_ANY);
	//m_wndWorkSpace2.EnableDocking(CBRS_ALIGN_ANY);
	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	EnableAutoHideBars(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndMenuBar);
	DockControlBar(&m_wndToolBar);
	DockControlBar (&m_wndWorkSpace);
	//m_wndWorkSpace2.AttachToTabWnd (&m_wndWorkSpace, BCGP_DM_STANDARD, FALSE, NULL);
	DockControlBar(&m_wndOutput);


	m_wndToolBar.EnableCustomizeButton (TRUE, ID_VIEW_CUSTOMIZE, _T("Customize..."));

	// Enable conttol bar context menu (list of bars + customize command):
	EnableControlBarMenu (	
		TRUE,				// Enable
		ID_VIEW_CUSTOMIZE, 	// Customize command ID
		_T("Customize..."),	// Customize command text
		ID_VIEW_TOOLBARS);	// Menu items with this ID will be replaced by
							// toolbars menu
	OnAppLook (m_nAppLook);


	
	//LoadUserType();
	//LoadProdType();
	//PostMessage(WM_MDIMAXIMIZE);
	//ShowWindow(SW_MAXIMIZE);

	//int wide = GetSystemMetrics(SM_CXSCREEN);
	//int height = GetSystemMetrics(SM_CYSCREEN);

	//MoveWindow(0,0,wide,height);

	//GetActiveWindow()->MoveWindow(0, 0, 1024,768);

	//this->SetWindowText( _T("����ʽ�ƶ��ɼ��������") );
	
	m_wndStatusBar.SetPaneWidth(1,100);
	m_wndStatusBar.SetPaneTextColor(1,RGB(0,0,0));
	CString strText;
	strText.Format(_T("��ǰ�û�:%s"),g_LoginUsrInfo.szLoginName);
	m_wndStatusBar.SetPaneText(1,strText);

	ModifyStyle(0,WS_CAPTION,SWP_FRAMECHANGED);

	SetTimer(100,1000,NULL);

	
	//ztadd for CLogFile
	g_pLogInfo   = new CLogFile("LogInfo");
	g_pLogInfo->Enable( );
	g_pLogInfo->m_MAX_ROW  = 1000;

	ReGetAllDepartInfo();//��ȡ���첿��//

	int t1,t2;
	CString str;

	t1= GetTickCount();

	m_ModeParMng.NewItemInfo();
	m_ExcelOptFun.NewItemInfo();

	m_ModeXmlAnalysis.m_pParMng = &m_ModeParMng;

	t2 = GetTickCount()-t1;
	str.Format(_T("���� CMainFrame.OnCreate,NewItemInfo ��ʱ %d ����"),t2);
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnViewCustomize()
{
	//------------------------------------
	// Create a customize toolbars dialog:
	//------------------------------------
	CBCGPToolbarCustomize* pDlgCust = new CBCGPToolbarCustomize (this,
		TRUE /* Automatic menus scaning */
		);

	pDlgCust->Create ();
}

afx_msg LRESULT CMainFrame::OnToolbarReset(WPARAM /*wp*/,LPARAM)
{
	// TODO: reset toolbar with id = (UINT) wp to its initial state:
	//
	// UINT uiToolBarId = (UINT) wp;
	// if (uiToolBarId == IDR_MAINFRAME)
	// {
	//		do something with m_wndToolBar
	// }

	return 0;
}

void CMainFrame::OnAppLook(UINT id)
{
	CBCGPDockManager::SetDockMode (BCGP_DT_STANDARD);

	m_nAppLook = id;

	CBCGPTabbedControlBar::m_StyleTabWnd = CBCGPTabWnd::STYLE_3D;

	switch (m_nAppLook)
	{
	case ID_VIEW_APPLOOK_2000:
		// enable Office 2000 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager));
		break;

	case ID_VIEW_APPLOOK_XP:
		// enable Office XP look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		// enable Windows XP look (in other OS Office XP look will be used):
		CBCGPWinXPVisualManager::m_b3DTabsXPTheme = TRUE;
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPWinXPVisualManager));
		break;

	case ID_VIEW_APPLOOK_2003:
		// enable Office 2003 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2003));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS2005:
		// enable VS 2005 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerVS2005));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS2008:
		// enable VS 2008 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerVS2008));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS2010:
		// enable VS 2010 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerVS2010));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	case ID_VIEW_APPLOOK_2007:
	case ID_VIEW_APPLOOK_2007_1:
	case ID_VIEW_APPLOOK_2007_2:
	case ID_VIEW_APPLOOK_2007_3:
		// enable Office 2007 look:

		switch (m_nAppLook)
		{
		case ID_VIEW_APPLOOK_2007:
			CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_2007_1:
			CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_2007_2:
			CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_Silver);
			break;

		case ID_VIEW_APPLOOK_2007_3:
			CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_Aqua);
			break;
		}

		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	case ID_VIEW_APPLOOK_2010_1:
	case ID_VIEW_APPLOOK_2010_2:
	case ID_VIEW_APPLOOK_2010_3:
		// enable Office 2010 look:
		switch (m_nAppLook)
		{
		case ID_VIEW_APPLOOK_2010_1:
			CBCGPVisualManager2010::SetStyle (CBCGPVisualManager2010::VS2010_Blue);
			break;

		case ID_VIEW_APPLOOK_2010_2:
			CBCGPVisualManager2010::SetStyle (CBCGPVisualManager2010::VS2010_Black);
			break;

		case ID_VIEW_APPLOOK_2010_3:
			CBCGPVisualManager2010::SetStyle (CBCGPVisualManager2010::VS2010_Silver);
			break;
		}

		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2010));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WIN7:
		// enable Windows 7 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerScenic));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	default:
		ASSERT (FALSE);
	}

	CBCGPDockManager* pDockManager = GetDockManager ();
	if (pDockManager != NULL)
	{
		ASSERT_VALID (pDockManager);
		pDockManager->AdjustBarFrames ();
	}

	CBCGPTabbedControlBar::ResetTabs ();

	RecalcLayout ();
	RedrawWindow (NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt (_T("ApplicationLook"), m_nAppLook);
}
void CMainFrame::Exit()
{
	CBCGPFrameWnd::OnClose();
}
void CMainFrame::OnClose()
{
	
	if(MessageBox(_T("ȷ���˳�ϵͳ?(ȷ��/ȡ��)��"),_T(""),MB_OKCANCEL|MB_ICONQUESTION) == IDOK)
	{
		KillTimer(100);
		

		int t1,t2;
		CString str;

		t1= GetTickCount();

		ReleaseProducts(&g_SelProducts);
		ReleaseGroups(&g_AllGroups);
		g_AllUpDeparts.clear();
		ReleaseRoles(&g_AllRoles);

		t2 = GetTickCount()-t1;
		str.Format(_T("�ͷ� CMainFrame::OnClose:Release ��ʱ %d ����"),t2);
		g_pLogInfo->WriteLogFile(str.GetBuffer(0));

		
		t1= GetTickCount();

		m_ExcelOptFun.DeleteItemInfo();
		m_ModeParMng.DeleteItemInfo();

		t2 = GetTickCount()-t1;
		str.Format(_T("�ͷ� CMainFrame::OnClose:DeleteItemInfo ��ʱ %d ����"),t2);
		g_pLogInfo->WriteLogFile(str.GetBuffer(0));


		//ztadd for CLogFile
		if (g_pLogInfo != NULL)
		{
			delete g_pLogInfo;
		}
		g_pLogInfo = NULL;


		CBCGPFrameWnd::OnClose();
	}
}
void CMainFrame::OnUpdateAppLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio (m_nAppLook == pCmdUI->m_nID);
}
void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CBCGPFrameWnd::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
}

void CMainFrame::OnMenuUsrMng()
{
	CUserMenage  nDlg;
	nDlg.DoModal();

	//g_DtMngView->ChangeViewMode(1,1);
}

void CMainFrame::OnMenuChangePwd()
{
	CResetUsrPwd nDlg;
	nDlg.DoModal();
}


void CMainFrame::OnMenuDepartMng()
{

	CUpDepart  nDlg;
	nDlg.DoModal();

	//CDepartMng   nDlg;
	//nDlg.DoModal();
	//g_DtMngView->ChangeViewMode(2,2);
}


void CMainFrame::OnUpdateMenuUsrMng(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( (g_LoginUsrInfo.nUserType != user_normal) );
	
}


void CMainFrame::OnMenuModeMmg()
{
	CModeMng     nModeMng;//ģ��//

	int ret;
	nModeMng.m_ShowType = Add_NewMode;
	if(nModeMng.DoModal() == IDOK)
	{
		StBasMode *pModeInfo = &nModeMng.m_ShowModeInfo.m_CurModeInfo;

		ret = AddTheMode(pModeInfo);
		if(ret == 1)
		{
			g_pLeftTree->InitGuideTree();
		}
		
	}
	//g_DtMngView->ChangeViewMode(3,1);
}



void CMainFrame::OnMenuTaskMng()
{
	//CTaskMng  nTaskMng;//�������//
	//
	//nTaskMng.DoModal();

	//g_DtMngView->ChangeViewMode(5,1);
}


void CMainFrame::OnMenuMesTaskLoadIn()
{
	//���� MES ������Ϣ///
	CLoadMesTask dlg;
	if (dlg.DoModal() == IDOK)
	{
		g_pLeftTree->InitGuideTree();
	}
}

void CMainFrame::OnMenuExcelTaskLoadIn()
{
	//���� Excel ������Ϣ///
	CLoadTaskInfo nDlg;
	if(nDlg.DoModal() == IDOK)
	{

	}
	//g_DtMngView->ChangeViewMode(5,4);
}

//���񵼳�//
void CMainFrame::OnBatchOutTaskMenu()
{
	/*CSelDlg  dlg;
	dlg.m_nType = Batch_OutTask;
	if(dlg.DoModal() == IDOK)
	{

	}*/

	CTaskDownUpLoad dlg;
	dlg.m_ShowType =  Task_DownLoad;
	dlg.DoModal();
}
//����ɼ����ݵ���//
void CMainFrame::OnTaskDataLoadin()
{
	// TODO: �ڴ���������������
	CTaskDownUpLoad dlg;
	dlg.m_ShowType =  Task_UpLoad;
	dlg.DoModal();
}
//�����ѯ//
void CMainFrame::OnMenuTaskSearch()
{
	/*StTstResultBase* pTstResult = &g_DtMngView->m_ResultSearch.m_TstResultBase;
	memset(pTstResult,0,sizeof(StTstResultBase));
	pTstResult->nGroupOid = g_CurSelDepart.nOid;
	pTstResult->nResultType = Task_DarkSearch;
	g_DtMngView->m_ResultSearch.SearchBaseByTaskName();
	g_DtMngView->ChangeViewMode(6,1);*/

	//�°�������ѯ//
	StBasTask* pResultSearchInfo = &g_DtMngView->m_ResultSearchNew.m_ResultSearchInfo;
	pResultSearchInfo->Release();
	pResultSearchInfo->stTaskBaseInfo.nGroupOid = g_CurSelDepart.nOid;
	pResultSearchInfo->stTaskBaseInfo.nResultType = Task_DarkSearch;
	g_DtMngView->m_ResultSearchNew.m_ResultSearchInfoDlg.DisPalySearchInfo();
	g_DtMngView->m_ResultSearchNew.m_ResultSearchInfoDlg.OnBnClickedButton1();
	g_DtMngView->ChangeViewMode(6,1);
}
//������ݲ�ѯ//
void CMainFrame::OnMenuResultSearch()
{
	/*StTstResultBase* pTstResult = &g_DtMngView->m_ResultSearch.m_TstResultBase;
	memset(pTstResult,0,sizeof(StTstResultBase));
	pTstResult->nGroupOid = g_CurSelDepart.nOid;
	pTstResult->nResultType = Result_Search;
	g_DtMngView->m_ResultSearch.SearchBaseByTaskName();
	g_DtMngView->ChangeViewMode(6,1);*/

	//�°�Ľ����ѯ//
	StBasTask* pResultSearchInfo = &g_DtMngView->m_ResultSearchNew.m_ResultSearchInfo;
	pResultSearchInfo->Release();
	pResultSearchInfo->stTaskBaseInfo.nGroupOid = g_CurSelDepart.nOid;
	pResultSearchInfo->stTaskBaseInfo.nResultType = Result_Search;
	g_DtMngView->m_ResultSearchNew.m_ResultSearchInfoDlg.DisPalySearchInfo();
	g_DtMngView->m_ResultSearchNew.m_ResultSearchInfoDlg.OnBnClickedButton1();
	g_DtMngView->ChangeViewMode(6,1);
}

void CMainFrame::OnMenuResultSum()
{
	g_DtMngView->ChangeViewMode(6,2);
}


//��ǰ����ѡ��//
void CMainFrame::OnCurdepartMenu()
{
	CCurDepartSel nDlg;
	if(nDlg.DoModal() == IDOK)
	{
		ReleaseProducts(&g_SelProducts);
		CString strUserLogName = g_LoginUsrInfo.szLoginName;
		if(!strUserLogName.IsEmpty())
		{
			g_UserConfig.GetSelProductConfig(strUserLogName,&g_SelProducts);
		}

		CreateSQLSelProducts(&g_SelProducts);

		g_pLeftTree->InitGuideTree();
		CString strCurDepart;
		strCurDepart.Format(_T("��ǰ����:%s"),g_CurSelDepart.szGroupName);
		m_wndWorkSpace.SetWindowText(strCurDepart);
		m_wndStatusBar.SetPaneWidth(3,200);
		m_wndStatusBar.SetPaneTextColor(3,RGB(0,0,0));
		m_wndStatusBar.SetPaneText(3,strCurDepart);
	}
}



void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == 100)
	{
		//m_wndStatusBar.SetPaneWidth(3,200);
		//m_wndStatusBar.SetPaneTextColor(3,RGB(0,0,0));
		m_wndStatusBar.SetPaneWidth(2,200);
		m_wndStatusBar.SetPaneTextColor(2,RGB(0,0,0));
		CString strText;
		strText.Format(_T("ϵͳʱ��:%s"),GetDateTimeString());
		m_wndStatusBar.SetPaneText(2,strText);

		//m_wndStatusBar.SetPaneWidth(1,200);
		//m_wndStatusBar.SetPaneTextColor(1,RGB(0,0,0));
		//m_wndStatusBar.SetPaneBackgroundColor(1,RGB(255,255,255));
		//m_wndStatusBar.EnablePaneDoubleClick();

		//m_wndStatusBar.SetPaneBackgroundColor(0,RGB(255,255,255));
		
	}
	

	CBCGPFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
	// TODO: �ڴ˴������Ϣ����������
}


void CMainFrame::OnBatchSelProductMenu()
{
	CSelDlg dlg;
	dlg.m_nType = Sel_Product;
	if(dlg.DoModal() == IDOK)
	{

		g_pLeftTree->InitGuideTree();
	}
}

void CMainFrame::OnUpdateCurdepartMenu(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( (g_LoginUsrInfo.nUserType != user_normal) );
}



void CMainFrame::OnUpdateMenuDepartMng(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( (g_LoginUsrInfo.nUserType != user_normal) );
	//pCmdUI->Enable( (g_LoginUsrInfo.nUserType == user_admin) );
}

void CMainFrame::OnAddTaskMenu()
{
	int ret = 0, i,nCount;
	CTaskMng  nTaskMng;//�������//
	CString strText, str;
	vector<CString> strErrorArray;
	nTaskMng.m_ShowType = Add_NewTask;
	if(nTaskMng.DoModal() == IDOK)
	{ 
		StBasTask *pTaskInfo = &nTaskMng.m_ShowTaskInfo.m_CurTaskInfo;
		ret = AddNewTask(pTaskInfo,strErrorArray);
		if(ret == 1)
		{
			g_MainFram->m_wndOutput.InsertErrorArrayText(strErrorArray);
			g_pLeftTree->InitGuideTree();
		}else
		{
			g_MainFram->m_wndOutput.InsertErrorArrayText(strErrorArray);
			nCount = strErrorArray.size();
			for (i = 0;i<nCount;i++)
			{
				str.Format(_T("%d.%s\n"), i+1, strErrorArray.at(i));
				strText+=str;
			}
			AfxMessageBox(strText);

		}
	}
}

void CMainFrame::OnReportSetMenu()
{
	CReportMode nDlg;
	nDlg.m_ShowType = Report_Mode;
	if(nDlg.DoModal() == IDOK)
	{

	}
}


void CMainFrame::OnModeComputeMenu()
{
	// TODO: �ڴ���������������
	CReportMode nDlg;
	nDlg.m_ShowType = Formula_Mode;
	if(nDlg.DoModal() == IDOK)
	{

	}
}

void CMainFrame::OnUpdateMenuModeMmg(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable( (g_LoginUsrInfo.nUserType != user_normal) );
}

void CMainFrame::OnUpdateAddTaskMenu(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable( (g_LoginUsrInfo.nUserType != user_normal) );
}

void CMainFrame::OnUpdateModeComputeMenu(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable( (g_LoginUsrInfo.nUserType != user_normal) );
}

void CMainFrame::OnUpdateReportSetMenu(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable( (g_LoginUsrInfo.nUserType != user_normal) );
}

void CMainFrame::OnUpdateMenuExcelTaskLoadIn(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable( (g_LoginUsrInfo.nUserType != user_normal) );
}

void CMainFrame::OnUpdateMenuMesTaskLoadIn(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable( (g_LoginUsrInfo.nUserType != user_normal) );
}

//֤����ģ��ά��//
void CMainFrame::OnTestimonialMenu()
{
	// TODO: �ڴ���������������
	CTestimonialMng dlg;
	if(dlg.DoModal() == IDOK)
	{

	}
}

void CMainFrame::OnUpdateTestimonialMenu(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable( (g_LoginUsrInfo.nUserType != user_normal) );
}
