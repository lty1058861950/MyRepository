#pragma once


// CResetUsrPwd �Ի���

class CResetUsrPwd : public CDialog
{
	DECLARE_DYNAMIC(CResetUsrPwd)

public:
	CResetUsrPwd(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CResetUsrPwd();

// �Ի�������
	enum { IDD = IDD_RESETPWD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
};
