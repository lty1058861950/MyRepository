// BatchSelOpt.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataManage.h"
#include "BatchSelOpt.h"


// CBatchSelOpt �Ի���

IMPLEMENT_DYNAMIC(CBatchSelOpt, CDialog)

CBatchSelOpt::CBatchSelOpt(CWnd* pParent /*=NULL*/)
	: CDialog(CBatchSelOpt::IDD, pParent)
{
	m_nType = 0;
}

CBatchSelOpt::~CBatchSelOpt()
{
}

void CBatchSelOpt::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CBatchSelOpt, CDialog)
	ON_WM_SIZE()
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CBatchSelOpt::OnNMRClickList1)
	ON_COMMAND(ID_RECOVERY_MENU, &CBatchSelOpt::RecoveryGroup)
	ON_BN_CLICKED(IDOK, &CBatchSelOpt::OnBnClickedOk)
END_MESSAGE_MAP()


// CBatchSelOpt ��Ϣ�������

BOOL CBatchSelOpt::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_list.EnableRClickMenu(FALSE);
	InitPopMenu1( );
	InitPopMenu2( );

	if(m_nType == Batch_Group)
	{
		this->SetWindowText(_T("�ָ�����"));
		InitInvalidDepartList();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CBatchSelOpt::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialog::OnOK();
}

void CBatchSelOpt::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
}
void  CBatchSelOpt::InitPopMenu1( )					//��ʼ���˵�1
{
	if(!m_PopupMenu1.GetSafeHmenu())
	{
		m_PopupMenu1.CreatePopupMenu();

		m_PopupMenu1.AppendMenu(MF_STRING, ID_RECOVERY_MENU,        "�ָ�����");

	}
}

void  CBatchSelOpt::InitPopMenu2( )					//��ʼ���˵�1	
{
	if(!m_PopupMenu2.GetSafeHmenu())
	{
		m_PopupMenu2.CreatePopupMenu();

		m_PopupMenu2.AppendMenu(MF_STRING, IDC_DEPART_EDIT_BTN,		"�޸Ĳ���");


	}
}
void CBatchSelOpt::RecoveryGroup()
{
	CEditableListCtrl *pList = &m_list;
	int Index = pList->GetFirstSelectedItem(),
		nCount = pList->GetItemCount();

	if(Index < 0 || Index >= nCount)
	{
		return;
	}

	UINT nGoupOid = pList->GetItemData(Index);
	CString str,strGroup = pList->GetItemText(Index,1);

	if(!m_DMng.RecoveryGroup(nGoupOid))
	{
		str.Format(_T("����\"%s\"�ָ�ʧ��!"),strGroup);
		AfxMessageBox(str);
	}else
	{
		str.Format(_T("����\"%s\"�ѻָ�!"),strGroup);
		pList->DeleteItem(Index);
		AfxMessageBox(str);
	}
}
void CBatchSelOpt::InitInvalidDepartList()
{
	CEditableListCtrl *pList = &m_list;
	int     i;
	CString	str;
	int     iColNum; 
	char	ItemName[20][30] = {"���", "��������"};
	int     ItemLen[20]      = {50,150};
	ListCtrl_ClearAllColumn(pList);
	iColNum = 2;

	for (i=0; i<iColNum; i++)
	{
		str.Format("%s", ItemName[i]);
		pList->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen[i]);	
	}

	int nCount;
	vector<StHrGroup *> nArrayGroup;
	if(m_DMng.GetAllInvalidGroup(&nArrayGroup))
	{
		nCount = nArrayGroup.size();
		for (i = 0;i<nCount;i++)
		{
			str.Format(_T("%d"),i+1);
			pList->InsertItem(i,str);
			pList->SetItemText(i,1,nArrayGroup.at(i)->szGroupName);
			pList->SetItemData(i,nArrayGroup.at(i)->nOid);

			delete nArrayGroup.at(i);
		}
		nArrayGroup.clear();
	}



}

void CBatchSelOpt::ListCtrl_ClearAllColumn(CEditableListCtrl *pList)
{
	int		i, nColCnt;

	pList->DeleteAllItems();
	nColCnt = pList->GetHeaderCtrl()->GetItemCount();	
	for (i=0; i<nColCnt; i++)
	{
		pList->DeleteColumn(0);
	}
}
void CBatchSelOpt::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	CEditableListCtrl *pList = &m_list;
	int Index = pList->GetFirstSelectedItem(),
		nCount = pList->GetItemCount();
	if(Index <0 || Index >= nCount)
	{
		return;
	}

	POINT	point;
	GetCursorPos(&point);
	m_PopupMenu1.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
	*pResult = 0;
}

void CBatchSelOpt::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}
