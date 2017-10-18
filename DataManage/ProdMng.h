#pragma once
#include "mylistctrl\editablelistctrl.h"
#include "afxcmn.h"

// CProdMng �Ի���


class CProdMng : public CDialog
{
	DECLARE_DYNAMIC(CProdMng)

public:
	CProdMng(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CProdMng();

// �Ի�������
	enum { IDD = IDD_PRODMNG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	StBasProduct     m_CurProdInfo;

	CProductInfo     m_ProductInfo;
	CProductPicNum   m_ProductPicNum;
public:
	void     AutoSize();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	int             m_ShowType;
protected:
	virtual void OnOK();
};
