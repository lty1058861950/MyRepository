#include "stdafx.h"
#include "SysSetConfig.h"

static void GetSysDateString(char *cDate)
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

static void GetSysTimeString(char *cTime)
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

static void SetXmlRootInfoLoad(TiXmlElement *pRootInfo)
{	
	char Date[24] = {0}; 
	char Time[24] = {0};
	GetSysDateString(Date);
	GetSysTimeString(Time);
	pRootInfo->SetAttribute("Version", DECL_LOAD_VERSION);
	pRootInfo->SetAttribute("Date", Date);
	pRootInfo->SetAttribute("Time", Time);
}

CSysSetConfig::CSysSetConfig(void)
{
}

CSysSetConfig::~CSysSetConfig(void)
{
}


int CSysSetConfig::SetSelProductConfig(CString strUserLogName,vector<StBasProduct *> *pArrayProduct)
{
	//生成任务结构//
	char      szFileName[512] = {0,};
	CString str,str1,str2;

	memset(szFileName,0,sizeof(szFileName));
	sprintf(szFileName,_T("%s\\%s"),g_WorkPath,USER_DIR_DEF);
	if(GetFileAttributes(szFileName) == 0xFFFFFFFF)
	{
		CreateDirectory(szFileName,NULL);
	}

	str = szFileName;
	memset(szFileName,0,sizeof(szFileName));
	sprintf(szFileName,_T("%s\\%s_%02d%s"),str,strUserLogName,g_CurSelDepart.nOid,USER_CONFIG_DEF);
	remove(szFileName);

	int i,nCount;
	//建立XML文件头----------------------------------------------------------------------------
	TiXmlDocument	doc;
	TiXmlDeclaration* pDec = new TiXmlDeclaration(DECL_LOAD_VERSION, DECL_LOAD_ENCODING, DECL_LOAD_STANDALONE);
	doc.LinkEndChild(pDec);
	TiXmlElement* pRootInfo = new TiXmlElement("RootInfo");
	doc.LinkEndChild(pRootInfo);	
	SetXmlRootInfoLoad(pRootInfo);
	//-----------------------------------------------------------------------------------------
	TiXmlElement	*pTabSrtRoot, *pTempRoot; 
	TiXmlElement    *pTempElem1;

	//测试模板结构信息 Set
	pTabSrtRoot = new TiXmlElement("UserSetConfig");
	pRootInfo->LinkEndChild(pTabSrtRoot);

	//1.1_TabItemData
	pTempRoot = new TiXmlElement("SelProductInfo");

	nCount = pArrayProduct->size();
	pTempRoot->SetAttribute("RowCnt", nCount);
	pTabSrtRoot->LinkEndChild(pTempRoot);

	CString strText;
	StBasProduct *pProductInfo;
	for(i = 0;i<nCount;i++)//第一层 共有多少个附件//
	{
		pProductInfo = pArrayProduct->at(i);
		strText.Format("ItemRoot%d",i+1);
		pTempElem1 = new TiXmlElement(strText);
		pTempElem1->SetAttribute("nOid", pProductInfo->nOid);
		pTempElem1->SetAttribute("szProductNo", pProductInfo->szProductNo);
		pTempElem1->SetAttribute("szProductName", pProductInfo->szProductName);
		pTempRoot->LinkEndChild(pTempElem1);
	}

	doc.SaveFile(szFileName);
	return 1;

}
int CSysSetConfig::GetSelProductConfig(CString strUserLogName,vector<StBasProduct *> *pArrayProduct)
{
	char      szFileName[MAX_PATH] = {0,};
	CString  str;
	memset(szFileName,0,sizeof(szFileName));
	sprintf(szFileName,_T("%s\\%s"),g_WorkPath,USER_DIR_DEF);
	if(GetFileAttributes(szFileName) == 0xFFFFFFFF)
	{
		CreateDirectory(szFileName,NULL);
	}

	str = szFileName;
	memset(szFileName,0,sizeof(szFileName));
	sprintf(szFileName,_T("%s\\%s_%02d%s"),str,strUserLogName,g_CurSelDepart.nOid,USER_CONFIG_DEF);

	//------------------------------------------------------------------------------
	TiXmlDocument   doc( szFileName );
	TiXmlElement	* pRootInfo;
	if (!doc.LoadFile())
	{
		return 0;
	}
	pRootInfo = doc.RootElement();
	TiXmlElement	*pRoot, *pRootType, *pRoot1;
	int				Layer1, Layer2, Layer3;
	CString			strTemp;
	int             nRowNum = 0;
	int             nColNum = 0;
	int             nRowPos=0, nColPos=0;
	int             nCount=0;



	Layer1 = 0;
	Layer2 = 0;
	Layer3 = 0;

	if (pRootInfo)
	{
		//  ----------------------------------------------------------------------
		pRoot= pRootInfo->FirstChildElement("UserSetConfig");
		if (pRoot)
		{
			//2.1 结果数据
			pRootType = pRoot->FirstChildElement("SelProductInfo");

			if (pRootType)
			{
				//1.
				strTemp = pRootType->Attribute("RowCnt");
				nCount = atoi(strTemp.GetBuffer(0));

				CString strText;


				for (int i = 0;i<nCount;i++)
				{
					StBasProduct *pProductInfo = new StBasProduct;
					memset(pProductInfo,0,sizeof(StBasProduct));
					//第一层
					strText.Format("ItemRoot%d",i+1);
					pRoot1 = pRootType->FirstChildElement(strText);
					if (pRoot1)
					{
						pProductInfo->nOid = atoi(pRoot1->Attribute(_T("nOid")));
						strcpy(pProductInfo->szProductNo, pRoot1->Attribute(_T("szProductNo")));
						strcpy(pProductInfo->szProductName, pRoot1->Attribute(_T("szProductName")));
						
						pArrayProduct->push_back(pProductInfo);
					}
				}


			}
		}

	}//if pRootInfo

	return 1;
}
