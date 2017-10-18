// TaskPicNum.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "TaskPicNum.h"


// CTaskPicNum 对话框

IMPLEMENT_DYNAMIC(CTaskPicNum, CDialog)

CTaskPicNum::CTaskPicNum(CWnd* pParent /*=NULL*/)
	: CDialog(CTaskPicNum::IDD, pParent)
{
	m_pCurTaskInfo = NULL;
	m_pShowTaskInfo =NULL;
}

CTaskPicNum::~CTaskPicNum()
{
}

void CTaskPicNum::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ALLPICNUM_LIST, m_AllPicNumList);
	DDX_Control(pDX, IDC_SEL_PICNUM_LIST, m_SelPicNumList);
}


BEGIN_MESSAGE_MAP(CTaskPicNum, CDialog)
	ON_BN_CLICKED(IDC_ALLADD_BTN, &CTaskPicNum::OnBnClickedAlladdBtn)
	ON_BN_CLICKED(IDC_ADD_BTN, &CTaskPicNum::OnBnClickedAddBtn)
	ON_BN_CLICKED(IDC_DEL_BTN, &CTaskPicNum::OnBnClickedDelBtn)
	ON_BN_CLICKED(IDC_ALLDEL_BTN, &CTaskPicNum::OnBnClickedAlldelBtn)
END_MESSAGE_MAP()


// CTaskPicNum 消息处理程序
void CTaskPicNum::InitPicNumList()
{
	if(m_pCurTaskInfo == NULL)
	{
		return;
	}
	int i, nCount, pos;
	CString strNum;
	m_AllPicNumList.DeleteAllItems();
	CEditableListCtrl *pList = &m_AllPicNumList;
	vector<StBasPicNum> stPicNumArray;
	if(m_DMng.GetProductPicNumInfo(m_pCurTaskInfo->stProductInfo.nOid,&stPicNumArray))
	{
		nCount = stPicNumArray.size();
		for (i = 0;i<nCount;i++)
		{
			pos = 1;
			strNum.Format(_T("%d"), i+1);
			pList->InsertItem(i,strNum);
			pList->SetItemData(i,stPicNumArray.at(i).nOid);
			pList->SetItemText(i,pos++,stPicNumArray.at(i).szPicNumNo);
			pList->SetItemText(i,pos++,stPicNumArray.at(i).szPicNumName);
		}
	}else
	{
		//AfxMessageBox(_T("初始化"));
	}

	stPicNumArray.clear();

	m_SelPicNumList.DeleteAllItems();

	pList = &m_SelPicNumList;
	vector<StBasTaskPicNum *> *pArryTaskPicNum = &m_pCurTaskInfo->pArryTaskPicNum;
	nCount = pArryTaskPicNum->size();
	
	StBasTaskPicNum *pTaskPicNum;
	for( i = 0;i<nCount;i++)
	{
		pos =1;
		pTaskPicNum = pArryTaskPicNum->at(i);
		strNum.Format(_T("%d"),i+1);
		pList->InsertItem(i,strNum);
		pList->SetItemData(i,pTaskPicNum->nOid);
		pList->SetItemText(1,pos++,pTaskPicNum->szPicNumNo);
		pList->SetItemText(1,pos++,pTaskPicNum->szPicNumName);
	}
}
void CTaskPicNum::OnBnClickedAlladdBtn()
{
	m_SelPicNumList.DeleteAllItems();
	int nRows = m_AllPicNumList.GetItemCount();
	CString strNum,strText;
	for(int i = 0;i<nRows;i++)
	{
		strNum.Format(_T("%d"),i+1);
		strText=m_AllPicNumList.GetItemText(i,1);
		UINT nPicNumOid = m_AllPicNumList.GetItemData(i);
		
		if(CheckListRepeatText(&m_SelPicNumList,1,nPicNumOid))
		{
			continue;
		}
		m_SelPicNumList.InsertItem(i,strNum);
		m_SelPicNumList.SetItemData(i,nPicNumOid);
		m_SelPicNumList.SetItemText(i,1,strText);

	}
	
}

void CTaskPicNum::OnBnClickedAddBtn()
{
	int index = m_AllPicNumList.GetFirstSelectedItem();
	if(index<0)
		return;

	CString strText = m_AllPicNumList.GetItemText(index,1);
	UINT nPicNumOid = m_AllPicNumList.GetItemData(index);
	if(CheckListRepeatText(&m_SelPicNumList,1,nPicNumOid))
	{
		AfxMessageBox(_T("已经添加了这项!"));
		return;
	}
	int nRow = m_SelPicNumList.GetItemCount();
	CString strNum;
	strNum.Format(_T("%d"),nRow+1);
	m_SelPicNumList.InsertItem(nRow,strNum);
	m_SelPicNumList.SetItemData(nRow,nPicNumOid);
	m_SelPicNumList.SetItemText(nRow,1,strText);
}

void CTaskPicNum::OnBnClickedDelBtn()
{
	int index = -1;
	while(1)
	{
		index = m_SelPicNumList.GetFirstSelectedItem();
		if(index<0)
			return;
		m_SelPicNumList.DeleteItem(index);
	}
}

void CTaskPicNum::OnBnClickedAlldelBtn()
{
	m_SelPicNumList.DeleteAllItems();
}
//检查是否有重复内容///
BOOL CTaskPicNum::CheckListRepeatText(void *nList,int index,UINT nPicNumOid)
{
	if(!nList)
		return TRUE;
	CEditableListCtrl* pList = (CEditableListCtrl*)nList;
	int nCount = pList->GetItemCount();
	for(int i = 0;i<nCount;i++)
	{
		if(nPicNumOid == pList->GetItemData(i))
		{
			return TRUE;
		}
	}
	return FALSE;
}
BOOL CTaskPicNum::OnInitDialog()
{
	CDialog::OnInitDialog();

	char *ColName1[] = {"序号","图号代号",_T("图号名称")};
	int  ColWidth1[] = {50,100,100};
	m_AllPicNumList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_GRIDLINES);

	for(int i = 0;i<3;i++)
	{
		m_AllPicNumList.InsertColumn(i, ColName1[i],LVCFMT_CENTER, ColWidth1[i]);
	}
	m_AllPicNumList.EnableRClickMenu(FALSE);

	char *ColName2[] = {"序号","图号代号",_T("图号名称")};
	int  ColWidth2[] = {50,100,100};
	m_SelPicNumList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_GRIDLINES);

	for(int i = 0;i<3;i++)
	{
		m_SelPicNumList.InsertColumn(i, ColName2[i],LVCFMT_CENTER, ColWidth2[i]);
	}
	m_SelPicNumList.EnableRClickMenu(FALSE);


	
	InitPicNumList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CTaskPicNum::OnOK()
{
	CString strText;
	int i,nCount = 0;
	UINT nPicNumOid;
	CEditableListCtrl *pList1 = &m_pShowTaskInfo->m_TaskCfg.m_TaskPicNum;
	pList1->DeleteAllItems();
	CEditableListCtrl *pList2 = &m_SelPicNumList;
	
	m_pCurTaskInfo->ReleasePicNum();
	nCount = pList2->GetItemCount();

	m_pCurTaskInfo->stTaskBaseInfo.nModifyType = Task_ModifyAll;
	
	StBasPicNum  nPicNumInfo;
	int pos;
	for (i = 0;i<nCount;i++)
	{
		StBasTaskPicNum *pTaskPicNum = new StBasTaskPicNum;
		memset(pTaskPicNum,0,sizeof(StBasTaskPicNum));
		memset(&nPicNumInfo,0,sizeof(StBasPicNum));

		nPicNumOid = pList2->GetItemData(i);
		if(m_DMng.GetPicNumDataFromOid(nPicNumOid,&nPicNumInfo))
		{

		}
		
		pTaskPicNum->nTaskOid = m_pCurTaskInfo->stTaskBaseInfo.nOid;
		pTaskPicNum->nPicNumOid = nPicNumInfo.nOid;
		pTaskPicNum->nPicNumIndex = i+1;
		strcpy(pTaskPicNum->szPicNumNo,nPicNumInfo.szProductNo);
		strcpy(pTaskPicNum->szPicNumName,nPicNumInfo.szPicNumName);

		m_pCurTaskInfo->pArryTaskPicNum.push_back(pTaskPicNum);
		pos = 1;
		strText.Format("%d",i+1);
		pList1->InsertItem(i,strText);
		pList1->SetItemData(i, nPicNumInfo.nOid);
		pList1->SetItemText(i,pos++,nPicNumInfo.szPicNumNo);
		pList1->SetItemText(i,pos++,nPicNumInfo.szPicNumName);

	}

	//重新组建信息//
	m_pShowTaskInfo->BuildTaskDetail();

	CDialog::OnOK();
}
