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
	//���񵼳���������///
	BOOL  ExPortUsrInfo();//1.�����û���Ϣ//
	BOOL  ExPortModeInfo();//2.����ģ����Ϣ//
	BOOL  ExPortTaskInfo();//3.����������Ϣ//
	BOOL  ExPortProdNumbelsInfo();//4.������Ʒ���//
	BOOL  ExPortModeTabStr(UINT nModeOidm,CString strTabName);//5.����ģ�����ݱ�ṹ///

	BOOL  ExPortHisValue();//������ֵ��������ֵ�� �Բ�Ʒ/ģ��Ϊ��λ �齨XML�ļ���ֵ//
	BOOL  ExPortEnclosure();//����������ṹ//

	BOOL  CopyTaskMode(StBasTaskMode *pTaskMode);
	BOOL  AutoBuildTabStruct(CString nModeTabName,
		CppSQLite3DB *pSqlite,int Flags, vector<StBasModeDesc> *pStModeDesArray);//0.����Sqlite  //1.����Oracle 

};
