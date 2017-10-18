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

enum TabDataType { datatype_null, datatype_num, datatype_string, datatype_caluate};		//1.浮点型, 2.字符串, 3.公式计算

enum TabConfigType 
{ 
	Tab_SizeInfo=1,      //1.表格结构_行列及合并单元格个数
	Tab_HeadLen,		//2.表格结构_表头列宽度
		
	Tab_ItemData,		//3.表格模板_单元格数据		
	Tab_ItemFlag,		//4.表格模板_单元格标志
	Tab_CellSrt,		//5.表格模板_合并单元格结构
		
	Tab_RowSrt,			//6.表格模板_列简称结构
	Tab_ColSrt,			//7.表格模板_行简称结构
	Tab_DataSrt,		//8.表格模板_输出数据结构
	Tab_AlarmSrt,		//9.表格模板_数据报警结构
		
	Tab_BaseSrt,        //10.表格模板_测试基础信息结构 (数据库)
	Out_BaseData,		//11.测试结果_基础数据 (数据库)
	Out_TestData,       //12.测试结果_数据显示
	Out_AppData,		//13.测试结果_附件显示
	Prod_HisChk,        //14.历史极值检测信息
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
	mode_normal = 0,	//标准类型
	mode_rowvar,		//行可变类型
};

#define TAB_CLR_EDIT_BK		   RGB(230, 230, 230)
#define TAB_CLR_DATA_BK_ALA	   RGB(255, 193, 193)   //错误颜色 (红色)
#define TAB_CLR_DATA_BK_HIS	   RGB(251, 212, 180)   //错误颜色 (橙色)
#define TAB_CLR_DATA_BK_APP	   RGB(214, 227, 228)   //背景颜色 (中绿色)
#define TAB_CLR_DATA_BK_NO     RGB(234, 241, 221)   //背景颜色 (浅绿色)

#define TAB_CLR_DATA_NUM_BK    RGB(234, 241, 221)	//背景颜色 (浅绿色)
#define TAB_CLR_DATA_STR_BK    RGB(219, 229, 241)	//背景颜色 (浅蓝色)
#define TAB_CLR_DATA_CAL_BK    RGB(216, 216, 216)   //背景颜色 (灰色)



#define TAB_CLR_DATA_BK_ORDER		RGB(216, 216, 216)   //序号背景 
#define TAB_CLR_DATA_BK_NAME		RGB(219, 238, 243)   //名称背景

#define TAB_CLR_DATA_BK_CALCULATE	RGB(204,192,218)	 //计算背景 (紫色)
//#define TAB_CLR_DATA_BK_CALCULATE	RGB(184, 104, 228)   //计算背景 (蓝色)


#define MIN_COL_WIDTH          20
#define MAX_COL_WIDTH          500
#define DEF_COL_WIDTH          120


#define TITLE_NAME_MODE_PAR_CFG		_T("检验记录模板配置")
#define TITLE_NAME_PROD_HIS_CHK		_T("产品历史极值信息")
//1.检验模板目录树
//----------------------------------------------------------
//1.1检验模板_结构配置
#define TREE_NAME_TAB_SRT_CFG		_T("检验记录模板_结构配置")
#define TREE_NAME_TAB_SIZE_INFO			_T("表格行列配置") 
#define TREE_NAME_TAB_HEAD_LEN			_T("表格列宽度配置") 
#define TREE_NAME_TAB_ITEM_DATA			_T("单元格数据配置") 
#define TREE_NAME_TAB_ITEM_FLAG 		_T("单元格标志") 
#define TREE_NAME_TAB_CELL_SRT			_T("合并单元格配置")

//1.2检测模板_数据配置
#define TREE_NAME_TAB_DATA_CFG		_T("检验记录模板_数据配置") 
#define TREE_NAME_TAB_ROW_SRT			_T("行简称结构配置") 
#define TREE_NAME_TAB_COL_SRT 			_T("列简称结构配置") 
#define TREE_NAME_TAB_DATA_SRT			_T("输出数据结构")

//1.3检测模板_报警配置
#define TREE_NAME_TAB_ALARM_CFG		_T("检验记录模板_报警配置") 
#define TREE_NAME_TAB_ALARM_SRT			_T("报警参数配置") 

//2.产品历史极值信息
//----------------------------------------------------------
#define TREE_NAME_TAB_HIS_CFG		_T("产品统计_历史极值") 
#define TREE_NAME_TAB_HIS_INFO			_T("产品历史极值信息") 

//3.测试结果
#define TREE_NAME_TAB_OUT_RESULT	_T("检验记录_测试结果")
#define TREE_NAME_TAB_OUT_DATA			_T("测试结果数据信息") 
#define TREE_NAME_TAB_OUT_APP			_T("测试结果附件信息") 


#define TAB_DATA_TYPE_NUM		_T("数值型")
#define TAB_DATA_TYPE_STRING	_T("字符串")
#define TAB_DATA_TYPE_CAL       _T("公式计算") 


/*

Tab_HeadLen=1,		//1.表格模板_表头列宽度
Tab_ItemData,		//2.表格模板_单元格数据		
Tab_ItemFlag,		//3.表格模板_单元格标志
Tab_CellSrt,		//4.表格模板_合并单元格结构
Tab_RowSrt,			//5.表格模板_列简称结构
Tab_ColSrt,			//6.表格模板_行简称结构
Tab_DataSrt,		//7.表格模板_输出数据结构
Tab_AlarmSrt,		//8.表格模板_数据报警结构

Tab_BaseSrt,        //9.表格模板_测试基础信息结构 (数据库)
Out_BaseData,		//10.测试结果_基础数据 (数据库)
Out_TestData,       //11.测试结果_数据显示
Out_AppData,		//12.测试结果_附件显示
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
	char ***m_ItemInfo;					//1.数据信息	
	int   **m_ItemFlag;					//2.数据标志	[XLS_MAX_ROW][XLS_MAX_COL]
	int    *m_ColLen;					//3.列长度		[XLS_MAX_COL]
	int     m_nSumColLen;               //总列长
	
public: //
	int			m_nTabCellCnt;							
	StTabCell  *m_stTabCell;			//4.合并单元格	[XLS_CELL_CNT]
		
	int			m_nTabRowSrtCnt;		//有效行个数
	StTabRow   *m_stTabRow;				//5.行参数设置	[XLS_MAX_ROW]
	
	int			m_nTabColSrtCnt;		//有效列个数
	StTabCol   *m_stTabCol;				//6.列参数设置	[XLS_MAX_COL]

	//测试结果数据相关
	//---------------------------------------------------------------------
	int			m_nDataCnt;
	StTabData  *m_stTabData;			//7.测试结果	[TAB_MAX_DATA_CNT]

	StTabAlarm *m_stTabAlarm;			//8.报警设置	[TAB_MAX_DATA_CNT]

	//历史级值检测
	//----------------------------------------------------------------------
	StTabHisChk *m_stTabHisChk;			//9.历史极值检测[TAB_MAX_DATA_CNT]


	//测试结果输出
	//----------------------------------------------------------------------
	StOutTestData *m_stOutTestData;		//10.测试结果	[TAB_MAX_DATA_CNT]

	int           m_nOutAppDataCnt;
	StOutAppData  *m_stOutAppData;		//11.附件信息	[MD_MAX_APP_CNT]
	StOutAppData  *m_stTmpOutAppData;	//12.Tmp附件信息[MD_MAX_APP_CNT]

	//多行测试结果相关
	//----------------------------------------------------------------------
	int           m_nModeType;				//模板类型  
	int           m_nMulRowCnt;				//多行行数 
	int			  m_nMulDataCnt;            //多行数据个数
	int           m_mulrow;
                

	char          m_szUsrName[MAX_USR_NAME_LEN];			//用户名称
	char          m_szOutAppDataUsrName[MAX_USR_NAME_LEN];	//测试结果_用户名称
	char          m_szOutAppDataUsrTime[MAX_USR_NAME_LEN];  //测试结查_存储时间

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
	void CalculateTabCellSize( );					//获取数据长度
	int  CheckTabCellOk( );							//检测合并单元格是否正确
	void ResetItemFlag( );							//重置标志状态
	void GetItemFlagFromData( );                    //从ItemData获取ItemFlag

	//------------------------------------------------------------------------------
	int  GetTabDataList( );							//获取数据列表	
	int  GetTabCellType(char *szDataName);			//获取单元格数据类型
	int  GetTabDataRowAndColNameFlag( );			//获取行名称和列名称标志
	int  CheckTabDataRowAndColNotNull( );			//检测TabData行和列不为空
	int  GetTabDataRowAndColNameToStTabData( );     //获取表数据

	//报警相关
	//------------------------------------------------------------------------------
	int  GetTabAlarmJudgeTypeFromDesc(char *szJudgeDesc);  
	int  GetTabAlarmJudgeDescFormType(int nJudgeType, char *szJudgeDesc);
	int  GetTabAlarmDisDescFromPos(int nPos, char *szDisDesc);
	int  GetTabDataPos(int iRow, int iCol);
	int  CalculateAlarmFlag(int nPos, double fVal);
	
	int  CalculateHisChkFlag(int nPos, double fVal);


	int  CalculateFetchProgress( );

	
	//数据列表显示相关
	//==============================================================================
	void ListCtrl_ClearAllColumn(CListCtrl *pList);
		
	void DisplayTabSizeInfo(CListCtrl *pList);		//显示表格模板_表格尺寸信息
	void DisplayTabHeadLen(CListCtrl *pList);		//显示表格模板_表头列宽度
	void DisplayTabItemData(CListCtrl *pList);		//显示表格模板_单元格数据
	void DisplayTabItemFlag(CListCtrl *pList);		//显示表格模板_单元格标志
	void DisplayTabCellSrtCfg(CListCtrl *pList);	//显示表格模板_合并单元格结构
	void DisplayTabCellSrt(CListCtrl *pList);		//显示表格模板_合并单元格结构

	void DisplayTabRowSrt(CListCtrl *pList);		//显示表格模板_列名称配置信息
    void DisplayTabColSrt(CListCtrl *pList);		//显示表格模板_行名称配置信息
	void DisplayTabOutDataSrt(CListCtrl *pList);	//显示表格模板_输出数据结构
	void DisplayTabAlarmSrt(CListCtrl *pList);		//显示表格模板_数据报警配置

	void DisplayProdHisChk(CListCtrl *pList);		//产品统计_历史极值报警

	void DisplayProdAppData(CListCtrl *pList);		//测试结果_附件信息

	//数据存储相关
	//==============================================================================
	int  SaveTabSizeInfo(CListCtrl *pList);
	int  SaveTabHeadLen(CListCtrl *pList);
	int	 SaveTabItemData(CListCtrl *pList);
	int  SaveTabCellSrt(CListCtrl *pList);

	int  SaveTabRowSrt(CListCtrl *pList);
	int  SaveTabColSrt(CListCtrl *pList);

	int  SaveTabOutDataSrt(CListCtrl *pList);

	int  SaveTabAlarmSrt(CListCtrl *pList);

	int  SaveProdHisChk(CListCtrl *pList);			//产品统计_历史极值配置

	//目录树
	//================================================================================
	void InitTree_TabStruct(CTreeCtrl *pTree);		//目录树_模板结构
	void InitTree_TabResult(CTreeCtrl *pTree);		//目录树_测试结果

	int MyList_SetListItemEdit(CListCtrl *pList, int row, int col);							//设置单元格可更改				
	int MyList_SetListItemBkColor(CListCtrl *pList, int row, int col, COLORREF bkColor);	//设置单元格标识	
	int MyList_ResetListItemBkColor(CListCtrl *pList, int row, int col);					//设置单元格标识
	int MyList_RemoveAllListMark(CListCtrl *pList);											//清除列表所有标记
	int MyList_SetListEdit(CListCtrl *pList, BOOL bEdit);


	//Excel操作
	int GetExcelCalModeResult(char *szExcelCalModeName);									//获取计算结果数据
	int SetExcelCalModeInputNum(char *szExcelTmpModeName);									//设置输入结果数据
	int GetExcelCalModeCalulateNum(char *szExcelTmpModeName);								//获取生成结果数据

	int GetDataTypeStr(int iDataType, char *szDataType);

	int IsTableCalType( );

};

#endif // !defined(AFX_MODEPARMNG_H__B266F315_DB1E_4FEC_A8B9_EB7F4B7B8F8F__INCLUDED_)
