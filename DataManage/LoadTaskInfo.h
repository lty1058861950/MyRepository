#pragma once
#include "mylistctrl\editablelistctrl.h"
#include "PubStruct.h"

#define XLS_LOAD_MAX_GRP_CNT   4
#define XLS_LOAD_MAX_DUAN_CNT  50
#define XLS_LOAD_MAX_ITEM_CNT   150

#define SPLICT_CHAR_HENG_GANG  '-'
#define SPLICT_CHAR_XIE_GANG   '/'

#define SPLICT_CHAR_BO_LANG_XINA '~'
#define SPLICT_CHAR_DOU_HAO      ','
#define SPLICT_CHAR_FEN_HAO      ';'
#define SPLICT_CHAR_JING_HAO     '#'
#define SPLICT_CHAR_HONG_DAI_HUAN  '&'
#define SPLICT_CHAR_HUANG_HANG     0x0A    //excel ����

#define SPEC_STR_BO_LAN_XIAN_1	"��"
#define SPEC_STR_BO_LAN_XIAN_2  "~"
#define SPEC_STR_DOU_HAO_1		"��"
#define SPEC_STR_DOU_HAO_2		","
#define SPEC_STR_FEN_HAO_1		"��"
#define SPEC_STR_FEN_HAO_2		";"
#define SPEC_STR_SHUANG_GANG_1  "����"
#define SPEC_STR_DUN_HAO_1      "��"
#define SPEC_STR_XIE_GAN_1      "/"
#define SPEC_STR_JING_HAO       "#"
#define SPEC_STR_NULL           ""
#define SPEC_STR_JU_HAO_1       "."
#define SPEC_STR_HONG_DAI_HUAN  "&"




//#define SPEC_STR_HENG_GANG_1   "��"


typedef struct _XlsBasTask
{
	UINT	nOid;						      	//01.����OID
	char	szTaskName[DB_NAME_LEN];	      	//02.��������
	char	szProjectNo[DB_NAME_LEN];	      	//03.���鵥��
	UINT	nTaskStatus;						//04.����״̬
	UINT	nTaskType;	      	                //05.��������
	char    szModel[DB_NAME_LEN];			    //06.�ͺ�
	char    szPhase[DB_NAME_LEN];			    //07.�׶�
	UINT	nProductOid;	      	            //08.��ƷOID
	char    szProductName[DB_NAME_LEN];         //09.��Ʒ����
	char    szProductNo[DB_NAME_LEN];			//10.��Ʒ����
	UINT	nSeriesOid;						    //11.��Ʒϵ�к�OID
	char    szSeriesName[DB_NAME_LEN];			//12.��Ʒϵ�к�����
	char    szProductCode[DB_NAME_LEN];			//13.��Ʒ���
	int  	nCodeNumber;						//14.����
	char    szBatch[DB_NAME_LEN];		       	//15.���κ�
	UINT    nGroupOid;		                	//16.���첿��
	char    szGroupName[DB_NAME_LEN];           //16_1 ���첿������
	char    szUpUser[DB_USER_LEN];			    //17.������
	char    szUpDate[DB_USER_LEN];		    	//18.��������
	char    szSendDate[DB_USER_LEN];			//19.�·�����
	char    szCheckLeader[DB_USER_LEN];			//20.�����鳤
	char    szCheckUser[DB_USER_LEN];			//21.����Ա����
	char    szTechUser[DB_USER_LEN];			//22.����Ա 
	int  	nArmyTest;						    //23.����
	int  	nDianShiNum;						//24.��������
	char    szAccording1[DB_BACK_LEN];			//25.��������1
	char    szAccording2[DB_BACK_LEN];			//26.��������2
	char    szAccording3[DB_BACK_LEN];			//27.��������3
	char    szAccording4[DB_BACK_LEN];			//28.��������4
	char    szAccording5[DB_BACK_LEN];			//29.��������5
	char    szTaskRemark[DB_BACK_LEN];			//30.��ע
	char    szPlanBegTime[DB_USER_LEN];			//31.�ƻ���ʼʱ��
	char    szPlanEndTime[DB_USER_LEN];			//32.�ƻ�����ʱ��
	char    szRealBegTime[DB_USER_LEN];			//33.ʵ�ʿ�ʼʱ��
	char    szRealEndTime[DB_USER_LEN];			//34.ʵ�ʽ���ʱ��

	//�Զ����Ʒ������Ϣ 
	int     nCodeCnt;											//��Ÿ���
	char    szCodeNameArray[MAX_PIC_NUM_CNT][MAX_PIC_NAME_LEN];	//�����Ϣ
}XlsBasTask;

// CLoadTaskInfo �Ի���

class CLoadTaskInfo : public CDialog
{
	DECLARE_DYNAMIC(CLoadTaskInfo)

public:
	CLoadTaskInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLoadTaskInfo();

// �Ի�������
	enum { IDD = IDD_LOADTASKINFO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CExcelOptFun  m_ExcelOptFun;
	CEditableListCtrl m_TaskList;

	int  MaxCol;//List�����//

	CString  m_ErrorText;//������Ϣ//


//ztadd 
public:
	int m_nXlsBasTaskCnt;
	vector<XlsBasTask > m_XlsBasTaskInfo;
	int     m_nCodeCnt;												//��Ÿ���
	char    m_szCodeNameArray[MAX_PIC_NUM_CNT][MAX_PIC_NAME_LEN];	//�����Ϣ

public:
	int LoadXlsTaskInfo( );					//��Excel�������������Ϣ
	int GetProductNoFromSrcProductNo(char *szSrcProductNo, char *szProductNo, char *szProductSeries);	//��ȡ��Ʒ����+ϵ�к�
	int GetProductCodeFromSrcCodeList(int nCodeCnt, char *szSrcCodeList);		//��ȡ��Ʒ����б�
	void ClearCodeNameInfo( );
	int  GetArmyTestValue(char *szArmyTest);
	int  GetStrArrayFormStrList(char *szGrpStr, char splictChar, int nMaxCnt, int &nCnt, CString strArray[]);

	int InsertXlsTaskInfo( );

public:
	BOOL InitLoadTasksList();//��Excel ��ʼ��List//
	int  CheckFiledName(char *strText);//������� �Ƿ���Ч//
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void     AutoSize();
	afx_msg void OnBnClickedLoadtaskOpenfileBtn();
	virtual BOOL DestroyWindow();
protected:
	virtual void OnOK();
public:
	afx_msg void OnBnClickedLoadtaskErrorBtn();
	CEditableListCtrl m_NewProdList;
	CEditableListCtrl m_NewDepart;
	afx_msg void OnBnClickedOk();
};
