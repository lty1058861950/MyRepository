// ShowInfoList.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "ShowInfoList.h"
#include "ProdMng.h"


// CShowInfoList 对话框
CShowInfoList *g_pShowInfoList = NULL;
IMPLEMENT_DYNAMIC(CShowInfoList, CDialog)

CShowInfoList::CShowInfoList(CWnd* pParent /*=NULL*/)
	: CDialog(CShowInfoList::IDD, pParent)
{
	m_ShowType = Show_Product;
	g_pShowInfoList = this;
}

CShowInfoList::~CShowInfoList()
{
	/*m_ProductInfo.DestroyWindow();
	m_ProductPicNum.DestroyWindow();*/
	m_ProductFuction.DestroyWindow();
	m_ShowModeInfo.DestroyWindow();
	m_ShowTaskInfo.DestroyWindow();
}

void CShowInfoList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CShowInfoList, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CShowInfoList 消息处理程序

BOOL CShowInfoList::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ProductSearch.Create(IDD_PRODUCT_SEARCH_DLG,this);
	/*m_ProductInfo.Create(IDD_PRODUCT_INFO_DLG,this);
	m_ProductPicNum.Create(IDD_PRODUCT_PICNUM_DLG,this);*/
	m_ProductFuction.Create(IDD_PRODUCT_BTN_DLG,this);
	

	m_ModeFuction.Create(IDD_MODE_BTN_DLG, this);
	m_ModeSearch.Create(IDD_MODE_SEARCH_BTN, this);
	m_ShowModeInfo.Create(IDD_SHOWMODEINFO_DLG,this);
	m_ShowModeInfo.m_pModeTree = &g_pLeftTree->m_GuideTree;
	

	m_TaskFuction.Create(IDD_TASK_BTN_DLG, this);
	m_TaskSearch.Create(IDD_TASK_SEARCH_DLG, this);
	m_ShowTaskInfo.Create(IDD_SHOWTASKINFO_DLG,this);
	m_ShowTaskInfo.m_pTaskTree = &g_pLeftTree->m_GuideTree;
	
	m_ResultList.Create(IDD_RESULT_LIST_DLG, this);

	m_TaskFuction.m_pTaskSearchInfo = &m_TaskSearch.m_TaskSearchInfo;

	ChangeShowWindow(m_ShowType);
	ChangeTaskBtnShow(m_TaskFuction.m_pTaskSearchInfo);

	StBasProduct nProductInfo;
	memset(&nProductInfo,0,sizeof(StBasProduct));
	nProductInfo.nGroupOid = g_CurSelDepart.nOid;
	
	
	m_ProductSearch.OnBnClickedSearchBtn();
	//DisplayProdInfo(&nProductInfo);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CShowInfoList::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}

void CShowInfoList::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	AutoSize();
}
void CShowInfoList::AutoSize()
{
	CRect Rect ;
	GetClientRect(&Rect) ;

	int nBtnWidth = 80;
	int nBtnHeight = 30;
	int nProdSearchHeight = 120;
	int nModeSearchHeight = 180;
	int nTaskSearchHeight = 130;
	int nTaskSearchHeight1 = 160;
	int nTaskSearchHeight2 = 190;
	int nTaskSearchHeight3 = 220;

	if (GetDlgItem(IDC_SHOWLIST_STATIC1)->GetSafeHwnd())
	{
		GetDlgItem(IDC_SHOWLIST_STATIC1)->MoveWindow(1,1,Rect.Width()-1*2,Rect.Height()-1*2);
	}

	if (IsWindow(m_ShowModeInfo.m_hWnd))
	{
		m_ShowModeInfo.MoveWindow(3,13,Rect.Width()-6,Rect.Height()-(13+10));
	}

	if (IsWindow(m_ShowTaskInfo.m_hWnd))
	{
		m_ShowTaskInfo.MoveWindow(3,13,Rect.Width()-6,Rect.Height()-(13+10));
	}

	int nUserType = g_LoginUsrInfo.nUserType;

	if(m_ShowType == Show_Product)
	{
		

		if(nUserType == user_normal)
		{
			if (m_ResultList.GetSafeHwnd())
			{
				m_ResultList.MoveWindow(5,13+nProdSearchHeight,Rect.Width()-(5*2),Rect.Height()-(13+10+nProdSearchHeight));
			}
		}else
		{
			if (m_ResultList.GetSafeHwnd())
			{
				m_ResultList.MoveWindow(5,13+nProdSearchHeight,Rect.Width()-(5*2),Rect.Height()-(13+10+nProdSearchHeight+50));
			}
		}
		
	}

	if(m_ShowType == Show_Mode)
	{
		
		if(nUserType == user_normal)
		{
			if (m_ResultList.GetSafeHwnd())
			{
				m_ResultList.MoveWindow(5,13+nModeSearchHeight,Rect.Width()-(5*2),Rect.Height()-(13+10+nModeSearchHeight));
			}
		}else
		{
			if (m_ResultList.GetSafeHwnd())
			{
				m_ResultList.MoveWindow(5,13+nModeSearchHeight,Rect.Width()-(5*2),Rect.Height()-(13+10+nModeSearchHeight+50));
			}
		}

		
	}

	if(m_ShowType == Show_Task)
	{

		int nTaskStatues = m_TaskSearch.m_TaskSearchInfo.stTaskBaseInfo.nTaskStatus;
		switch(nTaskStatues)
		{
		
		case Task_Init://0行//
			{
				//任务模块//
				if(m_TaskSearch.GetSafeHwnd())
				{
					m_TaskSearch.MoveWindow(3,13,Rect.Width()-6,nTaskSearchHeight);
				}

				if(nUserType == user_normal)
				{
					if (m_ResultList.GetSafeHwnd())
					{
						m_ResultList.MoveWindow(5,13+nTaskSearchHeight,Rect.Width()-(5*2),Rect.Height()-(13+10+nTaskSearchHeight));
					}
				}else
				{
					if (m_ResultList.GetSafeHwnd())
					{
						m_ResultList.MoveWindow(5,13+nTaskSearchHeight,Rect.Width()-(5*2),Rect.Height()-(13+10+nTaskSearchHeight+50));
					}
				}


				if(m_TaskFuction.GetSafeHwnd())
				{
					m_TaskFuction.MoveWindow(3,Rect.bottom-(45),Rect.Width()-6,35);
				}
			}
			break;

		case Task_OK://1行//
		case Task_Runing:
			{
				//任务模块//
				if(m_TaskSearch.GetSafeHwnd())
				{
					m_TaskSearch.MoveWindow(3,13,Rect.Width()-6,nTaskSearchHeight1);
				}

				if(nUserType == user_normal)
				{
					if (m_ResultList.GetSafeHwnd())
					{
						m_ResultList.MoveWindow(5,13+nTaskSearchHeight1,Rect.Width()-(5*2),Rect.Height()-(13+10+nTaskSearchHeight1));
					}
				}else
				{
					if (m_ResultList.GetSafeHwnd())
					{
						m_ResultList.MoveWindow(5,13+nTaskSearchHeight1,Rect.Width()-(5*2),Rect.Height()-(13+10+nTaskSearchHeight1+50));
					}
				}


				if(m_TaskFuction.GetSafeHwnd())
				{
					m_TaskFuction.MoveWindow(3,Rect.bottom-(45),Rect.Width()-6,35);
				}
			}
			break;
		case Task_Finish://2行//
			{
				//任务模块//
				if(m_TaskSearch.GetSafeHwnd())
				{
					m_TaskSearch.MoveWindow(3,13,Rect.Width()-6,nTaskSearchHeight2);
				}

				if(nUserType == user_normal)
				{
					if (m_ResultList.GetSafeHwnd())
					{
						m_ResultList.MoveWindow(5,13+nTaskSearchHeight2,Rect.Width()-(5*2),Rect.Height()-(13+10+nTaskSearchHeight2));
					}
				}else
				{
					if (m_ResultList.GetSafeHwnd())
					{
						m_ResultList.MoveWindow(5,13+nTaskSearchHeight2,Rect.Width()-(5*2),Rect.Height()-(13+10+nTaskSearchHeight2+50));
					}
				}
				

				if(m_TaskFuction.GetSafeHwnd())
				{
					m_TaskFuction.MoveWindow(3,Rect.bottom-(45),Rect.Width()-6,35);
				}
			}
			break;
		case  Task_All://2行//
			{
				//任务模块//
				if(m_TaskSearch.GetSafeHwnd())
				{
					m_TaskSearch.MoveWindow(3,13,Rect.Width()-6,nTaskSearchHeight2);
				}

				//if (m_ResultList.GetSafeHwnd())
				//{
				//	m_ResultList.MoveWindow(5,13+nTaskSearchHeight2,Rect.Width()-(5*2),Rect.Height()-(13+10+nTaskSearchHeight2));
				//}

				if(nUserType == user_normal)
				{
					if (m_ResultList.GetSafeHwnd())
					{
						m_ResultList.MoveWindow(5,13+nTaskSearchHeight2,Rect.Width()-(5*2),Rect.Height()-(13+10+nTaskSearchHeight2));
					}
				}else
				{
					if (m_ResultList.GetSafeHwnd())
					{
						m_ResultList.MoveWindow(5,13+nTaskSearchHeight2,Rect.Width()-(5*2),Rect.Height()-(13+10+nTaskSearchHeight2+50));
					}
				}


				if(m_TaskFuction.GetSafeHwnd())
				{
					m_TaskFuction.MoveWindow(3,Rect.bottom-(45),Rect.Width()-6,35);
				}
			}
			break;
		}
	}
	//产品模块//
	if(m_ProductSearch.GetSafeHwnd())
	{
		m_ProductSearch.MoveWindow(3,13,Rect.Width()-6,nProdSearchHeight);
	}
	
	if(m_ProductFuction.GetSafeHwnd())
	{
		m_ProductFuction.MoveWindow(3,Rect.bottom-(45),Rect.Width()-6,35);
	}
	
	//模板模块//
	if(m_ModeSearch.GetSafeHwnd())
	{
		m_ModeSearch.MoveWindow(3,13,Rect.Width()-6,nModeSearchHeight);
	}

	if(m_ModeFuction.GetSafeHwnd())
	{
		m_ModeFuction.MoveWindow(3,Rect.bottom-(45),Rect.Width()-6,35);
	}

	
}

void CShowInfoList::ListCtrl_ClearAllColumn()
{
	int		i, nColCnt;
	CEditableListCtrl *pList2 = &m_ResultList.m_ResultList;

	

	pList2->DeleteAllItems();
	nColCnt = pList2->GetHeaderCtrl()->GetItemCount();	
	for (i=0; i<nColCnt; i++)
	{
		pList2->DeleteColumn(0);
	}
}

void CShowInfoList::ChangeShowWindow(int nShowType)
{
	int nUserType = g_LoginUsrInfo.nUserType;
	if(nShowType == Show_Product)
	{
		m_ResultList.ShowWindow(SW_SHOW);
		if(nUserType == user_normal)
		{
			m_ProductFuction.ShowWindow(SW_HIDE);
		}else
		{
			m_ProductFuction.ShowWindow(SW_SHOW);
		}
		
		m_ProductSearch.ShowWindow(SW_SHOW);

		m_ModeFuction.ShowWindow(SW_HIDE);
		m_ModeSearch.ShowWindow(SW_HIDE);
		m_ShowModeInfo.ShowWindow(SW_HIDE);

		m_ShowTaskInfo.ShowWindow(SW_HIDE);
		m_TaskSearch.ShowWindow(SW_HIDE);
		m_TaskFuction.ShowWindow(SW_HIDE);

		
	}

	if(nShowType == Show_Mode)
	{
		m_ResultList.ShowWindow(SW_SHOW);
		m_ProductFuction.ShowWindow(SW_HIDE);
		m_ProductSearch.ShowWindow(SW_HIDE);

		if(nUserType == user_normal)
		{
			m_ModeFuction.ShowWindow(SW_HIDE);
		}else
		{
			m_ModeFuction.ShowWindow(SW_SHOW);
		}
		
		m_ModeSearch.ShowWindow(SW_SHOW);
		m_ShowModeInfo.ShowWindow(SW_HIDE);

		m_ShowTaskInfo.ShowWindow(SW_HIDE);
		m_TaskSearch.ShowWindow(SW_HIDE);
		m_TaskFuction.ShowWindow(SW_HIDE);
	}

	if(nShowType == Show_Task)
	{
		m_ResultList.ShowWindow(SW_SHOW);
		m_ProductFuction.ShowWindow(SW_HIDE);
		m_ProductSearch.ShowWindow(SW_HIDE);

		m_ModeFuction.ShowWindow(SW_HIDE);
		m_ModeSearch.ShowWindow(SW_HIDE);
		m_ShowModeInfo.ShowWindow(SW_HIDE);

		m_ShowTaskInfo.ShowWindow(SW_HIDE);
		m_TaskSearch.ShowWindow(SW_SHOW);
		if(nUserType == user_normal)
		{
			m_TaskFuction.ShowWindow(SW_HIDE);
		}else
		{
			m_TaskFuction.ShowWindow(SW_SHOW);
		}
		
	}
	
	if(nShowType == Show_OneMode)
	{
		m_ResultList.ShowWindow(SW_HIDE);
		m_ProductFuction.ShowWindow(SW_HIDE);
		m_ProductSearch.ShowWindow(SW_HIDE);

		m_ModeFuction.ShowWindow(SW_HIDE);
		m_ModeSearch.ShowWindow(SW_HIDE);
		m_ShowModeInfo.ShowWindow(SW_SHOW);

		m_ShowTaskInfo.ShowWindow(SW_HIDE);
		m_TaskSearch.ShowWindow(SW_HIDE);
		m_TaskFuction.ShowWindow(SW_HIDE);
	}
	if(nShowType == Show_OneTask)
	{
		m_ResultList.ShowWindow(SW_HIDE);
		m_ProductFuction.ShowWindow(SW_HIDE);
		m_ProductSearch.ShowWindow(SW_HIDE);

		m_ModeFuction.ShowWindow(SW_HIDE);
		m_ModeSearch.ShowWindow(SW_HIDE);
		m_ShowModeInfo.ShowWindow(SW_HIDE);

		m_ShowTaskInfo.ShowWindow(SW_SHOW);
		m_TaskSearch.ShowWindow(SW_HIDE);
		m_TaskFuction.ShowWindow(SW_HIDE);
	}
	m_ShowType = nShowType;
	PostMessage(WM_SIZE);
}
void CShowInfoList::ChangeTaskBtnShow(StBasTask *pTaskSearchInfo)
{
	int nTaskStatus = pTaskSearchInfo->stTaskBaseInfo.nTaskStatus;
	switch(nTaskStatus)
	{
	case Task_Init:
		{
			m_TaskFuction.GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);//取消任务//
			m_TaskFuction.GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_HIDE);//更改派工//
			m_TaskFuction.GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_HIDE);//任务多次执行//
			m_TaskFuction.GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_HIDE);//结果上传//
			m_TaskFuction.GetDlgItem(IDC_BUTTON6)->ShowWindow(SW_HIDE);//任务下载//

			m_TaskFuction.GetDlgItem(IDC_TASK_ADD_BTN)->ShowWindow(SW_SHOW);//添加任务//
			m_TaskFuction.GetDlgItem(IDC_TASK_EDT_BTN)->ShowWindow(SW_SHOW);//更改任务//
			m_TaskFuction.GetDlgItem(IDC_TASK_DEL_BTN)->ShowWindow(SW_SHOW);//删除任务//
			m_TaskFuction.GetDlgItem(IDC_TASK_SEND_BTN)->ShowWindow(SW_SHOW);//派工任务//
			m_TaskFuction.GetDlgItem(IDC_BUTTON3)->ShowWindow(SW_SHOW);//任务检测//

			
			m_TaskFuction.PostMessage(WM_SIZE);
		}
		break;
	case Task_OK:
		{
			m_TaskFuction.GetDlgItem(IDC_TASK_ADD_BTN)->ShowWindow(SW_HIDE);//添加任务//
			m_TaskFuction.GetDlgItem(IDC_TASK_EDT_BTN)->ShowWindow(SW_HIDE);//更改任务//
			m_TaskFuction.GetDlgItem(IDC_TASK_SEND_BTN)->ShowWindow(SW_HIDE);//派工任务//
			m_TaskFuction.GetDlgItem(IDC_BUTTON3)->ShowWindow(SW_HIDE);//任务检测//
			m_TaskFuction.GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_HIDE);//任务多次执行//
			m_TaskFuction.GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_HIDE);//结果上传//
			
			
			m_TaskFuction.GetDlgItem(IDC_TASK_DEL_BTN)->ShowWindow(SW_SHOW);//删除任务//
			m_TaskFuction.GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_SHOW);//取消任务//
			m_TaskFuction.GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_SHOW);//更改派工//
			m_TaskFuction.GetDlgItem(IDC_BUTTON6)->ShowWindow(SW_SHOW);//任务下载//

			m_TaskFuction.PostMessage(WM_SIZE);
		}
		break;
	case Task_Runing:
		{
			m_TaskFuction.GetDlgItem(IDC_TASK_ADD_BTN)->ShowWindow(SW_HIDE);//添加任务//
			m_TaskFuction.GetDlgItem(IDC_TASK_EDT_BTN)->ShowWindow(SW_HIDE);//更改任务//
			m_TaskFuction.GetDlgItem(IDC_TASK_SEND_BTN)->ShowWindow(SW_HIDE);//派工任务//
			m_TaskFuction.GetDlgItem(IDC_BUTTON3)->ShowWindow(SW_HIDE);//任务检测//
			m_TaskFuction.GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_HIDE);//任务多次执行//
			m_TaskFuction.GetDlgItem(IDC_BUTTON6)->ShowWindow(SW_HIDE);//任务下载//
			

			
			
			m_TaskFuction.GetDlgItem(IDC_TASK_DEL_BTN)->ShowWindow(SW_SHOW);//删除任务//
			m_TaskFuction.GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_SHOW);//取消任务//
			m_TaskFuction.GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_SHOW);//更改派工//
			m_TaskFuction.GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_SHOW);//结果上传//

			
			m_TaskFuction.PostMessage(WM_SIZE);
		}
		break;
	case Task_Finish:
		{
			m_TaskFuction.GetDlgItem(IDC_TASK_ADD_BTN)->ShowWindow(SW_HIDE);//添加任务//
			m_TaskFuction.GetDlgItem(IDC_TASK_EDT_BTN)->ShowWindow(SW_HIDE);//更改任务//
			m_TaskFuction.GetDlgItem(IDC_TASK_SEND_BTN)->ShowWindow(SW_HIDE);//派工任务//
			m_TaskFuction.GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);//取消任务//
			m_TaskFuction.GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_HIDE);//更改派工//
			m_TaskFuction.GetDlgItem(IDC_BUTTON3)->ShowWindow(SW_HIDE);//任务检测//
			m_TaskFuction.GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_HIDE);//结果上传//
			m_TaskFuction.GetDlgItem(IDC_BUTTON6)->ShowWindow(SW_HIDE);//任务下载//

		
			m_TaskFuction.GetDlgItem(IDC_TASK_DEL_BTN)->ShowWindow(SW_SHOW);//删除任务//
			m_TaskFuction.GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_SHOW);//任务多次执行//
			

			
			m_TaskFuction.PostMessage(WM_SIZE);
			
		}
		break;
	case Task_All:
		{
			m_TaskFuction.GetDlgItem(IDC_TASK_SEND_BTN)->ShowWindow(SW_HIDE);//派工任务//
			m_TaskFuction.GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);//取消任务//
			m_TaskFuction.GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_HIDE);//更改派工//
			m_TaskFuction.GetDlgItem(IDC_BUTTON3)->ShowWindow(SW_HIDE);//任务检测//
			m_TaskFuction.GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_HIDE);//任务多次执行//
			m_TaskFuction.GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_HIDE);//结果上传//
			m_TaskFuction.GetDlgItem(IDC_BUTTON6)->ShowWindow(SW_HIDE);//任务下载//

			m_TaskFuction.GetDlgItem(IDC_TASK_ADD_BTN)->ShowWindow(SW_HIDE);//添加任务//
			m_TaskFuction.GetDlgItem(IDC_TASK_EDT_BTN)->ShowWindow(SW_HIDE);//更改任务//
			m_TaskFuction.GetDlgItem(IDC_TASK_DEL_BTN)->ShowWindow(SW_SHOW);//删除任务//

			m_TaskFuction.ShowWindow(SW_SHOW);
			m_TaskFuction.PostMessage(WM_SIZE);
		}
		break;
	}
}

void CShowInfoList::InsertOneProdToList(StBasProduct *pProductInfo)
{
	CEditableListCtrl *pList2 = &m_ResultList.m_ResultList;

	CString strNum, strText;
	int nCur,nCount = 0;
	int pos = 1;

	nCount = pList2->GetItemCount();
	strNum.Format(_T("%d"),nCount+1);
	nCur = pList2->InsertItem(nCount,strNum);
	pList2->SetItemData(nCur,pProductInfo->nOid);
	pList2->SetItemText(nCur,pos++,pProductInfo->szProductNo);
	pList2->SetItemText(nCur,pos++,pProductInfo->szProductName);

	/*strText = GetProductType(pProductInfo->nPicNumType);
	pList2->SetItemText(nCur,pos++,strText);*/
	pList2->SetItemText(nCur,pos++,pProductInfo->szCreateTime);
	pList2->SetItemText(nCur,pos++,pProductInfo->szCreateUser);
}
void CShowInfoList::ModifyOneProdToList(int nIndex, StBasProduct *pProductInfo)
{
	CEditableListCtrl *pList2 = &m_ResultList.m_ResultList;
	CString strText;
	int nCount = 0;
	int pos = 1;


	nCount = pList2->GetItemCount();
	if(nIndex <0 || nIndex >= nCount)
	{
		return;
	}
	pList2->SetItemData(nIndex,pProductInfo->nOid);
	pList2->SetItemText(nIndex,pos++,pProductInfo->szProductNo);
	pList2->SetItemText(nIndex,pos++,pProductInfo->szProductName);

	/*strText = GetProductType(pProductInfo->nPicNumType);
	pList2->SetItemText(nIndex,pos++,strText);*/
	pList2->SetItemText(nIndex,pos++,pProductInfo->szCreateTime);
	pList2->SetItemText(nIndex,pos++,pProductInfo->szCreateUser);

}

void CShowInfoList::DisplayProdInfo(StBasProduct *pStBasProduct)
{
	m_ShowType = Show_Product;
	m_ResultList.m_ShowType = Show_Product;
	ChangeShowWindow(m_ShowType);
	CString strTitle;
	strTitle.Format(_T("产品管理界面"));
	GetDlgItem(IDC_SHOWLIST_STATIC1)->SetWindowText(strTitle);
	
	CEditableListCtrl *pList2 = &m_ResultList.m_ResultList;

	int     i;
	CString	str, strText;
	int     iColNum; 
	char	ItemName[20][30] = {"序号", "产品代号", "产品名称",
		"创建时间","创建人"};
	int     ItemLen[20]      = {50,100,200,150,100};
	int     EnableCol = 2;

	ListCtrl_ClearAllColumn();
	iColNum = 5;

	for (i=0; i<iColNum; i++)
	{
		str.Format("%s", ItemName[i]);
		pList2->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen[i]);
	}

	//开始查找//
	UINT nGroupOid = g_CurSelDepart.nOid;

	
	//显示本部门的所有产品//
	int   nCount = 0;
	vector<StBasProduct> nArrayProduct;
	StBasProduct *pProductInfo;
	if(m_DMng.GetGroupProductData (nGroupOid,pStBasProduct,&nArrayProduct))
	{
		nCount = nArrayProduct.size();

		for(i = 0;i<nCount;i++)
		{
			pProductInfo = &nArrayProduct.at(i);
			InsertOneProdToList(pProductInfo);

		}
		nArrayProduct.clear();
	}
		
	//显示结果信息//
	int nPerPageNum = pStBasProduct->nPerPageNum;
	int nResultNum = pStBasProduct->nResultNum;
	int nCurPage = pStBasProduct->nCurPage;
	int nPageNum = 1;

	if(nPerPageNum == g_nSearchPerPageNum[All_Result])
	{

	}else
	{
		if( nResultNum%nPerPageNum >0)
		{
			nPageNum = (nResultNum/nPerPageNum)+1;
		}else
		{
			nPageNum = nResultNum/nPerPageNum;
		}
	}

	if(nPageNum<= 0)
	{
		nPageNum = 1;
	}
	
	strText.Format(_T("共查询到 %d 条数据"), pStBasProduct->nResultNum);
	m_ResultList.GetDlgItem(IDC_LIST_STATIC1)->SetWindowText(strText);
	strText.Format(_T("%d/%d"),nCurPage , nPageNum);
	m_ResultList.GetDlgItem(IDC_LIST_STATIC2)->SetWindowText(strText);

	//将结果反馈给 ResultList界面//
	StSearchSetInfo *pSearchSetInfo = &m_ResultList.m_stSearchSetInfo;
	pSearchSetInfo->nCurPage = nCurPage;
	pSearchSetInfo->nAimPage = nCurPage;
	pSearchSetInfo->nMaxPage = nPageNum;
	m_ResultList.SetBtnStatus();
	
}


void CShowInfoList::DisplayModeInfo(StBasMode *pModesearchInfo)
{

	CEditableListCtrl *pList2 = &m_ResultList.m_ResultList;
	
	m_ShowType = Show_Mode;
	m_ResultList.m_ShowType = Show_Mode;
	ChangeShowWindow(m_ShowType);

	CString strTitle;
	strTitle.Format(_T("检验记录管理界面"));
	GetDlgItem(IDC_SHOWLIST_STATIC1)->SetWindowText(strTitle);
	
	int     i;
	CString	str, strText;
	int     iColNum,iColNum1; 

	char	ItemName[20][30] = {"序号","模板名称","模板版本","模板类型","行可变属性",
		"模板大小","数据表名称","模板已使用","适用的产品","产品型号", 
		"产品阶段","创建时间","创建人",};
	int     ItemLen[20]      = {50,100,100,100,100, 100,150,100,100,100, 100,150,100};

	char	ItemName1[20][30] = {"序号","模板名称","模板版本","模板类型","适用的产品",
		"行可变属性","创建时间","创建人",};
	int     ItemLen1[20]      = {50,100,100,100,100, 100,150,100};

	int     EnableCol = 2;

	ListCtrl_ClearAllColumn();
	iColNum = 13;
	iColNum1 = 8;

	if(g_DebugShow)
	{
		for (i=0; i<iColNum1; i++)
		{
			str.Format("%s", ItemName1[i]);
			pList2->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen1[i]);	
		}

	}else
	{
		for (i=0; i<iColNum; i++)
		{
			str.Format("%s", ItemName[i]);
			pList2->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen[i]);	
		}
	}
	

	//开始查找//
	UINT nGroupOid = pModesearchInfo->nGroupOid = g_CurSelDepart.nOid;
	UINT nProductOid = pModesearchInfo->stProductInfo.nOid;

	if(nGroupOid == 0)
	{
		return;
	}else
	{
		//以类型的方式进行显示//
		int     i,nCount = 0;
		vector<StBasMode> stBasModeArray;
		
		if(m_DMng.GetGroupModeInfo (nGroupOid,pModesearchInfo,&stBasModeArray))
		{
			nCount = stBasModeArray.size();
			for(i = 0;i<nCount;i++)
			{
				InsertOneModeToList(&stBasModeArray.at(i));
			}

			stBasModeArray.clear();
		}
		
	}


	//显示结果信息//
	int nPerPageNum = pModesearchInfo->nPerPageNum;
	int nResultNum = pModesearchInfo->nResultNum;
	int nCurPage = pModesearchInfo->nCurPage;
	int nPageNum = 1;

	if(nPerPageNum == g_nSearchPerPageNum[All_Result])
	{

	}else
	{
		if( nResultNum%nPerPageNum >0)
		{
			nPageNum = (nResultNum/nPerPageNum)+1;
		}else
		{
			nPageNum = nResultNum/nPerPageNum;
		}
	}

	if(nPageNum<= 0)
	{
		nPageNum = 1;
	}
	strText.Format(_T("共查询到 %d 条数据"), pModesearchInfo->nResultNum);
	m_ResultList.GetDlgItem(IDC_LIST_STATIC1)->SetWindowText(strText);
	strText.Format(_T("%d/%d"),nCurPage , nPageNum);
	m_ResultList.GetDlgItem(IDC_LIST_STATIC2)->SetWindowText(strText);

	//将结果反馈给 ResultList界面//
	StSearchSetInfo *pSearchSetInfo = &m_ResultList.m_stSearchSetInfo;
	pSearchSetInfo->nCurPage = nCurPage;
	pSearchSetInfo->nAimPage = nCurPage;
	pSearchSetInfo->nMaxPage = nPageNum;
	m_ResultList.SetBtnStatus();
}

void CShowInfoList::InsertOneModeToList(StBasMode *pStBasMode)
{
	CEditableListCtrl *pList2 = &m_ResultList.m_ResultList;

	CString strNum, strText;
	int nCur,nCount = 0, pos ;

	nCount = pList2->GetItemCount();
	strNum.Format(_T("%d"),nCount+1);
	nCur = pList2->InsertItem(nCount,strNum);

	if(g_DebugShow)
	{
		pos = 1;
		pList2->SetItemData(nCur, pStBasMode->nOid);
		strText.Format(_T("%s"), pStBasMode->szModeName);//1	模板名称	
		pList2->SetItemText(nCur,pos++,strText);
		strText.Format(_T("%s"), pStBasMode->szModeVersion);//  2.模板版本
		pList2->SetItemText(nCur,pos++,strText);
		strText.Format(_T("%s"), GetModeType(pStBasMode->nModeType));//3	模板类型
		pList2->SetItemText(nCur,pos++,strText);

		strText.Format(_T("%s"), pStBasMode->stProductInfo.szProductNo);//4	适用产品代号
		pList2->SetItemText(nCur,pos++,strText);//产品代号//
		strText.Format(_T("%s"), GetModeRowVar(pStBasMode->nModeRowVar));//5	行可变类型
		pList2->SetItemText(nCur,pos++,strText);
		strText.Format(_T("%s"), pStBasMode->szCreateTime);//6.创建时间
		pList2->SetItemText(nCur,pos++,strText);
		strText.Format(_T("%s"), pStBasMode->szCreateUser);//7.创建人
		pList2->SetItemText(nCur,pos++,strText);
	}else
	{
		pos = 1;
		pList2->SetItemData(nCur, pStBasMode->nOid);
		strText.Format(_T("%s"), pStBasMode->szModeName);
		pList2->SetItemText(nCur,pos++,strText);
		strText.Format(_T("%s"), pStBasMode->szModeVersion);
		pList2->SetItemText(nCur,pos++,strText);
		strText.Format(_T("%s"), GetModeType(pStBasMode->nModeType));
		pList2->SetItemText(nCur,pos++,strText);
		strText.Format(_T("%s"), GetModeRowVar(pStBasMode->nModeRowVar));
		pList2->SetItemText(nCur,pos++,strText);
		strText.Format(_T("%s"), GetModeSizeText(pStBasMode->nModeSize));
		pList2->SetItemText(nCur,pos++,strText);//模板大小//
		strText.Format(_T("%s"), pStBasMode->szModeTabName);
		pList2->SetItemText(nCur,pos++,strText);//表名//
		strText.Format(_T("%s"), GetModeInitStr(pStBasMode->nInitTabSrt));
		pList2->SetItemText(nCur,pos++,strText);//初始化结构//
		strText.Format(_T("%s"), pStBasMode->stProductInfo.szProductNo);
		pList2->SetItemText(nCur,pos++,strText);//产品代号//
		strText.Format(_T("%s"), pStBasMode->szModel);
		pList2->SetItemText(nCur,pos++,strText);//型号//
		strText.Format(_T("%s"), pStBasMode->szPhase);
		pList2->SetItemText(nCur,pos++,strText);//阶段//
		strText.Format(_T("%s"), pStBasMode->szCreateTime);
		pList2->SetItemText(nCur,pos++,strText);
		strText.Format(_T("%s"), pStBasMode->szCreateUser);
		pList2->SetItemText(nCur,pos++,strText);
	}
	


}
void CShowInfoList::ModifyOneModeToList(int nIndex, StBasMode *pStBasMode)
{

	CEditableListCtrl *pList2 = &m_ResultList.m_ResultList;

	CString strText;
	int nCount = 0,pos = 1;;
	
	nCount = pList2->GetItemCount();
	if(nIndex <0 || nIndex >= nCount)
	{
		return;
	}

	if(g_DebugShow)
	{
		pos = 1;
		pList2->SetItemData(nIndex, pStBasMode->nOid);
		strText.Format(_T("%s"), pStBasMode->szModeName);//1	模板名称	
		pList2->SetItemText(nIndex,pos++,strText);
		strText.Format(_T("%s"), pStBasMode->szModeVersion);//  2.模板版本
		pList2->SetItemText(nIndex,pos++,strText);
		strText.Format(_T("%s"), GetModeType(pStBasMode->nModeType));//3	模板类型
		pList2->SetItemText(nIndex,pos++,strText);

		strText.Format(_T("%s"), pStBasMode->stProductInfo.szProductNo);//4	适用产品代号
		pList2->SetItemText(nIndex,pos++,strText);//产品代号//
		strText.Format(_T("%s"), GetModeRowVar(pStBasMode->nModeRowVar));//5	行可变类型
		pList2->SetItemText(nIndex,pos++,strText);
		strText.Format(_T("%s"), pStBasMode->szCreateTime);//6.创建时间
		pList2->SetItemText(nIndex,pos++,strText);
		strText.Format(_T("%s"), pStBasMode->szCreateUser);//7.创建人
		pList2->SetItemText(nIndex,pos++,strText);
	}else
	{
		pos = 1;
		pList2->SetItemData(nIndex, pStBasMode->nOid);
		strText.Format(_T("%s"), pStBasMode->szModeName);
		pList2->SetItemText(nIndex,pos++,strText);
		strText.Format(_T("%s"), pStBasMode->szModeVersion);
		pList2->SetItemText(nIndex,pos++,strText);
		strText.Format(_T("%s"), GetModeType(pStBasMode->nModeType));
		pList2->SetItemText(nIndex,pos++,strText);
		strText.Format(_T("%s"), GetModeRowVar(pStBasMode->nModeRowVar));
		pList2->SetItemText(nIndex,pos++,strText);
		strText.Format(_T("%s"), GetModeSizeText(pStBasMode->nModeSize));
		pList2->SetItemText(nIndex,pos++,strText);//模板大小//
		strText.Format(_T("%s"), pStBasMode->szModeTabName);
		pList2->SetItemText(nIndex,pos++,strText);//表名//
		strText.Format(_T("%s"), GetModeInitStr(pStBasMode->nInitTabSrt));
		pList2->SetItemText(nIndex,pos++,strText);//初始化结构//
		strText.Format(_T("%s"), pStBasMode->stProductInfo.szProductNo);
		pList2->SetItemText(nIndex,pos++,strText);//产品代号//
		strText.Format(_T("%s"), pStBasMode->szModel);
		pList2->SetItemText(nIndex,pos++,strText);//型号//
		strText.Format(_T("%s"), pStBasMode->szPhase);
		pList2->SetItemText(nIndex,pos++,strText);//阶段//
		strText.Format(_T("%s"), pStBasMode->szCreateTime);
		pList2->SetItemText(nIndex,pos++,strText);
		strText.Format(_T("%s"), pStBasMode->szCreateUser);
		pList2->SetItemText(nIndex,pos++,strText);
	}
	
}


void CShowInfoList::InsertOneTaskToList(StBasTask *pBasTaskInfo)
{
	
	CEditableListCtrl *pList2 = &m_ResultList.m_ResultList;

	CString strNum, strText;
	int nCur,pos,nCount = 0;
	

	nCount = pList2->GetItemCount();
	strNum.Format(_T("%d"),nCount+1);
	nCur = pList2->InsertItem(nCount,strNum);

	
	pList2->SetItemData(nCur,pBasTaskInfo->stTaskBaseInfo.nOid);

	/*char	ItemName1[35][30] = {
		"序号", "任务状态","任务名称","产品代号",_T("产品批次号")
		"编号数量","产品名称","型号", "阶段","交检部门",
		"检验组长","检验员姓名","创建时间","创建人","派工时间",
		"执行时间","完成时间",};*/

	//char	ItemName1[35][30] = {
	//	"序号", 
	//	"任务状态",	"任务名称",	"产品代号",	_T("产品批次号"),
	//	"型号",		"阶段",		"检验组长",		"检验员",
	//	"交检部门",	"创建时间",	"创建人",		"派工时间",
	//	"执行时间",	"完成时间",};
	if(g_DebugShow)
	{
		pos = 1;
		strText.Format(_T("%s"), GetTaskStatus(pBasTaskInfo->stTaskBaseInfo.nTaskStatus));
		pList2->SetItemText(nCur,pos++,strText);//任务状态
		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szTaskName);//任务名称
		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stProductInfo.szProductNo);//产品代号
		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szBatch);//批次号

		//strText.Format(_T("%d"),pBasTaskInfo->stTaskBaseInfo.nCodeNumber);//数量
		//pList2->SetItemText(nCur,pos++,strText);
		//pList2->SetItemText(nCur,pos++,pBasTaskInfo->stProductInfo.szProductName);//产品名称

		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szModel);//产品型号
		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szPhase);//产品阶段

		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szCheckLeader);//检验组长
		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szCheckUser);//检验员姓名

		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stHrUpDepart.szUpDepartName);//交检部门

		pList2->SetItemText(nCur,pos++, GetTaskArmyText(pBasTaskInfo->stTaskBaseInfo.nArmyTest) );//是否军检

		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szCreateDate);//创建时间//
		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szCreateUser);//创建人//
		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szSendDate);//派工时间//
		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szDownLoadDate);//下载时间//
		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szFinishDate);//完成时间//

	}else
	{
		pos = 1;
		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szTaskName);//任务名称
		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szProjectNo);//检验单号

		strText.Format(_T("%s"), GetTaskStatus(pBasTaskInfo->stTaskBaseInfo.nTaskStatus));
		pList2->SetItemText(nCur,pos++,strText);//任务状态
		strText.Format(_T("%s"), GetTaskType(pBasTaskInfo->stTaskBaseInfo.nTaskType));
		pList2->SetItemText(nCur,pos++,strText);//任务类型


		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szModel);//产品型号
		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szPhase);//产品阶段
		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stProductInfo.szProductNo);//产品代号

		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szProductCode);//产品编号
		strText.Format(_T("%d"),pBasTaskInfo->stTaskBaseInfo.nCodeNumber);//数量
		pList2->SetItemText(nCur,pos++,strText);
		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szBatch);//批次号
		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stHrUpDepart.szUpDepartName);//交检部门
		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szUpUser);//交检人
		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szUpDate);//交检日期

		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szCreateUser);//创建人//
		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szCreateDate);//创建时间//
		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szSendDate);//派工时间//
		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szDownLoadDate);//下载时间//
		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szFinishDate);//完成时间//

		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szCheckLeader);//检验组长
		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szCheckUser);//检验员姓名
		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szTechUser);//工艺员

		strText.Format(_T("%s"),GetTaskArmyText(pBasTaskInfo->stTaskBaseInfo.nArmyTest));//军检
		pList2->SetItemText(nCur,pos++,strText);

		strText.Format(_T("%d"),pBasTaskInfo->stTaskBaseInfo.nDianShiNum);//典试数量
		pList2->SetItemText(nCur,pos++,strText);

		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szAccording1);//验收依据1
		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szAccording2);//验收依据2
		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szAccording3);//验收依据3
		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szAccording4);//验收依据4
		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szAccording5);//验收依据5
		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szTaskRemark);//备注
		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szPlanBegTime);//计划开始时间
		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szPlanEndTime);//计划结束时间
		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szRealBegTime);//实际开始时间
		pList2->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szRealEndTime);//实际结束时间
	}
	
}
void CShowInfoList::ModifyOneTaskToList(int nIndex,StBasTask *pBasTaskInfo)
{
	CEditableListCtrl *pList2 = &m_ResultList.m_ResultList;

	CString strText;
	int nCount = 0,pos = 1;;
	nCount = pList2->GetItemCount();
	if(nIndex <0 || nIndex >= nCount)
	{
		return;
	}

	
	pList2->SetItemData(nIndex,pBasTaskInfo->stTaskBaseInfo.nOid);

	if(g_DebugShow)
	{
		pos = 1;

		strText.Format(_T("%s"), GetTaskStatus(pBasTaskInfo->stTaskBaseInfo.nTaskStatus));
		pList2->SetItemText(nIndex,pos++,strText);//任务状态
		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szTaskName);//任务名称
		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stProductInfo.szProductNo);//产品代号
		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szBatch);//批次号

		//strText.Format(_T("%d"),pBasTaskInfo->stTaskBaseInfo.nCodeNumber);//数量
		//pList2->SetItemText(nIndex,pos++,strText);
		//pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stProductInfo.szProductName);//产品名称

		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szModel);//产品型号
		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szPhase);//产品阶段

		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szCheckLeader);//检验组长
		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szCheckUser);//检验员姓名

		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stHrUpDepart.szUpDepartName);//交检部门

		pList2->SetItemText(nIndex,pos++, GetTaskArmyText(pBasTaskInfo->stTaskBaseInfo.nArmyTest) );//是否军检

		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szCreateDate);//创建时间//
		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szCreateUser);//创建人//
		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szSendDate);//派工时间//
		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szDownLoadDate);//下载时间//
		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szFinishDate);//完成时间//


		//strText.Format(_T("%s"), GetTaskStatus(pBasTaskInfo->stTaskBaseInfo.nTaskStatus));
		//pList2->SetItemText(nIndex,pos++,strText);//任务状态
		//pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szTaskName);//任务名称
		//pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stProductInfo.szProductNo);//产品代号
		//pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szBatch);//批次号

		//strText.Format(_T("%d"),pBasTaskInfo->stTaskBaseInfo.nCodeNumber);//数量
		//pList2->SetItemText(nIndex,pos++,strText);
		//pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stProductInfo.szProductName);//产品名称
		//pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szModel);//产品型号
		//pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szPhase);//产品阶段
		//pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stHrUpDepart.szUpDepartName);//交检部门

		//pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szCheckLeader);//检验组长
		//pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szCheckUser);//检验员姓名
		//pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szCreateDate);//创建时间//
		//pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szCreateUser);//创建人//
		//pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szSendDate);//派工时间//
		//pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szDownLoadDate);//下载时间//
		//pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szFinishDate);//完成时间//
	}else
	{
		pos = 1;
		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szTaskName);//任务名称
		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szProjectNo);//检验单号

		strText.Format(_T("%s"), GetTaskStatus(pBasTaskInfo->stTaskBaseInfo.nTaskStatus));
		pList2->SetItemText(nIndex,pos++,strText);//任务状态
		strText.Format(_T("%s"), GetTaskType(pBasTaskInfo->stTaskBaseInfo.nTaskType));
		pList2->SetItemText(nIndex,pos++,strText);//任务类型


		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szModel);//产品型号
		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szPhase);//产品阶段
		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stProductInfo.szProductNo);//产品代号

		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szProductCode);//产品编号
		strText.Format(_T("%d"),pBasTaskInfo->stTaskBaseInfo.nCodeNumber);//数量
		pList2->SetItemText(nIndex,pos++,strText);
		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szBatch);//批次号
		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stHrUpDepart.szUpDepartName);//交检部门
		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szUpUser);//交检人
		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szUpDate);//交检日期

		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szCreateUser);//创建人//
		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szCreateDate);//创建时间//
		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szSendDate);//派工时间//
		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szDownLoadDate);//下载时间//
		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szFinishDate);//完成时间//

		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szCheckLeader);//检验组长
		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szCheckUser);//检验员姓名
		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szTechUser);//工艺员

		strText.Format(_T("%s"),GetTaskArmyText(pBasTaskInfo->stTaskBaseInfo.nArmyTest));//军检
		pList2->SetItemText(nIndex,pos++,strText);

		strText.Format(_T("%d"),pBasTaskInfo->stTaskBaseInfo.nDianShiNum);//典试数量
		pList2->SetItemText(nIndex,pos++,strText);

		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szAccording1);//验收依据1
		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szAccording2);//验收依据2
		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szAccording3);//验收依据3
		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szAccording4);//验收依据4
		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szAccording5);//验收依据5
		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szTaskRemark);//备注
		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szPlanBegTime);//计划开始时间
		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szPlanEndTime);//计划结束时间
		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szRealBegTime);//实际开始时间
		pList2->SetItemText(nIndex,pos++,pBasTaskInfo->stTaskBaseInfo.szRealEndTime);//实际结束时间
	}
	
}
int CShowInfoList::DisPlayTaskInfo(StBasTask *pStBasTaskSearchInfo)
{
	CEditableListCtrl *pList2 = &m_ResultList.m_ResultList;
	
	m_ShowType = Show_Task;
	m_ResultList.m_ShowType = Show_Task;
	ChangeShowWindow(m_ShowType);
	ChangeTaskBtnShow(pStBasTaskSearchInfo);

	CString strTitle;
	strTitle.Format(_T("测试任务管理界面"));
	GetDlgItem(IDC_SHOWLIST_STATIC1)->SetWindowText(strTitle);

	int     i;
	CString	str;
	int     iColNum,iColNum1; 
	
	char	ItemName[35][30] = {"序号", "任务名称", "检验单号","任务状态","任务类型",
		"产品型号", "产品阶段","产品代号","产品编号","数量",
		"批次号","交检部门","交检人","交检日期","创建人",
		"创建日期","派工日期","下载日期","完成日期","检验组长",
		"检验员姓名","工艺员","军检","典试数量","验收依据1",
		"验收依据2","验收依据3","验收依据4","验收依据5","备注",
		"计划开始时间","计划结束时间","实际开始时间","实际结束时间"};
	int     ItemLen[40]      = {50,150,150,100,100, 100,100,150,100,100, 100,100,100,150,100,   
	 150,150,150,150,100, 100,100,100,100,100, 100,100,100,100,100,
	150,150,150, 150};

	char	ItemName1[35][30] = {
		"序号", 
		"任务状态",	"任务名称",	"产品代号",	_T("产品批次号"),
		"型号",		"阶段",		"检验组长",		"检验员",
		"交检部门",	"是否军检", "创建时间",	   "创建人",		
		"派工时间",	"执行时间",	"完成时间",};
	int     ItemLen1[40]      = {
		50,
		60,		100,	80,		80, 
		80,		80,		80,		80,
		100,	80,     120,	80,		
		120,	120,	120};

	ListCtrl_ClearAllColumn();
	iColNum = 34;
	iColNum1 = 16;

	if(g_DebugShow)
	{
		for (i=0; i<iColNum1; i++)
		{
			str.Format("%s", ItemName1[i]);
			pList2->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen1[i]);	
		}
	}else
	{
		for (i=0; i<iColNum; i++)
		{
			str.Format("%s", ItemName[i]);
			pList2->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen[i]);	
		}
	}
	

	//开始查找//
	//注意1.因为任务是基于产品的，产品是基于部门的 所以查询任务必须通过产品 因为任务没有部门属性//
	//    2.任务的交检部门和产品所属的部门不是同一个东西，产品所属的部门称之为 "组" 更为合适.
	//    3......
	int nRows = 0;
	char szSQL[1024] = {0};

	UINT nGroupOid = pStBasTaskSearchInfo->stHrGroup.nOid = g_CurSelDepart.nOid;
	UINT nProductOid = pStBasTaskSearchInfo->stProductInfo.nOid;
	int  nTaskStatus = pStBasTaskSearchInfo->stTaskBaseInfo.nTaskStatus;
	int  nTreeItemType = pStBasTaskSearchInfo->stTaskBaseInfo.TreeItemType;

	if(nGroupOid == 0)
	{
		return 1;
	}else 
	{
		int     i,nCount = 0;
		vector<StBasTask > nArrayTask;
		if(m_DMng.GetGroupTaskInfo (nGroupOid,pStBasTaskSearchInfo,&nArrayTask))
		{
			nCount = nArrayTask.size();
			for(i = 0;i<nCount;i++)
			{
				InsertOneTaskToList(&nArrayTask.at(i));
			}

			nArrayTask.clear();
		}
	}
	
	//显示结果信息//
	CString strText;
	StBasTaskBaseInfo *pTaskBaseInfo = &pStBasTaskSearchInfo->stTaskBaseInfo;
	int nPerPageNum = pTaskBaseInfo->nPerPageNum;
	int nResultNum = pTaskBaseInfo->nResultNum;
	int nCurPage = pTaskBaseInfo->nCurPage;
	int nPageNum = 1;
	int bFlag = 1;

	if(nPerPageNum == g_nSearchPerPageNum[All_Result])
	{

	}else
	{
		if( nResultNum%nPerPageNum >0)
		{
			nPageNum = (nResultNum/nPerPageNum)+1;
		}else
		{
			nPageNum = nResultNum/nPerPageNum;
		}
	}

	if (nPageNum<= 0)
	{
		nPageNum = 1;
	}

	if( nCurPage > nPageNum )
	{
		nCurPage = 1;
		bFlag = 0;
	}

	strText.Format(_T("共查询到 %d 条数据"), pTaskBaseInfo->nResultNum);
	m_ResultList.GetDlgItem(IDC_LIST_STATIC1)->SetWindowText(strText);
	strText.Format(_T("%d/%d"),nCurPage , nPageNum);
	m_ResultList.GetDlgItem(IDC_LIST_STATIC2)->SetWindowText(strText);

	//将结果反馈给 ResultList界面//
	StSearchSetInfo *pSearchSetInfo = &m_ResultList.m_stSearchSetInfo;
	pSearchSetInfo->nCurPage = nCurPage;
	pSearchSetInfo->nAimPage = nCurPage;
	pSearchSetInfo->nMaxPage = nPageNum;
	m_ResultList.SetBtnStatus();
	
	return bFlag;
}


void CShowInfoList::DisplayOneModeDescInfo()
{
	
	ChangeShowWindow(Show_OneMode);
	CString strTitle;
	strTitle.Format(_T("检验记录管理界面"));
	GetDlgItem(IDC_SHOWLIST_STATIC1)->SetWindowText(strTitle);
}
void CShowInfoList::DisplayOneTaskDescInfo()
{
	ChangeShowWindow(Show_OneTask);
	CString strTitle;
	strTitle.Format(_T("测试任务管理界面"));
	GetDlgItem(IDC_SHOWLIST_STATIC1)->SetWindowText(strTitle);
}
