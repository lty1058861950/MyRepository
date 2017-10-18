// TaskModeMng.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "TaskModeMng.h"


// CTaskModeMng 对话框

IMPLEMENT_DYNAMIC(CTaskModeMng, CDialog)

CTaskModeMng::CTaskModeMng(CWnd* pParent /*=NULL*/)
	: CDialog(CTaskModeMng::IDD, pParent)
{
	m_pCurTaskInfo = NULL;
	m_pShowTaskInfo =NULL;
}

CTaskModeMng::~CTaskModeMng()
{
}

void CTaskModeMng::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHOWTASKINFO_CURTASKALLMODE_LIST, m_CurTaskAllModeList);
	DDX_Control(pDX, IDC_SHOWTASKINFO_TASKMODE_LIST, m_ShowTaskInfoModeList);
}


BEGIN_MESSAGE_MAP(CTaskModeMng, CDialog)
	ON_BN_CLICKED(IDC_SHOWTASKINFO_ADDALLMODE_BTN, &CTaskModeMng::OnBnClickedShowtaskinfoAddallmodeBtn)
	ON_BN_CLICKED(IDC_SHOWTASKINFO_ADDMODE_BTN, &CTaskModeMng::OnBnClickedShowtaskinfoAddmodeBtn)
	ON_BN_CLICKED(IDC_SHOWTASKINFO_DELMODE_BTN, &CTaskModeMng::OnBnClickedShowtaskinfoDelmodeBtn)
	ON_BN_CLICKED(IDC_SHOWTASKINFO_DELALLMODE_BTN, &CTaskModeMng::OnBnClickedShowtaskinfoDelallmodeBtn)
	ON_COMMAND_RANGE(IDC_CHECK1,IDC_CHECK3, OnUpdateChart )
END_MESSAGE_MAP()


// CTaskModeMng 消息处理程序

BOOL CTaskModeMng::OnInitDialog()
{
	CDialog::OnInitDialog();

	char *ColName2[] = {"序号","模板名称","模板类型","模板行可变"};
	int  ColWidth2[] = {50,100,80,80};
	m_ShowTaskInfoModeList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_GRIDLINES);

	for(int i = 0;i<4;i++)
	{
		m_ShowTaskInfoModeList.InsertColumn(i, ColName2[i],LVCFMT_CENTER, ColWidth2[i]);
	}
	m_ShowTaskInfoModeList.EnableRClickMenu(FALSE);

	char *ColName3[] = {"序号","模板名称","模板类型","模板行可变"};
	int  ColWidth3[] = {50,100,80,80};
	m_CurTaskAllModeList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_GRIDLINES);

	for(int i = 0;i<4;i++)
	{
		m_CurTaskAllModeList.InsertColumn(i, ColName3[i],LVCFMT_CENTER, ColWidth3[i]);
	}
	m_CurTaskAllModeList.EnableRClickMenu(FALSE);

	////
	StBasProduct *pProductInfo = &m_pCurTaskInfo->stProductInfo;
	((CButton *)GetDlgItem(IDC_CHECK1))->SetCheck(TRUE);
	if(pProductInfo->nPicNumType == Product_normal)
	{
		((CButton *)GetDlgItem(IDC_CHECK2))->SetCheck(TRUE);
		((CButton *)GetDlgItem(IDC_CHECK3))->SetCheck(FALSE);
		((CButton *)GetDlgItem(IDC_CHECK3))->EnableWindow(FALSE);
	}else
	{
		((CButton *)GetDlgItem(IDC_CHECK2))->SetCheck(FALSE);
		((CButton *)GetDlgItem(IDC_CHECK2))->EnableWindow(FALSE);
		((CButton *)GetDlgItem(IDC_CHECK3))->SetCheck(TRUE);
	}
	FindCurTaskModes();


	m_ShowTaskInfoModeList.DeleteAllItems();

	int pos;
	vector<StBasTaskMode *> *pArryTaskMode = &m_pCurTaskInfo->pArryTaskMode;
	int i,nIndex,nRows = pArryTaskMode->size();
	CString strNum;
	StBasTaskMode *pTaskMode;
	for( i = 0;i<nRows;i++)
	{
		pTaskMode = pArryTaskMode->at(i);
		strNum.Format(_T("%d"),i+1);
		pos = 1;
		nIndex = m_ShowTaskInfoModeList.InsertItem(i,strNum);
		m_ShowTaskInfoModeList.SetItemData(i,pTaskMode->nModeOid);
		m_ShowTaskInfoModeList.SetItemText(nIndex,pos++,pTaskMode->szModeName);
		m_ShowTaskInfoModeList.SetItemText(nIndex,pos++,g_ModeType[pTaskMode->nModeType]);
		m_ShowTaskInfoModeList.SetItemText(nIndex,pos++,g_ModeRowVal[pTaskMode->nModeRowvar]);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
//添加所有可用模板//
void CTaskModeMng::OnBnClickedShowtaskinfoAddallmodeBtn()
{
	//m_ShowTaskInfoModeList.DeleteAllItems();
	int nRows = m_CurTaskAllModeList.GetItemCount();
	CString strNum,strModeName,strModeType,strModeRowVal;
	for(int i = 0;i<nRows;i++)
	{
		strNum.Format(_T("%d"),i+1);
		strModeName=m_CurTaskAllModeList.GetItemText(i,1);
		strModeType = m_CurTaskAllModeList.GetItemText(i,2);
		strModeRowVal = m_CurTaskAllModeList.GetItemText(i,3);
		UINT nModeOid = m_CurTaskAllModeList.GetItemData(i);
		if(CheckListRepeatText(&m_ShowTaskInfoModeList,1,nModeOid))
		{
			continue;
		}
		m_ShowTaskInfoModeList.InsertItem(i,strNum);
		m_ShowTaskInfoModeList.SetItemData(i,nModeOid);
		m_ShowTaskInfoModeList.SetItemText(i,1,strModeName);
		m_ShowTaskInfoModeList.SetItemText(i,2,strModeType);
		m_ShowTaskInfoModeList.SetItemText(i,3,strModeRowVal);

	}

}
//添加模板//
void CTaskModeMng::OnBnClickedShowtaskinfoAddmodeBtn()
{
	int index = m_CurTaskAllModeList.GetFirstSelectedItem();
	if(index<0)
		return;

	CString strModeName,strModeType,strModeRowVal;
	strModeName = m_CurTaskAllModeList.GetItemText(index,1);
	strModeType = m_CurTaskAllModeList.GetItemText(index,2);
	strModeRowVal = m_CurTaskAllModeList.GetItemText(index,3);
	UINT nModeOid = m_CurTaskAllModeList.GetItemData(index);
	if(CheckListRepeatText(&m_ShowTaskInfoModeList,1,nModeOid))
	{
		AfxMessageBox(_T("已经添加了这项!"));
		return;
	}
	int nRow = m_ShowTaskInfoModeList.GetItemCount();
	CString strNum;
	strNum.Format(_T("%d"),nRow+1);
	m_ShowTaskInfoModeList.InsertItem(nRow,strNum);
	m_ShowTaskInfoModeList.SetItemData(nRow,nModeOid);
	m_ShowTaskInfoModeList.SetItemText(nRow,1,strModeName);
	m_ShowTaskInfoModeList.SetItemText(nRow,2,strModeType);
	m_ShowTaskInfoModeList.SetItemText(nRow,3,strModeRowVal);
}
//移除模板//
void CTaskModeMng::OnBnClickedShowtaskinfoDelmodeBtn()
{
	int index = -1;
	while(1)
	{
		index = m_ShowTaskInfoModeList.GetFirstSelectedItem();
		if(index<0)
			return;
		m_ShowTaskInfoModeList.DeleteItem(index);
	}

}
//移除所有模板//
void CTaskModeMng::OnBnClickedShowtaskinfoDelallmodeBtn()
{
	m_ShowTaskInfoModeList.DeleteAllItems();
}

//检查是否有重复内容///
BOOL CTaskModeMng::CheckListRepeatText(void *nList,int index,UINT nModeOid)
{
	if(!nList)
		return TRUE;
	CEditableListCtrl* pList = (CEditableListCtrl*)nList;
	int nCount = pList->GetItemCount();
	for(int i = 0;i<nCount;i++)
	{
		if(nModeOid == pList->GetItemData(i))
		{
			return TRUE;
		}
	}
	return FALSE;
}



void CTaskModeMng::FindCurTaskModes()
{
	m_CurTaskAllModeList.DeleteAllItems();
	

	CListCtrl *pList = &m_CurTaskAllModeList;
	vector<StBasMode > nModeArry;
	StBasMode stModeSearchInfo;
	memset(&stModeSearchInfo, 0, sizeof(StBasMode));

	UINT nGroupOid = g_CurSelDepart.nOid;
	CString strProductNo = _T("");
	m_pShowTaskInfo->GetDlgItem(IDC_PRODUCTNO_EDT)->GetWindowText(strProductNo);
	strcpy(stModeSearchInfo.stProductInfo.szProductNo, strProductNo);
	
	if(((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck())
	{
		if(m_DMng.GetGroupModeTypeData(nGroupOid, Mode_Currency, &nModeArry))
		{
			int i,nCount,Index;
			CString strNum;
			nCount = nModeArry.size();
			for (i = 0;i<nCount;i++)
			{
				Index = pList->GetItemCount();
				strNum.Format(_T("%d"),Index+1);
				pList->InsertItem(Index,strNum);
				pList->SetItemData(Index,nModeArry.at(i).nOid);
				pList->SetItemText(Index,1,nModeArry.at(i).szModeName);
				pList->SetItemText(Index,2,g_ModeType[nModeArry.at(i).nModeType]);
				pList->SetItemText(Index,3,g_ModeRowVal[nModeArry.at(i).nModeRowVar]);

			}
			nModeArry.clear();
		}
		
	}

	if(((CButton *)GetDlgItem(IDC_CHECK2))->GetCheck())
	{
		stModeSearchInfo.bModeDedicated  = Sel_Check;
		if(m_DMng.GetGroupModeInfo(nGroupOid, &stModeSearchInfo, &nModeArry))
		{
			int i,nCount,Index;
			CString strNum;
			nCount = nModeArry.size();
			for (i = 0;i<nCount;i++)
			{
				Index = pList->GetItemCount();
				strNum.Format(_T("%d"),Index+1);
				pList->InsertItem(Index,strNum);
				pList->SetItemData(Index,nModeArry.at(i).nOid);
				pList->SetItemText(Index,1,nModeArry.at(i).szModeName);
				pList->SetItemText(Index,2,g_ModeType[nModeArry.at(i).nModeType]);
				pList->SetItemText(Index,3,g_ModeRowVal[nModeArry.at(i).nModeRowVar]);

			}
			nModeArry.clear();
		}
	}

	if(((CButton *)GetDlgItem(IDC_CHECK3))->GetCheck())
	{
		if(m_DMng.GetGroupModeTypeData(nGroupOid, Mode_LineDed, &nModeArry))
		{
			int i,nCount,Index;
			CString strNum;
			nCount = nModeArry.size();
			for (i = 0;i<nCount;i++)
			{
				Index = pList->GetItemCount();
				strNum.Format(_T("%d"),Index+1);
				pList->InsertItem(Index,strNum);
				pList->SetItemData(Index,nModeArry.at(i).nOid);
				pList->SetItemText(Index,1,nModeArry.at(i).szModeName);
				pList->SetItemText(Index,2,g_ModeType[nModeArry.at(i).nModeType]);
				pList->SetItemText(Index,3,g_ModeRowVal[nModeArry.at(i).nModeRowVar]);

			}
			nModeArry.clear();
		}
	}

	
}

void CTaskModeMng::OnOK()
{
	CString strText;
	int i,nCount = 0;
	CEditableListCtrl *pList1 = &m_pShowTaskInfo->m_TaskCfg.m_TaskMode;
	pList1->DeleteAllItems();
	CEditableListCtrl *pList2 = &m_ShowTaskInfoModeList;
	StBasMode  nModeInfo;
	UINT  nModeOid = 0;
	int pos;

	nCount = pList2->GetItemCount();
	m_pCurTaskInfo->ReleaseMode();
	m_pCurTaskInfo->stTaskBaseInfo.nModifyType = Task_ModifyAll;
	for (i = 0;i<nCount;i++)
	{
		StBasTaskMode *pTaskMode = new StBasTaskMode;
		nModeOid = pList2->GetItemData(i);
		memset(pTaskMode,0,sizeof(StBasTaskMode));
		memset(&nModeInfo,0,sizeof(StBasMode));
		if(m_DMng.GetModeDataOid(nModeOid, &nModeInfo))
		{

		}

		pTaskMode->nTaskOid = m_pCurTaskInfo->stTaskBaseInfo.nOid;
		pTaskMode->nModeIndex = i+1;
		pTaskMode->nModeOid = nModeInfo.nOid;
		strcpy(pTaskMode->szModeName,nModeInfo.szModeName);
		pTaskMode->nModeType = nModeInfo.nModeType;
		pTaskMode->nModeRowvar = nModeInfo.nModeRowVar;
		

		m_pCurTaskInfo->pArryTaskMode.push_back(pTaskMode);

		
		pos = 1;
		strText.Format("%d",i+1);
		pList1->InsertItem(i,strText);
		pList1->SetItemData(i,nModeInfo.nOid);
		pList1->SetItemText(i,pos++,nModeInfo.szModeName);
		pList1->SetItemText(i,pos++,GetModeType(nModeInfo.nModeType));
		pList1->SetItemText(i,pos++,GetModeRowVar(nModeInfo.nModeRowVar));

		nModeInfo.Release();

	}

	//重新组建信息//
	m_pShowTaskInfo->BuildTaskDetail();

	
	CDialog::OnOK();
}

void CTaskModeMng::OnUpdateChart(UINT nID)
{
	if (nID>=IDC_CHECK1 &&nID <= IDC_CHECK3)
	{
		CButton * pButt= (CButton*)GetDlgItem(nID) ;
		if (pButt!=NULL)
		{
			//pButt->SetCheck(pButt->GetCheck()) ;
			FindCurTaskModes();
		}
		
	}
}
