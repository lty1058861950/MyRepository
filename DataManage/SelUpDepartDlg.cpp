// SelUpDepartDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "SelUpDepartDlg.h"


// CSelUpDepartDlg 对话框

IMPLEMENT_DYNAMIC(CSelUpDepartDlg, CDialog)

CSelUpDepartDlg::CSelUpDepartDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelUpDepartDlg::IDD, pParent)
{

}

CSelUpDepartDlg::~CSelUpDepartDlg()
{
}

void CSelUpDepartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_DepartList);
}


BEGIN_MESSAGE_MAP(CSelUpDepartDlg, CDialog)
	ON_WM_SIZE()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CSelUpDepartDlg::OnNMDblclkList1)
END_MESSAGE_MAP()


// CSelUpDepartDlg 消息处理程序

BOOL CSelUpDepartDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CEditableListCtrl *pList1 = &m_DepartList;

	int     i;
	CString	str, strText;
	int     iColNum; 
	char	ItemName[20][30] = {"序号", "部门名称"};
	int     ItemLen[20]      = {50,100};
	int     EnableCol = 2;

	iColNum = 2;

	for (i=0; i<iColNum; i++)
	{
		str.Format("%s", ItemName[i]);
		pList1->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen[i]);
	}
	pList1->EnableRClickMenu(FALSE);

	DisplayUpDepartList();

	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSelUpDepartDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CString str;
	int i, nCount;
	CEditableListCtrl *pList1 = &m_DepartList;
	i = pList1->GetFirstSelectedItem();
	nCount = pList1->GetItemCount();
	if(i<0 || i>= nCount)
	{
		str.Format(_T("请选择一个部门!"));
		AfxMessageBox(str);
		return;
	}
	m_UpDepartName = pList1->GetItemText(i,1);
	CDialog::OnOK();
}

void CSelUpDepartDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
}

void CSelUpDepartDlg::InsertUpDepartToList(StHrUpDepart *pUpDepartInfo)
{
	CEditableListCtrl *pList = &m_DepartList;
	CString strText;
	int pos = 1,nCount;
	nCount = pList->GetItemCount();
	strText.Format(_T("%d"), nCount+1);
	pList->InsertItem(nCount, strText);
	pList->SetItemData(nCount,pUpDepartInfo->nOid);
	//OID不显示//
	pos = 1;
	strText.Format(_T("%s"), pUpDepartInfo->szUpDepartName);
	pList->SetItemText(nCount,pos++,strText);

}

void CSelUpDepartDlg::DisplayUpDepartList()
{
	m_DepartList.DeleteAllItems();

	vector<StHrUpDepart > nUpDepartArry;
	if(m_DMng.GetAllUpDepart(&nUpDepartArry))
	{
		int i, nCount = nUpDepartArry.size();
		for( i = 0;i<nCount;i++)
		{
			StHrUpDepart *pUpDepartInfo = NULL;
			pUpDepartInfo = &nUpDepartArry.at(i);
			if(pUpDepartInfo == NULL)
			{
				continue;
			}

			InsertUpDepartToList(pUpDepartInfo);
		}
		nUpDepartArry.clear();

	}
}

void CSelUpDepartDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here

	OnOK();

	*pResult = 0;
}
