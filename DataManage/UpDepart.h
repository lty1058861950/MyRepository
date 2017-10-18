#pragma once
#include "afxcmn.h"


#define    ID_UP_DEPART_ADD        5001
#define    ID_UP_DEPART_MODIFY     5002
#define    ID_UP_DEPART_DEL        5003
// CUpDepart 对话框

class CUpDepart : public CDialog
{
	DECLARE_DYNAMIC(CUpDepart)

public:
	CUpDepart(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUpDepart();

// 对话框数据
	enum { IDD = IDD_UP_DEPART_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMenu		m_PopupMenu1;
	CMenu		m_PopupMenu2;
	void InitPopMenu1( );					//初始化菜单1
	void InitPopMenu2( );					//初始化菜单2	

	virtual BOOL OnInitDialog();
	void    AutoSize();
	void    InitDepartTree();

	void     NotFindSetNull();
	void     ShowDepartInfo();

	void    OnMenuDepartAdd();
	void    OnMenuDepartModify();
	void    OnMenuDepartDel();
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	CTreeCtrl m_UpDepartTree;
	CImageList	m_TreeImgList;
	StHrUpDepart  m_UpDepartInfo;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
};
