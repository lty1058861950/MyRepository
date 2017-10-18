#pragma once

#include "DepartMng.h"
#include "Resource.h"
#include "mylistctrl\editablelistctrl.h"
// CShowDepart �Ի���
class CDepartMng;
class CShowDepart : public CDialog
{
	DECLARE_DYNAMIC(CShowDepart)

public:
	CShowDepart(CWnd* pParent = NULL);   // ��׼���캯��
	CShowDepart(int ShowType,CDepartMng* pDepartMng,
		CString PDID = "",CString DID = "",CWnd* pParent = NULL);
	virtual ~CShowDepart();

// �Ի�������
	enum { IDD = IDD_SHOWDEPART_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_ShowType;
	CDepartMng* m_pDepartMng;
	CEditableListCtrl m_ShowDepartUsrList;
	CString m_PDID,m_DID;
public:
	void   InitContrlStateAdd();
	void   InitContrlStateEdit();

	void   InitContrlInfoAdd();
	void   InitContrlInfoEdit();

	BOOL   CheckInfoAdd(StHrGroup *pDepartInfo);
	BOOL   CheckInfoEdit(StHrGroup *pDepartInfo);

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedShowdepartAddusrBtn();
	afx_msg void OnBnClickedShowdepartDelusrBtn();
protected:
	virtual void OnOK();
	
};
