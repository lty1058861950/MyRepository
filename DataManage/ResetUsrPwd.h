#pragma once


// CResetUsrPwd 对话框

class CResetUsrPwd : public CDialog
{
	DECLARE_DYNAMIC(CResetUsrPwd)

public:
	CResetUsrPwd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CResetUsrPwd();

// 对话框数据
	enum { IDD = IDD_RESETPWD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
};
