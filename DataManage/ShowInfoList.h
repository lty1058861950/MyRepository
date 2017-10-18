#pragma once
#include "mylistctrl\editablelistctrl.h"

#include "ResultList.h"
#include "ProductSearch.h"
#include "ProductFuction.h"
#include "ProductInfo.h"
#include "ProductPicNum.h"

#include "ModeFuction.h"
#include "ModeSearch.h"

#include "TaskFuction.h"
#include "TaskSearch.h"



// CShowInfoList 对话框

class CShowInfoList : public CDialog
{
	DECLARE_DYNAMIC(CShowInfoList)

public:
	CShowInfoList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CShowInfoList();

// 对话框数据
	enum { IDD = IDD_SHOWLIST_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	
	CResultList    m_ResultList;			//结果列表_带分页

	CProductSearch m_ProductSearch;			//产品查询对话框_查询条件
	/*CProductInfo   m_ProductInfo;
	CProductPicNum m_ProductPicNum;*/
	CProductFuction m_ProductFuction;		//产品操作对话框_操作按钮


	CShowModeInfo  m_ShowModeInfo;			//模板对话框
	CModeSearch    m_ModeSearch;			//模板查询对话框_查询条件
	CModeFuction   m_ModeFuction;			//模板操作对话框_操作按钮



	CTaskFuction  m_TaskFuction;
	CShowTaskInfo  m_ShowTaskInfo;
	CTaskSearch   m_TaskSearch;
	int          m_ShowType;

	virtual BOOL OnInitDialog();
	void    AutoSize();
	void ListCtrl_ClearAllColumn();

	void ChangeShowWindow(int nShowType);								//切换显示
	void ChangeTaskBtnShow(StBasTask *pTaskSearchInfo);					//任务切换: 新任务，已派工，已执行，已完成

	void DisplayProdInfo(StBasProduct *pStBasProduct);					//显示产品列表
	void InsertOneProdToList(StBasProduct *pStBasProduct);				//插入一个产品更新列表
	void ModifyOneProdToList(int nIndex, StBasProduct *pStBasProduct);	//修改一个产品更新更表
	
	void DisplayModeInfo(StBasMode *pModesearchInfo);					//显示模板列表
	void InsertOneModeToList(StBasMode *pStBasMode);					//插入一个模板更新列表
	void ModifyOneModeToList(int nIndex, StBasMode *pStBasMode);		//修改一个产品更新列表

	int  DisPlayTaskInfo(StBasTask *pStBasTaskSearchInfo);				//显示任务列表
	void InsertOneTaskToList(StBasTask *pStBasTask);					//插入一个任务更新列表
	void ModifyOneTaskToList(int nIndex,StBasTask *pBasTaskInfo);		//修改一个任务更新列表

	void DisplayOneModeDescInfo();										//显示一个模板对话框
	void DisplayOneTaskDescInfo();										//显示一个任务对话框

protected:
	virtual void OnOK();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
