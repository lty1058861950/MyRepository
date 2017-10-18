#pragma  once 
#include <vector>
#include "PubPadStruct.h"
using namespace std;

//ztadd for lty
//--------------------------------------------------------
#define DB_USER_LEN     20        //数据库_人名_最大长度
#define DB_NAME_LEN     100       //数据库_名称_最大长度
#define DB_BACK_LEN     200		  //数据库_备注_最大长度
#define DB_FILE_PATH    1024      //文件路径//

typedef struct _DbConfig
{
	char  szDBName[DB_NAME_LEN];//数据库名称//
	char  szUserName[DB_NAME_LEN];//用户名//
	char  szUserPwd[DB_NAME_LEN];//密码//
}DbConfig;



//--------------------------------------------------------
//字段定义规则： n开头表示整型, sz开头表示字符串,d开头表示时间；
//---------------------------------------------------------
//01.角色表结构
typedef struct _StHrRole{
	UINT    nOid;                        //01.角色OID
	char    szRoleName[DB_NAME_LEN];     //02.角色名称
	char    szRoleNo[DB_NAME_LEN];       //03.角色编码
}StHrRole;
//02.用户表结构
typedef struct _StHrUser
{
	UINT	nOid;							//01.用户OID
	char	szLoginName[DB_USER_LEN];		//02.登录名
	char	szUserName[DB_USER_LEN];		//03.姓名
	char    szUserPwd[DB_USER_LEN];			//04.登录密码
	UINT    nRoleOid;                       //05.角色OID
	char    szRoleName[DB_NAME_LEN];		//05_1.角色名称
	UINT    nGroupOid;						//06.所在部门OID
	char    szGroupName[DB_NAME_LEN];       //06_1.所在部门OID
	char    szUserSignfile[DB_NAME_LEN];	//07.签名文件
	UINT    nUserLogstate;					//08.状态 :1.在线 2.禁用   
	UINT	nUserType;						//09.用户类型: 1.内置用户 2.系统业务用户
	char    szCall[DB_NAME_LEN];			//10.办公电话
	char    szEmail[DB_NAME_LEN];			//11.邮箱
	char	szPhone[DB_NAME_LEN];			//12.手机
	int     nPadDevID;                      //13.PAD设备ID

	char     szPadUpTime[DB_USER_LEN];       //PAD上传时间//
}StHrUser;

//03.部门表结构
typedef struct _StHrGroup
{
	UINT	nOid;							//01.部门OID
	UINT    nPOid;                          //02.上级部门OID
	char	szGroupName[DB_NAME_LEN];		//03.部门名称
	char	szGroupNo[DB_NAME_LEN];		    //04.部门编号
	char    szGroupType[DB_USER_LEN];		//05.部门类型
	char    szDescription[DB_BACK_LEN];     //06.描述
	char    szCall[DB_NAME_LEN];			//07.电话
	char    szFaxs[DB_NAME_LEN];			//08.传真
	char	szAddress[DB_BACK_LEN];			//09.地址
	int     nInvalid;                       //10.失效标志 就是删除

	int       TreeItemType;                 //当前树节点的类型
	HTREEITEM hItem;                        //当前所选树节点的指针
}StHrGroup;


//04.交检部门
typedef struct _StHrUpDepart 
{
	UINT	nOid;							//01.部门OID
	UINT    nPOid;                          //02.上级部门OID
	char	szUpDepartName[DB_NAME_LEN];		//03.部门名称
	char	szUpDepartNo[DB_NAME_LEN];		    //04.部门编号
	char    szUpDepartType[DB_USER_LEN];		//05.部门类型
	char    szDescription[DB_BACK_LEN];     //06.描述
	char    szCall[DB_NAME_LEN];			//07.电话
	char    szFaxs[DB_NAME_LEN];			//08.传真
	char	szAddress[DB_BACK_LEN];			//09.地址
	int     nInvalid;                       //10.失效标志 就是删除

	int       TreeItemType;                 //当前树节点的类型
	HTREEITEM hItem;                        //当前所选树节点的指针
}StHrUpDepart;


typedef struct _StBasProduct{
	UINT	nOid;						      	//01.产品代号OID
	char	szProductNo[DB_NAME_LEN];	      	//02.产品代号
	char	szProductName[DB_NAME_LEN];	      	//03.产品名称
	//UINT    nSeriesType;		                //04.系列类型:0.无系列号,1.有系列号
	UINT    nPicNumType;                        //05.图号类型:0.无图号(普通产品),1.有图号(线缆)
	UINT	nGroupOid;							//06.所在部门OID
	char    szGroupName[DB_NAME_LEN];           //06_1部门名称
	char    szCreateTime[DB_NAME_LEN];			//07.创建时间
	char    szCreateUser[DB_NAME_LEN];			//08.创建人


	//以下是产品查询时另加的字段//
	char    szCreateBeginTime[DB_NAME_LEN];     //1.查询时 创建的开始时间;
	char    szCreateEndTime[DB_NAME_LEN];       //2.查询时 创建的结束时间; 
	int     bProductNormal;						//3.普通产品被选中
	int     bProductLine;                       //4.线缆产品被选中
     
	int     nPerPageNum;                        //3.查询时每页的个数
	int     nCurPage;                           //4.当前的显示页
	int     nResultNum;                         //5.结果数量
	
}StBasProduct;

/*
typedef struct _StBasSeries{
	UINT	nOid;						      	//01.产品系列OID
	char	szSeriesName[DB_NAME_LEN];	      	//02.产品系列名
	UINT	nProductOid;						//03.产品OID
	char	szProductNo[DB_NAME_LEN];	      	//04.产品代号
	char    szCreateTime[DB_NAME_LEN];			//05.创建时间
	char    szCreateUser[DB_NAME_LEN];			//06.创建人

	int       TreeItemType;                 //当前树节点的类型
	HTREEITEM hItem;                        //当前所选树节点的指针

}StBasSeries;
*/

typedef struct _StBasPicNum{
	UINT	nOid;						      	//01.产品图号OID
	char	szPicNumNo[DB_NAME_LEN];	      	//02.图号代号
	char	szPicNumName[DB_NAME_LEN];	      	//03.图号名称
	UINT	nProductOid;						//04.产品OID
	char	szProductNo[DB_NAME_LEN];	      	//4_1.产品代号
	char    szProductName[DB_NAME_LEN];         //4_2.产品名称
	char    szCreateTime[DB_NAME_LEN];			//06.创建时间
	char    szCreateUser[DB_NAME_LEN];			//07.创建人
	UINT	nGroupOid;

	int       TreeItemType;                 //当前树节点的类型
	HTREEITEM hItem;                        //当前所选树节点的指针

}StBasPicNum;


//模板信息
typedef struct  _StBasMode
{
	//模板数据信息
	//-------------------------------------------------------------
	UINT	nOid;						      	//01.模板OID
	char	szModeName[DB_NAME_LEN];	      	//02.模板名称
	char	szModeVersion[DB_NAME_LEN];	      	//03.模板版本
	UINT	nModeType;						    //04.模板类型:0.未启用, 1.产品通用,2.产品专用,3.线缆专用
	UINT	nModeRowVar;	      	            //05.模板行可变状态：0.不可变 1.行可变
	int	    nModeSize;	      	                //06.模板大小
	char    szModeTabName[DB_NAME_LEN];			//07.模板数据表表名
	UINT	nInitTabSrt;	      	            //08.是否建立数据表结构：0.未建立 1.已建立
	UINT	nGroupOid;						    //09.所在部门OID
	char    szGroupName[DB_NAME_LEN];                        //09_1.部门名称
	StBasProduct stProductInfo;                //10.适用产品OID 11.产品代号  产品信息

	char    szModel[DB_NAME_LEN];			    //12.适用型号
	char    szPhase[DB_NAME_LEN];			    //13.适用阶段
	char    szCreateTime[DB_NAME_LEN];			//14.模板创建时间
	char    szCreateUser[DB_NAME_LEN];			//15.模板创建人
	char    *pXmlFile;                          //16.模板的描述XML文件
	int     nFormula;                           //17.有无公式模板 0.没有， 1.有
	
	int       TreeItemType;                 //当前树节点的类型
	HTREEITEM hItem;                        //当前所选树节点的指针
	HTREEITEM phItem;                       //当前所选树父节点的指针
	CTreeCtrl *pModeTree;                   //树节点指针//

	void Release()
	{
		if(pXmlFile != NULL)
		{
			delete []pXmlFile;
			pXmlFile = NULL;
			nModeSize = 0;
		}
	}

	//模板查询条件
	//-------------------------------------------------------------
	//以下是查询时另加的字段//
	char  szCreateBeginTime[DB_USER_LEN];//1.创建开始时间//
	char  szCreateEndTime[DB_USER_LEN];  //2.创建结束时间//

	int   bModeCurrency;                 //3.通用模板 值大于等于1表示查询  0不查询 
	int   bModeDedicated;                //4.产品专用 同上
	int   bModeLineDed;                  //5.线缆专用 同上
	int   bModeNotUse;                   //6.未启用   同上

	int   bModeRowNoChange;              //7.行不可变 同上
	int   bModeRowChange;                //8.行可变   同上

	int   bInitedTabSrt;                 //9.已初始化表结构   同上
	int   bUnInitTabStr;                 //10.未初始化表结构  同上


	int     nPerPageNum;                 //11.查询时每页的个数
	int     nCurPage;                    //12.当前的显示页
	int     nResultNum;                  //13.结果数量
}StBasMode;

typedef struct  _StBasTaskSave{
	UINT nOid;                        //01.数据表OID
	UINT nGroupOid;                   //02.部门OID
	char szBaseTabName[DB_NAME_LEN];      //03.数据基础表名字
	char szAttaTabName[DB_NAME_LEN];      //04.数据附加表名字
	char szCreateTime[DB_USER_LEN];   //05.创建时间
	char szCreateUser[DB_USER_LEN];   //06.创建人
}StHrGroupSave;

typedef struct  _StBasModeSave{
	UINT nOid;                        //01.数据表OID
	UINT nModeOid;                    //02.模板ID
	char szTabName[DB_NAME_LEN];      //03.数据表名字
	char szCreateTime[DB_USER_LEN];   //04.创建时间
	char szCreateUser[DB_USER_LEN];   //05.创建人
}StBasModeSave;

typedef struct _StBasModeDesc{
	UINT nOid;                        //01.数据表OID
	UINT nModeOid;                    //02.模板ID
	UINT nModeSaveOid;                //03.模板存储记录ID
	char szFieldName[DB_USER_LEN];    //04.表字段
	int  nDateType;                   //05.字段类型
	char szDescxx[DB_NAME_LEN];       //06.字段描述
	char szCreateTime[DB_USER_LEN];   //07.创建时间
	char szCreateUser[DB_USER_LEN];   //08.创建人

}StBasModeDesc;
typedef struct _StBasTaskCode {
	UINT nOid;                        //01.任务编号OID
	UINT nTaskOid;                    //02.任务OID
	int  nCodeIndex;                  //03.任务内编号顺序从1开始
	int  nDianshiTest;                //04.是否典试
	char szCodeName[DB_NAME_LEN];     //05.编号名称
	UINT nGroupOid;
}StBasTaskCode;

typedef struct _StBasTaskMode{
	UINT nOid;                        //01.任务模板表OID
	UINT nTaskOid;                    //02.任务OID
	int  nModeIndex;                  //03.任务内模板顺序从1开始
	UINT nModeOid;					  //04.模板OID
	char szModeName[DB_NAME_LEN];     //05.模板名称
	int  nModeType;                   //06.模板类型:0.产品通用,1.产品专用,2.线缆专用,3.未启用
	int  nModeRowvar;                 //07.模板行可变状态：0.不可变 1.行可变
	int  nFormula;                    //08.有无公式模板 0.没有， 1.有
	char *pModeInfoFile;              //09.XML文件模板的基本信息, 任务下发时记录模板的状态
	int  nInfoSize;                   //09_1  基本信息的文件长度
	char *pModeXmlFile;               //10.XML文件模板配置信息, 任务下发时记录模板的状态
	int  nXmlSize;                    //10_1  XML配置文件的长度
	StBasMode pModeInfo;              //将文件转化为结构体 记录模板的状态//
	UINT nGroupOid;

	void  Release()
	{
		if(pModeInfoFile != NULL)
		{
			delete []pModeInfoFile;
		}
		if(pModeXmlFile != NULL)
		{
			delete []pModeXmlFile;
		}

		pModeInfo.Release();
	}
}StBasTaskMode;

typedef struct  _StBasTaskPicNum
{
	UINT nOid;                        //01.任务编号表OID
	UINT nTaskOid;                    //02.任务OID
	int  nPicNumIndex;                //03.任务内模板顺序从1开始
	UINT nPicNumOid;				  //04.图号Oid
	char szPicNumNo[DB_NAME_LEN];     //05.图号代号
	char szPicNumName[DB_NAME_LEN];   //06.图号名称
	UINT nGroupOid;
}StBasTaskPicNum;


//任务基础表//
typedef struct _StTstResultBase{
	UINT nOid;                               //01.任务详情表OID
	UINT nTaskOid;                           //02.任务Oid
	char szSendDate[DB_USER_LEN];            //03.下发时间
	char szTaskName[DB_NAME_LEN];            //04.任务名称
	char szImportDate[DB_USER_LEN];          //05.导入时间
	char szCheckUser[DB_USER_LEN];           //06.检查人
	UINT nProductOid;                        //07.产品OID
	char szProductNo[DB_NAME_LEN];           //08.产品代号
	
	UINT      nGroupOid;
	int       nResultType;
	int       TreeItemType;                 //当前树节点的类型
	HTREEITEM hItem;                        //当前所选树节点的指针
	CTreeCtrl *pResultTree;
}StTstResultBase;
//任务表详情//
typedef struct _StTstResultAtta{

	UINT	nOid;						      	//01.任务详情表OID
	UINT    nTaskOid;                           //02.任务Oid
	UINT    nModeOid;                           //03.模板Oid
	UINT    nProductOid;                        //04.产品代号Oid
	UINT    nSeriesOid;                         //05.产品系列Oid

	char    szProductName[DB_NAME_LEN];			//06.产品名称
	char    szProductNo[DB_NAME_LEN];			//07.产品代号
	char    szSeriesName[DB_NAME_LEN];          //08.系列名称
	char    szModel[DB_NAME_LEN];               //09.产品型号
	char    szPhase[DB_NAME_LEN];               //10.产品阶段
	char    szProductCode[DB_NAME_LEN];         //11.编号名称
	char    szModeName[DB_NAME_LEN];            //12.模板名称
	int     nModeType;                          //13.模板类型
	int     nModeRowVar;                        //14.模板行可变属性
	int     nDianshiTest;                       //15.是否典试
	int     nPicNumCount;                       //16.图号数量
	int     nPercent;                           //17.完成进度(百分比)
	int     bFinished;                          //18.完成状态
	char    szFinishedTime[DB_NAME_LEN];		//19.完成时间
	char    szCheckUser[DB_USER_LEN];           //20.检查人
	char    szSendDate[DB_USER_LEN];            //21.任务下发时间
	char    szImportDate[DB_USER_LEN];          //22.导入时间
	UINT    nBaseOid;                           //23.任务基础表的OID
	char    szTaskName[DB_NAME_LEN];            //24.任务名称

	int     nFormula;                           //25.有无公式模板 0.没有， 1.有
	char    szBatch[DB_NAME_LEN];               //26.产品批次号

	UINT      nGroupOid;
	int       TreeItemType;                 //当前树节点的类型
	HTREEITEM hItem;                        //当前所选树节点的指针
	CTreeCtrl *pResultTree;
}StTstResultAtta;


typedef struct _StBasTaskBaseInfo{
	UINT	nOid;						      	//01.任务OID
	char	szTaskName[DB_NAME_LEN];	      	//02.任务名称
	char	szProjectNo[DB_NAME_LEN];	      	//03.检验单号
	UINT	nTaskStatus;						//04.任务状态
	UINT	nTaskType;	      	                //05.任务类型
	char    szModel[DB_NAME_LEN];			    //06.型号
	char    szPhase[DB_NAME_LEN];			    //07.阶段
	//UINT	nProductOid;	      	            //08.产品OID
	//char    szProductName[DB_NAME_LEN];       //09.产品名称
	//char    szProductNo[DB_NAME_LEN];			//10.产品代号
	UINT	nSeriesOid;						    //11.产品系列号OID
	char    szSeriesName[DB_NAME_LEN];			//12.产品系列号名称
	char    szProductCode[DB_NAME_LEN];			//13.产品编号
	int  	nCodeNumber;						//14.数量
	char    szBatch[DB_NAME_LEN];		       	//15.批次号
	

	UINT    nGroupOid;		                	//16.任务所属部门
	char    szGroupName[DB_NAME_LEN];           //16_1 任务所属部门名称
	char    szUpUser[DB_USER_LEN];			    //17.交检人
	char    szUpDate[DB_USER_LEN];		    	//18.交检日期
	char    szSendDate[DB_USER_LEN];			//19.下发日期
	char    szCheckLeader[DB_USER_LEN];			//20.检验组长
	char    szCheckUser[DB_USER_LEN];			//21.检验员姓名
	char    szTechUser[DB_USER_LEN];			//22.工艺员 
	int  	nArmyTest;						    //23.军检
	int  	nDianShiNum;						//24.典试数量
	char    szAccording1[DB_BACK_LEN];			//25.验收依据1
	char    szAccording2[DB_BACK_LEN];			//26.验收依据2
	char    szAccording3[DB_BACK_LEN];			//27.验收依据3
	char    szAccording4[DB_BACK_LEN];			//28.验收依据4
	char    szAccording5[DB_BACK_LEN];			//29.验收依据5
	char    szTaskRemark[DB_BACK_LEN];			//30.备注
	char    szPlanBegTime[DB_USER_LEN];			//31.计划开始时间
	char    szPlanEndTime[DB_USER_LEN];			//32.计划结束时间
	char    szRealBegTime[DB_USER_LEN];			//33.实际开始时间
	char    szRealEndTime[DB_USER_LEN];			//34.实际结束时间

	char    szDownLoadDate[DB_USER_LEN];                   //35.下载时间
	char    szFinishDate[DB_USER_LEN];                     //36.任务完成时间
	char    szImportDate[DB_USER_LEN];                     //37.数据导入时间
	char    szCreateDate[DB_USER_LEN];                     //37.任务创建时间
	char    szCreateUser[DB_USER_LEN];                     //38.任务创建人

	int       TreeItemType;                 //当前树节点的类型
	HTREEITEM hItem;                        //当前所选树节点的指针
	CTreeCtrl *pTaskTree;

	int     nModifyType;                   //修改模式  0,只修改基本信息  1.修改所有信息(包括编号  模板  图号等)

	//辅助CList控件修改字段//

	int   nListIndex;                      //当前选中的List行数//

	//以下是查询时 另加的字段//
	char  szCreateBeginTime[DB_USER_LEN];//1.创建开始时间//
	char  szCreateEndTime[DB_USER_LEN];  //2.创建结束时间//
	char  szSendBeginTime[DB_USER_LEN];//3.派工开始时间//
	char  szSendEndTime[DB_USER_LEN];  //4.派工结束时间//
	char  szDownLoadBeginTime[DB_USER_LEN];//5.下载开始时间//
	char  szDownLoadEndTime[DB_USER_LEN];  //6.下载结束时间//
	char  szFinishBeginTime[DB_USER_LEN];//7.完成开始时间//
	char  szFinishEndTime[DB_USER_LEN];  //8.完成结束时间//


	int     bTaskInit;                  //3.新任务
	int     bTaskOk;                    //4.已派工
	int     bTaskRuning;                //5.执行中
	int     bTaskFinish;                //6.已完成
	int     bTaskStop;                  //7.已中止


	int     bTaskTest;                  //8.任务是类型  检验
	int     bTaskReTest;                //9.复验
	int     bTaskHelpReTest;            //10.外协复验

	int     nPerPageNum;                 //11.查询时每页的个数
	int     nCurPage;                    //12.当前的显示页
	int     nResultNum;                  //13.结果数量

	//2017-03-07 Liuty add  为导入数据时加的字段//

	int     nIndex;                      //1.序号
	char    szFoldName[DB_FILE_PATH];    //2.文件目录
	char    szFileName[DB_BACK_LEN];     //3.文件名

	//2017-04-05 Liuty add 为基于任务的结果查询时另加的字段
	int     nResultType;                 //1.查询类型
}StBasTaskBaseInfo;

typedef struct _StBasTask{
	StBasTaskBaseInfo stTaskBaseInfo;            //任务的基础信息//
	StBasProduct  stProductInfo;                 //产品的详细信息//
	StHrGroup     stHrGroup;                     //所属部门的详细信息
	StHrUpDepart  stHrUpDepart;                  //交检部门的详细信息

	vector<StBasTaskCode *> pArryTaskCode;
	vector<StBasTaskMode *> pArryTaskMode;
	vector<StBasTaskPicNum *> pArryTaskPicNum;
	vector<StTstResultAtta *> pArryTastResultBase;

	void   ReleaseBase()
	{
		memset(&stTaskBaseInfo,0,sizeof(StBasTaskBaseInfo));
		memset(&stProductInfo,0,sizeof(StBasProduct));
		memset(&stHrGroup,0,sizeof(StHrGroup));
		memset(&stHrUpDepart,0,sizeof(StHrUpDepart));

	}
	void   ReleaseCode()
	{
		int i, nCount = 0;
		nCount = pArryTaskCode.size();
		if(nCount>=1)
		{
			//释放内存//
			for (i = 0; i<nCount; i++)
			{
				delete pArryTaskCode.at(i);
			}
			pArryTaskCode.clear();
			
		}
	}
	void   ReleaseMode()
	{
		int i, nCount = 0;
		nCount = pArryTaskMode.size();
		if(nCount>=1)
		{
			//释放内存//
			for (i = 0; i<nCount; i++)
			{
				pArryTaskMode.at(i)->Release();
				delete pArryTaskMode.at(i);
			}
			pArryTaskMode.clear();
			
		}
		
	}
	void   ReleasePicNum()
	{
		int i, nCount = 0;
		nCount = pArryTaskPicNum.size();
		if(nCount>=1)
		{
			//释放内存//
			for (i = 0; i<nCount; i++)
			{
				delete pArryTaskPicNum.at(i);
			}
			pArryTaskPicNum.clear();
			
		}
	}
	void   ReleaseTaskResult()
	{
		int i, nCount = 0;
		nCount = pArryTastResultBase.size();
		if(nCount>=1)
		{
			//释放内存//
			for (i = 0; i<nCount; i++)
			{
				delete pArryTastResultBase.at(i);
			}
			pArryTastResultBase.clear();
			
		}
	}
	void   Release()
	{
		ReleaseBase();
		ReleaseCode();
		ReleaseMode();
		ReleasePicNum();
		ReleaseTaskResult();
	}
}StBasTask;


//2017-04-05 Liuty Add 任务基础结构新版
typedef struct  _StTstResultBaseNew{
	UINT              nOid;                         //1.基础数据表的OID
	StBasTask         stTaskInfo;                   //2.任务的全部信息

	void  Release()
	{
		nOid = 0;
		stTaskInfo.Release();
	}
}StTstResultBaseNew;

typedef struct _StSearchSetInfo{
	int	nPerPageNum;						      	//01.每一页的结果数量
	int nAimPage;                                  //02.转到那一页
	int nCurPage;                                  //03.当前页
	int nMaxPage;                                  //04.最大页数
}StSearchSetInfo;



typedef struct _StBasAttachment{
	char Exclosure_OldName[DB_BACK_LEN];//附件原始名称//
	char Exclosure_Name[DB_BACK_LEN];//附件名称//
	int  nModeCellOrder;//数据标号，在模板的第几个单元格//
	char ModeDesc[DB_NAME_LEN];//所属模板的标识//
	int  nDataType;//数据类型//
	char BUILDUSR[DB_USER_LEN];//采集人//
	char BUILDTime[DB_USER_LEN];//采集时间//
}StBasAttachment;

//测试数据结构//
typedef struct _TestDataStr{
	int  Index;//数据的序号//
	int  iDataType;        //数据类型//
	char Name[XLS_MAX_LEN];//数据库对应的字段名///
	char Desc[XLS_MAX_LEN];//字段数据的描述//
	char Data[XLS_MAX_LEN];//数据//
	char CheckUsr[DB_USER_LEN];//检查人//
	char CheckTime[DB_USER_LEN];//检查时间//
}TestDataStr;


typedef struct _StBasTestimonialPage1{
	char szTitle[DB_NAME_LEN];                //1.标题
	int  nPageNum;                            //2.共几页
	char szProductNo[DB_NAME_LEN];            //3.产品代号
	char szProductName[DB_NAME_LEN];          //4.产品名称
	char szProductCode[DB_NAME_LEN];          //5.出厂编号  -》 产品编号
	char szPhase[DB_NAME_LEN];                //6.研制阶段  -》 阶段
	char szProductionUnit[DB_NAME_LEN];       //7.生产单位
	char szLeaveFactoryDate[DB_NAME_LEN];     //8.出厂日期
}StBasTestimonialPage1;
typedef struct _StBasTestimonialPage2{
	char szTitle[DB_NAME_LEN];                //1.标题
	int  nCount;                              //2.有几项规则
	char szRules[DB_USER_LEN][DB_BACK_LEN*2];   //3.规则内容 1、2、3、。。。
}StBasTestimonialPage2;

typedef struct _StBasTestimonialPage3{
	char szTitle[DB_NAME_LEN];                //1.标题  目录
	int  nCount;                              //2.有几项目录
	char szRules[DB_USER_LEN][DB_NAME_LEN];   //3.目录内容 1、2、3、。。。
	int  nPageNums[DB_USER_LEN];              //4.每一项的页码
}StBasTestimonialPage3;

typedef struct _StBasTestimonialPage4{
	char szTitle[DB_NAME_LEN];                //1.标题  产品合格结论
	int  nShowType;                           //2.类型
}StBasTestimonialPage4;


typedef struct _StBasPage5ProductSort
{
	char szProductName[DB_NAME_LEN];
	char szProductNo[DB_NAME_LEN];    
	char szProductCode[DB_NAME_LEN];
	char szUnitName[DB_NAME_LEN];
	char szRemark[DB_BACK_LEN];
}StBasPage5ProductSort;
typedef struct _StBasTestimonialPage5{
	char szTitle[DB_NAME_LEN];                //1.标题  产品合格结论
	vector<StBasPage5ProductSort>  stProdSortArray;//2.产品配套表的产品
	void Relese()
	{
		memset(szTitle, 0, sizeof(szTitle));
		stProdSortArray.clear();
	}
}StBasTestimonialPage5;

typedef struct _StTabMergeCell
{
	int	iBegRow;	//起始行号
	int iBegCol;	//起始列号
	int iEndRow;	//终止行号
	int iEndCol;	//终止列号

	int iRowNum;	//合并后行数
	int iColNum;	//合并后列数
}StTabMergeCell; 

typedef struct _StBasTstUnit{
	int      nCount;
	char     szUnits[DB_USER_LEN][DB_NAME_LEN];
}StBasTstUnit;
typedef struct _StBasTstCheckDate{
	int      nCount;
	char     szCheckDates[DB_USER_LEN][DB_NAME_LEN];
}StBasTstCheckDate;

typedef struct _StBasPage6DeviceCarte
{
	char szDeviceName[DB_NAME_LEN];                         //1.技术条件规定用
	char szStdParameter[DB_NAME_LEN];                       //2.验收时用
	char szTstParameter[DB_NAME_LEN];                       //3.历次测试用  1
	char szHisParameter1[DB_NAME_LEN];                      //4.历次测试用  2
	char szHisParameter2[DB_NAME_LEN];                      //5.历次测试用  3
	char szHisParameter3[DB_NAME_LEN];                      //6.历次测试用  4
	char szHisParameter4[DB_NAME_LEN];                      //7.历次测试用  5
}StBasPage6DeviceCarte;
typedef struct _StBasTestimonialPage6{
	char                  szTitle[DB_NAME_LEN];                //1.标题  测试产品用仪器（设备）清单
	vector<StBasPage6DeviceCarte>  stDeviceCarteArray;//2.产品配套表的产品

	StBasTstUnit          stTstUnits;
	StBasTstCheckDate     stTstCheckDates;
	void Relese()
	{
		memset(szTitle, 0, sizeof(szTitle));
		stDeviceCarteArray.clear();

		memset(&stTstUnits, 0, sizeof(StBasTstUnit));
		memset(&stTstCheckDates, 0, sizeof(StBasTstCheckDate));
	}
}StBasTestimonialPage6;

typedef struct _StBasPage7TestEnvironment
{
	char   szProjectName[DB_NAME_LEN];
	char   szUnit[DB_NAME_LEN];
	char   szStdValue[DB_NAME_LEN];
	char   szTstValue[DB_NAME_LEN];
	char   szHisValue1[DB_NAME_LEN];
	char   szHisValue2[DB_NAME_LEN];
	char   szHisValue3[DB_NAME_LEN];
	char   szHisValue4[DB_NAME_LEN];
}StBasPage7TestEnvironment;
typedef struct _StBasTestimonialPage7{
	char szTitle[DB_NAME_LEN];                //1.标题  检查测试时环境条件记录
	vector<StBasPage7TestEnvironment>  stTestEnvironment;//2.测试环境

	StBasTstUnit          stTstUnits;
	StBasTstCheckDate     stTstCheckDates;
	void Relese()
	{
		memset(szTitle, 0, sizeof(szTitle));
		stTestEnvironment.clear();

		memset(&stTstUnits, 0, sizeof(StBasTstUnit));
		memset(&stTstCheckDates, 0, sizeof(StBasTstCheckDate));
	}
}StBasTestimonialPage7;


typedef struct _StBasTestimonialPage8{
	char szTitle[DB_NAME_LEN];                //1.标题  产品技术性能测试记录
	vector<StTstResultAtta>  stTstResultAtta; //2.结果数据附件

	void Relese()
	{
		memset(szTitle, 0, sizeof(szTitle));
		stTstResultAtta.clear();
	}
	
}StBasTestimonialPage8;


typedef struct  _StBasPage9ConnectTeleTime
{
	char szBegEndTime[DB_NAME_LEN];                  //1.起止时间
	char szTemp[DB_USER_LEN];                        //2.温度
	char szHumidity[DB_USER_LEN];                    //3.湿度
	char szWorkStatus[DB_NAME_LEN];                  //4.工作情况
	char szThisConnTele[DB_USER_LEN];                //5.本次通电时间
	char szHisConnTele[DB_USER_LEN];                 //6.累计通电时间
	char szOperUser[DB_USER_LEN];                    //7.操作者
	char szCheckUser[DB_USER_LEN];                   //8.检查者
}StBasPage9ConnectTeleTime;
typedef struct _StBasTestimonialPage9{
	char szTitle[DB_NAME_LEN];                //1.标题  通电时间记录
	vector<StBasPage9ConnectTeleTime>  stTstConnectTele; //2.通电数据

	void Relese()
	{
		memset(szTitle, 0, sizeof(szTitle));
		stTstConnectTele.clear();
	}

}StBasTestimonialPage9;


typedef struct  _StBasPage10TaskOver
{
	char szOverTime[DB_USER_LEN];                    //1.起止时间
	char szOverAccording[DB_USER_LEN];               //2.交接依据
	char szExplain[DB_NAME_LEN];                     //3.交接说明
	char szOutUnit[DB_USER_LEN];                     //4.交出单位
	char szOutUser[DB_USER_LEN];                     //5.交出承办人
	char szInUnit[DB_USER_LEN];                      //6.接收单位
	char szInUser[DB_USER_LEN];                      //7.接收承办人
}StBasPage10TaskOver;

typedef struct _StBasTestimonialPage10{
	char szTitle[DB_NAME_LEN];                       //1.标题  交接记录
	vector<StBasPage10TaskOver>  stTstTaskOver;      //2.交接数据
	void Relese()
	{
		memset(szTitle, 0, sizeof(szTitle));
		stTstTaskOver.clear();
	}

}StBasTestimonialPage10;
typedef struct _StBasPage11SpecialRecord{
	char szRecordText[DB_BACK_LEN];               //1.内容
	char szUnit[DB_USER_LEN];                     //2.单位
	char szUser[DB_USER_LEN];                     //3.姓名
	char szDate[DB_USER_LEN];                     //4.日期

}StBasPage11SpecialRecord;
typedef struct _StBasTestimonialPage11{
	char szTitle[DB_NAME_LEN];                       //1.标题  特殊记载
	vector<StBasPage11SpecialRecord>  stTstSpecialRecord;      //2.记载数据
	void Relese()
	{
		memset(szTitle, 0, sizeof(szTitle));
		stTstSpecialRecord.clear();
	}

}StBasTestimonialPage11;
//证明书结构//
typedef struct _StBasTestimonial{
	StBasTestimonialPage1   stPage1;
	StBasTestimonialPage2   stPage2;
	StBasTestimonialPage3   stPage3;
	StBasTestimonialPage4   stPage4;
	StBasTestimonialPage5   stPage5;
	StBasTestimonialPage6   stPage6;
	StBasTestimonialPage7   stPage7;
	StBasTestimonialPage8   stPage8;
	StBasTestimonialPage9   stPage9;
	StBasTestimonialPage10  stPage10;
	StBasTestimonialPage11  stPage11;
	void  Relese()
	{
		memset(&stPage1, 0, sizeof(StBasTestimonialPage1));
		memset(&stPage2, 0, sizeof(StBasTestimonialPage2));
		memset(&stPage3, 0, sizeof(StBasTestimonialPage3));
		memset(&stPage4, 0, sizeof(StBasTestimonialPage4));
		stPage5.Relese();
		stPage6.Relese();
		stPage7.Relese();
		stPage8.Relese();
		stPage9.Relese();
		stPage10.Relese();
		stPage11.Relese();

	}
}StBasTestimonial;