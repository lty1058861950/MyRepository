#pragma once
#include "afxcmn.h"

#include "MyListCtrl/EditableListCtrl.h"
#include "PubStruct.h"

//#define MAX_PIC_NUM_CNT    200
//#define MAX_PIC_NAME_LEN   50


typedef struct _MesBasTask
{
	UINT	nOid;								//01.原始OID
	char    szProductNo[DB_NAME_LEN];			//02.产品代号
	char	szProjectNo[DB_NAME_LEN];	      	//03.检验单号
	char    szProductName[DB_NAME_LEN];         //04.产品名称
	char    szModel[DB_NAME_LEN];			    //05.型号
	char    szPhase[DB_NAME_LEN];			    //06.阶段
	int  	nDianShiNum;						//07.典试数量

	int     nCodeCnt;											//编号个数
	int     nPicNumCnt;											//图号个数
	char    szCodeNameArray[MAX_PIC_NUM_CNT][MAX_PIC_NAME_LEN];	//编号信息
	char    szPicNoArray[MAX_PIC_NUM_CNT][MAX_PIC_NAME_LEN];	//图号代号
	char    szPicNameArray[MAX_PIC_NUM_CNT][MAX_PIC_NAME_LEN];	//图号名称
}MesBasTask;



// CLoadMesTask dialog

class CLoadMesTask : public CDialog
{
	DECLARE_DYNAMIC(CLoadMesTask)

public:
	CLoadMesTask(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLoadMesTask();

// Dialog Data
	enum { IDD = IDD_LOAD_MES_TASK };

public:

	
	int  m_nSrcCodeCnt;
	int  m_nDesCodeCnt;
	char m_SrcCodeName[MAX_PIC_NUM_CNT][MAX_PIC_NAME_LEN];
	char m_DesCodeName[MAX_PIC_NUM_CNT][MAX_PIC_NAME_LEN];

	int  m_nSrcPicCnt;
	int  m_nDesPicCnt;
	char m_SrcPicNo[MAX_PIC_NUM_CNT][MAX_PIC_NAME_LEN];
	char m_SrcPicName[MAX_PIC_NUM_CNT][MAX_PIC_NAME_LEN];
	char m_DesPicNo[MAX_PIC_NUM_CNT][MAX_PIC_NAME_LEN];
	char m_DesPicName[MAX_PIC_NUM_CNT][MAX_PIC_NAME_LEN];

	int m_nMesBasTaskCnt;
	vector<MesBasTask > m_MesBasTaskInfo;

	int GetTaskInfo(int nCodeCnt, char *szSumTask);
	int GetPicNumInfo(int nPicCnt, char *szSumPicNo, char *szSumPicName);
	void LoadMesTaskInfo1( );					//第一种方法

	int GetTaskInfo2(MesBasTask *pMesBasTask);
	int GetPicNumInfo2(MesBasTask *pMesBasTask );
	int  LoadMesTaskInfo2( );					//第二种方法

public:
	void AdjustOnSize( );
	void InitListInfo1( );			//初始化列表头信息



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CEditableListCtrl m_ListCtrl;
	afx_msg void OnBnClickedOk();
};
