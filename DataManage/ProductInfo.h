#pragma once


// CProductInfo �Ի���

class CProductInfo : public CDialog
{
	DECLARE_DYNAMIC(CProductInfo)

public:
	CProductInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CProductInfo();

// �Ի�������
	enum { IDD = IDD_PRODUCT_INFO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
