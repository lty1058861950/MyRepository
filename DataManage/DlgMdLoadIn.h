#if !defined(AFX_DLGMDLOADIN_H__C7BA711F_2D60_4C3D_A3FD_81167133D328__INCLUDED_)
#define AFX_DLGMDLOADIN_H__C7BA711F_2D60_4C3D_A3FD_81167133D328__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMdLoadIn.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMdLoadIn dialog

class CDlgMdLoadIn : public CDialog
{
// Construction
public:
	CDlgMdLoadIn(CWnd* pParent = NULL);   // standard constructor

public:
	int		m_IsOpen;
	CString m_strPath;
	int     m_nType;    //1.导入, 2.导出, 3.添加附件

// Dialog Data
	//{{AFX_DATA(CDlgMdLoadIn)
	enum { IDD = IDD_MODE_LOAD_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMdLoadIn)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMdLoadIn)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnPath();
	virtual void OnOK();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMDLOADIN_H__C7BA711F_2D60_4C3D_A3FD_81167133D328__INCLUDED_)
