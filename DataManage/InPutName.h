#pragma once


// CInPutName �Ի���

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
	CInPutName(InputInfo *pInputInfo,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInPutName();

// �Ի�������
	enum { IDD = IDD_INPUT_NAME_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	InputInfo *m_pInputInfo;
	virtual BOOL OnInitDialog();
	void    InitWindowText();
	BOOL    CheckName(int nType);// ��� ���ƵĺϷ���//
protected:
	virtual void OnOK();
public:
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
};
