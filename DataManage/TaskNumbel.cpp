// TaskNumbel.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "TaskNumbel.h"


// CTaskNumbel 对话框

IMPLEMENT_DYNAMIC(CTaskNumbelMng, CDialog)

CTaskNumbelMng::CTaskNumbelMng(CWnd* pParent /*=NULL*/)
	: CDialog(CTaskNumbelMng::IDD, pParent)
{
	m_pCurTaskInfo = NULL;
	m_pShowTaskInfo =NULL;
}

CTaskNumbelMng::~CTaskNumbelMng()
{
	m_ExcelOptFun.DeleteItemInfo();
}

void CTaskNumbelMng::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHOWTASKINFO_NUMBEL_LIST, m_ShowTaskInfoNumbelsList);
}


BEGIN_MESSAGE_MAP(CTaskNumbelMng, CDialog)
	ON_BN_CLICKED(IDC_SHOWTASKINFO_ADDPRODNUMBEL_BTN, &CTaskNumbelMng::OnBnClickedShowtaskinfoAddprodnumbelBtn)
	ON_BN_CLICKED(IDC_SHOWTASKINFO_BATCHLOAD_BNT, &CTaskNumbelMng::OnBnClickedShowtaskinfoBatchloadBnt)
	ON_BN_CLICKED(IDC_SHOWTASKINFO_DELNUM_BNT, &CTaskNumbelMng::OnBnClickedShowtaskinfoDelnumBnt)
	ON_BN_CLICKED(IDC_SHOWTASKINFO_NUMDELALL_BNT, &CTaskNumbelMng::OnBnClickedShowtaskinfoNumdelallBnt)
END_MESSAGE_MAP()


// CTaskNumbel 消息处理程序
BOOL CTaskNumbelMng::OnInitDialog()
{
	CDialog::OnInitDialog();
	char *ColName1[] = {"序号","产品编号",_T("典试")};
	int  ColWidth1[] = {50,100,100};
	m_ShowTaskInfoNumbelsList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_GRIDLINES);

	for(int i = 0;i<3;i++)
	{
		m_ShowTaskInfoNumbelsList.InsertColumn(i, ColName1[i],LVCFMT_CENTER, ColWidth1[i]);
	}
	m_ShowTaskInfoNumbelsList.EnableRClickMenu(FALSE);


	m_ExcelOptFun.NewItemInfo();

	FindCurTaskProdNumbels();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

//添加产品编号//
void CTaskNumbelMng::OnBnClickedShowtaskinfoAddprodnumbelBtn()
{
	CString strText;
	GetDlgItem(IDC_SHOWTASKINFO_LOADPRODNUMBEL_EDT)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();
	if(strText.IsEmpty())
	{
		return;
	}
	if(CheckListRepeatText(&m_ShowTaskInfoNumbelsList,1,strText))
	{
		AfxMessageBox(_T("已经添加了这项!"));
		return;
	}
	int nRow = m_ShowTaskInfoNumbelsList.GetItemCount();
	CString strNum;
	strNum.Format(_T("%d"),nRow+1);
	m_ShowTaskInfoNumbelsList.InsertItem(nRow,strNum);
	MyList_SetListItemEdit(&m_ShowTaskInfoNumbelsList, nRow, 2);
	m_ShowTaskInfoNumbelsList.SetItemText(nRow,1,strText);
}

int CTaskNumbelMng::MyList_SetListItemEdit(CListCtrl *pList, int row, int col)					//设置单元格可更改
{
	CEditableListCtrl *pEditList = (CEditableListCtrl*) pList;
	pEditList->SetEditable(FALSE);
	pEditList->AddEditCell(row,col);
	//pEditList->EnableEditButton(TRUE);
	return 1;
}
BOOL CTaskNumbelMng::ContinueAddProdNumbel(CString &OutInfo)
{
	int nRow = m_ExcelOptFun.m_row;
	int nCount = m_ShowTaskInfoNumbelsList.GetItemCount();
	int RePeast = 0,Succeed = 0;
	CString strNum,strReText;
	for(int i = 0;i<nRow-1;i++)
	{
		if(CheckListRepeatText(&m_ShowTaskInfoNumbelsList,1,m_ExcelOptFun.m_ItemInfo[i+1][1]))
		{
			RePeast++;
			strReText+=m_ExcelOptFun.m_ItemInfo[i+1][1];
			strReText+=_T("  ");
			continue;
		}
		Succeed++;
		strNum.Format(_T("%d"),nCount+1);
		m_ShowTaskInfoNumbelsList.InsertItem(nCount,strNum);
		m_ShowTaskInfoNumbelsList.SetItemText(nCount++,1,m_ExcelOptFun.m_ItemInfo[i+1][1]);
	}
	OutInfo.Format(_T("成功导入 %d 项, 重复的有 %d 项,分别：%s"),Succeed,RePeast,strReText);
	return TRUE;
}
//批量添加产品编号///
void CTaskNumbelMng::OnBnClickedShowtaskinfoBatchloadBnt()
{
	CFileDialog *lpszOpenFile;    //定义一个CfileDialog对象
	lpszOpenFile = new CFileDialog(TRUE,"","",OFN_FILEMUSTEXIST |OFN_HIDEREADONLY , "文件类型(*.xls;*.xlsx)|*.xls;*.xlsx||");//生成一个对话框
	if(lpszOpenFile->DoModal() == IDOK)//假如点击对话框确定按钮
	{
		CString	szGetName,OutInfo;
		szGetName = lpszOpenFile->GetPathName();	//得到打开文件的路径

		m_ExcelOptFun.ClearParamInfo();
		m_ExcelOptFun.ReadExcelFile(szGetName);

		if(ContinueAddProdNumbel(OutInfo))
		{
			AfxMessageBox(OutInfo);
		}

	}
}
//移除编号//
void CTaskNumbelMng::OnBnClickedShowtaskinfoDelnumBnt()
{
	int index = -1;
	while(1)
	{
		index = m_ShowTaskInfoNumbelsList.GetFirstSelectedItem();
		if(index<0)
			return;
		m_ShowTaskInfoNumbelsList.DeleteItem(index);
	}

}
//移除所有编号//
void CTaskNumbelMng::OnBnClickedShowtaskinfoNumdelallBnt()
{
	m_ShowTaskInfoNumbelsList.DeleteAllItems();
}
//检查是否有重复内容///
BOOL CTaskNumbelMng::CheckListRepeatText(void *nList,int index,CString strText)
{
	if(!nList)
		return TRUE;
	CEditableListCtrl* pList = (CEditableListCtrl*)nList;
	int nCount = pList->GetItemCount();
	for(int i = 0;i<nCount;i++)
	{
		if(strText == pList->GetItemText(i,index))
		{
			return TRUE;
		}
	}
	return FALSE;
}

void CTaskNumbelMng::FindCurTaskProdNumbels()
{
	m_ShowTaskInfoNumbelsList.DeleteAllItems();
	
	vector<StBasTaskCode *> *pArryTaskCode = &m_pCurTaskInfo->pArryTaskCode;
	int i,nIndex,nRows = pArryTaskCode->size();
	CString strNum;
	StBasTaskCode *pTaskCode;
	for( i = 0;i<nRows;i++)
	{
		pTaskCode = pArryTaskCode->at(i);
		strNum.Format(_T("%d"),i+1);
		nIndex = m_ShowTaskInfoNumbelsList.InsertItem(i,strNum);
		m_ShowTaskInfoNumbelsList.SetItemText(nIndex,1,pTaskCode->szCodeName);
		m_ShowTaskInfoNumbelsList.SetItemText(nIndex,2,pTaskCode->nDianshiTest>0 ? _T("1"):_T("0"));
		MyList_SetListItemEdit(&m_ShowTaskInfoNumbelsList, nIndex, 2);
	}
	

	
}


void CTaskNumbelMng::OnOK()
{
	
	CString strText;
	int i,nCount = 0;
	int pos;
	CEditableListCtrl *pList1 = &m_pShowTaskInfo->m_TaskCfg.m_TaskNumber;
	pList1->DeleteAllItems();
	CEditableListCtrl *pList2 = &m_ShowTaskInfoNumbelsList;

	
	nCount = pList2->GetItemCount();
	m_pCurTaskInfo->ReleaseCode();
	m_pCurTaskInfo->stTaskBaseInfo.nModifyType = Task_ModifyAll;
	CString strCodeName,strDianshi;
	
	for (i = 0;i<nCount;i++)
	{
		StBasTaskCode *pTaskCode = new StBasTaskCode;
		memset(pTaskCode,0,sizeof(StBasTaskCode));

		strCodeName = pList2->GetItemText(i,1);
		strDianshi = pList2->GetItemText(i,2);
		
		pTaskCode->nTaskOid = m_pCurTaskInfo->stTaskBaseInfo.nOid;
		pTaskCode->nCodeIndex = i+1;
		pTaskCode->nDianshiTest = atoi(strDianshi);
		strcpy(pTaskCode->szCodeName,strCodeName);
		m_pCurTaskInfo->pArryTaskCode.push_back(pTaskCode);
		pos = 1;
		strText.Format("%d",i+1);
		pList1->InsertItem(i,strText);
		pList1->SetItemText(i,pos++,pTaskCode->szCodeName);
		pList1->SetItemText(i,pos++,GetDianshiText(pTaskCode->nDianshiTest));
		
	}
	//重新组建数据//
	m_pShowTaskInfo->BuildTaskDetail();

	//更新界面的产品数量//
	strText.Format(_T("%d"), nCount);
	m_pShowTaskInfo->GetDlgItem(IDC_PRODUCT_NUMBER_EDT)->SetWindowText(strText);


	CDialog::OnOK();
}
