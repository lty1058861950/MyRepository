#pragma once

#include "TinyXML\tinyxml.h"
#include "SqliteDb\CppSQLite3.h"

#define PATH_XML_LOADOUT_TASK_CFG                "XmlLoadOutTaskCfg"		//任务导出信息文件//
#define File_Xml_LoadOut_UsrInfo                 "OutXmlUsrInfo.txt"        //导出的用户信息///
#define File_Xml_LoadOut_ModeInfo                "OutXmlModeInfo.txt"       //导出的模板的基本信息//
#define File_Xml_LoadOut_TaskInfo                "OutXmlTaskInfo.txt"       //导出的任务信息//
#define File_xml_LoadOut_TaskNumbelMode          "OutXmlTaskNumbelMode.txt"    //导出的任务表的信息//
#define File_xml_LoadOut_Exclosure               "OutXmlExclosure.txt"       //附件表结构//

#define Sqlite_TaskDbFile_Root					 "OutTaskInfo"
#define Sqlite_TaskDbFile_Path                   "OutTaskInfo\\OutTask.db"//数据库的文件的相对路径//
#define Batch_Task_Path                          "MulTaskIn"
#define Mul_Task_FileName                        "MulTaskListDown.task"

// 默认值定义
// xml declaration
#define DECL_LOAD_VERSION		"1.0"	// for XML Msg
#define DECL_LOAD_ENCODING		"GB2312"
#define DECL_LOAD_STANDALONE		"yes"


static void GetSysDateString(char *cDate);
static void GetSysTimeString(char *cTime);
static void SetXmlRootInfoLoad(TiXmlElement *pRootInfo);
/*
extern char *g_UsrTab[];
extern char *g_TaskTab[];
extern char *g_ModeTab[];
extern char *g_TstResultTab[];

extern char g_ModeRowVal[2][20];
extern char g_ModeType[4][20];
extern char g_TaskState[7][10];
extern char g_TaskType[3][10];

extern int g_HrRoleLen;
extern int g_UsrLen;
extern int g_DepartLen;
extern int g_ProdLen;
extern int g_SeriesLen;
extern int g_PicNumLen;
extern int g_ModeLen;
extern int g_ModeSaveLen;
extern int g_TaskLen;
extern int g_TaskCodeLen;
extern int g_TaskModeLen;
extern int g_TaskPicNumLen;
extern int g_TstResultLen;

*/

class LoadOutTaskXmlAnalysis
{
public:
	LoadOutTaskXmlAnalysis(void);
	virtual ~LoadOutTaskXmlAnalysis(void);
public:
	CppSQLite3DB m_SqliteDb;
	CString m_szDbPath;
	CString m_szTaskOutPath;

	//当前所有的用户的基本信息//
	vector<StHrUser *> m_ArrayUsrInfo;
	StHrUser m_CurLogUsrInfo;

	////
	vector<StBasMode *> m_ArrayModeInfo;//所有模版的基本信息///
	StBasMode m_CurModeInfo;//当前正在录入的模板///


	StBasTask m_CurTaskInfo;//本次任务的全部基本信息//

	vector<StTstResultAtta *> m_ArrayTaskNumbelMode;//所有任务//
	StTstResultAtta *m_pCurTaskNumbelMode;//当前正在录入的任务项//

public:
	void ClearAllData();//清空所有数据//

	int GetCurModeXmlFileName(char *pFileName, char *pPathName);
	//保存文件到指定路径下///
	int WriteFileToLocal(char *pFilePath,char*FileData,int nLen);
	//读取指定路径下的文件//
	int ReadFileFromLocal(char *pFilePath,char **FileData,int &nLen);
	//切换模板时删除指定路径下的文件///
	int DelSrtHisDataFile();

	//导出用户信息//
	//字段名 字段个数 字段值//
	int SetXmlLoadOutUsrInfo(StHrUser *pUsrInfo);             //将要导出的用户信息 写到XML文件中////
	int GetXmlLoadOutUsrInfo(StHrUser *pUsrInfo);
	int GetAllUsrInfo();////从数据库中获取所有用户的基本信息////
	int GetCurLogUsrInfo(char *UsrLogName,char *UsrPwd);

	//模板的信息函数//
	int SetXmlLoadOutModeInfo(StBasMode *pModeInfo);//生成XML模板的基本信息///
	int GetXmlLoadOutModeInfo(StBasMode *pModeInfo);//从解析本地XML获得一个模板的基本信息//
	int GetAllModeInfo();//从数据库中获取所有模板的基本信息//
	//根据模板的名称 从数据库中读取模板文件，存到指定目录下并把当前模版的基本信息存到 m_CurModeInfo//
	int GetModeInfoAndXmlFile(UINT nModeOid, char *szModeName);

	//任务的信息函数///
	int SetXmlLoadOutTaskInfo(StBasTask *pTskInfo);//本次任务信息 导入到XML文件中//
	int UpdateTaskInfoToDb();//任务信息更新(主要是保存编号是否典试)//
	int GetXmlLoadOutTaskInfo(StBasTask *pTaskInfo);//从数据库中 获取本次任务的基本信息//
	int GetCurTaskInfo();//获得当前任务的全部信息//

	int GetCurTaskInfoLoad(StBasTask *pTaskInfo);//从本地路径下获取任务信息//
	int GetCurTaskInfoLoad();//从本地路径下获取//

	//任务的信息函数///
	//Fields 这张表所有字段值 nCol 字段的个数, //
	int SetXmlLoadOutTaskNumbelMode(vector<StTstResultAtta *> *pArryTstResultBase);//任务序号表//
	//Fields 这张表所有字段值 nCol 字段的个数, //
	int GetXmlLoadOutTaskNumbelMode(vector<StTstResultAtta *> *pArryTstResultBase);//获取任务表全部内容//
	int GetAllTaskNumbelMode();
	int UpdateTaskNumbelToDb();
	int GetCurTaskNumbelMode(char *ProdNumbel,UINT nModeOid);//切换当前正在录入的任务//




	//结构数据存储///
	int SaveTestDataToDb();
	int GetTestDataFromDb();

	//2017-01-17 liutyAdd
	int SetBatchOutTask(CString szDefPath,StHrUser *pUserInfo, vector<StBasTask *> *pBatchTaskArray);
	int GetBatchOutTask(CString szDefPath,StHrUser *pUserInfo, vector<StBasTask *> *pBatchTaskArray);

public:
	//解析数据///
	int AnalysisData(CArray<TestDataStr,TestDataStr> &nDataArray,//数据结构//
		CArray<StBasAttachment,StBasAttachment> &nExclosureArray);//附件结构//
	
};
