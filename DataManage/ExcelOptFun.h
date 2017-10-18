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
	char ***m_ItemInfo;					//1.数据信息	
	int   **m_ItemFlag;					//2.数据标志	[XLS_MAX_ROW][XLS_MAX_COL]
	int    *m_ColLen;					//3.列长度		[XLS_MAX_COL]
	int     m_nSumColLen;               //总列长
	
public: //
	int			m_nTabCellCnt;							
	StTabCell  *m_stTabCell;			//4.合并单元格	[XLS_CELL_CNT]
	
	int			m_nTabRowSrtCnt;		//有效行个数
	StTabRow   *m_stTabRow;				//5.行参数设置	[XLS_MAX_ROW]
	
	int			m_nTabColSrtCnt;		//有效列个数
	StTabCol   *m_stTabCol;				//6.列参数设置	[XLS_MAX_COL]


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

	void CalculateTabCellSize( );					//获取数据长度
	int  CheckTabCellOk( );							//检测合并单元格是否正确
	void ResetItemFlag( );
	int  GetTabCellType(char *szDataName);			//获取单元格数据类型

/*	
	int  GetTabDataList( );							//获取数据列表		
	int  GetTabDataRowAndColNameFlag( );			//获取行名称和列名称标志
*/
	//int WriteCellTypesGridCtrlToExcel(CCellTypesGridCtrl *pGridCtrl, CString fileName);

/*
	//数据列表显示相关
	//==============================================================================
	void ListCtrl_ClearAllColumn(CListCtrl *pList);

	void DisplayTabHeadLen(CListCtrl *pList);		//显示表格模板_表头列宽度
	void DisplayTabItemData(CListCtrl *pList);		//显示表格模板_单元格数据
	void DisplayTabItemFlag(CListCtrl *pList);		//显示表格模板_单元格标志
	void DisplayTabCellSrt(CListCtrl *pList);		//显示表格模板_合并单元格结构
	void DisplayTabOutDataSrt(CListCtrl *pList);	//显示表格模板_输出数据结构
	void DisplayTabRowSrt(CListCtrl *pList);		//显示表格模板_列名称配置信息
    void DisplayTabColSrt(CListCtrl *pList);		//显示表格模板_行名称配置信息
*/

	//lty Add 2017-2-7
	int WriteDataToExcel(CModeParMng *pPar,CListCtrl *pDecList,CListCtrl *pAttachList,
		CString fileName, int IsHaveTail = 0); 

};

#endif // !defined(AFX_EXCELOPTFUN_H__C046652B_FC50_48FE_8ED5_7C32FA982C3A__INCLUDED_)
