// ProductPicNum.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataManage.h"
#include "ProductPicNum.h"
#include "PicNumMng.h"


// CProductPicNum �Ի���

IMPLEMENT_DYNAMIC(CProductPicNum, CDialog)

CProductPicNum::CProductPicNum(CWnd* pParent /*=NULL*/)
	: CDialog(CProductPicNum::IDD, pParent)
{
	m_pCurProdInfo = NULL;
}

CProductPicNum::~CProductPicNum()
{
}

void CProductPicNum::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SERIES_LIST, m_PicNumList);
}


BEGIN_MESSAGE_MAP(CProductPicNum, CDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_PICNUMMNG_BTN, &CProductPicNum::OnBnClickedPicnummngBtn)
END_MESSAGE_MAP()


// CProductPicNum ��Ϣ�������

BOOL CProductPicNum::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	DisplayProductPicNum(&m_PicNumList);
	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CProductPicNum::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialog::OnOK();
}

void CProductPicNum::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	AutoSize();
}

void CProductPicNum::AutoSize()
{
	CRect Rect ;
	GetClientRect(&Rect);

	int nBtnWidth = 80;
	int nBtnHeight = 30;

	if (GetDlgItem(IDC_PROD_STATIC10)->GetSafeHwnd())
	{
		GetDlgItem(IDC_PROD_STATIC10)->MoveWindow(1,5,Rect.Width()-(1*2),Rect.Height()-(5*2));
	}

	if (m_PicNumList.GetSafeHwnd())
	{
		m_PicNumList.MoveWindow((5+1),(5+20),Rect.Width()-((5+1)*2),Rect.Height()-((5+20+5)+(nBtnHeight+10)));
	}

	if (GetDlgItem(IDC_PICNUMMNG_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_PICNUMMNG_BTN)->MoveWindow(10,Rect.bottom-(nBtnHeight+10),nBtnWidth,nBtnHeight);
	}
	
}

void CProductPicNum::DisplayProductPicNum(CEditableListCtrl *pList)
{
	int     i;
	CString	str;
	int     iColNum; 
	char	ItemName[20][30] = {"���", "ͼ�Ŵ���","ͼ������","����ʱ��","������"};

	int     ItemLen[20]      = {50,150,150,150,100};
	iColNum = 5;

	for (i=0; i<iColNum; i++)
	{
		str.Format("%s", ItemName[i]);
		pList->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen[i]);	
	}
	pList->EnableRClickMenu(FALSE);


}

void CProductPicNum::InitPicNumList()
{
	if(m_pCurProdInfo == NULL)
	{
		return;
	}
	m_PicNumList.DeleteAllItems();
	int i, nCount, pos;
	CString strNum;
	vector<StBasPicNum> stPicNumArray;
	CEditableListCtrl *pList = &m_PicNumList;

	if(m_DMng.GetProductPicNumInfo(m_pCurProdInfo->nOid,&stPicNumArray))
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
		//AfxMessageBox(_T("��ʼ��"));
	}
	stPicNumArray.clear();
}


void CProductPicNum::OnBnClickedPicnummngBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPicNumMng Dlg;
	Dlg.m_pCurSelProduct =  m_pCurProdInfo;
	Dlg.DoModal();
}
