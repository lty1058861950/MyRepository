// SelDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "SelDlg.h"
#include "BatchExportTask.h"

// CSelDlg 对话框

IMPLEMENT_DYNAMIC(CSelDlg, CDialog)

CSelDlg::CSelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelDlg::IDD, pParent)
{
	m_nType = 0;
}

CSelDlg::~CSelDlg()
{
}

void CSelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_SrcList);
	DDX_Control(pDX, IDC_LIST2, m_DecList);
}


BEGIN_MESSAGE_MAP(CSelDlg, CDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_FIND_BTN, &CSelDlg::OnBnClickedFindBtn)
	ON_BN_CLICKED(IDC_ALL_SEL_BTN, &CSelDlg::OnBnClickedAllSelBtn)
	ON_BN_CLICKED(IDC_SINGLE_SEL_BTN, &CSelDlg::OnBnClickedSingleSelBtn)
	ON_BN_CLICKED(IDC_SINGLE_DEL_BTN, &CSelDlg::OnBnClickedSingleDelBtn)
	ON_BN_CLICKED(IDC_ALL_DEL_BTN, &CSelDlg::OnBnClickedAllDelBtn)
END_MESSAGE_MAP()


// CSelDlg 消息处理程序

BOOL CSelDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_SrcList.EnableRClickMenu(FALSE);
	m_DecList.EnableRClickMenu(FALSE);

	switch(m_nType)
	{
	case Sel_Product:
		{
			DisPalyProductSel();
		}
		break;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSelDlg::OnOK()
{
	
	switch(m_nType)
	{
	case Sel_Product:
		{
			SaveSelProducts();

		}
		break;
	}

	CDialog::OnOK();
}

void CSelDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
}
void  CSelDlg::DisPalyProductSel()
{
	CEditableListCtrl *pList1 = &m_SrcList;
	CEditableListCtrl *pList2 = &m_DecList;
	int     i,nCount;
	CString	str;
	int     iColNum; 
	char	ItemName[20][30] = {"序号", "产品代号","产品名称"};
	int     ItemLen[20]      = {50,100,150};
	ListCtrl_ClearAllColumn(pList1);
	iColNum = 3;

	//显示设置
	this->SetWindowText(_T("选择你关心的产品"));
	GetDlgItem(IDC_STATIC3)->SetWindowText(_T("本部门所有产品"));
	GetDlgItem(IDC_STATIC2)->SetWindowText(_T("当前选中的产品"));

	((CButton *)GetDlgItem(IDC_CHECK1))->ShowWindow(SW_HIDE);
	((CButton *)GetDlgItem(IDC_CHECK2))->ShowWindow(SW_HIDE);
	((CButton *)GetDlgItem(IDC_CHECK3))->ShowWindow(SW_HIDE);
	((CButton *)GetDlgItem(IDC_CHECK4))->ShowWindow(SW_HIDE);


	for (i=0; i<iColNum; i++)
	{
		str.Format("%s", ItemName[i]);
		pList1->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen[i]);	
	}

	

	for (i=0; i<iColNum; i++)
	{
		str.Format("%s", ItemName[i]);
		pList2->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen[i]);	
	}


	nCount = g_SelProducts.size();
	StBasProduct *pProductInfo;
	for (i = 0;i<nCount;i++)
	{
		pProductInfo = g_SelProducts.at(i);
		str.Format(_T("%d"),i+1);
		pList2->InsertItem(i,str);
		pList2->SetItemData(i,pProductInfo->nOid);
		pList2->SetItemText(i,1,pProductInfo->szProductNo);
		pList2->SetItemText(i,2,pProductInfo->szProductName);
	}
	
	CString strProductNo;
	GetDlgItem(IDC_EDIT1)->GetWindowText(strProductNo);
	strProductNo = strProductNo.TrimLeft();
	strProductNo = strProductNo.TrimRight();

	InitProductList(strProductNo);
}

void  CSelDlg::InitProductList(CString strProductNo)
{
	UINT nGroupOid = g_CurSelDepart.nOid;
	vector<StBasProduct > nProductArry;
	StBasProduct *pProductInfo;
	int pos;
	CEditableListCtrl *pList = &m_SrcList;

	pList->DeleteAllItems();
	StBasProduct nProductSearch;
	memset(&nProductSearch, 0, sizeof(StBasProduct));
	strcpy(nProductSearch.szProductNo, strProductNo);
	if(m_DMng.GetGroupProductData(nGroupOid,&nProductSearch,&nProductArry))
	{
		int i,nProductCount;
		CString str;
		nProductCount = nProductArry.size();
		for (i = 0;i<nProductCount;i++)
		{
			pProductInfo = &nProductArry.at(i);
			str.Format(_T("%d"),i+1);
			pList->InsertItem(i,str);
			pList->SetItemData(i,pProductInfo->nOid);
			pos = 1;
			pList->SetItemText(i,pos++,pProductInfo->szProductNo);
			pList->SetItemText(i,pos++,pProductInfo->szProductName);
		}
		nProductArry.clear();
	}
}


void  CSelDlg::SaveSelProducts()
{
	int i,nCount;
	CEditableListCtrl *pList2 = &m_DecList;

	ReleaseProducts(&g_SelProducts);
	nCount = pList2->GetItemCount();
	for (i = 0;i<nCount;i++)
	{
		StBasProduct *pProductInfo = new StBasProduct;
		memset(pProductInfo,0,sizeof(StBasProduct));
		pProductInfo->nOid = pList2->GetItemData(i);
		strcpy(pProductInfo->szProductNo,pList2->GetItemText(i,1));
		strcpy(pProductInfo->szProductName,pList2->GetItemText(i,2));
		g_SelProducts.push_back(pProductInfo);
	}

	CreateSQLSelProducts(&g_SelProducts);
	CString strUserLogName = g_LoginUsrInfo.szLoginName;
	if(!strUserLogName.IsEmpty())
	{
		g_UserConfig.SetSelProductConfig(strUserLogName,&g_SelProducts);
	}
	
	
}


void CSelDlg::ListCtrl_ClearAllColumn(CEditableListCtrl *pList)
{
	int		i, nColCnt;

	pList->DeleteAllItems();
	nColCnt = pList->GetHeaderCtrl()->GetItemCount();	
	for (i=0; i<nColCnt; i++)
	{
		pList->DeleteColumn(0);
	}
}
void CSelDlg::OnBnClickedFindBtn()
{
	CString strProductNo;
	GetDlgItem(IDC_EDIT1)->GetWindowText(strProductNo);
	strProductNo = strProductNo.TrimLeft();
	strProductNo = strProductNo.TrimRight();

	switch(m_nType)
	{
	case Sel_Product:
		{
			InitProductList(strProductNo);
		}
		break;
	}
}

BOOL CSelDlg::CheckItemSame(UINT OID)//检查是否已有这一项了//
{
	CEditableListCtrl *pList2 = &m_DecList;
	int i,nCount = pList2->GetItemCount();

	for (i = 0;i<nCount;i++)
	{
		if(OID == pList2->GetItemData(i))
		{
			break;
		}
	}
	if(i>=nCount)
	{
		return TRUE;//没有//
	}
	return FALSE;//有//
}
void CSelDlg::OnBnClickedAllSelBtn()
{
	CEditableListCtrl *pList1 = &m_SrcList;
	CEditableListCtrl *pList2 = &m_DecList;
	int		i, j, nCount,nColCnt;
	int     Index;
	UINT    OID;
	CString strNum;

	nCount = pList1->GetItemCount();
	nColCnt = pList1->GetHeaderCtrl()->GetItemCount();
	for (i = 0;i<nCount;i++)
	{
		OID = pList1->GetItemData(i);
		if(!CheckItemSame(OID))
		{
			continue;
		}
		Index = pList2->GetItemCount();
		strNum.Format("%d",Index+1);
		pList2->InsertItem(Index,strNum);
		pList2->SetItemData(Index,OID);
		for (j=1; j<=nColCnt; j++)
		{
			pList2->SetItemText(Index,j,pList1->GetItemText(i,j));
		}
	}
	
}

void CSelDlg::OnBnClickedSingleSelBtn()
{
	CEditableListCtrl *pList1 = &m_SrcList;
	CEditableListCtrl *pList2 = &m_DecList;

	int		j, nSel,nCount,nColCnt;
	int     Index;
	UINT    OID;
	CString strNum;

	nSel = pList1->GetFirstSelectedItem();
	nCount = pList1->GetItemCount();
	nColCnt = pList1->GetHeaderCtrl()->GetItemCount();
	if(nSel < 0 || nSel >= nCount)
	{
		AfxMessageBox(_T("请选中左边的一项!"));
		return;
	}

	OID = pList1->GetItemData(nSel);
	if(!CheckItemSame(OID))
	{
		return;
	}
	Index = pList2->GetItemCount();
	strNum.Format("%d",Index+1);
	pList2->InsertItem(Index,strNum);
	pList2->SetItemData(Index,OID);
	for (j=1; j<=nColCnt; j++)
	{
		pList2->SetItemText(Index,j,pList1->GetItemText(nSel,j));
	}
}

void CSelDlg::OnBnClickedSingleDelBtn()
{
	CEditableListCtrl *pList2 = &m_DecList;
	int		nSel;
	while(1)
	{
		nSel = pList2->GetFirstSelectedItem();
		if(nSel < 0)
		{
			break;
		}
		pList2->DeleteItem(nSel);
	}
	
}

void CSelDlg::OnBnClickedAllDelBtn()
{
	CEditableListCtrl *pList2 = &m_DecList;
	pList2->DeleteAllItems();

}
