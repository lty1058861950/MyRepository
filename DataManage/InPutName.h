#pragma once


// CInPutName 对话框

typedef struct _InputInfo{
	int     Type;
	int     nPicNum;
	int     nSeries;
	CString WindowText;
	CString NameStatic;
	CString CodeStatic;
	CString OutName;
	CString OutCode;
}InputInfo;
class CInPutName : public CDialog
{
	DECLARE_DYNAMIC(CInPutName)

public:
	CInPutName(InputInfo *pInputInfo,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInPutName();

// 对话框数据
	enum { IDD = IDD_INPUT_NAME_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	InputInfo *m_pInputInfo;
	virtual BOOL OnInitDialog();
	void    InitWindowText();
	BOOL    CheckName(int nType);// 检查 名称的合法性//
protected:
	virtual void OnOK();
public:
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
};
