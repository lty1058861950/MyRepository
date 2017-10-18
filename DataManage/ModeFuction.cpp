// ModeFuction.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "ModeFuction.h"


// CModeFuction 对话框

IMPLEMENT_DYNAMIC(CModeFuction, CDialog)

CModeFuction::CModeFuction(CWnd* pParent /*=NULL*/)
	: CDialog(CModeFuction::IDD, pParent)
{

}

CModeFuction::~CModeFuction()
{
}

void CModeFuction::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModeFuction, CDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_MODEMNG_ADD_BTN, &CModeFuction::OnBnClickedModemngAddBtn)
	ON_BN_CLICKED(IDC_MODEMNG_DEL_BTN, &CModeFuction::OnBnClickedModemngDelBtn)
	ON_BN_CLICKED(IDC_MODEMNG_EDIT_BTN, &CModeFuction::OnBnClickedModemngEditBtn)
	ON_BN_CLICKED(IDC_MODEMNG_COPY_BTN, &CModeFuction::OnBnClickedModemngCopyBtn)
	ON_BN_CLICKED(IDC_MODEMNG_PASTE_BTN, &CModeFuction::OnBnClickedModemngPasteBtn)
END_MESSAGE_MAP()


// CModeFuction 消息处理程序

BOOL CModeFuction::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CModeFuction::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}

void CModeFuction::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	AutoSize();
}

void CModeFuction::AutoSize()
{
	CRect Rect ;
	GetClientRect(&Rect) ;
	
	int nBtnWidth = 80;
	int nBtnHeight = 30;



	if (GetDlgItem(IDC_MODEMNG_ADD_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_MODEMNG_ADD_BTN)->MoveWindow(10,1,nBtnWidth,nBtnHeight);
	}
	if (GetDlgItem(IDC_MODEMNG_DEL_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_MODEMNG_DEL_BTN)->MoveWindow(10+(nBtnWidth+10)*1,1,nBtnWidth,nBtnHeight);
	}
	if (GetDlgItem(IDC_MODEMNG_EDIT_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_MODEMNG_EDIT_BTN)->MoveWindow(10+(nBtnWidth+10)*2,1,nBtnWidth,nBtnHeight);
	}
	if (GetDlgItem(IDC_MODEMNG_COPY_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_MODEMNG_COPY_BTN)->MoveWindow(10+(nBtnWidth+10)*4,1,nBtnWidth,nBtnHeight);
	}
	if (GetDlgItem(IDC_MODEMNG_PASTE_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_MODEMNG_PASTE_BTN)->MoveWindow(10+(nBtnWidth+10)*5,1,nBtnWidth,nBtnHeight);
	}
	
}


void CModeFuction::OnBnClickedModemngAddBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = 0;
	CModeMng  nModeMng;//检查任务//
	nModeMng.m_ShowType = Add_NewMode;
	if(nModeMng.DoModal() == IDOK)
	{
		StBasMode *pModeInfo = &nModeMng.m_ShowModeInfo.m_CurModeInfo;
		
		ret = AddTheMode(pModeInfo);
		if(ret == 1)
		{
			g_pShowInfoList->InsertOneModeToList(pModeInfo);
			g_pLeftTree->InitGuideTree();
		}
	}
}

void CModeFuction::OnBnClickedModemngDelBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	CEditableListCtrl *pList2 = &g_pShowInfoList->m_ResultList.m_ResultList;

	int nIndex, nCount, ret = 0;

	nIndex = pList2->GetFirstSelectedItem();
	nCount = pList2->GetItemCount();
	if(nIndex < 0 || nIndex >= nCount)
		return;

	UINT nModeOid = pList2->GetItemData(nIndex);
	StBasMode stModeInfo;
	memset(&stModeInfo, 0, sizeof(StBasMode));
	stModeInfo.Release();
	if(!m_DMng.GetModeDataOid(nModeOid,&stModeInfo))
	{
		return;
	}
	ret = DelTheMode(&stModeInfo);

	if(ret == 1)
	{
		pList2->DeleteItem(nIndex);
		g_pLeftTree->InitGuideTree();
	}
	stModeInfo.Release();

	
}

void CModeFuction::OnBnClickedModemngEditBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	CEditableListCtrl *pList2 = &g_pShowInfoList->m_ResultList.m_ResultList;


	int nIndex, nCount, ret = 0;
	nIndex = pList2->GetFirstSelectedItem();
	nCount = pList2->GetItemCount();
	if(nIndex < 0 || nIndex >= nCount)
		return;

	UINT nModeOid = pList2->GetItemData(nIndex);
	CModeMng  nModeMng;//检查任务//


	StBasMode *pModeInfo = &nModeMng.m_ShowModeInfo.m_CurModeInfo;
	pModeInfo->Release();
	if(!m_DMng.GetModeDataOid(nModeOid,pModeInfo))
	{
		return;
	}
	nModeMng.m_ShowType = Modify_Mode;
	if(nModeMng.DoModal() == IDOK)
	{
		ret = ModifyTheMode(pModeInfo);
		if(ret == 1)
		{
			g_pShowInfoList->ModifyOneModeToList(nIndex,pModeInfo);
			g_pLeftTree->InitGuideTree();
		}
	}
}

void CModeFuction::OnBnClickedModemngCopyBtn()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CModeFuction::OnBnClickedModemngPasteBtn()
{
	// TODO: 在此添加控件通知处理程序代码
}
