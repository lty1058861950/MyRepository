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



#define TEXT_RIGHT_1	_T("�ϸ�")    
#define TEXT_WRONG_1	_T("���ϸ�")
#define TEXT_RIGHT_2    _T("��")  
#define TEXT_WRONG_2	_T("��")


#define COND_NULL           _T("��")
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
	int	iBegRow;	//��ʼ�к�
	int iBegCol;	//��ʼ�к�
	int iEndRow;	//��ֹ�к�
	int iEndCol;	//��ֹ�к�
	int iRowNum;	//�ϲ�������
	int iColNum;	//�ϲ�������
}StTabCell; 


typedef struct 
{
	int  iRowPos;					//�к�, (��1��ʼ)
	int  bDataFlag;                 //����״̬
	char szRowName[XLS_MAX_LEN];	//�����ݼ��
}StTabRow; 


typedef struct 
{
	int  iColPos;					//�к�, (��1��ʼ)
	int  bDataFlag;
	char szColName[XLS_MAX_LEN];	//�����ݼ��
}StTabCol; 


typedef struct 
{
	char szDbColName[XLS_MAX_LEN];	//��������
	char szOutDataName[XLS_MAX_LEN];//�������� = [�м��_�м��]
	int  iBegRow;					//��ʼ�к�
	int	 iBegCol;					//��ʼ�к�
	int  iDataType;                 //�������ͣ�1.������, 2.�ַ���, 3.��ʽ����  
}StTabData; 


typedef struct 
{
	int  iBasePos;					//���         
	char szBaseName[XLS_MAX_LEN];	//��������      
	int  iBaseType;                 //��������  
	int  szBaseFrom[XLS_MAX_LEN];	//������Դ  
}StTabBase; 


typedef struct 
{
	int		bCheckFlag;					//�Ƿ���
	int		nJudgeType;				//�ж�����
	char	szJudgeDesc[XLS_MAX_LEN];	//�ж�����
	char	szTarget1[XLS_MAX_LEN];		//ָ��ֵ1
	char	szTarget2[XLS_MAX_LEN];		//ָ��ֵ2
	double	fTarget1;					//ָ��1(������)
	double	fTarget2;					//ָ��2(������)
}StTabAlarm; 

//��ʷ��ֵ���
//----------------------------------------------------------------------
typedef struct 
{
	int		bHisChkFlag;				//�Ƿ������ʷ��ֵ���
	char	szHisValMin[XLS_MAX_LEN];	//��ʷ��Сֵ
	char	szHisValMax[XLS_MAX_LEN];	//��ʷ���ֵ
	double	fHisValMin;					//��Сֵ(������)
	double	fHisValMax;					//���ֵ(������)
}StTabHisChk; 


//���Խ�� = ���Ի�����Ϣ + N*�������� 
//-----------------------------------------------------------------------
//���Խ��_��������
typedef struct 
{
	char szTestBegTime[MAX_PATH];	//���Կ�ʼʱ��
	char szTestEndTimee[MAX_PATH];	//���Խ���ʱ��
	int  bTestFinished;				//������ɱ�־             
	char szBaseCode[XLS_MAX_LEN];	//1.���
	char szBaseTest[XLS_MAX_LEN];	//2.����
	char szBaseCheck[XLS_MAX_LEN];	//3.����
}StOutBaseData; 


//���Խ��_��������  (����Appdendix)
typedef struct 
{	
	int  nTabDataPos;				//�������_���(��1��ʼ) 
	int  nAppendixType;				//��������
	char szSrcFileName[MAX_PATH];	//ԭʼ����
	char szDesFileName[MAX_PATH];	//��������=��Ʒ����_��Ʒ���_ģ������_����������(ԭʼ����)
	char szUpUsr[XLS_MAX_LEN];		//�ϴ���Ա
	char szUpTime[XLS_MAX_LEN];		//�ϴ�ʱ��
}StOutAppData;  


//���Խ��_��������  
typedef struct 
{
	char szOutData[XLS_MAX_LEN];					//���Խ������
	char szOutDesc[XLS_MAX_LEN];                    //���Խ������    //ztadd 2016-12-29
	int  bAlarmFlag;								//����״̬
	int  bHisFlag;									//��ʷ��ֵ���״״
	char szTestUsr[XLS_MAX_LEN];					//������Ա
	char szTestTime[XLS_MAX_LEN];					//����ʱ��
	int  nAppendixFileCnt;							//��������
	//StOutAppData stResultAppData[MD_MAX_APP_CNT];	//����ָ���б�
}StOutTestData; 