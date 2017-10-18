// ExcelOptFun.cpp: implementation of the CExcelOptFun class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ExcelOptFun.h"
#include "math.h"
#include "ModeParMng.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CExcelOptFun::CExcelOptFun()
{
	m_IsNew = 0;
}

CExcelOptFun::~CExcelOptFun()
{

}


int CExcelOptFun::NewItemInfo( )
{
	int			i,j;
	CString		str;
	
	m_IsNew = 1;
	
	//Excel�������----------------------------------------------
	
	//1.������Ϣ	[XLS_MAX_ROW][XLS_MAX_COL][XLS_MAX_LEN]
	//----------------------------------------------------------------
	m_ItemInfo = new char** [XLS_MAX_ROW];
	for (i=0; i<XLS_MAX_ROW; i++)
	{
		m_ItemInfo[i] = new char* [XLS_MAX_COL];
		for (j=0; j<XLS_MAX_COL; j++)
		{
			m_ItemInfo[i][j] = new char[XLS_MAX_LEN];
		}
	}
	
	//2.���ݱ�־	[XLS_MAX_ROW][XLS_MAX_COL]
	//----------------------------------------------------------------
	m_ItemFlag = new int* [XLS_MAX_ROW];
	for (i=0; i<XLS_MAX_ROW; i++)
	{
		m_ItemFlag[i] = new int[XLS_MAX_COL];
	}
	
	//3.�г���		[XLS_MAX_COL]
	//----------------------------------------------------------------
	m_ColLen = new int[XLS_MAX_COL];			
    m_nSumColLen = 0;               //���г�
	
	
	//4.�ϲ���Ԫ��	[TAB_MAX_CELL_CNT]
	//----------------------------------------------------------------
	m_nTabCellCnt = 0;
	m_stTabCell = new StTabCell[TAB_MAX_CELL_CNT];
	
	
	//5.�в�������	[XLS_MAX_ROW]
	//----------------------------------------------------------------
	m_nTabRowSrtCnt = 0;		//��Ч�и���
	m_stTabRow = new StTabRow[XLS_MAX_ROW];	
	
	//6.�в�������		
	//----------------------------------------------------------------
	m_nTabColSrtCnt = 0;		//��Ч�и���
	m_stTabCol = new StTabCol[XLS_MAX_COL];			

	return 1;
}

int CExcelOptFun::DeleteItemInfo( )
{
	int i,j;
	
	if (m_IsNew == 0)
	{
		return 0;
	}
	else
	{
		m_IsNew = 0;
	}
	
	
	//Excel�������----------------------------------------------

	//1.������Ϣ	[XLS_MAX_ROW][XLS_MAX_COL][XLS_MAX_LEN]
	//----------------------------------------------------------------
	m_row = 0;
	m_col = 0;
	for (i=0; i<XLS_MAX_ROW; i++)
	{
		for (j=0; j<XLS_MAX_COL; j++)
		{
			if (m_ItemInfo[i][j] != NULL)
			{
				delete[] m_ItemInfo[i][j];
				m_ItemInfo[i][j] = NULL;
			}
		}	
		if (m_ItemInfo[i] != NULL)
		{
			delete[] m_ItemInfo[i];
			m_ItemInfo[i] = NULL;
		}
	}
	
	if (m_ItemInfo != NULL)
	{
		delete[] m_ItemInfo;
		m_ItemInfo = NULL;
	}
	
	//2.���ݱ�־	[XLS_MAX_ROW][XLS_MAX_COL]
	//----------------------------------------------------------------
	for (i=0; i<XLS_MAX_ROW; i++)
	{
		if (m_ItemFlag[i] != NULL)
		{
			delete[] m_ItemFlag[i];
			m_ItemFlag[i] = NULL;
		}
	}
	
	if (m_ItemFlag != NULL)
	{
		delete[] m_ItemFlag;
		m_ItemFlag = NULL;
	}
	
	//3.�г���		[XLS_MAX_COL]
	//----------------------------------------------------------------				
    m_nSumColLen = 0;               //���г�
	if (m_ColLen != NULL)
	{
		delete[] m_ColLen;
		m_ColLen = NULL;
	}
	
	//4.�ϲ���Ԫ��	[TAB_MAX_CELL_CNT]
	//----------------------------------------------------------------
	m_nTabCellCnt = 0;
	if (m_stTabCell != NULL)
	{
		delete[] m_stTabCell;
		m_stTabCell = NULL;
	}
	
	
	//5.�в�������	[XLS_MAX_ROW]
	//----------------------------------------------------------------
	m_nTabRowSrtCnt = 0;		//��Ч�и���
	if (m_stTabRow != NULL)
	{
		delete[] m_stTabRow;
		m_stTabRow = NULL;
	}
	
	//6.�в�������		
	//----------------------------------------------------------------
	m_nTabColSrtCnt = 0;		//��Ч�и���
	if (m_stTabCol != NULL)
	{
		delete[] m_stTabCol;
		m_stTabCol = NULL;
	}			

	return 1;
}


int CExcelOptFun::ClearParamInfo( int IsInit )
{
	int i, j;

	//1.������Ϣ	[XLS_MAX_ROW][XLS_MAX_COL][XLS_MAX_LEN]
	//2.���ݱ�־	[XLS_MAX_ROW][XLS_MAX_COL]
	//----------------------------------------------------------------
	m_row = 0;
	m_col = 0;
	
	for (i=0; i<XLS_MAX_ROW; i++)
	{
		for (j=0; j<XLS_MAX_COL; j++)
		{
			memset( (char*)m_ItemInfo[i][j], 0, sizeof(char)*XLS_MAX_LEN);
			m_ItemFlag[i][j] = 0;
		}
	}
	
	//3.�г���		[XLS_MAX_COL]
	//----------------------------------------------------------------	
	m_nSumColLen = 0;                       //���г�
	for (i=0; i<XLS_MAX_COL; i++)
	{
		m_ColLen[i] = 0;					//Excel�г���
	}
	
	//4.�ϲ���Ԫ��	[TAB_MAX_CELL_CNT]
	//----------------------------------------------------------------
	m_nTabCellCnt = 0;						//�ϲ���Ԫ����Ϣ
	for (i=0; i<TAB_MAX_CELL_CNT; i++)
	{
		memset( (char*)(&m_stTabCell[i]), 0, sizeof(StTabCell) );	
	}
	
	//5.�в�������	[XLS_MAX_ROW]
	//----------------------------------------------------------------
	m_nTabRowSrtCnt = 0;						//��Ч�и���
	for (i=0; i<XLS_MAX_ROW; i++)
	{
		memset( (char*)(&m_stTabRow[i]), 0, sizeof(StTabRow));
	}
	
	//6.�в�������		
	//----------------------------------------------------------------
	m_nTabColSrtCnt = 0;						//��Ч�и���
	for (i=0; i<XLS_MAX_COL; i++)
	{
		memset( (char*)(&m_stTabCol[i]), 0, sizeof(StTabCol));
	}


	return 1;
}

//=================================================================================

int CExcelOptFun::ReadExcelFile_ContexMode(CString fileName)
{
	int			percent=0;
	char        ItemVal[XLS_MAX_COL][100] = {0,};
	int         bFlag = 1;

	//����app��ȫ�ֻ��Ա���� 	
	_Application app;
	Workbooks	books;   
	_Workbook	book;   
	Worksheets  sheets;   
	_Worksheet  sheet;   
	LPDISPATCH  lpDisp;   
	Range		range;   
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR); 
	Range		usedRange; 
	COleVariant vResult;

	int			i,j,k;
	int			sheetCnt;
	CString		str,str1, strFileName;
	long		iRowNum, iColNum, iStartRow, iStartCol;
	//char        *pValue;

	int         xlsCnt = 0;
	int         oldDevOrd= 0;
	CTime       t = CTime::GetCurrentTime();
	CString     strTime;
	double      fVal = 0;
	int         nVal = 0;
	double      floatPI = 0.0000001;

	int		nWidth = 0;
	double	fHeight = 0;
	CString strTemp;
	VARIANT vTemp;
	int    nSumColLen;
	int    pos;


	strTime.Format("%04d-%02d-%02d %02d:%02d:%02d", 
		t.GetYear(), t.GetMonth(),  t.GetDay(),
		t.GetHour(), t.GetMinute(), t.GetSecond());


	//-------------------------------------------------------------------

	//fileName = pDlg->m_strFileName;

	//2.����Excel ������(����Excel)
	if (!app.CreateDispatch("Excel.Application"))   
	{   
		AfxMessageBox("�޷�����Excel������");   
		return FALSE;   
	}  

	//3.����Excel��״̬
	app.SetVisible(FALSE);		// ʹExcel�ɼ�   
	app.SetUserControl(TRUE);	// ���������û�����Excel 


	//4.�����е�Excel�ļ�
	books.AttachDispatch(app.GetWorkbooks());   

	lpDisp = books.Open(fileName, covOptional, covOptional,  covOptional,   covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional,   
		covOptional, covOptional, covOptional, covOptional);  


	//�õ�Workbook 
	book.AttachDispatch(lpDisp);

	// �õ�Worksheets
	sheets = book.GetSheets(); 

	sheetCnt = sheets.GetCount();  //��ù���������	//sheets.length;


	nSumColLen = 0;
	
	bFlag = 1;

	if (sheetCnt < 2)
	{
		str.Format("Read Excel Sheet Count Small Error, SheetCnt=%d", sheetCnt); 	
		AfxMessageBox(str);
		bFlag = 0;
	}

	//ѭ�����б� 
	//for (i=1; i<=sheetCnt; i++)	
	for (i=1; i<=2; i++)	
	{ 
		if (bFlag == 0)
		{
			break;
		}

		//��ȡ��i�������� 
		sheet=sheets.GetItem(COleVariant((short)i)); 

		//sheet.Name//��i��������ı���  ������Ҫ�ı��� �Լ�д���ַ��������ṹ�������� 
		strFileName = sheet.GetName();

		usedRange.AttachDispatch(sheet.GetUsedRange()); 

		range.AttachDispatch(usedRange.GetRows()); 

		iRowNum = range.GetCount(); //�Ѿ�ʹ�õ����� 

		range.AttachDispatch(usedRange.GetColumns()); 

		iColNum = range.GetCount(); //�Ѿ�ʹ�õ����� 

		iStartRow=usedRange.GetRow(); //��ʹ���������ʼ�У���1��ʼ 

		iStartCol=usedRange.GetColumn(); //��ʹ���������ʼ�У���1��ʼ 

		str.Format("%d, %d", iRowNum, iColNum);
		//AfxMessageBox(str);

		if ( (iRowNum > XLS_MAX_ROW) || (iColNum > XLS_MAX_COL) )  
		{
			str.Format("Excel Row=%d or Col=%d Num is Out of Range, RowMax=%d, ColMax=%d", 
				iRowNum, iColNum, XLS_MAX_ROW, XLS_MAX_COL);
			AfxMessageBox(str);
			bFlag = 0;
			break;
		}


		if (i == 2)
		{
			if (iColNum != 4)
			{
				str.Format("Excel Sheet2 iColNum Value 4, iColNum=%d", iColNum);
				AfxMessageBox(str);
				bFlag = 0;
				break;
			}
			if (iColNum > TAB_MAX_CELL_CNT)
			{
				str.Format("Excel ColNum=%d Out of Range, Max=%d!", iColNum-1, TAB_MAX_CELL_CNT);		
				AfxMessageBox(str);
				bFlag = 0;
				break;
			}
			else
			{
				m_nTabCellCnt = iRowNum - 1;
			}
		}

		if (i == 1)		//Sheet1ҳ
		{
			m_row = iRowNum;
			m_col = iColNum;
		}

		//memset((char*)m_ItemInfo, 0, XLS_MAX_ROW*XLS_MAX_COL*XLS_MAX_LEN);


		for (j=1; j<=iRowNum; j++)		//��
		{
			memset(ItemVal, 0, 20*200);
			for (k=1; k<=iColNum; k++)	//��
			{

				//��ȡ��һ����Ԫ���ֵ 
				range.AttachDispatch(sheet.GetCells()); 

				range.AttachDispatch(range.GetItem (COleVariant((long)j),COleVariant((long)k)).pdispVal ); 

				vResult =range.GetValue2(); 

				if ((j == 1) && (i == 1))  //Sheet1ҳ
				{
					vTemp = range.GetWidth();
					nWidth = (int) (vTemp.dblVal); //(int) (vTemp.dblVal / 6); 
					vTemp = range.GetHeight();
					fHeight = vTemp.dblVal; 

					m_ColLen[k-1] = nWidth;				//��¼�п�
					nSumColLen = nSumColLen + nWidth;	//��¼���п�
				}

				str = "";

				if(vResult.vt == VT_BSTR) //�ַ��� 
				{ 
					str=vResult.bstrVal; 
				} 
				else if (vResult.vt==VT_R8) //8�ֽڵ����� 
				{ 
					fVal = vResult.dblVal;
					nVal = (int) vResult.dblVal;

					if ( fabs(fVal-nVal) > floatPI)
					{
						str.Format("%5.3f",vResult.dblVal);
					}
					else
					{
						str.Format("%d",(int)vResult.dblVal);
					}
				} 
				else if(vResult.vt==VT_DATE) //ʱ���ʽ 
				{ 
					//SYSTEMTIME st; 
					//VariantTimeToSystemTime(&vResult.date, &st); 
				} 
				else if(vResult.vt==VT_EMPTY) //��Ԫ��յ� 
				{ 
					str=""; 
				} 

				str.TrimLeft();
				str.TrimRight();

				strcpy(ItemVal[k-1], str.GetBuffer(0));	

				if (i == 1)		//Sheet1ҳ
				{
					strcpy(m_ItemInfo[j-1][k-1], str.GetBuffer(0));

					m_ItemFlag[j-1][k-1] = GetTabCellType(str.GetBuffer(0));	//��¼����״̬
				}
				else if (i==2)   //Sheet2ҳ
				{
					if (j != 1)
					{
						pos = j-2;
						if (k == 1)
						{
							m_stTabCell[pos].iBegRow = atoi(str.GetBuffer(0));
						}
						else if (k == 2)
						{
							m_stTabCell[pos].iBegCol = atoi(str.GetBuffer(0));
						}
						else if (k == 3)
						{							
							m_stTabCell[pos].iEndRow = atoi(str.GetBuffer(0));	
						}
						else if (k == 4)
						{	
							m_stTabCell[pos].iEndCol = atoi(str.GetBuffer(0));	
						}
					}
				}
			

				//AfxMessageBox(str);

			}	//end for (k=1; k<iColNum; k++)	//��		

		}	//end for (j=1; j<iRowNum; j++)		//��

	}	//end for (i=1; i<=sheetCnt; i++)  		//ѭ�����б� 

	CalculateTabCellSize( );

	usedRange.ReleaseDispatch();

	range.ReleaseDispatch();
	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();
	book.ReleaseDispatch();
	books.ReleaseDispatch();

	app.Quit();
	app.ReleaseDispatch();

	return bFlag;
}

//--------------------------------------------------------------------------------------
int CExcelOptFun::ReadExcelFile_ContexMode2(CString fileName)
{
	int			percent=0;
	char        ItemVal[XLS_MAX_COL][100] = {0,};
	int         bFlag = 1;

	//����app��ȫ�ֻ��Ա���� 	
	_Application app;
	Workbooks	books;   
	_Workbook	book;   
	Worksheets  sheets;   
	_Worksheet  sheet;   
	LPDISPATCH  lpDisp;   
	Range		range;   
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR); 
	Range		usedRange; 
	COleVariant vResult;

	int			i,j,k;
	int			sheetCnt;
	CString		str,str1, strFileName;
	long		iRowNum, iColNum, iStartRow, iStartCol;
	//char        *pValue;

	int         xlsCnt = 0;
	int         oldDevOrd= 0;
	CTime       t = CTime::GetCurrentTime();
	CString     strTime;
	double      fVal = 0;
	int         nVal = 0;
	double      floatPI = 0.0000001;

	int		nWidth = 0;
	double	fHeight = 0;
	CString strTemp;
	VARIANT vTemp;
	int    nSumColLen;
	//int    pos;


	strTime.Format("%04d-%02d-%02d %02d:%02d:%02d", 
		t.GetYear(), t.GetMonth(),  t.GetDay(),
		t.GetHour(), t.GetMinute(), t.GetSecond());


	//-------------------------------------------------------------------

	//fileName = pDlg->m_strFileName;

	//2.����Excel ������(����Excel)
	if (!app.CreateDispatch("Excel.Application"))   
	{   
		AfxMessageBox("�޷�����Excel������");   
		return FALSE;   
	}  

	//3.����Excel��״̬
	app.SetVisible(FALSE);		// ʹExcel�ɼ�   
	app.SetUserControl(TRUE);	// ���������û�����Excel 


	//4.�����е�Excel�ļ�
	books.AttachDispatch(app.GetWorkbooks());   

	lpDisp = books.Open(fileName, covOptional, covOptional,  covOptional,   covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional,   
		covOptional, covOptional, covOptional, covOptional);  


	//�õ�Workbook 
	book.AttachDispatch(lpDisp);

	// �õ�Worksheets
	sheets = book.GetSheets(); 

	sheetCnt = sheets.GetCount();  //��ù���������	//sheets.length;


	nSumColLen = 0;

	bFlag = 1;

	if (sheetCnt < 1)
	{
		str.Format("Read Excel Sheet Count Small Error, SheetCnt=%d", sheetCnt); 	
		AfxMessageBox(str);
		bFlag = 0;
	}

	m_nTabCellCnt = 0;

	//ѭ�����б� 
	//for (i=1; i<=sheetCnt; i++)	
	for (i=1; i<=1; i++)	
	{ 
		if (bFlag == 0)
		{
			break;
		}

		//��ȡ��i�������� 
		sheet=sheets.GetItem(COleVariant((short)i)); 

		//sheet.Name//��i��������ı���  ������Ҫ�ı��� �Լ�д���ַ��������ṹ�������� 
		strFileName = sheet.GetName();

		usedRange.AttachDispatch(sheet.GetUsedRange()); 

		range.AttachDispatch(usedRange.GetRows()); 

		iRowNum = range.GetCount(); //�Ѿ�ʹ�õ����� 

		range.AttachDispatch(usedRange.GetColumns()); 

		iColNum = range.GetCount(); //�Ѿ�ʹ�õ����� 

		iStartRow=usedRange.GetRow(); //��ʹ���������ʼ�У���1��ʼ 

		iStartCol=usedRange.GetColumn(); //��ʹ���������ʼ�У���1��ʼ 

		str.Format("%d, %d", iRowNum, iColNum);
		//AfxMessageBox(str);

		if ( (iRowNum > XLS_MAX_ROW) || (iColNum > XLS_MAX_COL) )  
		{
			str.Format("Excel Row=%d or Col=%d Num is Out of Range, RowMax=%d, ColMax=%d", 
				iRowNum, iColNum, XLS_MAX_ROW, XLS_MAX_COL);
			AfxMessageBox(str);
			bFlag = 0;
			break;
		}


		if (i == 1)		//Sheet1ҳ
		{
			m_row = iRowNum;
			m_col = iColNum;
		}

		//memset((char*)m_ItemInfo, 0, XLS_MAX_ROW*XLS_MAX_COL*XLS_MAX_LEN);


		for (j=1; j<=iRowNum; j++)		//��
		{
			memset(ItemVal, 0, 20*200);
			for (k=1; k<=iColNum; k++)	//��
			{

				//��ȡ��һ����Ԫ���ֵ 
				range.AttachDispatch(sheet.GetCells()); 

				range.AttachDispatch(range.GetItem (COleVariant((long)j),COleVariant((long)k)).pdispVal ); 

				vResult =range.GetValue2(); 

				if ((j == 1) && (i == 1))  //Sheet1ҳ
				{
					vTemp = range.GetWidth();
					nWidth = (int) (vTemp.dblVal); //(int) (vTemp.dblVal / 6); 
					vTemp = range.GetHeight();
					fHeight = vTemp.dblVal; 

					m_ColLen[k-1] = nWidth;				//��¼�п�
					nSumColLen = nSumColLen + nWidth;	//��¼���п�
				}

				str = "";

				if(vResult.vt == VT_BSTR) //�ַ��� 
				{ 
					str=vResult.bstrVal; 
				} 
				else if (vResult.vt==VT_R8) //8�ֽڵ����� 
				{ 
					fVal = vResult.dblVal;
					nVal = (int) vResult.dblVal;

					if ( fabs(fVal-nVal) > floatPI)
					{
						str.Format("%5.3f",vResult.dblVal);
					}
					else
					{
						str.Format("%d",(int)vResult.dblVal);
					}
				} 
				else if(vResult.vt==VT_DATE) //ʱ���ʽ 
				{ 
					//SYSTEMTIME st; 
					//VariantTimeToSystemTime(&vResult.date, &st); 
				} 
				else if(vResult.vt==VT_EMPTY) //��Ԫ��յ� 
				{ 
					str=""; 
				} 

				str.TrimLeft();
				str.TrimRight();

				strcpy(ItemVal[k-1], str.GetBuffer(0));	

				//---------------------------------------------------------
				VARIANT var;
				var= range.GetMergeCells();
				if (var.boolVal == -1)
				{
					//�Ǻϲ���Ԫ��
					Range rangeMerge;
					rangeMerge.AttachDispatch( range.GetMergeArea(), TRUE);

					//�ϲ�����
					rangeMerge.AttachDispatch( rangeMerge.GetRows(), TRUE);
					int nRow = rangeMerge.GetCount();

					//�ϲ�����
					rangeMerge.AttachDispatch( rangeMerge.GetColumns(), TRUE);
					int nCol = rangeMerge.GetCount();

					int nStarRow = rangeMerge.GetRow();
					int nStarColumn = rangeMerge.GetColumn();

					CheckAndAddTableCell(nStarRow, nStarColumn, nRow, nCol);
				}



				if (i == 1)		//Sheet1ҳ
				{
					strcpy(m_ItemInfo[j-1][k-1], str.GetBuffer(0));

					m_ItemFlag[j-1][k-1] = GetTabCellType(str.GetBuffer(0));	//��¼����״̬
				}
			

			}	//end for (k=1; k<iColNum; k++)	//��		

		}	//end for (j=1; j<iRowNum; j++)		//��

	}	//end for (i=1; i<=sheetCnt; i++)  		//ѭ�����б� 

	CalculateTabCellSize( );

	usedRange.ReleaseDispatch();

	range.ReleaseDispatch();
	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();
	book.ReleaseDispatch();
	books.ReleaseDispatch();

	app.Quit();
	app.ReleaseDispatch();

	return bFlag;
}


int CExcelOptFun::CheckAndAddTableCell(int nStarRow, int nStarColumn, int nRow, int nCol)
{
	int			i, pos;
	StTabCell	*pStTabCell = NULL;
	int         bExit= 0;

	if (m_nTabCellCnt == 0)
	{
		pos = 0;

		pStTabCell = &m_stTabCell[pos];

		pStTabCell->iBegRow = nStarRow;
	
		pStTabCell->iBegCol = nStarColumn;
			
		pStTabCell->iEndRow = nStarRow + nRow - 1;	

		pStTabCell->iEndCol = nStarColumn + nCol -1;	

		m_nTabCellCnt ++;
	}
	else 
	{
		bExit = 0;
		for (i=0; i<m_nTabCellCnt; i++)
		{
			pStTabCell = &m_stTabCell[i];
			if (   (pStTabCell->iBegRow == nStarRow)
				&& (pStTabCell->iBegCol == nStarColumn)
				)
			{
				bExit = 1;
				break;
			}
		}

		if (bExit == 0)
		{
			pos = m_nTabCellCnt;

			pStTabCell = &m_stTabCell[pos];

			pStTabCell->iBegRow = nStarRow;

			pStTabCell->iBegCol = nStarColumn;

			pStTabCell->iEndRow = nStarRow + nRow - 1;	

			pStTabCell->iEndCol = nStarColumn + nCol -1;	

			m_nTabCellCnt ++;
		}
	}


	return !bExit;
}

//--------------------------------------------------------------------------------------

int CExcelOptFun::WriteExcelFile_ContexMode(CString fileName)
{
	{
		//����app��ȫ�ֻ��Ա���� 	
		_Application app;

		//�������
		Workbooks	books;   
		_Workbook	book;   
		Worksheets  sheets;   
		_Worksheet  sheet;   
		//LPDISPATCH  lpDisp;   
		Range		range;   
		COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR); 

		int			i, j, row, col, pos, cnt;
		CString     str, strName, strCell, strBeg, strEnd;
		char        nameArray[20][30] = {0,};


		int tick;


		tick = GetTickCount();


		if (!app.CreateDispatch("Excel.Application"))   
		{   
			AfxMessageBox("�޷�����Excel������");   
			return FALSE;   
		}  

		//�½�һ��.xls�ļ�����д������
		//COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

		// Get the Workbooks collection so that you can add a new workbook
		books.AttachDispatch(app.GetWorkbooks());  // �õ�Workbooks
		book = books.Add(covOptional);     // �õ�Workbook


		// Get the Worksheets collection so that you can get the IDispatch for the first Worksheet
		sheets = book.GetWorksheets();     // �õ�Worksheets


		//sheets.Delete();

		CString vtMissing = "MySheetNew";

		//sheets.Add(vtMissing,_variant_t(sheet),_variant_t((short)1),COleVariant((short)1)); 

		sheet = sheets.GetItem(COleVariant((short)1)); // �õ�Worksheet

		cnt = 1; 

		pos = 0;
		for (i=0; i<m_row; i++)
		{
			for (j=0; j<m_col; j++)
			{
				row = i+1;
				col = j+1;
				strName = m_ItemInfo[i][j];

				strCell.Format("%c%d", 'A'+col-1, row);
				range  = sheet.GetRange(COleVariant(strCell.GetBuffer(0)), covOptional);  // ��ȡA1 Range
				range.SetValue2( COleVariant(strName.GetBuffer(0)));                               // �������
				range.SetHorizontalAlignment(COleVariant((long)-4108));// ˮƽ���ж��� 
				//SetCellBorder(&range);	

				if (i==0)
				{
					range.SetColumnWidth( COleVariant((long)m_ColLen[j]/6) );
				}
			}

			str.Format("%d / %d , Percent=%d%%", pos, 15*cnt, pos*100 / (15*cnt) );
			//GetDlgItem(IDC_STATIC_INF)->SetWindowText(str);
		}

		CString		strlt, strrd;
		Range		rgMyRge;
		StTabCell	*pStTabCell = NULL;
	

		for (i=0; i<m_nTabCellCnt; i++)
		{
			pStTabCell = &m_stTabCell[i];
				
			//strlt = "A1";
			//strrd = "C4";

			strlt.Format("%c%d", 'A'+pStTabCell->iBegCol-1, pStTabCell->iBegRow);
			strrd.Format("%c%d", 'A'+pStTabCell->iEndCol-1, pStTabCell->iEndRow);

			rgMyRge.AttachDispatch(sheet.GetRange(COleVariant(strlt), COleVariant(strrd)), TRUE);

			rgMyRge.SetHorizontalAlignment( COleVariant((long)3) );

			rgMyRge.SetMergeCells( COleVariant((long)TRUE) );
		}


		// �ֱ���ÿ����Ԫ���������
		// Excel2000 �ú���SetValue()����, Excel2003�ú���SetValue2()

		sheet.SetName("��ģ��");

		//----------------------------------------------------------------------------




		//app.SetVisible(TRUE);

		app.SetAlertBeforeOverwriting(FALSE); 
		app.SetDisplayAlerts(FALSE); 
		//5�����ѽ���.xls�ļ����Ϊ
		//COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
		book.SaveAs(COleVariant(fileName),covOptional,covOptional,
			covOptional,covOptional,covOptional,0,
			covOptional,covOptional,covOptional,covOptional,covOptional);  


		//6���ر�Excel����

		//AfxMessageBox("ok1");

		//COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
		book.SetSaved(TRUE);     // ��Workbook�ı���״̬����Ϊ�ѱ��棬������ϵͳ��ʾ�Ƿ��˹�����

		//AfxMessageBox("ok2");

		range.ReleaseDispatch();    // �ͷ�Range����
		sheet.ReleaseDispatch();    // �ͷ�Sheet����
		sheets.ReleaseDispatch();    // �ͷ�Sheets����

		book.ReleaseDispatch();     // �ͷ�Workbook����
		books.ReleaseDispatch();    // �ͷ�Workbooks����

		book.Close (covOptional, covOptional,covOptional);// �ر�Workbook����
		books.Close();           // �ر�Workbooks����

		app.Quit();					// �˳�_Application
		app.ReleaseDispatch ();     // �ͷ�_Application

		str.Format("�������! ��ʱ%d����", GetTickCount()-tick);
		AfxMessageBox(str);
		return 1;
	}

}

//---------------------------------------------------------------------------------------


void CExcelOptFun::CalculateTabCellSize( )
{
	int i;
	int nWidth  = 0;
	int nHeight = 0;
	StTabCell  *pTabCell = NULL;
	for (i=0; i<m_nTabCellCnt; i++)
	{
		pTabCell = &m_stTabCell[i];
		nWidth  =  pTabCell->iEndCol - pTabCell->iBegCol + 1;
		nHeight =  pTabCell->iEndRow - pTabCell->iBegRow + 1;

		pTabCell->iRowNum = nHeight;
		pTabCell->iColNum = nWidth;
	}
}


int CExcelOptFun::CheckTabCellOk( )							//���ϲ���Ԫ���Ƿ���ȷ
{
	int i,j,k;
	int bFlag = 1;
	int bCellFlag = 0;
	int nWidth  = 0;
	int nHeight = 0;
	int nRow, nCol, iRowNum, iColNum, posX, posY;
	StTabCell  *pTabCell = NULL;
	CString str;


	ResetItemFlag( );

	nRow = m_row;
	nCol = m_col;

	//1.��Ԫ������Χ���
	for (i=0; i<m_nTabCellCnt; i++)
	{
		pTabCell = &m_stTabCell[i];
		
		//1.
		if ( (pTabCell->iBegRow < 1) || (pTabCell->iBegRow > nRow) )
		{
			str.Format(_T("Error, pos=%d, iBegRow=%d, Out of Range Min=1 or Max=%d!"), 
						i+1, pTabCell->iBegRow, nRow);
			AfxMessageBox(str);
			bFlag = 0;
			break;
		}

		//2.
		if ( (pTabCell->iBegCol < 1) || (pTabCell->iBegCol > nCol) )
		{
			str.Format(_T("Error, pos=%d, iBegCol=%d, Out of Range Min=1 or Max=%d!"), 
				i+1, pTabCell->iBegCol, nCol);
			AfxMessageBox(str);
			bFlag = 0;
			break;
		}

		//3.
		if ( (pTabCell->iEndRow < 1) || (pTabCell->iEndRow > nRow) )
		{
			str.Format(_T("Error, pos=%d, iEndRow=%d, Out of Range Min=1 or Max=%d!"), 
				i+1, pTabCell->iEndRow, nRow);
			AfxMessageBox(str);
			bFlag = 0;
			break;
		}
		
		//4.
		if ( (pTabCell->iEndCol <1 ) || (pTabCell->iEndCol > nCol) )
		{
			str.Format(_T("Error, pos=%d, iEndCol=%d, Out of Range Min=1 or Max=%d!"), 
				i+1, pTabCell->iEndCol, nCol);
			AfxMessageBox(str);
			bFlag = 0;
			break;
		}

		//5.
		if (pTabCell->iEndRow < pTabCell->iBegRow)
		{
			str.Format(_T("Error, pos=%d, iEndRow < iBegRow,  iEndRow=%d, iBegRow=%d !"), 
				i+1, pTabCell->iEndRow, pTabCell->iBegRow);
			bFlag = 0;
			break;
		}

		//6.
		if (pTabCell->iEndCol < pTabCell->iBegCol)
		{
			str.Format(_T("Error, pos=%d, iEndCol < iBegCol,  iEndCol=%d, iBegCol=%d !"), 
				i+1, pTabCell->iEndCol, pTabCell->iBegCol);
			AfxMessageBox(str);
			bFlag = 0;
			break;
		}

		//7.
		if ( (pTabCell->iRowNum <= 1) &&  (pTabCell->iColNum <= 1) )
		{
			str.Format(_T("Error, pos=%d, iRowNum <= 1 and iColNum <=1, iBegRow=%d, iBegCol=%d !"), 
				i+1, pTabCell->iBegRow, pTabCell->iBegCol);
			AfxMessageBox(str);
			bFlag = 0;
			break;
		}
	}

	if (bFlag == 0)
	{
		return bFlag;
	}


	//2.��Ԫ��ϲ�״̬���
	for (i=0; i<m_nTabCellCnt; i++)
	{
		pTabCell = &m_stTabCell[i];
		iRowNum = pTabCell->iRowNum;
		iColNum = pTabCell->iColNum;

		bCellFlag = 1; 
		posX = pTabCell->iBegRow - 1;
		posY = pTabCell->iBegCol - 1;
		for (j=0; j<iRowNum; j++)
		{
			for (k=0; k<iColNum; k++)
			{
				if ((j == 0) && (k == 0))
				{
					if (    (m_ItemFlag[posX+0][posY+0] == cell_desc)  
						|| (m_ItemFlag[posX+0][posY+0] == cell_data) 
						|| (m_ItemFlag[posX+0][posY+0] == cell_order) 
						|| (m_ItemFlag[posX+0][posY+0] == cell_name) 
						|| (m_ItemFlag[posX+0][posY+0] == cell_string) 
						|| (m_ItemFlag[posX+0][posY+0] == cell_calculate) 
						)
					{

					}
					else
					{
						bCellFlag = 0;
						str.Format(_T("Error, pos=%d, iRow=%d, iCol=%d, FirstCell Data Empty!"), 
							i+1, posX+j+1, posY+k+1);
						AfxMessageBox(str);
						break;
					}
				}
				else
				{
					if (   (m_ItemFlag[posX+j][posY+k] == cell_desc)  
						|| (m_ItemFlag[posX+j][posY+k] == cell_data) 
						|| (m_ItemFlag[posX+j][posY+k] == cell_order) 
						|| (m_ItemFlag[posX+j][posY+k] == cell_name) 
						|| (m_ItemFlag[posX+j][posY+k] == cell_string) 
						|| (m_ItemFlag[posX+j][posY+k] == cell_calculate)   
						)
					{
						bCellFlag = 0;
						str.Format(_T("Error, pos=%d, iRow=%d, iCol=%d, Data Not Empty!"), 
							i+1, posX+j+1, posY+k+1);
						AfxMessageBox(str);
						break;
					}
					else
					{
						if ( (iRowNum >= 1) && (iColNum == 1) )
						{
							m_ItemFlag[posX+j][posY+k] = (i+1)*10 + 1;
						}
						else if ( (iRowNum == 1) && (iColNum >= 1) )
						{
							m_ItemFlag[posX+j][posY+k] = (i+1)*10 + 2;
						}
						else
						{
							m_ItemFlag[posX+j][posY+k] = (i+1)*10 + 3;
						}
					}
				}
			}
			if (bCellFlag == 0)
			{
				break;
			}
		}

		if (bCellFlag == 0)
		{
			break;
		}
	}

	if (bCellFlag == 0)
	{
		bFlag = 0;
		return bFlag;
	}

	//3.����Ϊ�ռ��
	for (i=0; i<m_row; i++)
	{
		for (j=0; j<m_col; j++)
		{
			if (m_ItemFlag[i][j] == 0)
			{
				str.Format(_T("Error, ItemData is Empty, iRow=%d, iCol=%d !"), 
					 i+1, j+1);
				AfxMessageBox(str);
				bFlag = 0;
				break;
			}
		}
		if (bFlag == 0)
		{
			break;
		}
	}

	return bFlag;

}

void CExcelOptFun::ResetItemFlag( )
{
	int i,j;

	for (i=0; i<m_row; i++)
	{
		for (j=0; j<m_col; j++)
		{
			if (   (m_ItemFlag[i][j] == cell_desc)  
				|| (m_ItemFlag[i][j] == cell_data) 
				|| (m_ItemFlag[i][j] == cell_order)
				|| (m_ItemFlag[i][j] == cell_name)
				|| (m_ItemFlag[i][j] == cell_string) 
				|| (m_ItemFlag[i][j] == cell_calculate)
			)
			{
				//src
			}
			else
			{
				m_ItemFlag[i][j] = cell_null;		
			}
		}
	}
}

int CExcelOptFun::GetTabCellType(char *szDataName)			//��ȡ��Ԫ����������
{
	int		nType = 0;
	int     pos;
	char    *pData = NULL;
	char    specChar = 0;
	char    tmpBuf[200] = {0,};
	CString str;

	if (strlen(szDataName) == NULL)
	{
		nType = cell_null;
	}
	else
	{
		str = szDataName;
		str = str.MakeUpper();

		//pData = szDataName;
		strcpy(tmpBuf, str.GetBuffer(0));
		pData = tmpBuf;
		pos = str.Find(SPEC_CHAR);
		if ( (pos != -1) && (pData[0] == HEAD_CHAR) )
		{
			specChar = pData[2];

			switch (specChar)
			{
			case SPEC_CHAR_N_NUM:
				{
					nType = cell_data;
					break;
				}		
			case SPEC_CHAR_O_ORD:
				{
					nType = cell_order;
					break;
				}
			case SPEC_CHAR_P_PIC:
				{
					nType = cell_name;
					break;
				}
			case SPEC_CHAR_S_STR:
				{
					nType = cell_string;
					break;
				}		
			case SPEC_CHAR_C_CAL:
				{
					nType = cell_calculate;
					break;
				}
			default:
				nType = cell_data;
			}
			
		}
		else
		{
			nType = cell_desc;
		}
	}
	return nType;

}

//===============================================================================

//-----------------------excel opt begin--------------------------------------

int CExcelOptFun::ReadExcelFile(CString fileName)
{
	int			percent=0;
	char        ItemVal[XLS_MAX_COL][100] = {0,};
	int         Flag = 1;

	//����app��ȫ�ֻ��Ա���� 	
	_Application app;
	Workbooks	books;   
	_Workbook	book;   
	Worksheets  sheets;   
	_Worksheet  sheet;   
	LPDISPATCH  lpDisp;   
	Range		range;   
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR); 
	Range		usedRange; 
	COleVariant vResult;

	int			i,j,k;
	int			sheetCnt;
	CString		str,str1, strFileName;
	long		iRowNum, iColNum, iStartRow, iStartCol;
	//char        *pValue;

	int         xlsCnt = 0;
	int         oldDevOrd= 0;
	CTime       t = CTime::GetCurrentTime();
	CString     strTime;
	double      fVal = 0;
	int         nVal = 0;
	double      floatPI = 0.0000001;

	int     nWidth = 0;
	double  fHeight = 0;
	CString strTemp;
	VARIANT vTemp;
	int    nSumColLen;


	strTime.Format("%04d-%02d-%02d %02d:%02d:%02d", 
		t.GetYear(), t.GetMonth(),  t.GetDay(),
		t.GetHour(), t.GetMinute(), t.GetSecond());


	//-------------------------------------------------------------------

	//fileName = pDlg->m_strFileName;

	//2.����Excel ������(����Excel)
	if (!app.CreateDispatch("Excel.Application"))   
	{   
		AfxMessageBox("�޷�����Excel������");   
		return FALSE;   
	}  

	//3.����Excel��״̬
	app.SetVisible(FALSE);		// ʹExcel�ɼ�   
	app.SetUserControl(TRUE);	// ���������û�����Excel 


	//4.�����е�Excel�ļ�
	books.AttachDispatch(app.GetWorkbooks());   

	lpDisp = books.Open(fileName, covOptional, covOptional,  covOptional,   covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional,   
		covOptional, covOptional, covOptional, covOptional);  


	//�õ�Workbook 
	book.AttachDispatch(lpDisp);

	// �õ�Worksheets
	sheets = book.GetSheets(); 

	sheetCnt = sheets.GetCount();  //��ù���������	//sheets.length;


	nSumColLen = 0;
	
	Flag = 1;

	//ѭ�����б� 
	//for (i=1; i<=sheetCnt; i++)	
	for (i=1; i<=1; i++)	
	{ 
		//��ȡ��i�������� 
		sheet=sheets.GetItem(COleVariant((short)i)); 

		//sheet.Name//��i��������ı���  ������Ҫ�ı��� �Լ�д���ַ��������ṹ�������� 
		strFileName = sheet.GetName();

		usedRange.AttachDispatch(sheet.GetUsedRange()); 

		range.AttachDispatch(usedRange.GetRows()); 

		iRowNum = range.GetCount(); //�Ѿ�ʹ�õ����� 

		range.AttachDispatch(usedRange.GetColumns()); 

		iColNum = range.GetCount(); //�Ѿ�ʹ�õ����� 

		iStartRow=usedRange.GetRow(); //��ʹ���������ʼ�У���1��ʼ 

		iStartCol=usedRange.GetColumn(); //��ʹ���������ʼ�У���1��ʼ 

		str.Format("%d, %d", iRowNum, iColNum);
		//AfxMessageBox(str);

		if ( (iRowNum > XLS_MAX_ROW) || (iColNum > XLS_MAX_COL) )  
		{
			str.Format("Excel Row=%d or Col=%d Num is Out of Range, RowMax=%d, ColMax=%d", 
				iRowNum, iColNum, XLS_MAX_ROW, XLS_MAX_COL);
			AfxMessageBox(str);
			break;
		}

		m_row = iRowNum;
		m_col = iColNum;

		//memset((char*)m_ItemInfo, 0, XLS_MAX_ROW*XLS_MAX_COL*XLS_MAX_LEN);


		for (j=1; j<=iRowNum; j++)		//��
		{
			memset(ItemVal, 0, 20*200);
			for (k=1; k<=iColNum; k++)	//��
			{

				//��ȡ��һ����Ԫ���ֵ 
				range.AttachDispatch(sheet.GetCells()); 

				range.AttachDispatch(range.GetItem (COleVariant((long)j),COleVariant((long)k)).pdispVal ); 

				vResult =range.GetValue2(); 

				if (j == 1) 
				{
					vTemp = range.GetWidth();
					nWidth = (int) (vTemp.dblVal); //(int) (vTemp.dblVal / 6); 
					vTemp = range.GetHeight();
					fHeight = vTemp.dblVal; 

					m_ColLen[k-1] = nWidth;				//��¼�п�
					nSumColLen = nSumColLen + nWidth;	//��¼���п�
				}

				str = "";

				if(vResult.vt == VT_BSTR) //�ַ��� 
				{ 
					str=vResult.bstrVal; 
				} 
				else if (vResult.vt==VT_R8) //8�ֽڵ����� 
				{ 
					fVal = vResult.dblVal;
					nVal = (int) vResult.dblVal;

					if ( fabs(fVal-nVal) > floatPI)
					{
						str.Format("%5.3f",vResult.dblVal);
					}
					else
					{
						str.Format("%d",(int)vResult.dblVal);
					}
				} 
				else if(vResult.vt==VT_DATE) //ʱ���ʽ 
				{ 
					//SYSTEMTIME st; 
					//VariantTimeToSystemTime(&vResult.date, &st); 
				} 
				else if(vResult.vt==VT_EMPTY) //��Ԫ��յ� 
				{ 
					str=""; 
				} 

				str.TrimLeft();
				str.TrimRight();

				strcpy(ItemVal[k-1], str.GetBuffer(0));	

				strcpy(m_ItemInfo[j-1][k-1], str.GetBuffer(0));

				if (strlen(str.GetBuffer(0)) != 0)		//��¼����״̬
				{
					m_ItemFlag[j-1][k-1] = 1;
				}
				else
				{
					m_ItemFlag[j-1][k-1] = 0;
				}

				//AfxMessageBox(str);

			}	//end for (k=1; k<iColNum; k++)	//��		

		}	//end for (j=1; j<iRowNum; j++)		//��

	}	//end for (i=1; i<=sheetCnt; i++)  		//ѭ�����б� 

	usedRange.ReleaseDispatch();

	range.ReleaseDispatch();
	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();
	book.ReleaseDispatch();
	books.ReleaseDispatch();

	app.Quit();
	app.ReleaseDispatch();

	return Flag;
}

int CExcelOptFun::WriteExcelFile(CString fileName)
{
	//����app��ȫ�ֻ��Ա���� 	
	_Application app;

	//�������
	Workbooks	books;   
	_Workbook	book;   
	Worksheets  sheets;   
	_Worksheet  sheet;   
	//LPDISPATCH  lpDisp;   
	Range		range;   
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR); 

	int			i, j, row, col, pos, cnt;
	CString     str, strName, strCell, strBeg, strEnd;
	char        nameArray[20][30] = {0,};

	char ItemName[20][20] = {	
		"ʼ��",		"��֧1",	"��֧2",	"��֧3",   "��֧4", 
		"����",		"�ź�����",	"��ѹ",		"����",
		"���(mm2)","����(p/n)","��ע",	    "����"
	};

	int tick;


	tick = GetTickCount();


	if (!app.CreateDispatch("Excel.Application"))   
	{   
		AfxMessageBox("�޷�����Excel������");   
		return FALSE;   
	}  

	//�½�һ��.xls�ļ�����д������
	//COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	// Get the Workbooks collection so that you can add a new workbook
	books.AttachDispatch(app.GetWorkbooks());  // �õ�Workbooks
	book = books.Add(covOptional);     // �õ�Workbook


	// Get the Worksheets collection so that you can get the IDispatch for the first Worksheet
	sheets = book.GetWorksheets();     // �õ�Worksheets


	//sheets.Delete();

	CString vtMissing = "MySheetNew";


	//sheets.Add(vtMissing,_variant_t(sheet),_variant_t((short)1),COleVariant((short)1)); 

	sheet = sheets.GetItem(COleVariant((short)1)); // �õ�Worksheet


	cnt = 1; 

	pos = 0;
	for (i=0; i<m_row; i++)
	{
		for (j=0; j<m_col; j++)
		{
			row = i+1;
			col = j+1;
			strName = m_ItemInfo[i][j];

			strCell.Format("%c%d", 'A'+col-1, row);
			range  = sheet.GetRange(COleVariant(strCell.GetBuffer(0)), covOptional);  // ��ȡA1 Range
			range.SetValue2( COleVariant(strName.GetBuffer(0)));                               // �������
			range.SetHorizontalAlignment(COleVariant((long)-4108));// ˮƽ���ж��� 
			//SetCellBorder(&range);				
		}

		str.Format("%d / %d , Percent=%d%%", pos, 15*cnt, pos*100 / (15*cnt) );
		//GetDlgItem(IDC_STATIC_INF)->SetWindowText(str);
	}


	// �ֱ���ÿ����Ԫ���������
	// Excel2000 �ú���SetValue()����, Excel2003�ú���SetValue2()

	sheet.SetName("MyName1");

	//app.SetVisible(TRUE);

	app.SetAlertBeforeOverwriting(FALSE); 
	app.SetDisplayAlerts(FALSE); 
	//5�����ѽ���.xls�ļ����Ϊ
	//COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	book.SaveAs(COleVariant(fileName),covOptional,covOptional,
		covOptional,covOptional,covOptional,0,
		covOptional,covOptional,covOptional,covOptional,covOptional);  


	//6���ر�Excel����

	//AfxMessageBox("ok1");

	//COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	book.SetSaved(TRUE);     // ��Workbook�ı���״̬����Ϊ�ѱ��棬������ϵͳ��ʾ�Ƿ��˹�����

	//AfxMessageBox("ok2");

	range.ReleaseDispatch();    // �ͷ�Range����
	sheet.ReleaseDispatch();    // �ͷ�Sheet����
	sheets.ReleaseDispatch();    // �ͷ�Sheets����

	book.ReleaseDispatch();     // �ͷ�Workbook����
	books.ReleaseDispatch();    // �ͷ�Workbooks����

	book.Close (covOptional, covOptional,covOptional);// �ر�Workbook����
	books.Close();           // �ر�Workbooks����

	app.Quit();					// �˳�_Application
	app.ReleaseDispatch ();     // �ͷ�_Application

	str.Format("�������! ��ʱ%d����", GetTickCount()-tick);
	AfxMessageBox(str);
	return 1;
}


int CExcelOptFun::WriteListToExcel(CListCtrl *pList, CString fileName, int IsHaveTail)
{
	//����app��ȫ�ֻ��Ա���� 	
	_Application app;

	//�������
	Workbooks	books;   
	_Workbook	book;   
	Worksheets  sheets;   
	_Worksheet  sheet;   
	//LPDISPATCH  lpDisp;   
	Range		range;   
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR); 

	int			i, j, row, col, pos, cnt;
	CString     str, strName, strCell, strBeg, strEnd;
	char        nameArray[20][30] = {0,};



	int tick;


	tick = GetTickCount();


	if (!app.CreateDispatch("Excel.Application"))   
	{   
		AfxMessageBox("�޷�����Excel������");   
		return FALSE;   
	}  

	//�½�һ��.xls�ļ�����д������
	//COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	// Get the Workbooks collection so that you can add a new workbook
	books.AttachDispatch(app.GetWorkbooks());  // �õ�Workbooks
	book = books.Add(covOptional);     // �õ�Workbook


	// Get the Worksheets collection so that you can get the IDispatch for the first Worksheet
	sheets = book.GetWorksheets();     // �õ�Worksheets


	//sheets.Delete();

	CString vtMissing = "MySheetNew";


	//sheets.Add(vtMissing,_variant_t(sheet),_variant_t((short)1),COleVariant((short)1)); 

	sheet = sheets.GetItem(COleVariant((short)1)); // �õ�Worksheet

	int nRow, nCol, ret, colLen=20;

	char   buff[100]; 
	LVCOLUMN   Column; 
	memset(&Column,0,sizeof(LVCOLUMN)); 
	Column.mask   =   LVCF_TEXT; 
	Column.cchTextMax = 100; 
	Column.pszText    = buff; 



	nCol  = pList->GetHeaderCtrl()->GetItemCount();
	nRow = pList->GetItemCount();

	if (IsHaveTail != 0)
	{
		nRow = nRow - 1;
	}

	cnt = 1; 

	pos = 0;
	for (i=0; i<nRow+1; i++)
	{
		for (j=0; j<nCol; j++)
		{
			
			row = i+1;
			col = j+1;

			if (i==0)
			{
				memset(buff, 0, 100); 
				memset(&Column,0,sizeof(LVCOLUMN)); 
				Column.mask   =   LVCF_TEXT | LVCF_WIDTH; 
				Column.cchTextMax = 100; 
				Column.pszText    = buff; 
				ret = pList->GetColumn(j, &Column);
				colLen  = Column.cx;
				strName = Column.pszText;
				//AfxMessageBox(strName);
			}
			else
			{
				strName = pList->GetItemText(i-1, j);
			}
			

			strCell.Format("%c%d", 'A'+col-1, row);
			range  = sheet.GetRange(COleVariant(strCell.GetBuffer(0)), covOptional);  // ��ȡA1 Range
			if (i== 0)
			{
				range.SetColumnWidth(_variant_t((long)(colLen/7)));
			}
			range.SetValue2( COleVariant(strName.GetBuffer(0)));                               // �������
			range.SetHorizontalAlignment(COleVariant((long)-4108));// ˮƽ���ж��� 
			//SetCellBorder(&range);				
		}

	}


	// �ֱ���ÿ����Ԫ���������
	// Excel2000 �ú���SetValue()����, Excel2003�ú���SetValue2()

	sheet.SetName("MyName1");

	//app.SetVisible(TRUE);

	app.SetAlertBeforeOverwriting(FALSE); 
	app.SetDisplayAlerts(FALSE); 
	//5�����ѽ���.xls�ļ����Ϊ
	//COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	book.SaveAs(COleVariant(fileName),covOptional,covOptional,
		covOptional,covOptional,covOptional,0,
		covOptional,covOptional,covOptional,covOptional,covOptional);  


	//6���ر�Excel����

	//AfxMessageBox("ok1");

	//COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	book.SetSaved(TRUE);     // ��Workbook�ı���״̬����Ϊ�ѱ��棬������ϵͳ��ʾ�Ƿ��˹�����

	//AfxMessageBox("ok2");

	range.ReleaseDispatch();    // �ͷ�Range����
	sheet.ReleaseDispatch();    // �ͷ�Sheet����
	sheets.ReleaseDispatch();    // �ͷ�Sheets����

	book.ReleaseDispatch();     // �ͷ�Workbook����
	books.ReleaseDispatch();    // �ͷ�Workbooks����

	book.Close (covOptional, covOptional,covOptional);// �ر�Workbook����
	books.Close();           // �ر�Workbooks����

	app.Quit();					// �˳�_Application
	app.ReleaseDispatch ();     // �ͷ�_Application

	str.Format("�������! ��ʱ%d����", GetTickCount()-tick);
	AfxMessageBox(str);
	return 1;


}

//----------------------------------------------------------------------


/*
int CExcelOptFun::WriteCellTypesGridCtrlToExcel(CCellTypesGridCtrl *pGridCtrl, CString fileName)
{
	//����app��ȫ�ֻ��Ա���� 	
	_Application app;

	//�������
	Workbooks	books;   
	_Workbook	book;   
	Worksheets  sheets;   
	_Worksheet  sheet;   
	//LPDISPATCH  lpDisp;   
	Range		range;   
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR); 

	int			i, j, row, col, pos, cnt;
	CString     str, strName, strCell, strBeg, strEnd;
	char        nameArray[20][30] = {0,};



	int tick;


	tick = GetTickCount();


	if (!app.CreateDispatch("Excel.Application"))   
	{   
		AfxMessageBox("�޷�����Excel������");   
		return FALSE;   
	}  

	//�½�һ��.xls�ļ�����д������
	//COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	// Get the Workbooks collection so that you can add a new workbook
	books.AttachDispatch(app.GetWorkbooks());  // �õ�Workbooks
	book = books.Add(covOptional);     // �õ�Workbook


	// Get the Worksheets collection so that you can get the IDispatch for the first Worksheet
	sheets = book.GetWorksheets();     // �õ�Worksheets


	//sheets.Delete();

	CString vtMissing = "MySheetNew";


	//sheets.Add(vtMissing,_variant_t(sheet),_variant_t((short)1),COleVariant((short)1)); 

	sheet = sheets.GetItem(COleVariant((short)1)); // �õ�Worksheet

	int nRow, nCol, colLen=25;

	char   buff[100]; 
	char       Name[100];
	LVCOLUMN   Column; 
	memset(&Column,0,sizeof(LVCOLUMN)); 
	Column.mask   =   LVCF_TEXT; 
	Column.cchTextMax = 100; 
	Column.pszText    = buff; 



	nCol  = pGridCtrl->GetColumnCount();
	nRow = pGridCtrl->GetRowCount();

	cnt = 1; 

	pos = 0;
	for (i=0; i<nRow+1; i++)
	{
		for (j=0; j<nCol; j++)
		{

			row = i+1;
			col = j+1;

			if (i==0)
			{
				memset(buff, 0, 100); 
				strName = pGridCtrl->GetColumnName(j);
			}
			else
			{
				memset(Name, 0, 100);
				pGridCtrl->GetItemText(i-1, j, Name);
				strName = Name;
			}


			strCell.Format("%c%d", 'A'+col-1, row);
			range  = sheet.GetRange(COleVariant(strCell.GetBuffer(0)), covOptional);  // ��ȡA1 Range
			if (i== 0)
			{
				range.SetColumnWidth(_variant_t((long)(colLen)));
			}
			range.SetValue2( COleVariant(strName.GetBuffer(0)));                               // �������
			range.SetHorizontalAlignment(COleVariant((long)-4108));// ˮƽ���ж��� 
			//SetCellBorder(&range);				
		}

	}


	// �ֱ���ÿ����Ԫ���������
	// Excel2000 �ú���SetValue()����, Excel2003�ú���SetValue2()

	//sheet.SetName("MyName1");

	//app.SetVisible(TRUE);

	app.SetAlertBeforeOverwriting(FALSE); 
	app.SetDisplayAlerts(FALSE); 
	//5�����ѽ���.xls�ļ����Ϊ
	//COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	book.SaveAs(COleVariant(fileName),covOptional,covOptional,
		covOptional,covOptional,covOptional,0,
		covOptional,covOptional,covOptional,covOptional,covOptional);  


	//6���ر�Excel����

	//AfxMessageBox("ok1");

	//COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	book.SetSaved(TRUE);     // ��Workbook�ı���״̬����Ϊ�ѱ��棬������ϵͳ��ʾ�Ƿ��˹�����

	//AfxMessageBox("ok2");

	range.ReleaseDispatch();    // �ͷ�Range����
	sheet.ReleaseDispatch();    // �ͷ�Sheet����
	sheets.ReleaseDispatch();    // �ͷ�Sheets����

	book.ReleaseDispatch();     // �ͷ�Workbook����
	books.ReleaseDispatch();    // �ͷ�Workbooks����

	book.Close (covOptional, covOptional,covOptional);// �ر�Workbook����
	books.Close();           // �ر�Workbooks����

	app.Quit();					// �˳�_Application
	app.ReleaseDispatch ();     // �ͷ�_Application

	str.Format("�������! ��ʱ%d����", GetTickCount()-tick);
	AfxMessageBox(str);
	return 1;


}
*/




int CExcelOptFun:: AppendExcelFile(CString fileName, int begRow, int endRow, int begCol, int endCol, int sheetNum, int bStyleCenter)
{
	//����app��ȫ�ֻ��Ա���� 	
	_Application app;

	//�������
	Workbooks	books;   
	_Workbook	book;   
	Worksheets  sheets;   
	_Worksheet  sheet;   
	LPDISPATCH  lpDisp;   
	Range		range;   
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR); 

	int			i, j, row, col, pos;
	CString     str, strName, strCell, strBeg, strEnd;
	int tick;

	tick = GetTickCount();


	int sheetCnt;

	//2.����Excel ������(����Excel)
	if (!app.CreateDispatch("Excel.Application"))   
	{   
		AfxMessageBox("�޷�����Excel������");   
		return FALSE;   
	}  

	//3.����Excel��״̬
	app.SetVisible(FALSE);		// ʹExcel�ɼ�   
	app.SetUserControl(TRUE);	// ���������û�����Excel 


	//4.�����е�Excel�ļ�
	books.AttachDispatch(app.GetWorkbooks());   

	lpDisp = books.Open(fileName, covOptional, covOptional,  covOptional,   covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional,   
		covOptional, covOptional, covOptional, covOptional);  


	//�õ�Workbook 
	book.AttachDispatch(lpDisp);

	// �õ�Worksheets
	sheets = book.GetSheets(); 

	sheetCnt = sheets.GetCount();  //��ù���������	//sheets.length;

	
	if ((sheetNum < 0 ) && (sheetNum > sheetCnt))
	{
		sheetNum = 1;
	}
	sheet = sheets.GetItem(COleVariant((short)sheetNum)); // �õ�Worksheet

	pos = 0;
	for (i=begRow; i<endRow; i++)
	{
		for (j=begCol; j<endCol; j++)
		{
				row = i+1;
				col = j+1;
				strName = m_ItemInfo[i][j];

				//strName.Format("row%d_col%d", row, col);

				strCell.Format("%c%d", 'A'+col-1, row);
				range  = sheet.GetRange(COleVariant(strCell.GetBuffer(0)), covOptional);  // ��ȡA1 Range
				range.SetValue2( COleVariant(strName.GetBuffer(0)));                               // �������
				
				if (bStyleCenter)
				{
					range.SetHorizontalAlignment(COleVariant((long)-4108));// ˮƽ���ж��� 
				}
				//SetCellBorder(&range);
		}
	}

	//sheet.SetName("MyName1");
	//app.SetVisible(TRUE);

	app.SetAlertBeforeOverwriting(FALSE); 
	app.SetDisplayAlerts(FALSE);


	//4.�����ļ�
	book.Save();

	//6���ر�Excel����
	book.SetSaved(TRUE);     // ��Workbook�ı���״̬����Ϊ�ѱ��棬������ϵͳ��ʾ�Ƿ��˹�����

	range.ReleaseDispatch();    // �ͷ�Range����
	sheet.ReleaseDispatch();    // �ͷ�Sheet����
	sheets.ReleaseDispatch();    // �ͷ�Sheets����

	book.ReleaseDispatch();     // �ͷ�Workbook����
	books.ReleaseDispatch();    // �ͷ�Workbooks����

	book.Close (covOptional, covOptional,covOptional);// �ر�Workbook����
	books.Close();           // �ر�Workbooks����

	app.Quit();					// �˳�_Application
	app.ReleaseDispatch ();     // �ͷ�_Application

	str.Format("Append�������! ��ʱ%d����", GetTickCount()-tick);
	//AfxMessageBox(str);
	return 1;
}

//==============================================================================


//----------------------------------------------------------------------
int CExcelOptFun::WriteDataToExcel(CModeParMng		*pPar,CListCtrl *pDecList,CListCtrl *pAttachList,
								   CString fileName, int IsHaveTail) //lty Add 2017-2-7
{
	//����app��ȫ�ֻ��Ա���� 	
	_Application app;

	//�������
	Workbooks	books;   
	_Workbook	book;   
	Worksheets  sheets;   
	_Worksheet  sheet;   
	//LPDISPATCH  lpDisp;   
	Range		range;   
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR); 

	int			i, j, row, col, pos, cnt,sheetIndex;
	CString     str, strName, strCell, strBeg, strEnd;
	char        nameArray[20][30] = {0,};



	int tick;


	tick = GetTickCount();


	if (!app.CreateDispatch("Excel.Application"))   
	{   
		AfxMessageBox("�޷�����Excel������");   
		return FALSE;   
	}  

	//�½�һ��.xls�ļ�����д������
	//COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	// Get the Workbooks collection so that you can add a new workbook
	books.AttachDispatch(app.GetWorkbooks());  // �õ�Workbooks
	book = books.Add(covOptional);     // �õ�Workbook


	// Get the Worksheets collection so that you can get the IDispatch for the first Worksheet
	sheets = book.GetWorksheets();     // �õ�Worksheets


	//sheets.Delete();

	CString vtMissing = "MySheetNew";

	int			nDataPos;
	int          nItemFlag = 0;
	char         *pItemInfo = NULL;


	sheet = sheets.GetItem(COleVariant((short)1)); // �õ�Worksheet

	cnt = 1; 

	pos = 0;
	nDataPos = 0;
	for (i=0; i<m_row; i++)
	{
		for (j=0; j<m_col; j++)
		{
			row = i+1;
			col = j+1;
			strName = m_ItemInfo[i][j];
			nItemFlag = pPar->m_ItemFlag[row-1][col-1];
			pItemInfo = pPar->m_ItemInfo[row-1][col-1];
			if (nItemFlag == cell_desc)
			{
				strName.Format(_T("%s"), pItemInfo);
			}	
			else if (nItemFlag == cell_data)
			{
				if (pPar->m_nModeType == mode_normal)
				{
					if (nDataPos < pPar->m_nDataCnt)
					{
						strName.Format(_T("%s"), pPar->m_stOutTestData[nDataPos].szOutData);
					}
					else
					{
						strName.Format( _T("") );
					}
				}
				else
				{
					if (nDataPos < pPar->m_nMulDataCnt)
					{
						strName.Format(_T("%s"), pPar->m_stOutTestData[nDataPos].szOutData);
					}
					else
					{
						strName.Format( _T("") );
					}
				}

				nDataPos++;
			}


			strCell.Format("%c%d", 'A'+col-1, row);
			range  = sheet.GetRange(COleVariant(strCell.GetBuffer(0)), covOptional);  // ��ȡA1 Range
			range.SetValue2( COleVariant(strName.GetBuffer(0)));                               // �������
			range.SetHorizontalAlignment(COleVariant((long)-4108));// ˮƽ���ж��� 
			//SetCellBorder(&range);	

			if (i==0)
			{
				range.SetColumnWidth( COleVariant((long)m_ColLen[j]/6) );
			}
		}

		str.Format("%d / %d , Percent=%d%%", pos, 15*cnt, pos*100 / (15*cnt) );
		//GetDlgItem(IDC_STATIC_INF)->SetWindowText(str);
	}



	CString		strlt, strrd;
	Range		rgMyRge;
	StTabCell	*pStTabCell = NULL;


	for (i=0; i<m_nTabCellCnt; i++)
	{
		pStTabCell = &m_stTabCell[i];

		//strlt = "A1";
		//strrd = "C4";

		strlt.Format("%c%d", 'A'+pStTabCell->iBegCol-1, pStTabCell->iBegRow);
		strrd.Format("%c%d", 'A'+pStTabCell->iEndCol-1, pStTabCell->iEndRow);

		rgMyRge.AttachDispatch(sheet.GetRange(COleVariant(strlt), COleVariant(strrd)), TRUE);

		rgMyRge.SetHorizontalAlignment( COleVariant((long)3) );

		rgMyRge.SetMergeCells( COleVariant((long)TRUE) );
	}


	// �ֱ���ÿ����Ԫ���������
	// Excel2000 �ú���SetValue()����, Excel2003�ú���SetValue2()

	sheet.SetName("������Ϣ");


	//sheets.Add(vtMissing,_variant_t(sheet),_variant_t((short)1),COleVariant((short)1)); 

	for (sheetIndex = 2;sheetIndex<=3;sheetIndex++)
	{
		sheet = sheets.GetItem(COleVariant((short)sheetIndex)); // �õ�Worksheet

		int nRow, nCol, ret, colLen=20;

		char   buff[100]; 
		LVCOLUMN   Column; 
		memset(&Column,0,sizeof(LVCOLUMN)); 
		Column.mask   =   LVCF_TEXT; 
		Column.cchTextMax = 100; 
		Column.pszText    = buff; 


		CListCtrl *pList = NULL;
		if(sheetIndex == 2)
		{
			pList = pDecList;
		}else if(sheetIndex==3)
		{
			pList = pAttachList;
		}

		if(pList == NULL)
		{
			continue;
		}
		nCol  = pList->GetHeaderCtrl()->GetItemCount();
		nRow = pList->GetItemCount();

		if (IsHaveTail != 0)
		{
			nRow = nRow - 1;
		}

		cnt = 1; 

		pos = 0;
		for (i=0; i<nRow+1; i++)
		{
			for (j=0; j<nCol; j++)
			{

				row = i+1;
				col = j+1;

				if (i==0)
				{
					memset(buff, 0, 100); 
					memset(&Column,0,sizeof(LVCOLUMN)); 
					Column.mask   =   LVCF_TEXT | LVCF_WIDTH; 
					Column.cchTextMax = 100; 
					Column.pszText    = buff; 
					ret = pList->GetColumn(j, &Column);
					colLen  = Column.cx;
					strName = Column.pszText;
					//AfxMessageBox(strName);
				}
				else
				{
					strName = pList->GetItemText(i-1, j);
				}


				strCell.Format("%c%d", 'A'+col-1, row);
				range  = sheet.GetRange(COleVariant(strCell.GetBuffer(0)), covOptional);  // ��ȡA1 Range
				if (i== 0)
				{
					range.SetColumnWidth(_variant_t((long)(colLen/7)));
				}
				range.SetValue2( COleVariant(strName.GetBuffer(0)));                               // �������
				range.SetHorizontalAlignment(COleVariant((long)-4108));// ˮƽ���ж��� 
				//SetCellBorder(&range);				
			}

		}


		// �ֱ���ÿ����Ԫ���������
		// Excel2000 �ú���SetValue()����, Excel2003�ú���SetValue2()

		if(sheetIndex == 2)
		{
			sheet.SetName(_T("������Ϣ"));
		}else if(sheetIndex == 3)
		{
			sheet.SetName(_T("������Ϣ"));
		}

	}




	//app.SetVisible(TRUE);

	app.SetAlertBeforeOverwriting(FALSE); 
	app.SetDisplayAlerts(FALSE); 
	//5�����ѽ���.xls�ļ����Ϊ
	//COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	book.SaveAs(COleVariant(fileName),covOptional,covOptional,
		covOptional,covOptional,covOptional,0,
		covOptional,covOptional,covOptional,covOptional,covOptional);  


	//6���ر�Excel����

	//AfxMessageBox("ok1");

	//COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	book.SetSaved(TRUE);     // ��Workbook�ı���״̬����Ϊ�ѱ��棬������ϵͳ��ʾ�Ƿ��˹�����

	//AfxMessageBox("ok2");

	range.ReleaseDispatch();    // �ͷ�Range����
	sheet.ReleaseDispatch();    // �ͷ�Sheet����
	sheets.ReleaseDispatch();    // �ͷ�Sheets����

	book.ReleaseDispatch();     // �ͷ�Workbook����
	books.ReleaseDispatch();    // �ͷ�Workbooks����

	book.Close (covOptional, covOptional,covOptional);// �ر�Workbook����
	books.Close();           // �ر�Workbooks����

	app.Quit();					// �˳�_Application
	app.ReleaseDispatch ();     // �ͷ�_Application

	str.Format("�������! ��ʱ%d����", GetTickCount()-tick);
	AfxMessageBox(str);
	return 1;
}