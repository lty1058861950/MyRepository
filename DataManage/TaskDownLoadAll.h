#pragma once
#include "mylistctrl\editablelistctrl.h"


// CTaskDownLoadAll �Ի���

class CTaskDownLoadAll : public CDialog
{
	DECLARE_DYNAMIC(CTaskDownLoadAll)

public:
	CTaskDownLoadAll(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTaskDownLoadAll();

// �Ի�������
	enum { IDD = IDD_TASK_DOWNALL_DLG };

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
	CEditableListCtrl m_TaskDownLoadList;
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
};
