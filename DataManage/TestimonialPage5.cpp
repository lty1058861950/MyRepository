// TestimonialPage5.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "TestimonialPage5.h"
#include "ModeXmlStruct.h"

// CTestimonialPage5 对话框

IMPLEMENT_DYNAMIC(CTestimonialPage5, CDialog)

CTestimonialPage5::CTestimonialPage5(CWnd* pParent /*=NULL*/)
	: CDialog(CTestimonialPage5::IDD, pParent)
{
	m_pPage5Info = NULL;
	m_pGrid = NULL;
}

CTestimonialPage5::~CTestimonialPage5()
{
	if(m_pGrid != NULL)
	{
		delete m_pGrid;
	}
}

void CTestimonialPage5::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTestimonialPage5, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CTestimonialPage5 消息处理程序

BOOL CTestimonialPage5::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_Font1.CreateFont(32,0,0,0,FW_SEMIBOLD,0,0,0,134,3,2,1,2,_T("Arial"));	//大标题
	m_Font2.CreateFont(18,0,0,0,FW_SEMIBOLD,0,0,0,134,3,2,1,2,_T("宋体"));	//页数
	m_Font3.CreateFont(16,0,0,0,0,0,0,0,134,3,2,1,2,_T("宋体"));	//数据项

	GetDlgItem(IDC_STATIC1)->SetFont(&m_Font2);

	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CTestimonialPage5::DispalyPageInfo()
{
	StBasTestimonialPage5 *pPage5Info = m_pPage5Info;
	vector<StBasPage5ProductSort> *pProdInfo = &pPage5Info->stProdSortArray;
	int i, pos, nRow;
	int nBegrow;
	CString str;
	str.Format(_T("%s"), pPage5Info->szTitle);
	GetDlgItem(IDC_STATIC1)->SetWindowText(str);
	CGridCtrl *pList = m_pGrid;

	DispalyModeStyle();
	nBegrow = 2;
	nRow = pProdInfo->size();
	for (i = nBegrow;i< nRow+nBegrow; i++)
	{
		pos = 2;
		m_pGrid->SetItemText(i, pos++,pProdInfo->at(i-nBegrow).szProductName);
		m_pGrid->SetItemText(i, pos++,pProdInfo->at(i-nBegrow).szProductNo);
		m_pGrid->SetItemText(i, pos++,pProdInfo->at(i-nBegrow).szProductCode);
		m_pGrid->SetItemText(i, pos++,pProdInfo->at(i-nBegrow).szUnitName);
		m_pGrid->SetItemText(i, pos++,pProdInfo->at(i-nBegrow).szRemark);
	}
}

void CTestimonialPage5::GetPageInfo()
{
	/*int i, nCount;
	CModeParMng *pPar = m_pModeParMng;
	int          nDataPos,nItemFlag = 0;
	char         *pItemInfo = NULL;
	int          nTmpDataPos= 0;*/


	
	StBasTestimonialPage5 *pPage5Info = m_pPage5Info;
	vector<StBasPage5ProductSort> *pStProdSortArray = &pPage5Info->stProdSortArray;//2.产品配套表的产品
	pStProdSortArray->clear();

	StBasPage5ProductSort stProdSort;
	int pos;
	int row, col;
	int nRowNum, nColNum;
	CString str;
	nRowNum = m_pGrid->GetRowCount();
	nColNum = m_pGrid->GetColumnCount();

	int nBegRow = 2,nEndRow = nRowNum;
	int nBegCol = 2,nEndCol = nColNum;

	for(row=nBegRow; row<nEndRow; row++)
	{
		memset(&stProdSort, 0, sizeof(StBasPage5ProductSort));
		pos=nBegCol;

		str = m_pGrid->GetItemText(row, pos++);
		str = str.TrimLeft();
		str = str.TrimRight();
		strcpy(stProdSort.szProductName, str);

		str = m_pGrid->GetItemText(row, pos++);
		str = str.TrimLeft();
		str = str.TrimRight();
		strcpy(stProdSort.szProductNo, str);

		str = m_pGrid->GetItemText(row, pos++);
		str = str.TrimLeft();
		str = str.TrimRight();
		strcpy(stProdSort.szProductCode, str);

		str = m_pGrid->GetItemText(row, pos++);
		str = str.TrimLeft();
		str = str.TrimRight();
		strcpy(stProdSort.szUnitName, str);

		str = m_pGrid->GetItemText(row, pos++);
		str = str.TrimLeft();
		str = str.TrimRight();
		strcpy(stProdSort.szRemark, str);


	}
}
void CTestimonialPage5::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnOK();
}

void CTestimonialPage5::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	AutoSize();
}

void CTestimonialPage5::DispalyModeStyle()
{
	//拷贝文件到  指定路径//
	CString str1, str2;
	str1.Format(_T("%s\\%s\\%s"), g_WorkPath, Report_Mode_Path, _T("TestimonialPage5.txt"));

	str2.Format(_T("%s\\%s\\%s"), g_WorkPath, PATH_XML_MODE_PAR_CFG, MD_XML_FILE_TAB_SRT_INFO);

	CopyFile(str1,str2,0);
	m_pModeParMng->ClearParamInfo();

	//1.获取模板结构
	m_pModeXmlAnalysis->GetXmlMdTabSrtInfo();			
	m_pModeParMng->GetItemFlagFromData( );             //从ItemData获取ItemFlag

	m_pGrid = InitGridCtrl_MUL(this,m_pModeParMng, m_pGrid);
	//InitGridCtrl_MUL();
	PostMessage(WM_SIZE);
}

void CTestimonialPage5::AutoSize()
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



void CTestimonialPage5::InitGridCtrl()
{
	CWnd *pWnd;
	int nRowCnt = 16, nColCnt = 6;
	int  row,col;
	StTabCell    *pTabCell = NULL;
	int			nDataPos;
	CString       str, str2;
	char *ColName[] = {"序号","产品名称","产品代号","出场编号(软件版本号)","生产单位",
		"备注"};
	int  ColWidth[] = {60,150,150,200,150,  150};

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

				//if(row==0 && col==0)
				//{
				//	Item.nFormat = DT_WORDBREAK|DT_VCENTER|DT_CENTER;//;
				//	Item.strText.Format(" ");
				//}
				if(row < 1)
				{
					Item.nFormat = DT_WORDBREAK|DT_VCENTER|DT_CENTER;//|DT_VCENTER;
					//Item.strText.Format("%C", col+0x40);
					Item.strText.Format("\n%s", ColName[col]);
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
		m_pGrid->AutoSizeRows();      //自动设置行高

		//---------------------------------------------------------
		for(col=0; col<m_pGrid->GetColumnCount(); col++)
		{
			m_pGrid->SetColumnWidth(col, ColWidth[col]);
		}

		for(row=0; row<m_pGrid->GetRowCount(); row++)
		{
			m_pGrid->SetRowHeight(row, 60);
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
