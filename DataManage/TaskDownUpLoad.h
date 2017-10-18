#pragma once

#include "TaskDownLoadAll.h"
#include "TaskDownLoadSel.h"
#include "TaskUpLoad.h"
#include "BatchImportData.h"

// CTaskDownUpLoad 对话框

class CTaskDownUpLoad : public CDialog
{
	DECLARE_DYNAMIC(CTaskDownUpLoad)

public:
	CTaskDownUpLoad(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTaskDownUpLoad();

// 对话框数据
	enum { IDD = IDD_TASK_OUT_IN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CTaskDownLoadAll  m_TaskDownLoadAll;
	CTaskDownLoadSel  m_TaskDownLoadSel;

	CTaskUpLoad       m_TaskUpLoad;

	StBasTask         m_TaskSearchInfo;
	int               m_ShowType;

	CBatchImportData  m_BatchImportData;
	virtual BOOL OnInitDialog();
	void     AutoSize();
	void     DisPlayTaskInfo(StBasTask *pStBasTaskSearchInfo);
	void     InsertOneTaskToList(StBasTask *pBasTaskInfo);
	BOOL     CheckItemSame(UINT OID);//检查是否已有这一项了//

	void     DisPlayResultList();
	void     InsertTaskDataToList(StBasTask *pBasTaskInfo);
protected:
	virtual void OnOK();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
};
