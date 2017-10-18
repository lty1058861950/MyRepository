#pragma once


class CUserMenage;
// CShowUsr 对话框

class CShowUsr : public CDialog
{
	DECLARE_DYNAMIC(CShowUsr)

public:
	CShowUsr(CWnd* pParent = NULL);   // 标准构造函数
	CShowUsr(int ShowType,CUserMenage* pUsrMng,CWnd* pParent = NULL);
	virtual ~CShowUsr();

// 对话框数据
	enum { IDD = IDD_SHOWUSR_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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


	BOOL    CheckInfoAdd(StHrUser *pUsrInfo);//检查 添加用户 信息是否完整可行//
	BOOL    CheckInfoEdit(StHrUser *pUsrInfo);//检查 修改用户 信息是否完整可行//
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	afx_msg void OnBnClickedShowusrResetpwndBtn();
};
