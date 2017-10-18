#pragma once
#include "mylistctrl\editablelistctrl.h"

#define   ID_MENU1_LOADIN    2000
#define   ID_MENU2_OPENDIR   2001

// CReportMode �Ի���

class CReportMode : public CDialog
{
	DECLARE_DYNAMIC(CReportMode)

public:
	CReportMode(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CReportMode();

// �Ի�������
	enum { IDD = IDD_REPORT_MODE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	CMenu		m_PopupMenu1;
	void        InitPopMenu1( );					//��ʼ���˵�1
	CString     m_CurFilePath;

	int         m_ShowType;

public:
	virtual BOOL OnInitDialog();
	void    InitReportModeList();
	COLORREF ModeFileIsExists(CString szFilePath, int Index);//��鵱ǰ����ģ���Ƿ����//
	//CString BuildFilePath(StBasMode *pModeInfo);//�齨ģ��·��//
	void     InsertModeToList(StBasMode *pModeInfo);

	void    Refurbish();//ˢ��״̬//

	void    LoadInModeFile();//����ģ���ļ�//
	void    OpenFileDir();//���ļ������ļ���//
	void    AutoSize();
	CEditableListCtrl m_ReportModeList;
	afx_msg void OnBnClickedShowBtn();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void OnUpdateChart(UINT nID) ;

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
};
