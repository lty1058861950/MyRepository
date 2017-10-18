// ResultShow.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataManage.h"
#include "ResultShow.h"
#include "WordSrc\\WordOptFun.h"
#include "MainFrm.h"

// CResultShow �Ի���

static int g_nFirstWidth = 100;
static int g_nColWidth = 120;

IMPLEMENT_DYNAMIC(CResultShow, CDialog)

CResultShow::CResultShow(CWnd* pParent /*=NULL*/)
	: CDialog(CResultShow::IDD, pParent)
{
	m_pGrid = NULL;
	m_pCurAttaInfo = NULL;
	
}

CResultShow::~CResultShow()
{
	int t1,t2;
	CString str;
	t1= GetTickCount();

	
	t2 = GetTickCount()-t1;
	str.Format(_T("�ͷ� CResultShow ��ʱ %d ����"),t2);
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));

	if (m_pGrid != NULL)
	{
		delete m_pGrid;
		m_pGrid = NULL;
	}
}

void CResultShow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RESHOW_TAB, m_Tab1);
	DDX_Control(pDX, IDC_DEC_LIST, m_DecList);
	DDX_Control(pDX, IDC_ATTACHMENT_LIST, m_AttachmentList);
}


BEGIN_MESSAGE_MAP(CResultShow, CDialog)
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_RESHOW_TAB, &CResultShow::OnTcnSelchangeReshowTab)
	ON_BN_CLICKED(IDC_CREATE_REPORT_BTN, &CResultShow::OnBnClickedCreateReportBtn)
	ON_BN_CLICKED(IDC_OUT_DATA_BTN, &CResultShow::OnBnClickedOutDataBtn)
	ON_NOTIFY(NM_RCLICK, IDC_ATTACHMENT_LIST, &CResultShow::OnNMRClickAttachmentList)
	ON_COMMAND(ID_MENU1_LOADOUT_ATTACH, &CResultShow::LoadOutAttachFile)
	ON_COMMAND(ID_MENU2_OPEN_DIRECTORY, &CResultShow::OpenFileDirectory)
END_MESSAGE_MAP()


// CResultShow ��Ϣ�������

BOOL CResultShow::OnInitDialog()
{
	CDialog::OnInitDialog();

	int t1,t2;
	CString str;
	t1= GetTickCount();

	
	g_MainFram->m_ExcelOptFun.ClearParamInfo();
	//�����ݿ��ж�ȡģ������  �ɼ�����  ��ʷ��ֵ  ������Ϣ(ͼ����Ϣ)//
	g_MainFram->m_ModeParMng.ClearParamInfo();

	m_LoadOutTask.GetCurTaskInfoLoad();

	int nRet = 0;
	nRet = m_LoadOutTask.AnalysisData(m_DataArray,m_ExclosureArray);//��ȡ��ǰ�����������//
	if(!nRet)
	{
		//return 0;
	}

	g_pDataArray = &m_DataArray;////1.����

	t2 = GetTickCount()-t1;
	str.Format(_T("CResultShow::OnInitDialog() GetCurTaskInfoLoad,AnalysisData ��ʱ %d ����"),t2);
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));


	CModeParMng *pPar = &g_MainFram->m_ModeParMng;
	int    nMulRowCnt = 1;
	//CString str;

	int nPicNumCount = g_PicNum = m_LoadOutTask.m_CurTaskInfo.pArryTaskPicNum.size();
	g_pArryTaskPicNum = &m_LoadOutTask.m_CurTaskInfo.pArryTaskPicNum;//2.ͼ����Ϣ///
	g_pCurAttaInfo = m_pCurAttaInfo;//3.������Ϣ//
	

	if (m_pCurAttaInfo->nModeRowVar == mode_rowvar)
	{
		nMulRowCnt = nPicNumCount;
		pPar->m_nModeType = mode_rowvar;
		pPar->m_nMulRowCnt = nMulRowCnt;
	}
	else
	{
		pPar->m_nModeType = mode_normal;
	}

	if (pPar->m_nModeType == mode_rowvar) 
	{
		if ((pPar->m_nMulRowCnt < 1) || (pPar->m_nMulRowCnt > MUL_MAX_ROW) )
		{
			str.Format(_T("������Χ,nCnt=%d, Max=%d"), pPar->m_nMulRowCnt, MUL_MAX_ROW);
			AfxMessageBox(str);
			return FALSE;
		}
	}

	if (pPar->m_nMulRowCnt > MUL_MAX_ROW)
	{
		pPar->m_nMulRowCnt = MUL_MAX_ROW;
	}

	g_MainFram->m_ModeParMng.ClearParamInfo();
	//m_ModeXmlAnalysis.m_pParMng = &m_ModeParMng;

	
	//1.��ȡģ��ṹ
	g_MainFram->m_ModeXmlAnalysis.GetXmlMdTabSrtInfo();			
	g_MainFram->m_ModeParMng.GetItemFlagFromData( );             //��ItemData��ȡItemFlag


	//2.��ȡ���Խ��
	g_MainFram->m_ModeXmlAnalysis.GetXmlMdTabOutData( );		//��ȡģ���_�����������

	//3.��ȡ��ֵ�������
	g_MainFram->m_ModeXmlAnalysis.GetXmlMdTabHisInfo( );		//��ȡģ���_��ʷ��ֵ���

	
	if (m_pCurAttaInfo->nModeRowVar == mode_rowvar)
	{	
		//��������
		pPar->m_nMulDataCnt = pPar->m_nDataCnt*pPar->m_nMulRowCnt;
		pPar->m_mulrow = pPar->m_row+pPar->m_nMulRowCnt+1;
	}


	InitGridCtrl_MUL();
	InitPopMenu1( );


	

	TCITEM tcItem;
	tcItem.mask = TCIF_TEXT;
	tcItem.pszText = _T("������Ϣ");
	m_Tab1.InsertItem(0,&tcItem) ;

	tcItem.pszText = _T("������Ϣ");
	m_Tab1.InsertItem(1,&tcItem) ;

	tcItem.pszText = _T("������Ϣ");
	m_Tab1.InsertItem(2,&tcItem) ;

	m_pGrid->ShowWindow(SW_SHOW);
	m_DecList.ShowWindow(SW_HIDE);
	m_AttachmentList.ShowWindow(SW_HIDE);


	DisplayOutDataDesc( );
	DisplayProdAppData( );

	m_DecList.EnableRClickMenu(FALSE);
	m_AttachmentList.EnableRClickMenu(FALSE);

	m_fontMark1.CreateFont(14,0,0,0,200,0,0,0,134,3,2,1,2,_T("Arial"));			//��ͨ

	m_Tab1.SetFont(&m_fontMark1);
	GetDlgItem(IDC_REPORT_SHOW_STATIC1)->SetFont(&m_fontMark1);

	m_ProductInfo.Format(_T("��Ʒ����:%s,    ��Ʒ���:%s,    ����ģ��:%s"),
		m_pCurAttaInfo->szProductNo, 
		m_pCurAttaInfo->szProductCode, 
		m_pCurAttaInfo->szModeName );

	GetDlgItem(IDC_REPORT_SHOW_STATIC1)->SetWindowText(m_ProductInfo);
	MoveWindow(0,0,1224,g_WinHeight);
	CenterWindow();
	PostMessage(WM_SIZE);

	t2 = GetTickCount()-t1;
	str.Format(_T("CResultShow::OnInitDialog() ��ʱ %d ����"),t2);
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
void CResultShow::AutoSize()
{
	CRect Rect ;
	GetClientRect(&Rect) ;
	int BtnWidth = 80;
	int BtnHeight = 30;

	int nStaticWidth = m_ProductInfo.GetLength()*10;

	if(GetDlgItem(IDC_REPORT_SHOW_STATIC1)->GetSafeHwnd())
	{
		GetDlgItem(IDC_REPORT_SHOW_STATIC1)->MoveWindow(Rect.left+(Rect.Width()/2-nStaticWidth/2),13,nStaticWidth,BtnHeight);
	}

	if(GetDlgItem(IDC_CREATE_REPORT_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_CREATE_REPORT_BTN)->MoveWindow(Rect.right-BtnWidth*2,8,BtnWidth,BtnHeight);
	}



	if(m_Tab1.GetSafeHwnd())
	{
		m_Tab1.MoveWindow(1,25,Rect.Width()-(2),Rect.Height()-(80));
	}

	if(m_pGrid->GetSafeHwnd())
	{
		m_pGrid->MoveWindow(3,50,Rect.Width()-(6),Rect.Height()-(110));
	}

	if(m_DecList.GetSafeHwnd())
	{
		m_DecList.MoveWindow(3,50,Rect.Width()-(6),Rect.Height()-(110));
	}

	if(m_AttachmentList.GetSafeHwnd())
	{
		m_AttachmentList.MoveWindow(3,50,Rect.Width()-(6),Rect.Height()-(110));
	}

	
	if(GetDlgItem(IDC_OUT_DATA_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_OUT_DATA_BTN)->MoveWindow(20,Rect.bottom-(40),BtnWidth,BtnHeight);
	}


	if(GetDlgItem(IDCANCEL)->GetSafeHwnd())
	{
		GetDlgItem(IDCANCEL)->MoveWindow(Rect.right-(BtnWidth+20),Rect.bottom-(40),BtnWidth,BtnHeight);
	}


}
void CResultShow::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	AutoSize();
}

void  CResultShow::InitPopMenu1( )					//��ʼ���˵�1
{
	if(!m_PopupMenu1.GetSafeHmenu())
	{
		m_PopupMenu1.CreatePopupMenu();
		m_PopupMenu1.AppendMenu(MF_STRING, ID_MENU1_LOADOUT_ATTACH,		"���������ļ�");
		m_PopupMenu1.AppendMenu(MF_STRING, ID_MENU2_OPEN_DIRECTORY,		"�������ļ���");

	}
}
void CResultShow::InitGridCtrl_NULL()
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
		m_pGrid->AutoSizeRows();      //�Զ������и�

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

void CResultShow::InitGridCtrl()
{
	CWnd *pWnd;
	int nRowCnt, nColCnt;
	int  row,col;
	CModeParMng *pPar = &g_MainFram->m_ModeParMng;
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
		m_pGrid->AutoSizeRows();      //�Զ������и�

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
					str2 = str2 + "\n";
				}
				str2 = str2 + str;
				Item.strText.Format("%s", str2);
				m_pGrid->SetItem(&Item);
			}
		}

	}

}





void CResultShow::InitGridCtrl_MUL( )
{

	CWnd *pWnd;
	int nRowCnt, nColCnt, nCnt;
	int  row,col;
	CModeParMng *pPar = &g_MainFram->m_ModeParMng;
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






void CResultShow::DisplayOutDataDesc( )
{
	CModeParMng  *pPar = &g_MainFram->m_ModeParMng; 
	CListCtrl    *pList = &m_DecList;
	StTabData    *pTabData  = NULL;
	StOutTestData  *pOutTestData = NULL;

	char       szJudgeDesc[XLS_MAX_LEN] ={0,};

	int		i, rowPos, pos, pos1, nRow;
	CString	str;
	int     iRowNum, iColNum;
	char	ItemName[20][30] = {"���",	  "�������",  "����ͼ��", "��������",  
		"����ֵ", "����������Ϣ",	
	};
	char	ItemName2[20][30] = {"���",  "�к�",  "�к�", "��������",  
		"����ֵ", "����������Ϣ",	
	};
	int     ItemLen[20]      = {  50,		120,		120,		120,	 
		120,		400,		80 ,	110
	};

	pPar->ListCtrl_ClearAllColumn(pList);

	if (pPar->m_nModeType == mode_normal)
	{
		iRowNum = pPar->m_nDataCnt;
	}
	else
	{
		iRowNum = pPar->m_nMulDataCnt;
	}

	iColNum = 6;

	for (i=0; i<iColNum; i++)
	{
		if (pPar->m_nModeType == mode_normal)
		{
			str.Format("%s", ItemName2[i]);
		}
		else
		{
			str.Format("%s", ItemName[i]);
		}

		pList->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen[i]);	
	}

	rowPos = 0;
	for (i=0; i<iRowNum; i++)
	{
		pos1 = i % pPar->m_nDataCnt;
		nRow = i / pPar->m_nDataCnt;
		pTabData = &pPar->m_stTabData[pos1];
		pOutTestData = &pPar->m_stOutTestData[i];

		if (   (strcmp(pOutTestData->szOutData, TEXT_WRONG_1) == 0)
			|| (strcmp(pOutTestData->szOutData, TEXT_WRONG_2) == 0)
			)
		{

		}
		else
		{
			continue;
		}

		//1.
		str.Format("%3d", rowPos+1);
		pList->InsertItem(rowPos, str);

		pos = 1;

		if (pPar->m_nModeType == mode_normal)
		{
			//2.�к�
			str.Format( _T("%d"), pTabData->iBegRow);
			pList->SetItemText(rowPos, pos++, str);	

			//3.�к�
			str.Format( _T("%d"), pTabData->iBegCol);
			pList->SetItemText(rowPos, pos++, str);
		}
		else
		{
			//2.�����
			str.Format( _T("%d"), nRow+1);
			pList->SetItemText(rowPos, pos++, str);	

			//3.ͼ��
			str = "";
			if (nRow < pPar->m_nMulRowCnt)
			{
				str = m_LoadOutTask.m_CurTaskInfo.pArryTaskPicNum.at(nRow)->szPicNumNo;
			}
			pList->SetItemText(rowPos, pos++, str);
		}


		//4.	
		str.Format( _T("%s"), pTabData->szOutDataName);
		pList->SetItemText(rowPos, pos++, str);

		//5.
		str.Format( _T("%s"), pOutTestData->szOutData);
		pList->SetItemText(rowPos, pos++, str);

		//6.
		str.Format( _T("%s"), pOutTestData->szOutDesc);
		pList->SetItemText(rowPos, pos++, str);


		rowPos++;	
	}

}

void CResultShow::DisplayProdAppData()		//���Խ��_������Ϣ
{
	CModeParMng  *pPar = &g_MainFram->m_ModeParMng; 
	StTabData    *pTabData  = NULL;
	StOutAppData  *pOutAppData = NULL;
	CListCtrl *pList = &m_AttachmentList;

	char       szJudgeDesc[XLS_MAX_LEN] ={0,};

	int		i, pos;
	CString	str;
	int     iRowNum, iColNum;
	char	ItemName[20][30] = {"���",			"���ݱ�_���ֶ�����",  "���ݱ�_���ֶ�����", "��������",  
		"����ԭʼ����",	  "��������",			"�����Ա",			"���ʱ��",    "��������·��"
	};
	int     ItemLen[20]      = {  50,		120,			120,		70,	 
		120,		280,			80 ,	110,   512
	};
	CEditableListCtrl *pEditList = (CEditableListCtrl *)pList; 

	iRowNum = pPar->m_nOutAppDataCnt;
	iColNum = 9;

	for (i=0; i<iColNum; i++)
	{
		str.Format("%s", ItemName[i]);
		pList->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen[i]);	
	}

	for (i=0; i<iRowNum; i++)
	{
		pOutAppData = &pPar->m_stOutAppData[i];


		pos = pOutAppData->nTabDataPos;

		pos = pos % pPar->m_nDataCnt;

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

		//�齨����·��//
		//9.
		str.Format( _T("%s\\%s"), BuildAttamentFilePath(m_pCurAttaInfo),pOutAppData->szDesFileName);
		pList->SetItemText(i, pos, str);
		pos++;	
	}
}

void CResultShow::OnTcnSelchangeReshowTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	int i = m_Tab1.GetCurSel(),nCount = m_Tab1.GetItemCount();

	if(i<0 || i>=nCount)
	{
		return ;
	}

	switch(i)
	{
	case 0:
		{
			m_pGrid->ShowWindow(SW_SHOW);
			m_DecList.ShowWindow(SW_HIDE);
			m_AttachmentList.ShowWindow(SW_HIDE);
		}
		break;
	case 1:
		{
			m_pGrid->ShowWindow(SW_HIDE);
			m_DecList.ShowWindow(SW_SHOW);
			m_AttachmentList.ShowWindow(SW_HIDE);
		}
		break;
	case 2:
		{
			m_pGrid->ShowWindow(SW_HIDE);
			m_DecList.ShowWindow(SW_HIDE);
			m_AttachmentList.ShowWindow(SW_SHOW);
		}
	}
	*pResult = 0;
}

void CResultShow::OnBnClickedCreateReportBtn()
{

	CString str, strFileName, strDesFile, strCreateFile;
	int		ret, tick1,tick2;

	
	strCreateFile.Format(_T("Report_%s"),GetDateTimeString2());

	CFileDialog *lpszOpenFile;    //����һ��CfileDialog����
	lpszOpenFile = new CFileDialog(FALSE,".doc",strCreateFile,OFN_FILEMUSTEXIST |OFN_HIDEREADONLY , 
		"�ļ�����(*.doc)|*.doc||");//����һ���Ի���
	if(lpszOpenFile->DoModal() == IDOK)//�������Ի���ȷ����ť
	{

		strCreateFile = lpszOpenFile->GetPathName();	//�õ����ļ���·��

	}else
	{
		delete lpszOpenFile;	//�ͷŷ���ĶԻ���
		return ;
	}
	delete lpszOpenFile;	//�ͷŷ���ĶԻ���

	

	


	if (m_pCurAttaInfo->nModeRowVar == mode_normal)
	{
		tick1 = GetTickCount();


		StBasMode StBasModeInfo;
		memset(&StBasModeInfo, 0, sizeof(StBasMode));

		StBasModeInfo.nModeType = m_pCurAttaInfo->nModeType;
		strcpy(StBasModeInfo.szModeName, m_pCurAttaInfo->szModeName);
		strcpy(StBasModeInfo.stProductInfo.szProductNo, m_pCurAttaInfo->szProductNo);
		strFileName = BuildReportModeFilePath(&StBasModeInfo);

		if(GetFileAttributes(strFileName.GetBuffer(0)) == 0xFFFFFFFF)
		{
			str.Format(_T("����ģ�岻���� ��%s"),strFileName);
			AfxMessageBox(str);
			return ;
		}


		memset(StBasModeInfo.szModeName, 0, sizeof(StBasModeInfo.szModeName));
		strcpy(StBasModeInfo.szModeName, _T("t_Mode2"));
		strDesFile = BuildReportModeFilePath(&StBasModeInfo);


		
		//strFileName = _T("c:\\Mode2.doc");
		//strDesFile  = _T("c:\\t_Mode2.doc");

		ret = WordOpt_MakeTabModeToTabData(strFileName.GetBuffer(0), strDesFile.GetBuffer(0));

		tick2 = GetTickCount()-tick1;
		str.Format("��ʱ%d����! ret=%d, ����ļ���%s", tick2, ret, strDesFile.GetBuffer(0)); 
		//AfxMessageBox(str);	



		//CString str, strFileName, strDesFile;
		//int		ret, tick1,tick2;
		tick1 = GetTickCount();

		//strCreateFile  = _T("c:\\t_ModeInfo_2.doc");
		//strFileName = _T("c:\\t_Mode2.doc");

		ret = WordOpt_MakeReportTabInfoDemo(strCreateFile.GetBuffer(0),strDesFile.GetBuffer(0));

		tick2 = GetTickCount()-tick1;
		str.Format("��ʱ%d����! ret=%d, ����ļ���%s", tick2, ret, strCreateFile.GetBuffer(0)); 
		AfxMessageBox(str);	

	}else
	{
		int		ret, tick1,tick2;
		tick1 = GetTickCount();

		//strCreateFile = _T("C:\\tt2.doc");
		ret = WordOpt_MakeReportRowVarDemo( strCreateFile.GetBuffer(0) ); 

		tick2 = GetTickCount()-tick1;
		str.Format("��ʱ%d����! ret=%d, ����ļ���%s", tick2, ret, strCreateFile.GetBuffer(0)); 
		AfxMessageBox(str);	
	}
	
	remove(strDesFile.GetBuffer(0));
}


int CResultShow::CopyParDataToExcel(CModeParMng  *pPar,CExcelOptFun *pXls)
{
	int i,j;

	if (  (pPar == NULL) || (pXls == NULL))
	{
		return 0;
	}

	//1.Sheet1 ����
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

	pXls->m_nSumColLen = pPar->m_nSumColLen;                           //���г�
	for (i=0; i<pPar->m_col; i++)
	{
		pXls->m_ColLen[i] = pPar->m_ColLen[i];		//Excel�г���
	}


	//2.Sheet2 ����
	pXls->m_nTabCellCnt = pPar->m_nTabCellCnt;
	for (i=0; i<pPar->m_nTabCellCnt; i++)
	{
		memcpy( (char*)(&pXls->m_stTabCell[i]), (char*)(&pPar->m_stTabCell[i]), sizeof(StTabCell));
	}

	return 1;
}
void CResultShow::OnBnClickedOutDataBtn()
{
	int				ret=0;
	CString         str;
	CExcelOptFun	*pXls = &g_MainFram->m_ExcelOptFun; 
	CModeParMng		*pPar = &g_MainFram->m_ModeParMng;
	CString strCreateFile;

	if ( (pPar->m_row <= 0) || (pPar->m_col<= 0) )
	{
		AfxMessageBox( _T("�����������������Ϊ��!") );
		return;
	}
	if (pPar->CheckTabCellOk() == 0)
	{
		AfxMessageBox( _T("���ṹ����쳣���޷�����!") );
		return;
	}

	CFileDialog *lpszOpenFile;    //����һ��CfileDialog����
	lpszOpenFile = new CFileDialog(FALSE,".xls",m_pCurAttaInfo->szModeName,OFN_FILEMUSTEXIST |OFN_HIDEREADONLY , 
		"�ļ�����(*.xls)|*.xls||");//����һ���Ի���
	if(lpszOpenFile->DoModal() == IDOK)//�������Ի���ȷ����ť
	{

		strCreateFile = lpszOpenFile->GetPathName();	//�õ����ļ���·��

	}else
	{
		delete lpszOpenFile;	//�ͷŷ���ĶԻ���
		return ;
	}
	delete lpszOpenFile;	//�ͷŷ���ĶԻ���


	CopyParDataToExcel(pPar, pXls);

	g_MainFram->m_ExcelOptFun.WriteDataToExcel(pPar,&m_DecList,&m_AttachmentList,strCreateFile);
}

void CResultShow::LoadOutAttachFile()
{
	CString strFileName = m_CurFilePath;
	CString strDecFilePath = m_CurFilePath;
	CString str, strText;
	int pos;
	while((pos = strFileName.Find('\\')) >=0)
	{
		str+=strFileName.Left(pos+1);
		strFileName = strFileName.Right(strFileName.GetLength()-pos-1);
	}

	CPathDialog dlg(_T("·��"),_T("·��"),_T("c:\\"),NULL);
	if(dlg.DoModal()==IDOK)
	{
		//UpdateData();
		str = dlg.GetPathName();
		
	}else
	{
		return ;
	}

	pos = str.GetLength();
	if(str[pos-1] == '\\')
	{
		str = str.Left(pos-1);
	}

	strText.Format(_T("%s\\%s"), str, strFileName);
	CopyFile(strDecFilePath,strText,0);


	str.Format(_T("/select,%s"), strText);
	//ShellExecute(NULL,_T("explore"),strText,NULL,NULL,SW_SHOWNORMAL);
	ShellExecute(NULL,_T("open"),_T("explorer.exe"),str,NULL,SW_SHOWNORMAL);

}
void CResultShow::OpenFileDirectory()
{
	CString strDecFilePath = m_CurFilePath;
	CString strText, str = strDecFilePath;
	/*while((pos = strDecFilePath.Find('\\')) >=0)
	{
		str+=strDecFilePath.Left(pos+1);
		strDecFilePath = strDecFilePath.Right(strDecFilePath.GetLength()-pos-1);
	}*/


	if(GetFileAttributes(str.GetBuffer(0)) == 0xFFFFFFFF)
	{
		strText.Format(_T("�ļ�������=%s !"), str);
		AfxMessageBox(strText);
		return;
	}

	strText.Format(_T("/select,%s"), str);
	//ShellExecute(NULL,_T("explore"),strText,NULL,NULL,SW_SHOWNORMAL);
	ShellExecute(NULL,_T("open"),_T("explorer.exe"),strText,NULL,SW_SHOWNORMAL);

}

void CResultShow::OnNMRClickAttachmentList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	int i, nCount;
	nCount = m_AttachmentList.GetItemCount();
	i = m_AttachmentList.GetFirstSelectedItem();
	if(i<0 || i>= nCount)
	{
		return;
	}

	POINT	point;
	GetCursorPos(&point);
	CString strFilePath = m_CurFilePath = m_AttachmentList.GetItemText(i,8);

	m_PopupMenu1.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
	
	*pResult = 0;
}
