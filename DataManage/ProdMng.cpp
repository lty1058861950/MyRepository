// ProdMng.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "ProdMng.h"

#include "PicNumMng.h"

// CProdMng 对话框

IMPLEMENT_DYNAMIC(CProdMng, CDialog)

CProdMng::CProdMng(CWnd* pParent /*=NULL*/)
	: CDialog(CProdMng::IDD, pParent)
{
	m_ShowType = View_Product;
	memset(&m_CurProdInfo, 0, sizeof(StBasProduct));

}

CProdMng::~CProdMng()
{
	m_ProductInfo.DestroyWindow();
	m_ProductPicNum.DestroyWindow();
}

void CProdMng::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProdMng, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()



BOOL CProdMng::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString strText;
	m_ProductInfo.Create(IDD_PRODUCT_INFO_DLG, this);
	m_ProductInfo.m_pCurProdInfo = &m_CurProdInfo;
	m_ProductInfo.DisPlayProductInfo();
	m_ProductInfo.ShowWindow(SW_SHOW);

	m_ProductPicNum.Create(IDD_PRODUCT_PICNUM_DLG, this);
	m_ProductInfo.m_pCurProdInfo = &m_CurProdInfo;
	//m_ProductPicNum.ShowWindow(SW_SHOW);
	m_ProductPicNum.ShowWindow(SW_HIDE);

	switch(m_ShowType)
	{
	case Add_Product:
		{
			this->SetWindowText(_T("添加一个产品"));
			GetDlgItem(IDOK)->SetWindowText(_T("确定"));
		}
		break;
	case Modify_Product:
		{
			strText.Format(_T("正在修改产品(产品代号=%s)"),m_CurProdInfo.szProductNo);
			this->SetWindowText(strText);
			GetDlgItem(IDOK)->SetWindowText(_T("保存"));
		}
		break;
	case View_Product:
		{
			strText.Format(_T("产品代号=%s"), m_CurProdInfo.szProductNo);
			this->SetWindowText(strText);
			GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
			m_ProductPicNum.GetDlgItem(IDC_PICNUMMNG_BTN)->EnableWindow(FALSE);
			GetDlgItem(IDCANCEL)->SetWindowText(_T("退出"));
		}
		break;
	}
	//this->MoveWindow(0,0,600,500);
	this->MoveWindow(0,0,600,300);
	this->CenterWindow();
	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CProdMng::OnSize(UINT nType, int cx, int cy)
{
	AutoSize();
	CDialog::OnSize(nType, cx, cy);
}
void CProdMng::AutoSize()
{
	CRect Rect ;
	GetClientRect(&Rect);

	int nBtnWidth = 80;
	int nBtnHeight = 30;


	int nInfoHeight = 150;
	int nPicNumHeight = 250;

	//产品模块//
	if(m_ProductInfo.GetSafeHwnd())
	{
		m_ProductInfo.MoveWindow(3,10,Rect.Width()-(3*2),nInfoHeight);
	}

	if(m_ProductPicNum.GetSafeHwnd())
	{
		m_ProductPicNum.MoveWindow(3,10+nInfoHeight+10,Rect.Width()-(3*2),
			Rect.Height()-(10+nInfoHeight+10+nBtnHeight+10));
	}

	if(GetDlgItem(IDOK)->GetSafeHwnd())
	{
		GetDlgItem(IDOK)->MoveWindow(Rect.right-(10+(nBtnWidth+10)*2),Rect.bottom-(nBtnHeight+5),nBtnWidth,nBtnHeight);
	}
	if(GetDlgItem(IDCANCEL)->GetSafeHwnd())
	{
		GetDlgItem(IDCANCEL)->MoveWindow(Rect.right-(10+(nBtnWidth+10)*1),Rect.bottom-(nBtnHeight+5),nBtnWidth,nBtnHeight);
	}
}

void CProdMng::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	m_ProductInfo.GetProdInfo();
	CDialog::OnOK();
}
