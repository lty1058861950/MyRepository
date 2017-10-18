// ModeParMng.h: interface for the CModeParMng class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODEPARMNG_H__B266F315_DB1E_4FEC_A8B9_EB7F4B7B8F8F__INCLUDED_)
#define AFX_MODEPARMNG_H__B266F315_DB1E_4FEC_A8B9_EB7F4B7B8F8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PubStruct.h"
#include "MyListCtrl/EditableListCtrl.h"

#define CALC_SIGN_KEY	0xa000
#define DATA_TYPE_KEY   0xa001
#define ALA_SWITCH_KEY  0xa002

#define HEAD_CHAR			'D'
#define SPEC_CHAR			"_"

#define SPEC_CHAR_N_NUM     'N'
#define SPEC_CHAR_S_STR     'S'
#define SPEC_CHAR_C_CAL     'C'

#define SPEC_CHAR_O_ORD		'O'
#define SPEC_CHAR_P_PIC		'P'

enum TabCellType { cell_null, cell_desc, cell_data, cell_order, cell_name, cell_string, cell_calculate };

enum TabDataType { datatype_null, datatype_num, datatype_string, datatype_caluate};		//1.������, 2.�ַ���, 3.��ʽ����

enum TabConfigType 
{ 
	Tab_SizeInfo=1,      //1.���ṹ_���м��ϲ���Ԫ�����
	Tab_HeadLen,		//2.���ṹ_��ͷ�п��
		
	Tab_ItemData,		//3.���ģ��_��Ԫ������		
	Tab_ItemFlag,		//4.���ģ��_��Ԫ���־
	Tab_CellSrt,		//5.���ģ��_�ϲ���Ԫ��ṹ
		
	Tab_RowSrt,			//6.���ģ��_�м�ƽṹ
	Tab_ColSrt,			//7.���ģ��_�м�ƽṹ
	Tab_DataSrt,		//8.���ģ��_������ݽṹ
	Tab_AlarmSrt,		//9.���ģ��_���ݱ����ṹ
		
	Tab_BaseSrt,        //10.���ģ��_���Ի�����Ϣ�ṹ (���ݿ�)
	Out_BaseData,		//11.���Խ��_�������� (���ݿ�)
	Out_TestData,       //12.���Խ��_������ʾ
	Out_AppData,		//13.���Խ��_������ʾ
	Prod_HisChk,        //14.��ʷ��ֵ�����Ϣ
};

enum TabCondType 
{ 
	type_null=0,      //1.
	type_big,			
	type_small,		
	type_bigequal,		
	type_smallequal,		
	type_equal,		
	type_unequal,	
	type_between1,	
	type_between2,			
};


enum TabErrType
{
	err_no = 0,
	err_alarm,
	err_hischk
};

enum TabModeType
{
	mode_normal = 0,	//��׼����
	mode_rowvar,		//�пɱ�����
};

#define TAB_CLR_EDIT_BK		   RGB(230, 230, 230)
#define TAB_CLR_DATA_BK_ALA	   RGB(255, 193, 193)   //������ɫ (��ɫ)
#define TAB_CLR_DATA_BK_HIS	   RGB(251, 212, 180)   //������ɫ (��ɫ)
#define TAB_CLR_DATA_BK_APP	   RGB(214, 227, 228)   //������ɫ (����ɫ)
#define TAB_CLR_DATA_BK_NO     RGB(234, 241, 221)   //������ɫ (ǳ��ɫ)

#define TAB_CLR_DATA_NUM_BK    RGB(234, 241, 221)	//������ɫ (ǳ��ɫ)
#define TAB_CLR_DATA_STR_BK    RGB(219, 229, 241)	//������ɫ (ǳ��ɫ)
#define TAB_CLR_DATA_CAL_BK    RGB(216, 216, 216)   //������ɫ (��ɫ)



#define TAB_CLR_DATA_BK_ORDER		RGB(216, 216, 216)   //��ű��� 
#define TAB_CLR_DATA_BK_NAME		RGB(219, 238, 243)   //���Ʊ���

#define TAB_CLR_DATA_BK_CALCULATE	RGB(204,192,218)	 //���㱳�� (��ɫ)
//#define TAB_CLR_DATA_BK_CALCULATE	RGB(184, 104, 228)   //���㱳�� (��ɫ)


#define MIN_COL_WIDTH          20
#define MAX_COL_WIDTH          500
#define DEF_COL_WIDTH          120


#define TITLE_NAME_MODE_PAR_CFG		_T("�����¼ģ������")
#define TITLE_NAME_PROD_HIS_CHK		_T("��Ʒ��ʷ��ֵ��Ϣ")
//1.����ģ��Ŀ¼��
//----------------------------------------------------------
//1.1����ģ��_�ṹ����
#define TREE_NAME_TAB_SRT_CFG		_T("�����¼ģ��_�ṹ����")
#define TREE_NAME_TAB_SIZE_INFO			_T("�����������") 
#define TREE_NAME_TAB_HEAD_LEN			_T("����п������") 
#define TREE_NAME_TAB_ITEM_DATA			_T("��Ԫ����������") 
#define TREE_NAME_TAB_ITEM_FLAG 		_T("��Ԫ���־") 
#define TREE_NAME_TAB_CELL_SRT			_T("�ϲ���Ԫ������")

//1.2���ģ��_��������
#define TREE_NAME_TAB_DATA_CFG		_T("�����¼ģ��_��������") 
#define TREE_NAME_TAB_ROW_SRT			_T("�м�ƽṹ����") 
#define TREE_NAME_TAB_COL_SRT 			_T("�м�ƽṹ����") 
#define TREE_NAME_TAB_DATA_SRT			_T("������ݽṹ")

//1.3���ģ��_��������
#define TREE_NAME_TAB_ALARM_CFG		_T("�����¼ģ��_��������") 
#define TREE_NAME_TAB_ALARM_SRT			_T("������������") 

//2.��Ʒ��ʷ��ֵ��Ϣ
//----------------------------------------------------------
#define TREE_NAME_TAB_HIS_CFG		_T("��Ʒͳ��_��ʷ��ֵ") 
#define TREE_NAME_TAB_HIS_INFO			_T("��Ʒ��ʷ��ֵ��Ϣ") 

//3.���Խ��
#define TREE_NAME_TAB_OUT_RESULT	_T("�����¼_���Խ��")
#define TREE_NAME_TAB_OUT_DATA			_T("���Խ��������Ϣ") 
#define TREE_NAME_TAB_OUT_APP			_T("���Խ��������Ϣ") 


#define TAB_DATA_TYPE_NUM		_T("��ֵ��")
#define TAB_DATA_TYPE_STRING	_T("�ַ���")
#define TAB_DATA_TYPE_CAL       _T("��ʽ����") 


/*

Tab_HeadLen=1,		//1.���ģ��_��ͷ�п��
Tab_ItemData,		//2.���ģ��_��Ԫ������		
Tab_ItemFlag,		//3.���ģ��_��Ԫ���־
Tab_CellSrt,		//4.���ģ��_�ϲ���Ԫ��ṹ
Tab_RowSrt,			//5.���ģ��_�м�ƽṹ
Tab_ColSrt,			//6.���ģ��_�м�ƽṹ
Tab_DataSrt,		//7.���ģ��_������ݽṹ
Tab_AlarmSrt,		//8.���ģ��_���ݱ����ṹ

Tab_BaseSrt,        //9.���ģ��_���Ի�����Ϣ�ṹ (���ݿ�)
Out_BaseData,		//10.���Խ��_�������� (���ݿ�)
Out_TestData,       //11.���Խ��_������ʾ
Out_AppData,		//12.���Խ��_������ʾ
};
*/





class CModeParMng  
{
public:
	CModeParMng();
	virtual ~CModeParMng();

public:
	int		m_IsNew;
	
	int		m_row;
	int		m_col;
	char ***m_ItemInfo;					//1.������Ϣ	
	int   **m_ItemFlag;					//2.���ݱ�־	[XLS_MAX_ROW][XLS_MAX_COL]
	int    *m_ColLen;					//3.�г���		[XLS_MAX_COL]
	int     m_nSumColLen;               //���г�
	
public: //
	int			m_nTabCellCnt;							
	StTabCell  *m_stTabCell;			//4.�ϲ���Ԫ��	[XLS_CELL_CNT]
		
	int			m_nTabRowSrtCnt;		//��Ч�и���
	StTabRow   *m_stTabRow;				//5.�в�������	[XLS_MAX_ROW]
	
	int			m_nTabColSrtCnt;		//��Ч�и���
	StTabCol   *m_stTabCol;				//6.�в�������	[XLS_MAX_COL]

	//���Խ���������
	//---------------------------------------------------------------------
	int			m_nDataCnt;
	StTabData  *m_stTabData;			//7.���Խ��	[TAB_MAX_DATA_CNT]

	StTabAlarm *m_stTabAlarm;			//8.��������	[TAB_MAX_DATA_CNT]

	//��ʷ��ֵ���
	//----------------------------------------------------------------------
	StTabHisChk *m_stTabHisChk;			//9.��ʷ��ֵ���[TAB_MAX_DATA_CNT]


	//���Խ�����
	//----------------------------------------------------------------------
	StOutTestData *m_stOutTestData;		//10.���Խ��	[TAB_MAX_DATA_CNT]

	int           m_nOutAppDataCnt;
	StOutAppData  *m_stOutAppData;		//11.������Ϣ	[MD_MAX_APP_CNT]
	StOutAppData  *m_stTmpOutAppData;	//12.Tmp������Ϣ[MD_MAX_APP_CNT]

	//���в��Խ�����
	//----------------------------------------------------------------------
	int           m_nModeType;				//ģ������  
	int           m_nMulRowCnt;				//�������� 
	int			  m_nMulDataCnt;            //�������ݸ���
	int           m_mulrow;
                

	char          m_szUsrName[MAX_USR_NAME_LEN];			//�û�����
	char          m_szOutAppDataUsrName[MAX_USR_NAME_LEN];	//���Խ��_�û�����
	char          m_szOutAppDataUsrTime[MAX_USR_NAME_LEN];  //���Խ��_�洢ʱ��

	int           m_nFetchPercent;
	int           m_nFetchCnt;
	int           m_nFetchSum;
	int           m_bFetchFinished;
	char          m_szFetchSaveTime[30];

	int           m_bCalType;

public:
	int  NewItemInfo( );
	int  DeleteItemInfo( );
	int  ClearParamInfo( int IsInit = 1 );

public:
	void CalculateTabCellSize( );					//��ȡ���ݳ���
	int  CheckTabCellOk( );							//���ϲ���Ԫ���Ƿ���ȷ
	void ResetItemFlag( );							//���ñ�־״̬
	void GetItemFlagFromData( );                    //��ItemData��ȡItemFlag

	//------------------------------------------------------------------------------
	int  GetTabDataList( );							//��ȡ�����б�	
	int  GetTabCellType(char *szDataName);			//��ȡ��Ԫ����������
	int  GetTabDataRowAndColNameFlag( );			//��ȡ�����ƺ������Ʊ�־
	int  CheckTabDataRowAndColNotNull( );			//���TabData�к��в�Ϊ��
	int  GetTabDataRowAndColNameToStTabData( );     //��ȡ������

	//�������
	//------------------------------------------------------------------------------
	int  GetTabAlarmJudgeTypeFromDesc(char *szJudgeDesc);  
	int  GetTabAlarmJudgeDescFormType(int nJudgeType, char *szJudgeDesc);
	int  GetTabAlarmDisDescFromPos(int nPos, char *szDisDesc);
	int  GetTabDataPos(int iRow, int iCol);
	int  CalculateAlarmFlag(int nPos, double fVal);
	
	int  CalculateHisChkFlag(int nPos, double fVal);


	int  CalculateFetchProgress( );

	
	//�����б���ʾ���
	//==============================================================================
	void ListCtrl_ClearAllColumn(CListCtrl *pList);
		
	void DisplayTabSizeInfo(CListCtrl *pList);		//��ʾ���ģ��_���ߴ���Ϣ
	void DisplayTabHeadLen(CListCtrl *pList);		//��ʾ���ģ��_��ͷ�п��
	void DisplayTabItemData(CListCtrl *pList);		//��ʾ���ģ��_��Ԫ������
	void DisplayTabItemFlag(CListCtrl *pList);		//��ʾ���ģ��_��Ԫ���־
	void DisplayTabCellSrtCfg(CListCtrl *pList);	//��ʾ���ģ��_�ϲ���Ԫ��ṹ
	void DisplayTabCellSrt(CListCtrl *pList);		//��ʾ���ģ��_�ϲ���Ԫ��ṹ

	void DisplayTabRowSrt(CListCtrl *pList);		//��ʾ���ģ��_������������Ϣ
    void DisplayTabColSrt(CListCtrl *pList);		//��ʾ���ģ��_������������Ϣ
	void DisplayTabOutDataSrt(CListCtrl *pList);	//��ʾ���ģ��_������ݽṹ
	void DisplayTabAlarmSrt(CListCtrl *pList);		//��ʾ���ģ��_���ݱ�������

	void DisplayProdHisChk(CListCtrl *pList);		//��Ʒͳ��_��ʷ��ֵ����

	void DisplayProdAppData(CListCtrl *pList);		//���Խ��_������Ϣ

	//���ݴ洢���
	//==============================================================================
	int  SaveTabSizeInfo(CListCtrl *pList);
	int  SaveTabHeadLen(CListCtrl *pList);
	int	 SaveTabItemData(CListCtrl *pList);
	int  SaveTabCellSrt(CListCtrl *pList);

	int  SaveTabRowSrt(CListCtrl *pList);
	int  SaveTabColSrt(CListCtrl *pList);

	int  SaveTabOutDataSrt(CListCtrl *pList);

	int  SaveTabAlarmSrt(CListCtrl *pList);

	int  SaveProdHisChk(CListCtrl *pList);			//��Ʒͳ��_��ʷ��ֵ����

	//Ŀ¼��
	//================================================================================
	void InitTree_TabStruct(CTreeCtrl *pTree);		//Ŀ¼��_ģ��ṹ
	void InitTree_TabResult(CTreeCtrl *pTree);		//Ŀ¼��_���Խ��

	int MyList_SetListItemEdit(CListCtrl *pList, int row, int col);							//���õ�Ԫ��ɸ���				
	int MyList_SetListItemBkColor(CListCtrl *pList, int row, int col, COLORREF bkColor);	//���õ�Ԫ���ʶ	
	int MyList_ResetListItemBkColor(CListCtrl *pList, int row, int col);					//���õ�Ԫ���ʶ
	int MyList_RemoveAllListMark(CListCtrl *pList);											//����б����б��
	int MyList_SetListEdit(CListCtrl *pList, BOOL bEdit);


	//Excel����
	int GetExcelCalModeResult(char *szExcelCalModeName);									//��ȡ����������
	int SetExcelCalModeInputNum(char *szExcelTmpModeName);									//��������������
	int GetExcelCalModeCalulateNum(char *szExcelTmpModeName);								//��ȡ���ɽ������

	int GetDataTypeStr(int iDataType, char *szDataType);

	int IsTableCalType( );

};

#endif // !defined(AFX_MODEPARMNG_H__B266F315_DB1E_4FEC_A8B9_EB7F4B7B8F8F__INCLUDED_)
