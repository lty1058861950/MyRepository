#pragma once
#include "mylistctrl\editablelistctrl.h"


// CTaskDownSel �Ի���

class CTaskDownLoadSel : public CDialog
{
	DECLARE_DYNAMIC(CTaskDownLoadSel)

public:
	CTaskDownLoadSel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTaskDownLoadSel();

// �Ի�������
	enum { IDD = IDD_TASK_DOWNSEL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void     AutoSize();
protected:
	virtual void OnOK();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CEditableListCtrl m_TaskDownLoadSelList;
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
};
