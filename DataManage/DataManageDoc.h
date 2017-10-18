// DataManageDoc.h : interface of the CDataManageDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATAMANAGEDOC_H__8D83F9C9_3262_4B35_9528_A85BEB61EA09__INCLUDED_)
#define AFX_DATAMANAGEDOC_H__8D83F9C9_3262_4B35_9528_A85BEB61EA09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDataManageDoc : public CDocument
{
protected: // create from serialization only
	CDataManageDoc();
	DECLARE_DYNCREATE(CDataManageDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataManageDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDataManageDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDataManageDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATAMANAGEDOC_H__8D83F9C9_3262_4B35_9528_A85BEB61EA09__INCLUDED_)
