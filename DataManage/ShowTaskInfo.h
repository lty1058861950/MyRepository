#pragma once
#include "afxcmn.h"
#include "ShowTaskData.h"
#include "ResultSearch.h"
#include "ResultSearchNew.h"
#include "mylistctrl\editablelistctrl.h"
#include "SqliteDb\CppSQLite3.h"
#include "LoadOutTaskXmlAnalysis.h"
#include "PathDialog.h"
#include "TaskCfg.h"

// CShowTaskInfo 对话框

class CShowTaskInfo : public CDialog
{
	DECLARE_DYNAMIC(CShowTaskInfo)

public:
	CShowTaskInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CShowTaskInfo();

// 对话框数据
	enum { IDD = IDD_SHOWTASKINFO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	//CShowTaskDetailInfo m_ShowTaskDetailInfo;
	DECLARE_MESSAGE_MAP()
public:

	CTaskCfg          m_TaskCfg;			//任务配置： 产品编号、模板、图号
	CShowTaskData     m_ShowTaskData;		//任务详情： 
	CResultSearch     m_ResultSearch;		//结果数据
	CResultSearchNew  m_ResultSearchNew;//新版的历史数据//

	CTreeCtrl         *m_pTaskTree;
	StBasTask         m_CurTaskInfo;

	CTabCtrl          m_ShowTaskInfoTab;

	LoadOutTaskXmlAnalysis m_LoadOutTask;
	int               m_ShowType;
	
	CppSQLite3DB  m_SqliteDb;
protected:
	virtual void OnOK();
public:
	void  AutoSize();
	void  SetControlShow(UINT nShow);//基本信息//

	void  GetTreeItemType(HTREEITEM hItem,StBasTask *pStr);

	//BOOL  AddNewTask();	//新建任务///
	BOOL  EditTast();		//修改这个任务//
	BOOL  DelTast();		//删除这个任务//

	BOOL  SendTaskToPad();	//下发这个任务//
	BOOL  StopTask();		//中止这个任务//


	//任务相关
	//----------------------------------------------------------------
	void  DisplayTaskInfo();			//更新任务显示信息//
	void  FindCurTaskProdNumbels();		//显示任务所有的产品编号信息//
	void  FindCurTaskModes();			//显示任务所有模板信息//
	void  FindCurTaskPicNum();			//显示任务所选中的图号//
	void  BuildTaskDetail();			//组建任务的详细信息//
	
	void  InitTaskTypeComBo();			//初始化 ComBox//
    UINT  GetSelDepartOid();			

	CString GetCDateCtrlTime(UINT UID);	//获取时间控件的时间///
	BOOL  GetChangeTaskInfo();			//检查任务信息是否被更改/


	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	afx_msg void OnTcnSelchangeShowtaskinfoTab(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL DestroyWindow();

	afx_msg void OnBnClickedSelProductnoBtn();
	afx_msg void OnBnClickedSelUpdepartBtn();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
protected:
	virtual void OnCancel();
};
