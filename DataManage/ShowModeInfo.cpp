// ShowModeInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "ShowModeInfo.h"
#include "ModeMng.h"
#include "MainFrm.h"
#include "SelProductDlg.h"
// CShowModeInfo 对话框

IMPLEMENT_DYNAMIC(CShowModeInfo, CDialog)

CShowModeInfo::CShowModeInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CShowModeInfo::IDD, pParent)
{
	memset(&m_CurModeInfo,0,sizeof(StBasMode));
	memset(&m_CutBoard,0,sizeof(StBasMode));
	m_CutType = FALSE;
	m_pModeTree = NULL;

	m_ShowType = View_Mode;
}

CShowModeInfo::~CShowModeInfo()
{
	m_CurModeInfo.Release();
	m_CutBoard.Release();
	
}

void CShowModeInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHOWMODEINFO_TAB, m_ShowModeTab);
}


BEGIN_MESSAGE_MAP(CShowModeInfo, CDialog)
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_SHOWMODEINFO_TAB, &CShowModeInfo::OnTcnSelchangeShowmodeinfoTab)
	ON_BN_CLICKED(IDC_DEL_TAB_BTN, &CShowModeInfo::OnBnClickedDelTabBtn)
	ON_CBN_SELCHANGE(IDC_SHOWMODEINFO_TYPE_EDT, &CShowModeInfo::OnCbnSelchangeShowmodeinfoTypeEdt)
	ON_BN_CLICKED(IDC_MODE_SEL_PRODUCTNO_BTN, &CShowModeInfo::OnBnClickedModeSelProductnoBtn)
END_MESSAGE_MAP()


// CShowModeInfo 消息处理程序

BOOL CShowModeInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	TCITEM tcItem;
	tcItem.mask = TCIF_TEXT;
	tcItem.pszText = _T("模板信息");
	m_ShowModeTab.InsertItem(0,&tcItem) ;

	tcItem.pszText = _T("模板样式");
	m_ShowModeTab.InsertItem(1,&tcItem) ;
	/*tcItem.pszText = _T("模板总览");
	m_ShowModeTab.InsertItem(2,&tcItem) ;*/

	//g_pModeMng = (CModeMng*)GetParent();
	m_ShowModeStyle.Create(IDD_SHOWMODESTYLE_DLG,this);
	m_ShowModeStyle.m_pShowModeInfo =this;
	m_ShowModeStyle.ShowWindow(SW_HIDE);

	/*m_ShowModeStyle.m_pModeParMng = &g_DtMngView->m_ModeParMng2;
	m_ShowModeStyle.m_pExcelOptFun = &g_DtMngView->m_ExcelOptFun2;
	m_ShowModeStyle.m_pModeXmlAnalysis = &g_DtMngView->m_ModeXmlAnalysis2;*/

	

	//m_ShowModeAll.Create(IDD_SHOWMODEALL_DLG,this);
	//m_ShowModeAll.ShowWindow(SW_HIDE);


	InitModeTypeCom();
	InitModeRowValCom();
	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CShowModeInfo::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	AutoSize();
	// TODO: 在此处添加消息处理程序代码
}
void CShowModeInfo::AutoSize()
{
	CRect Rect ;
	GetClientRect(&Rect) ;
	int nBtnWidth = 80;
	int nBtnHeight = 30;

	if(m_ShowModeTab.GetSafeHwnd())
	{
		m_ShowModeTab.MoveWindow(1,1,Rect.Width()-2,Rect.Height()-2);
	}
	if (m_ShowModeStyle.GetSafeHwnd())
	{
		m_ShowModeStyle.MoveWindow(1+2,1+22,Rect.Width()-(2+4),Rect.Height()-(2+24));
	}

	CRect rcReck;
	if(GetDlgItem(IDC_SHOWMODEINFO_STATIC13)->GetSafeHwnd())
	{
		GetDlgItem(IDC_SHOWMODEINFO_STATIC13)->GetWindowRect(&rcReck);
		//ClientToScreen(&rcReck);
		ScreenToClient(&rcReck);
		rcReck.right = Rect.right-10;
		GetDlgItem(IDC_SHOWMODEINFO_STATIC13)->MoveWindow(&rcReck);
	}
	if(GetDlgItem(IDC_SHOWMODEINFO_STATIC14)->GetSafeHwnd())
	{
		GetDlgItem(IDC_SHOWMODEINFO_STATIC14)->GetWindowRect(&rcReck);
		ScreenToClient(&rcReck);
		rcReck.right = Rect.right-10;
		GetDlgItem(IDC_SHOWMODEINFO_STATIC14)->MoveWindow(&rcReck);
	}
	if(GetDlgItem(IDC_SHOWMODEINFO_STATIC15)->GetSafeHwnd())
	{
		GetDlgItem(IDC_SHOWMODEINFO_STATIC15)->GetWindowRect(&rcReck);
		ScreenToClient(&rcReck);
		rcReck.right = Rect.right-10;
		GetDlgItem(IDC_SHOWMODEINFO_STATIC15)->MoveWindow(&rcReck);
	}
	if(GetDlgItem(IDOK)->GetSafeHwnd())
	{
		GetDlgItem(IDOK)->MoveWindow(Rect.right-((10)+(nBtnWidth+10)*2),Rect.bottom-(nBtnHeight+10),nBtnWidth,nBtnHeight);
	}
	if(GetDlgItem(IDCANCEL)->GetSafeHwnd())
	{
		GetDlgItem(IDCANCEL)->MoveWindow(Rect.right-((10)+(nBtnWidth+10)*1),Rect.bottom-(nBtnHeight+10),nBtnWidth,nBtnHeight);
	}
}


void CShowModeInfo::GetTreeItemType(HTREEITEM hItem,StBasMode *pStr)
{

	if(hItem == NULL)
	{
		return;
	}
	CString strItem = m_pModeTree->GetItemText(hItem);
	if(strItem.IsEmpty())
		return;
	int nTreeID = m_pModeTree->GetItemData(hItem);

	int nType,nID;
	if(!NumOneToTwo(nTreeID,nType,nID))
	{
		return;
	}
	switch(nType)
	{
	case MODE_TREE_TYPE_DEPART:
		{
			pStr->nGroupOid = nID;
			HTREEITEM hpItem = m_pModeTree->GetParentItem(hItem);
			GetTreeItemType(hpItem, pStr);

		}
		break;
	case MODE_TREE_TYPE_MODETYPE:
		{
			pStr->nModeType = nID;
			HTREEITEM hpItem = m_pModeTree->GetParentItem(hItem);
			GetTreeItemType(hpItem, pStr);

		}
		break;
	case MODE_TREE_TYPE_PRODCODE:
		{
			pStr->stProductInfo.nOid = nID;
			HTREEITEM hpItem = m_pModeTree->GetParentItem(hItem);
			GetTreeItemType(hpItem, pStr);

		}
		break;
	default:
		{

		}
		break;
	}
	return ;

}

void CShowModeInfo::InitModeTypeCom()
{
	CComboBox *pComBo = (CComboBox*)GetDlgItem(IDC_SHOWMODEINFO_TYPE_EDT);
	pComBo->ResetContent();
	
	int i;
	for (i = Mode_Currency;i<=Mode_NotUse;i++)
	{
		pComBo->AddString(g_ModeType[i]);
	}
	pComBo->SetCurSel(1);

}
void CShowModeInfo::InitModeRowValCom()
{
	CComboBox *pComBo = (CComboBox*)GetDlgItem(IDC_SHOWMODEINFO_OFFSHOOT_EDT);
	pComBo->ResetContent();

	int i;
	for (i = ModeRow_NoChange;i<= ModeRow_Change;i++)
	{
		pComBo->AddString(g_ModeRowVal[i]);
	}
	pComBo->SetCurSel(0);

}
void  CShowModeInfo::SetModeTypeCtrl(int nInitTabSrt)//根据模板表初始化的状态 设置控件的状态//
{
	int nUserType = g_LoginUsrInfo.nUserType;
	(GetDlgItem(IDC_SHOWMODEINFO_TYPE_EDT))->EnableWindow(!nInitTabSrt);//1.模板类型将不可变
	(GetDlgItem(IDC_SHOWMODEINFO_OFFSHOOT_EDT))->EnableWindow(!nInitTabSrt);//2.行属性将不可变

	if(m_CurModeInfo.nModeType == Mode_Dedicated)
	{
		((CEdit *)GetDlgItem(IDC_SHOWMODEINFO_PRODID_EDT))->SetReadOnly(nInitTabSrt);//3.产品代号也将不可变
		((CEdit *)GetDlgItem(IDC_SHOWMODEINFO_PRODMODEL_EDT))->SetReadOnly(nInitTabSrt);//4.产品型号  也将不可变
		((CEdit *)GetDlgItem(IDC_SHOWMODEINFO_PRODPHASE_EDT))->SetReadOnly(nInitTabSrt);//5.产品阶段
	}
	

	//样式页面的功能限制//
	if(nUserType == user_normal)
	{
		//普通用户没有更改模板的权利//
		m_ShowModeStyle.GetDlgItem(IDC_LOAD_MODE_BTN)->EnableWindow(FALSE);//6.模板结构不可再更改了
		GetDlgItem(IDC_DEL_TAB_BTN)->EnableWindow(FALSE);
	}else
	{
		m_ShowModeStyle.GetDlgItem(IDC_LOAD_MODE_BTN)->EnableWindow(!nInitTabSrt);//6.模板结构不可再更改了
		GetDlgItem(IDC_DEL_TAB_BTN)->EnableWindow(TRUE);
	}
	


}
void CShowModeInfo::SetProductCtrlShowType(int nModeType)
{
	int nShowType = 0;
	CString strText;
	StBasMode *pModeInfo = &m_CurModeInfo;
	switch(nModeType)
	{
	case Mode_Currency:
		{
			nShowType = 0;
			((CEdit *)GetDlgItem(IDC_SHOWMODEINFO_PRODID_EDT))->SetWindowText(_T(""));
			((CEdit *)GetDlgItem(IDC_SHOWMODEINFO_PRODMODEL_EDT))->SetWindowText(_T(""));
			((CEdit *)GetDlgItem(IDC_SHOWMODEINFO_PRODPHASE_EDT))->SetWindowText(_T(""));
		}
		break;
	case Mode_Dedicated:
		{
			nShowType = 1;
			strText.Format(_T("%s"), pModeInfo->stProductInfo.szProductNo);
			((CEdit *)GetDlgItem(IDC_SHOWMODEINFO_PRODID_EDT))->SetWindowText(strText);
			strText.Format(_T("%s"), pModeInfo->szModel);
			((CEdit *)GetDlgItem(IDC_SHOWMODEINFO_PRODMODEL_EDT))->SetWindowText(strText);
			strText.Format(_T("%s"), pModeInfo->szPhase);
			((CEdit *)GetDlgItem(IDC_SHOWMODEINFO_PRODPHASE_EDT))->SetWindowText(strText);
		}
		break;
	case Mode_LineDed:
		{
			nShowType = 0;
			((CEdit *)GetDlgItem(IDC_SHOWMODEINFO_PRODID_EDT))->SetWindowText(_T(""));
			((CEdit *)GetDlgItem(IDC_SHOWMODEINFO_PRODMODEL_EDT))->SetWindowText(_T(""));
			((CEdit *)GetDlgItem(IDC_SHOWMODEINFO_PRODPHASE_EDT))->SetWindowText(_T(""));
		}
		break;
	case Mode_NotUse:
		{
			nShowType = 0;
			((CEdit *)GetDlgItem(IDC_SHOWMODEINFO_PRODID_EDT))->SetWindowText(_T(""));
			((CEdit *)GetDlgItem(IDC_SHOWMODEINFO_PRODMODEL_EDT))->SetWindowText(_T(""));
			((CEdit *)GetDlgItem(IDC_SHOWMODEINFO_PRODPHASE_EDT))->SetWindowText(_T(""));
		}
		break;
	}

	((CEdit *)GetDlgItem(IDC_SHOWMODEINFO_PRODID_EDT))->SetReadOnly(!nShowType);
	((CEdit *)GetDlgItem(IDC_SHOWMODEINFO_PRODMODEL_EDT))->SetReadOnly(!nShowType);
	((CEdit *)GetDlgItem(IDC_SHOWMODEINFO_PRODPHASE_EDT))->SetReadOnly(!nShowType);

	(GetDlgItem(IDC_MODE_SEL_PRODUCTNO_BTN))->EnableWindow(nShowType);
}
BOOL CShowModeInfo::SetModeTypeRorvarComBoText(StBasMode *pStr)
{

	//显示模板类型//
	
	int nModeType = pStr->nModeType;
	CComboBox *pComBo2 = (CComboBox*)GetDlgItem(IDC_SHOWMODEINFO_TYPE_EDT);
	
	if(nModeType >= Mode_Currency && nModeType <= Mode_NotUse)
	{
		pComBo2->SetCurSel(nModeType);
	}
	

	//显示模板行可变属性//
	int nModeRowVar = pStr->nModeRowVar;
	CComboBox *pComBo3 = (CComboBox*)GetDlgItem(IDC_SHOWMODEINFO_OFFSHOOT_EDT);

	if(nModeRowVar >= ModeRow_NoChange && nModeRowVar <= ModeRow_Change)
	{
		pComBo3->SetCurSel(nModeRowVar);
	}	
	return TRUE;
}
void CShowModeInfo::SetControlShow(UINT nShow)
{
	
	GetDlgItem(IDC_SHOWMODEINFO_STATIC1)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWMODEINFO_STATIC2)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWMODEINFO_STATIC3)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWMODEINFO_STATIC4)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWMODEINFO_STATIC5)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWMODEINFO_STATIC6)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWMODEINFO_STATIC7)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWMODEINFO_STATIC8)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWMODEINFO_STATIC9)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWMODEINFO_STATIC10)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWMODEINFO_STATIC11)->ShowWindow(nShow);
	//GetDlgItem(IDC_SHOWMODEINFO_STATIC12)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWMODEINFO_STATIC13)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWMODEINFO_STATIC14)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWMODEINFO_STATIC15)->ShowWindow(nShow);
	GetDlgItem(IDC_STATIC1)->ShowWindow(nShow);
	GetDlgItem(IDC_EDIT1)->ShowWindow(nShow);


	
		

	
	GetDlgItem(IDC_DEL_TAB_BTN)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWMODEINFO_NAME_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWMODEINFO_EDITION_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWMODEINFO_SIZE_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWMODEINFO_DATATABNAME_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWMODEINFO_PRODID_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_MODE_SEL_PRODUCTNO_BTN)->ShowWindow(nShow);

	GetDlgItem(IDC_SHOWMODEINFO_PRODMODEL_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWMODEINFO_PRODPHASE_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWMODEINFO_BUILDTIME_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWMODEINFO_BUILDUSR_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWMODEINFO_TYPE_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWMODEINFO_OFFSHOOT_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWMODEINFO_DATATABINFO_EDT)->ShowWindow(nShow);

	int nUserType = g_LoginUsrInfo.nUserType;

	if(m_ShowType == View_Mode)
	{
		GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
	}else
	{
		if(nUserType == user_normal)
		{
			GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
		}else
		{
			GetDlgItem(IDOK)->ShowWindow(nShow);
		}
		
	}
	
	GetDlgItem(IDCANCEL)->ShowWindow(nShow);
	
}

BOOL CShowModeInfo::GetModeInfoChange()
{
	UINT nGroupOid = g_CurSelDepart.nOid;
	CString strText;
	BOOL  Is_Change = FALSE;
	//1.模板名称
	GetDlgItem(IDC_SHOWMODEINFO_NAME_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	if(strcmp(strText, m_CurModeInfo.szModeName) != 0)
	{
		memset(m_CurModeInfo.szModeName,0,sizeof(m_CurModeInfo.szModeName));
		strcpy(m_CurModeInfo.szModeName,strText);
		Is_Change = TRUE;
	}
	GetDlgItem(IDC_SHOWMODEINFO_EDITION_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	if(strcmp(strText, m_CurModeInfo.szModeVersion) != 0)
	{
		memset(m_CurModeInfo.szModeVersion,0,sizeof(m_CurModeInfo.szModeVersion));
		strcpy(m_CurModeInfo.szModeVersion,strText);
		Is_Change = TRUE;
	}

	CComboBox *pComBo = (CComboBox *)GetDlgItem(IDC_SHOWMODEINFO_TYPE_EDT);
	int index = pComBo->GetCurSel();

	if(index >= 0)
	{
		if(m_CurModeInfo.nModeType != index)
		{
			m_CurModeInfo.nModeType = index;
			Is_Change = TRUE;
		}
	}else
	{
		AfxMessageBox(_T("模板类型选择错误!"));
		Is_Change = FALSE;
		return Is_Change;
	}
	
	
	
	pComBo = (CComboBox *)GetDlgItem(IDC_SHOWMODEINFO_OFFSHOOT_EDT);
	index = pComBo->GetCurSel();
	if(index>=0)
	{
		if(m_CurModeInfo.nModeRowVar != index)
		{
			m_CurModeInfo.nModeRowVar = index;
			Is_Change = TRUE;
		}
		
	}else
	{
		AfxMessageBox(_T("请选择模板的行可变的属性!"));
		Is_Change = FALSE;
		return Is_Change;

	}
	
	((CEdit*)GetDlgItem(IDC_SHOWMODEINFO_PRODID_EDT))->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	if(m_CurModeInfo.nModeType == Mode_Dedicated)
	{
		if(strcmp(_T(""), strText) == 0)
		{
			AfxMessageBox(_T("产品名称不能为空!请选择一个产品"));
			Is_Change = FALSE;
			return Is_Change;

		}
		
		if(strcmp(strText,m_CurModeInfo.stProductInfo.szProductNo) != 0)
		{
			memset(m_CurModeInfo.stProductInfo.szProductNo,0,sizeof(m_CurModeInfo.stProductInfo.szProductNo));
			strcpy(m_CurModeInfo.stProductInfo.szProductNo,strText);
			Is_Change = TRUE;
		}

	}else
	{
		m_CurModeInfo.stProductInfo.nOid = 0;
	}
	
	
	GetDlgItem(IDC_SHOWMODEINFO_PRODMODEL_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	if(strcmp(strText, m_CurModeInfo.szModel) != 0)
	{
		memset(m_CurModeInfo.szModel,0,sizeof(m_CurModeInfo.szModel));
		strcpy(m_CurModeInfo.szModel,strText);
		Is_Change = TRUE;
	}

	GetDlgItem(IDC_SHOWMODEINFO_PRODPHASE_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	if(strcmp(strText, m_CurModeInfo.szPhase) != 0)
	{
		memset(m_CurModeInfo.szPhase,0,sizeof(m_CurModeInfo.szPhase));
		strcpy(m_CurModeInfo.szPhase,strText);
		Is_Change = TRUE;
	}
	

	

	return Is_Change;
}


void CShowModeInfo::CopyModeStruct(StBasMode *pDecModeInfo,StBasMode *pSrcModeInfo)
{
	m_CutType = TRUE;
	pDecModeInfo->Release();
	memset(pDecModeInfo,0,sizeof(StBasMode));
	memcpy(pDecModeInfo,pSrcModeInfo,sizeof(StBasMode));
	//对XML指针进行 深拷贝//
	pDecModeInfo->pXmlFile = new char[pSrcModeInfo->nModeSize+1];
	memset(pDecModeInfo->pXmlFile,0,pSrcModeInfo->nModeSize+1);
	memcpy(pDecModeInfo->pXmlFile,pSrcModeInfo->pXmlFile,pSrcModeInfo->nModeSize);
}


BOOL CShowModeInfo::AddNewMode()
{
	//选中产品不提示//
	////
	StBasMode *pCurModeStr = &m_CurModeInfo;

	StBasMode nModeInfo;
	memset(&nModeInfo,0,sizeof(StBasMode));

	BOOL  Is_Hav = FALSE;
	switch(pCurModeStr->TreeItemType)
	{
	case MODE_TREE_TYPE_MODETYPE:
		{
			switch(pCurModeStr->nOid)
			{

			case Mode_Currency://通用模板默认属性//
				{
					nModeInfo.nModeType = Mode_Currency;
					nModeInfo.nModeRowVar = ModeRow_NoChange;
					Is_Hav = TRUE;
				}
				break;
			case Mode_Dedicated://产品专用的模板//
				{

				}
				break;
			case Mode_LineDed://线缆专用模板默认属性//
				{
					nModeInfo.nModeType = Mode_LineDed;
					nModeInfo.nModeRowVar = ModeRow_Change;

					Is_Hav = TRUE;
				}
				break;
			case Mode_NotUse://未启用的模板默认属性//
				{
					nModeInfo.nModeType = Mode_NotUse;
					nModeInfo.nModeRowVar = ModeRow_NoChange;

					Is_Hav = TRUE;
				}
				break;
			}
		}
		break;
	case MODE_TREE_TYPE_PRODCODE:
		{
			nModeInfo.nModeType = Mode_Dedicated;
			nModeInfo.nModeRowVar = ModeRow_NoChange;

			Is_Hav = TRUE;
		}
		break;
	}

	if(Is_Hav == TRUE)
	{
		InputInfo nInPutInfo;
		nInPutInfo.Type =Add_Mode;
		nInPutInfo.WindowText = "请输入一个模板的名称!";
		nInPutInfo.NameStatic  = "模板名称:";
		CInPutName nDlg(&nInPutInfo);

		if(nDlg.DoModal() != IDOK)
		{
			return FALSE;
		}

		nModeInfo.pModeTree = m_CurModeInfo.pModeTree;
		nModeInfo.hItem = m_CurModeInfo.hItem;
		strcpy(nModeInfo.szModeName, nInPutInfo.OutName);

		strcpy(nModeInfo.stProductInfo.szProductNo, pCurModeStr->stProductInfo.szProductNo);
		strcpy(nModeInfo.szCreateUser, g_LoginUsrInfo.szLoginName);
		strcpy(nModeInfo.szCreateTime, GetDateTimeString());
		GetTreeItemType(pCurModeStr->hItem,&nModeInfo);
		if(m_DMng.IsGroupProdModeExists(nModeInfo.nGroupOid,
			nModeInfo.stProductInfo.nOid,nModeInfo.stProductInfo.szProductNo))
		{
			CString strText;
			strText.Format(_T("此模板 \"%s\" 已经存在了!"),nModeInfo.szModeName);
			AfxMessageBox(strText);
			return FALSE;
		}else
		{
			CTreeCtrl *pTree = nModeInfo.pModeTree;
			HTREEITEM HItem = NULL;
			HItem = nModeInfo.hItem ;
			CString strText,strModeName = nModeInfo.szModeName;
			if(!HItem)
			{
				return FALSE;
			}
			int nTreeID;
			if(m_DMng.AddNewMode(&nModeInfo))
			{
				if(NumTwoToOne(nTreeID,MODE_TREE_TYPE_MODE,nModeInfo.nOid))
				{
					
					MyInsertTree(pTree,strModeName,HItem,nTreeID,3,3);
				}
				strText.Format(_T("添加模板: \"%s\" 成功!"),strModeName);
				g_MainFram->m_wndOutput.InsertErrorText(strText);
			}else
			{
				strText.Format(_T("添加模板: \"%s\" 失败!"),strModeName);
				g_MainFram->m_wndOutput.InsertErrorText(strText);
				AfxMessageBox(strText);
				return FALSE;
			}
		}

	}
	return FALSE;
}

BOOL CShowModeInfo::DelMode()
{
	CTreeCtrl *pTree = m_CurModeInfo.pModeTree;
	CString strText;
	//删除模板需要考虑的问题///
	//1.//
	//2.//
	//3.//
	//4.//
	if(!m_CurModeInfo.hItem || m_CurModeInfo.TreeItemType != MODE_TREE_TYPE_MODE)
	{
		return FALSE;
	}
	if(MessageBox(_T("确定删除此模板吗?(确定/取消)）"),_T(""),MB_OKCANCEL|MB_ICONQUESTION) != IDOK)
	{
		return TRUE;
	}

	if(m_DMng.DelOldMode(m_CurModeInfo.nOid))
	{
		pTree->DeleteItem(m_CurModeInfo.hItem);
		strText.Format(_T("删除模板: \"%s\" 成功!"),m_CurModeInfo.szModeName);
		g_MainFram->m_wndOutput.InsertErrorText(strText);

		m_CurModeInfo.Release();
		memset(&m_CurModeInfo,0,sizeof(StBasMode));
		return TRUE;
	}
	return FALSE;
}
BOOL CShowModeInfo::EditMode()
{
	StBasMode *pModeCurInfo = &m_CurModeInfo;
	CTreeCtrl *pTree = pModeCurInfo->pModeTree;
	HTREEITEM HItem = NULL;
	HItem = pModeCurInfo->hItem ;
	CString strText,strTaskNewName,strTaskOldName = pModeCurInfo->szModeName;
	if(!HItem || pModeCurInfo->TreeItemType != MODE_TREE_TYPE_MODE)
	{
		return FALSE;
	}

	if(GetModeInfoChange())
	{
		strTaskNewName = pModeCurInfo->szModeName;
		if(m_DMng.EditOldMode(pModeCurInfo))
		{
			//修改成功后修改树的节点文本///
			pTree->SetItemText(HItem,strTaskNewName);
			strText.Format(_T("已将模板名从: \"%s\" 修改为 \"%s\""),strTaskOldName,strTaskNewName);
			g_MainFram->m_wndOutput.InsertErrorText(strText);
			
		}else
		{
			strText.Format(_T("修改任务: \"%s\" 失败!"),strTaskOldName);
			g_MainFram->m_wndOutput.InsertErrorText(strText);
			AfxMessageBox(strText);
			return FALSE;
		}
	}
	return TRUE;
}
BOOL CShowModeInfo::CopyModeTree()
{
	//复制一个模板//
	if(m_CurModeInfo.hItem && m_CurModeInfo.TreeItemType == MODE_TREE_TYPE_MODE)
	{
		CopyModeStruct(&m_CutBoard,&m_CurModeInfo);
		return TRUE;
		
	}else
	{
		AfxMessageBox(_T("请选中一个模板再复制"));
		
	}
	return FALSE;
}
BOOL CShowModeInfo::PasteMode()
{
	//粘贴模板分2中情况:
	//1.新建, 需要新增的是 ID 名称 类型 表名 适用的产品，产品初始化表结构，
	//2.替换，给出提示;
	//就是除了ID  名称 类型 表名 初始化表结构(再说) 保持不变 其他都一样//
	if(!m_CutType)
	{
		AfxMessageBox("当前没有复制任何模板!");
		return FALSE;
	}

	StBasMode *pModeInfo = &m_CurModeInfo;
	if(pModeInfo->hItem)
	{
		if(pModeInfo->TreeItemType == MODE_TREE_TYPE_MODE)//替换//
		{
			return FALSE;
		}else //新建//
		{
			if(pModeInfo->TreeItemType == MODE_TREE_TYPE_MODETYPE)
			{
				if(pModeInfo->nOid == Mode_Dedicated)
				{
					return FALSE;
				}
			}
			StBasMode nModeInfo;
			memset(&nModeInfo,0,sizeof(StBasMode));

			InputInfo nInPutInfo;
			nInPutInfo.Type =Add_Mode;
			nInPutInfo.WindowText = "请输入一个模板的名称!";
			nInPutInfo.NameStatic  = "模板名称:";
			CInPutName nDlg(&nInPutInfo);

			if(nDlg.DoModal() != IDOK)
			{
				return FALSE;
			}

			strcpy(nModeInfo.szModeName, nInPutInfo.OutName);
			GetTreeItemType(pModeInfo->hItem,&nModeInfo);

			nModeInfo.pModeTree = pModeInfo->pModeTree;
			nModeInfo.hItem = pModeInfo->hItem;
			nModeInfo.nModeSize = m_CutBoard.nModeSize;
			strcpy(nModeInfo.szCreateTime, GetDateTimeString());
			strcpy(nModeInfo.szCreateUser, g_LoginUsrInfo.szLoginName);

			

			if(m_DMng.AddNewMode(&nModeInfo))
			{
				CTreeCtrl *pTree = nModeInfo.pModeTree;
				HTREEITEM HItem = NULL;
				HItem = nModeInfo.hItem ;
				CString strText,strModeName = nModeInfo.szModeName;
				int nTreeID;
				if(m_DMng.UpdateModeXmlFile(nModeInfo.nOid,m_CutBoard.pXmlFile,m_CutBoard.nModeSize))
				{
					if(NumTwoToOne(nTreeID,MODE_TREE_TYPE_MODE,nModeInfo.nOid))
					{
						MyInsertTree(pTree,strModeName,HItem,nTreeID,3,3);
					}
					strText.Format(_T("添加模板: \"%s\" 成功!"),strModeName);
					g_MainFram->m_wndOutput.InsertErrorText(strText);
				}else
				{
					strText.Format(_T("添加模板: \"%s\" 失败!"),strModeName);
					g_MainFram->m_wndOutput.InsertErrorText(strText);
					AfxMessageBox(strText);
					return FALSE;
				}
				return TRUE;
			}else
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}
void CShowModeInfo::DisPalyModeInfo()
{
	CString strText;
	strText.Format(_T("%s"), m_CurModeInfo.szModeName);
	GetDlgItem(IDC_SHOWMODEINFO_NAME_EDT)->SetWindowText(m_CurModeInfo.szModeName);
	strText.Format(_T("%s"), m_CurModeInfo.szModeVersion);
	GetDlgItem(IDC_SHOWMODEINFO_EDITION_EDT)->SetWindowText(strText);
	strText.Format(_T("%s"), m_CurModeInfo.szModel);
	GetDlgItem(IDC_SHOWMODEINFO_PRODMODEL_EDT)->SetWindowText(strText);
	strText.Format(_T("%s"), m_CurModeInfo.szPhase);
	GetDlgItem(IDC_SHOWMODEINFO_PRODPHASE_EDT)->SetWindowText(strText);
	strText.Format(_T("%s"), m_CurModeInfo.szCreateTime);
	GetDlgItem(IDC_SHOWMODEINFO_BUILDTIME_EDT)->SetWindowText(strText);
	strText.Format(_T("%s"), m_CurModeInfo.szCreateUser);
	GetDlgItem(IDC_SHOWMODEINFO_BUILDUSR_EDT)->SetWindowText(strText);
	strText.Format(_T("%s"), GetModeInitStr(m_CurModeInfo.nInitTabSrt));
	GetDlgItem(IDC_SHOWMODEINFO_DATATABINFO_EDT)->SetWindowText(strText);

	strText.Format(_T("%s"), m_CurModeInfo.stProductInfo.szProductNo);
	GetDlgItem(IDC_SHOWMODEINFO_PRODID_EDT)->SetWindowText(strText);

	
	//公式模板 //
	if(m_CurModeInfo.nFormula)
	{
		strText.Format(_T("有"));
	}else
	{
		strText.Format(_T("无"));
	}
	
	GetDlgItem(IDC_EDIT1)->SetWindowText(strText);

	SetModeTypeRorvarComBoText(&m_CurModeInfo);
	SetProductCtrlShowType(m_CurModeInfo.nModeType);
	SetModeTypeCtrl(m_CurModeInfo.nInitTabSrt);
	

	
	int nLen = m_CurModeInfo.nModeSize;
	strText = GetModeSizeText(nLen);
	GetDlgItem(IDC_SHOWMODEINFO_SIZE_EDT)->SetWindowText(strText);
	strText.Format(_T("%s"), m_CurModeInfo.szModeTabName);
	GetDlgItem(IDC_SHOWMODEINFO_DATATABNAME_EDT)->SetWindowText(strText);
	m_ShowModeStyle.DisPlayModeStyle();
	
}

void CShowModeInfo::OnTcnSelchangeShowmodeinfoTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nShowType;
	if ((nShowType = m_ShowModeTab.GetCurSel())==0)
	{
		SetControlShow(SW_SHOW);
		m_ShowModeStyle.ShowWindow(SW_HIDE) ;
		//m_ShowModeAll.ShowWindow(SW_HIDE);
	}
	if (nShowType==1)
	{
		SetControlShow(SW_HIDE);
		m_ShowModeStyle.ShowWindow(SW_SHOW) ;
		//m_ShowModeAll.ShowWindow(SW_HIDE);
	}
	/*if (nShowType==2)
	{
		SetControlShow(SW_HIDE);
		m_ShowModeStyle.ShowWindow(SW_HIDE) ;
		m_ShowModeAll.ShowWindow(SW_SHOW);
	}*/
	*pResult = 0;
}

void CShowModeInfo::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	int ret = 0;
	ret = GetModeInfoChange();
	if(ret == 1)
	{
		if(m_ShowType == Tree_Modify_Mode)
		{
			ModifyTheMode(&m_CurModeInfo);
			g_pLeftTree->InitGuideTree();
			return;
		}
	}
	

	
	if(ret == 1)
	{
		if(1)
		{
			CDialog::OnOK();
			CModeMng *pDlg = ((CModeMng *)GetParent());
			pDlg->CModeMng::OnOK();
		}
	}

	
}

void CShowModeInfo::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	if(m_ShowType == Tree_Modify_Mode)
	{
		return;
	}else
	{
		CDialog::OnCancel();
		CModeMng *pDlg = ((CModeMng *)GetParent());
		pDlg->CModeMng::OnCancel();
	}
}

void CShowModeInfo::OnBnClickedDelTabBtn()
{
	// TODO: 在此添加控件通知处理程序代码//

	CString str ,strTabName;
	UINT    nGroupOid,nModeOid;

	nGroupOid = g_CurSelDepart.nOid;
	nModeOid = m_CurModeInfo.nOid;
	if(nGroupOid<=0)
	{
		return;
	}
	if(nModeOid <=0 )
	{
		return ;
	}
	//1.从Bas_Mode_Save//清除创建的记录
	if(!m_DMng.IsModeStrTabExists(nModeOid))
	{
		return ;
	}
	if(!m_DMng.DelOldModeSave(nModeOid))
	{
		str.Format(_T("清除创建表信息时出错!"));
		AfxMessageBox(str);
	}else
	{
		strTabName.Format(_T("%s%.4d_%.4d"),g_TstData,nGroupOid,nModeOid);
		int nCount = 0;
		nCount = m_DMng.GetDataCount(strTabName.GetBuffer(0));
		//检查表中有多少条数据
		str.Format(_T("当前表 \"%s\" 中有 %d 条数据，是否删除表?(确定/取消)"),strTabName,nCount);
		if(MessageBox(str,_T("提示"),MB_OKCANCEL|MB_ICONQUESTION) != IDOK)
		{
			return ;
		}

		//2.删除这个数据表
		if(!m_DMng.DeleteTableData(strTabName.GetBuffer(0),TRUE))
		{
			str.Format(_T("删除 \"%s\" 表失败!"));
			AfxMessageBox(str);
		}else
		{
			m_CurModeInfo.nInitTabSrt = 0;
			if(!m_DMng.EditOldMode(&m_CurModeInfo))
			{
				
			}else
			{
				GetDlgItem(IDC_SHOWMODEINFO_DATATABINFO_EDT)->SetWindowText(m_CurModeInfo.nInitTabSrt >=1 ?_T("是"): _T("否"));
			}
			str.Format(_T("\"%s\" 表已经删除!"),strTabName);
			DisPalyModeInfo();
			AfxMessageBox(str);
		}
	}
	
}

void CShowModeInfo::OnCbnSelchangeShowmodeinfoTypeEdt()
{
	// TODO: 在此添加控件通知处理程序代码//

	int nIndex, nCount;
	CComboBox *pComBox = (CComboBox *)GetDlgItem(IDC_SHOWMODEINFO_TYPE_EDT);
	nIndex = pComBox->GetCurSel();
	nCount = pComBox->GetCount();

	if(nIndex < 0 || nIndex >= nCount)
	{
		return ;
	}

	switch(nIndex)
	{
	case Mode_Currency:
		{
			SetProductCtrlShowType(FALSE);
		}
		break;
	case Mode_Dedicated:
		{
			SetProductCtrlShowType(TRUE);
		}
		break;
	case Mode_LineDed:
		{
			SetProductCtrlShowType(FALSE);
		}
		break;
	case Mode_NotUse:
		{
			SetProductCtrlShowType(FALSE);
		}
		break;
	}
}


void CShowModeInfo::OnBnClickedModeSelProductnoBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	CSelProductDlg dlg;
	dlg.m_SearchInfo.bProductNormal = Sel_Check;
	if(dlg.DoModal() == IDOK)
	{
		GetDlgItem(IDC_SHOWMODEINFO_PRODID_EDT)->SetWindowText(dlg.m_strProductNo);
	}
}
