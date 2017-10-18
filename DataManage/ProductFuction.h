#pragma once


// CProductFuction 对话框

class CProductFuction : public CDialog
{
	DECLARE_DYNAMIC(CProductFuction)

public:
	CProductFuction(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CProductFuction();

// 对话框数据
	enum { IDD = IDD_PRODUCT_BTN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int         m_ChangeStatus;
	StBasProduct *m_pProdInfo;

	UINT        m_nProductOid;
public:
	virtual BOOL OnInitDialog();
	void     AutoSize();
protected:
	virtual void OnOK();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedProdAddBtn();
	afx_msg void OnBnClickedProdDelBtn();
	afx_msg void OnBnClickedProdEdtBtn();
	afx_msg void OnBnClickedProdDelAll();
};
