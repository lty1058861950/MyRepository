#pragma  once 
#include <vector>
#include "PubPadStruct.h"
using namespace std;

//ztadd for lty
//--------------------------------------------------------
#define DB_USER_LEN     20        //���ݿ�_����_��󳤶�
#define DB_NAME_LEN     100       //���ݿ�_����_��󳤶�
#define DB_BACK_LEN     200		  //���ݿ�_��ע_��󳤶�
#define DB_FILE_PATH    1024      //�ļ�·��//

typedef struct _DbConfig
{
	char  szDBName[DB_NAME_LEN];//���ݿ�����//
	char  szUserName[DB_NAME_LEN];//�û���//
	char  szUserPwd[DB_NAME_LEN];//����//
}DbConfig;



//--------------------------------------------------------
//�ֶζ������ n��ͷ��ʾ����, sz��ͷ��ʾ�ַ���,d��ͷ��ʾʱ�䣻
//---------------------------------------------------------
//01.��ɫ��ṹ
typedef struct _StHrRole{
	UINT    nOid;                        //01.��ɫOID
	char    szRoleName[DB_NAME_LEN];     //02.��ɫ����
	char    szRoleNo[DB_NAME_LEN];       //03.��ɫ����
}StHrRole;
//02.�û���ṹ
typedef struct _StHrUser
{
	UINT	nOid;							//01.�û�OID
	char	szLoginName[DB_USER_LEN];		//02.��¼��
	char	szUserName[DB_USER_LEN];		//03.����
	char    szUserPwd[DB_USER_LEN];			//04.��¼����
	UINT    nRoleOid;                       //05.��ɫOID
	char    szRoleName[DB_NAME_LEN];		//05_1.��ɫ����
	UINT    nGroupOid;						//06.���ڲ���OID
	char    szGroupName[DB_NAME_LEN];       //06_1.���ڲ���OID
	char    szUserSignfile[DB_NAME_LEN];	//07.ǩ���ļ�
	UINT    nUserLogstate;					//08.״̬ :1.���� 2.����   
	UINT	nUserType;						//09.�û�����: 1.�����û� 2.ϵͳҵ���û�
	char    szCall[DB_NAME_LEN];			//10.�칫�绰
	char    szEmail[DB_NAME_LEN];			//11.����
	char	szPhone[DB_NAME_LEN];			//12.�ֻ�
	int     nPadDevID;                      //13.PAD�豸ID

	char     szPadUpTime[DB_USER_LEN];       //PAD�ϴ�ʱ��//
}StHrUser;

//03.���ű�ṹ
typedef struct _StHrGroup
{
	UINT	nOid;							//01.����OID
	UINT    nPOid;                          //02.�ϼ�����OID
	char	szGroupName[DB_NAME_LEN];		//03.��������
	char	szGroupNo[DB_NAME_LEN];		    //04.���ű��
	char    szGroupType[DB_USER_LEN];		//05.��������
	char    szDescription[DB_BACK_LEN];     //06.����
	char    szCall[DB_NAME_LEN];			//07.�绰
	char    szFaxs[DB_NAME_LEN];			//08.����
	char	szAddress[DB_BACK_LEN];			//09.��ַ
	int     nInvalid;                       //10.ʧЧ��־ ����ɾ��

	int       TreeItemType;                 //��ǰ���ڵ������
	HTREEITEM hItem;                        //��ǰ��ѡ���ڵ��ָ��
}StHrGroup;


//04.���첿��
typedef struct _StHrUpDepart 
{
	UINT	nOid;							//01.����OID
	UINT    nPOid;                          //02.�ϼ�����OID
	char	szUpDepartName[DB_NAME_LEN];		//03.��������
	char	szUpDepartNo[DB_NAME_LEN];		    //04.���ű��
	char    szUpDepartType[DB_USER_LEN];		//05.��������
	char    szDescription[DB_BACK_LEN];     //06.����
	char    szCall[DB_NAME_LEN];			//07.�绰
	char    szFaxs[DB_NAME_LEN];			//08.����
	char	szAddress[DB_BACK_LEN];			//09.��ַ
	int     nInvalid;                       //10.ʧЧ��־ ����ɾ��

	int       TreeItemType;                 //��ǰ���ڵ������
	HTREEITEM hItem;                        //��ǰ��ѡ���ڵ��ָ��
}StHrUpDepart;


typedef struct _StBasProduct{
	UINT	nOid;						      	//01.��Ʒ����OID
	char	szProductNo[DB_NAME_LEN];	      	//02.��Ʒ����
	char	szProductName[DB_NAME_LEN];	      	//03.��Ʒ����
	//UINT    nSeriesType;		                //04.ϵ������:0.��ϵ�к�,1.��ϵ�к�
	UINT    nPicNumType;                        //05.ͼ������:0.��ͼ��(��ͨ��Ʒ),1.��ͼ��(����)
	UINT	nGroupOid;							//06.���ڲ���OID
	char    szGroupName[DB_NAME_LEN];           //06_1��������
	char    szCreateTime[DB_NAME_LEN];			//07.����ʱ��
	char    szCreateUser[DB_NAME_LEN];			//08.������


	//�����ǲ�Ʒ��ѯʱ��ӵ��ֶ�//
	char    szCreateBeginTime[DB_NAME_LEN];     //1.��ѯʱ �����Ŀ�ʼʱ��;
	char    szCreateEndTime[DB_NAME_LEN];       //2.��ѯʱ �����Ľ���ʱ��; 
	int     bProductNormal;						//3.��ͨ��Ʒ��ѡ��
	int     bProductLine;                       //4.���²�Ʒ��ѡ��
     
	int     nPerPageNum;                        //3.��ѯʱÿҳ�ĸ���
	int     nCurPage;                           //4.��ǰ����ʾҳ
	int     nResultNum;                         //5.�������
	
}StBasProduct;

/*
typedef struct _StBasSeries{
	UINT	nOid;						      	//01.��Ʒϵ��OID
	char	szSeriesName[DB_NAME_LEN];	      	//02.��Ʒϵ����
	UINT	nProductOid;						//03.��ƷOID
	char	szProductNo[DB_NAME_LEN];	      	//04.��Ʒ����
	char    szCreateTime[DB_NAME_LEN];			//05.����ʱ��
	char    szCreateUser[DB_NAME_LEN];			//06.������

	int       TreeItemType;                 //��ǰ���ڵ������
	HTREEITEM hItem;                        //��ǰ��ѡ���ڵ��ָ��

}StBasSeries;
*/

typedef struct _StBasPicNum{
	UINT	nOid;						      	//01.��Ʒͼ��OID
	char	szPicNumNo[DB_NAME_LEN];	      	//02.ͼ�Ŵ���
	char	szPicNumName[DB_NAME_LEN];	      	//03.ͼ������
	UINT	nProductOid;						//04.��ƷOID
	char	szProductNo[DB_NAME_LEN];	      	//4_1.��Ʒ����
	char    szProductName[DB_NAME_LEN];         //4_2.��Ʒ����
	char    szCreateTime[DB_NAME_LEN];			//06.����ʱ��
	char    szCreateUser[DB_NAME_LEN];			//07.������
	UINT	nGroupOid;

	int       TreeItemType;                 //��ǰ���ڵ������
	HTREEITEM hItem;                        //��ǰ��ѡ���ڵ��ָ��

}StBasPicNum;


//ģ����Ϣ
typedef struct  _StBasMode
{
	//ģ��������Ϣ
	//-------------------------------------------------------------
	UINT	nOid;						      	//01.ģ��OID
	char	szModeName[DB_NAME_LEN];	      	//02.ģ������
	char	szModeVersion[DB_NAME_LEN];	      	//03.ģ��汾
	UINT	nModeType;						    //04.ģ������:0.δ����, 1.��Ʒͨ��,2.��Ʒר��,3.����ר��
	UINT	nModeRowVar;	      	            //05.ģ���пɱ�״̬��0.���ɱ� 1.�пɱ�
	int	    nModeSize;	      	                //06.ģ���С
	char    szModeTabName[DB_NAME_LEN];			//07.ģ�����ݱ����
	UINT	nInitTabSrt;	      	            //08.�Ƿ������ݱ�ṹ��0.δ���� 1.�ѽ���
	UINT	nGroupOid;						    //09.���ڲ���OID
	char    szGroupName[DB_NAME_LEN];                        //09_1.��������
	StBasProduct stProductInfo;                //10.���ò�ƷOID 11.��Ʒ����  ��Ʒ��Ϣ

	char    szModel[DB_NAME_LEN];			    //12.�����ͺ�
	char    szPhase[DB_NAME_LEN];			    //13.���ý׶�
	char    szCreateTime[DB_NAME_LEN];			//14.ģ�崴��ʱ��
	char    szCreateUser[DB_NAME_LEN];			//15.ģ�崴����
	char    *pXmlFile;                          //16.ģ�������XML�ļ�
	int     nFormula;                           //17.���޹�ʽģ�� 0.û�У� 1.��
	
	int       TreeItemType;                 //��ǰ���ڵ������
	HTREEITEM hItem;                        //��ǰ��ѡ���ڵ��ָ��
	HTREEITEM phItem;                       //��ǰ��ѡ�����ڵ��ָ��
	CTreeCtrl *pModeTree;                   //���ڵ�ָ��//

	void Release()
	{
		if(pXmlFile != NULL)
		{
			delete []pXmlFile;
			pXmlFile = NULL;
			nModeSize = 0;
		}
	}

	//ģ���ѯ����
	//-------------------------------------------------------------
	//�����ǲ�ѯʱ��ӵ��ֶ�//
	char  szCreateBeginTime[DB_USER_LEN];//1.������ʼʱ��//
	char  szCreateEndTime[DB_USER_LEN];  //2.��������ʱ��//

	int   bModeCurrency;                 //3.ͨ��ģ�� ֵ���ڵ���1��ʾ��ѯ  0����ѯ 
	int   bModeDedicated;                //4.��Ʒר�� ͬ��
	int   bModeLineDed;                  //5.����ר�� ͬ��
	int   bModeNotUse;                   //6.δ����   ͬ��

	int   bModeRowNoChange;              //7.�в��ɱ� ͬ��
	int   bModeRowChange;                //8.�пɱ�   ͬ��

	int   bInitedTabSrt;                 //9.�ѳ�ʼ����ṹ   ͬ��
	int   bUnInitTabStr;                 //10.δ��ʼ����ṹ  ͬ��


	int     nPerPageNum;                 //11.��ѯʱÿҳ�ĸ���
	int     nCurPage;                    //12.��ǰ����ʾҳ
	int     nResultNum;                  //13.�������
}StBasMode;

typedef struct  _StBasTaskSave{
	UINT nOid;                        //01.���ݱ�OID
	UINT nGroupOid;                   //02.����OID
	char szBaseTabName[DB_NAME_LEN];      //03.���ݻ���������
	char szAttaTabName[DB_NAME_LEN];      //04.���ݸ��ӱ�����
	char szCreateTime[DB_USER_LEN];   //05.����ʱ��
	char szCreateUser[DB_USER_LEN];   //06.������
}StHrGroupSave;

typedef struct  _StBasModeSave{
	UINT nOid;                        //01.���ݱ�OID
	UINT nModeOid;                    //02.ģ��ID
	char szTabName[DB_NAME_LEN];      //03.���ݱ�����
	char szCreateTime[DB_USER_LEN];   //04.����ʱ��
	char szCreateUser[DB_USER_LEN];   //05.������
}StBasModeSave;

typedef struct _StBasModeDesc{
	UINT nOid;                        //01.���ݱ�OID
	UINT nModeOid;                    //02.ģ��ID
	UINT nModeSaveOid;                //03.ģ��洢��¼ID
	char szFieldName[DB_USER_LEN];    //04.���ֶ�
	int  nDateType;                   //05.�ֶ�����
	char szDescxx[DB_NAME_LEN];       //06.�ֶ�����
	char szCreateTime[DB_USER_LEN];   //07.����ʱ��
	char szCreateUser[DB_USER_LEN];   //08.������

}StBasModeDesc;
typedef struct _StBasTaskCode {
	UINT nOid;                        //01.������OID
	UINT nTaskOid;                    //02.����OID
	int  nCodeIndex;                  //03.�����ڱ��˳���1��ʼ
	int  nDianshiTest;                //04.�Ƿ����
	char szCodeName[DB_NAME_LEN];     //05.�������
	UINT nGroupOid;
}StBasTaskCode;

typedef struct _StBasTaskMode{
	UINT nOid;                        //01.����ģ���OID
	UINT nTaskOid;                    //02.����OID
	int  nModeIndex;                  //03.������ģ��˳���1��ʼ
	UINT nModeOid;					  //04.ģ��OID
	char szModeName[DB_NAME_LEN];     //05.ģ������
	int  nModeType;                   //06.ģ������:0.��Ʒͨ��,1.��Ʒר��,2.����ר��,3.δ����
	int  nModeRowvar;                 //07.ģ���пɱ�״̬��0.���ɱ� 1.�пɱ�
	int  nFormula;                    //08.���޹�ʽģ�� 0.û�У� 1.��
	char *pModeInfoFile;              //09.XML�ļ�ģ��Ļ�����Ϣ, �����·�ʱ��¼ģ���״̬
	int  nInfoSize;                   //09_1  ������Ϣ���ļ�����
	char *pModeXmlFile;               //10.XML�ļ�ģ��������Ϣ, �����·�ʱ��¼ģ���״̬
	int  nXmlSize;                    //10_1  XML�����ļ��ĳ���
	StBasMode pModeInfo;              //���ļ�ת��Ϊ�ṹ�� ��¼ģ���״̬//
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
	UINT nOid;                        //01.�����ű�OID
	UINT nTaskOid;                    //02.����OID
	int  nPicNumIndex;                //03.������ģ��˳���1��ʼ
	UINT nPicNumOid;				  //04.ͼ��Oid
	char szPicNumNo[DB_NAME_LEN];     //05.ͼ�Ŵ���
	char szPicNumName[DB_NAME_LEN];   //06.ͼ������
	UINT nGroupOid;
}StBasTaskPicNum;


//���������//
typedef struct _StTstResultBase{
	UINT nOid;                               //01.���������OID
	UINT nTaskOid;                           //02.����Oid
	char szSendDate[DB_USER_LEN];            //03.�·�ʱ��
	char szTaskName[DB_NAME_LEN];            //04.��������
	char szImportDate[DB_USER_LEN];          //05.����ʱ��
	char szCheckUser[DB_USER_LEN];           //06.�����
	UINT nProductOid;                        //07.��ƷOID
	char szProductNo[DB_NAME_LEN];           //08.��Ʒ����
	
	UINT      nGroupOid;
	int       nResultType;
	int       TreeItemType;                 //��ǰ���ڵ������
	HTREEITEM hItem;                        //��ǰ��ѡ���ڵ��ָ��
	CTreeCtrl *pResultTree;
}StTstResultBase;
//���������//
typedef struct _StTstResultAtta{

	UINT	nOid;						      	//01.���������OID
	UINT    nTaskOid;                           //02.����Oid
	UINT    nModeOid;                           //03.ģ��Oid
	UINT    nProductOid;                        //04.��Ʒ����Oid
	UINT    nSeriesOid;                         //05.��Ʒϵ��Oid

	char    szProductName[DB_NAME_LEN];			//06.��Ʒ����
	char    szProductNo[DB_NAME_LEN];			//07.��Ʒ����
	char    szSeriesName[DB_NAME_LEN];          //08.ϵ������
	char    szModel[DB_NAME_LEN];               //09.��Ʒ�ͺ�
	char    szPhase[DB_NAME_LEN];               //10.��Ʒ�׶�
	char    szProductCode[DB_NAME_LEN];         //11.�������
	char    szModeName[DB_NAME_LEN];            //12.ģ������
	int     nModeType;                          //13.ģ������
	int     nModeRowVar;                        //14.ģ���пɱ�����
	int     nDianshiTest;                       //15.�Ƿ����
	int     nPicNumCount;                       //16.ͼ������
	int     nPercent;                           //17.��ɽ���(�ٷֱ�)
	int     bFinished;                          //18.���״̬
	char    szFinishedTime[DB_NAME_LEN];		//19.���ʱ��
	char    szCheckUser[DB_USER_LEN];           //20.�����
	char    szSendDate[DB_USER_LEN];            //21.�����·�ʱ��
	char    szImportDate[DB_USER_LEN];          //22.����ʱ��
	UINT    nBaseOid;                           //23.����������OID
	char    szTaskName[DB_NAME_LEN];            //24.��������

	int     nFormula;                           //25.���޹�ʽģ�� 0.û�У� 1.��
	char    szBatch[DB_NAME_LEN];               //26.��Ʒ���κ�

	UINT      nGroupOid;
	int       TreeItemType;                 //��ǰ���ڵ������
	HTREEITEM hItem;                        //��ǰ��ѡ���ڵ��ָ��
	CTreeCtrl *pResultTree;
}StTstResultAtta;


typedef struct _StBasTaskBaseInfo{
	UINT	nOid;						      	//01.����OID
	char	szTaskName[DB_NAME_LEN];	      	//02.��������
	char	szProjectNo[DB_NAME_LEN];	      	//03.���鵥��
	UINT	nTaskStatus;						//04.����״̬
	UINT	nTaskType;	      	                //05.��������
	char    szModel[DB_NAME_LEN];			    //06.�ͺ�
	char    szPhase[DB_NAME_LEN];			    //07.�׶�
	//UINT	nProductOid;	      	            //08.��ƷOID
	//char    szProductName[DB_NAME_LEN];       //09.��Ʒ����
	//char    szProductNo[DB_NAME_LEN];			//10.��Ʒ����
	UINT	nSeriesOid;						    //11.��Ʒϵ�к�OID
	char    szSeriesName[DB_NAME_LEN];			//12.��Ʒϵ�к�����
	char    szProductCode[DB_NAME_LEN];			//13.��Ʒ���
	int  	nCodeNumber;						//14.����
	char    szBatch[DB_NAME_LEN];		       	//15.���κ�
	

	UINT    nGroupOid;		                	//16.������������
	char    szGroupName[DB_NAME_LEN];           //16_1 ����������������
	char    szUpUser[DB_USER_LEN];			    //17.������
	char    szUpDate[DB_USER_LEN];		    	//18.��������
	char    szSendDate[DB_USER_LEN];			//19.�·�����
	char    szCheckLeader[DB_USER_LEN];			//20.�����鳤
	char    szCheckUser[DB_USER_LEN];			//21.����Ա����
	char    szTechUser[DB_USER_LEN];			//22.����Ա 
	int  	nArmyTest;						    //23.����
	int  	nDianShiNum;						//24.��������
	char    szAccording1[DB_BACK_LEN];			//25.��������1
	char    szAccording2[DB_BACK_LEN];			//26.��������2
	char    szAccording3[DB_BACK_LEN];			//27.��������3
	char    szAccording4[DB_BACK_LEN];			//28.��������4
	char    szAccording5[DB_BACK_LEN];			//29.��������5
	char    szTaskRemark[DB_BACK_LEN];			//30.��ע
	char    szPlanBegTime[DB_USER_LEN];			//31.�ƻ���ʼʱ��
	char    szPlanEndTime[DB_USER_LEN];			//32.�ƻ�����ʱ��
	char    szRealBegTime[DB_USER_LEN];			//33.ʵ�ʿ�ʼʱ��
	char    szRealEndTime[DB_USER_LEN];			//34.ʵ�ʽ���ʱ��

	char    szDownLoadDate[DB_USER_LEN];                   //35.����ʱ��
	char    szFinishDate[DB_USER_LEN];                     //36.�������ʱ��
	char    szImportDate[DB_USER_LEN];                     //37.���ݵ���ʱ��
	char    szCreateDate[DB_USER_LEN];                     //37.���񴴽�ʱ��
	char    szCreateUser[DB_USER_LEN];                     //38.���񴴽���

	int       TreeItemType;                 //��ǰ���ڵ������
	HTREEITEM hItem;                        //��ǰ��ѡ���ڵ��ָ��
	CTreeCtrl *pTaskTree;

	int     nModifyType;                   //�޸�ģʽ  0,ֻ�޸Ļ�����Ϣ  1.�޸�������Ϣ(�������  ģ��  ͼ�ŵ�)

	//����CList�ؼ��޸��ֶ�//

	int   nListIndex;                      //��ǰѡ�е�List����//

	//�����ǲ�ѯʱ ��ӵ��ֶ�//
	char  szCreateBeginTime[DB_USER_LEN];//1.������ʼʱ��//
	char  szCreateEndTime[DB_USER_LEN];  //2.��������ʱ��//
	char  szSendBeginTime[DB_USER_LEN];//3.�ɹ���ʼʱ��//
	char  szSendEndTime[DB_USER_LEN];  //4.�ɹ�����ʱ��//
	char  szDownLoadBeginTime[DB_USER_LEN];//5.���ؿ�ʼʱ��//
	char  szDownLoadEndTime[DB_USER_LEN];  //6.���ؽ���ʱ��//
	char  szFinishBeginTime[DB_USER_LEN];//7.��ɿ�ʼʱ��//
	char  szFinishEndTime[DB_USER_LEN];  //8.��ɽ���ʱ��//


	int     bTaskInit;                  //3.������
	int     bTaskOk;                    //4.���ɹ�
	int     bTaskRuning;                //5.ִ����
	int     bTaskFinish;                //6.�����
	int     bTaskStop;                  //7.����ֹ


	int     bTaskTest;                  //8.����������  ����
	int     bTaskReTest;                //9.����
	int     bTaskHelpReTest;            //10.��Э����

	int     nPerPageNum;                 //11.��ѯʱÿҳ�ĸ���
	int     nCurPage;                    //12.��ǰ����ʾҳ
	int     nResultNum;                  //13.�������

	//2017-03-07 Liuty add  Ϊ��������ʱ�ӵ��ֶ�//

	int     nIndex;                      //1.���
	char    szFoldName[DB_FILE_PATH];    //2.�ļ�Ŀ¼
	char    szFileName[DB_BACK_LEN];     //3.�ļ���

	//2017-04-05 Liuty add Ϊ��������Ľ����ѯʱ��ӵ��ֶ�
	int     nResultType;                 //1.��ѯ����
}StBasTaskBaseInfo;

typedef struct _StBasTask{
	StBasTaskBaseInfo stTaskBaseInfo;            //����Ļ�����Ϣ//
	StBasProduct  stProductInfo;                 //��Ʒ����ϸ��Ϣ//
	StHrGroup     stHrGroup;                     //�������ŵ���ϸ��Ϣ
	StHrUpDepart  stHrUpDepart;                  //���첿�ŵ���ϸ��Ϣ

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
			//�ͷ��ڴ�//
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
			//�ͷ��ڴ�//
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
			//�ͷ��ڴ�//
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
			//�ͷ��ڴ�//
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


//2017-04-05 Liuty Add ��������ṹ�°�
typedef struct  _StTstResultBaseNew{
	UINT              nOid;                         //1.�������ݱ��OID
	StBasTask         stTaskInfo;                   //2.�����ȫ����Ϣ

	void  Release()
	{
		nOid = 0;
		stTaskInfo.Release();
	}
}StTstResultBaseNew;

typedef struct _StSearchSetInfo{
	int	nPerPageNum;						      	//01.ÿһҳ�Ľ������
	int nAimPage;                                  //02.ת����һҳ
	int nCurPage;                                  //03.��ǰҳ
	int nMaxPage;                                  //04.���ҳ��
}StSearchSetInfo;



typedef struct _StBasAttachment{
	char Exclosure_OldName[DB_BACK_LEN];//����ԭʼ����//
	char Exclosure_Name[DB_BACK_LEN];//��������//
	int  nModeCellOrder;//���ݱ�ţ���ģ��ĵڼ�����Ԫ��//
	char ModeDesc[DB_NAME_LEN];//����ģ��ı�ʶ//
	int  nDataType;//��������//
	char BUILDUSR[DB_USER_LEN];//�ɼ���//
	char BUILDTime[DB_USER_LEN];//�ɼ�ʱ��//
}StBasAttachment;

//�������ݽṹ//
typedef struct _TestDataStr{
	int  Index;//���ݵ����//
	int  iDataType;        //��������//
	char Name[XLS_MAX_LEN];//���ݿ��Ӧ���ֶ���///
	char Desc[XLS_MAX_LEN];//�ֶ����ݵ�����//
	char Data[XLS_MAX_LEN];//����//
	char CheckUsr[DB_USER_LEN];//�����//
	char CheckTime[DB_USER_LEN];//���ʱ��//
}TestDataStr;


typedef struct _StBasTestimonialPage1{
	char szTitle[DB_NAME_LEN];                //1.����
	int  nPageNum;                            //2.����ҳ
	char szProductNo[DB_NAME_LEN];            //3.��Ʒ����
	char szProductName[DB_NAME_LEN];          //4.��Ʒ����
	char szProductCode[DB_NAME_LEN];          //5.�������  -�� ��Ʒ���
	char szPhase[DB_NAME_LEN];                //6.���ƽ׶�  -�� �׶�
	char szProductionUnit[DB_NAME_LEN];       //7.������λ
	char szLeaveFactoryDate[DB_NAME_LEN];     //8.��������
}StBasTestimonialPage1;
typedef struct _StBasTestimonialPage2{
	char szTitle[DB_NAME_LEN];                //1.����
	int  nCount;                              //2.�м������
	char szRules[DB_USER_LEN][DB_BACK_LEN*2];   //3.�������� 1��2��3��������
}StBasTestimonialPage2;

typedef struct _StBasTestimonialPage3{
	char szTitle[DB_NAME_LEN];                //1.����  Ŀ¼
	int  nCount;                              //2.�м���Ŀ¼
	char szRules[DB_USER_LEN][DB_NAME_LEN];   //3.Ŀ¼���� 1��2��3��������
	int  nPageNums[DB_USER_LEN];              //4.ÿһ���ҳ��
}StBasTestimonialPage3;

typedef struct _StBasTestimonialPage4{
	char szTitle[DB_NAME_LEN];                //1.����  ��Ʒ�ϸ����
	int  nShowType;                           //2.����
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
	char szTitle[DB_NAME_LEN];                //1.����  ��Ʒ�ϸ����
	vector<StBasPage5ProductSort>  stProdSortArray;//2.��Ʒ���ױ�Ĳ�Ʒ
	void Relese()
	{
		memset(szTitle, 0, sizeof(szTitle));
		stProdSortArray.clear();
	}
}StBasTestimonialPage5;

typedef struct _StTabMergeCell
{
	int	iBegRow;	//��ʼ�к�
	int iBegCol;	//��ʼ�к�
	int iEndRow;	//��ֹ�к�
	int iEndCol;	//��ֹ�к�

	int iRowNum;	//�ϲ�������
	int iColNum;	//�ϲ�������
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
	char szDeviceName[DB_NAME_LEN];                         //1.���������涨��
	char szStdParameter[DB_NAME_LEN];                       //2.����ʱ��
	char szTstParameter[DB_NAME_LEN];                       //3.���β�����  1
	char szHisParameter1[DB_NAME_LEN];                      //4.���β�����  2
	char szHisParameter2[DB_NAME_LEN];                      //5.���β�����  3
	char szHisParameter3[DB_NAME_LEN];                      //6.���β�����  4
	char szHisParameter4[DB_NAME_LEN];                      //7.���β�����  5
}StBasPage6DeviceCarte;
typedef struct _StBasTestimonialPage6{
	char                  szTitle[DB_NAME_LEN];                //1.����  ���Բ�Ʒ���������豸���嵥
	vector<StBasPage6DeviceCarte>  stDeviceCarteArray;//2.��Ʒ���ױ�Ĳ�Ʒ

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
	char szTitle[DB_NAME_LEN];                //1.����  ������ʱ����������¼
	vector<StBasPage7TestEnvironment>  stTestEnvironment;//2.���Ի���

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
	char szTitle[DB_NAME_LEN];                //1.����  ��Ʒ�������ܲ��Լ�¼
	vector<StTstResultAtta>  stTstResultAtta; //2.������ݸ���

	void Relese()
	{
		memset(szTitle, 0, sizeof(szTitle));
		stTstResultAtta.clear();
	}
	
}StBasTestimonialPage8;


typedef struct  _StBasPage9ConnectTeleTime
{
	char szBegEndTime[DB_NAME_LEN];                  //1.��ֹʱ��
	char szTemp[DB_USER_LEN];                        //2.�¶�
	char szHumidity[DB_USER_LEN];                    //3.ʪ��
	char szWorkStatus[DB_NAME_LEN];                  //4.�������
	char szThisConnTele[DB_USER_LEN];                //5.����ͨ��ʱ��
	char szHisConnTele[DB_USER_LEN];                 //6.�ۼ�ͨ��ʱ��
	char szOperUser[DB_USER_LEN];                    //7.������
	char szCheckUser[DB_USER_LEN];                   //8.�����
}StBasPage9ConnectTeleTime;
typedef struct _StBasTestimonialPage9{
	char szTitle[DB_NAME_LEN];                //1.����  ͨ��ʱ���¼
	vector<StBasPage9ConnectTeleTime>  stTstConnectTele; //2.ͨ������

	void Relese()
	{
		memset(szTitle, 0, sizeof(szTitle));
		stTstConnectTele.clear();
	}

}StBasTestimonialPage9;


typedef struct  _StBasPage10TaskOver
{
	char szOverTime[DB_USER_LEN];                    //1.��ֹʱ��
	char szOverAccording[DB_USER_LEN];               //2.��������
	char szExplain[DB_NAME_LEN];                     //3.����˵��
	char szOutUnit[DB_USER_LEN];                     //4.������λ
	char szOutUser[DB_USER_LEN];                     //5.�����а���
	char szInUnit[DB_USER_LEN];                      //6.���յ�λ
	char szInUser[DB_USER_LEN];                      //7.���ճа���
}StBasPage10TaskOver;

typedef struct _StBasTestimonialPage10{
	char szTitle[DB_NAME_LEN];                       //1.����  ���Ӽ�¼
	vector<StBasPage10TaskOver>  stTstTaskOver;      //2.��������
	void Relese()
	{
		memset(szTitle, 0, sizeof(szTitle));
		stTstTaskOver.clear();
	}

}StBasTestimonialPage10;
typedef struct _StBasPage11SpecialRecord{
	char szRecordText[DB_BACK_LEN];               //1.����
	char szUnit[DB_USER_LEN];                     //2.��λ
	char szUser[DB_USER_LEN];                     //3.����
	char szDate[DB_USER_LEN];                     //4.����

}StBasPage11SpecialRecord;
typedef struct _StBasTestimonialPage11{
	char szTitle[DB_NAME_LEN];                       //1.����  �������
	vector<StBasPage11SpecialRecord>  stTstSpecialRecord;      //2.��������
	void Relese()
	{
		memset(szTitle, 0, sizeof(szTitle));
		stTstSpecialRecord.clear();
	}

}StBasTestimonialPage11;
//֤����ṹ//
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