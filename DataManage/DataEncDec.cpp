// DataEncDec.cpp: implementation of the CDataEncDec class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DataManage.h"
#include "DataEncDec.h"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <set>
#include <iomanip>
#include "time.h"
//#include "PubFun.h"



#define SM4_BLOCK_SIZE 16  //算法的分组长度128位（16字节）。
#define ENCRYPT	1
#define DECRYPT	0


#include "CJZDALGExports.h"
#pragma comment(lib,"CJZDALGExports.lib")


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const int  BUF_SIZE_1 = 131072;     //128K = 128*1024 = 131
const int  BUF_SIZE_2 = 1024;       //  1K = 1024

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDataEncDec::CDataEncDec()
{

}

CDataEncDec::~CDataEncDec()
{

}

int CDataEncDec::DoFileEncryptOrDecry( char *szSrcFileName, char *szDesFileName, bool bEnc)	//文件加密
{
	FILE	*fp1=NULL;
	FILE	*fp2=NULL;
	long	curpos, length;
	long     nFileSize1;
	int     nPackCnt1, nPackCnt2, nPackTailLen;
	long    nTmpLen1, nTmpLen2;
	int     i,j, nLen;
	CString str;
	UCHAR    *pBuf1=NULL;
	UCHAR    *pBuf2=NULL; 
	UCHAR    bCharSn = 0x73;

	//原始密钥128位（16字节）
	unsigned char rawkey[SM4_BLOCK_SIZE]={0x1, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10};

	//初始向量128位（16字节）
	unsigned char IV[SM4_BLOCK_SIZE]=	{0x42, 0x2c, 0x66, 0xf5, 0x20, 0xf3, 0xe7, 0xee, 0x26, 0x88, 0x8d, 0xbc, 0xde, 0x8c, 0x75, 0x4};
	unsigned char IV2[SM4_BLOCK_SIZE]=	{0,};

	unsigned char *in,*out;
	int           nTimes = 1;  

	int    pltxlenth = 0;


	if ( (szSrcFileName == NULL) || (szSrcFileName == NULL) )
	{
		AfxMessageBox( _T("Error:原始文件或目标文件不能为空!") );
		return 0;
	}

	fp1 = fopen(szSrcFileName, "rb");
	if (fp1 == NULL)
	{
		str.Format("Error:%s原文件打开失败!", szSrcFileName);
		AfxMessageBox(str);
		return 0;
	}

	curpos = ftell(fp1);
	fseek(fp1, 0L, SEEK_END);
	length = ftell(fp1);
	fseek(fp1, curpos, SEEK_SET);
	nFileSize1 = length;

	if (nFileSize1 <= 0)
	{
		fclose(fp1);

		str.Format("Error:%s原文件, 长度为零无法加解密!", szSrcFileName);
		AfxMessageBox(str);		
		return 0;
	}

	fp2 = fopen(szDesFileName, "wb");
	if (fp2 == NULL)
	{
		str.Format("Error:%s目标文件打开失败!", szDesFileName);
		AfxMessageBox(str);
		return 0;
	}

	nPackCnt1 = 0;
	nPackCnt2 = 0;
	nPackTailLen = 0;
	nTmpLen1 = nFileSize1;
	if (nFileSize1 > BUF_SIZE_1)
	{
		nPackCnt1 = nTmpLen1 / BUF_SIZE_1;

		nTmpLen2 = nTmpLen1 % BUF_SIZE_1;

		nPackCnt2 = nTmpLen2 / BUF_SIZE_2;

		nPackTailLen = nTmpLen2 % BUF_SIZE_2;
	}
	else
	{
		nPackCnt1 = 0;

		nTmpLen2 = nTmpLen1;	

		nPackCnt2 = nTmpLen2 / BUF_SIZE_2;

		nPackTailLen = nTmpLen2 % BUF_SIZE_2;
	}

	pBuf1 = new UCHAR[BUF_SIZE_1+1]; 
	pBuf2 = new UCHAR[BUF_SIZE_1+1]; 

	in = (unsigned char *) malloc((BUF_SIZE_1+1) * sizeof(unsigned char));//in占有pltxlenth+1字节的空间
	out = (unsigned char *) malloc((BUF_SIZE_1+1) * sizeof(unsigned char));//out占有pltxlenth+1字节的空间


	//1.Pack1 data dealwith
	for (i=0; i<nPackCnt1; i++)
	{
		memset(pBuf1, 0, BUF_SIZE_1+1);
		if ( !feof(fp1) )
		{
			nLen = fread(pBuf1, 1, BUF_SIZE_1, fp1);
		}

		//文件加解密处理[1]----------------------------------

		//1.获取原始数据 :  pBuf1
		memset(in,  0, BUF_SIZE_1+1);
		memset(out, 0, BUF_SIZE_1+1);
		memcpy(in, pBuf1, BUF_SIZE_1);

		//2.数据加解密处理
		pltxlenth = BUF_SIZE_1;
		for(j=0; j<nTimes; j++)//加密数据量为10MB  10240
		{
			memcpy(IV2, IV, 16);
			DoEncrypOrDecry(in, pltxlenth, out, rawkey, IV2, bEnc);	//接口函数的使用，执行加密。
			memcpy(in, out, pltxlenth);
		}

		//3.获取结果数据 :  pBuf2
		memset(pBuf2, 0, BUF_SIZE_1+1);
		memcpy(pBuf2, out, BUF_SIZE_1);


		//记录最后加解密后数值
		if ( (nPackTailLen != 0) && (i == nPackCnt1-1) )
		{
			bCharSn = pBuf2[BUF_SIZE_1-1];
		}

		fwrite(pBuf2, 1, BUF_SIZE_1, fp2);
	}

	memset(pBuf1, 0, BUF_SIZE_1+1);

	//2.Pack2 data dealwith
	for (i=0; i<nPackCnt2; i++)
	{
		memset(pBuf1, 0, BUF_SIZE_2+1);

		if ( !feof(fp1) )
		{
			nLen = fread(pBuf1, 1, BUF_SIZE_2, fp1);
		}

		//文件加解密处理[2]----------------------------------

		//1.获取原始数据 :  pBuf1
		memset(in,  0, BUF_SIZE_2+1);
		memset(out, 0, BUF_SIZE_2+1);
		memcpy(in, pBuf1, BUF_SIZE_2);

		//2.数据加解密处理
		pltxlenth = BUF_SIZE_2;
		for(j=0; j<nTimes; j++)//加密数据量为10MB  10240
		{
			memcpy(IV2, IV, 16);
			DoEncrypOrDecry(in, pltxlenth, out, rawkey, IV2, bEnc);	//接口函数的使用，执行加密。
			memcpy(in, out, pltxlenth);
		}

		//3.获取结果数据 :  pBuf2
		memset(pBuf2, 0, BUF_SIZE_2+1);
		memcpy(pBuf2, out, BUF_SIZE_2);


		//记录最后加解密后数值
		if ( (nPackTailLen != 0) && (i == nPackCnt1-1) )
		{
			bCharSn = pBuf2[BUF_SIZE_2-1];
		}

		fwrite(pBuf2, 1, BUF_SIZE_2, fp2);
	}

	memset(pBuf1, 0, BUF_SIZE_1+1);

	//3.Pack Tail data dealwith
	if (nPackTailLen != 0)
	{
		memset(pBuf1, 0, nPackTailLen+1);
		if ( !feof(fp1) )
		{
			nLen = fread(pBuf1, 1, nPackTailLen, fp1);
		}

		//文件加解密处理[3]----------------------------------

		//1.获取原始数据 :  pBuf1
		memset(in,  0, BUF_SIZE_1+1);
		memset(out, 0, BUF_SIZE_1+1);
		memcpy(in, pBuf1, nPackTailLen);

		//2.数据加解密处理
		pltxlenth = nPackTailLen;	

		for(j=0; j<pltxlenth; j++)//加密数据量为10MB  10240
		{
			out[j] = in[j] ^ bCharSn;
		}

		//3.获取结果数据 :  pBuf2
		memset(pBuf2, 0, nPackTailLen+1);
		memcpy(pBuf2, out, nPackTailLen);


		fwrite(pBuf2, 1, nPackTailLen, fp2);	
	}

	delete pBuf1;
	pBuf1 = NULL;
	delete pBuf2;
	pBuf2 = NULL;

	delete in;
	in = NULL;
	delete out;
	out = NULL;

	fclose(fp1);
	fclose(fp2);

	return 1;
}



int CDataEncDec::DoFileEncryptOrDecry(char *szFileName, bool bEnc, bool bSaveTmpFile)                   //对文件进行加解密
{
	int		ret = 0;
	CString str, strTmp, strTmpRoot;

	strTmpRoot = TMP_FILE_FOLDER;

	if(GetFileAttributes(strTmpRoot) == 0xFFFFFFFF)
		CreateDirectory(strTmpRoot, NULL);

	str.Format(_T("%s"), szFileName);
	if (str.Find(".bmp") != -1)
	{
		strTmp.Format(_T("%s\\tmp.bmp"), strTmpRoot);
	}
	else if (str.Find(".avi") != -1)
	{
		strTmp.Format(_T("%s\\tmp.avi"), strTmpRoot);
	}
	else
	{
		strTmp.Format(_T("%s\\tmp.tmp"), strTmpRoot);
	}

	memset(m_szTmpFile, 0, MAX_PATH);
	strcpy(m_szTmpFile, strTmp.GetBuffer(0));

	//1.复制文件
	ret = CopyFile(szFileName, strTmp.GetBuffer(0), 0);
	if (ret == 0)
	{
		str.Format( _T("ret=%d, \r\n srcName=%s,\r\n desFile=%s"), ret, szFileName, strTmp);
		AfxMessageBox(str);
		return 0;
	}

	//2.加密文件
	ret = DoFileEncryptOrDecry(strTmp.GetBuffer(0), szFileName, bEnc);
	if (ret == 0)
	{
		return 0;
	}

	//3.删除原文件
	if (bSaveTmpFile == 0)
	{
		ret = DeleteFile(strTmp.GetBuffer(0));
		if (ret == 0)
		{
			str.Format( _T("Error:DeleteFile, ret=%d, \r\n srcName=%s,"), ret, strTmp);
			AfxMessageBox(str);
			return 0;
		}

		memset(m_szTmpFile, 0, MAX_PATH);
	}

	return 1;
}


int CDataEncDec::DeleteTmpFile( )
{
	int nLen = 0;
	int ret = 0;

	nLen = strlen(m_szTmpFile);

	if (nLen != 0)
	{
		HANDLE h;
		LPWIN32_FIND_DATA pFD=new WIN32_FIND_DATA;
		BOOL bFound=FALSE;

		if (pFD)
		{
			h=FindFirstFile(m_szTmpFile, pFD);
			bFound=(h!=INVALID_HANDLE_VALUE);
		}

		delete pFD;
		pFD = NULL;

		if (bFound != 0)
		{
			ret = DeleteFile(m_szTmpFile);
			memset(m_szTmpFile, 0, MAX_PATH);
		}
	}

	return ret;
}

int CDataEncDec::DoFileHexToAsc(char *szFileName, int bSaveTmpFile)                   //对文件进行处理_HexToAsc
{
	int		ret = 0;
	CString str, strTmp, strTmpRoot;
	char    szSrcFileName[MAX_PATH] = {0,};
	char    szDesFileName[MAX_PATH] = {0,};
	char    *srcBuf = NULL;
	char    *desBuf = NULL;
	FILE	*fp1=NULL;
	FILE	*fp2=NULL;
	long	curpos, length;
	long    nFileSize1,nFileSize2;
	int     nLen1 = 0, nLen2 = 0;

	strTmpRoot = TMP_FILE_FOLDER;

	if(GetFileAttributes(strTmpRoot) == 0xFFFFFFFF)
		CreateDirectory(strTmpRoot, NULL);

	strTmp.Format(_T("%s\\tmp.hex"), strTmpRoot);

	memset(m_szTmpFile, 0, MAX_PATH);
	strcpy(m_szTmpFile, strTmp.GetBuffer(0));

	//1.复制文件
	ret = CopyFile(szFileName, strTmp.GetBuffer(0), 0);
	if (ret == 0)
	{
		str.Format( _T("ret=%d, \r\n srcName=%s,\r\n desFile=%s"), ret, szFileName, strTmp);
		AfxMessageBox(str);
		return 0;
	}

	strcpy(szSrcFileName, strTmp.GetBuffer(0));
	strcpy(szDesFileName, szFileName);

	//2.ASC
	if ( (szSrcFileName == NULL) || (szSrcFileName == NULL) )
	{
		AfxMessageBox( _T("Error:原始文件或目标文件不能为空!") );
		return 0;
	}

	fp1 = fopen(szSrcFileName, "rb");
	if (fp1 == NULL)
	{
		str.Format("Error:%s原文件打开失败!", szSrcFileName);
		AfxMessageBox(str);
		return 0;
	}

	curpos = ftell(fp1);
	fseek(fp1, 0L, SEEK_END);
	length = ftell(fp1);
	fseek(fp1, curpos, SEEK_SET);
	nFileSize1 = length;

	if (nFileSize1 <= 0)
	{
		fclose(fp1);

		str.Format("Error:%s原文件, 长度为零!", szSrcFileName);
		AfxMessageBox(str);		
		return 0;
	}

	fp2 = fopen(szDesFileName, "wb");
	if (fp2 == NULL)
	{
		str.Format("Error:%s目标文件打开失败!", szDesFileName);
		AfxMessageBox(str);
		return 0;
	}

	nFileSize2 = nFileSize1/2;
	srcBuf = new char[nFileSize1+1];
	desBuf = new char[nFileSize2+1];

	memset(srcBuf, 0, nFileSize1+1);
	memset(desBuf, 0, nFileSize2+1);

	nLen1 = fread(srcBuf, 1, nFileSize1, fp1);

	ChangeHexAsc(srcBuf, desBuf, nFileSize2);

	nLen2 = fwrite(desBuf, 1, nFileSize2, fp2);


	delete srcBuf;
	srcBuf = NULL;
	delete desBuf;
	desBuf = NULL;

	fclose(fp1);
	fp1 = NULL;
	fclose(fp2);
	fp2 = NULL;

	//3.删除原文件
	if (bSaveTmpFile == 0)
	{
		ret = DeleteFile(strTmp.GetBuffer(0));
		if (ret == 0)
		{
			str.Format( _T("Error:DeleteFile, ret=%d, \r\n srcName=%s,"), ret, strTmp);
			AfxMessageBox(str);
			return 0;
		}

		memset(m_szTmpFile, 0, MAX_PATH);
	}

	return 1;
}



int CDataEncDec::DoFileAscToHex(char *szFileName, int bSaveTmpFile)					 //对文件进行处理_AscToHex
{
	int		ret = 0;
	CString str, strTmp, strTmpRoot;
	char    szSrcFileName[MAX_PATH] = {0,};
	char    szDesFileName[MAX_PATH] = {0,};
	char    *srcBuf = NULL;
	char    *desBuf = NULL;
	FILE	*fp1=NULL;
	FILE	*fp2=NULL;
	long	curpos, length;
	long    nFileSize1,nFileSize2;
	int     nLen1 = 0, nLen2 = 0;

	strTmpRoot = TMP_FILE_FOLDER;

	if(GetFileAttributes(strTmpRoot) == 0xFFFFFFFF)
		CreateDirectory(strTmpRoot, NULL);

	strTmp.Format(_T("%s\\tmp.asc"), strTmpRoot);

	memset(m_szTmpFile, 0, MAX_PATH);
	strcpy(m_szTmpFile, strTmp.GetBuffer(0));

	//1.复制文件
	ret = CopyFile(szFileName, strTmp.GetBuffer(0), 0);
	if (ret == 0)
	{
		str.Format( _T("ret=%d, \r\n srcName=%s,\r\n desFile=%s"), ret, szFileName, strTmp);
		AfxMessageBox(str);
		return 0;
	}

	strcpy(szSrcFileName, strTmp.GetBuffer(0));
	strcpy(szDesFileName, szFileName);

	//2.ASC
	if ( (szSrcFileName == NULL) || (szSrcFileName == NULL) )
	{
		AfxMessageBox( _T("Error:原始文件或目标文件不能为空!") );
		return 0;
	}

	fp1 = fopen(szSrcFileName, "rb");
	if (fp1 == NULL)
	{
		str.Format("Error:%s原文件打开失败!", szSrcFileName);
		AfxMessageBox(str);
		return 0;
	}

	curpos = ftell(fp1);
	fseek(fp1, 0L, SEEK_END);
	length = ftell(fp1);
	fseek(fp1, curpos, SEEK_SET);
	nFileSize1 = length;

	if (nFileSize1 <= 0)
	{
		fclose(fp1);

		str.Format("Error:%s原文件, 长度为零!", szSrcFileName);
		AfxMessageBox(str);		
		return 0;
	}

	fp2 = fopen(szDesFileName, "wb");
	if (fp2 == NULL)
	{
		str.Format("Error:%s目标文件打开失败!", szDesFileName);
		AfxMessageBox(str);
		return 0;
	}

	nFileSize2 = nFileSize1*2;
	srcBuf = new char[nFileSize1+1];
	desBuf = new char[nFileSize2+1];

	memset(srcBuf, 0, nFileSize1+1);
	memset(desBuf, 0, nFileSize2+1);

	nLen1 = fread(srcBuf, 1, nFileSize1, fp1);

	ChangeAscHex(srcBuf, desBuf, nFileSize1);

	nLen2 = fwrite(desBuf, 1, nFileSize2, fp2);


	delete srcBuf;
	srcBuf = NULL;
	delete desBuf;
	desBuf = NULL;

	fclose(fp1);
	fp1 = NULL;
	fclose(fp2);
	fp2 = NULL;

	//3.删除原文件
	if (bSaveTmpFile == 0)
	{
		ret = DeleteFile(strTmp.GetBuffer(0));
		if (ret == 0)
		{
			str.Format( _T("Error:DeleteFile, ret=%d, \r\n srcName=%s,"), ret, strTmp);
			AfxMessageBox(str);
			return 0;
		}

		memset(m_szTmpFile, 0, MAX_PATH);
	}
	return 1;
}