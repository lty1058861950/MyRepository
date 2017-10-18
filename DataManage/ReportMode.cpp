// ReportMode.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "ReportMode.h"


// CReportMode 对话框

IMPLEMENT_DYNAMIC(CReportMode, CDialog)

CReportMode::CReportMode(CWnd* pParent /*=NULL*/)
	: CDialog(CReportMode::IDD, pParent)
{
	m_ShowType = Report_Mode;
}

CReportMode::~CReportMode()
{

}

void CReportMode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ReportModeList);
}


BEGIN_MESSAGE_MAP(CReportMode, CDialog)
	ON_BN_CLICKED(IDC_SHOW_BTN, &CReportMode::OnBnClickedShowBtn)
	ON_COMMAND_RANGE(IDC_CHECK1,IDC_CHECK4, OnUpdateChart )
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CReportMode::OnNMRClickList1)
	ON_COMMAND(ID_MENU1_LOADIN, &CReportMode::LoadInModeFile)
	ON_COMMAND(ID_MENU2_OPENDIR, &CReportMode::OpenFileDir)
END_MESSAGE_MAP()


// CReportMode 消息处理程序

void CReportMode::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}

BOOL CReportMode::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString strText;
	char *ColName1[] = {"序号","模板名称","模板类型","适用的产品","状态","所在路径"};
	int  ColWidth1[] = {50,150,100,100,100,1024};
	m_ReportModeList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_GRIDLINES);

	for(int i = 0;i<6;i++)
	{
		m_ReportModeList.InsertColumn(i, ColName1[i],LVCFMT_CENTER, ColWidth1[i]);
	}
	m_ReportModeList.EnableRClickMenu(FALSE);

	if(m_ShowType == Report_Mode)
	{
		strText.Format(_T("报告模板维护"));
		this->SetWindowText(strText);
		
	}else
	{
		strText.Format(_T("公式模板维护"));
		this->SetWindowText(strText);
	}

	MoveWindow(0,0,1224,g_WinHeight);
	CenterWindow();
	InitPopMenu1( );


	((CButton *)GetDlgItem(IDC_CHECK1))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_CHECK2))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_CHECK3))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_CHECK4))->SetCheck(TRUE);
	InitReportModeList();

	SetTimer(2,1000,NULL);
	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CReportMode::InsertModeToList(StBasMode *pModeInfo)
{
	int Index;
	CString strNum, strFilePath;
	int nPos = 0;
	nPos = 1;
	Index = m_ReportModeList.GetItemCount();
	strNum.Format(_T("%d"),Index+1);
	m_ReportModeList.InsertItem(Index,strNum);
	m_ReportModeList.SetItemData(Index,pModeInfo->nOid);

	strNum.Format(_T("%s"),pModeInfo->szModeName);
	m_ReportModeList.SetItemText(Index,nPos++,strNum);
	strNum.Format(_T("%s"),GetModeType(pModeInfo->nModeType));
	m_ReportModeList.SetItemText(Index,nPos++,strNum);
	strNum.Format(_T("%s"),pModeInfo->stProductInfo.szProductNo);
	m_ReportModeList.SetItemText(Index,nPos++,strNum);

	if(m_ShowType == Report_Mode)
	{
		strFilePath = BuildReportModeFilePath(pModeInfo);
	}else
	{
		strFilePath = BuildModeFormulaFilePath(g_WorkPath,pModeInfo);
	}
	
	strNum.Format(_T("%s"),strFilePath);
	m_ReportModeList.SetItemText(Index,5,strNum);
	m_ReportModeList.SetItemColor(Index,5,ModeFileIsExists(strNum,Index));
}
void CReportMode::InitReportModeList()
{
	vector<StBasMode > nModeArry;
	StBasMode stModeSearchInfo;
	UINT nGroupOid = g_CurSelDepart.nOid;
	CString strProductNo;
	CString strFilePath;
	StBasMode *pModeSearchInfo = &stModeSearchInfo;
	memset(pModeSearchInfo, 0, sizeof(StBasMode));
	int nPos = 0;

	int i,nCount;
	CString strNum;

	
	GetDlgItem(IDC_PRODUCT_NO_EDT)->GetWindowText(strProductNo);
	strProductNo = strProductNo.TrimLeft();
	strProductNo = strProductNo.TrimRight();
	m_ReportModeList.DeleteAllItems();

	strcpy(pModeSearchInfo->stProductInfo.szProductNo, strProductNo);
	if(((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck())
	{
		if(m_DMng.GetGroupModeTypeData(nGroupOid,Mode_Currency,&nModeArry))
		{
			nCount = nModeArry.size();
			for (i = 0;i<nCount;i++)
			{
				InsertModeToList(&nModeArry.at(i));
			}

			nModeArry.clear();
		}
	}

	if(((CButton *)GetDlgItem(IDC_CHECK2))->GetCheck())
	{
		pModeSearchInfo->bModeDedicated = Sel_Check;
		nPos++;
		if(nPos>=1)
		{
			if(m_DMng.GetGroupModeInfo(nGroupOid,pModeSearchInfo,&nModeArry))
			{
				nCount = nModeArry.size();
				for (i = 0;i<nCount;i++)
				{
					InsertModeToList(&nModeArry.at(i));
				}
				nModeArry.clear();
			}
		}
	}

	if(((CButton *)GetDlgItem(IDC_CHECK3))->GetCheck())
	{
		nCount = nModeArry.size();
		for (i = 0;i<nCount;i++)
		{
			InsertModeToList(&nModeArry.at(i));
		}

		nModeArry.clear();
	}

	if(((CButton *)GetDlgItem(IDC_CHECK4))->GetCheck())
	{
		nCount = nModeArry.size();
		for (i = 0;i<nCount;i++)
		{
			InsertModeToList(&nModeArry.at(i));
		}

		nModeArry.clear();
	}

	
	
	
}
void CReportMode::OnBnClickedShowBtn()
{
	InitReportModeList();
}

void CReportMode::AutoSize()
{
	CRect Rect ;
	GetClientRect(&Rect) ;

	if(GetDlgItem(IDC_REPORT_MODE_STATIC1)->GetSafeHwnd())
	{
		GetDlgItem(IDC_REPORT_MODE_STATIC1)->MoveWindow(3,3,Rect.Width()-6,100);
	}
	if(m_ReportModeList.GetSafeHwnd())
	{
		m_ReportModeList.MoveWindow(3,113,Rect.Width()-6,Rect.Height()-(123+50));
	}


	if(GetDlgItem(IDCANCEL)->GetSafeHwnd())
	{
		GetDlgItem(IDCANCEL)->MoveWindow(Rect.right-100,Rect.bottom-40,80,30);
	}

}

void CReportMode::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	AutoSize();
}

void CReportMode::OnUpdateChart(UINT nID)
{
	if (nID>=IDC_CHECK1 &&nID <= IDC_CHECK4)
	{
		CButton * pButt= (CButton*)GetDlgItem(nID) ;
		if (pButt!=NULL)
		{
			//pButt->SetCheck(pButt->GetCheck()) ;
			InitReportModeList();
		}
		
	}
}

COLORREF CReportMode::ModeFileIsExists(CString szFilePath, int Index)//检查当前报告模板是否存在//
{
	if(GetFileAttributes(szFilePath.GetBuffer(0)) == 0xFFFFFFFF)
	{
		m_ReportModeList.SetItemText(Index,4,_T("不存在"));
		return DEF_COL_RRED;
	}
	m_ReportModeList.SetItemText(Index,4,_T("存在"));
	return DEF_COL_BLUE;
}

//CString CReportMode::BuildFilePath(StBasMode *pModeInfo)//组建模板路径//
//{
//	CString strFilePath,strFilePath1,strFilePath2;
//	strFilePath1.Format(_T("%s\\%s"),g_WorkPath,Report_Mode_Path);
//	if(GetFileAttributes(strFilePath1.GetBuffer(0)) == 0xFFFFFFFF)
//	{
//		CreateDirectory(strFilePath1.GetBuffer(0),NULL);
//	}
//
//	strFilePath2.Format(_T("%s\\%s"),strFilePath1,g_CurSelDepart.szGroupName);
//	if(GetFileAttributes(strFilePath2.GetBuffer(0)) == 0xFFFFFFFF)
//	{
//		CreateDirectory(strFilePath2.GetBuffer(0),NULL);
//	}
//
//	switch(pModeInfo->nModeType)
//	{
//	case Mode_Currency:
//		{
//			strFilePath1.Format(_T("%s\\%s"),strFilePath2,g_ModeType[pModeInfo->nModeType]);
//			if(GetFileAttributes(strFilePath1.GetBuffer(0)) == 0xFFFFFFFF)
//			{
//				CreateDirectory(strFilePath1.GetBuffer(0),NULL);
//			}
//			strFilePath2.Format(_T("%s\\%s%s"),strFilePath1,pModeInfo->szModeName,Mode_FILE_EX);
//			strFilePath = strFilePath2;
//		}
//		break;
//	case Mode_Dedicated:
//		{
//			strFilePath1.Format(_T("%s\\%s"),strFilePath2,g_ModeType[pModeInfo->nModeType]);
//			if(GetFileAttributes(strFilePath1.GetBuffer(0)) == 0xFFFFFFFF)
//			{
//				CreateDirectory(strFilePath1.GetBuffer(0),NULL);
//			}
//
//			strFilePath2.Format(_T("%s\\%s"),strFilePath1,pModeInfo->szProductNo);
//			if(GetFileAttributes(strFilePath2.GetBuffer(0)) == 0xFFFFFFFF)
//			{
//				CreateDirectory(strFilePath2.GetBuffer(0),NULL);
//			}
//
//			strFilePath1.Format(_T("%s\\%s%s"),strFilePath2,pModeInfo->szModeName,Mode_FILE_EX);
//			strFilePath = strFilePath1;
//			
//
//		}
//		break;
//	case Mode_LineDed:
//		{
//			strFilePath1.Format(_T("%s\\%s"),strFilePath2,g_ModeType[pModeInfo->nModeType]);
//			if(GetFileAttributes(strFilePath1.GetBuffer(0)) == 0xFFFFFFFF)
//			{
//				CreateDirectory(strFilePath1.GetBuffer(0),NULL);
//			}
//			strFilePath2.Format(_T("%s\\%s%s"),strFilePath1,pModeInfo->szModeName,Mode_FILE_EX);
//			strFilePath = strFilePath2;
//		}
//		break;
//	case Mode_NotUse:
//		{
//			strFilePath1.Format(_T("%s\\%s"),strFilePath2,g_ModeType[pModeInfo->nModeType]);
//			if(GetFileAttributes(strFilePath1.GetBuffer(0)) == 0xFFFFFFFF)
//			{
//				CreateDirectory(strFilePath1.GetBuffer(0),NULL);
//			}
//			strFilePath2.Format(_T("%s\\%s%s"),strFilePath1,pModeInfo->szModeName,Mode_FILE_EX);
//			strFilePath = strFilePath2;
//		}
//		break;
//	default:
//		break;
//	}
//	
//	return strFilePath;
//}
void CReportMode::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == 2)
	{
		Refurbish();
	}
	CDialog::OnTimer(nIDEvent);
}

void CReportMode::Refurbish()//刷新状态//
{
	int i,nCount = m_ReportModeList.GetItemCount();
	CString strFilePath;
	for(i = 0;i<nCount;i++)
	{
		strFilePath = m_ReportModeList.GetItemText(i,5);
		m_ReportModeList.SetItemColor(i,5,ModeFileIsExists(strFilePath,i));
	}
	m_ReportModeList.Invalidate(FALSE);

}

void CReportMode::LoadInModeFile()//导入模板文件//
{
	CString strDecFilePath = m_CurFilePath;
	CString	strSrcFilePath;
	CString strText;
	CFileDialog *lpszOpenFile;    //定义一个CfileDialog对象

	if(m_ShowType == Report_Mode)
	{
		strText.Format(_T("文件类型(Word文件 *.doc)|*.doc||"));
	}else
	{
		strText.Format(_T("文件类型(Excel文件 *.xls,*.xlsx;)|*.xls;*.xlsx||"));
	}
	
	lpszOpenFile = new CFileDialog(TRUE,"","",OFN_FILEMUSTEXIST |OFN_HIDEREADONLY , strText);//生成一个对话框
	if(lpszOpenFile->DoModal() == IDOK)//假如点击对话框确定按钮
	{
		
		strSrcFilePath = lpszOpenFile->GetPathName();	//得到打开文件的路径

		CopyFile(strSrcFilePath, strDecFilePath.GetBuffer(0),  0);
	}

	delete lpszOpenFile;	//释放分配的对话框



}
void CReportMode::OpenFileDir()//打开文件所在文件夹//
{
	CString strDecFilePath = m_CurFilePath;
	CString str, str2;
	int pos = 0;
	int nLen = 0,nRet=0, nRet2=0;

	//1.存在就打开文件并选中， 不存在就打开所在文件夹//
	if(GetFileAttributes(strDecFilePath.GetBuffer(0)) == 0xffffffff)
	{
		while((pos = strDecFilePath.Find('\\')) >=0)
		{
			str+=strDecFilePath.Left(pos+1);
			strDecFilePath = strDecFilePath.Right(strDecFilePath.GetLength()-pos-1);
		}

		nLen = str.GetLength();
		if (nLen > 0)
		{
			str = str.Left(nLen-1);
		}

		nRet = GetFileAttributes(str.GetBuffer(0));
		if(GetFileAttributes(str.GetBuffer(0)) == 0xFFFFFFFF)
		{
			return;
		}
		//ShellExecute(NULL,_T("explore"),str,NULL,NULL,SW_SHOWNORMAL);
		ShellExecute(NULL,_T("open"),_T("explorer.exe"),str,NULL,SW_SHOWNORMAL);
	}else
	{
		str.Format(_T("/select,%s"), strDecFilePath);
		//ShellExecute(NULL,_T("explore"),strText,NULL,NULL,SW_SHOWNORMAL);
		ShellExecute(NULL,_T("open"),_T("explorer.exe"),str,NULL,SW_SHOWNORMAL);
	}
	
}

void  CReportMode::InitPopMenu1( )					//初始化菜单1
{
	if(!m_PopupMenu1.GetSafeHmenu())
	{
		m_PopupMenu1.CreatePopupMenu();

		m_PopupMenu1.AppendMenu(MF_STRING, ID_MENU1_LOADIN,		"导入模板文件");
		m_PopupMenu1.AppendMenu(MF_STRING, ID_MENU2_OPENDIR,		"打开所在文件夹");

	}
}

void CReportMode::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	int Index = m_ReportModeList.GetFirstSelectedItem(),
		nCount = m_ReportModeList.GetItemCount();
	if(Index <0 || Index >= nCount)
	{
		return;
	}

	POINT	point;
	GetCursorPos(&point);
	CString strFilePath = m_CurFilePath = m_ReportModeList.GetItemText(Index,5);

	m_PopupMenu1.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
	*pResult = 0;
}
