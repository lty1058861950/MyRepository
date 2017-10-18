// AdjustmentDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "AdjustmentDlg.h"


// CAdjustmentDlg 对话框

IMPLEMENT_DYNAMIC(CAdjustmentDlg, CDialog)

CAdjustmentDlg::CAdjustmentDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAdjustmentDlg::IDD, pParent)
{
	m_pStCreateReportAtta = NULL;
	m_CreateType = CreateReport_Task;
}

CAdjustmentDlg::~CAdjustmentDlg()
{
	m_ResultAttaArray.clear();
}

void CAdjustmentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
}


BEGIN_MESSAGE_MAP(CAdjustmentDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CAdjustmentDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAdjustmentDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CAdjustmentDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CAdjustmentDlg::OnBnClickedButton4)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CAdjustmentDlg 消息处理程序

//上移一行//
void CAdjustmentDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex,j, nCount,nColCnt;
	UINT    OID1, OID2;

	CStringArray strArray1, strArray2;
	CString strNum;
	CEditableListCtrl *pList = &m_List;
	nCount = m_List.GetItemCount();
	nIndex = m_List.GetFirstSelectedItem();
	if(nIndex<0 || nIndex >= nCount)
	{
		return;
	}

	if(nIndex <= 0)//已经是第一行了//
	{
		return;
	}


	nColCnt = pList->GetHeaderCtrl()->GetItemCount();
	OID1 = pList->GetItemData(nIndex);
	OID2 = pList->GetItemData(nIndex-1);

	for (j = 1;j<nColCnt;j++)
	{
		strArray1.Add(pList->GetItemText(nIndex, j));
		strArray2.Add(pList->GetItemText(nIndex-1, j));
	}

	pList->SetItemData(nIndex,OID2);
	pList->SetItemData(nIndex-1,OID1);
	for (j=1; j<nColCnt; j++)
	{
		pList->SetItemText(nIndex,j,strArray2.GetAt(j-1));
		pList->SetItemText(nIndex-1,j,strArray1.GetAt(j-1));
	}

	pList->SetItemState(nIndex, 0, LVIS_SELECTED|LVIS_FOCUSED);
	pList->SetItemState(nIndex-1,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
	pList->SetFocus();

}
//下移一行
void CAdjustmentDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex,j, nCount,nColCnt;
	UINT    OID1, OID2;

	CStringArray strArray1, strArray2;
	CString strNum;
	CEditableListCtrl *pList = &m_List;
	nCount = m_List.GetItemCount();
	nIndex = m_List.GetFirstSelectedItem();
	if(nIndex<0 || nIndex >= nCount)
	{
		return;
	}

	if(nIndex >= (nCount-1))//已经是最后一行了//
	{
		return;
	}

	
	nColCnt = pList->GetHeaderCtrl()->GetItemCount();
	OID1 = pList->GetItemData(nIndex);
	OID2 = pList->GetItemData(nIndex+1);

	for (j = 1;j<nColCnt;j++)
	{
		strArray1.Add(pList->GetItemText(nIndex, j));
		strArray2.Add(pList->GetItemText(nIndex+1, j));
	}
	
	pList->SetItemData(nIndex,OID2);
	pList->SetItemData(nIndex+1,OID1);
	for (j=1; j<nColCnt; j++)
	{
		pList->SetItemText(nIndex,j,strArray2.GetAt(j-1));
		pList->SetItemText(nIndex+1,j,strArray1.GetAt(j-1));
	}

	pList->SetItemState(nIndex, 0, LVIS_SELECTED|LVIS_FOCUSED);
	pList->SetItemState(nIndex+1,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);
	pList->SetFocus();
	
}
//删除一行//
void CAdjustmentDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码//

	CString strNum;
	int i, nCount;
	CEditableListCtrl *pList = &m_List;
	nCount = pList->GetItemCount();
	for(i = 0;i<nCount;i++)
	{
		if(pList->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			pList->DeleteItem(i);
		}
	}

	//排序//

	nCount = pList->GetItemCount();
	for (i = 0;i<nCount;i++)
	{
		strNum.Format(_T("%d"), i+1);
		pList->SetItemText(i,0,strNum);
	}
}
//复原//
void CAdjustmentDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	int i, nCount;
	CEditableListCtrl *pList = &m_List;
	pList->DeleteAllItems();
	nCount = m_ResultAttaArray.size();
	for (i = 0;i<nCount;i++)
	{
		InseartAttachToList(&m_ResultAttaArray.at(i));
	}
}
void CAdjustmentDlg::InseartAttachToList(StTstResultAtta *pTstResultAtta)
{
	int nIndex,nCount;
	CString strNum;
	CEditableListCtrl *pList = &m_List;
	int pos;
	int num;

	nCount = m_List.GetItemCount();
	strNum.Format(_T("%d"), nCount+1);
	nIndex = pList->InsertItem(nCount, strNum);
	pList->SetItemData(nIndex, pTstResultAtta->nOid);

	pos = 1;
	pList->SetItemText(nCount,pos++,pTstResultAtta->szSendDate);
	pList->SetItemText(nCount,pos++,pTstResultAtta->szImportDate);
	pList->SetItemText(nCount,pos++,pTstResultAtta->szTaskName);
	pList->SetItemText(nCount,pos++,pTstResultAtta->szProductNo);

	pList->SetItemText(nCount,pos++,pTstResultAtta->szProductCode);
	pList->SetItemText(nCount,pos++,pTstResultAtta->szModeName);
	strNum.Format(_T("%d"), pTstResultAtta->nDianshiTest);
	pList->SetItemText(nCount,pos++,strNum);
	pList->SetItemText(nCount,pos++,GetModeType(pTstResultAtta->nModeType));

	num = pTstResultAtta->nModeRowVar;
	pList->SetItemText(nCount,pos++,GetModeRowVar(num));
	if(num == ModeRow_Change)
	{
		strNum.Format(_T("%d"), pTstResultAtta->nPicNumCount);
		pList->SetItemText(nCount,pos,strNum);
	}
	pos++;
	strNum.Format(_T("%d"), pTstResultAtta->nPercent);
	pList->SetItemText(nCount,pos++,strNum);
	strNum.Format(_T("%d"), pTstResultAtta->bFinished);
	pList->SetItemText(nCount,pos++,strNum);
	pList->SetItemText(nCount,pos++,pTstResultAtta->szFinishedTime);
	pList->SetItemText(nCount,pos++,pTstResultAtta->szCheckUser);


	
	pList->SetItemText(nIndex, pos++, pTstResultAtta->szSendDate);

}
void CAdjustmentDlg::DisPlayResultAttach()
{
	int i, nCount;
	CString str;
	CString strProductCode;
	UINT nBaseOid = 0;
	UINT nGroupOid = g_CurSelDepart.nOid;
	vector<StTstResultAtta> StResultAtta;
	CEditableListCtrl *pList = &m_List;
	nBaseOid = m_pStCreateReportAtta->nBaseOid;

	strProductCode = m_pStCreateReportAtta->szProductCode;
	pList->DeleteAllItems();
	m_ResultAttaArray.clear();
	if(m_CreateType == CreateReport_Task)
	{
		if(!m_DMng.GetTstResultAttaBaseOid(nGroupOid,nBaseOid,&m_ResultAttaArray))
		{
			str.Format(_T("获取结果附件信息时出错!"));
			AfxMessageBox(str);
			return;
		}
		
	}else if(m_CreateType == CreateReport_ProdCode)
	{
		if(!m_DMng.GetTstResultAttaBaseOidAndProductCode(nGroupOid,nBaseOid,strProductCode.GetBuffer(0),&m_ResultAttaArray))
		{
			str.Format(_T("获取结果附件信息时出错!"));
			AfxMessageBox(str);
			return;
		}
	}
	

	nCount = m_ResultAttaArray.size();
	for (i = 0;i<nCount;i++)
	{
		InseartAttachToList(&m_ResultAttaArray.at(i));
	}
}
BOOL CAdjustmentDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	int i;
	char *ColName4[] = {"序号","下发日期","导入日期","任务名称","产品代号",
		"产品编号",_T("模板名称"),_T("是否典试"),_T("模板类型"),_T("模板行可变"),
		_T("图号数量"),_T("完成进度(百分比)"),_T("完成状态"),_T("完成时间"),_T("检查人")};
	int ColWidth4[] = {50,150,150,100,100,   100,100,100,100,100,   100,100,100,150,100};
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_GRIDLINES);

	for(i = 0;i<15;i++)
	{
		m_List.InsertColumn(i, ColName4[i],LVCFMT_CENTER, ColWidth4[i]);
	}
	m_List.EnableRClickMenu(FALSE);


	DisPlayResultAttach();

	PostMessage(WM_SIZE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CAdjustmentDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	int i, nCount;
	CString str;
	UINT nGroupOid = g_CurSelDepart.nOid;
	UINT nAttaOid = 0;
	CEditableListCtrl *pList = &m_List;
	nCount = pList->GetItemCount();
	m_CreateReportArray.clear();
	for (i = 0;i<nCount;i++)
	{
		nAttaOid = pList->GetItemData(i);
		StTstResultAtta StCreateReportAtta;
		memset(&StCreateReportAtta, 0, sizeof(StTstResultAtta));

		if(!m_DMng.GetTstResultOid(nGroupOid,nAttaOid,&StCreateReportAtta))
		{
			/*str.Format(_T("获取结果附件信息时出错!"));
			AfxMessageBox(str);
			return;*/
		}else
		{
			m_CreateReportArray.push_back(StCreateReportAtta);	
		}

	}
	CDialog::OnOK();
}

void CAdjustmentDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	AutoSize();
}

void CAdjustmentDlg::AutoSize()
{
	/*IDC_STATIC1
		IDC_LIST1
		IDC_BUTTON4
		IDC_BUTTON3
		IDC_BUTTON1
		IDC_BUTTON2*/

	CRect Rect ;
	GetClientRect(&Rect) ;
	int nBtnWidgh = 80;
	int nBtnHeight = 30;

	if(GetDlgItem(IDC_STATIC1)->GetSafeHwnd())
	{
		GetDlgItem(IDC_STATIC1)->MoveWindow(5, 5, 
			Rect.Width()-((5*2) + nBtnWidgh+20), Rect.Height()-((5*2)+nBtnHeight+10));
	}

	if(GetDlgItem(IDC_LIST1)->GetSafeHwnd())
	{
		GetDlgItem(IDC_LIST1)->MoveWindow(5+5, 5+20, 
			Rect.Width()-(((5+5)*2) + nBtnWidgh+20), Rect.Height()-((5*2+20+5)+nBtnHeight+10));
	}


	if(GetDlgItem(IDC_BUTTON4)->GetSafeHwnd())
	{
		GetDlgItem(IDC_BUTTON4)->MoveWindow(Rect.right-(10+(nBtnWidgh+10)*1),
			Rect.top+(20+(nBtnHeight+10)*1), nBtnWidgh, nBtnHeight);
	}
	if(GetDlgItem(IDC_BUTTON3)->GetSafeHwnd())
	{
		GetDlgItem(IDC_BUTTON3)->MoveWindow(Rect.right-(10+(nBtnWidgh+10)*1),
			Rect.top+(20+(nBtnHeight+10)*2), nBtnWidgh, nBtnHeight);
	}
	if(GetDlgItem(IDC_BUTTON1)->GetSafeHwnd())
	{
		GetDlgItem(IDC_BUTTON1)->MoveWindow(Rect.right-(10+(nBtnWidgh+10)*1),
			Rect.top+(20+(nBtnHeight+10)*3), nBtnWidgh, nBtnHeight);
	}
	if(GetDlgItem(IDC_BUTTON2)->GetSafeHwnd())
	{
		GetDlgItem(IDC_BUTTON2)->MoveWindow(Rect.right-(10+(nBtnWidgh+10)*1),
			Rect.top+(20+(nBtnHeight+10)*4), nBtnWidgh, nBtnHeight);
	}


	if(GetDlgItem(IDOK)->GetSafeHwnd())
	{
		GetDlgItem(IDOK)->MoveWindow(Rect.right-((nBtnWidgh+10)*2),
			Rect.bottom-((nBtnHeight+10)*1), nBtnWidgh, nBtnHeight);
	}

	if(GetDlgItem(IDCANCEL)->GetSafeHwnd())
	{
		GetDlgItem(IDCANCEL)->MoveWindow(Rect.right-((nBtnWidgh+10)*1),
			Rect.bottom-((nBtnHeight+10)*1), nBtnWidgh, nBtnHeight);
	}

}
