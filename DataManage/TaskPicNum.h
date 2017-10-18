#pragma once
#include "mylistctrl\editablelistctrl.h"



// CTaskPicNum �Ի���

class CTaskPicNum : public CDialog
{
	DECLARE_DYNAMIC(CTaskPicNum)

public:
	CTaskPicNum(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTaskPicNum();

// �Ի�������
	enum { IDD = IDD_TASK_PICNUM_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEditableListCtrl m_AllPicNumList;
	CEditableListCtrl m_SelPicNumList;
	StBasTask *m_pCurTaskInfo;

	CShowTaskInfo *m_pShowTaskInfo;

	void    InitPicNumList();
	BOOL    CheckListRepeatText(void *nList,int index,UINT nPicNumOid);//���List���Ƿ����ظ����ı�///
	afx_msg void OnBnClickedAlladdBtn();
	afx_msg void OnBnClickedAddBtn();
	afx_msg void OnBnClickedDelBtn();
	afx_msg void OnBnClickedAlldelBtn();
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
};
