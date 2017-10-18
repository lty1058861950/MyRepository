#pragma once
#include "ShowTaskInfo.h"
#include "afxcmn.h"
// CTaskMng 对话框
#define  ID_SENDTASK_MENU      2000
#define  ID_STOPTASK_MENU      2001

class CTaskMng : public CDialog
{
	DECLARE_DYNAMIC(CTaskMng)

public:
	CTaskMng(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTaskMng();

// 对话框数据
	enum { IDD = IDD_TASK_MNG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CShowTaskInfo m_ShowTaskInfo;
	int  m_ShowType;
public:
	void     AutoSize();
	void     DelTreeChildItem(CTreeCtrl *pTree,HTREEITEM hItem);

public:

	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	virtual void OnOK();
	virtual void OnCancel();
};
