#pragma once


// CCurDepartSel 对话框

class CCurDepartSel : public CDialog
{
	DECLARE_DYNAMIC(CCurDepartSel)

public:
	CCurDepartSel(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCurDepartSel();

// 对话框数据
	enum { IDD = IDD_CURDEPART_SEL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	void     InitDepartList();
};
