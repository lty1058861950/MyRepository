// LeftTree.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataManage.h"
#include "LeftTree.h"
#include "MainFrm.h"
#include "ProdMng.h"

// CLeftTree �Ի���

IMPLEMENT_DYNAMIC(CLeftTree, CDialog)
CLeftTree     *g_pLeftTree = NULL;
CLeftTree::CLeftTree(CWnd* pParent /*=NULL*/)
	: CDialog(CLeftTree::IDD, pParent)
{
	memset(m_TaskTreeItem,0,sizeof(m_TaskTreeItem));
	g_pLeftTree = this;
}

CLeftTree::~CLeftTree()
{
}

void CLeftTree::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LEFT_TREE, m_GuideTree);
}


BEGIN_MESSAGE_MAP(CLeftTree, CDialog)
	ON_WM_SIZE()
	ON_NOTIFY(NM_CLICK, IDC_LEFT_TREE, &CLeftTree::OnNMClickLeftTree)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(NM_RCLICK, IDC_LEFT_TREE, &CLeftTree::OnNMRClickLeftTree)
	ON_COMMAND(ID_L_ADDMODE_MENU, &CLeftTree::AddModeMenu)
	ON_COMMAND(ID_L_ADDPRODUCT_MENU, &CLeftTree::AddProductMenu)
	ON_COMMAND(ID_L_DELMODE_MENU, &CLeftTree::DelModeMenu)
	ON_COMMAND(ID_L_COPYMODE_MENU, &CLeftTree::CopyModeMenu)
	ON_COMMAND(ID_L_PASTEMODE_MENU, &CLeftTree::PasteModeMenu)

	ON_COMMAND(ID_L_ADDTASK_MENU, &CLeftTree::AddTaskMenu)
	ON_COMMAND(ID_L_DELTASK_MENU, &CLeftTree::DelTaskMenu)
	ON_COMMAND(ID_L_SENDTASK_MENU, &CLeftTree::SendTaskMenu)
	ON_COMMAND(ID_L_STOPTASK_MENU, &CLeftTree::StopTaskMenu)
	
END_MESSAGE_MAP()


// CLeftTree ��Ϣ�������


BOOL CLeftTree::OnInitDialog()
{
	CDialog::OnInitDialog();

	int nIcons[] = {
		IDI_LEV_1,  IDI_LEV_2,  IDI_LEV_3,	IDI_LEV_4, 	// 0 - 4�� Ŀ¼������
		IDI_ICON1,  IDI_ICON2,  IDI_ICON6,  IDI_ICON5,
		IDI_ICON3,  IDI_ICON4,  IDI_LEV_3_2, IDI_LEV_3_3
	};

	m_TreeImgList.Create(16,16,ILC_COLOR32 | ILC_MASK,0,0);
	for(int i=0; i<sizeof(nIcons); i++)
	{
		m_TreeImgList.Replace(-1, LoadIcon(::AfxGetInstanceHandle(), 
			MAKEINTRESOURCE(nIcons[i])));
	}

	m_GuideTree.SetImageList(&m_TreeImgList, TVSIL_NORMAL);
	m_GuideTree.SetItemHeight(20);
	InitGuideTree();


	InitTaskMenu1( );					//��ʼ���˵�1
	InitTaskMenu2( );					//��ʼ���˵�2

	InitModeMenu1( );					//��ʼ���˵�1
	InitModeMenu1_1( );				//��ʼ���˵�1
	InitModeMenu1_2();
	InitModeMenu2( );					//��ʼ���˵�2
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CLeftTree::AddModeMenu()
{
	CShowModeInfo *pShowModeInfo = &g_DtMngView->m_ShowInfoList.m_ShowModeInfo;
	pShowModeInfo->AddNewMode();
			
				
	//g_DtMngView->m_ShowInfoList.m_ShowModeInfo.AddNewMode();
}

void CLeftTree::AddProductMenu()
{
	int ret = 0;
	CProdMng nProdMng;
	nProdMng.m_ShowType = Add_Product;
	if(nProdMng.DoModal() == IDOK)
	{
		nProdMng.m_CurProdInfo.nPicNumType = Product_normal;
		nProdMng.m_CurProdInfo.nGroupOid = g_CurSelDepart.nOid;
		ret = AddNewProd(&nProdMng.m_CurProdInfo);
		if(ret == 1)
		{
			g_pLeftTree->InitGuideTree();
		}
	}
}
void CLeftTree::DelModeMenu()
{
	CShowModeInfo *pShowModeInfo = &g_DtMngView->m_ShowInfoList.m_ShowModeInfo;
	pShowModeInfo->DelMode();
}
void CLeftTree::CopyModeMenu()
{
	CShowModeInfo *pShowModeInfo = &g_DtMngView->m_ShowInfoList.m_ShowModeInfo;
	pShowModeInfo->CopyModeTree();
}
void CLeftTree::PasteModeMenu()
{
	CShowModeInfo *pShowModeInfo = &g_DtMngView->m_ShowInfoList.m_ShowModeInfo;
	pShowModeInfo->PasteMode();
}

void CLeftTree::AddTaskMenu()
{
	//CShowTaskInfo *pShowTaskInfo = &g_DtMngView->m_ShowInfoList.m_ShowTaskInfo;
	//pShowTaskInfo->AddNewTask();
}
void CLeftTree::DelTaskMenu()
{
	CShowTaskInfo *pShowTaskInfo = &g_DtMngView->m_ShowInfoList.m_ShowTaskInfo;
	pShowTaskInfo->DelTast();
}
void CLeftTree::SendTaskMenu()
{
	CShowTaskInfo *pShowTaskInfo = &g_DtMngView->m_ShowInfoList.m_ShowTaskInfo;
	UINT nGroupOid = g_CurSelDepart.nOid;
	HTREEITEM hItem = m_TaskTreeItem[Task_Runing];
	if(pShowTaskInfo->SendTaskToPad())
	{
		StBasTask *pTaskInfo = &pShowTaskInfo->m_CurTaskInfo;
		CTreeCtrl *pTree = pTaskInfo->stTaskBaseInfo.pTaskTree;
		
		//ˢ�� ִ���е�ת̨��//
		//DelTreeChildItem(pTree,hItem);
		//InitTaskStatusProdTree(hItem,nGroupOid,Task_Runing);

		RefleshExecuteTree( );
		RefleshFinishedTree( );

		//���µ�ǰ����� ���ڵ������״̬//
		//���ý���//
		pTree->SelectItem(pTaskInfo->stTaskBaseInfo.hItem);
		int nIcon1 = GetTaskIcon(pTaskInfo->stTaskBaseInfo.nTaskStatus);
		pTree->SetItemImage(pTaskInfo->stTaskBaseInfo.hItem,nIcon1,nIcon1);
		AfxMessageBox("���񵼳����!");
	}
}

void CLeftTree::RefleshExecuteTree( )
{
	CShowTaskInfo *pShowTaskInfo = &g_DtMngView->m_ShowInfoList.m_ShowTaskInfo;
	UINT nGroupOid = g_CurSelDepart.nOid;
	HTREEITEM hItem = m_TaskTreeItem[Task_Runing];
	StBasTask *pTaskInfo = &pShowTaskInfo->m_CurTaskInfo;
	CTreeCtrl *pTree = pTaskInfo->stTaskBaseInfo.pTaskTree;

	DelTreeChildItem(pTree,hItem);
	InitTaskStatusProdTree(hItem,nGroupOid,Task_Runing);

}

void CLeftTree::RefleshFinishedTree( )
{
	CShowTaskInfo *pShowTaskInfo = &g_DtMngView->m_ShowInfoList.m_ShowTaskInfo;
	HTREEITEM hItem = m_TaskTreeItem[Task_Finish];
	UINT nGroupOid = g_CurSelDepart.nOid;
	StBasTask *pTaskInfo = &pShowTaskInfo->m_CurTaskInfo;
	CTreeCtrl *pTree = pTaskInfo->stTaskBaseInfo.pTaskTree;

	DelTreeChildItem(pTree,hItem);
	InitTaskStatusProdTree(hItem,nGroupOid,Task_Finish);

}

void CLeftTree::StopTaskMenu()
{
	CShowTaskInfo *pShowTaskInfo = &g_DtMngView->m_ShowInfoList.m_ShowTaskInfo;
	//pShowTaskInfo->StopTask();
}
void  CLeftTree::InitModeMenu1( )					//��ʼ���˵�1
{
	if(!m_ModeMenu1.GetSafeHmenu())
	{
		m_ModeMenu1.CreatePopupMenu();

		m_ModeMenu1.AppendMenu(MF_STRING, ID_L_ADDMODE_MENU,		"���ģ��");

	}
}
void  CLeftTree::InitModeMenu1_1( )					//��ʼ���˵�1
{
	if(!m_ModeMenu1_1.GetSafeHmenu())
	{
		m_ModeMenu1_1.CreatePopupMenu();

		m_ModeMenu1_1.AppendMenu(MF_STRING, ID_L_ADDMODE_MENU,	    "���ģ��");
		m_ModeMenu1_1.AppendMenu(MF_STRING, ID_L_PASTEMODE_MENU,	"ճ��ģ��");

	}
}

void  CLeftTree::InitModeMenu1_2()
{
	if(!m_ModeMenu1_2.GetSafeHmenu())
	{
		m_ModeMenu1_2.CreatePopupMenu();

		m_ModeMenu1_2.AppendMenu(MF_STRING, ID_L_ADDPRODUCT_MENU,	    "��Ӳ�Ʒ");
	}
}
void  CLeftTree::InitModeMenu2( )					//��ʼ���˵�1	
{
	if(!m_ModeMenu2.GetSafeHmenu())
	{
		m_ModeMenu2.CreatePopupMenu();

		m_ModeMenu2.AppendMenu(MF_STRING, ID_L_DELMODE_MENU,		"ɾ��ģ��");

		m_ModeMenu2.AppendMenu(MF_STRING, ID_L_COPYMODE_MENU,	    "����ģ��");

		//m_ModeMenu2.AppendMenu(MF_STRING, ID_L_PASTEMODE_MENU,	    "ճ��ģ��");


	}
}

void  CLeftTree::InitTaskMenu1( )					//��ʼ���˵�1
{
	if(!m_TaskMenu1.GetSafeHmenu())
	{
		m_TaskMenu1.CreatePopupMenu();

		m_TaskMenu1.AppendMenu(MF_STRING, ID_L_ADDTASK_MENU,	"�������");

	}
}

void  CLeftTree::InitTaskMenu2( )					//��ʼ���˵�1	
{
	if(!m_TaskMenu2.GetSafeHmenu())
	{
		m_TaskMenu2.CreatePopupMenu();

		m_TaskMenu2.AppendMenu(MF_STRING, ID_L_DELTASK_MENU,	"ɾ������");
		m_TaskMenu2.AppendMenu(MF_STRING, ID_L_SENDTASK_MENU,	"�·�����");
		m_TaskMenu2.AppendMenu(MF_STRING, ID_L_STOPTASK_MENU,	"��ֹ����");
	}
}

void CLeftTree::InitProdTree(HTREEITEM hDItem,UINT nGroupOid,int ShowType)
{
	int     i,nCount = 0;
	vector<StBasProduct > nArrayProduct;
	StBasProduct *pProductInfo;
	HTREEITEM hParent1;
	int nTreeID;
	if(ShowType == MODE_TREE_TYPE_DEPART)//ֻ��ģ��ֲ�Ʒ����//
	{
		if(!m_DMng.GetGroupPicNumProdInfo (nGroupOid,Product_normal,&nArrayProduct))
		{
			return;
		}
	}else
	{
		if(!m_DMng.GetGroupProductInfo (nGroupOid,&nArrayProduct))
		{
			return;
		}
	}
	
	nCount = nArrayProduct.size();

	//�����������ͬ��Ʒ���Ĳ�Ʒ����һ����ʾ///
	for(i = 0;i<nCount;i++)
	{
		pProductInfo = &nArrayProduct.at(i);
		int nPicNum = pProductInfo->nPicNumType;
		int nIcon1 = 2,nIcon2 = 2;
		if( nPicNum== Product_normal)
		{
			nIcon1 = nIcon2 = 2;
		}else
		{
			nIcon1 = nIcon2 = 11;
		}

		UINT nProductOid = pProductInfo->nOid;
		if(ShowType == MODE_TREE_TYPE_DEPART)
		{
			if(NumTwoToOne(nTreeID,MODE_TREE_TYPE_PRODCODE,nProductOid))
			{
				hParent1 = MyInsertTree(&m_GuideTree,pProductInfo->szProductNo,hDItem,nTreeID,nIcon1,nIcon2);
				InitModeTree(hParent1,nProductOid);
			}

		}
		if(ShowType == PROD_TREE_TYPE_DEPART)
		{
			if(NumTwoToOne(nTreeID,PROD_TREE_TYPE_PRODCODE,nProductOid))
			{
				hParent1 = MyInsertTree(&m_GuideTree,pProductInfo->szProductNo,hDItem,nTreeID,nIcon1,nIcon2);
			}
		}
		
	}
	
	nArrayProduct.clear();
	//m_GuideTree.Expand(hDItem,TVE_EXPAND);


}

void CLeftTree::InitTaskStatusProdTree(HTREEITEM hParent,UINT GroupOid,int nTaskStatus)
{
	//��ȡ��ǰ���ŵ����в�Ʒ��///
	int     i,nCount = 0;
	vector<StBasProduct > nArrayProduct;
	StBasProduct *pProductInfo;
	HTREEITEM hParent1;
	int nTreeID;
	if(m_DMng.GetGroupProductInfo (GroupOid,&nArrayProduct))
	{
		nCount = nArrayProduct.size();

		//�����������ͬ��Ʒ���Ĳ�Ʒ����һ����ʾ///
		for(i = 0;i<nCount;i++)
		{
			pProductInfo = &nArrayProduct.at(i);
			int nPicNum = pProductInfo->nPicNumType;
			int nIcon1 = 2,nIcon2 = 2;
			if( nPicNum== Product_normal)
			{
				nIcon1 = nIcon2 = 10;
			}else
			{
				nIcon1 = nIcon2 = 11;
			}

			if(NumTwoToOne(nTreeID,TASK_TREE_TYPE_PRODCODE,pProductInfo->nOid))
			{
				if(nTaskStatus == Task_All)
				{
					hParent1 = MyInsertTree(&m_GuideTree,pProductInfo->szProductNo,hParent,nTreeID,nIcon1, nIcon2);
					InitTaskTree(hParent1,pProductInfo->nOid);
				}else
				{
					if(m_DMng.IsStatusProdTaskExists(nTaskStatus,pProductInfo->nOid))
					{
						hParent1 = MyInsertTree(&m_GuideTree,pProductInfo->szProductNo,hParent,nTreeID,nIcon1, nIcon2);
						InitTaskStatusTree(hParent1,pProductInfo->nOid, nTaskStatus);
					}
				}
				

			}
		}
		nArrayProduct.clear();
	}
	//m_GuideTree.Expand(hParent,TVE_EXPAND);

}


void CLeftTree::InitTaskTree(HTREEITEM &hParent,UINT nProdOid)
{

	int     i,nCount = 0;
	vector<StBasTask *> nArrayTask;
	StBasTask *pTaskInfo;
	int nTreeID;
	if(m_DMng.GetProductTaskInfo (nProdOid,&nArrayTask))
	{
		nCount = nArrayTask.size();
		for(i = 0;i<nCount;i++)
		{
			pTaskInfo = nArrayTask.at(i);
			if(NumTwoToOne(nTreeID,TASK_TREE_TYPE_TASK,pTaskInfo->stTaskBaseInfo.nOid))
			{
				int nIcon = GetTaskIcon(pTaskInfo->stTaskBaseInfo.nTaskStatus);
				MyInsertTree(&m_GuideTree,pTaskInfo->stTaskBaseInfo.szTaskName,hParent,nTreeID,nIcon,nIcon);
			}

			delete nArrayTask.at(i);
		}
		nArrayTask.clear();

	}

	m_GuideTree.Expand(hParent,TVE_EXPAND);

}


void CLeftTree::InitTaskStatusTree(HTREEITEM &hParent,UINT nProdOid, int nTaskStatus)
{
	int     i,nCount = 0;
	vector<StBasTask *> nArrayTask;
	StBasTask *pTaskInfo;
	int nTreeID;
	if(m_DMng.GetProductTaskStatusInfo(nProdOid,nTaskStatus,&nArrayTask))
	{
		nCount = nArrayTask.size();
		for(i = 0;i<nCount;i++)
		{
			pTaskInfo = nArrayTask.at(i);
			if(NumTwoToOne(nTreeID,TASK_TREE_TYPE_TASK,pTaskInfo->stTaskBaseInfo.nOid))
			{
				int nIcon = GetTaskIcon(pTaskInfo->stTaskBaseInfo.nTaskStatus);
				MyInsertTree(&m_GuideTree,pTaskInfo->stTaskBaseInfo.szTaskName,hParent,nTreeID,nIcon,nIcon);
			}

			delete nArrayTask.at(i);
		}
		nArrayTask.clear();

	}

	m_GuideTree.Expand(hParent,TVE_EXPAND);
}
int  CLeftTree::GetProductTreeItemType(HTREEITEM hItem,StBasProduct *pProdInfo)
{
	if(hItem == NULL)
	{
		return 0;
	}
	CString strItem = m_GuideTree.GetItemText(hItem);
	if(strItem.IsEmpty())
		return 0;
	int nTreeID = m_GuideTree.GetItemData(hItem);

	int nType,nID;
	if(!NumOneToTwo(nTreeID,nType,nID))
	{
		return 0;
	}

	switch(nType)
	{
	case PROD_TREE_TYPE_DEPART:
		{
			pProdInfo->nGroupOid = nID;
			HTREEITEM hpItem = m_GuideTree.GetParentItem(hItem);
			GetProductTreeItemType(hpItem, pProdInfo);

		}
		break;
	case PROD_TREE_TYPE_PRODCODE:
		{
			pProdInfo->nOid = nID;
			HTREEITEM hpItem = m_GuideTree.GetParentItem(hItem);
			GetProductTreeItemType(hpItem, pProdInfo);
		}
		break;
	default:
		{

		}
		break;
	}
	return 1;
}
int  CLeftTree::GetModeTreeItemType(HTREEITEM hItem,StBasMode *pModeInfo)
{
	if(hItem == NULL)
	{
		return 0;
	}
	CString strItem = m_GuideTree.GetItemText(hItem);
	if(strItem.IsEmpty())
		return 0;
	int nTreeID = m_GuideTree.GetItemData(hItem);

	int nType,nID;
	if(!NumOneToTwo(nTreeID,nType,nID))
	{
		return 0;
	}
	switch(nType)
	{
	case MODE_TREE_TYPE_DEPART:
		{
			pModeInfo->nGroupOid = nID;
			HTREEITEM hpItem = m_GuideTree.GetParentItem(hItem);
			GetModeTreeItemType(hpItem, pModeInfo);

		}
		break;
	case MODE_TREE_TYPE_MODETYPE:
		{
			pModeInfo->nModeType = nID;
			HTREEITEM hpItem = m_GuideTree.GetParentItem(hItem);
			GetModeTreeItemType(hpItem, pModeInfo);

		}
		break;
	case MODE_TREE_TYPE_PRODCODE:
		{
			pModeInfo->stProductInfo.nOid = nID;
			HTREEITEM hpItem = m_GuideTree.GetParentItem(hItem);
			GetModeTreeItemType(hpItem, pModeInfo);

		}
		break;
	default:
		{

		}
		break;
	}
	return 1;
}
int  CLeftTree::GetTaskTreeItemType(HTREEITEM hItem,StBasTask *pTaskInfo)
{
	if(hItem == NULL)
	{
		return 0;
	}
	CString strItem = m_GuideTree.GetItemText(hItem);
	if(strItem.IsEmpty())
		return 0;
	int nTreeID = m_GuideTree.GetItemData(hItem);

	int nType,nID;
	if(!NumOneToTwo(nTreeID,nType,nID))
	{
		return 0;
	}

	switch(nType)
	{
	case TASK_TREE_TYPE_DEPART:
		{
			pTaskInfo->stProductInfo.nGroupOid = nID;
			HTREEITEM hpItem = m_GuideTree.GetParentItem(hItem);
			GetTaskTreeItemType(hpItem, pTaskInfo);

		}
		break;
	case TASK_TREE_TYPE_TASKTYPE:
		{
			HTREEITEM hpItem = m_GuideTree.GetParentItem(hItem);
			switch(nID)
			{
			case Task_Init:
				{
					pTaskInfo->stTaskBaseInfo.nTaskStatus = Task_Init;
				}
				break;
			case Task_OK:
				{
					pTaskInfo->stTaskBaseInfo.nTaskStatus = Task_OK;
				}
				break;
			case Task_Runing:
				{
					pTaskInfo->stTaskBaseInfo.nTaskStatus = Task_Runing;
				}
				break;
			case Task_Finish:
				{
					pTaskInfo->stTaskBaseInfo.nTaskStatus = Task_Finish;
				}
				break;
			case Task_All:
				{
					pTaskInfo->stTaskBaseInfo.nTaskStatus = Task_All;
				}
				break;
			}
			GetTaskTreeItemType(hpItem, pTaskInfo);

		}
		break;
	case TASK_TREE_TYPE_PRODCODE:
		{
			pTaskInfo->stProductInfo.nOid = nID;
			HTREEITEM hpItem = m_GuideTree.GetParentItem(hItem);
			GetTaskTreeItemType(hpItem, pTaskInfo);

		}
		break;
	default:
		{

		}
		break;
	}
	return 1;
}
int  CLeftTree::GetResultTreeItemType(HTREEITEM hItem,StTstResultBase *pTstResultInfo)
{
	if(hItem == NULL)
	{
		return 0;
	}
	CString strItem = m_GuideTree.GetItemText(hItem);
	if(strItem.IsEmpty())
		return 0;
	int nTreeID = m_GuideTree.GetItemData(hItem);

	int nType,nID;
	if(!NumOneToTwo(nTreeID,nType,nID))
	{
		return 0;
	}

	switch(nType)
	{
	case RESULT_TREE_TYPE_DEPART:
		{
			pTstResultInfo->nGroupOid = nID;
			HTREEITEM hpItem = m_GuideTree.GetParentItem(hItem);
			GetResultTreeItemType(hpItem, pTstResultInfo);

		}
		break;
	case RESULT_TREE_TYPE_TYPE:
		{
			pTstResultInfo->nResultType = nID;
			HTREEITEM hpItem = m_GuideTree.GetParentItem(hItem);
			
			GetResultTreeItemType(hpItem, pTstResultInfo);

		}
		break;
	default:
		{

		}
		break;
	}
	return 1;
}
int  CLeftTree::GetResultTreeItemTypeNew(HTREEITEM hItem,StBasTask *pResultSearchInfo)
{
	if(hItem == NULL)
	{
		return 0;
	}
	CString strItem = m_GuideTree.GetItemText(hItem);
	if(strItem.IsEmpty())
		return 0;
	int nTreeID = m_GuideTree.GetItemData(hItem);

	int nType,nID;
	if(!NumOneToTwo(nTreeID,nType,nID))
	{
		return 0;
	}

	switch(nType)
	{
	case RESULT_TREE_TYPE_DEPART:
		{
			pResultSearchInfo->stTaskBaseInfo.nGroupOid = nID;
			HTREEITEM hpItem = m_GuideTree.GetParentItem(hItem);
			GetResultTreeItemTypeNew(hpItem, pResultSearchInfo);

		}
		break;
	case RESULT_TREE_TYPE_TYPE:
		{
			pResultSearchInfo->stTaskBaseInfo.nResultType = nID;
			HTREEITEM hpItem = m_GuideTree.GetParentItem(hItem);

			GetResultTreeItemTypeNew(hpItem, pResultSearchInfo);

		}
		break;
	default:
		{

		}
		break;
	}
	return 1;
}
void  CLeftTree::InitModeTreeFromModeType(HTREEITEM hParent,UINT GroupOid,int nModeType)
{
	int     i,nCount = 0;
	vector<StBasMode> stBasModeArry;
	HTREEITEM hParent1;
	int nTreeID;
	if(m_DMng.GetGroupModeTypeData (GroupOid,nModeType,&stBasModeArry))
	{
		nCount = stBasModeArry.size();

		//�����������ͬ��Ʒ���Ĳ�Ʒ����һ����ʾ///
		for(i = 0;i<nCount;i++)
		{
			if(NumTwoToOne(nTreeID,MODE_TREE_TYPE_MODE,stBasModeArry.at(i).nOid))
			{
				hParent1 = MyInsertTree(&m_GuideTree,stBasModeArry.at(i).szModeName,hParent,nTreeID,3,3);
			}

		}
		stBasModeArry.clear();
	}
	m_GuideTree.Expand(hParent,TVE_EXPAND);
}

void CLeftTree::InitModeTree(HTREEITEM hParent,UINT nProdOid)
{

	int     i,nCount = 0;
	vector<StBasMode> StBasModeArray;
	int nTreeID;
	if(m_DMng.GetProdModeData (nProdOid,&StBasModeArray))
	{
		nCount = StBasModeArray.size();

		//�����������ͬ��Ʒ���Ĳ�Ʒ����һ����ʾ///
		for(i = 0;i<nCount;i++)
		{
			if(NumTwoToOne(nTreeID,MODE_TREE_TYPE_MODE,StBasModeArray.at(i).nOid))
			{
				MyInsertTree(&m_GuideTree,StBasModeArray.at(i).szModeName,hParent,nTreeID,3,3);
			}

		}
		StBasModeArray.clear();
	}
	m_GuideTree.Expand(hParent,TVE_EXPAND);

}
void CLeftTree::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	CRect Rect ;
	GetClientRect(&Rect) ;
	if(m_GuideTree.GetSafeHwnd())
		m_GuideTree.MoveWindow(&Rect);
	// TODO: �ڴ˴������Ϣ����������
}
void CLeftTree::InitGuideTree()
{
	//���ݵ�ǰѡ�еĲ��Ż�Ĭ�ϵ�¼�Ĳ��ų�ʼ���ṹ��//
	HTREEITEM hParent1,hParent2;
	m_GuideTree.DeleteAllItems();

	int nTreeID;
	int nNum = 0;
	CString strText,strGroupName;
	
	strGroupName = g_CurSelDepart.szGroupName;
	UINT nGroupOid = g_CurSelDepart.nOid;

	//nNum = m_DMng.GetProdCountGroup(nGroupOid);
	//strText.Format(_T("��Ʒ��Ϣ(%d)"),nNum);
	strText.Format(_T("��Ʒ��Ϣ"));
	if(NumTwoToOne(nTreeID,PROD_TREE_TYPE_DEPART,nGroupOid))
	{
		hParent1 = MyInsertTree(&m_GuideTree,strText,TVI_ROOT,nTreeID,0,0);

		//InitProdTree(hParent1,nGroupOid,PROD_TREE_TYPE_DEPART);

		////��Ʒ����: 0.��ͨ��Ʒ,1.���²�Ʒ
		//if(NumTwoToOne(nTreeID,PROD_TREE_TYPE_PRODTYPE,PROD_TREE_TYPE_General))
		//{
		//	hParent2 = MyInsertTree(&m_GuideTree,g_ProdPicNumType[PROD_TREE_TYPE_General],hParent1,nTreeID,1,1);
		//	InitProdTree(hParent2,g_CurSelDepart.nOid,ID_PRODMNG_IN);
		//}

		//if(NumTwoToOne(nTreeID,PROD_TREE_TYPE_PRODTYPE,PROD_TREE_TYPE_Line))
		//{
		//	hParent2 = MyInsertTree(&m_GuideTree,g_ProdPicNumType[PROD_TREE_TYPE_Line],hParent1,nTreeID,1,1);
		//	//InitProdTree(hParent2,g_CurSelDepart.nOid,ID_PRODMNG_IN);
		//}



		m_GuideTree.Expand(hParent1,TVE_EXPAND);
	}

	//nNum = m_DMng.GetModeCountGroup(nGroupOid);
	//strText.Format(_T("�����¼ģ��(%d)"), nNum);
	strText.Format(_T("�����¼ģ��"));
	if(NumTwoToOne(nTreeID,MODE_TREE_TYPE_DEPART,nGroupOid))
	{
		hParent1 = MyInsertTree(&m_GuideTree,strText,TVI_ROOT,nTreeID,0,0);


		//ģ������: 0.��Ʒͨ��,1.��Ʒר��,2.����ר�� 3.δ����,

		nNum = m_DMng.GetModeCountGroupType(nGroupOid,Mode_Currency);
		strText.Format(_T("%s"), g_ModeType[Mode_Currency]);
		if(NumTwoToOne(nTreeID,MODE_TREE_TYPE_MODETYPE,Mode_Currency))
		{
			hParent2 = MyInsertTree(&m_GuideTree,strText,hParent1,nTreeID,1,1);
			InitModeTreeFromModeType(hParent2,nGroupOid,Mode_Currency);
		}

		nNum = m_DMng.GetModeCountGroupType(nGroupOid,Mode_Dedicated);
		strText.Format(_T("%s"), g_ModeType[Mode_Dedicated]);
		if(NumTwoToOne(nTreeID,MODE_TREE_TYPE_MODETYPE,Mode_Dedicated))
		{
			hParent2 = MyInsertTree(&m_GuideTree,strText,hParent1,nTreeID,1,1);
			InitProdTree(hParent2,nGroupOid,MODE_TREE_TYPE_DEPART);
		}

		nNum = m_DMng.GetModeCountGroupType(nGroupOid,Mode_LineDed);
		strText.Format(_T("%s"), g_ModeType[Mode_LineDed]);
		if(NumTwoToOne(nTreeID,MODE_TREE_TYPE_MODETYPE,Mode_LineDed))
		{
			hParent2 = MyInsertTree(&m_GuideTree,strText,hParent1,nTreeID,1,1);
			InitModeTreeFromModeType(hParent2,nGroupOid,Mode_LineDed);
		}

		nNum = m_DMng.GetModeCountGroupType(nGroupOid,Mode_NotUse);
		strText.Format(_T("%s"), g_ModeType[Mode_NotUse]);
		if(NumTwoToOne(nTreeID,MODE_TREE_TYPE_MODETYPE,Mode_NotUse))
		{
			hParent2 = MyInsertTree(&m_GuideTree,strText,hParent1,nTreeID,1,1);
			InitModeTreeFromModeType(hParent2,nGroupOid,Mode_NotUse);
		}

		m_GuideTree.Expand(hParent1,TVE_EXPAND);
	}

	nNum = m_DMng.GetTaskCountGroup(nGroupOid);
	//strText.Format(_T("��������(%d)"), nNum);
	strText.Format(_T("��������"));
	if(NumTwoToOne(nTreeID,TASK_TREE_TYPE_DEPART,nGroupOid))
	{

		hParent1 = MyInsertTree(&m_GuideTree,strText,TVI_ROOT,nTreeID,0,0);
		//�������:   ���������ɹ���ִ���С�����ɡ�����ֹ//
		//

		nNum = m_DMng.GetTaskCountGroupStatus(nGroupOid,Task_Init);
		//strText.Format(_T("%s(%d)"), g_TaskState[Task_Init], nNum);
		strText.Format(_T("%s"), g_TaskState[Task_Init]);
		if(NumTwoToOne(nTreeID,TASK_TREE_TYPE_TASKTYPE,Task_Init))
		{
			m_TaskTreeItem[Task_Init]=hParent2 = MyInsertTree(&m_GuideTree,strText,hParent1,nTreeID,1,1);
			//InitTaskStatusProdTree(m_TaskTreeItem[Task_Init],nGroupOid,Task_Init);
		}

		nNum = m_DMng.GetTaskCountGroupStatus(nGroupOid,Task_OK);
		//strText.Format(_T("%s(%d)"), g_TaskState[Task_OK], nNum);
		strText.Format(_T("%s"), g_TaskState[Task_OK]);
		if(NumTwoToOne(nTreeID,TASK_TREE_TYPE_TASKTYPE,Task_OK))
		{
			m_TaskTreeItem[Task_OK]=hParent2 = MyInsertTree(&m_GuideTree,strText,hParent1,nTreeID,1,1);
			//InitTaskStatusProdTree(m_TaskTreeItem[Task_OK],nGroupOid,Task_OK);
		}


		nNum = m_DMng.GetTaskCountGroupStatus(nGroupOid,Task_Runing);
		//strText.Format(_T("%s(%d)"), g_TaskState[Task_Runing], nNum);
		strText.Format(_T("%s"), g_TaskState[Task_Runing]);
		if(NumTwoToOne(nTreeID,TASK_TREE_TYPE_TASKTYPE,Task_Runing))
		{
			m_TaskTreeItem[Task_Runing]=hParent2 = MyInsertTree(&m_GuideTree,strText,hParent1,nTreeID,1,1);
			//InitTaskStatusProdTree(m_TaskTreeItem[Task_Runing],nGroupOid,Task_Runing);
		}

		nNum = m_DMng.GetTaskCountGroupStatus(nGroupOid,Task_Finish);
		//strText.Format(_T("%s(%d)"), g_TaskState[Task_Finish], nNum);
		strText.Format(_T("%s"), g_TaskState[Task_Finish]);
		if(NumTwoToOne(nTreeID,TASK_TREE_TYPE_TASKTYPE,Task_Finish))
		{
			m_TaskTreeItem[Task_Finish]=hParent2 = MyInsertTree(&m_GuideTree,strText,hParent1,nTreeID,1,1);
			//InitTaskStatusProdTree(m_TaskTreeItem[Task_Finish],nGroupOid,Task_Finish);

		}

		nNum = m_DMng.GetTaskCountGroup(nGroupOid);
		//strText.Format(_T("%s(%d)"), g_TaskState[Task_All], nNum);
		strText.Format(_T("%s"), g_TaskState[Task_All]);
		if(NumTwoToOne(nTreeID,TASK_TREE_TYPE_TASKTYPE,Task_All))
		{
			m_TaskTreeItem[Task_All]=hParent2 = MyInsertTree(&m_GuideTree,strText,hParent1,nTreeID,1,1);
			//InitTaskStatusProdTree(m_TaskTreeItem[Task_All],nGroupOid,Task_All);
		}

		m_GuideTree.Expand(hParent1,TVE_EXPAND);
	}

	strText.Format(_T("���Խ��"));
	if(NumTwoToOne(nTreeID,RESULT_TREE_TYPE_DEPART,nGroupOid))
	{
		hParent1 = MyInsertTree(&m_GuideTree,strText,TVI_ROOT,nTreeID,0,0);
		//������ݲ�ѯ����:   �����ѯ��������ݲ�ѯ//
		//Result_Task, Result_Atta

		if(NumTwoToOne(nTreeID,RESULT_TREE_TYPE_TYPE,Task_DarkSearch))
		{
			hParent2 = MyInsertTree(&m_GuideTree,g_ResultType[Result_Task],hParent1,nTreeID,1,1);
		}

		if(NumTwoToOne(nTreeID,RESULT_TREE_TYPE_TYPE,Result_Search))
		{
			hParent2 = MyInsertTree(&m_GuideTree,g_ResultType[Result_Atta],hParent1,nTreeID,1,1);
		}

		m_GuideTree.Expand(hParent1,TVE_EXPAND);
	}
	/*strText.Format(_T("��Ʒ��ʷ��ֵ"));
	if(NumTwoToOne(nTreeID,HIS_TRRE_ITEM_TYPE_DEPART,nGroupOid))
	{
		hParent1 = MyInsertTree(&m_GuideTree,strText,TVI_ROOT,nTreeID,0,0);
		m_GuideTree.Expand(hParent1,TVE_EXPAND);
	}
	strText.Format(_T("��Ʒ֤����"));
	if(NumTwoToOne(nTreeID,REPORT_TRRE_ITEM_TYPE_DEPART,nGroupOid))
	{
		hParent1 = MyInsertTree(&m_GuideTree,strText,TVI_ROOT,nTreeID,0,0);
		m_GuideTree.Expand(hParent1,TVE_EXPAND);
	}*/
	m_GuideTree.SelectItem(NULL);

	
	
}

//ɾ��ĳ���ڵ��µ������ӽڵ�///
void CLeftTree::DelTreeChildItem(CTreeCtrl *pTree,HTREEITEM hItem)
{
	if(!hItem)
		return;
	HTREEITEM hChildItem = NULL;
	while((hChildItem = pTree->GetChildItem(hItem)) != NULL)
	{
		pTree->DeleteItem(hChildItem);
	}
}
void CLeftTree::OnNMClickLeftTree(NMHDR *pNMHDR, LRESULT *pResult)
{

	if(g_DtMngView->m_uMenuSelRow != 0 || g_DtMngView->m_uMenuSelCol != 0)
	{
		g_DtMngView->ChangeViewMode(0,0);
	}
	
	TVHITTESTINFO	tvhtif;
	GetCursorPos(&tvhtif.pt);
	m_GuideTree.ScreenToClient(&tvhtif.pt);
	m_GuideTree.HitTest(&tvhtif);

	int nUserType = g_LoginUsrInfo.nUserType;
	if(tvhtif.flags & TVHT_ONITEM)
	{
		//int nIcon1, nIcon2;
		//m_DepartMngTree->GetItemImage(tvhtif.hItem, nIcon1, nIcon2);
		m_GuideTree.SelectItem(tvhtif.hItem);
		CString strItem = m_GuideTree.GetItemText(tvhtif.hItem);
		if(strItem.IsEmpty())
			return;
		

		//�鿴��Ʒ�������Ϣ//
		int nTreeID = m_GuideTree.GetItemData(tvhtif.hItem);

		int nType,nID;
		if(!NumOneToTwo(nTreeID,nType,nID))
		{
			return;
		}

		switch(nType)
		{
		case PROD_TREE_TYPE_DEPART     :
			{
				//StBasProduct *pProductSearchInfo = g_pShowInfoList->m_ProductSearch.m_ProductSearch;
				//GetProductTreeItemType(tvhtif.hItem,pProductSearchInfo);
				g_DtMngView->m_ShowInfoList.m_ProductSearch.OnBnClickedSearchBtn();
			}
			break;
		case MODE_TREE_TYPE_DEPART:
			{
				StBasMode *pModeInfo = &g_DtMngView->m_ShowInfoList.m_ShowModeInfo.m_CurModeInfo;
				pModeInfo->Release();
				memset(pModeInfo,0,sizeof(StBasMode));

				pModeInfo->TreeItemType = MODE_TREE_TYPE_DEPART;
				pModeInfo->hItem = tvhtif.hItem;
				pModeInfo->nOid = nID;
				pModeInfo->pModeTree = &m_GuideTree;
				GetModeTreeItemType(tvhtif.hItem,pModeInfo);

				//���ò�ѯ������ �����²���������ʼΪ��  ���е�//
				StBasMode *pModeSearchInfo =  &g_DtMngView->m_ShowInfoList.m_ModeSearch.m_ModeSearchInfo;
				pModeSearchInfo->Release();
				memset(pModeSearchInfo, 0, sizeof(StBasMode));


				pModeSearchInfo->bModeCurrency = Sel_Check;
				pModeSearchInfo->bModeDedicated = Sel_Check;
				pModeSearchInfo->bModeLineDed = Sel_Check;
				pModeSearchInfo->bModeNotUse = Sel_Check;


			/*	pModeSearchInfo->bModeRowChange = Sel_Check;
				pModeSearchInfo->bModeRowNoChange = Sel_Check;
				pModeSearchInfo->bUnInitTabStr = Sel_Check;
				pModeSearchInfo->bInitedTabSrt = Sel_Check;*/

				pModeSearchInfo->nModeRowVar = ModeRow_All;
				pModeSearchInfo->nInitTabSrt = ModeTab_All;
	
				
				g_DtMngView->m_ShowInfoList.m_ModeSearch.DisplaySearchInfo();//��ʼ��Ϣ//
				g_DtMngView->m_ShowInfoList.m_ModeSearch.OnBnClickedSearchBtn();//��ѯ//
				
			}
			break;
		case MODE_TREE_TYPE_MODETYPE:
			{
				StBasMode *pModeInfo = &g_DtMngView->m_ShowInfoList.m_ShowModeInfo.m_CurModeInfo;
				pModeInfo->Release();
				memset(pModeInfo,0,sizeof(StBasMode));

				pModeInfo->TreeItemType = MODE_TREE_TYPE_MODETYPE;
				pModeInfo->hItem = tvhtif.hItem;
				pModeInfo->nOid = nID;
				pModeInfo->pModeTree = &m_GuideTree;
				GetModeTreeItemType(tvhtif.hItem,pModeInfo);


				//���ò�ѯ������ �����²���������ʼΪ��  ���е�//
				StBasMode *pModeSearchInfo =  &g_DtMngView->m_ShowInfoList.m_ModeSearch.m_ModeSearchInfo;
				pModeSearchInfo->Release();
				memset(pModeSearchInfo, 0, sizeof(StBasMode));


				switch(nID)
				{
				case Mode_Currency:
					{
						pModeSearchInfo->bModeCurrency = Sel_Check;
						pModeSearchInfo->bModeDedicated = UnSel_Check;
						pModeSearchInfo->bModeLineDed = UnSel_Check;
						pModeSearchInfo->bModeNotUse = UnSel_Check;
					}
					break;
				case Mode_Dedicated:
					{
						pModeSearchInfo->bModeCurrency = UnSel_Check;
						pModeSearchInfo->bModeDedicated = Sel_Check;
						pModeSearchInfo->bModeLineDed = UnSel_Check;
						pModeSearchInfo->bModeNotUse = UnSel_Check;
					}
					break;
				case Mode_LineDed:
					{
						pModeSearchInfo->bModeCurrency = UnSel_Check;
						pModeSearchInfo->bModeDedicated = UnSel_Check;
						pModeSearchInfo->bModeLineDed = Sel_Check;
						pModeSearchInfo->bModeNotUse = UnSel_Check;
					}
					break;
				case Mode_NotUse:
					{
						pModeSearchInfo->bModeCurrency = UnSel_Check;
						pModeSearchInfo->bModeDedicated = UnSel_Check;
						pModeSearchInfo->bModeLineDed = UnSel_Check;
						pModeSearchInfo->bModeNotUse = Sel_Check;
					}
					break;
				}
				
				pModeSearchInfo->nModeRowVar = ModeRow_All;
				pModeSearchInfo->nInitTabSrt = ModeTab_All;

				/*pModeSearchInfo->bModeRowChange = Sel_Check;
				pModeSearchInfo->bModeRowNoChange = Sel_Check;
				pModeSearchInfo->bUnInitTabStr = Sel_Check;
				pModeSearchInfo->bInitedTabSrt = Sel_Check;*/

				
				g_DtMngView->m_ShowInfoList.m_ModeSearch.DisplaySearchInfo();//��ʼ��Ϣ//
				g_DtMngView->m_ShowInfoList.m_ModeSearch.OnBnClickedSearchBtn();//��ѯ//
				

			}
			break;
		case MODE_TREE_TYPE_PRODCODE:
			{
				StBasMode *pModeInfo = &g_DtMngView->m_ShowInfoList.m_ShowModeInfo.m_CurModeInfo;
				pModeInfo->Release();
				memset(pModeInfo,0,sizeof(StBasMode));

				pModeInfo->TreeItemType = MODE_TREE_TYPE_PRODCODE;
				pModeInfo->hItem = tvhtif.hItem;
				pModeInfo->nOid = nID;
				pModeInfo->pModeTree = &m_GuideTree;
				GetModeTreeItemType(tvhtif.hItem,pModeInfo);
				//���ò�ѯ������ �����²���������ʼΪ��  ���е�//
				StBasMode *pModeSearchInfo =  &g_DtMngView->m_ShowInfoList.m_ModeSearch.m_ModeSearchInfo;
				pModeSearchInfo->Release();
				memset(pModeSearchInfo, 0, sizeof(StBasMode));

				pModeSearchInfo->stProductInfo.nOid = pModeInfo->stProductInfo.nOid;
				memset(pModeSearchInfo->stProductInfo.szProductNo, 0, sizeof(pModeSearchInfo->stProductInfo.szProductNo));
				strcpy(pModeSearchInfo->stProductInfo.szProductNo, strItem);

				pModeSearchInfo->bModeCurrency = UnSel_Check;
				pModeSearchInfo->bModeDedicated = Sel_Check;
				pModeSearchInfo->bModeLineDed = UnSel_Check;
				pModeSearchInfo->bModeNotUse = UnSel_Check;

				pModeSearchInfo->nModeRowVar = ModeRow_All;
				pModeSearchInfo->nInitTabSrt = ModeTab_All;

				
				g_DtMngView->m_ShowInfoList.m_ModeSearch.DisplaySearchInfo();//��ʼ��Ϣ//
				g_DtMngView->m_ShowInfoList.m_ModeSearch.OnBnClickedSearchBtn();//��ѯ//
			}
			break;

		case MODE_TREE_TYPE_MODE:
			{
				StBasMode *pModeInfo = &g_DtMngView->m_ShowInfoList.m_ShowModeInfo.m_CurModeInfo;
				CShowModeInfo *pShowModeInfo = &g_DtMngView->m_ShowInfoList.m_ShowModeInfo;
				pModeInfo->Release();
				memset(pModeInfo,0,sizeof(StBasMode));

				pModeInfo->TreeItemType = MODE_TREE_TYPE_MODE;
				pModeInfo->hItem = tvhtif.hItem;
				pModeInfo->nOid = nID;
				pModeInfo->pModeTree = &m_GuideTree;
				pShowModeInfo->m_ShowType = Tree_Modify_Mode;
				//Ȩ������//
				if(nUserType != user_normal)
				{
					pShowModeInfo->GetDlgItem(IDOK)->ShowWindow(SW_SHOW);
					pShowModeInfo->GetDlgItem(IDOK)->SetWindowText(_T("����"));
				}else
				{
					pShowModeInfo->GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
				}
				pShowModeInfo->GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);


				m_DMng.GetModeDataOid(nID,pModeInfo);
				pShowModeInfo->DisPalyModeInfo();
				g_DtMngView->m_ShowInfoList.DisplayOneModeDescInfo();
			}
			break;

			

		case TASK_TREE_TYPE_DEPART:
			{
				StBasTask *pTaskInfo = &g_DtMngView->m_ShowInfoList.m_ShowTaskInfo.m_CurTaskInfo;
				pTaskInfo->Release();
				pTaskInfo->stTaskBaseInfo.nOid = nID;
				pTaskInfo->stTaskBaseInfo.TreeItemType = TASK_TREE_TYPE_DEPART;
				pTaskInfo->stTaskBaseInfo.hItem = tvhtif.hItem;
				pTaskInfo->stTaskBaseInfo.pTaskTree = &m_GuideTree;

				GetTaskTreeItemType(tvhtif.hItem,pTaskInfo);

				////���ò�ѯ������ �����²������е�����//
				StBasTask *pTaskSearchInfo =  &g_DtMngView->m_ShowInfoList.m_TaskSearch.m_TaskSearchInfo;
				pTaskSearchInfo->Release();

				pTaskSearchInfo->stTaskBaseInfo.nArmyTest = Army_All;//����ȫ��

				pTaskSearchInfo->stTaskBaseInfo.nTaskStatus = Task_All;//1.����״̬

				pTaskSearchInfo->stTaskBaseInfo.bTaskInit = Sel_Check;//2.������
				pTaskSearchInfo->stTaskBaseInfo.bTaskOk = Sel_Check;   //3.���ɹ�
				pTaskSearchInfo->stTaskBaseInfo.bTaskRuning = Sel_Check; //4.ִ����
				pTaskSearchInfo->stTaskBaseInfo.bTaskFinish = Sel_Check;  //5.�����
				pTaskSearchInfo->stTaskBaseInfo.bTaskStop = Sel_Check;    //6.����ֹ

				pTaskSearchInfo->stTaskBaseInfo.bTaskTest = Sel_Check;//1.����
				pTaskSearchInfo->stTaskBaseInfo.bTaskReTest = Sel_Check;   //2.����
				pTaskSearchInfo->stTaskBaseInfo.bTaskHelpReTest = Sel_Check; //3.��Э����

				
				g_DtMngView->m_ShowInfoList.m_TaskSearch.DisplaySearchInfo();//��ʼ��Ϣ//
				g_DtMngView->m_ShowInfoList.m_TaskSearch.OnBnClickedTaskSearchBtn();//��ѯ////
			}
			break;

		case TASK_TREE_TYPE_TASKTYPE:
			{
				StBasTask *pTaskInfo = &g_DtMngView->m_ShowInfoList.m_ShowTaskInfo.m_CurTaskInfo;
				pTaskInfo->Release();
				pTaskInfo->stTaskBaseInfo.nOid = nID;
				pTaskInfo->stTaskBaseInfo.TreeItemType = TASK_TREE_TYPE_TASKTYPE;
				pTaskInfo->stTaskBaseInfo.hItem = tvhtif.hItem;
				pTaskInfo->stTaskBaseInfo.pTaskTree = &m_GuideTree;


				GetTaskTreeItemType(tvhtif.hItem,pTaskInfo);
				////���ò�ѯ������ �����²������е�����//
				StBasTask *pTaskSearchInfo =  &g_DtMngView->m_ShowInfoList.m_TaskSearch.m_TaskSearchInfo;
				pTaskSearchInfo->Release();

				pTaskSearchInfo->stTaskBaseInfo.nTaskStatus = nID;//1.����״̬

				switch(nID)
				{
				case Task_Init:
					{
						pTaskSearchInfo->stTaskBaseInfo.bTaskInit = Sel_Check;//2.������
						
					}
					break;
				case Task_OK:
					{
						pTaskSearchInfo->stTaskBaseInfo.bTaskOk = Sel_Check;   //3.���ɹ�
						
					}
					break;
				case Task_Finish:
					{
						pTaskSearchInfo->stTaskBaseInfo.bTaskFinish = Sel_Check;  //5.�����
						
					}
					break;
				case Task_Runing:
					{
						pTaskSearchInfo->stTaskBaseInfo.bTaskRuning = Sel_Check; //4.ִ����
						
					}
					break;
				case Task_All:
					{

						pTaskSearchInfo->stTaskBaseInfo.bTaskInit = Sel_Check;//2.������
						pTaskSearchInfo->stTaskBaseInfo.bTaskOk = Sel_Check;   //3.���ɹ�
						pTaskSearchInfo->stTaskBaseInfo.bTaskRuning = Sel_Check; //4.ִ����
						pTaskSearchInfo->stTaskBaseInfo.bTaskFinish = Sel_Check;  //5.�����
						pTaskSearchInfo->stTaskBaseInfo.bTaskStop = Sel_Check;    //6.����ֹ
					}
				}

				pTaskSearchInfo->stTaskBaseInfo.nArmyTest = Army_All;//����ȫ��
				pTaskSearchInfo->stTaskBaseInfo.bTaskTest = Sel_Check;//1.����
				pTaskSearchInfo->stTaskBaseInfo.bTaskReTest = Sel_Check;   //2.����
				pTaskSearchInfo->stTaskBaseInfo.bTaskHelpReTest = Sel_Check; //3.��Э����

				//pTaskSearchInfo->stTaskBaseInfo.bTaskInit = Sel_Check;//2.������
				//pTaskSearchInfo->stTaskBaseInfo.bTaskOk = Sel_Check;   //3.���ɹ�
				//pTaskSearchInfo->stTaskBaseInfo.bTaskRuning = Sel_Check; //4.ִ����
				//pTaskSearchInfo->stTaskBaseInfo.bTaskFinish = Sel_Check;  //5.�����
				//pTaskSearchInfo->stTaskBaseInfo.bTaskStop = Sel_Check;    //6.����ֹ

				g_DtMngView->m_ShowInfoList.m_TaskSearch.DisplaySearchInfo();//��ʼ��Ϣ//
				g_DtMngView->m_ShowInfoList.m_TaskSearch.OnBnClickedTaskSearchBtn();//��ѯ////
			}
			break;
			

		case TASK_TREE_TYPE_PRODCODE:
			{
				StBasTask *pTaskInfo = &g_DtMngView->m_ShowInfoList.m_ShowTaskInfo.m_CurTaskInfo;
				pTaskInfo->Release();
				pTaskInfo->stTaskBaseInfo.nOid = nID;
				pTaskInfo->stTaskBaseInfo.TreeItemType = TASK_TREE_TYPE_PRODCODE;
				pTaskInfo->stTaskBaseInfo.hItem = tvhtif.hItem;
				pTaskInfo->stTaskBaseInfo.pTaskTree = &m_GuideTree;


				GetTaskTreeItemType(tvhtif.hItem,pTaskInfo);
				////���ò�ѯ������ �����²������е�����//
				StBasTask *pTaskSearchInfo =  &g_DtMngView->m_ShowInfoList.m_TaskSearch.m_TaskSearchInfo;
				pTaskSearchInfo->Release();

				pTaskSearchInfo->stTaskBaseInfo.nTaskStatus = pTaskInfo->stTaskBaseInfo.nTaskStatus;//1.����״̬
				strcpy(pTaskSearchInfo->stProductInfo.szProductNo, strItem); 

				//pTaskSearchInfo->stTaskBaseInfo.bTaskInit = Sel_Check;//2.������
				//pTaskSearchInfo->stTaskBaseInfo.bTaskOk = Sel_Check;   //3.���ɹ�
				//pTaskSearchInfo->stTaskBaseInfo.bTaskRuning = Sel_Check; //4.ִ����
				//pTaskSearchInfo->stTaskBaseInfo.bTaskFinish = Sel_Check;  //5.�����
				//pTaskSearchInfo->stTaskBaseInfo.bTaskStop = Sel_Check;    //6.����ֹ

				pTaskSearchInfo->stTaskBaseInfo.nArmyTest = Army_All;//����ȫ��
				pTaskSearchInfo->stTaskBaseInfo.bTaskTest = Sel_Check;//1.����
				pTaskSearchInfo->stTaskBaseInfo.bTaskReTest = Sel_Check;   //2.����
				pTaskSearchInfo->stTaskBaseInfo.bTaskHelpReTest = Sel_Check; //3.��Э����


				g_DtMngView->m_ShowInfoList.m_TaskSearch.DisplaySearchInfo();//��ʼ��Ϣ//
				g_DtMngView->m_ShowInfoList.m_TaskSearch.OnBnClickedTaskSearchBtn();//��ѯ////
			}
			break;

		case TASK_TREE_TYPE_TASK:
			{
				StBasTask *pTaskInfo = &g_DtMngView->m_ShowInfoList.m_ShowTaskInfo.m_CurTaskInfo;
				CShowTaskInfo *pShowTaskInfo = &g_DtMngView->m_ShowInfoList.m_ShowTaskInfo;
				pTaskInfo->Release();
				pTaskInfo->stTaskBaseInfo.nOid = nID;
				pTaskInfo->stTaskBaseInfo.TreeItemType = TASK_TREE_TYPE_TASK;
				pTaskInfo->stTaskBaseInfo.hItem = tvhtif.hItem;
				pTaskInfo->stTaskBaseInfo.pTaskTree = &m_GuideTree;

				////
				pShowTaskInfo->m_ShowType = Tree_Modify_Task;
				//1.��Ʒ���Ų���ѡ
				((CEdit *)pShowTaskInfo->GetDlgItem(IDC_PRODUCTNO_EDT))->SetReadOnly(TRUE);
				((CEdit *)pShowTaskInfo->GetDlgItem(IDC_PRODNAME_EDT))->SetReadOnly(TRUE);
				(pShowTaskInfo->GetDlgItem(IDC_SEL_PRODUCTNO_BTN))->EnableWindow(FALSE);

				
				if(m_DMng.GetTaskDataOid(nID,pTaskInfo))
				{
					if(m_DMng.GetProdDataOid(pTaskInfo->stProductInfo.nOid,
						&pTaskInfo->stProductInfo))
					{
						pShowTaskInfo->DisplayTaskInfo();
						g_DtMngView->m_ShowInfoList.DisplayOneTaskDescInfo();
					}

				}
				
			}
			break;

		
		case RESULT_TREE_TYPE_DEPART:
			{
				g_DtMngView->ChangeViewMode(6,1);

				/*StTstResultBase* pTstResult = &g_DtMngView->m_ResultSearch.m_TstResultBase;
				memset(pTstResult,0,sizeof(StTstResultBase));
				pTstResult->TreeItemType = RESULT_TREE_TYPE_DEPART;
				pTstResult->hItem = tvhtif.hItem;
				pTstResult->pResultTree = &m_GuideTree;
				GetResultTreeItemType(tvhtif.hItem,pTstResult);*/

				//�°�Ľ����ѯ//
				StBasTask* pResultSearchInfo = &g_DtMngView->m_ResultSearchNew.m_ResultSearchInfo;
				pResultSearchInfo->Release();
				pResultSearchInfo->stTaskBaseInfo.TreeItemType = RESULT_TREE_TYPE_DEPART;
				pResultSearchInfo->stTaskBaseInfo.hItem = tvhtif.hItem;
				pResultSearchInfo->stTaskBaseInfo.pTaskTree = &m_GuideTree;
				GetResultTreeItemTypeNew(tvhtif.hItem,pResultSearchInfo);

			}
			break;
			case RESULT_TREE_TYPE_TYPE:
			{
				g_DtMngView->ChangeViewMode(6,1);

				/*StTstResultBase* pTstResult = &g_DtMngView->m_ResultSearch.m_TstResultBase;
				memset(pTstResult,0,sizeof(StTstResultBase));
				pTstResult->TreeItemType = RESULT_TREE_TYPE_TYPE;
				pTstResult->hItem = tvhtif.hItem;
				pTstResult->pResultTree = &m_GuideTree;
				GetResultTreeItemType(tvhtif.hItem,pTstResult);
				g_DtMngView->m_ResultSearch.SearchBaseByTaskName();*/

				//�°�Ľ����ѯ//
				StBasTask* pResultSearchInfo = &g_DtMngView->m_ResultSearchNew.m_ResultSearchInfo;
				pResultSearchInfo->Release();
				pResultSearchInfo->stTaskBaseInfo.TreeItemType = RESULT_TREE_TYPE_DEPART;
				pResultSearchInfo->stTaskBaseInfo.hItem = tvhtif.hItem;
				pResultSearchInfo->stTaskBaseInfo.pTaskTree = &m_GuideTree;
				GetResultTreeItemTypeNew(tvhtif.hItem,pResultSearchInfo);
				g_DtMngView->m_ResultSearchNew.m_ResultSearchInfoDlg.DisPalySearchInfo();
				g_DtMngView->m_ResultSearchNew.m_ResultSearchInfoDlg.OnBnClickedButton1();
			}
			break;

		}
	}
	*pResult = 0;
}



void CLeftTree::OnNMRClickLeftTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(g_DtMngView->m_uMenuSelRow != 0 || g_DtMngView->m_uMenuSelCol != 0)
	{
		g_DtMngView->ChangeViewMode(0,0);
	}

	POINT	point;
	GetCursorPos(&point);

	TVHITTESTINFO	tvhtif;
	GetCursorPos(&tvhtif.pt);
	m_GuideTree.ScreenToClient(&tvhtif.pt);
	m_GuideTree.HitTest(&tvhtif);

	int nUserType = g_LoginUsrInfo.nUserType;
	if(tvhtif.flags & TVHT_ONITEM)
	{
		//int nIcon1, nIcon2;
		//m_DepartMngTree->GetItemImage(tvhtif.hItem, nIcon1, nIcon2);
		m_GuideTree.SelectItem(tvhtif.hItem);
		CString strItem = m_GuideTree.GetItemText(tvhtif.hItem);
		if(strItem.IsEmpty())
			return;


		//�鿴��Ʒ�������Ϣ//
		int nTreeID = m_GuideTree.GetItemData(tvhtif.hItem);

		int nType,nID;
		if(!NumOneToTwo(nTreeID,nType,nID))
		{
			return;
		}

		switch(nType)
		{
		case PROD_TREE_TYPE_DEPART     :
			{
				g_DtMngView->m_ShowInfoList.m_ProductSearch.OnBnClickedSearchBtn();
			}
			break;
		case PROD_TREE_TYPE_PRODCODE:
			{
				StBasProduct nProductInfo;
				memset(&nProductInfo,0,sizeof(StBasProduct));
				GetProductTreeItemType(tvhtif.hItem,&nProductInfo);
			}
			break;

		case MODE_TREE_TYPE_DEPART:
			{
				StBasMode *pModeInfo = &g_DtMngView->m_ShowInfoList.m_ShowModeInfo.m_CurModeInfo;
				pModeInfo->Release();
				memset(pModeInfo,0,sizeof(StBasMode));

				pModeInfo->TreeItemType = MODE_TREE_TYPE_DEPART;
				pModeInfo->hItem = tvhtif.hItem;
				pModeInfo->nOid = nID;
				pModeInfo->pModeTree = &m_GuideTree;
				GetModeTreeItemType(tvhtif.hItem,pModeInfo);
				//���ò�ѯ������ �����²���������ʼΪ��  ���е�//
				StBasMode *pModeSearchInfo =  &g_DtMngView->m_ShowInfoList.m_ModeSearch.m_ModeSearchInfo;
				pModeSearchInfo->Release();
				memset(pModeSearchInfo, 0, sizeof(StBasMode));

				pModeSearchInfo->bModeCurrency = Sel_Check;
				pModeSearchInfo->bModeDedicated = Sel_Check;
				pModeSearchInfo->bModeLineDed = Sel_Check;
				pModeSearchInfo->bModeNotUse = Sel_Check;


				/*pModeSearchInfo->bModeRowChange = Sel_Check;
				pModeSearchInfo->bModeRowNoChange = Sel_Check;
				pModeSearchInfo->bUnInitTabStr = Sel_Check;
				pModeSearchInfo->bInitedTabSrt = Sel_Check;*/
				pModeSearchInfo->nModeRowVar = ModeRow_All;
				pModeSearchInfo->nInitTabSrt = ModeTab_All;

				
				g_DtMngView->m_ShowInfoList.m_ModeSearch.DisplaySearchInfo();//��ʼ��Ϣ//
				g_DtMngView->m_ShowInfoList.m_ModeSearch.OnBnClickedSearchBtn();//��ѯ//
			}
			break;
		case MODE_TREE_TYPE_MODETYPE:
			{
				StBasMode *pModeInfo = &g_DtMngView->m_ShowInfoList.m_ShowModeInfo.m_CurModeInfo;
				pModeInfo->Release();
				memset(pModeInfo,0,sizeof(StBasMode));

				pModeInfo->TreeItemType = MODE_TREE_TYPE_MODETYPE;
				pModeInfo->hItem = tvhtif.hItem;
				pModeInfo->nOid = nID;
				pModeInfo->pModeTree = &m_GuideTree;
				GetModeTreeItemType(tvhtif.hItem,pModeInfo);
				//���ò�ѯ������ �����²���������ʼΪ��  ���е�//
				StBasMode *pModeSearchInfo =  &g_DtMngView->m_ShowInfoList.m_ModeSearch.m_ModeSearchInfo;
				pModeSearchInfo->Release();
				memset(pModeSearchInfo, 0, sizeof(StBasMode));


				switch(nID)
				{
				case Mode_Currency:
					{
						pModeSearchInfo->bModeCurrency = Sel_Check;
						pModeSearchInfo->bModeDedicated = UnSel_Check;
						pModeSearchInfo->bModeLineDed = UnSel_Check;
						pModeSearchInfo->bModeNotUse = UnSel_Check;
					}
					break;
				case Mode_Dedicated:
					{
						pModeSearchInfo->bModeCurrency = UnSel_Check;
						pModeSearchInfo->bModeDedicated = Sel_Check;
						pModeSearchInfo->bModeLineDed = UnSel_Check;
						pModeSearchInfo->bModeNotUse = UnSel_Check;
					}
					break;
				case Mode_LineDed:
					{
						pModeSearchInfo->bModeCurrency = UnSel_Check;
						pModeSearchInfo->bModeDedicated = UnSel_Check;
						pModeSearchInfo->bModeLineDed = Sel_Check;
						pModeSearchInfo->bModeNotUse = UnSel_Check;
					}
					break;
				case Mode_NotUse:
					{
						pModeSearchInfo->bModeCurrency = UnSel_Check;
						pModeSearchInfo->bModeDedicated = UnSel_Check;
						pModeSearchInfo->bModeLineDed = UnSel_Check;
						pModeSearchInfo->bModeNotUse = Sel_Check;
					}
					break;
				}

				/*pModeSearchInfo->bModeRowChange = Sel_Check;
				pModeSearchInfo->bModeRowNoChange = Sel_Check;
				pModeSearchInfo->bUnInitTabStr = Sel_Check;
				pModeSearchInfo->bInitedTabSrt = Sel_Check;*/
				pModeSearchInfo->nModeRowVar = ModeRow_All;
				pModeSearchInfo->nInitTabSrt = ModeTab_All;

				
				g_DtMngView->m_ShowInfoList.m_ModeSearch.DisplaySearchInfo();//��ʼ��Ϣ//
				g_DtMngView->m_ShowInfoList.m_ModeSearch.OnBnClickedSearchBtn();//��ѯ//


				//Ȩ������//
				if(nUserType != user_normal)
				{
					if(pModeInfo->nModeType == Mode_Dedicated)
					{
						m_ModeMenu1_2.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
						
					}else
					{
						if(g_DtMngView->m_ShowInfoList.m_ShowModeInfo.m_CutType == FALSE)
						{
							m_ModeMenu1.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
						}else
						{
							m_ModeMenu1_1.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
						}
						
					}

					
				}
				

			}
			break;
		case MODE_TREE_TYPE_PRODCODE:
			{
				StBasMode *pModeInfo = &g_DtMngView->m_ShowInfoList.m_ShowModeInfo.m_CurModeInfo;
				pModeInfo->Release();
				memset(pModeInfo,0,sizeof(StBasMode));

				pModeInfo->TreeItemType = MODE_TREE_TYPE_PRODCODE;
				pModeInfo->hItem = tvhtif.hItem;
				pModeInfo->nOid = nID;
				pModeInfo->pModeTree = &m_GuideTree;
				GetModeTreeItemType(tvhtif.hItem,pModeInfo);
				//���ò�ѯ������ �����²���������ʼΪ��  ���е�//
				StBasMode *pModeSearchInfo =  &g_DtMngView->m_ShowInfoList.m_ModeSearch.m_ModeSearchInfo;
				pModeSearchInfo->Release();
				memset(pModeSearchInfo, 0, sizeof(StBasMode));


				pModeSearchInfo->stProductInfo.nOid = pModeInfo->stProductInfo.nOid;
				memset(pModeSearchInfo->stProductInfo.szProductNo, 0, sizeof(pModeSearchInfo->stProductInfo.szProductNo));
				strcpy(pModeSearchInfo->stProductInfo.szProductNo, strItem);

				pModeSearchInfo->bModeCurrency = UnSel_Check;
				pModeSearchInfo->bModeDedicated = Sel_Check;
				pModeSearchInfo->bModeLineDed = UnSel_Check;
				pModeSearchInfo->bModeNotUse = UnSel_Check;


				pModeSearchInfo->nModeRowVar = ModeRow_All;
				pModeSearchInfo->nInitTabSrt = ModeTab_All;

				
				g_DtMngView->m_ShowInfoList.m_ModeSearch.DisplaySearchInfo();//��ʼ��Ϣ//
				g_DtMngView->m_ShowInfoList.m_ModeSearch.OnBnClickedSearchBtn();//��ѯ//


				//Ȩ������//
				if(nUserType != user_normal)
				{
					if(g_DtMngView->m_ShowInfoList.m_ShowModeInfo.m_CutType == FALSE)
					{
						m_ModeMenu1.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
					}else
					{
						m_ModeMenu1_1.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
					}
				}
				
			}
			break;

		case MODE_TREE_TYPE_MODE:
			{
				StBasMode *pModeInfo = &g_DtMngView->m_ShowInfoList.m_ShowModeInfo.m_CurModeInfo;
				CShowModeInfo *pShowModeInfo = &g_DtMngView->m_ShowInfoList.m_ShowModeInfo;
				pModeInfo->Release();
				memset(pModeInfo,0,sizeof(StBasMode));
				pModeInfo->Release();
				memset(pModeInfo,0,sizeof(StBasMode));

				pModeInfo->TreeItemType = MODE_TREE_TYPE_MODE;
				pModeInfo->hItem = tvhtif.hItem;
				pModeInfo->nOid = nID;
				pModeInfo->pModeTree = &m_GuideTree;
				pShowModeInfo->m_ShowType = Tree_Modify_Mode;
				pShowModeInfo->GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);
				//Ȩ������//
				if(nUserType != user_normal)
				{
					pShowModeInfo->GetDlgItem(IDOK)->ShowWindow(SW_SHOW);
					pShowModeInfo->GetDlgItem(IDOK)->SetWindowText(_T("����"));
				}else
				{
					pShowModeInfo->GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
				}
				


				m_DMng.GetModeDataOid(nID,pModeInfo);
				pShowModeInfo->DisPalyModeInfo();
				g_DtMngView->m_ShowInfoList.DisplayOneModeDescInfo();


				//Ȩ������//
				if(nUserType != user_normal)
				{
					m_ModeMenu2.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
				}
				
			}
			break;



		case TASK_TREE_TYPE_DEPART:
			{
				StBasTask *pTaskInfo = &g_DtMngView->m_ShowInfoList.m_ShowTaskInfo.m_CurTaskInfo;
				pTaskInfo->Release();
				pTaskInfo->stTaskBaseInfo.nOid = nID;
				pTaskInfo->stTaskBaseInfo.TreeItemType = TASK_TREE_TYPE_DEPART;
				pTaskInfo->stTaskBaseInfo.hItem = tvhtif.hItem;
				pTaskInfo->stTaskBaseInfo.pTaskTree = &m_GuideTree;


				GetTaskTreeItemType(tvhtif.hItem,pTaskInfo);
				////���ò�ѯ������ �����²������е�����//
				StBasTask *pModeSearchInfo =  &g_DtMngView->m_ShowInfoList.m_TaskSearch.m_TaskSearchInfo;
				pModeSearchInfo->Release();


				g_DtMngView->m_ShowInfoList.m_TaskSearch.DisplaySearchInfo();//��ʼ��Ϣ//
				g_DtMngView->m_ShowInfoList.m_TaskSearch.OnBnClickedTaskSearchBtn();//��ѯ////
			}
			break;

		case TASK_TREE_TYPE_TASKTYPE:
			{
				StBasTask *pTaskInfo = &g_DtMngView->m_ShowInfoList.m_ShowTaskInfo.m_CurTaskInfo;
				pTaskInfo->Release();
				pTaskInfo->stTaskBaseInfo.nOid = nID;
				pTaskInfo->stTaskBaseInfo.TreeItemType = TASK_TREE_TYPE_TASKTYPE;
				pTaskInfo->stTaskBaseInfo.hItem = tvhtif.hItem;
				pTaskInfo->stTaskBaseInfo.pTaskTree = &m_GuideTree;


				GetTaskTreeItemType(tvhtif.hItem,pTaskInfo);
				////���ò�ѯ������ �����²������е�����//
				StBasTask *pModeSearchInfo =  &g_DtMngView->m_ShowInfoList.m_TaskSearch.m_TaskSearchInfo;
				pModeSearchInfo->Release();


				g_DtMngView->m_ShowInfoList.m_TaskSearch.DisplaySearchInfo();//��ʼ��Ϣ//
				g_DtMngView->m_ShowInfoList.m_TaskSearch.OnBnClickedTaskSearchBtn();//��ѯ////
			}
			break;


		case TASK_TREE_TYPE_PRODCODE:
			{
				StBasTask *pTaskInfo = &g_DtMngView->m_ShowInfoList.m_ShowTaskInfo.m_CurTaskInfo;
				pTaskInfo->Release();
				pTaskInfo->stTaskBaseInfo.nOid = nID;
				pTaskInfo->stTaskBaseInfo.TreeItemType = TASK_TREE_TYPE_PRODCODE;
				pTaskInfo->stTaskBaseInfo.hItem = tvhtif.hItem;
				pTaskInfo->stTaskBaseInfo.pTaskTree = &m_GuideTree;


				GetTaskTreeItemType(tvhtif.hItem,pTaskInfo);
				////���ò�ѯ������ �����²������е�����//
				StBasTask *pModeSearchInfo =  &g_DtMngView->m_ShowInfoList.m_TaskSearch.m_TaskSearchInfo;
				pModeSearchInfo->Release();


				g_DtMngView->m_ShowInfoList.m_TaskSearch.DisplaySearchInfo();//��ʼ��Ϣ//
				g_DtMngView->m_ShowInfoList.m_TaskSearch.OnBnClickedTaskSearchBtn();//��ѯ////

				m_TaskMenu1.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);

			}
			break;

		case TASK_TREE_TYPE_TASK:
			{
				sizeof(StBasTask);
				StBasTask *pTaskInfo = &g_DtMngView->m_ShowInfoList.m_ShowTaskInfo.m_CurTaskInfo;
				pTaskInfo->Release();
				pTaskInfo->stTaskBaseInfo.nOid = nID;
				pTaskInfo->stTaskBaseInfo.TreeItemType = TASK_TREE_TYPE_TASK;
				pTaskInfo->stTaskBaseInfo.hItem = tvhtif.hItem;
				pTaskInfo->stTaskBaseInfo.pTaskTree = &m_GuideTree;

				if(m_DMng.GetTaskDataOid(nID,pTaskInfo))
				{
					if(m_DMng.GetProdDataOid(pTaskInfo->stProductInfo.nOid,
						&pTaskInfo->stProductInfo))
					{
						g_DtMngView->m_ShowInfoList.m_ShowTaskInfo.DisplayTaskInfo();
						g_DtMngView->m_ShowInfoList.DisplayOneTaskDescInfo();
						m_TaskMenu2.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
					}

				}

			}
			break;

		case RESULT_TREE_TYPE_DEPART:
			{
				g_DtMngView->ChangeViewMode(6,1);
			}
			break;

		}
	}
	*pResult = 0;
}
