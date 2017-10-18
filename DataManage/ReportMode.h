#pragma once
#include "mylistctrl\editablelistctrl.h"

#define   ID_MENU1_LOADIN    2000
#define   ID_MENU2_OPENDIR   2001

// CReportMode 对话框

class CReportMode : public CDialog
{
	DECLARE_DYNAMIC(CReportMode)

public:
	CReportMode(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CReportMode();

// 对话框数据
	enum { IDD = IDD_REPORT_MODE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	CMenu		m_PopupMenu1;
	void        InitPopMenu1( );					//初始化菜单1
	CString     m_CurFilePath;

	int         m_ShowType;

public:
	virtual BOOL OnInitDialog();
	void    InitReportModeList();
	COLORREF ModeFileIsExists(CString szFilePath, int Index);//检查当前报告模板是否存在//
	//CString BuildFilePath(StBasMode *pModeInfo);//组建模板路径//
	void     InsertModeToList(StBasMode *pModeInfo);

	void    Refurbish();//刷新状态//

	void    LoadInModeFile();//导入模板文件//
	void    OpenFileDir();//打开文件所在文件夹//
	void    AutoSize();
	CEditableListCtrl m_ReportModeList;
	afx_msg void OnBnClickedShowBtn();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void OnUpdateChart(UINT nID) ;

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
};
