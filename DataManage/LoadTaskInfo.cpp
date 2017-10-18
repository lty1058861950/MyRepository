// LoadTaskInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataManage.h"
#include "LoadTaskInfo.h"


// CLoadTaskInfo �Ի���

IMPLEMENT_DYNAMIC(CLoadTaskInfo, CDialog)

CLoadTaskInfo::CLoadTaskInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CLoadTaskInfo::IDD, pParent)
{
	MaxCol = 35;


	m_ErrorText = "��ѡ��һ��Excel�ļ�";
}

CLoadTaskInfo::~CLoadTaskInfo()
{
	//AfxMessageBox(_T("��������"));

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


// CLoadTaskInfo ��Ϣ�������

BOOL CLoadTaskInfo::OnInitDialog()
{
	CDialog::OnInitDialog();


	//���ݿ⹲��28���ֶ� �ֶ�˳��Ϊ://����ID��(1)';���鵥��(2)';'״̬(3)';'���첿��(4)';'��Ʒ����(5)';
									//'��Ʒ����(6)';'��Ʒ���(7)'����(8)';'���κ�(9)'; '��Ʒ�ͺ�(10)';
									///'��Ʒ�׶�(11)';'������(12)'; '��������(13)';'����Ա����(14)'; '�����鳤(15)';
									//'����Ա(16)';'����(17)';'��������(18)';'��������1(19)'; '��������2(20)';
									//'��������3(21)';'��������4(22)';'��������5(23)'; '��ע(24)';'�ƻ���ʼʱ��(25)'
									//;'�ƻ�����ʱ��(26)';'ʵ�ʿ�ʼʱ��(27)';'ʵ�ʽ���ʱ��(28)';


	//���湲��35���ֶ� ֻ��21���ֶ�����Чֵ �ֱ���:"�����ͺ�(10)","�����������(2)","��Ʒ����(5)","��Ʒ����(6)","����(8)",
										//"��Ʒ���(7)","��Ʒ�׶�(11)","����(17)","��������(18)","�����鳤(15)",//
										//"����Ա����(14)","���첿��(4)","����Ա(16)","��������1(19)","��������2(20)",//
										//"��������3(21)","��������4(22)","��������5(23)","������(12)","����������(13)","��ע(24)"///
	///( 10, 2, 5, 6, 8,    7, 11, 17, 18, 15,    14, 4, 16, 19, 20,   21, 22, 23, 12, 13,   24)




	//���ݿ��л���7���ֶ����������ɵ� �ֱ���://"����ID��(1)","״̬(3)","���κ�(9)"'�ƻ���ʼʱ��(25)'/;'�ƻ�����ʱ��(26)'
											//;'ʵ�ʿ�ʼʱ��(27)';'ʵ�ʽ���ʱ��(28)';

	
	



	//(2, 3, 4, 5, 6,   7, 8, 9, 10, 11,   12, 13, 14, 16, 17,    18, 19, 20, 21, 22, 34)//��Щ����Ч��
	char *ColName[] = {"���","��״̬","�����ͺ�","�����������","��Ʒ����",
		"��Ʒ����","����","��Ʒ���","��Ʒ�׶�","����",
		"��������","�����鳤","����Ա����","���첿��","����Ա",
		"�������","��������1","��������2","��������3","��������4",
		"��������5","������","����������","����������","�������ǩ��",
		"�����������","��Ʒ����","��Ʒ��������","���첿���쵼���","���첿���쵼ǩ��",
		"���첿���쵼ǩ������","����Ա���","����Աǩ��","����Ա����","��ע"};
	int  ColWidth[] = {50,100,100,200,150,  100,100,200,100,100,
	100,100,100,100,100,  100,200,200,200,200,  200,100,150,100,100,
	150,100,150,100,100,  200,100,100,150,300};
	m_TaskList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_GRIDLINES);

	for(int i = 0;i<MaxCol;i++)
	{
		m_TaskList.InsertColumn(i, ColName[i],LVCFMT_CENTER, ColWidth[i]);
	}
	m_TaskList.EnableRClickMenu(FALSE);
	
	char *ColName1[] = {"���","��Ʒ����","��Ʒ����"};
	int  ColWidth1[] = {50,100,100};
	m_NewProdList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_GRIDLINES);

	for(int i = 0;i<3;i++)
	{
		m_NewProdList.InsertColumn(i, ColName1[i],LVCFMT_CENTER, ColWidth1[i]);
	}
	m_NewProdList.EnableRClickMenu(FALSE);


	char *ColName2[] = {"���","��������","���ű��"};
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
	// �쳣: OCX ����ҳӦ���� FALSE
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
	CFileDialog *lpszOpenFile;    //����һ��CfileDialog����
	lpszOpenFile = new CFileDialog(TRUE,"","",OFN_FILEMUSTEXIST |OFN_HIDEREADONLY , "�ļ�����(*.xls;*.xlsx)|*.xls;*.xlsx||");//����һ���Ի���
	if(lpszOpenFile->DoModal() == IDOK)//�������Ի���ȷ����ť
	{
		CString	szGetName;
		szGetName = lpszOpenFile->GetPathName();	//�õ����ļ���·��
		GetDlgItem(IDC_LOADTASK_XLSFILE_EDT)->SetWindowText(szGetName);

		m_ExcelOptFun.ClearParamInfo();
		m_ExcelOptFun.ReadExcelFile(szGetName);

		m_ErrorText = _T("");

		GetDlgItem(IDC_LOADTASK_STATIC3)->SetWindowText("������ʾ:");

		InitLoadTasksList();//��ʼ��List//

	}

	delete lpszOpenFile;	//�ͷŷ���ĶԻ���
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
	strText.Format(_T("��⵽���Ϸ���������:\n"));
	for(int j = 0;j<nCol;j++)
	{
		if(!strcmp("",m_ExcelOptFun.m_ItemInfo[0][j]))
		{
			//�ֶ�ֵΪ��  �����///
			CString strText1;
			strText1.Format("�� %d �� �ֶ����� Ϊ���Ѻ���",j+1);
			
			continue;
		}
		index = 0;
		index = CheckFiledName(m_ExcelOptFun.m_ItemInfo[0][j]);
		if(!index)
		{
			//���� 0 ��ʾ ���ǺϷ��ֶ� ������ʾ//
			nColB = TRUE;
			CString strError;
			strError.Format(_T("%d.��Excel�ļ��� %d �� ������: \"%s\"\n"),k++,j+1,m_ExcelOptFun.m_ItemInfo[0][j]);
			strText+=strError;
		}else
		{
			//��Ч�ֶ� Ӧ���ز���List�����±�//
			//���ں�Excel�ֶε�˳��///
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

	char *ColName[] = {"���","��״̬","�����ͺ�","�����������","��Ʒ����",
		"��Ʒ����","����","��Ʒ���","��Ʒ�׶�","����",
		"��������","�����鳤","����Ա����","���첿��","����Ա",
		"�������","��������1","��������2","��������3","��������4",
		"��������5","������","����������","����������","�������ǩ��",
		"�����������","��Ʒ����","��Ʒ��������","���첿���쵼���","���첿���쵼ǩ��",
		"���첿���쵼ǩ������","����Ա���","����Աǩ��","����Ա����","��ע"};

	for(int j = 1;j<MaxCol;j++)
	{
		if(!strcmp(strText,ColName[j]))
		{
			//����ֵ����0 ֤������Ч�ֶ�///
			//�ҵ���Ч�ֶ� ��������Ӧ��List���±�///
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
	// TODO: �ڴ����ר�ô����/����û���
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
	LoadXlsTaskInfo( );					//��Excel�������������Ϣ

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

	splictPos = str.Find(SPLICT_CHAR_HUANG_HANG);  //����
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
	//��Ʒ����_���ݴ���
	splictPos = str.Find(SPLICT_CHAR_XIE_GANG);  //�ַ���'/'
	if (splictPos != -1)
	{
		str1 = str.Left(splictPos);
		str2 = str.Right(nLen-splictPos-1);

		bFindFlag1 = 0;
		nLen1 = strlen(str1.GetBuffer(0));
		nPos1 = str1.Find(SPLICT_CHAR_HENG_GANG);	 //�ַ���'-'
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

	splictPos1 = strTmp.Find(SPLICT_CHAR_HENG_GANG);	 //�ַ���'-'
	if (splictPos1 != -1)
	{
		strTmp  = strTmp.Right(nTmpLen-splictPos1-1);
		nTmpLen = strTmp.GetLength();
		splictPos2 =  strTmp.Find(SPLICT_CHAR_HENG_GANG);	 //�ַ���'-'
		if (splictPos2 != -1)
		{
			bHaveSeries = 1;
			nSeriesPos  = splictPos1+1+splictPos2;
		}
	}
	else
	{
		str.Format("�Ƿ��Ĳ�Ʒ���Ÿ�ʽ:%s", strProductAll);
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
				strErr.Format(_T("�������ֵ����! nArrayPos=%d, nMaxCnt"), nArrayPos, nMaxCnt);
				AfxMessageBox(strErr);
				return 0;
			}
			strArray[nArrayPos++] = strHead;
		}
	}

	nCnt = nArrayPos;

	return 1;
}


int CLoadTaskInfo::GetProductCodeFromSrcCodeList(int nCodeCnt, char *szSrcCodeList)					//��ȡ��Ʒ����б�
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
		strErr.Format("��Ÿ�������: nCodePos=%d, nMax=%d, �������ֵ����!", nCodePos, MAX_PIC_NUM_CNT);
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

	//1.��ȡ�����
	nGrpCnt = 0;
	ret = GetStrArrayFormStrList(strCodeList.GetBuffer(0), SPLICT_CHAR_FEN_HAO, XLS_LOAD_MAX_GRP_CNT, nGrpCnt, strGrpArray);
	if (ret == 0)
	{
		return 0;
	}

	strItemHead = "";

	for (i=0; i<nGrpCnt; i++)
	{
	
		//1.1��ȡ���ڶθ���
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
							strErr.Format("��Ÿ�������: nCodePos=%d, nMax=%d, �������ֵ����!", nCodePos, MAX_PIC_NUM_CNT);
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
							strErr.Format("��Ÿ�������: nCodePos=%d, nMax=%d, �������ֵ����!", nCodePos, MAX_PIC_NUM_CNT);
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
					strErr.Format("��Ÿ�������: nCodePos=%d, nMax=%d, �������ֵ����!", nCodePos, MAX_PIC_NUM_CNT);
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
		str.Format("Error, ��Ÿ�������, ԭʼ����=%d, ���������%s, ������=%d", nCodeCnt, szSrcCodeList, nCodePos);
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
	if (strcmp(str.GetBuffer(0), _T("��")) == 0)
	{
		nType = 1;
	}
	else
	{
		nType = 0;
	}
	return nType;
}

int CLoadTaskInfo::LoadXlsTaskInfo( )					//��Excel�������������Ϣ
{
	CListCtrl *pList = &m_TaskList;

	CString   str, strSum;
	CString   strProductNo, strProductCode, strPicNo, strPicName;
	CString   strProjectNo, strProductName, strModelNo, strPhase, strDianShiQty;
	CString   strSumCode, strSumPicNo, strSumPicName;
	CString   strTmpTaskName;
	int       nCodeCnt, nPicNoCnt;
	StBasProduct	stBasProduct, *pStBasProduct;		//��Ʒ��Ϣ
	//StBasSeries		stBasSeries,  *pStBasSeries;        //��Ʒϵ����Ϣ
	StBasPicNum     stBasPicNum,  *pStBasPicNum;        //��Ʒͼ����Ϣ
	StBasTask		stBasTask,	  *pStBaseTask;			//������Ϣ
	StBasTaskBaseInfo *pStBasTaskBaseInfo;
	StBasTaskCode	stBasTaskCode, *pStBasTaskCode;		//��������Ϣ
	StBasTaskPicNum stBasTaskPicNum, *pStBasTaskPicNum;	//����ͼ����Ϣ

	int       nTaskOid, nTaskCnt, nTaskPos;
	int		  i,j, nProdPos, nCnt;

	int       nCurGroupOid = 1;							//����OID
	char     szCreateTime[DB_USER_LEN] = {0,};			//����ʱ��
	char     szCreateUser[DB_USER_LEN] ={0,};			//������
	
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

	//����OID
	nCurGroupOid = g_CurSelDepart.nOid;   //ע�⣺��ȫ�ֱ�����ʼ��, ����OID

	//��������
	GetSysDateTime(szCreateTime);



	char *ColName[] = {"���","��״̬","�����ͺ�","�����������","��Ʒ����",
		"��Ʒ����","����","��Ʒ���","��Ʒ�׶�","����",
		"��������","�����鳤","����Ա����","���첿��","����Ա",
		"�������","��������1","��������2","��������3","��������4",
		"��������5","������","����������","����������","�������ǩ��",
		"�����������","��Ʒ����","��Ʒ��������","���첿���쵼���","���첿���쵼ǩ��",
		"���첿���쵼ǩ������","����Ա���","����Աǩ��","����Ա����","��ע"};


    /*
	nProdPos  = 0;	//��Ʒ����
	nTaskPos  = 0;   //�������
	nCodeCnt  = 0;	//��Ÿ���
	nPicNoCnt = 0;  //ͼ�Ÿ���
	strSumCode	  = "";
	strSumPicNo   = "";
	strSumPicName = "";
	*/

	pStBasProduct = &stBasProduct;		//��Ʒ��Ϣ
	//pStBasSeries  = &stBasSeries;		//��Ʒϵ����Ϣ 
	pStBasPicNum  = &stBasPicNum;		//��Ʒͼ����Ϣ
	pStBaseTask	  = &stBasTask;			//������Ϣ
	pStBasTaskBaseInfo = &pStBaseTask->stTaskBaseInfo; //����Ļ�����Ϣ///
	pStBasTaskCode= &stBasTaskCode;		//��������Ϣ
	pStBasTaskPicNum = &stBasTaskPicNum;	//����ͼ����Ϣ


	//1.��ȡ�������������Ϣ
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

		//��¼��Ʒ��Ϣ
		memset( (char*)pXlsBasTask, 0, sizeof(XlsBasTask));

		strSrcProductNo   = strArray[5];   //��Ʒ����+ϵ�к�
		strSrcProductCode = strArray[7];   //��Ʒ���

		nCodeNumber = atoi(strArray[6].GetBuffer(0)); //��Ʒ���_����

		//1.1��ȡ��Ʒ����
		memset(szProductNo,		0, DB_NAME_LEN);
		memset(szProductSeries, 0, DB_NAME_LEN);

		if (i == 23)
		{
			i = i;
		}

		ret = GetProductNoFromSrcProductNo(strSrcProductNo.GetBuffer(0), szProductNo, szProductSeries);	//��ȡ��Ʒ���ţ�ϵ�к�
		if (ret == 0)
		{
			continue;
		}

		//��Ʒ���Ŵ���
		str.Format("��Ʒ���ţ�nTaskPos=%02d, Product_no=%s, ��Ʒ����=%s, ��Ʒϵ�к�=%s",
			i+1, strSrcProductNo, szProductNo, szProductSeries);
		g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);


		//1.2��ȡ��Ʒ����б�
		ClearCodeNameInfo( );
		ret = GetProductCodeFromSrcCodeList(nCodeNumber, strSrcProductCode.GetBuffer(0));
		if (ret != 0)
		{
			//�Ա�����ֵ: pXlsBasTask 
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
			str.Format("��Ʒ���ţ�nTaskPos=%02d, Product_no=%s, nCodeNumber=%d,nCodeCnt=%d",
				i+1, strSrcProductNo, nCodeNumber, m_nCodeCnt);
			g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
			//2.
			str.Format("ԭʼ���: ��Ÿ���=%d, �������=%s", nCodeNumber, strSrcProductCode);
			g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
			//3.
			str.Format("������: ��Ÿ���=%d, ����б�=%s", m_nCodeCnt, strSum);
			g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
		}
		else
		{
			bErrFlag = 1;
			break;
		}

		//------------------------------------------------------------------------------

		//UINT	nOid;						      							//01.����OID
		//strcpy(pXlsBasTask->szTaskName,	strArray[3].GetBuffer(0));		//02.��������   [3]
		strcpy(pXlsBasTask->szProjectNo,	strArray[3].GetBuffer(0));		//03.���鵥��
		//UINT	nTaskStatus;						//04.����״̬
		//UINT	nTaskType;	      	                //05.��������
		strcpy(pXlsBasTask->szModel,		strArray[8].GetBuffer(0));		//06.�ͺ�
		strcpy(pXlsBasTask->szPhase,		strArray[2].GetBuffer(0));		//07.�׶�
		//UINT	nProductOid;	      	            //08.��ƷOID
	
		strcpy(pXlsBasTask->szProductName,	strArray[4].GetBuffer(0));	    //09.��Ʒ����
	
		strcpy(pXlsBasTask->szProductNo,	szProductNo);					//10.��Ʒ����

		//ztedit for 2017-03-23
		pStBaseTask->stTaskBaseInfo.nSeriesOid = 0;						
		strcpy(pStBaseTask->stTaskBaseInfo.szSeriesName,	"");
		//pXlsBasTask->nSeriesOid;											//11.��Ʒϵ�к�OID
		//strcpy(pXlsBasTask->szSeriesName,	szProductSeries);				//12.��Ʒϵ�к�����


		//pXlsBasTask->szProductCode[DB_NAME_LEN];							//13.��Ʒ���
		pXlsBasTask->nCodeNumber = nCodeNumber;								//14.����
		//pXlsBasTask->szBatch[DB_NAME_LEN];		    //15.���κ�
		//UINT    nGroupOid;		                	//16.���첿��
		strcpy(pXlsBasTask->szGroupName,	strArray[13].GetBuffer(0));		//16_1 ���첿������
		strcpy(pXlsBasTask->szUpUser,		strArray[21].GetBuffer(0));		//17.������
		//strcpy(pXlsBasTask->szUpDate,		strArray[22].GetBuffer(0));		//18.��������
		//char    szSendDate[DB_USER_LEN];			//19.�·�����
		strcpy(pXlsBasTask->szCheckLeader,	strArray[11].GetBuffer(0));		//20.�����鳤
		strcpy(pXlsBasTask->szCheckUser,	strArray[12].GetBuffer(0));		//21.����Ա����
		strcpy(pXlsBasTask->szTechUser,		strArray[14].GetBuffer(0));		//22.����Ա 
		pXlsBasTask->nArmyTest=GetArmyTestValue(strArray[9].GetBuffer(0));	//23.����
		pXlsBasTask->nDianShiNum = atoi(strArray[10].GetBuffer(0));			//24.��������
		strcpy(pXlsBasTask->szAccording1,	strArray[16].GetBuffer(0));		//25.��������1
		strcpy(pXlsBasTask->szAccording2,	strArray[17].GetBuffer(0));		//26.��������2
		strcpy(pXlsBasTask->szAccording3,	strArray[18].GetBuffer(0));		//27.��������3
		strcpy(pXlsBasTask->szAccording4,	strArray[19].GetBuffer(0));		//28.��������4
		strcpy(pXlsBasTask->szAccording5,	strArray[20].GetBuffer(0));		//29.��������5
		strcpy(pXlsBasTask->szTaskRemark,	strArray[34].GetBuffer(0));		//30.��ע
		//char    szPlanBegTime[DB_USER_LEN];			//31.�ƻ���ʼʱ��
		//char    szPlanEndTime[DB_USER_LEN];			//32.�ƻ�����ʱ��
		//char    szRealBegTime[DB_USER_LEN];			//33.ʵ�ʿ�ʼʱ��
		//char    szRealEndTime[DB_USER_LEN];			//34.ʵ�ʽ���ʱ��

		m_XlsBasTaskInfo.push_back(xlsBasTask);

		nTaskPos++;		

	}
	m_nXlsBasTaskCnt = nTaskPos;

	
	
	if (bErrFlag != 0)
	{
		str.Format("�쳣�˳��������������=%d, ��ǰ�к�=%d", nTaskPos+1, i+1);
		AfxMessageBox(str);	
		return 0;
	}

	str.Format("�������=%d", nTaskPos);
	AfxMessageBox(str);	

	// return 0;



	//4.���룺��Ʒ��Ϣ, ��Ʒϵ����Ϣ, ������Ϣ, �����ţ� ��Ʒͼ�ţ�����ͼ��
	//4.1   �����Ʒ��Ϣ
	//4.2   �����Ʒϵ����Ϣ
	//4.3   ����������Ϣ
	//4.3.1 ������������Ϣ
	//4.3.2 �����Ʒͼ����Ϣ
	//4.3.3 ��������ͼ����Ϣ
	//-------------------------------------------------------------------------------
	nTaskCnt = m_nXlsBasTaskCnt;
	for (i=0; i<nTaskCnt; i++)
	{
		pCurXlsBasTask = &m_XlsBasTaskInfo.at(i);

		//4.1 �����Ʒ��Ϣ(1)
		//--------------------------------------------------------------------------------------
		memset(pStBasProduct, 0, sizeof(StBasProduct));
		//UINT	nOid;						      								//01.��Ʒ����OID
		strcpy(pStBasProduct->szProductNo, pCurXlsBasTask->szProductNo);		//02.��Ʒ����
		strcpy(pStBasProduct->szProductName, pCurXlsBasTask->szProductName);	//03.��Ʒ����
		pStBasProduct->nPicNumType = Product_normal;							//05.ͼ������:0.��ͼ��(��ͨ��Ʒ),1.��ͼ��(����)
		pStBasProduct->nGroupOid   = nCurGroupOid;								//06.���ڲ���OID
		strcpy(pStBasProduct->szCreateTime, szCreateTime);						//07.����ʱ��
		strcpy(pStBasProduct->szCreateUser, szCreateUser);						//08.������

		//4.1��Ʒ����
		//--------------------------------------------------------------------------------------
		bProdExist = m_DMng.IsProdExists(nCurGroupOid, pStBasProduct->szProductNo);
		if (bProdExist == 0)  
		{
			ret = m_DMng.AddNewProd(pStBasProduct);
			if (ret != 0)
			{
				AddNewProductToConfig(pStBasProduct);
				str.Format("DB_OPT_����_��Ʒ����_�ɹ���nProdPos=%d, Product_no=%s", 
					i+1, pCurXlsBasTask->szProductNo);
				g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
			}
			else
			{
				str.Format("DB_ERR_����_��Ʒ����_�쳣��nProdPos=%d, Product_no=%s", 
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
				str.Format("DB_OPT_����_��Ʒ����_�����Ѵ��ڣ�nProdPos=%d, Product_no=%s", 
							 i+1, pCurXlsBasTask->szProductNo);
				g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
			}
			else
			{
				str.Format("DB_ERR_����_��Ʒ����_��ȡ�쳣��nProdPos=%d, Product_no=%s", 
						i+1, pCurXlsBasTask->szProductNo);
				g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
				AfxMessageBox(str);
				return 0;
			}
		}

	

		//4.2 ����������Ϣ
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

		
		//UINT	nOid;						      							//01.����OID
		strcpy(pStBaseTask->stTaskBaseInfo.szTaskName, strTmpTaskName);					//02.��������
		strcpy(pStBaseTask->stTaskBaseInfo.szProjectNo,	pCurXlsBasTask->szProjectNo);	//03.���鵥��
		//UINT	nTaskStatus;												//04.����״̬
		//UINT	nTaskType;	      											//05.��������
		strcpy(pStBaseTask->stTaskBaseInfo.szModel,		pCurXlsBasTask->szModel);		//06.�ͺ�
		strcpy(pStBaseTask->stTaskBaseInfo.szPhase,		pCurXlsBasTask->szPhase);		//07.�׶�
		pStBaseTask->stProductInfo.nOid =	pStBasProduct->nOid;					//08.��ƷOID
		strcpy(pStBaseTask->stProductInfo.szProductName,	pCurXlsBasTask->szProductName);	//09.��Ʒ����
		strcpy(pStBaseTask->stProductInfo.szProductNo,	pCurXlsBasTask->szProductNo);	//10.��Ʒ����
		
		//ztedit for 2017-03-23
		pStBaseTask->stTaskBaseInfo.nSeriesOid = 0;						//11.��Ʒϵ�к�OID
		strcpy(pStBaseTask->stTaskBaseInfo.szSeriesName, "");
		//pStBaseTask->stTaskBaseInfo.nSeriesOid = pStBasSeries->nOid;						//11.��Ʒϵ�к�OID
		//strcpy(pStBaseTask->stTaskBaseInfo.szSeriesName,	pStBasSeries->szSeriesName);	//12.��Ʒϵ�к�����
		
		//char    szProductCode[DB_USER_LEN];								//13.��Ʒ���
		pStBaseTask->stTaskBaseInfo.nCodeNumber = pCurXlsBasTask->nCodeCnt;				//14.����
		//char    szBatch[DB_USER_LEN];		       							//15.���κ�
		pStBaseTask->stTaskBaseInfo.nGroupOid = nCurGroupOid;								//16.���첿��
		strcpy(pStBaseTask->stTaskBaseInfo.szGroupName,	pCurXlsBasTask->szGroupName);	//16_1 ���첿������
		strcpy(pStBaseTask->stTaskBaseInfo.szUpUser,		pCurXlsBasTask->szUpUser);		//17.������
		//strcpy(pStBaseTask->szUpDate,		pCurXlsBasTask->szUpUser);		//18.��������
		//char    szSendDate[DB_USER_LEN];									//19.�·�����
		strcpy(pStBaseTask->stTaskBaseInfo.szCheckLeader,	pCurXlsBasTask->szCheckLeader);	//20.�����鳤
		strcpy(pStBaseTask->stTaskBaseInfo.szCheckUser, 	pCurXlsBasTask->szCheckUser);	//21.����Ա����
		strcpy(pStBaseTask->stTaskBaseInfo.szTechUser,		pCurXlsBasTask->szTechUser);	//22.����Ա 
		pStBaseTask->stTaskBaseInfo.nArmyTest = pCurXlsBasTask->nArmyTest;					//23.����
		pStBaseTask->stTaskBaseInfo.nDianShiNum = pCurXlsBasTask->nDianShiNum;				//24.��������
		strcpy(pStBaseTask->stTaskBaseInfo.szAccording1,	pCurXlsBasTask->szAccording1);	//25.��������1
		strcpy(pStBaseTask->stTaskBaseInfo.szAccording2,	pCurXlsBasTask->szAccording2);	//26.��������2
		strcpy(pStBaseTask->stTaskBaseInfo.szAccording3,	pCurXlsBasTask->szAccording3);	//27.��������3
		strcpy(pStBaseTask->stTaskBaseInfo.szAccording4,	pCurXlsBasTask->szAccording4);	//28.��������4
		strcpy(pStBaseTask->stTaskBaseInfo.szAccording5,	pCurXlsBasTask->szAccording5);	//29.��������5
		strcpy(pStBaseTask->stTaskBaseInfo.szTaskRemark,	pCurXlsBasTask->szTaskRemark);	//30.��ע
		//char    szPlanBegTime[DB_USER_LEN];			//31.�ƻ���ʼʱ��
		//char    szPlanEndTime[DB_USER_LEN];			//32.�ƻ�����ʱ��
		//char    szRealBegTime[DB_USER_LEN];			//33.ʵ�ʿ�ʼʱ��
		//char    szRealEndTime[DB_USER_LEN];			//34.ʵ�ʽ���ʱ��

		
		//--------------------------------------------------------------------------------------
		bTaskExist = m_DMng.IsProductTaskExists(pStBasProduct->nOid, strTmpTaskName.GetBuffer(0));
		if (bTaskExist == 0)
		{
			ret = m_DMng.AddNewTask(pStBaseTask);
			if (ret != 0)
			{
				str.Format("DB_OPT_����_����_�ɹ���nTaskPos=%d, Product_no=%s, Project_name=%s, nCodeCnt=%d",
					 i+1, pCurXlsBasTask->szProductNo, pCurXlsBasTask->szProjectNo, pCurXlsBasTask->nCodeCnt);
				g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
			}
			else
			{
				str.Format("DB_ERR_����_����_�쳣��nTaskPos=%d, Product_no=%s, Project_name=%s, nCodeCnt=%d",
					i+1, pCurXlsBasTask->szProductNo, pCurXlsBasTask->szProjectNo, pCurXlsBasTask->nCodeCnt);
				g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
				AfxMessageBox(str);
				return 0;
			}

			//4.3.1 ������������Ϣ
			//--------------------------------------------------------------------------------------
			for (j=0; j<pCurXlsBasTask->nCodeCnt; j++)
			{
				memset(pStBasTaskCode, 0, sizeof(StBasTaskCode));

				//UINT nOid;															//01.������OID
				pStBasTaskCode->nTaskOid = pStBaseTask->stTaskBaseInfo.nOid;							//02.����OID
				pStBasTaskCode->nCodeIndex = j+1;										//03.�����ڱ��˳���1��ʼ
				pStBasTaskCode->nDianshiTest = 0;										//04.�Ƿ����
				strcpy(pStBasTaskCode->szCodeName, pCurXlsBasTask->szCodeNameArray[j]);	//05.�������

				ret = m_DMng.AddNewTaskCode(pStBasTaskCode);
				if (ret != 0)
				{
					str.Format("DB_OPT_����_������_�ɹ���nTaskPos=%d, Product_no=%s, nCodeIndex=%d, szCodeName=%s",
						i+1, pCurXlsBasTask->szProductNo, pStBasTaskCode->nCodeIndex, pStBasTaskCode->szCodeName);
					g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
				}
				else
				{
					str.Format("DB_ERR_����_������_�쳣��nOid=%d, nTaskPos=%d, Product_no=%s, nCodeIndex=%d, szCodeName=%s",
						i+1, pCurXlsBasTask->szProductNo, pStBasTaskCode->nCodeIndex, pStBasTaskCode->szCodeName);
					g_pLogInfo->WriteLogFile("nPos=%04d, %s", ++g_nPos, str);
					AfxMessageBox(str);
					return 0;
				}
			}
		}
		//--------------------------------------------------------------------------------------


	} //end for (i=0; i<nTaskCnt; i++)


	str.Format("����������!");
	AfxMessageBox(str);	


	m_XlsBasTaskInfo.clear();
	m_nXlsBasTaskCnt = 0;

	return 1;
}
