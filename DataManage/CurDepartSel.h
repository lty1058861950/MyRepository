#pragma once


// CCurDepartSel �Ի���

class CCurDepartSel : public CDialog
{
	DECLARE_DYNAMIC(CCurDepartSel)

public:
	CCurDepartSel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCurDepartSel();

// �Ի�������
	enum { IDD = IDD_CURDEPART_SEL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	void     InitDepartList();
};
