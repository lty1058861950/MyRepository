#pragma once
#include "afxcmn.h"
#include "ShowModeInfo.h"
// CModeMng �Ի���//

class CModeMng : public CDialog
{
	DECLARE_DYNAMIC(CModeMng)

public:
	CModeMng(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CModeMng();

// �Ի�������
	enum { IDD = IDD_MODEMNG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CShowModeInfo  m_ShowModeInfo;
	int            m_ShowType;
	
public:
	void  AutoSize();


	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	virtual void OnOK();
	virtual void OnCancel();
};
