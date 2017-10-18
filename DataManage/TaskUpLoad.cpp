// TaskUpLoad.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataManage.h"
#include "TaskUpLoad.h"
#include "TaskDownUpLoad.h"

// CTaskUpLoad �Ի���

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


// CTaskUpLoad ��Ϣ�������

BOOL CTaskUpLoad::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

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
	strText.Format(_T("����Ա����: %s    PAD�豸��: %d "), strUserName, nPadID);
	GetDlgItem(IDC_STATIC10)->SetWindowText(strText);

	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CTaskUpLoad::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialog::OnOK();
}

void CTaskUpLoad::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
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



	//��Ʒģ��//
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

//ѡ��·��//
void CTaskUpLoad::OnBnClickedButton1()
{
	
	CFileDialog *lpszOpenFile;    //����һ��CfileDialog����
	lpszOpenFile = new CFileDialog(TRUE,"","",OFN_FILEMUSTEXIST |OFN_HIDEREADONLY , "�ļ�����(*.data)|*.data||");//����һ���Ի���
	if(lpszOpenFile->DoModal() == IDOK)//�������Ի���ȷ����ť
	{
		m_strCurTaskDataPath = lpszOpenFile->GetPathName();	//�õ����ļ���·��
		m_strDecFileName = lpszOpenFile->GetFileName();
		GetDlgItem(IDC_EDIT1)->SetWindowText(m_strCurTaskDataPath);

		m_strCurTaskDataPath = m_strCurTaskDataPath.Left(m_strCurTaskDataPath.GetLength()-m_strDecFileName.GetLength());
	}

	delete lpszOpenFile;	//�ͷŷ���ĶԻ���
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*CPathDialog dlg(_T("·��"),_T("·��"),strDefFilePath,NULL);
	if(dlg.DoModal()==IDOK)
	{
		strDefFilePath = dlg.GetPathName();
		GetDlgItem(IDC_EDIT1)->SetWindowText(strDefFilePath);
	
	}else
	{
		return ;
	}*/

}

//��ȡ�������//
void CTaskUpLoad::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������//
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
		strText.Format(_T("�ļ�=%s  ������!"), strMulTaskFile);
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
