// ShowTaskInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "ShowTaskInfo.h"
#include "ModeXmlStruct.h"

#include "MainFrm.h"
#include "BatchExportTask.h"
#include "SelUserDlg.h"
#include "SelUpDepartDlg.h"
#include "SelProductDlg.h"
// CShowTaskInfo 对话框

IMPLEMENT_DYNAMIC(CShowTaskInfo, CDialog)

CShowTaskInfo::CShowTaskInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CShowTaskInfo::IDD, pParent)
{
	m_CurTaskInfo.Release();
	m_pTaskTree = NULL;

	m_ShowType = View_Task;
}

CShowTaskInfo::~CShowTaskInfo()
{
	m_CurTaskInfo.Release();
}

void CShowTaskInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHOWTASKINFO_TAB, m_ShowTaskInfoTab);
}


BEGIN_MESSAGE_MAP(CShowTaskInfo, CDialog)
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_SHOWTASKINFO_TAB, &CShowTaskInfo::OnTcnSelchangeShowtaskinfoTab)
	ON_BN_CLICKED(IDC_SEL_PRODUCTNO_BTN, &CShowTaskInfo::OnBnClickedSelProductnoBtn)
	ON_BN_CLICKED(IDC_SEL_UPDEPART_BTN, &CShowTaskInfo::OnBnClickedSelUpdepartBtn)
	ON_BN_CLICKED(IDC_BUTTON2, &CShowTaskInfo::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CShowTaskInfo::OnBnClickedButton3)
END_MESSAGE_MAP()


// CShowTaskInfo 消息处理程序

BOOL CShowTaskInfo::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	TCITEM tcItem;
	tcItem.mask = TCIF_TEXT;
	tcItem.pszText = _T("基本信息");
	m_ShowTaskInfoTab.InsertItem(0,&tcItem) ;

	tcItem.pszText = _T("任务详情");
	m_ShowTaskInfoTab.InsertItem(1,&tcItem) ;

	tcItem.pszText = _T("结果数据");
	m_ShowTaskInfoTab.InsertItem(2,&tcItem) ;


	m_TaskCfg.Create(IDD_TASK_CFG_DLG, this);
	m_TaskCfg.m_pShowTaskInfo = this;
	m_TaskCfg.ShowWindow(SW_HIDE);

	m_ShowTaskData.Create(IDD_SHOWTASKDATA_DLG,this);
	m_ShowTaskData.m_pShowTaskInfo = this;
	m_ShowTaskData.ShowWindow(SW_HIDE);

	m_ResultSearch.Create(IDD_RESULT_SEARCH_DLG,this);
	m_ResultSearch.ShowWindow(SW_HIDE);

	m_ResultSearchNew.Create(IDD_RESULT_SEARCH_NEW_DLG, this);
	m_ResultSearchNew.ShowWindow(SW_HIDE);

	SetControlShow(SW_SHOW);

	InitTaskTypeComBo();
	PostMessage(WM_SIZE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CShowTaskInfo::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	AutoSize();
	// TODO: 在此处添加消息处理程序代码
}
void CShowTaskInfo::InitTaskTypeComBo()
{

	CComboBox * pComBo = (CComboBox*)GetDlgItem(IDC_TASK_TYPE_COM);
	pComBo->ResetContent();

	int i;
	for (i = Task_Test;i<=Task_HelpReTest;i++)
	{
		pComBo->AddString(g_TaskType[i]);
	}
	pComBo->SetCurSel(0);

	pComBo = (CComboBox*)GetDlgItem(IDC_ARMY_TEST_COM);
	pComBo->ResetContent();

	pComBo->AddString(_T("否"));
	pComBo->AddString(_T("是"));
	pComBo->SetCurSel(0);
}

UINT  CShowTaskInfo::GetSelDepartOid()
{
	CComboBox *pComBox = (CComboBox *)GetDlgItem(IDC_UP_DEPART_COM);
	int Index,nCount;
	UINT nGroupOid = 0;
	nCount = pComBox->GetCount();
	Index = pComBox->GetCurSel();
	if(nCount <=0)
	{
		nGroupOid = 0;
	}
	if(Index <0 || Index >= nCount)
	{
		nGroupOid =  pComBox->GetItemData(0);

	}else
	{
		nGroupOid = pComBox->GetItemData(Index);
	}

	return nGroupOid;
}

void CShowTaskInfo::AutoSize()
{
	CRect Rect ;
	GetClientRect(&Rect) ;
	int nBtnWidth = 80;
	int nBtnHeight = 30;

	int nStaticHead = 325;
	int nStaticHead1 = 300;

	

	if(m_ShowTaskInfoTab.GetSafeHwnd())
	{
		m_ShowTaskInfoTab.MoveWindow(0,0,Rect.Width(),Rect.Height());
	}

	if(GetDlgItem(IDC_SHOWTASKINFO_STATIC)->GetSafeHwnd())
	{
		GetDlgItem(IDC_SHOWTASKINFO_STATIC)->MoveWindow(1+2,1+22,Rect.Width()-(2+4),nStaticHead1);
	}


	if (m_ShowTaskData.GetSafeHwnd())
	{
		m_ShowTaskData.MoveWindow(1+2,1+22,Rect.Width()-(2+4),Rect.Height()-(2+24));
	}

	if (m_ResultSearch.GetSafeHwnd())
	{
		m_ResultSearch.MoveWindow(1+2,1+22,Rect.Width()-(2+4),Rect.Height()-(2+24));
	}

	if (m_ResultSearchNew.GetSafeHwnd())
	{
		m_ResultSearchNew.MoveWindow(1+2,1+22,Rect.Width()-(2+4),Rect.Height()-(2+24));
	}

	if (m_TaskCfg.GetSafeHwnd())
	{
		m_TaskCfg.MoveWindow(1,1+nStaticHead,Rect.Width()-(1*2),Rect.Height()-(1*2+nStaticHead+(nBtnHeight+20)));
	}


//功能按钮的位置///

	if(GetDlgItem(IDOK)->GetSafeHwnd())
	{
		GetDlgItem(IDOK)->MoveWindow(Rect.right-((nBtnWidth+10)*2),Rect.bottom-40,nBtnWidth,nBtnHeight);
	}

	if(GetDlgItem(IDCANCEL)->GetSafeHwnd())
	{
		GetDlgItem(IDCANCEL)->MoveWindow(Rect.right-((nBtnWidth+10)*1),Rect.bottom-40,nBtnWidth,nBtnHeight);
	}
	

	
	
}

void CShowTaskInfo::GetTreeItemType(HTREEITEM hItem,StBasTask *pStr)
{

	if(hItem == NULL)
	{
		return;
	}
	CString strItem = m_pTaskTree->GetItemText(hItem);
	if(strItem.IsEmpty())
		return;
	int nTreeID = m_pTaskTree->GetItemData(hItem);

	int nType,nID;
	if(!NumOneToTwo(nTreeID,nType,nID))
	{
		return;
	}

	switch(nType)
	{
	case TASK_TREE_TYPE_DEPART:
		{
			pStr->stTaskBaseInfo.nGroupOid = nID;
			HTREEITEM hpItem = m_pTaskTree->GetParentItem(hItem);
			GetTreeItemType(hpItem, pStr);

		}
		break;
	case TASK_TREE_TYPE_TASKTYPE:
		{
			pStr->stTaskBaseInfo.nTaskStatus = nID;
			HTREEITEM hpItem = m_pTaskTree->GetParentItem(hItem);
			GetTreeItemType(hpItem, pStr);

		}
		break;
	case TASK_TREE_TYPE_PRODCODE:
		{
			pStr->stProductInfo.nOid = nID;
			HTREEITEM hpItem = m_pTaskTree->GetParentItem(hItem);
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


/*
BOOL CShowTaskInfo::AddNewTask()  //del
{
	StBasTask *pTaskInfo = &m_CurTaskInfo;
	CString  strTaskName;
	strTaskName.Format(_T("%s_%s"),
		m_pTaskTree->GetItemText(pTaskInfo->stTaskBaseInfo.hItem),pTaskInfo->stTaskBaseInfo.szBatch);

	InputInfo nInPutInfo;
	nInPutInfo.Type =Add_Task;
	nInPutInfo.WindowText = "请输入一个任务名称!";
	nInPutInfo.NameStatic  = "任务名称:";
	nInPutInfo.OutName = strTaskName;
	CInPutName nDlg(&nInPutInfo);

	if(nDlg.DoModal() != IDOK)
	{
		return FALSE;
	}


	StBasTask  nTaskInfo;
	nTaskInfo.Release();
	StBasTaskBaseInfo *pTaskBaseInfo = &nTaskInfo.stTaskBaseInfo;
	StBasProduct      *pProductInfo = &nTaskInfo.stProductInfo;
	strcpy(pTaskBaseInfo->szTaskName,nInPutInfo.OutName);
	pTaskBaseInfo->nTaskStatus = Task_Init;
	pTaskBaseInfo->nTaskType = Task_Test;

	pProductInfo->nOid = pTaskInfo->stProductInfo.nOid;
	pTaskBaseInfo->pTaskTree = pTaskInfo->stTaskBaseInfo.pTaskTree;
	pTaskBaseInfo->hItem = pTaskInfo->stTaskBaseInfo.hItem;
	pTaskBaseInfo->TreeItemType = pTaskInfo->stTaskBaseInfo.TreeItemType;


	strcpy(pTaskBaseInfo->szPlanBegTime,GetDateTimeString());
	strcpy(pTaskBaseInfo->szPlanEndTime,GetDateTimeString());

	GetTreeItemType(pTaskInfo->stTaskBaseInfo.hItem,&nTaskInfo);
	if(m_DMng.IsProductTaskExists(pProductInfo->nOid,
		pTaskBaseInfo->szTaskName))
	{
		CString strText;
		strText.Format(_T("此任务 \"%s\" 已经存在了!"),nTaskInfo.stTaskBaseInfo.szTaskName);
		AfxMessageBox(strText);
		return FALSE;
	}else
	{
		CTreeCtrl *pTree = nTaskInfo.stTaskBaseInfo.pTaskTree;
		HTREEITEM HItem = NULL;
		HItem = nTaskInfo.stTaskBaseInfo.hItem ;
		CString strText,strTaskName = nTaskInfo.stTaskBaseInfo.szTaskName;
		if(!HItem || nTaskInfo.stTaskBaseInfo.TreeItemType != TASK_TREE_TYPE_PRODCODE)
		{
			return FALSE;
		}
		int nTreeID;
		if(m_DMng.AddNewTask(&nTaskInfo))
		{
			if(NumTwoToOne(nTreeID,TASK_TREE_TYPE_TASK,nTaskInfo.stTaskBaseInfo.nOid))
			{
				int nIcon = GetTaskIcon(nTaskInfo.stTaskBaseInfo.nTaskStatus);
				MyInsertTree(pTree,strTaskName,HItem,nTreeID,nIcon,nIcon);
			}
			strText.Format(_T("添加任务: \"%s\" 成功!"),strTaskName);
			g_MainFram->m_wndOutput.InsertErrorText(strText);
		}else
		{
			strText.Format(_T("添加任务: \"%s\" 失败!"),strTaskName);
			g_MainFram->m_wndOutput.InsertErrorText(strText);
			AfxMessageBox(strText);
			return FALSE;
		}
	}
	return TRUE;
}
*/

BOOL CShowTaskInfo::EditTast()
{
	StBasTask *pTaskInfo = &m_CurTaskInfo;
	CTreeCtrl *pTree = pTaskInfo->stTaskBaseInfo.pTaskTree;
	HTREEITEM HItem = NULL;
	CString strText,strTaskNewName,strTaskOldName = pTaskInfo->stTaskBaseInfo.szTaskName;
	HItem = pTaskInfo->stTaskBaseInfo.hItem ;
	if(!HItem || pTaskInfo->stTaskBaseInfo.TreeItemType != TASK_TREE_TYPE_TASK)
	{
		return FALSE;
	}
	
	//if(CheckTaskInfoChange())
	if(1)
	{
		strTaskNewName = pTaskInfo->stTaskBaseInfo.szTaskName;
		if(m_DMng.EditOldTask(pTaskInfo))
		{
			//检查产品编号数量与配置是否一致//
			int nNum = m_CurTaskInfo.pArryTaskCode.size();

			int nRows = m_CurTaskInfo.stTaskBaseInfo.nCodeNumber;

			if(nNum !=nRows)
			{
				CString strNum;
				strNum.Format(_T("任务要求检查 %d 项产品，实际选择了 %d 项"),nRows,nNum);
				AfxMessageBox(strNum);
			}

			pTree->SetItemText(HItem,strTaskNewName);

			if(strTaskOldName != strTaskNewName)
			{
				strText.Format(_T("已将任务名从: \"%s\" 修改为 \"%s\""),strTaskOldName,strTaskNewName);
				g_MainFram->m_wndOutput.InsertErrorText(strText);
			}
			strText.Format(_T("保存操作完毕!"));
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
BOOL CShowTaskInfo::DelTast()
{
	//删除任务是要检查几项//
	//1.检查任务状态 已完成 导出的 不能删除//
	//2.清空 当前任务的 任务编号表的所有编号///
	//3.清空 当前任务的  任务模板表的所有模板///

	CTreeCtrl *pTree = m_CurTaskInfo.stTaskBaseInfo.pTaskTree;
	if(!m_CurTaskInfo.stTaskBaseInfo.hItem || m_CurTaskInfo.stTaskBaseInfo.TreeItemType != TASK_TREE_TYPE_TASK)
	{
		return TRUE;
	}
	if(MessageBox(_T("确定删除此任务吗?(确定/取消)）"),_T(""),MB_OKCANCEL|MB_ICONQUESTION) != IDOK)
	{
		return TRUE;
	}

	if(m_DMng.DelOldTask(m_CurTaskInfo.stTaskBaseInfo.nOid))
	{
		pTree->DeleteItem(m_CurTaskInfo.stTaskBaseInfo.hItem);
		return TRUE;
	}

	return FALSE;
}



void CShowTaskInfo::SetControlShow(UINT nShow)
{
//Static  解释说明//
	GetDlgItem(IDC_SHOWTASKINFO_STATIC1)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWTASKINFO_STATIC3)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWTASKINFO_STATIC4)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWTASKINFO_STATIC5)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWTASKINFO_STATIC6)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWTASKINFO_STATIC7)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWTASKINFO_STATIC8)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWTASKINFO_STATIC9)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWTASKINFO_STATIC10)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWTASKINFO_STATIC11)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWTASKINFO_STATIC12)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWTASKINFO_STATIC13)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWTASKINFO_STATIC14)->ShowWindow(nShow);

	GetDlgItem(IDC_SHOWTASKINFO_STATIC15)->ShowWindow(nShow);
	
	GetDlgItem(IDC_SHOWTASKINFO_STATIC18)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWTASKINFO_STATIC19)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWTASKINFO_STATIC20)->ShowWindow(nShow);

	GetDlgItem(IDC_SHOWTASKINFO_STATIC21)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWTASKINFO_STATIC22)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWTASKINFO_STATIC23)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWTASKINFO_STATIC24)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWTASKINFO_STATIC25)->ShowWindow(nShow);

	GetDlgItem(IDC_SHOWTASKINFO_STATIC26)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWTASKINFO_STATIC27)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWTASKINFO_STATIC28)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWTASKINFO_STATIC29)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWTASKINFO_STATIC30)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWTASKINFO_STATIC31)->ShowWindow(nShow);

	GetDlgItem(IDC_SHOWTASKINFO_STATIC35)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWTASKINFO_STATIC36)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWTASKINFO_STATIC37)->ShowWindow(nShow);
	GetDlgItem(IDC_STATIC1)->ShowWindow(nShow);//导入时间//
	
	
//基本信息//
	GetDlgItem(IDC_TASK_NAME_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_PROJECT_NO_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_TASK_STATUS_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_TASK_TYPE_COM)->ShowWindow(nShow);
	GetDlgItem(IDC_SHOWTASKINFO_DEPART_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_UP_TIME_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_UP_USER_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_CHECK_USER_EDT)->ShowWindow(nShow);

	GetDlgItem(IDC_PRODNAME_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_PRODUCTNO_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_DOWNLOAD_DATE_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_PRODUCTCODE_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_PRODUCT_MODEL_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_PRODUCT_PHASE_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_PRODUCT_NUMBER_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_BATCH_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_SEND_DATE_EDT)->ShowWindow(nShow);

	GetDlgItem(IDC_PLAN_BEGTIME)->ShowWindow(nShow);
	GetDlgItem(IDC_PLAN_ENDTIME)->ShowWindow(nShow);
	GetDlgItem(IDC_REAL_BEGTIME_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_REAL_ENDTIME_EDT)->ShowWindow(nShow);

	GetDlgItem(IDC_EDIT1)->ShowWindow(nShow);
	GetDlgItem(IDC_ARMY_TEST_COM)->ShowWindow(nShow);
	GetDlgItem(IDC_DIANSHI_NUM_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_TECHNOLOGY_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_ACCORDING1_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_ACCORDING2_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_ACCORDING3_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_ACCORDING4_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_ACCORDING5_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_TASK_REMARK_EDT)->ShowWindow(nShow);

	GetDlgItem(IDC_FINISH_DATE_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_CREATE_USER_EDT)->ShowWindow(nShow);
	GetDlgItem(IDC_CREATE_TIME_EDT)->ShowWindow(nShow);
	
	GetDlgItem(IDC_EDIT2)->ShowWindow(nShow);//导入时间//
	
		
	GetDlgItem(IDC_SEL_PRODUCTNO_BTN)->ShowWindow(nShow);
	GetDlgItem(IDC_SEL_UPDEPART_BTN)->ShowWindow(nShow);
	GetDlgItem(IDC_BUTTON2)->ShowWindow(nShow);
	GetDlgItem(IDC_BUTTON3)->ShowWindow(nShow);

//产品编号  和 记录模板//

	m_TaskCfg.ShowWindow(nShow);
	//功能按钮/// 
	if(m_ShowType == View_Task)
	{
		GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
	}else
	{
		GetDlgItem(IDOK)->ShowWindow(nShow);
	}

	if(m_ShowType == Tree_Modify_Task)
	{
		GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);
	}else
	{
		GetDlgItem(IDCANCEL)->ShowWindow(nShow);
	}
	
	GetDlgItem(IDCANCEL)->ShowWindow(nShow);
	
}


BOOL CShowTaskInfo::GetChangeTaskInfo()
{
	BOOL  Is_Change = TRUE;//检验单/
	
	CString strText,str;
	int     Num;
	GetDlgItem(IDC_TASK_NAME_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();

	if(strText.IsEmpty())
	{
		str.Format(_T("任务名称不能为空!"));
		AfxMessageBox(str);
		Is_Change =  FALSE;
		return Is_Change;
	}
	if(strcmp(strText,m_CurTaskInfo.stTaskBaseInfo.szTaskName) != 0)
	{
		memset(m_CurTaskInfo.stTaskBaseInfo.szTaskName, 0,sizeof(m_CurTaskInfo.stTaskBaseInfo.szTaskName));
		strcpy(m_CurTaskInfo.stTaskBaseInfo.szTaskName,strText);
		Is_Change = TRUE;
	}

	//任务类型//
	CComboBox *pComBo = (CComboBox *)GetDlgItem(IDC_TASK_TYPE_COM);
	int nSel = pComBo->GetCurSel();
	if(nSel != m_CurTaskInfo.stTaskBaseInfo.nTaskType)
	{
			m_CurTaskInfo.stTaskBaseInfo.nTaskType = nSel;
			Is_Change = TRUE;
	}

	//产品代号//
	GetDlgItem(IDC_PRODUCTNO_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();

	if(strText.IsEmpty())
	{
		str.Format(_T("产品代号不能为空!"));
		AfxMessageBox(str);
		Is_Change =  FALSE;
		return Is_Change;
	}
	if(strcmp(strText,m_CurTaskInfo.stProductInfo.szProductNo) != 0)
	{
		memset(m_CurTaskInfo.stProductInfo.szProductNo, 0,sizeof(m_CurTaskInfo.stProductInfo.szProductNo));
		strcpy(m_CurTaskInfo.stProductInfo.szProductNo,strText);
		Is_Change = TRUE;
	}
	//产品名称//
	GetDlgItem(IDC_PRODNAME_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	
	if(strcmp(strText,m_CurTaskInfo.stProductInfo.szProductName) != 0)
	{
		memset(m_CurTaskInfo.stProductInfo.szProductName, 0,sizeof(m_CurTaskInfo.stProductInfo.szProductName));
		strcpy(m_CurTaskInfo.stProductInfo.szProductName,strText);
		Is_Change = TRUE;
	}

	//产品编号/
	GetDlgItem(IDC_PRODUCTCODE_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();

	if(strcmp(strText,m_CurTaskInfo.stTaskBaseInfo.szProductCode) != 0)
	{
		memset(m_CurTaskInfo.stTaskBaseInfo.szProductCode, 0,sizeof(m_CurTaskInfo.stTaskBaseInfo.szProductCode));
		strcpy(m_CurTaskInfo.stTaskBaseInfo.szProductCode,strText);
		Is_Change = TRUE;
	}
	
	//编号数量//
	GetDlgItem(IDC_PRODUCT_NUMBER_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	Num = atoi(strText);
	if(Num != m_CurTaskInfo.stTaskBaseInfo.nCodeNumber)
	{
		m_CurTaskInfo.stTaskBaseInfo.nCodeNumber = Num;
		Is_Change = TRUE;
	}
	//批次//
	GetDlgItem(IDC_BATCH_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	if(strcmp(strText,m_CurTaskInfo.stTaskBaseInfo.szBatch) != 0)
	{
		memset(m_CurTaskInfo.stTaskBaseInfo.szBatch, 0,sizeof(m_CurTaskInfo.stTaskBaseInfo.szBatch));
		strcpy(m_CurTaskInfo.stTaskBaseInfo.szBatch,strText);
		Is_Change = TRUE;
	}
	//型号//
	GetDlgItem(IDC_PRODUCT_MODEL_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	if(strcmp(strText,m_CurTaskInfo.stTaskBaseInfo.szModel) != 0)
	{
		memset(m_CurTaskInfo.stTaskBaseInfo.szModel, 0,sizeof(m_CurTaskInfo.stTaskBaseInfo.szModel));
		strcpy(m_CurTaskInfo.stTaskBaseInfo.szModel,strText);
		Is_Change = TRUE;
	}
	
	//阶段//
	GetDlgItem(IDC_PRODUCT_PHASE_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	if(strcmp(strText,m_CurTaskInfo.stTaskBaseInfo.szPhase) != 0)
	{
		memset(m_CurTaskInfo.stTaskBaseInfo.szPhase, 0,sizeof(m_CurTaskInfo.stTaskBaseInfo.szPhase));
		strcpy(m_CurTaskInfo.stTaskBaseInfo.szPhase,strText);
		Is_Change = TRUE;
	}

	//交检部门//
	GetDlgItem(IDC_SHOWTASKINFO_DEPART_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	if(strcmp(strText,m_CurTaskInfo.stHrUpDepart.szUpDepartName) != 0)
	{
		memset(m_CurTaskInfo.stHrUpDepart.szUpDepartName, 0,sizeof(m_CurTaskInfo.stHrUpDepart.szUpDepartName));
		strcpy(m_CurTaskInfo.stHrUpDepart.szUpDepartName,strText);
		Is_Change = TRUE;
	}

	if(strText.IsEmpty())
	{
		str.Format(_T("交检部门不能为空!"));
		AfxMessageBox(str);
		Is_Change =  FALSE;
		return Is_Change;
	}


//新加的10项//
	//检查组长//
	GetDlgItem(IDC_EDIT1)->GetWindowText(strText);
	if(strcmp(strText,m_CurTaskInfo.stTaskBaseInfo.szCheckLeader) != 0)
	{
		memset(m_CurTaskInfo.stTaskBaseInfo.szCheckLeader, 0,sizeof(m_CurTaskInfo.stTaskBaseInfo.szCheckLeader));
		strcpy(m_CurTaskInfo.stTaskBaseInfo.szCheckLeader,strText);
		Is_Change = TRUE;
	}
	

	//工艺员//
	GetDlgItem(IDC_TECHNOLOGY_EDT)->GetWindowText(strText);
	if(strcmp(strText,m_CurTaskInfo.stTaskBaseInfo.szTechUser) != 0)
	{
		memset(m_CurTaskInfo.stTaskBaseInfo.szTechUser, 0,sizeof(m_CurTaskInfo.stTaskBaseInfo.szTechUser));
		strcpy(m_CurTaskInfo.stTaskBaseInfo.szTechUser,strText);
		Is_Change = TRUE;
	}

	//军检//
	pComBo = (CComboBox*)GetDlgItem(IDC_ARMY_TEST_COM);
	nSel = pComBo->GetCurSel();
	if(nSel < 0 || nSel >= pComBo->GetCount())
	{
		nSel = 0;
	}
	if(nSel != m_CurTaskInfo.stTaskBaseInfo.nArmyTest)
	{
		m_CurTaskInfo.stTaskBaseInfo.nArmyTest = nSel;
		Is_Change = TRUE;
	}

	//典试数量//
	GetDlgItem(IDC_DIANSHI_NUM_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	Num = atoi(strText);
	if(Num != m_CurTaskInfo.stTaskBaseInfo.nDianShiNum)
	{
		m_CurTaskInfo.stTaskBaseInfo.nDianShiNum = Num;
		Is_Change = TRUE;
	}
	//验收依据1//
	GetDlgItem(IDC_ACCORDING1_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	if(strcmp(strText,m_CurTaskInfo.stTaskBaseInfo.szAccording1) != 0)
	{
		memset(m_CurTaskInfo.stTaskBaseInfo.szAccording1, 0,sizeof(m_CurTaskInfo.stTaskBaseInfo.szAccording1));
		strcpy(m_CurTaskInfo.stTaskBaseInfo.szAccording1,strText);
		Is_Change = TRUE;
	}
	//验收依据2//
	GetDlgItem(IDC_ACCORDING2_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	if(strcmp(strText,m_CurTaskInfo.stTaskBaseInfo.szAccording2) != 0)
	{
		memset(m_CurTaskInfo.stTaskBaseInfo.szAccording2, 0,sizeof(m_CurTaskInfo.stTaskBaseInfo.szAccording2));
		strcpy(m_CurTaskInfo.stTaskBaseInfo.szAccording2,strText);
		Is_Change = TRUE;
	}
	//验收依据3//
	GetDlgItem(IDC_ACCORDING3_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	if(strcmp(strText,m_CurTaskInfo.stTaskBaseInfo.szAccording3) != 0)
	{
		memset(m_CurTaskInfo.stTaskBaseInfo.szAccording3, 0,sizeof(m_CurTaskInfo.stTaskBaseInfo.szAccording3));
		strcpy(m_CurTaskInfo.stTaskBaseInfo.szAccording3,strText);
		Is_Change = TRUE;
	}
	//验收依据4//
	GetDlgItem(IDC_ACCORDING4_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	if(strcmp(strText,m_CurTaskInfo.stTaskBaseInfo.szAccording4) != 0)
	{
		memset(m_CurTaskInfo.stTaskBaseInfo.szAccording4, 0,sizeof(m_CurTaskInfo.stTaskBaseInfo.szAccording4));
		strcpy(m_CurTaskInfo.stTaskBaseInfo.szAccording4,strText);
		Is_Change = TRUE;
	}

	//验收依据5//
	GetDlgItem(IDC_ACCORDING5_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	if(strcmp(strText,m_CurTaskInfo.stTaskBaseInfo.szAccording5) != 0)
	{
		memset(m_CurTaskInfo.stTaskBaseInfo.szAccording5, 0,sizeof(m_CurTaskInfo.stTaskBaseInfo.szAccording5));
		strcpy(m_CurTaskInfo.stTaskBaseInfo.szAccording5,strText);
		Is_Change = TRUE;
	}
	//备注//
	GetDlgItem(IDC_TASK_REMARK_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	if(strcmp(strText,m_CurTaskInfo.stTaskBaseInfo.szTaskRemark) != 0)
	{
		memset(m_CurTaskInfo.stTaskBaseInfo.szTaskRemark, 0,sizeof(m_CurTaskInfo.stTaskBaseInfo.szTaskRemark));
		strcpy(m_CurTaskInfo.stTaskBaseInfo.szTaskRemark,strText);
		Is_Change = TRUE;
	}

	//计划开始时间 //
	strText=GetCDateCtrlTime(IDC_PLAN_BEGTIME);
	if(strcmp(strText,m_CurTaskInfo.stTaskBaseInfo.szPlanBegTime) != 0)
	{
		memset(m_CurTaskInfo.stTaskBaseInfo.szPlanBegTime, 0,sizeof(m_CurTaskInfo.stTaskBaseInfo.szPlanBegTime));
		strcpy(m_CurTaskInfo.stTaskBaseInfo.szPlanBegTime,strText);
		Is_Change = TRUE;
	}
	//计划结束时间//
	strText=GetCDateCtrlTime(IDC_PLAN_ENDTIME);
	if(strcmp(strText,m_CurTaskInfo.stTaskBaseInfo.szPlanEndTime) != 0)
	{
		memset(m_CurTaskInfo.stTaskBaseInfo.szPlanEndTime, 0,sizeof(m_CurTaskInfo.stTaskBaseInfo.szPlanEndTime));
		strcpy(m_CurTaskInfo.stTaskBaseInfo.szPlanEndTime,strText);
		Is_Change = TRUE;
	}

	//检验组长//
	GetDlgItem(IDC_EDIT1)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	if(strcmp(strText,m_CurTaskInfo.stTaskBaseInfo.szCheckLeader) != 0)
	{
		memset(m_CurTaskInfo.stTaskBaseInfo.szCheckLeader, 0,sizeof(m_CurTaskInfo.stTaskBaseInfo.szCheckLeader));
		strcpy(m_CurTaskInfo.stTaskBaseInfo.szCheckLeader,strText);
		Is_Change = TRUE;
	}


	//检验员//
	GetDlgItem(IDC_CHECK_USER_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	if(strcmp(strText,m_CurTaskInfo.stTaskBaseInfo.szCheckUser) != 0)
	{
		memset(m_CurTaskInfo.stTaskBaseInfo.szCheckUser, 0,sizeof(m_CurTaskInfo.stTaskBaseInfo.szCheckUser));
		strcpy(m_CurTaskInfo.stTaskBaseInfo.szCheckUser,strText);
		Is_Change = TRUE;
	}
	
		
	//检查产品编号数量与配置是否一致//
	int nNum = m_CurTaskInfo.pArryTaskCode.size();

	int nRows = m_CurTaskInfo.stTaskBaseInfo.nCodeNumber;

	if(nNum != nRows)
	{
		CString strNum;
		strNum.Format(_T("任务要求检查 %d 项产品，实际选择了 %d 项"),nRows,nNum);
		AfxMessageBox(strNum);
		Is_Change = FALSE;
	}

	if(m_CurTaskInfo.stTaskBaseInfo.nModifyType == Task_ModifyAll)
	{
		Is_Change = TRUE;
	}
	return Is_Change;
}
CString CShowTaskInfo::GetCDateCtrlTime(UINT UID)
{
	int nHour,nMinute,nSecond;
	CString strTime;
	CTime nTime;
	CDateTimeCtrl *pCtrl = NULL;
	pCtrl = (CDateTimeCtrl*)GetDlgItem(UID);
	if(!pCtrl)
	{
		return _T("");
	}
	pCtrl->GetTime(nTime);

	//nTime.GetAsSystemTime(pTime);
	nHour = nTime.GetHour();
	nMinute = nTime.GetMinute();
	nSecond = nTime.GetSecond();
	strTime.Format(_T("%s %02d:%02d:%02d"),nTime.Format(_T("%Y-%m-%d")),nHour,nMinute,nSecond);
	return strTime;
}
//获得一项任务的基本信息//
void CShowTaskInfo::DisplayTaskInfo()
{
	StBasTask *pTaskInfo = &m_CurTaskInfo;
	StBasTaskBaseInfo *pTaskBaseInfo = &pTaskInfo->stTaskBaseInfo;
	StBasProduct      *pProductInfo = &pTaskInfo->stProductInfo;
	StHrUpDepart      *pUpDepartInfo = &pTaskInfo->stHrUpDepart;
	CString strText;
	SYSTEMTIME pTime;
	CTime nTime;

	
	strText.Format(_T("%s"), pTaskBaseInfo->szTaskName);
	GetDlgItem(IDC_TASK_NAME_EDT)->SetWindowText(strText);//1.任务名称
	GetDlgItem(IDC_PROJECT_NO_EDT)->SetWindowText(pTaskBaseInfo->szProjectNo);//2.检验单号
	GetDlgItem(IDC_TASK_STATUS_EDT)->SetWindowText(g_TaskState[pTaskBaseInfo->nTaskStatus]);//3.任任务状态

	SetTaskTypeComBoText(pTaskBaseInfo->nTaskType, (CComboBox*)GetDlgItem(IDC_TASK_TYPE_COM));//4.任务类型
	SetArmyTestComBoText(pTaskBaseInfo->nArmyTest, (CComboBox*)GetDlgItem(IDC_ARMY_TEST_COM));//是否军检
	
	strText.Format(_T("%s"), pUpDepartInfo->szUpDepartName);       //5.交检部门
	GetDlgItem(IDC_SHOWTASKINFO_DEPART_EDT)->SetWindowText(strText);
	
	GetDlgItem(IDC_PRODNAME_EDT)->SetWindowText(pProductInfo->szProductName);//6.产品名称
	GetDlgItem(IDC_PRODUCTNO_EDT)->SetWindowText(pProductInfo->szProductNo);//7.产品代号
	GetDlgItem(IDC_PRODUCTCODE_EDT)->SetWindowText(pTaskBaseInfo->szProductCode);//8.产品编号缩写
	
	strText.Format(_T("%d"),pTaskBaseInfo->nCodeNumber);
	GetDlgItem(IDC_PRODUCT_NUMBER_EDT)->SetWindowText(strText);//9.产品数量
	GetDlgItem(IDC_BATCH_EDT)->SetWindowText(pTaskBaseInfo->szBatch);//10.批次号
	GetDlgItem(IDC_PRODUCT_MODEL_EDT)->SetWindowText(pTaskBaseInfo->szModel);//11.型号
	GetDlgItem(IDC_PRODUCT_PHASE_EDT)->SetWindowText(pTaskBaseInfo->szPhase);//12.阶段
	GetDlgItem(IDC_UP_USER_EDT)->SetWindowText(pTaskBaseInfo->szUpUser);//13.交检人
	GetDlgItem(IDC_UP_TIME_EDT)->SetWindowText(pTaskBaseInfo->szUpDate);//14.交检日期
	GetDlgItem(IDC_CHECK_USER_EDT)->SetWindowText(pTaskBaseInfo->szCheckUser);//15.检验员姓名



	GetDlgItem(IDC_EDIT1)->SetWindowText(pTaskBaseInfo->szCheckLeader);//16.检验组长
	GetDlgItem(IDC_TECHNOLOGY_EDT)->SetWindowText(pTaskBaseInfo->szTechUser);//17.工艺员


	GetDlgItem(IDC_SEND_DATE_EDT)->SetWindowText(pTaskBaseInfo->szSendDate);//18.派发时间
	strText.Format(_T("%d"),pTaskBaseInfo->nDianShiNum);
	GetDlgItem(IDC_DIANSHI_NUM_EDT)->SetWindowText(strText);//19.典试数量
	GetDlgItem(IDC_ACCORDING1_EDT)->SetWindowText(pTaskBaseInfo->szAccording1);//20.检验依据1
	GetDlgItem(IDC_ACCORDING2_EDT)->SetWindowText(pTaskBaseInfo->szAccording2);//21.检验依据2
	GetDlgItem(IDC_ACCORDING3_EDT)->SetWindowText(pTaskBaseInfo->szAccording3);//22.检验依据3
	GetDlgItem(IDC_ACCORDING4_EDT)->SetWindowText(pTaskBaseInfo->szAccording4);//23.检验依据4
	GetDlgItem(IDC_ACCORDING5_EDT)->SetWindowText(pTaskBaseInfo->szAccording5);//24.检验依据5
	GetDlgItem(IDC_TASK_REMARK_EDT)->SetWindowText(pTaskBaseInfo->szTaskRemark);//25.备注
	
	nTime.GetCurrentTime();
	nTime.GetAsSystemTime(pTime);
	StringToTime(pTaskBaseInfo->szPlanBegTime,_T("%d-%d-%d %d:%d:%d"),pTime);
	((CDateTimeCtrl*)GetDlgItem(IDC_PLAN_BEGTIME))->SetTime(&pTime);//26.计划开始时间
	StringToTime(pTaskBaseInfo->szPlanEndTime,_T("%d-%d-%d %d:%d:%d"),pTime);
	((CDateTimeCtrl*)GetDlgItem(IDC_PLAN_ENDTIME))->SetTime(&pTime);//27.计划结束时间

	GetDlgItem(IDC_REAL_BEGTIME_EDT)->SetWindowText(pTaskBaseInfo->szRealBegTime);//28.实际开始时间
	GetDlgItem(IDC_REAL_ENDTIME_EDT)->SetWindowText(pTaskBaseInfo->szRealEndTime);//29.实际结束时间
	
	GetDlgItem(IDC_CREATE_TIME_EDT)->SetWindowText(pTaskBaseInfo->szCreateDate);//30.创建时间
	GetDlgItem(IDC_CREATE_USER_EDT)->SetWindowText(pTaskBaseInfo->szCreateUser);//31.创建人
	
	GetDlgItem(IDC_DOWNLOAD_DATE_EDT)->SetWindowText(pTaskBaseInfo->szDownLoadDate);//32.下载时间
	GetDlgItem(IDC_EDIT2)->SetWindowText(pTaskBaseInfo->szImportDate); //33.数据导入时间
	GetDlgItem(IDC_FINISH_DATE_EDT)->SetWindowText(pTaskBaseInfo->szFinishDate);//34.完成时间
	
		
	
	//任务编号//
	FindCurTaskProdNumbels();
	//任务使用模板//
	FindCurTaskModes();

	//任务选中的图号
	FindCurTaskPicNum();
	//组建任务详情//
	BuildTaskDetail();
	
	m_ShowTaskData.InitGridCtrl_NULL();
	m_ShowTaskData.PostMessage(WM_SIZE);

	//基于任务的精确查找///
	StTstResultBase *pResultBase = &m_ResultSearch.m_TstResultBase;
	memset(pResultBase,0,sizeof(StTstResultBase));
	pResultBase->nGroupOid = g_CurSelDepart.nOid;
	pResultBase->nTaskOid = pTaskBaseInfo->nOid;
	strcpy(pResultBase->szTaskName,pTaskBaseInfo->szTaskName);
	strcpy(pResultBase->szProductNo,pProductInfo->szProductNo);
	pResultBase->nResultType = Task_ExactSearch;
	m_ResultSearch.SearchBaseByTaskName();


	//2017-04-05  新版的结果数据查询//
	StBasTask  *pResultSearchInfo = &m_ResultSearchNew.m_ResultSearchInfo;
	pResultSearchInfo->Release();
	pResultSearchInfo->stTaskBaseInfo.nGroupOid = g_CurSelDepart.nOid;
	pResultSearchInfo->stTaskBaseInfo.nOid = pTaskBaseInfo->nOid;
	strcpy(pResultSearchInfo->stTaskBaseInfo.szTaskName,pTaskBaseInfo->szTaskName);
	strcpy(pResultSearchInfo->stProductInfo.szProductNo,pProductInfo->szProductNo);
	pResultSearchInfo->stTaskBaseInfo.nResultType = Task_ExactSearch;
	m_ResultSearchNew.m_ResultSearchInfoDlg.DisPalySearchInfo();
	m_ResultSearchNew.m_ResultSearchInfoDlg.OnBnClickedButton1();
}

void CShowTaskInfo::FindCurTaskProdNumbels()
{
	CEditableListCtrl *pList = &m_TaskCfg.m_TaskNumber;
	pList->DeleteAllItems();
	if(m_DMng.GetTaskCodeData(&m_CurTaskInfo,m_CurTaskInfo.stTaskBaseInfo.nOid))
	{
		int i,nIndex,nRows = m_CurTaskInfo.pArryTaskCode.size();
		CString strText=_T("");
		StBasTaskCode *pTaskCode = NULL;
		for( i = 0;i<nRows;i++)
		{

			pTaskCode = NULL;
			pTaskCode = m_CurTaskInfo.pArryTaskCode.at(i);
			if(pTaskCode == NULL)
			{
				continue;
			}
			strText.Format(_T("%d"),i+1);
			nIndex = pList->InsertItem(i,strText);
			strText.Format(_T("%s"),pTaskCode->szCodeName);
			pList->SetItemText(nIndex,1,strText);
			strText.Format(_T("%s"), GetDianshiText(pTaskCode->nDianshiTest));
			pList->SetItemText(nIndex,2,strText);
		}
	}
}


void CShowTaskInfo::FindCurTaskModes()
{
	CEditableListCtrl *pList = &m_TaskCfg.m_TaskMode;
	
	pList->DeleteAllItems();
	if(m_DMng.GetTaskModeData(&m_CurTaskInfo,m_CurTaskInfo.stTaskBaseInfo.nOid))
	{
		int i,nIndex,nRows = m_CurTaskInfo.pArryTaskMode.size();
		CString strText=_T("");
		StBasTaskMode *pTaskMode = NULL;
		for( i = 0;i<nRows;i++)
		{
			
			pTaskMode = NULL;
			pTaskMode = m_CurTaskInfo.pArryTaskMode.at(i);
			if(pTaskMode == NULL)
			{
				continue;
			}
			strText.Format(_T("%d"),i+1);
			nIndex = pList->InsertItem(i,strText);

			strText.Format(_T("%s"), pTaskMode->szModeName);
			pList->SetItemText(nIndex,1,strText);
			strText.Format(_T("%s"), GetModeType(pTaskMode->nModeType));
			pList->SetItemText(nIndex,2,strText);
			strText.Format(_T("%s"), GetModeRowVar(pTaskMode->nModeRowvar));
			pList->SetItemText(nIndex,3,strText);
		}
	}
}
void  CShowTaskInfo::FindCurTaskPicNum()
{
	CEditableListCtrl *pList = &m_TaskCfg.m_TaskPicNum;
	pList->DeleteAllItems();

	if(m_DMng.GetTaskPicNumData(&m_CurTaskInfo,m_CurTaskInfo.stTaskBaseInfo.nOid))
	{
		//vector<StBasTaskPicNum *> *pArryTaskPicNum = m_CurTaskInfo.pArryTaskPicNum;
		int i,nIndex,nRows = m_CurTaskInfo.pArryTaskPicNum.size();
		CString strNum=_T("");
		StBasTaskPicNum *pTaskPicNum = NULL;
		for( i = 0;i<nRows;i++)
		{
			//memset(&pTaskPicNum,0,sizeof(StBasTaskPicNum));
			pTaskPicNum = NULL;
			pTaskPicNum = m_CurTaskInfo.pArryTaskPicNum.at(i);
			if(pTaskPicNum == NULL)
			{
				continue;
			}
			strNum.Format(_T("%d"),i+1);
			nIndex = pList->InsertItem(i,strNum);
			pList->SetItemText(nIndex,1,pTaskPicNum->szPicNumNo);
			pList->SetItemText(nIndex,2,pTaskPicNum->szPicNumName);
		}
	}
}
void CShowTaskInfo::BuildTaskDetail()
{
	CEditableListCtrl *pList = &m_TaskCfg.m_TaskDecCfg;
	pList->DeleteAllItems();
	m_CurTaskInfo.ReleaseTaskResult();
	vector<StTstResultAtta *> *pArryTstResultBase = &m_CurTaskInfo.pArryTastResultBase;
	int nCodeCount,nModeCount,nPicNumCount;
	nCodeCount = m_CurTaskInfo.pArryTaskCode.size();
	nModeCount = m_CurTaskInfo.pArryTaskMode.size();
	nPicNumCount = m_CurTaskInfo.pArryTaskPicNum.size();
	vector<StBasTaskCode *> *pArryTaskCode = &m_CurTaskInfo.pArryTaskCode;
	vector<StBasTaskMode *> *pArryTaskMode = &m_CurTaskInfo.pArryTaskMode;
	vector<StBasTaskPicNum *> *pArryTaskPicNum = &m_CurTaskInfo.pArryTaskPicNum;

	int i,j;
	int nIndex,pos,nOid = 1;
	char szTmpProdNumber[XLS_MAX_LEN] = {0,};
	CString str;
	for(i = 0;i<nCodeCount;i++)
	{
		StBasTaskCode *pTaskCode = NULL;
		pTaskCode = pArryTaskCode->at(i);
		for(j = 0;j<nModeCount;j++)
		{

			StTstResultAtta *pTstResultBase = new StTstResultAtta;
			memset(pTstResultBase,0,sizeof(StTstResultAtta));
			StBasTaskMode *pTaskMode = NULL;
			pTaskMode = pArryTaskMode->at(j);
			pTstResultBase->nOid = nOid++;
			pTstResultBase->nTaskOid = m_CurTaskInfo.stTaskBaseInfo.nOid;
			strcpy(pTstResultBase->szProductName, m_CurTaskInfo.stProductInfo.szProductName);
			strcpy(pTstResultBase->szProductNo, m_CurTaskInfo.stProductInfo.szProductNo);
			pTstResultBase->nProductOid = m_CurTaskInfo.stProductInfo.nOid;
			
			strcpy(pTstResultBase->szModel, m_CurTaskInfo.stTaskBaseInfo.szModel);
			strcpy(pTstResultBase->szPhase, m_CurTaskInfo.stTaskBaseInfo.szPhase);

			strcpy(pTstResultBase->szProductCode, pTaskCode->szCodeName);
			pTstResultBase->nDianshiTest = pTaskCode->nDianshiTest;

			pTstResultBase->nModeOid = pTaskMode->nModeOid;
			strcpy(pTstResultBase->szModeName, pTaskMode->szModeName);
			pTstResultBase->nModeType = pTaskMode->nModeType;
			pTstResultBase->nModeRowVar = pTaskMode->nModeRowvar;

			pTstResultBase->nPicNumCount = nPicNumCount;
			pArryTstResultBase->push_back(pTstResultBase);


			nIndex =pTstResultBase->nOid;

			//1.
			str.Format("%3d", nIndex);
			nIndex = pList->InsertItem(nIndex-1, str);
			pList->SetItemData(nIndex,pTstResultBase->nModeOid);

			pos = 1;

			if (strcmp(szTmpProdNumber, pTstResultBase->szProductCode) != 0)
			{
				//2.	
				str.Format( _T("%s"), pTstResultBase->szProductCode);
				pList->SetItemText(nIndex, pos++, str);

				memset(szTmpProdNumber, 0, XLS_MAX_LEN);
				strcpy(szTmpProdNumber, pTstResultBase->szProductCode);
			}
			else
			{
				pos = 2;
			}


			//3.	
			str.Format( _T("%s"), pTstResultBase->szModeName);
			pList->SetItemText(nIndex, pos++, str);

			//4.	
			str.Format( _T("%s"), (pTstResultBase->nDianshiTest >=1 ? _T("是") : _T("否")));
			pList->SetItemText(nIndex, pos, str);
			pos++;

			//5.
			str.Format( _T("%s"), g_ModeType[pTstResultBase->nModeType]);
			pList->SetItemText(nIndex, pos++, str);

			//6.
			str.Format( _T("%s"), g_ModeRowVal[pTstResultBase->nModeRowVar]);
			pList->SetItemText(nIndex, pos++, str);

			//7.
			str.Format( _T("%d"), pTstResultBase->nPicNumCount);
			pList->SetItemText(nIndex, pos++, str);
			


		}
	}

	//预览任务列表//
	m_ShowTaskData.InitTaskDecList();
}




void CShowTaskInfo::OnTcnSelchangeShowtaskinfoTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nShowType;
	if ((nShowType = m_ShowTaskInfoTab.GetCurSel())==0)
	{
		SetControlShow(SW_SHOW);

		m_ShowTaskData.ShowWindow(SW_HIDE);

		m_ResultSearch.ShowWindow(SW_HIDE);
		m_ResultSearchNew.ShowWindow(SW_HIDE);

	}
	if (nShowType==1)
	{
		SetControlShow(SW_HIDE);

		m_ShowTaskData.ShowWindow(SW_SHOW);

		m_ResultSearch.ShowWindow(SW_HIDE);
		m_ResultSearchNew.ShowWindow(SW_HIDE);
	}
	if (nShowType==2)
	{
		SetControlShow(SW_HIDE);

		m_ShowTaskData.ShowWindow(SW_HIDE);

		m_ResultSearch.ShowWindow(SW_HIDE);
		m_ResultSearchNew.ShowWindow(SW_SHOW);

	}
	*pResult = 0;
}


BOOL CShowTaskInfo::SendTaskToPad()
{
	//检查是否满足确认条件///
	//1.产品编号不能为零，并且要和检查的产品总数保持一致//
	//2.检查  不允许没有一个模板的任务，确认 下发等操作//
	/*
	StBasTask *pTaskInfo = &m_CurTaskInfo;
	BOOL nState = FALSE;
	if(!pTaskInfo->stTaskBaseInfo.hItem || pTaskInfo->stTaskBaseInfo.TreeItemType != TASK_TREE_TYPE_TASK)
	{
		return FALSE;
	}

	CBatchExportTask m_BatchOutTask;
	m_BatchOutTask.m_BatchTaskArray.push_back(pTaskInfo);
	//m_BatchOutTask.BatchSendTask();
	

	g_pLeftTree->RefleshExecuteTree( );
	g_pLeftTree->RefleshFinishedTree( );
	
	CTreeCtrl *pTree = pTaskInfo->stTaskBaseInfo.pTaskTree;
	pTree->SelectItem(pTaskInfo->stTaskBaseInfo.hItem);
	int nIcon1 = GetTaskIcon(pTaskInfo->stTaskBaseInfo.nTaskStatus);
	pTree->SetItemImage(pTaskInfo->stTaskBaseInfo.hItem,nIcon1,nIcon1);

	//更新控件的信息和显示//
	GetDlgItem(IDC_TASK_STATUS_EDT)->SetWindowText(g_TaskState[pTaskInfo->stTaskBaseInfo.nTaskStatus]);
	GetDlgItem(IDC_SEND_DATE_EDT)->SetWindowText(pTaskInfo->stTaskBaseInfo.szSendDate);
	g_MainFram->m_wndOutput.InsertErrorText("任务导出完毕!");*/

	return TRUE;
}

BOOL CShowTaskInfo::StopTask()//中止这个任务//
{
	CTreeCtrl *pTree = m_CurTaskInfo.stTaskBaseInfo.pTaskTree;
	//开始更新导出的状态//
	m_CurTaskInfo.stTaskBaseInfo.nTaskStatus = Task_All;
	if(!m_DMng.EditOldTask(&m_CurTaskInfo))
	{
		AfxMessageBox(_T("更新任务状态时失败!"));
	}

	//更新当前任务的 树节点和任务状态//
	//设置焦点//
	pTree->SelectItem(m_CurTaskInfo.stTaskBaseInfo.hItem);
	int nIcon1 = GetTaskIcon(m_CurTaskInfo.stTaskBaseInfo.nTaskStatus);
	pTree->SetItemImage(m_CurTaskInfo.stTaskBaseInfo.hItem,nIcon1,nIcon1);


	//更新控件的信息和显示//
	GetDlgItem(IDC_TASK_STATUS_EDT)->SetWindowText(g_TaskState[m_CurTaskInfo.stTaskBaseInfo.nTaskStatus]);
	return TRUE;
}

BOOL CShowTaskInfo::DestroyWindow()
{
	return CDialog::DestroyWindow();
}

void CShowTaskInfo::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	if(m_ShowType != Tree_Modify_Task)
	{
		CTaskMng *pDlg = ((CTaskMng *)GetParent());
		pDlg->CTaskMng::OnCancel();
	}
}

void CShowTaskInfo::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	int ret = 0;
	int i, nCount;
	CString strText, str;
	vector<CString> strErrorArray;
	if(m_ShowType == View_Task)
	{
		if(1)
		{
			CTaskMng *pDlg = ((CTaskMng *)GetParent());
			pDlg->CTaskMng::OnCancel();
		}
		return;
	}
	ret = GetChangeTaskInfo();
	if(ret == 1)
	{
		if(1)
		{
			if(m_ShowType == Tree_Modify_Task)
			{
				ModifyTheTask(&m_CurTaskInfo, strErrorArray);
				g_MainFram->m_wndOutput.InsertErrorArrayText(strErrorArray);
				nCount = strErrorArray.size();
				for (i = 0;i<nCount;i++)
				{
					str.Format(_T("%d.%s\n"), i+1, strErrorArray.at(i));
					strText+=str;
				}

				AfxMessageBox(strText);
				strErrorArray.clear();
			}else
			{
				CTaskMng *pDlg = ((CTaskMng *)GetParent());
				pDlg->CTaskMng::OnOK();
			}
			
		}
	}
	
	
	//EditTast();
	//CDialog::OnOK();
}

//选择产品//
void CShowTaskInfo::OnBnClickedSelProductnoBtn()
{
	// TODO: 在此添加控件通知处理程序代码//
	CSelProductDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		GetDlgItem(IDC_PRODUCTNO_EDT)->SetWindowText(dlg.m_strProductNo);
		GetDlgItem(IDC_PRODNAME_EDT)->SetWindowText(dlg.m_strProductName);
	}
}

//选择交检部门//
void CShowTaskInfo::OnBnClickedSelUpdepartBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strUpDepartName;
	CSelUpDepartDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		strUpDepartName = dlg.m_UpDepartName;
		GetDlgItem(IDC_SHOWTASKINFO_DEPART_EDT)->SetWindowText(strUpDepartName);
	}
}

//选择检验组长//
void CShowTaskInfo::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CSelUserDlg Dlg;
	CString strUserName;
	if(Dlg.DoModal() == IDOK)
	{
		strUserName = Dlg.m_SelUserName;
		GetDlgItem(IDC_EDIT1)->SetWindowText(strUserName);
	}

}
//选择检验员//
void CShowTaskInfo::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CSelUserDlg Dlg;
	CString strUserName;
	if(Dlg.DoModal() == IDOK)
	{
		strUserName = Dlg.m_SelUserName;
		GetDlgItem(IDC_CHECK_USER_EDT)->SetWindowText(strUserName);
	}

}

