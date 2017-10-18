// DlgParMng.cpp : implementation file
//

#include "stdafx.h"
#include "DlgParMng.h"
#include "DlgMdLoadIn.h"
#include "ModeXmlStruct.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDlgParMng dialog

CDlgParMng::CDlgParMng(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgParMng::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgParMng)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pShowModeStyle = NULL;
	m_pCurModeInfo = NULL;
}


void CDlgParMng::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgParMng)
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
	DDX_Control(pDX, IDC_TREE1, m_TreeCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgParMng, CDialog)
	//{{AFX_MSG_MAP(CDlgParMng)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BTN_LOAD_IN, OnBtnLoadIn)
	ON_BN_CLICKED(IDC_BTN_LOAD_OUT, OnBtnLoadOut)
	ON_BN_CLICKED(IDC_BTN_LOAD_STRUCT, OnBtnLoadStruct)
	ON_NOTIFY(NM_CLICK, IDC_TREE1, OnClickTree1)
	ON_BN_CLICKED(IDC_BTN_PAR_CHECK, OnBtnParCheck)
	ON_BN_CLICKED(IDC_BTN_SAVE_ALL, OnBtnSaveAll)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_LOAD_OUT_SRT, &CDlgParMng::OnBnClickedBtnLoadOutSrt)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgParMng message handlers

BOOL CDlgParMng::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	InitImageList();

	CEditableListCtrl *pEditList = (CEditableListCtrl*) GetDlgItem(IDC_LIST1);
	pEditList->EnableHotKey(FALSE);

	pEditList->AddStringToList(CALC_SIGN_KEY, COND_NULL			);
	pEditList->AddStringToList(CALC_SIGN_KEY, COND_BIG			);
	pEditList->AddStringToList(CALC_SIGN_KEY, COND_SMALL		);
	pEditList->AddStringToList(CALC_SIGN_KEY, COND_BIGEQUAL		);
	pEditList->AddStringToList(CALC_SIGN_KEY, COND_SMALLEQUAL	);
	pEditList->AddStringToList(CALC_SIGN_KEY, COND_EQUAL		);
	pEditList->AddStringToList(CALC_SIGN_KEY, COND_UNEQUAL		);
	pEditList->AddStringToList(CALC_SIGN_KEY,COND_BETWEEN_1		);
	pEditList->AddStringToList(CALC_SIGN_KEY,COND_BETWEEN_2		);
	//pEditList->BindListToItem(4,CALC_SIGN_KEY);

	InitSysInfo( );

	m_ListCtrl.EnableRClickMenu(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgParMng::InitSysInfo( )
{
	//CModeParMng *pPar = NULL;
	if(m_Type==1)
	{
		pPar = m_pShowModeStyle->m_pModeParMng;
		pXls  =m_pShowModeStyle->m_pExcelOptFun;
		pXml = m_pShowModeStyle->m_pModeXmlAnalysis;
		m_bTabCheck = &m_pShowModeStyle->m_bTabCheck;
	}
	CListCtrl   *pList = (CListCtrl *) GetDlgItem(IDC_LIST1);
	
	
	GetDlgItem(IDC_BTN_LOAD_IN)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_LOAD_OUT)->ShowWindow(FALSE);
	
	if (m_Type == 1)
	{
		//1.检验记录模板配置
		this->SetWindowText(TITLE_NAME_MODE_PAR_CFG);

		pPar->InitTree_TabStruct(&m_TreeCtrl);
		
		GetDlgItem(IDC_BTN_PAR_CHECK)->ShowWindow(TRUE);
		GetDlgItem(IDC_BTN_SAVE_ALL)->ShowWindow(TRUE);
		
		GetDlgItem(IDC_BTN_LOAD_STRUCT)->ShowWindow(TRUE);
		GetDlgItem(IDOK)->ShowWindow(TRUE);	

		//2017-03-02 Liuty Add: 根据模板的表初始化状态设置相关按钮的状态
		//-----------------------开始-----------------------------------//
		int nModeTabInit = m_pCurModeInfo->nInitTabSrt;

		int nUserType = g_LoginUsrInfo.nUserType;
		if(nUserType == user_normal)
		{
			GetDlgItem(IDC_BTN_SAVE_ALL)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_LOAD_STRUCT)->EnableWindow(FALSE);
			GetDlgItem(IDOK)->EnableWindow(FALSE);
		}else
		{
			GetDlgItem(IDC_BTN_SAVE_ALL)->EnableWindow(!nModeTabInit);
			GetDlgItem(IDC_BTN_LOAD_STRUCT)->EnableWindow(!nModeTabInit);
			GetDlgItem(IDOK)->EnableWindow(!nModeTabInit);
		}
		
		//-----------------------结束-----------------------------------//


		MyListCtrl_DeleteAllRowCol();
	}
	else
	{
		//2.产品历史极值信息
		this->SetWindowText(TITLE_NAME_PROD_HIS_CHK);

		pPar->InitTree_TabResult(&m_TreeCtrl);
		
		GetDlgItem(IDC_BTN_PAR_CHECK)->ShowWindow(FALSE);
		GetDlgItem(IDC_BTN_SAVE_ALL)->ShowWindow(FALSE);
		
		GetDlgItem(IDC_BTN_LOAD_STRUCT)->ShowWindow(FALSE);

		GetDlgItem(IDOK)->ShowWindow(TRUE);
		m_TableType = Prod_HisChk;

		
		MyListCtrl_DeleteAllRowCol();
		pPar->DisplayProdHisChk(pList);
	}
		
	m_nNum = 240; //300;
	m_PressFlag = 0;
	
	AdjustOnSize();
}

void CDlgParMng::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	AdjustOnSize();
}

int CDlgParMng::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here

	return 0;
}


//-----------------------------------------------------------------------------
void CDlgParMng::InitImageList()
{
	int nIcons[] = {
					IDI_LEV_1,  IDI_LEV_2,  IDI_LEV_3,	IDI_LEV_4, 	// 0 - 4： 目录树管理
					};
	
	m_TreeImgList.Create(16,16,ILC_COLOR32 | ILC_MASK,0,0);
	for(int i=0; i<sizeof(nIcons); i++)
	{
		m_TreeImgList.Replace(-1, LoadIcon(::AfxGetInstanceHandle(), 
			MAKEINTRESOURCE(nIcons[i])));
	}
	
	m_TreeCtrl.SetImageList(&m_TreeImgList, TVSIL_NORMAL);
}

void CDlgParMng::AdjustOnSize( )
{
	CRect  rect;
	int    x,y, nHeight, nWidth, nBord = 25, nBord2 = 30+25, nNum = 300;
	
	if ( !GetDlgItem(IDC_TREE1)->GetSafeHwnd() )
	{
		return;
	}
	
	GetClientRect(&rect);
	
	nNum = m_nNum;
	
	x = 0; 
	y = nBord;
	nWidth  = nNum - 5;
	nHeight = rect.Height() - nBord - nBord2;
	GetDlgItem(IDC_TREE1)->MoveWindow(x, y, nWidth, nHeight);
	
	//add move btn
	CRect  rect2;
	int    width, height;
	GetDlgItem(IDC_STATIC_MOVE)->GetClientRect(&rect2);
	width  = rect2.Width();
	height = rect2.Height();
	m_PressRect.left  = nWidth-4;
	m_PressRect.right = m_PressRect.left + width;
	m_PressRect.top   = nHeight+nBord;
	m_PressRect.bottom= m_PressRect.top + height; 
	GetDlgItem(IDC_STATIC_MOVE)->MoveWindow(m_PressRect);
	//end add
	
	
	GetDlgItem(IDC_STATIC_INF_1)->MoveWindow(x+3, y-20, 160, 18);
	
	x = nNum; 
	y = nBord;
	nWidth  = rect.Width()- nNum;
	nHeight = rect.Height() - nBord - nBord2;
	GetDlgItem(IDC_LIST1)->MoveWindow(x, y, nWidth, nHeight);
	
	GetDlgItem(IDC_STATIC_INF_2)->MoveWindow(x+3, y-20, 120, 18);
	
	
	int wLen=110, w=90,h=20+25;
	x = rect.Width() - 5*wLen;
	y = rect.Height() - 25 - 25;
	if (x < 0)
	{ 
		x = 0;
	}
	
	GetDlgItem(IDC_BTN_PAR_CHECK)->MoveWindow(10, y, w, h);
	GetDlgItem(IDC_BTN_SAVE_ALL)->MoveWindow(10+1*wLen, y, w, h);

	GetDlgItem(IDC_BTN_LOAD_IN)->MoveWindow(x+0*wLen, y, w, h);
	GetDlgItem(IDC_BTN_LOAD_OUT)->MoveWindow(x+1*wLen, y, w, h);
	GetDlgItem(IDC_BTN_LOAD_STRUCT)->MoveWindow(x+2*wLen, y, w, h);	
	GetDlgItem(IDC_BTN_LOAD_OUT_SRT)->MoveWindow(x+3*wLen, y, w, h);

	GetDlgItem(IDOK)->MoveWindow(x+4*wLen, y, w, h);
	GetDlgItem(IDCANCEL)->MoveWindow(x+5*wLen, y, w, h);
		
}


void CDlgParMng::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	if ( (point.x >= m_PressRect.left)  &&
		(point.x <= m_PressRect.right) &&
		(point.y >= m_PressRect.top)   &&
		(point.y <= m_PressRect.bottom)
		)
	{
		m_PressFlag = 1;
	}
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CDlgParMng::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	m_PressFlag = 0;
	
	CDialog::OnLButtonUp(nFlags, point);
}

void CDlgParMng::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	if (m_PressFlag != 0)
	{
		m_nNum = point.x;
		AdjustOnSize( );
	}
	
	CDialog::OnMouseMove(nFlags, point);
}

//-----------------------------------------------------------------------------

void CDlgParMng::OnBtnLoadIn() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgParMng::OnBtnLoadOut() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgParMng::OnBtnLoadStruct() 
{
	// TODO: Add your control notification handler code here
	CDlgMdLoadIn	dlg;
	CString			fileName, str;
	int				ret=0;
	//CExcelOptFun	*pXls = &g_pDlg->m_ExcelOptFun; 
	//CModeParMng		*pPar = &g_pDlg->m_ModeParMng;
		
	dlg.m_strPath = _T("C:\\Test_struct.xls");
	dlg.m_nType = 1;
	if (dlg.DoModal() == IDOK)
	{
		fileName = dlg.m_strPath;		

		//ztadd for 2016-9-13_V1.0.2
		pPar->ClearParamInfo(1);

		ret = pXls->ReadExcelFile_ContexMode2(fileName.GetBuffer(0));
		if (ret != 0)
		{
			*m_bTabCheck = pXls->CheckTabCellOk();
			str.Format("导入操作完毕! 行数=%d, 列数=%d", pXls->m_row, pXls->m_col);
			AfxMessageBox(str);
			if(m_Type == 1)
			{
				m_pShowModeStyle->CopyExcelDataToPar(pXls, pPar);
			}
			
			
			if (*m_bTabCheck != 0)
			{
				pPar->GetTabDataList( );							//获取数据列表
			}
		}
		else
		{
			str.Format("导入模板失败!");
			AfxMessageBox(str);
		}
	}

}


void CDlgParMng::OnOK() 
{
	// TODO: Add extra validation here
	//CModeParMng *pPar = NULL;
	/*if(m_Type==1)
	{
		pPar = &g_pDlg->m_ModeParMng;
	}else
	{
		pPar = &g_pHisDlg->m_ModeParMng;
	}*/
	/*CModeXmlAnalysis *pXml = NULL;
	if(m_Type==1)
	{
		pXml = &g_pDlg->m_ModeXmlAnalysis;
	}else
	{
		pXml = &g_pHisDlg->m_ModeXmlAnalysis;
	}*/
	
	CListCtrl	*pList = (CListCtrl *) GetDlgItem(IDC_LIST1);
	int         ret = -1;
	CString		str;

	switch (m_TableType)
	{
		
		case Tab_SizeInfo:
			{
				ret = pPar->SaveTabSizeInfo(pList);
				break;
			}			
		case Tab_HeadLen:
			{
				ret = pPar->SaveTabHeadLen(pList);
				break;
			}
		case Tab_ItemData:
			{
				ret = pPar->SaveTabItemData(pList);
				break;
			}
		case Tab_ItemFlag:
			{
				//pPar->DisplayTabItemFlag(pList);
				break;
			}
		case Tab_CellSrt:
			{
				ret = pPar->SaveTabCellSrt(pList);
				if (ret != 0)
				{
					AfxMessageBox("设置成功!");
					pPar->DisplayTabCellSrt(pList);
				}
				break;
			}			
		case Tab_RowSrt:
			{
				pPar->SaveTabRowSrt(pList);
				break;
			}				
		case Tab_ColSrt:
			{
				pPar->SaveTabColSrt(pList);
				break;
			}
		case Tab_DataSrt:
			{	
				//pPar->SaveTabOutDataSrt(pList);
				break;
			}
		case Tab_AlarmSrt:
			{
				pPar->SaveTabAlarmSrt(pList);
				break;
			}	
		case Prod_HisChk:
			{
				MyListCtrl_DeleteAllRowCol();
				pPar->DisplayProdHisChk(pList);

				if (0 != pPar->SaveProdHisChk(pList))
				{
					pXml->SetXmlMdTabHisInfo();
					AfxMessageBox("设置成功!");
				}
				
				break;
			}
		default:
			{
				AfxMessageBox("Error Type");
			}
	}

	if (ret != -1)
	{
		str.Format( _T("ret=%d"), ret);
		AfxMessageBox(str);
	}
	
	//CDialog::OnOK();
}

//-----------------------------------------------------------------------------

void CDlgParMng::OnClickTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	//CModeParMng *pPar = NULL;
	/*if(m_Type==1)
	{
		pPar = &g_pDlg->m_ModeParMng;
	}else
	{
		pPar = &g_pHisDlg->m_ModeParMng;
	}*/
	CTreeCtrl *pTree = (CTreeCtrl*) GetDlgItem(IDC_TREE1);
	CListCtrl *pList = (CListCtrl *) GetDlgItem(IDC_LIST1);
	
	TVHITTESTINFO	tvhtif;
	GetCursorPos(&tvhtif.pt);
	pTree->ScreenToClient(&tvhtif.pt);
	pTree->HitTest(&tvhtif);
	
	if(tvhtif.flags & TVHT_ONITEM)
	{
		int nIcon1, nIcon2;
		pTree->GetItemImage(tvhtif.hItem, nIcon1, nIcon2);
		CString strItem = pTree->GetItemText(tvhtif.hItem);
		if(strItem.IsEmpty())
			return;
		int nTreeID = pTree->GetItemData(tvhtif.hItem);
		
		// nTreeID  ： 目录树ID
		// strItem  ： 目录树名称
		// nIcon1   ： ICO位置值
		
		int		nIconIndex = nIcon1;
		CString str;
		int     Num = 0;
		
		if (nTreeID > 0)
		{
			m_TableType = nTreeID;
			
			switch (nTreeID )
			{
				
				case Tab_SizeInfo:
					{
					MyListCtrl_DeleteAllRowCol();
					pPar->DisplayTabSizeInfo(pList);
					break;
					}
				
				case Tab_HeadLen:
					{
					MyListCtrl_DeleteAllRowCol();
					pPar->DisplayTabHeadLen(pList);
					break;
					}
				case Tab_ItemData:
					{
						MyListCtrl_DeleteAllRowCol();
						pPar->DisplayTabItemData(pList);
						break;
					}
				case Tab_ItemFlag:
					{
						MyListCtrl_DeleteAllRowCol();
						pPar->DisplayTabItemFlag(pList);
						break;
					}
				case Tab_CellSrt:
					{
						MyListCtrl_DeleteAllRowCol();
						pPar->DisplayTabCellSrt(pList);
						break;
					}
				
				case Tab_RowSrt:
					{
						MyListCtrl_DeleteAllRowCol();
						pPar->GetTabDataRowAndColNameFlag();
						pPar->DisplayTabRowSrt(pList);
						break;
					}
					
				case Tab_ColSrt:
					{
						MyListCtrl_DeleteAllRowCol();	
						pPar->GetTabDataRowAndColNameFlag();
						pPar->DisplayTabColSrt(pList);
						break;
					}
				case Tab_DataSrt:
					{
						MyListCtrl_DeleteAllRowCol();
						pPar->GetTabDataList( );							//获取数据列表
						pPar->DisplayTabOutDataSrt(pList);
						break;
					}
				case Tab_AlarmSrt:
					{
						MyListCtrl_DeleteAllRowCol();
						pPar->DisplayTabAlarmSrt(pList);
						break;
					}

				case Prod_HisChk:
					{
						MyListCtrl_DeleteAllRowCol();
						pPar->DisplayProdHisChk(pList);
						break;
					}

				default:
					{
						//AfxMessageBox("Error");
					}
			}
		}
	}

	*pResult = 0;
}

void CDlgParMng:: MyListCtrl_DeleteAllRowCol( )
{
	CListCtrl *pList = (CListCtrl *) GetDlgItem(IDC_LIST1);
	
	//pList->SetExtendedStyle(pList->GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	
	pList->DeleteAllItems();
	
	if (pList->GetHeaderCtrl() != NULL)
	{
		while (pList->GetHeaderCtrl()->GetItemCount() > 0)
		{	
			pList->DeleteColumn(0);
		}
	}
	
	m_ListCtrl.RemoveAllEditCell();
	m_ListCtrl.ResetAllItemColor();
	m_ListCtrl.UnBindListToItem(4);
}



void CDlgParMng::OnBtnParCheck() 
{
	// TODO: Add your control notification handler code here
	//CModeParMng  *pPar = &g_pDlg->m_ModeParMng;
	CString		 str;
	int          bDataChkFlag = 0;
	*m_bTabCheck = pPar->CheckTabCellOk();
	str.Format("row=%d, col=%d, Check=%d", pPar->m_row, pPar->m_col, *m_bTabCheck);	
	if (*m_bTabCheck == 0)
	{
		AfxMessageBox(str);
	}
	else
	{
		bDataChkFlag = pPar->CheckTabDataRowAndColNotNull( );			//检测TabData行和列不为空
		str.Format(_T("表结构检测:TabSrtCheck=%d, 输出数据名称检测:TabDataCheck=%d"), 
					bDataChkFlag, bDataChkFlag);
		AfxMessageBox(str);
	}
	
	if (*m_bTabCheck != 0)
	{
		pPar->GetTabDataList( );							//获取数据列表
	}
}

void CDlgParMng::OnBtnSaveAll() 
{
	/*if(BuildTabAndSaveModeXMLToDb())
	{
		AfxMessageBox("保存完毕!");
	}else
	{
		AfxMessageBox(_T("创建表失败"));
	}*/

	pXml->SetXmlMdTabSrtInfo();
	pXml->SetXmlMdTabHisInfo();		//设置模板表_历史极值检测

//保存XML到数据库//
	if(SaveModeXmlToDb())
	{
		AfxMessageBox("保存完毕!");
	}else
	{
		AfxMessageBox("保存失败");
	}
	
}
BOOL CDlgParMng::SaveModeXmlToDb()
{
	char strFilePath[512] = {0};
	char *strFileInfo;
	int nLen = 0;
	StBasMode *nModeInfo = m_pCurModeInfo;

	memset(strFilePath,0,512);
	pXml->GetCurModeXmlFileName(MD_XML_FILE_TAB_SRT_INFO, strFilePath);
	ReadFile(strFilePath,&strFileInfo,nLen);
	
	CString str;
	int bCalType = 0;
	bCalType = pPar->IsTableCalType();
	str.Format("bCalType=%d", bCalType);
	//AfxMessageBox(str);
	
	nModeInfo->nFormula = bCalType;
	//int Long = file.Seek(0,SEEK_END);
	//int Size = file.Seek(0,SEEK_SET);

	nModeInfo->Release();
	if(!m_DMng.UpdateModeXmlFile(nModeInfo->nOid,strFileInfo,nLen))
	{
		delete []strFileInfo;
		if(nModeInfo->nOid <= 0)
		{
			AfxMessageBox(_T("请先保存模板基本信息, 在导入模板样式!"));
		}
		return FALSE;
	}
	nModeInfo->nModeSize = nLen;
	nModeInfo->pXmlFile = new char[nModeInfo->nModeSize+1];
	memset(nModeInfo->pXmlFile,0,nModeInfo->nModeSize+1);
	memcpy(nModeInfo->pXmlFile,strFileInfo,nModeInfo->nModeSize);

	delete []strFileInfo;
	//更新 字段 模板大小//
	if(!m_DMng.EditOldMode(nModeInfo))
	{
		AfxMessageBox(_T("模板大小更新失败"));
		return FALSE;
	}

	m_pShowModeStyle->m_pShowModeInfo->DisPalyModeInfo();
	return TRUE;
}




void CDlgParMng::OnBnClickedBtnLoadOutSrt()
{
	CDlgMdLoadIn	dlg;
	CString			fileName, str;
	int				ret=0;
	CExcelOptFun	*pXls = m_pShowModeStyle->m_pExcelOptFun; 
	CModeParMng		*pPar = m_pShowModeStyle->m_pModeParMng;


	if ( (pPar->m_row <= 0) || (pPar->m_col<= 0) )
	{
		AfxMessageBox( _T("表格行数和列数不能为零!") );
		return;
	}
	if (pPar->CheckTabCellOk() == 0)
	{
		AfxMessageBox( _T("表格结构检测异常，无法导出!") );
		return;
	}

	dlg.m_strPath = _T("C:\\Test_struct_out.xls");
	dlg.m_nType = 2;
	if (dlg.DoModal() == IDOK)
	{
		fileName = dlg.m_strPath;	

		m_pShowModeStyle->CopyParDataToExcel(pPar, pXls);

		ret = pXls->WriteExcelFile_ContexMode(fileName.GetBuffer(0));
		if (ret != 0)
		{
			//AfxMessageBox(_T("导出操作完毕!") );
		}
		else
		{
			str.Format("ret=%d", ret);
			AfxMessageBox(str);
		}
	}
}
