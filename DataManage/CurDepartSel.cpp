// CurDepartSel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataManage.h"
#include "CurDepartSel.h"


// CCurDepartSel �Ի���

IMPLEMENT_DYNAMIC(CCurDepartSel, CDialog)

CCurDepartSel::CCurDepartSel(CWnd* pParent /*=NULL*/)
	: CDialog(CCurDepartSel::IDD, pParent)
{
}

CCurDepartSel::~CCurDepartSel()
{
}

void CCurDepartSel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCurDepartSel, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CCurDepartSel ��Ϣ�������

void CCurDepartSel::OnOK()
{
	CComboBox *pGroupComB = (CComboBox *)GetDlgItem(IDC_CUR_DEPART_COMBO);
	CString strGroupName;
	int nCount = pGroupComB->GetCount(),Index = pGroupComB->GetCurSel();
	if(Index<0 || Index>=nCount)
	{
		return;
	}else
	{
		memset(&g_CurSelDepart,0,sizeof(StHrGroup));

		UINT nOid = pGroupComB->GetItemData(Index);

		int i,nCount = 0;
		CString strText;

		nCount = g_AllGroups.size();
		StHrGroup *pStHrGroup = NULL;
		for (i = 0;i<nCount;i++)
		{
			pStHrGroup = g_AllGroups.at(i);

			if(pStHrGroup->nOid == nOid)
			{
				memcpy(&g_CurSelDepart,pStHrGroup,sizeof(StHrGroup));
				g_GroupSelect = i;

				CString nFileName ;
				CString str;
				nFileName.Format("%s\\%s",g_WorkPath,USRMNG_USRCFG_FILENAME) ;
				str.Format(_T("%d"), g_GroupSelect);
				if(/*g_LoginUsrInfo.nUserType == user_admin*/1)
				{
					WritePrivateProfileString("Def_GroupSelect","GroupSelect", str, nFileName);
				}

				break;
			}
		}
	}

	CDialog::OnOK();
	
}

void CCurDepartSel::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialog::OnCancel();
}

void CCurDepartSel::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
}

BOOL CCurDepartSel::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitDepartList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CCurDepartSel::InitDepartList()
{
	CComboBox *pGroupComB = (CComboBox *)GetDlgItem(IDC_CUR_DEPART_COMBO);
	pGroupComB->ResetContent();
	
	int i,nCount = 0;
	nCount = g_AllGroups.size();
	StHrGroup *pStHrGroup = NULL;
	for (i = 0;i<nCount;i++)
	{
		pStHrGroup = g_AllGroups.at(i);

		pGroupComB->AddString(pStHrGroup->szGroupName);
		pGroupComB->SetItemData(i,pStHrGroup->nOid);
		if(pStHrGroup->nOid == g_CurSelDepart.nOid)
		{
			pGroupComB->SetCurSel(i);
		}
	}
}
