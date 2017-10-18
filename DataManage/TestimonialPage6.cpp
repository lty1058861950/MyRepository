// TestimonialPage6.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataManage.h"
#include "TestimonialPage6.h"
#include "ModeXmlStruct.h"


static int g_nFirstWidth = 100;
static int g_nColWidth = 120;
// CTestimonialPage6 �Ի���

IMPLEMENT_DYNAMIC(CTestimonialPage6, CDialog)

CTestimonialPage6::CTestimonialPage6(CWnd* pParent /*=NULL*/)
	: CDialog(CTestimonialPage6::IDD, pParent)
{
	m_pGrid = NULL;
}

CTestimonialPage6::~CTestimonialPage6()
{
	if(m_pGrid != NULL)
	{
		delete m_pGrid;
	}
}

void CTestimonialPage6::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTestimonialPage6, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CTestimonialPage6 ��Ϣ�������

BOOL CTestimonialPage6::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_Font1.CreateFont(32,0,0,0,FW_SEMIBOLD,0,0,0,134,3,2,1,2,_T("Arial"));	//�����
	m_Font2.CreateFont(18,0,0,0,FW_SEMIBOLD,0,0,0,134,3,2,1,2,_T("����"));	//ҳ��
	m_Font3.CreateFont(16,0,0,0,0,0,0,0,134,3,2,1,2,_T("����"));	//������

	GetDlgItem(IDC_STATIC1)->SetFont(&m_Font2);

	PostMessage( WM_SIZE );
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CTestimonialPage6::DispalyPageInfo()
{
	StBasTestimonialPage6 *pPage6Info = m_pPage6Info;
	vector<StBasPage6DeviceCarte> *pDeviceCarte = &pPage6Info->stDeviceCarteArray;
	StBasTstUnit *pUnits = &pPage6Info->stTstUnits;
	StBasTstCheckDate *pCheckDates = &pPage6Info->stTstCheckDates;

	int i, j, pos, nRow, nCol;
	CString str;
	str.Format(_T("%s"), pPage6Info->szTitle);
	GetDlgItem(IDC_STATIC1)->SetWindowText(str);
	CGridCtrl *pList = m_pGrid;
	int nBegrow;

	DispalyModeStyle();

	//1.�豸�嵥//
	
	nBegrow = 4;
	nRow = pDeviceCarte->size();
	for (i = nBegrow;i< nRow+nBegrow; i++)
	{
		pos = 2;
		m_pGrid->SetItemState(i,pos, GVIS_MODIFIED);
		m_pGrid->SetItemText(i, pos++,pDeviceCarte->at(i-nBegrow).szDeviceName);
		m_pGrid->SetItemState(i,pos, GVIS_MODIFIED);
		m_pGrid->SetItemText(i, pos++,pDeviceCarte->at(i-nBegrow).szStdParameter);
		m_pGrid->SetItemState(i,pos, GVIS_MODIFIED);
		m_pGrid->SetItemText(i, pos++,pDeviceCarte->at(i-nBegrow).szTstParameter);
		m_pGrid->SetItemState(i,pos, GVIS_MODIFIED);
		m_pGrid->SetItemText(i, pos++,pDeviceCarte->at(i-nBegrow).szHisParameter1);
		m_pGrid->SetItemState(i,pos, GVIS_MODIFIED);
		m_pGrid->SetItemText(i, pos++,pDeviceCarte->at(i-nBegrow).szHisParameter2);
		m_pGrid->SetItemState(i,pos, GVIS_MODIFIED);
		m_pGrid->SetItemText(i, pos++,pDeviceCarte->at(i-nBegrow).szHisParameter3);
		m_pGrid->SetItemState(i,pos, GVIS_MODIFIED);
		m_pGrid->SetItemText(i, pos++,pDeviceCarte->at(i-nBegrow).szHisParameter4);
	}

	//2.��鵥λ//
	nBegrow = 14;
	nCol = pUnits->nCount;
	i = nBegrow;

	pos = 4;
	for (j = 0; (j< nCol && j< 5) ;j++)
	{
		m_pGrid->SetItemState(i,pos, GVIS_MODIFIED);
		m_pGrid->SetItemText(i, pos++,pUnits->szUnits[j]);
	}
		

	//3.��������Ϣ//
	nBegrow = 15;
	nCol = pCheckDates->nCount;
	i = nBegrow;
	pos = 4;
	for (j = 0; (j< nCol && j< 5) ;j++)
	{
		m_pGrid->SetItemState(i,pos, GVIS_MODIFIED);
		m_pGrid->SetItemText(i, pos++,pCheckDates->szCheckDates[j]);
		
	}

		
}
void CTestimonialPage6::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialog::OnOK();
}

void CTestimonialPage6::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	AutoSize();
}


void CTestimonialPage6::AutoSize()
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

void CTestimonialPage6::DispalyModeStyle()
{
	//�����ļ���  ָ��·��//
	CString str1, str2;
	str1.Format(_T("%s\\%s\\%s"), g_WorkPath, Report_Mode_Path, _T("TestimonialPage6.txt"));

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

void CTestimonialPage6::InitGridCtrl()
{
	CWnd *pWnd;
	int nRowCnt = 15, nColCnt = 8;
	int  row,col, i, nCount;
	int			nDataPos;
	CString       str, str2;
	char *ColName1[] = {"���","����","����(�豸)���ͺš����","","",  "","",""};
	char *ColName2[] = {"","","��������\n��  ��  ��","����ʱ��","��ʷ������",  "","",""};
	char *ColName3[] = {"","","","","��  1  ��",  "��  2  ��","��  3  ��","��  4  ��"};
	char *ColName13[] = {"��  ��  ��  λ","","","","",  "","",""};
	char *ColName14[] = {"������  (����,  ����)","","","","",  "","",""};

	vector<StTabMergeCell>   stTabMergeCells;
	StTabMergeCell    nTabMergeCell;
	StTabMergeCell    *pTabCell = NULL;
	//�ϲ� 1.���
	memset(&nTabMergeCell, 0,sizeof(StTabMergeCell));
	nTabMergeCell.iBegRow = 0;
	nTabMergeCell.iBegCol = 0;
	nTabMergeCell.iEndRow = 2;
	nTabMergeCell.iEndCol = 0;
	nTabMergeCell.iRowNum = 0;
	nTabMergeCell.iColNum = 0;
	stTabMergeCells.push_back(nTabMergeCell);

	//�ϲ� 2.����
	memset(&nTabMergeCell, 0,sizeof(StTabMergeCell));
	nTabMergeCell.iBegRow = 0;
	nTabMergeCell.iBegCol = 1;
	nTabMergeCell.iEndRow = 2;
	nTabMergeCell.iEndCol = 1;
	nTabMergeCell.iRowNum = 0;
	nTabMergeCell.iColNum = 1;
	stTabMergeCells.push_back(nTabMergeCell);

	//�ϲ� 3.����(�豸)���ͺš����
	memset(&nTabMergeCell, 0,sizeof(StTabMergeCell));
	nTabMergeCell.iBegRow = 0;
	nTabMergeCell.iBegCol = 2;
	nTabMergeCell.iEndRow = 0;
	nTabMergeCell.iEndCol = 7;
	nTabMergeCell.iRowNum = 0;
	nTabMergeCell.iColNum = 2;
	stTabMergeCells.push_back(nTabMergeCell);

	//�ϲ� 4.��������\n��  ��  ��
	memset(&nTabMergeCell, 0,sizeof(StTabMergeCell));
	nTabMergeCell.iBegRow = 1;
	nTabMergeCell.iBegCol = 2;
	nTabMergeCell.iEndRow = 2;
	nTabMergeCell.iEndCol = 2;
	nTabMergeCell.iRowNum = 1;
	nTabMergeCell.iColNum = 2;
	stTabMergeCells.push_back(nTabMergeCell);

	//�ϲ� 5.����ʱ��
	memset(&nTabMergeCell, 0,sizeof(StTabMergeCell));
	nTabMergeCell.iBegRow = 1;
	nTabMergeCell.iBegCol = 3;
	nTabMergeCell.iEndRow = 2;
	nTabMergeCell.iEndCol = 3;
	nTabMergeCell.iRowNum = 1;
	nTabMergeCell.iColNum = 3;
	stTabMergeCells.push_back(nTabMergeCell);

	//�ϲ� 6.��ʷ������
	memset(&nTabMergeCell, 0,sizeof(StTabMergeCell));
	nTabMergeCell.iBegRow = 1;
	nTabMergeCell.iBegCol = 4;
	nTabMergeCell.iEndRow = 1;
	nTabMergeCell.iEndCol = 7;
	nTabMergeCell.iRowNum = 1;
	nTabMergeCell.iColNum = 4;
	stTabMergeCells.push_back(nTabMergeCell);


	int  ColWidth[] = {60,150,100,100,100,  100,100,100};

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

				if(row==0)
				{
					Item.nFormat = DT_WORDBREAK|DT_VCENTER|DT_CENTER;//;
					Item.strText.Format(" ", ColName1[col]);
				}else if(row == 1)
				{
					Item.nFormat = DT_WORDBREAK|DT_VCENTER|DT_CENTER;//|DT_VCENTER;
					//Item.strText.Format("%C", col+0x40);
					Item.strText.Format("\n%s", ColName2[col]);
				}
				else if(row == 1)
				{
					Item.nFormat = DT_WORDBREAK|DT_VCENTER|DT_CENTER;//|DT_VCENTER;
					Item.strText.Format("\n%s", ColName2[col]);
				}
				else
				{
					/*Item.nFormat = DT_CENTER|DT_VCENTER|DT_END_ELLIPSIS;
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
					}*/
				}

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


		//�ϲ���Ԫ��//
		nCount = stTabMergeCells.size();
		for (i=0; i<nCount; i++)
		{
			pTabCell = &stTabMergeCells.at(i);
			m_pGrid->MergeCells(pTabCell->iBegRow, pTabCell->iBegCol, pTabCell->iEndRow, pTabCell->iEndCol);

			if (pTabCell->iRowNum > 1)
			{
				GV_ITEM Item;
				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = pTabCell->iBegRow;
				Item.col = pTabCell->iBegCol;
				Item.nFormat = DT_WORDBREAK|DT_VCENTER|DT_CENTER;

				//str = m_pGrid->SetItemText(pTabCell->iRowNum, pTabCell->iColNum, );
				


				/*str.Replace("\n", "");

				str2 = "";
				for (j=0; j<pTabCell->iRowNum/2; j++)
				{
					str2 = str2 + "\n";
				}
				str2 = str2 + str;
				Item.strText.Format("%s", str2);
				m_pGrid->SetItem(&Item);*/
			}



		}
	}

}


/*
void CTestimonialPage6::InitGridCtrl_MUL( )
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