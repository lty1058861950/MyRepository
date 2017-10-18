// WordOffice.h: interface for the CWordOffice class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORDOFFICE_H__CD5D47A2_59D5_4A50_874A_98E0EE7DFEC3__INCLUDED_)
#define AFX_WORDOFFICE_H__CD5D47A2_59D5_4A50_874A_98E0EE7DFEC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "msword.h"

#include "atlbase.h"
#include "msword.h"
#include "comdef.h"
#include <afxdisp.h> //COlVirant

//using namespace OfficeWord11;

class CWordOffice  
{
public:
	CWordOffice();
	virtual ~CWordOffice();

private:
 public:   
	OfficeWord11:: _Application m_wdApp;
    OfficeWord11:: Documents m_wdDocs;
    OfficeWord11:: _Document m_wdDoc;

    OfficeWord11:: Selection m_wdSel;
    OfficeWord11:: Range     m_wdRange;
    OfficeWord11:: InlineShapes m_wdInlineShapes; 
    OfficeWord11:: InlineShape m_wdInlineShape;
	OfficeWord11:: Tables		m_wdTables;
	OfficeWord11:: Table		m_wdTable;
	OfficeWord11:: Cell  m_wdCell;
	OfficeWord11:: Range m_tbRange;
	OfficeWord11:: Columns m_wdColumns;
	OfficeWord11:: Column  m_wdColumn;
	OfficeWord11:: _Font m_wdFont;

public:
    //操作
    //**********************创建新文档*******************************************
    BOOL CreateApp();                    //创建一个新的WORD应用程序
    BOOL CreateDocuments();                //创建一个新的Word文档集合
    BOOL CreateDocument();                //创建一个新的Word文档
    BOOL Create();                        //创建新的WORD应用程序并创建一个新的文档
    void ShowApp();                        //显示WORD文档
    void HideApp();                        //隐藏word文档

    //**********************打开文档*********************************************
    BOOL OpenDocument(CString fileName);//打开已经存在的文档。
    BOOL Open(CString fileName);        //创建新的WORD应用程序并打开一个已经存在的文档。
    BOOL SetActiveDocument(short i);    //设置当前激活的文档。

    //**********************保存文档*********************************************
    BOOL SaveDocument();                //文档是以打开形式，保存。
    BOOL SaveDocumentAs(CString fileName);//文档以创建形式，保存。
    BOOL CloseDocument();
    void CloseApp(); 

    //**********************文本书写操作*****************************************
    void WriteText(CString szText);        //当前光标处写文本
    void WriteNewLineText(CString szText, int nLineCount = 1); //换N行写字
    void WriteEndLine(CString szText);    //文档结尾处写文本
    void WholeStory();                    //全选文档内容
    void Copy();                        //复制文本内容到剪贴板
    void InsertFile(CString fileName);    //将本地的文件全部内容写入到当前文档的光标处。
    
    //**********************图片插入操作*****************************************
    void InsertShapes(CString fileName);//在当前光标的位置插入图片

	//**********************插入表格操作*****************************************
	void AddTable(const long ilIndex, const long inColumn);
	void AddMultiRowTable(const long ilIndex, const long inRow, const long inColumn);
	void SetTableColumnText(CString szText);
	//设置单元格宽度
	void SetTableCellWidth(const float inCellWidth, const long inRow, const long inColumn);
	//设置单元格内容
	void SetTableCellText(CString szText, const long inRow, const long inColumn, const int inUnit);
	//拆分单元格
	void SplitTableCell(const long inRow, const long inColumn, const int inRowNum, const int inColNum);
	//合并单元格
	void UnionTableCell(const long inBgnRow, const long inBgnColumn, const long inEndRow, const long inEndColumn);	
	void InsertTableNewRow();
    
    //**********************超链接插入操作*****************************************
    void InsertHyperlink(CString fileLink);//超级链接地址，可以是相对路径。

	//===============================================================================

	//**********************表格操作*******************************************
	void CreateTable(const long ilIndex, int nRow, int nColumn);
	void WriteCellText(int nRow, int nColumne, CString szText); //往表格中写字

	//*********************字体设置*******************************************
	void SetFont(CString szFontName, float fSize = 9, long lFontColor = 0, long lBackColor=0);
	void SetFont(BOOL bBold, BOOL bItalic = FALSE, BOOL bUnderLine = FALSE);
	void SetTableFont(int nRow, int nColumn, CString szFontName = "宋体", float fSize=9, long lFontColor=0, long lBackColor = 0);
	void SetTableFont(int nRow, int nColumn, BOOL bBold, BOOL bItalic = FALSE, BOOL bUnderLine = FALSE);
	//*********************格式设置*******************************************
	void SetParaphformat(int nAlignment);
	//方法


};

#endif // !defined(AFX_WORDOFFICE_H__CD5D47A2_59D5_4A50_874A_98E0EE7DFEC3__INCLUDED_)
