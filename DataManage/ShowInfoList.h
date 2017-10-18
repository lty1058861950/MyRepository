#pragma once
#include "mylistctrl\editablelistctrl.h"

#include "ResultList.h"
#include "ProductSearch.h"
#include "ProductFuction.h"
#include "ProductInfo.h"
#include "ProductPicNum.h"

#include "ModeFuction.h"
#include "ModeSearch.h"

#include "TaskFuction.h"
#include "TaskSearch.h"



// CShowInfoList �Ի���

class CShowInfoList : public CDialog
{
	DECLARE_DYNAMIC(CShowInfoList)

public:
	CShowInfoList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CShowInfoList();

// �Ի�������
	enum { IDD = IDD_SHOWLIST_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	
	CResultList    m_ResultList;			//����б�_����ҳ

	CProductSearch m_ProductSearch;			//��Ʒ��ѯ�Ի���_��ѯ����
	/*CProductInfo   m_ProductInfo;
	CProductPicNum m_ProductPicNum;*/
	CProductFuction m_ProductFuction;		//��Ʒ�����Ի���_������ť


	CShowModeInfo  m_ShowModeInfo;			//ģ��Ի���
	CModeSearch    m_ModeSearch;			//ģ���ѯ�Ի���_��ѯ����
	CModeFuction   m_ModeFuction;			//ģ������Ի���_������ť



	CTaskFuction  m_TaskFuction;
	CShowTaskInfo  m_ShowTaskInfo;
	CTaskSearch   m_TaskSearch;
	int          m_ShowType;

	virtual BOOL OnInitDialog();
	void    AutoSize();
	void ListCtrl_ClearAllColumn();

	void ChangeShowWindow(int nShowType);								//�л���ʾ
	void ChangeTaskBtnShow(StBasTask *pTaskSearchInfo);					//�����л�: ���������ɹ�����ִ�У������

	void DisplayProdInfo(StBasProduct *pStBasProduct);					//��ʾ��Ʒ�б�
	void InsertOneProdToList(StBasProduct *pStBasProduct);				//����һ����Ʒ�����б�
	void ModifyOneProdToList(int nIndex, StBasProduct *pStBasProduct);	//�޸�һ����Ʒ���¸���
	
	void DisplayModeInfo(StBasMode *pModesearchInfo);					//��ʾģ���б�
	void InsertOneModeToList(StBasMode *pStBasMode);					//����һ��ģ������б�
	void ModifyOneModeToList(int nIndex, StBasMode *pStBasMode);		//�޸�һ����Ʒ�����б�

	int  DisPlayTaskInfo(StBasTask *pStBasTaskSearchInfo);				//��ʾ�����б�
	void InsertOneTaskToList(StBasTask *pStBasTask);					//����һ����������б�
	void ModifyOneTaskToList(int nIndex,StBasTask *pBasTaskInfo);		//�޸�һ����������б�

	void DisplayOneModeDescInfo();										//��ʾһ��ģ��Ի���
	void DisplayOneTaskDescInfo();										//��ʾһ������Ի���

protected:
	virtual void OnOK();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
