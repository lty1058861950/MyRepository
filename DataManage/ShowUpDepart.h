#pragma once


// CShowUpDepart 对话框

class CShowUpDepart : public CDialog
{
	DECLARE_DYNAMIC(CShowUpDepart)

public:
	CShowUpDepart(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CShowUpDepart();

// 对话框数据
	enum { IDD = IDD_SHOW_UP_DEPART_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int   m_ShowType;
	StHrUpDepart *m_pUpDepart;
	virtual BOOL OnInitDialog();
	void     DisPalyUpDepartInfo();
	int     GetUpDepartInfo();
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
