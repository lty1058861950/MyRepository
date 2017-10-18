#pragma once
#include "afxcmn.h"
#include "mylistctrl\editablelistctrl.h"
#include "ShowTaskInfo.h"


// CTaskCfg 对话框

class CTaskCfg : public CDialog
{
	DECLARE_DYNAMIC(CTaskCfg)

public:
	CTaskCfg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTaskCfg();

// 对话框数据
	enum { IDD = IDD_TASK_CFG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void  AutoSize();
protected:
	virtual void OnOK();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedNumbelmngBtn();
	afx_msg void OnBnClickedTaskmodemngBtn();
	afx_msg void OnBnClickedTaskpicnumBtn();
	CTabCtrl m_Tab;
	CShowTaskInfo  *m_pShowTaskInfo;
	CEditableListCtrl m_TaskDecCfg;
	CEditableListCtrl m_TaskNumber;
	CEditableListCtrl m_TaskMode;
	CEditableListCtrl m_TaskPicNum;
	afx_msg void OnTcnSelchangeTaskCfgTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
