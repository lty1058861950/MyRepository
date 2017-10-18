// WordOffice.cpp: implementation of the CWordOffice class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WordOffice.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWordOffice::CWordOffice()
{

}

CWordOffice::~CWordOffice()
{
	CString str;
	str.Format("CWordOffice::~CWordOffice()��%d", 1);
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));

  COleVariant vTrue((short)TRUE),    
                vFalse((short)FALSE),
                vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
				//m_wdDoc.Save();

/*
				m_wdApp.Quit(vFalse,    // SaveChanges.
				vTrue,            // OriginalFormat.
				vFalse            // RouteDocument.
             );
*/

	  try {
		  str.Format("CWordOffice::~CWordOffice()��%d", 2);
		  g_pLogInfo->WriteLogFile(str.GetBuffer(0));
		  m_wdApp.Quit(vFalse,    // SaveChanges.
			  vTrue,            // OriginalFormat.
			  vFalse            // RouteDocument.
			  );
		  str.Format("CWordOffice::~CWordOffice()��%d", 3);
		  g_pLogInfo->WriteLogFile(str.GetBuffer(0));
	  }
	  catch (...) {
		  ;
		  str.Format("CWordOffice::~CWordOffice()��%d", 300);
		  g_pLogInfo->WriteLogFile(str.GetBuffer(0));
	  }

	str.Format("CWordOffice::~CWordOffice()��%d", 4);
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));


    //�ͷ��ڴ�������Դ
    m_wdInlineShape.ReleaseDispatch();


	str.Format("CWordOffice::~CWordOffice()��%d", 5);
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));

    m_wdInlineShapes.ReleaseDispatch();

	str.Format("CWordOffice::~CWordOffice()��%d", 6);
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));

    //m_wdTb.ReleaseDispatch();
    m_wdRange.ReleaseDispatch();

	str.Format("CWordOffice::~CWordOffice()��%d", 7);
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));

    m_wdSel.ReleaseDispatch();

	str.Format("CWordOffice::~CWordOffice()��%d", 8);
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));


    //m_wdFt.ReleaseDispatch();
    m_wdDoc.ReleaseDispatch();

	str.Format("CWordOffice::~CWordOffice()��%d", 9);
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));

    m_wdDocs.ReleaseDispatch();

	str.Format("CWordOffice::~CWordOffice()��%d", 10);
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));


    m_wdApp.ReleaseDispatch();


	str.Format("CWordOffice::~CWordOffice()��%d", 11);
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));

}

//����
BOOL CWordOffice::CreateApp()
{
    if (FALSE == m_wdApp.CreateDispatch("Word.Application"))
    {
        AfxMessageBox("Application����ʧ�ܣ���ȷ����װ��word 2000�����ϰ汾!", MB_OK|MB_ICONWARNING);
        return FALSE;
    }
    return TRUE;
}

BOOL CWordOffice::CreateDocuments()
{
    if (FALSE == CreateApp()) 
    {
        return FALSE;
    }
    m_wdDocs.AttachDispatch(m_wdApp.GetDocuments());
    if (!m_wdDocs.m_lpDispatch) 
    {
        AfxMessageBox("Documents����ʧ��!", MB_OK|MB_ICONWARNING);
        return FALSE;
    }
    return TRUE;
}

BOOL CWordOffice::CreateDocument()
{
    if (!m_wdDocs.m_lpDispatch) 
    {
        AfxMessageBox("DocumentsΪ��!", MB_OK|MB_ICONWARNING);
        return FALSE;
    }

    COleVariant varTrue(short(1),VT_BOOL),vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
    CComVariant Template(_T(""));    //û��ʹ��WORD���ĵ�ģ��
    CComVariant NewTemplate(false),DocumentType(0),Visible;

    m_wdDocs.Add(&Template,&NewTemplate,&DocumentType,&Visible);    

    //�õ�document����
    m_wdDoc = m_wdApp.GetActiveDocument();
    if (!m_wdDoc.m_lpDispatch) 
    {
        AfxMessageBox("Document��ȡʧ��!", MB_OK|MB_ICONWARNING);
        return FALSE;
    }
    //�õ�selection����
    m_wdSel = m_wdApp.GetSelection();
    if (!m_wdSel.m_lpDispatch) 
    {
        AfxMessageBox("Select��ȡʧ��!", MB_OK|MB_ICONWARNING);
        return FALSE;
    }
    //�õ�Range����
    m_wdRange = m_wdDoc.Range(vOptional,vOptional);
    if(!m_wdRange.m_lpDispatch)
    {
        AfxMessageBox("Range��ȡʧ��!", MB_OK|MB_ICONWARNING);
        return FALSE;
    }

    return TRUE;
}

BOOL CWordOffice::Create()
{
    if (FALSE == CreateDocuments()) 
    {
        return FALSE;
    }
    return CreateDocument();
}

void CWordOffice::ShowApp()
{
    m_wdApp.SetVisible(TRUE);
}

void CWordOffice::HideApp()
{
    m_wdApp.SetVisible(FALSE);
}

BOOL CWordOffice::OpenDocument(CString fileName)
{
    if (!m_wdDocs.m_lpDispatch) 
    {
        AfxMessageBox("DocumentsΪ��!", MB_OK|MB_ICONWARNING);
        return FALSE;
    }

    COleVariant vTrue((short)TRUE),    
                vFalse((short)FALSE),
                vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR),
                vZ((short)0);
    COleVariant     vFileName(_T(fileName));
    
    //�õ�document����
    m_wdDoc.AttachDispatch(m_wdDocs.Open(
                                vFileName,        // FileName
                                vTrue,            // Confirm Conversion.
                                vFalse,            // ReadOnly.
                                vFalse,            // AddToRecentFiles.
                                vOptional,        // PasswordDocument.
                                vOptional,        // PasswordTemplate.
                                vOptional,        // Revert.
                                vOptional,        // WritePasswordDocument.
                                vOptional,        // WritePasswordTemplate.
                                vOptional,        // Format. // Last argument for Word 97
                                vOptional,        // Encoding // New for Word 2000/2002
                                vOptional,        // Visible
                                /*����4����word2003��Ҫ�Ĳ��������汾��word2000��*/
                                vOptional,    // OpenAndRepair
                                vZ,            // DocumentDirection wdDocumentDirection LeftToRight
                                vOptional,    // NoEncodingDialog
                                vOptional
                                
                                )                // Close Open parameters
                            );                    // Close AttachDispatch
    
    if (!m_wdDoc.m_lpDispatch) 
    {
        AfxMessageBox("Document��ȡʧ��!", MB_OK|MB_ICONWARNING);
        return FALSE;
    }
    //�õ�selection����
    m_wdSel = m_wdApp.GetSelection();
    if (!m_wdSel.m_lpDispatch) 
    {
        AfxMessageBox("Select��ȡʧ��!", MB_OK|MB_ICONWARNING);
        return FALSE;
    }
    //�õ�ȫ��DOC��Range����
    m_wdRange = m_wdDoc.Range(vOptional,vOptional);
    if(!m_wdRange.m_lpDispatch)
    {
        AfxMessageBox("Range��ȡʧ��!", MB_OK|MB_ICONWARNING);
        return FALSE;
    }
    return TRUE;
}

BOOL CWordOffice::Open(CString fileName)
{
    if (FALSE == CreateDocuments()) 
    {
        return FALSE;
    }
    return OpenDocument(fileName);
}

BOOL CWordOffice::SetActiveDocument(short i)
{
    COleVariant     vIndex(_T(i)),vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

    m_wdDoc.AttachDispatch(m_wdDocs.Item(vIndex));
    m_wdDoc.Activate();
    if (!m_wdDoc.m_lpDispatch) 
    {
        AfxMessageBox("Document��ȡʧ��!", MB_OK|MB_ICONWARNING);
        return FALSE;
    }
    //�õ�selection����
    m_wdSel = m_wdApp.GetSelection();
    if (!m_wdSel.m_lpDispatch) 
    {
        AfxMessageBox("Select��ȡʧ��!", MB_OK|MB_ICONWARNING);
        return FALSE;
    }
    //�õ�ȫ��DOC��Range����
    m_wdRange = m_wdDoc.Range(vOptional,vOptional);
    if(!m_wdRange.m_lpDispatch)
    {
        AfxMessageBox("Range��ȡʧ��!", MB_OK|MB_ICONWARNING);
        return FALSE;
    }
    HideApp();
    return TRUE;
}

BOOL CWordOffice::SaveDocument()
{
    if (!m_wdDoc.m_lpDispatch) 
    {
        AfxMessageBox("Document��ȡʧ��!", MB_OK|MB_ICONWARNING);
        return FALSE;
    }
    m_wdDoc.Save();
    return TRUE;
}

BOOL CWordOffice::SaveDocumentAs(CString fileName)
{
    if (!m_wdDoc.m_lpDispatch) 
    {
        AfxMessageBox("Document��ȡʧ��!", MB_OK|MB_ICONWARNING);
        return FALSE;
    }
    COleVariant vTrue((short)TRUE),    
                vFalse((short)FALSE),
                vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
    COleVariant vFileName(_T(fileName));

    m_wdDoc.SaveAs(
                vFileName,    //VARIANT* FileName
                vOptional,    //VARIANT* FileFormat
                vOptional,    //VARIANT* LockComments
                vOptional,    //VARIANT* Password
                vOptional,    //VARIANT* AddToRecentFiles
                vOptional,    //VARIANT* WritePassword
                vOptional,    //VARIANT* ReadOnlyRecommended
                vOptional,    //VARIANT* EmbedTrueTypeFonts
                vOptional,    //VARIANT* SaveNativePictureFormat
                vOptional,    //VARIANT* SaveFormsData
                vOptional,    //VARIANT* SaveAsAOCELetter
				vOptional,
				vOptional,
				vOptional,
				vOptional,
				vOptional
                );
    return    TRUE;
}

BOOL CWordOffice::CloseDocument()
{
    COleVariant vTrue((short)TRUE),    
                vFalse((short)FALSE),
                vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
    m_wdDoc.Close(vFalse,    // SaveChanges.
             vTrue,            // OriginalFormat.
             vFalse            // RouteDocument.
             );
    m_wdDoc.AttachDispatch(m_wdApp.GetActiveDocument());
    if (!m_wdDoc.m_lpDispatch) 
    {
        AfxMessageBox("Document��ȡʧ��!", MB_OK|MB_ICONWARNING);
        return FALSE;
    }
    //�õ�selection����
    m_wdSel = m_wdApp.GetSelection();
    if (!m_wdSel.m_lpDispatch) 
    {
        AfxMessageBox("Select��ȡʧ��!", MB_OK|MB_ICONWARNING);
        return FALSE;
    }
    //�õ�ȫ��DOC��Range����
    m_wdRange = m_wdDoc.Range(vOptional,vOptional);
    if(!m_wdRange.m_lpDispatch)
    {
        AfxMessageBox("Range��ȡʧ��!", MB_OK|MB_ICONWARNING);
        return FALSE;
    }
    return TRUE;
}

void CWordOffice::CloseApp()
{
    COleVariant vTrue((short)TRUE),    
                vFalse((short)FALSE),
                vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
    m_wdDoc.Save();
    m_wdApp.Quit(vFalse,    // SaveChanges.
             vTrue,            // OriginalFormat.
             vFalse            // RouteDocument.
             );
    //�ͷ��ڴ�������Դ
    m_wdInlineShape.ReleaseDispatch();
    m_wdInlineShapes.ReleaseDispatch();
    //m_wdTb.ReleaseDispatch();
    m_wdRange.ReleaseDispatch();
    m_wdSel.ReleaseDispatch();
    //m_wdFt.ReleaseDispatch();
    m_wdDoc.ReleaseDispatch();
    m_wdDocs.ReleaseDispatch();
    m_wdApp.ReleaseDispatch();
}

void CWordOffice::WriteText(CString szText)
{
    m_wdSel.TypeText(szText);
}

void CWordOffice::WriteNewLineText(CString szText, int nLineCount /* = 1 */)
{
    int i;
    if (nLineCount <= 0)
    {
        nLineCount = 0;
    }
    for (i = 0; i < nLineCount; i++)
    {
        m_wdSel.TypeParagraph();
    }
    WriteText(szText);
}

void CWordOffice::WriteEndLine(CString szText)
{
    m_wdRange.InsertAfter(szText);
}

void CWordOffice::WholeStory()
{
    m_wdRange.WholeStory();
}

void CWordOffice::Copy()
{
    m_wdRange.CopyAsPicture();
}

void CWordOffice::InsertFile(CString fileName)
{
    COleVariant     vFileName(fileName),
                 vTrue((short)TRUE),
                 vFalse((short)FALSE),
                 vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR),
                 vNull(_T(""));
    /*
    void InsertFile(LPCTSTR FileName, VARIANT* Range, VARIANT* ConfirmConversions, VARIANT* Link, VARIANT* Attachment);
    */
    m_wdSel.InsertFile(
                    fileName,
                    vNull,
                    vFalse,
                    vFalse,
                    vFalse
                    );
}

void CWordOffice::InsertShapes(CString fileName)
{
    COleVariant vTrue((short)TRUE),    
                vFalse((short)FALSE),
                vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
    m_wdInlineShapes=m_wdSel.GetInlineShapes();
    m_wdInlineShape=m_wdInlineShapes.AddPicture(fileName,vFalse,vTrue,vOptional);
}

void CWordOffice::AddTable(const long ilIndex, const long inColumn)
{
	CComVariant DefaultTableBehavior(false);
	COleVariant vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	CComVariant AutoFitBehavior(false);
	
	if(inColumn <= 0)
	{
		return;
	}

	m_wdTables = m_wdDoc.GetTables();
	if(!m_wdTables.m_lpDispatch)
	{
		AfxMessageBox("Tables��ȡʧ��!", MB_OK|MB_ICONWARNING);
		return;
	}
	//�õ�table Range
	OfficeWord11:: Range m_tbRange = m_wdSel.GetRange();
	if(!m_tbRange.m_lpDispatch)
	{
		AfxMessageBox("Table Range��ȡʧ��!", MB_OK|MB_ICONWARNING);
		return;
	}
	//������ͷ
	m_wdTables.Add(m_tbRange,1, inColumn,&DefaultTableBehavior,&AutoFitBehavior);
	
	if(ilIndex <= 0)
	{
		m_wdTable = m_wdTables.Item(1);
	}
	else
	{
		m_wdTable = m_wdTables.Item(ilIndex);
	}
	//�õ����еĵ�Ԫ��
	m_wdCell = m_wdTable.Cell(0, 0);    
	m_wdCell.Select();
}

void CWordOffice::SetTableColumnText(CString szText)
{
	CComVariant varUnit(1), varCount(1), varExtend(0);
	//����������
	m_wdSel.TypeText(_T(szText));
	//���ƹ��
	m_wdSel.MoveRight(&varUnit, &varCount, &varExtend);
}

void CWordOffice::InsertTableNewRow()
{
	CComVariant varRowsNum(1);
	m_wdSel.InsertRowsBelow(&varRowsNum);
}

void CWordOffice::AddMultiRowTable(const long ilIndex, const long inRow, const long inColumn)
{
	CComVariant DefaultTableBehavior(false);
	COleVariant vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	CComVariant AutoFitBehavior(false);
	
	if(inColumn <= 0)
	{
		return;
	}
	
	m_wdTables = m_wdDoc.GetTables();
	if(!m_wdTables.m_lpDispatch)
	{
		AfxMessageBox("Tables��ȡʧ��!", MB_OK|MB_ICONWARNING);
		return;
	}
	//�õ�table Range
	OfficeWord11:: Range m_tbRange = m_wdSel.GetRange();
	if(!m_tbRange.m_lpDispatch)
	{
		AfxMessageBox("Table Range��ȡʧ��!", MB_OK|MB_ICONWARNING);
		return;
	}
	//������ͷ
	m_wdTables.Add(m_tbRange, inRow, inColumn,&DefaultTableBehavior,&AutoFitBehavior);
	
	if(ilIndex <= 0)
	{
		m_wdTable = m_wdTables.Item(1);
	}
	else
	{
		m_wdTable = m_wdTables.Item(ilIndex);
	}
}
//��ֵ�Ԫ��
void CWordOffice::SplitTableCell(const long inRow, const long inColumn,  const int inRowNum, const int inColNum)
{
	CComVariant varRowNum(inRowNum), varColNum(inColNum);
	//�õ���Ԫ��
	m_wdCell = m_wdTable.Cell(inRow, inColumn);

	//��ֵ�Ԫ��
	if((inRowNum > 0) && (inColNum >= 0))
	{
		m_wdCell.Split(&varRowNum, &varColNum);
	}

	//m_wdCell.Merge()
	
}

//�ϲ���Ԫ��
void CWordOffice::UnionTableCell(const long inBgnRow, const long inBgnColumn, const long inEndRow, const long inEndColumn)
{
	OfficeWord11:: Cell cBgnCell = m_wdTable.Cell(inBgnRow, inBgnColumn);
	OfficeWord11:: Cell cEndCell = m_wdTable.Cell(inEndRow, inEndColumn);
	cBgnCell.Merge(cEndCell);
	//m_wdCell = m_wdTable.Cell(inEndRow, inEndColumn);
	//m_wdTable.Cell(inBgnRow, inBgnColumn).Merge(m_wdCell);
}

//���õ�Ԫ����
void CWordOffice::SetTableCellWidth(const float inCellWidth, const long inRow, const long inColumn)
{
	m_wdColumns = m_wdTable.GetColumns();
	m_wdColumn = m_wdColumns.Item(inColumn);
	m_wdColumn.SetWidth(inCellWidth, 0);
}

//���õ�Ԫ�������
void CWordOffice::SetTableCellText(CString szText, const long inRow, const long inColumn, const int inUnit)
{
	//ѡ��Ԫ��
	m_wdCell = m_wdTable.Cell(inRow, inColumn);	

	m_wdCell.Select();

	CComVariant varUnit(inUnit), varCount(1), varExtend(0);
	//����������
	m_wdSel.TypeText(_T(szText));
	//���ƹ��
	m_wdSel.MoveRight(&varUnit, &varCount, &varExtend);
}
/*
void CWordOffice::InsertHyperlink(CString fileLink)
{
    COleVariant     vAddress(_T(fileLink)),vSubAddress(_T(""));
    Range aRange = m_wdSel.GetRange();
    Hyperlinks vHyperlinks(aRange.GetHyperlinks());

    vHyperlinks.Add(
                    aRange,            //Object�����衣ת��Ϊ�����ӵ��ı���ͼ�Ρ�
                    vAddress,         //Variant ���ͣ���ѡ��ָ�������ӵĵ�ַ���˵�ַ�����ǵ����ʼ���ַ��Internet ��ַ���ļ�������ע�⣬Microsoft Word �����õ�ַ����ȷ�ԡ�
                    vSubAddress,     //Variant ���ͣ���ѡ��Ŀ���ļ��ڵ�λ����������ǩ���������������õ�Ƭ��š�
                    vAddress,         //Variant ���ͣ���ѡ�������ָ�����ָ���ĳ�������ʱ��ʾ�Ŀ���������Ļ��ʾ�����ı���Ĭ��ֵΪ Address��
                    vAddress,         //Variant ���ͣ���ѡ��ָ���ĳ����ӵ���ʾ�ı����˲�����ֵ��ȡ���� Anchor ָ�����ı���ͼ�Ρ�
                    vSubAddress        //Variant ���ͣ���ѡ��Ҫ�����д�ָ���ĳ����ӵĿ�ܻ򴰿ڵ����֡�
                    ); 
    vHyperlinks.ReleaseDispatch();
}
*/

//==============================================================================



void CWordOffice::CreateTable(const long ilIndex, int nRow, int nColumn)
{
	m_wdDoc = m_wdApp.GetActiveDocument();
	
	OfficeWord11::Tables tbs = m_wdDoc.GetTables();
	VARIANT vtDefault, vtAuto;
	vtDefault.vt = VT_I4;
	vtAuto.vt = VT_I4;
	vtDefault.intVal = 1;
	vtAuto.intVal = 0;
	tbs.Add(m_wdSel.GetRange(), nRow, nColumn, &vtDefault, &vtAuto);  
	
	if (ilIndex <= 0)
	{
		m_wdTable = tbs.Item(1);
	}
	else
	{
		m_wdTable = tbs.Item(ilIndex);
	}
	VARIANT vtstyle;
	vtstyle.vt = VT_BSTR;
	_bstr_t bstr = "������";
	vtstyle.bstrVal = bstr;
	if (m_wdTable.GetStyle().bstrVal == vtstyle.bstrVal)
	{
		m_wdTable.SetStyle(&vtstyle);
		m_wdTable.SetApplyStyleFirstColumn(TRUE);
		m_wdTable.SetApplyStyleHeadingRows(TRUE);
		m_wdTable.SetApplyStyleLastColumn(TRUE);
		m_wdTable.SetApplyStyleLastRow(TRUE);        
	}
	
}

void CWordOffice::WriteCellText(int nRow, int nColumne, CString szText)
{
	OfficeWord11::Cell c = m_wdTable.Cell(nRow, nColumne);
	c.Select();
	m_wdSel.TypeText(szText);
}

void CWordOffice::SetFont(CString szFontName /*= "����"*/,float fSize, long lFontColor /*= 0*/,long lBackColor /*= 0*/)
{
	if (!m_wdSel.m_lpDispatch) 
	{
		AfxMessageBox("SelectΪ�գ���������ʧ��!", MB_OK|MB_ICONWARNING);
		return;
	}
	m_wdSel.SetText("F");
	m_wdFont = m_wdSel.GetFont();
	m_wdFont.SetSize(fSize);
	m_wdFont.SetName(szFontName);
	m_wdFont.SetColor(lFontColor);
	m_wdSel.SetFont(m_wdFont);
	OfficeWord11::Range r = m_wdSel.GetRange();
	r.SetHighlightColorIndex(lBackColor);
}

void CWordOffice::SetFont(BOOL bBold, BOOL bItalic /* = FALSE */, BOOL bUnderLine /* = FALSE */)
{
	if (!m_wdSel.m_lpDispatch) 
	{
		AfxMessageBox("SelectΪ�գ���������ʧ��!", MB_OK|MB_ICONWARNING);
		return;
	}
	m_wdSel.SetText("F");
	m_wdFont = m_wdSel.GetFont();
	m_wdFont.SetBold(bBold);
	m_wdFont.SetItalic(bItalic);
	m_wdFont.SetUnderline(bUnderLine);
	m_wdSel.SetFont(m_wdFont);
}

void CWordOffice::SetTableFont(int nRow, int nColumn, CString szFontName, float fSize, long lFontColor, long lBackColor)
{
	OfficeWord11::Cell c = m_wdTable.Cell(nRow, nColumn);
	c.Select();
	OfficeWord11::_Font ft = m_wdSel.GetFont();
	ft.SetName(szFontName);
	ft.SetSize(fSize);
	ft.SetColor(lFontColor);
	m_wdSel.SetFont(ft);
	OfficeWord11::Range r = m_wdSel.GetRange();
	r.SetHighlightColorIndex(lBackColor);
}
void CWordOffice::SetTableFont(int nRow, int nColumn, BOOL bBold, BOOL bItalic /* = FALSE */, BOOL bUnderLine /* = FALSE */)
{
	OfficeWord11::Cell c = m_wdTable.Cell(nRow, nColumn);
	c.Select();
	OfficeWord11::_Font ft = m_wdSel.GetFont();
	ft.SetBold(bBold);
	ft.SetItalic(bItalic);
	ft.SetUnderline(bUnderLine);
	m_wdSel.SetFont(ft);
}
void CWordOffice::SetParaphformat(int nAlignment)
{
	
	OfficeWord11::_ParagraphFormat p = m_wdSel.GetParagraphFormat();
	p.SetAlignment(nAlignment);
	m_wdSel.SetParagraphFormat(p);
	
}