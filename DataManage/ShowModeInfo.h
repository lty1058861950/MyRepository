#pragma once
#include "afxcmn.h"
#include "ShowModeStyle.h"
//#include "ShowModeAll.h"
// CShowModeInfo 对话框

class CModeMng;
class CShowModeInfo : public CDialog
{
	DECLARE_DYNAMIC(CShowModeInfo)

public:
	CShowModeInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CShowModeInfo();

// 对话框数据
	enum { IDD = IDD_SHOWMODEINFO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	StBasMode      m_CurModeInfo;//当前选中的模板//
	StBasMode      m_CutBoard;//剪切板 的模板//
	BOOL           m_CutType;//记录复制的状态//

	CTabCtrl m_ShowModeTab;
	CTreeCtrl *m_pModeTree;
	

	CShowModeStyle  m_ShowModeStyle;
	//CShowModeAll    m_ShowModeAll;
	int            m_ShowType;

	void  GetTreeItemType(HTREEITEM hItem,StBasMode *pStr);//获取所有父节点的类型//

	void  InitProductNoCom();
	void  InitModeTypeCom();
	void  InitModeRowValCom();

	void  SetControlShow(UINT nShow);
	void  SetProductCtrlShowType(int nModeType);//根据选择的模板类型 设置控件的状态//
	void  SetModeTypeCtrl(int nInitTabSrt);//根据模板表初始化的状态 设置控件的状态//
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
