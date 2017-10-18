#pragma once
#include "mylistctrl\editablelistctrl.h"


// CProductPicNum �Ի���

class CProductPicNum : public CDialog
{
	DECLARE_DYNAMIC(CProductPicNum)

public:
	CProductPicNum(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CProductPicNum();

// �Ի�������
	enum { IDD = IDD_PRODUCT_PICNUM_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEditableListCtrl m_PicNumList;
	StBasProduct  *m_pCurProdInfo;
public:
	virtual BOOL OnInitDialog();
	void     AutoSize();

	void     DisplayProductPicNum(CEditableListCtrl *pList);
	void     InitPicNumList();

protected:
	virtual void OnOK();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	afx_msg void OnBnClickedPicnummngBtn();
};
