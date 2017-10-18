#pragma once
#include "afxcmn.h"
#include "ShowTaskData.h"
#include "ResultSearch.h"
#include "ResultSearchNew.h"
#include "mylistctrl\editablelistctrl.h"
#include "SqliteDb\CppSQLite3.h"
#include "LoadOutTaskXmlAnalysis.h"
#include "PathDialog.h"
#include "TaskCfg.h"

// CShowTaskInfo �Ի���

class CShowTaskInfo : public CDialog
{
	DECLARE_DYNAMIC(CShowTaskInfo)

public:
	CShowTaskInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CShowTaskInfo();

// �Ի�������
	enum { IDD = IDD_SHOWTASKINFO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	//CShowTaskDetailInfo m_ShowTaskDetailInfo;
	DECLARE_MESSAGE_MAP()
public:

	CTaskCfg          m_TaskCfg;			//�������ã� ��Ʒ��š�ģ�塢ͼ��
	CShowTaskData     m_ShowTaskData;		//�������飺 
	CResultSearch     m_ResultSearch;		//�������
	CResultSearchNew  m_ResultSearchNew;//�°����ʷ����//

	CTreeCtrl         *m_pTaskTree;
	StBasTask         m_CurTaskInfo;

	CTabCtrl          m_ShowTaskInfoTab;

	LoadOutTaskXmlAnalysis m_LoadOutTask;
	int               m_ShowType;
	
	CppSQLite3DB  m_SqliteDb;
protected:
	virtual void OnOK();
public:
	void  AutoSize();
	void  SetControlShow(UINT nShow);//������Ϣ//

	void  GetTreeItemType(HTREEITEM hItem,StBasTask *pStr);

	//BOOL  AddNewTask();	//�½�����///
	BOOL  EditTast();		//�޸��������//
	BOOL  DelTast();		//ɾ���������//

	BOOL  SendTaskToPad();	//�·��������//
	BOOL  StopTask();		//��ֹ�������//


	//�������
	//----------------------------------------------------------------
	void  DisplayTaskInfo();			//����������ʾ��Ϣ//
	void  FindCurTaskProdNumbels();		//��ʾ�������еĲ�Ʒ�����Ϣ//
	void  FindCurTaskModes();			//��ʾ��������ģ����Ϣ//
	void  FindCurTaskPicNum();			//��ʾ������ѡ�е�ͼ��//
	void  BuildTaskDetail();			//�齨�������ϸ��Ϣ//
	
	void  InitTaskTypeComBo();			//��ʼ�� ComBox//
    UINT  GetSelDepartOid();			

	CString GetCDateCtrlTime(UINT UID);	//��ȡʱ��ؼ���ʱ��///
	BOOL  GetChangeTaskInfo();			//���������Ϣ�Ƿ񱻸���/


	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	afx_msg void OnTcnSelchangeShowtaskinfoTab(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL DestroyWindow();

	afx_msg void OnBnClickedSelProductnoBtn();
	afx_msg void OnBnClickedSelUpdepartBtn();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
protected:
	virtual void OnCancel();
};
