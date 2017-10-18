#pragma once
#include "OracleOci/OracleOciDbMng.h"

class CDataMng
{
public:
	CDataMng(void);
	~CDataMng(void);
public:
	BOOL nConnectStatus;

	//-----���ݿ���������ӿ�------	
	BOOL DeleteTableData( char *pTableName ,BOOL DelTab = FALSE);					//FALE Ĭ�ϱ�����ɾ��������//
	BOOL GetTableRowCount(char *pTableName, int &nCnt);								//��ȡ�и���
	CString GetFieldValue(char *szFile,COciSQLCursor	*OciSql);					//�������ݼ���ȡĳ���ֶ�

	BOOL QueryDataInfo(char *pTableName, CStringArray& ReturnVarArray,int nCol);	//��ȡ���е�ȫ������//
	BOOL GetDataInfo(char *szSQL, CStringArray& ReturnVarArray,int nCol);			//��ȡ���в�������//
	//����(�Ƽ�) ���õ� ��С��ID��///
	//CString  GetTabLeastID(CString nTabName,CString IDName);						//DEL_��ȡ�ַ���

	//SEQUENCE�������
	//----------------------------------------------------------------
	int  GetTabLeastOid(char *szTableName);											//��ȡ��С����ID			
	BOOL GetSeqId(char *szTableName,UINT &nCurID);									//��ȡSEQUENCE��ID

	//BOOL GetTableInfo(char *szSQL, CStringArray& ReturnVarArray,int nCol);					//
	//BOOL GetTableInfo(char *pTableName, CStringArray& ReturnVarArray,int *nCol,int len);
	//BOOL GetProdNameTableInfo(char *szSQL, CStringArray& ReturnVarArray,int nCol);

	//BOOL InsertDataInfo(char *szSQL);					//
	BOOL UpdateDataInfo(char *szSQL);					//�������ݡ����¡�ɾ��
	//BOOL DeleteDataInfo(char *szSQL);


	//���ºͻ�ȡ BOLB���͵�����//
	//----------------------------------------------------------------
	BOOL UpdateOracleBlob(char *szSQL,char *FieldName,char *strFileInfo,int nlen);		//����BLOB�������ݣ�����BLOB����
	BOOL GetTableBolbInfo(char *szSQL,char *FieldName,char *strFileInfo,int &nlen);		//��ȡBLOB����

	
	//һ���û�����
	//=================================================================================================
	
	//��ɫģ��ĺ���//
	int  GetRoleCount();													//��ȡ��ɫ����    [δ����]
	BOOL InitRoleTab();														//��ʼ����ɫ��Ϣ  [δ����]
	BOOL GetAllRole(vector<StHrRole *> *pAllRole);							//��ȡ���ý�ɫ��Ϣ[δ����]

	//�û�����ģ������ݲ���//
	BOOL InitUserTab();														//���Ϊ�ձ���ʼ��admin��user
	int  GetCountUserLogName(char *LogName);								//ͨ����¼�������û��Ƿ���ڣ� ���أ�����1,������0
	int  GetUserDataFromToDb(COciSQLCursor	*OciSql, StHrUser *pUserInfo);	//ͨ�����ݼ�����ȡ�û���Ϣ
	BOOL GetOneUsrInfoLogName(char *LogName,StHrUser *pStr);				//��ȡһ���û���Ϣ��ͨ��_��¼��_����
	BOOL GetOneUsrInfoOid(UINT nUserOid,StHrUser *pStr);					//��ȡһ���û���Ϣ��ͨ��_�û�OID_����

	int  GetCountUser(char *pTableName = _T(""));							//��ȡ�����û�����
	BOOL GetAllUserToPad(vector<StHrUser *> *pUserArry);					//��ȡ�����û���Ϣ������PAD�û���

	BOOL IsUserLogNameExists(char *LogName);								//�жϴ��û�_��¼��_�Ƿ����
	BOOL IsUserUserNameExists(char *UserName);								//�жϴ��û�_������_�Ƿ����
	BOOL AddNewUser(StHrUser *pStr);										//����û�
	BOOL EditOldUser(StHrUser *pStr);										//�����û���Ϣ
	BOOL DelUser(char *szLoginName);										//ɾ���û�

	//�޸��û�����//
	BOOL ReSetUsrPwd(char *NetPwd,char *UsrLogName);						//�����û�����



	//�������첿��
	//=================================================================================================
	//2017-03-01 liuty:add ���첿��ģ�麯��
	int  GetUpDepartCount(char *pTableName);											//��ȡ���첿�Ÿ���
	int  GetUpDepartDataFromToDb(COciSQLCursor	*OciSql, StHrUpDepart *pStUpDepart);	//ͨ�����ݼ�����ȡ���첿����Ϣ
	BOOL GetAllUpDepart(vector<StHrUpDepart > *pStHrUpDepartArry);						//��ȡ���н��첿����Ϣ
	BOOL GetOneUpDepartInfoOID(UINT OID,StHrUpDepart *pStUpDepart);						//��ȡһ�����첿����Ϣ��ͨ��_OID_��ȡ
	BOOL GetOneUpDepartInfoDepartName(char *szDepartName,StHrUpDepart *pStUpDepart);	//��ȡһ�����첿����Ϣ��ͨ��_���첿������_��ȡ
	BOOL IsUpDepartExists(CString DepartName);											//�жϲ����Ƿ����, �������Ʋ����ظ�
	BOOL AddNewUpDepart(StHrUpDepart *pStUpDepart);										//��ӽ��첿��
	BOOL EditOldUpDepart(StHrUpDepart *pStUpDepart);									//���Ľ��첿��
	BOOL DelUpDepart(UINT nOid);														//ɾ�����첿�ţ�ͨ��OID


	//���������
	//=================================================================================================
	BOOL InitGroupTab();																//���Ϊ�ձ���ʼ�������鴦����						
	int  GetGroupCount(char *pTableName = _T(""));										//��ȡ������ĸ���
	BOOL GetAllValidGroup(vector<StHrGroup *> *pStHrGroupArry);							//��ȡ���п�����
	BOOL GetAllInvalidGroup(vector<StHrGroup *> *pStHrGroupArry);						//��ȡ���в�������
	int  GetOneGroupInfoOID(UINT OID,StHrGroup *pStr);									//��ȡһ������Ϣ��ͨ��_OID_��ȡ
	int  GetOneGroupInfoName(char *szGroupName,StHrGroup *pStr);						//��ȡһ������Ϣ��ͨ��_������_��ȡ
	BOOL IsDepartExists(CString DepartName, UINT pOid = 0);								//�ж����Ƿ���ڣ������Ʋ����ظ�  

	BOOL AddNewGroup(StHrGroup *pStr);													//�����
	BOOL EditOldGroup(StHrGroup *pStr);													//������
	BOOL DelGroup(UINT nOid);															//�����鲻����
	BOOL RecoveryGroup(UINT nGroupOid);													//���������

	//���������ģ�麯��// Ϊÿһ���鴴��һ�� ����������һ�����������
	BOOL IsHrGroupSaveExists(UINT nGroupOid);											//���������ͽ���������Ƿ����: "HR_GROUP_SAVE"
	BOOL AddNewHrGroupSave(StHrGroupSave *pHrGroupSave);								//���һ�������������


	//�ġ���Ʒ����
	//=================================================================================================
	//��Ʒģ��ĺ���///
	int  GetProdCount(char *pTableName=_T(""));											//��ȡ��Ʒ����, [���������ڶ���]
	int  GetProdCountGroup(UINT nGroupOid);												//��ȡ��ǰ������в�Ʒ����
	int  GetProdDataFromToDb(COciSQLCursor	*OciSql, StBasProduct *pProductInfo);		//ͨ�����ݼ�����ȡ��Ʒ��Ϣ

	//��ʼ��������
	//��ȡ��Ʒ��Ϣ,������ID
	BOOL GetGroupProductInfo(UINT nGroupOid, vector<StBasProduct> *pArrayProduct);		//��ȡ��Ʒ��ǰ���Ʒ��Ϣ

	//ͨ��ģ����ѯ�ķ�ʽ ��ѯ�����ŵ����в�Ʒ��Ϣ 
	BOOL GetGroupProductData(UINT GroupOid, StBasProduct *pProductSearch, vector<StBasProduct> *pArrayProduct);
	
	//��ȡ��Ʒ��Ϣ���������,ͼ������[�̶�0]  nPicNumType��ͼ������  0.��ͼ������, 1.��ͼ������
	BOOL GetGroupPicNumProdInfo(UINT GroupOid,int nPicNumType,vector<StBasProduct > *pArrayProduct);  //������ʾ��ͼ�����͵Ĳ�Ʒ��

	//��ȡһ����Ʒ��Ϣ������_��ƷOID_��ȡ
	BOOL GetProdDataOid(UINT ProdOid,StBasProduct *pStr);//ͨ��Oid��ò�Ʒ����Ϣ

	//ͨ��һ����Ʒ��Ϣ������_����Oid�Ͳ�Ʒ����_���
	BOOL GetProdDataGroupOidProdNo(UINT GroupOid,char *szProductNo,StBasProduct *pStr);


	//1.��Ʒ����ģ�麯��
	BOOL  AddNewProd(StBasProduct *pStr);												//��Ӳ�Ʒ��Ϣ
	BOOL  IsProdExists(UINT GroupOid,char *szProductNo);								//�жϵ�ǰ��˲�Ʒ�Ƿ����,����_��Ʒ����_��ѯ
	BOOL  EditOldProd(StBasProduct *pStr);												//���Ĳ�Ʒ��Ϣ
	BOOL  DelOldProd(UINT nOid);														//ɾ����Ʒ��Ϣ

	//������в�Ʒ��������������
	BOOL  DelAllProd(UINT nGroupOid);                                                    //ɾ��ȫ����Ʒ
	BOOL  DelAllProd_PicNum(UINT nGroupOid);											 //ɾ��ȫ��ͼ����Ϣ


	//2.��Ʒͼ��ģ�麯��
	int  GetPicNumCount(char *pTableName);												//��ȡͼ�Ÿ�����[���������ڶ���]
	int  GetProdPicNumDataFromToDb(COciSQLCursor	*OciSql, StBasPicNum *pBasPicNum);	//ͨ�����ݼ�����ȡͼ����Ϣ
	BOOL GetProdPicNumData(UINT ProductOid,char *szPicNumNo,StBasPicNum *pBasPicNum);	//��ȡͼ�����ݣ�����_ͼ�Ŵ���_��ȡ
	BOOL GetPicNumDataFromOid(UINT PicNumOid,StBasPicNum *pBasPicNum);					//��ȡͼ�����ݣ�����_ͼ��OID_��ȡ
	BOOL GetProductPicNumInfo(UINT ProdOid,vector<StBasPicNum> *pPicNumArray);			//��ȡ��Ʒ����ͼ����Ϣ

	BOOL AddNewPicNum(StBasPicNum *pStr);												//���ͼ����Ϣ									
	BOOL IsPicNumExists(UINT ProductOid,char *szPicNumNo);								//�жϴ˲�Ʒ_ͼ�Ŵ���_�Ƿ����//
	BOOL EditOldPicNum(StBasPicNum *pStr);												//����ͼ����Ϣ
	BOOL DelOldPicNum(UINT nPicNumOid);													//ɾ��ͼ����Ϣ



	//�塢ģ�����
	//=================================================================================================
	//ģ��ģ��ĺ���///
	int  GetModeCount(char *pTableName=_T(""));											//��ȡģ�����

	int  GetModeCountGroup(UINT GroupOid);												//��ȡģ�����, ���������� 
	int  GetModeCountGroupType(UINT GroupOid,int nModeType);							//��ȡģ�����, ����_��OID��ģ������_��ȡ
	int  GetModeDataFromToDb(COciSQLCursor	*OciSql, StBasMode *pModeInfo);


	//ģ������
	//-------------------------------------------------------------------
	//��ȡģ����Ϣ, ��������:pModeSearchInfo
	BOOL GetGroupModeInfo(UINT GroupOid,StBasMode *pModeSearchInfo,vector<StBasMode> *pModeArry);//������ģ������//

	//��ȡģ����Ϣ, �������, ģ������
	BOOL GetGroupModeTypeData(UINT GroupOid,int nModeType,vector<StBasMode> *pModeArry);	//������ ĳ���� ��ȷ����//

	//��ȡ��Ʒ��ģ����Ϣ, ͨ��_��ƷOID_��ȡ
	BOOL GetProdModeData(UINT nProductOid,vector<StBasMode > *pModeArry);					//��Ʒ�¾�ȷ����//

	//��ȡһ��ģ����Ϣ, ͨ��_ģ��OID_��ȡ
	BOOL GetModeDataOid(UINT ModeOid,StBasMode *pStr);//ͨ��Oid���ģ�����Ϣ


	BOOL AddNewMode(StBasMode *pStr);													//���ģ��
	BOOL IsGroupProdModeExists(UINT GroupOid,UINT ProductOid,char *szModeName);			//�жϵ�ǰ��˲�Ʒ�����ģ���Ƿ����//
	BOOL EditOldMode(StBasMode *pStr);													//����ģ��
	BOOL DelOldMode(UINT ModeOid);														//ɾ��ģ��

	BOOL UpdateModeXmlFile(UINT nModeOid, char *strFileInfo,int nLen);					//����ģ��XML�ֶ�
	BOOL GetModeXmlFile(UINT nModeOid, char **strFileInfo,int &nLen);					//��ȡģ��XML�ֶ�


	//ģ��ṹ��ģ�麯��
	//-------------------------------------------------------------------
	BOOL IsModeStrTabExists(UINT nModeOid);												//���ģ��ṹ���Ƿ����//
	BOOL AddNewModeSave(StBasModeSave *pStr);											//���ģ��ṹ
	BOOL GetAllModeSave(vector<StBasModeSave *> *pModeSaveArray);						//��ȡ����ģ��ṹ
	BOOL DelOldModeSave(UINT nModeOid);													//ɾ��ģ��ṹ�����ļ�¼��Ϣ
	int  GetDataCount(char *szTabName);													//��ȡ���ݵĸ���

	//ģ����ֶε�����//
	BOOL AddNewModeDesc(StBasModeDesc *pModeDesc);										//���ģ���ֶ�����
	BOOL DelModeAllField(UINT nModeOid);												//ɾ��ģ���ֶ�����
	

	//�����������
	//=================================================================================================
	int  GetTaskCount(char *pTableName);												//��ȡ�������
	int  GetTaskCountGroup(UINT nGroupOid);												//��ȡ�����ŵ������������
	int  GetTaskCountGroupStatus(UINT nGroupOid, int nTaskStatus);						//��ȡ��ǰ���ĳ��״̬���������
	int  GetTaskDataFromToDb(COciSQLCursor	*OciSql, StBasTask *pTaskInfo);				//ͨ�����ݼ�����ȡ������Ϣ

	//��ȡ������Ϣ
	//-------------------------------------------------------------------
	//��ȡ��Ʒ��������Ϣ������_��ƷOID_��ȡ
	BOOL GetProductTaskInfo(UINT ProdOid,vector<StBasTask *> *pArrayTask);						

	//��ȡ��Ʒ��ָ������״̬��������Ϣ, ����_��ƷOID_����״̬_��ȡ
	BOOL GetProductTaskStatusInfo(UINT ProdOid,int nTaskStatus,vector<StBasTask *> *pArrayTask);

	//�жϵ�ǰ��Ʒ���д�״̬������//
	BOOL IsStatusProdTaskExists(int nTaskStatus,UINT ProductOid);

	//ģ����ѯ
	//-------------------------------------------------------------------
	//nGroupOid���������� �뽻�첿���޹�
	BOOL GetGroupTaskInfo(UINT nGroupOid, StBasTask *pTaskSearchInfo,vector<StBasTask> *pArrayTask);

	//ͨ��Oid����������Ϣ
	BOOL GetTaskDataOid(UINT nTaskOid,StBasTask *pStTaskInfo);
	
	//ͨ��_��ƷOID_��������_��ȡ������Ϣ
	BOOL GetTaskDataProdOidTaskName(UINT nProdOid,char *szTaskName, StBasTask *pStTaskInfo);


	BOOL AddNewTask(StBasTask *pTaskInfo);											//�������
	BOOL IsProductTaskExists(UINT ProductOid,char *szTaskName);						//�жϱ���Ʒ����������Ƿ����//
	BOOL EditOldTask(StBasTask *pTaskInfo);											//��������
	BOOL DelOldTask(UINT nTaskOid);													//ɾ������

	//ɾ��ȫ������
	BOOL DelAllTask(UINT nGroupOid);												//ɾ����������
	BOOL DelAllTask_AllCode(UINT nGroupOid);										//ɾ���������б��
	BOOL DelAllTask_ALLMode(UINT nGroupOid);										//ɾ����������ģ��
	BOOL DelAllTask_ALLPicNum(UINT nGroupOid);										//ɾ����������ͼ����Ϣ


	//��������_��Ʒ���
	//-------------------------------------------------------------------
	//1.������ģ�麯����///
	int  GetTaskCodeCount(char *pTableName);										//��ȡ�����Ʒ��Ÿ���										
	int  GetTaskCodeDataFromToDb(COciSQLCursor	*OciSql, StBasTaskCode *pTaskCode);	//ͨ�����ݼ�����ȡ�����Ʒ�����Ϣ
	BOOL GetTaskCodeData(StBasTask *pTaskInfo,UINT nTaskOid);						//��ȡ��Ʒ�����Ϣ,ͨ��_����OID_��ȡ


	BOOL AddNewTaskCode(StBasTaskCode *pTaskCode);									//�������Ĳ�Ʒ���								
	BOOL EditOldTaskCode(StBasTaskCode *pTaskCode);									//��Ҫ�޸� CODE_INDEX ˳��//
	BOOL IsTaskCodeExists(UINT nTaskOid,char *szCodeName);							//�жϱ��������������Ƿ����//
	BOOL DelOldTaskCode(UINT nTaskOid,char *szCodeName);							//ɾ����������Ϣ
	BOOL DelAllTaskCode(UINT nTaskOid);												//ɾ���������б��
	
	//2.����ģ��ģ�麯����//
	int  GetTaskModeCount(char *pTableName);										//��ȡ����ģ�����
	int  GetTaskModeDataFromToDb(COciSQLCursor	*OciSql, StBasTaskMode *pTaskMode); //ͨ�����ݼ�����ȡ����ģ������
	BOOL GetTaskModeData(StBasTask *pTaskInfo,UINT nTaskOid);						//��ȡ����ģ������

	BOOL AddNewTaskMode(StBasTaskMode *pTaskMode);									//�������ģ��
	BOOL DelAllTaskMode(UINT nTaskOid);												//ɾ����������ģ��

	BOOL UpdateTaskModeInfoFile(UINT nTaskModeOid,char *strFileInfo,int nLen);			//��������ģ�������Ϣ=ģ������XML
	BOOL GetTaskModeInfoFile(UINT nTaskOid,UINT nModeOid, char **strFileInfo,int &nLen);//��ȡ����ģ�������Ϣ

	BOOL UpdateTaskModeXmlFile(UINT nTaskModeOid,char *strFileInfo,int nLen);			//��������ģ��ṹ��Ϣ=ModeXML		
	BOOL GetTaskModeXmlFile(UINT nTaskOid,UINT nModeOid, char **strFileInfo,int &nLen);	//��ȡ����ģ��ṹ��Ϣ

	//3.����ͼ��ģ�麯����//
	int  GetTaskPicNumCount(char *pTableName);												//��ȡ����ͼ�Ÿ���
	int  GetTaskPicNumDataFromToDb(COciSQLCursor	*OciSql, StBasTaskPicNum *pTaskPicNum);	//ͨ�����ݼ�����ȡ����ͼ������
	BOOL GetTaskPicNumData(StBasTask *pTaskInfo,UINT nTaskOid);								//��ȡ����ͼ������
	BOOL AddNewTaskPicNum(StBasTaskPicNum *pTaskPicNum);									//�������ͼ����Ϣ
	BOOL DelAllTaskPicNum(UINT nTaskOid);													//ɾ����������ͼ����Ϣ


	//�ߡ������ѯģ��
	//=================================================================================================
	//1.���������ѯ//
	int   GetTstResultCountTaskName(char *szTabName);									//��ȡ�������//
	int   GetTaskResultDataDataFromToDb(COciSQLCursor	*OciSql, StTstResultBaseNew *pTaskBaseData);  //ͨ��һ�����ݼ���ȡһ��������

	BOOL  GetGroupTstResultBaseData(StBasTask *pResultSearchInfo, vector<StTstResultBaseNew> *stTstResultBaseDataArray);//�����������ƽ���ģ����ѯ//
	BOOL  GetTaskTstResultBaseData(StBasTask *pResultSearchInfo, vector<StTstResultBaseNew> *stTstResultBaseDataArray);//��������ID ���о�ȷ��ѯ//

	//2.���������ѯ
	int   GetTaskResultDataDataFromToDb(COciSQLCursor	*OciSql, StTstResultAtta *pResultAttachData);  //ͨ��һ�����ݼ���ȡһ��������
	BOOL  GetGroupTstResultAttachData(StBasTask *pResultSearchInfo,vector<StTstResultAtta> *pStResultAttaArray);       //ͨ�� �ֶν���ģ����ѯ//
	//����������OID,��ȡ��ģ����Խ������
	BOOL  GetTstResultAttaBaseOid(UINT nGroupOid,UINT nBaseOid,vector<StTstResultAtta> *pStResultAttaArray);
	
	//3.��ʾ���ݺ����ɲ�Ʒ����//
	//����������OID��ָ����ţ���ģ����Խ������
	BOOL  GetTstResultAttaBaseOidAndProductCode(UINT nGroupOid,UINT nBaseOid,char *szProductCode,vector<StTstResultAtta> *pStResultAttaArray);
	
	//��ȡģ����Խ�����ݣ�����ģ��������OID
	BOOL  GetTstResultOid(UINT nGroupOid,UINT nAttaOid, StTstResultAtta *pTstResultInfo);

	//��ȡ�������OID��ָ��Ŀ¼�£�\XmlModeParCfg\*.XML
	BOOL  GetAttaXmlFile(UINT nGroupOid,UINT nAttaOid);//����������ļ� ����д������Ŀ¼��//

	//4.�������ɾ��
	BOOL  DelBaseData(UINT nGroupOid,UINT nBaseOid);					//ɾ�����������
	BOOL  DelAttaData(UINT nGroupOid,UINT nBaseOid=0,UINT nAttaOid=0);	//���������//
	BOOL  DelModeData(UINT nGroupOid,UINT nBaseOid=0, UINT nAttaOid=0);	//ģ�����ݱ�//


	//�ˡ�MES������ع���
	//=================================================================================================
	//zt add ���������2�ַ�ʽ
	BOOL GetProductCodeFromProductBarCode(char *szProductBarCode, char *szProductCode);
	BOOL GetMesProductCount(int &nCnt);
	BOOL GetMesProductInfo(int &nCnt, CListCtrl *pList);
};
