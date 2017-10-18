#pragma once
#include "LoadOutTaskXmlAnalysis.h"
#include "MainFrm.h"
#include "ModeXmlStruct.h"
class CBatchImportData
{
public:
	CBatchImportData(void);
	~CBatchImportData(void);
public:
	LoadOutTaskXmlAnalysis  m_LoadOutTask;
	StBasTask               *m_pStBaseInfo;//当前录入的任务指针//

	StHrUser                m_CheckUserInfo;
	vector<StBasTask *>     m_BatchTaskDataArray;
	vector<CString>         m_TaskDataFilePath;
public:
	BOOL  BatchTaskDataImport();
	BOOL  SingleTaskDataImport(CString strDataFilePath,vector<CString> &strErrorArray);//单个进行处理//

	//数据导入函数集合///
	//数据导入流程//
	BOOL  ImPortTestData();//1.数据表导入
	BOOL  ImPortTaskInfo();//2.任务信息表导入

	int   AnalysisData();//解析数据并保存到数据库//
	int   IsTstResultExists(UINT nGroupOid);//判断任务基础表是否存在//
	BOOL  AddTstResultBase(StTstResultBase *pStTstResultBase);//将数据索引插入任务基础表//
	int   AutoCreateHrGroupSaveTab(CString strBaseTabName,CString strAttaTabName);
	BOOL  AddTstResultData(StTstResultAtta *pStTstResult,UINT nGroupOid);

	BOOL  DoDecFromTestDataXmlFile(  );				//执行解密_对测试结果数据XML文件
	BOOL  DoDecFromAppFile(char *szFileName);       //执行解密_对附件文件

};
