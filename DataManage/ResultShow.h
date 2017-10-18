#pragma once
#include "afxcmn.h"
#include "LoadOutTaskXmlAnalysis.h"
#include "ExcelOptFun.h"

// CResultShow 对话框
#define               ID_MENU1_LOADOUT_ATTACH      5021
#define               ID_MENU2_OPEN_DIRECTORY      5022

class CResultShow : public CDialog
{
	DECLARE_DYNAMIC(CResultShow)

public:
	CResultShow(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CResultShow();

// 对话框数据
	enum { IDD = IDD_RESULT_SHOW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CGridCtrl			*m_pGrid;

	CMenu		m_PopupMenu1;
	void        InitPopMenu1( );					//初始化菜单1

	/*CModeParMng			m_ModeParMng;
	CModeXmlAnalysis	m_ModeXmlAnalysis;
	CExcelOptFun		m_ExcelOptFun;*/


	StTstResultAtta     *m_pCurAttaInfo;
	LoadOutTaskXmlAnalysis  m_LoadOutTask;
	CArray<TestDataStr,TestDataStr> m_DataArray;
	CArray<StBasAttachment,StBasAttachment> m_ExclosureArray;

	void  InitGridCtrl_NULL();
	void  InitGridCtrl();
	void  InitGridCtrl_MUL( );
	void  DisplayOutDataDesc( );
	void  DisplayProdAppData();

	int   CopyParDataToExcel(CModeParMng  *pPar,CExcelOptFun *pXls);
	void  AutoSize();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CTabCtrl m_Tab1;
	CEditableListCtrl m_DecList;              
	CEditableListCtrl m_AttachmentList;
	CFont m_fontMark1;
	CString m_ProductInfo;
	CString m_CurFilePath;
	afx_msg void OnTcnSelchangeReshowTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCreateReportBtn();
	afx_msg void OnBnClickedOutDataBtn();
	afx_msg void OnNMRClickAttachmentList(NMHDR *pNMHDR, LRESULT *pResult);

	void     LoadOutAttachFile();
	void     OpenFileDirectory();
};
