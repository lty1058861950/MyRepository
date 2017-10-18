#pragma once


// CModeFuction 对话框

class CModeFuction : public CDialog
{
	DECLARE_DYNAMIC(CModeFuction)

public:
	CModeFuction(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CModeFuction();

// 对话框数据
	enum { IDD = IDD_MODE_BTN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
