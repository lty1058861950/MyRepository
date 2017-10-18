#pragma once


// CProductInfo 对话框

class CProductInfo : public CDialog
{
	DECLARE_DYNAMIC(CProductInfo)

public:
	CProductInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CProductInfo();

// 对话框数据
	enum { IDD = IDD_PRODUCT_INFO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	StBasProduct  *m_pCurProdInfo;
public:
	virtual BOOL OnInitDialog();
	void     AutoSize();
	void     DisPlayProductInfo();////
	void     GetProdInfo();

protected:
	virtual void OnOK();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
