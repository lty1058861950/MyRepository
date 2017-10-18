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
//从pad端移植来的///
extern int  g_bDebug;
////
//////////////////////////////////////////////////////////////////////////
//定义全局变量
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
extern int  g_nPos;					//日志序号
extern int  g_bAddEncOrDec;			//是否为加密模式


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

//所有数据库的表名//

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

//数据库表结构//

extern int   g_DebugShow;
//用户模块全局函数//
//获取用户类型文本//
extern CString GetUserTypeText(int nUserType);					//获取用户类型

//交检部门模块全局函数//
extern BOOL AddNewUpDepart(StHrUpDepart *pUpDepartInfo);
extern BOOL DelTheUpDepart(StHrUpDepart *pUpDepartInfo);
extern BOOL ModifyTheUpDepart(StHrUpDepart *pUpDepartInfo);
//产品模块全局函数//
extern CString GetProductType(int nPicNumType);
extern BOOL AddNewProd(StBasProduct *m_pProdInfo);
extern BOOL DelTheProd(StBasProduct *m_pProdInfo);
extern BOOL ModifyTheProd(StBasProduct *m_pProdInfo);

//模板模块全局函数///
//获取模板类型文本///
extern CString GetModeType(int nModeType);
//获取模板的行可变属性///
extern CString GetModeRowVar(int nModeRowVar);
//获取模板大小的字符串///
extern CString GetModeSizeText(int nModeSize);
//获取模板是否初始化///
extern CString GetModeInitStr(int nInitTabSrt);
//组建模板数据表名称
extern CString GetModeTabName(StBasMode *pModeInfo);

//添加一个新模板
extern BOOL  AddTheMode(StBasMode *pModeInfo);
//修改这个模板
extern BOOL  ModifyTheMode(StBasMode *pModeInfo);
//删除这个模板
extern BOOL DelTheMode(StBasMode *pModeInfo);


//任务模块全局函数//
//获取任务类型//
extern CString GetTaskType(int nTaskType);
//获取任务状态文本///
extern CString GetTaskStatus(int nTaskStatus);
//获取任务是否军检///
extern CString GetTaskArmyText(int nArmyTest);
//获取产品编号是否典试///
extern CString GetDianshiText(int nDianTest);

extern BOOL SetArmyTestComBoText(int nTaskType, CComboBox *pComBo);
extern BOOL SetTaskTypeComBoText(int nTaskType, CComboBox *pComBo);

//添加一项任务
extern BOOL AddNewTask(StBasTask *pTaskInfo,vector<CString> &strErrorArray);
//修改本次任务//
extern BOOL ModifyTheTask(StBasTask *pTaskInfo,vector<CString> &strErrorArray);
//删除一项任务//
extern BOOL DelTheTask(StBasTask *pTaskInfo);
//检测任务是否合格//
extern BOOL CheckTheTask(StBasTask *pTaskInfo, CString &strWarning/*提示信息*/);

extern int GetModeType(char *szModeType);
extern int GetModeRowVar(char *szModeRowVar);
extern int GetTaskIcon(int TaskState);
extern int AddNewProductToConfig(StBasProduct *pProductInfo);
extern int DelProductToConfig(StBasProduct *pProductInfo);
extern int CreateSQLSelProducts(vector<StBasProduct *> *pArrayProduct);
extern CString BuildReportModeFilePath(StBasMode *pModeInfo);//组建报告模板路径//
//组建模板公式文件路径// nOutType: 0.普通的加载，1.导出任务时组建
extern CString BuildModeFormulaFilePath(char *szRelativePath,StBasMode *pModeInfo, int nOutType = 0);
extern CString BuildAttamentFilePath(StTstResultAtta *StTstResultAtta);//组建附件文件路径//

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
功能：十六进制到ASC码的转换
*/

void ChangeAscHex( char *sur, char *des , int number);
/*
功能：ASC到十六进制码的转换
*/


#endif