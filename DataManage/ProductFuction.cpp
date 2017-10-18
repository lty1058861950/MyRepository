// ProductFuction.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataManage.h"
#include "ProductFuction.h"
#include "ProdMng.h"


// CProductFuction �Ի���

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


// CProductFuction ��Ϣ�������

BOOL CProductFuction::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CProductFuction::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialog::OnOK();
}

void CProductFuction::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������//
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������//
	
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

	strText.Format(_T("ȷ��ɾ�����в�Ʒ��������������? ��ע��:�˲����൱����ձ�,���ɻָ���"));
	//ɾ��һ���Ʒ��Ҫ���� ����///
	if(::MessageBox(NULL,strText,_T("��ʾ"),MB_OKCANCEL|MB_ICONQUESTION) != IDOK)
	{
		return;
	}

	//����OID
	nCurGroupOid = g_CurSelDepart.nOid;   //ע�⣺��ȫ�ֱ�����ʼ��, ����OID
	
	m_DMng.DelAllProd(nCurGroupOid);		//ɾ�����в�Ʒ
	m_DMng.DelAllProd_PicNum(nCurGroupOid);	//

	m_DMng.DelAllTask(nCurGroupOid);
	m_DMng.DelAllTask_AllCode(nCurGroupOid);
	m_DMng.DelAllTask_ALLMode(nCurGroupOid);
	m_DMng.DelAllTask_ALLPicNum(nCurGroupOid);


	
	AfxMessageBox("ɾ�����в�Ʒ�������!");

}
