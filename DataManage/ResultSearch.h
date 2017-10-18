#pragma once
#include "mylistctrl\editablelistctrl.h"
#include "ResultShow.h"

#define  ID_MENU1_DELDATA_BASE              2011
#define  ID_MENU1_C_TASK_REPORT_BASE        2012
#define  ID_MENU1_DELDATA_ATTA              2021
#define  ID_MENU1_C_PRODUCT_REPORT_ATTA     2022
#define  ID_MENU1_C_MODE_REPORT_ATTA        2023
// CResultSearch 对话框

class CResultSearch : public CDialog
{
	DECLARE_DYNAMIC(CResultSearch)

public:
	CResultSearch(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CResultSearch();

// 对话框数据
	enum { IDD = IDD_RESULT_SEARCH_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMenu		m_PopupMenu1;
	CMenu		m_PopupMenu2;
	void InitPopMenu1( );					//初始化菜单1
	void InitPopMenu2( );					//初始化菜单2
public:
	void  AutoSize();
		
	void  SetContrlShow();

	BOOL  SearchBaseByTaskName();//通过模糊查询检索任务列表//

	BOOL  ShowCurData();//显示找到的数据///

	void  DelBaseData();//以任务为单位删除结果数据//
	void  DelAttaData();//以结果附件为单位删除结果数据//

	void  CreateTaskReport();//以任务为单位生成报告文件//
	void  CreateProductCodeReport();//以产品编号为单位生成报告文件//
	void  CreateModeReport();//以模板为单位生成报告文件
	void  CreateReportBase(vector<StTstResultAtta> *StResultAtta,CString strCreateFile);//生成报告
public:
	StTstResultBase m_TstResultBase;
	StTstResultAtta m_TstResultAtta;
	
	virtual BOOL OnInitDialog();

	afx_msg void OnPaint();
	CEditableListCtrl m_TstRresultAttaList;
	CEditableListCtrl m_TstRresultBaseList;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedResultSearchBtn();
protected:
	virtual void OnOK();
public:
	afx_msg void OnNMDblclkResultSearchList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickResultSearchList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedResultSearchTaskBtn();
	afx_msg void OnBnClickedResultSearchProductnoBtn();
	afx_msg void OnBnClickedResultSearchBeginBtn();
	afx_msg void OnBnClickedResultSearchEndBtn();
	afx_msg void OnNMRClickResultSearchList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickResultSearchList1(NMHDR *pNMHDR, LRESULT *pResult);
};
