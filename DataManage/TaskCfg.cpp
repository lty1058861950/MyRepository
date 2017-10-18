// TaskCfg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataManage.h"
#include "TaskCfg.h"

#include "TaskNumbel.h"
#include "TaskModeMng.h"
#include "TaskPicNum.h"
// CTaskCfg �Ի���

IMPLEMENT_DYNAMIC(CTaskCfg, CDialog)

CTaskCfg::CTaskCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CTaskCfg::IDD, pParent)
{
	m_pShowTaskInfo = NULL;
}

CTaskCfg::~CTaskCfg()
{
}

void CTaskCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TASK_CFG_TAB1, m_Tab);
	DDX_Control(pDX, IDC_TASKINFO_LIST, m_TaskDecCfg);
	DDX_Control(pDX, IDC_TASK_NUMBEL_LIST, m_TaskNumber);
	DDX_Control(pDX, IDC_TASKMODE_LIST, m_TaskMode);
	DDX_Control(pDX, IDC_TASKPICNUM_LIST, m_TaskPicNum);
}


BEGIN_MESSAGE_MAP(CTaskCfg, CDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_NUMBELMNG_BTN, &CTaskCfg::OnBnClickedNumbelmngBtn)
	ON_BN_CLICKED(IDC_TASKMODEMNG_BTN, &CTaskCfg::OnBnClickedTaskmodemngBtn)
	ON_BN_CLICKED(IDC_TASKPICNUM_BTN, &CTaskCfg::OnBnClickedTaskpicnumBtn)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TASK_CFG_TAB1, &CTaskCfg::OnTcnSelchangeTaskCfgTab1)
END_MESSAGE_MAP()


// CTaskCfg ��Ϣ�������

BOOL CTaskCfg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	TCITEM tcItem;
	tcItem.mask = TCIF_TEXT;
	tcItem.pszText = _T("������������");
	m_Tab.InsertItem(0,&tcItem);
	tcItem.pszText = _T("��Ʒ�����Ϣ");
	m_Tab.InsertItem(1,&tcItem);
	tcItem.pszText = _T("��Ʒģ����Ϣ");
	m_Tab.InsertItem(2,&tcItem);
	tcItem.pszText = _T("��Ʒͼ����Ϣ");
	m_Tab.InsertItem(3,&tcItem);



	int i;
	char *ColName4[] = {"���","��Ʒ���",_T("ģ������"),"�Ƿ����",_T("ģ������"),_T("ģ���пɱ�"),_T("ͼ������")};
	int  ColWidth4[] = {50,100,100,100,100,   100,100};
	m_TaskDecCfg.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_GRIDLINES);

	for(int i = 0;i<7;i++)
	{
		m_TaskDecCfg.InsertColumn(i, ColName4[i],LVCFMT_CENTER, ColWidth4[i]);
	}
	m_TaskDecCfg.EnableRClickMenu(FALSE);

	char *ColName1[] = {"���","��Ʒ���",_T("����")};
	int  ColWidth1[] = {50,100,50};
	m_TaskNumber.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_GRIDLINES);

	for( i = 0;i<3;i++)
	{
		m_TaskNumber.InsertColumn(i, ColName1[i],LVCFMT_CENTER, ColWidth1[i]);
	}
	m_TaskNumber.EnableRClickMenu(FALSE);

	char *ColName2[] = {"���","ģ������",_T("ģ������"), _T("�пɱ�����")};
	int  ColWidth2[] = {50,100, 100, 100};
	m_TaskMode.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_GRIDLINES);

	for( i = 0;i<4;i++)
	{
		m_TaskMode.InsertColumn(i, ColName2[i],LVCFMT_CENTER, ColWidth2[i]);
	}
	m_TaskMode.EnableRClickMenu(FALSE);


	char *ColName3[] = {"���","ͼ�Ŵ���","ͼ������"};
	int  ColWidth3[] = {50,100,100};
	m_TaskPicNum.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_GRIDLINES);

	for( i = 0;i<3;i++)
	{
		m_TaskPicNum.InsertColumn(i, ColName3[i],LVCFMT_CENTER, ColWidth3[i]);
	}
	m_TaskPicNum.EnableRClickMenu(FALSE);

	m_TaskDecCfg.ShowWindow(SW_SHOW);
	m_TaskNumber.ShowWindow(SW_HIDE);
	m_TaskMode.ShowWindow(SW_HIDE);
	m_TaskPicNum.ShowWindow(SW_HIDE);

	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CTaskCfg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialog::OnOK();
}

void CTaskCfg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	AutoSize();
}

void CTaskCfg::AutoSize()
{
	CRect Rect ;
	GetClientRect(&Rect) ;
	int nBtnWidth = 80;
	int nBtnHeight = 30;


	if(GetDlgItem(IDC_TASK_CFG_STATIC1)->GetSafeHwnd())
	{
		GetDlgItem(IDC_TASK_CFG_STATIC1)->MoveWindow(1, 1, Rect.Width()-(1*2), Rect.Height()-(1*2));
	}


	if(m_Tab.GetSafeHwnd())
	{
		m_Tab.MoveWindow(5, 8, Rect.Width()-(5*2), Rect.Height()-(8+4));
	}


	int hh = 35;
	if(m_TaskDecCfg.GetSafeHwnd())
	{
		m_TaskDecCfg.MoveWindow(10, hh, Rect.Width()-(2*10), Rect.Height()-(hh+10+nBtnHeight+10));
	}
	if(m_TaskNumber.GetSafeHwnd())
	{
		m_TaskNumber.MoveWindow(10, hh, Rect.Width()-(2*10), Rect.Height()-(hh+10+nBtnHeight+10));
	}
	if(m_TaskMode.GetSafeHwnd())
	{
		m_TaskMode.MoveWindow(10, hh, Rect.Width()-(2*10), Rect.Height()-(hh+10+nBtnHeight+10));
	}
	if(m_TaskPicNum.GetSafeHwnd())
	{
		m_TaskPicNum.MoveWindow(10, hh, Rect.Width()-(2*10), Rect.Height()-(hh+10+nBtnHeight+10));
	}


	//���ܰ�ť��λ��///
	if(GetDlgItem(IDC_NUMBELMNG_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_NUMBELMNG_BTN)->MoveWindow(10+((nBtnWidth+10)*0),Rect.bottom-(nBtnHeight+10),nBtnWidth,nBtnHeight);
	}

	if(GetDlgItem(IDC_TASKMODEMNG_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_TASKMODEMNG_BTN)->MoveWindow(10+((nBtnWidth+10)*1),Rect.bottom-(nBtnHeight+10),nBtnWidth,nBtnHeight);
	}

	if(GetDlgItem(IDC_TASKPICNUM_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_TASKPICNUM_BTN)->MoveWindow(10+((nBtnWidth+10)*2),Rect.bottom-(nBtnHeight+10),nBtnWidth,nBtnHeight);
	}



}


void CTaskCfg::OnBnClickedNumbelmngBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTaskNumbelMng dlg;
	dlg.m_pCurTaskInfo = &m_pShowTaskInfo->m_CurTaskInfo;
	dlg.m_pShowTaskInfo = m_pShowTaskInfo;
	if(dlg.DoModal() == IDOK)
	{

	}
}

void CTaskCfg::OnBnClickedTaskmodemngBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTaskModeMng dlg;
	dlg.m_pCurTaskInfo = &m_pShowTaskInfo->m_CurTaskInfo;
	dlg.m_pShowTaskInfo = m_pShowTaskInfo;
	if(dlg.DoModal() == IDOK)
	{

	}
}

void CTaskCfg::OnBnClickedTaskpicnumBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTaskPicNum dlg;
	dlg.m_pCurTaskInfo = &m_pShowTaskInfo->m_CurTaskInfo;
	dlg.m_pShowTaskInfo = m_pShowTaskInfo;
	if(dlg.DoModal() == IDOK)
	{

	}

}

void CTaskCfg::OnTcnSelchangeTaskCfgTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	switch(m_Tab.GetCurSel())
	{
	case 0:
		{
			m_TaskDecCfg.ShowWindow(SW_SHOW);
			m_TaskNumber.ShowWindow(SW_HIDE);
			m_TaskMode.ShowWindow(SW_HIDE);
			m_TaskPicNum.ShowWindow(SW_HIDE);
		}
		break;
	case 1:
		{
			m_TaskDecCfg.ShowWindow(SW_HIDE);
			m_TaskNumber.ShowWindow(SW_SHOW);
			m_TaskMode.ShowWindow(SW_HIDE);
			m_TaskPicNum.ShowWindow(SW_HIDE);

		}
		break;
	case 2:
		{
			m_TaskDecCfg.ShowWindow(SW_HIDE);
			m_TaskNumber.ShowWindow(SW_HIDE);
			m_TaskMode.ShowWindow(SW_SHOW);
			m_TaskPicNum.ShowWindow(SW_HIDE);


		}
		break;
	case 3:
		{
			m_TaskDecCfg.ShowWindow(SW_HIDE);
			m_TaskNumber.ShowWindow(SW_HIDE);
			m_TaskMode.ShowWindow(SW_HIDE);
			m_TaskPicNum.ShowWindow(SW_SHOW);
		}
		break;

	}
	*pResult = 0;
}
