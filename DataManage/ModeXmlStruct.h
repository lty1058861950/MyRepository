
#if !defined(AFX_MODEXML_STRUCT_H__INCLUDED_)
#define AFX_MODEXML_STRUCT_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//2017-01-21_add   �����
//----------------------------------------------------------------------------

//�����񱾵�XML�ļ��洢
#define XML_FILE_MUL_TASK_PAR_CFG	_T("MulTaskParCfg.txt")		//�������������_�ļ�����

//������XML�ļ�����
#define XML_FILE_MUL_TASK_LIST_DOWN  _T("MulTaskListDown.txt")	//������������_�ļ�����

//���񵼳���������ļ�����
#define XML_FILE_MUL_TASK_DATA_UP    _T("MulTaskDataUp.txt")		//���Խ���ϴ�_�ļ�����


#define ROOT_MUL_TASK_PAR_CFG	 _T("MulTaskParCfg")		//��������洢
#define ROOT_MUL_TASK_LIST_DOWN  _T("MulTaskListDown")		//������������
#define ROOT_MUL_TASK_DATA_UP    _T("MulTaskDataUp")		//���Խ���ϴ�

//����洢
#define TASK_CFG_CHECK_USER		_T("CheckUser")
#define TASK_CFG_PAD_DEV_ID		_T("PadDevId")

//��������
#define TASK_DOWN_CHECK_USER    _T("CheckUser")
#define TASK_DOWN_PAD_DEV_ID    _T("PadDevId")
#define TASK_DOWN_TIME			_T("TaskDownTime")

//����ϴ�
#define TASK_UP_CHECK_USER		_T("CheckUser")
#define TASK_UP_PAD_DEV_ID		_T("PadDevId")
#define TASK_UP_TIME		    _T("PadUpTime")

//===========================================================================
	//1.ģ���_�ṹ��Ϣ
	//2.ģ���_�������
	//3.ģ���_��ʷ��ֵ���

#define PATH_XML_MODE_PAR_CFG         "XmlModeParCfg"		//ģ���������

//XML�ļ���
#define MD_XML_FILE_TAB_SRT_INFO	"MdXmlTabSrtInfo.txt"	//1.ģ���_�ṹ��Ϣ
#define MD_XML_FILE_TAB_OUT_INFO	"MdXmlTabOutInfo.txt"	//2.ģ���_�������
#define MD_XML_FILE_TAB_HIS_INFO    "MdXmlTabHisInfo.txt"	//3.ģ���_��ʷ��ֵ���


//XML�ֶα�ʶ
#define MD_XML_CFG_TAB_SRT_INFO		"MdCfgTabSrtInfo"		//1.ģ���_�ṹ��Ϣ
#define MD_XML_CFG_TAB_OUT_INFO		"MdCfgTabOutInfo"		//2.ģ���_�������
#define MD_XML_CFG_TAB_HIS_INFO		"MdCfgTabHisInfo"		//3.ģ���_��ʷ��ֵ���

//XML�ֶα�ʶ_�ṹ��Ϣ
#define MD_XML_ROOT_TAB_SIZE_INFO   "TabSizeInfo"		//1.���ṹ_���м��ϲ���Ԫ�����
#define MD_XML_ROOT_TAB_ITEM_DATA   "TabItemData"		//3.���ģ��_��Ԫ������	
#define MD_XML_ROOT_TAB_HEAD_LEN    "TabHeadLen"        //2.���ṹ_��ͷ�п��		
#define MD_XML_ROOT_TAB_CELL_SRT    "TabCellSrt"		//5.���ģ��_�ϲ���Ԫ��ṹ
#define MD_XML_ROOT_TAB_ROW_SRT		"TabRowSrt"			//6.���ģ��_�м�ƽṹ
#define MD_XML_ROOT_TAB_COL_SRT		"TabColSrt"			//7.���ģ��_�м�ƽṹ
#define MD_XML_ROOT_TAB_DATA_SRT    "TabDataSrt"		//8.���ģ��_������ݽṹ
#define MD_XML_ROOT_TAB_ALARM_SRT	"TabAlarmSrt"		//9.���ģ��_���ݱ����ṹ	

//XML�ֶα�ʶ_�������
#define MD_XML_ROOT_OUT_BASE_DATA   "OutBaseData"		//11.���Խ��_�������� (���ݿ�)

#define MD_XML_ROOT_OUT_TEST_DATA   "OutTestData"       //12.���Խ��_������ʾ
#define MD_XML_ROOT_OUT_APP_DATA    "OutAppData"		//13.���Խ��_������ʾ

#define MD_XML_ROOT_TAB_BASE_SRT    "TabBaseSrt"        //10.���ģ��_���Ի�����Ϣ�ṹ (���ݿ�)




//XML��Ŀ¼����
#define MD_XML_ROOT_INFO            "RootInfo"

#define MD_XML_ATTR_ROOT_1          "ItemRoot1"
#define MD_XML_ATTR_ROOT_2          "ItemRoot2"
#define MD_XML_ATTR_ROOT_3          "ItemRoot3"
#define MD_XML_ATTR_ROOT_4          "ItemRoot4"

//XML��������
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
#define MD_XML_ST_DATA_BEG_ROW		"BegRow"	//��ʼ�к�
#define MD_XML_ST_DATA_BEG_COL      "BegCol"	//��ʼ�к�
#define MD_XML_ST_DATA_TYPE			"DataType"	//��������

#define MD_XML_ST_ROWCOL_POS        "Pos"
#define MD_XML_ST_ROWCOL_FLAG		"Flag"
#define MD_XML_ST_ROWCOL_NAME		"Name"

#define MD_XML_ST_TAB_ROW_CNT		"TabRowCnt"
#define MD_XML_ST_TAB_COL_CNT		"TabColCnt"

#define MD_XML_ST_CELL_BEG_ROW		"BegRow"
#define MD_XML_ST_CELL_BEG_COL		"BegCol"
#define MD_XML_ST_CELL_END_ROW		"EndRow"
#define MD_XML_ST_CELL_END_COL		"EndCol"

#define MD_XML_ST_ALA_CHECK_FLAG	"CheckFlag"		//�Ƿ���
#define MD_XML_ST_ALA_JUDGE_TYPE	"JudgeType"		//�ж�����
#define MD_XML_ST_ALA_JUDGE_DESC	"JudgeDesc"		//�ж�����
#define MD_XML_ST_ALA_TARGET_1      "Target1"		//ָ��ֵ1
#define MD_XML_ST_ALA_TARGET_2 		"Target2"		//ָ��ֵ2

//-------------------------------------------------------
#define MD_XML_ST_OUT_DATA 			"OutData"		//���Խ������	
#define MD_XML_ST_OUT_DESC 			"OutDesc"		//���Խ������	
#define MD_XML_ST_OUT_ALARM_FLAG	"AlarmFlag"		//����״̬
#define MD_XML_ST_OUT_HIS_FLAG		"HisFlag"		//��ʷ��ֵ���״̬
#define MD_XML_ST_OUT_TEST_USR      "TestUsr"		//������Ա
#define MD_XML_ST_OUT_TEST_TIME     "TestTime"		//����ʱ��


//������Ϣ
//-------------------------------------------------------
#define MD_XML_ST_APP_TAB_DATA_POS  "TabDataPos"	//�������_���(��1��ʼ) 
#define MD_XML_ST_APP_APPENDIX_TYPE "AppendixType"	//��������
#define MD_XML_ST_APP_SRC_FILE_NAME "SrcFileName"	//ԭʼ����
#define MD_XML_ST_APP_DES_FILE_NAME "DesFileName"	//��������=��Ʒ����_��Ʒ���_ģ������_����������(ԭʼ����)
#define MD_XML_ST_APP_UP_USR		"UpUsr"			//�ϴ���Ա
#define MD_XML_ST_APP_UP_TIME		"UpTime"		//�ϴ�ʱ��

//----------------------------------------------------------
#define MD_XML_ST_HIS_FLAG 			"HisFlag"		//����־				
#define MD_XML_ST_HIS_MIN			"ValMin"		//��Сֵ
#define MD_XML_ST_HIS_MAX			"ValMax"		//���ֵ

// Ĭ��ֵ����
// xml declaration
#define DECL_VERSION		"1.0"	// for XML Msg
#define DECL_ENCODING		"GB2312"
#define DECL_STANDALONE		"yes"

// Default settings for MSG
#define DEF_MSG_VERSION		"1"		// Ĭ��xml�汾
#define DEF_MSG_TYPE		"DT_TYPE"



#define PAR_MAX_CNT  50
#define FUN_MAX_CNT  20

#define TYPE_NODEFINE		0			//δ����
#define TYPE_VOID			1			//������
#define TYPE_STRUCT			2			//�ṹ��
#define TYPE_INTEGER		3			//����
#define TYPE_STRING			4			//�ַ���

#define TYPE_STR_NODEFINE   "Nodefine"	//δ����
#define TYPE_STR_VOID		"Void"		//������
#define TYPE_STR_STRUCT		"Struct"	//�ṹ��
#define TYPE_STR_INTEGER	"Integer"	//����
#define TYPE_STR_STRING		"String"	//�ַ���


#pragma pack(push) //�������״̬ 
#pragma pack(1)//�趨Ϊ1�ֽڶ���


typedef struct 
{
	char Version[30];
	char Type[30];
	char DateTime[30];
}XML_MSG_INFO;

#pragma pack(pop)//�ָ�����״̬


#endif // !defined(AFX_MODEXML_STRUCT_H__INCLUDED_)