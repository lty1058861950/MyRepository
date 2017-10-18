// TestimonialPage7.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataManage.h"
#include "TestimonialPage7.h"
#include "ModeXmlStruct.h"


// CTestimonialPage7 �Ի���
static int g_nFirstWidth = 100;
static int g_nColWidth = 120;
IMPLEMENT_DYNAMIC(CTestimonialPage7, CDialog)

CTestimonialPage7::CTestimonialPage7(CWnd* pParent /*=NULL*/)
	: CDialog(CTestimonialPage7::IDD, pParent)
{
	m_pGrid = NULL;
}

CTestimonialPage7::~CTestimonialPage7()
{
	if(m_pGrid != NULL)
	{
		delete m_pGrid;
	}
}

void CTestimonialPage7::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTestimonialPage7, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CTestimonialPage7 ��Ϣ�������

BOOL CTestimonialPage7::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_Font1.CreateFont(32,0,0,0,FW_SEMIBOLD,0,0,0,134,3,2,1,2,_T("Arial"));	//�����
	m_Font2.CreateFont(18,0,0,0,FW_SEMIBOLD,0,0,0,134,3,2,1,2,_T("����"));	//ҳ��
	m_Font3.CreateFont(16,0,0,0,0,0,0,0,134,3,2,1,2,_T("����"));	//������

	GetDlgItem(IDC_STATIC1)->SetFont(&m_Font2);

	//InitGridCtrl();

	PostMessage( WM_SIZE );
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CTestimonialPage7::DispalyPageInfo()
{
	StBasTestimonialPage7 *pPage7Info = m_pPage7Info;
	vector<StBasPage7TestEnvironment> *pTestEnvironment = &pPage7Info->stTestEnvironment;
	StBasTstUnit *pUnits = &pPage7Info->stTstUnits;
	StBasTstCheckDate *pCheckDates = &pPage7Info->stTstCheckDates;

	int i, j, pos, nRow, nCol;
	CString str;
	str.Format(_T("%s"), pPage7Info->szTitle);
	GetDlgItem(IDC_STATIC1)->SetWindowText(str);
	int nBegrow;

	DispalyModeStyle();

	//1.�豸�嵥//
	nBegrow = 3;
	nRow = pTestEnvironment->size();
	for (i = nBegrow;i< nRow+nBegrow; i++)
	{
		pos = 2;
		m_pGrid->SetItemText(i, pos++,pTestEnvironment->at(i-nBegrow).szProjectName);
		m_pGrid->SetItemText(i, pos++,pTestEnvironment->at(i-nBegrow).szUnit);
		m_pGrid->SetItemText(i, pos++,pTestEnvironment->at(i-nBegrow).szStdValue);
		m_pGrid->SetItemText(i, pos++,pTestEnvironment->at(i-nBegrow).szTstValue);
		m_pGrid->SetItemText(i, pos++,pTestEnvironment->at(i-nBegrow).szHisValue1);
		m_pGrid->SetItemText(i, pos++,pTestEnvironment->at(i-nBegrow).szHisValue2);
		m_pGrid->SetItemText(i, pos++,pTestEnvironment->at(i-nBegrow).szHisValue3);
		m_pGrid->SetItemText(i, pos++,pTestEnvironment->at(i-nBegrow).szHisValue4);
	}


	//2.��鵥λ//
	nBegrow = 13;
	nCol = pUnits->nCount;
	i = nBegrow;

	pos = 5;
	for (j = 0; (j< nCol && j< 5) ;j++)
	{
		m_pGrid->SetItemText(i, pos++,pUnits->szUnits[j]);
	}


	//3.��������Ϣ//
	nBegrow = 14;
	nCol = pCheckDates->nCount;
	i = nBegrow;
	pos = 5;
	for (j = 0; (j< nCol && j< 5) ;j++)
	{
		m_pGrid->SetItemText(i, pos++,pCheckDates->szCheckDates[j]);

	}
	
}

void CTestimonialPage7::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialog::OnOK();
}

void CTestimonialPage7::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	AutoSize();
}


void CTestimonialPage7::AutoSize()
{
	CString str;
	CRect Rect ;
	GetClientRect(&Rect) ;


	int nBtnWidth = 80;
	int nBtnHeight = 30;


	int nStaticWidth = Rect.Width()-(100*2);
	int nLeftpos = (Rect.Width()/2- nStaticWidth/2);


	if(GetDlgItem(IDC_STATIC1)->GetSafeHwnd())
	{
		GetDlgItem(IDC_STATIC1)->MoveWindow(nLeftpos, 5+10, nStaticWidth, 30);
	}

	if(m_pGrid->GetSafeHwnd())
	{
		m_pGrid->MoveWindow(5, 5+10+40, Rect.Width()-(5*2), Rect.Height()-(5+10+40+10));
	}
}


void CTestimonialPage7::DispalyModeStyle()
{
	//�����ļ���  ָ��·��//
	CString str1, str2;
	str1.Format(_T("%s\\%s\\%s"), g_WorkPath, Report_Mode_Path, _T("TestimonialPage7.txt"));

	str2.Format(_T("%s\\%s\\%s"), g_WorkPath, PATH_XML_MODE_PAR_CFG, MD_XML_FILE_TAB_SRT_INFO);

	CopyFile(str1,str2,0);
	m_pModeParMng->ClearParamInfo();

	CModeParMng *pPar = m_pModeParMng;

	//1.��ȡģ��ṹ
	m_pModeXmlAnalysis->GetXmlMdTabSrtInfo();			
	m_pModeParMng->GetItemFlagFromData( );             //��ItemData��ȡItemFlag

	m_pGrid = InitGridCtrl_MUL(this,m_pModeParMng, m_pGrid);
	//InitGridCtrl_MUL();
	PostMessage(WM_SIZE);
}
void CTestimonialPage7::InitGridCtrl()
{
	CWnd *pWnd;
	int nRowCnt = 14, nColCnt = 9;
	int  row,col;
	StTabCell    *pTabCell = NULL;
	int			nDataPos;
	CString       str, str2;
	char *ColName1[] = {"���","��Ŀ","����\n��λ","��������\n��  ��  ֵ","����ʱ\nʵ��ֵ",    "��ʷ����ʵ��ֵ", "", "", ""};
	char *ColName2[] = {"","","","","",    "�� 1 ��", "�� 2 ��", "�� 3 ��", "�� 4 ��"};
	int  ColWidth[] = {60,200,50,100,100,  100,100,100,100};

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
				m_pGrid->SetRowCount(nRowCnt);
				m_pGrid->SetColumnCount(nColCnt);
				m_pGrid->SetFixedRowCount(0);
				m_pGrid->SetFixedColumnCount(0);
			}	

		}
		catch (CMemoryException* e)
		{
			e->ReportError();
			e->Delete();
		}

		CFont fontMark;
		//fontMark.CreateFont(14,0,0,0,200,0,0,0,134,3,2,1,2,_T("Arial"));			//��ͨ
		fontMark.CreateFont(14,0,0,0,FW_SEMIBOLD,0,0,0,134,3,2,1,2,_T("Arial"));	//�Ӵ�
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

				//if(row==0 && col==0)
				//{
				//	Item.nFormat = DT_WORDBREAK|DT_VCENTER|DT_CENTER;//;
				//	Item.strText.Format(" ");
				//}
				if(row < 1)
				{
					Item.nFormat = DT_WORDBREAK|DT_VCENTER|DT_CENTER;//|DT_VCENTER;
					//Item.strText.Format("%C", col+0x40);
					Item.strText.Format("\n%s", ColName1[col]);
				}
				else if(col <1)
				{
					Item.nFormat = DT_WORDBREAK|DT_VCENTER|DT_CENTER;//|DT_VCENTER;
					Item.strText.Format("\n%d", row);
				}
				/*else
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
				}*/

				m_pGrid->SetItem(&Item);

				m_pGrid->SetItemState(row,col, m_pGrid->GetItemState(row,col) | GVIS_READONLY);

			}
			m_pGrid->Invalidate();
		}

		m_pGrid->AutoSize();
		m_pGrid->AutoSizeRows();      //�Զ������и�

		//---------------------------------------------------------
		for(col=0; col<m_pGrid->GetColumnCount(); col++)
		{
			m_pGrid->SetColumnWidth(col, ColWidth[col]);
		}

		for(row=0; row<m_pGrid->GetRowCount(); row++)
		{
			m_pGrid->SetRowHeight(row, 60);
		}


		//���õ�һ�У���һ����ɫ
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


/*
void CTestimonialPage7::InitGridCtrl_MUL( )
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
		//fontMark.CreateFont(14,0,0,0,200,0,0,0,134,3,2,1,2,_T("Arial"));			//��ͨ
		fontMark.CreateFont(TEXT_SIZE_GRID,0,0,0,FW_SEMIBOLD,0,0,0,134,3,2,1,2,_T("Arial"));	//�Ӵ�
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
		m_pGrid->AutoSizeRows();      //�Զ������и�

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


		//���õ�һ�У���һ����ɫ
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




*/