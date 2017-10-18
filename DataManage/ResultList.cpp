// ResultList.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "ResultList.h"
#include "ProdMng.h"
#include "MainFrm.h"

// CResultList 对话框

IMPLEMENT_DYNAMIC(CResultList, CDialog)

CResultList::CResultList(CWnd* pParent /*=NULL*/)
	: CDialog(CResultList::IDD, pParent)
{
	m_pResultSearchNew = NULL;
	m_ShowType = Show_Product;
	memset(&m_stSearchSetInfo, 0,sizeof(StSearchSetInfo));
}

CResultList::~CResultList()
{
}

void CResultList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ResultList);
}


BEGIN_MESSAGE_MAP(CResultList, CDialog)
	ON_WM_SIZE()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CResultList::OnNMDblclkList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CResultList::OnNMRClickList1)
	ON_BN_CLICKED(IDC_FIRST_BTN, &CResultList::OnBnClickedFirstBtn)
	ON_BN_CLICKED(IDC_GOTO_BTN, &CResultList::OnBnClickedGotoBtn)
	ON_BN_CLICKED(IDC_TOP_BTN, &CResultList::OnBnClickedTopBtn)
	ON_BN_CLICKED(IDC_NEXT_BTN, &CResultList::OnBnClickedNextBtn)
	ON_BN_CLICKED(IDC_LAST_BTN, &CResultList::OnBnClickedLastBtn)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CResultList::OnNMClickList1)
END_MESSAGE_MAP()


// CResultList 消息处理程序

BOOL CResultList::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_ResultList.EnableRClickMenu(FALSE);
	InitPageNumComBox();
	SetBtnStatus();
	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CResultList::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnOK();
}

void CResultList::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	AutoSize();
}
void CResultList::InitPageNumComBox()
{
	CComboBox *pComBox = ((CComboBox *)GetDlgItem(IDC_PAGE_NUM_COMB));
	int i;
	pComBox->ResetContent();

	for (i = Five_Result;i<= All_Result;i++)
	{
		pComBox->AddString(g_szSearchPerPageNums[i]);
	}

	pComBox->SetCurSel(0);

}

void CResultList::GetPageNumComBox()
{
	CComboBox *pComBox = ((CComboBox *)GetDlgItem(IDC_PAGE_NUM_COMB));
	int nIndex, nCount;
	nIndex = pComBox->GetCurSel();
	nCount = pComBox->GetCount();
	if(nIndex < 0 || nIndex >= nCount)
	{
		nIndex = All_Result;
	}
	m_stSearchSetInfo.nPerPageNum = g_nSearchPerPageNum[nIndex];
}

void CResultList::SetBtnStatus()
{
	StSearchSetInfo *pSearchSetInfo = &m_stSearchSetInfo;
	int  nCurPage = pSearchSetInfo->nCurPage;
	int  nMaxPage = pSearchSetInfo->nMaxPage;
	if(nCurPage<=1)
	{
		GetDlgItem(IDC_TOP_BTN)->EnableWindow(FALSE);
	}else
	{
		GetDlgItem(IDC_TOP_BTN)->EnableWindow(TRUE);
	}

	if(nCurPage >= nMaxPage)
	{
		GetDlgItem(IDC_NEXT_BTN)->EnableWindow(FALSE);
	}else
	{
		GetDlgItem(IDC_NEXT_BTN)->EnableWindow(TRUE);
	}
}
void CResultList::AutoSize()
{
	CRect Rect ;
	GetClientRect(&Rect);

	int nBtnWidth = 60;
	int nBtnHeight = 25;


	int nStaticHeight = 22;
	int nPicNumHeight = 250;

	//产品模块//
	if(GetDlgItem(IDC_LIST_STATIC1)->GetSafeHwnd())
	{
		GetDlgItem(IDC_LIST_STATIC1)->MoveWindow(0,5,Rect.Width()-(0*2),Rect.Height()-(5*2));
	}

	if(m_ResultList.GetSafeHwnd())
	{
		m_ResultList.MoveWindow(3,5+20,Rect.Width()-(3*2),
			Rect.Height()-((5+20)+nBtnHeight+20));
	}

	if(GetDlgItem(IDC_LIST_STATIC3)->GetSafeHwnd())
	{
		GetDlgItem(IDC_LIST_STATIC3)->MoveWindow(Rect.right-(10+(nBtnWidth+10)*10),Rect.bottom-(nBtnHeight+5),nBtnWidth,nStaticHeight);
	}

	if(GetDlgItem(IDC_PAGE_NUM_COMB)->GetSafeHwnd())
	{
		GetDlgItem(IDC_PAGE_NUM_COMB)->MoveWindow(Rect.right-(10+(nBtnWidth+10)*9),Rect.bottom-(nBtnHeight+10),80,nBtnHeight*10);
	}


	
	if(GetDlgItem(IDC_LIST_STATIC2)->GetSafeHwnd())
	{
		GetDlgItem(IDC_LIST_STATIC2)->MoveWindow(Rect.right-(10+(nBtnWidth+10)*7),Rect.bottom-(nBtnHeight+5),nBtnWidth,nStaticHeight);
	}

	if(GetDlgItem(IDC_AIRM_EDT)->GetSafeHwnd())
	{
		GetDlgItem(IDC_AIRM_EDT)->MoveWindow(Rect.right-(10+(nBtnWidth+10)*6),Rect.bottom-(nBtnHeight+8),nBtnWidth,nStaticHeight);
	}

	if(GetDlgItem(IDC_GOTO_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_GOTO_BTN)->MoveWindow(Rect.right-(10+(nBtnWidth+10)*5),Rect.bottom-(nBtnHeight+10),nBtnWidth,nBtnHeight);
	}

	
	if(GetDlgItem(IDC_FIRST_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_FIRST_BTN)->MoveWindow(Rect.right-(10+(nBtnWidth+10)*4),Rect.bottom-(nBtnHeight+10),nBtnWidth,nBtnHeight);
	}

	if(GetDlgItem(IDC_TOP_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_TOP_BTN)->MoveWindow(Rect.right-(10+(nBtnWidth+10)*3),Rect.bottom-(nBtnHeight+10),nBtnWidth,nBtnHeight);
	}

	if(GetDlgItem(IDC_NEXT_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_NEXT_BTN)->MoveWindow(Rect.right-(10+(nBtnWidth+10)*2),Rect.bottom-(nBtnHeight+10),nBtnWidth,nBtnHeight);
	}

	if(GetDlgItem(IDC_LAST_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_LAST_BTN)->MoveWindow(Rect.right-(10+(nBtnWidth+10)*1),Rect.bottom-(nBtnHeight+10),nBtnWidth,nBtnHeight);
	}
}

void CResultList::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码//

	int ret = 0;
	int i, nIndex,nCount;
	CString strText, str;
	vector<CString> strErrorArray;
	CEditableListCtrl *pList = &m_ResultList;
	nIndex = pList->GetFirstSelectedItem();
	nCount = pList->GetItemCount();

	if(nIndex <0 || nIndex >= nCount)
	{
		return;
	}

	

	int nUserType = g_LoginUsrInfo.nUserType;
	//双击查看产品信息//
	if(m_ShowType == Show_Product)
	{
		
		UINT nProductOid = m_ResultList.GetItemData(nIndex);
		CProdMng nProdMng;
		if(!m_DMng.GetProdDataOid(nProductOid,&nProdMng.m_CurProdInfo))
		{
			return;
		}
		if(nUserType == user_normal)
		{
			nProdMng.m_ShowType = View_Product;
			if(nProdMng.DoModal() == IDOK)
			{

			}
		}else
		{
			nProdMng.m_ShowType = Modify_Product;
			if(nProdMng.DoModal() == IDOK)
			{
				//nProdMng.m_ProductInfo.GetProdInfo();
				
				ret = ModifyTheProd(&nProdMng.m_CurProdInfo);
				if(ret == 1)
				{
					g_pShowInfoList->ModifyOneProdToList(nIndex,&nProdMng.m_CurProdInfo);
				}
				
			}
		}
		return;
		
		
	}


	//双击查看模板信息//

	if(m_ShowType == Show_Mode)
	{
		UINT nModeOid = m_ResultList.GetItemData(nIndex);
		CModeMng     nModeMng;//模板//
		
		StBasMode    *pModeInfo = &nModeMng.m_ShowModeInfo.m_CurModeInfo;
		pModeInfo->Release();
		memset(pModeInfo, 0, sizeof(StBasMode));
		if(!m_DMng.GetModeDataOid(nModeOid,&nModeMng.m_ShowModeInfo.m_CurModeInfo))
		{
			return;
		}
		

		if(nUserType == user_normal)
		{
			nModeMng.m_ShowType=View_Mode;
			if(nModeMng.DoModal() == IDOK)
			{

			}
			
		}else
		{
			nModeMng.m_ShowType = Modify_Mode;
			if(nModeMng.DoModal() == IDOK)
			{
				ret = ModifyTheMode(pModeInfo);
				if(ret == 1)
				{
					g_pShowInfoList->ModifyOneModeToList(nIndex,pModeInfo);
				}
			}
		}
		return ;
	}

	//双击查看任务信息//
	if(m_ShowType == Show_Task)
	{

		UINT nTaskOid = m_ResultList.GetItemData(nIndex);
		CTaskMng  nTaskMng;//检查任务//
		StBasTask *pTaskInfo = &nTaskMng.m_ShowTaskInfo.m_CurTaskInfo;
		pTaskInfo->Release();
		if(!m_DMng.GetTaskDataOid(nTaskOid,pTaskInfo))
		{
			return;
		}
		
		if(nUserType == user_normal)
		{
			nTaskMng.m_ShowType = View_Task;
			if(nTaskMng.DoModal() == IDOK)
			{

			}
		}else
		{
			if(pTaskInfo->stTaskBaseInfo.nTaskStatus == Task_Init)
			{
				nTaskMng.m_ShowType = Modify_Task;
				if(nTaskMng.DoModal() == IDOK)
				{
					//nTaskMng.m_ShowTaskInfo.GetChangeTaskInfo();
					ret = ModifyTheTask(pTaskInfo,strErrorArray);
					if(ret == 1)
					{
						g_pShowInfoList->ModifyOneTaskToList(nIndex,pTaskInfo);
					}
					g_MainFram->m_wndOutput.InsertErrorArrayText(strErrorArray);

					nCount = strErrorArray.size();
					for (i = 0;i<nCount;i++)
					{
						str.Format(_T("%d.%s\n"), i+1, strErrorArray.at(i));
						strText+=str;
					}

					strErrorArray.clear();
					AfxMessageBox(strText);
				}
			}else
			{
				nTaskMng.m_ShowType = View_Task;
				if(nTaskMng.DoModal() == IDOK)
				{

				}
			}
			
		}
		return;
	}

	//双击查看结果附件的信息//
	if(m_ShowType == Show_Result)
	{

		//是否是结果附件表的列表显示//
		if(m_SmallType == Result_Atta)
		{
			m_pResultSearchNew->ShowAttaData();
		}
	}


	*pResult = 0;
}
void CResultList::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	int i, nCount, Index;
	CString strText;

	//单击查看任务项信息//
	if(m_ShowType == Show_Result)
	{

		//是否是任务基础表的列表显示//
		if(m_SmallType == Result_Task)
		{
			nCount = m_ResultList.GetItemCount();
			Index = m_ResultList.GetFirstSelectedItem();

			if(Index < 0 || Index >= nCount)
			{
				return ;
			}

			UINT nBaseOid = m_ResultList.GetItemData(Index);
			UINT nGroupOid = g_CurSelDepart.nOid;
			vector<StTstResultAtta> stResultAttachArray;

			if(!m_DMng.GetTstResultAttaBaseOid(nGroupOid,nBaseOid,&stResultAttachArray))
			{
				return ;
			}

			
			m_pResultSearchNew->m_TstRresultAttaList.DeleteAllItems();

			nCount = stResultAttachArray.size();
			strText.Format(_T("共查询到 %d 条结果数据"), nCount);
			m_pResultSearchNew->GetDlgItem(IDC_STATIC3)->SetWindowText(strText);
			for (i = 0;i<nCount;i++)
			{
				m_pResultSearchNew->InsertResultAttachToList(&stResultAttachArray.at(i));
			}

			stResultAttachArray.clear();

		}
	}


	*pResult = 0;
}
void CResultList::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	//单击查看任务项信息//
	if(m_ShowType == Show_Result)
	{

		//是否是任务基础表的列表显示//
		if(m_SmallType == Result_Task)
		{
			m_pResultSearchNew->Menu1Fuction();
		}else if(m_SmallType == Result_Atta)
		{
			m_pResultSearchNew->Menu2Fuction();
		}
	}
	*pResult = 0;
}


//转到目标页//
void CResultList::OnBnClickedGotoBtn()
{
	// TODO: 在此添加控件通知处理程序代码//

	StSearchSetInfo *pSearchSetInfo = &m_stSearchSetInfo;
	CString strAimPage;
	int    nAimPage = 1;
	GetDlgItem(IDC_AIRM_EDT)->GetWindowText(strAimPage);
	nAimPage = atoi(strAimPage);
	if(nAimPage<=0)
	{
		nAimPage = 1;
	}

	if(nAimPage > pSearchSetInfo->nMaxPage)
	{
		CString str;
		str.Format("Err,输入页码超出范围! 当前页码=%d, 最大页码=%d", nAimPage, pSearchSetInfo->nMaxPage);
		AfxMessageBox(str);
		return;
	}

	pSearchSetInfo->nAimPage = nAimPage;

	switch(m_ShowType)
	{
	case Show_Product:
		{
			g_pShowInfoList->m_ProductSearch.OnBnClickedSearchBtn();
		}
		break;
	case Show_Mode:
		{
			g_pShowInfoList->m_ModeSearch.OnBnClickedSearchBtn();
		}
		break;
	case Show_Task:
		{
			g_pShowInfoList->m_TaskSearch.OnBnClickedTaskSearchBtn();
		}
		break;
	case Show_Result:
		{
			m_pResultSearchNew->m_ResultSearchInfoDlg.OnBnClickedButton1();
			break;
		}
	}

}

//首页//
void CResultList::OnBnClickedFirstBtn()
{
	// TODO: 在此添加控件通知处理程序代码//

	StSearchSetInfo *pSearchSetInfo = &m_stSearchSetInfo;

	if(pSearchSetInfo->nCurPage<=1)
	{
		return;
	}

	pSearchSetInfo->nAimPage = 1;

	switch(m_ShowType)
	{
	case Show_Product:
		{
			g_pShowInfoList->m_ProductSearch.OnBnClickedSearchBtn();
		}
		break;
	case Show_Mode:
		{
			g_pShowInfoList->m_ModeSearch.OnBnClickedSearchBtn();
		}
		break;
	case Show_Task:
		{
			g_pShowInfoList->m_TaskSearch.OnBnClickedTaskSearchBtn();
			break;
		}
	case Show_Result:
		{
			m_pResultSearchNew->m_ResultSearchInfoDlg.OnBnClickedButton1();
			break;
		}
		
	}

}


//上一页//
void CResultList::OnBnClickedTopBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	StSearchSetInfo *pSearchSetInfo = &m_stSearchSetInfo;

	if(pSearchSetInfo->nCurPage<=1)
	{
		return;
	}

	pSearchSetInfo->nAimPage--;
	//pSearchSetInfo->nCurPage--;

	switch(m_ShowType)
	{
	case Show_Product:
		{
			g_pShowInfoList->m_ProductSearch.OnBnClickedSearchBtn();
		}
		break;
	case Show_Mode:
		{
			g_pShowInfoList->m_ModeSearch.OnBnClickedSearchBtn();
		}
		break;
	case Show_Task:
		{
			g_pShowInfoList->m_TaskSearch.OnBnClickedTaskSearchBtn();
		}
		break;
	case Show_Result:
		{
			m_pResultSearchNew->m_ResultSearchInfoDlg.OnBnClickedButton1();
			break;
		}
	}
}
//下一页//
void CResultList::OnBnClickedNextBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	StSearchSetInfo *pSearchSetInfo = &m_stSearchSetInfo;

	if(pSearchSetInfo->nCurPage>=pSearchSetInfo->nMaxPage)
	{
		return;
	}

	pSearchSetInfo->nAimPage++;
	//pSearchSetInfo->nCurPage++;

	switch(m_ShowType)
	{
	case Show_Product:
		{
			g_pShowInfoList->m_ProductSearch.OnBnClickedSearchBtn();
		}
		break;
	case Show_Mode:
		{
			g_pShowInfoList->m_ModeSearch.OnBnClickedSearchBtn();
		}
		break;
	case Show_Task:
		{
			g_pShowInfoList->m_TaskSearch.OnBnClickedTaskSearchBtn();
		}
		break;
	case Show_Result:
		{
			m_pResultSearchNew->m_ResultSearchInfoDlg.OnBnClickedButton1();
			break;
		}
	}

}

//末页//
void CResultList::OnBnClickedLastBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	StSearchSetInfo *pSearchSetInfo = &m_stSearchSetInfo;

	if(pSearchSetInfo->nCurPage>=pSearchSetInfo->nMaxPage)
	{
		return;
	}

	pSearchSetInfo->nAimPage = pSearchSetInfo->nMaxPage;
	//pSearchSetInfo->nCurPage = pSearchSetInfo->nMaxPage;

	switch(m_ShowType)
	{
	case Show_Product:
		{
			g_pShowInfoList->m_ProductSearch.OnBnClickedSearchBtn();
		}
		break;
	case Show_Mode:
		{
			g_pShowInfoList->m_ModeSearch.OnBnClickedSearchBtn();
		}
		break;
	case Show_Task:
		{
			g_pShowInfoList->m_TaskSearch.OnBnClickedTaskSearchBtn();
		}
		break;
	case Show_Result:
		{
			m_pResultSearchNew->m_ResultSearchInfoDlg.OnBnClickedButton1();
			break;
		}
	}
}


