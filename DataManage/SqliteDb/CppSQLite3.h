////////////////////////////////////////////////////////////////////////////////
// CppSQLite3 - A C++ wrapper around the SQLite3 embedded database library.
//
// Copyright (c) 2004..2007 Rob Groves. All Rights Reserved. rob.groves@btinternet.com
// 
// Permission to use, copy, modify, and distribute this software and its
// documentation for any purpose, without fee, and without a written
// agreement, is hereby granted, provided that the above copyright notice, 
// this paragraph and the following two paragraphs appear in all copies, 
// modifications, and distributions.
//
// IN NO EVENT SHALL THE AUTHOR BE LIABLE TO ANY PARTY FOR DIRECT,
// INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST
// PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION,
// EVEN IF THE AUTHOR HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// THE AUTHOR SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
// PARTICULAR PURPOSE. THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF
// ANY, PROVIDED HEREUNDER IS PROVIDED "AS IS". THE AUTHOR HAS NO OBLIGATION
// TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
//
// V3.0		03/08/2004	-Initial Version for sqlite3
//
// V3.1		16/09/2004	-Implemented getXXXXField using sqlite3 functions
//						-Added CppSQLiteDB3::tableExists()
//
// V3.2		01/07/2005	-Fixed execScalar to handle a NULL result
//			12/07/2007	-Added CppSQLiteDB::IsAutoCommitOn()
//						-Added int64 functions to CppSQLite3Query
//						-Added Name based parameter binding to CppSQLite3Statement.
////////////////////////////////////////////////////////////////////////////////
#ifndef _CppSQLite3_H_
#define _CppSQLite3_H_

#include "sqlite3.h"
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

#define CPPSQLITE_ERROR 1000

class CppSQLite3Exception
{
public:

    CppSQLite3Exception(const int nErrCode,
                    char* szErrMess,
                    bool bDeleteMsg=true);

    CppSQLite3Exception(const CppSQLite3Exception&  e);

    virtual ~CppSQLite3Exception();

    const int errorCode() { return mnErrCode; }

    const char* errorMessage() { return mpszErrMess; }

    static const char* errorCodeAsString(int nErrCode);

private:

    int mnErrCode;
    char* mpszErrMess;
};


class CppSQLite3Buffer
{
public:

    CppSQLite3Buffer();

    ~CppSQLite3Buffer();

    const char* format(const char* szFormat, ...);

    operator const char*() { return mpBuf; }

    void clear();

private:

    char* mpBuf;
};


class CppSQLite3Binary
{
public:

    CppSQLite3Binary();

    ~CppSQLite3Binary();

    void setBinary(const unsigned char* pBuf, int nLen);
    void setEncoded(const unsigned char* pBuf);

    const unsigned char* getEncoded();
    const unsigned char* getBinary();

    int getBinaryLength();

    unsigned char* allocBuffer(int nLen);

    void clear();

private:

    unsigned char* mpBuf;
    int mnBinaryLen;
    int mnBufferLen;
    int mnEncodedLen;
    bool mbEncoded;
};


class CppSQLite3Query
{
public:

    CppSQLite3Query();

    CppSQLite3Query(const CppSQLite3Query& rQuery);

    CppSQLite3Query(sqlite3* pDB,
				sqlite3_stmt* pVM,
                bool bEof,
                bool bOwnVM=true);

    CppSQLite3Query& operator=(const CppSQLite3Query& rQuery);

    virtual ~CppSQLite3Query();

    int numFields();

    int fieldIndex(const char* szField);
    const char* fieldName(int nCol);

    const char* fieldDeclType(int nCol);
    int fieldDataType(int nCol);

    const char* fieldValue(int nField);
    const char* fieldValue(const char* szField);

    int getIntField(int nField, int nNullValue=0);
    int getIntField(const char* szField, int nNullValue=0);

	sqlite_int64 getInt64Field(int nField, sqlite_int64 nNullValue=0);
	sqlite_int64 getInt64Field(const char* szField, sqlite_int64 nNullValue=0);

    double getFloatField(int nField, double fNullValue=0.0);
    double getFloatField(const char* szField, double fNullValue=0.0);

    const char* getStringField(int nField, const char* szNullValue="");
    const char* getStringField(const char* szField, const char* szNullValue="");

    const unsigned char* getBlobField(int nField, int& nLen);
    const unsigned char* getBlobField(const char* szField, int& nLen);

	bool fieldIsNull(int nField);
    bool fieldIsNull(const char* szField);

    bool eof();

    void nextRow();

    void finalize();

private:

    void checkVM();

	sqlite3* mpDB;
    sqlite3_stmt* mpVM;
    bool mbEof;
    int mnCols;
    bool mbOwnVM;
};


/******************************************************************************
���ܣ������ṩ�˲�ѯ�������
	
	  �ṩ�����ַ��ʵ�ǰ�е�ָ����ķ�ʽ
		1.�ֶκ�
		2.�ֶ���
********************************************************************************/
class CppSQLite3Table
{
public:
//���캯��
    CppSQLite3Table();	
    CppSQLite3Table(const CppSQLite3Table& rTable);
    CppSQLite3Table(char** paszResults, int nRows, int nCols);
    virtual ~CppSQLite3Table();

//��ֵ������
    CppSQLite3Table& operator=(const CppSQLite3Table& rTable);

//����
    int numFields();//�������
    int numRows();	//�������

//����
    void setRow(int nRow);	//����Ҫ�ĺ���,���Ƽ�¼�еĵ�ǰλ��
    const char* fieldName(int nCol);	//�õ�ָ���е��ֶ���

    const char* fieldValue(int nField);	//�õ���ǰ�е�ָ���е�ֵ
    const char* fieldValue(const char* szField);

    int getIntField(int nField, int nNullValue=0);
    int getIntField(const char* szField, int nNullValue=0);

    double getFloatField(int nField, double fNullValue=0.0);
    double getFloatField(const char* szField, double fNullValue=0.0);

    const char* getStringField(int nField, const char* szNullValue="");
    const char* getStringField(const char* szField, const char* szNullValue="");

    bool fieldIsNull(int nField);	//�жϵ�ǰ�е�ָ�����Ƿ�Ϊ��
    bool fieldIsNull(const char* szField);


    void finalize();
private:
	int mnCurrentRow;	

    void checkResults();

    int mnCols;
    int mnRows;
    char** mpaszResults;
};


class CppSQLite3Statement
{
public:

    CppSQLite3Statement();

    CppSQLite3Statement(const CppSQLite3Statement& rStatement);

    CppSQLite3Statement(sqlite3* pDB, sqlite3_stmt* pVM);

    virtual ~CppSQLite3Statement();

    CppSQLite3Statement& operator=(const CppSQLite3Statement& rStatement);

    int execDML();

    CppSQLite3Query execQuery();

    void bind(int nParam, const char* szValue);
    void bind(int nParam, const int nValue);
    void bind(int nParam, const double dwValue);
    void bind(int nParam, const unsigned char* blobValue, int nLen);
    void bindNull(int nParam);

	int bindParameterIndex(const char* szParam);
    void bind(const char* szParam, const char* szValue);
    void bind(const char* szParam, const int nValue);
    void bind(const char* szParam, const double dwValue);
    void bind(const char* szParam, const unsigned char* blobValue, int nLen);
    void bindNull(const char* szParam);

	void reset();

    void finalize();

private:

    void checkDB();
    void checkVM();

    sqlite3* mpDB;
    sqlite3_stmt* mpVM;
};

typedef struct _ReadBolbStr{
	int nLen;//���ݳ���//
	char *nData;//������Ϣ//
}ReadBlobStr;
class CppSQLite3DB
{
public:
//���캯��
    CppSQLite3DB();				//��ʼ���ڲ�����
    virtual ~CppSQLite3DB();    //�ͷ����ݣ��ر����ݿ�����

//��������
    void open(const char* szFile);//�����ݿ��Ψһ���
    void close();				  //�ر����ݿ��Ψһ���
	void interrupt() { sqlite3_interrupt(mpDB); }

    int execDML(const char* szSQL);						//�������ݱ��ڱ����ĵļ�¼���������룬ɾ�����޸ģ�			
	int execScalar(const char* szSQL, int nNullValue=0); //������ѯ

    
	CppSQLite3Query execQuery(const char* szSQL);
    CppSQLite3Table getTable(const char* szSQL);		//���ز�ѯ��
    CppSQLite3Statement compileStatement(const char* szSQL);

 
//�ศ������
    static const char* SQLiteVersion() { return SQLITE_VERSION; }
    static const char* SQLiteHeaderVersion() { return SQLITE_VERSION; }
    static const char* SQLiteLibraryVersion() { return sqlite3_libversion(); }
    static int SQLiteLibraryVersionNumber() { return sqlite3_libversion_number(); }

//����
	bool IsAutoCommitOn();		
	void setBusyTimeout(int nMillisecs);
	sqlite_int64 lastRowId();				//��������¼��ID������޲��붯���򷵻�0
	bool tableExists(const char* szTable);	//ָ�����Ƿ����

public:
	//Sqlite blob����д��//
	int SqliteWriteBolb(char *szSQL,char *Data,int len);
	//Sqlite blob���Ͷ�ȡ//
	int GetBolbBytes(char *szSQL,int &len);
	int SqliteReadBolb(char *szSQL,char **Data,int &len);
	int SqliteReadBolb(char *szSQL,vector<void *> &ArrayData /*ReadBlobStr** ArrayData*/,int &nCount);
	 sqlite3* mpDB;
private:
	//��ֹ���ƹ����븳ֵ����
    CppSQLite3DB(const CppSQLite3DB& db);
    CppSQLite3DB& operator=(const CppSQLite3DB& db);

    sqlite3_stmt* compile(const char* szSQL);

	//������ݿ��Ƿ��
    void checkDB();

   
    int mnBusyTimeoutMs;
};


#endif
