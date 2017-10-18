// DataManageView.h : interface of the CDataManageView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATAMANAGEVIEW_H__E4FA1400_860D_4FF1_BA6E_8029605DD015__INCLUDED_)
#define AFX_DATAMANAGEVIEW_H__E4FA1400_860D_4FF1_BA6E_8029605DD015__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TaskMng.h"

//#include "HisExtremum.h"
#include "ModeMng.h"

#include "ResultSearch.h"
#include "DataManageDoc.h"

#include "ReportMng.h"

#include "ShowInfoList.h"

class CDataManageView : public CFormView
{
protected: // create from serialization only
	CDataManageView();
	DECLARE_DYNCREATE(CDataManageView)

public:
	//{{AFX_DATA(CDataManageView)
	enum{ IDD = IDD_DATAMANAGE_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CDataManageDoc* GetDocument(); 

	int  m_uMenuSelRow ;//当前选择的菜单行
	int  m_uMenuSelCol ;//当前选择的菜单列
// Operations
public:
	CModeParMng			m_ModeParMng2;
	CModeXmlAnalysis	m_ModeXmlAnalysis2;
	CExcelOptFun		m_ExcelOptFun2;
public:
	//CUserMenage  m_UsrMng;

	//CProdMng     m_ProdMng;
	//CDepartMng   m_DepartMng;

	//CModeMng     m_ModeMng;//模板//

	//CHisExtremum m_HisExtremum;//极值//

	//CTaskMng     m_TaskMng;//检查任务//
	//CTaskLoadOut m_TaskLoadOut;
	//CTaskLoadIn  m_TaskLoadIn;

	CResultSearch        m_ResultSearch;//结果查询//
	CResultSearchNew     m_ResultSearchNew;     //结果查询//  新版的

	CReportMng    m_ReportMng;//生成报告///

	CShowInfoList  m_ShowInfoList;
	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataManageView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDataManageView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDataManageView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	afx_msg void OnFilePrintPreview();
	DECLARE_MESSAGE_MAP()
public:
	void AdjustSize() ;
	void ChangeViewMode(int nMenuSelRow, int nMenuSelCol) ;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
};

#ifndef _DEBUG  // debug version in DataManageView.cpp
inline CDataManageDoc* CDataManageView::GetDocument()
   { return (CDataManageDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATAMANAGEVIEW_H__E4FA1400_860D_4FF1_BA6E_8029605DD015__INCLUDED_)
