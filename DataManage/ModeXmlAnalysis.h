// ModeXmlAnalysis.h: interface for the CModeXmlAnalysis class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODEXMLANALYSIS_H__748D3CC3_66B4_427C_A004_49C9C1117CD2__INCLUDED_)
#define AFX_MODEXMLANALYSIS_H__748D3CC3_66B4_427C_A004_49C9C1117CD2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ModeParMng.h"
#include "TinyXML\tinyxml.h"

void GetSysDate(char *cDate);
void GetSysTime(char *cTime);
void GetSysDateTime(char *cDateTime);
void SetXmlRootInfo(TiXmlElement *pRootInfo);

class CModeXmlAnalysis  
{
public:
	CModeXmlAnalysis();
	virtual ~CModeXmlAnalysis();

public:
	CModeParMng *m_pParMng;

public:
	
	int GetCurModeXmlFileName(char *pFileName, char *pPathName);

	//1.ģ���_�ṹ��Ϣ
	int SetXmlMdTabSrtInfo( );		//����ģ���_�ṹ��Ϣ
	int GetXmlMdTabSrtInfo( );		//��ȡģ���_�ṹ��Ϣ

	//2.ģ���_�������
	int SetXmlMdTabOutData( );		//����ģ���_�������
	int GetXmlMdTabOutData( );		//��ȡģ���_�������

	//3.ģ���_��ʷ��ֵ���	
	int SetXmlMdTabHisInfo( );		//����ģ���_��ʷ��ֵ���
	int GetXmlMdTabHisInfo( );		//��ȡģ���_��ʷ��ֵ���

};

#endif // !defined(AFX_MODEXMLANALYSIS_H__748D3CC3_66B4_427C_A004_49C9C1117CD2__INCLUDED_)
