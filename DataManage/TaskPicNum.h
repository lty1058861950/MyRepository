#pragma once
#include "mylistctrl\editablelistctrl.h"



// CTaskPicNum 对话框

class CTaskPicNum : public CDialog
{
	DECLARE_DYNAMIC(CTaskPicNum)

public:
	CTaskPicNum(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTaskPicNum();

// 对话框数据
	enum { IDD = IDD_TASK_PICNUM_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEditableListCtrl m_AllPicNumList;
	CEditableListCtrl m_SelPicNumList;
	StBasTask *m_pCurTaskInfo;

	CShowTaskInfo *m_pShowTaskInfo;

	void    InitPicNumList();
	BOOL    CheckListRepeatText(void *nList,int index,UINT nPicNumOid);//检查List中是否有重复的文本///
	afx_msg void OnBnClickedAlladdBtn();
	afx_msg void OnBnClickedAddBtn();
	afx_msg void OnBnClickedDelBtn();
	afx_msg void OnBnClickedAlldelBtn();
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
};
