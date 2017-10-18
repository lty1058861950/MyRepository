// DataManage.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DataManage.h"

#include "MainFrm.h"
#include "DataManageDoc.h"
#include "DataManageView.h"
#include "SysLogin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataManageApp
OracleOciDbMng *g_pOrcOciDb =NULL;
BEGIN_MESSAGE_MAP(CDataManageApp, CWinApp)
	//{{AFX_MSG_MAP(CDataManageApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	//ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataManageApp construction

CDataManageApp::CDataManageApp() :
	CBCGPWorkspace (TRUE /* m_bResourceSmartUpdate */)
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDataManageApp object

CDataManageApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDataManageApp initialization

BOOL CDataManageApp::InitInstance()
{
	// Initialize OLE libraries
	m_hMutex = ::CreateMutex(NULL,FALSE,_T("DataManage"));
	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(m_hMutex);
		m_hMutex = NULL;

		//HWND hWnd = FindWindow(NULL, m_pszExeName);
		//if(IsWindow(hWnd))
		//{
		//	//::MessageBox(NULL, TEXT("已经有一个实例在运行了。"), TEXT("注意"), MB_OK);
		//	::ShowWindow(hWnd, SW_RESTORE);     // 显示
		//	::SetForegroundWindow(hWnd);       // 激活
		//	return FALSE;
		//}

		CWnd* pDesktopWnd = CWnd::GetDesktopWindow();
		CWnd* pWnd = pDesktopWnd->GetWindow(GW_CHILD);
		while (pWnd != NULL)
		{
			
			if(::GetProp(pWnd->m_hWnd, m_pszExeName))
			{
				::MessageBox(NULL, TEXT("已经有一个实例在运行了。"), TEXT("注意"), MB_OK);
				pWnd->ShowWindow(SW_RESTORE);
				pWnd->SetForegroundWindow();
				return FALSE;
			}
			pWnd = pWnd->GetWindow(GW_HWNDNEXT);
		}

		AfxMessageBox(_T("您已经运行了本软件!"));
		return FALSE;
	}
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	globalData.SetDPIAware ();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("BCGP AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	SetRegistryBase (_T("Settings"));

	// Initialize all Managers for usage. They are automatically constructed
	// if not yet present
	InitContextMenuManager();
	InitKeyboardManager();

	// TODO: Remove this if you don't want extended tooltips:
	InitTooltipManager();

	CBCGPToolTipParams params;
	params.m_bVislManagerTheme = TRUE;

	theApp.GetTooltipManager ()->SetTooltipParams (
		BCGP_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS (CBCGPToolTipCtrl),
		&params);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.


	GetCurrentDirectory(256,g_WorkPath);

	
	memset(&g_Configs,0,sizeof(DbConfig));
	strcpy(g_Configs.szDBName, _T("ZJLH"));
	strcpy(g_Configs.szUserName, _T("pad_jh"));
	strcpy(g_Configs.szUserPwd, _T("pad_jh"));

	g_pOrcOciDb  =&m_OrcOciDb;

	m_DMng.nConnectStatus = m_OrcOciDb.ConnectOracle(g_Configs.szDBName,g_Configs.szUserName,g_Configs.szUserPwd);

	CString nFileName ;
	nFileName.Format("%s\\%s",g_WorkPath,USRMNG_USRCFG_FILENAME) ;
	//部门选择项//
	g_GroupSelect = GetPrivateProfileInt("Def_GroupSelect","GroupSelect",0,nFileName);
	//纸张方向
	g_PaperDirection = GetPrivateProfileInt("Report_Paper_Direction","PaperDirection",1,nFileName);

	//PAD的个数
	g_PadCount = GetPrivateProfileInt("DEF_PAD_COUNT","PAD_NUMBER",0,nFileName);
	
	
	//登录//
	CSysLogin nLogin;
	
	if(nLogin.DoModal() != IDOK)
	{
		return FALSE;
	}

	
	

	
	CString strUserLogName = g_LoginUsrInfo.szLoginName;
	if(!strUserLogName.IsEmpty())
	{
		g_UserConfig.GetSelProductConfig(strUserLogName,&g_SelProducts);
	}

	CreateSQLSelProducts(&g_SelProducts);

	
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CDataManageDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CDataManageView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	
	//m_pMainWnd->ShowWindow(SW_MAXIMIZE);
	/*m_pMainWnd->PostMessage(WM_MDIMAXIMIZE);
	m_pMainWnd->UpdateWindow();*/

	


	m_pMainWnd->ShowWindow(SW_RESTORE);
	m_pMainWnd->MoveWindow(0, 0, 1366,768);
	//m_pMainWnd->ShowWindow(SW_MAXIMIZE);
	m_pMainWnd->CenterWindow();

	
	CString strText;
	strText.Format(_T("%s_%s(当前用户:%s)"),TITLE_INFO,TITLE_VERSION,g_LoginUsrInfo.szLoginName);
	m_pMainWnd->SetWindowText( strText );

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDataManageApp message handlers

int CDataManageApp::ExitInstance() 
{

	m_OrcOciDb.ColseOracle();

	BCGCBProCleanUp();

	return CWinApp::ExitInstance();
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//CBCGPURLLinkButton	m_btnURL;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//DDX_Control(pDX, IDC_COMPANY_URL, m_btnURL);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CDataManageApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

void CDataManageApp::PreLoadState ()
{

	//GetContextMenuManager()->AddMenu (_T("My menu"), IDR_CONTEXT_MENU);

	// TODO: add another context menus here
}


/////////////////////////////////////////////////////////////////////////////
// CDataManageApp message handlers


BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CString strText;
	strText.Format(_T("%s_%s %s"),TITLE_INFO,TITLE_VERSION,TITLE_DATE);
	GetDlgItem(IDC_STATIC_INF)->SetWindowText(strText);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
