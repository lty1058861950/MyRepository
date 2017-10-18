// UpDepart.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "UpDepart.h"
#include "ShowUpDepart.h"

// CUpDepart 对话框

IMPLEMENT_DYNAMIC(CUpDepart, CDialog)

CUpDepart::CUpDepart(CWnd* pParent /*=NULL*/)
	: CDialog(CUpDepart::IDD, pParent)
{
	memset(&m_UpDepartInfo, 0, sizeof(StHrUpDepart));
}

CUpDepart::~CUpDepart()
{
}

void CUpDepart::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_UpDepartTree);
}


BEGIN_MESSAGE_MAP(CUpDepart, CDialog)
	ON_WM_SIZE()
	ON_NOTIFY(NM_CLICK, IDC_TREE1, &CUpDepart::OnNMClickTree1)
	ON_NOTIFY(NM_RCLICK, IDC_TREE1, &CUpDepart::OnNMRClickTree1)
	ON_COMMAND(ID_UP_DEPART_ADD, &CUpDepart::OnMenuDepartAdd)
	ON_COMMAND(ID_UP_DEPART_MODIFY, &CUpDepart::OnMenuDepartModify)
	ON_COMMAND(ID_UP_DEPART_DEL, &CUpDepart::OnMenuDepartDel)
END_MESSAGE_MAP()


// CUpDepart 消息处理程序

BOOL CUpDepart::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	int nIcons[] = {
		IDI_LEV_1,  IDI_LEV_2,  IDI_LEV_3,	IDI_LEV_4, 	// 0 - 4： 目录树管理
	};

	m_TreeImgList.Create(16,16,ILC_COLOR32 | ILC_MASK,0,0);
	for(int i=0; i<sizeof(nIcons); i++)
	{
		m_TreeImgList.Replace(-1, LoadIcon(::AfxGetInstanceHandle(), 
			MAKEINTRESOURCE(nIcons[i])));
	}

	m_UpDepartTree.SetImageList(&m_TreeImgList, TVSIL_NORMAL);
	m_UpDepartTree.SetItemHeight(20);


	InitPopMenu1( );					//初始化菜单1
	InitPopMenu2( );					//初始化菜单2

	MoveWindow(0,0,824,568);
	CenterWindow();
	InitDepartTree();

	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CUpDepart::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnOK();
}

void CUpDepart::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnCancel();
}

void CUpDepart::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	AutoSize();

	// TODO: 在此处添加消息处理程序代码
}

void CUpDepart::AutoSize()
{
	CRect Rect ;
	GetClientRect(&Rect) ;

	int nTreeWidth = 200;
	int nBtnWidth = 60;
	int nBtnHeight = 30;

	if (GetDlgItem(IDC_STATIC1)->GetSafeHwnd())
	{
		GetDlgItem(IDC_STATIC1)->MoveWindow(1,5,Rect.Width()-1*2,Rect.Height()-5*2);
	}

	if (m_UpDepartTree.GetSafeHwnd())
	{
		m_UpDepartTree.MoveWindow(1+5,21,nTreeWidth,Rect.Height()-70);
	}

	if (GetDlgItem(IDCANCEL)->GetSafeHwnd())
	{
		GetDlgItem(IDCANCEL)->MoveWindow(Rect.right-(nBtnWidth+30),Rect.bottom-(nBtnHeight+20),
			nBtnWidth,nBtnHeight);
	}
}


void  CUpDepart::InitPopMenu1( )					//初始化菜单1
{
	if(!m_PopupMenu1.GetSafeHmenu())
	{
		m_PopupMenu1.CreatePopupMenu();

		m_PopupMenu1.AppendMenu(MF_STRING, ID_UP_DEPART_ADD,		"添加部门");

	}
}

void  CUpDepart::InitPopMenu2( )					//初始化菜单1	
{
	if(!m_PopupMenu2.GetSafeHmenu())
	{
		m_PopupMenu2.CreatePopupMenu();

		m_PopupMenu2.AppendMenu(MF_STRING, ID_UP_DEPART_MODIFY,		"修改部门");
		m_PopupMenu2.AppendMenu(MF_STRING, ID_UP_DEPART_DEL,		"删除部门");

	}
}

void CUpDepart::InitDepartTree()
{
	m_UpDepartTree.DeleteAllItems();
	int nTreeID;
	HTREEITEM hParent1;
	if(NumTwoToOne(nTreeID,Group_Tree_Type1,0))
	{
		hParent1 = MyInsertTree(&m_UpDepartTree,_T("部门组织结构"),TVI_ROOT,nTreeID,0,0);
	}


	CTreeCtrl *pTree = &m_UpDepartTree;

	int i,nCount = 0;
	int Icon1 = 1,Icon2 = 1;

	nCount = g_AllUpDeparts.size();
	for (i = 0;i<nCount;i++)
	{
		if(NumTwoToOne(nTreeID,Group_Tree_Type2,g_AllUpDeparts.at(i).nOid))
		{
			MyInsertTree(pTree,g_AllUpDeparts.at(i).szUpDepartName,hParent1,nTreeID,Icon1,Icon2);
		}
	}


	if(nCount>0)
	{
		pTree->Expand(hParent1,TVE_EXPAND);
	}


}

void CUpDepart::NotFindSetNull()
{
	CString strText = _T("");
	GetDlgItem(IDC_EDIT1)->SetWindowText(strText);
	GetDlgItem(IDC_EDIT4)->SetWindowText(strText);
	GetDlgItem(IDC_EDIT5)->SetWindowText(strText);
	GetDlgItem(IDC_EDIT6)->SetWindowText(strText);

	GetDlgItem(IDC_EDIT7)->SetWindowText(strText);
	GetDlgItem(IDC_EDIT8)->SetWindowText(strText);
	GetDlgItem(IDC_EDIT9)->SetWindowText(strText);
}
void CUpDepart::ShowDepartInfo()
{
	NotFindSetNull();
	StHrUpDepart *pUpDepartInfo = &m_UpDepartInfo;
	CString strText;
	strText.Format(_T("%s"), pUpDepartInfo->szUpDepartName);
	GetDlgItem(IDC_EDIT1)->SetWindowText(strText);
	strText.Format(_T("%s"), pUpDepartInfo->szUpDepartNo);
	GetDlgItem(IDC_EDIT4)->SetWindowText(strText);
	strText.Format(_T("%s"), pUpDepartInfo->szUpDepartType);
	GetDlgItem(IDC_EDIT5)->SetWindowText(strText);
	strText.Format(_T("%s"), pUpDepartInfo->szCall);
	GetDlgItem(IDC_EDIT6)->SetWindowText(strText);
	strText.Format(_T("%s"), pUpDepartInfo->szFaxs);
	GetDlgItem(IDC_EDIT7)->SetWindowText(strText);
	strText.Format(_T("%s"), pUpDepartInfo->szAddress);
	GetDlgItem(IDC_EDIT8)->SetWindowText(strText);
	strText.Format(_T("%s"), pUpDepartInfo->szDescription);
	GetDlgItem(IDC_EDIT9)->SetWindowText(strText);
}

void CUpDepart::OnMenuDepartAdd()
{
	CShowUpDepart nDlg;
	nDlg.m_pUpDepart = &m_UpDepartInfo;
	nDlg.m_ShowType = UpDepart_Add;
	if(nDlg.DoModal() == IDOK)
	{
		ReGetAllDepartInfo();
		InitDepartTree();
	}
}
void CUpDepart::OnMenuDepartModify()
{
	CShowUpDepart nDlg;
	nDlg.m_pUpDepart = &m_UpDepartInfo;
	nDlg.m_ShowType = UpDepart_Modify;
	if(nDlg.DoModal() == IDOK)
	{
		ReGetAllDepartInfo();
		InitDepartTree();
	}
}
void CUpDepart::OnMenuDepartDel()
{
	int ret = 0;
	ret = DelTheUpDepart(&m_UpDepartInfo);
	if(ret >= 1)
	{
		ReGetAllDepartInfo();
		InitDepartTree();
	}
}

void CUpDepart::OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码


	TVHITTESTINFO	tvhtif;
	GetCursorPos(&tvhtif.pt);
	m_UpDepartTree.ScreenToClient(&tvhtif.pt);
	m_UpDepartTree.HitTest(&tvhtif);

	if(tvhtif.flags & TVHT_ONITEM)
	{
		memset(&m_UpDepartInfo, 0, sizeof(StHrUpDepart));
		//int nIcon1, nIcon2;
		//m_DepartMngTree->GetItemImage(tvhtif.hItem, nIcon1, nIcon2);
		CString strItem = m_UpDepartTree.GetItemText(tvhtif.hItem);
		if(strItem.IsEmpty())
			return;
		int nTreeID = m_UpDepartTree.GetItemData(tvhtif.hItem);

		// nTreeID  ： 目录树ID
		// strItem  ： 目录树名称
		// nIcon1   ： ICO位置值

		//int		nIconIndex = nIcon1

		int nType,nID;
		if(!NumOneToTwo(nTreeID,nType,nID))
		{
			return;
		}

		switch(nType)
		{
		case Group_Tree_Type1:
			{
				m_UpDepartInfo.TreeItemType = Group_Tree_Type1;
				m_UpDepartInfo.hItem = tvhtif.hItem;
				m_UpDepartInfo.nOid = nID;
				NotFindSetNull();
			}
			break;
		case Group_Tree_Type2:
			{
				if(nID>0)
				{
					//获取相关部门的所有信息//
					m_UpDepartInfo.TreeItemType = Group_Tree_Type2;
					m_UpDepartInfo.hItem = tvhtif.hItem;
					m_UpDepartInfo.nOid = nID;
					m_DMng.GetOneUpDepartInfoOID(nID,&m_UpDepartInfo);
					
					ShowDepartInfo();
				}
			}
			break;
		}
	}



	*pResult = 0;
}

void CUpDepart::OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码

	POINT	point;
	GetCursorPos(&point);


	TVHITTESTINFO	tvhtif;
	GetCursorPos(&tvhtif.pt);
	m_UpDepartTree.ScreenToClient(&tvhtif.pt);
	m_UpDepartTree.HitTest(&tvhtif);

	if(tvhtif.flags & TVHT_ONITEM)
	{
		memset(&m_UpDepartInfo, 0, sizeof(StHrUpDepart));
		//int nIcon1, nIcon2;
		//m_DepartMngTree->GetItemImage(tvhtif.hItem, nIcon1, nIcon2);
		CString strItem = m_UpDepartTree.GetItemText(tvhtif.hItem);
		if(strItem.IsEmpty())
			return;
		int nTreeID = m_UpDepartTree.GetItemData(tvhtif.hItem);

		// nTreeID  ： 目录树ID
		// strItem  ： 目录树名称
		// nIcon1   ： ICO位置值

		//int		nIconIndex = nIcon1

		int nType,nID;
		if(!NumOneToTwo(nTreeID,nType,nID))
		{
			return;
		}

		switch(nType)
		{
		case Group_Tree_Type1:
			{
				m_UpDepartInfo.TreeItemType = Group_Tree_Type1;
				m_UpDepartInfo.hItem = tvhtif.hItem;
				m_UpDepartInfo.nOid = nID;
				NotFindSetNull();
				m_PopupMenu1.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
			}
			break;
		case Group_Tree_Type2:
			{
				if(nID>0)
				{
					//获取相关部门的所有信息//
					m_UpDepartInfo.TreeItemType = Group_Tree_Type2;
					m_UpDepartInfo.hItem = tvhtif.hItem;
					m_UpDepartInfo.nOid = nID;
					m_DMng.GetOneUpDepartInfoOID(nID,&m_UpDepartInfo);
					ShowDepartInfo();

					m_PopupMenu2.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
				}
			}
			break;
		}
	}
	*pResult = 0;
}
