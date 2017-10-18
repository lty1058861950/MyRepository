// ModeParMng.cpp: implementation of the CModeParMng class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ModeParMng.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

double      floatPI = 0.0000001;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CModeParMng::CModeParMng()
{
	m_IsNew = 0;

	//1.������Ϣ
	m_row = 0;
	m_col = 0;
	m_ItemInfo = NULL;

	//2.���ݱ�־
	m_ItemFlag = NULL;
	
	//3.�г���			
    m_nSumColLen = 0;           //���г�
	m_ColLen = NULL;
	
	//4.�ϲ���Ԫ��	
	m_nTabCellCnt = 0;
	m_stTabCell = NULL;
	
	//5.�в�������
	m_nTabRowSrtCnt = 0;		//��Ч�и���
	m_stTabRow = NULL;
	
	//6.�в�������		
	m_nTabColSrtCnt = 0;		//��Ч�и���
	m_stTabCol = NULL;
			
	//���Խ���������
	//================================================================
	
	//7.���Խ��	
	m_nDataCnt = 0;
	m_stTabData = NULL;
				
	//8.��������
	m_stTabAlarm = NULL;
	
	//9.��ʷ��ֵ���[TAB_MAX_DATA_CNT]
	//================================================================		
	m_stTabHisChk = NULL;
	
	//���Խ�����
	//================================================================
	
	//10.���Խ��
	m_stOutTestData = NULL;
	
	//11.������Ϣ	
	//----------------------------------------------------------------
	m_nOutAppDataCnt = 0;	
	m_stOutAppData = NULL;

	memset(m_szUsrName,				0,	MAX_USR_NAME_LEN);		//�û�����	
	memset(m_szOutAppDataUsrName,	0,	MAX_USR_NAME_LEN);		//���Խ��_�û�����
	memset(m_szOutAppDataUsrTime,	0,  30);					//���Խ��_�洢ʱ��

	m_nModeType  = mode_normal;
	m_nMulDataCnt = 1; 

	m_nFetchPercent  = 0;
	m_nFetchCnt = 0;
	m_nFetchSum = 0;
	m_bFetchFinished = 0;
	memset(m_szFetchSaveTime, 0, 30);

	m_bCalType = 0;
}

CModeParMng::~CModeParMng()
{

}

//=================================================================================

int CModeParMng::NewItemInfo( )
{
	int			i,j;
	CString		str;
	
	m_IsNew = 1;
		
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
	
	//���Խ���������
	//================================================================
	
	//7.���Խ��	[TAB_MAX_DATA_CNT]
	//----------------------------------------------------------------
	m_nDataCnt = 0;
	m_stTabData = new StTabData[TAB_MAX_DATA_CNT];				
	
	//8.��������	[TAB_MAX_DATA_CNT]
	//----------------------------------------------------------------
	m_stTabAlarm = new StTabAlarm[TAB_MAX_DATA_CNT];		
	
	
	//9.��ʷ��ֵ���[TAB_MAX_DATA_CNT]
	//================================================================
	m_stTabHisChk = new StTabHisChk[TAB_MAX_DATA_CNT];			
	
	
	//���Խ�����
	//================================================================

	//10.���Խ��	[TAB_MAX_DATA_CNT]
	//----------------------------------------------------------------

	m_stOutTestData = new StOutTestData[TAB_MAX_DATA_CNT];		
	
	//11.������Ϣ	[MD_MAX_APP_CNT]
	//----------------------------------------------------------------
	m_nOutAppDataCnt = 0;
	m_stOutAppData = new StOutAppData[MD_MAX_APP_CNT];
	
	//12.Tmp������Ϣ	[MD_MAX_APP_CNT]
	m_stTmpOutAppData= new StOutAppData[MD_MAX_APP_CNT];	
	return 1;
}

int CModeParMng::DeleteItemInfo( )
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
	
	//���Խ���������
	//================================================================
	
	//7.���Խ��	[TAB_MAX_DATA_CNT]
	//----------------------------------------------------------------
	m_nDataCnt = 0;
	if (m_stTabData != NULL)
	{
		delete[] m_stTabData;
		m_stTabData = NULL;
	}				
	
	//8.��������	[TAB_MAX_DATA_CNT]
	//----------------------------------------------------------------		
	if (m_stTabAlarm != NULL)
	{
		delete[] m_stTabAlarm;
		m_stTabAlarm = NULL;
	}	
	
	//9.��ʷ��ֵ���[TAB_MAX_DATA_CNT]
	//================================================================		
	if (m_stTabHisChk != NULL)
	{
		delete[] m_stTabHisChk;
		m_stTabHisChk = NULL;
	}
	
	//���Խ�����
	//================================================================
	
	//10.���Խ��	[TAB_MAX_DATA_CNT]
	//----------------------------------------------------------------
	if (m_stOutTestData != NULL)
	{
		delete[] m_stOutTestData;
		m_stOutTestData = NULL;
	}	
	
	//11.������Ϣ	[MD_MAX_APP_CNT]
	//----------------------------------------------------------------
	m_nOutAppDataCnt = 0;	
	if (m_stOutAppData != NULL)
	{
		delete[] m_stOutAppData;
		m_stOutAppData = NULL;
	}	

	//12.Tmp������Ϣ	[MD_MAX_APP_CNT]
	//----------------------------------------------------------------
	if (m_stTmpOutAppData != NULL)
	{
		delete[] m_stTmpOutAppData;
		m_stTmpOutAppData = NULL;
	}	


	return 1;
}


int CModeParMng::ClearParamInfo( int IsInit )
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

	//���Խ���������
	//================================================================
	
	//7.���Խ��	[TAB_MAX_DATA_CNT]
	//----------------------------------------------------------------
	m_nDataCnt = 0;
	for (i=0; i<TAB_MAX_DATA_CNT; i++)
	{
		memset( (char*)(&m_stTabData[i]), 0, sizeof(m_stTabData) );	
	}
	
	//8.��������	[TAB_MAX_DATA_CNT]
	//----------------------------------------------------------------		
	for (i=0; i<TAB_MAX_DATA_CNT; i++)
	{
		memset( (char*)(&m_stTabAlarm[i]), 0, sizeof(StTabAlarm));
	}

	//9.��ʷ��ֵ���[TAB_MAX_DATA_CNT]
	//================================================================		
	for (i=0; i<TAB_MAX_DATA_CNT; i++)
	{
		memset( (char*)(&m_stTabHisChk[i]), 0, sizeof(StTabHisChk));
	}
	
	
	//10.���Խ��	[TAB_MAX_DATA_CNT]
	//----------------------------------------------------------------	
	for (i=0; i<TAB_MAX_DATA_CNT; i++)
	{
		memset( (char*)(&m_stOutTestData[i]), 0, sizeof(StOutTestData));
	}
	
	//11.������Ϣ	[MD_MAX_APP_CNT]
	//----------------------------------------------------------------
	m_nOutAppDataCnt = 0;
	for (i=0; i<MD_MAX_APP_CNT; i++)
	{
		memset( (char*)(&m_stOutAppData[i]), 0, sizeof(StOutAppData));
	}

	//12.Tmp������Ϣ	[MD_MAX_APP_CNT]
	//----------------------------------------------------------------
	for (i=0; i<MD_MAX_APP_CNT; i++)
	{
		memset( (char*)(&m_stTmpOutAppData[i]), 0, sizeof(StOutAppData));
	}

	return 1;
}

//=================================================================================


void CModeParMng::CalculateTabCellSize( )
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


int CModeParMng::CheckTabCellOk( )							//���ϲ���Ԫ���Ƿ���ȷ
{
	int i,j,k;
	int bFlag = 1;
	int bCellFlag = 1;
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

void CModeParMng::ResetItemFlag( )
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


void CModeParMng::GetItemFlagFromData( )                   //��ItemInfo��ȡItemFlag
{
	int i,j;
	
	if (m_nModeType == mode_normal)
	{
		for (i=0; i<m_row; i++)
		{
			for (j=0; j<m_col; j++)
			{
				m_ItemFlag[i][j] = GetTabCellType(m_ItemInfo[i][j]);			
			}
		}
	}
	else if (m_nModeType == mode_rowvar) 
	{
		for (i=0; i<m_row; i++)
		{
			for (j=0; j<m_col; j++)
			{
				m_ItemFlag[i][j] = GetTabCellType(m_ItemInfo[i][j]);			
			}
		}

		int pos = m_row-1;
		for (i=m_row; i<m_row+m_nMulRowCnt-1; i++)
		{
			for (j=0;j<m_col; j++)
			{
				m_ItemFlag[i][j] = m_ItemFlag[pos][j];
			}
		}
	}
	

}

//---------------------------------------------------------------------------------
int CModeParMng::GetTabDataList( )							//��ȡ�����б�
{
	int i,j, nCnt;
	StTabData *pTabData = NULL;
	CString   str;
	char      *pData = NULL;
	int       nDinType = 0;
	
	nCnt = 0;
	for (i=0; i<m_row; i++)
	{
		for (j=0; j<m_col; j++)
		{
			if (	(m_ItemFlag[i][j] == cell_data)
				||  (m_ItemFlag[i][j] == cell_string)
				||  (m_ItemFlag[i][j] == cell_calculate)
			   )
			{
				nDinType = m_ItemFlag[i][j];

				pTabData= &m_stTabData[nCnt];
				str.Format( _T("D%02d_%d_%d"), nCnt+1, i+1, j+1);
				strcpy(pTabData->szDbColName, str.GetBuffer(0));
				//strcpy(pTabData->szOutDataName, "");
				pTabData->iBegRow = i+1;
				pTabData->iBegCol = j+1;

				//��������
				if (nDinType == cell_data)
				{
					pTabData->iDataType = datatype_num;
				}
				else if (nDinType == cell_string)
				{
					pTabData->iDataType = datatype_string;
				}
				else if (nDinType == cell_calculate)
				{
					pTabData->iDataType = datatype_caluate;
				}

				nCnt++;
					
				if (nCnt >= TAB_MAX_DATA_CNT)
				{
					str.Format(_T("Out of Max Range %d"), TAB_MAX_DATA_CNT);
					AfxMessageBox(str);
					return 0;
				}		
			}
		}
	}
	
	m_nDataCnt = nCnt; 
	
	return 1;
}	


int CModeParMng::GetTabCellType(char *szDataName)			//��ȡ��Ԫ����������
{
	int		nType = 0;
	int     pos;
	char    *pData = NULL;
	CString str;
	char    specChar = 0;
	char    tmpBuf[200] = {0,};

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

int CModeParMng::GetTabDataRowAndColNameFlag( )			//��ȡ�����ƺ������Ʊ�־
{
	int		 i,j, nCnt;
	StTabRow *pTabRow = NULL;
	StTabCol *pTabCol = NULL;

	for (i=0; i<m_row; i++)
	{
		pTabRow = &m_stTabRow[i];
		pTabRow->iRowPos   = i+1;
		pTabRow->bDataFlag = 0;
	}

	for (i=0; i<m_col; i++)
	{
		pTabCol = &m_stTabCol[i];
		pTabCol->iColPos   = i+1;
		pTabCol->bDataFlag = 0;
	}

	for (i=0; i<m_row; i++)
	{
		pTabRow = &m_stTabRow[i];
		for (j=0; j<m_col; j++)
		{
			pTabCol = &m_stTabCol[j];
			if  (    (m_ItemFlag[i][j] == cell_data)
				  || (m_ItemFlag[i][j] == cell_string)
		          || (m_ItemFlag[i][j] == cell_calculate)
				 )
			{
				pTabRow->bDataFlag = 1;
				pTabCol->bDataFlag = 1;
			}
		}
	}

	nCnt = 0;
	for (i=0; i<m_row; i++)
	{
		pTabRow = &m_stTabRow[i];
		if (pTabRow->bDataFlag != 0)
		{
			nCnt++;
		}
	}
	m_nTabRowSrtCnt = nCnt;

	nCnt = 0;
	for (i=0; i<m_col; i++)
	{
		pTabCol = &m_stTabCol[i];
		if (pTabCol->bDataFlag != 0)
		{
			nCnt++;
		}
	}
	m_nTabColSrtCnt = nCnt;

	return 1;
}


int CModeParMng::CheckTabDataRowAndColNotNull( )			//���TabData�к��в�Ϊ��
{
	StTabRow	*pTabRow = NULL;
	StTabCol	*pTabCol = NULL;
	StTabData	*pTabData = NULL;
	int		 bFlag;
	int		 i;
	CString  str;

	GetTabDataRowAndColNameFlag( );			//��ȡ�����ƺ������Ʊ�־

	bFlag = 0;

	for (i=0; i<m_row;i++)
	{
		pTabRow = &m_stTabRow[i];
		if (pTabRow->bDataFlag != 0)
		{
			if (strlen(pTabRow->szRowName) == 0)
			{
				str.Format(_T("Error: TabRow, pos=%d, RowName is NULL!"), i+1);
				AfxMessageBox(str);
				bFlag = 1;
				break;
			}
		}
	}

	if (bFlag != 0)
	{
		return  0;
	}

	for (i=0; i<m_col;i++)
	{
		pTabCol = &m_stTabCol[i];
		if (pTabCol->bDataFlag != 0)
		{
			if (strlen(pTabCol->szColName) == 0)
			{
				str.Format(_T("Error: TabCol, pos=%d, ColName is NULL!"), i+1);
				AfxMessageBox(str);
				bFlag = 1;
				break;
			}
		}
	}
	
	if (bFlag != 0)
	{
		return  0;
	}

	for (i=0; i<m_nDataCnt; i++)
	{
		pTabData = &m_stTabData[i];
		if (strlen(pTabData->szOutDataName) == 0)
		{
			str.Format(_T("Error: TabData, pos=%d, OutDataName is NULL!"), i+1);
			AfxMessageBox(str);
			bFlag = 1;
			break;
		}
	}

	if (bFlag != 0)
	{
		return  0;
	}

	return 1;
}


int CModeParMng::GetTabDataRowAndColNameToStTabData( )     //��ȡ��������������
{
	CModeParMng  *pPar = this; 
	StTabData    *pTabData = NULL;
	StTabRow  *pTabRow = NULL;
	StTabCol  *pTabCol = NULL;

	int		i, j, pos;
	CString	str;
	int     iRowNum;//, iColNum;
	char	ItemName[20][30] = {"���", "���ݱ�_���ֶ�����",  "�к�", "�м��",  "�к�", "�м��", "���ݱ�_���ֶ�����",};
	int     ItemLen[20]      = {  50,     140,                 60,		100,	  60,	100,		180 };

	
	if (pPar->m_nModeType == mode_normal)
	{
		iRowNum = pPar->m_nDataCnt;
		//iColNum = 7;
		for (i=0; i<iRowNum; i++)
		{
			pTabData = &pPar->m_stTabData[i];

			//4.
			pTabRow = &m_stTabRow[pTabData->iBegRow-1];

			//6.
			pTabCol = &m_stTabCol[pTabData->iBegCol-1];

			if ( (strlen(pTabRow->szRowName)!=0) && (strlen(pTabCol->szColName) != 0) )
			{
				str.Format( _T("%s_%s"), pTabRow->szRowName, pTabCol->szColName);
				strcpy(pTabData->szOutDataName, str.GetBuffer(0));
			}
			else
			{
				str.Format( _T("%s"), pTabData->szOutDataName);
			}	
		}
	}
	else if (pPar->m_nModeType == mode_rowvar)
	{
		iRowNum = pPar->m_nDataCnt;	
		pos = 0;
		for (i=1; i<pPar->m_nMulRowCnt; i++)
		{
			for (j=0; j<iRowNum; j++)
			{
				//m_stTabData
				memcpy((char*)(&pPar->m_stTabData[i*iRowNum+j]), (char*)(&pPar->m_stTabData[j]), sizeof(StTabData));

				pTabData = &pPar->m_stTabData[i*iRowNum+j];
				pTabData->iBegRow = pTabData->iBegRow+i;

				//m_stTabAlarm;			//8.��������	[TAB_MAX_DATA_CNT]
				memcpy((char*)(&pPar->m_stTabAlarm[i*iRowNum+j]), (char*)(&pPar->m_stTabAlarm[j]), sizeof(StTabAlarm));

				//m_stTabHisChk			��ʷ��ֵ���
				memcpy((char*)(&pPar->m_stTabHisChk[i*iRowNum+j]), (char*)(&pPar->m_stTabHisChk[j]), sizeof(StTabHisChk));
	
			}

			//m_stRowName
			memcpy((char*)(&pPar->m_stTabRow[i+1]), (char*)(&pPar->m_stTabRow[1]), sizeof(StTabRow));
			pPar->m_stTabRow[i].iRowPos = i;

		}

		iRowNum = pPar->m_nDataCnt * pPar->m_nMulRowCnt;

		for (i=0; i<iRowNum; i++)
		{
			pTabData = &pPar->m_stTabData[i];

			//4.
			pTabRow = &m_stTabRow[pTabData->iBegRow-1];

			//6.
			pTabCol = &m_stTabCol[pTabData->iBegCol-1];

			if ( (strlen(pTabRow->szRowName)!=0) && (strlen(pTabCol->szColName) != 0) )
			{
				str.Format( _T("%s_%s"), pTabRow->szRowName, pTabCol->szColName);
				strcpy(pTabData->szOutDataName, str.GetBuffer(0));
			}
			else
			{
				str.Format( _T("%s"), pTabData->szOutDataName);
			}	
		
		}

	}

	return 1;

}




//�������
//------------------------------------------------------------------------------
int CModeParMng::GetTabAlarmJudgeTypeFromDesc(char *szJudgeDesc)
{
	int bRet = -1;
	int nJudgeType = 0;

	if ( (szJudgeDesc == NULL) || (strlen(szJudgeDesc) == 0) )
	{
		return -1;
	}

	if (strcmp(szJudgeDesc, COND_NULL) == 0)
	{
		nJudgeType = type_null;
	}
	else if (strcmp(szJudgeDesc, COND_BIG		) == 0)
	{
		nJudgeType = type_big;
	}
	else if (strcmp(szJudgeDesc, COND_SMALL		) == 0)
	{
		nJudgeType = type_small;
	}
	else if (strcmp(szJudgeDesc, COND_BIGEQUAL	) == 0)
	{
		nJudgeType = type_bigequal;
	}
	else if (strcmp(szJudgeDesc, COND_SMALLEQUAL) == 0)
	{
		nJudgeType = type_smallequal;
	}
	else if (strcmp(szJudgeDesc, COND_EQUAL		) == 0)
	{
		nJudgeType = type_equal;
	}
	else if (strcmp(szJudgeDesc, COND_UNEQUAL	) == 0)
	{
		nJudgeType = type_unequal;
	}
	else if (strcmp(szJudgeDesc, COND_BETWEEN_1	) == 0)
	{
		nJudgeType = type_between1;
	}
	else if (strcmp(szJudgeDesc, COND_BETWEEN_2	) == 0)
	{
		nJudgeType = type_between2;
	}

	return nJudgeType;

}
	
int CModeParMng::GetTabAlarmJudgeDescFormType(int nJudgeType, char *szJudgeDesc)
{
	int bRet = 1;

	switch (nJudgeType)
	{
		case type_null:
			{
				strcpy(szJudgeDesc, COND_NULL);
				break;
			}
		case type_big:
			{
				strcpy(szJudgeDesc, COND_BIG);
				break;
			}
		case type_small:
			{
				strcpy(szJudgeDesc, COND_SMALL);
				break;
			}
		case type_bigequal:
			{
				strcpy(szJudgeDesc, COND_BIGEQUAL);
				break;
			}
		case type_smallequal:
			{
				strcpy(szJudgeDesc, COND_SMALLEQUAL);
				break;
			}
		case type_equal:
			{
				strcpy(szJudgeDesc, COND_EQUAL);
				break;
			}
		case type_unequal:
			{
				strcpy(szJudgeDesc, COND_UNEQUAL);
				break;
			}
		case type_between1:
			{
				strcpy(szJudgeDesc, COND_BETWEEN_1);
				break;
			}
		case type_between2:
			{
				strcpy(szJudgeDesc, COND_BETWEEN_2);
				break;
			}
		default:
			{
				bRet = 0;
				break;
			}
	}
	
	return bRet;

}


int CModeParMng::GetTabAlarmDisDescFromPos(int nPos, char *szDisDesc)
{
	StTabAlarm *pTabAlarm = NULL;
	
	int		bRet = 1;
	int		nJudgeType = 0;
	CString str=_T("");
	int     nRowBei = 1;
	
	if (m_nModeType == mode_rowvar)
	{
		nRowBei = m_nMulRowCnt;
	}

	if ( (nPos < 0) || (nPos > m_nDataCnt*nRowBei-1) )
	{
		return 0;
	}
	else
	{
		pTabAlarm = &m_stTabAlarm[nPos];
		nJudgeType = pTabAlarm->nJudgeType;
	}
	
	
	
	switch (nJudgeType)
	{
	case type_null:
		{
			str.Format(_T("%s"), COND_NULL);
			break;
		}
	case type_big:
		{
			str.Format(_T("x>%s"), pTabAlarm->szTarget1);
			break;
		}
	case type_small:
		{
			str.Format(_T("x<%s"), pTabAlarm->szTarget1);
			break;
		}
	case type_bigequal:
		{
			str.Format(_T("x>=%s"), pTabAlarm->szTarget1);
			break;
		}
	case type_smallequal:
		{
			str.Format(_T("x<=%s"), pTabAlarm->szTarget1);
			break;
		}
	case type_equal:
		{
			str.Format(_T("x==%s"), pTabAlarm->szTarget1);
			break;
		}
	case type_unequal:
		{
			str.Format(_T("x!=%s"), pTabAlarm->szTarget1);
			break;
		}
	case type_between1:
		{
			str.Format(_T("%s<x<%s"), pTabAlarm->szTarget1, pTabAlarm->szTarget2);
			break;
		}
	case type_between2:
		{
			str.Format(_T("%s<=x<=%s"), pTabAlarm->szTarget1, pTabAlarm->szTarget2);
			break;
		}
	default:
		{
			bRet = 0;
			break;
		}
	}

	strcpy(szDisDesc, str.GetBuffer(0));
	
	return bRet;
	
}

int CModeParMng::GetTabDataPos(int iRow, int iCol)
{
	int i, pos = -1;
	StTabData *pTabData = NULL;

	if (m_nModeType == mode_normal)
	{
		for (i=0; i<m_nDataCnt; i++)
		{
			pTabData = &m_stTabData[i];
			if ((pTabData->iBegRow == iRow) && (pTabData->iBegCol == iCol) )
			{
				pos = i;
				break;
			}
		}
	}
	else if (m_nModeType == mode_rowvar)
	{
		for (i=0; i<m_nDataCnt*m_nMulRowCnt; i++)
		{
			pTabData = &m_stTabData[i];
			if ((pTabData->iBegRow == iRow) && (pTabData->iBegCol == iCol) )
			{
				pos = i;
				break;
			}
		}
	}
	
	
	return pos;
}


int CModeParMng::CalculateAlarmFlag(int nPos, double fVal)
{
	int bErrFlag = 0;
	double fTarger1, fTarger2;
	StTabAlarm *pTabAlarm = NULL;
	int			nJudgeType;

	pTabAlarm = &m_stTabAlarm[nPos];
	nJudgeType = pTabAlarm->nJudgeType;
	fTarger1 = atof(pTabAlarm->szTarget1);
	fTarger2 = atof(pTabAlarm->szTarget2);

	
	switch (nJudgeType)
	{
	case type_null:
		{
			bErrFlag = 0;
			break;
		}
	case type_big:
		{
			if (fVal > fTarger1)
			{
				bErrFlag = 0;
			}
			else
			{
				bErrFlag = 1;
			}
			break;
		}
	case type_small:
		{
			if (fVal < fTarger1)
			{
				bErrFlag = 0;
			}
			else
			{
				bErrFlag = 1;
			}
			break;
		}
	case type_bigequal:
		{
			if (fVal >= fTarger1)
			{
				bErrFlag = 0;
			}
			else
			{
				bErrFlag = 1;
			}
			break;
		}
	case type_smallequal:
		{
			if (fVal <= fTarger1)
			{
				bErrFlag = 0;
			}
			else
			{
				bErrFlag = 1;
			}
			break;
		}
	case type_equal:
		{
			if (fabs(fVal - fTarger1) < floatPI)
			{
				bErrFlag = 0;
			}
			else
			{
				bErrFlag = 1;
			}
			break;
		}
	case type_unequal:
		{
			if (fabs(fVal - fTarger1) > floatPI)
			{
				bErrFlag = 0;
			}
			else
			{
				bErrFlag = 1;
			}
			break;
		}
	case type_between1:
		{
			if ( (fTarger1 < fVal) && (fVal < fTarger2) )
			{
				bErrFlag = 0;
			}
			else
			{
				bErrFlag = 1;
			}
			break;
		}
	case type_between2:
		{
			if ( (fTarger1 <= fVal) && (fVal <= fTarger2) )
			{
				bErrFlag = 0;
			}
			else
			{
				bErrFlag = 1;
			}
			break;
		}
	default:
		{
			bErrFlag = 0;
			break;
		}
	}
	
	return bErrFlag;
}


int CModeParMng::CalculateHisChkFlag(int nPos, double fVal)
{
	int bErrFlag = 0;
	double fTarger1, fTarger2;
	StTabHisChk *pTabHisChk = NULL;
	//int			nJudgeType;

	pTabHisChk = &m_stTabHisChk[nPos];

	fTarger1 = atof(pTabHisChk->szHisValMin);
	fTarger2 = atof(pTabHisChk->szHisValMax);

	if (pTabHisChk->bHisChkFlag != 0)
	{
		if ( (fTarger1 <= fVal) && (fVal <= fTarger2) )
		{
			bErrFlag = 0;
		}
		else
		{
			bErrFlag = 1;
		}
	}
	else
	{
		bErrFlag = 0;
	}
		
	return bErrFlag;
}



//�����б���ʾ���
//==============================================================================
void CModeParMng::ListCtrl_ClearAllColumn(CListCtrl *pList)
{
	int		i, nColCnt;
	pList->DeleteAllItems();
	nColCnt = pList->GetHeaderCtrl()->GetItemCount();
	for (i=0; i<nColCnt; i++)
	{
		pList->DeleteColumn(0);
	}	
}

void CModeParMng::DisplayTabSizeInfo(CListCtrl *pList)		//��ʾ���ģ��_���ߴ���Ϣ
{
	CModeParMng *pPar = this; 
	
	int		i,pos;
	CString	str;
	int     iRowNum, iColNum; 
	char	ItemName[20][30] = {"���", "��������", "����ֵ*", "����ʾ���", "xxxx4"};
	int     ItemLen[20]      = {  50,     130,     120, 100,       80 };
	int     EnableCol = 2;
	
	ListCtrl_ClearAllColumn(pList);
	
	iRowNum = 3;
	iColNum = 3;
	
	for (i=0; i<iColNum; i++)
	{
		str.Format("%s", ItemName[i]);
		pList->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen[i]);	
	}
	

	for (i=0; i<iRowNum; i++)
	{
		//1.
		str.Format("%3d", i+1);
		pList->InsertItem(i, str);
		
		pos = 1;
		if (i == 0)
		{
			//1.2
			str.Format( _T("����и���") );
			pList->SetItemText(i, pos++, str);
			
			//1.3
			str.Format( _T("%d"), pPar->m_row);
			pList->SetItemText(i, pos++, str);
		}
		else if (i == 1)
		{
			//2.2
			str.Format( _T("����и���") );
			pList->SetItemText(i, pos++, str);
			
			//2.3
			str.Format( _T("%d"), pPar->m_col);
			pList->SetItemText(i, pos++, str);
		}
		
		else if (i == 2)
		{
			//2.2
			str.Format( _T("�ϲ���Ԫ�����") );
			pList->SetItemText(i, pos++, str);
			
			//2.3
			str.Format( _T("%d"), pPar->m_col);
			pList->SetItemText(i, pos++, str);
		}	

		MyList_SetListItemEdit(pList, i, EnableCol);
		//MyList_SetListItemBkColor(pList, i, 2, TAB_CLR_EDIT_BK);
	}

	
	
}

void CModeParMng::DisplayTabHeadLen(CListCtrl *pList) 
{	
	CModeParMng *pPar = this; 

	int		i,pos;
	CString	str;
	int     iRowNum, iColNum; 
	char	ItemName[20][30] = {"�к�", "��1������", "��2������", "����ʾ���*", "xxxx4"};
	//char	ItemName[20][30] = {"�к�", "����ʾ���*", "xxxx4"};
	int     ItemLen[20]      = {  50,     120,     120,		120,       80 };
	int     EnableCol = 3;
			
	ListCtrl_ClearAllColumn(pList);

	iRowNum = pPar->m_col;
	iColNum = 4;
	
	for (i=0; i<iColNum; i++)
	{
		str.Format("%s", ItemName[i]);
		pList->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen[i]);	
	}
	
	for (i=0; i<iRowNum; i++)
	{
		//1.
		str.Format("%3C", 'A'+i);
		pList->InsertItem(i, str);
		
		pos = 1;
		
		//2.
		str.Format( _T("%s"), pPar->m_ItemInfo[0][i]);
		pList->SetItemText(i, pos++, str);	
		
		//3.
		str.Format( _T("%s"), pPar->m_ItemInfo[1][i]);
		pList->SetItemText(i, pos++, str);	

		//4.
		str.Format( _T("%d"), pPar->m_ColLen[i]);
		pList->SetItemText(i, pos++, str);	
		
		MyList_SetListItemEdit(pList, i, EnableCol);
	}

}

void CModeParMng::DisplayTabItemData(CListCtrl *pList)
{
	CModeParMng *pPar = this; 

	int		i,j;
	CString	str;
	char    *pValue = NULL;
	int     iRowNum, iColNum;

	ListCtrl_ClearAllColumn(pList);
	MyList_RemoveAllListMark(pList);

	iRowNum = pPar->m_row;
	iColNum = pPar->m_col;
	
	for (i=0; i<iColNum+1; i++)
	{
		if (i==0)
		{
			str.Format( _T(" ") );
			pList->InsertColumn(i, str,   LVCFMT_LEFT, 50);	
		}
		else
		{
			str.Format("%C", 'A'+i-1);
			pList->InsertColumn(i, str,   LVCFMT_LEFT, pPar->m_ColLen[i-1]);	
		}
	
	}
	
	for (i=0; i<iRowNum; i++)
	{
		str.Format("%3d", i+1);
		pList->InsertItem(i, str);
		
		for (j=0; j<iColNum; j++)
		{
			str.Format( _T("%s"), pPar->m_ItemInfo[i][j]);
			pList->SetItemText(i, j+1, str);
			
			MyList_SetListItemEdit(pList, i, j+1);
		}
	}

	
}


void CModeParMng::DisplayTabItemFlag(CListCtrl *pList)		//��ʾ���ģ��_��Ԫ���־
{
	CModeParMng *pPar = this; 
	
	int		i,j;
	CString	str;
	char    *pValue = NULL;
	int     iRowNum, iColNum;
	
	ListCtrl_ClearAllColumn(pList);
	
	iRowNum = pPar->m_row;
	iColNum = pPar->m_col;
	
	for (i=0; i<iColNum+1; i++)
	{
		if (i == 0)
		{
			str.Format( _T(" "));
			pList->InsertColumn(i, str,   LVCFMT_LEFT, 50);	
		}
		else
		{
			str.Format("%C", 'A'+i-1);
			pList->InsertColumn(i, str,   LVCFMT_LEFT, pPar->m_ColLen[i-1]);	
		}
		
	}
	
	for (i=0; i<iRowNum; i++)
	{
		str.Format("%3d", i+1);
		pList->InsertItem(i, str);
		
		for (j=0; j<iColNum; j++)
		{
			str.Format( _T("%d"), pPar->m_ItemFlag[i][j]);
			pList->SetItemText(i, j+1, str);	
		}
	}
}

void CModeParMng::DisplayTabCellSrtCfg(CListCtrl *pList)		//��ʾ���ģ��_�ϲ���Ԫ��ṹ
{
	CModeParMng	*pPar = this; 
	StTabCell	*pTabCell = NULL;

	int		i, pos;
	CString	str;
	int     iRowNum, iColNum;
	char	ItemName[20][30] = {"���", "��ʼ�к�", "��ʼ�к�", "��ֹ�к�", "��ֹ�к�","����", "����"};
	int     ItemLen[20]      = {  50,     100,      100,       100,          100,       100,   100};
	
	ListCtrl_ClearAllColumn(pList);
	
	iRowNum = pPar->m_nTabCellCnt;
	iColNum = 5;
	
	for (i=0; i<iColNum; i++)
	{
		str.Format("%s", ItemName[i]);
		pList->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen[i]);	
	}
	
	for (i=0; i<iRowNum; i++)
	{
		pos = 1;
		pTabCell = &pPar->m_stTabCell[i];
		//1.
		str.Format("%3d", i+1);
		pList->InsertItem(i, str);
		
		//2.
		str.Format("%d", pTabCell->iBegRow);
		pList->SetItemText(i, pos, str);
		MyList_SetListItemEdit(pList, i, pos);
		pos++;
		
		//3.
		str.Format("%d", pTabCell->iBegCol);
		pList->SetItemText(i, pos, str);
		MyList_SetListItemEdit(pList, i, pos);
		pos++;
		
		//4.
		str.Format("%d", pTabCell->iEndRow);
		pList->SetItemText(i, pos, str);
		MyList_SetListItemEdit(pList, i, pos);
		pos++;
		
		//5.
		str.Format("%d", pTabCell->iEndCol);
		pList->SetItemText(i, pos, str);
		MyList_SetListItemEdit(pList, i, pos);
		pos++;	
		
		//6.
		//str.Format("%d", pTabCell->iRowNum);
		//pList->SetItemText(i, pos++, str);
		
		//7.
		//str.Format("%d", pTabCell->iColNum);
		//pList->SetItemText(i, pos, str);	
	}

}

void CModeParMng::DisplayTabCellSrt(CListCtrl *pList)		//��ʾ���ģ��_�ϲ���Ԫ��ṹ
{
	CModeParMng	*pPar = this; 
	StTabCell	*pTabCell = NULL;
	
	int		i, pos;
	CString	str;
	int     iRowNum, iColNum;
	char	ItemName[20][30] = {"���", "��ʼ�к�*", "��ʼ�к�*", "��ֹ�к�*", "��ֹ�к�*","����", "����"};
	int     ItemLen[20]      = {  50,     100,      100,       100,          100,       100,   100};
	
	ListCtrl_ClearAllColumn(pList);
	
	iRowNum = pPar->m_nTabCellCnt;
	iColNum = 7;
	
	for (i=0; i<iColNum; i++)
	{
		str.Format("%s", ItemName[i]);
		pList->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen[i]);	
	}
	
	for (i=0; i<iRowNum; i++)
	{
		pos = 1;
		pTabCell = &pPar->m_stTabCell[i];
		//1.
		str.Format("%3d", i+1);
		pList->InsertItem(i, str);
		
		//2.
		str.Format("%d", pTabCell->iBegRow);
		pList->SetItemText(i, pos, str);
		MyList_SetListItemEdit(pList, i, pos);
		pos++;
		
		//3.
		str.Format("%d", pTabCell->iBegCol);
		pList->SetItemText(i, pos, str);
		MyList_SetListItemEdit(pList, i, pos);
		pos++;
		
		//4.
		str.Format("%d", pTabCell->iEndRow);
		pList->SetItemText(i, pos, str);
		MyList_SetListItemEdit(pList, i, pos);
		pos++;
		
		//5.
		str.Format("%d", pTabCell->iEndCol);
		pList->SetItemText(i, pos, str);
		MyList_SetListItemEdit(pList, i, pos);
		pos++;	
		
		//6.
		str.Format("%d", pTabCell->iRowNum);
		pList->SetItemText(i, pos++, str);
		
		//7.
		str.Format("%d", pTabCell->iColNum);
		pList->SetItemText(i, pos, str);	
	}
	
}


//2017-2-14 V1.1.1 ��������
void CModeParMng::DisplayTabRowSrt(CListCtrl *pList)		
{
	CModeParMng  *pPar = this; 
	StTabRow     *pTabRow = NULL;
	
	int		i, pos;
	CString	str;
	int     iRowNum, iColNum;
	char	ItemName[20][30] = {"�к�", "��1������", "��2������", "��3������", "��4������", "��������", "�м��*"};
	int     ItemLen[20]      = { 100,      120,       120,    120, 120, 80,    120 };
	
	ListCtrl_ClearAllColumn(pList);

	iRowNum = pPar->m_row;
	iColNum = 7;
	
	for (i=0; i<iColNum; i++)
	{
		str.Format("%s", ItemName[i]);
		pList->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen[i]);	
	}
	
	for (i=0; i<iRowNum; i++)
	{
		pTabRow = &pPar->m_stTabRow[i];
		
		pos = 0;
		//1.
		str.Format("%3d", i+1);
		pList->InsertItem(i, str);

		str.Format( _T("%d"), pTabRow->iRowPos);
		pList->SetItemText(i, pos++, str);	
		
		//2.
		str.Format( _T("%s"), pPar->m_ItemInfo[i][0]);
		pList->SetItemText(i, pos, str);	
		MyList_SetListItemEdit(pList, i, pos);
		pos++;	
		
		//3.
		str.Format( _T("%s"), pPar->m_ItemInfo[i][1]);
		pList->SetItemText(i, pos, str);	
		MyList_SetListItemEdit(pList, i, pos);
		pos++;	

		//4.
		str.Format( _T("%s"), pPar->m_ItemInfo[i][2]);
		pList->SetItemText(i, pos, str);	
		MyList_SetListItemEdit(pList, i, pos);
		pos++;	

		//5.
		str.Format( _T("%s"), pPar->m_ItemInfo[i][3]);
		pList->SetItemText(i, pos, str);	
		MyList_SetListItemEdit(pList, i, pos);
		pos++;	


		//4.	
		str.Format( _T("%d"), pTabRow->bDataFlag);
		pList->SetItemText(i, pos++, str);
		
		//5.	
		if (pTabRow->bDataFlag == 0)
		{
			str.Format( _T("%s"), "");
		}
		else
		{
			if (strlen(pTabRow->szRowName) == 0)
			{
				if (strlen(pPar->m_ItemInfo[i][1]) == 0)
				{
					strcpy(pTabRow->szRowName, pPar->m_ItemInfo[i][0]);
				}
				else
				{
					strcpy(pTabRow->szRowName, pPar->m_ItemInfo[i][1]);
				}
				
			}
			str.Format( _T("%s"), pTabRow->szRowName);
			MyList_SetListItemEdit(pList, i, pos);
		}
		pList->SetItemText(i, pos, str);	
	
		pos++;
	}
}


void CModeParMng::DisplayTabColSrt(CListCtrl *pList)		
{
	CModeParMng  *pPar = this; 
	StTabCol     *pTabCol = NULL;
	
	int		i, pos;
	CString	str, strColumn;
	int     iRowNum, iColNum;
	char	ItemName[20][30] = {"�к�", "��1������", "��2������", "��������", "�м��*"};
	int     ItemLen[20]      = {  100,      120,       120,       80,       120 };
	
	ListCtrl_ClearAllColumn(pList);

	iRowNum = pPar->m_col;
	iColNum = 5;
	
	for (i=0; i<iColNum; i++)
	{
		str.Format("%s", ItemName[i]);
		pList->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen[i]);	
	}
	
	for (i=0; i<iRowNum; i++)
	{
		pTabCol = &pPar->m_stTabCol[i];
		
		pos = 0;
		//1.
		str.Format("%3C", 'A'+i);
		pList->InsertItem(i, str);

		str.Format( _T("%d"), pTabCol->iColPos);
		pList->SetItemText(i, pos++, str);
		
		//2.
		str.Format( _T("%s"), pPar->m_ItemInfo[0][i]);
		pList->SetItemText(i, pos, str);	
		MyList_SetListItemEdit(pList, i, pos);
		pos++;

		//3.
		str.Format( _T("%s"), pPar->m_ItemInfo[1][i]);
		pList->SetItemText(i, pos, str);	
		MyList_SetListItemEdit(pList, i, pos);
		pos++;	
		
		//4.	
		str.Format( _T("%d"), pTabCol->bDataFlag);
		pList->SetItemText(i, pos++, str);
		
		//5.	
		if (pTabCol->bDataFlag == 0)
		{
			str.Format( _T("%s"), "");
		}
		else
		{
			if (strlen(pTabCol->szColName) == 0)
			{
				strcpy(pTabCol->szColName, pPar->m_ItemInfo[0][i]);
			}
			str.Format( _T("%s"), pTabCol->szColName);
			MyList_SetListItemEdit(pList, i, pos);
		}
		pList->SetItemText(i, pos, str);
		pos++;
	}
}


void CModeParMng::DisplayTabOutDataSrt(CListCtrl *pList)		//��ʾ���ģ��_������ݽṹ	
{
	CModeParMng  *pPar = this; 
	StTabData    *pTabData = NULL;
	StTabRow  *pTabRow = NULL;
	StTabCol  *pTabCol = NULL;
	CEditableListCtrl *pEditList = (CEditableListCtrl *)pList;
	
	int		i, pos;
	CString	str;
	int     iRowNum, iColNum;
	char	ItemName[20][30] = {"���", "���ݱ�_���ֶ�����",	"�к�",					"�м��",  
								"�к�", "�м��",				"���ݱ�_���ֶ�����",	"��������",
								"��������*"
								};
	int     ItemLen[20]      = {  50,     140,					 60,			100,	 
									60,		100,				180,           100,
									100};

	char szDataType[XLS_MAX_LEN] = {0,};
	
	ListCtrl_ClearAllColumn(pList);
	
	iRowNum = pPar->m_nDataCnt;
	iColNum = 7+1;


	//pEditList->BindListToItem(8, DATA_TYPE_KEY);   //��������

	
	for (i=0; i<iColNum; i++)
	{
		str.Format("%s", ItemName[i]);
		pList->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen[i]);	
	}
	
	for (i=0; i<iRowNum; i++)
	{
		pTabData = &pPar->m_stTabData[i];
		
		//1.
		str.Format("%3d", i+1);
		pList->InsertItem(i, str);
		
		pos = 1;
		//2.
		str.Format( _T("%s"), pTabData->szDbColName);
		pList->SetItemText(i, pos++, str);	
		
		//3.	
		str.Format( _T("%d"), pTabData->iBegRow);
		pList->SetItemText(i, pos++, str);
		
		//4.
		pTabRow = &m_stTabRow[pTabData->iBegRow-1];
		str.Format( _T("%s"), pTabRow->szRowName);
		pList->SetItemText(i, pos++, str);	
		
		//5.	
		str.Format( _T("%d"), pTabData->iBegCol);
		pList->SetItemText(i, pos++, str);	
		
		//6.
		pTabCol = &m_stTabCol[pTabData->iBegCol-1];
		str.Format( _T("%s"), pTabCol->szColName);
		pList->SetItemText(i, pos++, str);	
		
		//7.
		if ( (strlen(pTabRow->szRowName)!=0) && (strlen(pTabCol->szColName) != 0) )
		{
			str.Format( _T("%s_%s"), pTabRow->szRowName, pTabCol->szColName);
			strcpy(pTabData->szOutDataName, str.GetBuffer(0));
		}
		else
		{
			str.Format( _T("%s"), pTabData->szOutDataName);
		}
		
		pList->SetItemText(i, pos, str);	
		//MyList_SetListItemEdit(pList, i, pos);
		pos++;

		//8.��������
		memset(szDataType, 0, XLS_MAX_LEN);
		pPar->GetDataTypeStr(pTabData->iDataType, szDataType);
		str = szDataType;
		
		pList->SetItemText(i, pos, str);	
		pos++;

	}
}


void CModeParMng::DisplayTabAlarmSrt(CListCtrl *pList)		//��ʾ���ģ��_���ݱ�������
{
	CModeParMng  *pPar = this; 
	StTabData    *pTabData  = NULL;
	StTabAlarm   *pTabAlarm = NULL;
	StTabRow  *pTabRow = NULL;
	StTabCol  *pTabCol = NULL;
	char       szJudgeDesc[XLS_MAX_LEN] ={0,};
	
	int		i, pos;
	CString	str;
	int     iRowNum, iColNum;
	char	ItemName[20][30] = {"���",		"���ݱ�_���ֶ�����",  "���ݱ�_���ֶ�����", "��������", "����־*",  
								"��⹫ʽ*", "ָ��ֵx1*",			  "ָ��ֵx2*",
								};
	int     ItemLen[20]      = {  50,		140,					180,		100,	100, 
								100,		100,					100 
								};
	CEditableListCtrl *pEditList = (CEditableListCtrl *)pList; 

	int    bEnableEdit = 0;
	char   szDataType[XLS_MAX_LEN] = {0,};

	ListCtrl_ClearAllColumn(pList);
	
	iRowNum = pPar->m_nDataCnt;
	iColNum = 8;
		
	for (i=0; i<iColNum; i++)
	{
		str.Format("%s", ItemName[i]);
		pList->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen[i]);	
	}
	
	pEditList->BindListToItem(5,CALC_SIGN_KEY);

	pEditList->BindListToItem(4,ALA_SWITCH_KEY);
	
	for (i=0; i<iRowNum; i++)
	{
		pTabData = &pPar->m_stTabData[i];
		pTabAlarm= &pPar->m_stTabAlarm[i];
		
		//1.
		str.Format("%3d", i+1);
		pList->InsertItem(i, str);
		
		pos = 1;
		//2.
		str.Format( _T("%s"), pTabData->szDbColName);
		pList->SetItemText(i, pos++, str);	
		
		//3.	
		str.Format( _T("%s"), pTabData->szOutDataName);
		pList->SetItemText(i, pos++, str);


		//4.��������
		bEnableEdit = 1;


		memset(szDataType, 0, XLS_MAX_LEN);
		pPar->GetDataTypeStr(pTabData->iDataType, szDataType);
		str = szDataType;

		pList->SetItemText(i, pos++, str);

		
		//5.
		str.Format( _T("%d"), pTabAlarm->bCheckFlag);
		pList->SetItemText(i, pos, str);
		if (bEnableEdit != 0)
		{
			MyList_SetListItemEdit(pList, i, pos);
		}
		pos++;	
		
		//6.	
		memset(szJudgeDesc, 0, XLS_MAX_LEN);
		GetTabAlarmJudgeDescFormType(pTabAlarm->nJudgeType, szJudgeDesc);
		strcpy(pTabAlarm->szJudgeDesc, szJudgeDesc);
		str.Format( _T("%s"), pTabAlarm->szJudgeDesc);
		pList->SetItemText(i, pos, str);

		if (bEnableEdit != 0)
		{
			MyList_SetListItemEdit(pList, i, pos);
		}
		pos++;	
		
		//7.
		str.Format( _T("%s"), pTabAlarm->szTarget1);
		pList->SetItemText(i, pos, str);
		
		if (bEnableEdit != 0)
		{
			MyList_SetListItemEdit(pList, i, pos);
		}
		pos++;

		//8.
		str.Format( _T("%s"), pTabAlarm->szTarget2);
		pList->SetItemText(i, pos, str);
		
		if (bEnableEdit != 0)
		{
			MyList_SetListItemEdit(pList, i, pos);
		}
		pos++;	

	}
}

//---------------------------------------------------------------------------------
void CModeParMng::DisplayProdHisChk(CListCtrl *pList)		//��Ʒͳ��_��ʷ��ֵ����
{
	CModeParMng  *pPar = this; 
	StTabData    *pTabData  = NULL;
	StTabHisChk  *pTabHisChk = NULL;

	char       szJudgeDesc[XLS_MAX_LEN] ={0,};
	
	int		i, pos;
	CString	str;
	int     iRowNum, iColNum;
	char	ItemName[20][30] = {"���",		"���ݱ�_���ֶ�����",  "���ݱ�_���ֶ�����", "����־",  
								 "��ʷ��Сֵ",			  "��ʷ��Сֵ",
	};
	int     ItemLen[20]      = {  50,		140,					180,		100,	 
								100,		100,					100 
	};
	CEditableListCtrl *pEditList = (CEditableListCtrl *)pList; 
	
	ListCtrl_ClearAllColumn(pList);
	
	iRowNum = pPar->m_nDataCnt;
	iColNum = 6;
	
	for (i=0; i<iColNum; i++)
	{
		str.Format("%s", ItemName[i]);
		pList->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen[i]);	
	}
		
	for (i=0; i<iRowNum; i++)
	{
		pTabData   = &pPar->m_stTabData[i];
		pTabHisChk = &pPar->m_stTabHisChk[i];
		
		//1.
		str.Format("%3d", i+1);
		pList->InsertItem(i, str);
		
		pos = 1;
		//2.
		str.Format( _T("%s"), pTabData->szDbColName);
		pList->SetItemText(i, pos++, str);	
		
		//3.	
		str.Format( _T("%s"), pTabData->szOutDataName);
		pList->SetItemText(i, pos++, str);
		
		//4.
		str.Format( _T("%d"), pTabHisChk->bHisChkFlag);
		pList->SetItemText(i, pos, str);
		//zttest
		//MyList_SetListItemEdit(pList, i, pos);
		pos++;	
		
		//5.	
		str.Format( _T("%s"), pTabHisChk->szHisValMin);
		pList->SetItemText(i, pos, str);
		//zttest
		//MyList_SetListItemEdit(pList, i, pos);
		pos++;	
		
		//6.
		str.Format( _T("%s"), pTabHisChk->szHisValMax);
		pList->SetItemText(i, pos, str);
		//zttest
		//MyList_SetListItemEdit(pList, i, pos);
		pos++;	
	}
}


//---------------------------------------------------------------------------------
void CModeParMng::DisplayProdAppData(CListCtrl *pList)		//���Խ��_������Ϣ
{
	CModeParMng  *pPar = this; 
	StTabData    *pTabData  = NULL;
	StOutAppData  *pOutAppData = NULL;

	char       szJudgeDesc[XLS_MAX_LEN] ={0,};

	int		i, pos;
	CString	str;
	int     iRowNum, iColNum;
	char	ItemName[20][30] = {"���",			"���ݱ�_���ֶ�����",  "���ݱ�_���ֶ�����", "��������",  
							    "����ԭʼ����",	  "��������",			"�����Ա",			"���ʱ��"
	};
	int     ItemLen[20]      = {  50,		120,			120,		70,	 
								 120,		280,			80 ,	110
	};
	CEditableListCtrl *pEditList = (CEditableListCtrl *)pList; 

	ListCtrl_ClearAllColumn(pList);

	iRowNum = pPar->m_nOutAppDataCnt;
	iColNum = 8;

	for (i=0; i<iColNum; i++)
	{
		str.Format("%s", ItemName[i]);
		pList->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen[i]);	
	}

	for (i=0; i<iRowNum; i++)
	{
		pOutAppData = &pPar->m_stOutAppData[i];

		pos = pOutAppData->nTabDataPos;
		pTabData   = &pPar->m_stTabData[pos];	

		//1.
		str.Format("%3d", i+1);
		pList->InsertItem(i, str);

		pos = 1;
		//2.
		str.Format( _T("%s"), pTabData->szDbColName);
		pList->SetItemText(i, pos++, str);	

		//3.	
		str.Format( _T("%s"), pTabData->szOutDataName);
		pList->SetItemText(i, pos++, str);

		//4.
		if (pOutAppData->nAppendixType == 1)
		{
			str= _T("��Ƭ����");
		}
		else if (pOutAppData->nAppendixType == 2)
		{
			str= _T("��Ƶ����");
		}
		else if (pOutAppData->nAppendixType == 3)
		{
			str= _T("�ļ�����");
		}
		else
		{
			str= _T("Errδ���������");
		}	
		pList->SetItemText(i, pos, str);
		pos++;	

		//5.	
		str.Format( _T("%s"), pOutAppData->szSrcFileName);
		pList->SetItemText(i, pos, str);
		pos++;	

		//6.
		str.Format( _T("%s"), pOutAppData->szDesFileName);
		pList->SetItemText(i, pos, str);
		pos++;	

		//7.	
		str.Format( _T("%s"), pOutAppData->szUpUsr);
		pList->SetItemText(i, pos, str);
		pos++;	

		//8.
		str.Format( _T("%s"), pOutAppData->szUpTime);
		pList->SetItemText(i, pos, str);
		pos++;	
	}
}


//---------------------------------------------------------------------------------

//���ݴ洢���
//==============================================================================
int CModeParMng::SaveTabSizeInfo(CListCtrl *pList)
{
	int		i;
	int		nCnt, nColPos;
	CString str;
	char	ItemVal[TMP_MAX_CNT][100] = {0,};
	int     nRow,nCol, nCellCnt, nTemp, pos;

	nColPos = 2;
	nCnt = 3;
	for (i=0; i<nCnt; i++)
	{
		str = pList->GetItemText(i, nColPos);
		strcpy(ItemVal[i], str.GetBuffer(0));
	}

	pos = 0;
	nRow = atoi(ItemVal[pos++]);
	if ((nRow <= 0) || (nRow > XLS_MAX_ROW))
	{
		str.Format(_T("����,������Χ[1, %d], nRow=%d,"), nRow, XLS_MAX_ROW);
		AfxMessageBox(str);
		return 0;
	}

	nCol = atoi(ItemVal[pos++]);
	if ((nCol <= 0) || (nCol > XLS_MAX_COL))
	{
		str.Format(_T("����,������Χ[1, %d], nCol=%d,"), nRow, XLS_MAX_ROW);
		AfxMessageBox(str);
		return 0;
	}

	nTemp = nRow*nCol;

	nCellCnt = atoi(ItemVal[pos++]);
	if ((nCellCnt < 0) || (nCellCnt > TAB_MAX_CELL_CNT))
	{
		str.Format(_T("����, ������Χ[0, %d], nCellCnt=%d,"), nRow, TAB_MAX_CELL_CNT);
		AfxMessageBox(str);
		return 0;
	}

	m_row = nRow;
	m_col = nCol;
	m_nTabCellCnt = nCellCnt;

	for (i=0; i<nCol; i++)
	{
		if (m_ColLen[i] < MIN_COL_WIDTH)
		{
			m_ColLen[i] = DEF_COL_WIDTH;
		}
	}

	return 1;
}

int CModeParMng::SaveTabHeadLen(CListCtrl *pList)
{
	int		i;
	int		nCnt, nColPos;
	CString str;
	int     nCellWidth;
	
	nColPos = 3;
	nCnt = m_col;
	for (i=0; i<nCnt; i++)
	{
		str = pList->GetItemText(i, nColPos);
		nCellWidth = atoi(str.GetBuffer(0));
		if ((nCellWidth < MIN_COL_WIDTH) || (nCellWidth > MAX_COL_WIDTH) )
		{
			str.Format(_T("��%d��,����������Χ[%d, %d], nWidth=%d,"), i+1, MIN_COL_WIDTH, MAX_COL_WIDTH, nCellWidth);
			AfxMessageBox(str);
			return 0;
		}
	}

	for (i=0; i<nCnt; i++)
	{
		str = pList->GetItemText(i, nColPos);
		nCellWidth = atoi(str.GetBuffer(0));
		m_ColLen[i] = nCellWidth;
	}
	
	return 1;
}


int CModeParMng::SaveTabItemData(CListCtrl *pList)
{
	int		i, j;
	CString str;
	char    *pData = NULL;
		
	for (i=0; i<m_row; i++)
	{
		for (j=0; j<m_col; j++)
		{
			str = pList->GetItemText(i, j+1);
			str.TrimLeft();
			str.TrimRight();
			pData = m_ItemInfo[i][j];
			memset(pData, 0, XLS_MAX_LEN);
			strcpy(pData, str.GetBuffer(0));
		}
	}

	GetItemFlagFromData( );
	
	return 1;
}


int CModeParMng::SaveTabCellSrt(CListCtrl *pList)
{
	int		i, j, nCnt = 0;;
	CString str;
	char    *pData = NULL;
	int 	ItemVal[10] = {0,};
	int     bFlag = 1;
	int     nRow, nCol;
	int     iBegRow, iBegCol, iEndRow, iEndCol;
	StTabCell  *pTabCell = NULL;

	nRow = m_row;
	nCol = m_col;
	
	for (i=0; i<m_nTabCellCnt; i++)
	{
		for (j=0;j<4; j++)
		{
			str = pList->GetItemText(i, j+1);
			str.TrimLeft();
			str.TrimRight();
			ItemVal[j] = atoi( str.GetBuffer(0) );	
		}
	
		iBegRow = ItemVal[0];
		iBegCol = ItemVal[1];
		iEndRow = ItemVal[2];
		iEndCol = ItemVal[3];
		
		//1.
		if ( (iBegRow < 1) || (iBegRow > nRow) )
		{
			str.Format(_T("Error, pos=%d, iBegRow=%d, Out of Range Min=1 or Max=%d!"), 
				i+1, iBegRow, nRow);
			AfxMessageBox(str);
			bFlag = 0;
			break;
		}
		
		//2.
		if ( (iBegCol < 1) || (iBegCol > nCol) )
		{
			str.Format(_T("Error, pos=%d, iBegCol=%d, Out of Range Min=1 or Max=%d!"), 
				i+1, iBegCol, nCol);
			AfxMessageBox(str);
			bFlag = 0;
			break;
		}
		
		//3.
		if ( (iEndRow < 1) || (iEndRow > nRow) )
		{
			str.Format(_T("Error, pos=%d, iEndRow=%d, Out of Range Min=1 or Max=%d!"), 
				i+1, iEndRow, nRow);
			AfxMessageBox(str);
			bFlag = 0;
			break;
		}
		
		//4.
		if ( (iEndCol <1 ) || (iEndCol > nCol) )
		{
			str.Format(_T("Error, pos=%d, iEndCol=%d, Out of Range Min=1 or Max=%d!"), 
				i+1, iEndCol, nCol);
			AfxMessageBox(str);
			bFlag = 0;
			break;
		}
		
		//5.
		if (iEndRow < iBegRow)
		{
			str.Format(_T("Error, pos=%d, iEndRow < iBegRow,  iEndRow=%d, iBegRow=%d !"), 
				i+1, iEndRow, iBegRow);
			bFlag = 0;
			break;
		}
		
		//6.
		if (iEndCol < iBegCol)
		{
			str.Format(_T("Error, pos=%d, iEndCol < iBegCol,  iEndCol=%d, iBegCol=%d !"), 
				i+1, iEndCol, iBegCol);
			AfxMessageBox(str);
			bFlag = 0;
			break;
		}
			
		
	}
	

	if (bFlag == 0)
	{
		return bFlag;
	}

	
	for (i=0; i<m_nTabCellCnt; i++)
	{
		pTabCell = &m_stTabCell[i];

		for (j=0;j<4; j++)
		{
			str = pList->GetItemText(i, j+1);
			str.TrimLeft();
			str.TrimRight();
			ItemVal[j] = atoi( str.GetBuffer(0) );	
		}
		
		iBegRow = ItemVal[0];
		iBegCol = ItemVal[1];
		iEndRow = ItemVal[2];
		iEndCol = ItemVal[3];
		
		pTabCell->iBegRow = iBegRow;
		pTabCell->iBegCol = iBegCol;
		pTabCell->iEndRow = iEndRow;
		pTabCell->iEndCol = iEndCol;		
	}

	CalculateTabCellSize();
	
	return bFlag;
}



int CModeParMng::SaveTabRowSrt(CListCtrl *pList)
{
	int		i, j, bFlag = 1;
	int		nCnt, nColPos;
	CString str;
	char	ItemVal[TMP_MAX_CNT][100] = {0,};
	int     ItemFlg[TMP_MAX_CNT] = {0,};
	StTabRow *pTabRow = NULL;
	int     bSameFlag = 0;
	char    *pSrc, *pDes;
	
	//2017-2-14 V1.1.1 �������� 4->4+2
	nColPos = 4+2;
	nCnt = m_row;
  
	for (i=0; i<nCnt; i++)
	{
		pTabRow = &m_stTabRow[i];
		str = pList->GetItemText(i, nColPos);
		str.TrimLeft();
		str.TrimRight();
		ItemFlg[i] = pTabRow->bDataFlag;
		if (ItemFlg[i] != 0)
		{
			if (strlen(str.GetBuffer(0)) == 0)
			{
				str.Format(_T("Error, pos=%d, iCol=%d, It is NULL!"), 
					i+1, nColPos+1);
				AfxMessageBox(str);
				bFlag = 0;
				break;
			}
			strcpy(ItemVal[i], str.GetBuffer(0));
		}
	}

	if (bFlag == 0)
	{
		//return 0;
	}

	bSameFlag = 0;
	for (i=0; i<nCnt-1; i++)
	{
		pSrc = ItemVal[i];
		for (j=i+1; j<nCnt; j++)
		{
			pDes = ItemVal[j];
			if ( (strlen(pSrc) != 0) && (strlen(pDes) != 0) )
			{
				if (strcmp(pSrc, pDes) == 0)
				{
					str.Format(_T("Error, Row1=%d, Row2=%d, Name=%s, Name Same! "), 
						i+1, j+1, pSrc);
					AfxMessageBox(str);
					bSameFlag = 1;
					break;
				}
			}
		}

		if (bSameFlag != 0)
		{
			break;
		}
	}

	if (bSameFlag != 0)
	{
		//return 0;
	}

	for (i=0; i<nCnt; i++)
	{
		pTabRow = &m_stTabRow[i];
		str = pList->GetItemText(i, nColPos);
		ItemFlg[i] = pTabRow->bDataFlag;
		if (ItemFlg[i] == 0)
		{
			memset(pTabRow->szRowName, 0, XLS_MAX_LEN);
		}
		else
		{
			strcpy(pTabRow->szRowName, str.GetBuffer(0));
		}
	}

	return 1;
}
	
int CModeParMng::SaveTabColSrt(CListCtrl *pList)
{
	int		i, j, bFlag = 1;
	int		nCnt, nColPos;
	CString str;
	char	ItemVal[TMP_MAX_CNT][100] = {0,};
	int     ItemFlg[TMP_MAX_CNT] = {0,};
	StTabCol *pTabCol = NULL;
	int     bSameFlag = 0;
	char    *pSrc, *pDes;
	
	nColPos = 4;
	nCnt = m_col;
	
	for (i=0; i<nCnt; i++)
	{
		pTabCol = &m_stTabCol[i];
		str = pList->GetItemText(i, nColPos);
		str.TrimLeft();
		str.TrimRight();
		ItemFlg[i] = pTabCol->bDataFlag;
		if (ItemFlg[i] != 0)
		{
			if (strlen(str.GetBuffer(0)) == 0)
			{
				str.Format(_T("Error, pos=%d, iCol=%d, It is NULL!"), 
					i+1, nColPos+1);
				AfxMessageBox(str);
				bFlag = 0;
				break;
			}
			strcpy(ItemVal[i], str.GetBuffer(0));
		}
	}
	
	if (bFlag == 0)
	{
		//return 0;
	}
	
	bSameFlag = 0;
	for (i=0; i<nCnt-1; i++)
	{
		pSrc = ItemVal[i];
		for (j=i+1; j<nCnt; j++)
		{
			pDes = ItemVal[j];
			if ( (strlen(pSrc) != 0) && (strlen(pDes) != 0) )
			{
				if (strcmp(pSrc, pDes) == 0)
				{
					str.Format(_T("Error, Row1=%d, Row2=%d, Name=%s, Name Same! "), 
						i+1, j+1, pSrc);
					AfxMessageBox(str);
					bSameFlag = 1;
					break;
				}
			}
		}
		
		if (bSameFlag != 0)
		{
			break;
		}
	}
	
	if (bSameFlag != 0)
	{
		//return 0;
	}
	
	for (i=0; i<nCnt; i++)
	{
		pTabCol = &m_stTabCol[i];
		str = pList->GetItemText(i, nColPos);
		ItemFlg[i] = pTabCol->bDataFlag;
		if (ItemFlg[i] == 0)
		{
			memset(pTabCol->szColName, 0, XLS_MAX_LEN);
		}
		else
		{
			strcpy(pTabCol->szColName, str.GetBuffer(0));
		}
	}

	return 1;
}

int CModeParMng::SaveTabOutDataSrt(CListCtrl *pList)
{
/*	int		i, j, bFlag = 1;
	int		nCnt, nColPos;
	CString str;
	char	ItemVal[TMP_MAX_CNT][100] = {0,};
	int     ItemFlg[TMP_MAX_CNT] = {0,};
	StTabData    *pTabData = NULL;
	int     bSameFlag = 0;
	char    *pSrc, *pDes;

	nColPos = 8;
	nCnt = m_nDataCnt;

	for (i=0; i<nCnt; i++)
	{
		pTabData = &m_stTabData[i];
		str = pList->GetItemText(i, nColPos);
		str.TrimLeft();
		str.TrimRight();
		if (strcmp(str.GetBuffer(0), TAB_DATA_TYPE_FLOAT) == 0)
		{
			pTabData->iDataType = datatype_float;
		}
		else if (strcmp(str.GetBuffer(0), TAB_DATA_TYPE_STRING) == 0)
		{
			pTabData->iDataType = datatype_string;
		}
		else
		{
			pTabData->iDataType = datatype_float;
		}
	}
*/
	return 1;
}


int CModeParMng::SaveTabAlarmSrt(CListCtrl *pList)
{
	int		i, j, bFlag = 1;
	int		nCnt, nColPos;
	CString str;
	char	ItemVal[TMP_MAX_CNT][100] = {0,};
	int     ItemFlg[TMP_MAX_CNT] = {0,};
	StTabAlarm *pTabAlarm = NULL;
	int     bSameFlag = 0;
	//char    *pSrc, *pDes;
	
	nColPos = 3+1;
	nCnt = m_nDataCnt;
	
	for (i=0; i<nCnt; i++)
	{
		pTabAlarm = &m_stTabAlarm[i];
		for (j=0; j<4; j++)
		{
			str = pList->GetItemText(i, nColPos+j);
			str.TrimLeft();
			str.TrimRight();
			if (j == 0)
			{
				pTabAlarm->bCheckFlag = atoi(str.GetBuffer(0));
			}
			else if (j == 1)
			{
				strcpy(pTabAlarm->szJudgeDesc, str.GetBuffer(0));
				pTabAlarm->nJudgeType = GetTabAlarmJudgeTypeFromDesc(str.GetBuffer(0));	
			}
			else if (j == 2)
			{
				strcpy(pTabAlarm->szTarget1, str.GetBuffer(0));
			}
			else
			{
				strcpy(pTabAlarm->szTarget2, str.GetBuffer(0));
			}
		}
	}
	

	return 1;

}


int CModeParMng::SaveProdHisChk(CListCtrl *pList)			//��Ʒͳ��_��ʷ��ֵ����
{
	int		i, j, bFlag = 1;
	int		nCnt, nColPos;
	CString str;
	char	ItemVal[TMP_MAX_CNT][100] = {0,};
	int     ItemFlg[TMP_MAX_CNT] = {0,};
	StTabHisChk *pTabHisChk = NULL;
	int     bSameFlag = 0;
	//char    *pSrc, *pDes;
	double fVal1, fVal2;

	nColPos = 3;
	nCnt = m_nDataCnt;

	if (nCnt == 0)
	{
		return 0;
	}

	for (i=0; i<nCnt; i++)
	{
		pTabHisChk = &m_stTabHisChk[i];
		for (j=0; j<3; j++)
		{
			str = pList->GetItemText(i, nColPos+j);
			str.TrimLeft();
			str.TrimRight();
			if (j == 0)
			{
				pTabHisChk->bHisChkFlag = atoi(str.GetBuffer(0));
			}
			else if (j == 1)
			{
				strcpy(pTabHisChk->szHisValMin, str.GetBuffer(0));
			}
			else if (j == 2)
			{
				strcpy(pTabHisChk->szHisValMax, str.GetBuffer(0));

				if (pTabHisChk->bHisChkFlag != 0)
				{	
					fVal1 = atof(pTabHisChk->szHisValMin);
					fVal2 = atof(pTabHisChk->szHisValMax);

					if (fVal1 > fVal2)
					{
						str.Format(_T("���ò�������:��%d��,��ֵ��Сֵ%.2f, ���ڼ�ֵ���ֵ%.2f!"), i+1, fVal1, fVal2);
						AfxMessageBox(str);
						return 0;
					}
					pTabHisChk->fHisValMin = atof(pTabHisChk->szHisValMin);
					pTabHisChk->fHisValMax  = atof(pTabHisChk->szHisValMax);

				}
			}


		}
	}

	return 1;

}


//Ŀ¼��
//================================================================================
void CModeParMng::InitTree_TabStruct(CTreeCtrl *pTree)		//Ŀ¼��_ģ��ṹ
{
	HTREEITEM	hRoot0, hRoot1;
	CString     strItem;
	
	pTree->DeleteAllItems();

	//[1].����ģ��Ŀ¼��	
	hRoot0  = MyInsertTree(pTree, TREE_NAME_TAB_SRT_CFG,	TVI_ROOT, NULL, 0);	
	
		//1.���ߴ�
		hRoot1	= MyInsertTree(pTree, TREE_NAME_TAB_SIZE_INFO, hRoot0, Tab_SizeInfo, 1);
		
		//2.��Ԫ���п��
		hRoot1	= MyInsertTree(pTree, TREE_NAME_TAB_HEAD_LEN, hRoot0, Tab_HeadLen, 1);

		//3.��Ԫ������
		hRoot1	= MyInsertTree(pTree, TREE_NAME_TAB_ITEM_DATA, hRoot0, Tab_ItemData, 1);		

	if (g_bDebug != 0)
	{
		//4.��Ԫ���־
		hRoot1	= MyInsertTree(pTree, TREE_NAME_TAB_ITEM_FLAG, hRoot0, Tab_ItemFlag, 1);
	}

		//5.�ϲ���Ԫ��ṹ
		hRoot1	= MyInsertTree(pTree, TREE_NAME_TAB_CELL_SRT, hRoot0, Tab_CellSrt, 1);	

	pTree->Expand(hRoot0, TVM_EXPAND);

	//[2]���ģ��_��������
	hRoot0  = MyInsertTree(pTree, TREE_NAME_TAB_DATA_CFG,	TVI_ROOT, NULL, 0);	

		//5.�м�ƽṹ
		hRoot1	= MyInsertTree(pTree, TREE_NAME_TAB_ROW_SRT, hRoot0, Tab_RowSrt, 1);		
		
		//6.�м�ƽṹ
		hRoot1	= MyInsertTree(pTree, TREE_NAME_TAB_COL_SRT, hRoot0, Tab_ColSrt, 1);
		
		//7.���ݽṹ����
		hRoot1	= MyInsertTree(pTree, TREE_NAME_TAB_DATA_SRT, hRoot0, Tab_DataSrt, 1);
	
	pTree->Expand(hRoot0, TVM_EXPAND);

	//[3]�����¼ģ��_��������
	hRoot0  = MyInsertTree(pTree, TREE_NAME_TAB_ALARM_CFG,	TVI_ROOT, NULL, 0);	

		//8.���ݱ�������
		hRoot1	= MyInsertTree(pTree, TREE_NAME_TAB_ALARM_SRT, hRoot0, Tab_AlarmSrt, 1);
		
	pTree->Expand(hRoot0, TVM_EXPAND);

}

void CModeParMng::InitTree_TabResult(CTreeCtrl *pTree)		//Ŀ¼��_���Խ��
{
	HTREEITEM	hRoot0, hRoot1;
	CString     strItem;
	
	pTree->DeleteAllItems();
	
	//2.��Ʒ��ʷ��ֵ��Ϣ
	//----------------------------------------------------------
	hRoot0  = MyInsertTree(pTree, TREE_NAME_TAB_HIS_CFG,	TVI_ROOT, NULL, 0);	
	
		//2.1��Ʒ��ʷ��ֵ��Ϣ
		hRoot1	= MyInsertTree(pTree, TREE_NAME_TAB_HIS_INFO, hRoot0, Prod_HisChk, 1);
	
	
	pTree->Expand(hRoot0, TVM_EXPAND);
}

//-----------------------------------------------------------------------------------------------
//ListCtrl��ʾ��غ���
int CModeParMng::MyList_SetListItemEdit(CListCtrl *pList, int row, int col)					//���õ�Ԫ��ɸ���
{
	CEditableListCtrl *pEditList = (CEditableListCtrl*) pList;
	pEditList->SetEditable(FALSE);
	pEditList->AddEditCell(row,col);
	//pEditList->EnableEditButton(TRUE);
	return 1;
}

int CModeParMng::MyList_SetListItemBkColor(CListCtrl *pList, int row, int col, COLORREF bkColor)	//���õ�Ԫ���ʶ
{
	CEditableListCtrl *pEditList = (CEditableListCtrl*) pList;
	pEditList->SetItemColor(row, col, bkColor);
	return 1;
}

int CModeParMng::MyList_ResetListItemBkColor(CListCtrl *pList, int row, int col)					//���õ�Ԫ���ʶ
{
	CEditableListCtrl *pEditList = (CEditableListCtrl*) pList;
	pEditList->ResetItemColor(row, col);
	return 1;
}

//ListCtrl��ʾ��غ���
int CModeParMng::MyList_RemoveAllListMark(CListCtrl *pList)								//����б����б��
{	
	CEditableListCtrl *pEditList = (CEditableListCtrl*) pList;
	pEditList->RemoveAllEditCell();
	pEditList->ResetAllItemColor();
	return 1;
}

int CModeParMng::MyList_SetListEdit(CListCtrl *pList, BOOL bEdit)
{	
	CEditableListCtrl *pEditList = (CEditableListCtrl*) pList;
	pEditList->SetEditable(bEdit);
	return 1;
}


//-----------------------------------------------------------------------------------------------
int CModeParMng::CalculateFetchProgress( )
{
	int ret = 0;
	int i;
	int nSum, nCnt;
	CString str;
	StOutTestData *pStOutTestData = NULL;

	if (m_nModeType == mode_normal)
	{
		nSum = m_nDataCnt;
	}
	else if (m_nModeType == mode_rowvar)
	{
		nSum = m_nMulDataCnt;
	}
	
	nCnt = 0;
	for (i=0; i<nSum; i++)
	{
		pStOutTestData = &m_stOutTestData[i];
		str = pStOutTestData->szOutData;
		if ( strlen(str.GetBuffer(0)) > 0 )
		{
			str = str.TrimLeft();
			str = str.TrimRight();
			if ( strlen(str.GetBuffer(0)) > 0 )
			{
				nCnt++;
			}
		}
	}

	//
	m_nFetchCnt = nCnt;
	m_nFetchSum = nSum;

	m_nFetchPercent = nCnt*100 / nSum;
	if (nSum == nCnt)
	{
		//if (m_bFetchFinished == 0)
		{
			memset(m_szFetchSaveTime, 0, 30);
			GetSysDateTime(m_szFetchSaveTime);
		}
		m_bFetchFinished = 1;
	}
	else
	{
		m_bFetchFinished = 0;
	}
	
	return ret;
}


//Excel����
//=================================================================================================
int CModeParMng::GetExcelCalModeResult(char *szExcelCalModeName)		//��ȡ����������
{
	int  bFileExist = 0, bFlag;
	char szTmpExcelCalModeName[MAX_PATH] = {0,};
	CString str, strTmpFileName;
	int  ret = 0;

	if (szExcelCalModeName == NULL)
	{
		AfxMessageBox( _T("Err:�ļ�����Ϊ��!") );
		return 0;
	}

	bFileExist = PubFun_IsFileExist(szExcelCalModeName);
	if (bFileExist == 0)
	{
		str.Format( _T("Err:ԭ�ļ�������, FileName=%s"), szExcelCalModeName);
		return 0;
	}

	//strTmpFileName.Format( _T("%s\\tempCal.xlsx"), g_WorkPath);

	strTmpFileName.Format( _T("c:\\tempCal.xlsx") );
	strcpy(szTmpExcelCalModeName, strTmpFileName.GetBuffer(0));

	bFlag = CopyFile(szExcelCalModeName, szTmpExcelCalModeName, 0);

	if (bFlag == 0)
	{
		str.Format( _T("Err:�ļ�����ʧ��! SrcFileName=%s"), szExcelCalModeName);
		AfxMessageBox(str);
		return 0;
	}

	ret = SetExcelCalModeInputNum(szTmpExcelCalModeName);
	if (ret == 0)
	{
		AfxMessageBox("дģ����������ʧ��!");
		return 0;
	}

	ret = GetExcelCalModeCalulateNum(szTmpExcelCalModeName);
	if (ret == 0)
	{
		AfxMessageBox("��ģ�������ʧ��!");
		return 0;
	}

	//::DeleteFile(szExcelCalModeName);

	return 1;
}

int CModeParMng::SetExcelCalModeInputNum(char *szExcelTmpModeName)		//��������������
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
	Range		usedRange; 
	COleVariant vResult;

	int			i, j, row, col, pos;
	CString     str, strName, strCell, strBeg, strEnd, strSheetName;
	int tick;

	CModeParMng *pPar = this;
	char *fileName = NULL;
	int   sheetNum = 1;
	int   bStyleCenter = 0;
	int   iRowNum, iColNum;
	int   nDataPos = 0;
	StOutTestData *pStOutTestData = NULL;

	fileName = szExcelTmpModeName;

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

	strSheetName = sheet.GetName();

	usedRange.AttachDispatch(sheet.GetUsedRange()); 

	range.AttachDispatch(usedRange.GetRows()); 

	iRowNum = range.GetCount(); //�Ѿ�ʹ�õ����� 

	range.AttachDispatch(usedRange.GetColumns()); 

	iColNum = range.GetCount(); //�Ѿ�ʹ�õ����� 

	pos = 0;
	nDataPos = 0;
	for (i=0; i<pPar->m_row; i++)
	{
		for (j=0; j<pPar->m_col; j++)
		{
			row = i+1;
			col = j+1;
			

			//strName.Format("row%d_col%d", row, col);

			if (pPar->m_ItemFlag[i][j] == cell_data)
			{

				pStOutTestData = &m_stOutTestData[nDataPos];

				strName = pStOutTestData->szOutData;

				strCell.Format("%c%d", 'A'+col-1, row);
				range  = sheet.GetRange(COleVariant(strCell.GetBuffer(0)), covOptional);  // ��ȡA1 Range
				range.SetValue2( COleVariant(strName.GetBuffer(0)));                               // �������
				
				if (bStyleCenter)
				{
					range.SetHorizontalAlignment(COleVariant((long)-4108));// ˮƽ���ж��� 
				}
			}

			if (     (pPar->m_ItemFlag[i][j] == cell_data)
				  || (pPar->m_ItemFlag[i][j] == cell_string)
				  || (pPar->m_ItemFlag[i][j] == cell_calculate)
				)
			{
				nDataPos++;
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

int CModeParMng::GetExcelCalModeCalulateNum(char *szExcelTmpModeName)	//��ȡ���ɽ������
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
	//VARIANT vTemp;
	int    nSumColLen;

	char   *fileName = NULL; 
	CModeParMng *pPar = this;
	int    nDataPos = 0;
	StOutTestData *pStOutTestData = NULL;
	char    szDateTime[MAX_USR_NAME_LEN]= {0,};

	fileName = szExcelTmpModeName;


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

		nDataPos = 0;

		for (j=1; j<=pPar->m_row; j++)		//��
		{
			memset(ItemVal, 0, 20*200);

			for (k=1; k<=pPar->m_col; k++)	//��
			{

				//��ȡ��һ����Ԫ���ֵ 
				range.AttachDispatch(sheet.GetCells()); 

				range.AttachDispatch(range.GetItem (COleVariant((long)j),COleVariant((long)k)).pdispVal ); 

				vResult =range.GetValue2(); 
				
				/*
				if (j == 1) 
				{
					vTemp = range.GetWidth();
					nWidth = (int) (vTemp.dblVal); //(int) (vTemp.dblVal / 6); 
					vTemp = range.GetHeight();
					fHeight = vTemp.dblVal; 

					m_ColLen[k-1] = nWidth;				//��¼�п�
					nSumColLen = nSumColLen + nWidth;	//��¼���п�
				}
				*/

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

				/*
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
				*/



				if (pPar->m_ItemFlag[j-1][k-1] == cell_calculate)
				{
					pStOutTestData = &m_stOutTestData[nDataPos];
					strcpy(pStOutTestData->szOutData, str.GetBuffer(0));
					
					//3.������Ա
					strcpy(pStOutTestData->szTestUsr, m_szUsrName);

					//4.����ʱ��
					GetSysDateTime(szDateTime);
					strcpy(pStOutTestData->szTestTime, szDateTime);
				}

				if (     (pPar->m_ItemFlag[j-1][k-1] == cell_data)
					|| (pPar->m_ItemFlag[j-1][k-1] == cell_string)
					|| (pPar->m_ItemFlag[j-1][k-1] == cell_calculate)
					)
				{
					nDataPos++;
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


int  CModeParMng::GetDataTypeStr(int iDataType, char *szDataType)
{
	CString  str;

	if (iDataType == datatype_num)
	{
		str = TAB_DATA_TYPE_NUM;
	}
	else if (iDataType == datatype_string)
	{
		str = TAB_DATA_TYPE_STRING;
	}
	else if (iDataType == datatype_caluate)
	{
		str = TAB_DATA_TYPE_CAL;
	}
	else
	{
		str = TAB_DATA_TYPE_NUM;
	}

	strcpy(szDataType, str.GetBuffer(0));

	return 1;
}

int  CModeParMng::IsTableCalType( )
{
	int i,j;
	int bFlag = 0;
	for (i=0; i<m_row; i++)
	{
		for (j=0; j<m_col; j++)
		{
			if (m_ItemFlag[i][j] == cell_calculate)
			{
				bFlag = 1;
				break;
			}
		}
		if (bFlag != 0)
		{
			break;
		}
	}

	return bFlag;
}