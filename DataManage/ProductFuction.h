#pragma once


// CProductFuction �Ի���

class CProductFuction : public CDialog
{
	DECLARE_DYNAMIC(CProductFuction)

public:
	CProductFuction(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CProductFuction();

// �Ի�������
	enum { IDD = IDD_PRODUCT_BTN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
