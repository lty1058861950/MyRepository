//////////////////////////////////////////////////////////////////////////
//定义全局函数，变量，常量.
//////////////////////////////////////////////////////////////////////////
#pragma  once 


#define SQL_SELECT	1
#define SQL_UPDATE	2

#define G_TREEID    8
#define Max_Log_Item  100
#define TEXT_SIZE_GRID				16
#define TAB_GRID_HEIGHT   45
#define Sel_Product_OFF 1       //产品筛选开关//
#define TITLE_VERSION     _T("V1.1.0")   //版本信息//
#define TITLE_DATE        _T("2017-04-05 13:30")
#define TITLE_INFO        _T("交互式移动采集管理软件")



//V1.1.0_2017-04-05
//1.加入数据解密处理


//[Report_Paper_Direction]
//PaperDirection=1
//ztadd for lty

enum eSelCheck { UnSel_Check = 0, Sel_Check};
enum eGuideItem { Product_Item = 0, Mode_Item, Task_Item, Result_Item};
enum eUserType { user_normal = 0, user_advance, user_admin };
enum eBatchOpt { Batch_Group = 0, Sel_Product, Batch_OutTask, Batch_InTaskData};
enum eGroupStatus { Group_Invalid = 0, Group_Valid};								//0.不可用， 1.可用
enum eUpDepartMng { UpDepart_Add = 0, UpDepart_Modify, UpDepart_View};//交检部门的  添加  更改  查看///
enum eModeFormula { Report_Mode = 0, Formula_Mode};  //报告模板   公式模板//

//产品//
enum eProdShowType{ Add_Product = 0, Modify_Product, View_Product};//添加模式 、修改模式 、查看模式///
enum eProductType { Product_normal = 0, Product_Line };//普通产品////线缆产品//      
//enum eSeriesType { Series_Hav = 0, Series_Not};
enum ePicNum { Detail = 0, Simple };//详细的  简单的//

//模板//
enum eModeShowType{ Add_NewMode = 0, Modify_Mode, View_Mode, Tree_Modify_Mode};//添加模式 、修改模式 、查看模式、从树上修改模式///
enum eModeType { Mode_Currency = 0, Mode_Dedicated, Mode_LineDed, Mode_NotUse};
enum eModeRowval { ModeRow_NoChange = 0, ModeRow_Change, ModeRow_All};
enum eModeInitTab { ModeTab_UnInit = 0, ModeTab_Init, ModeTab_All};

//任务//
enum eTaskShowType{ Add_NewTask = 0, Modify_Task, View_Task,Tree_Modify_Task};//添加模式 、修改模式 、查看模式、从树上修改模式///
enum eTaskStatus { Task_Init=0, Task_OK, Task_Runing, Task_Finish, Task_All};//任务状态//
enum eTaskType { Task_Test = 0, Task_ReTest, Task_HelpReTest};//任务类型//
enum eTaskArmy { Army_Not = 0, Army_Yes, Army_All};   //否  是  全部//
enum eTaskDownUpLoad { Task_DownLoad = 0, Task_UpLoad}; // 任务下载, 结果上传//
enum eTaskModifyType { Task_ModifyBase, Task_ModifyAll};  //修改模式  Task_ModifyBase: 只修改基本信息   Task_ModeAll: 修改全部信息(包括 编号 模板 图号)

//列表显示

enum eShowType{ Show_Product, Show_Mode, Show_Task, Show_OneMode, Show_OneTask, Show_Result};
//               产品_列表    模板_列表,  任务_列表， 模板_对话框， 任务_对话框

//查询//
enum eSearchPageNum{ Five_Result = 0, Ten_Result, Twenty_Result, All_Result};  //每显示的个数  5、10、20、全部数据//
enum eResultType { Result_Task = 0, Result_Atta};//任务查询  结果数据查询//
enum eSearchModel { Task_DarkSearch = 0, Task_ExactSearch, Result_Search};//查询模式:  基于任务模糊查询  基于任务ID的精确查询  多条件综合模糊查询//

enum eAddObject { Add_ProductNo = 0, Add_Series, Add_Mode, Add_Task};

//生成产品报告3中方式//  1.以任务为单位  2.以产品编号为单位    3.以模板为单位
enum eCreateReport { CreateReport_Task, CreateReport_ProdCode, CreateReport_Mode};

//证明书//
enum eTestimonialPage { Testimonial_Page1, Testimonial_Page2, Testimonial_Page3, Testimonial_Page4,
					  Testimonial_Page5, Testimonial_Page6, Testimonial_Page7, Testimonial_Page8,
					  Testimonial_Page9, Testimonial_Page10, Testimonial_Page11, Testimonial_Page12 };

enum ePage4Type { Page4_Type1, Page4_Type2, Page4_Type3};
//各个模块的Tree节点类型//


//部门模块//
#define Group_Tree_Type1               1
#define Group_Tree_Type2               2

//产品模块//
#define PROD_TREE_TYPE_DEPART          5    
#define PROD_TREE_TYPE_PRODCODE        7
//模板管理模块//
#define MODE_TREE_TYPE_DEPART          11
#define MODE_TREE_TYPE_MODETYPE        12
#define MODE_TREE_TYPE_PRODCODE        13
#define MODE_TREE_TYPE_MODE            14
//任务管理模块//
#define TASK_TREE_TYPE_DEPART          16
#define TASK_TREE_TYPE_TASKTYPE        17
#define TASK_TREE_TYPE_PRODCODE        18
#define TASK_TREE_TYPE_TASK            20

//结果数据查询分类//
#define RESULT_TREE_TYPE_DEPART       26
#define RESULT_TREE_TYPE_TYPE         27
#define RESULT_TREE_TYPE_PRODUCT      28
#define RESULT_TREE_TYPE_SERIES       29

//证明书模块//
#define TESTIMONIAL_TREE_PAGE1     30
#define TESTIMONIAL_TREE_PAGE2     31
#define TESTIMONIAL_TREE_PAGE3     32
#define TESTIMONIAL_TREE_PAGE4     33
#define TESTIMONIAL_TREE_PAGE5     34
#define TESTIMONIAL_TREE_PAGE6     35
#define TESTIMONIAL_TREE_PAGE7     36
#define TESTIMONIAL_TREE_PAGE8     37
#define TESTIMONIAL_TREE_PAGE9     38
#define TESTIMONIAL_TREE_PAGE10    39
#define TESTIMONIAL_TREE_PAGE11    40
#define TESTIMONIAL_TREE_PAGE12    41
//模板的显示风格的参数属性///

#define IDC_GRID  10011 //GridCtrl控件的ID///

#define GRID_BK_COLOR			RGB(255,  255,  255)			//表格外部背景颜色
#define GRID_TEXT_COLOR			RGB(0,  0,    0  )				//表格内所有单元格文字颜色
#define GRID_TEXT_BK_COLOR		RGB(0xFF, 0xFF, 0xFF)			//表格内所有单元格背景颜色

#define MY_TABLE_HEAD_COLOR     RGB(226, 233, 241)              //表格内表头颜色
#define MY_GRID_LINE_COLOR      RGB(128, 128, 128)				//表格线颜色

#define GRID_LINE_COLOR         RGB(0,	0,	0	) 



  
#define MODE_TREE_ROOT_TEXT "测试模板管理"           //模板树的根节点//
#define MODE_TREE_TYPE1_TEXT "模板类型1"             //模板树的根节点//
#define MODE_TREE_TYPE1_1_TEXT "模板小类1_1"         //模板树的根节点//
#define MODE_TREE_TYPE2_TEXT "模板类型2"             //模板树的根节点//
#define MODE_TREE_TYPE2_1_TEXT "模板小类1_1"         //模板树的根节点//


#define Seq_Role               "seq_role.nextval"
#define Seq_User               "seq_user.nextval"
#define Seq_UserCurID          "seq_user.currval"

#define Seq_Group              "seq_group.nextval"
#define Seq_GroupCurID         "seq_group.currval"

#define Seq_Group_Save         "seq_group_save.nextval"
#define Seq_Group_SaveCurID    "seq_group_save.currval"

#define Seq_Depart              "seq_depart.nextval"
#define Seq_DepartCurID         "seq_depart.currval"

#define Seq_Product            "seq_product.nextval"
#define Seq_ProductCurID       "seq_product.currval "

#define Seq_Series             "seq_series.nextval"
#define Seq_SeriesCurID        "seq_series.currval"

#define Seq_PicNum             "seq_picnum.nextval"
#define Seq_PicNumCurID        "seq_picnum.currval" 

#define Seq_Mode               "seq_mode.nextval"
#define Seq_ModeCurID          "seq_mode.currval"
#define Seq_Mode_Save          "seq_mode_save.nextval"
#define Seq_Mode_SaveCurID     "seq_mode_save.currval"

#define Seq_Task               "Seq_Task.nextval"
#define Seq_TaskCurID          "Seq_Task.currval"

#define Seq_Task_Code          "seq_Task_code.nextval"
#define Seq_Task_CodeCurID     "seq_Task_code.currval"
#define Seq_Task_Mode          "seq_Task_mode.nextval"
#define Seq_Task_ModeCurID     "seq_Task_mode.currval"
#define Seq_Task_PicNum        "seq_Task_picNum.nextval"
#define Seq_Task_PicNumCurID   "seq_Task_picNum.currval"


//配置文件的名字///
#define USRMNG_USRCFG_FILENAME "SysUsrMngCfg.ini"
#define Prode_Type_Cfg         "ProdeTypeCfg.ini"
#define ExclosureFile_Path     "ExclosureFile"            //附件存储目录
#define Report_Mode_Path       "ReportMode"               //报告模板文件夹//
#define Report_Temp_Path       "ReportTempPath"           //生成报告时缓存目录//
#define Report_FILE_EX         ".doc"
#define Mode_Formula_Path      "MulTaskCal"          //模板公式路径//
#define Formula_FILE_EX         ".xlsx"

///zt

#define TAB_VIEW_MES_INSTITUTE       _T("VIEW_CHK_INSTITUTE_TEST")

#define NOT_SERIES                   _T("")