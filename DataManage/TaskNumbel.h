#pragma once
#include "afxcmn.h"
#include "mylistctrl\editablelistctrl.h"

// CTaskNumbel 对话框

class CTaskNumbelMng : public CDialog
{
	DECLARE_DYNAMIC(CTaskNumbelMng)

public:
	CTaskNumbelMng(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTaskNumbelMng();

// 对话框数据
	enum { IDD = IDD_TASK_NUMBEL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEditableListCtrl m_ShowTaskInfoNumbelsList;
	CExcelOptFun  m_ExcelOptFun;
	CArray<StBasTaskCode,StBasTaskCode> TaskCodeArray;
	CShowTaskInfo *m_pShowTaskInfo;
	StBasTask     *m_pCurTaskInfo;
	BOOL  ContinueAddProdNumbel(CString &OutInfo);//连续添加产品编号信息//
	BOOL  CheckListRepeatText(void *nList,int index,CString strText);//检查List中是否有重复的文本///
	afx_msg void OnBnClickedShowtaskinfoAddprodnumbelBtn();
	afx_msg void OnBnClickedShowtaskinfoBatchloadBnt();//
	afx_msg void OnBnClickedShowtaskinfoDelnumBnt();//
	afx_msg void OnBnClickedShowtaskinfoNumdelallBnt();//
	virtual BOOL OnInitDialog();

	int  MyList_SetListItemEdit(CListCtrl *pList, int row, int col);
	void  FindCurTaskProdNumbels();//显示任务所有的产品编号信息//
protected:
	virtual void OnOK();
};
