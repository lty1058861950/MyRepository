#if !defined(AFX_WORDOPTFUN_H__INCLUDED_)
#define AFX_WORDOPTFUN_H__INCLUDED_
#define TitleFontSize  14   


//����: �����пɱ�ģ�屨��
//����: szSaveFileName, �������ļ�
//���أ������Ƿ�ɹ�
//��ע: ���ݴ˺�����д,���屨�溯��		
int WordOpt_MakeReportRowVarDemo(char *szSaveFileName);		
					
//����: ���ݱ���ģ��,���ɱ�������
//����: szSrcModeTabFileName,	������ģ���ļ�
//		szOutTabFileName,		���������ļ�
//���أ������Ƿ�ɹ�
//��ע: Դ�ļ�����Ŀ���ļ�������ͬ��
int WordOpt_MakeTabModeToTabData(char *szSrcTabModeFileName, char *szOutTabDataFileName);


//����: ���ݱ�������, ���ɱ�����Ϣ�б�
//����: szOutFileName,			��������Ϣ�ļ�(��������������ǰ�ͺ�������Ϣ)
//���أ������Ƿ�ɹ�		
//��ע: ���ݴ˺�����д,���屨�溯��	
int WordOpt_MakeReportTabInfoDemo(char *szOutTabInfoFileName,char *szSrcTabDataFileName);

int WordOpt_MakeTestimonialDemo(char *szOutTabInfoFileName,CStringArray &szSrcTabDataFileName);//lty Add 2017-02-15


//���ܣ�����ģ������ֵ������Ŀ������ֵ
//������szSrcValue,		ԭʼֵ
//		szDesValue��	Ŀ��ֵ
//���أ������Ƿ�ɹ�
int global_GetSrcValueToDesValue(char *szSrcValue, char *szDesValue);

#endif // !defined(AFX_WORDOPTFUN_H__INCLUDED_)
