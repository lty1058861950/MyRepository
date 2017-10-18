// DataManageDoc.cpp : implementation of the CDataManageDoc class
//

#include "stdafx.h"
#include "DataManage.h"

#include "DataManageDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataManageDoc

IMPLEMENT_DYNCREATE(CDataManageDoc, CDocument)

BEGIN_MESSAGE_MAP(CDataManageDoc, CDocument)
	//{{AFX_MSG_MAP(CDataManageDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataManageDoc construction/destruction

CDataManageDoc::CDataManageDoc()
{
	// TODO: add one-time construction code here
}

CDataManageDoc::~CDataManageDoc()
{
}

BOOL CDataManageDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDataManageDoc serialization

void CDataManageDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDataManageDoc diagnostics

#ifdef _DEBUG
void CDataManageDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDataManageDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDataManageDoc commands
