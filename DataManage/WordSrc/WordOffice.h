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
    //����
    //**********************�������ĵ�*******************************************
    BOOL CreateApp();                    //����һ���µ�WORDӦ�ó���
    BOOL CreateDocuments();                //����һ���µ�Word�ĵ�����
    BOOL CreateDocument();                //����һ���µ�Word�ĵ�
    BOOL Create();                        //�����µ�WORDӦ�ó��򲢴���һ���µ��ĵ�
    void ShowApp();                        //��ʾWORD�ĵ�
    void HideApp();                        //����word�ĵ�

    //**********************���ĵ�*********************************************
    BOOL OpenDocument(CString fileName);//���Ѿ����ڵ��ĵ���
    BOOL Open(CString fileName);        //�����µ�WORDӦ�ó��򲢴�һ���Ѿ����ڵ��ĵ���
    BOOL SetActiveDocument(short i);    //���õ�ǰ������ĵ���

    //**********************�����ĵ�*********************************************
    BOOL SaveDocument();                //�ĵ����Դ���ʽ�����档
    BOOL SaveDocumentAs(CString fileName);//�ĵ��Դ�����ʽ�����档
    BOOL CloseDocument();
    void CloseApp(); 

    //**********************�ı���д����*****************************************
    void WriteText(CString szText);        //��ǰ��괦д�ı�
    void WriteNewLineText(CString szText, int nLineCount = 1); //��N��д��
    void WriteEndLine(CString szText);    //�ĵ���β��д�ı�
    void WholeStory();                    //ȫѡ�ĵ�����
    void Copy();                        //�����ı����ݵ�������
    void InsertFile(CString fileName);    //�����ص��ļ�ȫ������д�뵽��ǰ�ĵ��Ĺ�괦��
    
    //**********************ͼƬ�������*****************************************
    void InsertShapes(CString fileName);//�ڵ�ǰ����λ�ò���ͼƬ

	//**********************���������*****************************************
	void AddTable(const long ilIndex, const long inColumn);
	void AddMultiRowTable(const long ilIndex, const long inRow, const long inColumn);
	void SetTableColumnText(CString szText);
	//���õ�Ԫ����
	void SetTableCellWidth(const float inCellWidth, const long inRow, const long inColumn);
	//���õ�Ԫ������
	void SetTableCellText(CString szText, const long inRow, const long inColumn, const int inUnit);
	//��ֵ�Ԫ��
	void SplitTableCell(const long inRow, const long inColumn, const int inRowNum, const int inColNum);
	//�ϲ���Ԫ��
	void UnionTableCell(const long inBgnRow, const long inBgnColumn, const long inEndRow, const long inEndColumn);	
	void InsertTableNewRow();
    
    //**********************�����Ӳ������*****************************************
    void InsertHyperlink(CString fileLink);//�������ӵ�ַ�����������·����

	//===============================================================================

	//**********************������*******************************************
	void CreateTable(const long ilIndex, int nRow, int nColumn);
	void WriteCellText(int nRow, int nColumne, CString szText); //�������д��

	//*********************��������*******************************************
	void SetFont(CString szFontName, float fSize = 9, long lFontColor = 0, long lBackColor=0);
	void SetFont(BOOL bBold, BOOL bItalic = FALSE, BOOL bUnderLine = FALSE);
	void SetTableFont(int nRow, int nColumn, CString szFontName = "����", float fSize=9, long lFontColor=0, long lBackColor = 0);
	void SetTableFont(int nRow, int nColumn, BOOL bBold, BOOL bItalic = FALSE, BOOL bUnderLine = FALSE);
	//*********************��ʽ����*******************************************
	void SetParaphformat(int nAlignment);
	//����


};

#endif // !defined(AFX_WORDOFFICE_H__CD5D47A2_59D5_4A50_874A_98E0EE7DFEC3__INCLUDED_)
