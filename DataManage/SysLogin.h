#pragma once
#include "StdAfx.h"

#include "btn\BtnST.h"

// CSysLogin 对话框
#define TEXT_SIZE_MODE				20
class CSysLogin : public CDialog
{
	DECLARE_DYNAMIC(CSysLogin)

public:
	CSysLogin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSysLogin();

	CButtonST  m_btn1;
	CButtonST  m_btn2;

// 对话框数据
	enum { IDD = IDD_SYSLOGIN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CFont m_fontMark1;
	char  szDefUserName[50];
	void    LoadDefUserLogin();
	virtual BOOL OnInitDialog();
protected:
	BOOL    LoginCheck();
	virtual void OnOK();
public:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	virtual void OnCancel();
};
