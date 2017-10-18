// ExcelOptFun.h: interface for the CExcelOptFun class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXCELOPTFUN_H__C046652B_FC50_48FE_8ED5_7C32FA982C3A__INCLUDED_)
#define AFX_EXCELOPTFUN_H__C046652B_FC50_48FE_8ED5_7C32FA982C3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "excel.h"
#include "comdef.h" 
#include "PubStruct.h"

using namespace OfficeExcel11;



//const char HEAD_CHAR='D';



class CExcelOptFun  
{
public:
	CExcelOptFun();
	virtual ~CExcelOptFun();

public:
	int		m_IsNew;

	int		m_row;
	int		m_col;
	char ***m_ItemInfo;					//1.������Ϣ	
	int   **m_ItemFlag;					//2.���ݱ�־	[XLS_MAX_ROW][XLS_MAX_COL]
	int    *m_ColLen;					//3.�г���		[XLS_MAX_COL]
	int     m_nSumColLen;               //���г�
	
public: //
	int			m_nTabCellCnt;							
	StTabCell  *m_stTabCell;			//4.�ϲ���Ԫ��	[XLS_CELL_CNT]
	
	int			m_nTabRowSrtCnt;		//��Ч�и���
	StTabRow   *m_stTabRow;				//5.�в�������	[XLS_MAX_ROW]
	
	int			m_nTabColSrtCnt;		//��Ч�и���
	StTabCol   *m_stTabCol;				//6.�в�������	[XLS_MAX_COL]


public:
	int  NewItemInfo( );
	int  DeleteItemInfo( );
	int  ClearParamInfo( int IsInit = 1 );

//-----------------------excel opt begin--------------------------------------
	
	int ReadExcelFile(CString fileName);
	int WriteExcelFile(CString fileName);
	int WriteListToExcel(CListCtrl *pList, CString fileName, int IsHaveTail = 0);
	int SetCellBorder(Range *pRange);	
	int AppendExcelFile(CString fileName, int begRow, int endRow, int begCol, int endCol, int sheetNum=1, int bStyleCenter=1);
//----------------------------------------------------------------------------
	
	int  ReadExcelFile_ContexMode(CString fileName);
	int  ReadExcelFile_ContexMode2(CString fileName);
	int  WriteExcelFile_ContexMode(CString fileName);
	int  CheckAndAddTableCell(int nStarRow, int nStarColumn, int nRow, int nCol);

	void CalculateTabCellSize( );					//��ȡ���ݳ���
	int  CheckTabCellOk( );							//���ϲ���Ԫ���Ƿ���ȷ
	void ResetItemFlag( );
	int  GetTabCellType(char *szDataName);			//��ȡ��Ԫ����������

/*	
	int  GetTabDataList( );							//��ȡ�����б�		
	int  GetTabDataRowAndColNameFlag( );			//��ȡ�����ƺ������Ʊ�־
*/
	//int WriteCellTypesGridCtrlToExcel(CCellTypesGridCtrl *pGridCtrl, CString fileName);

/*
	//�����б���ʾ���
	//==============================================================================
	void ListCtrl_ClearAllColumn(CListCtrl *pList);

	void DisplayTabHeadLen(CListCtrl *pList);		//��ʾ���ģ��_��ͷ�п��
	void DisplayTabItemData(CListCtrl *pList);		//��ʾ���ģ��_��Ԫ������
	void DisplayTabItemFlag(CListCtrl *pList);		//��ʾ���ģ��_��Ԫ���־
	void DisplayTabCellSrt(CListCtrl *pList);		//��ʾ���ģ��_�ϲ���Ԫ��ṹ
	void DisplayTabOutDataSrt(CListCtrl *pList);	//��ʾ���ģ��_������ݽṹ
	void DisplayTabRowSrt(CListCtrl *pList);		//��ʾ���ģ��_������������Ϣ
    void DisplayTabColSrt(CListCtrl *pList);		//��ʾ���ģ��_������������Ϣ
*/

	//lty Add 2017-2-7
	int WriteDataToExcel(CModeParMng *pPar,CListCtrl *pDecList,CListCtrl *pAttachList,
		CString fileName, int IsHaveTail = 0); 

};

#endif // !defined(AFX_EXCELOPTFUN_H__C046652B_FC50_48FE_8ED5_7C32FA982C3A__INCLUDED_)
