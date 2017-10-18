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

	//1.模板表_结构信息
	int SetXmlMdTabSrtInfo( );		//设置模板表_结构信息
	int GetXmlMdTabSrtInfo( );		//获取模板表_结构信息

	//2.模板表_数据输出
	int SetXmlMdTabOutData( );		//设置模板表_数据输出
	int GetXmlMdTabOutData( );		//获取模板表_数据输出

	//3.模板表_历史极值检测	
	int SetXmlMdTabHisInfo( );		//设置模板表_历史极值检测
	int GetXmlMdTabHisInfo( );		//获取模板表_历史极值检测

};

#endif // !defined(AFX_MODEXMLANALYSIS_H__748D3CC3_66B4_427C_A004_49C9C1117CD2__INCLUDED_)
