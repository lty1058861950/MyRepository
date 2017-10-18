#pragma once
#include "afxcmn.h"
#include "mylistctrl\editablelistctrl.h"

#include "ShowDepart.h"
// CDepartMng �Ի���

class CDepartMng : public CDialog
{
	DECLARE_DYNAMIC(CDepartMng)

public:
	CDepartMng(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDepartMng();

// �Ի�������
	enum { IDD = IDD_GROUPMNG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	StHrGroup m_CurSelDepart;
	CTreeCtrl m_DepartMngTree;
	CEditableListCtrl m_CurDepartUsrList;
	CImageList	m_TreeImgList;

public:
	CMenu		m_PopupMenu1;
	CMenu		m_PopupMenu2;
	void InitPopMenu1( );					//��ʼ���˵�1
	void InitPopMenu2( );					//��ʼ���˵�2	


public:
	void     InitDepartTree();
	void     InitUsrList();
	void     InitContrlState();
	void     NotFindSetNull();
	void     ShowDepartInfo();


	BOOL     DeleteOneDepart(StHrGroup *pDepartInfo);
	BOOL     AddNewDepart(StHrGroup *pDepartInfo);
	BOOL     EditOneDepart(StHrGroup *pDepartInfo);

	void     SetDepartTree(CString strText,int EditMode,int Param = 0,HTREEITEM NextItem = NULL);
	void     AutoSize();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNMClickDepartMngTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedDepartAddBtn();
	afx_msg void OnBnClickedDepartDelBtn();
	afx_msg void OnBnClickedDepartEditBtn();
	afx_msg void OnNMDblclkDepartMngTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickDepartMngTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedRecoveryBtn();
};
