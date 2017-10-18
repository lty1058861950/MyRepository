#pragma once

#include "TinyXML\tinyxml.h"
#include "SqliteDb\CppSQLite3.h"

#define PATH_XML_LOADOUT_TASK_CFG                "XmlLoadOutTaskCfg"		//���񵼳���Ϣ�ļ�//
#define File_Xml_LoadOut_UsrInfo                 "OutXmlUsrInfo.txt"        //�������û���Ϣ///
#define File_Xml_LoadOut_ModeInfo                "OutXmlModeInfo.txt"       //������ģ��Ļ�����Ϣ//
#define File_Xml_LoadOut_TaskInfo                "OutXmlTaskInfo.txt"       //������������Ϣ//
#define File_xml_LoadOut_TaskNumbelMode          "OutXmlTaskNumbelMode.txt"    //��������������Ϣ//
#define File_xml_LoadOut_Exclosure               "OutXmlExclosure.txt"       //������ṹ//

#define Sqlite_TaskDbFile_Root					 "OutTaskInfo"
#define Sqlite_TaskDbFile_Path                   "OutTaskInfo\\OutTask.db"//���ݿ���ļ������·��//
#define Batch_Task_Path                          "MulTaskIn"
#define Mul_Task_FileName                        "MulTaskListDown.task"

// Ĭ��ֵ����
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

	//��ǰ���е��û��Ļ�����Ϣ//
	vector<StHrUser *> m_ArrayUsrInfo;
	StHrUser m_CurLogUsrInfo;

	////
	vector<StBasMode *> m_ArrayModeInfo;//����ģ��Ļ�����Ϣ///
	StBasMode m_CurModeInfo;//��ǰ����¼���ģ��///


	StBasTask m_CurTaskInfo;//���������ȫ��������Ϣ//

	vector<StTstResultAtta *> m_ArrayTaskNumbelMode;//��������//
	StTstResultAtta *m_pCurTaskNumbelMode;//��ǰ����¼���������//

public:
	void ClearAllData();//�����������//

	int GetCurModeXmlFileName(char *pFileName, char *pPathName);
	//�����ļ���ָ��·����///
	int WriteFileToLocal(char *pFilePath,char*FileData,int nLen);
	//��ȡָ��·���µ��ļ�//
	int ReadFileFromLocal(char *pFilePath,char **FileData,int &nLen);
	//�л�ģ��ʱɾ��ָ��·���µ��ļ�///
	int DelSrtHisDataFile();

	//�����û���Ϣ//
	//�ֶ��� �ֶθ��� �ֶ�ֵ//
	int SetXmlLoadOutUsrInfo(StHrUser *pUsrInfo);             //��Ҫ�������û���Ϣ д��XML�ļ���////
	int GetXmlLoadOutUsrInfo(StHrUser *pUsrInfo);
	int GetAllUsrInfo();////�����ݿ��л�ȡ�����û��Ļ�����Ϣ////
	int GetCurLogUsrInfo(char *UsrLogName,char *UsrPwd);

	//ģ�����Ϣ����//
	int SetXmlLoadOutModeInfo(StBasMode *pModeInfo);//����XMLģ��Ļ�����Ϣ///
	int GetXmlLoadOutModeInfo(StBasMode *pModeInfo);//�ӽ�������XML���һ��ģ��Ļ�����Ϣ//
	int GetAllModeInfo();//�����ݿ��л�ȡ����ģ��Ļ�����Ϣ//
	//����ģ������� �����ݿ��ж�ȡģ���ļ����浽ָ��Ŀ¼�²��ѵ�ǰģ��Ļ�����Ϣ�浽 m_CurModeInfo//
	int GetModeInfoAndXmlFile(UINT nModeOid, char *szModeName);

	//�������Ϣ����///
	int SetXmlLoadOutTaskInfo(StBasTask *pTskInfo);//����������Ϣ ���뵽XML�ļ���//
	int UpdateTaskInfoToDb();//������Ϣ����(��Ҫ�Ǳ������Ƿ����)//
	int GetXmlLoadOutTaskInfo(StBasTask *pTaskInfo);//�����ݿ��� ��ȡ��������Ļ�����Ϣ//
	int GetCurTaskInfo();//��õ�ǰ�����ȫ����Ϣ//

	int GetCurTaskInfoLoad(StBasTask *pTaskInfo);//�ӱ���·���»�ȡ������Ϣ//
	int GetCurTaskInfoLoad();//�ӱ���·���»�ȡ//

	//�������Ϣ����///
	//Fields ���ű������ֶ�ֵ nCol �ֶεĸ���, //
	int SetXmlLoadOutTaskNumbelMode(vector<StTstResultAtta *> *pArryTstResultBase);//������ű�//
	//Fields ���ű������ֶ�ֵ nCol �ֶεĸ���, //
	int GetXmlLoadOutTaskNumbelMode(vector<StTstResultAtta *> *pArryTstResultBase);//��ȡ�����ȫ������//
	int GetAllTaskNumbelMode();
	int UpdateTaskNumbelToDb();
	int GetCurTaskNumbelMode(char *ProdNumbel,UINT nModeOid);//�л���ǰ����¼�������//




	//�ṹ���ݴ洢///
	int SaveTestDataToDb();
	int GetTestDataFromDb();

	//2017-01-17 liutyAdd
	int SetBatchOutTask(CString szDefPath,StHrUser *pUserInfo, vector<StBasTask *> *pBatchTaskArray);
	int GetBatchOutTask(CString szDefPath,StHrUser *pUserInfo, vector<StBasTask *> *pBatchTaskArray);

public:
	//��������///
	int AnalysisData(CArray<TestDataStr,TestDataStr> &nDataArray,//���ݽṹ//
		CArray<StBasAttachment,StBasAttachment> &nExclosureArray);//�����ṹ//
	
};
