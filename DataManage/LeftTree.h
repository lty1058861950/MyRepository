#pragma once
#include "afxcmn.h"
#include "Resource.h"



#define  ID_L_ADDMODE_MENU       3000
#define  ID_L_DELMODE_MENU       3001
#define  ID_L_COPYMODE_MENU      3002
#define  ID_L_PASTEMODE_MENU     3003
#define  ID_L_ADDPRODUCT_MENU    3004

#define  ID_L_ADDTASK_MENU       3010
#define  ID_L_DELTASK_MENU       3011
#define  ID_L_SENDTASK_MENU      3012
#define  ID_L_STOPTASK_MENU      3013

// CLeftTree �Ի���

class CLeftTree : public CDialog
{
	DECLARE_DYNAMIC(CLeftTree)

public:
	CLeftTree(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLeftTree();

// �Ի�������
	enum { IDD = IDD_LEFT_TREE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CMenu		m_TaskMenu1;
	CMenu		m_TaskMenu2;
	void InitTaskMenu1( );					//��ʼ���˵�1
	void InitTaskMenu2( );					//��ʼ���˵�2
public:
	CMenu		m_ModeMenu1;
	CMenu		m_ModeMenu1_1;
	CMenu		m_ModeMenu1_2;
	CMenu		m_ModeMenu2;
	void InitModeMenu1( );					//��ʼ���˵�1
	void InitModeMenu1_1( );				//��ʼ���˵�1
	void InitModeMenu1_2();
	void InitModeMenu2( );					//��ʼ���˵�2
public:
	void     InitProdTree(HTREEITEM hDItem,UINT nGroupOid,int ShowType = 0);
	void     InitModeTreeFromModeType(HTREEITEM hParent,UINT GroupOid,int nModeType);
	void     InitModeTree(HTREEITEM hParent,UINT nProdOid);
	void     InitTaskStatusProdTree(HTREEITEM hParent,UINT GroupOid,int nTaskStatus);
	void     InitTaskTree(HTREEITEM &hParent,UINT nProdOid);
	void     InitTaskStatusTree(HTREEITEM &hParent,UINT nProdOid, int nTaskStatus);



	int      GetProductTreeItemType(HTREEITEM hItem,StBasProduct *pProdInfo);
	int      GetModeTreeItemType(HTREEITEM hItem,StBasMode *pModeInfo);
	int      GetTaskTreeItemType(HTREEITEM hItem,StBasTask *pTaskInfo);
	int      GetResultTreeItemType(HTREEITEM hItem,StTstResultBase *pTstResultInfo);
	int      GetResultTreeItemTypeNew(HTREEITEM hItem,StBasTask *pResultSearchInfo);
	void     AddModeMenu();
	void     AddProductMenu();
	void     DelModeMenu();
	void     CopyModeMenu();
	void     PasteModeMenu();

	void     AddTaskMenu();
	void     DelTaskMenu();
	void     SendTaskMenu();
	void     StopTaskMenu();

	void    RefleshExecuteTree( );
	void    RefleshFinishedTree( );
public:
	void    InitGuideTree();
	void    DelTreeChildItem(CTreeCtrl *pTree,HTREEITEM hItem);//ɾ��ĳ���ڵ��µ������ӽڵ�///
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CTreeCtrl m_GuideTree;
	CImageList	m_TreeImgList;
	HTREEITEM  m_TaskTreeItem[6];//�����������ڵ����Ҫ�����ڵ�//
	afx_msg void OnNMClickLeftTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickLeftTree(NMHDR *pNMHDR, LRESULT *pResult);
};
