// SelUserDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataManage.h"
#include "SelUserDlg.h"


// CSelUserDlg �Ի���

IMPLEMENT_DYNAMIC(CSelUserDlg, CDialog)

CSelUserDlg::CSelUserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelUserDlg::IDD, pParent)
{
	m_SelUserName = _T("");
}

CSelUserDlg::~CSelUserDlg()
{
}

void CSelUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_UserList);
}


BEGIN_MESSAGE_MAP(CSelUserDlg, CDialog)
	ON_WM_SIZE()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CSelUserDlg::OnNMDblclkList1)
END_MESSAGE_MAP()


// CSelUserDlg ��Ϣ�������

void CSelUserDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	int nIndex, nCount;
	CString strText;

	CEditableListCtrl *pList = &m_UserList;
	nCount  = pList->GetItemCount();
	nIndex = pList->GetFirstSelectedItem();

	if(nIndex <0 || nIndex >= nCount)
	{
		strText.Format(_T("��ѡ��һ������Ա!"));
		AfxMessageBox(strText);
		return;
	}
	m_SelUserName = pList->GetItemText(nIndex, 1);
	CDialog::OnOK();
}

BOOL CSelUserDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CEditableListCtrl *pList1 = &m_UserList;

	int     i;
	CString	str, strText;
	int     iColNum; 
	char	ItemName[20][30] = {"���", "����","�û�����"};
	int     ItemLen[20]      = {50,100,120};
	int     EnableCol = 2;

	iColNum = 3;

	for (i=0; i<iColNum; i++)
	{
		str.Format("%s", ItemName[i]);
		pList1->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen[i]);
	}

	pList1->EnableRClickMenu(FALSE);
	DisplayUserList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CSelUserDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
}

void CSelUserDlg::InsertUserToList(StHrUser *pUserInfo)
{
	CEditableListCtrl *pList = &m_UserList;
	CString strText;
	int pos = 1,nCount;
	nCount = pList->GetItemCount();
	strText.Format(_T("%d"), nCount+1);
	pList->InsertItem(nCount, strText);
	pList->SetItemData(nCount,pUserInfo->nOid);
	//OID����ʾ//
	pos = 1;
	strText.Format(_T("%s"), pUserInfo->szUserName);
	pList->SetItemText(nCount,pos++,strText);
	strText.Format(_T("%s"), GetUserTypeText(pUserInfo->nUserType));
	pList->SetItemText(nCount,pos++,strText);

	/*
	strText.Format(_T("%s"), pUserInfo->szLoginName);
	pList->SetItemText(nCount,pos++,strText);
	
	//��ȡ�û��Ĳ���//
	strText.Format(_T("%s"), pUserInfo->szGroupName);
	pList->SetItemText(nCount,pos++,strText);

	strText.Format(_T("%s"), GetUserTypeText(pUserInfo->nUserType));
	pList->SetItemText(nCount,pos++,strText);

	strText.Format(_T("%s"), pUserInfo->szUserSignfile);
	pList->SetItemText(nCount,pos++,strText);

	strText.Format(_T("%s"), pUserInfo->szCall);
	pList->SetItemText(nCount,pos++,strText);

	strText.Format(_T("%s"), pUserInfo->szEmail);
	pList->SetItemText(nCount,pos++,strText);
	strText.Format(_T("%s"), pUserInfo->szPhone);
	pList->SetItemText(nCount,pos++,strText);
	strText.Format(_T("%d"), pUserInfo->nPadDevID);
	pList->SetItemText(nCount,pos++,strText);*/

}
void CSelUserDlg::DisplayUserList()
{
	m_UserList.DeleteAllItems();

	vector<StHrUser *> nUserArry;
	if(m_DMng.GetAllUserToPad(&nUserArry))
	{
		int i, nCount = nUserArry.size();
		for( i = 0;i<nCount;i++)
		{
			StHrUser *pUserInfo = NULL;
			pUserInfo = nUserArry.at(i);
			if(pUserInfo == NULL || pUserInfo->nUserType == user_admin)
			{
				continue;
			}

			InsertUserToList(pUserInfo);
			delete pUserInfo;
		}
		nUserArry.clear();

	}
}
void CSelUserDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	
	OnOK();

	*pResult = 0;
}
