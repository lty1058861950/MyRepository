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
	typeDoDecry = 0,			//ִ�н��ܲ���
	typeDoEncrypt = 1,		    //ִ�м��ܲ���
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
	* ������DoFileEncryptOrDecry	�ļ��ӽ������ݴ���
	* ���룺szSrcFileName			ԭ�ļ�
	szDesFileName			Ŀ���ļ�
	bEnc					�Ƿ����			1:����, 0:����;
	* �����int					�����Ƿ�ɹ�
	* ˵��: �ļ����ܽ������ݴ���, ��ԭ�ļ����м��ܽ������ݴ��������Ŀ���ļ���
	*/
	int DoFileEncryptOrDecry( char *szSrcFileName, char *szDesFileName, bool bEnc);	//�ļ����������

	/*
	* ������DoFileEncryptOrDecry	�ļ��ӽ������ݴ���
	* ���룺szFileName				�ļ���
	bEnc					�Ƿ����			1:����, 0:����;
	bSaveTmpFIle			�Ƿ񱣴���ʱ�ļ�	1:����, 0:������ 
	* ���: int					�����Ƿ�ɹ�
	* ˵��: �ļ����ܽ������ݴ���, ��ԭ�ļ����мӽ��ܴ�����ԭ�ļ��� ��ʱ�ļ�����m_szTmpFile
	*/
	int DoFileEncryptOrDecry( char *szFileName, bool bEnc, bool bSaveTmpFile);       //���ļ����мӽ���

	/*
	* ����: DeleteTmpFile
	* ���룺�� 
	* ���: int					�����Ƿ�ɹ�
	* ˵��: ɾ����ʱ�ļ�����ʱ�ļ�����m_szTmpFile
	*/
	int DeleteTmpFile( );

	int DoFileHexToAsc(char *szFileName, int bSaveTmpFile = 0);                  //���ļ����д���_HexToAsc

	int DoFileAscToHex(char *szFileName, int bSaveTmpFile = 0);					 //���ļ����д���_AscToHex
};

#endif // !defined(AFX_DATAENCDEC_H__AFB0647A_889A_4FEC_9351_41F7ACB83C3F__INCLUDED_)
