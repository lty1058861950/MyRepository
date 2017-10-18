#pragma once
#include "afxcmn.h"

#include "MyListCtrl/EditableListCtrl.h"
#include "PubStruct.h"

//#define MAX_PIC_NUM_CNT    200
//#define MAX_PIC_NAME_LEN   50


typedef struct _MesBasTask
{
	UINT	nOid;								//01.ԭʼOID
	char    szProductNo[DB_NAME_LEN];			//02.��Ʒ����
	char	szProjectNo[DB_NAME_LEN];	      	//03.���鵥��
	char    szProductName[DB_NAME_LEN];         //04.��Ʒ����
	char    szModel[DB_NAME_LEN];			    //05.�ͺ�
	char    szPhase[DB_NAME_LEN];			    //06.�׶�
	int  	nDianShiNum;						//07.��������

	int     nCodeCnt;											//��Ÿ���
	int     nPicNumCnt;											//ͼ�Ÿ���
	char    szCodeNameArray[MAX_PIC_NUM_CNT][MAX_PIC_NAME_LEN];	//�����Ϣ
	char    szPicNoArray[MAX_PIC_NUM_CNT][MAX_PIC_NAME_LEN];	//ͼ�Ŵ���
	char    szPicNameArray[MAX_PIC_NUM_CNT][MAX_PIC_NAME_LEN];	//ͼ������
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
	void LoadMesTaskInfo1( );					//��һ�ַ���

	int GetTaskInfo2(MesBasTask *pMesBasTask);
	int GetPicNumInfo2(MesBasTask *pMesBasTask );
	int  LoadMesTaskInfo2( );					//�ڶ��ַ���

public:
	void AdjustOnSize( );
	void InitListInfo1( );			//��ʼ���б�ͷ��Ϣ



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CEditableListCtrl m_ListCtrl;
	afx_msg void OnBnClickedOk();
};
