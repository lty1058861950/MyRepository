// ResultSearchNew.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataManage.h"
#include "ResultSearchNew.h"
#include "WordSrc\\WordOptFun.h"
#include "AdjustmentDlg.h"

// CResultSearchNew �Ի���
IMPLEMENT_DYNAMIC(CResultSearchNew, CDialog)

CResultSearchNew::CResultSearchNew(CWnd* pParent /*=NULL*/)
	: CDialog(CResultSearchNew::IDD, pParent)
{
	m_ResultSearchInfo.Release();
	m_ResultSearchInfo.stTaskBaseInfo.nResultType = Task_DarkSearch;

	memset(&m_CurSelResultAtta, 0, sizeof(StTstResultAtta));
}

CResultSearchNew::~CResultSearchNew()
{
	m_ResultSearchInfo.Release();
}

void CResultSearchNew::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_TstRresultBaseList);
	DDX_Control(pDX, IDC_LIST2, m_TstRresultAttaList);
}


BEGIN_MESSAGE_MAP(CResultSearchNew, CDialog)
	ON_WM_SIZE()
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CResultSearchNew::OnNMClickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &CResultSearchNew::OnNMDblclkList2)

	ON_COMMAND(ID_MENU1_DELDATA_BASE_NEW, &CResultSearchNew::DelBaseDataNew)


	ON_COMMAND(ID_MENU1_C_TASK_REPORT_BASE_NEW, &CResultSearchNew::CreateTaskReportNew)
	ON_COMMAND(ID_MENU1_C_PRODUCT_REPORT_ATTA_NEW, &CResultSearchNew::CreateProductCodeReportNew)
	ON_COMMAND(ID_MENU1_C_MODE_REPORT_ATTA_NEW, &CResultSearchNew::CreateModeReportNew)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CResultSearchNew::OnNMRClickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST2, &CResultSearchNew::OnNMRClickList2)
END_MESSAGE_MAP()


// CResultSearchNew ��Ϣ�������

BOOL CResultSearchNew::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_ResultSearchInfoDlg.Create(IDD_RESULT_SEARCH_INFO_DLG, this);
	m_ResultSearchInfoDlg.ShowWindow(SW_SHOW);

	m_ResultTaskBase.Create(IDD_RESULT_LIST_DLG, this);
	m_ResultTaskBase.ShowWindow(SW_SHOW);
	m_ResultAttach.Create(IDD_RESULT_LIST_DLG, this);
	m_ResultAttach.ShowWindow(SW_SHOW);

	m_ResultSearchInfoDlg.m_pResultSearchNew = this;
	m_ResultTaskBase.m_pResultSearchNew = this;
	m_ResultAttach.m_pResultSearchNew = this;

	InitPopMenu1( );
	InitPopMenu2( );

	InitListCtrlColumn();
	SetContrlShow();
	PostMessage(WM_SIZE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CResultSearchNew::InitListCtrlColumn()
{
	CEditableListCtrl *pList1 = &m_TstRresultBaseList;
	CEditableListCtrl *pList2 = &m_TstRresultAttaList;
	CEditableListCtrl *pList3 = &m_ResultTaskBase.m_ResultList;
	CEditableListCtrl *pList4 = &m_ResultAttach.m_ResultList;

	int     i;
	CString	str;
	int     iColNum1; 
	char	ItemName1[20][30] = {"���",_T("�·�����"),_T("��������"),_T("��������"),_T("��Ʒ����"),
		_T("��Ʒ����"),_T("�����")};
	int     ItemLen1[20]      = {50,150,150,100,100,  100,100};

	iColNum1 = 7;
	for (i=0; i<iColNum1; i++)
	{
		str.Format("%s", ItemName1[i]);
		pList1->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen1[i]);
		pList3->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen1[i]);
	}

	pList1->EnableRClickMenu(FALSE);

	int     iColNum2; 
	char	ItemName2[20][30] = {"���","�·�����","��������","��������","��Ʒ����",
		"��Ʒ���",_T("ģ������"),_T("�Ƿ����"),_T("ģ������"),_T("ģ���пɱ�"),
		_T("ͼ������"),_T("��ɽ���(�ٷֱ�)"),_T("���״̬"),_T("���ʱ��"),_T("�����")};
	int     ItemLen2[20]      = {50,150,150,100,100,   100,100,100,100,100,   100,100,100,150,100};

	iColNum2 = 15;
	for (i=0; i<iColNum2; i++)
	{
		str.Format("%s", ItemName2[i]);
		pList2->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen2[i]);
		pList4->InsertColumn(i, str,   LVCFMT_LEFT, ItemLen2[i]);
	}

	pList2->EnableRClickMenu(FALSE);


	//���б����ʾ����ҳ�ڴ˳�ʼ����//
	m_ResultTaskBase.m_ShowType = Show_Result;
	m_ResultAttach.m_ShowType = Show_Result;
}


void CResultSearchNew::InsertTaskBaseDataToList(StTstResultBaseNew *pTaskBaseData)
{
	CEditableListCtrl *pList1 = NULL;
	CString str;
	int nCount, pos;
	StBasTaskBaseInfo *pTaskBaseInfo = &pTaskBaseData->stTaskInfo.stTaskBaseInfo;
	StBasProduct *pProductInfo = &pTaskBaseData->stTaskInfo.stProductInfo;
	StHrUpDepart *pUpDepartInfo = &pTaskBaseData->stTaskInfo.stHrUpDepart;

	int nResultSearchType = m_ResultSearchInfo.stTaskBaseInfo.nResultType;

	if(nResultSearchType == Task_DarkSearch)//�������� ģ����ѯ//
	{
		pList1 = &m_ResultTaskBase.m_ResultList;
		
	}else if(nResultSearchType == Task_ExactSearch)//��������ȷ����//
	{
		pList1 = &m_TstRresultBaseList;
	}

	if(pList1 == NULL)
	{
		return;
	}

	pos = 1;
	nCount = pList1->GetItemCount();
	str.Format(_T("%d"), nCount+1);
	pList1->InsertItem(nCount, str);
	pList1->SetItemData(nCount, pTaskBaseData->nOid);
	pList1->SetItemText(nCount, pos++, pTaskBaseInfo->szSendDate);
	pList1->SetItemText(nCount, pos++, pTaskBaseInfo->szImportDate);
	pList1->SetItemText(nCount, pos++, pTaskBaseInfo->szTaskName);
	pList1->SetItemText(nCount, pos++, pProductInfo->szProductNo);
	pList1->SetItemText(nCount, pos++, pProductInfo->szProductName);
	pList1->SetItemText(nCount, pos++, pTaskBaseInfo->szCheckUser);
	

}
void CResultSearchNew::InsertResultAttachToList(StTstResultAtta    *pResultAttachData)
{
	CEditableListCtrl *pList1 = NULL;
	CString str;
	int nCount, pos, n;

	int nResultSearchType = m_ResultSearchInfo.stTaskBaseInfo.nResultType;
	
	if(nResultSearchType == Task_DarkSearch)//�������� ģ����ѯ//
	{
		pList1 = &m_TstRresultAttaList;

	}else if(nResultSearchType == Task_ExactSearch)//��������ȷ����//
	{
		pList1 = &m_TstRresultAttaList;
	}else if(nResultSearchType == Result_Search)      //�����ѯ//
	{
		pList1 = &m_ResultAttach.m_ResultList;
	}

	if(pList1 == NULL)
	{
		return;
	}
	
	pos = 1;
	nCount = pList1->GetItemCount();
	str.Format(_T("%d"),nCount+1);
	pList1->InsertItem(nCount,str);
	pList1->SetItemData(nCount,pResultAttachData->nOid);
	pList1->SetItemText(nCount,pos++,pResultAttachData->szSendDate);
	pList1->SetItemText(nCount,pos++,pResultAttachData->szImportDate);
	pList1->SetItemText(nCount,pos++,pResultAttachData->szTaskName);
	pList1->SetItemText(nCount,pos++,pResultAttachData->szProductNo);

	pList1->SetItemText(nCount,pos++,pResultAttachData->szProductCode);
	pList1->SetItemText(nCount,pos++,pResultAttachData->szModeName);

	pList1->SetItemText(nCount,pos++,GetDianshiText(pResultAttachData->nDianshiTest));
	pList1->SetItemText(nCount,pos++,GetModeType(pResultAttachData->nModeType));

	n = pResultAttachData->nModeRowVar;
	pList1->SetItemText(nCount,pos++,GetModeRowVar(n));
	if(n == ModeRow_Change)
	{
		str.Format(_T("%d"), pResultAttachData->nPicNumCount);
		pList1->SetItemText(nCount,pos,str);
	}
	pos++;
	str.Format(_T("%d%%"), pResultAttachData->nPercent);
	pList1->SetItemText(nCount,pos++,str);
	str.Format(_T("%d"), pResultAttachData->bFinished);
	pList1->SetItemText(nCount,pos++,str);
	pList1->SetItemText(nCount,pos++,pResultAttachData->szFinishedTime);
	pList1->SetItemText(nCount,pos++,pResultAttachData->szCheckUser);
}
void CResultSearchNew::SetContrlShow()
{
	CString strText;
	int nCount = 0;
	int nResultSearchType = m_ResultSearchInfo.stTaskBaseInfo.nResultType;

	strText.Format(_T("����ѯ�� %d ����������"),nCount);
	GetDlgItem(IDC_STATIC2)->SetWindowText(strText);
	m_ResultTaskBase.GetDlgItem(IDC_LIST_STATIC1)->SetWindowText(strText);

	strText.Format(_T("����ѯ�� %d ���������"),nCount);
	GetDlgItem(IDC_STATIC3)->SetWindowText(strText);
	m_ResultAttach.GetDlgItem(IDC_LIST_STATIC1)->SetWindowText(strText);



	switch(nResultSearchType)
	{
	case Task_DarkSearch://1.���������ģ����ѯ//
		{
			GetDlgItem(IDC_STATIC1)->SetWindowText(_T("�����ѯ����"));

			GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC3)->ShowWindow(SW_SHOW);
			m_TstRresultBaseList.ShowWindow(SW_HIDE);
			m_TstRresultAttaList.ShowWindow(SW_SHOW);

			m_ResultTaskBase.ShowWindow(SW_SHOW);
			m_ResultAttach.ShowWindow(SW_HIDE);

			m_ResultTaskBase.m_SmallType = Result_Task;

			//���ò�ѯ�����ؼ���״̬//
			((CEdit*)(m_ResultSearchInfoDlg.GetDlgItem(IDC_EDIT1)))->SetReadOnly(FALSE);
			((CEdit*)(m_ResultSearchInfoDlg.GetDlgItem(IDC_EDIT2)))->SetReadOnly(FALSE);
			(m_ResultSearchInfoDlg.GetDlgItem(IDC_BUTTON2))->EnableWindow(TRUE);
			((m_ResultSearchInfoDlg.GetDlgItem(IDC_STATIC4)))->ShowWindow(FALSE);
			((m_ResultSearchInfoDlg.GetDlgItem(IDC_EDIT5)))->ShowWindow(FALSE);
		}
		break;
	case Task_ExactSearch://2.��������ľ�ȷ��ѯ
		{
			GetDlgItem(IDC_STATIC1)->SetWindowText(_T(""));

			GetDlgItem(IDC_STATIC2)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC3)->ShowWindow(SW_SHOW);
			m_TstRresultBaseList.ShowWindow(SW_SHOW);
			m_TstRresultAttaList.ShowWindow(SW_SHOW);

			m_ResultTaskBase.ShowWindow(SW_HIDE);
			m_ResultAttach.ShowWindow(SW_HIDE);

			m_ResultTaskBase.m_SmallType = Result_Task;

			//���ò�ѯ�����ؼ���״̬//
			((CEdit*)(m_ResultSearchInfoDlg.GetDlgItem(IDC_EDIT1)))->SetReadOnly(TRUE);
			((CEdit*)(m_ResultSearchInfoDlg.GetDlgItem(IDC_EDIT2)))->SetReadOnly(TRUE);
			(m_ResultSearchInfoDlg.GetDlgItem(IDC_BUTTON2))->EnableWindow(FALSE);
			((m_ResultSearchInfoDlg.GetDlgItem(IDC_STATIC4)))->ShowWindow(FALSE);
			((m_ResultSearchInfoDlg.GetDlgItem(IDC_EDIT5)))->ShowWindow(FALSE);
		}
		break;
	case Result_Search://3.������ݲ�ѯ
		{
			GetDlgItem(IDC_STATIC1)->SetWindowText(_T("�����ѯ����"));
			GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC3)->ShowWindow(SW_HIDE);

			m_TstRresultBaseList.ShowWindow(SW_HIDE);
			m_TstRresultAttaList.ShowWindow(SW_HIDE);

			m_ResultTaskBase.ShowWindow(SW_HIDE);
			m_ResultAttach.ShowWindow(SW_SHOW);

			m_ResultAttach.m_SmallType = Result_Atta;

			//���ò�ѯ�����ؼ���״̬//
			((CEdit*)(m_ResultSearchInfoDlg.GetDlgItem(IDC_EDIT1)))->SetReadOnly(FALSE);
			((CEdit*)(m_ResultSearchInfoDlg.GetDlgItem(IDC_EDIT2)))->SetReadOnly(FALSE);
			(m_ResultSearchInfoDlg.GetDlgItem(IDC_BUTTON2))->EnableWindow(TRUE);
			((m_ResultSearchInfoDlg.GetDlgItem(IDC_STATIC4)))->ShowWindow(TRUE);
			((m_ResultSearchInfoDlg.GetDlgItem(IDC_EDIT5)))->ShowWindow(TRUE);
		}
		break;
	}
}


int CResultSearchNew::SearchResultData()
{
	int i, nCount;
	m_TstRresultBaseList.DeleteAllItems();
	m_TstRresultAttaList.DeleteAllItems();
	m_ResultTaskBase.m_ResultList.DeleteAllItems();
	m_ResultAttach.m_ResultList.DeleteAllItems();
	PostMessage(WM_SIZE);
	SetContrlShow();

	int nResultSearchType = m_ResultSearchInfo.stTaskBaseInfo.nResultType;

	m_ResultSearchInfoDlg.GetSearchInfo();//��ȡ��ѯ����//


	vector<StTstResultBaseNew>  stTaskBaseDataArray;
	vector<StTstResultAtta>     stResultAttachArray;
	switch(nResultSearchType)
	{
	case Task_DarkSearch://�������� ģ����ѯ//
		{
			m_ResultTaskBase.GetPageNumComBox();//��ȡҳ����Ŀ��ҳ//
			if(!m_DMng.GetGroupTstResultBaseData(&m_ResultSearchInfo,&stTaskBaseDataArray))
			{
				return 0;
			}
			nCount = stTaskBaseDataArray.size();
			for (i = 0;i<nCount; i++)
			{
				InsertTaskBaseDataToList(&stTaskBaseDataArray.at(i));

				stTaskBaseDataArray.at(i).Release();
			}
			stTaskBaseDataArray.clear();

		}
		break; 
	case Task_ExactSearch://��������ȷ����//
		{
			m_ResultTaskBase.GetPageNumComBox();//��ȡҳ����Ŀ��ҳ//
			if(!m_DMng.GetTaskTstResultBaseData(&m_ResultSearchInfo,&stTaskBaseDataArray))
			{
				return 0;
			}
			nCount = stTaskBaseDataArray.size();
			for (i = 0;i<nCount; i++)
			{
				InsertTaskBaseDataToList(&stTaskBaseDataArray.at(i));

				stTaskBaseDataArray.at(i).Release();
			}
			stTaskBaseDataArray.clear();
		}
		break;
	case Result_Search:
		{
			m_ResultAttach.GetPageNumComBox();//��ȡҳ����Ŀ��ҳ//
			if(!m_DMng.GetGroupTstResultAttachData(&m_ResultSearchInfo,&stResultAttachArray))
			{
				return 0;
			}

			nCount = stResultAttachArray.size();
			for (i = 0;i<nCount; i++)
			{
				InsertResultAttachToList(&stResultAttachArray.at(i));

			}
			stResultAttachArray.clear();
			
		}
		break;
	}

	//�����������������//

	CString strText;
	//��ʾ�����Ϣ//
	int nPerPageNum = m_ResultSearchInfo.stTaskBaseInfo.nPerPageNum;
	int nResultNum = m_ResultSearchInfo.stTaskBaseInfo.nResultNum;
	int nCurPage = m_ResultSearchInfo.stTaskBaseInfo.nCurPage;
	int nPageNum = 1;
	int bFlag = 1;

	if(nPerPageNum == g_nSearchPerPageNum[All_Result])
	{

	}else
	{
		if( nResultNum%nPerPageNum >0)
		{
			nPageNum = (nResultNum/nPerPageNum)+1;
		}else
		{
			nPageNum = nResultNum/nPerPageNum;
		}
	}

	if(nPageNum<= 0)
	{
		nPageNum = 1;
	}

	if( nCurPage > nPageNum )
	{
		nCurPage = 1;
		bFlag = 2;
	}

	CResultList *pResList = NULL;
	StSearchSetInfo *pSearchSetInfo = NULL;
	switch(nResultSearchType)
	{
	case Task_DarkSearch://�������� ģ����ѯ//
		{
			pResList = &m_ResultTaskBase;
		}
		break; 
	case Task_ExactSearch://��������ȷ����//
		{
			pResList = NULL;


		}
		break;
	case Result_Search:
		{
			pResList = &m_ResultAttach;

		}
		break;
	}

	switch(nResultSearchType)
	{
	case Task_DarkSearch://�������� ģ����ѯ//
		{
			strText.Format(_T("����ѯ�� %d ����������"), m_ResultSearchInfo.stTaskBaseInfo.nResultNum);
			pResList->GetDlgItem(IDC_LIST_STATIC1)->SetWindowText(strText);
			strText.Format(_T("%d/%d"),nCurPage , nPageNum);
			pResList->GetDlgItem(IDC_LIST_STATIC2)->SetWindowText(strText);
			break;
		}
	case Result_Search:
		{
			strText.Format(_T("����ѯ�� %d ���������"), m_ResultSearchInfo.stTaskBaseInfo.nResultNum);
			pResList->GetDlgItem(IDC_LIST_STATIC1)->SetWindowText(strText);
			strText.Format(_T("%d/%d"),nCurPage , nPageNum);
			pResList->GetDlgItem(IDC_LIST_STATIC2)->SetWindowText(strText);
			break;
		}
		
	case Task_ExactSearch://��������ȷ����//
		{
			strText.Format(_T("����ѯ�� %d ����������"), m_ResultSearchInfo.stTaskBaseInfo.nResultNum);
			GetDlgItem(IDC_STATIC2)->SetWindowText(strText);
		}
		break;
	}

	

	//����������� ResultList����//
	
	if(pResList != NULL)
	{
		pSearchSetInfo = &pResList->m_stSearchSetInfo;
		pSearchSetInfo->nCurPage = nCurPage;
		pSearchSetInfo->nAimPage = nCurPage;
		pSearchSetInfo->nMaxPage = nPageNum;
		pResList->SetBtnStatus();
	}
	

	return bFlag;
}

BOOL CResultSearchNew::GetCurSelAttaData()
{
	CEditableListCtrl *pList1 = NULL;
	int t1,t2;
	CString str;
	t1= GetTickCount();

	DelFile();

	int nResultSearchType = m_ResultSearchInfo.stTaskBaseInfo.nResultType;
	if(nResultSearchType == Task_DarkSearch)//�������� ģ����ѯ//
	{
		pList1 = &m_TstRresultAttaList;

	}else if(nResultSearchType == Task_ExactSearch)//��������ȷ����//
	{
		pList1 = &m_TstRresultAttaList;
	}else if(nResultSearchType == Result_Search)      //�����ѯ//
	{
		pList1 = &m_ResultAttach.m_ResultList;
	}

	if(pList1 == NULL)
	{
		return FALSE;
	}
	int Index = pList1->GetFirstSelectedItem(), nCount = pList1->GetItemCount();
	if(Index<0 || Index >= nCount)
		return FALSE;
	//�齨��ѯ����//
	UINT nAttaOid = pList1->GetItemData(Index);
	UINT nGroupOid = g_CurSelDepart.nOid;

	memset(&m_CurSelResultAtta, 0, sizeof(StTstResultAtta));
	if(!m_DMng.GetTstResultOid(nGroupOid,nAttaOid,&m_CurSelResultAtta))
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
	str.Format(_T("CResultSearch::ShowCurData ��ʱ %d ����"),t2);
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));
	return TRUE;
}

int CResultSearchNew::ShowAttaData()
{
	if(GetCurSelAttaData())
	{
		CResultShow ndlg;
		ndlg.m_pCurAttaInfo = &m_CurSelResultAtta;
		ndlg.DoModal();
	}
	this->InvalidateRect(NULL);

	return 1;
}


void CResultSearchNew::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialog::OnOK();
}

void CResultSearchNew::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	AutoSize();
}

void CResultSearchNew::AutoSize()
{
	CRect Rect ;
	GetClientRect(&Rect) ;

	

	int nSearchHeight = 120;
	int nListHeight = (Rect.Height()-(nSearchHeight+20+10+20+10+25*2))/2;

	int nGroupStaticpos = 5;
	int nSearchpos = nGroupStaticpos+20;

	int nGroupList1pos = nSearchpos+nSearchHeight+10;
	int nList1pos = nGroupList1pos+20;

	int nGroupList2pos = nList1pos+nListHeight+20;
	int nList2pos = nGroupList2pos+20;


	//1.
	if (GetDlgItem(IDC_STATIC1)->GetSafeHwnd())
	{
		GetDlgItem(IDC_STATIC1)->MoveWindow(1,
			nGroupStaticpos,Rect.Width()-1*2,Rect.Height()-(nGroupStaticpos*2));
	}




	//2.��ѯ����
	if(m_ResultSearchInfoDlg.GetSafeHwnd())
	{
		m_ResultSearchInfoDlg.MoveWindow(5, nSearchpos, Rect.Width()-(2*5), nSearchHeight);
	}


	int nResultSearchType = m_ResultSearchInfo.stTaskBaseInfo.nResultType;

	if(nResultSearchType == Result_Search)
	{
		if(m_ResultTaskBase.GetSafeHwnd())
		{
			m_ResultTaskBase.MoveWindow(5,nGroupList1pos,Rect.Width()-(5*2),nListHeight+25);
		}
		if(m_ResultAttach.GetSafeHwnd())
		{
			m_ResultAttach.MoveWindow(5,nGroupList1pos,Rect.Width()-(5*2),(nListHeight+25)*2);
		}
	}else
	{
		if(m_ResultTaskBase.GetSafeHwnd())
		{
			m_ResultTaskBase.MoveWindow(5,nGroupList1pos,Rect.Width()-(5*2),nListHeight+25);
		}
		if(m_ResultAttach.GetSafeHwnd())
		{
			m_ResultAttach.MoveWindow(5,nGroupList2pos,Rect.Width()-(5*2),nListHeight+25);
		}
	}
	//3.����List ��
	if (GetDlgItem(IDC_STATIC2)->GetSafeHwnd())
	{
		GetDlgItem(IDC_STATIC2)->MoveWindow(5,nGroupList1pos,Rect.Width()-(5*2),nListHeight+25);
	}
	if(m_TstRresultBaseList.GetSafeHwnd())
	{
		m_TstRresultBaseList.MoveWindow(5+5,nList1pos,Rect.Width()-((5+5)*2),nListHeight);
	}

	//4.������ List ��
	if (GetDlgItem(IDC_STATIC3)->GetSafeHwnd())
	{
		GetDlgItem(IDC_STATIC3)->MoveWindow(5,nGroupList2pos,Rect.Width()-(5*2),nListHeight+25);
	}
	if(m_TstRresultAttaList.GetSafeHwnd())
	{
		m_TstRresultAttaList.MoveWindow(5+5,nList2pos,Rect.Width()-((5+5)*2),nListHeight);
	}

}
void CResultSearchNew::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	int i, nCount, Index;
	CString strText;
	CEditableListCtrl *pList1 = &m_TstRresultBaseList;
	nCount = pList1->GetItemCount();
	Index = pList1->GetFirstSelectedItem();

	if(Index < 0 || Index >= nCount)
	{
		return ;
	}

	UINT nBaseOid = pList1->GetItemData(Index);
	UINT nGroupOid = g_CurSelDepart.nOid;
	vector<StTstResultAtta> stResultAttachArray;

	if(!m_DMng.GetTstResultAttaBaseOid(nGroupOid,nBaseOid,&stResultAttachArray))
	{
		return ;
	}

	m_TstRresultAttaList.DeleteAllItems();
	nCount = stResultAttachArray.size();
	strText.Format(_T("����ѯ�� %d ���������"), nCount);
	GetDlgItem(IDC_STATIC3)->SetWindowText(strText);

	for (i = 0;i<nCount;i++)
	{
		InsertResultAttachToList(&stResultAttachArray.at(i));
	}

	stResultAttachArray.clear();

	*pResult = 0;
}

void CResultSearchNew::OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowAttaData();

	*pResult = 0;
}

void CResultSearchNew::Menu1Fuction()
{
	CEditableListCtrl *pList1 = NULL;
	int nResultSearchType = m_ResultSearchInfo.stTaskBaseInfo.nResultType;
	if(nResultSearchType == Task_DarkSearch)//�������� ģ����ѯ//
	{
		pList1 = &m_ResultTaskBase.m_ResultList;
	}else if(nResultSearchType == Task_ExactSearch)//�������� ��ȷ��ѯ//
	{
		pList1 = &m_TstRresultBaseList;
	}
	int Index = pList1->GetFirstSelectedItem(),
		nCount = pList1->GetItemCount();
	if(Index <0 || Index >= nCount)
	{
		return;
	}

	POINT	point;
	GetCursorPos(&point);
	m_PopupMenu1.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
}

void CResultSearchNew::DelBaseDataNew()//������Ϊ��λɾ���������//
{
	CEditableListCtrl *pList1 = NULL;
	int nResultSearchType = m_ResultSearchInfo.stTaskBaseInfo.nResultType;
	if(nResultSearchType == Task_DarkSearch)//�������� ģ����ѯ//
	{
		pList1 = &m_ResultTaskBase.m_ResultList;
	}else if(nResultSearchType == Task_ExactSearch)//�������� ��ȷ��ѯ//
	{
		pList1 = &m_TstRresultBaseList;
	}
	if(pList1 == NULL)
	{
		return;
	}
	int Index = pList1->GetFirstSelectedItem(),
		nCount = pList1->GetItemCount();
	if(Index <0 || Index >= nCount)
	{
		return;
	}


	if(MessageBox(_T("ȷ��ɾ��������?\n(����ɾ�����޷��ָ�!)��"),_T(""),MB_OKCANCEL|MB_ICONQUESTION) != IDOK)
	{
		return ;
	}
	UINT nGroupOid = g_CurSelDepart.nOid;
	UINT nBaseOid = pList1->GetItemData(Index);
	if(m_DMng.DelBaseData(nGroupOid,nBaseOid))
	{
		pList1->DeleteItem(Index);
	}

}


void CResultSearchNew::Menu2Fuction()
{
	CEditableListCtrl *pList1 = NULL;
	int nResultSearchType = m_ResultSearchInfo.stTaskBaseInfo.nResultType;
	if(nResultSearchType == Task_DarkSearch)//�������� ģ����ѯ//
	{
		pList1 = &m_TstRresultAttaList;
	}else if(nResultSearchType == Task_ExactSearch)//�������� ��ȷ��ѯ//
	{
		pList1 = &m_TstRresultAttaList;
	}else if(nResultSearchType == Result_Search)//������  �����ѯ//
	{
		pList1 = &m_ResultAttach.m_ResultList;
	}
	if(pList1 == NULL)
	{
		return;
	}
	int Index = pList1->GetFirstSelectedItem(),
		nCount = pList1->GetItemCount();
	if(Index <0 || Index >= nCount)
	{
		return;
	}

	POINT	point;
	GetCursorPos(&point);
	m_PopupMenu2.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
}
//������Ϊ��λ���ɱ����ļ�//
void  CResultSearchNew::CreateTaskReportNew()
{
	CString str, strFileName, strDesFile, strSrcFile, strCreateFile;
	int		ret, tick1,tick2;

	CEditableListCtrl *pList1 = NULL;
	int nResultSearchType = m_ResultSearchInfo.stTaskBaseInfo.nResultType;
	if(nResultSearchType == Task_DarkSearch)//�������� ģ����ѯ//
	{
		pList1 = &m_TstRresultAttaList;
	}else if(nResultSearchType == Task_ExactSearch)//�������� ��ȷ��ѯ//
	{
		pList1 = &m_TstRresultAttaList;
	}else if(nResultSearchType == Result_Search)//������  �����ѯ//
	{
		pList1 = &m_ResultAttach.m_ResultList;
	}
	if(pList1 == NULL)
	{
		return;
	}
	int Index = pList1->GetFirstSelectedItem(),
		nCount = pList1->GetItemCount();
	if(Index <0 || Index >= nCount)
	{
		return;
	}

	CString strTaskName = pList1->GetItemText(Index,3);
	CString strProductNo = pList1->GetItemText(Index,4);
	str.Format(_T("�Ƿ���������=\"%s\"�ı����ļ�?(ȷ��/ȡ��)"),strTaskName);
	if(MessageBox(str,_T("��ʾ"),MB_OKCANCEL|MB_ICONQUESTION) != IDOK)
	{
		return ;
	}

	//1.��ȡ�������Ľ��������Ϣ

	UINT nGroupOid = g_CurSelDepart.nOid;
	UINT nAttaOid = pList1->GetItemData(Index);


	StTstResultAtta stCreateReportAtta;
	memset(&stCreateReportAtta, 0, sizeof(StTstResultAtta));

	if(!m_DMng.GetTstResultOid(nGroupOid,nAttaOid,&stCreateReportAtta))
	{
		str.Format(_T("��ȡ���������Ϣʱ����!"));
		AfxMessageBox(str);
		return;
	}




	vector<StTstResultAtta> *pStResultAtta = NULL;
	CAdjustmentDlg AdjustmentDlg;
	AdjustmentDlg.m_CreateType = CreateReport_Task;
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


	//2.ѡ��һ�������ļ�����
	strCreateFile.Format(_T("%s_%s"),strProductNo,GetDateTimeString2());
	CFileDialog *lpszOpenFile;    //����һ��CfileDialog����
	lpszOpenFile = new CFileDialog(FALSE,".doc",strCreateFile,OFN_FILEMUSTEXIST |OFN_HIDEREADONLY , 
		"�ļ�����(*.doc)|*.doc||");//����һ���Ի���
	if(lpszOpenFile->DoModal() == IDOK)//�������Ի���ȷ����ť
	{

		strCreateFile = lpszOpenFile->GetPathName();	//�õ����ļ���·��

	}else
	{
		delete lpszOpenFile;	//�ͷŷ���ĶԻ���
		return ;
	}
	delete lpszOpenFile;	//�ͷŷ���ĶԻ���







	CreateReportBaseNew(pStResultAtta,strCreateFile);
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

		//1.����  2.ͼ����Ϣ  3.����ģ����Ϣ//


		if(!m_DMng.GetAttaXmlFile(nGroupOid,pCurAttaInfo->nOid))
		{
			continue;
		}

		m_LoadOutTask.GetCurTaskInfoLoad();

		int nRet = 0;
		nRet = m_LoadOutTask.AnalysisData(m_DataArray,m_ExclosureArray);//��ȡ��ǰ�����������//
		if(!nRet)
		{
			//return 0;
		}

		g_pDataArray = &m_DataArray;////1.����

		int nPicNumCount = g_PicNum = m_LoadOutTask.m_CurTaskInfo.pArryTaskPicNum.size();
		g_pArryTaskPicNum = &m_LoadOutTask.m_CurTaskInfo.pArryTaskPicNum;//2.ͼ����Ϣ///
		g_pCurAttaInfo = pCurAttaInfo;//3.������Ϣ//




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
				str.Format(_T("����ģ�岻���� ��%s"),strFileName);
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
			str.Format("��ʱ%d����! ret=%d, ����ļ���%s", tick2, ret, strDesFile.GetBuffer(0)); 
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
			str.Format("��ʱ%d����! ret=%d, ����ļ���%s", tick2, ret, strSrcFile.GetBuffer(0));
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
			str.Format("��ʱ%d����! ret=%d, ����ļ���%s", tick2, ret, strSrcFile.GetBuffer(0)); 
			g_pLogInfo->WriteLogFile(str.GetBuffer(0));
			//AfxMessageBox(str);	
		}

		remove(strDesFile.GetBuffer(0));


	}
	/******************************************************/

	ret = WordOpt_MakeTestimonialDemo(strCreateFile.GetBuffer(0),nStrFileNames);
	pStResultAtta->clear();


	t2 = GetTickCount()-t1;
	str.Format("��ʱ%d����! ret=%d, ����ļ���%s", t2, ret, strCreateFile.GetBuffer(0)); 
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));
	AfxMessageBox(str);	


}
//�Բ�Ʒ���Ϊ��λ���ɱ����ļ�//
void  CResultSearchNew::CreateProductCodeReportNew()
{

	CString str, strFileName, strDesFile, strSrcFile, strCreateFile;

	CEditableListCtrl *pList1 = NULL;
	int nResultSearchType = m_ResultSearchInfo.stTaskBaseInfo.nResultType;
	if(nResultSearchType == Task_DarkSearch)//�������� ģ����ѯ//
	{
		pList1 = &m_TstRresultAttaList;
	}else if(nResultSearchType == Task_ExactSearch)//�������� ��ȷ��ѯ//
	{
		pList1 = &m_TstRresultAttaList;
	}else if(nResultSearchType == Result_Search)//������  �����ѯ//
	{
		pList1 = &m_ResultAttach.m_ResultList;
	}
	if(pList1 == NULL)
	{
		return;
	}
	int Index = pList1->GetFirstSelectedItem(),
		nCount = pList1->GetItemCount();
	if(Index <0 || Index >= nCount)
	{
		return;
	}


	CString strProductNo = pList1->GetItemText(Index,4);
	CString strProductCode = pList1->GetItemText(Index,5);
	str.Format(_T("�Ƿ����ɲ�Ʒ����, ��Ʒ���=\"%s\" ?(ȷ��/ȡ��)"),strProductCode);
	if(MessageBox(str,_T("��ʾ"),MB_OKCANCEL|MB_ICONQUESTION) != IDOK)
	{
		return ;
	}



	//1.��ȡ�������Ľ��������Ϣ

	UINT nGroupOid = g_CurSelDepart.nOid;
	UINT nAttaOid = pList1->GetItemData(Index);
	UINT nBaseOid = 0;

	StTstResultAtta stCreateReportAtta;
	memset(&stCreateReportAtta, 0, sizeof(StTstResultAtta));

	if(!m_DMng.GetTstResultOid(nGroupOid,nAttaOid,&stCreateReportAtta))
	{
		str.Format(_T("��ȡ���������Ϣʱ����!"));
		AfxMessageBox(str);
		return;
	}

	vector<StTstResultAtta> *pStResultAtta = NULL;
	CAdjustmentDlg AdjustmentDlg;
	AdjustmentDlg.m_CreateType = CreateReport_ProdCode;
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


	//2.ѡ��һ�������ļ�����
	strCreateFile.Format(_T("%s_%s_%s"),strProductNo,strProductCode,GetDateTimeString2());
	CFileDialog *lpszOpenFile;    //����һ��CfileDialog����
	lpszOpenFile = new CFileDialog(FALSE,".doc",strCreateFile,OFN_FILEMUSTEXIST |OFN_HIDEREADONLY , 
		"�ļ�����(*.doc)|*.doc||");//����һ���Ի���
	if(lpszOpenFile->DoModal() == IDOK)//�������Ի���ȷ����ť
	{

		strCreateFile = lpszOpenFile->GetPathName();	//�õ����ļ���·��

	}else
	{
		delete lpszOpenFile;	//�ͷŷ���ĶԻ���
		return ;
	}
	delete lpszOpenFile;	//�ͷŷ���ĶԻ���

	CreateReportBaseNew(pStResultAtta,strCreateFile);

}

//��ģ��Ϊ��λ���ɱ����ļ�
void  CResultSearchNew::CreateModeReportNew()
{

	CString str, strFileName, strDesFile, strSrcFile, strCreateFile;

	CEditableListCtrl *pList1 = NULL;
	int nResultSearchType = m_ResultSearchInfo.stTaskBaseInfo.nResultType;
	if(nResultSearchType == Task_DarkSearch)//�������� ģ����ѯ//
	{
		pList1 = &m_TstRresultAttaList;
	}else if(nResultSearchType == Task_ExactSearch)//�������� ��ȷ��ѯ//
	{
		pList1 = &m_TstRresultAttaList;
	}else if(nResultSearchType == Result_Search)//������  �����ѯ//
	{
		pList1 = &m_ResultAttach.m_ResultList;
	}
	if(pList1 == NULL)
	{
		return;
	}
	int Index = pList1->GetFirstSelectedItem(),
		nCount = pList1->GetItemCount();
	if(Index <0 || Index >= nCount)
	{
		return;
	}

	CString strProductNo = pList1->GetItemText(Index,4);
	CString strProductCode = pList1->GetItemText(Index,6);

	CString strModeName = pList1->GetItemText(Index,7);
	str.Format(_T("�Ƿ����ɲ�Ʒģ��=\"%s\"�ı����ļ�?(ȷ��/ȡ��)"),strModeName);
	if(MessageBox(str,_T("��ʾ"),MB_OKCANCEL|MB_ICONQUESTION) != IDOK)
	{
		return ;
	}




	//1.ѡ��һ�������ļ�����
	strCreateFile.Format(_T("%s_%s_%s_%s"),strProductNo,strProductCode,strModeName,GetDateTimeString2());
	CFileDialog *lpszOpenFile;    //����һ��CfileDialog����
	lpszOpenFile = new CFileDialog(FALSE,".doc",strCreateFile,OFN_FILEMUSTEXIST |OFN_HIDEREADONLY , 
		"�ļ�����(*.doc)|*.doc||");//����һ���Ի���
	if(lpszOpenFile->DoModal() == IDOK)//�������Ի���ȷ����ť
	{

		strCreateFile = lpszOpenFile->GetPathName();	//�õ����ļ���·��

	}else
	{
		delete lpszOpenFile;	//�ͷŷ���ĶԻ���
		return ;
	}
	delete lpszOpenFile;	//�ͷŷ���ĶԻ���





	//2.��ȡ�������Ľ��������Ϣ

	UINT nGroupOid = g_CurSelDepart.nOid;
	UINT nAttaOid = pList1->GetItemData(Index);
	UINT nBaseOid = 0;

	StTstResultAtta m_CreateReportAtta;
	memset(&m_CreateReportAtta, 0, sizeof(StTstResultAtta));

	if(!m_DMng.GetTstResultOid(nGroupOid,nAttaOid,&m_CreateReportAtta))
	{
		str.Format(_T("��ȡ���������Ϣʱ����!"));
		AfxMessageBox(str);
		return;
	}
	vector<StTstResultAtta> StResultAtta;
	StResultAtta.push_back(m_CreateReportAtta);

	CreateReportBaseNew(&StResultAtta,strCreateFile);



}

//���ɱ���
void  CResultSearchNew::CreateReportBaseNew(vector<StTstResultAtta> *pStResultAtta,CString strCreateFile)
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

		//1.����  2.ͼ����Ϣ  3.����ģ����Ϣ//


		if(!m_DMng.GetAttaXmlFile(nGroupOid,pCurAttaInfo->nOid))
		{
			continue;
		}

		m_LoadOutTask.m_CurTaskInfo.Release();
		m_LoadOutTask.GetCurTaskInfoLoad();

		int nRet = 0;
		m_DataArray.RemoveAll();
		m_ExclosureArray.RemoveAll();
		nRet = m_LoadOutTask.AnalysisData(m_DataArray,m_ExclosureArray);//��ȡ��ǰ�����������//
		if(!nRet)
		{
			//return 0;
		}

		g_pDataArray = &m_DataArray;////1.����

		int nPicNumCount = g_PicNum = m_LoadOutTask.m_CurTaskInfo.pArryTaskPicNum.size();
		g_pArryTaskPicNum = &m_LoadOutTask.m_CurTaskInfo.pArryTaskPicNum;//2.ͼ����Ϣ///
		g_pCurAttaInfo = pCurAttaInfo;//3.������Ϣ//




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
				str.Format(_T("����ģ�岻���� ��%s"),strFileName);
				AfxMessageBox(str);
				continue ;
			}


			strSrcFile.Format(_T("%s\\%s\\%s_%s.doc"),g_WorkPath,
				Report_Temp_Path,StBasModeInfo.szModeName,GetDateTimeFileNameString());

			str.Format("[��%d��]��ʼ�����ļ���%s",i+1, strSrcFile.GetBuffer(0));
			g_pLogInfo->WriteLogFile(str.GetBuffer(0));


			tick1 = GetTickCount();
			//strFileName = _T("c:\\Mode2.doc");
			//strDesFile  = _T("c:\\t_Mode2.doc");
			strDesFile.Format(_T("%s\\%s\\t%d_Mode.doc"),g_WorkPath,Report_Temp_Path,i+1);
			str.Format("��ʼ�����ļ���%s", strDesFile.GetBuffer(0));
			g_pLogInfo->WriteLogFile(str.GetBuffer(0));

			ret = WordOpt_MakeTabModeToTabData(strFileName.GetBuffer(0), strDesFile.GetBuffer(0));


			str.Format("CreateReportBase��%d, ret=%d", 1, ret);
			g_pLogInfo->WriteLogFile(str.GetBuffer(0));


			tick2 = GetTickCount()-tick1;
			str.Format("��ʱ%d����! ret=%d, �����ļ��ɹ���%s", tick2, ret, strDesFile.GetBuffer(0)); 
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
			str.Format("��ʱ%d����! ret=%d, [��%d��]�����ļ��ɹ���%s", tick2, ret,i+1, strSrcFile.GetBuffer(0));
			g_pLogInfo->WriteLogFile(str.GetBuffer(0));
			//AfxMessageBox(str);	

		}else
		{
			tick1 = GetTickCount();

			//strCreateFile = _T("C:\\tt2.doc");

			strSrcFile.Format(_T("%s\\%s\\%s.doc"),g_WorkPath, Report_Temp_Path,GetDateTimeFileNameString());
			str.Format("[��%d��]��ʼ�����ļ���%s",i+1, strSrcFile.GetBuffer(0));
			g_pLogInfo->WriteLogFile(str.GetBuffer(0));

			ret = WordOpt_MakeReportRowVarDemo( strSrcFile.GetBuffer(0) ); 

			nStrFileNames.Add(strSrcFile);

			tick2 = GetTickCount()-tick1;
			str.Format("��ʱ%d����! ret=%d, [��%d��]�����ļ��ɹ���%s", tick2, ret,i+1, strSrcFile.GetBuffer(0)); 
			g_pLogInfo->WriteLogFile(str.GetBuffer(0));
			//AfxMessageBox(str);	
		}

		remove(strDesFile.GetBuffer(0));


	}
	/******************************************************/

	tick1 = GetTickCount();

	ret = WordOpt_MakeTestimonialDemo(strCreateFile.GetBuffer(0),nStrFileNames);

	tick2 = GetTickCount()-tick1;
	str.Format("��ʱ%d����! ret=%d, �ϲ��м��ļ�,�ļ�����%d", tick2, ret, nCount); 
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));


	pStResultAtta->clear();
	t2 = GetTickCount()-t1;
	str.Format("��ʱ%d����! ret=%d, ����ļ���%s", t2, ret, strCreateFile.GetBuffer(0)); 
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));
	AfxMessageBox(str);	
}

void  CResultSearchNew::InitPopMenu1( )					//��ʼ���˵�1
{
	if(!m_PopupMenu1.GetSafeHmenu())
	{
		m_PopupMenu1.CreatePopupMenu();

		m_PopupMenu1.AppendMenu(MF_STRING, ID_MENU1_DELDATA_BASE,		"ɾ������");

	}
}

void  CResultSearchNew::InitPopMenu2( )					//��ʼ���˵�1
{
	if(!m_PopupMenu2.GetSafeHmenu())
	{
		m_PopupMenu2.CreatePopupMenu();

		m_PopupMenu2.AppendMenu(MF_STRING, ID_MENU1_C_PRODUCT_REPORT_ATTA,     "���ɲ�Ʒ����");
		m_PopupMenu2.AppendMenu(MF_STRING, ID_MENU1_C_MODE_REPORT_ATTA,        "����ģ�屨��");
		m_PopupMenu2.AppendMenu(MF_STRING, ID_MENU1_C_TASK_REPORT_BASE,       "�������񱨸�");
		//m_PopupMenu2.AppendMenu(MF_SEPARATOR);
		//m_PopupMenu2.AppendMenu(MF_STRING, ID_MENU1_DELDATA_ATTA,		"ɾ������");


	}
}
void CResultSearchNew::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Menu1Fuction();
	*pResult = 0;
}

void CResultSearchNew::OnNMRClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Menu2Fuction();
	*pResult = 0;
}
