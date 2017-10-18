// PicNumMng.cpp : 实现文件
//

#include "stdafx.h"
#include "DataManage.h"
#include "PicNumMng.h"


// CPicNumMng 对话框

IMPLEMENT_DYNAMIC(CPicNumMng, CDialog)

CPicNumMng::CPicNumMng(CWnd* pParent /*=NULL*/)
	: CDialog(CPicNumMng::IDD, pParent)
{
	m_pCurSelProduct = NULL;
	m_CurSelItem = -1;
}

CPicNumMng::~CPicNumMng()
{
}

void CPicNumMng::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICNUM_LIST, m_PicNumList);
}


BEGIN_MESSAGE_MAP(CPicNumMng, CDialog)
	ON_BN_CLICKED(IDC_ADD_BTN, &CPicNumMng::OnBnClickedAddBtn)
	ON_BN_CLICKED(IDC_DEL_BTN, &CPicNumMng::OnBnClickedDelBtn)
	ON_BN_CLICKED(IDOK, &CPicNumMng::OnBnClickedOk)
	ON_NOTIFY(NM_CLICK, IDC_PICNUM_LIST, &CPicNumMng::OnNMClickPicnumList)
END_MESSAGE_MAP()


// CPicNumMng 消息处理程序

BOOL CPicNumMng::OnInitDialog()
{
	CDialog::OnInitDialog();

	int     i;
	CString	str;
	int     iColNum; 
	char	ItemName[20][30] = {"序号", "图号代号","图号名称","创建时间","创建人"};

	int     ItemLen[20]      = {50,150,100,150,100};
	iColNum = 5;

	for (i=0; i<iColNum; i++)
	{
		str.Format("%s", ItemName[i]);
		m_PicNumList.InsertColumn(i, str,   LVCFMT_LEFT, ItemLen[i]);	
	}
	m_PicNumList.EnableRClickMenu(FALSE);
	InitPicNumList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CPicNumMng::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnOK();
}

void CPicNumMng::InitPicNumList()
{
	if(m_pCurSelProduct == NULL)
	{
		return;
	}

	m_PicNumList.DeleteAllItems();

	int i, nCount, pos;
	CString strNum;
	vector<StBasPicNum> stPicNumArray;
	CEditableListCtrl *pList = &m_PicNumList;

	if(m_DMng.GetProductPicNumInfo(m_pCurSelProduct->nOid,&stPicNumArray))
	{

		nCount = stPicNumArray.size();
		for (i = 0;i<nCount;i++)
		{
			pos = 1;
			strNum.Format(_T("%d"), i+1);
			pList->InsertItem(i,strNum);
			pList->SetItemData(i,stPicNumArray.at(i).nOid);
			pList->SetItemText(i,pos++,stPicNumArray.at(i).szPicNumNo);
			pList->SetItemText(i,pos++,stPicNumArray.at(i).szPicNumName);
		}
	}else
	{
		//AfxMessageBox(_T("初始化"));
	}
	stPicNumArray.clear();
}
void CPicNumMng::OnBnClickedAddBtn()
{
	if(m_pCurSelProduct == NULL)
	{
		return;
	}
	StBasPicNum nPicNumInfo;
	memset(&nPicNumInfo,0,sizeof(StBasPicNum));

	CString strPicNumNo,strPicNumName;
	GetDlgItem(IDC_PICNUMNO_EDT)->GetWindowText(strPicNumNo);
	strPicNumNo = strPicNumNo.TrimLeft();
	strPicNumNo = strPicNumNo.TrimRight();
	if(strPicNumNo.IsEmpty())
	{
		AfxMessageBox(_T("图号代号不能为空值!"));
		return;
	}
	GetDlgItem(IDC_PICNUMNAME_EDT)->GetWindowText(strPicNumName);
	strPicNumName = strPicNumName.TrimLeft();
	strPicNumName = strPicNumName.TrimRight();

	strcpy(nPicNumInfo.szPicNumNo,strPicNumNo);
	strcpy(nPicNumInfo.szPicNumName,strPicNumName);

	if(m_pCurSelProduct->nOid <=0)
	{
		AfxMessageBox(_T("没有此产品"));
		return;
	}
	nPicNumInfo.nProductOid = m_pCurSelProduct->nOid;
	strcpy(nPicNumInfo.szProductNo,m_pCurSelProduct->szProductNo);
	strcpy(nPicNumInfo.szCreateTime,GetDateTimeString());
	strcpy(nPicNumInfo.szCreateUser,g_LoginUsrInfo.szLoginName);
	CString strText;

	if(m_DMng.IsPicNumExists(nPicNumInfo.nProductOid,nPicNumInfo.szPicNumNo))
	{
		strText.Format(_T("产品 \"%s\" 下图号 \"%s\" 已经存在!"),nPicNumInfo.szProductNo,nPicNumInfo.szPicNumNo);
		AfxMessageBox(strText);
		return;
	}
	if(m_DMng.AddNewPicNum(&nPicNumInfo))
	{
		strText.Format(_T("添加新图号 \"%s\" 成功!"),nPicNumInfo.szPicNumNo);
		AfxMessageBox(strText);
	}else
	{
		strText.Format(_T("添加新图号 \"%s\" 失败!"),nPicNumInfo.szPicNumNo);
		AfxMessageBox(strText);
	}

}

void CPicNumMng::OnBnClickedDelBtn()
{
	// TODO: 在此添加控件通知处理程序代码//
	CString strText;
	int nIndex = m_CurSelItem = m_PicNumList.GetFirstSelectedItem();
	int nCount = m_PicNumList.GetItemCount();
	if(m_CurSelItem < 0 || m_CurSelItem >= nCount)
	{
		return ;
	}
	int nPicNumOid =  m_PicNumList.GetItemData(nIndex);
	CString strPicNumNo = m_PicNumList.GetItemText(nIndex,1);
	//从数据库中删除//
	if(m_DMng.DelOldPicNum(nPicNumOid))
	{
		strText.Format(_T("删除图号 \"%s\" 成功!"),strPicNumNo);
		AfxMessageBox(strText);
	}else
	{
		strText.Format(_T("删除图号 \"%s\" 失败!"),strPicNumNo);
		AfxMessageBox(strText);
		return ;
	}

	m_PicNumList.DeleteItem(nIndex);
}

//修改//
void CPicNumMng::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strPicNumNo,strPicNumName;
	GetDlgItem(IDC_PICNUMNO_EDT)->GetWindowText(strPicNumNo);
	GetDlgItem(IDC_PICNUMNAME_EDT)->GetWindowText(strPicNumName);

	strPicNumNo = strPicNumNo.TrimLeft();
	strPicNumNo = strPicNumNo.TrimRight();
	strPicNumName = strPicNumName.TrimLeft();
	strPicNumName = strPicNumName.TrimRight();


	strcpy(m_PicNumInfo.szPicNumNo,strPicNumNo);
	strcpy(m_PicNumInfo.szPicNumName,strPicNumName);

	//保存到数据库中//
	if(m_DMng.EditOldPicNum(&m_PicNumInfo))
	{
		AfxMessageBox(_T("修改图号成功!"));
	}else
	{
		AfxMessageBox(_T("修改图号失败!"));
		return ;
	}
	m_PicNumList.SetItemText(m_CurSelItem,1,m_PicNumInfo.szPicNumNo);
	m_PicNumList.SetItemText(m_CurSelItem,2,m_PicNumInfo.szPicNumName);


	//OnOK();
}


void CPicNumMng::OnNMClickPicnumList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = m_CurSelItem = m_PicNumList.GetFirstSelectedItem();
	int nCount = m_PicNumList.GetItemCount();
	if(m_CurSelItem < 0 || m_CurSelItem >= nCount)
	{
		return ;
	}

	memset(&m_PicNumInfo,0,sizeof(StBasPicNum));
	m_PicNumInfo.nOid = m_PicNumList.GetItemData(nIndex);
	strcpy(m_PicNumInfo.szPicNumNo,m_PicNumList.GetItemText(nIndex,1));
	strcpy(m_PicNumInfo.szPicNumName,m_PicNumList.GetItemText(nIndex,2));
	strcpy(m_PicNumInfo.szCreateTime,m_PicNumList.GetItemText(nIndex,3));
	strcpy(m_PicNumInfo.szCreateUser,m_PicNumList.GetItemText(nIndex,4));
	m_PicNumInfo.nProductOid = m_pCurSelProduct->nOid;
	strcpy(m_PicNumInfo.szProductNo,m_pCurSelProduct->szProductNo);


	//显示到控件上//


	GetDlgItem(IDC_PICNUMNO_EDT)->SetWindowText(m_PicNumInfo.szPicNumNo);
	GetDlgItem(IDC_PICNUMNAME_EDT)->SetWindowText(m_PicNumInfo.szPicNumName);
	*pResult = 0;
}
