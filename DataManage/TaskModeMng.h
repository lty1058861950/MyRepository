#pragma once
#include "mylistctrl\editablelistctrl.h"
#include "afxcmn.h"

// CTaskModeMng �Ի���

class CTaskModeMng : public CDialog
{
	DECLARE_DYNAMIC(CTaskModeMng)

public:
	CTaskModeMng(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTaskModeMng();

// �Ի�������
	enum { IDD = IDD_TASK_MODE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEditableListCtrl m_ShowTaskInfoModeList;//��ǰʹ�õ�ģ��//
	CEditableListCtrl m_CurTaskAllModeList;//���к�ѡģ��//
	StBasTask *m_pCurTaskInfo;

	CShowTaskInfo *m_pShowTaskInfo;
	virtual BOOL OnInitDialog();
	BOOL  CheckListRepeatText(void *nList,int index,UINT nModeOid);//���List���Ƿ����ظ����ı�///
	afx_msg void OnBnClickedShowtaskinfoAddallmodeBtn();
	afx_msg void OnBnClickedShowtaskinfoAddmodeBtn();
	afx_msg void OnBnClickedShowtaskinfoDelmodeBtn();
	afx_msg void OnBnClickedShowtaskinfoDelallmodeBtn();

	void  FindCurTaskModes();
	void OnUpdateChart(UINT nID) ;

protected:
	virtual void OnOK();
};
