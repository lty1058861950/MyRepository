#pragma once
#include "GridCtrl_src/GridCtrl.h"


#include "ExcelOptFun.h"
#include "ModeParMng.h"
#include "ModeXmlAnalysis.h"
#include "DlgParMng.h"
class CDlgParMng;
// CShowModeStyle 对话框
class CShowModeInfo;
class CShowModeStyle : public CDialog
{
	DECLARE_DYNAMIC(CShowModeStyle)

public:
	CShowModeStyle(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CShowModeStyle();

// 对话框数据
	enum { IDD = IDD_SHOWMODESTYLE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CGridCtrl  *m_pGrid;

	CShowModeInfo       *m_pShowModeInfo;
	CExcelOptFun		*m_pExcelOptFun;
	CModeParMng			*m_pModeParMng;
	CModeXmlAnalysis	*m_pModeXmlAnalysis;

	CDlgParMng    *m_pDlgParMng;

	int           m_bTabCheck;

	int   CheckAndDisplayAlarmBk( );
	int   CopyExcelDataToPar(CExcelOptFun *pXls,CModeParMng  *pPar);
	int   CopyParDataToExcel(CModeParMng  *pPar,CExcelOptFun *pXls);

	void  InitGridCtrl_NULL();
	void  InitGridCtrl();
	void  InitGridCtrl_MUL( );

	BOOL  DisPlayModeStyle();
	void  AutoSize();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedShowmodestyleParBtn();
protected:
	virtual void OnOK();
public:
	afx_msg void OnBnClickedShowmodestyleShowBtn();
	afx_msg void OnBnClickedLoadModeBtn();
	afx_msg void OnBnClickedOutModeBtn();
};
