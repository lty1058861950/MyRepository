// ProductFuction.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "ProductFuction.h"
#include "ProdMng.h"


// CProductFuction 对话框

IMPLEMENT_DYNAMIC(CProductFuction, CDialog)

CProductFuction::CProductFuction(CWnd* pParent /*=NULL*/)
	: CDialog(CProductFuction::IDD, pParent)
{
	m_ChangeStatus = 0;
	m_nProductOid = 0;
	m_pProdInfo = NULL;
}

CProductFuction::~CProductFuction()
{
}

void CProductFuction::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProductFuction, CDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_PROD_ADD_BTN, &CProductFuction::OnBnClickedProdAddBtn)
	ON_BN_CLICKED(IDC_PROD_DEL_BTN, &CProductFuction::OnBnClickedProdDelBtn)
	ON_BN_CLICKED(IDC_PROD_EDT_BTN, &CProductFuction::OnBnClickedProdEdtBtn)
	ON_BN_CLICKED(IDC_PROD_DEL_ALL, &CProductFuction::OnBnClickedProdDelAll)
END_MESSAGE_MAP()


// CProductFuction 消息处理程序

BOOL CProductFuction::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CProductFuction::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnOK();
}

void CProductFuction::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	AutoSize();
}

void CProductFuction::AutoSize()
{
	CRect Rect ;
	GetClientRect(&Rect);

	int nBtnWidth = 80;
	int nBtnHeight = 30;

	if (GetDlgItem(IDC_PROD_ADD_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_PROD_ADD_BTN)->MoveWindow(10,1,nBtnWidth,nBtnHeight);
	}

	if (GetDlgItem(IDC_PROD_EDT_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_PROD_EDT_BTN)->MoveWindow(10+(nBtnWidth+10)*1,1,nBtnWidth,nBtnHeight);
	}

	if (GetDlgItem(IDC_PROD_DEL_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_PROD_DEL_BTN)->MoveWindow(10+(nBtnWidth+10)*2,1,nBtnWidth,nBtnHeight);
	}

	if (GetDlgItem(IDC_PROD_DEL_ALL)->GetSafeHwnd())
	{
		GetDlgItem(IDC_PROD_DEL_ALL)->MoveWindow(10+(nBtnWidth+10)*3,1,nBtnWidth,nBtnHeight);
	}

	
}


void CProductFuction::OnBnClickedProdAddBtn()
{
	// TODO: 在此添加控件通知处理程序代码
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
			g_pShowInfoList->InsertOneProdToList(&nProdMng.m_CurProdInfo);
		}
	}
}

void CProductFuction::OnBnClickedProdDelBtn()
{
	// TODO: 在此添加控件通知处理程序代码//
	//CEditableListCtrl *pList1 = &g_pShowInfoList->m_ShowList;
	CEditableListCtrl *pList2 = &g_pShowInfoList->m_ResultList.m_ResultList;

	int nIndex, nCount, ret = 0;
	
	nIndex = pList2->GetFirstSelectedItem();
	nCount = pList2->GetItemCount();
	if(nIndex < 0 || nIndex >= nCount)
		return;

	UINT nProductOid = pList2->GetItemData(nIndex);
	StBasProduct stProductInfo;
	memset(&stProductInfo, 0, sizeof(StBasProduct));
	if(!m_DMng.GetProdDataOid(nProductOid,&stProductInfo))
	{
		return;
	}
	ret = DelTheProd(&stProductInfo);

	if(ret == 1)
	{
		pList2->DeleteItem(nIndex);
	}
}

void CProductFuction::OnBnClickedProdEdtBtn()
{
	// TODO: 在此添加控件通知处理程序代码//
	
	//CEditableListCtrl *pList1 = &g_pShowInfoList->m_ShowList;
	CEditableListCtrl *pList2 = &g_pShowInfoList->m_ResultList.m_ResultList;

	int nIndex, nCount, ret = 0;
	nIndex = pList2->GetFirstSelectedItem();
	nCount = pList2->GetItemCount();
	if(nIndex < 0 || nIndex >= nCount)
		return;

	UINT nProductOid = pList2->GetItemData(nIndex);
	CProdMng nProdMng;

	if(!m_DMng.GetProdDataOid(nProductOid,&nProdMng.m_CurProdInfo))
	{
		return;
	}
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

void CProductFuction::OnBnClickedProdDelAll()
{
	// TODO: Add your control notification handler code here
	CString strText;
	UINT    nCurGroupOid; 

	strText.Format(_T("确定删除所有产品，及所有任务吗? 请注意:此操作相当于清空表,不可恢复！"));
	//删除一项产品需要做的 步骤///
	if(::MessageBox(NULL,strText,_T("提示"),MB_OKCANCEL|MB_ICONQUESTION) != IDOK)
	{
		return;
	}

	//部门OID
	nCurGroupOid = g_CurSelDepart.nOid;   //注意：需全局变量初始化, 部门OID
	
	m_DMng.DelAllProd(nCurGroupOid);		//删除据有产品
	m_DMng.DelAllProd_PicNum(nCurGroupOid);	//

	m_DMng.DelAllTask(nCurGroupOid);
	m_DMng.DelAllTask_AllCode(nCurGroupOid);
	m_DMng.DelAllTask_ALLMode(nCurGroupOid);
	m_DMng.DelAllTask_ALLPicNum(nCurGroupOid);


	
	AfxMessageBox("删除所有产品操作完毕!");

}
