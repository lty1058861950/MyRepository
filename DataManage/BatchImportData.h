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
	StBasTask               *m_pStBaseInfo;//��ǰ¼�������ָ��//

	StHrUser                m_CheckUserInfo;
	vector<StBasTask *>     m_BatchTaskDataArray;
	vector<CString>         m_TaskDataFilePath;
public:
	BOOL  BatchTaskDataImport();
	BOOL  SingleTaskDataImport(CString strDataFilePath,vector<CString> &strErrorArray);//�������д���//

	//���ݵ��뺯������///
	//���ݵ�������//
	BOOL  ImPortTestData();//1.���ݱ���
	BOOL  ImPortTaskInfo();//2.������Ϣ����

	int   AnalysisData();//�������ݲ����浽���ݿ�//
	int   IsTstResultExists(UINT nGroupOid);//�ж�����������Ƿ����//
	BOOL  AddTstResultBase(StTstResultBase *pStTstResultBase);//�����������������������//
	int   AutoCreateHrGroupSaveTab(CString strBaseTabName,CString strAttaTabName);
	BOOL  AddTstResultData(StTstResultAtta *pStTstResult,UINT nGroupOid);

	BOOL  DoDecFromTestDataXmlFile(  );				//ִ�н���_�Բ��Խ������XML�ļ�
	BOOL  DoDecFromAppFile(char *szFileName);       //ִ�н���_�Ը����ļ�

};
