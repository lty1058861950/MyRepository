#pragma once
#include "mylistctrl\editablelistctrl.h"
#include "PathDialog.h"


// CTaskUpLoad 对话框
class CTaskDownUpLoad;
class CTaskUpLoad : public CDialog
{
	DECLARE_DYNAMIC(CTaskUpLoad)

public:
	CTaskUpLoad(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTaskUpLoad();

// 对话框数据
	enum { IDD = IDD_TASK_UPLOAD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEditableListCtrl m_ResultList;
	CRect             m_rcRect1,m_rcRect2;
	CRect             m_rcRect3,m_rcRect4, m_rcRect5;
	CTaskDownUpLoad   *m_pTaskDownUpLoad;

	CString           m_strCurTaskDataPath;
	CString           m_strDecFileName;
	virtual BOOL OnInitDialog();
	void     AutoSize();
protected:
	virtual void OnOK();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
