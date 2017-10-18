#pragma once
#include "mylistctrl\editablelistctrl.h"
#include "afxcmn.h"

// CTaskModeMng 对话框

class CTaskModeMng : public CDialog
{
	DECLARE_DYNAMIC(CTaskModeMng)

public:
	CTaskModeMng(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTaskModeMng();

// 对话框数据
	enum { IDD = IDD_TASK_MODE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEditableListCtrl m_ShowTaskInfoModeList;//当前使用的模板//
	CEditableListCtrl m_CurTaskAllModeList;//所有候选模板//
	StBasTask *m_pCurTaskInfo;

	CShowTaskInfo *m_pShowTaskInfo;
	virtual BOOL OnInitDialog();
	BOOL  CheckListRepeatText(void *nList,int index,UINT nModeOid);//检查List中是否有重复的文本///
	afx_msg void OnBnClickedShowtaskinfoAddallmodeBtn();
	afx_msg void OnBnClickedShowtaskinfoAddmodeBtn();
	afx_msg void OnBnClickedShowtaskinfoDelmodeBtn();
	afx_msg void OnBnClickedShowtaskinfoDelallmodeBtn();

	void  FindCurTaskModes();
	void OnUpdateChart(UINT nID) ;

protected:
	virtual void OnOK();
};
