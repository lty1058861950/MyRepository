// ResultSearchNew.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "ResultSearchNew.h"
#include "WordSrc\\WordOptFun.h"
#include "AdjustmentDlg.h"

// CResultSearchNew 对话框
IMPLEMENT_DYNAMIC(CResultSearchNew, CDialog)

CResultSearchNew::CResultSearchNew(CWnd* pParent /*=NULL*/)
	: CDialog(CResultSearchNew::IDD, pParent)
{
	m_ResultSearchInfo.Release();
	m_ResultSearchInfo.stTaskBaseInfo.nResultType = Task_DarkSearch;

	memset(&m_CurSelResultAtta, 0, sizeof(StTstResultAtta));
}

CResultSearchNew::~CResultSearchNew()
{
	m_ResultSearchInfo.Release();
}

void CResultSearchNew::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_TstRresultBaseList);
	DDX_Control(pDX, IDC_LIST2, m_TstRresultAttaList);
}


BEGIN_MESSAGE_MAP(CResultSearchNew, CDialog)
	ON_WM_SIZE()
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CResultSearchNew::OnNMClickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &CResultSearchNew::OnNMDblclkList2)

	ON_COMMAND(ID_MENU1_DELDATA_BASE_NEW, &CResultSearchNew::DelBaseDataNew)


	ON_COMMAND(ID_MENU1_C_TASK_REPORT_BASE_NEW, &CResultSearchNew::CreateTaskReportNew)
	ON_COMMAND(ID_MENU1_C_PRODUCT_REPORT_ATTA_NEW, &CResultSearchNew::CreateProductCodeReportNew)
	ON_COMMAND(ID_MENU1_C_MODE_REPORT_ATTA_NEW, &CResultSearchNew::CreateModeReportNew)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CResultSearchNew::OnNMRClickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST2, &CResultSearchNew::OnNMRClickList2)
END_MESSAGE_MAP()


// CResultSearchNew 消息处理程序

BOOL CResultSearchNew::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_ResultSearchInfoDlg.Create(IDD_RESULT_SEARCH_INFO_DLG, this);
	m_ResultSearchInfoDlg.ShowWindow(SW_SHOW);

	m_ResultTaskBase.Create(IDD_RESULT_LIST_DLG, this);
	m_ResultTaskBase.ShowWindow(SW_SHOW);
	m_ResultAttach.Create(IDD_RESULT_LIST_DLG, this);
	m_ResultAttach.ShowWindow(SW_SHOW);

	m_ResultSearchInfoDlg.m_pResultSearchNew = this;
	m_ResultTaskBase.m_pResultSearchNew = this;
	m_ResultAttach.m_pResultSearchNew = this;

	InitPopMenu1( );
	InitPopMenu2( );

	InitListCtrlColumn();
	SetContrlShow();
	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CResultSearchNew::InitListCtrlColumn()
{
	CEditableListCtrl *pList1 = &m_TstRresultBaseList;
	CEditableListCtrl *pList2 = &m_TstRresultAttaList;
	CEditableListCtrl *pList3 = &m_ResultTaskBase.m_ResultList;
	CEditableListCtrl *pList4 = &m_ResultAttach.m_ResultList;

	int     i;
	CString	str;
	int     iColNum1; 
	char	ItemName1[20][30] = {"序号",_T("下发日期"),_T("导入日期"),_T("任务名称"),_T("产品代号"),
		_T("产品名称"),_T("检查人")};
	int     ItemLen1[20]      = {50,150,150,100,100,  100,100};

	iColNum1 = 7;
	for (i=0; i<iColNum1; i++)
	{
		str.Format("%s", ItemName1[i]);
		pList1->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen1[i]);
		pList3->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen1[i]);
	}

	pList1->EnableRClickMenu(FALSE);

	int     iColNum2; 
	char	ItemName2[20][30] = {"序号","下发日期","导入日期","任务名称","产品代号",
		"产品编号",_T("模板名称"),_T("是否典试"),_T("模板类型"),_T("模板行可变"),
		_T("图号数量"),_T("完成进度(百分比)"),_T("完成状态"),_T("完成时间"),_T("检查人")};
	int     ItemLen2[20]      = {50,150,150,100,100,   100,100,100,100,100,   100,100,100,150,100};

	iColNum2 = 15;
	for (i=0; i<iColNum2; i++)
	{
		str.Format("%s", ItemName2[i]);
		pList2->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen2[i]);
		pList4->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen2[i]);
	}

	pList2->EnableRClickMenu(FALSE);


	//将列表的显示类型页在此初始化了//
	m_ResultTaskBase.m_ShowType = Show_Result;
	m_ResultAttach.m_ShowType = Show_Result;
}


void CResultSearchNew::InsertTaskBaseDataToList(StTstResultBaseNew *pTaskBaseData)
{
	CEditableListCtrl *pList1 = NULL;
	CString str;
	int nCount, pos;
	StBasTaskBaseInfo *pTaskBaseInfo = &pTaskBaseData->stTaskInfo.stTaskBaseInfo;
	StBasProduct *pProductInfo = &pTaskBaseData->stTaskInfo.stProductInfo;
	StHrUpDepart *pUpDepartInfo = &pTaskBaseData->stTaskInfo.stHrUpDepart;

	int nResultSearchType = m_ResultSearchInfo.stTaskBaseInfo.nResultType;

	if(nResultSearchType == Task_DarkSearch)//基于任务 模糊查询//
	{
		pList1 = &m_ResultTaskBase.m_ResultList;
		
	}else if(nResultSearchType == Task_ExactSearch)//基于任务精确查找//
	{
		pList1 = &m_TstRresultBaseList;
	}

	if(pList1 == NULL)
	{
		return;
	}

	pos = 1;
	nCount = pList1->GetItemCount();
	str.Format(_T("%d"), nCount+1);
	pList1->InsertItem(nCount, str);
	pList1->SetItemData(nCount, pTaskBaseData->nOid);
	pList1->SetItemText(nCount, pos++, pTaskBaseInfo->szSendDate);
	pList1->SetItemText(nCount, pos++, pTaskBaseInfo->szImportDate);
	pList1->SetItemText(nCount, pos++, pTaskBaseInfo->szTaskName);
	pList1->SetItemText(nCount, pos++, pProductInfo->szProductNo);
	pList1->SetItemText(nCount, pos++, pProductInfo->szProductName);
	pList1->SetItemText(nCount, pos++, pTaskBaseInfo->szCheckUser);
	

}
void CResultSearchNew::InsertResultAttachToList(StTstResultAtta    *pResultAttachData)
{
	CEditableListCtrl *pList1 = NULL;
	CString str;
	int nCount, pos, n;

	int nResultSearchType = m_ResultSearchInfo.stTaskBaseInfo.nResultType;
	
	if(nResultSearchType == Task_DarkSearch)//基于任务 模糊查询//
	{
		pList1 = &m_TstRresultAttaList;

	}else if(nResultSearchType == Task_ExactSearch)//基于任务精确查找//
	{
		pList1 = &m_TstRresultAttaList;
	}else if(nResultSearchType == Result_Search)      //结果查询//
	{
		pList1 = &m_ResultAttach.m_ResultList;
	}

	if(pList1 == NULL)
	{
		return;
	}
	
	pos = 1;
	nCount = pList1->GetItemCount();
	str.Format(_T("%d"),nCount+1);
	pList1->InsertItem(nCount,str);
	pList1->SetItemData(nCount,pResultAttachData->nOid);
	pList1->SetItemText(nCount,pos++,pResultAttachData->szSendDate);
	pList1->SetItemText(nCount,pos++,pResultAttachData->szImportDate);
	pList1->SetItemText(nCount,pos++,pResultAttachData->szTaskName);
	pList1->SetItemText(nCount,pos++,pResultAttachData->szProductNo);

	pList1->SetItemText(nCount,pos++,pResultAttachData->szProductCode);
	pList1->SetItemText(nCount,pos++,pResultAttachData->szModeName);

	pList1->SetItemText(nCount,pos++,GetDianshiText(pResultAttachData->nDianshiTest));
	pList1->SetItemText(nCount,pos++,GetModeType(pResultAttachData->nModeType));

	n = pResultAttachData->nModeRowVar;
	pList1->SetItemText(nCount,pos++,GetModeRowVar(n));
	if(n == ModeRow_Change)
	{
		str.Format(_T("%d"), pResultAttachData->nPicNumCount);
		pList1->SetItemText(nCount,pos,str);
	}
	pos++;
	str.Format(_T("%d%%"), pResultAttachData->nPercent);
	pList1->SetItemText(nCount,pos++,str);
	str.Format(_T("%d"), pResultAttachData->bFinished);
	pList1->SetItemText(nCount,pos++,str);
	pList1->SetItemText(nCount,pos++,pResultAttachData->szFinishedTime);
	pList1->SetItemText(nCount,pos++,pResultAttachData->szCheckUser);
}
void CResultSearchNew::SetContrlShow()
{
	CString strText;
	int nCount = 0;
	int nResultSearchType = m_ResultSearchInfo.stTaskBaseInfo.nResultType;

	strText.Format(_T("共查询到 %d 条任务数据"),nCount);
	GetDlgItem(IDC_STATIC2)->SetWindowText(strText);
	m_ResultTaskBase.GetDlgItem(IDC_LIST_STATIC1)->SetWindowText(strText);

	strText.Format(_T("共查询到 %d 条结果数据"),nCount);
	GetDlgItem(IDC_STATIC3)->SetWindowText(strText);
	m_ResultAttach.GetDlgItem(IDC_LIST_STATIC1)->SetWindowText(strText);



	switch(nResultSearchType)
	{
	case Task_DarkSearch://1.基于任务的模糊查询//
		{
			GetDlgItem(IDC_STATIC1)->SetWindowText(_T("结果查询界面"));

			GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC3)->ShowWindow(SW_SHOW);
			m_TstRresultBaseList.ShowWindow(SW_HIDE);
			m_TstRresultAttaList.ShowWindow(SW_SHOW);

			m_ResultTaskBase.ShowWindow(SW_SHOW);
			m_ResultAttach.ShowWindow(SW_HIDE);

			m_ResultTaskBase.m_SmallType = Result_Task;

			//设置查询条件控件的状态//
			((CEdit*)(m_ResultSearchInfoDlg.GetDlgItem(IDC_EDIT1)))->SetReadOnly(FALSE);
			((CEdit*)(m_ResultSearchInfoDlg.GetDlgItem(IDC_EDIT2)))->SetReadOnly(FALSE);
			(m_ResultSearchInfoDlg.GetDlgItem(IDC_BUTTON2))->EnableWindow(TRUE);
			((m_ResultSearchInfoDlg.GetDlgItem(IDC_STATIC4)))->ShowWindow(FALSE);
			((m_ResultSearchInfoDlg.GetDlgItem(IDC_EDIT5)))->ShowWindow(FALSE);
		}
		break;
	case Task_ExactSearch://2.基于任务的精确查询
		{
			GetDlgItem(IDC_STATIC1)->SetWindowText(_T(""));

			GetDlgItem(IDC_STATIC2)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC3)->ShowWindow(SW_SHOW);
			m_TstRresultBaseList.ShowWindow(SW_SHOW);
			m_TstRresultAttaList.ShowWindow(SW_SHOW);

			m_ResultTaskBase.ShowWindow(SW_HIDE);
			m_ResultAttach.ShowWindow(SW_HIDE);

			m_ResultTaskBase.m_SmallType = Result_Task;

			//设置查询条件控件的状态//
			((CEdit*)(m_ResultSearchInfoDlg.GetDlgItem(IDC_EDIT1)))->SetReadOnly(TRUE);
			((CEdit*)(m_ResultSearchInfoDlg.GetDlgItem(IDC_EDIT2)))->SetReadOnly(TRUE);
			(m_ResultSearchInfoDlg.GetDlgItem(IDC_BUTTON2))->EnableWindow(FALSE);
			((m_ResultSearchInfoDlg.GetDlgItem(IDC_STATIC4)))->ShowWindow(FALSE);
			((m_ResultSearchInfoDlg.GetDlgItem(IDC_EDIT5)))->ShowWindow(FALSE);
		}
		break;
	case Result_Search://3.结果数据查询
		{
			GetDlgItem(IDC_STATIC1)->SetWindowText(_T("结果查询界面"));
			GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC3)->ShowWindow(SW_HIDE);

			m_TstRresultBaseList.ShowWindow(SW_HIDE);
			m_TstRresultAttaList.ShowWindow(SW_HIDE);

			m_ResultTaskBase.ShowWindow(SW_HIDE);
			m_ResultAttach.ShowWindow(SW_SHOW);

			m_ResultAttach.m_SmallType = Result_Atta;

			//设置查询条件控件的状态//
			((CEdit*)(m_ResultSearchInfoDlg.GetDlgItem(IDC_EDIT1)))->SetReadOnly(FALSE);
			((CEdit*)(m_ResultSearchInfoDlg.GetDlgItem(IDC_EDIT2)))->SetReadOnly(FALSE);
			(m_ResultSearchInfoDlg.GetDlgItem(IDC_BUTTON2))->EnableWindow(TRUE);
			((m_ResultSearchInfoDlg.GetDlgItem(IDC_STATIC4)))->ShowWindow(TRUE);
			((m_ResultSearchInfoDlg.GetDlgItem(IDC_EDIT5)))->ShowWindow(TRUE);
		}
		break;
	}
}


int CResultSearchNew::SearchResultData()
{
	int i, nCount;
	m_TstRresultBaseList.DeleteAllItems();
	m_TstRresultAttaList.DeleteAllItems();
	m_ResultTaskBase.m_ResultList.DeleteAllItems();
	m_ResultAttach.m_ResultList.DeleteAllItems();
	PostMessage(WM_SIZE);
	SetContrlShow();

	int nResultSearchType = m_ResultSearchInfo.stTaskBaseInfo.nResultType;

	m_ResultSearchInfoDlg.GetSearchInfo();//获取查询条件//


	vector<StTstResultBaseNew>  stTaskBaseDataArray;
	vector<StTstResultAtta>     stResultAttachArray;
	switch(nResultSearchType)
	{
	case Task_DarkSearch://基于任务 模糊查询//
		{
			m_ResultTaskBase.GetPageNumComBox();//获取页数和目标页//
			if(!m_DMng.GetGroupTstResultBaseData(&m_ResultSearchInfo,&stTaskBaseDataArray))
			{
				return 0;
			}
			nCount = stTaskBaseDataArray.size();
			for (i = 0;i<nCount; i++)
			{
				InsertTaskBaseDataToList(&stTaskBaseDataArray.at(i));

				stTaskBaseDataArray.at(i).Release();
			}
			stTaskBaseDataArray.clear();

		}
		break; 
	case Task_ExactSearch://基于任务精确查找//
		{
			m_ResultTaskBase.GetPageNumComBox();//获取页数和目标页//
			if(!m_DMng.GetTaskTstResultBaseData(&m_ResultSearchInfo,&stTaskBaseDataArray))
			{
				return 0;
			}
			nCount = stTaskBaseDataArray.size();
			for (i = 0;i<nCount; i++)
			{
				InsertTaskBaseDataToList(&stTaskBaseDataArray.at(i));

				stTaskBaseDataArray.at(i).Release();
			}
			stTaskBaseDataArray.clear();
		}
		break;
	case Result_Search:
		{
			m_ResultAttach.GetPageNumComBox();//获取页数和目标页//
			if(!m_DMng.GetGroupTstResultAttachData(&m_ResultSearchInfo,&stResultAttachArray))
			{
				return 0;
			}

			nCount = stResultAttachArray.size();
			for (i = 0;i<nCount; i++)
			{
				InsertResultAttachToList(&stResultAttachArray.at(i));

			}
			stResultAttachArray.clear();
			
		}
		break;
	}

	//将结果反馈到界面上//

	CString strText;
	//显示结果信息//
	int nPerPageNum = m_ResultSearchInfo.stTaskBaseInfo.nPerPageNum;
	int nResultNum = m_ResultSearchInfo.stTaskBaseInfo.nResultNum;
	int nCurPage = m_ResultSearchInfo.stTaskBaseInfo.nCurPage;
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

	if(nPageNum<= 0)
	{
		nPageNum = 1;
	}

	if( nCurPage > nPageNum )
	{
		nCurPage = 1;
		bFlag = 2;
	}

	CResultList *pResList = NULL;
	StSearchSetInfo *pSearchSetInfo = NULL;
	switch(nResultSearchType)
	{
	case Task_DarkSearch://基于任务 模糊查询//
		{
			pResList = &m_ResultTaskBase;
		}
		break; 
	case Task_ExactSearch://基于任务精确查找//
		{
			pResList = NULL;


		}
		break;
	case Result_Search:
		{
			pResList = &m_ResultAttach;

		}
		break;
	}

	switch(nResultSearchType)
	{
	case Task_DarkSearch://基于任务 模糊查询//
		{
			strText.Format(_T("共查询到 %d 条任务数据"), m_ResultSearchInfo.stTaskBaseInfo.nResultNum);
			pResList->GetDlgItem(IDC_LIST_STATIC1)->SetWindowText(strText);
			strText.Format(_T("%d/%d"),nCurPage , nPageNum);
			pResList->GetDlgItem(IDC_LIST_STATIC2)->SetWindowText(strText);
			break;
		}
	case Result_Search:
		{
			strText.Format(_T("共查询到 %d 条结果数据"), m_ResultSearchInfo.stTaskBaseInfo.nResultNum);
			pResList->GetDlgItem(IDC_LIST_STATIC1)->SetWindowText(strText);
			strText.Format(_T("%d/%d"),nCurPage , nPageNum);
			pResList->GetDlgItem(IDC_LIST_STATIC2)->SetWindowText(strText);
			break;
		}
		
	case Task_ExactSearch://基于任务精确查找//
		{
			strText.Format(_T("共查询到 %d 条任务数据"), m_ResultSearchInfo.stTaskBaseInfo.nResultNum);
			GetDlgItem(IDC_STATIC2)->SetWindowText(strText);
		}
		break;
	}

	

	//将结果反馈给 ResultList界面//
	
	if(pResList != NULL)
	{
		pSearchSetInfo = &pResList->m_stSearchSetInfo;
		pSearchSetInfo->nCurPage = nCurPage;
		pSearchSetInfo->nAimPage = nCurPage;
		pSearchSetInfo->nMaxPage = nPageNum;
		pResList->SetBtnStatus();
	}
	

	return bFlag;
}

BOOL CResultSearchNew::GetCurSelAttaData()
{
	CEditableListCtrl *pList1 = NULL;
	int t1,t2;
	CString str;
	t1= GetTickCount();

	DelFile();

	int nResultSearchType = m_ResultSearchInfo.stTaskBaseInfo.nResultType;
	if(nResultSearchType == Task_DarkSearch)//基于任务 模糊查询//
	{
		pList1 = &m_TstRresultAttaList;

	}else if(nResultSearchType == Task_ExactSearch)//基于任务精确查找//
	{
		pList1 = &m_TstRresultAttaList;
	}else if(nResultSearchType == Result_Search)      //结果查询//
	{
		pList1 = &m_ResultAttach.m_ResultList;
	}

	if(pList1 == NULL)
	{
		return FALSE;
	}
	int Index = pList1->GetFirstSelectedItem(), nCount = pList1->GetItemCount();
	if(Index<0 || Index >= nCount)
		return FALSE;
	//组建查询条件//
	UINT nAttaOid = pList1->GetItemData(Index);
	UINT nGroupOid = g_CurSelDepart.nOid;

	memset(&m_CurSelResultAtta, 0, sizeof(StTstResultAtta));
	if(!m_DMng.GetTstResultOid(nGroupOid,nAttaOid,&m_CurSelResultAtta))
	{
		return FALSE;
	}else
	{
		if(!m_DMng.GetAttaXmlFile(nGroupOid,nAttaOid))
		{
			return FALSE;
		}
	}

	t2 = GetTickCount()-t1;
	str.Format(_T("CResultSearch::ShowCurData 用时 %d 毫秒"),t2);
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));
	return TRUE;
}

int CResultSearchNew::ShowAttaData()
{
	if(GetCurSelAttaData())
	{
		CResultShow ndlg;
		ndlg.m_pCurAttaInfo = &m_CurSelResultAtta;
		ndlg.DoModal();
	}
	this->InvalidateRect(NULL);

	return 1;
}


void CResultSearchNew::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnOK();
}

void CResultSearchNew::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	AutoSize();
}

void CResultSearchNew::AutoSize()
{
	CRect Rect ;
	GetClientRect(&Rect) ;

	

	int nSearchHeight = 120;
	int nListHeight = (Rect.Height()-(nSearchHeight+20+10+20+10+25*2))/2;

	int nGroupStaticpos = 5;
	int nSearchpos = nGroupStaticpos+20;

	int nGroupList1pos = nSearchpos+nSearchHeight+10;
	int nList1pos = nGroupList1pos+20;

	int nGroupList2pos = nList1pos+nListHeight+20;
	int nList2pos = nGroupList2pos+20;


	//1.
	if (GetDlgItem(IDC_STATIC1)->GetSafeHwnd())
	{
		GetDlgItem(IDC_STATIC1)->MoveWindow(1,
			nGroupStaticpos,Rect.Width()-1*2,Rect.Height()-(nGroupStaticpos*2));
	}




	//2.查询条件
	if(m_ResultSearchInfoDlg.GetSafeHwnd())
	{
		m_ResultSearchInfoDlg.MoveWindow(5, nSearchpos, Rect.Width()-(2*5), nSearchHeight);
	}


	int nResultSearchType = m_ResultSearchInfo.stTaskBaseInfo.nResultType;

	if(nResultSearchType == Result_Search)
	{
		if(m_ResultTaskBase.GetSafeHwnd())
		{
			m_ResultTaskBase.MoveWindow(5,nGroupList1pos,Rect.Width()-(5*2),nListHeight+25);
		}
		if(m_ResultAttach.GetSafeHwnd())
		{
			m_ResultAttach.MoveWindow(5,nGroupList1pos,Rect.Width()-(5*2),(nListHeight+25)*2);
		}
	}else
	{
		if(m_ResultTaskBase.GetSafeHwnd())
		{
			m_ResultTaskBase.MoveWindow(5,nGroupList1pos,Rect.Width()-(5*2),nListHeight+25);
		}
		if(m_ResultAttach.GetSafeHwnd())
		{
			m_ResultAttach.MoveWindow(5,nGroupList2pos,Rect.Width()-(5*2),nListHeight+25);
		}
	}
	//3.任务List 框
	if (GetDlgItem(IDC_STATIC2)->GetSafeHwnd())
	{
		GetDlgItem(IDC_STATIC2)->MoveWindow(5,nGroupList1pos,Rect.Width()-(5*2),nListHeight+25);
	}
	if(m_TstRresultBaseList.GetSafeHwnd())
	{
		m_TstRresultBaseList.MoveWindow(5+5,nList1pos,Rect.Width()-((5+5)*2),nListHeight);
	}

	//4.任务项 List 框
	if (GetDlgItem(IDC_STATIC3)->GetSafeHwnd())
	{
		GetDlgItem(IDC_STATIC3)->MoveWindow(5,nGroupList2pos,Rect.Width()-(5*2),nListHeight+25);
	}
	if(m_TstRresultAttaList.GetSafeHwnd())
	{
		m_TstRresultAttaList.MoveWindow(5+5,nList2pos,Rect.Width()-((5+5)*2),nListHeight);
	}

}
void CResultSearchNew::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	int i, nCount, Index;
	CString strText;
	CEditableListCtrl *pList1 = &m_TstRresultBaseList;
	nCount = pList1->GetItemCount();
	Index = pList1->GetFirstSelectedItem();

	if(Index < 0 || Index >= nCount)
	{
		return ;
	}

	UINT nBaseOid = pList1->GetItemData(Index);
	UINT nGroupOid = g_CurSelDepart.nOid;
	vector<StTstResultAtta> stResultAttachArray;

	if(!m_DMng.GetTstResultAttaBaseOid(nGroupOid,nBaseOid,&stResultAttachArray))
	{
		return ;
	}

	m_TstRresultAttaList.DeleteAllItems();
	nCount = stResultAttachArray.size();
	strText.Format(_T("共查询到 %d 条结果数据"), nCount);
	GetDlgItem(IDC_STATIC3)->SetWindowText(strText);

	for (i = 0;i<nCount;i++)
	{
		InsertResultAttachToList(&stResultAttachArray.at(i));
	}

	stResultAttachArray.clear();

	*pResult = 0;
}

void CResultSearchNew::OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	ShowAttaData();

	*pResult = 0;
}

void CResultSearchNew::Menu1Fuction()
{
	CEditableListCtrl *pList1 = NULL;
	int nResultSearchType = m_ResultSearchInfo.stTaskBaseInfo.nResultType;
	if(nResultSearchType == Task_DarkSearch)//基于任务 模糊查询//
	{
		pList1 = &m_ResultTaskBase.m_ResultList;
	}else if(nResultSearchType == Task_ExactSearch)//基于任务 精确查询//
	{
		pList1 = &m_TstRresultBaseList;
	}
	int Index = pList1->GetFirstSelectedItem(),
		nCount = pList1->GetItemCount();
	if(Index <0 || Index >= nCount)
	{
		return;
	}

	POINT	point;
	GetCursorPos(&point);
	m_PopupMenu1.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
}

void CResultSearchNew::DelBaseDataNew()//以任务为单位删除结果数据//
{
	CEditableListCtrl *pList1 = NULL;
	int nResultSearchType = m_ResultSearchInfo.stTaskBaseInfo.nResultType;
	if(nResultSearchType == Task_DarkSearch)//基于任务 模糊查询//
	{
		pList1 = &m_ResultTaskBase.m_ResultList;
	}else if(nResultSearchType == Task_ExactSearch)//基于任务 精确查询//
	{
		pList1 = &m_TstRresultBaseList;
	}
	if(pList1 == NULL)
	{
		return;
	}
	int Index = pList1->GetFirstSelectedItem(),
		nCount = pList1->GetItemCount();
	if(Index <0 || Index >= nCount)
	{
		return;
	}


	if(MessageBox(_T("确定删除数据吗?\n(数据删除后将无法恢复!)）"),_T(""),MB_OKCANCEL|MB_ICONQUESTION) != IDOK)
	{
		return ;
	}
	UINT nGroupOid = g_CurSelDepart.nOid;
	UINT nBaseOid = pList1->GetItemData(Index);
	if(m_DMng.DelBaseData(nGroupOid,nBaseOid))
	{
		pList1->DeleteItem(Index);
	}

}


void CResultSearchNew::Menu2Fuction()
{
	CEditableListCtrl *pList1 = NULL;
	int nResultSearchType = m_ResultSearchInfo.stTaskBaseInfo.nResultType;
	if(nResultSearchType == Task_DarkSearch)//基于任务 模糊查询//
	{
		pList1 = &m_TstRresultAttaList;
	}else if(nResultSearchType == Task_ExactSearch)//基于任务 精确查询//
	{
		pList1 = &m_TstRresultAttaList;
	}else if(nResultSearchType == Result_Search)//多条件  结果查询//
	{
		pList1 = &m_ResultAttach.m_ResultList;
	}
	if(pList1 == NULL)
	{
		return;
	}
	int Index = pList1->GetFirstSelectedItem(),
		nCount = pList1->GetItemCount();
	if(Index <0 || Index >= nCount)
	{
		return;
	}

	POINT	point;
	GetCursorPos(&point);
	m_PopupMenu2.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
}
//以任务为单位生成报告文件//
void  CResultSearchNew::CreateTaskReportNew()
{
	CString str, strFileName, strDesFile, strSrcFile, strCreateFile;
	int		ret, tick1,tick2;

	CEditableListCtrl *pList1 = NULL;
	int nResultSearchType = m_ResultSearchInfo.stTaskBaseInfo.nResultType;
	if(nResultSearchType == Task_DarkSearch)//基于任务 模糊查询//
	{
		pList1 = &m_TstRresultAttaList;
	}else if(nResultSearchType == Task_ExactSearch)//基于任务 精确查询//
	{
		pList1 = &m_TstRresultAttaList;
	}else if(nResultSearchType == Result_Search)//多条件  结果查询//
	{
		pList1 = &m_ResultAttach.m_ResultList;
	}
	if(pList1 == NULL)
	{
		return;
	}
	int Index = pList1->GetFirstSelectedItem(),
		nCount = pList1->GetItemCount();
	if(Index <0 || Index >= nCount)
	{
		return;
	}

	CString strTaskName = pList1->GetItemText(Index,3);
	CString strProductNo = pList1->GetItemText(Index,4);
	str.Format(_T("是否生成任务=\"%s\"的报告文件?(确定/取消)"),strTaskName);
	if(MessageBox(str,_T("提示"),MB_OKCANCEL|MB_ICONQUESTION) != IDOK)
	{
		return ;
	}

	//1.获取这个任务的结果附件信息

	UINT nGroupOid = g_CurSelDepart.nOid;
	UINT nAttaOid = pList1->GetItemData(Index);


	StTstResultAtta stCreateReportAtta;
	memset(&stCreateReportAtta, 0, sizeof(StTstResultAtta));

	if(!m_DMng.GetTstResultOid(nGroupOid,nAttaOid,&stCreateReportAtta))
	{
		str.Format(_T("获取结果附件信息时出错!"));
		AfxMessageBox(str);
		return;
	}




	vector<StTstResultAtta> *pStResultAtta = NULL;
	CAdjustmentDlg AdjustmentDlg;
	AdjustmentDlg.m_CreateType = CreateReport_Task;
	AdjustmentDlg.m_pStCreateReportAtta = &stCreateReportAtta;
	if(AdjustmentDlg.DoModal() == IDOK)
	{
		pStResultAtta = &AdjustmentDlg.m_CreateReportArray;
	}else
	{
		return;
	}

	if(pStResultAtta == NULL)
	{
		return;
	}

	if(pStResultAtta->size()<=0)
	{
		return;
	}


	//2.选择一个报告文件名称
	strCreateFile.Format(_T("%s_%s"),strProductNo,GetDateTimeString2());
	CFileDialog *lpszOpenFile;    //定义一个CfileDialog对象
	lpszOpenFile = new CFileDialog(FALSE,".doc",strCreateFile,OFN_FILEMUSTEXIST |OFN_HIDEREADONLY , 
		"文件类型(*.doc)|*.doc||");//生成一个对话框
	if(lpszOpenFile->DoModal() == IDOK)//假如点击对话框确定按钮
	{

		strCreateFile = lpszOpenFile->GetPathName();	//得到打开文件的路径

	}else
	{
		delete lpszOpenFile;	//释放分配的对话框
		return ;
	}
	delete lpszOpenFile;	//释放分配的对话框







	CreateReportBaseNew(pStResultAtta,strCreateFile);
	return ;
	int i;
	nCount = pStResultAtta->size();
	StTstResultAtta *pCurAttaInfo;
	LoadOutTaskXmlAnalysis  m_LoadOutTask;
	CArray<TestDataStr,TestDataStr> m_DataArray;
	CArray<StBasAttachment,StBasAttachment> m_ExclosureArray;
	CStringArray nStrFileNames;

	int t1,t2;

	/******************************************************/

	t1= GetTickCount();
	nStrFileNames.RemoveAll();
	for (i = 0;i<nCount;i++)
	{

		pCurAttaInfo = &pStResultAtta->at(i);

		//1.数据  2.图号信息  3.附件模板信息//


		if(!m_DMng.GetAttaXmlFile(nGroupOid,pCurAttaInfo->nOid))
		{
			continue;
		}

		m_LoadOutTask.GetCurTaskInfoLoad();

		int nRet = 0;
		nRet = m_LoadOutTask.AnalysisData(m_DataArray,m_ExclosureArray);//获取当前任务项的数据//
		if(!nRet)
		{
			//return 0;
		}

		g_pDataArray = &m_DataArray;////1.数据

		int nPicNumCount = g_PicNum = m_LoadOutTask.m_CurTaskInfo.pArryTaskPicNum.size();
		g_pArryTaskPicNum = &m_LoadOutTask.m_CurTaskInfo.pArryTaskPicNum;//2.图号信息///
		g_pCurAttaInfo = pCurAttaInfo;//3.附件信息//




		if (pCurAttaInfo->nModeRowVar == mode_normal)
		{
			tick1 = GetTickCount();

			StBasMode StBasModeInfo;
			memset(&StBasModeInfo, 0, sizeof(StBasMode));

			StBasModeInfo.nModeType = pCurAttaInfo->nModeType;
			strcpy(StBasModeInfo.szModeName, pCurAttaInfo->szModeName);
			strcpy(StBasModeInfo.stProductInfo.szProductNo, pCurAttaInfo->szProductNo);
			strFileName = BuildReportModeFilePath(&StBasModeInfo);

			if(GetFileAttributes(strFileName.GetBuffer(0)) == 0xFFFFFFFF)
			{
				str.Format(_T("报告模板不存在 ！%s"),strFileName);
				AfxMessageBox(str);
				continue ;
			}

			memset(StBasModeInfo.szModeName, 0, sizeof(StBasModeInfo.szModeName));
			strcpy(StBasModeInfo.szModeName, _T("t_Mode2"));
			strDesFile = BuildReportModeFilePath(&StBasModeInfo);


			//strFileName = _T("c:\\Mode2.doc");
			//strDesFile  = _T("c:\\t_Mode2.doc");

			ret = WordOpt_MakeTabModeToTabData(strFileName.GetBuffer(0), strDesFile.GetBuffer(0));

			tick2 = GetTickCount()-tick1;
			str.Format("用时%d毫秒! ret=%d, 输出文件：%s", tick2, ret, strDesFile.GetBuffer(0)); 
			//AfxMessageBox(str);	



			//CString str, strFileName, strDesFile;
			//int		ret, tick1,tick2;
			tick1 = GetTickCount();

			//strCreateFile  = _T("c:\\t_ModeInfo_2.doc");
			//strFileName = _T("c:\\t_Mode2.doc");

			strSrcFile.Format(_T("%s\\%s\\%s.doc"),g_WorkPath, Report_Mode_Path,GetDateTimeFileNameString());
			ret = WordOpt_MakeReportTabInfoDemo(strSrcFile.GetBuffer(0),strDesFile.GetBuffer(0));

			nStrFileNames.Add(strSrcFile);

			tick2 = GetTickCount()-tick1;
			str.Format("用时%d毫秒! ret=%d, 输出文件：%s", tick2, ret, strSrcFile.GetBuffer(0));
			g_pLogInfo->WriteLogFile(str.GetBuffer(0));
			//AfxMessageBox(str);	

		}else
		{
			int		ret, tick1,tick2;
			tick1 = GetTickCount();

			//strCreateFile = _T("C:\\tt2.doc");

			strSrcFile.Format(_T("%s\\%s\\%s.doc"),g_WorkPath, Report_Mode_Path,GetDateTimeFileNameString());
			ret = WordOpt_MakeReportRowVarDemo( strSrcFile.GetBuffer(0) ); 

			nStrFileNames.Add(strSrcFile);

			tick2 = GetTickCount()-tick1;
			str.Format("用时%d毫秒! ret=%d, 输出文件：%s", tick2, ret, strSrcFile.GetBuffer(0)); 
			g_pLogInfo->WriteLogFile(str.GetBuffer(0));
			//AfxMessageBox(str);	
		}

		remove(strDesFile.GetBuffer(0));


	}
	/******************************************************/

	ret = WordOpt_MakeTestimonialDemo(strCreateFile.GetBuffer(0),nStrFileNames);
	pStResultAtta->clear();


	t2 = GetTickCount()-t1;
	str.Format("用时%d毫秒! ret=%d, 输出文件：%s", t2, ret, strCreateFile.GetBuffer(0)); 
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));
	AfxMessageBox(str);	


}
//以产品编号为单位生成报告文件//
void  CResultSearchNew::CreateProductCodeReportNew()
{

	CString str, strFileName, strDesFile, strSrcFile, strCreateFile;

	CEditableListCtrl *pList1 = NULL;
	int nResultSearchType = m_ResultSearchInfo.stTaskBaseInfo.nResultType;
	if(nResultSearchType == Task_DarkSearch)//基于任务 模糊查询//
	{
		pList1 = &m_TstRresultAttaList;
	}else if(nResultSearchType == Task_ExactSearch)//基于任务 精确查询//
	{
		pList1 = &m_TstRresultAttaList;
	}else if(nResultSearchType == Result_Search)//多条件  结果查询//
	{
		pList1 = &m_ResultAttach.m_ResultList;
	}
	if(pList1 == NULL)
	{
		return;
	}
	int Index = pList1->GetFirstSelectedItem(),
		nCount = pList1->GetItemCount();
	if(Index <0 || Index >= nCount)
	{
		return;
	}


	CString strProductNo = pList1->GetItemText(Index,4);
	CString strProductCode = pList1->GetItemText(Index,5);
	str.Format(_T("是否生成产品报告, 产品编号=\"%s\" ?(确定/取消)"),strProductCode);
	if(MessageBox(str,_T("提示"),MB_OKCANCEL|MB_ICONQUESTION) != IDOK)
	{
		return ;
	}



	//1.获取这个任务的结果附件信息

	UINT nGroupOid = g_CurSelDepart.nOid;
	UINT nAttaOid = pList1->GetItemData(Index);
	UINT nBaseOid = 0;

	StTstResultAtta stCreateReportAtta;
	memset(&stCreateReportAtta, 0, sizeof(StTstResultAtta));

	if(!m_DMng.GetTstResultOid(nGroupOid,nAttaOid,&stCreateReportAtta))
	{
		str.Format(_T("获取结果附件信息时出错!"));
		AfxMessageBox(str);
		return;
	}

	vector<StTstResultAtta> *pStResultAtta = NULL;
	CAdjustmentDlg AdjustmentDlg;
	AdjustmentDlg.m_CreateType = CreateReport_ProdCode;
	AdjustmentDlg.m_pStCreateReportAtta = &stCreateReportAtta;
	if(AdjustmentDlg.DoModal() == IDOK)
	{
		pStResultAtta = &AdjustmentDlg.m_CreateReportArray;
	}else
	{
		return;
	}

	if(pStResultAtta == NULL)
	{
		return;
	}

	if(pStResultAtta->size()<=0)
	{
		return;
	}


	//2.选择一个报告文件名称
	strCreateFile.Format(_T("%s_%s_%s"),strProductNo,strProductCode,GetDateTimeString2());
	CFileDialog *lpszOpenFile;    //定义一个CfileDialog对象
	lpszOpenFile = new CFileDialog(FALSE,".doc",strCreateFile,OFN_FILEMUSTEXIST |OFN_HIDEREADONLY , 
		"文件类型(*.doc)|*.doc||");//生成一个对话框
	if(lpszOpenFile->DoModal() == IDOK)//假如点击对话框确定按钮
	{

		strCreateFile = lpszOpenFile->GetPathName();	//得到打开文件的路径

	}else
	{
		delete lpszOpenFile;	//释放分配的对话框
		return ;
	}
	delete lpszOpenFile;	//释放分配的对话框

	CreateReportBaseNew(pStResultAtta,strCreateFile);

}

//以模板为单位生成报告文件
void  CResultSearchNew::CreateModeReportNew()
{

	CString str, strFileName, strDesFile, strSrcFile, strCreateFile;

	CEditableListCtrl *pList1 = NULL;
	int nResultSearchType = m_ResultSearchInfo.stTaskBaseInfo.nResultType;
	if(nResultSearchType == Task_DarkSearch)//基于任务 模糊查询//
	{
		pList1 = &m_TstRresultAttaList;
	}else if(nResultSearchType == Task_ExactSearch)//基于任务 精确查询//
	{
		pList1 = &m_TstRresultAttaList;
	}else if(nResultSearchType == Result_Search)//多条件  结果查询//
	{
		pList1 = &m_ResultAttach.m_ResultList;
	}
	if(pList1 == NULL)
	{
		return;
	}
	int Index = pList1->GetFirstSelectedItem(),
		nCount = pList1->GetItemCount();
	if(Index <0 || Index >= nCount)
	{
		return;
	}

	CString strProductNo = pList1->GetItemText(Index,4);
	CString strProductCode = pList1->GetItemText(Index,6);

	CString strModeName = pList1->GetItemText(Index,7);
	str.Format(_T("是否生成产品模板=\"%s\"的报告文件?(确定/取消)"),strModeName);
	if(MessageBox(str,_T("提示"),MB_OKCANCEL|MB_ICONQUESTION) != IDOK)
	{
		return ;
	}




	//1.选择一个报告文件名称
	strCreateFile.Format(_T("%s_%s_%s_%s"),strProductNo,strProductCode,strModeName,GetDateTimeString2());
	CFileDialog *lpszOpenFile;    //定义一个CfileDialog对象
	lpszOpenFile = new CFileDialog(FALSE,".doc",strCreateFile,OFN_FILEMUSTEXIST |OFN_HIDEREADONLY , 
		"文件类型(*.doc)|*.doc||");//生成一个对话框
	if(lpszOpenFile->DoModal() == IDOK)//假如点击对话框确定按钮
	{

		strCreateFile = lpszOpenFile->GetPathName();	//得到打开文件的路径

	}else
	{
		delete lpszOpenFile;	//释放分配的对话框
		return ;
	}
	delete lpszOpenFile;	//释放分配的对话框





	//2.获取这个任务的结果附件信息

	UINT nGroupOid = g_CurSelDepart.nOid;
	UINT nAttaOid = pList1->GetItemData(Index);
	UINT nBaseOid = 0;

	StTstResultAtta m_CreateReportAtta;
	memset(&m_CreateReportAtta, 0, sizeof(StTstResultAtta));

	if(!m_DMng.GetTstResultOid(nGroupOid,nAttaOid,&m_CreateReportAtta))
	{
		str.Format(_T("获取结果附件信息时出错!"));
		AfxMessageBox(str);
		return;
	}
	vector<StTstResultAtta> StResultAtta;
	StResultAtta.push_back(m_CreateReportAtta);

	CreateReportBaseNew(&StResultAtta,strCreateFile);



}

//生成报告
void  CResultSearchNew::CreateReportBaseNew(vector<StTstResultAtta> *pStResultAtta,CString strCreateFile)
{
	UINT nGroupOid = g_CurSelDepart.nOid;
	CString str, strFileName, strDesFile, strSrcFile;
	int		ret=0, tick1=0,tick2=0;

	int i,nCount;
	nCount = pStResultAtta->size();
	StTstResultAtta *pCurAttaInfo;
	LoadOutTaskXmlAnalysis  m_LoadOutTask;
	CArray<TestDataStr,TestDataStr> m_DataArray;
	CArray<StBasAttachment,StBasAttachment> m_ExclosureArray;
	CStringArray nStrFileNames;

	int t1,t2;

	/******************************************************/

	str.Format(_T("%s\\%s"),g_WorkPath,Report_Temp_Path);
	if(GetFileAttributes(str.GetBuffer(0)) == 0xffffffff)
	{
		CreateDirectory(str.GetBuffer(0),NULL);
	}

	t1= GetTickCount();
	nStrFileNames.RemoveAll();
	for (i = 0;i<nCount;i++)
	{

		pCurAttaInfo = &pStResultAtta->at(i);

		//1.数据  2.图号信息  3.附件模板信息//


		if(!m_DMng.GetAttaXmlFile(nGroupOid,pCurAttaInfo->nOid))
		{
			continue;
		}

		m_LoadOutTask.m_CurTaskInfo.Release();
		m_LoadOutTask.GetCurTaskInfoLoad();

		int nRet = 0;
		m_DataArray.RemoveAll();
		m_ExclosureArray.RemoveAll();
		nRet = m_LoadOutTask.AnalysisData(m_DataArray,m_ExclosureArray);//获取当前任务项的数据//
		if(!nRet)
		{
			//return 0;
		}

		g_pDataArray = &m_DataArray;////1.数据

		int nPicNumCount = g_PicNum = m_LoadOutTask.m_CurTaskInfo.pArryTaskPicNum.size();
		g_pArryTaskPicNum = &m_LoadOutTask.m_CurTaskInfo.pArryTaskPicNum;//2.图号信息///
		g_pCurAttaInfo = pCurAttaInfo;//3.附件信息//




		if (pCurAttaInfo->nModeRowVar == mode_normal)
		{
			tick1 = GetTickCount();

			StBasMode StBasModeInfo;
			memset(&StBasModeInfo, 0, sizeof(StBasMode));

			StBasModeInfo.nModeType = pCurAttaInfo->nModeType;
			strcpy(StBasModeInfo.szModeName, pCurAttaInfo->szModeName);
			strcpy(StBasModeInfo.stProductInfo.szProductNo, pCurAttaInfo->szProductNo);
			strFileName = BuildReportModeFilePath(&StBasModeInfo);

			if(GetFileAttributes(strFileName.GetBuffer(0)) == 0xFFFFFFFF)
			{
				str.Format(_T("报告模板不存在 ！%s"),strFileName);
				AfxMessageBox(str);
				continue ;
			}


			strSrcFile.Format(_T("%s\\%s\\%s_%s.doc"),g_WorkPath,
				Report_Temp_Path,StBasModeInfo.szModeName,GetDateTimeFileNameString());

			str.Format("[第%d个]开始生成文件：%s",i+1, strSrcFile.GetBuffer(0));
			g_pLogInfo->WriteLogFile(str.GetBuffer(0));


			tick1 = GetTickCount();
			//strFileName = _T("c:\\Mode2.doc");
			//strDesFile  = _T("c:\\t_Mode2.doc");
			strDesFile.Format(_T("%s\\%s\\t%d_Mode.doc"),g_WorkPath,Report_Temp_Path,i+1);
			str.Format("开始生成文件：%s", strDesFile.GetBuffer(0));
			g_pLogInfo->WriteLogFile(str.GetBuffer(0));

			ret = WordOpt_MakeTabModeToTabData(strFileName.GetBuffer(0), strDesFile.GetBuffer(0));


			str.Format("CreateReportBase：%d, ret=%d", 1, ret);
			g_pLogInfo->WriteLogFile(str.GetBuffer(0));


			tick2 = GetTickCount()-tick1;
			str.Format("用时%d毫秒! ret=%d, 生成文件成功：%s", tick2, ret, strDesFile.GetBuffer(0)); 
			g_pLogInfo->WriteLogFile(str.GetBuffer(0));
			//AfxMessageBox(str);	



			//CString str, strFileName, strDesFile;
			//int		ret, tick1,tick2;
			tick1 = GetTickCount();

			//strCreateFile  = _T("c:\\t_ModeInfo_2.doc");
			//strFileName = _T("c:\\t_Mode2.doc");


			ret = WordOpt_MakeReportTabInfoDemo(strSrcFile.GetBuffer(0),strDesFile.GetBuffer(0));

			nStrFileNames.Add(strSrcFile);

			tick2 = GetTickCount()-tick1;
			str.Format("用时%d毫秒! ret=%d, [第%d个]生成文件成功：%s", tick2, ret,i+1, strSrcFile.GetBuffer(0));
			g_pLogInfo->WriteLogFile(str.GetBuffer(0));
			//AfxMessageBox(str);	

		}else
		{
			tick1 = GetTickCount();

			//strCreateFile = _T("C:\\tt2.doc");

			strSrcFile.Format(_T("%s\\%s\\%s.doc"),g_WorkPath, Report_Temp_Path,GetDateTimeFileNameString());
			str.Format("[第%d个]开始生成文件：%s",i+1, strSrcFile.GetBuffer(0));
			g_pLogInfo->WriteLogFile(str.GetBuffer(0));

			ret = WordOpt_MakeReportRowVarDemo( strSrcFile.GetBuffer(0) ); 

			nStrFileNames.Add(strSrcFile);

			tick2 = GetTickCount()-tick1;
			str.Format("用时%d毫秒! ret=%d, [第%d个]生成文件成功：%s", tick2, ret,i+1, strSrcFile.GetBuffer(0)); 
			g_pLogInfo->WriteLogFile(str.GetBuffer(0));
			//AfxMessageBox(str);	
		}

		remove(strDesFile.GetBuffer(0));


	}
	/******************************************************/

	tick1 = GetTickCount();

	ret = WordOpt_MakeTestimonialDemo(strCreateFile.GetBuffer(0),nStrFileNames);

	tick2 = GetTickCount()-tick1;
	str.Format("用时%d毫秒! ret=%d, 合并中间文件,文件个数%d", tick2, ret, nCount); 
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));


	pStResultAtta->clear();
	t2 = GetTickCount()-t1;
	str.Format("用时%d毫秒! ret=%d, 输出文件：%s", t2, ret, strCreateFile.GetBuffer(0)); 
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));
	AfxMessageBox(str);	
}

void  CResultSearchNew::InitPopMenu1( )					//初始化菜单1
{
	if(!m_PopupMenu1.GetSafeHmenu())
	{
		m_PopupMenu1.CreatePopupMenu();

		m_PopupMenu1.AppendMenu(MF_STRING, ID_MENU1_DELDATA_BASE,		"删除数据");

	}
}

void  CResultSearchNew::InitPopMenu2( )					//初始化菜单1
{
	if(!m_PopupMenu2.GetSafeHmenu())
	{
		m_PopupMenu2.CreatePopupMenu();

		m_PopupMenu2.AppendMenu(MF_STRING, ID_MENU1_C_PRODUCT_REPORT_ATTA,     "生成产品报告");
		m_PopupMenu2.AppendMenu(MF_STRING, ID_MENU1_C_MODE_REPORT_ATTA,        "生成模板报告");
		m_PopupMenu2.AppendMenu(MF_STRING, ID_MENU1_C_TASK_REPORT_BASE,       "生成任务报告");
		//m_PopupMenu2.AppendMenu(MF_SEPARATOR);
		//m_PopupMenu2.AppendMenu(MF_STRING, ID_MENU1_DELDATA_ATTA,		"删除数据");


	}
}
void CResultSearchNew::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	Menu1Fuction();
	*pResult = 0;
}

void CResultSearchNew::OnNMRClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	Menu2Fuction();
	*pResult = 0;
}
