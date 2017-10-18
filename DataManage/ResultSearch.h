#pragma once
#include "mylistctrl\editablelistctrl.h"
#include "ResultShow.h"

#define  ID_MENU1_DELDATA_BASE              2011
#define  ID_MENU1_C_TASK_REPORT_BASE        2012
#define  ID_MENU1_DELDATA_ATTA              2021
#define  ID_MENU1_C_PRODUCT_REPORT_ATTA     2022
#define  ID_MENU1_C_MODE_REPORT_ATTA        2023
// CResultSearch �Ի���

class CResultSearch : public CDialog
{
	DECLARE_DYNAMIC(CResultSearch)

public:
	CResultSearch(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CResultSearch();

// �Ի�������
	enum { IDD = IDD_RESULT_SEARCH_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CMenu		m_PopupMenu1;
	CMenu		m_PopupMenu2;
	void InitPopMenu1( );					//��ʼ���˵�1
	void InitPopMenu2( );					//��ʼ���˵�2
public:
	void  AutoSize();
		
	void  SetContrlShow();

	BOOL  SearchBaseByTaskName();//ͨ��ģ����ѯ���������б�//

	BOOL  ShowCurData();//��ʾ�ҵ�������///

	void  DelBaseData();//������Ϊ��λɾ���������//
	void  DelAttaData();//�Խ������Ϊ��λɾ���������//

	void  CreateTaskReport();//������Ϊ��λ���ɱ����ļ�//
	void  CreateProductCodeReport();//�Բ�Ʒ���Ϊ��λ���ɱ����ļ�//
	void  CreateModeReport();//��ģ��Ϊ��λ���ɱ����ļ�
	void  CreateReportBase(vector<StTstResultAtta> *StResultAtta,CString strCreateFile);//���ɱ���
public:
	StTstResultBase m_TstResultBase;
	StTstResultAtta m_TstResultAtta;
	
	virtual BOOL OnInitDialog();

	afx_msg void OnPaint();
	CEditableListCtrl m_TstRresultAttaList;
	CEditableListCtrl m_TstRresultBaseList;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedResultSearchBtn();
protected:
	virtual void OnOK();
public:
	afx_msg void OnNMDblclkResultSearchList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickResultSearchList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedResultSearchTaskBtn();
	afx_msg void OnBnClickedResultSearchProductnoBtn();
	afx_msg void OnBnClickedResultSearchBeginBtn();
	afx_msg void OnBnClickedResultSearchEndBtn();
	afx_msg void OnNMRClickResultSearchList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickResultSearchList1(NMHDR *pNMHDR, LRESULT *pResult);
};
