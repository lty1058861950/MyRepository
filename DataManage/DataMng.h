#pragma once
#include "OracleOci/OracleOciDbMng.h"

class CDataMng
{
public:
	CDataMng(void);
	~CDataMng(void);
public:
	BOOL nConnectStatus;

	//-----数据库操作函数接口------	
	BOOL DeleteTableData( char *pTableName ,BOOL DelTab = FALSE);					//FALE 默认保留表删除表数据//
	BOOL GetTableRowCount(char *pTableName, int &nCnt);								//获取行个数
	CString GetFieldValue(char *szFile,COciSQLCursor	*OciSql);					//根据数据集获取某个字段

	BOOL QueryDataInfo(char *pTableName, CStringArray& ReturnVarArray,int nCol);	//读取表中的全部数据//
	BOOL GetDataInfo(char *szSQL, CStringArray& ReturnVarArray,int nCol);			//读取表中部分数据//
	//给出(推荐) 可用的 最小的ID号///
	//CString  GetTabLeastID(CString nTabName,CString IDName);						//DEL_获取字符串

	//SEQUENCE操作相关
	//----------------------------------------------------------------
	int  GetTabLeastOid(char *szTableName);											//获取最小可用ID			
	BOOL GetSeqId(char *szTableName,UINT &nCurID);									//获取SEQUENCE的ID

	//BOOL GetTableInfo(char *szSQL, CStringArray& ReturnVarArray,int nCol);					//
	//BOOL GetTableInfo(char *pTableName, CStringArray& ReturnVarArray,int *nCol,int len);
	//BOOL GetProdNameTableInfo(char *szSQL, CStringArray& ReturnVarArray,int nCol);

	//BOOL InsertDataInfo(char *szSQL);					//
	BOOL UpdateDataInfo(char *szSQL);					//插入数据、更新、删除
	//BOOL DeleteDataInfo(char *szSQL);


	//更新和获取 BOLB类型的内容//
	//----------------------------------------------------------------
	BOOL UpdateOracleBlob(char *szSQL,char *FieldName,char *strFileInfo,int nlen);		//更新BLOB数据内容，插入BLOB数据
	BOOL GetTableBolbInfo(char *szSQL,char *FieldName,char *strFileInfo,int &nlen);		//获取BLOB数据

	
	//一、用户管理
	//=================================================================================================
	
	//角色模块的函数//
	int  GetRoleCount();													//获取角色个数    [未启用]
	BOOL InitRoleTab();														//初始化角色信息  [未启用]
	BOOL GetAllRole(vector<StHrRole *> *pAllRole);							//获取所用角色信息[未启用]

	//用户管理模块的数据操作//
	BOOL InitUserTab();														//如果为空表，初始化admin和user
	int  GetCountUserLogName(char *LogName);								//通过登录名查找用户是否存在， 返回：存在1,不存在0
	int  GetUserDataFromToDb(COciSQLCursor	*OciSql, StHrUser *pUserInfo);	//通过数据集，获取用户信息
	BOOL GetOneUsrInfoLogName(char *LogName,StHrUser *pStr);				//获取一个用户信息，通过_登录名_查找
	BOOL GetOneUsrInfoOid(UINT nUserOid,StHrUser *pStr);					//获取一个用户信息，通过_用户OID_查找

	int  GetCountUser(char *pTableName = _T(""));							//获取所有用户个数
	BOOL GetAllUserToPad(vector<StHrUser *> *pUserArry);					//获取所有用户信息，用于PAD用户表

	BOOL IsUserLogNameExists(char *LogName);								//判断此用户_登录名_是否存在
	BOOL IsUserUserNameExists(char *UserName);								//判断此用户_中文名_是否存在
	BOOL AddNewUser(StHrUser *pStr);										//添加用户
	BOOL EditOldUser(StHrUser *pStr);										//更改用户信息
	BOOL DelUser(char *szLoginName);										//删除用户

	//修改用户密码//
	BOOL ReSetUsrPwd(char *NetPwd,char *UsrLogName);						//重置用户密码



	//二、交检部门
	//=================================================================================================
	//2017-03-01 liuty:add 交检部门模块函数
	int  GetUpDepartCount(char *pTableName);											//获取交检部门个数
	int  GetUpDepartDataFromToDb(COciSQLCursor	*OciSql, StHrUpDepart *pStUpDepart);	//通过数据集，获取交检部门信息
	BOOL GetAllUpDepart(vector<StHrUpDepart > *pStHrUpDepartArry);						//获取所有交检部门信息
	BOOL GetOneUpDepartInfoOID(UINT OID,StHrUpDepart *pStUpDepart);						//获取一个交检部门信息，通过_OID_获取
	BOOL GetOneUpDepartInfoDepartName(char *szDepartName,StHrUpDepart *pStUpDepart);	//获取一个交检部门信息，通过_交检部门名称_获取
	BOOL IsUpDepartExists(CString DepartName);											//判断部门是否存在, 部门名称不能重复
	BOOL AddNewUpDepart(StHrUpDepart *pStUpDepart);										//添加交检部门
	BOOL EditOldUpDepart(StHrUpDepart *pStUpDepart);									//更改交检部门
	BOOL DelUpDepart(UINT nOid);														//删除交检部门，通过OID


	//三、组管理
	//=================================================================================================
	BOOL InitGroupTab();																//如果为空表，初始化“检验处”组						
	int  GetGroupCount(char *pTableName = _T(""));										//获取所有组的个数
	BOOL GetAllValidGroup(vector<StHrGroup *> *pStHrGroupArry);							//获取所有可用组
	BOOL GetAllInvalidGroup(vector<StHrGroup *> *pStHrGroupArry);						//获取所有不可用组
	int  GetOneGroupInfoOID(UINT OID,StHrGroup *pStr);									//获取一个组信息，通过_OID_获取
	int  GetOneGroupInfoName(char *szGroupName,StHrGroup *pStr);						//获取一个组信息，通过_组名称_获取
	BOOL IsDepartExists(CString DepartName, UINT pOid = 0);								//判断组是否存在，组名称不能重复  

	BOOL AddNewGroup(StHrGroup *pStr);													//添加组
	BOOL EditOldGroup(StHrGroup *pStr);													//更改组
	BOOL DelGroup(UINT nOid);															//设置组不可用
	BOOL RecoveryGroup(UINT nGroupOid);													//设置组可用

	//任务基础表模块函数// 为每一个组创建一个 任务基础表和一个结果附件表
	BOOL IsHrGroupSaveExists(UINT nGroupOid);											//任务基础表和结果附件表是否存在: "HR_GROUP_SAVE"
	BOOL AddNewHrGroupSave(StHrGroupSave *pHrGroupSave);								//添加一个组任务的描述


	//四、产品管理
	//=================================================================================================
	//产品模块的函数///
	int  GetProdCount(char *pTableName=_T(""));											//获取产品个数, [条件函数内定义]
	int  GetProdCountGroup(UINT nGroupOid);												//获取当前组的所有产品个数
	int  GetProdDataFromToDb(COciSQLCursor	*OciSql, StBasProduct *pProductInfo);		//通过数据集，获取产品信息

	//初始化任务树
	//获取产品信息,根据组ID
	BOOL GetGroupProductInfo(UINT nGroupOid, vector<StBasProduct> *pArrayProduct);		//获取产品当前组产品信息

	//通过模糊查询的方式 查询本部门的所有产品信息 
	BOOL GetGroupProductData(UINT GroupOid, StBasProduct *pProductSearch, vector<StBasProduct> *pArrayProduct);
	
	//获取产品信息，根据组号,图号类型[固定0]  nPicNumType：图号类型  0.无图号类型, 1.有图号类型
	BOOL GetGroupPicNumProdInfo(UINT GroupOid,int nPicNumType,vector<StBasProduct > *pArrayProduct);  //用于显示无图号类型的产品树

	//获取一个产品信息，根据_产品OID_获取
	BOOL GetProdDataOid(UINT ProdOid,StBasProduct *pStr);//通过Oid获得产品的信息

	//通过一个产品信息，根据_部门Oid和产品代号_获得
	BOOL GetProdDataGroupOidProdNo(UINT GroupOid,char *szProductNo,StBasProduct *pStr);


	//1.产品代号模块函数
	BOOL  AddNewProd(StBasProduct *pStr);												//添加产品信息
	BOOL  IsProdExists(UINT GroupOid,char *szProductNo);								//判断当前组此产品是否存在,根据_产品代号_查询
	BOOL  EditOldProd(StBasProduct *pStr);												//更改产品信息
	BOOL  DelOldProd(UINT nOid);														//删除产品信息

	//清除所有产品、所有任务配置
	BOOL  DelAllProd(UINT nGroupOid);                                                    //删除全部产品
	BOOL  DelAllProd_PicNum(UINT nGroupOid);											 //删除全部图号信息


	//2.产品图号模块函数
	int  GetPicNumCount(char *pTableName);												//获取图号个数，[条件函数内定义]
	int  GetProdPicNumDataFromToDb(COciSQLCursor	*OciSql, StBasPicNum *pBasPicNum);	//通过数据集，获取图号信息
	BOOL GetProdPicNumData(UINT ProductOid,char *szPicNumNo,StBasPicNum *pBasPicNum);	//获取图号数据，根据_图号代号_获取
	BOOL GetPicNumDataFromOid(UINT PicNumOid,StBasPicNum *pBasPicNum);					//获取图号数据，根据_图号OID_获取
	BOOL GetProductPicNumInfo(UINT ProdOid,vector<StBasPicNum> *pPicNumArray);			//获取产品据有图号信息

	BOOL AddNewPicNum(StBasPicNum *pStr);												//添加图号信息									
	BOOL IsPicNumExists(UINT ProductOid,char *szPicNumNo);								//判断此产品_图号代号_是否存在//
	BOOL EditOldPicNum(StBasPicNum *pStr);												//更改图号信息
	BOOL DelOldPicNum(UINT nPicNumOid);													//删除图号信息



	//五、模板管理
	//=================================================================================================
	//模板模块的函数///
	int  GetModeCount(char *pTableName=_T(""));											//获取模板个数

	int  GetModeCountGroup(UINT GroupOid);												//获取模板个数, 根据所属组 
	int  GetModeCountGroupType(UINT GroupOid,int nModeType);							//获取模板个数, 根据_组OID和模板类型_获取
	int  GetModeDataFromToDb(COciSQLCursor	*OciSql, StBasMode *pModeInfo);


	//模糊检索
	//-------------------------------------------------------------------
	//获取模板信息, 条件存于:pModeSearchInfo
	BOOL GetGroupModeInfo(UINT GroupOid,StBasMode *pModeSearchInfo,vector<StBasMode> *pModeArry);//部门下模糊检索//

	//获取模板信息, 根据组号, 模板类型
	BOOL GetGroupModeTypeData(UINT GroupOid,int nModeType,vector<StBasMode> *pModeArry);	//部门下 某类型 精确检索//

	//获取产品下模板信息, 通过_产品OID_获取
	BOOL GetProdModeData(UINT nProductOid,vector<StBasMode > *pModeArry);					//产品下精确检索//

	//获取一个模板信息, 通过_模板OID_获取
	BOOL GetModeDataOid(UINT ModeOid,StBasMode *pStr);//通过Oid获得模板的信息


	BOOL AddNewMode(StBasMode *pStr);													//添加模板
	BOOL IsGroupProdModeExists(UINT GroupOid,UINT ProductOid,char *szModeName);			//判断当前组此产品下这个模板是否存在//
	BOOL EditOldMode(StBasMode *pStr);													//更改模板
	BOOL DelOldMode(UINT ModeOid);														//删除模板

	BOOL UpdateModeXmlFile(UINT nModeOid, char *strFileInfo,int nLen);					//更新模板XML字段
	BOOL GetModeXmlFile(UINT nModeOid, char **strFileInfo,int &nLen);					//获取模板XML字段


	//模板结构表模块函数
	//-------------------------------------------------------------------
	BOOL IsModeStrTabExists(UINT nModeOid);												//检查模板结构表是否存在//
	BOOL AddNewModeSave(StBasModeSave *pStr);											//添加模板结构
	BOOL GetAllModeSave(vector<StBasModeSave *> *pModeSaveArray);						//获取所有模板结构
	BOOL DelOldModeSave(UINT nModeOid);													//删除模板结构创建的记录信息
	int  GetDataCount(char *szTabName);													//获取数据的个数

	//模板表字段的描述//
	BOOL AddNewModeDesc(StBasModeDesc *pModeDesc);										//添加模板字段描述
	BOOL DelModeAllField(UINT nModeOid);												//删除模板字段描述
	

	//六、任务管理
	//=================================================================================================
	int  GetTaskCount(char *pTableName);												//获取任务个数
	int  GetTaskCountGroup(UINT nGroupOid);												//获取本部门的所有任务个数
	int  GetTaskCountGroupStatus(UINT nGroupOid, int nTaskStatus);						//获取当前组的某个状态的任务个数
	int  GetTaskDataFromToDb(COciSQLCursor	*OciSql, StBasTask *pTaskInfo);				//通过数据集，获取任务信息

	//获取任务信息
	//-------------------------------------------------------------------
	//获取产品下任务信息，根据_产品OID_获取
	BOOL GetProductTaskInfo(UINT ProdOid,vector<StBasTask *> *pArrayTask);						

	//获取产品下指定任务状态的任务信息, 根据_产品OID_任务状态_获取
	BOOL GetProductTaskStatusInfo(UINT ProdOid,int nTaskStatus,vector<StBasTask *> *pArrayTask);

	//判断当前产品下有此状态的任务//
	BOOL IsStatusProdTaskExists(int nTaskStatus,UINT ProductOid);

	//模糊查询
	//-------------------------------------------------------------------
	//nGroupOid是所属部门 与交检部门无关
	BOOL GetGroupTaskInfo(UINT nGroupOid, StBasTask *pTaskSearchInfo,vector<StBasTask> *pArrayTask);

	//通过Oid获得任务的信息
	BOOL GetTaskDataOid(UINT nTaskOid,StBasTask *pStTaskInfo);
	
	//通过_产品OID_任务名称_获取任务信息
	BOOL GetTaskDataProdOidTaskName(UINT nProdOid,char *szTaskName, StBasTask *pStTaskInfo);


	BOOL AddNewTask(StBasTask *pTaskInfo);											//添加任务
	BOOL IsProductTaskExists(UINT ProductOid,char *szTaskName);						//判断本产品下这个任务是否存在//
	BOOL EditOldTask(StBasTask *pTaskInfo);											//更改任务
	BOOL DelOldTask(UINT nTaskOid);													//删除任务

	//删除全部任务
	BOOL DelAllTask(UINT nGroupOid);												//删除所有任务
	BOOL DelAllTask_AllCode(UINT nGroupOid);										//删除任务所有编号
	BOOL DelAllTask_ALLMode(UINT nGroupOid);										//删除任务所有模板
	BOOL DelAllTask_ALLPicNum(UINT nGroupOid);										//删除所有任务图号信息


	//任务配置_产品编号
	//-------------------------------------------------------------------
	//1.任务编号模块函数集///
	int  GetTaskCodeCount(char *pTableName);										//获取任务产品编号个数										
	int  GetTaskCodeDataFromToDb(COciSQLCursor	*OciSql, StBasTaskCode *pTaskCode);	//通过数据集，获取任务产品编号信息
	BOOL GetTaskCodeData(StBasTask *pTaskInfo,UINT nTaskOid);						//获取产品编号信息,通过_任务OID_获取


	BOOL AddNewTaskCode(StBasTaskCode *pTaskCode);									//添加任务的产品编号								
	BOOL EditOldTaskCode(StBasTaskCode *pTaskCode);									//主要修改 CODE_INDEX 顺序//
	BOOL IsTaskCodeExists(UINT nTaskOid,char *szCodeName);							//判断本任务下这个编号是否存在//
	BOOL DelOldTaskCode(UINT nTaskOid,char *szCodeName);							//删除任务编号信息
	BOOL DelAllTaskCode(UINT nTaskOid);												//删除任务所有编号
	
	//2.任务模板模块函数集//
	int  GetTaskModeCount(char *pTableName);										//获取任务模板个数
	int  GetTaskModeDataFromToDb(COciSQLCursor	*OciSql, StBasTaskMode *pTaskMode); //通过数据集，获取任务模板数据
	BOOL GetTaskModeData(StBasTask *pTaskInfo,UINT nTaskOid);						//获取任务模板数据

	BOOL AddNewTaskMode(StBasTaskMode *pTaskMode);									//添加任务模板
	BOOL DelAllTaskMode(UINT nTaskOid);												//删除任务所有模板

	BOOL UpdateTaskModeInfoFile(UINT nTaskModeOid,char *strFileInfo,int nLen);			//更新任务模板基础信息=模板描述XML
	BOOL GetTaskModeInfoFile(UINT nTaskOid,UINT nModeOid, char **strFileInfo,int &nLen);//获取任务模板基础信息

	BOOL UpdateTaskModeXmlFile(UINT nTaskModeOid,char *strFileInfo,int nLen);			//更新任务模板结构信息=ModeXML		
	BOOL GetTaskModeXmlFile(UINT nTaskOid,UINT nModeOid, char **strFileInfo,int &nLen);	//获取任务模板结构信息

	//3.任务图号模块函数集//
	int  GetTaskPicNumCount(char *pTableName);												//获取任务图号个数
	int  GetTaskPicNumDataFromToDb(COciSQLCursor	*OciSql, StBasTaskPicNum *pTaskPicNum);	//通过数据集，获取任务图号数据
	BOOL GetTaskPicNumData(StBasTask *pTaskInfo,UINT nTaskOid);								//获取任务图号数据
	BOOL AddNewTaskPicNum(StBasTaskPicNum *pTaskPicNum);									//添加任务图号信息
	BOOL DelAllTaskPicNum(UINT nTaskOid);													//删除所有任务图号信息


	//七、结果查询模块
	//=================================================================================================
	//1.基于任务查询//
	int   GetTstResultCountTaskName(char *szTabName);									//获取结果个数//
	int   GetTaskResultDataDataFromToDb(COciSQLCursor	*OciSql, StTstResultBaseNew *pTaskBaseData);  //通过一个数据集获取一项结果数据

	BOOL  GetGroupTstResultBaseData(StBasTask *pResultSearchInfo, vector<StTstResultBaseNew> *stTstResultBaseDataArray);//根据任务名称进行模糊查询//
	BOOL  GetTaskTstResultBaseData(StBasTask *pResultSearchInfo, vector<StTstResultBaseNew> *stTstResultBaseDataArray);//根据任务ID 进行精确查询//

	//2.结果附件查询
	int   GetTaskResultDataDataFromToDb(COciSQLCursor	*OciSql, StTstResultAtta *pResultAttachData);  //通过一个数据集获取一项结果数据
	BOOL  GetGroupTstResultAttachData(StBasTask *pResultSearchInfo,vector<StTstResultAtta> *pStResultAttaArray);       //通过 字段进行模糊查询//
	//根据任务结果OID,获取各模板测试结果数据
	BOOL  GetTstResultAttaBaseOid(UINT nGroupOid,UINT nBaseOid,vector<StTstResultAtta> *pStResultAttaArray);
	
	//3.显示数据和生成产品报告//
	//根据任务结果OID，指定编号，各模板测试结果数据
	BOOL  GetTstResultAttaBaseOidAndProductCode(UINT nGroupOid,UINT nBaseOid,char *szProductCode,vector<StTstResultAtta> *pStResultAttaArray);
	
	//获取模板测试结果数据，根据模板结果数据OID
	BOOL  GetTstResultOid(UINT nGroupOid,UINT nAttaOid, StTstResultAtta *pTstResultInfo);

	//获取结果数据OID到指定目录下：\XmlModeParCfg\*.XML
	BOOL  GetAttaXmlFile(UINT nGroupOid,UINT nAttaOid);//将结果附件文件 读出写到缓存目录下//

	//4.结果数据删除
	BOOL  DelBaseData(UINT nGroupOid,UINT nBaseOid);					//删除任务基础表
	BOOL  DelAttaData(UINT nGroupOid,UINT nBaseOid=0,UINT nAttaOid=0);	//结果附件表//
	BOOL  DelModeData(UINT nGroupOid,UINT nBaseOid=0, UINT nAttaOid=0);	//模板数据表//


	//八、MES导入相关功能
	//=================================================================================================
	//zt add 导入任务的2种方式
	BOOL GetProductCodeFromProductBarCode(char *szProductBarCode, char *szProductCode);
	BOOL GetMesProductCount(int &nCnt);
	BOOL GetMesProductInfo(int &nCnt, CListCtrl *pList);
};
