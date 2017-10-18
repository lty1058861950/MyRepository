#pragma once
#include "afxcmn.h"
#include "ShowModeStyle.h"
//#include "ShowModeAll.h"
// CShowModeInfo �Ի���

class CModeMng;
class CShowModeInfo : public CDialog
{
	DECLARE_DYNAMIC(CShowModeInfo)

public:
	CShowModeInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CShowModeInfo();

// �Ի�������
	enum { IDD = IDD_SHOWMODEINFO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	StBasMode      m_CurModeInfo;//��ǰѡ�е�ģ��//
	StBasMode      m_CutBoard;//���а� ��ģ��//
	BOOL           m_CutType;//��¼���Ƶ�״̬//

	CTabCtrl m_ShowModeTab;
	CTreeCtrl *m_pModeTree;
	

	CShowModeStyle  m_ShowModeStyle;
	//CShowModeAll    m_ShowModeAll;
	int            m_ShowType;

	void  GetTreeItemType(HTREEITEM hItem,StBasMode *pStr);//��ȡ���и��ڵ������//

	void  InitProductNoCom();
	void  InitModeTypeCom();
	void  InitModeRowValCom();

	void  SetControlShow(UINT nShow);
	void  SetProductCtrlShowType(int nModeType);//����ѡ���ģ������ ���ÿؼ���״̬//
	void  SetModeTypeCtrl(int nInitTabSrt);//����ģ����ʼ����״̬ ���ÿؼ���״̬//
	BOOL  SetModeTypeRorvarComBoText(StBasMode *pStr);
	void  DisPalyModeInfo();
	BOOL  GetModeInfoChange();

	void  CopyModeStruct(StBasMode *pDecModeInfo,StBasMode *pSrcModeInfo);
	BOOL  AddNewMode();
	BOOL  DelMode();
	BOOL  EditMode();

	BOOL  CopyModeTree();
	BOOL  PasteMode();

	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void  AutoSize();

	
	afx_msg void OnTcnSelchangeShowmodeinfoTab(NMHDR *pNMHDR, LRESULT *pResult);
protected:
	virtual void OnOK();
public:
	afx_msg void OnBnClickedDelTabBtn();
	afx_msg void OnCbnSelchangeShowmodeinfoTypeEdt();
protected:
	virtual void OnCancel();
public:
	afx_msg void OnBnClickedModeSelProductnoBtn();
};
