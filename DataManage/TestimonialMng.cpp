// TestimonialMng.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataManage.h"
#include "TestimonialMng.h"
#include "MainFrm.h"


// CTestimonialMng �Ի���

IMPLEMENT_DYNAMIC(CTestimonialMng, CDialog)

CTestimonialMng::CTestimonialMng(CWnd* pParent /*=NULL*/)
	: CDialog(CTestimonialMng::IDD, pParent)
{
	m_StrTestimonialInfo.Relese();
}

CTestimonialMng::~CTestimonialMng()
{
}

void CTestimonialMng::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_TestTree);
}


BEGIN_MESSAGE_MAP(CTestimonialMng, CDialog)
	ON_WM_SIZE()
	ON_NOTIFY(NM_CLICK, IDC_TREE1, &CTestimonialMng::OnNMClickTree1)
END_MESSAGE_MAP()


// CTestimonialMng ��Ϣ�������

BOOL CTestimonialMng::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CTreeCtrl *pTree = &m_TestTree;
	int nIcons[] = {
		IDI_LEV_1,  IDI_LEV_2,  IDI_LEV_3,	IDI_LEV_4 	// 0 - 4�� Ŀ¼������
	};

	m_TreeImgList.Create(16,16,ILC_COLOR32 | ILC_MASK,0,0);
	for(int i=0; i<sizeof(nIcons); i++)
	{
		m_TreeImgList.Replace(-1, LoadIcon(::AfxGetInstanceHandle(), 
			MAKEINTRESOURCE(nIcons[i])));
	}

	pTree->SetImageList(&m_TreeImgList, TVSIL_NORMAL);
	pTree->SetItemHeight(20);

	m_Page1.Create(IDD_TESTIMONIAL_PAGE1_DLG, this);
	m_Page1.ShowWindow(SW_SHOW);
	m_Page2.Create(IDD_TESTIMONIAL_PAGE2_DLG, this);
	m_Page2.ShowWindow(SW_HIDE);
	m_Page3.Create(IDD_TESTIMONIAL_PAGE3_DLG, this);
	m_Page3.ShowWindow(SW_HIDE);
	m_Page4.Create(IDD_TESTIMONIAL_PAGE4_DLG, this);
	m_Page4.ShowWindow(SW_HIDE);
	m_Page5.Create(IDD_TESTIMONIAL_PAGE5_DLG, this);
	m_Page5.ShowWindow(SW_HIDE);
	m_Page6.Create(IDD_TESTIMONIAL_PAGE6_DLG, this);
	m_Page6.ShowWindow(SW_HIDE);
	m_Page7.Create(IDD_TESTIMONIAL_PAGE7_DLG, this);
	m_Page7.ShowWindow(SW_HIDE);
	m_Page8.Create(IDD_TESTIMONIAL_PAGE8_DLG, this);
	m_Page8.ShowWindow(SW_HIDE);
	m_Page9.Create(IDD_TESTIMONIAL_PAGE9_DLG, this);
	m_Page9.ShowWindow(SW_HIDE);
	m_Page10.Create(IDD_TESTIMONIAL_PAGE10_DLG, this);
	m_Page10.ShowWindow(SW_HIDE);
	m_Page11.Create(IDD_TESTIMONIAL_PAGE11_DLG, this);
	m_Page11.ShowWindow(SW_HIDE);

	m_Page5.m_pModeParMng = &g_MainFram->m_ModeParMng;
	m_Page5.m_pModeXmlAnalysis = &g_MainFram->m_ModeXmlAnalysis;


	m_Page6.m_pModeParMng = &g_MainFram->m_ModeParMng;
	m_Page6.m_pModeXmlAnalysis = &g_MainFram->m_ModeXmlAnalysis;

	m_Page7.m_pModeParMng = &g_MainFram->m_ModeParMng;
	m_Page7.m_pModeXmlAnalysis = &g_MainFram->m_ModeXmlAnalysis;

	m_Page8.m_pModeParMng = &g_MainFram->m_ModeParMng;
	m_Page8.m_pModeXmlAnalysis = &g_MainFram->m_ModeXmlAnalysis;

	m_Page9.m_pModeParMng = &g_MainFram->m_ModeParMng;
	m_Page9.m_pModeXmlAnalysis = &g_MainFram->m_ModeXmlAnalysis;

	m_Page10.m_pModeParMng = &g_MainFram->m_ModeParMng;
	m_Page10.m_pModeXmlAnalysis = &g_MainFram->m_ModeXmlAnalysis;

	m_Page11.m_pModeParMng = &g_MainFram->m_ModeParMng;
	m_Page11.m_pModeXmlAnalysis = &g_MainFram->m_ModeXmlAnalysis;


	m_Page1.m_pPage1Info = &m_StrTestimonialInfo.stPage1;
	m_Page2.m_pPage2Info = &m_StrTestimonialInfo.stPage2;
	m_Page3.m_pPage3Info = &m_StrTestimonialInfo.stPage3;
	m_Page4.m_pPage4Info = &m_StrTestimonialInfo.stPage4;
	m_Page5.m_pPage5Info = &m_StrTestimonialInfo.stPage5;
	m_Page6.m_pPage6Info = &m_StrTestimonialInfo.stPage6;
	m_Page7.m_pPage7Info = &m_StrTestimonialInfo.stPage7;
	m_Page8.m_pPage8Info = &m_StrTestimonialInfo.stPage8;
	m_Page9.m_pPage9Info = &m_StrTestimonialInfo.stPage9;
	m_Page10.m_pPage10Info = &m_StrTestimonialInfo.stPage10;
	m_Page11.m_pPage11Info = &m_StrTestimonialInfo.stPage11;

	MoveWindow(0, 0,1214, 713);
	CenterWindow();

	PostMessage(WM_SIZE);
	InitTestimomialTree();

	InitTestimomialInfo();
	DisPlayPagesInfo();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CTestimonialMng::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialog::OnOK();
}

void CTestimonialMng::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	AutoSize();
}

void CTestimonialMng::AutoSize()
{
	CString str;
	CRect Rect ;
	GetClientRect(&Rect) ;

	//����ͨ�ñ�׼ B5ֽ 182mm * 257mm//
	int nxshu = 4;
	int nB5Width = 257;
	int nB5Height = 182;

	int nTreeWidth = 250;
	int nBtnWidth = 80;
	int nBtnHeight = 30;

	


	if(GetDlgItem(IDC_STATIC1)->GetSafeHwnd())
	{
		GetDlgItem(IDC_STATIC1)->MoveWindow(5, 5, nTreeWidth+(5*2), Rect.Height()-(5*2));
	}
	if(m_TestTree.GetSafeHwnd())
	{
		m_TestTree.MoveWindow(5+5,5+20,nTreeWidth,Rect.Height()-(5+20+10));
	}

	CRect rcRect;

	if(GetDlgItem(IDC_STATIC2)->GetSafeHwnd())
	{
		GetDlgItem(IDC_STATIC2)->MoveWindow((5+nTreeWidth+5)+10, 5, nB5Width*nxshu-98, nB5Height*nxshu-59);

		GetDlgItem(IDC_STATIC2)->GetWindowRect(&rcRect);

		str.Format(_T("���� ��=%d, ��+%d  B5 ��=%d ��=%d"), Rect.Width(), Rect.Height(), rcRect.Width(), rcRect.Height());
		if(GetDlgItem(IDC_STATIC3)->GetSafeHwnd())
		{
			GetDlgItem(IDC_STATIC3)->SetWindowText(str);
		}

	}


	if(m_Page1.GetSafeHwnd())
	{
		m_Page1.MoveWindow((5+nTreeWidth+5)+10, 5, nB5Width*nxshu-98, nB5Height*nxshu-59);
	}

	if(m_Page2.GetSafeHwnd())
	{
		m_Page2.MoveWindow((5+nTreeWidth+5)+10, 5, nB5Width*nxshu-98, nB5Height*nxshu-59);
	}
	

	if(m_Page3.GetSafeHwnd())
	{
		m_Page3.MoveWindow((5+nTreeWidth+5)+10, 5, nB5Width*nxshu-98, nB5Height*nxshu-59);
	}

	if(m_Page4.GetSafeHwnd())
	{
		m_Page4.MoveWindow((5+nTreeWidth+5)+10, 5, nB5Width*nxshu-98, nB5Height*nxshu-59);
	}

	if(m_Page5.GetSafeHwnd())
	{
		m_Page5.MoveWindow((5+nTreeWidth+5)+10+5, 5+20, nB5Width*nxshu-(98+10), nB5Height*nxshu-(59+20));
	}
	if(m_Page6.GetSafeHwnd())
	{
		m_Page6.MoveWindow((5+nTreeWidth+5)+10+5, 5+20, nB5Width*nxshu-(98+10), nB5Height*nxshu-(59+20));
	}
	
	if(m_Page7.GetSafeHwnd())
	{
		m_Page7.MoveWindow((5+nTreeWidth+5)+10+5, 5+20, nB5Width*nxshu-(98+10), nB5Height*nxshu-(59+20));
	}
	

	if(m_Page8.GetSafeHwnd())
	{
		m_Page8.MoveWindow((5+nTreeWidth+5)+10+5, 5+20, nB5Width*nxshu-(98+10), nB5Height*nxshu-(59+20));
	}

	if(m_Page9.GetSafeHwnd())
	{
		m_Page9.MoveWindow((5+nTreeWidth+5)+10+5, 5+20, nB5Width*nxshu-(98+10), nB5Height*nxshu-(59+20));
	}

	if(m_Page10.GetSafeHwnd())
	{
		m_Page10.MoveWindow((5+nTreeWidth+5)+10+5, 5+20, nB5Width*nxshu-(98+10), nB5Height*nxshu-(59+20));
	}

	if(m_Page11.GetSafeHwnd())
	{
		m_Page11.MoveWindow((5+nTreeWidth+5)+10+5, 5+20, nB5Width*nxshu-(98+10), nB5Height*nxshu-(59+20));
	}
	
	
}

void CTestimonialMng::InitTestimomialTree()
{
	HTREEITEM hParent,hParent1,hParent2,hParent3;
	CTreeCtrl *pTree = &m_TestTree;
	pTree->DeleteAllItems();

	int nTreeID;
	int nNum = 0;
	CString strText,strGroupName;

	int nIcon = 1;
	strGroupName = g_CurSelDepart.szGroupName;
	UINT nGroupOid = g_CurSelDepart.nOid;

	//��  ֤�����ʽ//
	strText.Format(_T("%s"), _T("֤�����ʽ"));
	if(NumTwoToOne(nTreeID,TESTIMONIAL_TREE_PAGE1,0))
	{
		hParent1 = MyInsertTree(pTree,strText,TVI_ROOT,nTreeID,0,0);

	}


	//��һҳ  ����//
	strText.Format(_T("1.%s"), g_TestimonialPage[Testimonial_Page1]);
	if(NumTwoToOne(nTreeID,TESTIMONIAL_TREE_PAGE1,0))
	{
		hParent = hParent2 = MyInsertTree(pTree,strText,hParent1,nTreeID,nIcon,nIcon);
		
	}
	
	//�ڶ�ҳ  ��д��ʹ�ù���/
	strText.Format(_T("2.%s"), g_TestimonialPage[Testimonial_Page2]);
	if(NumTwoToOne(nTreeID,TESTIMONIAL_TREE_PAGE2,0))
	{
		hParent2 = MyInsertTree(pTree,strText,hParent1,nTreeID,nIcon,nIcon);

	}

	//����ҳ  Ŀ¼//
	strText.Format(_T("3.%s"), g_TestimonialPage[Testimonial_Page3]);
	if(NumTwoToOne(nTreeID,TESTIMONIAL_TREE_PAGE3,0))
	{
		hParent2 = MyInsertTree(pTree,strText,hParent1,nTreeID,nIcon,nIcon);

	}

	//����ҳ  ��Ʒ�ϸ����//
	strText.Format(_T("4.%s"), g_TestimonialPage[Testimonial_Page4]);
	if(NumTwoToOne(nTreeID,TESTIMONIAL_TREE_PAGE4,Page4_Type1))
	{
		hParent2 = MyInsertTree(pTree,strText,hParent1,nTreeID,nIcon,nIcon);


		//����ҳ ��ʽ1//
		strText.Format(_T("4_1.%s"), _T("��ʽ1"));
		if(NumTwoToOne(nTreeID,TESTIMONIAL_TREE_PAGE4,Page4_Type1))
		{
			hParent3 = MyInsertTree(pTree,strText,hParent2,nTreeID,nIcon+1,nIcon+1);

		}
		//����ҳ ��ʽ2//
		strText.Format(_T("4_2.%s"), _T("��ʽ2"));
		if(NumTwoToOne(nTreeID,TESTIMONIAL_TREE_PAGE4,Page4_Type2))
		{
			hParent3 = MyInsertTree(pTree,strText,hParent2,nTreeID,nIcon+1,nIcon+1);

		}
		//����ҳ ��ʽ3//
		strText.Format(_T("4_3.%s"), _T("��ʽ3"));
		if(NumTwoToOne(nTreeID,TESTIMONIAL_TREE_PAGE4,Page4_Type3))
		{
			hParent3 = MyInsertTree(pTree,strText,hParent2,nTreeID,nIcon+1,nIcon+1);

		}

		pTree->Expand(hParent2,TVE_EXPAND);
	}

	//����ҳ ��Ʒ���ױ�//
	strText.Format(_T("5.%s"), g_TestimonialPage[Testimonial_Page5]);
	if(NumTwoToOne(nTreeID,TESTIMONIAL_TREE_PAGE5,0))
	{
		hParent2 = MyInsertTree(pTree,strText,hParent1,nTreeID,nIcon,nIcon);

	}

	//����ҳ  ���Բ�Ʒ���������豸���嵥//
	strText.Format(_T("6.%s"), g_TestimonialPage[Testimonial_Page6]);
	if(NumTwoToOne(nTreeID,TESTIMONIAL_TREE_PAGE6,0))
	{
		hParent2 = MyInsertTree(pTree,strText,hParent1,nTreeID,nIcon,nIcon);

	}

	//����ҳ  ������ʱ����������¼//
	strText.Format(_T("7.%s"), g_TestimonialPage[Testimonial_Page7]);
	if(NumTwoToOne(nTreeID,TESTIMONIAL_TREE_PAGE7,0))
	{
		hParent2 = MyInsertTree(pTree,strText,hParent1,nTreeID,nIcon,nIcon);

	}

	//�ڰ�ҳ  ��Ʒ�������ܲ��Լ�¼//
	strText.Format(_T("8.%s"), g_TestimonialPage[Testimonial_Page8]);
	if(NumTwoToOne(nTreeID,TESTIMONIAL_TREE_PAGE8,0))
	{
		hParent2 = MyInsertTree(pTree,strText,hParent1,nTreeID,nIcon,nIcon);

	}

	//�ھ�ҳ  ͨ��ʱ���¼//
	strText.Format(_T("9.%s"), g_TestimonialPage[Testimonial_Page9]);
	if(NumTwoToOne(nTreeID,TESTIMONIAL_TREE_PAGE9,0))
	{
		hParent2 = MyInsertTree(pTree,strText,hParent1,nTreeID,nIcon,nIcon);

	}

	//��ʮҳ  ���Ӽ�¼//
	strText.Format(_T("10.%s"), g_TestimonialPage[Testimonial_Page10]);
	if(NumTwoToOne(nTreeID,TESTIMONIAL_TREE_PAGE10,0))
	{
		hParent2 = MyInsertTree(pTree,strText,hParent1,nTreeID,nIcon,nIcon);

	}

	//��ʮһҳ  �������//
	strText.Format(_T("11.%s"), g_TestimonialPage[Testimonial_Page11]);
	if(NumTwoToOne(nTreeID,TESTIMONIAL_TREE_PAGE11,0))
	{
		hParent2 = MyInsertTree(pTree,strText,hParent1,nTreeID,nIcon,nIcon);

	}

	//��ʮ��ҳ  ���//
	strText.Format(_T("12.%s"), g_TestimonialPage[Testimonial_Page12]);
	if(NumTwoToOne(nTreeID,TESTIMONIAL_TREE_PAGE12,0))
	{
		hParent2 = MyInsertTree(pTree,strText,hParent1,nTreeID,nIcon,nIcon);

	}

	pTree->SelectItem(hParent);
	pTree->SetFocus();
	pTree->Expand(hParent1,TVE_EXPAND);
}
void CTestimonialMng::InitTestimomialInfo(StBasTestimonial *pStTestimonialInfo)
{
	StBasTestimonial *pStTestimonialInfoTemp = &m_StrTestimonialInfo;
	pStTestimonialInfoTemp->Relese();

	//��һҳ//
	strcpy(pStTestimonialInfoTemp->stPage1.szTitle, _T("��  Ʒ  ֤  ��  ��"));
	strcpy(pStTestimonialInfoTemp->stPage1.szProductionUnit, _T("�й�����Ƽ����Ź�˾�ھ��о�Ժ���ߡ����о���"));
	strcpy(pStTestimonialInfoTemp->stPage1.szProductNo, _T("YH2-28A-2"));
	strcpy(pStTestimonialInfoTemp->stPage1.szProductName, _T("���ĳ�����"));
	strcpy(pStTestimonialInfoTemp->stPage1.szProductCode, _T("06-003"));
	strcpy(pStTestimonialInfoTemp->stPage1.szPhase, _T("S"));
	strcpy(pStTestimonialInfoTemp->stPage1.szLeaveFactoryDate, _T("2016  ��  9  ��  13  ��"));

	if(pStTestimonialInfo != NULL)
	{
		strcpy(pStTestimonialInfoTemp->stPage1.szProductNo, pStTestimonialInfo->stPage1.szProductNo);
		strcpy(pStTestimonialInfoTemp->stPage1.szProductName, pStTestimonialInfo->stPage1.szProductName);
		strcpy(pStTestimonialInfoTemp->stPage1.szProductCode, pStTestimonialInfo->stPage1.szProductCode);
		strcpy(pStTestimonialInfoTemp->stPage1.szPhase, pStTestimonialInfo->stPage1.szPhase);
		strcpy(pStTestimonialInfoTemp->stPage1.szLeaveFactoryDate, pStTestimonialInfo->stPage1.szLeaveFactoryDate);
	}

	//�ڶ�ҳ
	int pos = 0;
	strcpy(pStTestimonialInfoTemp->stPage2.szTitle, _T("��  д  ��  ʹ  ��  ��  ��"));
	pStTestimonialInfoTemp->stPage2.nCount = 12;

	strcpy(pStTestimonialInfoTemp->stPage2.szRules[pos++], _T("��Ʒ֤����Ӧ��¼��Ʒ���������䡢��š����ԡ�ʹ�õ�����������Ʒ��ת��"));
	strcpy(pStTestimonialInfoTemp->stPage2.szRules[pos++], _T("��Ʒ֤�����Ǽ����ղ�Ʒ������֮һ����Ʒ֤����δ��Ҫ����дʱ�����յ�λ�ɾ��ղ�Ʒ��"));
	strcpy(pStTestimonialInfoTemp->stPage2.szRules[pos++], _T("��Ʒ֤������й�����Ӧ��ʱ��׼ȷ��д�������й���Աǩ����ǩ�����ڵ�Ӧ�԰�λ���ֱ�ʾ���硱20141206����"));
	strcpy(pStTestimonialInfoTemp->stPage2.szRules[pos++], _T("��Ʒ֤��������д���ݿɴ�ӡ����д��ǩ��Ӧ�ú�ɫ������ɫīˮ�ʣ����������ּ�Ӧ��������������������Ϳ�Ļ�θġ����и���Ӧ���û��ķ�ʽ������Ȩ��Աǩ�£���ͬһ���������ظ����ģ�ͬһҳ���Ĳ��ó�����������ĳ��Ŀ���ݲ���Ҫ��дʱ��Ӧ�á�/����ʾ��"));
	strcpy(pStTestimonialInfoTemp->stPage2.szRules[pos++], _T("��Ʒ֤����Ӧװ���ɲᲢ��ҳ�Σ���ĳ��Ŀ����һҳ������дʱ����ҳ����Ӧͳһ����ҳ�Ρ�"));
	strcpy(pStTestimonialInfoTemp->stPage2.szRules[pos++], _T("��Ʒ֤����ͳһ����ҳ�Ρ�Ŀ¼���κ�����ҳ��Ӧ�ڡ�������ء���˵������ҳ��ҳ�ţ���Χ������Ҫ���ݣ�Ŀ¼���ڸ��ġ�"));

	strcpy(pStTestimonialInfoTemp->stPage2.szRules[pos++], _T("װ������������Ӧ��д�ڡ�������ء�ҳ�С�"));

	strcpy(pStTestimonialInfoTemp->stPage2.szRules[pos++], _T("��Ʒ֤���������Ҫ�� Q/Y1-2014 ����Ʒ֤�������ʹ��Ҫ��ִ�С�"));
	strcpy(pStTestimonialInfoTemp->stPage2.szRules[pos++], _T("��Ʒ֤���������Ҫ�� Q/Y1-2014 ����Ʒ֤�������ʹ��Ҫ��ִ�С�"));
	strcpy(pStTestimonialInfoTemp->stPage2.szRules[pos++], _T("��Ʒ֤���������Ҫ�� Q/Y1-2014 ����Ʒ֤�������ʹ��Ҫ��ִ�С�"));
	strcpy(pStTestimonialInfoTemp->stPage2.szRules[pos++], _T("��Ʒ֤���������Ҫ�� Q/Y1-2014 ����Ʒ֤�������ʹ��Ҫ��ִ�С�"));
	strcpy(pStTestimonialInfoTemp->stPage2.szRules[pos++], _T("��Ʒ֤���������Ҫ�� Q/Y1-2014 ����Ʒ֤�������ʹ��Ҫ��ִ�С�"));

	//����ҳ
	pos = 0;

	strcpy(pStTestimonialInfoTemp->stPage3.szTitle, _T("Ŀ        ¼"));
	pStTestimonialInfoTemp->stPage3.nCount = 12;

	strcpy(pStTestimonialInfoTemp->stPage3.szRules[pos++], _T("����"));
	strcpy(pStTestimonialInfoTemp->stPage3.szRules[pos++], _T("��д��ʹ�ù���"));
	strcpy(pStTestimonialInfoTemp->stPage3.szRules[pos++], _T("Ŀ¼"));
	strcpy(pStTestimonialInfoTemp->stPage3.szRules[pos++], _T("��Ʒ�ϸ����"));
	strcpy(pStTestimonialInfoTemp->stPage3.szRules[pos++], _T("��Ʒ���ױ�"));
	strcpy(pStTestimonialInfoTemp->stPage3.szRules[pos++], _T("���Բ�Ʒ������(�豸)�嵥"));

	strcpy(pStTestimonialInfoTemp->stPage3.szRules[pos++], _T("������ʱ����������¼"));

	strcpy(pStTestimonialInfoTemp->stPage3.szRules[pos++], _T("��Ʒ�������ܲ��Լ�¼"));
	strcpy(pStTestimonialInfoTemp->stPage3.szRules[pos++], _T("ͨ��ʱ���¼"));
	strcpy(pStTestimonialInfoTemp->stPage3.szRules[pos++], _T("���Ӽ�¼"));
	strcpy(pStTestimonialInfoTemp->stPage3.szRules[pos++], _T("�������"));
	strcpy(pStTestimonialInfoTemp->stPage3.szRules[pos++], _T("���"));

	//����ҳ//
	strcpy(pStTestimonialInfoTemp->stPage4.szTitle, _T("��  Ʒ  ��  ��  ��  ��"));

	//����ҳ//
	strcpy(pStTestimonialInfoTemp->stPage5.szTitle, _T("��  Ʒ  ��  ��  ��"));
	StBasPage5ProductSort nProdInfo;
	memset(&nProdInfo, 0, sizeof(StBasPage5ProductSort));
	strcpy(nProdInfo.szProductName, _T("��ʱ�洢���̼�"));
	strcpy(nProdInfo.szProductNo, _T("RG/YJ3-26B/BY05"));
	strcpy(nProdInfo.szProductCode, _T("1.00"));
	strcpy(nProdInfo.szUnitName, _T("����"));
	strcpy(nProdInfo.szRemark, _T("20151021"));
	pStTestimonialInfoTemp->stPage5.stProdSortArray.push_back(nProdInfo);

	memset(&nProdInfo, 0, sizeof(StBasPage5ProductSort));
	strcpy(nProdInfo.szProductName, _T("��ʱ�洢���̼�"));
	strcpy(nProdInfo.szProductNo, _T("RG/YJ3-26B/BY05"));
	strcpy(nProdInfo.szProductCode, _T("1.00"));
	strcpy(nProdInfo.szUnitName, _T("����"));
	strcpy(nProdInfo.szRemark, _T("20151014"));
	pStTestimonialInfoTemp->stPage5.stProdSortArray.push_back(nProdInfo);

	memset(&nProdInfo, 0, sizeof(StBasPage5ProductSort));
	strcpy(nProdInfo.szProductName, _T("��ʱ�洢���̼�"));
	strcpy(nProdInfo.szProductNo, _T("RG/YJ3-26B/BY05"));
	strcpy(nProdInfo.szProductCode, _T("1.00"));
	strcpy(nProdInfo.szUnitName, _T("����"));
	strcpy(nProdInfo.szRemark, _T("20151024"));
	pStTestimonialInfoTemp->stPage5.stProdSortArray.push_back(nProdInfo);



	//����ҳ//
	strcpy(pStTestimonialInfoTemp->stPage6.szTitle, _T("���Բ�Ʒ���������豸���嵥"));
	StBasPage6DeviceCarte nDeviceCarte;
	memset(&nDeviceCarte, 0, sizeof(StBasPage6DeviceCarte));
	strcpy(nDeviceCarte.szDeviceName, _T("ֱ����ѹ��Դ"));
	strcpy(nDeviceCarte.szStdParameter, _T("DH1718"));
	strcpy(nDeviceCarte.szTstParameter, _T("DH1718"));
	strcpy(nDeviceCarte.szHisParameter1, _T("DH1718"));
	strcpy(nDeviceCarte.szHisParameter2, _T("DH1718"));
	strcpy(nDeviceCarte.szHisParameter3, _T("DH1718"));
	strcpy(nDeviceCarte.szHisParameter4, _T("DH1718"));
	pStTestimonialInfoTemp->stPage6.stDeviceCarteArray.push_back(nDeviceCarte);

	memset(&nDeviceCarte, 0, sizeof(StBasPage6DeviceCarte));
	strcpy(nDeviceCarte.szDeviceName, _T("�������ñ�"));
	strcpy(nDeviceCarte.szStdParameter, _T("2480R"));
	strcpy(nDeviceCarte.szTstParameter, _T("2480R"));
	strcpy(nDeviceCarte.szHisParameter1, _T("2480R"));
	strcpy(nDeviceCarte.szHisParameter2, _T("2480R"));
	strcpy(nDeviceCarte.szHisParameter3, _T("2480R"));
	strcpy(nDeviceCarte.szHisParameter4, _T("2480R"));
	pStTestimonialInfoTemp->stPage6.stDeviceCarteArray.push_back(nDeviceCarte);

	memset(&nDeviceCarte, 0, sizeof(StBasPage6DeviceCarte));
	strcpy(nDeviceCarte.szDeviceName, _T("����ʾ����"));
	strcpy(nDeviceCarte.szStdParameter, _T("DP04104"));
	strcpy(nDeviceCarte.szTstParameter, _T("DP04104"));
	strcpy(nDeviceCarte.szHisParameter1, _T("DP04104"));
	strcpy(nDeviceCarte.szHisParameter2, _T("DP04104"));
	strcpy(nDeviceCarte.szHisParameter3, _T("DP04104"));
	strcpy(nDeviceCarte.szHisParameter4, _T("DP04104"));
	pStTestimonialInfoTemp->stPage6.stDeviceCarteArray.push_back(nDeviceCarte);


	pStTestimonialInfoTemp->stPage6.stTstUnits.nCount = 2;
	strcpy(pStTestimonialInfoTemp->stPage6.stTstUnits.szUnits[0], _T("���ӳ���"));
	strcpy(pStTestimonialInfoTemp->stPage6.stTstUnits.szUnits[1], _T("����"));

	pStTestimonialInfoTemp->stPage6.stTstCheckDates.nCount = 2;
	strcpy(pStTestimonialInfoTemp->stPage6.stTstCheckDates.szCheckDates[0], _T("���� 20150723"));
	strcpy(pStTestimonialInfoTemp->stPage6.stTstCheckDates.szCheckDates[1], _T("��С�� 20150714"));



	//����ҳ//
	strcpy(pStTestimonialInfoTemp->stPage7.szTitle, _T("������ʱ����������¼"));
	StBasPage7TestEnvironment nTstEnvironment;
	memset(&nTstEnvironment, 0, sizeof(StBasPage7TestEnvironment));
	strcpy(nTstEnvironment.szProjectName, _T("�¶�"));
	strcpy(nTstEnvironment.szUnit, _T("��"));
	strcpy(nTstEnvironment.szStdValue, _T("����"));
	strcpy(nTstEnvironment.szTstValue, _T("25"));
	strcpy(nTstEnvironment.szHisValue1, _T("24"));
	strcpy(nTstEnvironment.szHisValue2, _T("22"));
	strcpy(nTstEnvironment.szHisValue3, _T(""));
	strcpy(nTstEnvironment.szHisValue4, _T(""));
	pStTestimonialInfoTemp->stPage7.stTestEnvironment.push_back(nTstEnvironment);

	
	memset(&nTstEnvironment, 0, sizeof(StBasPage7TestEnvironment));
	strcpy(nTstEnvironment.szProjectName, _T("���ʪ��"));
	strcpy(nTstEnvironment.szUnit, _T("%"));
	strcpy(nTstEnvironment.szStdValue, _T("/"));
	strcpy(nTstEnvironment.szTstValue, _T("80"));
	strcpy(nTstEnvironment.szHisValue1, _T("50"));
	strcpy(nTstEnvironment.szHisValue2, _T("40"));
	strcpy(nTstEnvironment.szHisValue3, _T(""));
	strcpy(nTstEnvironment.szHisValue4, _T(""));
	pStTestimonialInfoTemp->stPage7.stTestEnvironment.push_back(nTstEnvironment);

	pStTestimonialInfoTemp->stPage7.stTstUnits.nCount = 2;
	strcpy(pStTestimonialInfoTemp->stPage7.stTstUnits.szUnits[0], _T("���ӳ���2"));
	strcpy(pStTestimonialInfoTemp->stPage7.stTstUnits.szUnits[1], _T("����2"));

	pStTestimonialInfoTemp->stPage7.stTstCheckDates.nCount = 2;
	strcpy(pStTestimonialInfoTemp->stPage7.stTstCheckDates.szCheckDates[0], _T("����2 20150723"));
	strcpy(pStTestimonialInfoTemp->stPage7.stTstCheckDates.szCheckDates[1], _T("��С��2 20150714"));

	//�ڰ�ҳ//
	strcpy(pStTestimonialInfoTemp->stPage8.szTitle, _T("��Ʒ�������ܲ��Լ�¼"));

	//�ھ�ҳ//
	strcpy(pStTestimonialInfoTemp->stPage9.szTitle, _T("ͨ  ��  ʱ  ��  ��  ¼"));

	StBasPage9ConnectTeleTime ConnectTele;
	memset(&ConnectTele, 0, sizeof(StBasPage9ConnectTeleTime));
	strcpy(ConnectTele.szBegEndTime, _T("2017-1--2017-3"));
	strcpy(ConnectTele.szTemp, _T("50��"));
	strcpy(ConnectTele.szHumidity, _T("20%"));
	strcpy(ConnectTele.szWorkStatus, _T("����"));
	strcpy(ConnectTele.szThisConnTele, _T("25"));
	strcpy(ConnectTele.szHisConnTele, _T("30"));
	strcpy(ConnectTele.szOperUser, _T("Liuty"));
	strcpy(ConnectTele.szCheckUser, _T("Tangl"));
	pStTestimonialInfoTemp->stPage9.stTstConnectTele.push_back(ConnectTele);


	//��ʮҳ//
	strcpy(pStTestimonialInfoTemp->stPage10.szTitle, _T("��  ��  ��  ¼"));

	StBasPage10TaskOver stTaskOver;
	memset(&stTaskOver, 0, sizeof(StBasPage10TaskOver));
	strcpy(stTaskOver.szOverTime, _T("2017-1-03"));
	strcpy(stTaskOver.szOverAccording, _T("hehehe"));
	strcpy(stTaskOver.szExplain, _T("enenen"));
	strcpy(stTaskOver.szOutUnit, _T("����"));
	strcpy(stTaskOver.szOutUser, _T("Liu"));
	strcpy(stTaskOver.szInUnit, _T("68"));
	strcpy(stTaskOver.szInUser, _T("hh"));
	pStTestimonialInfoTemp->stPage10.stTstTaskOver.push_back(stTaskOver);

	//��ʮһҳ//
	strcpy(pStTestimonialInfoTemp->stPage11.szTitle, _T("��  ��  ��  ��"));

	StBasPage11SpecialRecord stSpecialRecord;
	memset(&stSpecialRecord, 0, sizeof(StBasPage11SpecialRecord));
	strcpy(stSpecialRecord.szRecordText, _T("��Ʒ����ʱ��ע�����֡��ʽ������ʹ��ǰע���û�֡��ʽ��"));
	strcpy(stSpecialRecord.szUnit, _T("����"));
	strcpy(stSpecialRecord.szUser, _T("tangl"));
	strcpy(stSpecialRecord.szDate, _T("2017-1-03"));
	pStTestimonialInfoTemp->stPage11.stTstSpecialRecord.push_back(stSpecialRecord);

	memset(&stSpecialRecord, 0, sizeof(StBasPage11SpecialRecord));
	strcpy(stSpecialRecord.szRecordText, _T("��  JAb24-2657  Ҫ��������������ע���û�֡��ʽ���汾Ϊ  Ab2.861.045TW2, �����ļ�����ΪYJ3-26B_5M.ZRQ,��̬���Ժϸ񣬵� 11-1 ҳ���� 11-3 ҳβ����ҳ��"));
	strcpy(stSpecialRecord.szUnit, _T("����"));
	strcpy(stSpecialRecord.szUser, _T("tangl"));
	strcpy(stSpecialRecord.szDate, _T("2017-1-03"));
	pStTestimonialInfoTemp->stPage11.stTstSpecialRecord.push_back(stSpecialRecord);
}
void CTestimonialMng::DisPlayPagesInfo()
{
	m_Page1.DispalyPageInfo();
	m_Page2.DispalyPageInfo();
	m_Page3.DispalyPageInfo();
	m_Page4.DispalyPageInfo();
	m_Page5.DispalyPageInfo();
	m_Page6.DispalyPageInfo();
	m_Page7.DispalyPageInfo();
	m_Page8.DispalyPageInfo();
	m_Page9.DispalyPageInfo();
	m_Page10.DispalyPageInfo();
	m_Page11.DispalyPageInfo();
}
void CTestimonialMng::OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString str;
	CTreeCtrl *pTree = &m_TestTree;
	TVHITTESTINFO	tvhtif;
	GetCursorPos(&tvhtif.pt);
	pTree->ScreenToClient(&tvhtif.pt);
	pTree->HitTest(&tvhtif);

	int nUserType = g_LoginUsrInfo.nUserType;
	if(tvhtif.flags & TVHT_ONITEM)
	{
		//int nIcon1, nIcon2;
		//m_DepartMngTree->GetItemImage(tvhtif.hItem, nIcon1, nIcon2);
		pTree->SelectItem(tvhtif.hItem);
		CString strItem = pTree->GetItemText(tvhtif.hItem);
		if(strItem.IsEmpty())
			return;
		

		//�鿴��Ʒ�������Ϣ//
		int nTreeID = pTree->GetItemData(tvhtif.hItem);

		int nType,nID;
		if(!NumOneToTwo(nTreeID,nType,nID))
		{
			return;
		}

		switch(nType)
		{
		case TESTIMONIAL_TREE_PAGE1:
			{
				str.Format(_T("�� %d ҳ"), 1);
				GetDlgItem(IDC_STATIC2)->SetWindowText(str);
				m_Page1.ShowWindow(SW_SHOW);
				m_Page2.ShowWindow(SW_HIDE);
				m_Page3.ShowWindow(SW_HIDE);
				m_Page4.ShowWindow(SW_HIDE);
				m_Page5.ShowWindow(SW_HIDE);
				m_Page6.ShowWindow(SW_HIDE);
				m_Page7.ShowWindow(SW_HIDE);
				m_Page8.ShowWindow(SW_HIDE);
				m_Page9.ShowWindow(SW_HIDE);
				m_Page10.ShowWindow(SW_HIDE);
				m_Page11.ShowWindow(SW_HIDE);
			}
			break;
		case TESTIMONIAL_TREE_PAGE2:
			{
				str.Format(_T("�� %d ҳ"), 2);
				GetDlgItem(IDC_STATIC2)->SetWindowText(str);
				m_Page1.ShowWindow(SW_HIDE);
				m_Page2.ShowWindow(SW_SHOW);
				m_Page3.ShowWindow(SW_HIDE);
				m_Page4.ShowWindow(SW_HIDE);
				m_Page5.ShowWindow(SW_HIDE);
				m_Page6.ShowWindow(SW_HIDE);
				m_Page7.ShowWindow(SW_HIDE);
				m_Page8.ShowWindow(SW_HIDE);
				m_Page9.ShowWindow(SW_HIDE);
				m_Page10.ShowWindow(SW_HIDE);
				m_Page11.ShowWindow(SW_HIDE);
			}
			break;
		case TESTIMONIAL_TREE_PAGE3:
			{
				str.Format(_T("�� %d ҳ"), 3);
				GetDlgItem(IDC_STATIC2)->SetWindowText(str);
				m_Page1.ShowWindow(SW_HIDE);
				m_Page2.ShowWindow(SW_HIDE);
				m_Page3.ShowWindow(SW_SHOW);
				m_Page4.ShowWindow(SW_HIDE);
				m_Page5.ShowWindow(SW_HIDE);
				m_Page6.ShowWindow(SW_HIDE);
				m_Page7.ShowWindow(SW_HIDE);
				m_Page8.ShowWindow(SW_HIDE);
				m_Page9.ShowWindow(SW_HIDE);
				m_Page10.ShowWindow(SW_HIDE);
				m_Page11.ShowWindow(SW_HIDE);
			}
			break;
		case TESTIMONIAL_TREE_PAGE4:
			{
				str.Format(_T("�� %d ҳ"), 4);
				GetDlgItem(IDC_STATIC2)->SetWindowText(str);
				m_Page1.ShowWindow(SW_HIDE);
				m_Page2.ShowWindow(SW_HIDE);
				m_Page3.ShowWindow(SW_HIDE);
				m_Page4.ShowWindow(SW_HIDE);
				m_Page4.ShowWindow(SW_SHOW);
				m_Page5.ShowWindow(SW_HIDE);
				m_Page6.ShowWindow(SW_HIDE);
				m_Page7.ShowWindow(SW_HIDE);
				m_Page8.ShowWindow(SW_HIDE);
				m_Page9.ShowWindow(SW_HIDE);
				m_Page10.ShowWindow(SW_HIDE);
				m_Page11.ShowWindow(SW_HIDE);
				
				m_StrTestimonialInfo.stPage4.nShowType = nID;
				//m_Page4.Invalidate(TRUE);
				m_Page4.PostMessage(WM_ERASEBKGND);

			}
			break;
		case TESTIMONIAL_TREE_PAGE5:
			{
				str.Format(_T("�� %d ҳ"), 5);
				GetDlgItem(IDC_STATIC2)->SetWindowText(str);

				m_Page1.ShowWindow(SW_HIDE);
				m_Page2.ShowWindow(SW_HIDE);
				m_Page3.ShowWindow(SW_HIDE);
				m_Page4.ShowWindow(SW_HIDE);
				m_Page5.ShowWindow(SW_SHOW);
				m_Page6.ShowWindow(SW_HIDE);
				m_Page7.ShowWindow(SW_HIDE);
				m_Page8.ShowWindow(SW_HIDE);
				m_Page9.ShowWindow(SW_HIDE);
				m_Page10.ShowWindow(SW_HIDE);
				m_Page11.ShowWindow(SW_HIDE);
			}
			break;
		case TESTIMONIAL_TREE_PAGE6:
			{
				str.Format(_T("�� %d ҳ"), 6);
				GetDlgItem(IDC_STATIC2)->SetWindowText(str);
				m_Page1.ShowWindow(SW_HIDE);
				m_Page2.ShowWindow(SW_HIDE);
				m_Page3.ShowWindow(SW_HIDE);
				m_Page4.ShowWindow(SW_HIDE);
				m_Page5.ShowWindow(SW_HIDE);
				m_Page6.ShowWindow(SW_SHOW);
				m_Page7.ShowWindow(SW_HIDE);
				m_Page8.ShowWindow(SW_HIDE);
				m_Page9.ShowWindow(SW_HIDE);
				m_Page10.ShowWindow(SW_HIDE);
				m_Page11.ShowWindow(SW_HIDE);
			}
			break;
		case TESTIMONIAL_TREE_PAGE7:
			{
				str.Format(_T("�� %d ҳ"), 7);
				GetDlgItem(IDC_STATIC2)->SetWindowText(str);
				m_Page1.ShowWindow(SW_HIDE);
				m_Page2.ShowWindow(SW_HIDE);
				m_Page3.ShowWindow(SW_HIDE);
				m_Page4.ShowWindow(SW_HIDE);
				m_Page5.ShowWindow(SW_HIDE);
				m_Page6.ShowWindow(SW_HIDE);
				m_Page7.ShowWindow(SW_SHOW);
				m_Page8.ShowWindow(SW_HIDE);
				m_Page9.ShowWindow(SW_HIDE);
				m_Page10.ShowWindow(SW_HIDE);
				m_Page11.ShowWindow(SW_HIDE);
			}
			break;
		case TESTIMONIAL_TREE_PAGE8:
			{
				str.Format(_T("�� %d ҳ"), 8);
				GetDlgItem(IDC_STATIC2)->SetWindowText(str);
				m_Page1.ShowWindow(SW_HIDE);
				m_Page2.ShowWindow(SW_HIDE);
				m_Page3.ShowWindow(SW_HIDE);
				m_Page4.ShowWindow(SW_HIDE);
				m_Page5.ShowWindow(SW_HIDE);
				m_Page6.ShowWindow(SW_HIDE);
				m_Page7.ShowWindow(SW_HIDE);
				m_Page8.ShowWindow(SW_SHOW);
				m_Page9.ShowWindow(SW_HIDE);
				m_Page10.ShowWindow(SW_HIDE);
				m_Page11.ShowWindow(SW_HIDE);
			}
			break;
		case TESTIMONIAL_TREE_PAGE9:
			{
				str.Format(_T("�� %d ҳ"), 9);
				GetDlgItem(IDC_STATIC2)->SetWindowText(str);
				m_Page1.ShowWindow(SW_HIDE);
				m_Page2.ShowWindow(SW_HIDE);
				m_Page3.ShowWindow(SW_HIDE);
				m_Page4.ShowWindow(SW_HIDE);
				m_Page5.ShowWindow(SW_HIDE);
				m_Page6.ShowWindow(SW_HIDE);
				m_Page7.ShowWindow(SW_HIDE);
				m_Page8.ShowWindow(SW_HIDE);
				m_Page9.ShowWindow(SW_SHOW);
				m_Page10.ShowWindow(SW_HIDE);
				m_Page11.ShowWindow(SW_HIDE);
			}
			break;
		case TESTIMONIAL_TREE_PAGE10:
			{
				str.Format(_T("�� %d ҳ"), 10);
				GetDlgItem(IDC_STATIC2)->SetWindowText(str);
				m_Page1.ShowWindow(SW_HIDE);
				m_Page2.ShowWindow(SW_HIDE);
				m_Page3.ShowWindow(SW_HIDE);
				m_Page4.ShowWindow(SW_HIDE);
				m_Page5.ShowWindow(SW_HIDE);
				m_Page6.ShowWindow(SW_HIDE);
				m_Page7.ShowWindow(SW_HIDE);
				m_Page8.ShowWindow(SW_HIDE);
				m_Page9.ShowWindow(SW_HIDE);
				m_Page10.ShowWindow(SW_SHOW);
				m_Page11.ShowWindow(SW_HIDE);
			}
			break;
		case TESTIMONIAL_TREE_PAGE11:
			{
				str.Format(_T("�� %d ҳ"), 11);
				GetDlgItem(IDC_STATIC2)->SetWindowText(str);
				m_Page1.ShowWindow(SW_HIDE);
				m_Page2.ShowWindow(SW_HIDE);
				m_Page3.ShowWindow(SW_HIDE);
				m_Page4.ShowWindow(SW_HIDE);
				m_Page5.ShowWindow(SW_HIDE);
				m_Page6.ShowWindow(SW_HIDE);
				m_Page7.ShowWindow(SW_HIDE);
				m_Page8.ShowWindow(SW_HIDE);
				m_Page9.ShowWindow(SW_HIDE);
				m_Page10.ShowWindow(SW_HIDE);
				m_Page11.ShowWindow(SW_SHOW);
			}
			break;
		case TESTIMONIAL_TREE_PAGE12:
			{
				str.Format(_T("�� %d ҳ"), 12);
				GetDlgItem(IDC_STATIC2)->SetWindowText(str);
				m_Page1.ShowWindow(SW_HIDE);
				m_Page2.ShowWindow(SW_HIDE);
				m_Page3.ShowWindow(SW_HIDE);
				m_Page4.ShowWindow(SW_HIDE);
				m_Page5.ShowWindow(SW_HIDE);
				m_Page6.ShowWindow(SW_HIDE);
				m_Page7.ShowWindow(SW_HIDE);
				m_Page8.ShowWindow(SW_HIDE);
				m_Page9.ShowWindow(SW_HIDE);
				m_Page10.ShowWindow(SW_HIDE);
				m_Page11.ShowWindow(SW_HIDE);
			}
			break;
		}
	
	}
	

	*pResult = 0;
}
