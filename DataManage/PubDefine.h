//////////////////////////////////////////////////////////////////////////
//����ȫ�ֺ���������������.
//////////////////////////////////////////////////////////////////////////
#pragma  once 


#define SQL_SELECT	1
#define SQL_UPDATE	2

#define G_TREEID    8
#define Max_Log_Item  100
#define TEXT_SIZE_GRID				16
#define TAB_GRID_HEIGHT   45
#define Sel_Product_OFF 1       //��Ʒɸѡ����//
#define TITLE_VERSION     _T("V1.1.0")   //�汾��Ϣ//
#define TITLE_DATE        _T("2017-04-05 13:30")
#define TITLE_INFO        _T("����ʽ�ƶ��ɼ��������")



//V1.1.0_2017-04-05
//1.�������ݽ��ܴ���


//[Report_Paper_Direction]
//PaperDirection=1
//ztadd for lty

enum eSelCheck { UnSel_Check = 0, Sel_Check};
enum eGuideItem { Product_Item = 0, Mode_Item, Task_Item, Result_Item};
enum eUserType { user_normal = 0, user_advance, user_admin };
enum eBatchOpt { Batch_Group = 0, Sel_Product, Batch_OutTask, Batch_InTaskData};
enum eGroupStatus { Group_Invalid = 0, Group_Valid};								//0.�����ã� 1.����
enum eUpDepartMng { UpDepart_Add = 0, UpDepart_Modify, UpDepart_View};//���첿�ŵ�  ���  ����  �鿴///
enum eModeFormula { Report_Mode = 0, Formula_Mode};  //����ģ��   ��ʽģ��//

//��Ʒ//
enum eProdShowType{ Add_Product = 0, Modify_Product, View_Product};//���ģʽ ���޸�ģʽ ���鿴ģʽ///
enum eProductType { Product_normal = 0, Product_Line };//��ͨ��Ʒ////���²�Ʒ//      
//enum eSeriesType { Series_Hav = 0, Series_Not};
enum ePicNum { Detail = 0, Simple };//��ϸ��  �򵥵�//

//ģ��//
enum eModeShowType{ Add_NewMode = 0, Modify_Mode, View_Mode, Tree_Modify_Mode};//���ģʽ ���޸�ģʽ ���鿴ģʽ���������޸�ģʽ///
enum eModeType { Mode_Currency = 0, Mode_Dedicated, Mode_LineDed, Mode_NotUse};
enum eModeRowval { ModeRow_NoChange = 0, ModeRow_Change, ModeRow_All};
enum eModeInitTab { ModeTab_UnInit = 0, ModeTab_Init, ModeTab_All};

//����//
enum eTaskShowType{ Add_NewTask = 0, Modify_Task, View_Task,Tree_Modify_Task};//���ģʽ ���޸�ģʽ ���鿴ģʽ���������޸�ģʽ///
enum eTaskStatus { Task_Init=0, Task_OK, Task_Runing, Task_Finish, Task_All};//����״̬//
enum eTaskType { Task_Test = 0, Task_ReTest, Task_HelpReTest};//��������//
enum eTaskArmy { Army_Not = 0, Army_Yes, Army_All};   //��  ��  ȫ��//
enum eTaskDownUpLoad { Task_DownLoad = 0, Task_UpLoad}; // ��������, ����ϴ�//
enum eTaskModifyType { Task_ModifyBase, Task_ModifyAll};  //�޸�ģʽ  Task_ModifyBase: ֻ�޸Ļ�����Ϣ   Task_ModeAll: �޸�ȫ����Ϣ(���� ��� ģ�� ͼ��)

//�б���ʾ

enum eShowType{ Show_Product, Show_Mode, Show_Task, Show_OneMode, Show_OneTask, Show_Result};
//               ��Ʒ_�б�    ģ��_�б�,  ����_�б� ģ��_�Ի��� ����_�Ի���

//��ѯ//
enum eSearchPageNum{ Five_Result = 0, Ten_Result, Twenty_Result, All_Result};  //ÿ��ʾ�ĸ���  5��10��20��ȫ������//
enum eResultType { Result_Task = 0, Result_Atta};//�����ѯ  ������ݲ�ѯ//
enum eSearchModel { Task_DarkSearch = 0, Task_ExactSearch, Result_Search};//��ѯģʽ:  ��������ģ����ѯ  ��������ID�ľ�ȷ��ѯ  �������ۺ�ģ����ѯ//

enum eAddObject { Add_ProductNo = 0, Add_Series, Add_Mode, Add_Task};

//���ɲ�Ʒ����3�з�ʽ//  1.������Ϊ��λ  2.�Բ�Ʒ���Ϊ��λ    3.��ģ��Ϊ��λ
enum eCreateReport { CreateReport_Task, CreateReport_ProdCode, CreateReport_Mode};

//֤����//
enum eTestimonialPage { Testimonial_Page1, Testimonial_Page2, Testimonial_Page3, Testimonial_Page4,
					  Testimonial_Page5, Testimonial_Page6, Testimonial_Page7, Testimonial_Page8,
					  Testimonial_Page9, Testimonial_Page10, Testimonial_Page11, Testimonial_Page12 };

enum ePage4Type { Page4_Type1, Page4_Type2, Page4_Type3};
//����ģ���Tree�ڵ�����//


//����ģ��//
#define Group_Tree_Type1               1
#define Group_Tree_Type2               2

//��Ʒģ��//
#define PROD_TREE_TYPE_DEPART          5    
#define PROD_TREE_TYPE_PRODCODE        7
//ģ�����ģ��//
#define MODE_TREE_TYPE_DEPART          11
#define MODE_TREE_TYPE_MODETYPE        12
#define MODE_TREE_TYPE_PRODCODE        13
#define MODE_TREE_TYPE_MODE            14
//�������ģ��//
#define TASK_TREE_TYPE_DEPART          16
#define TASK_TREE_TYPE_TASKTYPE        17
#define TASK_TREE_TYPE_PRODCODE        18
#define TASK_TREE_TYPE_TASK            20

//������ݲ�ѯ����//
#define RESULT_TREE_TYPE_DEPART       26
#define RESULT_TREE_TYPE_TYPE         27
#define RESULT_TREE_TYPE_PRODUCT      28
#define RESULT_TREE_TYPE_SERIES       29

//֤����ģ��//
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
//ģ�����ʾ���Ĳ�������///

#define IDC_GRID  10011 //GridCtrl�ؼ���ID///

#define GRID_BK_COLOR			RGB(255,  255,  255)			//����ⲿ������ɫ
#define GRID_TEXT_COLOR			RGB(0,  0,    0  )				//��������е�Ԫ��������ɫ
#define GRID_TEXT_BK_COLOR		RGB(0xFF, 0xFF, 0xFF)			//��������е�Ԫ�񱳾���ɫ

#define MY_TABLE_HEAD_COLOR     RGB(226, 233, 241)              //����ڱ�ͷ��ɫ
#define MY_GRID_LINE_COLOR      RGB(128, 128, 128)				//�������ɫ

#define GRID_LINE_COLOR         RGB(0,	0,	0	) 



  
#define MODE_TREE_ROOT_TEXT "����ģ�����"           //ģ�����ĸ��ڵ�//
#define MODE_TREE_TYPE1_TEXT "ģ������1"             //ģ�����ĸ��ڵ�//
#define MODE_TREE_TYPE1_1_TEXT "ģ��С��1_1"         //ģ�����ĸ��ڵ�//
#define MODE_TREE_TYPE2_TEXT "ģ������2"             //ģ�����ĸ��ڵ�//
#define MODE_TREE_TYPE2_1_TEXT "ģ��С��1_1"         //ģ�����ĸ��ڵ�//


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


//�����ļ�������///
#define USRMNG_USRCFG_FILENAME "SysUsrMngCfg.ini"
#define Prode_Type_Cfg         "ProdeTypeCfg.ini"
#define ExclosureFile_Path     "ExclosureFile"            //�����洢Ŀ¼
#define Report_Mode_Path       "ReportMode"               //����ģ���ļ���//
#define Report_Temp_Path       "ReportTempPath"           //���ɱ���ʱ����Ŀ¼//
#define Report_FILE_EX         ".doc"
#define Mode_Formula_Path      "MulTaskCal"          //ģ�幫ʽ·��//
#define Formula_FILE_EX         ".xlsx"

///zt

#define TAB_VIEW_MES_INSTITUTE       _T("VIEW_CHK_INSTITUTE_TEST")

#define NOT_SERIES                   _T("")