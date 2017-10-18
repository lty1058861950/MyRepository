// TaskUpLoad.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "TaskUpLoad.h"
#include "TaskDownUpLoad.h"

// CTaskUpLoad 对话框

IMPLEMENT_DYNAMIC(CTaskUpLoad, CDialog)

CTaskUpLoad::CTaskUpLoad(CWnd* pParent /*=NULL*/)
	: CDialog(CTaskUpLoad::IDD, pParent)
{
	m_pTaskDownUpLoad = NULL;
}

CTaskUpLoad::~CTaskUpLoad()
{
}

void CTaskUpLoad::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ResultList);
}


BEGIN_MESSAGE_MAP(CTaskUpLoad, CDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, &CTaskUpLoad::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTaskUpLoad::OnBnClickedButton2)
END_MESSAGE_MAP()


// CTaskUpLoad 消息处理程序

BOOL CTaskUpLoad::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	GetDlgItem(IDC_STATIC3)->GetWindowRect(&m_rcRect1);
	ScreenToClient(&m_rcRect1);

	GetDlgItem(IDC_STATIC10)->GetWindowRect(&m_rcRect2);
	ScreenToClient(&m_rcRect2);

	GetDlgItem(IDC_EDIT1)->GetWindowRect(&m_rcRect3);
	ScreenToClient(&m_rcRect3);

	GetDlgItem(IDC_BUTTON1)->GetWindowRect(&m_rcRect4);
	ScreenToClient(&m_rcRect4);

	GetDlgItem(IDC_BUTTON2)->GetWindowRect(&m_rcRect5);
	ScreenToClient(&m_rcRect5);

	CString strText;
	int nPadID = g_LoginUsrInfo.nPadDevID;
	CString strUserName = g_LoginUsrInfo.szUserName;
	strText.Format(_T("检验员姓名: %s    PAD设备号: %d "), strUserName, nPadID);
	GetDlgItem(IDC_STATIC10)->SetWindowText(strText);

	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CTaskUpLoad::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}

void CTaskUpLoad::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	AutoSize();
}

void CTaskUpLoad::AutoSize()
{
	CRect Rect ;
	GetClientRect(&Rect);

	int nBtnWidth = 80;
	int nBtnHeight = 25;
	int nStaticHeight1 = 100;

	int nStaticWidth = 50;
	int nStaticHeight = 20;



	//产品模块//
	if(GetDlgItem(IDC_STATIC1)->GetSafeHwnd())
	{
		GetDlgItem(IDC_STATIC1)->MoveWindow(0,5,Rect.Width()-(0*2),nStaticHeight1);
	}

	if(GetDlgItem(IDC_STATIC2)->GetSafeHwnd())
	{
		GetDlgItem(IDC_STATIC2)->MoveWindow(0,(5+nStaticHeight1+10),Rect.Width()-(0*2),Rect.Height()-(5*2+nStaticHeight1+10));
	}


	if(GetDlgItem(IDC_STATIC3)->GetSafeHwnd())
	{
		GetDlgItem(IDC_STATIC3)->MoveWindow(m_rcRect1);
	}
	if(GetDlgItem(IDC_EDIT1)->GetSafeHwnd())
	{
		GetDlgItem(IDC_EDIT1)->MoveWindow(m_rcRect1.right+2,m_rcRect3.top,Rect.Width()-(m_rcRect1.right+2+(nBtnWidth+10)*2),nBtnHeight);
	}
	if(GetDlgItem(IDC_BUTTON1)->GetSafeHwnd())
	{
		GetDlgItem(IDC_BUTTON1)->MoveWindow(Rect.right-((nBtnWidth+10)*2),m_rcRect4.top,nBtnWidth,nBtnHeight);
	}
	if(GetDlgItem(IDC_BUTTON2)->GetSafeHwnd())
	{
		GetDlgItem(IDC_BUTTON2)->MoveWindow(Rect.right-((nBtnWidth+10)*1),m_rcRect5.top,nBtnWidth,nBtnHeight);
	}

	if(GetDlgItem(IDC_STATIC10)->GetSafeHwnd())
	{
		GetDlgItem(IDC_STATIC10)->MoveWindow(10,m_rcRect2.top,Rect.Width()-(10*2),nStaticHeight);
	}



	if(m_ResultList.GetSafeHwnd())
	{
		m_ResultList.MoveWindow(5,(5+nStaticHeight1+10+20),Rect.Width()-(5*2),Rect.Height()-(5*2+nStaticHeight1+10+20*1+5));
	}

}

//选择路径//
void CTaskUpLoad::OnBnClickedButton1()
{
	
	CFileDialog *lpszOpenFile;    //定义一个CfileDialog对象
	lpszOpenFile = new CFileDialog(TRUE,"","",OFN_FILEMUSTEXIST |OFN_HIDEREADONLY , "文件类型(*.data)|*.data||");//生成一个对话框
	if(lpszOpenFile->DoModal() == IDOK)//假如点击对话框确定按钮
	{
		m_strCurTaskDataPath = lpszOpenFile->GetPathName();	//得到打开文件的路径
		m_strDecFileName = lpszOpenFile->GetFileName();
		GetDlgItem(IDC_EDIT1)->SetWindowText(m_strCurTaskDataPath);

		m_strCurTaskDataPath = m_strCurTaskDataPath.Left(m_strCurTaskDataPath.GetLength()-m_strDecFileName.GetLength());
	}

	delete lpszOpenFile;	//释放分配的对话框
	// TODO: 在此添加控件通知处理程序代码
	/*CPathDialog dlg(_T("路径"),_T("路径"),strDefFilePath,NULL);
	if(dlg.DoModal()==IDOK)
	{
		strDefFilePath = dlg.GetPathName();
		GetDlgItem(IDC_EDIT1)->SetWindowText(strDefFilePath);
	
	}else
	{
		return ;
	}*/

}

//获取结果数据//
void CTaskUpLoad::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码//
	CString strMulTaskFile;
	CString strText;
	GetDlgItem(IDC_EDIT1)->GetWindowText(strMulTaskFile);
	strMulTaskFile = strMulTaskFile.TrimLeft();
	strMulTaskFile = strMulTaskFile.TrimRight();

	if(strMulTaskFile.IsEmpty())
	{
		return;
	}
	if(GetFileAttributes(strMulTaskFile.GetBuffer(0)) == 0xffffffff)
	{
		strText.Format(_T("文件=%s  不存在!"), strMulTaskFile);
		AfxMessageBox(strText);
		return;
	}

	LoadOutTaskXmlAnalysis   nDataImport;
	vector<StBasTask *> *pTaskDataArray = &m_pTaskDownUpLoad->m_BatchImportData.m_BatchTaskDataArray;
	vector<CString >    *pDataFilePath = &m_pTaskDownUpLoad->m_BatchImportData.m_TaskDataFilePath;
	StHrUser  *pCheckUserInfo = &m_pTaskDownUpLoad->m_BatchImportData.m_CheckUserInfo;
	
	memset(pCheckUserInfo, 0,sizeof(StHrUser));
	int i, nCount;
	nCount = pTaskDataArray->size();
	for (i = 0;i<nCount;i++)
	{
		pTaskDataArray->at(i)->Release();
		delete pTaskDataArray->at(i);
	}
	pTaskDataArray->clear();
	

	nDataImport.GetBatchOutTask(strMulTaskFile, pCheckUserInfo, pTaskDataArray);

	
	nCount = pTaskDataArray->size();

	for (i = 0;i<nCount;i++)
	{
		m_pTaskDownUpLoad->InsertTaskDataToList(pTaskDataArray->at(i));
		strText.Format(_T("%s%s\\%s"), m_strCurTaskDataPath, pTaskDataArray->at(i)->stTaskBaseInfo.szFoldName,
			pTaskDataArray->at(i)->stTaskBaseInfo.szFileName);
		pDataFilePath->push_back(strText);
		
	}
	
}
