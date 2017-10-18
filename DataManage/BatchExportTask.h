#pragma once

#include "SqliteDb\CppSQLite3.h"
#include "LoadOutTaskXmlAnalysis.h"
#include "PathDialog.h"
#include "MainFrm.h"
#include "ModeXmlStruct.h"
class CBatchExportTask
{
public:
	CBatchExportTask(void);
	~CBatchExportTask(void);
public:
	vector<StBasTask *>      m_BatchTaskArray;
	StBasTask               *m_pStBasTaskInfo;
	LoadOutTaskXmlAnalysis   m_LoadOutTask;
	CppSQLite3DB        m_SqliteDb;
	/*CModeParMng			m_ModeParMng;
	CModeXmlAnalysis	m_ModeXmlAnalysis;*/
public:
	BOOL  BatchSendTask(CString strDefFilePath);
	BOOL  SingleSendTask(CString szGetName, vector<CString> &strErrorArray);
	//任务导出函数集合///
	BOOL  ExPortUsrInfo();//1.导出用户信息//
	BOOL  ExPortModeInfo();//2.导出模板信息//
	BOOL  ExPortTaskInfo();//3.导出任务信息//
	BOOL  ExPortProdNumbelsInfo();//4.导出产品编号//
	BOOL  ExPortModeTabStr(UINT nModeOidm,CString strTabName);//5.导出模板数据表结构///

	BOOL  ExPortHisValue();//导出极值表，遍历极值表 以产品/模板为单位 组建XML文件极值//
	BOOL  ExPortEnclosure();//导出附件表结构//

	BOOL  CopyTaskMode(StBasTaskMode *pTaskMode);
	BOOL  AutoBuildTabStruct(CString nModeTabName,
		CppSQLite3DB *pSqlite,int Flags, vector<StBasModeDesc> *pStModeDesArray);//0.创建Sqlite  //1.创建Oracle 

};
