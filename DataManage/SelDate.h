#pragma once
#include "afxdtctl.h"


// CSelDate �Ի���

class CSelDate : public CDialog
{
	DECLARE_DYNAMIC(CSelDate)

public:
	CSelDate(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSelDate();

// �Ի�������
	enum { IDD = IDD_SEL_DATE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	SYSTEMTIME m_stTime;
	CMonthCalCtrl m_SelDate;
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMcnSelchangeMonthcalendarDate(NMHDR *pNMHDR, LRESULT *pResult);
};
