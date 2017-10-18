// ModeXmlAnalysis.cpp: implementation of the CModeXmlAnalysis class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ModeXmlAnalysis.h"
#include "ModeXmlStruct.h"
#include "TinyXML\tinyxml.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

void GetSysDate(char *cDate)
{
	CTime	t = CTime::GetCurrentTime();
	int		year	= t.GetYear();
	int		month	= t.GetMonth();
	int		day		= t.GetDay();
	CString strTime;
	
	strTime.Format("%04d-%02d-%02d",year,month,day);
	strcpy(cDate, strTime.GetBuffer(0));
	return;
}

void GetSysTime(char *cTime)
{
	CTime	t = CTime::GetCurrentTime();
	int		hour	= t.GetHour();
	int		minute	= t.GetMinute();
	int		second	= t.GetSecond();
	CString strTime;
	
	strTime.Format("%02d:%02d:%02d",hour,minute,second);
	strcpy(cTime, strTime.GetBuffer(0));
	return;
}

void SetXmlRootInfo(TiXmlElement *pRootInfo)
{	
	char Date[24] = {0,}; 
	char Time[24] = {0,};
	GetSysDate(Date);
	GetSysTime(Time);
	pRootInfo->SetAttribute("Version", DECL_VERSION);
	pRootInfo->SetAttribute("Date", Date);
	pRootInfo->SetAttribute("Time", Time);
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CModeXmlAnalysis::CModeXmlAnalysis()
{

}

CModeXmlAnalysis::~CModeXmlAnalysis()
{

}


//---------------------------------------------------------------------


int CModeXmlAnalysis::GetCurModeXmlFileName(char *pFileName, char *pPathName)
{
	CModeParMng *pParMng = m_pParMng;
	CString		str, strPath;
	
	strPath = PATH_XML_MODE_PAR_CFG;

	//strPath.Format( _T("%s%d"),PATH_XML_MODE_PAR_CFG, g_pDlg->m_nCurTaskPos+1);
	strPath.Format( _T("%s"),PATH_XML_MODE_PAR_CFG);
	
	//	
	str.Format("%s\\%s\\%s", 
		g_WorkPath, 
		strPath,
		pFileName);
	
	strcpy(pPathName, str.GetBuffer(0));

	return 1;
}

//1.模板表_结构信息
int CModeXmlAnalysis::SetXmlMdTabSrtInfo( )		//设置模板表_结构信息
{
	CModeParMng *pParMng = m_pParMng;
	char      szFileName[MAX_PATH] = {0,};
	
	GetCurModeXmlFileName(MD_XML_FILE_TAB_SRT_INFO, szFileName);
	
	//建立XML文件头----------------------------------------------------------------------------
	TiXmlDocument	doc;
	TiXmlDeclaration* pDec = new TiXmlDeclaration(DECL_VERSION, DECL_ENCODING, DECL_STANDALONE);
	doc.LinkEndChild(pDec);
	TiXmlElement* pRootInfo = new TiXmlElement(MD_XML_ROOT_INFO);
	doc.LinkEndChild(pRootInfo);	
	SetXmlRootInfo(pRootInfo);
	//-----------------------------------------------------------------------------------------
	TiXmlElement	*pTabSrtRoot, *pTempRoot; 
	TiXmlElement	*pTempElem1, *pTempElem2;
	int				i,j;
	int             nRowCnt, nColCnt, nTabCellCnt;
	
	StTabCell       *pStTabCell = NULL;
	StTabRow        *pStTabRow  = NULL;
	StTabCol        *pStTabCol  = NULL;
	StTabData		*pStTabData = NULL; 
	StTabAlarm		*pStTabAlarm= NULL; 
	//

	nRowCnt = pParMng->m_row;
	nColCnt = pParMng->m_col;

	//测试模板结构信息 Set
	pTabSrtRoot = new TiXmlElement(MD_XML_CFG_TAB_SRT_INFO);
	pRootInfo->LinkEndChild(pTabSrtRoot);

	//1.1_TabItemData
	pTempRoot = new TiXmlElement(MD_XML_ROOT_TAB_ITEM_DATA);
	pTempRoot->SetAttribute(MD_XML_ST_TAB_ROW_CNT, nRowCnt);
	pTempRoot->SetAttribute(MD_XML_ST_TAB_COL_CNT, nColCnt);
	pTabSrtRoot->LinkEndChild(pTempRoot);

	for (i=0; i<nRowCnt; i++)
	{	
		pTempElem1 = new TiXmlElement(MD_XML_ATTR_ROOT_1);
		pTempElem1->SetAttribute(MD_XML_ATTR_INDEX_1, i+1);
		pTempRoot->LinkEndChild(pTempElem1);
		
		for (j=0; j<nColCnt; j++)
		{
			pTempElem2 = new TiXmlElement(MD_XML_ATTR_ROOT_2);
			pTempElem2->SetAttribute(MD_XML_ATTR_INDEX_2, j+1);
			pTempElem2->SetAttribute(MD_XML_ATTR_VALUE_2, pParMng->m_ItemInfo[i][j]);
			pTempElem1->LinkEndChild(pTempElem2);
		}
	}

	//1.2_表格结构_表头列宽度<TabHeadLen>
	pTempRoot = new TiXmlElement(MD_XML_ROOT_TAB_HEAD_LEN);
	pTempRoot->SetAttribute(MD_XML_ATTR_COUNT_ROOT, pParMng->m_col);
	pTabSrtRoot->LinkEndChild(pTempRoot);
	for (i=0; i<nColCnt; i++)
	{	
		pTempElem1 = new TiXmlElement(MD_XML_ATTR_ROOT_1);
		pTempElem1->SetAttribute(MD_XML_ATTR_INDEX_1, i+1);
		pTempElem1->SetAttribute(MD_XML_ATTR_VALUE_1, pParMng->m_ColLen[i]);
		pTempRoot->LinkEndChild(pTempElem1);
	}
		
	//5.表格模板_合并单元格结构		<TabCellSrt>
	nTabCellCnt = pParMng->m_nTabCellCnt;
	pTempRoot = new TiXmlElement(MD_XML_ROOT_TAB_CELL_SRT);
	pTempRoot->SetAttribute(MD_XML_ATTR_COUNT_ROOT, nTabCellCnt);
	pTabSrtRoot->LinkEndChild(pTempRoot);
	for (i=0; i<nTabCellCnt; i++)
	{		
		pTempElem1 = new TiXmlElement(MD_XML_ATTR_ROOT_1);
		pTempElem1->SetAttribute(MD_XML_ATTR_INDEX_1, i+1);

		pStTabCell = &pParMng->m_stTabCell[i];
		pTempElem1->SetAttribute(MD_XML_ST_CELL_BEG_ROW, pStTabCell->iBegRow);
		pTempElem1->SetAttribute(MD_XML_ST_CELL_BEG_COL, pStTabCell->iBegCol);
		pTempElem1->SetAttribute(MD_XML_ST_CELL_END_ROW, pStTabCell->iEndRow);
		pTempElem1->SetAttribute(MD_XML_ST_CELL_END_COL, pStTabCell->iEndCol);
		pTempRoot->LinkEndChild(pTempElem1);
	}


	//6.表格模板_列简称结构		"TabRowSrt"	
	pTempRoot = new TiXmlElement(MD_XML_ROOT_TAB_ROW_SRT);
	pTempRoot->SetAttribute(MD_XML_ATTR_COUNT_ROOT, pParMng->m_nTabRowSrtCnt);
	pTabSrtRoot->LinkEndChild(pTempRoot);
	for (i=0; i<nRowCnt; i++)
	{	
		
		pTempElem1 = new TiXmlElement(MD_XML_ATTR_ROOT_1);
		pTempElem1->SetAttribute(MD_XML_ATTR_INDEX_1, i+1);

		pStTabRow = &pParMng->m_stTabRow[i];
		pTempElem1->SetAttribute(MD_XML_ST_ROWCOL_POS,  pStTabRow->iRowPos);
		pTempElem1->SetAttribute(MD_XML_ST_ROWCOL_FLAG, pStTabRow->bDataFlag);
		pTempElem1->SetAttribute(MD_XML_ST_ROWCOL_NAME, pStTabRow->szRowName);
		pTempRoot->LinkEndChild(pTempElem1);
	}
		
	
	//7.表格模板_行简称结构		"TabColSrt"	
	pTempRoot = new TiXmlElement(MD_XML_ROOT_TAB_COL_SRT);
	pTempRoot->SetAttribute(MD_XML_ATTR_COUNT_ROOT, pParMng->m_nTabColSrtCnt);
	pTabSrtRoot->LinkEndChild(pTempRoot);
	for (i=0; i<nColCnt; i++)
	{		
		pTempElem1 = new TiXmlElement(MD_XML_ATTR_ROOT_1);
		pTempElem1->SetAttribute(MD_XML_ATTR_INDEX_1, i+1);
		
		pStTabCol = &pParMng->m_stTabCol[i];
		pTempElem1->SetAttribute(MD_XML_ST_ROWCOL_POS,  pStTabCol->iColPos);
		pTempElem1->SetAttribute(MD_XML_ST_ROWCOL_FLAG, pStTabCol->bDataFlag);
		pTempElem1->SetAttribute(MD_XML_ST_ROWCOL_NAME, pStTabCol->szColName);
		pTempRoot->LinkEndChild(pTempElem1);
	}

	//8.表格模板_输出数据结构	"TabDataSrt"
	pTempRoot = new TiXmlElement(MD_XML_ROOT_TAB_DATA_SRT);
	pTempRoot->SetAttribute(MD_XML_ATTR_COUNT_ROOT, pParMng->m_nDataCnt);
	pTabSrtRoot->LinkEndChild(pTempRoot);
	for (i=0; i<pParMng->m_nDataCnt; i++)
	{		
		pTempElem1 = new TiXmlElement(MD_XML_ATTR_ROOT_1);
		pTempElem1->SetAttribute(MD_XML_ATTR_INDEX_1, i+1);

		pStTabData = &pParMng->m_stTabData[i];
		pTempElem1->SetAttribute(MD_XML_ST_DATA_NAME,	pStTabData->szDbColName);
		pTempElem1->SetAttribute(MD_XML_ST_DATA_DESC,	pStTabData->szOutDataName);
		pTempElem1->SetAttribute(MD_XML_ST_DATA_BEG_ROW,pStTabData->iBegRow);		
		pTempElem1->SetAttribute(MD_XML_ST_DATA_BEG_COL,pStTabData->iBegCol);
		pTempElem1->SetAttribute(MD_XML_ST_DATA_TYPE,	pStTabData->iDataType);
		pTempRoot->LinkEndChild(pTempElem1);
	}

	//9.表格模板_数据报警结构	"TabAlarmSrt"			
	pTempRoot = new TiXmlElement(MD_XML_ROOT_TAB_ALARM_SRT);
	pTempRoot->SetAttribute(MD_XML_ATTR_COUNT_ROOT, pParMng->m_nDataCnt);
	pTabSrtRoot->LinkEndChild(pTempRoot);
	for (i=0; i<pParMng->m_nDataCnt; i++)
	{		
		pTempElem1 = new TiXmlElement(MD_XML_ATTR_ROOT_1);
		pTempElem1->SetAttribute(MD_XML_ATTR_INDEX_1, i+1);
		
		pStTabAlarm = &pParMng->m_stTabAlarm[i];
		pTempElem1->SetAttribute(MD_XML_ST_ALA_CHECK_FLAG,	pStTabAlarm->bCheckFlag);
		pTempElem1->SetAttribute(MD_XML_ST_ALA_JUDGE_TYPE,	pStTabAlarm->nJudgeType);
		//pTempElem1->SetAttribute(MD_XML_ST_ALA_JUDGE_DESC,	pStTabAlarm->szJudgeDesc);		
		pTempElem1->SetAttribute(MD_XML_ST_ALA_TARGET_1,	pStTabAlarm->szTarget1);	
		pTempElem1->SetAttribute(MD_XML_ST_ALA_TARGET_2,	pStTabAlarm->szTarget2);
		pTempRoot->LinkEndChild(pTempElem1);
	}

	doc.SaveFile(szFileName);
	
	return 1;
}

//2.模板表_数据输出
int CModeXmlAnalysis::SetXmlMdTabOutData( )		//设置模板表_数据输出
{
	CModeParMng *pParMng = m_pParMng;
	char      szFileName[MAX_PATH] = {0,};
	
	GetCurModeXmlFileName(MD_XML_FILE_TAB_OUT_INFO, szFileName);
	
	//建立XML文件头----------------------------------------------------------------------------
	TiXmlDocument	doc;
	TiXmlDeclaration* pDec = new TiXmlDeclaration(DECL_VERSION, DECL_ENCODING, DECL_STANDALONE);
	doc.LinkEndChild(pDec);
	TiXmlElement* pRootInfo = new TiXmlElement(MD_XML_ROOT_INFO);
	doc.LinkEndChild(pRootInfo);	
	SetXmlRootInfo(pRootInfo);
	//-----------------------------------------------------------------------------------------
	TiXmlElement	*pTabOutRoot, *pTempRoot; 
	TiXmlElement	*pTempElem1;
	int				i, pos;
	int             nDataCnt = 0;
	
	StTabData		*pStTabData = NULL; 
	StTabAlarm		*pStTabAlarm= NULL; 
	StOutTestData   *pStOutTestData = NULL;
	StOutAppData    *pStOutAppData = NULL;
	//
	char szDateTime[30] = {0,}; 
	GetSysDateTime(szDateTime);


	if (pParMng->m_nModeType == mode_normal)
	{
		nDataCnt = pParMng->m_nDataCnt;
	}
	else if (pParMng->m_nModeType == mode_rowvar)
	{
		nDataCnt = pParMng->m_nDataCnt * pParMng->m_nMulRowCnt;
	}
	

	//测试模板结构信息 Set
	pTabOutRoot = new TiXmlElement(MD_XML_CFG_TAB_OUT_INFO);
	pRootInfo->LinkEndChild(pTabOutRoot);

	//2.1 结果数据
	pTempRoot = new TiXmlElement(MD_XML_ROOT_OUT_TEST_DATA);
	pTempRoot->SetAttribute(MD_XML_ATTR_COUNT_ROOT, nDataCnt);
	pTempRoot->SetAttribute(MD_XML_ATTR_SAVE_USR,   pParMng->m_szUsrName);
	pTempRoot->SetAttribute(MD_XML_ATTR_SAVE_TIME,  szDateTime);
	pTabOutRoot->LinkEndChild(pTempRoot);


	for (i=0; i<nDataCnt; i++)
	{		
		pTempElem1 = new TiXmlElement(MD_XML_ATTR_ROOT_1);
		pTempElem1->SetAttribute(MD_XML_ATTR_INDEX_1, i+1);

		pStTabData = &pParMng->m_stTabData[i];
		pStOutTestData = &pParMng->m_stOutTestData[i];

		//结果数据_名称&描述
		pTempElem1->SetAttribute(MD_XML_ST_DATA_NAME,	pStTabData->szDbColName);
		pTempElem1->SetAttribute(MD_XML_ST_DATA_DESC,	pStTabData->szOutDataName);

		//ztadd 2017-03-15
		pTempElem1->SetAttribute(MD_XML_ST_DATA_TYPE, pStTabData->iDataType);

		//结果数据
		pTempElem1->SetAttribute(MD_XML_ST_OUT_DATA,		pStOutTestData->szOutData);		//测试结果数据
		
		//ztadd 2016-12-29
		pTempElem1->SetAttribute(MD_XML_ST_OUT_DESC,		pStOutTestData->szOutDesc);		//测试结果描述
		
		pTempElem1->SetAttribute(MD_XML_ST_OUT_ALARM_FLAG,	pStOutTestData->bAlarmFlag);	//报警状态
		pTempElem1->SetAttribute(MD_XML_ST_OUT_HIS_FLAG,	pStOutTestData->bHisFlag);		//历史极值检测状态
		pTempElem1->SetAttribute(MD_XML_ST_OUT_TEST_USR,    pStOutTestData->szTestUsr);		//测试人员
		pTempElem1->SetAttribute(MD_XML_ST_OUT_TEST_TIME,   pStOutTestData->szTestTime);	//测试时间

		pTempRoot->LinkEndChild(pTempElem1);
	}

	//2.2 附件信息
	pTempRoot = new TiXmlElement(MD_XML_ROOT_OUT_APP_DATA);
	pTempRoot->SetAttribute(MD_XML_ATTR_COUNT_ROOT, pParMng->m_nOutAppDataCnt);
	pTabOutRoot->LinkEndChild(pTempRoot);

	for (i=0; i<pParMng->m_nOutAppDataCnt; i++)
	{		
		pTempElem1 = new TiXmlElement(MD_XML_ATTR_ROOT_1);
		pTempElem1->SetAttribute(MD_XML_ATTR_INDEX_1, i+1);

		pStOutAppData = &pParMng->m_stOutAppData[i];
		pos = pStOutAppData->nTabDataPos;
		pStTabData = &pParMng->m_stTabData[pos];

		//结果数据_名称&描述
		pTempElem1->SetAttribute(MD_XML_ST_DATA_NAME,	pStTabData->szDbColName);
		pTempElem1->SetAttribute(MD_XML_ST_DATA_DESC,	pStTabData->szOutDataName);

		//结果数据
		pTempElem1->SetAttribute(MD_XML_ST_APP_TAB_DATA_POS ,	pStOutAppData->nTabDataPos);	//结果数据_序号(从1开始) 
		pTempElem1->SetAttribute(MD_XML_ST_APP_APPENDIX_TYPE ,	pStOutAppData->nAppendixType);	//附件类型
		pTempElem1->SetAttribute(MD_XML_ST_APP_SRC_FILE_NAME ,	pStOutAppData->szSrcFileName);	//原始名称
		pTempElem1->SetAttribute(MD_XML_ST_APP_DES_FILE_NAME ,	pStOutAppData->szDesFileName);	//附件名称=产品代号_产品编号_模板名称_数据项名称(原始名称)
		pTempElem1->SetAttribute(MD_XML_ST_APP_UP_USR ,			pStOutAppData->szUpUsr);		//上传人员
		pTempElem1->SetAttribute(MD_XML_ST_APP_UP_TIME ,		pStOutAppData->szUpTime);		//上传时间

		pTempRoot->LinkEndChild(pTempElem1);
	}

	doc.SaveFile(szFileName);
	
	return 1;	
}

//3.模板表_历史极值检测	
int CModeXmlAnalysis::SetXmlMdTabHisInfo( )		//设置模板表_历史极值检测
{
	CModeParMng *pParMng = m_pParMng;
	char      szFileName[MAX_PATH] = {0,};
	
	GetCurModeXmlFileName(MD_XML_FILE_TAB_HIS_INFO, szFileName);
	
	//建立XML文件头----------------------------------------------------------------------------
	TiXmlDocument	doc;
	TiXmlDeclaration* pDec = new TiXmlDeclaration(DECL_VERSION, DECL_ENCODING, DECL_STANDALONE);
	doc.LinkEndChild(pDec);
	TiXmlElement* pRootInfo = new TiXmlElement(MD_XML_ROOT_INFO);
	doc.LinkEndChild(pRootInfo);	
	SetXmlRootInfo(pRootInfo);
	//-----------------------------------------------------------------------------------------
	TiXmlElement	*pTabRoot; 
	TiXmlElement	*pTempElem1;
	int				i;
	int             nDataCnt = 0;
	
	StTabData		*pStTabData = NULL; 
	StTabHisChk		*pStTabHisChk = NULL;
	//	
	nDataCnt = pParMng->m_nDataCnt;
	
	//测试结果
	pTabRoot = new TiXmlElement(MD_XML_CFG_TAB_HIS_INFO);
	pTabRoot->SetAttribute(MD_XML_ATTR_COUNT_ROOT, pParMng->m_nDataCnt);
	pRootInfo->LinkEndChild(pTabRoot);
	
	for (i=0; i<pParMng->m_nDataCnt; i++)
	{		
		pTempElem1 = new TiXmlElement(MD_XML_ATTR_ROOT_1);
		pTempElem1->SetAttribute(MD_XML_ATTR_INDEX_1, i+1);
		
		pStTabData = &pParMng->m_stTabData[i];
		pStTabHisChk = &pParMng->m_stTabHisChk[i];
		
		//结果数据_名称&描述
		pTempElem1->SetAttribute(MD_XML_ST_DATA_NAME,	pStTabData->szDbColName);
		pTempElem1->SetAttribute(MD_XML_ST_DATA_DESC,	pStTabData->szOutDataName);
		
		//历史极值
		pTempElem1->SetAttribute(MD_XML_ST_HIS_FLAG,	pStTabHisChk->bHisChkFlag);		//检测标志				
		pTempElem1->SetAttribute(MD_XML_ST_HIS_MIN,		pStTabHisChk->szHisValMin);		//最小值
		pTempElem1->SetAttribute(MD_XML_ST_HIS_MAX,		pStTabHisChk->szHisValMax);		//最大值
		
		pTabRoot->LinkEndChild(pTempElem1);
	}
	
	doc.SaveFile(szFileName);
	
	return 1;		
}



//============================================================================
//1.模板表_结构信息
int CModeXmlAnalysis::GetXmlMdTabSrtInfo( )		//获取模板表_结构信息
{
	CModeParMng *pParMng = m_pParMng;
	char      szFileName[MAX_PATH] = {0,};
	
	GetCurModeXmlFileName(MD_XML_FILE_TAB_SRT_INFO, szFileName);
	
	//------------------------------------------------------------------------------
	TiXmlDocument   doc( szFileName );
	TiXmlElement	* pRootInfo;
	if (!doc.LoadFile())
	{
		return 0;
	}
	pRootInfo = doc.RootElement();
	//-------------------------------------------------------------------------------
	StTabCell       *pStTabCell = NULL;
	StTabRow        *pStTabRow  = NULL;
	StTabCol        *pStTabCol  = NULL;
	StTabData		*pStTabData = NULL; 
	StTabAlarm		*pStTabAlarm= NULL; 

	TiXmlElement	*pRoot, *pRootType, *pRoot1, *pRoot2;
	int				Layer1, Layer2, Layer3;
	CString			strTemp, str;
	int             nRowNum = 0;
	int             nColNum = 0;
	int             nRowPos=0, nColPos=0;
	int             nCount=0;
	
	
	
	Layer1 = 0;
	Layer2 = 0;
	Layer3 = 0;
	
	if (pRootInfo)
	{
		//1.1_TabItemData  ----------------------------------------------------------
		pRoot= pRootInfo->FirstChildElement(MD_XML_CFG_TAB_SRT_INFO);
		if (pRoot)
		{
			//1.1_TabItemData
			pRootType = pRoot->FirstChildElement(MD_XML_ROOT_TAB_ITEM_DATA);
	
			if (pRootType)
			{
				//1.
				strTemp = pRootType->Attribute(MD_XML_ST_TAB_ROW_CNT);
				nRowNum = atoi(strTemp.GetBuffer(0));
				if ( (nRowNum < 0) || (nRowNum > XLS_MAX_ROW) )
				{
					nRowNum = 0;
				}
				pParMng->m_row = nRowNum;	
				//2.
				strTemp = pRootType->Attribute(MD_XML_ST_TAB_COL_CNT);
				nColNum = atoi(strTemp.GetBuffer(0));
				if ( (nColNum < 0) || (nColNum > XLS_MAX_COL) )
				{
					nRowNum = 0;
				}
				pParMng->m_col = nColNum;
		
				//第一层
				pRoot1 = pRootType->FirstChildElement(MD_XML_ATTR_ROOT_1);		
				Layer1 = 0;
				if (pRoot1)
				{
					for (pRoot1; pRoot1; pRoot1=pRoot1->NextSiblingElement(MD_XML_ATTR_ROOT_1))
					{
						//第二层
						pRoot2 = pRoot1->FirstChildElement(MD_XML_ATTR_ROOT_2);	
						Layer2 = 0;
						for (pRoot2; pRoot2; pRoot2=pRoot2->NextSiblingElement(MD_XML_ATTR_ROOT_2))
						{
							//1.
							strTemp = pRoot2->Attribute(MD_XML_ATTR_VALUE_2);
							if ( (Layer1 < pParMng->m_row) || (Layer2 < pParMng->m_col) )
							{
								strcpy(pParMng->m_ItemInfo[Layer1][Layer2], strTemp.GetBuffer(0));
							}			
							Layer2++;
						}
						Layer1++;
					}		
				}
			}
			

			//1.2_表格结构_表头列宽度<TabHeadLen>
			//---------------------------------------------------------------------------
			pRootType = pRoot->FirstChildElement(MD_XML_ROOT_TAB_HEAD_LEN);
			if (pRootType)
			{
				//第一层
				pRoot1 = pRootType->FirstChildElement(MD_XML_ATTR_ROOT_1);		
				Layer1 = 0;
				if (pRoot1)
				{
					for (pRoot1; pRoot1; pRoot1=pRoot1->NextSiblingElement(MD_XML_ATTR_ROOT_1))
					{
						//1.
						strTemp = pRoot1->Attribute(MD_XML_ATTR_VALUE_1);

						if (Layer1 < pParMng->m_col)
						{
							pParMng->m_ColLen[Layer1] = atoi(strTemp.GetBuffer(0));
						}
						Layer1++;
					}
				}
			}

			//5.表格模板_合并单元格结构		<TabCellSrt>
			//---------------------------------------------------------------------------
			pRootType = pRoot->FirstChildElement(MD_XML_ROOT_TAB_CELL_SRT);
			if (pRootType)
			{
				strTemp = pRootType->Attribute(MD_XML_ATTR_COUNT_ROOT);
				nCount = atoi(strTemp.GetBuffer(0));	

				//第一层
				pRoot1 = pRootType->FirstChildElement(MD_XML_ATTR_ROOT_1);		
				Layer1 = 0;
				if (pRoot1)
				{
					for (pRoot1; pRoot1; pRoot1=pRoot1->NextSiblingElement(MD_XML_ATTR_ROOT_1))
					{
						pStTabCell = &pParMng->m_stTabCell[Layer1];
						//1.
						strTemp = pRoot1->Attribute(MD_XML_ST_CELL_BEG_ROW);
						pStTabCell->iBegRow = atoi(strTemp.GetBuffer(0));
						//2.
						strTemp = pRoot1->Attribute(MD_XML_ST_CELL_BEG_COL);
						pStTabCell->iBegCol = atoi(strTemp.GetBuffer(0));
						//3.
						strTemp = pRoot1->Attribute(MD_XML_ST_CELL_END_ROW);
						pStTabCell->iEndRow = atoi(strTemp.GetBuffer(0));
						//4.
						strTemp = pRoot1->Attribute(MD_XML_ST_CELL_END_COL);
						pStTabCell->iEndCol = atoi(strTemp.GetBuffer(0));

						pStTabCell->iRowNum = pStTabCell->iEndRow - pStTabCell->iBegRow + 1;
						pStTabCell->iColNum = pStTabCell->iEndCol - pStTabCell->iBegCol + 1;
					
						Layer1++;
					}
				}

				if (nCount != Layer1)
				{
					str.Format(_T("RootType=%s, nCount Error!  Count=%d, TotalCnt=%d!"), 
								MD_XML_ROOT_TAB_CELL_SRT, nCount, Layer1);
					AfxMessageBox(str);
					return 0;
				}
				else
				{
					pParMng->m_nTabCellCnt = Layer1;
				}
			}


			//6.表格模板_列简称结构		"TabRowSrt"	
			//---------------------------------------------------------------------------
			pRootType = pRoot->FirstChildElement(MD_XML_ROOT_TAB_ROW_SRT);
			if (pRootType)
			{
				strTemp = pRootType->Attribute(MD_XML_ATTR_COUNT_ROOT);
				nCount = atoi(strTemp.GetBuffer(0));	
				
				//第一层
				pRoot1 = pRootType->FirstChildElement(MD_XML_ATTR_ROOT_1);		
				Layer1 = 0;
				if (pRoot1)
				{
					for (pRoot1; pRoot1; pRoot1=pRoot1->NextSiblingElement(MD_XML_ATTR_ROOT_1))
					{
						pStTabRow = &pParMng->m_stTabRow[Layer1];
			
						//1.
						strTemp = pRoot1->Attribute(MD_XML_ST_ROWCOL_POS);  
						pStTabRow->iRowPos = atoi(strTemp.GetBuffer(0));
						//2.
						strTemp = pRoot1->Attribute(MD_XML_ST_ROWCOL_FLAG); 
						pStTabRow->bDataFlag = atoi(strTemp.GetBuffer(0));
						//3.
						strTemp = pRoot1->Attribute(MD_XML_ST_ROWCOL_NAME);
						strcpy(pStTabRow->szRowName, strTemp.GetBuffer(0));
						
						Layer1++;
					}
					pParMng->m_nTabRowSrtCnt = nCount;
				}	
			}

			//7.表格模板_行简称结构		"TabColSrt"	
			//---------------------------------------------------------------------------
			pRootType = pRoot->FirstChildElement(MD_XML_ROOT_TAB_COL_SRT);
			if (pRootType)
			{
				strTemp = pRootType->Attribute(MD_XML_ATTR_COUNT_ROOT);
				nCount = atoi(strTemp.GetBuffer(0));	
				
				//第一层
				pRoot1 = pRootType->FirstChildElement(MD_XML_ATTR_ROOT_1);		
				Layer1 = 0;
				if (pRoot1)
				{
					for (pRoot1; pRoot1; pRoot1=pRoot1->NextSiblingElement(MD_XML_ATTR_ROOT_1))
					{
						pStTabCol = &pParMng->m_stTabCol[Layer1];
						
						//1.
						strTemp = pRoot1->Attribute(MD_XML_ST_ROWCOL_POS);  
						pStTabCol->iColPos = atoi(strTemp.GetBuffer(0));
						//2.
						strTemp = pRoot1->Attribute(MD_XML_ST_ROWCOL_FLAG); 
						pStTabCol->bDataFlag = atoi(strTemp.GetBuffer(0));
						//3.
						strTemp = pRoot1->Attribute(MD_XML_ST_ROWCOL_NAME);
						strcpy(pStTabCol->szColName, strTemp.GetBuffer(0));
						
						Layer1++;
					}
					pParMng->m_nTabColSrtCnt = nCount;
				}	
			}

			//8.表格模板_输出数据结构	"TabDataSrt"
			//---------------------------------------------------------------------------
			pRootType = pRoot->FirstChildElement(MD_XML_ROOT_TAB_DATA_SRT);
			if (pRootType)
			{
				strTemp = pRootType->Attribute(MD_XML_ATTR_COUNT_ROOT);
				nCount = atoi(strTemp.GetBuffer(0));	
				
				//第一层
				pRoot1 = pRootType->FirstChildElement(MD_XML_ATTR_ROOT_1);		
				Layer1 = 0;
				if (pRoot1)
				{
					for (pRoot1; pRoot1; pRoot1=pRoot1->NextSiblingElement(MD_XML_ATTR_ROOT_1))
					{
						pStTabData = &pParMng->m_stTabData[Layer1];
						
						//1.
						strTemp = pRoot1->Attribute(MD_XML_ST_DATA_NAME);  
						strcpy(pStTabData->szDbColName, strTemp.GetBuffer(0));
						//2.
						strTemp = pRoot1->Attribute(MD_XML_ST_DATA_DESC);
						strcpy(pStTabData->szOutDataName, strTemp.GetBuffer(0)); 
						//3.
						strTemp = pRoot1->Attribute(MD_XML_ST_DATA_BEG_ROW);
						pStTabData->iBegRow = atoi(strTemp.GetBuffer(0));
						//4.
						strTemp = pRoot1->Attribute(MD_XML_ST_DATA_BEG_COL);
						pStTabData->iBegCol = atoi(strTemp.GetBuffer(0)); 

						//5.
						strTemp = pRoot1->Attribute(MD_XML_ST_DATA_TYPE);
						pStTabData->iDataType = atoi(strTemp.GetBuffer(0)); 
					
						Layer1++;
					}
					pParMng->m_nDataCnt = nCount;
				}	
			}

		
			//9.表格模板_数据报警结构	"TabAlarmSrt"
			//---------------------------------------------------------------------------
			pRootType = pRoot->FirstChildElement(MD_XML_ROOT_TAB_ALARM_SRT);
			if (pRootType)
			{
				strTemp = pRootType->Attribute(MD_XML_ATTR_COUNT_ROOT);
				nCount = atoi(strTemp.GetBuffer(0));	
				
				//第一层
				pRoot1 = pRootType->FirstChildElement(MD_XML_ATTR_ROOT_1);		
				Layer1 = 0;
				if (pRoot1)
				{
					for (pRoot1; pRoot1; pRoot1=pRoot1->NextSiblingElement(MD_XML_ATTR_ROOT_1))
					{
						pStTabAlarm = &pParMng->m_stTabAlarm[Layer1];
						
						//1.
						strTemp = pRoot1->Attribute(MD_XML_ST_ALA_CHECK_FLAG);  
						pStTabAlarm->bCheckFlag = atoi(strTemp.GetBuffer(0));
						//2.
						strTemp = pRoot1->Attribute(MD_XML_ST_ALA_JUDGE_TYPE);
						pStTabAlarm->nJudgeType = atoi(strTemp.GetBuffer(0));
						 
						//3.
						strTemp = pRoot1->Attribute(MD_XML_ST_ALA_TARGET_1);
						strcpy(pStTabAlarm->szTarget1, strTemp.GetBuffer(0));
						//4.
						strTemp = pRoot1->Attribute(MD_XML_ST_ALA_TARGET_2);
						strcpy(pStTabAlarm->szTarget2, strTemp.GetBuffer(0));
						
						Layer1++;
					}
					pParMng->m_nDataCnt = nCount;
				}	
			}


		}//if pRoot
		
	}//if pRootInfo
	
	return 1;	
}

//2.模板表_数据输出
int CModeXmlAnalysis::GetXmlMdTabOutData( )		//获取模板表_输出数据内容
{
	CModeParMng *pParMng = m_pParMng;
	char      szFileName[MAX_PATH] = {0,};
	
	GetCurModeXmlFileName(MD_XML_FILE_TAB_OUT_INFO, szFileName);
	
	//------------------------------------------------------------------------------
	TiXmlDocument   doc( szFileName );
	TiXmlElement	* pRootInfo;
	if (!doc.LoadFile())
	{
		return 0;
	}
	pRootInfo = doc.RootElement();
	//-------------------------------------------------------------------------------
	StOutTestData   *pStOutTestData = NULL;
	StOutAppData    *pStOutAppData = NULL;

	TiXmlElement	*pRoot, *pRootType, *pRoot1, *pRoot2;
	int				Layer1, Layer2, Layer3;
	CString			strTemp, str;
	int             nRowNum = 0;
	int             nColNum = 0;
	int             nRowPos=0, nColPos=0;
	int             nCount=0;
	int             nDataCnt = 0;
	
	
	
	Layer1 = 0;
	Layer2 = 0;
	Layer3 = 0;
	
	if (pRootInfo)
	{
		//  ----------------------------------------------------------------------
		pRoot= pRootInfo->FirstChildElement(MD_XML_CFG_TAB_OUT_INFO);
		if (pRoot)
		{
			//2.1 结果数据
			pRootType = pRoot->FirstChildElement(MD_XML_ROOT_OUT_TEST_DATA);
			
			if (pRootType)
			{
				//1.
				strTemp = pRootType->Attribute(MD_XML_ATTR_COUNT_ROOT);
				nCount = atoi(strTemp.GetBuffer(0));

				strTemp = pRootType->Attribute(MD_XML_ATTR_SAVE_USR);
				memset(pParMng->m_szOutAppDataUsrName, 0, MAX_USR_NAME_LEN);
				strcpy(pParMng->m_szOutAppDataUsrName, strTemp.GetBuffer(0));
				

				strTemp = pRootType->Attribute(MD_XML_ATTR_SAVE_TIME);
				memset(pParMng->m_szOutAppDataUsrTime, 0, 30);
				strcpy(pParMng->m_szOutAppDataUsrTime, strTemp.GetBuffer(0));
						
				//第一层
				pRoot1 = pRootType->FirstChildElement(MD_XML_ATTR_ROOT_1);		
				Layer1 = 0;
				if (pRoot1)
				{
					for (pRoot1; pRoot1; pRoot1=pRoot1->NextSiblingElement(MD_XML_ATTR_ROOT_1))
					{
						//第二层
						pRoot2 = pRoot1->FirstChildElement(MD_XML_ATTR_ROOT_2);	
					
						pStOutTestData = &pParMng->m_stOutTestData[Layer1];
							
						//结果数据
						//1.
						strTemp = pRoot1->Attribute(MD_XML_ST_OUT_DATA);		//测试结果数据	
						strcpy(pStOutTestData->szOutData, strTemp.GetBuffer(0));

						//ztadd 2016-12-29
						strTemp = pRoot1->Attribute(MD_XML_ST_OUT_DESC);		//测试结果描述	
						strcpy(pStOutTestData->szOutDesc, strTemp.GetBuffer(0));

						//2.
						strTemp = pRoot1->Attribute(MD_XML_ST_OUT_ALARM_FLAG);	//报警状态
						pStOutTestData->bAlarmFlag  = atoi(strTemp.GetBuffer(0));
						//3.
						strTemp = pRoot1->Attribute(MD_XML_ST_OUT_HIS_FLAG);	//历史极值检测状态
						pStOutTestData->bHisFlag	= atoi(strTemp.GetBuffer(0));
						//4.
						strTemp = pRoot1->Attribute(MD_XML_ST_OUT_TEST_USR);	//测试人员
						strcpy(pStOutTestData->szTestUsr, strTemp.GetBuffer(0));
						//5.
						strTemp = pRoot1->Attribute(MD_XML_ST_OUT_TEST_TIME);	//测试时间
						strcpy(pStOutTestData->szTestTime,strTemp.GetBuffer(0)); 

						Layer1++;
					}		
				}
			}

			nDataCnt = Layer1;
			

			//2.2 附件信息
			//---------------------------------------------------------------------------
			pRootType = pRoot->FirstChildElement(MD_XML_ROOT_OUT_APP_DATA);

			if (pRootType)
			{
				//1.
				strTemp = pRootType->Attribute(MD_XML_ATTR_COUNT_ROOT);
				nCount = atoi(strTemp.GetBuffer(0));
				pParMng->m_nOutAppDataCnt = nCount;

				//第一层
				pRoot1 = pRootType->FirstChildElement(MD_XML_ATTR_ROOT_1);		
				Layer1 = 0;
				if (pRoot1)
				{
					for (pRoot1; pRoot1; pRoot1=pRoot1->NextSiblingElement(MD_XML_ATTR_ROOT_1))
					{
						//第二层
						pRoot2 = pRoot1->FirstChildElement(MD_XML_ATTR_ROOT_2);	

						pStOutAppData = &pParMng->m_stOutAppData[Layer1];

						//结果数据
						//1.
						strTemp = pRoot1->Attribute(MD_XML_ST_APP_TAB_DATA_POS);			
						pStOutAppData->nTabDataPos = atoi(strTemp.GetBuffer(0));					
						//2.
						strTemp = pRoot1->Attribute(MD_XML_ST_APP_APPENDIX_TYPE);	
						pStOutAppData->nAppendixType  = atoi(strTemp.GetBuffer(0));
						//3.
						strTemp = pRoot1->Attribute(MD_XML_ST_APP_SRC_FILE_NAME);	
						strcpy(pStOutAppData->szSrcFileName, strTemp.GetBuffer(0));
						//4.
						strTemp = pRoot1->Attribute(MD_XML_ST_APP_DES_FILE_NAME);	
						strcpy(pStOutAppData->szDesFileName, strTemp.GetBuffer(0));
						//5.
						strTemp = pRoot1->Attribute(MD_XML_ST_APP_UP_USR);	
						strcpy(pStOutAppData->szUpUsr,strTemp.GetBuffer(0)); 
						//6.
						strTemp = pRoot1->Attribute(MD_XML_ST_APP_UP_TIME);	
						strcpy(pStOutAppData->szUpTime,strTemp.GetBuffer(0)); 

						Layer1++;
					}		
				}
			}
	
			
		}//if pRoot
		
	}//if pRootInfo
	
	return 1;
}

//3.模板表_历史极值检测	
int CModeXmlAnalysis::GetXmlMdTabHisInfo( )		//获取模板表_历史极值检测
{
	CModeParMng *pParMng = m_pParMng;
	char      szFileName[MAX_PATH] = {0,};
	
	GetCurModeXmlFileName(MD_XML_FILE_TAB_HIS_INFO, szFileName);
	
	//------------------------------------------------------------------------------
	TiXmlDocument   doc( szFileName );
	TiXmlElement	* pRootInfo;
	if (!doc.LoadFile())
	{
		return 0;
	}
	pRootInfo = doc.RootElement();
	//-------------------------------------------------------------------------------
	StTabHisChk   *pStTabHisChk = NULL;
	
	TiXmlElement	*pRoot,  *pRoot1;
	int				Layer1;
	CString			strTemp, str;
	int             nRowNum = 0;
	int             nColNum = 0;
	int             nRowPos=0, nColPos=0;
	int             nCount=0;
		
	Layer1 = 0;
	
	if (pRootInfo)
	{
		//  ----------------------------------------------------------------------
		pRoot= pRootInfo->FirstChildElement(MD_XML_CFG_TAB_HIS_INFO);
		if (pRoot)
		{	
			//1.
			strTemp = pRoot->Attribute(MD_XML_ATTR_COUNT_ROOT);
			nCount = atoi(strTemp.GetBuffer(0));
				
			//第一层
			pRoot1 = pRoot->FirstChildElement(MD_XML_ATTR_ROOT_1);		
			Layer1 = 0;
			if (pRoot1)
			{
				for (pRoot1; pRoot1; pRoot1=pRoot1->NextSiblingElement(MD_XML_ATTR_ROOT_1))
				{		
					pStTabHisChk = &pParMng->m_stTabHisChk[Layer1];
						
					//历史极值
					//1.
					strTemp = pRoot1->Attribute(MD_XML_ST_HIS_FLAG);		//检测标志	
					pStTabHisChk->bHisChkFlag = atoi(strTemp.GetBuffer(0));
					//2.
					strTemp = pRoot1->Attribute(MD_XML_ST_HIS_MIN);			//最小值
					strcpy(pStTabHisChk->szHisValMin, strTemp.GetBuffer(0)); 
					//3.
					strTemp = pRoot1->Attribute(MD_XML_ST_HIS_MAX);			//最大值
					strcpy(pStTabHisChk->szHisValMax, strTemp.GetBuffer(0)); 

					Layer1++;
				}		
			
			}
			
			
		}//if pRoot
		
	}//if pRootInfo
	
	return 1;
}