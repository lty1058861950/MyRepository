#pragma once
#include "afxcmn.h"
#include "mylistctrl\editablelistctrl.h"

// CTaskNumbel �Ի���

class CTaskNumbelMng : public CDialog
{
	DECLARE_DYNAMIC(CTaskNumbelMng)

public:
	CTaskNumbelMng(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTaskNumbelMng();

// �Ի�������
	enum { IDD = IDD_TASK_NUMBEL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEditableListCtrl m_ShowTaskInfoNumbelsList;
	CExcelOptFun  m_ExcelOptFun;
	CArray<StBasTaskCode,StBasTaskCode> TaskCodeArray;
	CShowTaskInfo *m_pShowTaskInfo;
	StBasTask     *m_pCurTaskInfo;
	BOOL  ContinueAddProdNumbel(CString &OutInfo);//������Ӳ�Ʒ�����Ϣ//
	BOOL  CheckListRepeatText(void *nList,int index,CString strText);//���List���Ƿ����ظ����ı�///
	afx_msg void OnBnClickedShowtaskinfoAddprodnumbelBtn();
	afx_msg void OnBnClickedShowtaskinfoBatchloadBnt();//
	afx_msg void OnBnClickedShowtaskinfoDelnumBnt();//
	afx_msg void OnBnClickedShowtaskinfoNumdelallBnt();//
	virtual BOOL OnInitDialog();

	int  MyList_SetListItemEdit(CListCtrl *pList, int row, int col);
	void  FindCurTaskProdNumbels();//��ʾ�������еĲ�Ʒ�����Ϣ//
protected:
	virtual void OnOK();
};
