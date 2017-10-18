#pragma once
#include "mylistctrl\editablelistctrl.h"


// CSelUserDlg �Ի���

class CSelUserDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelUserDlg)

public:
	CSelUserDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSelUserDlg();

// �Ի�������
	enum { IDD = IDD_SEL_USER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
	void    DisplayUserList();
	void    InsertUserToList(StHrUser *pUserInfo);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CEditableListCtrl m_UserList;
	CString m_SelUserName;
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
};
