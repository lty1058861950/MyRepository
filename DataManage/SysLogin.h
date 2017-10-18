#pragma once
#include "StdAfx.h"

#include "btn\BtnST.h"

// CSysLogin �Ի���
#define TEXT_SIZE_MODE				20
class CSysLogin : public CDialog
{
	DECLARE_DYNAMIC(CSysLogin)

public:
	CSysLogin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSysLogin();

	CButtonST  m_btn1;
	CButtonST  m_btn2;

// �Ի�������
	enum { IDD = IDD_SYSLOGIN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
