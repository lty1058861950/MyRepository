#pragma once


// CModeFuction �Ի���

class CModeFuction : public CDialog
{
	DECLARE_DYNAMIC(CModeFuction)

public:
	CModeFuction(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CModeFuction();

// �Ի�������
	enum { IDD = IDD_MODE_BTN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void  AutoSize();
protected:
	virtual void OnOK();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedModemngAddBtn();
	afx_msg void OnBnClickedModemngDelBtn();
	afx_msg void OnBnClickedModemngEditBtn();
	afx_msg void OnBnClickedModemngCopyBtn();
	afx_msg void OnBnClickedModemngPasteBtn();
};
