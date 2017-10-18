// SelUserDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "SelUserDlg.h"


// CSelUserDlg 对话框

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


// CSelUserDlg 消息处理程序

void CSelUserDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	int nIndex, nCount;
	CString strText;

	CEditableListCtrl *pList = &m_UserList;
	nCount  = pList->GetItemCount();
	nIndex = pList->GetFirstSelectedItem();

	if(nIndex <0 || nIndex >= nCount)
	{
		strText.Format(_T("请选择一个检验员!"));
		AfxMessageBox(strText);
		return;
	}
	m_SelUserName = pList->GetItemText(nIndex, 1);
	CDialog::OnOK();
}

BOOL CSelUserDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CEditableListCtrl *pList1 = &m_UserList;

	int     i;
	CString	str, strText;
	int     iColNum; 
	char	ItemName[20][30] = {"序号", "姓名","用户类型"};
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
	// 异常: OCX 属性页应返回 FALSE
}

void CSelUserDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
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
	//OID不显示//
	pos = 1;
	strText.Format(_T("%s"), pUserInfo->szUserName);
	pList->SetItemText(nCount,pos++,strText);
	strText.Format(_T("%s"), GetUserTypeText(pUserInfo->nUserType));
	pList->SetItemText(nCount,pos++,strText);

	/*
	strText.Format(_T("%s"), pUserInfo->szLoginName);
	pList->SetItemText(nCount,pos++,strText);
	
	//获取用户的部门//
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
