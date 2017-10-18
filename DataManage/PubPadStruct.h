#pragma  once 

#define XLS_MAX_ROW   512   //ztedit for V1.7.3
#define XLS_MAX_COL   100
#define XLS_MAX_LEN   120

#define TAB_MAX_CELL_CNT  100
#define TAB_MAX_DATA_CNT  400
#define TMP_MAX_CNT   120

#define MD_MAX_APP_CNT  50

#define MUL_MAX_ROW   150

#define MAX_USR_NAME_LEN            100

#define MAX_PIC_NUM_CNT    200
#define MAX_PIC_NAME_LEN   50



#define TEXT_RIGHT_1	_T("合格")    
#define TEXT_WRONG_1	_T("不合格")
#define TEXT_RIGHT_2    _T("√")  
#define TEXT_WRONG_2	_T("×")


#define COND_NULL           _T("无")
#define COND_BIG			_T("x>x1")
#define COND_SMALL			_T("x<x1")
#define COND_BIGEQUAL		_T("x>=x1")
#define COND_SMALLEQUAL		_T("x<=x1")
#define COND_EQUAL			_T("x==x1")
#define COND_UNEQUAL		_T("x!=x1")
#define COND_BETWEEN_1		_T("x1<x<x2")
#define COND_BETWEEN_2		_T("x1<=x<=x2")
typedef struct 
{
	int	iBegRow;	//起始行号
	int iBegCol;	//起始列号
	int iEndRow;	//终止行号
	int iEndCol;	//终止列号
	int iRowNum;	//合并后行数
	int iColNum;	//合并后列数
}StTabCell; 


typedef struct 
{
	int  iRowPos;					//行号, (从1开始)
	int  bDataFlag;                 //数据状态
	char szRowName[XLS_MAX_LEN];	//行数据简称
}StTabRow; 


typedef struct 
{
	int  iColPos;					//列号, (从1开始)
	int  bDataFlag;
	char szColName[XLS_MAX_LEN];	//列数据简称
}StTabCol; 


typedef struct 
{
	char szDbColName[XLS_MAX_LEN];	//描述名称
	char szOutDataName[XLS_MAX_LEN];//数据名称 = [行简称_列简称]
	int  iBegRow;					//起始行号
	int	 iBegCol;					//起始列号
	int  iDataType;                 //数据类型：1.符点型, 2.字符串, 3.公式计算  
}StTabData; 


typedef struct 
{
	int  iBasePos;					//序号         
	char szBaseName[XLS_MAX_LEN];	//数据名称      
	int  iBaseType;                 //数据类型  
	int  szBaseFrom[XLS_MAX_LEN];	//数据来源  
}StTabBase; 


typedef struct 
{
	int		bCheckFlag;					//是否检测
	int		nJudgeType;				//判断类型
	char	szJudgeDesc[XLS_MAX_LEN];	//判断名称
	char	szTarget1[XLS_MAX_LEN];		//指标值1
	char	szTarget2[XLS_MAX_LEN];		//指标值2
	double	fTarget1;					//指标1(符点型)
	double	fTarget2;					//指标2(符点型)
}StTabAlarm; 

//历史级值检测
//----------------------------------------------------------------------
typedef struct 
{
	int		bHisChkFlag;				//是否进行历史极值检测
	char	szHisValMin[XLS_MAX_LEN];	//历史最小值
	char	szHisValMax[XLS_MAX_LEN];	//历史最大值
	double	fHisValMin;					//最小值(符点型)
	double	fHisValMax;					//最大值(符点型)
}StTabHisChk; 


//测试结果 = 测试基础信息 + N*测试数据 
//-----------------------------------------------------------------------
//测试结果_基础数据
typedef struct 
{
	char szTestBegTime[MAX_PATH];	//测试开始时间
	char szTestEndTimee[MAX_PATH];	//测试结束时间
	int  bTestFinished;				//测试完成标志             
	char szBaseCode[XLS_MAX_LEN];	//1.编号
	char szBaseTest[XLS_MAX_LEN];	//2.测试
	char szBaseCheck[XLS_MAX_LEN];	//3.检验
}StOutBaseData; 


//测试结果_附件数据  (附件Appdendix)
typedef struct 
{	
	int  nTabDataPos;				//结果数据_序号(从1开始) 
	int  nAppendixType;				//附件类型
	char szSrcFileName[MAX_PATH];	//原始名称
	char szDesFileName[MAX_PATH];	//附件名称=产品代号_产品编号_模板名称_数据项名称(原始名称)
	char szUpUsr[XLS_MAX_LEN];		//上传人员
	char szUpTime[XLS_MAX_LEN];		//上传时间
}StOutAppData;  


//测试结果_测试数据  
typedef struct 
{
	char szOutData[XLS_MAX_LEN];					//测试结果数据
	char szOutDesc[XLS_MAX_LEN];                    //测试结果描述    //ztadd 2016-12-29
	int  bAlarmFlag;								//报警状态
	int  bHisFlag;									//历史极值检测状状
	char szTestUsr[XLS_MAX_LEN];					//测试人员
	char szTestTime[XLS_MAX_LEN];					//测试时间
	int  nAppendixFileCnt;							//附件个数
	//StOutAppData stResultAppData[MD_MAX_APP_CNT];	//附件指针列表
}StOutTestData; 