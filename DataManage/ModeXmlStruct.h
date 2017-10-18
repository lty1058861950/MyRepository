
#if !defined(AFX_MODEXML_STRUCT_H__INCLUDED_)
#define AFX_MODEXML_STRUCT_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//2017-01-21_add   任务表
//----------------------------------------------------------------------------

//多任务本地XML文件存储
#define XML_FILE_MUL_TASK_PAR_CFG	_T("MulTaskParCfg.txt")		//多任务参数配置_文件名称

//任务导入XML文件名称
#define XML_FILE_MUL_TASK_LIST_DOWN  _T("MulTaskListDown.txt")	//测试任务下载_文件名称

//任务导出结果数据文件名称
#define XML_FILE_MUL_TASK_DATA_UP    _T("MulTaskDataUp.txt")		//测试结果上传_文件名称


#define ROOT_MUL_TASK_PAR_CFG	 _T("MulTaskParCfg")		//测试任务存储
#define ROOT_MUL_TASK_LIST_DOWN  _T("MulTaskListDown")		//测试任务下载
#define ROOT_MUL_TASK_DATA_UP    _T("MulTaskDataUp")		//测试结果上传

//任务存储
#define TASK_CFG_CHECK_USER		_T("CheckUser")
#define TASK_CFG_PAD_DEV_ID		_T("PadDevId")

//任务下载
#define TASK_DOWN_CHECK_USER    _T("CheckUser")
#define TASK_DOWN_PAD_DEV_ID    _T("PadDevId")
#define TASK_DOWN_TIME			_T("TaskDownTime")

//结果上传
#define TASK_UP_CHECK_USER		_T("CheckUser")
#define TASK_UP_PAD_DEV_ID		_T("PadDevId")
#define TASK_UP_TIME		    _T("PadUpTime")

//===========================================================================
	//1.模板表_结构信息
	//2.模板表_数据输出
	//3.模板表_历史极值检测

#define PATH_XML_MODE_PAR_CFG         "XmlModeParCfg"		//模板参数配置

//XML文件名
#define MD_XML_FILE_TAB_SRT_INFO	"MdXmlTabSrtInfo.txt"	//1.模板表_结构信息
#define MD_XML_FILE_TAB_OUT_INFO	"MdXmlTabOutInfo.txt"	//2.模板表_数据输出
#define MD_XML_FILE_TAB_HIS_INFO    "MdXmlTabHisInfo.txt"	//3.模板表_历史极值检测


//XML字段标识
#define MD_XML_CFG_TAB_SRT_INFO		"MdCfgTabSrtInfo"		//1.模板表_结构信息
#define MD_XML_CFG_TAB_OUT_INFO		"MdCfgTabOutInfo"		//2.模板表_数据输出
#define MD_XML_CFG_TAB_HIS_INFO		"MdCfgTabHisInfo"		//3.模板表_历史极值检测

//XML字段标识_结构信息
#define MD_XML_ROOT_TAB_SIZE_INFO   "TabSizeInfo"		//1.表格结构_行列及合并单元格个数
#define MD_XML_ROOT_TAB_ITEM_DATA   "TabItemData"		//3.表格模板_单元格数据	
#define MD_XML_ROOT_TAB_HEAD_LEN    "TabHeadLen"        //2.表格结构_表头列宽度		
#define MD_XML_ROOT_TAB_CELL_SRT    "TabCellSrt"		//5.表格模板_合并单元格结构
#define MD_XML_ROOT_TAB_ROW_SRT		"TabRowSrt"			//6.表格模板_列简称结构
#define MD_XML_ROOT_TAB_COL_SRT		"TabColSrt"			//7.表格模板_行简称结构
#define MD_XML_ROOT_TAB_DATA_SRT    "TabDataSrt"		//8.表格模板_输出数据结构
#define MD_XML_ROOT_TAB_ALARM_SRT	"TabAlarmSrt"		//9.表格模板_数据报警结构	

//XML字段标识_数据输出
#define MD_XML_ROOT_OUT_BASE_DATA   "OutBaseData"		//11.测试结果_基础数据 (数据库)

#define MD_XML_ROOT_OUT_TEST_DATA   "OutTestData"       //12.测试结果_数据显示
#define MD_XML_ROOT_OUT_APP_DATA    "OutAppData"		//13.测试结果_附件显示

#define MD_XML_ROOT_TAB_BASE_SRT    "TabBaseSrt"        //10.表格模板_测试基础信息结构 (数据库)




//XML根目录描述
#define MD_XML_ROOT_INFO            "RootInfo"

#define MD_XML_ATTR_ROOT_1          "ItemRoot1"
#define MD_XML_ATTR_ROOT_2          "ItemRoot2"
#define MD_XML_ATTR_ROOT_3          "ItemRoot3"
#define MD_XML_ATTR_ROOT_4          "ItemRoot4"

//XML名称描述
#define MD_XML_ATTR_INDEX_1         "Index1"
#define MD_XML_ATTR_INDEX_2         "Index2"
#define MD_XML_ATTR_INDEX_3         "Index3"
#define MD_XML_ATTR_INDEX_4         "Index4"

#define MD_XML_ATTR_NAME_1          "Name1"
#define MD_XML_ATTR_NAME_2          "Name2"
#define MD_XML_ATTR_NAME_3          "Name3"
#define MD_XML_ATTR_NAME_4          "Name4"

#define MD_XML_ATTR_TYPE_1          "Type1"
#define MD_XML_ATTR_TYPE_2          "Type2"
#define MD_XML_ATTR_TYPE_3          "Type3"
#define MD_XML_ATTR_TYPE_4          "Type4"

#define MD_XML_ATTR_COUNT_ROOT      "Count"
#define MD_XML_ATTR_COUNT_1         "Count1"
#define MD_XML_ATTR_COUNT_2         "Count2"
#define MD_XML_ATTR_COUNT_3         "Count3"
#define MD_XML_ATTR_COUNT_4         "Count4"

#define MD_XML_ATTR_VALUE_1         "Value1"
#define MD_XML_ATTR_VALUE_2         "Value2"
#define MD_XML_ATTR_VALUE_3         "Value3"
#define MD_XML_ATTR_VALUE_4         "Value4"

#define MD_XML_ATTR_EDIT_1			"Edit1"
#define MD_XML_ATTR_EDIT_2			"Edit2"
#define MD_XML_ATTR_EDIT_3			"Edit3"
#define MD_XML_ATTR_EDIT_4			"Edit4"

#define MD_XML_ATTR_DESC_1			"Desc1"
#define MD_XML_ATTR_DESC_2			"Desc2"
#define MD_XML_ATTR_DESC_3			"Desc3"
#define MD_XML_ATTR_DESC_4			"Desc4"

#define MD_XML_ATTR_SAVE_USR		"SaveUsr"
#define MD_XML_ATTR_SAVE_TIME		"SaveTime"	

//-------------------------------------------------------

//#define MD_XML_ATTR_ENABLE_CNT	"EnableCount"
#define MD_XML_ST_DATA_NAME         "NAME"
#define MD_XML_ST_DATA_DESC			"DESC"
#define MD_XML_ST_DATA_BEG_ROW		"BegRow"	//起始行号
#define MD_XML_ST_DATA_BEG_COL      "BegCol"	//起始列号
#define MD_XML_ST_DATA_TYPE			"DataType"	//数据类型

#define MD_XML_ST_ROWCOL_POS        "Pos"
#define MD_XML_ST_ROWCOL_FLAG		"Flag"
#define MD_XML_ST_ROWCOL_NAME		"Name"

#define MD_XML_ST_TAB_ROW_CNT		"TabRowCnt"
#define MD_XML_ST_TAB_COL_CNT		"TabColCnt"

#define MD_XML_ST_CELL_BEG_ROW		"BegRow"
#define MD_XML_ST_CELL_BEG_COL		"BegCol"
#define MD_XML_ST_CELL_END_ROW		"EndRow"
#define MD_XML_ST_CELL_END_COL		"EndCol"

#define MD_XML_ST_ALA_CHECK_FLAG	"CheckFlag"		//是否检测
#define MD_XML_ST_ALA_JUDGE_TYPE	"JudgeType"		//判断类型
#define MD_XML_ST_ALA_JUDGE_DESC	"JudgeDesc"		//判断名称
#define MD_XML_ST_ALA_TARGET_1      "Target1"		//指标值1
#define MD_XML_ST_ALA_TARGET_2 		"Target2"		//指标值2

//-------------------------------------------------------
#define MD_XML_ST_OUT_DATA 			"OutData"		//测试结果数据	
#define MD_XML_ST_OUT_DESC 			"OutDesc"		//测试结果描述	
#define MD_XML_ST_OUT_ALARM_FLAG	"AlarmFlag"		//报警状态
#define MD_XML_ST_OUT_HIS_FLAG		"HisFlag"		//历史极值检测状态
#define MD_XML_ST_OUT_TEST_USR      "TestUsr"		//测试人员
#define MD_XML_ST_OUT_TEST_TIME     "TestTime"		//测试时间


//附件信息
//-------------------------------------------------------
#define MD_XML_ST_APP_TAB_DATA_POS  "TabDataPos"	//结果数据_序号(从1开始) 
#define MD_XML_ST_APP_APPENDIX_TYPE "AppendixType"	//附件类型
#define MD_XML_ST_APP_SRC_FILE_NAME "SrcFileName"	//原始名称
#define MD_XML_ST_APP_DES_FILE_NAME "DesFileName"	//附件名称=产品代号_产品编号_模板名称_数据项名称(原始名称)
#define MD_XML_ST_APP_UP_USR		"UpUsr"			//上传人员
#define MD_XML_ST_APP_UP_TIME		"UpTime"		//上传时间

//----------------------------------------------------------
#define MD_XML_ST_HIS_FLAG 			"HisFlag"		//检测标志				
#define MD_XML_ST_HIS_MIN			"ValMin"		//最小值
#define MD_XML_ST_HIS_MAX			"ValMax"		//最大值

// 默认值定义
// xml declaration
#define DECL_VERSION		"1.0"	// for XML Msg
#define DECL_ENCODING		"GB2312"
#define DECL_STANDALONE		"yes"

// Default settings for MSG
#define DEF_MSG_VERSION		"1"		// 默认xml版本
#define DEF_MSG_TYPE		"DT_TYPE"



#define PAR_MAX_CNT  50
#define FUN_MAX_CNT  20

#define TYPE_NODEFINE		0			//未定义
#define TYPE_VOID			1			//空类型
#define TYPE_STRUCT			2			//结构体
#define TYPE_INTEGER		3			//整型
#define TYPE_STRING			4			//字符串

#define TYPE_STR_NODEFINE   "Nodefine"	//未定义
#define TYPE_STR_VOID		"Void"		//空类型
#define TYPE_STR_STRUCT		"Struct"	//结构体
#define TYPE_STR_INTEGER	"Integer"	//整型
#define TYPE_STR_STRING		"String"	//字符串


#pragma pack(push) //保存对齐状态 
#pragma pack(1)//设定为1字节对齐


typedef struct 
{
	char Version[30];
	char Type[30];
	char DateTime[30];
}XML_MSG_INFO;

#pragma pack(pop)//恢复对齐状态


#endif // !defined(AFX_MODEXML_STRUCT_H__INCLUDED_)