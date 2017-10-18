#pragma once
#include "mylistctrl\editablelistctrl.h"


// CPicNumMng �Ի���

class CPicNumMng : public CDialog
{
	DECLARE_DYNAMIC(CPicNumMng)

public:
	CPicNumMng(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPicNumMng();

// �Ի�������
	enum { IDD = IDD_PICNUMMNG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEditableListCtrl m_PicNumList;
	StBasProduct *m_pCurSelProduct;
	int m_CurSelItem;
	StBasPicNum m_PicNumInfo;

	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	void    InitPicNumList();
	afx_msg void OnBnClickedAddBtn();
	afx_msg void OnBnClickedDelBtn();
	afx_msg void OnBnClickedOk();
	afx_msg void OnNMClickPicnumList(NMHDR *pNMHDR, LRESULT *pResult);
};
