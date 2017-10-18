#pragma once


// CTaskFuction 对话框

class CTaskFuction : public CDialog
{
	DECLARE_DYNAMIC(CTaskFuction)

public:
	CTaskFuction(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTaskFuction();

// 对话框数据
	enum { IDD = IDD_TASK_BTN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	StBasTask *m_pTaskSearchInfo;
	virtual BOOL OnInitDialog();
	void     AutoSize();
protected:
	virtual void OnOK();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedTaskAddBtn();
	afx_msg void OnBnClickedTaskEdtBtn();
	afx_msg void OnBnClickedTaskDelBtn();
	afx_msg void OnBnClickedTaskSendBtn();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton4();
};
