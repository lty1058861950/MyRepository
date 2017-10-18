// LoadMesTask.cpp : implementation file
//

#include "stdafx.h"
#include "DataManage.h"
#include "LoadMesTask.h"


// CLoadMesTask dialog

IMPLEMENT_DYNAMIC(CLoadMesTask, CDialog)

CLoadMesTask::CLoadMesTask(CWnd* pParent /*=NULL*/)
	: CDialog(CLoadMesTask::IDD, pParent)
{

}

CLoadMesTask::~CLoadMesTask()
{
}

void CLoadMesTask::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CLoadMesTask, CDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDOK, &CLoadMesTask::OnBnClickedOk)
END_MESSAGE_MAP()


// CLoadMesTask message handlers

BOOL CLoadMesTask::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	InitListInfo1( );			//初始化列表头信息

	AdjustOnSize( );

	//this->MoveWindow(0, 0, 1024, 768);
	this->MoveWindow(0,0,1224,g_WinHeight);
	this->CenterWindow();

	int nCnt = 0;
	CString str;
	m_DMng.GetMesProductCount(nCnt);
		
	str.Format("%d", nCnt);
	//AfxMessageBox(str);

	m_DMng.GetMesProductInfo(nCnt, &m_ListCtrl);

	m_nMesBasTaskCnt = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLoadMesTask::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	AdjustOnSize();
}

void CLoadMesTask::AdjustOnSize( )
{
	CRect  rect;
	int    x,y, nHeight, nWidth, nBord = 25, nBord2 = 30+25, nNum = 300;

	if ( !GetDlgItem(IDC_LIST1)->GetSafeHwnd() )
	{
		return;
	}

	GetClientRect(&rect);

	x = 10; 
	y = 10;
	nWidth  = rect.Width()- 20;
	nHeight = rect.Height() - 50;
	GetDlgItem(IDC_LIST1)->MoveWindow(x, y , nWidth, nHeight);

	x = rect.Width()  - 200;
	y = rect.Height() - 30;
	nWidth  = 80;
	nHeight = 26; 
	GetDlgItem(IDOK)->MoveWindow(x, y, nWidth, nHeight);

	x = rect.Width() - 100;
	GetDlgItem(IDCANCEL)->MoveWindow(x, y, nWidth, nHeight);

}

void CLoadMesTask::InitListInfo1( )			//显示列表信息
{
	CListCtrl *pList = (CListCtrl *) GetDlgItem(IDC_LIST1);

	pList->SetExtendedStyle(pList->GetExtendedStyle() | LVS_EX_GRIDLINES |
		LVS_EX_FULLROWSELECT);

	char ItemName[20][20] = {	"序号",		"设备名称",	"设备型号",		"生产厂家",
								"通讯方式"
							};

	int ItemLen[20]      =	{	80,		250,		250,			120,
		120
	};
	
	/*
	char *ColName[] = {"序号","锁状态","所属型号","课题编号任务号","产品名称",
		"产品代号","数量","产品编号","产品阶段","军检",
		"典试数量","检验组长","检验员姓名","交检部门","工艺员",
		"工序检验","验收依据1","验收依据2","验收依据3","验收依据4",
		"验收依据5","交检人","交检人日期","工序检验意见","工序检验签名",
		"工序检验日期","产品工艺","产品工艺日期","交检部门领导意见","交检部门领导签名",
		"交检部门领导签字日期","检验员意见","检验员签名","检验员日期","备注"};
	int  ColWidth[] = {50,100,100,200,150,  100,100,200,100,100,
		100,100,100,100,100,  100,200,200,200,200,  200,100,150,100,100,
		150,100,150,100,100,  200,100,100,150,300};
	*/

	char *ColName[] = {"序号",		
						"OID",				"产品代号",			"产品编号",    "整理后产品代号",
						"整理后产品编号",   "图号代号",			"图号名称",    "课题编号",		
						"产品名称",		    "型号",				"产品阶段",	  "典试数量", 
					};
	int  ColWidth[] = {	50,
						80,  	150,	200,	100,  
						100,	100,	150,	150,
						100,    100,    100,    100
					};

	int		i;
	CString str, strItem;

	pList->DeleteAllItems();

	if (pList->GetHeaderCtrl() != NULL)
	{
		while (pList->GetHeaderCtrl()->GetItemCount() > 0)
		{	
			pList->DeleteColumn(0);
		}
	}

	for (i=0; i<13; i++)
	{
		pList->InsertColumn(i, ColName[i], LVCFMT_LEFT, ColWidth[i]);	
	}

}




void CLoadMesTask::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//OnOK();
	LoadMesTaskInfo2( );		//第一种方法

}

//=================================================================================
void CLoadMesTask::LoadMesTaskInfo1( )		//第一种方法
{
	CListCtrl *pList = &m_ListCtrl;
	char      szCurProductNo[100] = {0,};		//当前产品代号
	char      szCurProductCode[100] = {0,};		//当前产品编号
	char      szProductNo[100]   = {0,};
	char      szProductCode[100] = {0,};
	CString   str;
	CString   strProductNo, strProductCode, strPicNo, strPicName;
	CString   strProjectNo, strProductName, strModelNo, strPhase, strDianShiQty;
	CString   strSumCode, strSumPicNo, strSumPicName;
	CString   strTmpTaskName;
	int       nCodeCnt, nPicNoCnt;
	StBasProduct	stBasProduct, *pStBasProduct;		//产品信息
	//StBasSeries		stBasSeries,  *pStBasSeries;        //产品系列信息
    StBasPicNum     stBasPicNum,  *pStBasPicNum;        //产品图号信息
	StBasTask		stBasTask,	  *pStBaseTask;			//任务信息
	StBasTaskCode	stBasTaskCode, *pStBasTaskCode;		//任务编号信息
	StBasTaskPicNum stBasTaskPicNum, *pStBasTaskPicNum;	//任务图号信息


	UINT       nOid, nCurOid, nPrevOid;
	int		  i,j, nProdPos, nTaskPos,nCnt;
	int       nCurGroupOid = 1;
	char     szCreateTime[DB_USER_LEN] = {0,};			//07.创建时间
	char     szCreateUser[DB_USER_LEN] ={0,}; 
	int      bProdExist = 0, bExist,bTaskExist; 
	int      ret;
	int      tick1,tick2;
	tick1 = GetTickCount();

	//部门OID
    nCurGroupOid = g_CurSelDepart.nOid;   //注意：需全局变量初始化, 部门OID

	//部门名称

	GetSysDateTime(szCreateTime);

	
	nCnt = pList->GetItemCount();
	nCurOid   = 0;
	nProdPos  = 0;	//产品个数
	nTaskPos  = 0;   //任务个数
	nCodeCnt  = 0;	//编号个数
	nPicNoCnt = 0;  //图号个数
	strSumCode	  = "";
	strSumPicNo   = "";
	strSumPicName = "";

	pStBasProduct = &stBasProduct;		//产品信息
	//pStBasSeries  = &stBasSeries;		//产品系列信息 
	pStBasPicNum  = &stBasPicNum;		//产品图号信息
	pStBaseTask	  = &stBasTask;			//任务信息
	pStBasTaskCode= &stBasTaskCode;		//任务编号信息
	pStBasTaskPicNum = &stBasTaskPicNum;	//任务图号信息

	for (i=0; i<nCnt; i++)
	{
		str = pList->GetItemText(i, 1);
		nOid = atoi(str.GetBuffer(0));
		strProductNo    = pList->GetItemText(i, 4);		//01.产品代号
		strProductCode  = pList->GetItemText(i, 5);		//02.产品编号
		strPicNo		= pList->GetItemText(i, 6);		//03.图号代号
		strPicName		= pList->GetItemText(i, 7);		//04.图号名称
		strProjectNo	= pList->GetItemText(i, 8);		//05.课题编号
		strProductName  = pList->GetItemText(i, 9);		//06.产品名称
		strModelNo      = pList->GetItemText(i, 10);	//07.型号
		strPhase        = pList->GetItemText(i, 11);	//08.阶段
		strDianShiQty   = pList->GetItemText(i, 12);	//09.典试数量
		

		if (i == 0)
		{
			if (strcmp(szCurProductNo, strProductNo.GetBuffer(0)) != 0)
			{
				memset(szCurProductNo,	0, 100);
				strcpy(szCurProductNo, strProductNo.GetBuffer(0));

				//nCurOid = nOid;
				
				str.Format("插入产品信息：nOid=%d, nProdPos=%d, Product_no=%s", nOid, nProdPos+1, szCurProductNo);
				//AfxMessageBox(str);
				g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);

				//插入产品信息(1)
				//--------------------------------------------------------------------------------------
				memset(pStBasProduct, 0, sizeof(StBasProduct));
				//UINT	nOid;						      							//01.产品代号OID
				strcpy(pStBasProduct->szProductNo, strProductNo.GetBuffer(0));		//02.产品代号
				strcpy(pStBasProduct->szProductName, strProductName.GetBuffer(0)); //03.产品名称
				pStBasProduct->nPicNumType = Product_Line;							//05.图号类型:0.无图号(普通产品),1.有图号(线缆)
				pStBasProduct->nGroupOid   = nCurGroupOid;							//06.所在部门OID
				strcpy(pStBasProduct->szCreateTime, szCreateTime);					//07.创建时间
				strcpy(pStBasProduct->szCreateUser, szCreateUser);					//08.创建人

				//1.1产品代号
				//----------------------------------
				bProdExist = m_DMng.IsProdExists(nCurGroupOid, pStBasProduct->szProductNo);
				if (bProdExist == 0)  
				{
					ret = m_DMng.AddNewProd(pStBasProduct);
					if (ret != 0)
					{
						AddNewProductToConfig(pStBasProduct);
						str.Format("DB_OPT_插入_产品代号_成功：nOid=%d, nProdPos=%d, Product_no=%s", nOid, nProdPos+1, szCurProductNo);
						g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
					}
					else
					{
						str.Format("DB_ERR_插入_产品代号_异常：nOid=%d, nProdPos=%d, Product_no=%s", nOid, nProdPos+1, szCurProductNo);
						g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
						AfxMessageBox(str);
						return;
					}
				}
				else
				{
					ret = m_DMng.GetProdDataGroupOidProdNo(nCurGroupOid,strProductNo.GetBuffer(0), pStBasProduct);
					if (ret != 0)
					{
						str.Format("DB_OPT_插入_产品代号_代号已存在：nOid=%d, nProdPos=%d, Product_no=%s", nOid, nProdPos+1, szCurProductNo);
						g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
					}
					else
					{
						str.Format("DB_ERR_插入_产品代号_读取异常：nOid=%d, nProdPos=%d, Product_no=%s", nOid, nProdPos+1, szCurProductNo);
						g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
						AfxMessageBox(str);
						return;
					}
				
				}

				
				
				//--------------------------------------------------------------------------------------

				nProdPos++;

			}	
		}

		if (nOid != nCurOid) 
		{
			if (strSumCode.GetLength() != 0)
			{
				str.Format("插入任务信息：nOid=%d, nTaskPos=%d, Product_no=%s, Porduct_CodeList=%s, PicNumList = %s",
					nCurOid, nTaskPos+1, szProductNo, strSumCode, strSumPicNo);
				//AfxMessageBox(str);
				g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);

				//插入任务信息(1)
				//--------------------------------------------------------------------------------------
				pStBaseTask->Release();

				//ztedit for 2017-03-23
				//strTmpTaskName.Format("%s_%d", pStBasSeries->szProductNo, nCurOid);
				strTmpTaskName.Format("%s_%d", strProductNo, nCurOid);

				//UINT	nOid;						      						//01.任务OID
				strcpy(pStBaseTask->stTaskBaseInfo.szTaskName, strTmpTaskName);							//02.任务名称
				strcpy(pStBaseTask->stTaskBaseInfo.szProjectNo, strProjectNo);					//03.检验单号
				//UINT	nTaskStatus;											//04.任务状态
				//UINT	nTaskType;	      										//05.任务类型
				strcpy(pStBaseTask->stTaskBaseInfo.szModel, strModelNo);						//06.型号
				strcpy(pStBaseTask->stTaskBaseInfo.szPhase, strPhase);							//07.阶段
				pStBaseTask->stProductInfo.nOid = pStBasProduct->nOid;					//08.产品OID
				strcpy(pStBaseTask->stProductInfo.szProductName, strProductNo);				//09.产品名称
				strcpy(pStBaseTask->stProductInfo.szProductNo,  strProductNo);				//10.产品代号


				//ztedit for 2017-03-23
				pStBaseTask->stTaskBaseInfo.nSeriesOid = 0;
				strcpy(pStBaseTask->stTaskBaseInfo.szSeriesName, "");

				//pStBaseTask->stTaskBaseInfo.nSeriesOid = pStBasSeries->nOid;					//11.产品系列号OID
				//strcpy(pStBaseTask->stTaskBaseInfo.szSeriesName, pStBasSeries->szSeriesName);	//12.产品系列号名称
				
				//char    szProductCode[DB_USER_LEN];							//13.产品编号
				//int  	nCodeNumber;											//14.数量
				//char    szBatch[DB_USER_LEN];		       						//15.批次号
				pStBaseTask->stTaskBaseInfo.nGroupOid = nCurGroupOid;								//16.交检部门
				//char    szGroupName[DB_USER_LEN];								//16_1 交检部门名称
				//char    szUpUser[DB_USER_LEN];								//17.交检人
				//char    szUpDate[DB_USER_LEN];		    					//18.交检日期
				//char    szSendDate[DB_USER_LEN];								//19.下发日期
				//char    szCheckLeader[DB_USER_LEN];							//20.检验组长
				//char    szCheckUser[DB_USER_LEN];								//21.检验员姓名
				//char    szTechUser[DB_USER_LEN];								//22.工艺员 
				//int  	nArmyTest;												//23.军检
				pStBaseTask->stTaskBaseInfo.nDianShiNum = atoi(strDianShiQty.GetBuffer(0));	//24.典试数量
				//char    szAccording1[DB_BACK_LEN];			//25.验收依据1
				//char    szAccording2[DB_BACK_LEN];			//26.验收依据2
				//char    szAccording3[DB_BACK_LEN];			//27.验收依据3
				//char    szAccording4[DB_BACK_LEN];			//28.验收依据4
				//char    szAccording5[DB_BACK_LEN];			//29.验收依据5
				//char    szTaskRemark[DB_BACK_LEN];			//30.备注
				//char    szPlanBegTime[DB_USER_LEN];			//31.计划开始时间
				//char    szPlanEndTime[DB_USER_LEN];			//32.计划结束时间
				//char    szRealBegTime[DB_USER_LEN];			//33.实际开始时间
				//char    szRealEndTime[DB_USER_LEN];			//34.实际结束时间

				//2.1任务信息
				//----------------------------------
				
				bTaskExist = m_DMng.IsProductTaskExists(pStBasProduct->nOid, strTmpTaskName.GetBuffer(0));
				if (bTaskExist == 0)
				{
					ret = m_DMng.AddNewTask(pStBaseTask);
					if (ret != 0)
					{
						str.Format("DB_OPT_插入_任务_成功：nOid=%d, nTaskPos=%d, Product_no=%s, Porduct_CodeList=%s, PicNumList = %s",
							nCurOid, nTaskPos+1, szProductNo, strSumCode, strSumPicNo);
						g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
					}
					else
					{
						str.Format("DB_ERR_插入_任务_异常：nOid=%d, nTaskPos=%d, Product_no=%s, Porduct_CodeList=%s, PicNumList = %s",
							nCurOid, nTaskPos+1, szProductNo, strSumCode, strSumPicNo);
						g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
						AfxMessageBox(str);
						return;
					}
				}

				//2.2任务编号信息
				//----------------------------------

					GetTaskInfo( nCodeCnt, strSumCode.GetBuffer(0));

					for (j=0; j<m_nDesCodeCnt; j++)
					{
						memset(pStBasTaskCode, 0, sizeof(StBasTaskCode));
						
						//UINT nOid;											//01.任务编号OID
						pStBasTaskCode->nTaskOid = pStBaseTask->stTaskBaseInfo.nOid;			//02.任务OID
						pStBasTaskCode->nCodeIndex = j+1;						//03.任务内编号顺序从1开始
						pStBasTaskCode->nDianshiTest = 0;						//04.是否典试
						strcpy(pStBasTaskCode->szCodeName, m_DesCodeName[j]);	//05.编号名称

						ret = m_DMng.AddNewTaskCode(pStBasTaskCode);
						if (ret != 0)
						{
							str.Format("DB_OPT_插入_任务编号_成功：nOid=%d, nTaskPos=%d, Product_no=%s, Porduct_CodeList=%s, PicNumList = %s",
								nCurOid, nTaskPos+1, szProductNo, strSumCode, strSumPicNo);
							g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
						}
						else
						{
							str.Format("DB_ERR_插入_任务编号_异常：nOid=%d, nTaskPos=%d, Product_no=%s, Porduct_CodeList=%s, PicNumList = %s",
								nCurOid, nTaskPos+1, szProductNo, strSumCode, strSumPicNo);
							g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
							AfxMessageBox(str);
							return;
						}

					}

					//2.3插入产品图号 + 任务图号
					//----------------------------------
					GetPicNumInfo(nPicNoCnt, strSumPicNo.GetBuffer(0), strSumPicName.GetBuffer(0));

					for (j=0; j<m_nDesPicCnt; j++)
					{
						//2.3.1 插入产品图号代号
						//----------------------------------------------------
						memset(pStBasPicNum, 0, sizeof(StBasPicNum));
						ret = m_DMng.GetProdPicNumData(pStBasProduct->nOid, m_DesPicNo[j], pStBasPicNum);//判断此产品图号是否存在
						if (ret == 0)
						{
							memset(pStBasPicNum, 0, sizeof(StBasPicNum));

							//插入产品图号
							//UINT	nOid;						      						//01.产品图号OID
							strcpy(pStBasPicNum->szPicNumNo, m_DesPicNo[j]);				//02.图号代号
							strcpy(pStBasPicNum->szPicNumName, m_DesPicName[j]);			//03.图号名称
							pStBasPicNum->nProductOid = pStBasProduct->nOid;				//04.产品OID
							strcpy(pStBasPicNum->szProductNo, pStBasProduct->szProductNo);	//05.产品代号
							strcpy(pStBasPicNum->szCreateTime, szCreateTime);				//06.创建时间
							strcpy(pStBasPicNum->szCreateUser, szCreateUser);				//07.创建人

							//添加产品图号
							ret = m_DMng.AddNewPicNum(pStBasPicNum);
							if (ret != 0)
							{
								str.Format("DB_OPT_插入_产品图号_成功：nOid=%d, nTaskPos=%d, Product_no=%s, PicNo=%s, PicName = %s",
									nCurOid, nTaskPos+1, szProductNo, m_DesPicNo[j], m_DesPicName[j]);
								g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
							}
							else
							{
								str.Format("DB_ERR_插入_产品图号_异常：nOid=%d, nTaskPos=%d, Product_no=%s, PicNo=%s, PicName = %s",
									nCurOid, nTaskPos+1, szProductNo, m_DesPicNo[j], m_DesPicName[j]);
								g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
								AfxMessageBox(str);
								return;
							}

						}

						//2.3.2 插入任务图号
						//-----------------------------------------------------
						memset(pStBasTaskPicNum, 0, sizeof(StBasTaskPicNum));
						
						//UINT nOid;											//01.任务编号表OID
						pStBasTaskPicNum->nTaskOid = pStBaseTask->stTaskBaseInfo.nOid;			//02.任务OID
						pStBasTaskPicNum->nPicNumIndex = j+1;					//03.任务内模板顺序从1开始
						pStBasTaskPicNum->nPicNumOid = pStBasPicNum->nOid;		//04.图号Oid
						strcpy(pStBasTaskPicNum->szPicNumNo, m_DesPicNo[j]);    //05.图号代号
						strcpy(pStBasTaskPicNum->szPicNumName, m_DesPicName[j]);//06.图号名称

						
						//添加任务图号
						ret = m_DMng.AddNewTaskPicNum(pStBasTaskPicNum);
						if (ret != 0)
						{
							str.Format("DB_OPT_插入_任务图号_成功：nOid=%d, nTaskPos=%d, Product_no=%s, PicNo=%s, PicName = %s",
								nCurOid, nTaskPos+1, szProductNo, m_DesPicNo[j], m_DesPicName[j]);
							g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
						}
						else
						{
							str.Format("DB_ERR_插入_任务图号_异常：nOid=%d, nTaskPos=%d, Product_no=%s, PicNo=%s, PicName = %s",
								nCurOid, nTaskPos+1, szProductNo, m_DesPicNo[j], m_DesPicName[j]);
							g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
							AfxMessageBox(str);
							return;
						}
					}
					

				//--------------------------------------------------------------------------------------

				nTaskPos++;
			}

			nPrevOid = nCurOid;
			nCurOid = nOid;

			memset(szProductNo,		0, 100);
			memset(szProductCode,	0, 100);
			strcpy(szProductNo,		strProductNo.GetBuffer(0));
			strcpy(szProductCode,	strProductCode.GetBuffer(0));

			nCodeCnt  = 0;
			nPicNoCnt = 0;
			strSumCode   = szProductCode;
			strSumPicNo   = strPicNo;
			strSumPicName = strPicName;
			nCodeCnt++;
			nPicNoCnt++;

			if (strcmp(szCurProductNo, strProductNo.GetBuffer(0)) != 0)
			{
				//
				memset(szCurProductNo,	0, 100);
				strcpy(szCurProductNo, strProductNo.GetBuffer(0));

				str.Format("插入产品信息：nOid=%d, nProdPos=%d, Product_no=%s", nOid, nProdPos+1, szCurProductNo);
				//AfxMessageBox(str);
				g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);

				//插入产品信息(1)
				//--------------------------------------------------------------------------------------
				memset(pStBasProduct, 0, sizeof(StBasProduct));
				//UINT	nOid;						      							//01.产品代号OID
				strcpy(pStBasProduct->szProductNo, strProductNo.GetBuffer(0));		//02.产品代号
				strcpy(pStBasProduct->szProductName, strProductName.GetBuffer(0)); //03.产品名称
				pStBasProduct->nPicNumType = 1;									//05.图号类型:0.无图号(普通产品),1.有图号(线缆)
				pStBasProduct->nGroupOid   = nCurGroupOid;							//06.所在部门OID
				strcpy(pStBasProduct->szCreateTime, szCreateTime);					//07.创建时间
				strcpy(pStBasProduct->szCreateUser, szCreateUser);					//08.创建人

				//1.1产品代号
				//----------------------------------
				bProdExist = m_DMng.IsProdExists(nCurGroupOid, pStBasProduct->szProductNo);
				if (bProdExist == 0)  
				{
					ret = m_DMng.AddNewProd(pStBasProduct);
					if (ret != 0)
					{
						AddNewProductToConfig(pStBasProduct);
						str.Format("DB_OPT_插入_产品代号_成功：nOid=%d, nProdPos=%d, Product_no=%s", nOid, nProdPos+1, szCurProductNo);
						g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
					}
					else
					{
						str.Format("DB_ERR_插入_产品代号_异常：nOid=%d, nProdPos=%d, Product_no=%s", nOid, nProdPos+1, szCurProductNo);
						g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
						AfxMessageBox(str);
						return;
					}

				}
				else
				{
					ret = m_DMng.GetProdDataGroupOidProdNo(nCurGroupOid,strProductNo.GetBuffer(0), pStBasProduct);
					if (ret != 0)
					{
						str.Format("DB_OPT_插入_产品代号_代号已存在：nOid=%d, nProdPos=%d, Product_no=%s", nOid, nProdPos+1, szCurProductNo);
						g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
					}
					else
					{
						str.Format("DB_ERR_插入_产品代号_读取异常：nOid=%d, nProdPos=%d, Product_no=%s", nOid, nProdPos+1, szCurProductNo);
						g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
						AfxMessageBox(str);
						return;
					}

				}

				


				//--------------------------------------------------------------------------------------

				nProdPos++;

			}	
		}
		else
		{
			if (strcmp(strProductCode, szProductCode) != 0)
			{
				memset(szProductCode,	0, 100);
				strcpy(szProductCode,	strProductCode.GetBuffer(0));
				strSumCode = strSumCode + "," +strProductCode;
				nCodeCnt++;
			}

			strSumPicNo = strSumPicNo + "," + strPicNo;
			strSumPicName = strSumPicName + "," + strPicName;
			nPicNoCnt++;
		}

		//m_DMng.AddNewProd(StBasProduct *pStr)

		if (nProdPos > 5)
		{
			//break;
		}
	}

	//最后一条任务信息
	if (strSumCode.GetLength() != 0)
	{
		str.Format("插入任务信息：nOid=%d, nTaskPos=%d, Product_no=%s, Porduct_CodeList=%s, PicNumList = %s",
			nCurOid, nTaskPos+1, szProductNo, strSumCode, strSumPicNo);
		//AfxMessageBox(str);
		g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);

		//插入任务信息(2)
		//--------------------------------------------------------------------------------------
		pStBaseTask->Release();

		//ztedit for 2017-03-23
		//strTmpTaskName.Format("%s_%d", pStBasSeries->szProductNo, nCurOid);
		strTmpTaskName.Format("%s_%d", strProductNo, nCurOid);

		//UINT	nOid;						      						//01.任务OID
		strcpy(pStBaseTask->stTaskBaseInfo.szTaskName, strTmpTaskName);							//02.任务名称
		strcpy(pStBaseTask->stTaskBaseInfo.szProjectNo, strProjectNo);					//03.检验单号
		//UINT	nTaskStatus;											//04.任务状态
		//UINT	nTaskType;	      										//05.任务类型
		strcpy(pStBaseTask->stTaskBaseInfo.szModel, strModelNo);						//06.型号
		strcpy(pStBaseTask->stTaskBaseInfo.szPhase, strPhase);							//07.阶段
		pStBaseTask->stProductInfo.nOid = pStBasProduct->nOid;					//08.产品OID
		strcpy(pStBaseTask->stProductInfo.szProductName, strProductNo);				//09.产品名称
		strcpy(pStBaseTask->stProductInfo.szProductNo,  strProductNo);				//10.产品代号

		//ztedit for 2017-03-23
		pStBaseTask->stTaskBaseInfo.nSeriesOid = 0;					
		strcpy(pStBaseTask->stTaskBaseInfo.szSeriesName, "");
		//pStBaseTask->stTaskBaseInfo.nSeriesOid = pStBasSeries->nOid;					//11.产品系列号OID
		//strcpy(pStBaseTask->stTaskBaseInfo.szSeriesName, pStBasSeries->szSeriesName);	//12.产品系列号名称
		
		//char    szProductCode[DB_USER_LEN];							//13.产品编号
		//int  	nCodeNumber;											//14.数量
		//char    szBatch[DB_USER_LEN];		       						//15.批次号
		pStBaseTask->stTaskBaseInfo.nGroupOid = nCurGroupOid;								//16.交检部门
		//char    szGroupName[DB_USER_LEN];								//16_1 交检部门名称
		//char    szUpUser[DB_USER_LEN];								//17.交检人
		//char    szUpDate[DB_USER_LEN];		    					//18.交检日期
		//char    szSendDate[DB_USER_LEN];								//19.下发日期
		//char    szCheckLeader[DB_USER_LEN];							//20.检验组长
		//char    szCheckUser[DB_USER_LEN];								//21.检验员姓名
		//char    szTechUser[DB_USER_LEN];								//22.工艺员 
		//int  	nArmyTest;												//23.军检
		pStBaseTask->stTaskBaseInfo.nDianShiNum = atoi(strDianShiQty.GetBuffer(0));	//24.典试数量
		//char    szAccording1[DB_BACK_LEN];			//25.验收依据1
		//char    szAccording2[DB_BACK_LEN];			//26.验收依据2
		//char    szAccording3[DB_BACK_LEN];			//27.验收依据3
		//char    szAccording4[DB_BACK_LEN];			//28.验收依据4
		//char    szAccording5[DB_BACK_LEN];			//29.验收依据5
		//char    szTaskRemark[DB_BACK_LEN];			//30.备注
		//char    szPlanBegTime[DB_USER_LEN];			//31.计划开始时间
		//char    szPlanEndTime[DB_USER_LEN];			//32.计划结束时间
		//char    szRealBegTime[DB_USER_LEN];			//33.实际开始时间
		//char    szRealEndTime[DB_USER_LEN];			//34.实际结束时间

		//2.1任务信息
		//----------------------------------

		bTaskExist = m_DMng.IsProductTaskExists(pStBasProduct->nOid, strTmpTaskName.GetBuffer(0));
		if (bTaskExist == 0)
		{
			ret = m_DMng.AddNewTask(pStBaseTask);
			if (ret != 0)
			{
				str.Format("DB_OPT_插入_任务_成功：nOid=%d, nTaskPos=%d, Product_no=%s, Porduct_CodeList=%s, PicNumList = %s",
					nCurOid, nTaskPos+1, szProductNo, strSumCode, strSumPicNo);
				g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
			}
			else
			{
				str.Format("DB_ERR_插入_任务_异常：nOid=%d, nTaskPos=%d, Product_no=%s, Porduct_CodeList=%s, PicNumList = %s",
					nCurOid, nTaskPos+1, szProductNo, strSumCode, strSumPicNo);
				g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
				AfxMessageBox(str);
				return;
			}
		}

		//2.2任务编号信息
		//----------------------------------

		GetTaskInfo( nCodeCnt, strSumCode.GetBuffer(0));

		for (j=0; j<m_nDesCodeCnt; j++)
		{
			memset(pStBasTaskCode, 0, sizeof(StBasTaskCode));

			//UINT nOid;											//01.任务编号OID
			pStBasTaskCode->nTaskOid = pStBaseTask->stTaskBaseInfo.nOid;			//02.任务OID
			pStBasTaskCode->nCodeIndex = j+1;						//03.任务内编号顺序从1开始
			pStBasTaskCode->nDianshiTest = 0;						//04.是否典试
			strcpy(pStBasTaskCode->szCodeName, m_DesCodeName[j]);	//05.编号名称

			ret = m_DMng.AddNewTaskCode(pStBasTaskCode);
			if (ret != 0)
			{
				str.Format("DB_OPT_插入_任务编号_成功：nOid=%d, nTaskPos=%d, Product_no=%s, Porduct_CodeList=%s, PicNumList = %s",
					nCurOid, nTaskPos+1, szProductNo, strSumCode, strSumPicNo);
				g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
			}
			else
			{
				str.Format("DB_ERR_插入_任务编号_异常：nOid=%d, nTaskPos=%d, Product_no=%s, Porduct_CodeList=%s, PicNumList = %s",
					nCurOid, nTaskPos+1, szProductNo, strSumCode, strSumPicNo);
				g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
				AfxMessageBox(str);
				return;
			}

		}

		//2.3插入产品图号 + 任务图号
		//----------------------------------
		GetPicNumInfo(nPicNoCnt, strSumPicNo.GetBuffer(0), strSumPicName.GetBuffer(0));

		for (j=0; j<m_nDesPicCnt; j++)
		{
			//2.3.1 插入产品图号代号
			//----------------------------------------------------
			memset(pStBasPicNum, 0, sizeof(StBasPicNum));
			ret = m_DMng.GetProdPicNumData(pStBasProduct->nOid, m_DesPicNo[j], pStBasPicNum);//判断此产品图号是否存在
			if (ret == 0)
			{
				memset(pStBasPicNum, 0, sizeof(StBasPicNum));

				//插入产品图号
				//UINT	nOid;						      						//01.产品图号OID
				strcpy(pStBasPicNum->szPicNumNo, m_DesPicNo[j]);				//02.图号代号
				strcpy(pStBasPicNum->szPicNumName, m_DesPicName[j]);			//03.图号名称
				pStBasPicNum->nProductOid = pStBasProduct->nOid;				//04.产品OID
				strcpy(pStBasPicNum->szProductNo, pStBasProduct->szProductNo);	//05.产品代号
				strcpy(pStBasPicNum->szCreateTime, szCreateTime);				//06.创建时间
				strcpy(pStBasPicNum->szCreateUser, szCreateUser);				//07.创建人

				//添加产品图号
				ret = m_DMng.AddNewPicNum(pStBasPicNum);
				if (ret != 0)
				{
					str.Format("DB_OPT_插入_产品图号_成功：nOid=%d, nTaskPos=%d, Product_no=%s, PicNo=%s, PicName = %s",
						nCurOid, nTaskPos+1, szProductNo, m_DesPicNo[j], m_DesPicName[j]);
					g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
				}
				else
				{
					str.Format("DB_ERR_插入_产品图号_异常：nOid=%d, nTaskPos=%d, Product_no=%s, PicNo=%s, PicName = %s",
						nCurOid, nTaskPos+1, szProductNo, m_DesPicNo[j], m_DesPicName[j]);
					g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
					AfxMessageBox(str);
					return;
				}

			}

			//2.3.2 插入任务图号
			//-----------------------------------------------------
			memset(pStBasTaskPicNum, 0, sizeof(StBasTaskPicNum));

			//UINT nOid;											//01.任务编号表OID
			pStBasTaskPicNum->nTaskOid = pStBaseTask->stTaskBaseInfo.nOid;			//02.任务OID
			pStBasTaskPicNum->nPicNumIndex = j+1;					//03.任务内模板顺序从1开始
			pStBasTaskPicNum->nPicNumOid = pStBasPicNum->nOid;		//04.图号Oid
			strcpy(pStBasTaskPicNum->szPicNumNo, m_DesPicNo[j]);    //05.图号代号
			strcpy(pStBasTaskPicNum->szPicNumName, m_DesPicName[j]);//06.图号名称


			//添加任务图号
			ret = m_DMng.AddNewTaskPicNum(pStBasTaskPicNum);
			if (ret != 0)
			{
				str.Format("DB_OPT_插入_任务图号_成功：nOid=%d, nTaskPos=%d, Product_no=%s, PicNo=%s, PicName = %s",
					nCurOid, nTaskPos+1, szProductNo, m_DesPicNo[j], m_DesPicName[j]);
				g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
			}
			else
			{
				str.Format("DB_ERR_插入_任务图号_异常：nOid=%d, nTaskPos=%d, Product_no=%s, PicNo=%s, PicName = %s",
					nCurOid, nTaskPos+1, szProductNo, m_DesPicNo[j], m_DesPicName[j]);
				g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
				AfxMessageBox(str);
				return;
			}
		}
		//--------------------------------------------------------------------------------------
		nTaskPos++;
	}


	tick2 = GetTickCount()-tick1;
	str.Format( _T("导出操作完毕, 用时%d毫秒, 产品代号个数=%d, 任务个数=%d"), tick2, nProdPos, nTaskPos);
	g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
	AfxMessageBox(str);
}
//=================================================================================


int  CLoadMesTask::GetTaskInfo(int nCodeCnt, char *szSumTask)
{
	int     i, j, nPos, nLen;
	CString str, strHead, strTail;
	char   *pSrcCodeName=NULL;
	char   *pDesCodeName=NULL;
	int    bSameFlag;

	m_nSrcCodeCnt = 0;
	m_nDesCodeCnt = 0;

	if ( (nCodeCnt <=  0) || (nCodeCnt > MAX_PIC_NUM_CNT) )
	{
		AfxMessageBox("任务个数超出范围!");
		return 0;
	}

	if (nCodeCnt == 1)
	{
		m_nSrcCodeCnt = 1;
		memset( (char*)m_SrcCodeName[0], 0, MAX_PIC_NAME_LEN);
		strcpy(m_SrcCodeName[0], szSumTask);

		m_nDesCodeCnt = 1;
		strcpy(m_DesCodeName[0], szSumTask);
		return 1;
	}

	str = szSumTask;

	m_nSrcCodeCnt = nCodeCnt;
	for (i=0; i<nCodeCnt; i++)
	{
		pSrcCodeName = m_SrcCodeName[i];
		memset( pSrcCodeName, 0, MAX_PIC_NAME_LEN);

		nLen = strlen(str.GetBuffer(0));
		nPos = str.Find( ',');
		if (nPos != -1)
		{
			strHead = str.Left(nPos);
			str = str.Right(nLen-nPos-1);
		}
		else
		{
			strHead = str;
		}
	
		strcpy(pSrcCodeName, strHead.GetBuffer(0));
	}

	m_nDesCodeCnt = 0;

	for (i=0; i<m_nSrcCodeCnt; i++)
	{
		pSrcCodeName = m_SrcCodeName[i];
		bSameFlag = 0;
		for (j=0; j<m_nDesCodeCnt; j++)
		{
			pDesCodeName = m_DesCodeName[j];
			if (strcmp(pSrcCodeName, pDesCodeName) == 0)
			{
				bSameFlag = 1;
				break;
			}
		}

		if (bSameFlag == 0)
		{
			pDesCodeName = m_DesCodeName[m_nDesCodeCnt];
			memset( pDesCodeName, 0, MAX_PIC_NAME_LEN);
			strcpy(pDesCodeName, pSrcCodeName);
			m_nDesCodeCnt++;
		}
	}

	return 1;
}

int  CLoadMesTask::GetPicNumInfo(int nPicCnt, char *szSumPicNo, char *szSumPicName)
{
	int     i, j, nPos, nLen1, nLen2;
	CString str, strNo, strNoHead, strName, strNameHead;
	char   *pSrcPicNo = NULL;
	char   *pSrcPicName=NULL;
	char   *pDesPicNo = NULL;
	char   *pDesPicName=NULL;

	int    bSameFlag;

	m_nSrcPicCnt = 0;
	m_nDesPicCnt = 0;

	if ( (nPicCnt <=  0) || (nPicCnt > MAX_PIC_NUM_CNT) )
	{
		AfxMessageBox("任务个数超出范围!");
		return 0;
	}

	if (nPicCnt == 1)
	{
		m_nSrcPicCnt = 1;
		memset( (char*)m_SrcPicNo[0], 0, MAX_PIC_NAME_LEN);
		memset( (char*)m_SrcPicName[0], 0, MAX_PIC_NAME_LEN);
		strcpy(m_SrcPicNo[0], szSumPicNo);
		strcpy(m_SrcPicName[0], szSumPicName);

		m_nDesPicCnt = 1;
		memset( (char*)m_DesPicNo[0], 0, MAX_PIC_NAME_LEN);
		memset( (char*)m_DesPicName[0], 0, MAX_PIC_NAME_LEN);
		strcpy(m_DesPicNo[0], szSumPicNo);
		strcpy(m_DesPicName[0], szSumPicName);

		return 1;
	}

	strNo   = szSumPicNo;
	strName = szSumPicName;

	m_nSrcPicCnt = nPicCnt;
	for (i=0; i<nPicCnt; i++)
	{
		pSrcPicNo   = m_SrcPicNo[i];
		pSrcPicName = m_SrcPicName[i];
		memset(pSrcPicNo, 0, MAX_PIC_NAME_LEN);
		memset(pSrcPicName, 0, MAX_PIC_NAME_LEN);

		nLen1 = strlen(strNo.GetBuffer(0));
		nPos = strNo.Find( ',');
		if (nPos != -1)
		{
			strNoHead = strNo.Left(nPos);
			strNo = strNo.Right(nLen1-nPos-1);
		}
		else
		{
			strNoHead = strNo;
		}

		nLen2 = strlen(strName.GetBuffer(0));
		nPos = strName.Find( ',');
		if (nPos != -1)
		{
			strNameHead = strName.Left(nPos);
			strName = strName.Right(nLen2-nPos-1);
		}
		else
		{
			strNameHead = strName;
		}

		strcpy(pSrcPicNo,	strNoHead.GetBuffer(0));
		strcpy(pSrcPicName, strNameHead.GetBuffer(0));
	}

	m_nDesPicCnt = 0;

	for (i=0; i<m_nSrcPicCnt; i++)
	{
		pSrcPicNo   = m_SrcPicNo[i];
		pSrcPicName = m_SrcPicName[i];

		bSameFlag = 0;
		for (j=0; j<m_nDesPicCnt; j++)
		{
			pDesPicNo   = m_DesPicNo[j];
			pDesPicName = m_DesPicName[j];

			if (strcmp(pSrcPicNo, pDesPicNo) == 0)
			{
				bSameFlag = 1;
				break;
			}
		}

		if (bSameFlag == 0)
		{
			pDesPicNo   = m_DesPicNo[m_nDesPicCnt];
			pDesPicName = m_DesPicName[m_nDesPicCnt];
			memset( pDesPicNo, 0, MAX_PIC_NAME_LEN);
			memset( pDesPicName, 0, MAX_PIC_NAME_LEN);

			strcpy(pDesPicNo,   pSrcPicNo);
			strcpy(pDesPicName, pSrcPicName);
			m_nDesPicCnt++;
		}
	}

	return 1;

}

//=================================================================================================

int CLoadMesTask::GetTaskInfo2( MesBasTask *pMesBasTask)
{
	int     i, j;
	CString str, strHead, strTail;
	char   *pSrcCodeName=NULL;
	char   *pDesCodeName=NULL;
	char   *pMesCodeName=NULL;
	int    bSameFlag;
	int    nCodeCnt;

	m_nSrcCodeCnt = 0;
	m_nDesCodeCnt = 0;

	nCodeCnt = pMesBasTask->nCodeCnt;

	if ( (nCodeCnt <=  0) || (nCodeCnt > MAX_PIC_NUM_CNT) )
	{
		str.Format( _T("编号个数超出范围! nCodeCnt=%d, Range=[0, %d]"), nCodeCnt, MAX_PIC_NUM_CNT);
		AfxMessageBox(str);
		return 0;
	}

	
	//1.
	//------------------------------------------------------------------------------------
	m_nSrcCodeCnt = nCodeCnt;
	for (i=0; i<nCodeCnt; i++)
	{
		pSrcCodeName = m_SrcCodeName[i];
		memset( pSrcCodeName, 0, MAX_PIC_NAME_LEN);
		strcpy(pSrcCodeName, pMesBasTask->szCodeNameArray[i]);
	}

	//2.
	//------------------------------------------------------------------------------------
	m_nDesCodeCnt = 0;
	for (i=0; i<m_nSrcCodeCnt; i++)
	{
		pSrcCodeName = m_SrcCodeName[i];
		bSameFlag = 0;
		for (j=0; j<m_nDesCodeCnt; j++)
		{
			pDesCodeName = m_DesCodeName[j];
			if (strcmp(pSrcCodeName, pDesCodeName) == 0)
			{
				bSameFlag = 1;
				break;
			}
		}

		if (bSameFlag == 0)
		{
			pDesCodeName = m_DesCodeName[m_nDesCodeCnt];
			memset( pDesCodeName, 0, MAX_PIC_NAME_LEN);
			strcpy(pDesCodeName, pSrcCodeName);
			m_nDesCodeCnt++;
		}
	}

	//3.
	//------------------------------------------------------------------------------------
	for (i=0; i<nCodeCnt; i++)
	{
		pMesCodeName = pMesBasTask->szCodeNameArray[i];
		memset( pMesCodeName, 0, MAX_PIC_NAME_LEN);
	}

	//4.
	//------------------------------------------------------------------------------------
	for (i=0; i<m_nDesCodeCnt; i++)
	{
		pMesCodeName = pMesBasTask->szCodeNameArray[i];
		memset( pMesCodeName, 0, MAX_PIC_NAME_LEN);
		strcpy(pMesCodeName, m_DesCodeName[i]);
	}
	pMesBasTask->nCodeCnt = m_nDesCodeCnt;

	return 1;
}



int CLoadMesTask::GetPicNumInfo2( MesBasTask *pMesBasTask)
{
	int     i, j;
	CString str, strNo, strNoHead, strName, strNameHead;
	char   *pSrcPicNo = NULL;
	char   *pSrcPicName=NULL;
	char   *pDesPicNo = NULL;
	char   *pDesPicName=NULL;

	int    bSameFlag;
	int    nPicCnt;

	m_nSrcPicCnt = 0;
	m_nDesPicCnt = 0;

	nPicCnt = pMesBasTask->nPicNumCnt;

	if ( (nPicCnt <=  0) || (nPicCnt > MAX_PIC_NUM_CNT) )
	{
		str.Format( _T("编号个数超出范围! nCodeCnt=%d, Range=[0, %d]"), nPicCnt, MAX_PIC_NUM_CNT);
		AfxMessageBox(str);
		return 0;
	}

	//1.
	//------------------------------------------------------------------------------------
	m_nSrcPicCnt = nPicCnt;
	for (i=0; i<m_nSrcPicCnt; i++)
	{
		pSrcPicNo   = m_SrcPicNo[i];
		pSrcPicName = m_SrcPicName[i];
		memset(pSrcPicNo, 0, MAX_PIC_NAME_LEN);
		memset(pSrcPicName, 0, MAX_PIC_NAME_LEN);

		strcpy(pSrcPicNo,	pMesBasTask->szPicNoArray[i]);
		strcpy(pSrcPicName, pMesBasTask->szPicNameArray[i]);
	}
	

	//2.
	//------------------------------------------------------------------------------------
	m_nDesPicCnt = 0;
	for (i=0; i<m_nSrcPicCnt; i++)
	{
		pSrcPicNo   = m_SrcPicNo[i];
		pSrcPicName = m_SrcPicName[i];

		bSameFlag = 0;
		for (j=0; j<m_nDesPicCnt; j++)
		{
			pDesPicNo   = m_DesPicNo[j];
			pDesPicName = m_DesPicName[j];

			if (strcmp(pSrcPicNo, pDesPicNo) == 0)
			{
				bSameFlag = 1;
				break;
			}
		}

		if (bSameFlag == 0)
		{
			pDesPicNo   = m_DesPicNo[m_nDesPicCnt];
			pDesPicName = m_DesPicName[m_nDesPicCnt];
			memset( pDesPicNo, 0, MAX_PIC_NAME_LEN);
			memset( pDesPicName, 0, MAX_PIC_NAME_LEN);

			strcpy(pDesPicNo,   pSrcPicNo);
			strcpy(pDesPicName, pSrcPicName);
			m_nDesPicCnt++;
		}
	}

	//3.
	//------------------------------------------------------------------------------------
	for (i=0; i<nPicCnt; i++)
	{	
		memset(pMesBasTask->szPicNoArray[i], 0, MAX_PIC_NAME_LEN);
		memset(pMesBasTask->szPicNameArray[i], 0, MAX_PIC_NAME_LEN);
	}

	//4.
	//------------------------------------------------------------------------------------
	for (i=0; i<m_nDesPicCnt; i++)
	{
		strcpy(pMesBasTask->szPicNoArray[i],   m_DesPicNo[i]);
		strcpy(pMesBasTask->szPicNameArray[i], m_DesPicName[i]);
	}
	pMesBasTask->nPicNumCnt = m_nDesPicCnt;

	return 1;
}

int CLoadMesTask::LoadMesTaskInfo2( )
{
	CListCtrl *pList = &m_ListCtrl;
	char      szCurProductNo[100] = {0,};		//当前产品代号
	char      szCurProductCode[100] = {0,};		//当前产品编号
	char      szProductNo[100]   = {0,};
	char      szProductCode[100] = {0,};
	CString   str;
	CString   strProductNo, strProductCode, strPicNo, strPicName;
	CString   strProjectNo, strProductName, strModelNo, strPhase, strDianShiQty;
	CString   strSumCode, strSumPicNo, strSumPicName;
	CString   strTmpTaskName;
	int       nCodeCnt, nPicNoCnt;
	StBasProduct	stBasProduct, *pStBasProduct;		//产品信息
	//StBasSeries		stBasSeries,  *pStBasSeries;        //产品系列信息
	StBasPicNum     stBasPicNum,  *pStBasPicNum;        //产品图号信息
	StBasTask		stBasTask,	  *pStBaseTask;			//任务信息
	StBasTaskCode	stBasTaskCode, *pStBasTaskCode;		//任务编号信息
	StBasTaskPicNum stBasTaskPicNum, *pStBasTaskPicNum;	//任务图号信息


	int       nTaskOid, nTaskCnt;

	UINT       nOid, nCurOid;
	int		  i,j, nProdPos, nTaskPos,nCnt;
	int       nCurGroupOid = 1;
	char     szCreateTime[DB_USER_LEN] = {0,};			//07.创建时间
	char     szCreateUser[DB_USER_LEN] ={0,}; 
	int      bProdExist = 0, bExist,bTaskExist, bTaskCodeExist, bTaskPicExist, ret;
	int      tick1,tick2;
	tick1 = GetTickCount();

	//部门OID
	nCurGroupOid = g_CurSelDepart.nOid;   //注意：需全局变量初始化, 部门OID

	//部门名称

	GetSysDateTime(szCreateTime);


	nCnt = pList->GetItemCount();
	nCurOid   = 0;
	nProdPos  = 0;	//产品个数
	nTaskPos  = 0;   //任务个数
	nCodeCnt  = 0;	//编号个数
	nPicNoCnt = 0;  //图号个数
	strSumCode	  = "";
	strSumPicNo   = "";
	strSumPicName = "";

	pStBasProduct = &stBasProduct;		//产品信息
	//pStBasSeries  = &stBasSeries;		//产品系列信息 
	pStBasPicNum  = &stBasPicNum;		//产品图号信息
	pStBaseTask	  = &stBasTask;			//任务信息
	pStBasTaskCode= &stBasTaskCode;		//任务编号信息
	pStBasTaskPicNum = &stBasTaskPicNum;	//任务图号信息


	MesBasTask  mesBasTask, *pMesBasTask, *pCurMesBasTask;

	pMesBasTask = &mesBasTask;

	//1.获取测试任务基础信息
	//-------------------------------------------------------------------------------
	m_MesBasTaskInfo.clear();
	m_nMesBasTaskCnt = 0;

	nTaskPos = 0;
	for (i=0; i<nCnt; i++)
	{
		str = pList->GetItemText(i, 1);
		nOid = atoi(str.GetBuffer(0));
		strProductNo    = pList->GetItemText(i, 4);		//01.产品代号
		strProductCode  = pList->GetItemText(i, 5);		//02.产品编号
		strPicNo		= pList->GetItemText(i, 6);		//03.图号代号
		strPicName		= pList->GetItemText(i, 7);		//04.图号名称
		strProjectNo	= pList->GetItemText(i, 8);		//05.课题编号
		strProductName  = pList->GetItemText(i, 9);		//06.产品名称
		strModelNo      = pList->GetItemText(i, 10);	//07.型号
		strPhase        = pList->GetItemText(i, 11);	//08.阶段
		strDianShiQty   = pList->GetItemText(i, 12);	//09.典试数量

		if (nOid != nCurOid)
		{
			nCurOid = nOid;

			//记录产品信息
			memset( (char*)pMesBasTask, 0, sizeof(MesBasTask));

			pMesBasTask->nOid = nOid;											//01.原始OID								
			strcpy(pMesBasTask->szProductNo, strProductNo.GetBuffer(0));		//02.产品代号
			strcpy(pMesBasTask->szProjectNo, strProjectNo.GetBuffer(0));	    //03.检验单号
			strcpy(pMesBasTask->szProductName, strProductName.GetBuffer(0));    //04.产品名称
			strcpy(pMesBasTask->szModel, strModelNo.GetBuffer(0));			    //05.型号
			strcpy(pMesBasTask->szPhase, strPhase.GetBuffer(0));			    //06.阶段
			pMesBasTask->nDianShiNum = atoi(strDianShiQty);						//07.典试数量

			m_MesBasTaskInfo.push_back(mesBasTask);

			nProdPos++;		
		}
	}
	m_nMesBasTaskCnt = nProdPos;

	str.Format("任务个数=%d", nProdPos);
	//AfxMessageBox(str);
   // return 0;


	//2.获取测试任务_编号信息_图号信息
	//-------------------------------------------------------------------------------
	nTaskPos = 0;
	nTaskOid = 0;

	for (i=0; i<nCnt; i++)
	{
		str = pList->GetItemText(i, 1);
		nOid = atoi(str.GetBuffer(0));
		strProductNo    = pList->GetItemText(i, 4);		//01.产品代号
		strProductCode  = pList->GetItemText(i, 5);		//02.产品编号
		strPicNo		= pList->GetItemText(i, 6);		//03.图号代号
		strPicName		= pList->GetItemText(i, 7);		//04.图号名称
		strProjectNo	= pList->GetItemText(i, 8);		//05.课题编号
		strProductName  = pList->GetItemText(i, 9);		//06.产品名称
		strModelNo      = pList->GetItemText(i, 10);	//07.型号
		strPhase        = pList->GetItemText(i, 11);	//08.阶段
		strDianShiQty   = pList->GetItemText(i, 12);	//09.典试数量

		if (nTaskPos < m_MesBasTaskInfo.size())
		{
			pCurMesBasTask = &m_MesBasTaskInfo.at(nTaskPos);
			nTaskOid  = pCurMesBasTask->nOid;

			if (nOid != nTaskOid)
			{
				nTaskPos++;
				pCurMesBasTask = &m_MesBasTaskInfo.at(nTaskPos);
				nTaskOid = pCurMesBasTask->nOid;
			}

			if (nOid == nTaskOid)
			{
				//1.编号信息
				strcpy(pCurMesBasTask->szCodeNameArray[pCurMesBasTask->nCodeCnt], strProductCode.GetBuffer(0));
				pCurMesBasTask->nCodeCnt++;

				//2.图号信息
				strcpy(pCurMesBasTask->szPicNoArray[pCurMesBasTask->nPicNumCnt], strPicNo.GetBuffer(0));
				strcpy(pCurMesBasTask->szPicNameArray[pCurMesBasTask->nPicNumCnt], strPicName.GetBuffer(0));
				pCurMesBasTask->nPicNumCnt++;
			}
			else
			{
				str.Format( _T("nOid检测异常! nOid=%d, TaskOid=%d"), nOid, nTaskOid);
				AfxMessageBox(str);
				return 0;
			}
		}
	}

	//3.处理编号信息和图号信息
	//-------------------------------------------------------------------------------
	nTaskCnt = m_nMesBasTaskCnt;
	for (i=0; i<nTaskCnt; i++)
	{
		pCurMesBasTask = &m_MesBasTaskInfo.at(i);
		ret = GetTaskInfo2(pCurMesBasTask);
		if (ret == 0)
		{
			return 0;
		}

		ret = GetPicNumInfo2(pCurMesBasTask);
		if (ret == 0)
		{
			return 0;
		}
	}

	//4.插入：产品信息, 产品系列信息, 任务信息, 任务编号， 产品图号，任务图号
	//4.1   插入产品信息
	//4.2   插入产品系列信息
	//4.3   插入任务信息
	//4.3.1 插入任务编号信息
	//4.3.2 插入产品图号信息
	//4.3.3 插入任务图号信息
	//-------------------------------------------------------------------------------
	nTaskCnt = m_nMesBasTaskCnt;
	for (i=0; i<nTaskCnt; i++)
	{
		pCurMesBasTask = &m_MesBasTaskInfo.at(i);

		//4.1 插入产品信息(1)
		//--------------------------------------------------------------------------------------
		memset(pStBasProduct, 0, sizeof(StBasProduct));
		//UINT	nOid;						      								//01.产品代号OID
		strcpy(pStBasProduct->szProductNo, pCurMesBasTask->szProductNo);		//02.产品代号
		strcpy(pStBasProduct->szProductName, pCurMesBasTask->szProductName);	//03.产品名称
		pStBasProduct->nPicNumType = Product_Line;								//05.图号类型:0.无图号(普通产品),1.有图号(线缆)
		pStBasProduct->nGroupOid   = nCurGroupOid;								//06.所在部门OID
		strcpy(pStBasProduct->szCreateTime, szCreateTime);						//07.创建时间
		strcpy(pStBasProduct->szCreateUser, szCreateUser);						//08.创建人

		//4.1产品代号
		//--------------------------------------------------------------------------------------
		bProdExist = m_DMng.IsProdExists(nCurGroupOid, pStBasProduct->szProductNo);
		if (bProdExist == 0)  
		{
			ret = m_DMng.AddNewProd(pStBasProduct);
			if (ret != 0)
			{
				AddNewProductToConfig(pStBasProduct);
				str.Format("DB_OPT_插入_产品代号_成功：nOid=%d, nProdPos=%d, Product_no=%s", 
							pCurMesBasTask->nOid, i+1, pCurMesBasTask->szProductNo);
				g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
			}
			else
			{
				str.Format("DB_ERR_插入_产品代号_异常：nOid=%d, nProdPos=%d, Product_no=%s", 
							pCurMesBasTask->nOid, i+1, pCurMesBasTask->szProductNo);
				g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
				AfxMessageBox(str);
				return 0;
			}
		}
		else
		{
			ret = m_DMng.GetProdDataGroupOidProdNo(nCurGroupOid,pStBasProduct->szProductNo, pStBasProduct);
			if (ret != 0)
			{
				str.Format("DB_OPT_插入_产品代号_代号已存在：nOid=%d, nProdPos=%d, Product_no=%s", 
							pCurMesBasTask->nOid, i+1, pCurMesBasTask->szProductNo);
				g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
			}
			else
			{
				str.Format("DB_ERR_插入_产品代号_读取异常：nOid=%d, nProdPos=%d, Product_no=%s", 
							pCurMesBasTask->nOid, i+1, pCurMesBasTask->szProductNo);
				g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
				AfxMessageBox(str);
				return 0;
			}

		}

		

		//4.2 插入任务信息
		//--------------------------------------------------------------------------------------
		pStBaseTask->Release();

		//ztedit for 2017-03-23
		//strTmpTaskName.Format("%s_%d", pStBasSeries->szProductNo, pCurMesBasTask->nOid);
		strTmpTaskName.Format("%s_%d", pCurMesBasTask->szProductNo, pCurMesBasTask->nOid);
	
		//UINT	nOid;						      							//01.任务OID
		strcpy(pStBaseTask->stTaskBaseInfo.szTaskName, strTmpTaskName);					//02.任务名称
		strcpy(pStBaseTask->stTaskBaseInfo.szProjectNo,	pCurMesBasTask->szProjectNo);	//03.检验单号
		//UINT	nTaskStatus;												//04.任务状态
		//UINT	nTaskType;	      											//05.任务类型
		strcpy(pStBaseTask->stTaskBaseInfo.szModel,		pCurMesBasTask->szModel);		//06.型号
		strcpy(pStBaseTask->stTaskBaseInfo.szPhase,		pCurMesBasTask->szPhase);		//07.阶段
		pStBaseTask->stProductInfo.nOid =	pStBasProduct->nOid;					//08.产品OID
		strcpy(pStBaseTask->stProductInfo.szProductName,	pCurMesBasTask->szProductName);	//09.产品名称
		strcpy(pStBaseTask->stProductInfo.szProductNo,	pCurMesBasTask->szProductNo);	//10.产品代号
		

		//ztedit for 2017-03-23
		pStBaseTask->stTaskBaseInfo.nSeriesOid = 0;
		strcpy(pStBaseTask->stTaskBaseInfo.szSeriesName, "");
		//pStBaseTask->stTaskBaseInfo.nSeriesOid = pStBasSeries->nOid;						//11.产品系列号OID
		//strcpy(pStBaseTask->stTaskBaseInfo.szSeriesName, pStBasSeries->szSeriesName);		//12.产品系列号名称
		
		//char    szProductCode[DB_USER_LEN];								//13.产品编号
		//int  	nCodeNumber;												//14.数量
		//char    szBatch[DB_USER_LEN];		       							//15.批次号
		pStBaseTask->stTaskBaseInfo.nGroupOid = nCurGroupOid;								//16.交检部门
		//char    szGroupName[DB_USER_LEN];									//16_1 交检部门名称
		//char    szUpUser[DB_USER_LEN];									//17.交检人
		//char    szUpDate[DB_USER_LEN];		    						//18.交检日期
		//char    szSendDate[DB_USER_LEN];									//19.下发日期
		//char    szCheckLeader[DB_USER_LEN];								//20.检验组长
		//char    szCheckUser[DB_USER_LEN];									//21.检验员姓名
		//char    szTechUser[DB_USER_LEN];									//22.工艺员 
		//int  	nArmyTest;													//23.军检
		pStBaseTask->stTaskBaseInfo.nDianShiNum = pCurMesBasTask->nDianShiNum;				//24.典试数量
		//char    szAccording1[DB_BACK_LEN];			//25.验收依据1
		//char    szAccording2[DB_BACK_LEN];			//26.验收依据2
		//char    szAccording3[DB_BACK_LEN];			//27.验收依据3
		//char    szAccording4[DB_BACK_LEN];			//28.验收依据4
		//char    szAccording5[DB_BACK_LEN];			//29.验收依据5
		//char    szTaskRemark[DB_BACK_LEN];			//30.备注
		//char    szPlanBegTime[DB_USER_LEN];			//31.计划开始时间
		//char    szPlanEndTime[DB_USER_LEN];			//32.计划结束时间
		//char    szRealBegTime[DB_USER_LEN];			//33.实际开始时间
		//char    szRealEndTime[DB_USER_LEN];			//34.实际结束时间

		//4.2 插入任务信息
		//--------------------------------------------------------------------------------------

		bTaskExist = m_DMng.IsProductTaskExists(pStBasProduct->nOid, strTmpTaskName.GetBuffer(0));
		if (bTaskExist == 0)
		{
			ret = m_DMng.AddNewTask(pStBaseTask);
			if (ret != 0)
			{
				str.Format("DB_OPT_插入_任务_成功：nOid=%d, nTaskPos=%d, Product_no=%s, Project_name=%s, nCodeCnt=%d, nPicNumCnt=%d",
					pCurMesBasTask->nOid, i+1, pCurMesBasTask->szProductNo, pCurMesBasTask->szProjectNo, pCurMesBasTask->nCodeCnt, pCurMesBasTask->nPicNumCnt);
				g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
			}
			else
			{
				str.Format("DB_ERR_插入_任务_异常：nOid=%d, nTaskPos=%d, Product_no=%s, Project_name=%s, nCodeCnt=%d, nPicNumCnt=%d",
					pCurMesBasTask->nOid, i+1, pCurMesBasTask->szProductNo, pCurMesBasTask->szProjectNo, pCurMesBasTask->nCodeCnt, pCurMesBasTask->nPicNumCnt);
				g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
				AfxMessageBox(str);
				return 0;
			}

			//4.3.1 插入任务编号信息
			//--------------------------------------------------------------------------------------
			for (j=0; j<pCurMesBasTask->nCodeCnt; j++)
			{
				memset(pStBasTaskCode, 0, sizeof(StBasTaskCode));

				//UINT nOid;															//01.任务编号OID
				pStBasTaskCode->nTaskOid = pStBaseTask->stTaskBaseInfo.nOid;							//02.任务OID
				pStBasTaskCode->nCodeIndex = j+1;										//03.任务内编号顺序从1开始
				pStBasTaskCode->nDianshiTest = 0;										//04.是否典试
				strcpy(pStBasTaskCode->szCodeName, pCurMesBasTask->szCodeNameArray[j]);	//05.编号名称

				ret = m_DMng.AddNewTaskCode(pStBasTaskCode);
				if (ret != 0)
				{
					str.Format("DB_OPT_插入_任务编号_成功：nOid=%d, nTaskPos=%d, Product_no=%s, nCodeIndex=%d, szCodeName=%s",
						pCurMesBasTask->nOid, i+1, pCurMesBasTask->szProductNo, pStBasTaskCode->nCodeIndex, pStBasTaskCode->szCodeName);
					g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
				}
				else
				{
					str.Format("DB_ERR_插入_任务编号_异常：nOid=%d, nTaskPos=%d, Product_no=%s, nCodeIndex=%d, szCodeName=%s",
						pCurMesBasTask->nOid, i+1, pCurMesBasTask->szProductNo, pStBasTaskCode->nCodeIndex, pStBasTaskCode->szCodeName);
					g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
					AfxMessageBox(str);
					return 0;
				}
			}

			//4.3.2 插入产品图号 + 任务图号
			//--------------------------------------------------------------------------------------
			for (j=0; j<pCurMesBasTask->nPicNumCnt; j++)
			{
				//4.3.2 插入产品图号代号
				//--------------------------------------------------------------------------------------
				memset(pStBasPicNum, 0, sizeof(StBasPicNum));
				ret = m_DMng.GetProdPicNumData(pStBasProduct->nOid, pCurMesBasTask->szPicNoArray[j], pStBasPicNum);//判断此产品图号是否存在
				if (ret == 0)
				{
					memset(pStBasPicNum, 0, sizeof(StBasPicNum));

					//插入产品图号代号
					//UINT	nOid;						      								//01.产品图号OID
					strcpy(pStBasPicNum->szPicNumNo,	pCurMesBasTask->szPicNoArray[j]);	//02.图号代号
					strcpy(pStBasPicNum->szPicNumName,	pCurMesBasTask->szPicNameArray[j]);	//03.图号名称
					pStBasPicNum->nProductOid = pStBasProduct->nOid;						//04.产品OID
					strcpy(pStBasPicNum->szProductNo, pStBasProduct->szProductNo);			//05.产品代号
					strcpy(pStBasPicNum->szCreateTime, szCreateTime);						//06.创建时间
					strcpy(pStBasPicNum->szCreateUser, szCreateUser);						//07.创建人

					//添加产品图号
					ret = m_DMng.AddNewPicNum(pStBasPicNum);
					if (ret != 0)
					{
						str.Format("DB_OPT_插入_产品图号_成功：nOid=%d, nTaskPos=%d, Product_no=%s, PicNo=%s, PicName = %s",
							pCurMesBasTask->nOid, i+1, pCurMesBasTask->szProductNo,pCurMesBasTask->szPicNoArray[j], pCurMesBasTask->szPicNameArray[j]);
						g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
					}
					else
					{
						str.Format("DB_ERR_插入_产品图号_异常：nOid=%d, nTaskPos=%d, Product_no=%s, PicNo=%s, PicName = %s",
							pCurMesBasTask->nOid, i+1, pCurMesBasTask->szProductNo,pCurMesBasTask->szPicNoArray[j], pCurMesBasTask->szPicNameArray[j]);
						g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
						AfxMessageBox(str);
						return 0;
					}

				}

				//4.3.3 插入任务图号
				//-----------------------------------------------------
				memset(pStBasTaskPicNum, 0, sizeof(StBasTaskPicNum));

				//UINT nOid;																//01.任务编号表OID
				pStBasTaskPicNum->nTaskOid = pStBaseTask->stTaskBaseInfo.nOid;								//02.任务OID
				pStBasTaskPicNum->nPicNumIndex = j+1;										//03.任务内模板顺序从1开始
				pStBasTaskPicNum->nPicNumOid = pStBasPicNum->nOid;							//04.图号Oid
				strcpy(pStBasTaskPicNum->szPicNumNo,	pCurMesBasTask->szPicNoArray[j]);   //05.图号代号
				strcpy(pStBasTaskPicNum->szPicNumName,	pCurMesBasTask->szPicNameArray[j]);	//06.图号名称


				//添加任务图号
				ret = m_DMng.AddNewTaskPicNum(pStBasTaskPicNum);
				if (ret != 0)
				{
					str.Format("DB_OPT_插入_任务图号_成功：nOid=%d, nTaskPos=%d, Product_no=%s, PicNo=%s, PicName = %s",
						pCurMesBasTask->nOid, i+1, pCurMesBasTask->szProductNo,pCurMesBasTask->szPicNoArray[j], pCurMesBasTask->szPicNameArray[j]);
					g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
				}
				else
				{
					str.Format("DB_ERR_插入_任务图号_异常：nOid=%d, nTaskPos=%d, Product_no=%s, PicNo=%s, PicName = %s",
						pCurMesBasTask->nOid, i+1, pCurMesBasTask->szProductNo,pCurMesBasTask->szPicNoArray[j], pCurMesBasTask->szPicNameArray[j]);
					g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
					AfxMessageBox(str);
					return 0;
				}
			}


		}


	}//endif for (i=0; i<nTaskCnt; i++)

		
		

	tick2 = GetTickCount()-tick1;

	str.Format("任务个数=%d", nProdPos);
	AfxMessageBox(str);

	m_MesBasTaskInfo.clear();
	m_nMesBasTaskCnt = 0;

	return 1;
}

