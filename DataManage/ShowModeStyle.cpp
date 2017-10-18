// ShowModeStyle.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "ShowModeStyle.h"
#include "ModeXmlStruct.h "

static int g_nFirstWidth = 100;
static int g_nColWidth = 120;
// CShowModeStyle 对话框
IMPLEMENT_DYNAMIC(CShowModeStyle, CDialog)

CShowModeStyle::CShowModeStyle(CWnd* pParent /*=NULL*/)
	: CDialog(CShowModeStyle::IDD, pParent)
{
	m_pGrid = NULL;

	m_pDlgParMng = NULL;
	m_pShowModeInfo = NULL;
}

CShowModeStyle::~CShowModeStyle()
{
	

	if (m_pGrid != NULL)
	{
		delete m_pGrid;
		m_pGrid = NULL;
	}

	if (m_pDlgParMng != NULL)
	{
		delete m_pDlgParMng;
		m_pDlgParMng = NULL;
	}
}

void CShowModeStyle::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CShowModeStyle, CDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_SHOWMODESTYLE_PAR_BTN, &CShowModeStyle::OnBnClickedShowmodestyleParBtn)
	ON_BN_CLICKED(IDC_SHOWMODESTYLE_SHOW_BTN, &CShowModeStyle::OnBnClickedShowmodestyleShowBtn)
	ON_BN_CLICKED(IDC_LOAD_MODE_BTN, &CShowModeStyle::OnBnClickedLoadModeBtn)
	ON_BN_CLICKED(IDC_OUT_MODE_BTN, &CShowModeStyle::OnBnClickedOutModeBtn)
END_MESSAGE_MAP()

// CShowModeStyle 消息处理程序

BOOL CShowModeStyle::OnInitDialog()
{
	CDialog::OnInitDialog();



	//CheckAndDisplayAlarmBk( );

	m_pExcelOptFun->ClearParamInfo();
	m_pModeParMng->ClearParamInfo();


	InitGridCtrl_NULL();

	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CShowModeStyle::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	AutoSize();
}

void CShowModeStyle::AutoSize()
{
	CRect Rect ;
	GetClientRect(&Rect) ;
	int nBtnWidth = 80;
	int nBtnHeight = 30;

	if(GetDlgItem(IDC_SHOWMODESTYLE_STATIC1)->GetSafeHwnd())
	{
		GetDlgItem(IDC_SHOWMODESTYLE_STATIC1)->MoveWindow(3,3,Rect.Width()-(3*2),80);
	}
	if (m_pGrid->GetSafeHwnd())
	{
		m_pGrid->MoveWindow(3,(3+80+10),Rect.Width()-(3*2),Rect.Height()-(3+80+10*2));
	}


	if(GetDlgItem(IDC_SHOWMODESTYLE_PAR_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_SHOWMODESTYLE_PAR_BTN)->MoveWindow(((3+20)+(nBtnWidth+10)*0),(3+30),nBtnWidth,nBtnHeight);
	}

	if(GetDlgItem(IDC_LOAD_MODE_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_LOAD_MODE_BTN)->MoveWindow(Rect.right-((10)+(nBtnWidth+10)*4),(3+30),nBtnWidth,nBtnHeight);
	}

	if(GetDlgItem(IDC_OUT_MODE_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_OUT_MODE_BTN)->MoveWindow(Rect.right-((10)+(nBtnWidth+10)*3),(3+30),nBtnWidth,nBtnHeight);
	}

	if(GetDlgItem(IDC_SHOWMODESTYLE_SHOW_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_SHOWMODESTYLE_SHOW_BTN)->MoveWindow(Rect.right-((10)+(nBtnWidth+10)*1),(3+30),nBtnWidth,nBtnHeight);
	}
}
void CShowModeStyle::InitGridCtrl_NULL()
{
	CWnd *pWnd;
	int nRowCnt, nColCnt;
	int  row,col;
	int	 nDataPos;
	CString       str, str2;

	nRowCnt = 30; 
	nColCnt = 20;

	pWnd = this; //	pWnd = GetDlgItem(IDC_STATIC_AREA);

	if(m_pGrid != NULL)
	{
		delete m_pGrid;
		m_pGrid = NULL;
	}

	if(m_pGrid == NULL)
	{
		m_pGrid = new CGridCtrl();
		CRect rc;
		GetClientRect(&rc);
		m_pGrid->Create(rc, pWnd, IDC_GRID, WS_CHILD|WS_VISIBLE);
		m_pGrid->SetEditable(TRUE);

		m_pGrid->SetTextColor(GRID_TEXT_COLOR);

		m_pGrid->SetTextBkColor(GRID_TEXT_BK_COLOR);

		m_pGrid->SetBkColor(GRID_BK_COLOR);

		m_pGrid->SetGridColor( MY_GRID_LINE_COLOR );

		m_pGrid->SetTitleTipBackClr( RGB(128,128,128) );
		m_pGrid->SetTitleTipTextClr( RGB(255,255,255) );

		try
		{
			m_pGrid->SetRowCount(nRowCnt+1);
			m_pGrid->SetColumnCount(nColCnt+1);
			m_pGrid->SetFixedRowCount(1);
			m_pGrid->SetFixedColumnCount(1);
		}
		catch (CMemoryException* e)
		{
			e->ReportError();
			e->Delete();
		}

		CFont fontMark;
		//fontMark.CreateFont(14,0,0,0,200,0,0,0,134,3,2,1,2,_T("Arial"));			//普通
		fontMark.CreateFont(14,0,0,0,FW_SEMIBOLD,0,0,0,134,3,2,1,2,_T("Arial"));	//加粗
		m_pGrid->SetFont(&fontMark);

		nDataPos = 0;
		for(row=0; row<m_pGrid->GetRowCount(); row++)
		{
			for(col=0; col<m_pGrid->GetColumnCount(); col++)
			{
				GV_ITEM Item;
				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = row;
				Item.col = col;

				if(row==0 && col==0)
				{
					Item.nFormat = DT_WORDBREAK|DT_VCENTER|DT_CENTER;//;
					Item.strText.Format(" ");
				}
				else if(row < 1)
				{
					Item.nFormat = DT_WORDBREAK|DT_VCENTER|DT_CENTER;//|DT_VCENTER;
					Item.strText.Format("%C", col+0x40);
				}
				else if(col <1)
				{
					Item.nFormat = DT_WORDBREAK|DT_VCENTER|DT_CENTER;//|DT_VCENTER;
					Item.strText.Format("%d", row);
				}
				else
				{

				}

				m_pGrid->SetItem(&Item);

				m_pGrid->SetItemState(row,col, m_pGrid->GetItemState(row,col) | GVIS_READONLY);

			}
			m_pGrid->Invalidate();
		}

		m_pGrid->AutoSize();
		m_pGrid->AutoSizeRows();      //自动设置行高

		//---------------------------------------------------------
		for(col=0; col<m_pGrid->GetColumnCount(); col++)
		{
			if (col == 0)
			{
				m_pGrid->SetColumnWidth(col, 40);
			}
			else
			{
				m_pGrid->SetColumnWidth(col, 100);
			}		
		}

		for(row=0; row<m_pGrid->GetRowCount(); row++)
		{
			if(row ==0)
			{
				m_pGrid->SetRowHeight(row, 30);
			}else
			{
				m_pGrid->SetRowHeight(row, 40);
			}

		}


		//设置第一行，第一列颜色
		//---------------------------------------------------------
		for(col=0; col<m_pGrid->GetColumnCount(); col++)
		{	
			m_pGrid->SetItemBkColour(0, col, MY_TABLE_HEAD_COLOR);
		}

		for(row=1; row<m_pGrid->GetRowCount(); row++)
		{	
			m_pGrid->SetItemBkColour(row, 0, MY_TABLE_HEAD_COLOR);
		}
	}

}

void CShowModeStyle::InitGridCtrl()
{
	CWnd *pWnd;
	int nRowCnt, nColCnt;
	int  row,col;
	CModeParMng *pPar = m_pModeParMng;
	StTabCell    *pTabCell = NULL;
	int			 i, j, nDataPos;
	CString       str, str2;

	nRowCnt = pPar->m_row; 
	nColCnt = pPar->m_col;

	pWnd = this; //	pWnd = GetDlgItem(IDC_STATIC_AREA);

	if(m_pGrid != NULL)
	{
		delete m_pGrid;
		m_pGrid = NULL;
	}

	if(m_pGrid == NULL)
	{
		m_pGrid = new CGridCtrl();
		CRect rc;
		GetClientRect(&rc);
		m_pGrid->Create(rc, pWnd, 10011, WS_CHILD|WS_VISIBLE);
		m_pGrid->SetEditable(TRUE);

		m_pGrid->SetTextColor(GRID_TEXT_COLOR);

		m_pGrid->SetTextBkColor(GRID_TEXT_BK_COLOR);

		m_pGrid->SetBkColor(GRID_BK_COLOR);

		m_pGrid->SetGridColor( MY_GRID_LINE_COLOR );

		m_pGrid->SetTitleTipBackClr( RGB(128,128,128) );
		m_pGrid->SetTitleTipTextClr( RGB(255,255,255) );

		try
		{
			
			if (nColCnt > 0)
			{
				m_pGrid->SetRowCount(nRowCnt+1);
				m_pGrid->SetColumnCount(nColCnt+1);
				m_pGrid->SetFixedRowCount(1);
				m_pGrid->SetFixedColumnCount(1);
			}	

		}
		catch (CMemoryException* e)
		{
			e->ReportError();
			e->Delete();
		}

		CFont fontMark;
		//fontMark.CreateFont(14,0,0,0,200,0,0,0,134,3,2,1,2,_T("Arial"));			//普通
		fontMark.CreateFont(14,0,0,0,FW_SEMIBOLD,0,0,0,134,3,2,1,2,_T("Arial"));	//加粗
		m_pGrid->SetFont(&fontMark);

		nDataPos = 0;
		for(row=0; row<m_pGrid->GetRowCount(); row++)
		{
			for(col=0; col<m_pGrid->GetColumnCount(); col++)
			{
				GV_ITEM Item;
				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = row;
				Item.col = col;

				if(row==0 && col==0)
				{
					Item.nFormat = DT_WORDBREAK|DT_VCENTER|DT_CENTER;//;
					Item.strText.Format(" ");
				}
				else if(row < 1)
				{
					Item.nFormat = DT_WORDBREAK|DT_VCENTER|DT_CENTER;//|DT_VCENTER;
					Item.strText.Format("%C", col+0x40);
				}
				else if(col <1)
				{
					Item.nFormat = DT_WORDBREAK|DT_VCENTER|DT_CENTER;//|DT_VCENTER;
					Item.strText.Format("%d", row);
				}
				else
				{
					Item.nFormat = DT_CENTER|DT_VCENTER|DT_END_ELLIPSIS;
					if (pPar->m_ItemFlag[row-1][col-1] == cell_desc)
					{
						Item.strText.Format(_T("%s"), pPar->m_ItemInfo[row-1][col-1]);
					}	
					else if ((pPar->m_ItemFlag[row-1][col-1] == cell_data))
					{
						if (nDataPos < pPar->m_nDataCnt)
						{
							Item.strText.Format(_T("%s"), pPar->m_stOutTestData[nDataPos].szOutData);
						}
						else
						{
							Item.strText.Format( _T("") );
						}

						m_pGrid->SetItemBkColour(row,col, TAB_CLR_DATA_BK_NO);
						nDataPos++;
					}
				}

				m_pGrid->SetItem(&Item);

				m_pGrid->SetItemState(row,col, m_pGrid->GetItemState(row,col) | GVIS_READONLY);

			}
			m_pGrid->Invalidate();
		}

		m_pGrid->AutoSize();
		m_pGrid->AutoSizeRows();      //自动设置行高

		//---------------------------------------------------------
		for(col=0; col<m_pGrid->GetColumnCount(); col++)
		{
			if (col == 0)
			{
				m_pGrid->SetColumnWidth(col, 40);
			}
			else
			{
				m_pGrid->SetColumnWidth(col, pPar->m_ColLen[col-1]);
			}		
		}

		for(row=0; row<m_pGrid->GetRowCount(); row++)
		{
			m_pGrid->SetRowHeight(row, 30);
		}


		//设置第一行，第一列颜色
		//---------------------------------------------------------
		for(col=0; col<m_pGrid->GetColumnCount(); col++)
		{	
			m_pGrid->SetItemBkColour(0, col, MY_TABLE_HEAD_COLOR);
		}

		for(row=1; row<m_pGrid->GetRowCount(); row++)
		{	
			m_pGrid->SetItemBkColour(row, 0, MY_TABLE_HEAD_COLOR);
		}


		for (i=0; i<pPar->m_nTabCellCnt; i++)
		{
			pTabCell = &pPar->m_stTabCell[i];
			m_pGrid->MergeCells(pTabCell->iBegRow, pTabCell->iBegCol, pTabCell->iEndRow, pTabCell->iEndCol);

			if (pTabCell->iRowNum > 1)
			{
				GV_ITEM Item;
				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = pTabCell->iBegRow;
				Item.col = pTabCell->iBegCol;
				Item.nFormat = DT_WORDBREAK|DT_VCENTER|DT_CENTER;

				if (pPar->m_ItemFlag[pTabCell->iBegRow-1][pTabCell->iBegCol-1] == cell_desc)
				{
					str.Format(_T("%s"), pPar->m_ItemInfo[pTabCell->iBegRow-1][pTabCell->iBegCol-1]);
				}
				else
				{
					//str = "";
					str = m_pGrid->GetItemText(pTabCell->iBegRow, pTabCell->iBegCol);
				}


				str.Replace("\n", "");

				str2 = "";
				for (j=0; j<pTabCell->iRowNum/2; j++)
				{
					str2 = str2 + "\n";
				}
				str2 = str2 + str;
				Item.strText.Format("%s", str2);
				m_pGrid->SetItem(&Item);
			}
		}

	}

}

void CShowModeStyle::InitGridCtrl_MUL( )
{
	CWnd *pWnd;
	int nRowCnt, nColCnt, nCnt;
	int  row,col;
	CModeParMng *pPar = m_pModeParMng;
	StTabCell    *pTabCell = NULL;
	int			 i, j, nDataPos, nRowPos;
	CString       str, str2;
	int          nItemFlag = 0;
	char         *pItemInfo = NULL;
	int          iDataType = 0;
	int          nTmpDataPos= 0;

	nRowCnt = pPar->m_row; 
	nColCnt = pPar->m_col;

	pWnd = this; //	pWnd = GetDlgItem(IDC_STATIC_AREA);

	nRowPos = 0;

	if(m_pGrid != NULL)
	{
		delete m_pGrid;
		m_pGrid = NULL;
	}

	if(m_pGrid == NULL)
	{
		m_pGrid = new CGridCtrl();
		CRect rc;
		GetClientRect(&rc);
		m_pGrid->Create(rc, pWnd, 10011, WS_CHILD|WS_VISIBLE);
		m_pGrid->SetEditable(TRUE);

		m_pGrid->SetTextColor(GRID_TEXT_COLOR);

		m_pGrid->SetTextBkColor(GRID_TEXT_BK_COLOR);

		m_pGrid->SetBkColor(GRID_BK_COLOR);

		m_pGrid->SetGridColor( MY_GRID_LINE_COLOR );

		m_pGrid->SetTitleTipBackClr( RGB(128,128,128) );
		m_pGrid->SetTitleTipTextClr( RGB(255,255,255) );

		try
		{
			if (nColCnt > 0)
			{
				if (pPar->m_nModeType == mode_normal)
				{
					m_pGrid->SetRowCount(nRowCnt+1);
					m_pGrid->SetColumnCount(nColCnt+1);
					m_pGrid->SetFixedRowCount(1);
					m_pGrid->SetFixedColumnCount(1);
				}
				else
				{
					m_pGrid->SetRowCount(nRowCnt+1+pPar->m_nMulRowCnt-1);
					m_pGrid->SetColumnCount(nColCnt+1);
					m_pGrid->SetFixedRowCount(1);    //1->2
					m_pGrid->SetFixedColumnCount(1);
				}


			}	
		}
		catch (CMemoryException* e)
		{
			e->ReportError();
			e->Delete();
		}

		CFont fontMark;
		//fontMark.CreateFont(14,0,0,0,200,0,0,0,134,3,2,1,2,_T("Arial"));			//普通
		fontMark.CreateFont(TEXT_SIZE_GRID,0,0,0,FW_SEMIBOLD,0,0,0,134,3,2,1,2,_T("Arial"));	//加粗
		m_pGrid->SetFont(&fontMark);

		nDataPos = 0;
		for(row=0; row<m_pGrid->GetRowCount(); row++)
		{
			for(col=0; col<m_pGrid->GetColumnCount(); col++)
			{
				GV_ITEM Item;
				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = row;
				Item.col = col;

				if(row==0 && col==0)
				{
					Item.nFormat = DT_WORDBREAK|DT_VCENTER|DT_CENTER;//;
					Item.strText.Format(" ");
				}
				else if(row < 1)
				{
					Item.nFormat = DT_WORDBREAK|DT_VCENTER|DT_CENTER;//|DT_VCENTER;
					Item.strText.Format("%C", col+0x40);
				}
				else if(col <1)
				{
					Item.nFormat = DT_WORDBREAK|DT_VCENTER|DT_CENTER;//|DT_VCENTER;
					Item.strText.Format("%d", row);
				}
				else
				{
					Item.nFormat = DT_CENTER|DT_VCENTER|DT_END_ELLIPSIS;

					if (row < nRowCnt)
					{
						nItemFlag = pPar->m_ItemFlag[row-1][col-1];
						pItemInfo = pPar->m_ItemInfo[row-1][col-1];
					}
					else
					{
						nItemFlag = pPar->m_ItemFlag[nRowCnt-1][col-1];
						pItemInfo = pPar->m_ItemInfo[nRowCnt-1][col-1];
					}

					if (nItemFlag == cell_desc)
					{
						Item.strText.Format(_T("%s"), pItemInfo);
					}	
					else if  (     (nItemFlag == cell_data) 
						|| (nItemFlag == cell_string) 
						)
					{
						if (pPar->m_nModeType == mode_normal)
						{
							if (nDataPos < pPar->m_nDataCnt)
							{
								Item.strText.Format(_T("%s"), pPar->m_stOutTestData[nDataPos].szOutData);
							}
							else
							{
								Item.strText.Format( _T("") );
							}
							nTmpDataPos = nDataPos;
						}
						else
						{
							if (nDataPos < pPar->m_nMulDataCnt)
							{
								Item.strText.Format(_T("%s"), pPar->m_stOutTestData[nDataPos].szOutData);
							}
							else
							{
								Item.strText.Format( _T("") );
							}
							nTmpDataPos = nDataPos % pPar->m_nDataCnt;
						}


						if (pPar->m_stTabData[nTmpDataPos].iDataType != datatype_string)
						{
							m_pGrid->SetItemBkColour(row,col, TAB_CLR_DATA_NUM_BK);
						}
						else
						{
							m_pGrid->SetItemBkColour(row,col, TAB_CLR_DATA_STR_BK);
						}


						nDataPos++;
					}
					else if (nItemFlag == cell_order)
					{
						Item.strText.Format( _T("%d"), row-1);
						m_pGrid->SetItemBkColour(row,col, TAB_CLR_DATA_BK_ORDER);
					}
					else if (nItemFlag == cell_name)
					{
						Item.strText.Format( _T("Name%d"), row-1);

						if (row-2 < pPar->m_nMulRowCnt)
						{
							//str = m_pShowModeInfo
							//str = m_LoadOutTask.m_CurTaskInfo.pArryTaskPicNum.at(row-2)->szPicNumNo;
							Item.strText = str;
						}


						m_pGrid->SetItemBkColour(row,col, TAB_CLR_DATA_BK_NAME);
					}
					else if (nItemFlag == cell_calculate)
					{
						Item.strText.Format( _T("%s"), pPar->m_stOutTestData[nDataPos].szOutData);
						//Item.strText = "";
						m_pGrid->SetItemBkColour(row,col, TAB_CLR_DATA_CAL_BK);
						nDataPos++;
					}
				}

				m_pGrid->SetItem(&Item);

				m_pGrid->SetItemState(row,col, m_pGrid->GetItemState(row,col) | GVIS_READONLY);

			}
			m_pGrid->Invalidate();
		}

		m_pGrid->AutoSize();
		m_pGrid->AutoSizeRows();      //自动设置行高

		//---------------------------------------------------------
		nCnt = m_pGrid->GetColumnCount() - 2;
		for(col=0; col<m_pGrid->GetColumnCount(); col++)
		{
			if (col == 0)
			{
				m_pGrid->SetColumnWidth(col, 40);
			}
			else if (col == 1)
			{
				m_pGrid->SetColumnWidth(col,g_nFirstWidth);
			}
			else
			{
				if (nCnt <= 6)
				{
					int nTempWidth = 900/nCnt;
					nTempWidth = (1024 - 310-200-30)/nCnt;
					m_pGrid->SetColumnWidth(col, nTempWidth); 
				}
				else
				{
					m_pGrid->SetColumnWidth(col,g_nColWidth);  //150->120
				}

			}

			//m_pGrid->SetColumnWidth(col, pPar->m_ColLen[col-1]);

		}

		for(row=0; row<m_pGrid->GetRowCount(); row++)
		{
			m_pGrid->SetRowHeight(row, TAB_GRID_HEIGHT);   //30->50
		}


		//设置第一行，第一列颜色
		//---------------------------------------------------------
		for(col=0; col<m_pGrid->GetColumnCount(); col++)
		{	
			m_pGrid->SetItemBkColour(0, col, MY_TABLE_HEAD_COLOR);
		}

		for(row=1; row<m_pGrid->GetRowCount(); row++)
		{	
			m_pGrid->SetItemBkColour(row, 0, MY_TABLE_HEAD_COLOR);
		}


		for (i=0; i<pPar->m_nTabCellCnt; i++)
		{
			pTabCell = &pPar->m_stTabCell[i];
			m_pGrid->MergeCells(pTabCell->iBegRow, pTabCell->iBegCol, pTabCell->iEndRow, pTabCell->iEndCol);

			if (pTabCell->iRowNum > 1)
			{
				GV_ITEM Item;
				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = pTabCell->iBegRow;
				Item.col = pTabCell->iBegCol;
				Item.nFormat = DT_WORDBREAK|DT_VCENTER|DT_CENTER;

				if (pPar->m_ItemFlag[pTabCell->iBegRow-1][pTabCell->iBegCol-1] == cell_desc)
				{
					str.Format(_T("%s"), pPar->m_ItemInfo[pTabCell->iBegRow-1][pTabCell->iBegCol-1]);
				}
				else
				{
					//str = "";
					str = m_pGrid->GetItemText(pTabCell->iBegRow, pTabCell->iBegCol);
				}


				str.Replace("\n", "");

				str2 = "";
				for (j=0; j<pTabCell->iRowNum/2; j++)
				{
					str2 = str2 + "\n\n";
				}
				str2 = str2 + str;
				Item.strText.Format("%s", str2);
				m_pGrid->SetItem(&Item);
			}
		}

	}
}




int CShowModeStyle::CheckAndDisplayAlarmBk( )
{
	int i, j;
	CString     str;
	CModeParMng *pPar = m_pModeParMng;
	StTabAlarm  *pTabAlarm = NULL;
	StTabHisChk *pTabHisChk = NULL;
	int			pos = 0;
	double      fVal, fTarger1, fTarger2; 
	int         bAlarmFlag, bHisFlag;
	int         bAlarmStatus = 0, bHisStatus = 0;
	int         nErrType = err_no;

	pos = 0;
	for (i=0; i<pPar->m_row; i++)
	{
		for (j=0; j<pPar->m_col;j++)
		{
			if (pPar->m_ItemFlag[i][j] == cell_data)
			{
				str = m_pGrid->GetItemText(i+1, j+1);
				fVal = atof(str.GetBuffer(0));
				pTabAlarm = &pPar->m_stTabAlarm[pos];
				pTabHisChk = &pPar->m_stTabHisChk[pos];

				if (strlen(str.GetBuffer(0)) != 0) 
				{
					bAlarmFlag = pTabAlarm->bCheckFlag;
					bHisFlag   = pTabHisChk->bHisChkFlag;
					bAlarmStatus = 0;
					bHisStatus = 0;

					if (bAlarmFlag != 0)
					{
						fTarger1 = atof(pTabAlarm->szTarget1);
						fTarger2 = atof(pTabAlarm->szTarget2);
						bAlarmStatus = pPar->CalculateAlarmFlag(pos, fVal);
					}

					if (bHisFlag != 0)
					{
						bHisStatus = pPar->CalculateHisChkFlag(pos, fVal);
					}

					if ( (bAlarmFlag != 0) && (bHisFlag != 0) )
					{
						if (bAlarmStatus != 0)
						{
							nErrType = err_alarm;
						}
						else if (bHisStatus != 0)
						{
							nErrType = err_hischk;
						}
						else
						{
							nErrType = err_no;
						}

					}
					else if (bAlarmFlag != 0)
					{
						if (bAlarmStatus != 0)
						{
							nErrType = err_alarm;
						}
						else
						{
							nErrType = err_no;
						}
					}
					else if (bHisFlag != 0)
					{
						if (bHisStatus != 0)
						{
							nErrType = err_hischk;
						}
						else
						{
							nErrType = err_no;
						}
					}
					else
					{
						nErrType = err_no;
					}
				}
				else
				{
					nErrType = err_no;
				}

				switch (nErrType)
				{
				case err_no:
					{
						m_pGrid->SetItemBkColour(i+1,j+1, TAB_CLR_DATA_BK_NO);
						break;
					}
				case err_alarm:
					{
						m_pGrid->SetItemBkColour(i+1,j+1, TAB_CLR_DATA_BK_ALA);
						break;
					}
				case err_hischk:
					{
						m_pGrid->SetItemBkColour(i+1,j+1, TAB_CLR_DATA_BK_HIS);
						break;
					}
				}
				pos++;
			}
		}

	}

	return 1;
}




int CShowModeStyle::CopyExcelDataToPar(CExcelOptFun *pXls,CModeParMng *pPar)
{
	int i,j;

	if ( (pXls == NULL) || (pPar == NULL) )
	{
		return 0;
	}

	//1.Sheet1 数据
	pPar->m_row = pXls->m_row;
	pPar->m_col = pXls->m_col;
	for (i=0; i<pXls->m_row; i++)
	{
		for (j=0; j<pXls->m_col; j++)
		{
			strcpy((char*)pPar->m_ItemInfo[i][j], (char*)pXls->m_ItemInfo[i][j]);
			pPar->m_ItemFlag[i][j] = pXls->m_ItemFlag[i][j];
		}
	}

	pPar->m_nSumColLen = pXls->m_nSumColLen;                           //总列长
	for (i=0; i<pXls->m_col; i++)
	{
		pPar->m_ColLen[i] = pXls->m_ColLen[i];		//Excel列长度
	}


	//2.Sheet2 数据
	pPar->m_nTabCellCnt = pXls->m_nTabCellCnt;
	for (i=0; i<pXls->m_nTabCellCnt; i++)
	{
		memcpy( (char*)(&pPar->m_stTabCell[i]), (char*)(&pXls->m_stTabCell[i]), sizeof(StTabCell));
	}

	return 1;
}


int CShowModeStyle::CopyParDataToExcel(CModeParMng  *pPar,CExcelOptFun *pXls)
{
	int i,j;

	if (  (pPar == NULL) || (pXls == NULL))
	{
		return 0;
	}

	//1.Sheet1 数据
	pXls->m_row = pPar->m_row;
	pXls->m_col = pPar->m_col;
	for (i=0; i<pPar->m_row; i++)
	{
		for (j=0; j<pPar->m_col; j++)
		{
			strcpy((char*)pXls->m_ItemInfo[i][j], (char*)pPar->m_ItemInfo[i][j]);
			pXls->m_ItemFlag[i][j] = pPar->m_ItemFlag[i][j];
		}
	}

	pXls->m_nSumColLen = pPar->m_nSumColLen;                           //总列长
	for (i=0; i<pPar->m_col; i++)
	{
		pXls->m_ColLen[i] = pPar->m_ColLen[i];		//Excel列长度
	}


	//2.Sheet2 数据
	pXls->m_nTabCellCnt = pPar->m_nTabCellCnt;
	for (i=0; i<pPar->m_nTabCellCnt; i++)
	{
		memcpy( (char*)(&pXls->m_stTabCell[i]), (char*)(&pPar->m_stTabCell[i]), sizeof(StTabCell));
	}

	return 1;
}


BOOL CShowModeStyle::DisPlayModeStyle()
{
	m_pExcelOptFun->ClearParamInfo();
	m_pModeParMng->ClearParamInfo();

	//m_ModeXmlAnalysis.m_pParMng = &m_ModeParMng;


	CModeParMng *pPar = m_pModeParMng;

	//1.获取模板结构
	m_pModeXmlAnalysis->GetXmlMdTabSrtInfo();			
	m_pModeParMng->GetItemFlagFromData( );             //从ItemData获取ItemFlag


	//2.获取测试结果
	//m_ModeXmlAnalysis.GetXmlMdTabOutData( );		//获取模板表_输出数据内容

	//3.获取极值检测配置
	m_pModeXmlAnalysis->GetXmlMdTabHisInfo( );		//获取模板表_历史极值检测

	m_bTabCheck = pPar->CheckTabCellOk();
	if (m_bTabCheck == 0)
	{
		AfxMessageBox("检测数据错误，无法显示模板!");
		return FALSE;
	}

	//pPar->m_nModeType = mode_rowvar;

	//InitGridCtrl();
	InitGridCtrl_MUL();
	PostMessage(WM_SIZE);
	return TRUE;
}
void CShowModeStyle::OnBnClickedShowmodestyleParBtn()
{
	CString str;

	if (m_pDlgParMng == NULL)
	{
		m_pDlgParMng = new CDlgParMng();
		m_pDlgParMng->m_pCurModeInfo = &m_pShowModeInfo->m_CurModeInfo;
		m_pDlgParMng->m_pShowModeStyle = this;
		m_pDlgParMng->m_Type = 1;
		m_pDlgParMng->Create(IDD_SHOWMODEPAR_DLG, NULL);		
		m_pDlgParMng->ShowWindow(TRUE);
	}
	else
	{
		m_pDlgParMng->m_Type = 1;
		m_pDlgParMng->m_pShowModeStyle = this;
		m_pDlgParMng->m_pCurModeInfo = &m_pShowModeInfo->m_CurModeInfo;
		m_pDlgParMng->InitSysInfo();
		m_pDlgParMng->ShowWindow(TRUE);
	}
}

void CShowModeStyle::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnOK();
}

void CShowModeStyle::OnBnClickedShowmodestyleShowBtn()
{
	DisPlayModeStyle();
}

void CShowModeStyle::OnBnClickedLoadModeBtn()
{
	CFileDialog *lpszOpenFile;    //定义一个CfileDialog对象
	lpszOpenFile = new CFileDialog(TRUE,"","",OFN_FILEMUSTEXIST |OFN_HIDEREADONLY , "文件类型(*.mode)|*.mode||");//生成一个对话框
	if(lpszOpenFile->DoModal() == IDOK)//假如点击对话框确定按钮
	{
		CString	szGetName;
		szGetName = lpszOpenFile->GetPathName();	//得到打开文件的路径
	
		char *strFileInfo;
		int nLen = 0;
		StBasMode *nModeInfo = &m_pShowModeInfo->m_CurModeInfo;
		ReadFile(szGetName.GetBuffer(0),&strFileInfo,nLen);
		nModeInfo->Release();
		if(nModeInfo->nOid <= 0)
		{
			AfxMessageBox(_T("请选中一个模板再操作!"));
			delete []strFileInfo;
			delete lpszOpenFile;	//释放分配的对话框
			return ;
		}
		if(!m_DMng.UpdateModeXmlFile(nModeInfo->nOid,strFileInfo,nLen))
		{
			delete []strFileInfo;
			delete lpszOpenFile;	//释放分配的对话框
			return ;
		}
		nModeInfo->nModeSize = nLen;
		nModeInfo->pXmlFile = new char[nModeInfo->nModeSize+1];
		memset(nModeInfo->pXmlFile,0,nModeInfo->nModeSize+1);
		memcpy(nModeInfo->pXmlFile,strFileInfo,nModeInfo->nModeSize);
		delete []strFileInfo;

		CString strFilePath;
		strFilePath.Format("%s\\%s\\%s",
			g_WorkPath,PATH_XML_MODE_PAR_CFG,MD_XML_FILE_TAB_SRT_INFO);
		remove(strFilePath);
		CopyFile(szGetName,strFilePath.GetBuffer(0),NULL);

		m_pModeParMng->ClearParamInfo();
		//m_pModeXmlAnalysis->m_pParMng = m_pModeParMng;
		//1.获取模板结构
		m_pModeXmlAnalysis->GetXmlMdTabSrtInfo();	
		m_pModeParMng->GetItemFlagFromData( ); 

		//InitGridCtrl();
		InitGridCtrl_MUL();
		PostMessage(WM_SIZE);

		
		//更新 字段 模板大小//
		if(!m_DMng.EditOldMode(nModeInfo))
		{
			AfxMessageBox(_T("模板大小更新失败"));
		}
		
	}
	delete lpszOpenFile;	//释放分配的对话框
}

void CShowModeStyle::OnBnClickedOutModeBtn()
{
	CFileDialog *lpszOpenFile;    //定义一个CfileDialog对象
	CString	szGetName;
	lpszOpenFile = new CFileDialog(FALSE,".mode","MdXmlTabSrtInfo.mode",OFN_FILEMUSTEXIST |OFN_HIDEREADONLY , 
		"文件类型(*.mode)|*.mode||");//生成一个对话框
	if(lpszOpenFile->DoModal() == IDOK)//假如点击对话框确定按钮
	{

		szGetName = lpszOpenFile->GetPathName();	//得到打开文件的路径

		CFile  pFile;
		if(!pFile.Open(szGetName,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite))
		{
			AfxMessageBox(_T("打开文件失败!"));
			delete lpszOpenFile;	//释放分配的对话框
			return;
		}

		StBasMode *pModeInfo = &m_pShowModeInfo->m_CurModeInfo;
		if(pModeInfo->nModeSize<=0 || strcmp(pModeInfo->pXmlFile,_T("")) == 0)
		{
			AfxMessageBox(_T("当前模板数据为空"));
			delete lpszOpenFile;	//释放分配的对话框
			return ;
		}else
		{
			pFile.Write(pModeInfo->pXmlFile,pModeInfo->nModeSize);
		}
		
		pFile.Close();

	}else
	{
		delete lpszOpenFile;	//释放分配的对话框
		return ;
	}
	delete lpszOpenFile;	//释放分配的对话框

	AfxMessageBox(_T("导出模板成功!"));
}
