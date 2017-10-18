// ShowTaskData.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "ShowTaskData.h"
#include "ModeXmlStruct.h"

// CShowTaskData 对话框

static int g_nFirstWidth = 100;
static int g_nColWidth = 120;

IMPLEMENT_DYNAMIC(CShowTaskData, CDialog)

CShowTaskData::CShowTaskData(CWnd* pParent /*=NULL*/)
	: CDialog(CShowTaskData::IDD, pParent)
{
	m_pGrid = NULL;
	m_pShowTaskInfo = NULL;
}

CShowTaskData::~CShowTaskData()
{
	if (m_pGrid != NULL)
	{
		delete m_pGrid;
		m_pGrid = NULL;
	}
}

void CShowTaskData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHOWTASKDATA_DEC_LIST, m_DecList);
}


BEGIN_MESSAGE_MAP(CShowTaskData, CDialog)
	ON_WM_SIZE()
	ON_NOTIFY(NM_CLICK, IDC_SHOWTASKDATA_DEC_LIST, &CShowTaskData::OnNMClickShowtaskdataDecList)
END_MESSAGE_MAP()


// CShowTaskData 消息处理程序

BOOL CShowTaskData::OnInitDialog()
{
	CDialog::OnInitDialog();

	//初始化任务详情列表//
	char *ColName4[] = {"序号","产品代号","产品名称","产品编号",_T("模板名称"),"是否典试",_T("模板类型"),_T("模板行可变"),_T("图号数量")};
	int  ColWidth4[] = {50,100,100,100,100,   100,100,100,100};
	m_DecList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_GRIDLINES);

	for(int i = 0;i<9;i++)
	{
		m_DecList.InsertColumn(i, ColName4[i],LVCFMT_CENTER, ColWidth4[i]);
	}
	m_DecList.EnableRClickMenu(FALSE);


	m_pModeParMng->ClearParamInfo();
	InitGridCtrl_NULL();

	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CShowTaskData::AutoSize()
{
	CRect Rect ;
	GetClientRect(&Rect) ;

	if(m_DecList.GetSafeHwnd())
	{
		m_DecList.MoveWindow(3,3,Rect.Width()-6,100);
	}

	if(m_pGrid->GetSafeHwnd())
	{
		m_pGrid->MoveWindow(3,105,Rect.Width()-6,Rect.Height()-(108));
	}
}
void CShowTaskData::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	AutoSize();
}

void CShowTaskData::InitGridCtrl_NULL()
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

void CShowTaskData::InitGridCtrl()
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

void CShowTaskData::InitGridCtrl_MUL( )
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
	///////////////////////////////////////////////////////////////////////////////////////
	
}






void CShowTaskData::InitTaskDecList()
{
	m_DecList.DeleteAllItems();

	StBasTask *pTaskInfo = &m_pShowTaskInfo->m_CurTaskInfo;

	int i,pos,nCount = pTaskInfo->pArryTastResultBase.size();
	StTstResultAtta *pTstResultAtta = NULL;
	CString str,strNum;

	char szTmpProdNumber[200] = {0,};

	for(i = 0;i<nCount;i++)
	{
		pTstResultAtta =  pTaskInfo->pArryTastResultBase.at(i);
		if(pTstResultAtta == NULL)
		{
			continue;
		}
		strNum.Format(_T("%d"),i+1);
		m_DecList.InsertItem(i,strNum);
		m_DecList.SetItemData(i,pTstResultAtta->nModeOid);

		pos = 1;

		if (strcmp(szTmpProdNumber, pTstResultAtta->szProductCode) != 0)
		{
			//1.
			if(strcmp(pTstResultAtta->szSeriesName,_T("")) == 0)
			{
				
				str.Format( _T("%s"), pTstResultAtta->szProductNo);
				m_DecList.SetItemText(i, pos++, str);
			}else
			{
				str.Format( _T("%s-%s"), pTstResultAtta->szProductNo,pTstResultAtta->szSeriesName);
				m_DecList.SetItemText(i, pos++, str);
			}
			

			//2.	
			str.Format( _T("%s"), pTstResultAtta->szProductName);
			m_DecList.SetItemText(i, pos++, str);


			//3.	
			str.Format( _T("%s"), pTstResultAtta->szProductCode);
			m_DecList.SetItemText(i, pos++, str);

			memset(szTmpProdNumber, 0, sizeof(szTmpProdNumber));
			strcpy(szTmpProdNumber, pTstResultAtta->szProductCode);
		}
		else
		{
			pos = 4;
		}
		//4.	
		str.Format( _T("%s"), pTstResultAtta->szModeName);
		m_DecList.SetItemText(i, pos++, str);

		//5.	
		str.Format( _T("%d"), pTstResultAtta->nDianshiTest);
		m_DecList.SetItemText(i, pos++, str);

		//6.
		str.Format( _T("%s"), g_ModeType[pTstResultAtta->nModeType]);
		m_DecList.SetItemText(i, pos++, str);

		//6.
		str.Format( _T("%s"), g_ModeRowVal[pTstResultAtta->nModeRowVar]);
		m_DecList.SetItemText(i, pos++, str);

		if(pTstResultAtta->nModeRowVar>0)
		{
			//7.
			str.Format( _T("%d"), pTstResultAtta->nPicNumCount);
			m_DecList.SetItemText(i, pos++, str);
		}
	}

}


BOOL CShowTaskData::AutoBuildTabStruct(CString nModeTabName,CppSQLite3DB *pSqlite,int Flags)
{
	m_pModeParMng->ClearParamInfo();

	//m_ModeXmlAnalysis.m_pParMng = &m_ModeParMng;
	//1.获取模板结构
	m_pModeXmlAnalysis->GetXmlMdTabSrtInfo();
	m_pModeXmlAnalysis->SetXmlMdTabHisInfo();
	//动态创建数据库表结构///
	int iRowNum = m_pModeParMng->m_nDataCnt;
	

	//nModeID = "0000000001";
	//nModeID = _T("ModeDataTab")+nModeID;
	//更新模板的附加信息//
	CString str,strText = "";
	str.Format(_T("%d"),iRowNum);
	//AfxMessageBox(str);
	StTabData    *pTabData = NULL;

	for (int i=0; i<iRowNum; i++)
	{
		pTabData = &m_pModeParMng->m_stTabData[i];

		str.Format(_T("%s VARCHAR2(100),"),pTabData->szDbColName);
		
		strText+=str;
	}

	char*szSQL = new char[2048+50*iRowNum];
	memset(szSQL,0,2048+50*iRowNum);
	sprintf(szSQL,_T("create table %s (\
					 OID            NUMBER(10) PRIMARY KEY not null,\
					 BELONG_MODEL   VARCHAR2(100),\
					 BELONG_MOMENT  VARCHAR2(100),\
					 PRODUCT_OID    NUMBER(10),\
					 PRODUCT_NO     VARCHAR2(100),\
					 PRODUCT_NAME   VARCHAR2(100),\
					 SERIES_OID     NUMBER(10),\
					 SERIES_NAME    VARCHAR2(100),\
					 PRODUCT_CODE	VARCHAR2(100),\
					 PICNUM_OID     NUMBER(10),\
					 PICNUM_NO      VARCHAR2(100),\
					 PICNUM_NAME    VARCHAR2(100),\
					 TASK_OID	    NUMBER(10),\
					 TASK_NAME      VARCHAR2(100),\
					 SEND_DATE      DATE,\
					 IMPORT_DATE    DATE,\
					 Def_Edit_3     VARCHAR2(100),\
					 Def_Edit_4     VARCHAR2(100),\
					 Def_Edit_5     VARCHAR2(100),\
					 Def_Edit_6     VARCHAR2(100),\
					 %s\
					 BASE_OID       NUMBER(10),\
					 ATTA_OID       NUMBER(10),\
					 DATA_XMLFILE   BLOB)"),nModeTabName,strText);
	if(Flags)
	{
		m_DMng.UpdateDataInfo(szSQL);
	}else
	{
		pSqlite->execDML(szSQL);
	}

	delete []szSQL;

	szSQL = new char[512];

	if(Flags)
	{

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.OID is '数据主键ID'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);
		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.BELONG_MODEL is '产品型号'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);
		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.BELONG_MOMENT is '产品阶段'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);
		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.PRODUCT_OID is '产品OID'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);
		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.PRODUCT_NO is '产品代号'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);
		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.PRODUCT_NAME is '产品名称'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);
		
		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.SERIES_OID is '产品系列OID'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);
		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.SERIES_NAME is '产品系列名'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.PRODUCT_CODE is '产品编号'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);
		
		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.PICNUM_OID is '图号Oid'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.PICNUM_NO is '图号代号'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.PICNUM_NAME is '图号名称'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.TASK_OID is '所属任务ID'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);
		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.TASK_NAME is '任务名称'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);
		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.SEND_DATE is '下发时间'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.IMPORT_DATE is '导入时间'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.Def_Edit_3 is '测试人'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.Def_Edit_4 is '检验'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.Def_Edit_5 is '军代表'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.Def_Edit_6 is '测试日期'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		for (int i = 0;i<iRowNum;i++)
		{
			pTabData = &m_pModeParMng->m_stTabData[i];
			memset(szSQL,0,512);
			sprintf(szSQL,_T("comment on column %s.%s is '%s'"),nModeTabName,pTabData->szDbColName,pTabData->szOutDataName);
			m_DMng.UpdateDataInfo(szSQL);
		}

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.BASE_OID is '任务基础表OID'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);
		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.ATTA_OID is '结构附件表OID'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);

		memset(szSQL,0,512);
		sprintf(szSQL,_T("comment on column %s.DATA_XMLFILE is '采集数据文件'"),nModeTabName);
		m_DMng.UpdateDataInfo(szSQL);
	}
	
	delete []szSQL;
	return TRUE;
}
void CShowTaskData::OnNMClickShowtaskdataDecList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码//

	//单击查询当前任务的详细情况//
	CListCtrl *pList = &m_DecList;
	int nCount = pList->GetItemCount(),Index = m_DecList.GetFirstSelectedItem();

	if(Index < 0 || Index >= nCount)
	{
		return ;
	}
	UINT nModeOid = pList->GetItemData(Index);
	
	char szSQL[2048] = {0};
	StBasMode nModeInfo;
	memset(&nModeInfo,0,sizeof(StBasMode));
	DelFile();
	if(m_DMng.GetModeDataOid(nModeOid,&nModeInfo))
	{
		//3.///
		CString strFilePath;
		CStdioFile file;
		CFileException e;
		strFilePath.Format("%s\\%s\\%s",
			g_WorkPath,PATH_XML_MODE_PAR_CFG,MD_XML_FILE_TAB_SRT_INFO);
		remove(strFilePath);
		if(!file.Open(strFilePath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite, &e))
		{
			char szMsg[128] = {0};
			e.GetErrorMessage(szMsg, 128);

			CString strErr;
			strErr.Format(_T("打开文件失败，原因为: %s"), szMsg);
			AfxMessageBox(strErr);
			return;
		}
		if(nModeInfo.pXmlFile == NULL || nModeInfo.nModeSize == 0)
		{

		}else
		{
			file.WriteString(nModeInfo.pXmlFile);
		}

		file.Close();
	}
	nModeInfo.Release();

	//从数据库中读取模板配置  采集数据  以及历史极值//

	CModeParMng *pPar =m_pModeParMng;

	m_pModeParMng->ClearParamInfo();

	//m_ModeXmlAnalysis.m_pParMng = &m_ModeParMng;
	//1.获取模板结构
	m_pModeXmlAnalysis->GetXmlMdTabSrtInfo();			
	m_pModeParMng->GetItemFlagFromData( );             //从ItemData获取ItemFlag


	//2.获取测试结果
	m_pModeXmlAnalysis->GetXmlMdTabOutData( );		//获取模板表_输出数据内容

	//3.获取极值检测配置
	m_pModeXmlAnalysis->GetXmlMdTabHisInfo( );		//获取模板表_历史极值检测

	int nPicNumCount = m_pShowTaskInfo->m_CurTaskInfo.pArryTaskPicNum.size();

	if (nModeInfo.nModeRowVar == mode_rowvar)
	{
		pPar->m_nModeType = mode_rowvar;
		pPar->m_nMulRowCnt = nPicNumCount;
	}
	else
	{
		pPar->m_nModeType = mode_normal;
	}

	InitGridCtrl_MUL();
	PostMessage(WM_SIZE);
	*pResult = 0;
}