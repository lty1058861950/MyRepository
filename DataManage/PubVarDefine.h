#pragma  once 

#include "PubStruct.h"
#include "DataMng.h"
#include "DataManageView.h"
#include "LeftTree.h"
#include "LogFile.h"
#include "SysSetConfig.h"
#include "ShowInfoList.h"
#include <vector>
using namespace std;
//��pad����ֲ����///
extern int  g_bDebug;
////
//////////////////////////////////////////////////////////////////////////
//����ȫ�ֱ���
//////////////////////////////////////////////////////////////////////////
class CDataManageApp;
class CMainFrame;
#ifdef GLOB_QUEUE_DEFINE
#else
extern CDataManageApp    theApp;
extern CDataManageView   *g_DtMngView;
extern CMainFrame        *g_MainFram;
extern OracleOciDbMng    *g_pOrcOciDb;
extern CLeftTree         *g_pLeftTree;
extern CShowInfoList     *g_pShowInfoList;
extern CDataMng          m_DMng;
extern CSysSetConfig     g_UserConfig;
//ztadd for CLogFile
extern vector<StBasProduct *> g_SelProducts;
extern vector<StHrGroup *>    g_AllGroups;
extern vector<StHrUpDepart>   g_AllUpDeparts;
extern vector<StHrRole *>     g_AllRoles;
extern CLogFile	              *g_pLogInfo;



extern DbConfig       g_Configs;
extern StHrUser       g_LoginUsrInfo;
extern StHrGroup      g_CurSelDepart;

extern CArray<TestDataStr,TestDataStr> *g_pDataArray;
extern vector<StBasTaskPicNum *> *g_pArryTaskPicNum ;
extern StTstResultAtta     *g_pCurAttaInfo;
extern int            g_PicNum;

extern CString       g_strSelProdsSQL;
//ztadd for CLogFile
extern int  g_nPos;					//��־���
extern int  g_bAddEncOrDec;			//�Ƿ�Ϊ����ģʽ


extern char g_WorkPath[512];
extern char g_Admin[];
extern char g_ReSetDefPwd[];
extern char g_SearchBeginTime[];
extern char g_SearchEndTime[];
extern char g_szSearchPerPageNums[4][20];
extern int  g_nSearchPerPageNum[4];

extern int  g_IdLen;
extern int  g_GroupSelect;
extern int  g_PaperDirection;
extern int  g_PadCount;
extern int  g_WinWidth;
extern int  g_WinHeight;


extern char g_TestimonialPage[12][100];
extern char g_ResultType[2][20];
extern char g_TaskState[5][20];
extern char g_TaskType[3][20];
extern char g_TaskShowType[5][20];

extern char g_UserType[3][20]; 
extern char g_UserStatus[2][20];

extern char g_ProdSeriesType[2][20];
extern char g_ProdPicNumType[2][20];

extern char g_ModeRowVal[2][20];
extern char g_ModeType[4][20];

//�������ݿ�ı���//

extern int g_HrRoleLen;
extern int g_DepartLen;
extern int g_ProdLen;
extern int g_SeriesLen;



extern char g_BasProduct[];
extern char g_BasProductPicNum[];
extern char g_BasMode[];
extern char g_BasModeSave[];
extern char g_BasModeDesc[];
extern char g_BasTask[];
extern char g_BasTaskCode[];
extern char g_BasTaskMode[];
extern char g_BasTaskPicNum[];



extern char g_HrRole[];
extern char g_HrUser[];
extern char g_HrGroup[];
extern char g_HrUpDepart[];
extern char g_HrGroupSave[];

extern char *g_TstData;
extern char *g_ResultBase;
extern char *g_ResultAtta;
extern char *g_Enclosure;

//���ݿ��ṹ//

extern int   g_DebugShow;
//�û�ģ��ȫ�ֺ���//
//��ȡ�û������ı�//
extern CString GetUserTypeText(int nUserType);					//��ȡ�û�����

//���첿��ģ��ȫ�ֺ���//
extern BOOL AddNewUpDepart(StHrUpDepart *pUpDepartInfo);
extern BOOL DelTheUpDepart(StHrUpDepart *pUpDepartInfo);
extern BOOL ModifyTheUpDepart(StHrUpDepart *pUpDepartInfo);
//��Ʒģ��ȫ�ֺ���//
extern CString GetProductType(int nPicNumType);
extern BOOL AddNewProd(StBasProduct *m_pProdInfo);
extern BOOL DelTheProd(StBasProduct *m_pProdInfo);
extern BOOL ModifyTheProd(StBasProduct *m_pProdInfo);

//ģ��ģ��ȫ�ֺ���///
//��ȡģ�������ı�///
extern CString GetModeType(int nModeType);
//��ȡģ����пɱ�����///
extern CString GetModeRowVar(int nModeRowVar);
//��ȡģ���С���ַ���///
extern CString GetModeSizeText(int nModeSize);
//��ȡģ���Ƿ��ʼ��///
extern CString GetModeInitStr(int nInitTabSrt);
//�齨ģ�����ݱ�����
extern CString GetModeTabName(StBasMode *pModeInfo);

//���һ����ģ��
extern BOOL  AddTheMode(StBasMode *pModeInfo);
//�޸����ģ��
extern BOOL  ModifyTheMode(StBasMode *pModeInfo);
//ɾ�����ģ��
extern BOOL DelTheMode(StBasMode *pModeInfo);


//����ģ��ȫ�ֺ���//
//��ȡ��������//
extern CString GetTaskType(int nTaskType);
//��ȡ����״̬�ı�///
extern CString GetTaskStatus(int nTaskStatus);
//��ȡ�����Ƿ����///
extern CString GetTaskArmyText(int nArmyTest);
//��ȡ��Ʒ����Ƿ����///
extern CString GetDianshiText(int nDianTest);

extern BOOL SetArmyTestComBoText(int nTaskType, CComboBox *pComBo);
extern BOOL SetTaskTypeComBoText(int nTaskType, CComboBox *pComBo);

//���һ������
extern BOOL AddNewTask(StBasTask *pTaskInfo,vector<CString> &strErrorArray);
//�޸ı�������//
extern BOOL ModifyTheTask(StBasTask *pTaskInfo,vector<CString> &strErrorArray);
//ɾ��һ������//
extern BOOL DelTheTask(StBasTask *pTaskInfo);
//��������Ƿ�ϸ�//
extern BOOL CheckTheTask(StBasTask *pTaskInfo, CString &strWarning/*��ʾ��Ϣ*/);

extern int GetModeType(char *szModeType);
extern int GetModeRowVar(char *szModeRowVar);
extern int GetTaskIcon(int TaskState);
extern int AddNewProductToConfig(StBasProduct *pProductInfo);
extern int DelProductToConfig(StBasProduct *pProductInfo);
extern int CreateSQLSelProducts(vector<StBasProduct *> *pArrayProduct);
extern CString BuildReportModeFilePath(StBasMode *pModeInfo);//�齨����ģ��·��//
//�齨ģ�幫ʽ�ļ�·��// nOutType: 0.��ͨ�ļ��أ�1.��������ʱ�齨
extern CString BuildModeFormulaFilePath(char *szRelativePath,StBasMode *pModeInfo, int nOutType = 0);
extern CString BuildAttamentFilePath(StTstResultAtta *StTstResultAtta);//�齨�����ļ�·��//

extern int  ReleaseProducts(vector<StBasProduct *> *pSelProducts);
extern int  ReleaseGroups(vector<StHrGroup *> *pStHrGroupArry);
extern int  ReGetAllGroupInfo();
extern int  ReGetAllDepartInfo();
extern int  ReleaseRoles(vector<StHrRole *> *pStHrRoleArry);

extern int GetUserTypeIndex(char *szUserType);
extern int GetUserStatusIndex(char *szUserStatus);
extern int NumTwoToOne(int &Num,int Num1,int Num2);
extern int NumOneToTwo(int Num,int &Num1,int &Num2);
extern int DelFile();
extern int ReadFile(char *szFilePath,char **pFileInfo,int &nLen);
extern CString GetStringID(int ID);
extern BOOL    StringToTime(const char *strTime,const char *FarmatStr,SYSTEMTIME &nSysTime);
extern CString SQLText(CString nFontText);
extern CString GetDateString();
extern CString GetTimeString();
extern void    GetSysDateTime(char *szDateTime);
extern CString GetDateTimeString();
extern CString GetDateTimeFileNameString();
extern CString GetDateTimeString2();

extern BOOL PubFun_IsFileExist(char* pFilename);
extern HTREEITEM MyInsertTree( CTreeCtrl *pTree, CString strName, HTREEITEM hParent, UINT Param );
extern HTREEITEM MyInsertTree( CTreeCtrl *pTree, CString strName, HTREEITEM hParent, UINT Param, UINT iPosIco);
extern HTREEITEM MyInsertTree( CTreeCtrl *pTree, CString strName, HTREEITEM hParent, UINT Param, UINT iPosIco1, UINT iPosIco2);
extern CGridCtrl *InitGridCtrl_MUL(CWnd *pWnd, CModeParMng *m_pModeParMng, CGridCtrl *m_pGrid);
extern void SetListColor(CEditableListCtrl*pList,int iCol=0 );



void ChangeHexAsc( char *sur, char *des , int number);
/*
���ܣ�ʮ�����Ƶ�ASC���ת��
*/

void ChangeAscHex( char *sur, char *des , int number);
/*
���ܣ�ASC��ʮ���������ת��
*/


#endif