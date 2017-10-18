
#pragma once
#include "StdAfx.h"
#include "MyListCtrl/EditableListCtrl.h"
#include "ModeXmlStruct.h"
#include <vector>
using namespace std;

static int g_nFirstWidth = 100;
static int g_nColWidth = 120;

#ifndef GLOB_QUEUE_DEFINE
void SetListColor(CEditableListCtrl*pList,int iCol)
{
	CHeaderCtrl * pHead= pList->GetHeaderCtrl() ;
	int iHeadTotal= pHead->GetItemCount();

	for(int i=0;i<pList->GetItemCount();i++)
	{
		for (int j=0;j<iHeadTotal;j++)
		{
			if (i%2)
				pList->SetItemColor(i,j,DEF_COL_WHITE) ;
			else
				pList->SetItemColor(i,j,DEF_COL_BLUE) ;
		}
	}
}

CGridCtrl * InitGridCtrl_MUL(CWnd *pWnd, CModeParMng *m_pModeParMng, CGridCtrl *m_pGrid )
{
	//CWnd *pWnd;
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

	//pWnd = this; //	pWnd = GetDlgItem(IDC_STATIC_AREA);

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
		GetClientRect(pWnd->m_hWnd,&rc);
		m_pGrid->Create(rc, pWnd, 10011, WS_CHILD|WS_VISIBLE);
		//PostMessage(pWnd->m_hWnd,WM_SIZE,0,0);
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
		int nLiu = 0;
		for(row=0; row<m_pGrid->GetRowCount(); row++)
		{
			for(col=0; col<m_pGrid->GetColumnCount(); col++)
			{
				GV_ITEM Item;
				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = row;
				Item.col = col;


				nLiu = 0;

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


						nLiu = 1;
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

				if(nLiu)
				{
					m_pGrid->SetItemState(row,col, m_pGrid->GetItemState(row,col) | GVIS_MODIFIED);

				}else
				{
					m_pGrid->SetItemState(row,col, m_pGrid->GetItemState(row,col) | GVIS_READONLY);

				}
				
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

	return m_pGrid;
}






HTREEITEM MyInsertTree( CTreeCtrl *pTree, CString strName, HTREEITEM hParent, UINT Param )
{
	TV_ITEM			tvItem;
	TV_INSERTSTRUCT tvInsert;
	HTREEITEM		ret;

	tvItem.mask				= TVIF_TEXT|TVIF_PARAM;
	tvItem.cchTextMax		= 15;
	tvItem.pszText			= strName.GetBuffer(24);
	tvItem.lParam			= Param; 

	tvInsert.hParent		= hParent;
	tvInsert.hInsertAfter	= TVI_LAST;
	tvInsert.item			= tvItem; 
	ret						= pTree->InsertItem(&tvInsert);

	return ret;
}


HTREEITEM MyInsertTree( CTreeCtrl *pTree, CString strName, HTREEITEM hParent, UINT Param, UINT iPosIco)
{
	TV_ITEM			tvItem;
	TV_INSERTSTRUCT tvInsert;
	HTREEITEM		ret;

	tvItem.mask				= TVIF_TEXT|TVIF_PARAM;
	tvItem.cchTextMax		= 15;
	tvItem.pszText			= strName.GetBuffer(24);
	tvItem.lParam			= Param; 

	tvInsert.hParent		= hParent;
	tvInsert.hInsertAfter	= TVI_LAST;
	tvInsert.item			= tvItem; 
	ret						= pTree->InsertItem(&tvInsert);

	pTree->SetItemImage(ret, iPosIco, iPosIco);	

	return ret;
}

HTREEITEM MyInsertTree( CTreeCtrl *pTree, CString strName, HTREEITEM hParent, UINT Param, UINT iPosIco1, UINT iPosIco2)
{
	TV_ITEM			tvItem;
	TV_INSERTSTRUCT tvInsert;
	HTREEITEM		hItem;

	tvItem.mask				= TVIF_TEXT|TVIF_PARAM;
	tvItem.cchTextMax		= 15;
	tvItem.pszText			= strName.GetBuffer(24);
	tvItem.lParam			= Param; 

	tvInsert.hParent		= hParent;
	tvInsert.hInsertAfter	= TVI_LAST;
	tvInsert.item			= tvItem; 
	hItem					= pTree->InsertItem(&tvInsert);

	pTree->SetItemImage(hItem, iPosIco1, iPosIco2);	

	return hItem;
}
CString SQLText(CString nFontText)
{
	if(nFontText.IsEmpty())
	{
		return _T(" is null");
	}else
	{
		CString strSqlText;
		strSqlText.Format(_T("='%s'"),nFontText);
		return strSqlText;
	}

}
//�ж��ļ��Ƿ����//
BOOL PubFun_IsFileExist(char* pFilename)
{
	HANDLE h;
	LPWIN32_FIND_DATA pFD=new WIN32_FIND_DATA;
	BOOL bFound=FALSE;

	if (pFD)
	{
		h=FindFirstFile(pFilename, pFD);
		bFound=(h!=INVALID_HANDLE_VALUE);
	}

	delete pFD;
	pFD = NULL;

	return bFound;
}

//����ת����ID��///
CString GetStringID(int ID)
{
	CString strID;
	strID.Format(_T("%d"),ID);
	int nLen = g_IdLen-strID.GetLength();

	for(int i = 0;i<nLen;i++)
	{
		strID = _T("0")+strID;
	}

	return strID;
}
BOOL StringToTime(const char *strTime,const char *FarmatStr,SYSTEMTIME &nSysTime)
{
	int year,month,day,hour,minute,second;
	if(-1==sscanf(strTime,FarmatStr,&year,&month,&day,&hour,&minute,&second))
	{
		return FALSE;
	}

	nSysTime.wYear = year;
	nSysTime.wMonth = month;
	nSysTime.wDay = day;
	nSysTime.wHour = hour;
	nSysTime.wMinute = minute;
	nSysTime.wSecond = second;
	return TRUE;
}
CString GetDateString()
{
	SYSTEMTIME systime;
	CString szTime;
	GetLocalTime(&systime);		
	szTime.Format("%04d-%02d-%02d",systime.wYear,systime.wMonth,systime.wDay);
	return szTime;
}
CString GetTimeString()
{
	SYSTEMTIME systime;
	CString szTime;
	GetLocalTime(&systime);
	szTime.Format("%02d:%02d:%02d",systime.wHour,systime.wMinute,systime.wSecond);
	return szTime;
}

void GetSysDateTime(char *szDateTime)
{
	CTime	t = CTime::GetCurrentTime();
	int		year	= t.GetYear();
	int		month	= t.GetMonth();
	int		day		= t.GetDay();
	int		hour	= t.GetHour();
	int		minute	= t.GetMinute();
	int		second	= t.GetSecond();
	CString strDateTime;

	strDateTime.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"), year,month,day,hour,minute,second);

	strcpy(szDateTime, strDateTime.GetBuffer(0));
	return;
}
CString GetDateTimeString2()
{
	SYSTEMTIME systime;
	CString szTime;
	GetLocalTime(&systime);		
	//szTime.Format("%04d-%02d-%02d ��%d %02d:%02d:%02d:%02d",systime.wYear,systime.wMonth,systime.wDay,systime.wDayOfWeek,
	//	systime.wHour,systime.wMinute,systime.wSecond,systime.wMilliseconds);
	szTime.Format("%04d-%02d-%02d_%02d_%02d",systime.wYear,systime.wMonth,systime.wDay,
		systime.wHour,systime.wMinute);
	return szTime;
}

CString GetDateTimeString()
{
	SYSTEMTIME systime;
	CString szTime;
	GetLocalTime(&systime);		
	//szTime.Format("%04d-%02d-%02d ��%d %02d:%02d:%02d:%02d",systime.wYear,systime.wMonth,systime.wDay,systime.wDayOfWeek,
	//	systime.wHour,systime.wMinute,systime.wSecond,systime.wMilliseconds);
	szTime.Format("%04d-%02d-%02d %02d:%02d:%02d",systime.wYear,systime.wMonth,systime.wDay,
		systime.wHour,systime.wMinute,systime.wSecond);
	return szTime;
}

CString GetDateTimeFileNameString()
{
	SYSTEMTIME systime;
	CString szTime;
	GetLocalTime(&systime);		
	//szTime.Format("%04d-%02d-%02d ��%d %02d:%02d:%02d:%02d",systime.wYear,systime.wMonth,systime.wDay,systime.wDayOfWeek,
	//	systime.wHour,systime.wMinute,systime.wSecond,systime.wMilliseconds);
	szTime.Format("%04d-%02d-%02d %02d_%02d_%02d",systime.wYear,systime.wMonth,systime.wDay,
		systime.wHour,systime.wMinute,systime.wSecond);
	return szTime;
}

//������(int)��ֵ �ϳ� һ��(int)///
//Flag��ʾ ��һ������ �ϳɺ�ռ��λ,��32λ//
int  NumTwoToOne(int &Num,int Num1,int Num2)
{
	Num = 0;
	if(Num1>0xff)
	{
		return 0;
	}
	if(Num2>0xffffff)
	{
		return 0;
	}
	Num1 = Num1<<(32-G_TREEID);
	Num2 = Num2&0xffffff;

	Num = Num1+Num2;
	return 1;

}

int NumOneToTwo(int Num,int &Num1,int &Num2)
{
	Num1 = 0;
	Num2 = 0;
	Num1 = Num>>(32-G_TREEID);
	Num2 = Num&0xffffff;

	return 1;

}

//ɾ��ָ��·�����ļ�//
int DelFile()
{
	CString strPath;
	strPath.Format( _T("%s//%s//%s"),
		g_WorkPath, 
		PATH_XML_MODE_PAR_CFG, 
		MD_XML_FILE_TAB_OUT_INFO);//�����ļ�//

	remove(strPath);

	strPath.Format( _T("%s//%s//%s"),
		g_WorkPath, 
		PATH_XML_MODE_PAR_CFG, 
		MD_XML_FILE_TAB_SRT_INFO);//ģ�������ļ�//

	remove(strPath);
	strPath.Format( _T("%s//%s//%s"),
		g_WorkPath, 
		PATH_XML_MODE_PAR_CFG, 
		MD_XML_FILE_TAB_HIS_INFO);//��ʷ��ֵ�ļ�//

	remove(strPath);
	return 1;
}

void ReportError() 
{ 
	LPVOID lpMsgBuf;
	DWORD dw = GetLastError(); 

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpMsgBuf,
		0, NULL );
	CString str;
	str.Format( _T("ErrCode=%d, %s"), dw, (char*)lpMsgBuf);
	AfxMessageBox(str);

	LocalFree(lpMsgBuf);
}

int  ReadFile(char *szFilePath,char **pFileInfo,int &nLen)
{
	CFile nFile;
	if(!nFile.Open(szFilePath, CFile::shareDenyNone /*| CFile::modeCreate*/ | CFile::modeRead |CFile::modeNoTruncate))
	{
		ReportError();
		return FALSE;
	}
	nLen = 0;
	nLen = nFile.GetLength();
	*pFileInfo = new char[nLen+1];
	memset(*pFileInfo, 0, nLen+1);
	nFile.Read(*pFileInfo,nLen);
	nFile.Close();
	return 1;
}


int GetTaskIcon(int TaskState)
{
	return TaskState+4;
}
int GetUserTypeIndex(char *szUserType)
{
	int i;
	for(i = 0;i<3;i++)
	{
		if(strcmp(szUserType,g_UserType[i]) == 0)
		{
			return i;
		}
	}
	return 0;
}
int GetUserStatusIndex(char *szUserStatus)
{
	int i;
	for(i = 0;i<2;i++)
	{
		if(strcmp(szUserStatus,g_UserStatus[i]) == 0)
		{
			return i;
		}

	}
	return 0;
}

int  ReleaseProducts(vector<StBasProduct *> *pSelProducts)
{
	int i,nCount = 0;
	nCount = pSelProducts->size();
	for (i = 0;i<nCount;i++)
	{
		delete pSelProducts->at(i);

	}
	pSelProducts->clear();
	return 1;
}

int  ReleaseGroups(vector<StHrGroup *> *pStHrGroupArry)
{
	int i,nCount = 0;
	nCount = pStHrGroupArry->size();
	for (i = 0;i<nCount;i++)
	{
		delete pStHrGroupArry->at(i);

	}
	pStHrGroupArry->clear();
	return 1;
}

int  ReGetAllGroupInfo()
{
	ReleaseGroups(&g_AllGroups);
	if(m_DMng.GetAllValidGroup(&g_AllGroups))
	{
		return 1;
	}
	return 0;
}

int  ReGetAllDepartInfo()
{
	g_AllUpDeparts.clear();
	if(m_DMng.GetAllUpDepart(&g_AllUpDeparts))
	{
		return 1;
	}
	return 0;
}
int  ReleaseRoles(vector<StHrRole *> *pStHrRoleArry)
{
	int i,nCount = 0;
	nCount = pStHrRoleArry->size();
	for (i = 0;i<nCount;i++)
	{
		delete pStHrRoleArry->at(i);

	}
	pStHrRoleArry->clear();
	return 1;
}

int  AddNewProductToConfig(StBasProduct *pProductInfo)
{
	StBasProduct *pProduct = new StBasProduct;
	memset(pProduct,0,sizeof(StBasProduct));
	memcpy(pProduct,pProductInfo,sizeof(StBasProduct));
	g_SelProducts.push_back(pProduct);
	CString strUserLogName = g_LoginUsrInfo.szLoginName;
	if(!strUserLogName.IsEmpty())
	{
		g_UserConfig.SetSelProductConfig(strUserLogName,&g_SelProducts);
	}

	CreateSQLSelProducts(&g_SelProducts);
	return 1;
}

int   DelProductToConfig(StBasProduct *pProductInfo)
{
	int i,nCount = 0;
	vector<StBasProduct *> nProducts;
	StBasProduct *pStBasProd;

	nCount = g_SelProducts.size();
	nProducts.clear();
	for (i = 0;i<nCount;i++)
	{
		if(pProductInfo->nOid != g_SelProducts.at(i)->nOid)
		{
			pStBasProd = new StBasProduct;
			memset(pStBasProd,0,sizeof(StBasProduct));
			memcpy(pStBasProd,g_SelProducts.at(i),sizeof(StBasProduct));
			nProducts.push_back(pStBasProd);
		}else
		{
			i = i;	
		}
		
	}
	ReleaseProducts(&g_SelProducts);

	nCount = nProducts.size();
	for (i = 0;i<nCount;i++)
	{
		pStBasProd = new StBasProduct;
		memset(pStBasProd,0,sizeof(StBasProduct));
		memcpy(pStBasProd,nProducts.at(i),sizeof(StBasProduct));
		g_SelProducts.push_back(pStBasProd);
	}
	ReleaseProducts(&nProducts);

	CString strUserLogName = g_LoginUsrInfo.szLoginName;
	if(!strUserLogName.IsEmpty())
	{
		g_UserConfig.SetSelProductConfig(strUserLogName,&g_SelProducts);
	}

	CreateSQLSelProducts(&g_SelProducts);
	return 1;
}
//�����û�ѡ�еĲ�Ʒ�齨SQL���//
int  CreateSQLSelProducts(vector<StBasProduct *> *pArrayProduct)
{
	g_strSelProdsSQL = _T("");
	int i, nCount = pArrayProduct->size();
	CString str;
	if(nCount>0)
	{
		g_strSelProdsSQL.Format(_T("OID in("));
	}else
	{
		g_strSelProdsSQL.Format(_T("OID in(0)"));
	}
	for (i = 0;i<nCount;i++)
	{
		if(i>=nCount-1)
		{
			str.Format(_T("%d)"),pArrayProduct->at(i)->nOid);
		}else
		{
			str.Format(_T("%d,"),pArrayProduct->at(i)->nOid);
		}
		
		g_strSelProdsSQL+=str;
	}
	return 1;
}

CString BuildReportModeFilePath(StBasMode *pModeInfo)//�齨����ģ��·��//
{
	CString strFilePath,strFilePath1,strFilePath2;
	strFilePath1.Format(_T("%s\\%s"),g_WorkPath,Report_Mode_Path);
	if(GetFileAttributes(strFilePath1.GetBuffer(0)) == 0xFFFFFFFF)
	{
		CreateDirectory(strFilePath1.GetBuffer(0),NULL);
	}

	strFilePath2.Format(_T("%s\\%s"),strFilePath1,g_CurSelDepart.szGroupName);
	if(GetFileAttributes(strFilePath2.GetBuffer(0)) == 0xFFFFFFFF)
	{
		CreateDirectory(strFilePath2.GetBuffer(0),NULL);
	}

	switch(pModeInfo->nModeType)
	{
	case Mode_Currency:
		{
			strFilePath1.Format(_T("%s\\%s"),strFilePath2,g_ModeType[pModeInfo->nModeType]);
			if(GetFileAttributes(strFilePath1.GetBuffer(0)) == 0xFFFFFFFF)
			{
				CreateDirectory(strFilePath1.GetBuffer(0),NULL);
			}
			strFilePath2.Format(_T("%s\\%s%s"),strFilePath1,pModeInfo->szModeName,Report_FILE_EX);
			strFilePath = strFilePath2;
		}
		break;
	case Mode_Dedicated:
		{
			strFilePath1.Format(_T("%s\\%s"),strFilePath2,g_ModeType[pModeInfo->nModeType]);
			if(GetFileAttributes(strFilePath1.GetBuffer(0)) == 0xFFFFFFFF)
			{
				CreateDirectory(strFilePath1.GetBuffer(0),NULL);
			}

			strFilePath2.Format(_T("%s\\%s"),strFilePath1,pModeInfo->stProductInfo.szProductNo);
			if(GetFileAttributes(strFilePath2.GetBuffer(0)) == 0xFFFFFFFF)
			{
				CreateDirectory(strFilePath2.GetBuffer(0),NULL);
			}

			strFilePath1.Format(_T("%s\\%s%s"),strFilePath2,pModeInfo->szModeName,Report_FILE_EX);
			strFilePath = strFilePath1;


		}
		break;
	case Mode_LineDed:
		{
			strFilePath1.Format(_T("%s\\%s"),strFilePath2,g_ModeType[pModeInfo->nModeType]);
			if(GetFileAttributes(strFilePath1.GetBuffer(0)) == 0xFFFFFFFF)
			{
				CreateDirectory(strFilePath1.GetBuffer(0),NULL);
			}
			strFilePath2.Format(_T("%s\\%s%s"),strFilePath1,pModeInfo->szModeName,Report_FILE_EX);
			strFilePath = strFilePath2;
		}
		break;
	case Mode_NotUse:
		{
			strFilePath1.Format(_T("%s\\%s"),strFilePath2,g_ModeType[pModeInfo->nModeType]);
			if(GetFileAttributes(strFilePath1.GetBuffer(0)) == 0xFFFFFFFF)
			{
				CreateDirectory(strFilePath1.GetBuffer(0),NULL);
			}
			strFilePath2.Format(_T("%s\\%s%s"),strFilePath1,pModeInfo->szModeName,Report_FILE_EX);
			strFilePath = strFilePath2;
		}
		break;
	default:
		break;
	}

	return strFilePath;
}

CString BuildModeFormulaFilePath(char *szRelativePath, StBasMode *pModeInfo, int nOutType)//�齨ģ�幫ʽ�ļ�·��//
{
	CString strFilePath,strFilePath1,strFilePath2;
	strFilePath1.Format(_T("%s\\%s"),szRelativePath,Mode_Formula_Path);
	if(GetFileAttributes(strFilePath1.GetBuffer(0)) == 0xFFFFFFFF)
	{
		CreateDirectory(strFilePath1.GetBuffer(0),NULL);
	}

	if(nOutType == 1)
	{
		strFilePath2 = strFilePath1;
	}else
	{
		strFilePath2.Format(_T("%s\\%s"),strFilePath1,g_CurSelDepart.szGroupName);
		if(GetFileAttributes(strFilePath2.GetBuffer(0)) == 0xFFFFFFFF)
		{
			CreateDirectory(strFilePath2.GetBuffer(0),NULL);
		}
		
	}
	

	switch(pModeInfo->nModeType)
	{
	case Mode_Currency:
		{
			strFilePath1.Format(_T("%s\\%s"),strFilePath2,g_ModeType[pModeInfo->nModeType]);
			if(GetFileAttributes(strFilePath1.GetBuffer(0)) == 0xFFFFFFFF)
			{
				CreateDirectory(strFilePath1.GetBuffer(0),NULL);
			}
			strFilePath2.Format(_T("%s\\%s%s"),strFilePath1,pModeInfo->szModeName,Formula_FILE_EX);
			strFilePath = strFilePath2;
		}
		break;
	case Mode_Dedicated:
		{
			strFilePath1.Format(_T("%s\\%s"),strFilePath2,g_ModeType[pModeInfo->nModeType]);
			if(GetFileAttributes(strFilePath1.GetBuffer(0)) == 0xFFFFFFFF)
			{
				CreateDirectory(strFilePath1.GetBuffer(0),NULL);
			}

			strFilePath2.Format(_T("%s\\%s"),strFilePath1,pModeInfo->stProductInfo.szProductNo);
			if(GetFileAttributes(strFilePath2.GetBuffer(0)) == 0xFFFFFFFF)
			{
				CreateDirectory(strFilePath2.GetBuffer(0),NULL);
			}

			strFilePath1.Format(_T("%s\\%s%s"),strFilePath2,pModeInfo->szModeName,Formula_FILE_EX);
			strFilePath = strFilePath1;


		}
		break;
	case Mode_LineDed:
		{
			strFilePath1.Format(_T("%s\\%s"),strFilePath2,g_ModeType[pModeInfo->nModeType]);
			if(GetFileAttributes(strFilePath1.GetBuffer(0)) == 0xFFFFFFFF)
			{
				CreateDirectory(strFilePath1.GetBuffer(0),NULL);
			}
			strFilePath2.Format(_T("%s\\%s%s"),strFilePath1,pModeInfo->szModeName,Formula_FILE_EX);
			strFilePath = strFilePath2;
		}
		break;
	case Mode_NotUse:
		{
			strFilePath1.Format(_T("%s\\%s"),strFilePath2,g_ModeType[pModeInfo->nModeType]);
			if(GetFileAttributes(strFilePath1.GetBuffer(0)) == 0xFFFFFFFF)
			{
				CreateDirectory(strFilePath1.GetBuffer(0),NULL);
			}
			strFilePath2.Format(_T("%s\\%s%s"),strFilePath1,pModeInfo->szModeName,Formula_FILE_EX);
			strFilePath = strFilePath2;
		}
		break;
	default:
		break;
	}

	return strFilePath;
}

CString BuildAttamentFilePath(StTstResultAtta *StTstResultAtta)//�齨�����ļ�·��//
{

	CString strInPath;
	CString strInDepartPath;
	CString strInTaskPath;
	CString strInProdPath;

	strInPath.Format( _T("%s\\%s"), g_WorkPath,ExclosureFile_Path);
	if(GetFileAttributes(strInPath.GetBuffer(0)) == 0xFFFFFFFF)
		CreateDirectory(strInPath.GetBuffer(0), NULL);


	strInDepartPath.Format( _T("%s\\%s"), strInPath,g_CurSelDepart.szGroupName);
	if(GetFileAttributes(strInDepartPath.GetBuffer(0)) == 0xFFFFFFFF)
		CreateDirectory(strInDepartPath.GetBuffer(0), NULL);

	strInTaskPath.Format( _T("%s\\%s"), strInDepartPath,StTstResultAtta->szTaskName);
	if(GetFileAttributes(strInTaskPath.GetBuffer(0)) == 0xFFFFFFFF)
		CreateDirectory(strInTaskPath.GetBuffer(0), NULL);

	strInProdPath.Format( _T("%s\\%s_%s_%s"), strInTaskPath, 
		StTstResultAtta->szProductNo, StTstResultAtta->szProductCode, StTstResultAtta->szModeName);
	if(GetFileAttributes(strInProdPath.GetBuffer(0)) == 0xFFFFFFFF)
		CreateDirectory(strInProdPath.GetBuffer(0), NULL);

	return strInProdPath;
}



void ChangeHexAsc( char *sur, char *des , int number)
{
	int i;
	char itemp1 , itemp2 ;

	for(i=0;i<number;i++)
	{
		if( sur[2*i] <= '9' )
		{
			itemp1 = sur[2*i] - 48;
		}
		else 
		{
			itemp1 = sur[2*i] - 87;
		}

		if( sur[2*i+1] <= '9' )
		{
			itemp2 = sur[2*i+1] - 48;
		}
		else 
		{
			itemp2 = sur[2*i+1] - 87;
		}

		des[i] = itemp1*16 + itemp2;				  				
	}

}

void ChangeAscHex( char *sur, char *des , int number)
{	
	CString			temp,temp1;
	int				i;
	unsigned int	change;

	temp = "";
	for (i=0; i<number; i++)
	{
		change = sur[i];
		temp1 = itoa((unsigned char)(change),des,16);
		if(temp1.GetLength() == 1)
		{
			temp1 = '0' + temp1;
		}

		temp += temp1;
	}

	temp += '\0';		
	memcpy (des, temp, temp.GetLength());		

	//return (temp.GetLength());
}








//��pad ����ֲ����////

int  g_bDebug = 0;

//////


char g_WorkPath[512];
char g_Admin[] = "admin";
char g_ReSetDefPwd[] = "123456";				//ϵͳĬ������//
char g_SearchBeginTime[] = _T("00:00:00");
char g_SearchEndTime[]   = _T("23:59:59");

//���Խ����ҳ��ʾ��������
char g_szSearchPerPageNums[4][20] = {_T("2"), _T("5"),_T("10"),_T("ȫ������")};//��ѯʱÿҳ�Ľ������//
int  g_nSearchPerPageNum[4] = {2, 5, 10, 0};

int  g_IdLen = 10;								//����ÿ�ű� ID�� �ַ����ĳ���//
int  g_GroupSelect = 0;							//�û��ϴ����õĲ���//
int  g_PaperDirection = 1;						//֤����ֽ�ŷ��� 0:���� 1:����//
int  g_PadCount = 0;
int  g_WinWidth    = 1024;
int  g_WinHeight = 600;

char g_TestimonialPage[12][100] = {
_T("����"), _T("��д��ʹ�ù���"), _T("Ŀ¼"), _T("��Ʒ�ϸ����"),
_T("��Ʒ���ױ�"), _T("���Բ�Ʒ������(�豸)�嵥"), _T("������ʱ����������¼"), _T("��Ʒ�������ܲ��Լ�¼"),
_T("ͨ��ʱ���¼"), _T("���Ӽ�¼"), _T("�������"), _T("���")};

char g_ResultType[2][20] = {"�����ѯ","������ݲ�ѯ"};

char g_TaskState[5][20] = {"������","���ɹ�","ִ����","�����","ȫ������"};
char g_TaskShowType[5][20] = {"������","���ɹ�","ִ����","�����","����ֹ"};
char g_TaskType[3][20] = { "����","����","��Э����"};


char g_ProdSeriesType[2][20] = {"��ϵ�к�","��ϵ��"};
char g_ProdPicNumType[2][20] = {"��ͨ��Ʒ","���²�Ʒ"};//1.��ͨ��Ʒ(��ͼ��) 2.���²�Ʒ(��ͼ��)//

char g_ModeRowVal[2][20] = {"���ɱ�","�пɱ�"};
char g_ModeType[4][20] = {"ͨ��ģ��","��Ʒר��","����ר��","δ����"};

char g_UserStatus[2][20] = {_T("����"),_T("����")};
char g_UserType[3][20] = {"����Ա","�����鳤","ϵͳ����Ա"};
//�������ݿ�ı����� �й�ϵ��Ϊһ��//

char g_HrRole[] = "HR_ROLE";						//1.��ɫ��//
char g_HrUser[] = "HR_USER";						//2.�û���//
char g_HrGroup[] = "HR_GROUP";						//3.���ű�//
char g_HrGroupSave[] = "HR_GROUP_SAVE";				//3_1.ÿ�����Ŷ����Լ�������������ͽ��������// ����洢������
char g_HrUpDepart[] = "HR_DEPART";					//4.���첿�ű�  2017-03-01 add

char g_BasProduct[]  = "BAS_PRODUCT";				//5.��Ʒ����
char g_BasProductPicNum[] = "BAS_PRODUCT_PICNUM";	//6.��Ʒ_ͼ����Ϣ 
char g_BasMode[] = "BAS_MODE";						//7.ģ���
char g_BasModeSave[] = "BAS_MODE_SAVE";				//7_1 ģ��ṹ���ݱ� ÿһ��ģ�嶼��һ�����ݱ�
char g_BasModeDesc[] = "BAS_MODE_DESC";				//7_1 ģ��ṹ���ݱ� ÿһ��ģ�嶼��һ�����ݱ�

char g_BasTask[] = "BAS_TASK";						//08.�����
char g_BasTaskCode[] = "BAS_TASK_CODE";				//09.�����ű�
char g_BasTaskMode[] = "BAS_TASK_MODE";				//10.����ģ���
char g_BasTaskPicNum[] = "BAS_TASK_PICNUM";			//11.����ͼ�ű�


char *g_TstData = "TST_DATA_";						//ģ�����ݱ��ǰ׺  һ���������ݱ��� ǰ׺_����ID_ģ��ID����: TST_DATA_0001_0001//
char *g_ResultBase = "TST_RESULT_BASE_";			//��������� ��̬���� ǰ׺_����ID ����001�����µ�  TST_RESULT_BASE_0001//
char *g_ResultAtta = "TST_RESULT_ATTA_";			//���Խ��������Ϣ ��̬���� ǰ׺_����ID ����001�����µ�  TST_RESULT_ATTA_0001//
char *g_Enclosure = "TST_ENCLOSURE_";				//���Ը�����   ��Ƭ  ��Ƶ  �ļ���;
//��ṹ���ֶ��� ����ͳһ����//////

//Ȩ���û��� �ֶ���//
int g_HrRoleLen = 3;

int g_DepartLen = 9;



//2017-03-10 ��ѯ�б���ʾ//
int     g_DebugShow = 1;       //0.��ʾ���Գ���ʱ��ʾ  1.��ʾ���û�ʱ ����ʾ//

CArray<TestDataStr,TestDataStr> *g_pDataArray = NULL;
vector<StBasTaskPicNum *> *g_pArryTaskPicNum = NULL;
StTstResultAtta     *g_pCurAttaInfo = NULL;
int           g_PicNum = 0;
StHrGroup     g_CurSelDepart;
StHrUser      g_LoginUsrInfo;
DbConfig      g_Configs;
CString       g_strSelProdsSQL;


vector<StBasProduct *> g_SelProducts;
vector<StHrGroup *> g_AllGroups;
vector<StHrUpDepart> g_AllUpDeparts;
vector<StHrRole *>  g_AllRoles;
CLogFile	*g_pLogInfo = NULL;
int         g_nPos = 0;			//��־���

int  g_bAddEncOrDec = 1;        //�Ƿ�Ϊ����ģʽ



CDataMng      m_DMng;
CSysSetConfig g_UserConfig;
#define GLOB_QUEUE_DEFINE
#endif