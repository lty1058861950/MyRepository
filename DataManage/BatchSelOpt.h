#pragma once
#include "mylistctrl\editablelistctrl.h"

#define   ID_RECOVERY_MENU      2057
// CBatchSelOpt �Ի���

class CBatchSelOpt : public CDialog
{
	DECLARE_DYNAMIC(CBatchSelOpt)

public:
	CBatchSelOpt(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBatchSelOpt();

// �Ի�������
	enum { IDD = IDD_BATCH_SEL_BTN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int  m_nType;
	CMenu		m_PopupMenu1;
	CMenu		m_PopupMenu2;
	void InitPopMenu1( );					//��ʼ���˵�1
	void InitPopMenu2( );					//��ʼ���˵�2	

public:
	CEditableListCtrl m_list;  
	void    ListCtrl_ClearAllColumn(CEditableListCtrl *pList);

	void    RecoveryGroup();
	void    InitInvalidDepartList();
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
};
