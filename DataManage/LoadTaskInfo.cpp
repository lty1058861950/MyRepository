// LoadTaskInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "LoadTaskInfo.h"


// CLoadTaskInfo 对话框

IMPLEMENT_DYNAMIC(CLoadTaskInfo, CDialog)

CLoadTaskInfo::CLoadTaskInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CLoadTaskInfo::IDD, pParent)
{
	MaxCol = 35;


	m_ErrorText = "先选择一个Excel文件";
}

CLoadTaskInfo::~CLoadTaskInfo()
{
	//AfxMessageBox(_T("析构函数"));

	m_ExcelOptFun.DeleteItemInfo();
	
}

void CLoadTaskInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LOADTASKINFO_LIST, m_TaskList);
	DDX_Control(pDX, IDC_LOADTASKINFO_NEWPRODLIST, m_NewProdList);
	DDX_Control(pDX, IDC_LOADTASKINFO_NEWDEPART_LIST, m_NewDepart);
}


BEGIN_MESSAGE_MAP(CLoadTaskInfo, CDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_LOADTASK_OPENFILE_BTN, &CLoadTaskInfo::OnBnClickedLoadtaskOpenfileBtn)
	ON_BN_CLICKED(IDC_LOADTASK_ERROR_BTN, &CLoadTaskInfo::OnBnClickedLoadtaskErrorBtn)
	ON_BN_CLICKED(IDOK, &CLoadTaskInfo::OnBnClickedOk)
END_MESSAGE_MAP()


// CLoadTaskInfo 消息处理程序

BOOL CLoadTaskInfo::OnInitDialog()
{
	CDialog::OnInitDialog();


	//数据库共有28个字段 字段顺序为://任务ID号(1)';检验单号(2)';'状态(3)';'交检部门(4)';'产品名称(5)';
									//'产品代号(6)';'产品编号(7)'数量(8)';'批次号(9)'; '产品型号(10)';
									///'产品阶段(11)';'交检人(12)'; '交检日期(13)';'检验员姓名(14)'; '检验组长(15)';
									//'工艺员(16)';'军检(17)';'典试数量(18)';'验收依据1(19)'; '验收依据2(20)';
									//'验收依据3(21)';'验收依据4(22)';'验收依据5(23)'; '备注(24)';'计划开始时间(25)'
									//;'计划结束时间(26)';'实际开始时间(27)';'实际结束时间(28)';


	//下面共有35个字段 只有21个字段是有效值 分别是:"所属型号(10)","课题编号任务号(2)","产品名称(5)","产品代号(6)","数量(8)",
										//"产品编号(7)","产品阶段(11)","军检(17)","典试数量(18)","检验组长(15)",//
										//"检验员姓名(14)","交检部门(4)","工艺员(16)","验收依据1(19)","验收依据2(20)",//
										//"验收依据3(21)","验收依据4(22)","验收依据5(23)","交检人(12)","交检人日期(13)","备注(24)"///
	///( 10, 2, 5, 6, 8,    7, 11, 17, 18, 15,    14, 4, 16, 19, 20,   21, 22, 23, 12, 13,   24)




	//数据库中还有7个字段是另外生成的 分别是://"任务ID号(1)","状态(3)","批次号(9)"'计划开始时间(25)'/;'计划结束时间(26)'
											//;'实际开始时间(27)';'实际结束时间(28)';

	
	



	//(2, 3, 4, 5, 6,   7, 8, 9, 10, 11,   12, 13, 14, 16, 17,    18, 19, 20, 21, 22, 34)//这些是有效列
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
	m_TaskList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_GRIDLINES);

	for(int i = 0;i<MaxCol;i++)
	{
		m_TaskList.InsertColumn(i, ColName[i],LVCFMT_CENTER, ColWidth[i]);
	}
	m_TaskList.EnableRClickMenu(FALSE);
	
	char *ColName1[] = {"序号","产品名称","产品代号"};
	int  ColWidth1[] = {50,100,100};
	m_NewProdList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_GRIDLINES);

	for(int i = 0;i<3;i++)
	{
		m_NewProdList.InsertColumn(i, ColName1[i],LVCFMT_CENTER, ColWidth1[i]);
	}
	m_NewProdList.EnableRClickMenu(FALSE);


	char *ColName2[] = {"序号","部门名称","部门编号"};
	int  ColWidth2[] = {50,100,100};
	m_NewDepart.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_GRIDLINES);

	for(int i = 0;i<3;i++)
	{
		m_NewDepart.InsertColumn(i, ColName2[i],LVCFMT_CENTER, ColWidth2[i]);
	}
	m_NewDepart.EnableRClickMenu(FALSE);
	/*m_NewDepart.ShowWindow(SW_HIDE);*/

	/*SetListColor(&m_TaskList);
	SetListColor(&m_NewProdList);*/
	m_ExcelOptFun.NewItemInfo();


	//ztadd for LoadTask_2016_12_27
	GetDlgItem(IDC_LOADTASK_STATIC4)->ShowWindow(FALSE);	
	m_NewProdList.ShowWindow(FALSE);
	GetDlgItem(IDC_LOADTASK_STATIC5)->ShowWindow(FALSE);
	m_NewDepart.ShowWindow(FALSE);


	this->MoveWindow(0,0,1224,g_WinHeight);
	this->CenterWindow();
	PostMessage(WM_SIZE);



	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void CLoadTaskInfo::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	AutoSize();
}
void CLoadTaskInfo::AutoSize()
{
	CRect Rect ;
	GetClientRect(&Rect) ;

	int nBtnWidth = 80;
	int nBtnHeight = 30;

	int ProdWid = 280;
	int DepartListWid = 200;

	if (GetDlgItem(IDC_LOADTASK_STATIC2)->GetSafeHwnd())
	{
		GetDlgItem(IDC_LOADTASK_STATIC2)->MoveWindow(6,6,Rect.Width()-12,70);
	}


	if (GetDlgItem(IDC_LOADTASK_STATIC3)->GetSafeHwnd())
	{
		GetDlgItem(IDC_LOADTASK_STATIC3)->MoveWindow(621,31,Rect.Width()-(621+nBtnWidth+20),30);
	}

	if (GetDlgItem(IDC_LOADTASK_ERROR_BTN)->GetSafeHwnd())
	{
		GetDlgItem(IDC_LOADTASK_ERROR_BTN)->MoveWindow(Rect.right-(nBtnWidth+10),26,nBtnWidth,nBtnHeight);
	}


	
	if (m_TaskList.GetSafeHwnd())
	{
		//ztadd for LoadTask_2016_12_27
		m_TaskList.MoveWindow(6,81,Rect.Width()-(12+20),Rect.Height()-(162));
		
		//m_TaskList.MoveWindow(6,81,Rect.Width()-(12+ProdWid+DepartListWid+20),Rect.Height()-(162));
		
	}

	//ztadd for LoadTask_2016_12_27
	/*
	if (GetDlgItem(IDC_LOADTASK_STATIC4)->GetSafeHwnd())
	{
		GetDlgItem(IDC_LOADTASK_STATIC4)->MoveWindow(Rect.right-(ProdWid+DepartListWid+20),81,ProdWid,Rect.Height()-(162));
	}
	if (m_NewProdList.GetSafeHwnd())
	{
		m_NewProdList.MoveWindow(Rect.right-(ProdWid+DepartListWid+10),101,ProdWid-20,Rect.Height()-(162+30));
	}

	if (GetDlgItem(IDC_LOADTASK_STATIC5)->GetSafeHwnd())
	{
		GetDlgItem(IDC_LOADTASK_STATIC5)->MoveWindow(Rect.right-(DepartListWid+10),81,DepartListWid,Rect.Height()-(162));
	}
	if (m_NewDepart.GetSafeHwnd())
	{
		m_NewDepart.MoveWindow(Rect.right-(DepartListWid),101,DepartListWid-20,Rect.Height()-(162+30));
	}
	*/


	if (GetDlgItem(IDOK)->GetSafeHwnd())
	{
		GetDlgItem(IDOK)->MoveWindow(Rect.right-(nBtnWidth+10)*2,Rect.bottom-35,nBtnWidth,nBtnHeight);
	}
	if (GetDlgItem(IDCANCEL)->GetSafeHwnd())
	{
		GetDlgItem(IDCANCEL)->MoveWindow(Rect.right-(nBtnWidth+10),Rect.bottom-35,nBtnWidth,nBtnHeight);
	}
}
void CLoadTaskInfo::OnBnClickedLoadtaskOpenfileBtn()
{
	CFileDialog *lpszOpenFile;    //定义一个CfileDialog对象
	lpszOpenFile = new CFileDialog(TRUE,"","",OFN_FILEMUSTEXIST |OFN_HIDEREADONLY , "文件类型(*.xls;*.xlsx)|*.xls;*.xlsx||");//生成一个对话框
	if(lpszOpenFile->DoModal() == IDOK)//假如点击对话框确定按钮
	{
		CString	szGetName;
		szGetName = lpszOpenFile->GetPathName();	//得到打开文件的路径
		GetDlgItem(IDC_LOADTASK_XLSFILE_EDT)->SetWindowText(szGetName);

		m_ExcelOptFun.ClearParamInfo();
		m_ExcelOptFun.ReadExcelFile(szGetName);

		m_ErrorText = _T("");

		GetDlgItem(IDC_LOADTASK_STATIC3)->SetWindowText("任务提示:");

		InitLoadTasksList();//初始化List//

	}

	delete lpszOpenFile;	//释放分配的对话框
}
BOOL CLoadTaskInfo::InitLoadTasksList()
{
	int nRow = m_ExcelOptFun.m_row;
	int nCol = m_ExcelOptFun.m_col;

	
	m_TaskList.DeleteAllItems();
	
	CString strText;
	for(int i = 0;i<nRow-1;i++)
	{
		strText.Format(_T("%d"),i+1);
		m_TaskList.InsertItem(i,strText);
	}
	int index;
	int k = 1;
	BOOL nColB = FALSE;
	strText.Format(_T("检测到不合法的列名称:\n"));
	for(int j = 0;j<nCol;j++)
	{
		if(!strcmp("",m_ExcelOptFun.m_ItemInfo[0][j]))
		{
			//字段值为空  则忽略///
			CString strText1;
			strText1.Format("第 %d 列 字段名称 为空已忽略",j+1);
			
			continue;
		}
		index = 0;
		index = CheckFiledName(m_ExcelOptFun.m_ItemInfo[0][j]);
		if(!index)
		{
			//返回 0 表示 不是合法字段 给出提示//
			nColB = TRUE;
			CString strError;
			strError.Format(_T("%d.在Excel文件第 %d 列 内容是: \"%s\"\n"),k++,j+1,m_ExcelOptFun.m_ItemInfo[0][j]);
			strText+=strError;
		}else
		{
			//有效字段 应返回插入List的列下标//
			//不在乎Excel字段的顺序///
			for(int i = 0;i<nRow-1;i++)
			{
				m_TaskList.SetItemText(i,index,m_ExcelOptFun.m_ItemInfo[i+1][j]);
			}
		}
		
	}

	if(nColB)
	{
		m_ErrorText+=("\n\n"+strText);
		AfxMessageBox(strText);
	}
	return TRUE;

}
int CLoadTaskInfo::CheckFiledName(char *strText)
{
	int nRow = m_ExcelOptFun.m_row;
	int nCol = m_ExcelOptFun.m_col;

	char *ColName[] = {"序号","锁状态","所属型号","课题编号任务号","产品名称",
		"产品代号","数量","产品编号","产品阶段","军检",
		"典试数量","检验组长","检验员姓名","交检部门","工艺员",
		"工序检验","验收依据1","验收依据2","验收依据3","验收依据4",
		"验收依据5","交检人","交检人日期","工序检验意见","工序检验签名",
		"工序检验日期","产品工艺","产品工艺日期","交检部门领导意见","交检部门领导签名",
		"交检部门领导签字日期","检验员意见","检验员签名","检验员日期","备注"};

	for(int j = 1;j<MaxCol;j++)
	{
		if(!strcmp(strText,ColName[j]))
		{
			//返回值不是0 证明是有效字段///
			//找到有效字段 返回所对应的List列下标///
			return j;
		}
	}
	return 0;
}
BOOL CLoadTaskInfo::DestroyWindow()
{
	
//AfxMessageBox(_T("DestroyWindow()"));
	return CDialog::DestroyWindow();
}


void CLoadTaskInfo::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	CDialog::OnOK();
}

void CLoadTaskInfo::OnBnClickedLoadtaskErrorBtn()
{
	AfxMessageBox(m_ErrorText);
}

void CLoadTaskInfo::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//OnOK();

	//ztadd for 
	LoadXlsTaskInfo( );					//从Excel导入测试任务信息

}


int CLoadTaskInfo::GetProductNoFromSrcProductNo(char *szSrcProductNo, char *szProductNo, char *szProductSeries)
{
	int		splictPos = 0,splictPos1, splictPos2;
	int     nPos1, nPos2, nSeriesPos;
	int     nLen, nLen1, nLen2, nSumLen, nTmpLen;
	int     bFindFlag1, bFindFlag2, bHaveSeries;
	CString str, str1, str2, strTmp;
	CString strProductAll, strProductNo, strProductSeries;
	char    szBuf[100] ={0,};
	//char    szBuf2[100] = "\r\n";

	str = szSrcProductNo;
	nLen = strlen(str.GetBuffer(0));

	strcpy(szBuf, str.GetBuffer(0));


	if (nLen <= 1)
	{
		return 0;
	}

	splictPos = str.Find(SPLICT_CHAR_HUANG_HANG);  //换行
	if (splictPos != -1)
	{
		return 0;
	}

	splictPos = str.Find(SPLICT_CHAR_HONG_DAI_HUAN);
	if (splictPos != -1)
	{
		str = str.Left(splictPos);
	}

	nLen = strlen(str.GetBuffer(0));
	//产品代号_数据处理
	splictPos = str.Find(SPLICT_CHAR_XIE_GANG);  //字符：'/'
	if (splictPos != -1)
	{
		str1 = str.Left(splictPos);
		str2 = str.Right(nLen-splictPos-1);

		bFindFlag1 = 0;
		nLen1 = strlen(str1.GetBuffer(0));
		nPos1 = str1.Find(SPLICT_CHAR_HENG_GANG);	 //字符：'-'
		if (nPos1 != -1)
		{
			bFindFlag1 = 1;
		}

		bFindFlag2 = 0;
		nLen2 = strlen(str2.GetBuffer(0));
		nPos2 = str2.Find('-');
		if (nPos2 != -1)
		{
			bFindFlag2 = 1;
		}

		if ((bFindFlag1 != 0) && (bFindFlag2 != 0))
		{
			strProductAll = str1;
		}
		else if (bFindFlag1 != 0)
		{
			strProductAll = str1;
		}
		else if (bFindFlag2 != 0)
		{
			strProductAll = str2;
		}
		else
		{
			strProductAll = str;
		}
	}
	else
	{
		strProductAll = str;
	}

	
	splictPos1 = -1;
	splictPos2 = -1;
	strTmp = strProductAll;
	nTmpLen = strTmp.GetLength();

	bHaveSeries = 0;
	nSeriesPos  = 0;

	splictPos1 = strTmp.Find(SPLICT_CHAR_HENG_GANG);	 //字符：'-'
	if (splictPos1 != -1)
	{
		strTmp  = strTmp.Right(nTmpLen-splictPos1-1);
		nTmpLen = strTmp.GetLength();
		splictPos2 =  strTmp.Find(SPLICT_CHAR_HENG_GANG);	 //字符：'-'
		if (splictPos2 != -1)
		{
			bHaveSeries = 1;
			nSeriesPos  = splictPos1+1+splictPos2;
		}
	}
	else
	{
		str.Format("非法的产品代号格式:%s", strProductAll);
		AfxMessageBox(str);
		return 0;
	}
	
	if (bHaveSeries != 0)
	{
		strTmp = strProductAll;
		nTmpLen = strTmp.GetLength();
		strProductNo = strTmp.Left(nSeriesPos);
		strProductSeries = strTmp.Right(nTmpLen-nSeriesPos-1);

		strcpy(szProductNo, strProductNo.GetBuffer(0));
		strcpy(szProductSeries,strProductSeries.GetBuffer(0));
	}
	else
	{
		strcpy(szProductNo, strProductAll.GetBuffer(0));
		strcpy(szProductSeries, _T(""));
	}

	return 1;
}

int CLoadTaskInfo::GetStrArrayFormStrList(char *szGrpStr, char splictChar, int nMaxCnt,  int &nCnt, CString strArray[])
{
	CString str, strHead, strErr;
	int		splictPos, nSplictCnt, nLen;
	int     nPos, nArrayPos;

	str = szGrpStr;

	nSplictCnt = 0;

	splictPos = 0; 
	nPos = 0;
	nArrayPos = 0;

	while (nPos != -1)
	{
		nLen = str.GetLength();
		nPos = str.Find(splictChar);
		if (nPos != -1)
		{
			strHead = str.Left(nPos);
			str = str.Right(nLen-nPos-1);
		}
		else
		{
			strHead = str;
		}

		if (strHead.GetLength() > 0)
		{
			if (nArrayPos > nMaxCnt)
			{
				strErr.Format(_T("超出最大值限制! nArrayPos=%d, nMaxCnt"), nArrayPos, nMaxCnt);
				AfxMessageBox(strErr);
				return 0;
			}
			strArray[nArrayPos++] = strHead;
		}
	}

	nCnt = nArrayPos;

	return 1;
}


int CLoadTaskInfo::GetProductCodeFromSrcCodeList(int nCodeCnt, char *szSrcCodeList)					//获取产品编号列表
{
	CString str, strCodeList, strErr;
	int     i, j, k, ret;
	int     nGrpCnt, nDuanCnt, nItemCnt; 
	int     splictPos;
	CString strGrpArray[XLS_LOAD_MAX_GRP_CNT];
	CString strDuanArray[XLS_LOAD_MAX_DUAN_CNT];
	CString strItemArray[XLS_LOAD_MAX_ITEM_CNT];

	CString strCurGrp, strCurDuan;
	CString strDuanHead, strItemBeg, strItemEnd, strItemHead;
	int     nBegPos, nEndPos, nCodePos;	
	int     num = 0, nDuanLen, nItemLen,nItemLen1;
	int     nItemVal;
	int     bSpecJingHao = 0;

	str = szSrcCodeList;

	//1.
	num = 0;
	num = str.Replace(SPEC_STR_BO_LAN_XIAN_1, SPEC_STR_BO_LAN_XIAN_2);
	//2.
	num = 0;
	num = str.Replace(SPEC_STR_DOU_HAO_1, SPEC_STR_DOU_HAO_2);
	//3.
	num = 0;
	num = str.Replace(SPEC_STR_FEN_HAO_1, SPEC_STR_FEN_HAO_2);
	//4.
	num = 0;
	num = str.Replace(SPEC_STR_SHUANG_GANG_1, SPEC_STR_BO_LAN_XIAN_2);
	//5.
	num = 0;
	num = str.Replace(SPEC_STR_DUN_HAO_1, SPEC_STR_DOU_HAO_2);
	//6.
	num = 0;
	num = str.Replace(SPEC_STR_XIE_GAN_1, SPEC_STR_DOU_HAO_2);
	//7.
	num = 0;
	num = str.Replace(SPEC_STR_JU_HAO_1, SPEC_STR_DOU_HAO_2);


	if (nCodeCnt >= MAX_PIC_NUM_CNT)
	{
		strErr.Format("编号个数错误: nCodePos=%d, nMax=%d, 超出最大值限制!", nCodePos, MAX_PIC_NUM_CNT);
		AfxMessageBox(strErr);
		return 0;
	}

	bSpecJingHao = 0;
	if (str.Find(SPLICT_CHAR_JING_HAO) != -1)
	{
		num = 0;
		num = str.Replace(SPEC_STR_JING_HAO, SPEC_STR_NULL);
		bSpecJingHao = 1;
	}

	strCodeList = str;

	if (nCodeCnt == 1)
	{
		m_nCodeCnt = nCodeCnt;
		strcpy(m_szCodeNameArray[0], szSrcCodeList);
		return 1;
	}

	nDuanLen = 0;
	nCodePos = 0;

	//1.获取组个数
	nGrpCnt = 0;
	ret = GetStrArrayFormStrList(strCodeList.GetBuffer(0), SPLICT_CHAR_FEN_HAO, XLS_LOAD_MAX_GRP_CNT, nGrpCnt, strGrpArray);
	if (ret == 0)
	{
		return 0;
	}

	strItemHead = "";

	for (i=0; i<nGrpCnt; i++)
	{
	
		//1.1获取组内段个数
		nDuanCnt = 0;
		ret = GetStrArrayFormStrList(strGrpArray[i].GetBuffer(0), SPLICT_CHAR_DOU_HAO, XLS_LOAD_MAX_DUAN_CNT, nDuanCnt, strDuanArray);
		if (ret == 0)
		{
			return 0;
		}
		for (j=0; j<nDuanCnt; j++)
		{
			nItemCnt = 0;
			
			strCurDuan = strDuanArray[j];
			nDuanLen = strCurDuan.GetLength(); 
			splictPos = strCurDuan.Find(SPLICT_CHAR_BO_LANG_XINA);
			if (splictPos != -1)
			{
				strItemBeg = strCurDuan.Left(splictPos);
				strItemEnd = strCurDuan.Right(nDuanLen-splictPos-1);
				nItemLen = strItemBeg.GetLength();
				
				if (strItemBeg.GetLength() <= 3)
				{
					nBegPos = atoi(strItemBeg.GetBuffer(0));
					nEndPos = atoi(strItemEnd.GetBuffer(0));
					nItemCnt = nEndPos-nBegPos+1;
					for (k=0; k<nItemCnt; k++)
					{
						if (strItemBeg.GetLength() == 3)
						{
							if (bSpecJingHao != 0)
							{
								str.Format("%03d#", nBegPos+k);
							}
							else
							{
								str.Format("%03d", nBegPos+k);
							}
						}
						else
						{
							if (bSpecJingHao != 0)
							{
								str.Format("%02d#", nBegPos+k);
							}
							else
							{
								str.Format("%02d", nBegPos+k);
							}
						}
						

						if (strItemHead.GetLength() > 0)
						{
							str = strItemHead + str;
						}

						if (nCodePos >= MAX_PIC_NUM_CNT)
						{
							strErr.Format("编号个数错误: nCodePos=%d, nMax=%d, 超出最大值限制!", nCodePos, MAX_PIC_NUM_CNT);
							AfxMessageBox(strErr);
							return 0;
						}
						strcpy(m_szCodeNameArray[nCodePos], str.GetBuffer(0));
						nCodePos++;
					}
				}
				else
				{
					strItemHead = strItemBeg.Left(nItemLen-3);   

					nBegPos = atoi(strItemBeg.Right(3));
					nEndPos = atoi(strItemEnd.Right(3));	
					nItemCnt = nEndPos-nBegPos+1;
					for (k=0; k<nItemCnt; k++)
					{
						if (bSpecJingHao != 0)
						{
							str.Format("%s%03d#", strItemHead, nBegPos+k);
						}
						else
						{
							str.Format("%s%03d", strItemHead, nBegPos+k);
						}

						if (nCodePos >= MAX_PIC_NUM_CNT)
						{
							strErr.Format("编号个数错误: nCodePos=%d, nMax=%d, 超出最大值限制!", nCodePos, MAX_PIC_NUM_CNT);
							AfxMessageBox(strErr);
							return 0;
						}
						strcpy(m_szCodeNameArray[nCodePos], str.GetBuffer(0));
						nCodePos++;
					}
				}
			
			

			}
			else
			{
				strItemBeg = strCurDuan;
				if (j == 0)
				{
					nItemLen = strItemBeg.GetLength();
					if (strItemBeg.GetLength() > 3)
					{
						strItemHead = strItemBeg.Left(nItemLen-3);
					}
					nItemLen1 = nItemLen;
				}
				
				
				if (strItemBeg.GetLength() != nItemLen1)
				{
					nItemVal = atoi(strCurDuan.Right(3));
					str.Format("%s%03d", strItemHead, nItemVal);
				}
				else
				{
					str = strItemBeg;
				}

				if (bSpecJingHao != 0)
				{
					str = str + SPEC_STR_JING_HAO;
				}

				if (nCodePos >= MAX_PIC_NUM_CNT)
				{
					strErr.Format("编号个数错误: nCodePos=%d, nMax=%d, 超出最大值限制!", nCodePos, MAX_PIC_NUM_CNT);
					AfxMessageBox(strErr);
					return 0;
				}
				strcpy(m_szCodeNameArray[nCodePos], str.GetBuffer(0));
				nCodePos++;
			}
		}

	}

	
	if (nCodeCnt != nCodePos)
	{
		str.Format("Error, 编号个数错误, 原始个数=%d, 编号描述＝%s, 检测个数=%d", nCodeCnt, szSrcCodeList, nCodePos);
		AfxMessageBox(str);
		return 0;
	}

	m_nCodeCnt = nCodePos;

	return 1;
}

void CLoadTaskInfo::ClearCodeNameInfo( )
{
	int i;
	m_nCodeCnt = 0;
	for (i=0; i<MAX_PIC_NUM_CNT; i++)
	{
		memset(m_szCodeNameArray[i], 0, MAX_PIC_NAME_LEN);
	}
}

int  CLoadTaskInfo::GetArmyTestValue(char *szArmyTest)
{
	CString str;
	int     nType = 0;

	str = str.TrimLeft();
	str = str.TrimRight();
	if (strcmp(str.GetBuffer(0), _T("是")) == 0)
	{
		nType = 1;
	}
	else
	{
		nType = 0;
	}
	return nType;
}

int CLoadTaskInfo::LoadXlsTaskInfo( )					//从Excel导入测试任务信息
{
	CListCtrl *pList = &m_TaskList;

	CString   str, strSum;
	CString   strProductNo, strProductCode, strPicNo, strPicName;
	CString   strProjectNo, strProductName, strModelNo, strPhase, strDianShiQty;
	CString   strSumCode, strSumPicNo, strSumPicName;
	CString   strTmpTaskName;
	int       nCodeCnt, nPicNoCnt;
	StBasProduct	stBasProduct, *pStBasProduct;		//产品信息
	//StBasSeries		stBasSeries,  *pStBasSeries;        //产品系列信息
	StBasPicNum     stBasPicNum,  *pStBasPicNum;        //产品图号信息
	StBasTask		stBasTask,	  *pStBaseTask;			//任务信息
	StBasTaskBaseInfo *pStBasTaskBaseInfo;
	StBasTaskCode	stBasTaskCode, *pStBasTaskCode;		//任务编号信息
	StBasTaskPicNum stBasTaskPicNum, *pStBasTaskPicNum;	//任务图号信息

	int       nTaskOid, nTaskCnt, nTaskPos;
	int		  i,j, nProdPos, nCnt;

	int       nCurGroupOid = 1;							//部门OID
	char     szCreateTime[DB_USER_LEN] = {0,};			//创建时间
	char     szCreateUser[DB_USER_LEN] ={0,};			//创建人
	
	char     szProductNo[DB_NAME_LEN] = {0,};
	char     szProductSeries[DB_NAME_LEN] ={0,};

	int      bProdExist = 0, bExist,bTaskExist, bTaskCodeExist, bTaskPicExist, ret;
	int      tick1,tick2;
	tick1 = GetTickCount();

	XlsBasTask  xlsBasTask, *pXlsBasTask, *pCurXlsBasTask;
	CString  strArray[35];
	CString  strSrcProductNo, strSrcProductCode;
	int      nCodeNumber = 0;
	int      bErrFlag = 0;


	pXlsBasTask = &xlsBasTask;

	//部门OID
	nCurGroupOid = g_CurSelDepart.nOid;   //注意：需全局变量初始化, 部门OID

	//部门名称
	GetSysDateTime(szCreateTime);



	char *ColName[] = {"序号","锁状态","所属型号","课题编号任务号","产品名称",
		"产品代号","数量","产品编号","产品阶段","军检",
		"典试数量","检验组长","检验员姓名","交检部门","工艺员",
		"工序检验","验收依据1","验收依据2","验收依据3","验收依据4",
		"验收依据5","交检人","交检人日期","工序检验意见","工序检验签名",
		"工序检验日期","产品工艺","产品工艺日期","交检部门领导意见","交检部门领导签名",
		"交检部门领导签字日期","检验员意见","检验员签名","检验员日期","备注"};


    /*
	nProdPos  = 0;	//产品个数
	nTaskPos  = 0;   //任务个数
	nCodeCnt  = 0;	//编号个数
	nPicNoCnt = 0;  //图号个数
	strSumCode	  = "";
	strSumPicNo   = "";
	strSumPicName = "";
	*/

	pStBasProduct = &stBasProduct;		//产品信息
	//pStBasSeries  = &stBasSeries;		//产品系列信息 
	pStBasPicNum  = &stBasPicNum;		//产品图号信息
	pStBaseTask	  = &stBasTask;			//任务信息
	pStBasTaskBaseInfo = &pStBaseTask->stTaskBaseInfo; //任务的基本信息///
	pStBasTaskCode= &stBasTaskCode;		//任务编号信息
	pStBasTaskPicNum = &stBasTaskPicNum;	//任务图号信息


	//1.获取测试任务基础信息
	//-------------------------------------------------------------------------------
	m_XlsBasTaskInfo.clear();
	m_nXlsBasTaskCnt = 0;

	nCnt = pList->GetItemCount();

	nTaskPos = 0;
	for (i=0; i<nCnt; i++)
	{
		str = pList->GetItemText(i, 1);

		for (j=0; j<MaxCol; j++)
		{
			strArray[j] = _T("");
			strArray[j] = pList->GetItemText(i, j);
		}

		//记录产品信息
		memset( (char*)pXlsBasTask, 0, sizeof(XlsBasTask));

		strSrcProductNo   = strArray[5];   //产品代号+系列号
		strSrcProductCode = strArray[7];   //产品编号

		nCodeNumber = atoi(strArray[6].GetBuffer(0)); //产品编号_数量

		//1.1获取产品代号
		memset(szProductNo,		0, DB_NAME_LEN);
		memset(szProductSeries, 0, DB_NAME_LEN);

		if (i == 23)
		{
			i = i;
		}

		ret = GetProductNoFromSrcProductNo(strSrcProductNo.GetBuffer(0), szProductNo, szProductSeries);	//获取产品代号，系列号
		if (ret == 0)
		{
			continue;
		}

		//产品代号处理
		str.Format("产品代号：nTaskPos=%02d, Product_no=%s, 产品代号=%s, 产品系列号=%s",
			i+1, strSrcProductNo, szProductNo, szProductSeries);
		g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);


		//1.2获取产品编号列表
		ClearCodeNameInfo( );
		ret = GetProductCodeFromSrcCodeList(nCodeNumber, strSrcProductCode.GetBuffer(0));
		if (ret != 0)
		{
			//对变量赋值: pXlsBasTask 
			strSum = _T("");
			for (j=0; j<m_nCodeCnt; j++)
			{
				strcpy(pXlsBasTask->szCodeNameArray[j], m_szCodeNameArray[j]);

				if (j == 0)
				{
					str.Format( _T("%s"), m_szCodeNameArray[j]);
				}
				else
				{
					str.Format( _T(",%s"), m_szCodeNameArray[j]);
				}
				strSum = strSum + str;		
			}

			pXlsBasTask->nCodeCnt = m_nCodeCnt;

			//1.
			str.Format("产品代号：nTaskPos=%02d, Product_no=%s, nCodeNumber=%d,nCodeCnt=%d",
				i+1, strSrcProductNo, nCodeNumber, m_nCodeCnt);
			g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
			//2.
			str.Format("原始编号: 编号个数=%d, 编号描述=%s", nCodeNumber, strSrcProductCode);
			g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
			//3.
			str.Format("结果编号: 编号个数=%d, 编号列表=%s", m_nCodeCnt, strSum);
			g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
		}
		else
		{
			bErrFlag = 1;
			break;
		}

		//------------------------------------------------------------------------------

		//UINT	nOid;						      							//01.任务OID
		//strcpy(pXlsBasTask->szTaskName,	strArray[3].GetBuffer(0));		//02.任务名称   [3]
		strcpy(pXlsBasTask->szProjectNo,	strArray[3].GetBuffer(0));		//03.检验单号
		//UINT	nTaskStatus;						//04.任务状态
		//UINT	nTaskType;	      	                //05.任务类型
		strcpy(pXlsBasTask->szModel,		strArray[8].GetBuffer(0));		//06.型号
		strcpy(pXlsBasTask->szPhase,		strArray[2].GetBuffer(0));		//07.阶段
		//UINT	nProductOid;	      	            //08.产品OID
	
		strcpy(pXlsBasTask->szProductName,	strArray[4].GetBuffer(0));	    //09.产品名称
	
		strcpy(pXlsBasTask->szProductNo,	szProductNo);					//10.产品代号

		//ztedit for 2017-03-23
		pStBaseTask->stTaskBaseInfo.nSeriesOid = 0;						
		strcpy(pStBaseTask->stTaskBaseInfo.szSeriesName,	"");
		//pXlsBasTask->nSeriesOid;											//11.产品系列号OID
		//strcpy(pXlsBasTask->szSeriesName,	szProductSeries);				//12.产品系列号名称


		//pXlsBasTask->szProductCode[DB_NAME_LEN];							//13.产品编号
		pXlsBasTask->nCodeNumber = nCodeNumber;								//14.数量
		//pXlsBasTask->szBatch[DB_NAME_LEN];		    //15.批次号
		//UINT    nGroupOid;		                	//16.交检部门
		strcpy(pXlsBasTask->szGroupName,	strArray[13].GetBuffer(0));		//16_1 交检部门名称
		strcpy(pXlsBasTask->szUpUser,		strArray[21].GetBuffer(0));		//17.交检人
		//strcpy(pXlsBasTask->szUpDate,		strArray[22].GetBuffer(0));		//18.交检日期
		//char    szSendDate[DB_USER_LEN];			//19.下发日期
		strcpy(pXlsBasTask->szCheckLeader,	strArray[11].GetBuffer(0));		//20.检验组长
		strcpy(pXlsBasTask->szCheckUser,	strArray[12].GetBuffer(0));		//21.检验员姓名
		strcpy(pXlsBasTask->szTechUser,		strArray[14].GetBuffer(0));		//22.工艺员 
		pXlsBasTask->nArmyTest=GetArmyTestValue(strArray[9].GetBuffer(0));	//23.军检
		pXlsBasTask->nDianShiNum = atoi(strArray[10].GetBuffer(0));			//24.典试数量
		strcpy(pXlsBasTask->szAccording1,	strArray[16].GetBuffer(0));		//25.验收依据1
		strcpy(pXlsBasTask->szAccording2,	strArray[17].GetBuffer(0));		//26.验收依据2
		strcpy(pXlsBasTask->szAccording3,	strArray[18].GetBuffer(0));		//27.验收依据3
		strcpy(pXlsBasTask->szAccording4,	strArray[19].GetBuffer(0));		//28.验收依据4
		strcpy(pXlsBasTask->szAccording5,	strArray[20].GetBuffer(0));		//29.验收依据5
		strcpy(pXlsBasTask->szTaskRemark,	strArray[34].GetBuffer(0));		//30.备注
		//char    szPlanBegTime[DB_USER_LEN];			//31.计划开始时间
		//char    szPlanEndTime[DB_USER_LEN];			//32.计划结束时间
		//char    szRealBegTime[DB_USER_LEN];			//33.实际开始时间
		//char    szRealEndTime[DB_USER_LEN];			//34.实际结束时间

		m_XlsBasTaskInfo.push_back(xlsBasTask);

		nTaskPos++;		

	}
	m_nXlsBasTaskCnt = nTaskPos;

	
	
	if (bErrFlag != 0)
	{
		str.Format("异常退出，解析任务个数=%d, 当前行号=%d", nTaskPos+1, i+1);
		AfxMessageBox(str);	
		return 0;
	}

	str.Format("任务个数=%d", nTaskPos);
	AfxMessageBox(str);	

	// return 0;



	//4.插入：产品信息, 产品系列信息, 任务信息, 任务编号， 产品图号，任务图号
	//4.1   插入产品信息
	//4.2   插入产品系列信息
	//4.3   插入任务信息
	//4.3.1 插入任务编号信息
	//4.3.2 插入产品图号信息
	//4.3.3 插入任务图号信息
	//-------------------------------------------------------------------------------
	nTaskCnt = m_nXlsBasTaskCnt;
	for (i=0; i<nTaskCnt; i++)
	{
		pCurXlsBasTask = &m_XlsBasTaskInfo.at(i);

		//4.1 插入产品信息(1)
		//--------------------------------------------------------------------------------------
		memset(pStBasProduct, 0, sizeof(StBasProduct));
		//UINT	nOid;						      								//01.产品代号OID
		strcpy(pStBasProduct->szProductNo, pCurXlsBasTask->szProductNo);		//02.产品代号
		strcpy(pStBasProduct->szProductName, pCurXlsBasTask->szProductName);	//03.产品名称
		pStBasProduct->nPicNumType = Product_normal;							//05.图号类型:0.无图号(普通产品),1.有图号(线缆)
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
				str.Format("DB_OPT_插入_产品代号_成功：nProdPos=%d, Product_no=%s", 
					i+1, pCurXlsBasTask->szProductNo);
				g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
			}
			else
			{
				str.Format("DB_ERR_插入_产品代号_异常：nProdPos=%d, Product_no=%s", 
					i+1, pCurXlsBasTask->szProductNo);
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
				str.Format("DB_OPT_插入_产品代号_代号已存在：nProdPos=%d, Product_no=%s", 
							 i+1, pCurXlsBasTask->szProductNo);
				g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
			}
			else
			{
				str.Format("DB_ERR_插入_产品代号_读取异常：nProdPos=%d, Product_no=%s", 
						i+1, pCurXlsBasTask->szProductNo);
				g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
				AfxMessageBox(str);
				return 0;
			}
		}

	

		//4.2 插入任务信息
		//--------------------------------------------------------------------------------------
		pStBaseTask->Release();

		//ztedit for 2017-03-23
		/*
		if ( strlen(pStBasSeries->szSeriesName) != 0)
		{
			strTmpTaskName.Format("%s-%s_%s", pStBasSeries->szProductNo, pStBasSeries->szSeriesName, pCurXlsBasTask->szProjectNo);
		}
		else
		{
			strTmpTaskName.Format("%s_%s", pStBasSeries->szProductNo, pCurXlsBasTask->szProjectNo);
		}
		*/
		strTmpTaskName.Format("%s_%s", pCurXlsBasTask->szProductNo, pCurXlsBasTask->szProjectNo);

		
		//UINT	nOid;						      							//01.任务OID
		strcpy(pStBaseTask->stTaskBaseInfo.szTaskName, strTmpTaskName);					//02.任务名称
		strcpy(pStBaseTask->stTaskBaseInfo.szProjectNo,	pCurXlsBasTask->szProjectNo);	//03.检验单号
		//UINT	nTaskStatus;												//04.任务状态
		//UINT	nTaskType;	      											//05.任务类型
		strcpy(pStBaseTask->stTaskBaseInfo.szModel,		pCurXlsBasTask->szModel);		//06.型号
		strcpy(pStBaseTask->stTaskBaseInfo.szPhase,		pCurXlsBasTask->szPhase);		//07.阶段
		pStBaseTask->stProductInfo.nOid =	pStBasProduct->nOid;					//08.产品OID
		strcpy(pStBaseTask->stProductInfo.szProductName,	pCurXlsBasTask->szProductName);	//09.产品名称
		strcpy(pStBaseTask->stProductInfo.szProductNo,	pCurXlsBasTask->szProductNo);	//10.产品代号
		
		//ztedit for 2017-03-23
		pStBaseTask->stTaskBaseInfo.nSeriesOid = 0;						//11.产品系列号OID
		strcpy(pStBaseTask->stTaskBaseInfo.szSeriesName, "");
		//pStBaseTask->stTaskBaseInfo.nSeriesOid = pStBasSeries->nOid;						//11.产品系列号OID
		//strcpy(pStBaseTask->stTaskBaseInfo.szSeriesName,	pStBasSeries->szSeriesName);	//12.产品系列号名称
		
		//char    szProductCode[DB_USER_LEN];								//13.产品编号
		pStBaseTask->stTaskBaseInfo.nCodeNumber = pCurXlsBasTask->nCodeCnt;				//14.数量
		//char    szBatch[DB_USER_LEN];		       							//15.批次号
		pStBaseTask->stTaskBaseInfo.nGroupOid = nCurGroupOid;								//16.交检部门
		strcpy(pStBaseTask->stTaskBaseInfo.szGroupName,	pCurXlsBasTask->szGroupName);	//16_1 交检部门名称
		strcpy(pStBaseTask->stTaskBaseInfo.szUpUser,		pCurXlsBasTask->szUpUser);		//17.交检人
		//strcpy(pStBaseTask->szUpDate,		pCurXlsBasTask->szUpUser);		//18.交检日期
		//char    szSendDate[DB_USER_LEN];									//19.下发日期
		strcpy(pStBaseTask->stTaskBaseInfo.szCheckLeader,	pCurXlsBasTask->szCheckLeader);	//20.检验组长
		strcpy(pStBaseTask->stTaskBaseInfo.szCheckUser, 	pCurXlsBasTask->szCheckUser);	//21.检验员姓名
		strcpy(pStBaseTask->stTaskBaseInfo.szTechUser,		pCurXlsBasTask->szTechUser);	//22.工艺员 
		pStBaseTask->stTaskBaseInfo.nArmyTest = pCurXlsBasTask->nArmyTest;					//23.军检
		pStBaseTask->stTaskBaseInfo.nDianShiNum = pCurXlsBasTask->nDianShiNum;				//24.典试数量
		strcpy(pStBaseTask->stTaskBaseInfo.szAccording1,	pCurXlsBasTask->szAccording1);	//25.验收依据1
		strcpy(pStBaseTask->stTaskBaseInfo.szAccording2,	pCurXlsBasTask->szAccording2);	//26.验收依据2
		strcpy(pStBaseTask->stTaskBaseInfo.szAccording3,	pCurXlsBasTask->szAccording3);	//27.验收依据3
		strcpy(pStBaseTask->stTaskBaseInfo.szAccording4,	pCurXlsBasTask->szAccording4);	//28.验收依据4
		strcpy(pStBaseTask->stTaskBaseInfo.szAccording5,	pCurXlsBasTask->szAccording5);	//29.验收依据5
		strcpy(pStBaseTask->stTaskBaseInfo.szTaskRemark,	pCurXlsBasTask->szTaskRemark);	//30.备注
		//char    szPlanBegTime[DB_USER_LEN];			//31.计划开始时间
		//char    szPlanEndTime[DB_USER_LEN];			//32.计划结束时间
		//char    szRealBegTime[DB_USER_LEN];			//33.实际开始时间
		//char    szRealEndTime[DB_USER_LEN];			//34.实际结束时间

		
		//--------------------------------------------------------------------------------------
		bTaskExist = m_DMng.IsProductTaskExists(pStBasProduct->nOid, strTmpTaskName.GetBuffer(0));
		if (bTaskExist == 0)
		{
			ret = m_DMng.AddNewTask(pStBaseTask);
			if (ret != 0)
			{
				str.Format("DB_OPT_插入_任务_成功：nTaskPos=%d, Product_no=%s, Project_name=%s, nCodeCnt=%d",
					 i+1, pCurXlsBasTask->szProductNo, pCurXlsBasTask->szProjectNo, pCurXlsBasTask->nCodeCnt);
				g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
			}
			else
			{
				str.Format("DB_ERR_插入_任务_异常：nTaskPos=%d, Product_no=%s, Project_name=%s, nCodeCnt=%d",
					i+1, pCurXlsBasTask->szProductNo, pCurXlsBasTask->szProjectNo, pCurXlsBasTask->nCodeCnt);
				g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
				AfxMessageBox(str);
				return 0;
			}

			//4.3.1 插入任务编号信息
			//--------------------------------------------------------------------------------------
			for (j=0; j<pCurXlsBasTask->nCodeCnt; j++)
			{
				memset(pStBasTaskCode, 0, sizeof(StBasTaskCode));

				//UINT nOid;															//01.任务编号OID
				pStBasTaskCode->nTaskOid = pStBaseTask->stTaskBaseInfo.nOid;							//02.任务OID
				pStBasTaskCode->nCodeIndex = j+1;										//03.任务内编号顺序从1开始
				pStBasTaskCode->nDianshiTest = 0;										//04.是否典试
				strcpy(pStBasTaskCode->szCodeName, pCurXlsBasTask->szCodeNameArray[j]);	//05.编号名称

				ret = m_DMng.AddNewTaskCode(pStBasTaskCode);
				if (ret != 0)
				{
					str.Format("DB_OPT_插入_任务编号_成功：nTaskPos=%d, Product_no=%s, nCodeIndex=%d, szCodeName=%s",
						i+1, pCurXlsBasTask->szProductNo, pStBasTaskCode->nCodeIndex, pStBasTaskCode->szCodeName);
					g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
				}
				else
				{
					str.Format("DB_ERR_插入_任务编号_异常：nOid=%d, nTaskPos=%d, Product_no=%s, nCodeIndex=%d, szCodeName=%s",
						i+1, pCurXlsBasTask->szProductNo, pStBasTaskCode->nCodeIndex, pStBasTaskCode->szCodeName);
					g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
					AfxMessageBox(str);
					return 0;
				}
			}
		}
		//--------------------------------------------------------------------------------------


	} //end for (i=0; i<nTaskCnt; i++)


	str.Format("导入操作完成!");
	AfxMessageBox(str);	


	m_XlsBasTaskInfo.clear();
	m_nXlsBasTaskCnt = 0;

	return 1;
}
