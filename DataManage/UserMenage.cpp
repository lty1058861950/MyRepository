// UserMenage.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "UserMenage.h"

// CUserMenage 对话框

IMPLEMENT_DYNAMIC(CUserMenage, CDialog)

CUserMenage::CUserMenage(CWnd* pParent /*=NULL*/)
	: CDialog(CUserMenage::IDD, pParent)
{
	memset(&m_CurUserInfo,0,sizeof(StHrUser));
}

CUserMenage::~CUserMenage()
{
}

void CUserMenage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_USRMNG_LIST1, m_UsrMngList);
}


BEGIN_MESSAGE_MAP(CUserMenage, CDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_USRMNGADD_BTN, &CUserMenage::OnBnClickedUsrmngaddBtn)
	ON_BN_CLICKED(IDC_USRMNGEDT_BTN, &CUserMenage::OnBnClickedUsrmngedtBtn)
	ON_BN_CLICKED(IDC_USRMNGDEL_BTN, &CUserMenage::OnBnClickedUsrmngdelBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_USRMNG_LIST1, &CUserMenage::OnNMDblclkUsrmngList1)
	ON_NOTIFY(NM_RCLICK, IDC_USRMNG_LIST1, &CUserMenage::OnNMRClickUsrmngList1)
	ON_BN_CLICKED(IDC_BTN_EXIT, &CUserMenage::OnBnClickedBtnExit)
END_MESSAGE_MAP()


// CUserMenage 消息处理程序

BOOL CUserMenage::OnInitDialog()
{
	CDialog::OnInitDialog();

	char *ColName[] = {"序号","用户登录名","姓名","所属部门","用户类型",
		"签名文件","办公电话","邮箱","手机","PAD号"};
	int  ColWidth[] = {50,100,100,100,100,  100,100,100,100,100,  100,50};
	m_UsrMngList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_GRIDLINES);

	for(int i = 0;i<10;i++)
	{
		m_UsrMngList.InsertColumn(i, ColName[i],LVCFMT_CENTER, ColWidth[i]);
	}
	m_UsrMngList.EnableRClickMenu(FALSE);
	//m_DbList.SetImageList(&m_ilLarge, LVSIL_NORMAL);
	//m_DbList.SetImageList(&m_ilSmall, LVSIL_SMALL);

	//根据角色权限设置按钮状态//

	/////////////////////////////

	MoveWindow(0,0,g_WinWidth,g_WinHeight);
	CenterWindow();

	InitPopMenu1( );
	InitPopMenu2( );
	InitTestList();
	PostMessage(WM_SIZE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void CUserMenage::InsertUserToList(StHrUser *pUserInfo)
{
	CEditableListCtrl *pList = &m_UsrMngList;
	CString strText;
	int pos = 1,nCount;
	nCount = pList->GetItemCount();
	strText.Format(_T("%d"), nCount+1);
	pList->InsertItem(nCount, strText);
	pList->SetItemData(nCount,pUserInfo->nOid);
	//OID不显示//
	pos = 1;
	strText.Format(_T("%s"), pUserInfo->szLoginName);
	pList->SetItemText(nCount,pos++,strText);
	strText.Format(_T("%s"), pUserInfo->szUserName);
	pList->SetItemText(nCount,pos++,strText);

	//获取用户的部门//
	strText.Format(_T("%s"), pUserInfo->szGroupName);
	pList->SetItemText(nCount,pos++,strText);

	strText.Format(_T("%s"), GetUserTypeText(pUserInfo->nUserType));
	pList->SetItemText(nCount,pos++,strText);

	strText.Format(_T("%s"), pUserInfo->szUserSignfile);
	pList->SetItemText(nCount,pos++,strText);

	strText.Format(_T("%s"), pUserInfo->szCall);
	pList->SetItemText(nCount,pos++,strText);

	strText.Format(_T("%s"), pUserInfo->szEmail);
	pList->SetItemText(nCount,pos++,strText);
	strText.Format(_T("%s"), pUserInfo->szPhone);
	pList->SetItemText(nCount,pos++,strText);
	strText.Format(_T("%d"), pUserInfo->nPadDevID);
	pList->SetItemText(nCount,pos++,strText);

}
void CUserMenage::InitTestList()
{
	m_UsrMngList.DeleteAllItems();
	
	vector<StHrUser *> nUserArry;
	if(m_DMng.GetAllUserToPad(&nUserArry))
	{
		int i, nCount = nUserArry.size();
		for( i = 0;i<nCount;i++)
		{
			StHrUser *pUserInfo = NULL;
			pUserInfo = nUserArry.at(i);
			if(pUserInfo == NULL)
			{
				continue;
			}

			InsertUserToList(pUserInfo);
			delete pUserInfo;
		}
		nUserArry.clear();

	}

}

void  CUserMenage::InitPopMenu1( )					//初始化菜单1
{
	if(!m_PopupMenu1.GetSafeHmenu())
	{
		m_PopupMenu1.CreatePopupMenu();

		m_PopupMenu1.AppendMenu(MF_STRING, IDC_USRMNGEDT_BTN,		"编辑用户");
		m_PopupMenu1.AppendMenu(MF_STRING, IDC_USRMNGDEL_BTN,		"删除用户");

	}
}

void  CUserMenage::InitPopMenu2( )					//初始化菜单1	
{
	if(!m_PopupMenu2.GetSafeHmenu())
	{
		m_PopupMenu2.CreatePopupMenu();

		m_PopupMenu2.AppendMenu(MF_STRING, IDC_USRMNGEDT_BTN,		"编辑用户");

	}
}

void CUserMenage::AutoSize()
{
	CRect Rect ;
	GetClientRect(&Rect) ;

	int nBtnWidth = 80;
	int nBtnHeight = 30;


	if (!GetDlgItem(IDC_USRMNG_STATIC1)->GetSafeHwnd())
	{
		return;
	}

	if (GetDlgItem(IDC_USRMNG_STATIC1)->GetSafeHwnd())
	{
		GetDlgItem(IDC_USRMNG_STATIC1)->MoveWindow(1,5,Rect.Width()-1*2,Rect.Height()-5*2);
	}
	if (m_UsrMngList.GetSafeHwnd())
	{
		m_UsrMngList.MoveWindow(11,51,Rect.Width()-22,Rect.Height()-102);
	}


	if (GetDlgItem(IDC_USRMNGADD_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_USRMNGADD_BTN)->MoveWindow(10,Rect.bottom-44,nBtnWidth,nBtnHeight);
	}

	if (GetDlgItem(IDC_USRMNGEDT_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_USRMNGEDT_BTN)->MoveWindow(10+(nBtnWidth+10)*1,Rect.bottom-44,nBtnWidth,nBtnHeight);
	}

	if (GetDlgItem(IDC_USRMNGDEL_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_USRMNGDEL_BTN)->MoveWindow(10+(nBtnWidth+10)*2,Rect.bottom-44,nBtnWidth,nBtnHeight);
	}

	/*
	if (GetDlgItem(IDC_USRMNGVIEW_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_USRMNGVIEW_BTN)->MoveWindow(10+(nBtnWidth+10)*3,Rect.bottom-44,nBtnWidth,nBtnHeight);
	}
	if (GetDlgItem(IDC_USRMNGREFRESH_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_USRMNGREFRESH_BTN)->MoveWindow(10+(nBtnWidth+10)*4,Rect.bottom-44,nBtnWidth,nBtnHeight);
	}
	*/

	GetDlgItem(IDC_BTN_EXIT)->MoveWindow(Rect.right-(nBtnWidth+10)-10, Rect.bottom-44,nBtnWidth,nBtnHeight);

}
void CUserMenage::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	AutoSize();
	
	// TODO: 在此处添加消息处理程序代码
}

BOOL  CUserMenage::AddNewUsr(StHrUser *nUsrInfo)
{
	if(m_DMng.AddNewUser(nUsrInfo))
	{
		InitTestList();
		return TRUE;
		
	}
	return FALSE;

}
BOOL  CUserMenage::DelOneUsr(CString strLoginName)
{
	return m_DMng.DelUser(strLoginName.GetBuffer(0));
}
BOOL  CUserMenage::EditOneUsr(StHrUser *pUsrInfo)
{
	if(m_DMng.EditOldUser(pUsrInfo))
	{
		InitTestList();
		return TRUE;
	}
	return FALSE;

}
void CUserMenage::OnBnClickedUsrmngaddBtn()
{
	CShowUsr nDlg(1,this);
	nDlg.DoModal();
}

void CUserMenage::OnBnClickedUsrmngedtBtn()
{
	int Index = m_UsrMngList.GetFirstSelectedItem();
	if (Index < 0)
	{
		AfxMessageBox("请先选中要更改的记录!");
		return;
	}

	UINT nUserOid = m_UsrMngList.GetItemData(Index);
	memset(&m_CurUserInfo,0,sizeof(StHrUser));
	if(m_DMng.GetOneUsrInfoOid(nUserOid,&m_CurUserInfo))
	{
		CShowUsr nDlg(2,this);
		nDlg.DoModal();
	}
	
}


void CUserMenage::OnBnClickedUsrmngdelBtn()
{
	int Index = m_UsrMngList.GetFirstSelectedItem();

	if (Index < 0)
	{
		AfxMessageBox("请先选中要删除的记录!");
		return;
	}

	if(Index>=0)
	{
		CString strName = m_UsrMngList.GetItemText(Index,1);
		if(strName== g_Admin)
		{
			AfxMessageBox(_T("不能删除,系统管理员用户!"));
			return;
		}
		if(strName == g_LoginUsrInfo.szLoginName)
		{
			AfxMessageBox(_T("不能删除自己!"));
			return;
		}

		CString strText;
		strText.Format(_T("是否要删除\" %s \"此用户(是/否)?"),strName);
		if(MessageBox(strText,_T("提示"),MB_YESNO|MB_ICONINFORMATION) != IDYES)
		{
			return;
		}

		if(DelOneUsr(m_UsrMngList.GetItemText(Index,1)))
		{
			InitTestList();
			AfxMessageBox(_T("删除用户成功!"));
		}else
		{
			AfxMessageBox(_T("删除用户时失败!"));
		}
		
	}
}


void CUserMenage::OnNMDblclkUsrmngList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码//
	
	//ztedit
	//OnBnClickedUsrmngviewBtn();
	OnBnClickedUsrmngedtBtn();

	*pResult = 0;
}



void CUserMenage::OnNMRClickUsrmngList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int Index = m_UsrMngList.GetFirstSelectedItem(),nCount = m_UsrMngList.GetItemCount();
	if(Index <0 || Index >= nCount)
	{
		return;
	}

	POINT	point;
	GetCursorPos(&point);
	CString strUserType = m_UsrMngList.GetItemText(Index,4);
	if(strcmp(strUserType,g_UserType[user_admin]) == 0)
	{
		m_PopupMenu2.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
	}else
	{
		m_PopupMenu1.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
	}
	
	*pResult = 0;
}

void CUserMenage::OnBnClickedBtnExit()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}
