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
#define SPLICT_CHAR_HUANG_HANG     0x0A    //excel 多行

#define SPEC_STR_BO_LAN_XIAN_1	"～"
#define SPEC_STR_BO_LAN_XIAN_2  "~"
#define SPEC_STR_DOU_HAO_1		"，"
#define SPEC_STR_DOU_HAO_2		","
#define SPEC_STR_FEN_HAO_1		"；"
#define SPEC_STR_FEN_HAO_2		";"
#define SPEC_STR_SHUANG_GANG_1  "——"
#define SPEC_STR_DUN_HAO_1      "、"
#define SPEC_STR_XIE_GAN_1      "/"
#define SPEC_STR_JING_HAO       "#"
#define SPEC_STR_NULL           ""
#define SPEC_STR_JU_HAO_1       "."
#define SPEC_STR_HONG_DAI_HUAN  "&"




//#define SPEC_STR_HENG_GANG_1   "—"


typedef struct _XlsBasTask
{
	UINT	nOid;						      	//01.任务OID
	char	szTaskName[DB_NAME_LEN];	      	//02.任务名称
	char	szProjectNo[DB_NAME_LEN];	      	//03.检验单号
	UINT	nTaskStatus;						//04.任务状态
	UINT	nTaskType;	      	                //05.任务类型
	char    szModel[DB_NAME_LEN];			    //06.型号
	char    szPhase[DB_NAME_LEN];			    //07.阶段
	UINT	nProductOid;	      	            //08.产品OID
	char    szProductName[DB_NAME_LEN];         //09.产品名称
	char    szProductNo[DB_NAME_LEN];			//10.产品代号
	UINT	nSeriesOid;						    //11.产品系列号OID
	char    szSeriesName[DB_NAME_LEN];			//12.产品系列号名称
	char    szProductCode[DB_NAME_LEN];			//13.产品编号
	int  	nCodeNumber;						//14.数量
	char    szBatch[DB_NAME_LEN];		       	//15.批次号
	UINT    nGroupOid;		                	//16.交检部门
	char    szGroupName[DB_NAME_LEN];           //16_1 交检部门名称
	char    szUpUser[DB_USER_LEN];			    //17.交检人
	char    szUpDate[DB_USER_LEN];		    	//18.交检日期
	char    szSendDate[DB_USER_LEN];			//19.下发日期
	char    szCheckLeader[DB_USER_LEN];			//20.检验组长
	char    szCheckUser[DB_USER_LEN];			//21.检验员姓名
	char    szTechUser[DB_USER_LEN];			//22.工艺员 
	int  	nArmyTest;						    //23.军检
	int  	nDianShiNum;						//24.典试数量
	char    szAccording1[DB_BACK_LEN];			//25.验收依据1
	char    szAccording2[DB_BACK_LEN];			//26.验收依据2
	char    szAccording3[DB_BACK_LEN];			//27.验收依据3
	char    szAccording4[DB_BACK_LEN];			//28.验收依据4
	char    szAccording5[DB_BACK_LEN];			//29.验收依据5
	char    szTaskRemark[DB_BACK_LEN];			//30.备注
	char    szPlanBegTime[DB_USER_LEN];			//31.计划开始时间
	char    szPlanEndTime[DB_USER_LEN];			//32.计划结束时间
	char    szRealBegTime[DB_USER_LEN];			//33.实际开始时间
	char    szRealEndTime[DB_USER_LEN];			//34.实际结束时间

	//自定义产品代号信息 
	int     nCodeCnt;											//编号个数
	char    szCodeNameArray[MAX_PIC_NUM_CNT][MAX_PIC_NAME_LEN];	//编号信息
}XlsBasTask;

// CLoadTaskInfo 对话框

class CLoadTaskInfo : public CDialog
{
	DECLARE_DYNAMIC(CLoadTaskInfo)

public:
	CLoadTaskInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoadTaskInfo();

// 对话框数据
	enum { IDD = IDD_LOADTASKINFO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CExcelOptFun  m_ExcelOptFun;
	CEditableListCtrl m_TaskList;

	int  MaxCol;//List最大列//

	CString  m_ErrorText;//错误信息//


//ztadd 
public:
	int m_nXlsBasTaskCnt;
	vector<XlsBasTask > m_XlsBasTaskInfo;
	int     m_nCodeCnt;												//编号个数
	char    m_szCodeNameArray[MAX_PIC_NUM_CNT][MAX_PIC_NAME_LEN];	//编号信息

public:
	int LoadXlsTaskInfo( );					//从Excel导入测试任务信息
	int GetProductNoFromSrcProductNo(char *szSrcProductNo, char *szProductNo, char *szProductSeries);	//获取产品代号+系列号
	int GetProductCodeFromSrcCodeList(int nCodeCnt, char *szSrcCodeList);		//获取产品编号列表
	void ClearCodeNameInfo( );
	int  GetArmyTestValue(char *szArmyTest);
	int  GetStrArrayFormStrList(char *szGrpStr, char splictChar, int nMaxCnt, int &nCnt, CString strArray[]);

	int InsertXlsTaskInfo( );

public:
	BOOL InitLoadTasksList();//读Excel 初始化List//
	int  CheckFiledName(char *strText);//检查列名 是否有效//
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
