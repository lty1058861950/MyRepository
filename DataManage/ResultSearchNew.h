#pragma once
#include "mylistctrl\editablelistctrl.h"
#include "ResultSearchInfo.h"
#include "ResultList.h"

// CResultSearchNew 对话框
#define  ID_MENU1_DELDATA_BASE_NEW              2011
#define  ID_MENU1_C_TASK_REPORT_BASE_NEW        2012
#define  ID_MENU1_DELDATA_ATTA_NEW              2021
#define  ID_MENU1_C_PRODUCT_REPORT_ATTA_NEW     2022
#define  ID_MENU1_C_MODE_REPORT_ATTA_NEW        2023
class CResultSearchNew : public CDialog
{
	DECLARE_DYNAMIC(CResultSearchNew)

public:
	CResultSearchNew(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CResultSearchNew();

// 对话框数据
	enum { IDD = IDD_RESULT_SEARCH_NEW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMenu		m_PopupMenu1;
	CMenu		m_PopupMenu2;
	void InitPopMenu1( );					//初始化菜单1
	void InitPopMenu2( );					//初始化菜单2

	void  Menu1Fuction();
	void  DelBaseDataNew();//以任务为单位删除结果数据//

	void  Menu2Fuction();
	void  CreateTaskReportNew();//以任务为单位生成报告文件//
	void  CreateProductCodeReportNew();//以产品编号为单位生成报告文件//
	void  CreateModeReportNew();//以模板为单位生成报告文件
	void  CreateReportBaseNew(vector<StTstResultAtta> *StResultAtta,CString strCreateFile);//生成报告

public:
	StBasTask    m_ResultSearchInfo;
	StTstResultAtta   m_CurSelResultAtta;
	CResultSearchInfo  m_ResultSearchInfoDlg;
	CResultList  m_ResultTaskBase, m_ResultAttach;

	CEditableListCtrl m_TstRresultBaseList;
	CEditableListCtrl m_TstRresultAttaList;
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void     AutoSize();
	void     InitListCtrlColumn();
	void     InsertTaskBaseDataToList(StTstResultBaseNew *pTaskBaseData);
	void     InsertResultAttachToList(StTstResultAtta    *pResultAttachData);

	void  SetContrlShow();    //设置控件的状态//
	int  SearchResultData();  //查询函数//


	BOOL  GetCurSelAttaData( );      //获取当前被选中的结果附件数据
	int   ShowAttaData();      //显示附件数据//
	
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickList2(NMHDR *pNMHDR, LRESULT *pResult);
};
