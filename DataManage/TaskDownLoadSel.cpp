// TaskDownSel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataManage.h"
#include "TaskDownLoadSel.h"


// CTaskDownSel �Ի���

IMPLEMENT_DYNAMIC(CTaskDownLoadSel, CDialog)

CTaskDownLoadSel::CTaskDownLoadSel(CWnd* pParent /*=NULL*/)
	: CDialog(CTaskDownLoadSel::IDD, pParent)
{

}

CTaskDownLoadSel::~CTaskDownLoadSel()
{
}

void CTaskDownLoadSel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_TaskDownLoadSelList);
}


BEGIN_MESSAGE_MAP(CTaskDownLoadSel, CDialog)
	ON_WM_SIZE()
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CTaskDownLoadSel::OnNMClickList1)
END_MESSAGE_MAP()


// CTaskDownSel ��Ϣ�������

BOOL CTaskDownLoadSel::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CTaskDownLoadSel::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialog::OnOK();
}

void CTaskDownLoadSel::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	AutoSize();
}

void CTaskDownLoadSel::AutoSize()
{
	CRect Rect ;
	GetClientRect(&Rect);

	int nBtnWidth = 60;
	int nBtnHeight = 25;


	//��Ʒģ��//
	if(GetDlgItem(IDC_STATIC1)->GetSafeHwnd())
	{
		GetDlgItem(IDC_STATIC1)->MoveWindow(0,5,Rect.Width()-(0*2),Rect.Height()-(5*2));
	}

	if(m_TaskDownLoadSelList.GetSafeHwnd())
	{
		m_TaskDownLoadSelList.MoveWindow(3,5+20,Rect.Width()-(3*2),
			Rect.Height()-((5+20+10)));
	}

}


void CTaskDownLoadSel::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
