#pragma once
#include "GridCtrl_src/GridCtrl.h"
//#include "afxwin.h"
#include "resource.h"
#include "ShowTaskInfo.h"
#include "ModeParMng.h"
#include "ModeXmlAnalysis.h"

#include "SqliteDb\CppSQLite3.h"
//class CppSQLite3DB;
class CShowTaskInfo;
// CShowTaskData 对话框

class CShowTaskData : public CDialog
{
	DECLARE_DYNAMIC(CShowTaskData)

public:
	CShowTaskData(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CShowTaskData();

// 对话框数据
	enum { IDD = IDD_SHOWTASKDATA_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CGridCtrl			*m_pGrid;
	CEditableListCtrl   m_DecList;
	CShowTaskInfo       *m_pShowTaskInfo;

	CModeParMng			*m_pModeParMng;
	CModeXmlAnalysis	*m_pModeXmlAnalysis;

	void  InitGridCtrl_NULL();
	void  InitGridCtrl();
	void  InitGridCtrl_MUL( );

	void  AutoSize();
public:
	void    InitTaskDecList();
	//读取模板的配置   采集的数据文件//
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNMClickShowtaskdataDecList(NMHDR *pNMHDR, LRESULT *pResult);

	BOOL  AutoBuildTabStruct(CString nModeTabName,CppSQLite3DB *pSqlite,int Flags = 1);//0.创建Sqlite  //1.创建Oracle 
};
