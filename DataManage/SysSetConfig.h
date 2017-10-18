#pragma once

#include "TinyXML\tinyxml.h"
#define USER_DIR_DEF                             "User_Config"
#define USER_CONFIG_DEF                          "Config.txt"

// 默认值定义
// xml declaration
#define DECL_LOAD_VERSION		"1.0"	// for XML Msg
#define DECL_LOAD_ENCODING		"GB2312"
#define DECL_LOAD_STANDALONE		"yes"


static void GetSysDateString(char *cDate);
static void GetSysTimeString(char *cTime);
static void SetXmlRootInfoLoad(TiXmlElement *pRootInfo);
class CSysSetConfig
{
public:
	CSysSetConfig(void);
	~CSysSetConfig(void);

	//2017-01-17 liutyAdd
	int SetSelProductConfig(CString strUserLogName,vector<StBasProduct *> *pArrayProduct);
	int GetSelProductConfig(CString strUserLogName,vector<StBasProduct *> *pArrayProduct);
};
