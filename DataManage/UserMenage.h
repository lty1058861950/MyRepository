#pragma once

#include "resource.h"
#include "mylistctrl\editablelistctrl.h"

#include "ShowUsr.h"
// CUserMenage 对话框

class CUserMenage : public CDialog
{
	DECLARE_DYNAMIC(CUserMenage)

public:
	CUserMenage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserMenage();

// 对话框数据
	enum { IDD = IDD_USERMENAGE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEditableListCtrl m_UsrMngList;
public:
	CMenu		m_PopupMenu1;
	CMenu		m_PopupMenu2;
	StHrUser    m_CurUserInfo;
	void InitPopMenu1( );					//初始化菜单1
	void InitPopMenu2( );					//初始化菜单2
public:
	virtual BOOL OnInitDialog();
	//查找显示函数///
	void     InitTestList();
	void     InsertUserToList(StHrUser *pUserInfo);

	//添加和修改函数////
	BOOL     AddNewUsr(StHrUser *nUsrInfo);
	BOOL     DelOneUsr(CString UID);
	BOOL     EditOneUsr(StHrUser *pUsrInfo);
	void     AutoSize();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedUsrmngaddBtn();
	afx_msg void OnBnClickedUsrmngedtBtn();
	afx_msg void OnBnClickedUsrmngdelBtn();
	afx_msg void OnNMDblclkUsrmngList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickUsrmngList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnExit();
};
