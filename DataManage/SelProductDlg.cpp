// SelProductDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "SelProductDlg.h"


// CSelProductDlg 对话框

IMPLEMENT_DYNAMIC(CSelProductDlg, CDialog)

CSelProductDlg::CSelProductDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelProductDlg::IDD, pParent)
{
	memset(&m_SearchInfo, 0,sizeof(StBasProduct));
}

CSelProductDlg::~CSelProductDlg()
{
}

void CSelProductDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ProdList);
}


BEGIN_MESSAGE_MAP(CSelProductDlg, CDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, &CSelProductDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_OK_SEL_BTN, &CSelProductDlg::OnBnClickedOkSelBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CSelProductDlg::OnNMDblclkList1)
END_MESSAGE_MAP()


// CSelProductDlg 消息处理程序

BOOL CSelProductDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	int     i, iColNum;
	char	ItemName[20][30] = {"序号", "产品代号","产品名称"};
	int     ItemLen[20]      = {50,150,200};
	CEditableListCtrl *pList = &m_ProdList;
	CString str;
	
	iColNum = 3;

	for (i=0; i<iColNum; i++)
	{
		str.Format("%s", ItemName[i]);
		pList->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen[i]);	
	}

	pList->EnableRClickMenu(FALSE);

	OnBnClickedButton1();

	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSelProductDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	OnBnClickedButton1();
	//CDialog::OnOK();
}

void CSelProductDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnCancel();
}

void CSelProductDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	AutoSize();
}
void  CSelProductDlg::AutoSize()
{
	CRect Rect ;
	GetClientRect(&Rect) ;
	int nHeardHeight = 100 - 20;
	int nBtnWidth = 80;
	int nBtnHeight = 30;

	int nStaticHead = 325;
	int nStaticHead1 = 300;

	if(GetDlgItem(IDC_STATIC3)->GetSafeHwnd())
	{
		GetDlgItem(IDC_STATIC3)->MoveWindow(5,5,Rect.Width()-(5*2),nHeardHeight-(5+10));
	}

	if(GetDlgItem(IDC_BUTTON1)->GetSafeHwnd())
	{
		GetDlgItem(IDC_BUTTON1)->MoveWindow(Rect.right-(10+(nBtnWidth+10)*1),  Rect.top + 20,  nBtnWidth, nBtnHeight);
	}


	if(GetDlgItem(IDC_STATIC2)->GetSafeHwnd())
	{
		GetDlgItem(IDC_STATIC2)->MoveWindow(5,nHeardHeight,Rect.Width()-(5*2),Rect.Height()-(nHeardHeight+10+(nBtnHeight+10)));
	}

	if(m_ProdList.GetSafeHwnd())
	{
		m_ProdList.MoveWindow(10,nHeardHeight+20,Rect.Width()-(10*2),Rect.Height()-(nHeardHeight+25+10+(nBtnHeight+10)));
	}


	if(GetDlgItem(IDC_OK_SEL_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_OK_SEL_BTN)->MoveWindow(Rect.right-(10+(nBtnWidth+10)*2),Rect.bottom-(nBtnHeight+10),nBtnWidth,nBtnHeight);
	}

	if(GetDlgItem(IDCANCEL)->GetSafeHwnd())
	{
		GetDlgItem(IDCANCEL)->MoveWindow(Rect.right-(10+(nBtnWidth+10)*1),Rect.bottom-(nBtnHeight+10),nBtnWidth,nBtnHeight);

	}
	
}
void CSelProductDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码//

	CEditableListCtrl *pList = &m_ProdList;
	pList->DeleteAllItems();
	UINT nGroupOid = g_CurSelDepart.nOid;
	int i, nCount, pos;
	CString strProdcutNo, strProductName;
	CString str;
	GetDlgItem(IDC_EDIT1)->GetWindowText(strProdcutNo);
	GetDlgItem(IDC_EDIT2)->GetWindowText(strProductName);

	strProdcutNo = strProdcutNo.TrimLeft();
	strProdcutNo = strProdcutNo.TrimRight();
	strProductName = strProductName.TrimLeft();
	strProductName = strProductName.TrimRight();

	memset(m_SearchInfo.szProductNo, 0,sizeof(m_SearchInfo.szProductNo));
	strcpy(m_SearchInfo.szProductNo, strProdcutNo);

	memset(m_SearchInfo.szProductName, 0, sizeof(m_SearchInfo.szProductName));
	strcpy(m_SearchInfo.szProductName, strProductName);


	vector<StBasProduct>  stProductArray;
	if(m_DMng.GetGroupProductData(nGroupOid, &m_SearchInfo,&stProductArray))
	{
		nCount = stProductArray.size();
		str.Format(_T("共查询到 %d 条数据"), nCount);
		GetDlgItem(IDC_STATIC2)->SetWindowText(str);
		for (i = 0;i<nCount;i++)
		{
			str.Format(_T("%d"), i+1);
			pList->InsertItem(i, str);
			pos = 1;

			pList->SetItemData(i, stProductArray.at(i).nOid);
			pList->SetItemText(i, pos++, stProductArray.at(i).szProductNo);
			pList->SetItemText(i, pos++, stProductArray.at(i).szProductName);
		}
	}
}

void CSelProductDlg::OnBnClickedOkSelBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex,nCount;
	CEditableListCtrl *pList = &m_ProdList;
	nCount = pList->GetItemCount();
	nIndex = pList->GetFirstSelectedItem();
	if(nIndex < 0 || nIndex >= nCount)
	{
		AfxMessageBox(_T("请选中一个产品!"));
		return;
	}

	m_strProductNo = pList->GetItemText(nIndex, 1);
	m_strProductName = pList->GetItemText(nIndex, 2);

	CDialog::OnOK();
}

void CSelProductDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here

	OnBnClickedOkSelBtn();

	*pResult = 0;
}
