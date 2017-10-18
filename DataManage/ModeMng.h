#pragma once
#include "afxcmn.h"
#include "ShowModeInfo.h"
// CModeMng 对话框//

class CModeMng : public CDialog
{
	DECLARE_DYNAMIC(CModeMng)

public:
	CModeMng(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CModeMng();

// 对话框数据
	enum { IDD = IDD_MODEMNG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
