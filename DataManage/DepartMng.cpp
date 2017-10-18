// DepartMng.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataManage.h"
#include "DepartMng.h"
#include "BatchSelOpt.h"
#include "MainFrm.h"


// CDepartMng �Ի���

IMPLEMENT_DYNAMIC(CDepartMng, CDialog)

CDepartMng::CDepartMng(CWnd* pParent /*=NULL*/)
	: CDialog(CDepartMng::IDD, pParent)
{

	memset(&m_CurSelDepart,0,sizeof(StHrGroup));
}

CDepartMng::~CDepartMng()
{
}

void CDepartMng::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DEPART_MNG_TREE, m_DepartMngTree);
	DDX_Control(pDX, IDC_DEPART_USR_LIST, m_CurDepartUsrList);
}


BEGIN_MESSAGE_MAP(CDepartMng, CDialog)
	ON_WM_SIZE()
	ON_NOTIFY(NM_CLICK, IDC_DEPART_MNG_TREE, &CDepartMng::OnNMClickDepartMngTree)
	ON_BN_CLICKED(IDC_DEPART_ADD_BTN, &CDepartMng::OnBnClickedDepartAddBtn)
	ON_BN_CLICKED(IDC_DEPART_DEL_BTN, &CDepartMng::OnBnClickedDepartDelBtn)
	ON_BN_CLICKED(IDC_DEPART_EDIT_BTN, &CDepartMng::OnBnClickedDepartEditBtn)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(NM_DBLCLK, IDC_DEPART_MNG_TREE, &CDepartMng::OnNMDblclkDepartMngTree)
	ON_NOTIFY(NM_RCLICK, IDC_DEPART_MNG_TREE, &CDepartMng::OnNMRClickDepartMngTree)
	ON_BN_CLICKED(IDC_RECOVERY_BTN, &CDepartMng::OnBnClickedRecoveryBtn)
END_MESSAGE_MAP()


// CDepartMng ��Ϣ�������

BOOL CDepartMng::OnInitDialog()
{
	CDialog::OnInitDialog();

	int nIcons[] = {
		IDI_LEV_1,  IDI_LEV_2,  IDI_LEV_3,	IDI_LEV_4, 	// 0 - 4�� Ŀ¼������
	};

	m_TreeImgList.Create(16,16,ILC_COLOR32 | ILC_MASK,0,0);
	for(int i=0; i<sizeof(nIcons); i++)
	{
		m_TreeImgList.Replace(-1, LoadIcon(::AfxGetInstanceHandle(), 
			MAKEINTRESOURCE(nIcons[i])));
	}

	m_DepartMngTree.SetImageList(&m_TreeImgList, TVSIL_NORMAL);
	m_DepartMngTree.SetItemHeight(20);
	


	MoveWindow(0,0,824,568);
	CenterWindow();
	InitUsrList();
	InitDepartTree();

	//zt add 
	InitPopMenu1();
	InitPopMenu2();
	GetDlgItem(IDC_DEPART_STATIC10)->ShowWindow(FALSE);
	GetDlgItem(IDC_DEPART_USR_LIST)->ShowWindow(FALSE);

	InitContrlState();
	PostMessage(WM_SIZE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDepartMng::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	AutoSize();
	// TODO: �ڴ˴������Ϣ����������
}
void CDepartMng::InitContrlState()
{
	((CEdit*)GetDlgItem(IDC_DEPART_CODE_EDT))->SetReadOnly(TRUE);
	((CEdit*)GetDlgItem(IDC_DEPART_NAME_EDT))->SetReadOnly(TRUE);
	((CEdit*)GetDlgItem(IDC_DEPART_TYPE_EDT))->SetReadOnly(TRUE);
	((CEdit*)GetDlgItem(IDC_DEPART_DESCRIBE_EDT))->SetReadOnly(TRUE);
	((CEdit*)GetDlgItem(IDC_DEPART_PHONE_EDT))->SetReadOnly(TRUE);
	((CEdit*)GetDlgItem(IDC_DEPART_FAXES_EDT))->SetReadOnly(TRUE);
	((CEdit*)GetDlgItem(IDC_DEPART_ADDRESS_EDT))->SetReadOnly(TRUE);
}
void CDepartMng::InitUsrList()
{
	m_CurDepartUsrList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_GRIDLINES);
	m_CurDepartUsrList.InsertColumn(0, _T("���"),LVCFMT_CENTER, 50);
	m_CurDepartUsrList.InsertColumn(1, _T("��¼��"),LVCFMT_CENTER, 100);
	m_CurDepartUsrList.InsertColumn(2, _T("�û�ID"),LVCFMT_CENTER, 100);
	m_CurDepartUsrList.EnableRClickMenu(FALSE);
}
void CDepartMng::InitDepartTree()
{
	m_DepartMngTree.DeleteAllItems();
	int nTreeID;
	HTREEITEM hParent1;
	if(NumTwoToOne(nTreeID,Group_Tree_Type1,0))
	{
		hParent1 = MyInsertTree(&m_DepartMngTree,_T("������֯�ṹ"),TVI_ROOT,nTreeID,0,0);
	}


	CTreeCtrl *pTree = &m_DepartMngTree;
	
	int i,nCount = 0;
	int Icon1 = 1,Icon2 = 1;
	
	nCount = g_AllGroups.size();
	for (i = 0;i<nCount;i++)
	{
		if(NumTwoToOne(nTreeID,Group_Tree_Type2,g_AllGroups.at(i)->nOid))
		{
			MyInsertTree(pTree,g_AllGroups.at(i)->szGroupName,hParent1,nTreeID,Icon1,Icon2);
		}
	}
	

	if(nCount>0)
	{
		pTree->Expand(hParent1,TVE_EXPAND);
	}

	
}

void CDepartMng::AutoSize()
{
	CRect Rect ;
	GetClientRect(&Rect) ;

	int nTreeWidth = 300;
	//int nBtnHeight = 30;

	if (GetDlgItem(IDC_DEPART_STATIC1)->GetSafeHwnd())
	{
		GetDlgItem(IDC_DEPART_STATIC1)->MoveWindow(1,5,Rect.Width()-1*2,Rect.Height()-5*2);
	}

	if (m_DepartMngTree.GetSafeHwnd())
	{
		m_DepartMngTree.MoveWindow(1+5,21,200,Rect.Height()-70);
	}
	
	///-------------------///
	/*
	if (GetDlgItem(IDC_DEPART_STATIC2)->GetSafeHwnd())
	{
		GetDlgItem(IDC_DEPART_STATIC2)->MoveWindow(nTreeWidth+20,71,60,20);
	}
	if (GetDlgItem(IDC_DEPART_CODE_EDT)->GetSafeHwnd())
	{
		GetDlgItem(IDC_DEPART_CODE_EDT)->MoveWindow(nTreeWidth+20+65,71,100,20);
	}
	if (GetDlgItem(IDC_DEPART_STATIC3)->GetSafeHwnd())
	{
		GetDlgItem(IDC_DEPART_STATIC3)->MoveWindow(nTreeWidth+20+65+120,71,60,20);
	}if (GetDlgItem(IDC_DEPART_NAME_EDT)->GetSafeHwnd())
	{
		GetDlgItem(IDC_DEPART_NAME_EDT)->MoveWindow(nTreeWidth+20+65+120+65,71,100,20);
	}
	if (GetDlgItem(IDC_DEPART_STATIC4)->GetSafeHwnd())
	{
		GetDlgItem(IDC_DEPART_STATIC4)->MoveWindow(nTreeWidth+20+65+120+65+120,71,60,20);
	}
	if (GetDlgItem(IDC_DEPART_TYPE_EDT)->GetSafeHwnd())
	{
		GetDlgItem(IDC_DEPART_TYPE_EDT)->MoveWindow(nTreeWidth+20+65+120+65+120+65,71,100,20);
	}
	//�绰�ʹ���//
	if (GetDlgItem(IDC_DEPART_STATIC5)->GetSafeHwnd())
	{
		GetDlgItem(IDC_DEPART_STATIC5)->MoveWindow(nTreeWidth+20,71+50,60,20);
	}
	if (GetDlgItem(IDC_DEPART_PHONE_EDT)->GetSafeHwnd())
	{
		GetDlgItem(IDC_DEPART_PHONE_EDT)->MoveWindow(nTreeWidth+20+65,71+50,150,20);
	}
	if (GetDlgItem(IDC_DEPART_STATIC6)->GetSafeHwnd())
	{
		GetDlgItem(IDC_DEPART_STATIC6)->MoveWindow(nTreeWidth+20+65+170,71+50,60,20);
	}
	if (GetDlgItem(IDC_DEPART_FAXES_EDT)->GetSafeHwnd())
	{
		GetDlgItem(IDC_DEPART_FAXES_EDT)->MoveWindow(nTreeWidth+20+65+170+65,71+50,150,20);
	}
	//��ַ//
	if (GetDlgItem(IDC_DEPART_STATIC7)->GetSafeHwnd())
	{
		GetDlgItem(IDC_DEPART_STATIC7)->MoveWindow(nTreeWidth+20,71+50*2,60,20);
	}
	if (GetDlgItem(IDC_DEPART_ADDRESS_EDT)->GetSafeHwnd())
	{
		GetDlgItem(IDC_DEPART_ADDRESS_EDT)->MoveWindow(nTreeWidth+20+65,71+50*2,300,20);
	}

//�û�������//
	if (GetDlgItem(IDC_DEPART_STATIC8)->GetSafeHwnd())
	{
		GetDlgItem(IDC_DEPART_STATIC8)->MoveWindow(nTreeWidth+20,Rect.bottom-310,200,260);
	}
	if (GetDlgItem(IDC_DEPART_USR_LIST)->GetSafeHwnd())
	{
		GetDlgItem(IDC_DEPART_USR_LIST)->MoveWindow(nTreeWidth+20+5,Rect.bottom-310+20,180,220);
	}
	if (GetDlgItem(IDC_DEPART_STATIC9)->GetSafeHwnd())
	{
		GetDlgItem(IDC_DEPART_STATIC9)->MoveWindow(nTreeWidth+20+220,Rect.bottom-310,200,250);
	}
	if (GetDlgItem(IDC_DEPART_DESCRIBE_EDT)->GetSafeHwnd())
	{
		GetDlgItem(IDC_DEPART_DESCRIBE_EDT)->MoveWindow(nTreeWidth+20+220+5,Rect.bottom-310+20,180,220);
	}
	*/
///���  ɾ��  �޸�////

	

	int nBtnWidth = 60;
	int nBtnHeight = 30;
	if (GetDlgItem(IDC_RECOVERY_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_RECOVERY_BTN)->MoveWindow(10,Rect.bottom-40,nBtnWidth,nBtnHeight);
	}

	if (GetDlgItem(IDC_DEPART_ADD_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_DEPART_ADD_BTN)->MoveWindow(10,Rect.bottom-40,nBtnWidth,nBtnHeight);
	}
	if (GetDlgItem(IDC_DEPART_DEL_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_DEPART_DEL_BTN)->MoveWindow(10+nBtnWidth+10,Rect.bottom-40,nBtnWidth,nBtnHeight);
	}
	if (GetDlgItem(IDC_DEPART_EDIT_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_DEPART_EDIT_BTN)->MoveWindow(10+(nBtnWidth+10)*2,Rect.bottom-40,nBtnWidth,nBtnHeight);
	}

}

void  CDepartMng::InitPopMenu1( )					//��ʼ���˵�1
{
	if(!m_PopupMenu1.GetSafeHmenu())
	{
		m_PopupMenu1.CreatePopupMenu();

		m_PopupMenu1.AppendMenu(MF_STRING, IDC_DEPART_ADD_BTN,		"��Ӳ���");
		m_PopupMenu1.AppendMenu(MF_STRING, IDC_RECOVERY_BTN,        "�ָ�����");

	}
}

void  CDepartMng::InitPopMenu2( )					//��ʼ���˵�1	
{
	if(!m_PopupMenu2.GetSafeHmenu())
	{
		m_PopupMenu2.CreatePopupMenu();

		m_PopupMenu2.AppendMenu(MF_STRING, IDC_DEPART_EDIT_BTN,		"�޸Ĳ���");

		m_PopupMenu2.AppendMenu(MF_STRING, IDC_DEPART_DEL_BTN,		"ɾ������");

	}
}


void CDepartMng::NotFindSetNull()
{
	GetDlgItem(IDC_DEPART_CODE_EDT)->SetWindowText(_T(""));
	GetDlgItem(IDC_DEPART_NAME_EDT)->SetWindowText(_T(""));
	GetDlgItem(IDC_DEPART_TYPE_EDT)->SetWindowText(_T(""));

	GetDlgItem(IDC_DEPART_DESCRIBE_EDT)->SetWindowText(_T(""));
	GetDlgItem(IDC_DEPART_PHONE_EDT)->SetWindowText(_T(""));
	GetDlgItem(IDC_DEPART_FAXES_EDT)->SetWindowText(_T(""));

	GetDlgItem(IDC_DEPART_ADDRESS_EDT)->SetWindowText(_T(""));
	m_CurDepartUsrList.DeleteAllItems();
}
void CDepartMng::ShowDepartInfo()
{
	NotFindSetNull();

	m_DepartMngTree.SetItemText(m_CurSelDepart.hItem,m_CurSelDepart.szGroupName);
	GetDlgItem(IDC_DEPART_CODE_EDT)->SetWindowText(m_CurSelDepart.szGroupNo);
	GetDlgItem(IDC_DEPART_NAME_EDT)->SetWindowText(m_CurSelDepart.szGroupName);
	GetDlgItem(IDC_DEPART_TYPE_EDT)->SetWindowText(m_CurSelDepart.szGroupType);
	GetDlgItem(IDC_DEPART_DESCRIBE_EDT)->SetWindowText(m_CurSelDepart.szDescription);
	GetDlgItem(IDC_DEPART_PHONE_EDT)->SetWindowText(m_CurSelDepart.szCall);
	GetDlgItem(IDC_DEPART_FAXES_EDT)->SetWindowText(m_CurSelDepart.szFaxs);
	GetDlgItem(IDC_DEPART_ADDRESS_EDT)->SetWindowText(m_CurSelDepart.szAddress);
	
	
}


void CDepartMng::OnNMClickDepartMngTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	TVHITTESTINFO	tvhtif;
	GetCursorPos(&tvhtif.pt);
	m_DepartMngTree.ScreenToClient(&tvhtif.pt);
	m_DepartMngTree.HitTest(&tvhtif);

	if(tvhtif.flags & TVHT_ONITEM)
	{
		memset(&m_CurSelDepart,0,sizeof(StHrGroup));
		//int nIcon1, nIcon2;
		//m_DepartMngTree->GetItemImage(tvhtif.hItem, nIcon1, nIcon2);
		CString strItem = m_DepartMngTree.GetItemText(tvhtif.hItem);
		if(strItem.IsEmpty())
			return;
		int nTreeID = m_DepartMngTree.GetItemData(tvhtif.hItem);

		// nTreeID  �� Ŀ¼��ID
		// strItem  �� Ŀ¼������
		// nIcon1   �� ICOλ��ֵ

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
				m_CurSelDepart.TreeItemType = Group_Tree_Type1;
				m_CurSelDepart.hItem = tvhtif.hItem;
				m_CurSelDepart.nOid = nID;
				NotFindSetNull();
			}
			break;
		case Group_Tree_Type2:
			{
				if(nID>0)
				{
					//��ȡ��ز��ŵ�������Ϣ//
					m_CurSelDepart.TreeItemType = Group_Tree_Type2;
					m_CurSelDepart.hItem = tvhtif.hItem;
					m_CurSelDepart.nOid = nID;
					m_DMng.GetOneGroupInfoOID(nID,&m_CurSelDepart);
					ShowDepartInfo();
				}
			}
			break;
		}
	}
	*pResult = 0;
}

void CDepartMng::SetDepartTree(CString strText,int EditMode,int Param,HTREEITEM NextItem)
{
	////EditMode  1.��ʾ���  2����ʾ�޸� 3.��ʾɾ��
	TVHITTESTINFO	tvhtif;
	tvhtif.hItem = m_DepartMngTree.GetSelectedItem();

	if(EditMode == 1)
	{
		HTREEITEM hNewItem;
		hNewItem = MyInsertTree(&m_DepartMngTree,strText,tvhtif.hItem,Param);
		m_DepartMngTree.SelectItem(hNewItem);
	}else if(EditMode == 2)
	{
		m_DepartMngTree.SetItemText(tvhtif.hItem,strText);
	}else if(EditMode == 3)
	{
		m_DepartMngTree.DeleteItem(tvhtif.hItem);
		m_DepartMngTree.SelectItem(NextItem);
	}
	m_DepartMngTree.SetFocus();
}
BOOL CDepartMng::AddNewDepart(StHrGroup *pDepartInfo)
{
	if(m_DMng.AddNewGroup(pDepartInfo))
	{
		ReGetAllGroupInfo();
		InitDepartTree();
		return TRUE;
	}
	return FALSE;
}
BOOL CDepartMng::EditOneDepart(StHrGroup *pDepartInfo)
{
	if(m_DMng.EditOldGroup(pDepartInfo))
	{
		//����޸����˵�ǰѡ�еĲ���//
		//1.����״̬����״̬��Ϣ
		if(pDepartInfo->nOid == g_CurSelDepart.nOid)
		{
			CString strCurDepart;
			strCurDepart.Format(_T("��ǰ����:%s"),g_CurSelDepart.szGroupName);
			g_MainFram->m_wndWorkSpace.SetWindowText(strCurDepart);
			g_MainFram->m_wndStatusBar.SetPaneText(3,strCurDepart);

		}
		memcpy(&m_CurSelDepart,pDepartInfo,sizeof(StHrGroup));
		ShowDepartInfo();
		return TRUE;
	}
	return FALSE;
}
BOOL CDepartMng::DeleteOneDepart(StHrGroup *pDepartInfo)
{
	////1.����Ƿ��� ��Ʒ�������� �������й� ����  ������ʾ
	////2.���ͱ������йص���Ա ���Ѳ��ź��û���ϵ�� USR_DEPART_DID��Ϊ��
	////3.ɾ��������


	////ɾ��������

	return m_DMng.DelGroup(pDepartInfo->nOid);
}


void CDepartMng::OnBnClickedDepartAddBtn()
{
	CString  strParentDID;
	TVHITTESTINFO	tvhtif;
	tvhtif.hItem = m_DepartMngTree.GetSelectedItem();
	if(!tvhtif.hItem)
	{
		AfxMessageBox(_T("δѡ�и�����"));
		return;
	}
	if(tvhtif.hItem == m_DepartMngTree.GetRootItem())
	{
		strParentDID = _T("");
		
	}else
	{
		int nTreeID = m_DepartMngTree.GetItemData(tvhtif.hItem);
		strParentDID = GetStringID(nTreeID);
	}

	CString strItem = m_DepartMngTree.GetItemText(tvhtif.hItem);
	if(strItem.IsEmpty())
		return;

	CShowDepart nDlg(1,this,strParentDID);
	if(nDlg.DoModal() == IDOK)
	{

	}
}

void CDepartMng::OnBnClickedDepartDelBtn()
{
	if(m_CurSelDepart.hItem == NULL)
	{
		return ;
	}

	CString strText;
	strText.Format(_T("�Ƿ�Ҫɾ��\" %s \"�˲���(��/��)?"),m_CurSelDepart.szGroupName);
	if(MessageBox(strText,_T("��ʾ"),MB_YESNO|MB_ICONINFORMATION) != IDYES)
	{
		return;
	}

	if(DeleteOneDepart(&m_CurSelDepart))
	{
		ReGetAllGroupInfo();
		//���ɾ���˵�ǰѡ�еĲ���//
		//1.��ʼ������  2.����״̬����״̬��Ϣ
		if(m_CurSelDepart.nOid == g_CurSelDepart.nOid)
		{
			memset(&g_CurSelDepart,0,sizeof(StHrGroup));
			g_pLeftTree->InitGuideTree();
			CString strCurDepart;
			strCurDepart.Format(_T("��ǰ����:%s"),g_CurSelDepart.szGroupName);
			g_MainFram->m_wndWorkSpace.SetWindowText(strCurDepart);
			g_MainFram->m_wndStatusBar.SetPaneText(3,strCurDepart);

		}
		InitDepartTree();
		strText.Format(_T("ɾ�� \"%s\" ���ųɹ�!"),g_CurSelDepart.szGroupName);
		AfxMessageBox(strText);
		return;
	}else
	{
		strText.Format(_T("ɾ�� \"%s\" ����ʧ��!"),g_CurSelDepart.szGroupName);
		AfxMessageBox(strText);
	}

}

void CDepartMng::OnBnClickedDepartEditBtn()
{
	CString  strParentDID,strDepartID;
	TVHITTESTINFO	tvhtif;
	tvhtif.hItem = m_DepartMngTree.GetSelectedItem();
	if(tvhtif.hItem == m_DepartMngTree.GetRootItem())
		return;
	CString strItem = m_DepartMngTree.GetItemText(tvhtif.hItem);
	if(strItem.IsEmpty())
		return;

	if(tvhtif.hItem != m_DepartMngTree.GetRootItem())
	{
		HTREEITEM hPTreeItem = m_DepartMngTree.GetParentItem(tvhtif.hItem);
		if(hPTreeItem == m_DepartMngTree.GetRootItem())
		{
			strParentDID = _T("");
		}else
		{
			int nPTreeID = m_DepartMngTree.GetItemData(hPTreeItem);
			strParentDID = GetStringID(nPTreeID);
		}
	}
	int nTreeID = m_DepartMngTree.GetItemData(tvhtif.hItem);
	if(!nTreeID)
		return;
	strDepartID = GetStringID(nTreeID);

	CShowDepart nDlg(2,this,strParentDID,strDepartID);
	nDlg.DoModal();
}




void CDepartMng::OnNMDblclkDepartMngTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	//OnBnClickedDepartEditBtn();
	*pResult = 0;
}

void CDepartMng::OnNMRClickDepartMngTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	POINT	point;
	GetCursorPos(&point);

	TVHITTESTINFO	tvhtif;
	GetCursorPos(&tvhtif.pt);
	m_DepartMngTree.ScreenToClient(&tvhtif.pt);
	m_DepartMngTree.HitTest(&tvhtif);

	if(tvhtif.flags & TVHT_ONITEM)
	{
		memset(&m_CurSelDepart,0,sizeof(StHrGroup));
		//int nIcon1, nIcon2;
		//m_DepartMngTree->GetItemImage(tvhtif.hItem, nIcon1, nIcon2);
		CString strItem = m_DepartMngTree.GetItemText(tvhtif.hItem);
		if(strItem.IsEmpty())
			return;
		int nTreeID = m_DepartMngTree.GetItemData(tvhtif.hItem);

		// nTreeID  �� Ŀ¼��ID
		// strItem  �� Ŀ¼������
		// nIcon1   �� ICOλ��ֵ

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
				m_CurSelDepart.TreeItemType = Group_Tree_Type1;
				m_CurSelDepart.hItem = tvhtif.hItem;
				m_CurSelDepart.nOid = nID;
				NotFindSetNull();
				m_PopupMenu1.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
			}
			break;
		case Group_Tree_Type2:
			{
				if(nID>0)
				{
					//��ȡ��ز��ŵ�������Ϣ//
					m_CurSelDepart.TreeItemType = Group_Tree_Type2;
					m_CurSelDepart.hItem = tvhtif.hItem;
					m_CurSelDepart.nOid = nID;
					m_DMng.GetOneGroupInfoOID(nID,&m_CurSelDepart);
					ShowDepartInfo();
					m_PopupMenu2.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
				}
			}
			break;
		}
	}
	*pResult = 0;
}

void CDepartMng::OnBnClickedRecoveryBtn()
{
	CBatchSelOpt dlg;
	dlg.m_nType = Batch_Group;
	if(dlg.DoModal() == IDOK)
	{
		ReGetAllGroupInfo();//���»�ȡ��Ч�Ĳ�����Ϣ///
		InitDepartTree();
	}
}
