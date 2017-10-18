// TaskDownUpLoad.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataManage.h"
#include "TaskDownUpLoad.h"
#include "BatchExportTask.h"


// CTaskDownUpLoad �Ի���

IMPLEMENT_DYNAMIC(CTaskDownUpLoad, CDialog)

CTaskDownUpLoad::CTaskDownUpLoad(CWnd* pParent /*=NULL*/)
	: CDialog(CTaskDownUpLoad::IDD, pParent)
{
	m_TaskSearchInfo.Release();
	m_ShowType = Task_DownLoad;
}

CTaskDownUpLoad::~CTaskDownUpLoad()
{
	m_TaskSearchInfo.Release();
}

void CTaskDownUpLoad::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTaskDownUpLoad, CDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, &CTaskDownUpLoad::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON5, &CTaskDownUpLoad::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON2, &CTaskDownUpLoad::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTaskDownUpLoad::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTaskDownUpLoad::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &CTaskDownUpLoad::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CTaskDownUpLoad::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CTaskDownUpLoad::OnBnClickedButton8)
END_MESSAGE_MAP()


// CTaskDownUpLoad ��Ϣ�������

BOOL CTaskDownUpLoad::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	
	m_TaskDownLoadAll.Create(IDD_TASK_DOWNALL_DLG, this);
	m_TaskDownLoadSel.Create(IDD_TASK_DOWNSEL_DLG, this);
	m_TaskUpLoad.Create(IDD_TASK_UPLOAD_DLG, this);//����ϴ�//
	m_TaskUpLoad.m_pTaskDownUpLoad = this;
	
	CString strText;

	if(m_ShowType == Task_DownLoad)
	{
		m_TaskDownLoadAll.ShowWindow(SW_SHOW);
		m_TaskDownLoadSel.ShowWindow(SW_SHOW);
		strText.Format(_T("C:\\OutTask\\%s"),GetDateString());
		GetDlgItem(IDC_EDIT1)->SetWindowText(strText);

		GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON6)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON7)->ShowWindow(SW_HIDE);

		strText.Format(_T("��������"));
		this->SetWindowText(strText);
		m_TaskUpLoad.ShowWindow(SW_HIDE);
	}else
	{
		m_TaskDownLoadAll.ShowWindow(SW_HIDE);
		m_TaskDownLoadSel.ShowWindow(SW_HIDE);

		GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON8)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_HIDE);


		GetDlgItem(IDC_BUTTON6)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON7)->ShowWindow(SW_SHOW);

		strText.Format(_T("����ϴ�"));
		this->SetWindowText(strText);
		m_TaskUpLoad.ShowWindow(SW_SHOW);
	}

	m_TaskSearchInfo.stTaskBaseInfo.bTaskOk = Sel_Check;
	m_TaskSearchInfo.stTaskBaseInfo.nArmyTest = Army_All;
	strcpy(m_TaskSearchInfo.stTaskBaseInfo.szCheckUser, g_LoginUsrInfo.szUserName); 
	
	MoveWindow(0, 0, 1124, 600);
	CenterWindow();
	DisPlayTaskInfo(&m_TaskSearchInfo);
	DisPlayResultList();
	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CTaskDownUpLoad::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialog::OnOK();
}

void CTaskDownUpLoad::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	AutoSize();
}

void CTaskDownUpLoad::AutoSize()
{
	CRect Rect ;
	GetClientRect(&Rect);

	int nBtnWidth = 80;
	int nBtnHeight = 30;
	int nBtnListHeight = (Rect.Height()/2)-20;


	if(m_TaskDownLoadAll.GetSafeHwnd())
	{
		m_TaskDownLoadAll.MoveWindow(3,5,Rect.Width()-(3*2),
			nBtnListHeight);
	}

	if(GetDlgItem(IDC_BUTTON1)->GetSafeHwnd())
	{
		GetDlgItem(IDC_BUTTON1)->MoveWindow(Rect.right-(10+(nBtnWidth+10)*4),nBtnListHeight+10,nBtnWidth,nBtnHeight);
	}

	if(GetDlgItem(IDC_BUTTON2)->GetSafeHwnd())
	{
		GetDlgItem(IDC_BUTTON2)->MoveWindow(Rect.right-(10+(nBtnWidth+10)*3),nBtnListHeight+10,nBtnWidth,nBtnHeight);
	}
	if(GetDlgItem(IDC_BUTTON3)->GetSafeHwnd())
	{
		GetDlgItem(IDC_BUTTON3)->MoveWindow(Rect.right-(10+(nBtnWidth+10)*2),nBtnListHeight+10,nBtnWidth,nBtnHeight);
	}
	if(GetDlgItem(IDC_BUTTON4)->GetSafeHwnd())
	{
		GetDlgItem(IDC_BUTTON4)->MoveWindow(Rect.right-(10+(nBtnWidth+10)*1),nBtnListHeight+10,nBtnWidth,nBtnHeight);
	}


	if(m_TaskDownLoadSel.GetSafeHwnd())
	{
		m_TaskDownLoadSel.MoveWindow(3,nBtnListHeight+15+(nBtnHeight),Rect.Width()-(3*2),
			nBtnListHeight-(50));
	}

	
	if(GetDlgItem(IDC_STATIC1)->GetSafeHwnd())
	{
		GetDlgItem(IDC_STATIC1)->MoveWindow(20,Rect.bottom-(nBtnHeight),nBtnWidth,nBtnHeight);
	}

	if(GetDlgItem(IDC_EDIT1)->GetSafeHwnd())
	{
		GetDlgItem(IDC_EDIT1)->MoveWindow((20+(nBtnWidth+10)*1),Rect.bottom-(nBtnHeight+5),Rect.Width()-(20+10+(nBtnWidth+10)*4),nBtnHeight-5);
	}
	if(GetDlgItem(IDC_BUTTON8)->GetSafeHwnd())
	{
		GetDlgItem(IDC_BUTTON8)->MoveWindow(Rect.right-(10+(nBtnWidth+10)*3),Rect.bottom-(nBtnHeight+10),nBtnWidth,nBtnHeight);
	}

	if(GetDlgItem(IDC_BUTTON5)->GetSafeHwnd())
	{
		GetDlgItem(IDC_BUTTON5)->MoveWindow(Rect.right-(10+(nBtnWidth+10)*2),Rect.bottom-(nBtnHeight+10),nBtnWidth,nBtnHeight);
	}

	if(m_TaskUpLoad.GetSafeHwnd())
	{
		m_TaskUpLoad.MoveWindow(3,5,Rect.Width()-(3*2),
			Rect.Height()-(5*2+40));
	}
	if(GetDlgItem(IDCANCEL)->GetSafeHwnd())
	{
		GetDlgItem(IDCANCEL)->MoveWindow(Rect.right-(10+(nBtnWidth+10)*1),Rect.bottom-(nBtnHeight+10),nBtnWidth,nBtnHeight);
	}

	if(GetDlgItem(IDC_BUTTON6)->GetSafeHwnd())
	{
		GetDlgItem(IDC_BUTTON6)->MoveWindow(Rect.right-(10+(nBtnWidth+10)*3),Rect.bottom-(nBtnHeight+10),nBtnWidth,nBtnHeight);
	}

	if(GetDlgItem(IDC_BUTTON7)->GetSafeHwnd())
	{
		GetDlgItem(IDC_BUTTON7)->MoveWindow(Rect.right-(10+(nBtnWidth+10)*2),Rect.bottom-(nBtnHeight+10),nBtnWidth,nBtnHeight);
	}

}

void CTaskDownUpLoad::InsertOneTaskToList(StBasTask *pBasTaskInfo)
{

	CEditableListCtrl *pList1 = &m_TaskDownLoadAll.m_TaskDownLoadList;
	CEditableListCtrl *pList2 = &m_TaskDownLoadSel.m_TaskDownLoadSelList;
	CString strNum, strText;
	int nCur,pos,nCount = 0;

	nCount = pList1->GetItemCount();
	strNum.Format(_T("%d"),nCount+1);
	nCur = pList1->InsertItem(nCount,strNum);

	/*"���", 
		"����״̬",	"��������",	"��Ʒ����",	_T("��Ʒ���κ�"),
		"�ͺ�",		"�׶�",		"�����鳤",		"����Ա",
		"���첿��",	"����ʱ��",	"������",		"�ɹ�ʱ��",
		"ִ��ʱ��",	"���ʱ��",};*/

	pos = 1;
	pList1->SetItemData(nCur,pBasTaskInfo->stTaskBaseInfo.nOid);

	strText.Format(_T("%s"), GetTaskStatus(pBasTaskInfo->stTaskBaseInfo.nTaskStatus));
	pList1->SetItemText(nCur,pos++,strText);//
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szTaskName);
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stProductInfo.szProductNo);
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szBatch);

	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szModel);
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szPhase);
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szCheckLeader);
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szCheckUser);
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stHrUpDepart.szUpDepartName);
	
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szCreateDate);
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szCreateUser);
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szSendDate);
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szDownLoadDate);
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szFinishDate);
	
}

void CTaskDownUpLoad::DisPlayTaskInfo(StBasTask *pStBasTaskSearchInfo)
{
	CEditableListCtrl *pList1 = &m_TaskDownLoadAll.m_TaskDownLoadList;
	CEditableListCtrl *pList2 = &m_TaskDownLoadSel.m_TaskDownLoadSelList;

	int     i;
	CString	str;
	int     iColNum; 

	char	ItemName[35][30] = {
		"���", 
		"����״̬",	"��������",	"��Ʒ����",	_T("��Ʒ���κ�"),
		"�ͺ�",		"�׶�",		"�����鳤",		"����Ա",
		"���첿��",	"����ʱ��",	"������",		"�ɹ�ʱ��",
		"ִ��ʱ��",	"���ʱ��",};
		int     ItemLen[40]      = {
			50,
			60,		100,	80,		80, 
			80,		80,		80,		80,
			100,	120,	80,		120,   
			120,	120};

	
	iColNum = 15;

	for (i=0; i<iColNum; i++)
	{
		str.Format("%s", ItemName[i]);
		pList1->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen[i]);	
		pList2->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen[i]);	
	}

	int nRows = 0;
	char szSQL[1024] = {0};

	UINT nGroupOid = pStBasTaskSearchInfo->stHrGroup.nOid = g_CurSelDepart.nOid;
	UINT nProductOid = pStBasTaskSearchInfo->stProductInfo.nOid;
	int  nTaskStatus = pStBasTaskSearchInfo->stTaskBaseInfo.nTaskStatus;
	int  nTreeItemType = pStBasTaskSearchInfo->stTaskBaseInfo.TreeItemType;

	if(nGroupOid == 0)
	{
		return;
	}else 
	{
		int     i,nCount = 0;
		vector<StBasTask > nArrayTask;
		if(m_DMng.GetGroupTaskInfo (nGroupOid,pStBasTaskSearchInfo,&nArrayTask))
		{
			nCount = nArrayTask.size();
			for(i = 0;i<nCount;i++)
			{
				InsertOneTaskToList(&nArrayTask.at(i));
			}

			nArrayTask.clear();
		}
	}

	//��ʾ�����Ϣ//
	CString strText;
	StBasTaskBaseInfo *pTaskBaseInfo = &pStBasTaskSearchInfo->stTaskBaseInfo;
	int nPerPageNum = pTaskBaseInfo->nPerPageNum;
	int nResultNum = pTaskBaseInfo->nResultNum;
	int nCurPage = pTaskBaseInfo->nCurPage;
	int nPageNum = 1;

	if(nPerPageNum == g_nSearchPerPageNum[All_Result])
	{

	}else
	{
		if( nResultNum%nPerPageNum >0)
		{
			nPageNum = (nResultNum/nPerPageNum)+1;
		}else
		{
			nPerPageNum = nResultNum/nPerPageNum;
		}
	}

	strText.Format(_T("���ɹ�������Ϣ:�������� %d ������"), pTaskBaseInfo->nResultNum);
	m_TaskDownLoadAll.GetDlgItem(IDC_STATIC1)->SetWindowText(strText);
	//strText.Format(_T("%d/%d"),nCurPage , nPageNum);
	//m_ResultList.GetDlgItem(IDC_LIST_STATIC2)->SetWindowText(strText);

}

BOOL CTaskDownUpLoad::CheckItemSame(UINT OID)//����Ƿ�������һ����//
{
	CEditableListCtrl *pList2 = &m_TaskDownLoadSel.m_TaskDownLoadSelList;
	int i,nCount = pList2->GetItemCount();

	for (i = 0;i<nCount;i++)
	{
		if(OID == pList2->GetItemData(i))
		{
			break;
		}
	}
	if(i>=nCount)
	{
		return TRUE;//û��//
	}
	return FALSE;//��//
}

//ȫ�����//
void CTaskDownUpLoad::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CEditableListCtrl *pList1 = &m_TaskDownLoadAll.m_TaskDownLoadList;
	CEditableListCtrl *pList2 = &m_TaskDownLoadSel.m_TaskDownLoadSelList;
	int		i, j, nCount,nColCnt;
	int     Index;
	UINT    OID;
	CString strNum;

	nCount = pList1->GetItemCount();
	nColCnt = pList1->GetHeaderCtrl()->GetItemCount();
	for (i = 0;i<nCount;i++)
	{
		OID = pList1->GetItemData(i);
		if(!CheckItemSame(OID))
		{
			continue;
		}
		Index = pList2->GetItemCount();
		strNum.Format("%d",Index+1);
		pList2->InsertItem(Index,strNum);
		pList2->SetItemData(Index,OID);
		for (j=1; j<=nColCnt; j++)
		{
			pList2->SetItemText(Index,j,pList1->GetItemText(i,j));
		}
	}
}

//���һ��//

void CTaskDownUpLoad::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CEditableListCtrl *pList1 = &m_TaskDownLoadAll.m_TaskDownLoadList;
	CEditableListCtrl *pList2 = &m_TaskDownLoadSel.m_TaskDownLoadSelList;

	int		j, nSel,nCount,nColCnt;
	int     Index;
	UINT    OID;
	CString strNum;

	nSel = pList1->GetFirstSelectedItem();
	nCount = pList1->GetItemCount();
	nColCnt = pList1->GetHeaderCtrl()->GetItemCount();
	if(nSel < 0 || nSel >= nCount)
	{
		AfxMessageBox(_T("��ѡ����ߵ�һ��!"));
		return;
	}

	OID = pList1->GetItemData(nSel);
	if(!CheckItemSame(OID))
	{
		return;
	}
	Index = pList2->GetItemCount();
	strNum.Format("%d",Index+1);
	pList2->InsertItem(Index,strNum);
	pList2->SetItemData(Index,OID);
	for (j=1; j<=nColCnt; j++)
	{
		pList2->SetItemText(Index,j,pList1->GetItemText(nSel,j));
	}
}
//ɾ��һ��//
void CTaskDownUpLoad::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CEditableListCtrl *pList2 = &m_TaskDownLoadSel.m_TaskDownLoadSelList;
	int		nSel;
	while(1)
	{
		nSel = pList2->GetFirstSelectedItem();
		if(nSel < 0)
		{
			break;
		}
		pList2->DeleteItem(nSel);
	}
}

//ȫ��ɾ��//
void CTaskDownUpLoad::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CEditableListCtrl *pList2 =  &m_TaskDownLoadSel.m_TaskDownLoadSelList;
	pList2->DeleteAllItems();
}

//��������//
void CTaskDownUpLoad::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������//
	CEditableListCtrl *pList2 =  &m_TaskDownLoadSel.m_TaskDownLoadSelList;
	CBatchExportTask m_BatchOutTask;

	CString strText, str1, str2;
	int  nErrorNum = 0;
	int i;
	int nCount=pList2->GetItemCount();
	UINT nID;

	//1.��ȡ��Ϣ�����//
	for (i = 0;i<nCount;i++)
	{
		StBasTask  *pTaskInfo = new StBasTask;
		pTaskInfo->Release();
		nID = pList2->GetItemData(i);
		if(m_DMng.GetTaskDataOid(nID,pTaskInfo))
		{
			if(m_DMng.GetProdDataOid(pTaskInfo->stProductInfo.nOid,
				&pTaskInfo->stProductInfo))
			{

				if(m_DMng.GetTaskCodeData(pTaskInfo,pTaskInfo->stTaskBaseInfo.nOid))
				{

				}

				if(m_DMng.GetTaskModeData(pTaskInfo,pTaskInfo->stTaskBaseInfo.nOid))
				{

				}

				if(m_DMng.GetTaskPicNumData(pTaskInfo,pTaskInfo->stTaskBaseInfo.nOid))
				{

				}
			}

		}

		
		if(CheckTheTask(pTaskInfo,str1))
		{
			str1.Format(_T("����=%s ���ͨ��!\n"), pTaskInfo->stTaskBaseInfo.szTaskName);
			strText+=str1;
			strText+=_T("\n");
			m_BatchOutTask.m_BatchTaskArray.push_back(pTaskInfo);
		}else
		{
			str2.Format(_T("����=%s ���ʧ��!\n"), pTaskInfo->stTaskBaseInfo.szTaskName);
			str2+=str1;
			strText+=str2;
			strText+=_T("\n");

			nErrorNum++;
			pTaskInfo->Release();
			delete pTaskInfo;
			pTaskInfo = NULL;
		}
		
	}

	if(nErrorNum >= 1)
	{
		if(MessageBox(strText,_T("��ʾ"),MB_OKCANCEL|MB_ICONQUESTION) != IDOK)
		{
			return ;
		}
	}


	//2.���Ŀ¼  �������Զ�����//
	GetDlgItem(IDC_EDIT1)->GetWindowText(strText);
	strText = strText.TrimLeft();
	strText = strText.TrimRight();

	int pos = 0;
	pos = strText.Find('\\');
	str2 = _T("");
	if(pos > 0)
	{
		str1 = strText.Left(pos);
		strText = strText.Right(strText.GetLength()-(pos+1));
		str2=str1;
	}
	while((pos = strText.Find('\\')) > 0)
	{
		str1 = strText.Left(pos);
		strText = strText.Right(strText.GetLength()-(pos+1));
		str2+=(_T("\\")+str1);

		if(GetFileAttributes(str2.GetBuffer(0)) == 0xffffffff)
		{
			CreateDirectory(str2.GetBuffer(0), NULL);
		}
	}
	if(!strText.IsEmpty())
	{
		str2+=(_T("\\")+strText);

		if(GetFileAttributes(str2.GetBuffer(0)) == 0xffffffff)
		{
			CreateDirectory(str2.GetBuffer(0), NULL);
		}
	}

	//3.��ʼ�����·�����//
	if(nCount>0)
	{
		m_BatchOutTask.BatchSendTask(str2);
	}else
	{
		return;
	}

	for (i = 0;i<nCount;i++)
	{
		m_BatchOutTask.m_BatchTaskArray.at(i)->Release();
		delete m_BatchOutTask.m_BatchTaskArray.at(i);
	}

}

void CTaskDownUpLoad::InsertTaskDataToList(StBasTask *pBasTaskInfo)
{

	CEditableListCtrl *pList1 = &m_TaskUpLoad.m_ResultList;
	CString strNum, strText;
	int nCur,pos,nCount = 0;

	char	ItemName[20][30] = {
		"���", "��������","��Ʒ����","��Ʒ���κ�","�������",
		"��Ʒ����","�ͺ�", "�׶�","���첿��","�����鳤",
		"����Ա����","����ʱ��","������","�ɹ�ʱ��","ִ��ʱ��",
		"�������ʱ��"};

	nCount = pList1->GetItemCount();
	strNum.Format(_T("%d"),nCount+1);
	nCur = pList1->InsertItem(nCount,strNum);

	pos = 1;
	pList1->SetItemData(nCur,pBasTaskInfo->stTaskBaseInfo.nOid);
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szTaskName);

	//strText.Format(_T("%s"), GetTaskStatus(pBasTaskInfo->stTaskBaseInfo.nTaskStatus));
	//pList1->SetItemText(nCur,pos++,strText);//
	//strText.Format(_T("%s"), GetTaskType(pBasTaskInfo->stTaskBaseInfo.nTaskType));
//	pList1->SetItemText(nCur,pos++,strText);//

	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stProductInfo.szProductNo);
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szBatch);
	strText.Format(_T("%d"),pBasTaskInfo->stTaskBaseInfo.nCodeNumber);
	pList1->SetItemText(nCur,pos++,strText);

	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stProductInfo.szProductName);
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szModel);
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szPhase);
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stHrUpDepart.szUpDepartName);
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szCheckLeader);


	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szCheckUser);
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szCreateDate);
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szCreateUser);
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szSendDate);
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szDownLoadDate);
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szFinishDate);
	

	/*
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szProductCode);
	
	
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szGroupName);
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szUpUser);
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szUpDate);
	
	
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szTechUser);

	strText.Format(_T("%s"),GetTaskArmyText(pBasTaskInfo->stTaskBaseInfo.nArmyTest));//
	pList1->SetItemText(nCur,pos++,strText);

	strText.Format(_T("%d"),pBasTaskInfo->stTaskBaseInfo.nDianShiNum);
	pList1->SetItemText(nCur,pos++,strText);

	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szAccording1);
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szAccording2);
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szAccording3);
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szAccording4);
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szAccording5);
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szTaskRemark);
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szPlanBegTime);
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szPlanEndTime);
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szRealBegTime);
	pList1->SetItemText(nCur,pos++,pBasTaskInfo->stTaskBaseInfo.szRealEndTime);
*/
}


void CTaskDownUpLoad::DisPlayResultList()
{
	CEditableListCtrl *pList1 = &m_TaskUpLoad.m_ResultList;

	int     i;
	CString	str;
	int     iColNum; 

	char	ItemName[20][30] = {
	"���", "��������","��Ʒ����","��Ʒ���κ�","�������",
	"��Ʒ����","�ͺ�", "�׶�","���첿��","�����鳤",
	"����Ա����","����ʱ��","������","�ɹ�ʱ��","ִ��ʱ��",
	"�������ʱ��"};
	int     ItemLen[40]      = {50,150,150,100,100, 100,100,150,100,100, 100,150,100,100,100,
		100,100,100,100,100, 100,100,100,100,100, 100,100,100,100,100,
		100,100,100};


	iColNum = 16;

	for (i=0; i<iColNum; i++)
	{
		str.Format("%s", ItemName[i]);
		pList1->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen[i]);
	}
}

//������//
void CTaskDownUpLoad::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

//����ϴ�//
void CTaskDownUpLoad::OnBnClickedButton7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_BatchImportData.BatchTaskDataImport();
}

//����·��ѡ��//
void CTaskDownUpLoad::OnBnClickedButton8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������//

	CString strDefFilePath;
	GetDlgItem(IDC_EDIT1)->GetWindowText(strDefFilePath);
	strDefFilePath = strDefFilePath.TrimLeft();
	strDefFilePath = strDefFilePath.TrimRight();

	CPathDialog dlg(_T("·��"),_T("·��"),strDefFilePath,NULL);
	if(dlg.DoModal()==IDOK)
	{
		strDefFilePath = dlg.GetPathName();
	}else
	{
		return ;
	}

	GetDlgItem(IDC_EDIT1)->SetWindowText(strDefFilePath);

}
