// TestimonialMng.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "TestimonialMng.h"
#include "MainFrm.h"


// CTestimonialMng 对话框

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


// CTestimonialMng 消息处理程序

BOOL CTestimonialMng::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CTreeCtrl *pTree = &m_TestTree;
	int nIcons[] = {
		IDI_LEV_1,  IDI_LEV_2,  IDI_LEV_3,	IDI_LEV_4 	// 0 - 4： 目录树管理
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
	// 异常: OCX 属性页应返回 FALSE
}

void CTestimonialMng::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnOK();
}

void CTestimonialMng::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	AutoSize();
}

void CTestimonialMng::AutoSize()
{
	CString str;
	CRect Rect ;
	GetClientRect(&Rect) ;

	//国内通用标准 B5纸 182mm * 257mm//
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

		str.Format(_T("窗口 宽=%d, 高+%d  B5 宽=%d 高=%d"), Rect.Width(), Rect.Height(), rcRect.Width(), rcRect.Height());
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

	//根  证明书格式//
	strText.Format(_T("%s"), _T("证明书格式"));
	if(NumTwoToOne(nTreeID,TESTIMONIAL_TREE_PAGE1,0))
	{
		hParent1 = MyInsertTree(pTree,strText,TVI_ROOT,nTreeID,0,0);

	}


	//第一页  封面//
	strText.Format(_T("1.%s"), g_TestimonialPage[Testimonial_Page1]);
	if(NumTwoToOne(nTreeID,TESTIMONIAL_TREE_PAGE1,0))
	{
		hParent = hParent2 = MyInsertTree(pTree,strText,hParent1,nTreeID,nIcon,nIcon);
		
	}
	
	//第二页  填写及使用规则/
	strText.Format(_T("2.%s"), g_TestimonialPage[Testimonial_Page2]);
	if(NumTwoToOne(nTreeID,TESTIMONIAL_TREE_PAGE2,0))
	{
		hParent2 = MyInsertTree(pTree,strText,hParent1,nTreeID,nIcon,nIcon);

	}

	//第三页  目录//
	strText.Format(_T("3.%s"), g_TestimonialPage[Testimonial_Page3]);
	if(NumTwoToOne(nTreeID,TESTIMONIAL_TREE_PAGE3,0))
	{
		hParent2 = MyInsertTree(pTree,strText,hParent1,nTreeID,nIcon,nIcon);

	}

	//第四页  产品合格结论//
	strText.Format(_T("4.%s"), g_TestimonialPage[Testimonial_Page4]);
	if(NumTwoToOne(nTreeID,TESTIMONIAL_TREE_PAGE4,Page4_Type1))
	{
		hParent2 = MyInsertTree(pTree,strText,hParent1,nTreeID,nIcon,nIcon);


		//第四页 样式1//
		strText.Format(_T("4_1.%s"), _T("样式1"));
		if(NumTwoToOne(nTreeID,TESTIMONIAL_TREE_PAGE4,Page4_Type1))
		{
			hParent3 = MyInsertTree(pTree,strText,hParent2,nTreeID,nIcon+1,nIcon+1);

		}
		//第四页 样式2//
		strText.Format(_T("4_2.%s"), _T("样式2"));
		if(NumTwoToOne(nTreeID,TESTIMONIAL_TREE_PAGE4,Page4_Type2))
		{
			hParent3 = MyInsertTree(pTree,strText,hParent2,nTreeID,nIcon+1,nIcon+1);

		}
		//第四页 样式3//
		strText.Format(_T("4_3.%s"), _T("样式3"));
		if(NumTwoToOne(nTreeID,TESTIMONIAL_TREE_PAGE4,Page4_Type3))
		{
			hParent3 = MyInsertTree(pTree,strText,hParent2,nTreeID,nIcon+1,nIcon+1);

		}

		pTree->Expand(hParent2,TVE_EXPAND);
	}

	//第五页 产品配套表//
	strText.Format(_T("5.%s"), g_TestimonialPage[Testimonial_Page5]);
	if(NumTwoToOne(nTreeID,TESTIMONIAL_TREE_PAGE5,0))
	{
		hParent2 = MyInsertTree(pTree,strText,hParent1,nTreeID,nIcon,nIcon);

	}

	//第六页  测试产品用仪器（设备）清单//
	strText.Format(_T("6.%s"), g_TestimonialPage[Testimonial_Page6]);
	if(NumTwoToOne(nTreeID,TESTIMONIAL_TREE_PAGE6,0))
	{
		hParent2 = MyInsertTree(pTree,strText,hParent1,nTreeID,nIcon,nIcon);

	}

	//第七页  检查测试时环境条件记录//
	strText.Format(_T("7.%s"), g_TestimonialPage[Testimonial_Page7]);
	if(NumTwoToOne(nTreeID,TESTIMONIAL_TREE_PAGE7,0))
	{
		hParent2 = MyInsertTree(pTree,strText,hParent1,nTreeID,nIcon,nIcon);

	}

	//第八页  产品技术性能测试记录//
	strText.Format(_T("8.%s"), g_TestimonialPage[Testimonial_Page8]);
	if(NumTwoToOne(nTreeID,TESTIMONIAL_TREE_PAGE8,0))
	{
		hParent2 = MyInsertTree(pTree,strText,hParent1,nTreeID,nIcon,nIcon);

	}

	//第九页  通电时间记录//
	strText.Format(_T("9.%s"), g_TestimonialPage[Testimonial_Page9]);
	if(NumTwoToOne(nTreeID,TESTIMONIAL_TREE_PAGE9,0))
	{
		hParent2 = MyInsertTree(pTree,strText,hParent1,nTreeID,nIcon,nIcon);

	}

	//第十页  交接记录//
	strText.Format(_T("10.%s"), g_TestimonialPage[Testimonial_Page10]);
	if(NumTwoToOne(nTreeID,TESTIMONIAL_TREE_PAGE10,0))
	{
		hParent2 = MyInsertTree(pTree,strText,hParent1,nTreeID,nIcon,nIcon);

	}

	//第十一页  特殊记载//
	strText.Format(_T("11.%s"), g_TestimonialPage[Testimonial_Page11]);
	if(NumTwoToOne(nTreeID,TESTIMONIAL_TREE_PAGE11,0))
	{
		hParent2 = MyInsertTree(pTree,strText,hParent1,nTreeID,nIcon,nIcon);

	}

	//第十二页  封底//
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

	//第一页//
	strcpy(pStTestimonialInfoTemp->stPage1.szTitle, _T("产  品  证  明  书"));
	strcpy(pStTestimonialInfoTemp->stPage1.szProductionUnit, _T("中国航天科技集团公司第九研究院第七○四研究所"));
	strcpy(pStTestimonialInfoTemp->stPage1.szProductNo, _T("YH2-28A-2"));
	strcpy(pStTestimonialInfoTemp->stPage1.szProductName, _T("中心程序器"));
	strcpy(pStTestimonialInfoTemp->stPage1.szProductCode, _T("06-003"));
	strcpy(pStTestimonialInfoTemp->stPage1.szPhase, _T("S"));
	strcpy(pStTestimonialInfoTemp->stPage1.szLeaveFactoryDate, _T("2016  年  9  月  13  日"));

	if(pStTestimonialInfo != NULL)
	{
		strcpy(pStTestimonialInfoTemp->stPage1.szProductNo, pStTestimonialInfo->stPage1.szProductNo);
		strcpy(pStTestimonialInfoTemp->stPage1.szProductName, pStTestimonialInfo->stPage1.szProductName);
		strcpy(pStTestimonialInfoTemp->stPage1.szProductCode, pStTestimonialInfo->stPage1.szProductCode);
		strcpy(pStTestimonialInfoTemp->stPage1.szPhase, pStTestimonialInfo->stPage1.szPhase);
		strcpy(pStTestimonialInfoTemp->stPage1.szLeaveFactoryDate, pStTestimonialInfo->stPage1.szLeaveFactoryDate);
	}

	//第二页
	int pos = 0;
	strcpy(pStTestimonialInfoTemp->stPage2.szTitle, _T("填  写  和  使  用  规  则"));
	pStTestimonialInfoTemp->stPage2.nCount = 12;

	strcpy(pStTestimonialInfoTemp->stPage2.szRules[pos++], _T("产品证明书应记录产品出厂、运输、存放、测试、使用的情况，并随产品流转。"));
	strcpy(pStTestimonialInfoTemp->stPage2.szRules[pos++], _T("产品证明书是检查接收产品的依据之一。产品证明书未按要求填写时，接收单位可拒收产品。"));
	strcpy(pStTestimonialInfoTemp->stPage2.szRules[pos++], _T("产品证明书的有关内容应及时、准确填写，并由有关人员签署，需签署日期的应以八位数字表示，如”20141206“。"));
	strcpy(pStTestimonialInfoTemp->stPage2.szRules[pos++], _T("产品证明书中填写内容可打印，书写和签署应用黑色或蓝黑色墨水笔，各项内容字迹应工整、清晰，不得随意涂改或刮改。如有更改应采用划改方式并由授权人员签章，但同一处不允许重复更改，同一页更改不得超过两处。当某栏目内容不需要填写时，应用”/“表示。"));
	strcpy(pStTestimonialInfoTemp->stPage2.szRules[pos++], _T("产品证明书应装订成册并编页次，当某项目内容一页不够填写时可续页，但应统一编排页次。"));
	strcpy(pStTestimonialInfoTemp->stPage2.szRules[pos++], _T("产品证明书统一编排页次、目录后，任何新增页均应在”特殊记载“中说明新增页的页号（范围）及简要内容，目录不在更改。"));

	strcpy(pStTestimonialInfoTemp->stPage2.szRules[pos++], _T("装弹（箭）结论应填写在”特殊记载“页中。"));

	strcpy(pStTestimonialInfoTemp->stPage2.szRules[pos++], _T("产品证明书的其他要求按 Q/Y1-2014 《产品证明书编制使用要求》执行。"));
	strcpy(pStTestimonialInfoTemp->stPage2.szRules[pos++], _T("产品证明书的其他要求按 Q/Y1-2014 《产品证明书编制使用要求》执行。"));
	strcpy(pStTestimonialInfoTemp->stPage2.szRules[pos++], _T("产品证明书的其他要求按 Q/Y1-2014 《产品证明书编制使用要求》执行。"));
	strcpy(pStTestimonialInfoTemp->stPage2.szRules[pos++], _T("产品证明书的其他要求按 Q/Y1-2014 《产品证明书编制使用要求》执行。"));
	strcpy(pStTestimonialInfoTemp->stPage2.szRules[pos++], _T("产品证明书的其他要求按 Q/Y1-2014 《产品证明书编制使用要求》执行。"));

	//第三页
	pos = 0;

	strcpy(pStTestimonialInfoTemp->stPage3.szTitle, _T("目        录"));
	pStTestimonialInfoTemp->stPage3.nCount = 12;

	strcpy(pStTestimonialInfoTemp->stPage3.szRules[pos++], _T("封面"));
	strcpy(pStTestimonialInfoTemp->stPage3.szRules[pos++], _T("填写及使用规则"));
	strcpy(pStTestimonialInfoTemp->stPage3.szRules[pos++], _T("目录"));
	strcpy(pStTestimonialInfoTemp->stPage3.szRules[pos++], _T("产品合格结论"));
	strcpy(pStTestimonialInfoTemp->stPage3.szRules[pos++], _T("产品配套表"));
	strcpy(pStTestimonialInfoTemp->stPage3.szRules[pos++], _T("测试产品用仪器(设备)清单"));

	strcpy(pStTestimonialInfoTemp->stPage3.szRules[pos++], _T("检查测试时环境条件记录"));

	strcpy(pStTestimonialInfoTemp->stPage3.szRules[pos++], _T("产品技术性能测试记录"));
	strcpy(pStTestimonialInfoTemp->stPage3.szRules[pos++], _T("通电时间记录"));
	strcpy(pStTestimonialInfoTemp->stPage3.szRules[pos++], _T("交接记录"));
	strcpy(pStTestimonialInfoTemp->stPage3.szRules[pos++], _T("特殊记载"));
	strcpy(pStTestimonialInfoTemp->stPage3.szRules[pos++], _T("封底"));

	//第四页//
	strcpy(pStTestimonialInfoTemp->stPage4.szTitle, _T("产  品  合  格  结  论"));

	//第五页//
	strcpy(pStTestimonialInfoTemp->stPage5.szTitle, _T("产  品  配  套  表"));
	StBasPage5ProductSort nProdInfo;
	memset(&nProdInfo, 0, sizeof(StBasPage5ProductSort));
	strcpy(nProdInfo.szProductName, _T("延时存储器固件"));
	strcpy(nProdInfo.szProductNo, _T("RG/YJ3-26B/BY05"));
	strcpy(nProdInfo.szProductCode, _T("1.00"));
	strcpy(nProdInfo.szUnitName, _T("八室"));
	strcpy(nProdInfo.szRemark, _T("20151021"));
	pStTestimonialInfoTemp->stPage5.stProdSortArray.push_back(nProdInfo);

	memset(&nProdInfo, 0, sizeof(StBasPage5ProductSort));
	strcpy(nProdInfo.szProductName, _T("延时存储器固件"));
	strcpy(nProdInfo.szProductNo, _T("RG/YJ3-26B/BY05"));
	strcpy(nProdInfo.szProductCode, _T("1.00"));
	strcpy(nProdInfo.szUnitName, _T("八室"));
	strcpy(nProdInfo.szRemark, _T("20151014"));
	pStTestimonialInfoTemp->stPage5.stProdSortArray.push_back(nProdInfo);

	memset(&nProdInfo, 0, sizeof(StBasPage5ProductSort));
	strcpy(nProdInfo.szProductName, _T("延时存储器固件"));
	strcpy(nProdInfo.szProductNo, _T("RG/YJ3-26B/BY05"));
	strcpy(nProdInfo.szProductCode, _T("1.00"));
	strcpy(nProdInfo.szUnitName, _T("八室"));
	strcpy(nProdInfo.szRemark, _T("20151024"));
	pStTestimonialInfoTemp->stPage5.stProdSortArray.push_back(nProdInfo);



	//第六页//
	strcpy(pStTestimonialInfoTemp->stPage6.szTitle, _T("测试产品用仪器（设备）清单"));
	StBasPage6DeviceCarte nDeviceCarte;
	memset(&nDeviceCarte, 0, sizeof(StBasPage6DeviceCarte));
	strcpy(nDeviceCarte.szDeviceName, _T("直流稳压电源"));
	strcpy(nDeviceCarte.szStdParameter, _T("DH1718"));
	strcpy(nDeviceCarte.szTstParameter, _T("DH1718"));
	strcpy(nDeviceCarte.szHisParameter1, _T("DH1718"));
	strcpy(nDeviceCarte.szHisParameter2, _T("DH1718"));
	strcpy(nDeviceCarte.szHisParameter3, _T("DH1718"));
	strcpy(nDeviceCarte.szHisParameter4, _T("DH1718"));
	pStTestimonialInfoTemp->stPage6.stDeviceCarteArray.push_back(nDeviceCarte);

	memset(&nDeviceCarte, 0, sizeof(StBasPage6DeviceCarte));
	strcpy(nDeviceCarte.szDeviceName, _T("数字万用表"));
	strcpy(nDeviceCarte.szStdParameter, _T("2480R"));
	strcpy(nDeviceCarte.szTstParameter, _T("2480R"));
	strcpy(nDeviceCarte.szHisParameter1, _T("2480R"));
	strcpy(nDeviceCarte.szHisParameter2, _T("2480R"));
	strcpy(nDeviceCarte.szHisParameter3, _T("2480R"));
	strcpy(nDeviceCarte.szHisParameter4, _T("2480R"));
	pStTestimonialInfoTemp->stPage6.stDeviceCarteArray.push_back(nDeviceCarte);

	memset(&nDeviceCarte, 0, sizeof(StBasPage6DeviceCarte));
	strcpy(nDeviceCarte.szDeviceName, _T("四线示波器"));
	strcpy(nDeviceCarte.szStdParameter, _T("DP04104"));
	strcpy(nDeviceCarte.szTstParameter, _T("DP04104"));
	strcpy(nDeviceCarte.szHisParameter1, _T("DP04104"));
	strcpy(nDeviceCarte.szHisParameter2, _T("DP04104"));
	strcpy(nDeviceCarte.szHisParameter3, _T("DP04104"));
	strcpy(nDeviceCarte.szHisParameter4, _T("DP04104"));
	pStTestimonialInfoTemp->stPage6.stDeviceCarteArray.push_back(nDeviceCarte);


	pStTestimonialInfoTemp->stPage6.stTstUnits.nCount = 2;
	strcpy(pStTestimonialInfoTemp->stPage6.stTstUnits.szUnits[0], _T("电子车间"));
	strcpy(pStTestimonialInfoTemp->stPage6.stTstUnits.szUnits[1], _T("八室"));

	pStTestimonialInfoTemp->stPage6.stTstCheckDates.nCount = 2;
	strcpy(pStTestimonialInfoTemp->stPage6.stTstCheckDates.szCheckDates[0], _T("唐莉 20150723"));
	strcpy(pStTestimonialInfoTemp->stPage6.stTstCheckDates.szCheckDates[1], _T("王小二 20150714"));



	//第七页//
	strcpy(pStTestimonialInfoTemp->stPage7.szTitle, _T("检查测试时环境条件记录"));
	StBasPage7TestEnvironment nTstEnvironment;
	memset(&nTstEnvironment, 0, sizeof(StBasPage7TestEnvironment));
	strcpy(nTstEnvironment.szProjectName, _T("温度"));
	strcpy(nTstEnvironment.szUnit, _T("℃"));
	strcpy(nTstEnvironment.szStdValue, _T("常温"));
	strcpy(nTstEnvironment.szTstValue, _T("25"));
	strcpy(nTstEnvironment.szHisValue1, _T("24"));
	strcpy(nTstEnvironment.szHisValue2, _T("22"));
	strcpy(nTstEnvironment.szHisValue3, _T(""));
	strcpy(nTstEnvironment.szHisValue4, _T(""));
	pStTestimonialInfoTemp->stPage7.stTestEnvironment.push_back(nTstEnvironment);

	
	memset(&nTstEnvironment, 0, sizeof(StBasPage7TestEnvironment));
	strcpy(nTstEnvironment.szProjectName, _T("相对湿度"));
	strcpy(nTstEnvironment.szUnit, _T("%"));
	strcpy(nTstEnvironment.szStdValue, _T("/"));
	strcpy(nTstEnvironment.szTstValue, _T("80"));
	strcpy(nTstEnvironment.szHisValue1, _T("50"));
	strcpy(nTstEnvironment.szHisValue2, _T("40"));
	strcpy(nTstEnvironment.szHisValue3, _T(""));
	strcpy(nTstEnvironment.szHisValue4, _T(""));
	pStTestimonialInfoTemp->stPage7.stTestEnvironment.push_back(nTstEnvironment);

	pStTestimonialInfoTemp->stPage7.stTstUnits.nCount = 2;
	strcpy(pStTestimonialInfoTemp->stPage7.stTstUnits.szUnits[0], _T("电子车间2"));
	strcpy(pStTestimonialInfoTemp->stPage7.stTstUnits.szUnits[1], _T("八室2"));

	pStTestimonialInfoTemp->stPage7.stTstCheckDates.nCount = 2;
	strcpy(pStTestimonialInfoTemp->stPage7.stTstCheckDates.szCheckDates[0], _T("唐莉2 20150723"));
	strcpy(pStTestimonialInfoTemp->stPage7.stTstCheckDates.szCheckDates[1], _T("王小二2 20150714"));

	//第八页//
	strcpy(pStTestimonialInfoTemp->stPage8.szTitle, _T("产品技术性能测试记录"));

	//第九页//
	strcpy(pStTestimonialInfoTemp->stPage9.szTitle, _T("通  电  时  间  记  录"));

	StBasPage9ConnectTeleTime ConnectTele;
	memset(&ConnectTele, 0, sizeof(StBasPage9ConnectTeleTime));
	strcpy(ConnectTele.szBegEndTime, _T("2017-1--2017-3"));
	strcpy(ConnectTele.szTemp, _T("50℃"));
	strcpy(ConnectTele.szHumidity, _T("20%"));
	strcpy(ConnectTele.szWorkStatus, _T("正常"));
	strcpy(ConnectTele.szThisConnTele, _T("25"));
	strcpy(ConnectTele.szHisConnTele, _T("30"));
	strcpy(ConnectTele.szOperUser, _T("Liuty"));
	strcpy(ConnectTele.szCheckUser, _T("Tangl"));
	pStTestimonialInfoTemp->stPage9.stTstConnectTele.push_back(ConnectTele);


	//第十页//
	strcpy(pStTestimonialInfoTemp->stPage10.szTitle, _T("交  接  记  录"));

	StBasPage10TaskOver stTaskOver;
	memset(&stTaskOver, 0, sizeof(StBasPage10TaskOver));
	strcpy(stTaskOver.szOverTime, _T("2017-1-03"));
	strcpy(stTaskOver.szOverAccording, _T("hehehe"));
	strcpy(stTaskOver.szExplain, _T("enenen"));
	strcpy(stTaskOver.szOutUnit, _T("八室"));
	strcpy(stTaskOver.szOutUser, _T("Liu"));
	strcpy(stTaskOver.szInUnit, _T("68"));
	strcpy(stTaskOver.szInUser, _T("hh"));
	pStTestimonialInfoTemp->stPage10.stTstTaskOver.push_back(stTaskOver);

	//第十一页//
	strcpy(pStTestimonialInfoTemp->stPage11.szTitle, _T("特  殊  记  载"));

	StBasPage11SpecialRecord stSpecialRecord;
	memset(&stSpecialRecord, 0, sizeof(StBasPage11SpecialRecord));
	strcpy(stSpecialRecord.szRecordText, _T("产品验收时已注入测试帧格式，请在使用前注入用户帧格式。"));
	strcpy(stSpecialRecord.szUnit, _T("八室"));
	strcpy(stSpecialRecord.szUser, _T("tangl"));
	strcpy(stSpecialRecord.szDate, _T("2017-1-03"));
	pStTestimonialInfoTemp->stPage11.stTstSpecialRecord.push_back(stSpecialRecord);

	memset(&stSpecialRecord, 0, sizeof(StBasPage11SpecialRecord));
	strcpy(stSpecialRecord.szRecordText, _T("据  JAb24-2657  要求进行软件升级，注入用户帧格式，版本为  Ab2.861.045TW2, 数据文件名称为YJ3-26B_5M.ZRQ,常态测试合格，第 11-1 页至第 11-3 页尾新增页。"));
	strcpy(stSpecialRecord.szUnit, _T("八室"));
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
	// TODO: 在此添加控件通知处理程序代码

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
		

		//查看产品的相关信息//
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
				str.Format(_T("第 %d 页"), 1);
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
				str.Format(_T("第 %d 页"), 2);
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
				str.Format(_T("第 %d 页"), 3);
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
				str.Format(_T("第 %d 页"), 4);
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
				str.Format(_T("第 %d 页"), 5);
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
				str.Format(_T("第 %d 页"), 6);
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
				str.Format(_T("第 %d 页"), 7);
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
				str.Format(_T("第 %d 页"), 8);
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
				str.Format(_T("第 %d 页"), 9);
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
				str.Format(_T("第 %d 页"), 10);
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
				str.Format(_T("第 %d 页"), 11);
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
				str.Format(_T("第 %d 页"), 12);
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
