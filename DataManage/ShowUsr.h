#pragma once


class CUserMenage;
// CShowUsr �Ի���

class CShowUsr : public CDialog
{
	DECLARE_DYNAMIC(CShowUsr)

public:
	CShowUsr(CWnd* pParent = NULL);   // ��׼���캯��
	CShowUsr(int ShowType,CUserMenage* pUsrMng,CWnd* pParent = NULL);
	virtual ~CShowUsr();

// �Ի�������
	enum { IDD = IDD_SHOWUSR_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_ShowType;
	CUserMenage *m_pUsrMng;
	CString m_CurSelUsrName;
	CStringArray m_UsrTypeName;
	CStringArray m_UsrStateName;

	void    SetContrlStateAdd();
	void    SetContrlStateEdit();


	void    InitContrlInfoAdd();
	void    InitContrlInfoEdit();


	void    InitComBoxs();
	void    SetUserDepart(UINT nGroupOid);
	void    SerUserType(int nUserType);
	void    SerUserPadID(int nPadDevID);//7


	BOOL    CheckInfoAdd(StHrUser *pUsrInfo);//��� ����û� ��Ϣ�Ƿ���������//
	BOOL    CheckInfoEdit(StHrUser *pUsrInfo);//��� �޸��û� ��Ϣ�Ƿ���������//
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	afx_msg void OnBnClickedShowusrResetpwndBtn();
};
