#pragma once
#include "mylistctrl\editablelistctrl.h"
#include "ResultSearchInfo.h"
#include "ResultList.h"

// CResultSearchNew �Ի���
#define  ID_MENU1_DELDATA_BASE_NEW              2011
#define  ID_MENU1_C_TASK_REPORT_BASE_NEW        2012
#define  ID_MENU1_DELDATA_ATTA_NEW              2021
#define  ID_MENU1_C_PRODUCT_REPORT_ATTA_NEW     2022
#define  ID_MENU1_C_MODE_REPORT_ATTA_NEW        2023
class CResultSearchNew : public CDialog
{
	DECLARE_DYNAMIC(CResultSearchNew)

public:
	CResultSearchNew(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CResultSearchNew();

// �Ի�������
	enum { IDD = IDD_RESULT_SEARCH_NEW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CMenu		m_PopupMenu1;
	CMenu		m_PopupMenu2;
	void InitPopMenu1( );					//��ʼ���˵�1
	void InitPopMenu2( );					//��ʼ���˵�2

	void  Menu1Fuction();
	void  DelBaseDataNew();//������Ϊ��λɾ���������//

	void  Menu2Fuction();
	void  CreateTaskReportNew();//������Ϊ��λ���ɱ����ļ�//
	void  CreateProductCodeReportNew();//�Բ�Ʒ���Ϊ��λ���ɱ����ļ�//
	void  CreateModeReportNew();//��ģ��Ϊ��λ���ɱ����ļ�
	void  CreateReportBaseNew(vector<StTstResultAtta> *StResultAtta,CString strCreateFile);//���ɱ���

public:
	StBasTask    m_ResultSearchInfo;
	StTstResultAtta   m_CurSelResultAtta;
	CResultSearchInfo  m_ResultSearchInfoDlg;
	CResultList  m_ResultTaskBase, m_ResultAttach;

	CEditableListCtrl m_TstRresultBaseList;
	CEditableListCtrl m_TstRresultAttaList;
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void     AutoSize();
	void     InitListCtrlColumn();
	void     InsertTaskBaseDataToList(StTstResultBaseNew *pTaskBaseData);
	void     InsertResultAttachToList(StTstResultAtta    *pResultAttachData);

	void  SetContrlShow();    //���ÿؼ���״̬//
	int  SearchResultData();  //��ѯ����//


	BOOL  GetCurSelAttaData( );      //��ȡ��ǰ��ѡ�еĽ����������
	int   ShowAttaData();      //��ʾ��������//
	
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickList2(NMHDR *pNMHDR, LRESULT *pResult);
};
