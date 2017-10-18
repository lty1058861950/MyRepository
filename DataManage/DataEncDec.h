// DataEncDec.h: interface for the CDataEncDec class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATAENCDEC_H__AFB0647A_889A_4FEC_9351_41F7ACB83C3F__INCLUDED_)
#define AFX_DATAENCDEC_H__AFB0647A_889A_4FEC_9351_41F7ACB83C3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define TMP_FILE_FOLDER   _T("d:")

enum //DoEncOrDecType
{
	typeDoDecry = 0,			//执行解密操作
	typeDoEncrypt = 1,		    //执行加密操作
};

class CDataEncDec  
{
public:
	CDataEncDec();
	virtual ~CDataEncDec();
public:
	char  m_szTmpFile[MAX_PATH];

public:
	/*
	* 函数：DoFileEncryptOrDecry	文件加解密数据处理
	* 输入：szSrcFileName			原文件
	szDesFileName			目标文件
	bEnc					是否加密			1:加密, 0:解密;
	* 输出：int					操作是否成功
	* 说明: 文件加密解密数据处理, 对原文件进行加密解密数据处理后生成目标文件。
	*/
	int DoFileEncryptOrDecry( char *szSrcFileName, char *szDesFileName, bool bEnc);	//文件加密与解密

	/*
	* 函数：DoFileEncryptOrDecry	文件加解密数据处理
	* 输入：szFileName				文件名
	bEnc					是否加密			1:加密, 0:解密;
	bSaveTmpFIle			是否保存临时文件	1:保存, 0:不保存 
	* 输出: int					操作是否成功
	* 说明: 文件加密解密数据处理, 对原文件进行加解密处理覆盖原文件， 临时文件存于m_szTmpFile
	*/
	int DoFileEncryptOrDecry( char *szFileName, bool bEnc, bool bSaveTmpFile);       //对文件进行加解密

	/*
	* 函数: DeleteTmpFile
	* 输入：无 
	* 输出: int					操作是否成功
	* 说明: 删除临时文件，临时文件存于m_szTmpFile
	*/
	int DeleteTmpFile( );

	int DoFileHexToAsc(char *szFileName, int bSaveTmpFile = 0);                  //对文件进行处理_HexToAsc

	int DoFileAscToHex(char *szFileName, int bSaveTmpFile = 0);					 //对文件进行处理_AscToHex
};

#endif // !defined(AFX_DATAENCDEC_H__AFB0647A_889A_4FEC_9351_41F7ACB83C3F__INCLUDED_)
