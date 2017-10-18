// ResultSearch.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "ResultSearch.h"
#include "SelDate.h"
#include "WordSrc\\WordOptFun.h"
#include "AdjustmentDlg.h"

// CResultSearch 对话框

IMPLEMENT_DYNAMIC(CResultSearch, CDialog)

CResultSearch::CResultSearch(CWnd* pParent /*=NULL*/)
	: CDialog(CResultSearch::IDD, pParent)
{
	memset(&m_TstResultAtta,0,sizeof(StTstResultAtta));
}

CResultSearch::~CResultSearch()
{
}

void CResultSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RESULT_SEARCH_LIST1, m_TstRresultAttaList);
	DDX_Control(pDX, IDC_RESULT_SEARCH_LIST2, m_TstRresultBaseList);
}


BEGIN_MESSAGE_MAP(CResultSearch, CDialog)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_RESULT_SEARCH_BTN, &CResultSearch::OnBnClickedResultSearchBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_RESULT_SEARCH_LIST1, &CResultSearch::OnNMDblclkResultSearchList1)
	ON_NOTIFY(NM_CLICK, IDC_RESULT_SEARCH_LIST2, &CResultSearch::OnNMClickResultSearchList2)
	ON_BN_CLICKED(IDC_RESULT_SEARCH_TASK_BTN, &CResultSearch::OnBnClickedResultSearchTaskBtn)
	ON_BN_CLICKED(IDC_RESULT_SEARCH_PRODUCTNO_BTN, &CResultSearch::OnBnClickedResultSearchProductnoBtn)
	ON_BN_CLICKED(IDC_RESULT_SEARCH_BEGIN_BTN, &CResultSearch::OnBnClickedResultSearchBeginBtn)
	ON_BN_CLICKED(IDC_RESULT_SEARCH_END_BTN, &CResultSearch::OnBnClickedResultSearchEndBtn)
	ON_NOTIFY(NM_RCLICK, IDC_RESULT_SEARCH_LIST2, &CResultSearch::OnNMRClickResultSearchList2)
	ON_NOTIFY(NM_RCLICK, IDC_RESULT_SEARCH_LIST1, &CResultSearch::OnNMRClickResultSearchList1)
	ON_COMMAND(ID_MENU1_DELDATA_BASE, &CResultSearch::DelBaseData)
	ON_COMMAND(ID_MENU1_DELDATA_ATTA, &CResultSearch::DelAttaData)

	ON_COMMAND(ID_MENU1_C_TASK_REPORT_BASE, &CResultSearch::CreateTaskReport)
	ON_COMMAND(ID_MENU1_C_PRODUCT_REPORT_ATTA, &CResultSearch::CreateProductCodeReport)
	ON_COMMAND(ID_MENU1_C_MODE_REPORT_ATTA, &CResultSearch::CreateModeReport)
END_MESSAGE_MAP()

// CResultSearch 消息处理程序

BOOL CResultSearch::OnInitDialog()
{
	CDialog::OnInitDialog();

	char *ColName3[] = {"序号",_T("下发日期"),_T("导入日期"),_T("任务名称"),_T("产品代号"),
		_T("产品名称"),_T("检查人")};
	int  i,ColWidth3[] = {50,150,150,100,100,  100,100};
	m_TstRresultBaseList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_GRIDLINES);

	for(i = 0;i<7;i++)
	{
		m_TstRresultBaseList.InsertColumn(i, ColName3[i],LVCFMT_CENTER, ColWidth3[i]);
	}
	m_TstRresultBaseList.EnableRClickMenu(FALSE);


	
	char *ColName4[] = {"序号","下发日期","导入日期","任务名称","产品代号",
		"产品编号",_T("模板名称"),_T("是否典试"),_T("模板类型"),_T("模板行可变"),
		_T("图号数量"),_T("完成进度(百分比)"),_T("完成状态"),_T("完成时间"),_T("检查人")};
	int ColWidth4[] = {50,150,150,100,100,   100,100,100,100,100,   100,100,100,150,100};
	m_TstRresultAttaList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_GRIDLINES);

	for(i = 0;i<15;i++)
	{
		m_TstRresultAttaList.InsertColumn(i, ColName4[i],LVCFMT_CENTER, ColWidth4[i]);
	}
	m_TstRresultAttaList.EnableRClickMenu(FALSE);

	InitPopMenu1( );
	InitPopMenu2( );
	//CheckRadioButton(IDC_RESULT_SEARCH_TASK_RDO,IDC_RESULT_SEARCH_PRODCODE_RDO,IDC_RESULT_SEARCH_TASK_RDO);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CResultSearch::SetContrlShow()
{
	int ResultModel = m_TstResultBase.nResultType;

	switch(ResultModel)
	{
	case Task_DarkSearch:
		{
			GetDlgItem(IDC_RESULT_SEARCH_STATIC1)->SetWindowText(_T("结果查询界面"));
			((CEdit*)GetDlgItem(IDC_RESULT_SEARCH_TASK_EDT))->SetReadOnly(FALSE);
			m_TstRresultBaseList.ShowWindow(SW_SHOW);
			m_TstRresultAttaList.ShowWindow(SW_SHOW);
		}
		break;
	case Task_ExactSearch:
		{
			GetDlgItem(IDC_RESULT_SEARCH_STATIC1)->SetWindowText(_T(""));

			GetDlgItem(IDC_RESULT_SEARCH_TASK_BTN)->EnableWindow(FALSE);
			GetDlgItem(IDC_RESULT_SEARCH_TASK_EDT)->SetWindowText(m_TstResultBase.szTaskName);
			((CEdit*)GetDlgItem(IDC_RESULT_SEARCH_TASK_EDT))->SetReadOnly(TRUE);

			GetDlgItem(IDC_RESULT_SEARCH_PRODUCTNO_BTN)->EnableWindow(FALSE);
			GetDlgItem(IDC_PRODUCT_NO_EDT)->SetWindowText(m_TstResultBase.szProductNo);
			((CEdit*)GetDlgItem(IDC_PRODUCT_NO_EDT))->SetReadOnly(TRUE);


			m_TstRresultBaseList.ShowWindow(SW_SHOW);
			m_TstRresultAttaList.ShowWindow(SW_SHOW);
		}
		break;
	case Result_Search:
		{
			GetDlgItem(IDC_RESULT_SEARCH_STATIC1)->SetWindowText(_T("结果查询界面"));
			((CEdit*)GetDlgItem(IDC_RESULT_SEARCH_TASK_EDT))->SetReadOnly(FALSE);
			m_TstRresultBaseList.ShowWindow(SW_HIDE);
			m_TstRresultAttaList.ShowWindow(SW_SHOW);
		}
		break;
	default:
		{

		}
		break;
	}
}

void CResultSearch::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
}
void CResultSearch::AutoSize()
{
	CRect Rect ;
	GetClientRect(&Rect) ;
	if (GetDlgItem(IDC_RESULT_SEARCH_STATIC1)->GetSafeHwnd())
	{
		GetDlgItem(IDC_RESULT_SEARCH_STATIC1)->MoveWindow(1,5,Rect.Width()-1*2,Rect.Height()-5*2);
	}

	if(GetDlgItem(IDC_RESULT_SEARCH_STATIC2)->GetSafeHwnd())
	{
		GetDlgItem(IDC_RESULT_SEARCH_STATIC2)->MoveWindow(6,16,Rect.Width()-12,115);
	}

	int ResultModel = m_TstResultBase.nResultType;
	switch(ResultModel)
	{
	case Task_DarkSearch:
		{

		}
	case Task_ExactSearch:
		{
			if(m_TstRresultBaseList.GetSafeHwnd())
			{
				m_TstRresultBaseList.MoveWindow(3,133,Rect.Width()-6,(Rect.Height()-(143))/2);
			}
			if(m_TstRresultAttaList.GetSafeHwnd())
			{
				m_TstRresultAttaList.MoveWindow(3,133+(Rect.Height()-(143))/2,Rect.Width()-6,(Rect.Height()-(143))/2);
			}
		}
		break;
	case Result_Search:
		{
			if(m_TstRresultAttaList.GetSafeHwnd())
			{
				m_TstRresultAttaList.MoveWindow(3,133,Rect.Width()-6,Rect.Height()-(143));
			}
		}
		break;
	default:
		{
			if(m_TstRresultBaseList.GetSafeHwnd())
			{
				m_TstRresultBaseList.MoveWindow(3,133,Rect.Width()-6,(Rect.Height()-(143))/2);
			}
			if(m_TstRresultAttaList.GetSafeHwnd())
			{
				m_TstRresultAttaList.MoveWindow(3,133+(Rect.Height()-(143))/2,Rect.Width()-6,(Rect.Height()-(143))/2);
			}
		}
		break;
	}
}
void CResultSearch::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	AutoSize();
}


void CResultSearch::OnBnClickedResultSearchBtn()
{

	SearchBaseByTaskName();
	
}


//通过模糊查询检索任务列表//
BOOL CResultSearch::SearchBaseByTaskName()
{
	/*
	m_TstRresultBaseList.DeleteAllItems();
	m_TstRresultAttaList.DeleteAllItems();
	PostMessage(WM_SIZE);

	SetContrlShow();

	UINT nGroupOid, nTaskOid;
	CString strTaskName;
	CString strProductNo;
	CString strSeriesName;
	CString strBeginDate;
	CString strEndDate;

	StSearchInfo nSearchInfo;
	memset(&nSearchInfo,0,sizeof(StSearchInfo));


	GetDlgItem(IDC_RESULT_SEARCH_TASK_EDT)->GetWindowText(strTaskName);
	strTaskName = strTaskName.TrimLeft();
	strTaskName = strTaskName.TrimRight();
	strcpy(nSearchInfo.szTaskName,strTaskName);

	GetDlgItem(IDC_PRODUCT_NO_EDT)->GetWindowText(strProductNo);
	strProductNo = strProductNo.TrimLeft();
	strProductNo = strProductNo.TrimRight();
	strcpy(nSearchInfo.szProductNo,strProductNo);



	GetDlgItem(IDC_RESULT_SEARCH_BEGINDATE_EDT)->GetWindowText(strBeginDate);
	strBeginDate = strBeginDate.TrimLeft();
	strBeginDate = strBeginDate.TrimRight();
	strcpy(nSearchInfo.szBeginDate,strBeginDate);


	GetDlgItem(IDC_RESULT_SEARCH_ENDDATE_EDT)->GetWindowText(strEndDate);
	strEndDate = strEndDate.TrimLeft();
	strEndDate = strEndDate.TrimRight();
	strcpy(nSearchInfo.szEndDate,strEndDate);


	
	nSearchInfo.nGroupOid = nGroupOid = m_TstResultBase.nGroupOid = g_CurSelDepart.nOid;
	nSearchInfo.nTaskOid = nTaskOid = m_TstResultBase.nTaskOid;
	strcpy(m_TstResultBase.szTaskName,nSearchInfo.szTaskName);

	int ResultModel = m_TstResultBase.nResultType;
	switch(ResultModel)
	{
	case Task_DarkSearch://基于任务 模糊查询//
		{
			if(!m_DMng.InitGroupTstResultBaseList(&nSearchInfo,&m_TstRresultBaseList))
			{
				return FALSE;
			}
		}
		break; 
	case Task_ExactSearch://基于任务精确查找//
		{
			if(!m_DMng.InitTaskTstResultBaseList(&nSearchInfo,&m_TstRresultBaseList))
			{
				return FALSE;
			}
		}
		break;
	case Result_Search:
		{
			if(!m_DMng.InitSearchTstResultList(&nSearchInfo,&m_TstRresultAttaList))
			{
				return FALSE;
			}

			
		}
		break;
	default:
		{

		}
		break;
	}
	
*/
	return TRUE;
}



void CResultSearch::OnOK()
{
	OnBnClickedResultSearchBtn();
	//CDialog::OnOK();
}

BOOL CResultSearch::ShowCurData()
{
	int t1,t2;
	CString str;
	t1= GetTickCount();

	DelFile();
	int Index = m_TstRresultAttaList.GetFirstSelectedItem(), nCount = m_TstRresultAttaList.GetItemCount();
	if(Index<0 || Index >= nCount)
		return FALSE;
	//组建查询条件//
	UINT nAttaOid = m_TstRresultAttaList.GetItemData(Index);
	UINT nGroupOid = g_CurSelDepart.nOid;

	memset(&m_TstResultAtta,0,sizeof(StTstResultAtta));
	if(!m_DMng.GetTstResultOid(nGroupOid,nAttaOid,&m_TstResultAtta))
	{
		return FALSE;
	}else
	{
		if(!m_DMng.GetAttaXmlFile(nGroupOid,nAttaOid))
		{
			return FALSE;
		}
	}

	t2 = GetTickCount()-t1;
	str.Format(_T("CResultSearch::ShowCurData 用时 %d 毫秒"),t2);
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));
	return TRUE;
}

void CResultSearch::OnNMDblclkResultSearchList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if(ShowCurData())
	{
		CResultShow ndlg;
		ndlg.m_pCurAttaInfo = &m_TstResultAtta;
		ndlg.DoModal();
	}
	*pResult = 0;
	this->InvalidateRect(NULL);
}


void CResultSearch::OnNMClickResultSearchList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码//

	//单击查询当前任务的详细情况//
/*
	int nCount = m_TstRresultBaseList.GetItemCount(),Index = m_TstRresultBaseList.GetFirstSelectedItem();

	if(Index < 0 || Index >= nCount)
	{
		return ;
	}

	UINT nBaseOid = m_TstRresultBaseList.GetItemData(Index);
	memset(m_TstResultBase.szTaskName,0,sizeof(m_TstResultBase.szTaskName));
	memset(m_TstResultBase.szSendDate,0,sizeof(m_TstResultBase.szSendDate));
	memset(m_TstResultBase.szCheckUser,0,sizeof(m_TstResultBase.szCheckUser));
	m_TstResultBase.nOid = nBaseOid;
	
	m_TstRresultAttaList.DeleteAllItems();
	if(!m_DMng.InitBaseOidTstResultList(m_TstResultBase.nGroupOid,m_TstResultBase.nOid,&m_TstRresultAttaList))
	{
		return ;
	}*/
	*pResult = 0;
}

void CResultSearch::OnBnClickedResultSearchTaskBtn()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CResultSearch::OnBnClickedResultSearchProductnoBtn()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CResultSearch::OnBnClickedResultSearchBeginBtn()
{
	CSelDate Dlg;
	CString strBeginDate;
	SYSTEMTIME *pstTime = NULL;
	if(Dlg.DoModal() == IDOK)
	{
		pstTime = &Dlg.m_stTime;
		strBeginDate.Format(_T("%04d-%02d-%02d"),pstTime->wYear,pstTime->wMonth,pstTime->wDay);
		GetDlgItem(IDC_RESULT_SEARCH_BEGINDATE_EDT)->SetWindowText(strBeginDate);
	}
}

void CResultSearch::OnBnClickedResultSearchEndBtn()
{
	
	CSelDate Dlg;
	CString strBeginDate;
	SYSTEMTIME *pstTime = NULL;
	if(Dlg.DoModal() == IDOK)
	{
		pstTime = &Dlg.m_stTime;
		strBeginDate.Format(_T("%04d-%02d-%02d"),pstTime->wYear,pstTime->wMonth,pstTime->wDay);
		GetDlgItem(IDC_RESULT_SEARCH_ENDDATE_EDT)->SetWindowText(strBeginDate);
	}
}

void CResultSearch::DelBaseData()//以任务为单位删除结果数据//
{
	int Index = m_TstRresultBaseList.GetFirstSelectedItem(),
		nCount = m_TstRresultBaseList.GetItemCount();

	if(Index<0 || Index>=nCount)
	{
		return ;
	}

	if(MessageBox(_T("确定删除数据吗?\n(数据删除后将无法恢复!)）"),_T(""),MB_OKCANCEL|MB_ICONQUESTION) != IDOK)
	{
		return ;
	}
	UINT nGroupOid = g_CurSelDepart.nOid;
	UINT nBaseOid = m_TstRresultBaseList.GetItemData(Index);
	if(m_DMng.DelBaseData(nGroupOid,nBaseOid))
	{
		m_TstRresultBaseList.DeleteItem(Index);
	}

}
void CResultSearch::DelAttaData()//以结果附件为单位删除结果数据//
{
	int Index = m_TstRresultAttaList.GetFirstSelectedItem(),
		nCount = m_TstRresultAttaList.GetItemCount();

	if(Index<0 || Index>=nCount)
	{
		return ;
	}

	if(MessageBox(_T("确定删除数据吗?\n(数据删除后将无法恢复!)）"),_T(""),MB_OKCANCEL|MB_ICONQUESTION) != IDOK)
	{
		return ;
	}
	UINT nGroupOid = g_CurSelDepart.nOid;
	UINT nBaseOid = 0;
	UINT bAttaOid = m_TstRresultAttaList.GetItemData(Index);
	
	if(m_DMng.DelAttaData(nGroupOid,nBaseOid,bAttaOid))
	{
		m_TstRresultAttaList.DeleteItem(Index);
	}
}

//以任务为单位生成报告文件//
void  CResultSearch::CreateTaskReport()
{
	CString str, strFileName, strDesFile, strSrcFile, strCreateFile;
	int		ret, tick1,tick2;

	int Index = m_TstRresultAttaList.GetFirstSelectedItem(),
		nCount = m_TstRresultAttaList.GetItemCount();

	if(Index<0 || Index>=nCount)
	{
		return ;
	}

	CString strTaskName = m_TstRresultAttaList.GetItemText(Index,3);
	CString strProductNo = m_TstRresultAttaList.GetItemText(Index,4);
	str.Format(_T("是否生成任务=\"%s\"的报告文件?(确定/取消)"),strTaskName);
	if(MessageBox(str,_T("提示"),MB_OKCANCEL|MB_ICONQUESTION) != IDOK)
	{
		return ;
	}

	//1.获取这个任务的结果附件信息

	UINT nGroupOid = g_CurSelDepart.nOid;
	UINT nAttaOid = m_TstRresultAttaList.GetItemData(Index);


	StTstResultAtta stCreateReportAtta;
	memset(&stCreateReportAtta, 0, sizeof(StTstResultAtta));

	if(!m_DMng.GetTstResultOid(nGroupOid,nAttaOid,&stCreateReportAtta))
	{
		str.Format(_T("获取结果附件信息时出错!"));
		AfxMessageBox(str);
		return;
	}




	vector<StTstResultAtta> *pStResultAtta = NULL;
	CAdjustmentDlg AdjustmentDlg;
	AdjustmentDlg.m_pStCreateReportAtta = &stCreateReportAtta;
	if(AdjustmentDlg.DoModal() == IDOK)
	{
		pStResultAtta = &AdjustmentDlg.m_CreateReportArray;
	}else
	{
		return;
	}

	if(pStResultAtta == NULL)
	{
		return;
	}

	if(pStResultAtta->size()<=0)
	{
		return;
	}


	//2.选择一个报告文件名称
	strCreateFile.Format(_T("%s_%s"),strProductNo,GetDateTimeString2());
	CFileDialog *lpszOpenFile;    //定义一个CfileDialog对象
	lpszOpenFile = new CFileDialog(FALSE,".doc",strCreateFile,OFN_FILEMUSTEXIST |OFN_HIDEREADONLY , 
		"文件类型(*.doc)|*.doc||");//生成一个对话框
	if(lpszOpenFile->DoModal() == IDOK)//假如点击对话框确定按钮
	{

		strCreateFile = lpszOpenFile->GetPathName();	//得到打开文件的路径

	}else
	{
		delete lpszOpenFile;	//释放分配的对话框
		return ;
	}
	delete lpszOpenFile;	//释放分配的对话框


	

	
	
	
	CreateReportBase(pStResultAtta,strCreateFile);
	return ;
	int i;
	nCount = pStResultAtta->size();
	StTstResultAtta *pCurAttaInfo;
	LoadOutTaskXmlAnalysis  m_LoadOutTask;
	CArray<TestDataStr,TestDataStr> m_DataArray;
	CArray<StBasAttachment,StBasAttachment> m_ExclosureArray;
	CStringArray nStrFileNames;

	int t1,t2;

	/******************************************************/

	t1= GetTickCount();
	nStrFileNames.RemoveAll();
	for (i = 0;i<nCount;i++)
	{
		
		pCurAttaInfo = &pStResultAtta->at(i);

		//1.数据  2.图号信息  3.附件模板信息//
		

		if(!m_DMng.GetAttaXmlFile(nGroupOid,pCurAttaInfo->nOid))
		{
			continue;
		}

		m_LoadOutTask.GetCurTaskInfoLoad();

		int nRet = 0;
		nRet = m_LoadOutTask.AnalysisData(m_DataArray,m_ExclosureArray);//获取当前任务项的数据//
		if(!nRet)
		{
			//return 0;
		}

		g_pDataArray = &m_DataArray;////1.数据

		int nPicNumCount = g_PicNum = m_LoadOutTask.m_CurTaskInfo.pArryTaskPicNum.size();
		g_pArryTaskPicNum = &m_LoadOutTask.m_CurTaskInfo.pArryTaskPicNum;//2.图号信息///
		g_pCurAttaInfo = pCurAttaInfo;//3.附件信息//


		

		if (pCurAttaInfo->nModeRowVar == mode_normal)
		{
			tick1 = GetTickCount();

			StBasMode StBasModeInfo;
			memset(&StBasModeInfo, 0, sizeof(StBasMode));

			StBasModeInfo.nModeType = pCurAttaInfo->nModeType;
			strcpy(StBasModeInfo.szModeName, pCurAttaInfo->szModeName);
			strcpy(StBasModeInfo.stProductInfo.szProductNo, pCurAttaInfo->szProductNo);
			strFileName = BuildReportModeFilePath(&StBasModeInfo);

			if(GetFileAttributes(strFileName.GetBuffer(0)) == 0xFFFFFFFF)
			{
				str.Format(_T("报告模板不存在 ！%s"),strFileName);
				AfxMessageBox(str);
				continue ;
			}

			memset(StBasModeInfo.szModeName, 0, sizeof(StBasModeInfo.szModeName));
			strcpy(StBasModeInfo.szModeName, _T("t_Mode2"));
			strDesFile = BuildReportModeFilePath(&StBasModeInfo);


			//strFileName = _T("c:\\Mode2.doc");
			//strDesFile  = _T("c:\\t_Mode2.doc");

			ret = WordOpt_MakeTabModeToTabData(strFileName.GetBuffer(0), strDesFile.GetBuffer(0));

			tick2 = GetTickCount()-tick1;
			str.Format("用时%d毫秒! ret=%d, 输出文件：%s", tick2, ret, strDesFile.GetBuffer(0)); 
			//AfxMessageBox(str);	



			//CString str, strFileName, strDesFile;
			//int		ret, tick1,tick2;
			tick1 = GetTickCount();

			//strCreateFile  = _T("c:\\t_ModeInfo_2.doc");
			//strFileName = _T("c:\\t_Mode2.doc");

			strSrcFile.Format(_T("%s\\%s\\%s.doc"),g_WorkPath, Report_Mode_Path,GetDateTimeFileNameString());
			ret = WordOpt_MakeReportTabInfoDemo(strSrcFile.GetBuffer(0),strDesFile.GetBuffer(0));

			nStrFileNames.Add(strSrcFile);

			tick2 = GetTickCount()-tick1;
			str.Format("用时%d毫秒! ret=%d, 输出文件：%s", tick2, ret, strSrcFile.GetBuffer(0));
			g_pLogInfo->WriteLogFile(str.GetBuffer(0));
			//AfxMessageBox(str);	

		}else
		{
			int		ret, tick1,tick2;
			tick1 = GetTickCount();

			//strCreateFile = _T("C:\\tt2.doc");

			strSrcFile.Format(_T("%s\\%s\\%s.doc"),g_WorkPath, Report_Mode_Path,GetDateTimeFileNameString());
			ret = WordOpt_MakeReportRowVarDemo( strSrcFile.GetBuffer(0) ); 

			nStrFileNames.Add(strSrcFile);

			tick2 = GetTickCount()-tick1;
			str.Format("用时%d毫秒! ret=%d, 输出文件：%s", tick2, ret, strSrcFile.GetBuffer(0)); 
			g_pLogInfo->WriteLogFile(str.GetBuffer(0));
			//AfxMessageBox(str);	
		}

		remove(strDesFile.GetBuffer(0));

	
	}
	/******************************************************/

	ret = WordOpt_MakeTestimonialDemo(strCreateFile.GetBuffer(0),nStrFileNames);
	pStResultAtta->clear();


	t2 = GetTickCount()-t1;
	str.Format("用时%d毫秒! ret=%d, 输出文件：%s", t2, ret, strCreateFile.GetBuffer(0)); 
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));
	AfxMessageBox(str);	

	
}
//以产品编号为单位生成报告文件//
void  CResultSearch::CreateProductCodeReport()
{

	CString str, strFileName, strDesFile, strSrcFile, strCreateFile;

	int Index = m_TstRresultAttaList.GetFirstSelectedItem(),
		nCount = m_TstRresultAttaList.GetItemCount();

	if(Index<0 || Index>=nCount)
	{
		return ;
	}

	CString strProductNo = m_TstRresultAttaList.GetItemText(Index,4);
	CString strProductCode = m_TstRresultAttaList.GetItemText(Index,5);
	str.Format(_T("是否生成产品报告, 产品编号=\"%s\" ?(确定/取消)"),strProductCode);
	if(MessageBox(str,_T("提示"),MB_OKCANCEL|MB_ICONQUESTION) != IDOK)
	{
		return ;
	}

	
	
	//1.获取这个任务的结果附件信息

	UINT nGroupOid = g_CurSelDepart.nOid;
	UINT nAttaOid = m_TstRresultAttaList.GetItemData(Index);
	UINT nBaseOid = 0;

	StTstResultAtta stCreateReportAtta;
	memset(&stCreateReportAtta, 0, sizeof(StTstResultAtta));

	if(!m_DMng.GetTstResultOid(nGroupOid,nAttaOid,&stCreateReportAtta))
	{
		str.Format(_T("获取结果附件信息时出错!"));
		AfxMessageBox(str);
		return;
	}

	vector<StTstResultAtta> *pStResultAtta = NULL;
	CAdjustmentDlg AdjustmentDlg;
	AdjustmentDlg.m_pStCreateReportAtta = &stCreateReportAtta;
	if(AdjustmentDlg.DoModal() == IDOK)
	{
		pStResultAtta = &AdjustmentDlg.m_CreateReportArray;
	}else
	{
		return;
	}

	if(pStResultAtta == NULL)
	{
		return;
	}

	if(pStResultAtta->size()<=0)
	{
		return;
	}


	//2.选择一个报告文件名称
	strCreateFile.Format(_T("%s_%s_%s"),strProductNo,strProductCode,GetDateTimeString2());
	CFileDialog *lpszOpenFile;    //定义一个CfileDialog对象
	lpszOpenFile = new CFileDialog(FALSE,".doc",strCreateFile,OFN_FILEMUSTEXIST |OFN_HIDEREADONLY , 
		"文件类型(*.doc)|*.doc||");//生成一个对话框
	if(lpszOpenFile->DoModal() == IDOK)//假如点击对话框确定按钮
	{

		strCreateFile = lpszOpenFile->GetPathName();	//得到打开文件的路径

	}else
	{
		delete lpszOpenFile;	//释放分配的对话框
		return ;
	}
	delete lpszOpenFile;	//释放分配的对话框

	CreateReportBase(pStResultAtta,strCreateFile);

}

//以模板为单位生成报告文件
void  CResultSearch::CreateModeReport()
{

	CString str, strFileName, strDesFile, strSrcFile, strCreateFile;
	
	int Index = m_TstRresultAttaList.GetFirstSelectedItem(),
		nCount = m_TstRresultAttaList.GetItemCount();

	if(Index<0 || Index>=nCount)
	{
		return ;
	}

	CString strProductNo = m_TstRresultAttaList.GetItemText(Index,4);
	CString strProductCode = m_TstRresultAttaList.GetItemText(Index,6);

	CString strModeName = m_TstRresultAttaList.GetItemText(Index,7);
	str.Format(_T("是否生成产品模板=\"%s\"的报告文件?(确定/取消)"),strModeName);
	if(MessageBox(str,_T("提示"),MB_OKCANCEL|MB_ICONQUESTION) != IDOK)
	{
		return ;
	}


	

	//1.选择一个报告文件名称
	strCreateFile.Format(_T("%s_%s_%s_%s"),strProductNo,strProductCode,strModeName,GetDateTimeString2());
	CFileDialog *lpszOpenFile;    //定义一个CfileDialog对象
	lpszOpenFile = new CFileDialog(FALSE,".doc",strCreateFile,OFN_FILEMUSTEXIST |OFN_HIDEREADONLY , 
		"文件类型(*.doc)|*.doc||");//生成一个对话框
	if(lpszOpenFile->DoModal() == IDOK)//假如点击对话框确定按钮
	{

		strCreateFile = lpszOpenFile->GetPathName();	//得到打开文件的路径

	}else
	{
		delete lpszOpenFile;	//释放分配的对话框
		return ;
	}
	delete lpszOpenFile;	//释放分配的对话框





	//2.获取这个任务的结果附件信息

	UINT nGroupOid = g_CurSelDepart.nOid;
	UINT nAttaOid = m_TstRresultAttaList.GetItemData(Index);
	UINT nBaseOid = 0;

	StTstResultAtta m_CreateReportAtta;
	memset(&m_CreateReportAtta, 0, sizeof(StTstResultAtta));

	if(!m_DMng.GetTstResultOid(nGroupOid,nAttaOid,&m_CreateReportAtta))
	{
		str.Format(_T("获取结果附件信息时出错!"));
		AfxMessageBox(str);
		return;
	}
	vector<StTstResultAtta> StResultAtta;
	StResultAtta.push_back(m_CreateReportAtta);

	CreateReportBase(&StResultAtta,strCreateFile);
	

	
}

//生成报告
void  CResultSearch::CreateReportBase(vector<StTstResultAtta> *pStResultAtta,CString strCreateFile)
{
	UINT nGroupOid = g_CurSelDepart.nOid;
	CString str, strFileName, strDesFile, strSrcFile;
	int		ret=0, tick1=0,tick2=0;

	int i,nCount;
	nCount = pStResultAtta->size();
	StTstResultAtta *pCurAttaInfo;
	LoadOutTaskXmlAnalysis  m_LoadOutTask;
	CArray<TestDataStr,TestDataStr> m_DataArray;
	CArray<StBasAttachment,StBasAttachment> m_ExclosureArray;
	CStringArray nStrFileNames;

	int t1,t2;

	/******************************************************/

	str.Format(_T("%s\\%s"),g_WorkPath,Report_Temp_Path);
	if(GetFileAttributes(str.GetBuffer(0)) == 0xffffffff)
	{
		CreateDirectory(str.GetBuffer(0),NULL);
	}

	t1= GetTickCount();
	nStrFileNames.RemoveAll();
	for (i = 0;i<nCount;i++)
	{

		pCurAttaInfo = &pStResultAtta->at(i);

		//1.数据  2.图号信息  3.附件模板信息//


		if(!m_DMng.GetAttaXmlFile(nGroupOid,pCurAttaInfo->nOid))
		{
			continue;
		}

		m_LoadOutTask.m_CurTaskInfo.Release();
		m_LoadOutTask.GetCurTaskInfoLoad();

		int nRet = 0;
		m_DataArray.RemoveAll();
		m_ExclosureArray.RemoveAll();
		nRet = m_LoadOutTask.AnalysisData(m_DataArray,m_ExclosureArray);//获取当前任务项的数据//
		if(!nRet)
		{
			//return 0;
		}

		g_pDataArray = &m_DataArray;////1.数据

		int nPicNumCount = g_PicNum = m_LoadOutTask.m_CurTaskInfo.pArryTaskPicNum.size();
		g_pArryTaskPicNum = &m_LoadOutTask.m_CurTaskInfo.pArryTaskPicNum;//2.图号信息///
		g_pCurAttaInfo = pCurAttaInfo;//3.附件信息//




		if (pCurAttaInfo->nModeRowVar == mode_normal)
		{
			tick1 = GetTickCount();

			StBasMode StBasModeInfo;
			memset(&StBasModeInfo, 0, sizeof(StBasMode));

			StBasModeInfo.nModeType = pCurAttaInfo->nModeType;
			strcpy(StBasModeInfo.szModeName, pCurAttaInfo->szModeName);
			strcpy(StBasModeInfo.stProductInfo.szProductNo, pCurAttaInfo->szProductNo);
			strFileName = BuildReportModeFilePath(&StBasModeInfo);

			if(GetFileAttributes(strFileName.GetBuffer(0)) == 0xFFFFFFFF)
			{
				str.Format(_T("报告模板不存在 ！%s"),strFileName);
				AfxMessageBox(str);
				continue ;
			}

			
			strSrcFile.Format(_T("%s\\%s\\%s_%s.doc"),g_WorkPath,
				Report_Temp_Path,StBasModeInfo.szModeName,GetDateTimeFileNameString());

			str.Format("[第%d个]开始生成文件：%s",i+1, strSrcFile.GetBuffer(0));
			g_pLogInfo->WriteLogFile(str.GetBuffer(0));


			tick1 = GetTickCount();
			//strFileName = _T("c:\\Mode2.doc");
			//strDesFile  = _T("c:\\t_Mode2.doc");
			strDesFile.Format(_T("%s\\%s\\t%d_Mode.doc"),g_WorkPath,Report_Temp_Path,i+1);
			str.Format("开始生成文件：%s", strDesFile.GetBuffer(0));
			g_pLogInfo->WriteLogFile(str.GetBuffer(0));

			ret = WordOpt_MakeTabModeToTabData(strFileName.GetBuffer(0), strDesFile.GetBuffer(0));


			str.Format("CreateReportBase：%d, ret=%d", 1, ret);
			g_pLogInfo->WriteLogFile(str.GetBuffer(0));


			tick2 = GetTickCount()-tick1;
			str.Format("用时%d毫秒! ret=%d, 生成文件成功：%s", tick2, ret, strDesFile.GetBuffer(0)); 
			g_pLogInfo->WriteLogFile(str.GetBuffer(0));
			//AfxMessageBox(str);	



			//CString str, strFileName, strDesFile;
			//int		ret, tick1,tick2;
			tick1 = GetTickCount();

			//strCreateFile  = _T("c:\\t_ModeInfo_2.doc");
			//strFileName = _T("c:\\t_Mode2.doc");

			
			ret = WordOpt_MakeReportTabInfoDemo(strSrcFile.GetBuffer(0),strDesFile.GetBuffer(0));

			nStrFileNames.Add(strSrcFile);

			tick2 = GetTickCount()-tick1;
			str.Format("用时%d毫秒! ret=%d, [第%d个]生成文件成功：%s", tick2, ret,i+1, strSrcFile.GetBuffer(0));
			g_pLogInfo->WriteLogFile(str.GetBuffer(0));
			//AfxMessageBox(str);	

		}else
		{
			tick1 = GetTickCount();

			//strCreateFile = _T("C:\\tt2.doc");

			strSrcFile.Format(_T("%s\\%s\\%s.doc"),g_WorkPath, Report_Temp_Path,GetDateTimeFileNameString());
			str.Format("[第%d个]开始生成文件：%s",i+1, strSrcFile.GetBuffer(0));
			g_pLogInfo->WriteLogFile(str.GetBuffer(0));

			ret = WordOpt_MakeReportRowVarDemo( strSrcFile.GetBuffer(0) ); 

			nStrFileNames.Add(strSrcFile);

			tick2 = GetTickCount()-tick1;
			str.Format("用时%d毫秒! ret=%d, [第%d个]生成文件成功：%s", tick2, ret,i+1, strSrcFile.GetBuffer(0)); 
			g_pLogInfo->WriteLogFile(str.GetBuffer(0));
			//AfxMessageBox(str);	
		}

		remove(strDesFile.GetBuffer(0));


	}
	/******************************************************/

	tick1 = GetTickCount();

	ret = WordOpt_MakeTestimonialDemo(strCreateFile.GetBuffer(0),nStrFileNames);

	tick2 = GetTickCount()-tick1;
	str.Format("用时%d毫秒! ret=%d, 合并中间文件,文件个数%d", tick2, ret, nCount); 
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));


	pStResultAtta->clear();
	t2 = GetTickCount()-t1;
	str.Format("用时%d毫秒! ret=%d, 输出文件：%s", t2, ret, strCreateFile.GetBuffer(0)); 
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));
	AfxMessageBox(str);	
}

void  CResultSearch::InitPopMenu1( )					//初始化菜单1
{
	if(!m_PopupMenu1.GetSafeHmenu())
	{
		m_PopupMenu1.CreatePopupMenu();

		m_PopupMenu1.AppendMenu(MF_STRING, ID_MENU1_DELDATA_BASE,		"删除数据");
		
	}
}

void  CResultSearch::InitPopMenu2( )					//初始化菜单1
{
	if(!m_PopupMenu2.GetSafeHmenu())
	{
		m_PopupMenu2.CreatePopupMenu();

		m_PopupMenu2.AppendMenu(MF_STRING, ID_MENU1_C_PRODUCT_REPORT_ATTA,     "生成产品报告");
		m_PopupMenu2.AppendMenu(MF_STRING, ID_MENU1_C_MODE_REPORT_ATTA,        "生成模板报告");
		m_PopupMenu2.AppendMenu(MF_STRING, ID_MENU1_C_TASK_REPORT_BASE,       "生成任务报告");
		//m_PopupMenu2.AppendMenu(MF_SEPARATOR);
		//m_PopupMenu2.AppendMenu(MF_STRING, ID_MENU1_DELDATA_ATTA,		"删除数据");


	}
}
void CResultSearch::OnNMRClickResultSearchList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	int Index = m_TstRresultBaseList.GetFirstSelectedItem(),
		nCount = m_TstRresultBaseList.GetItemCount();
	if(Index <0 || Index >= nCount)
	{
		return;
	}

	POINT	point;
	GetCursorPos(&point);
	m_PopupMenu1.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);

	*pResult = 0;
}

void CResultSearch::OnNMRClickResultSearchList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	int Index = m_TstRresultAttaList.GetFirstSelectedItem(),
		nCount = m_TstRresultAttaList.GetItemCount();
	if(Index <0 || Index >= nCount)
	{
		return;
	}

	POINT	point;
	GetCursorPos(&point);
	m_PopupMenu2.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);


	
	*pResult = 0;
}
