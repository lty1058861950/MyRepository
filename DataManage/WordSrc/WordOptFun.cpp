#include "stdafx.h"
#include "WordOptFun.h"
#include "WordOffice.h"

int WordOpt_MakeReportRowVarDemo(char *szSaveFileName) 
{
	// TODO: Add your control notification handler code here

	int		i, j, pos, nCnt, nPageCnt;
	int     nTabOrd, ret;
	int     nPicPos, nDataPos;
	CWordOffice wd;	//����һ������word�Ķ���
		
	CString str;

	if (strlen(szSaveFileName) == 0)
	{
		str.Format("�ļ�������Ϊ��!");
		AfxMessageBox(str);
		return FALSE;
	}

	ret = wd.Create(); //����һ��wordӦ�ó�������һ���ĵ�
	if (ret == FALSE)
	{
		return FALSE;
	}

	nPageCnt = 1;
	for (i=1; i<=nPageCnt; i++)	  
	{
		wd.SetFont("����", 25 ,RGB(0, 0, 0), 0); //��������(�ֺţ�����������ɫ)
		wd.SetFont(1,0,0);						//��������Ϊ���壬����б�壬û���»���

		wd.SetParaphformat(1);					//��������Ϊ���ж���

		str.Format(_T("%s"),g_pCurAttaInfo->szModeName);
		wd.WriteText(str);	//д����
		wd.m_wdSel.TypeParagraph();				//�س�����

		wd.SetFont(0,0,0);
		wd.SetFont("����", 12 ,RGB(0, 0, 0), 0);
		wd.SetParaphformat(0);			//��������Ϊ[0.�����,1.���У�2.�Ҷ���]

		str.Format(_T("��Ʒ����:%-20s    ��Ʒ���:%s"),g_pCurAttaInfo->szProductNo,g_pCurAttaInfo->szProductCode);

		wd.WriteText(str);	//д����
		wd.m_wdSel.TypeParagraph(); //�س�����

		//���ñ������ 
		wd.SetFont("����", 12, RGB(0,0,0)); 
		wd.SetFont(1,0,0);
 
		wd.SetParaphformat(1); //��������ΪLEFT����

		wd.SetFont(0,0,0);
		
		nTabOrd = i;
		
		wd.CreateTable(nTabOrd,2,6); //����һ��2��4�еı��

		wd.SetTableFont(1,1,1,0,0);
		wd.SetTableFont(1,2,1,0,0);
		wd.SetTableFont(1,3,1,0,0);
		wd.SetTableFont(1,4,1,0,0);	
		wd.SetTableFont(1,5,1,0,0);
		wd.SetTableFont(1,6,1,0,0);

		wd.WriteCellText(1,1,"���"); //��1��1�е�Ԫд��ѧ�š�
		wd.WriteCellText(1,2,"ͼ��"); //��1��2�е�Ԫд��������
		wd.WriteCellText(1,3,"���"); //...
		wd.WriteCellText(1,4,"��ͨ");
		wd.WriteCellText(1,5,"��Ե");
		wd.WriteCellText(1,6,"����");

		wd.SetTableCellWidth(50, 1, 1);
		wd.SetTableCellWidth(90, 1, 2);

		nCnt = g_PicNum;
		nDataPos = 0;
		for (j=1; j<=nCnt; j++)
		{
			nPicPos = j-1;
			//1.
			str.Format("%d", j);
			wd.WriteCellText(j+1, 1, str);

			//2.
			str.Format("%s", g_pArryTaskPicNum->at(nPicPos)->szPicNumNo);
			wd.WriteCellText(j+1, 2, str);

			pos = 3;
			//3.
			str.Format(_T("%s"), g_pDataArray->GetAt(nDataPos++).Data);
			wd.WriteCellText(j+1, pos, str);
			pos++;

			//4.
			str.Format(_T("%s"),g_pDataArray->GetAt(nDataPos++).Data);
			wd.WriteCellText(j+1, pos, str);
			pos++;

			//5.
			str.Format(_T("%s"), g_pDataArray->GetAt(nDataPos++).Data);
			wd.WriteCellText(j+1, pos, str);
			pos++;

			//6.
			str.Format(_T("%s"), g_pDataArray->GetAt(nDataPos++).Data);
			wd.WriteCellText(j+1, pos, str);
			pos++;

			if (j != nCnt)
			{
				wd.InsertTableNewRow();
			}
		}
 
		CComVariant varUnit(1), varCount(1), varExtend(0);
		wd.m_wdSel.MoveRight(&varUnit, &varCount, &varExtend);	//���ƹ��
   
		wd.WriteText("������:         �����:            ������:     "); //д����
		wd.SetParaphformat(0);			//��������Ϊ[0.�����,1.���У�2.�Ҷ���]
   
		//wd.m_wdSel.TypeParagraph();				//�س�����

		if (i != nPageCnt)
		{
			//wd.m_wdSel.TypeParagraph();				//�س�����
			wd.m_wdSel.InsertBreak(COleVariant((long)0));//�����ҳ��
		}
	}

	ret = wd.SaveDocumentAs( szSaveFileName );
	if (ret == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL InTableProc( IN OfficeWord11:: Table& _wordTableObj )
{
	BOOL bStatus = FALSE;
	LONG nCounter = 1;
	LONG nCellConter = 0;
	LONG nCase = 0;
	LONG nStrLength = 0;
	CString strTitle;
	CString strTemp;
	CString strTransferValue;
	
	OfficeWord11::Rows wordRows;
	OfficeWord11::Cell wordCell;
	OfficeWord11::Cells wordCells;
	OfficeWord11::Range wordRange;
	int  bFind;
	char szDesValue[500] = {0,};
	
	try {
		
		wordRange = _wordTableObj.GetRange();
		wordRows = wordRange.GetRows();
		bStatus = TRUE;
	}
	catch (...) {
		return bStatus;
	}
	
	wordCells = wordRange.GetCells();
	nCellConter = wordCells.GetCount();
	while (nCounter <= nCellConter) {
		wordCell = wordCells.Item(nCounter);
		wordRange = wordCell.GetRange();
		
		strTemp = wordRange.GetText();
		nStrLength = strTemp.GetLength();
        strTitle = strTemp.Left(nStrLength-2);
		
		/*
		* �滻��������
		*/	
		memset(szDesValue, 0, 500);
		bFind = global_GetSrcValueToDesValue(strTitle.GetBuffer(0), szDesValue);
		if (bFind != 0)
		{
			strTransferValue = szDesValue;	
		}
		else
		{
			strTransferValue = strTitle;
		}

		if (_T("") != strTransferValue) 
		{
			wordRange.SetText(strTransferValue);
		}
		
		nCounter++;
	}
	
	return bStatus;
}

int WordOpt_MakeTabModeToTabData(char *szSrcTabModeFileName, char *szOutTabDataFileName)
{
	int     ret;
	CString str;
	
	CWordOffice wd;
	int     bStatus = FALSE;

	str.Format("WordOpt_MakeTabModeToTabData��%d", 1);
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));
	
	if ( (strlen(szSrcTabModeFileName) == 0) || (strlen(szOutTabDataFileName) == 0) )
	{
		str.Format("Դ�ļ���Ŀ���ļ�����Ϊ��!");
		AfxMessageBox(str);
		return FALSE;
	}
	if ( (strcmp(szSrcTabModeFileName, szOutTabDataFileName) == 0) )
	{
		str.Format("Դ�ļ���Ŀ���ļ�������ͬ!");
		AfxMessageBox(str);
		return FALSE;
	}

	//if (-1 == _taccess(szSrcTabModeFileName, 0)) 
	if (0 == PubFun_IsFileExist(szSrcTabModeFileName))
	{	
		str.Format(_T("Դ�ļ�������, %s"), szSrcTabModeFileName);
		AfxMessageBox(str);
		return FALSE;
	}

	ret = CopyFile(szSrcTabModeFileName, szOutTabDataFileName, 0);

	if (ret == 0)
	{
		str.Format(_T("�ļ�����ʧ��, Դ�ļ�:%s, Ŀ���ļ�:%s"), 
					szSrcTabModeFileName,
					szOutTabDataFileName);
		AfxMessageBox(str);
		return FALSE;
	}
	
	ret = wd.Open(szOutTabDataFileName);
	if (ret == 0)
	{
		return FALSE;
	}


	str.Format("WordOpt_MakeTabModeToTabData��%d", 2);
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));


	LONG nCounter = 1;
	LONG nTableCounter = 0;
	BOOL bLoopStatus = TRUE;
	
	OfficeWord11::Table wordTable;
	
	try {
		wd.m_wdTables = wd.m_wdDoc.GetTables();
	}
	catch (...) {
		;
	}
	
	nTableCounter = wd.m_wdTables.GetCount()+1;
	while (bLoopStatus && nCounter < nTableCounter) 
	{
		wordTable = wd.m_wdTables.Item(nCounter);
		bLoopStatus = InTableProc(wordTable);
		if (!bLoopStatus) 
		{
			continue;
		}
		nCounter++;
	}

	str.Format("WordOpt_MakeTabModeToTabData��%d", 3);
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));

	wd.SaveDocument();

	str.Format("WordOpt_MakeTabModeToTabData��%d", 4);
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));

	//wd.CloseApp();
	str.Format("WordOpt_MakeTabModeToTabData��%d", 5);
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));


	return TRUE;
}


int WordOpt_MakeReportTabInfoDemo(char *szOutTabInfoFileName,char *szSrcTabDataFileName)
{
	int		i, j, pos, nCnt, nPageCnt;
	int     nTabOrd, ret;
	CWordOffice wd;	//����һ������word�Ķ���
	//char    szSrcTabDataFileName[100]={0,}; 
	OfficeWord11:: _Document   DocAcitve;
	OfficeWord11:: PageSetup   pageSetup;
	
	CString str;

	//strcpy(szSrcTabDataFileName, _T("c:\\t_Mode2.doc") )
	
	str.Format("WordOpt_MakeReportTabInfoDemo��%d", 1);
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));
	
	if (strlen(szOutTabInfoFileName) == 0)
	{
		str.Format("�ļ�������Ϊ��!");
		AfxMessageBox(str);
		return FALSE;
	}

	str.Format("WordOpt_MakeReportTabInfoDemo��%d", 2);
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));

	
	ret = wd.Create(); //����һ��wordӦ�ó�������һ���ĵ�
	if (ret == FALSE)
	{
		return FALSE;
	}
	

	DocAcitve = wd.m_wdApp.GetActiveDocument();
	pageSetup = DocAcitve.GetPageSetup();
	pageSetup.SetOrientation(g_PaperDirection);     //ҳ�淽��0.����, 1.����



	nPageCnt = 1;
	for (i=1; i<=nPageCnt; i++)	  
	{
		wd.SetFont("����", TitleFontSize ,RGB(0, 0, 0), 0); //��������(�ֺţ�����������ɫ)
		wd.SetFont(0,0,0);						//��������Ϊ���壬����б�壬û���»���
		
		wd.SetParaphformat(1);					//��������Ϊ���ж���
		str.Format(_T("%s"),g_pCurAttaInfo->szModeName);
		wd.WriteText(str);	//д����
		wd.m_wdSel.TypeParagraph();				//�س�����
		
		wd.SetFont(0,0,0);
		wd.SetFont("����", 12 ,RGB(0, 0, 0), 0);
		wd.SetParaphformat(0);			//��������Ϊ[0.�����,1.���У�2.�Ҷ���]

		str.Format(_T("��Ʒ����:%-20s ��Ʒ���:%s"),g_pCurAttaInfo->szProductNo,g_pCurAttaInfo->szProductCode);
		wd.WriteText(str);	//д����
		//wd.m_wdSel.TypeParagraph(); //�س�����	
		
		wd.InsertFile(szSrcTabDataFileName);

		CComVariant varUnit(1), varCount(1), varExtend(0);
		//wd.m_wdSel.MoveLeft(&varUnit, &varCount, &varExtend);	//���ƹ��
		wd.m_wdSel.Delete(&varUnit, &varCount);
		
		wd.SetFont(0,0,0);
		wd.SetFont("����", 12 ,RGB(0, 0, 0), 0);
		wd.WriteText("������:         �����:            ������:     "); //д����
		wd.SetParaphformat(0);			//��������Ϊ[0.�����,1.���У�2.�Ҷ���]
		//wd.m_wdSel.TypeParagraph();				//�س�����
	}

	str.Format("WordOpt_MakeReportTabInfoDemo��%d", 3);
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));


	ret = wd.SaveDocumentAs( szOutTabInfoFileName );
	if (ret == FALSE)
	{
		return FALSE;
	}

	str.Format("WordOpt_MakeReportTabInfoDemo��%d", 4);
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));


	return TRUE;
}


int WordOpt_MakeTestimonialDemo(char *szOutTabInfoFileName,CStringArray &szSrcTabDataFileName)
{
	int		i, j, pos, nCnt, nPageCnt;
	int     nTabOrd, ret;
	CWordOffice wd;	//����һ������word�Ķ���
	//char    szSrcTabDataFileName[100]={0,}; 
	OfficeWord11:: _Document   DocAcitve;
	OfficeWord11:: PageSetup   pageSetup;

	CString str;

	//strcpy(szSrcTabDataFileName, _T("c:\\t_Mode2.doc") );

	if (strlen(szOutTabInfoFileName) == 0)
	{
		str.Format("�ļ�������Ϊ��!");
		AfxMessageBox(str);
		return FALSE;
	}

	ret = wd.Create(); //����һ��wordӦ�ó�������һ���ĵ�
	if (ret == FALSE)
	{
		return FALSE;
	}

	DocAcitve = wd.m_wdApp.GetActiveDocument();
	pageSetup = DocAcitve.GetPageSetup();
	pageSetup.SetOrientation(g_PaperDirection);     //ҳ�淽��0.����, 1.����


	nPageCnt = szSrcTabDataFileName.GetCount();
	for (i=0; i<nPageCnt; i++)	  
	{
		wd.InsertFile(szSrcTabDataFileName.GetAt(i));

		CComVariant varUnit(1), varCount(1), varExtend(0);
		//wd.m_wdSel.MoveLeft(&varUnit, &varCount, &varExtend);	//���ƹ��
		wd.m_wdSel.Delete(&varUnit, &varCount);

		if (i < nPageCnt-1)
		{
			//wd.m_wdSel.TypeParagraph();				//�س�����
			wd.m_wdSel.InsertBreak(COleVariant((long)0));//�����ҳ��
		}
		remove(szSrcTabDataFileName.GetAt(i));
	}

	ret = wd.SaveDocumentAs( szOutTabInfoFileName );
	if (ret == FALSE)
	{
		return FALSE;
	}


	return TRUE;
}



int global_GetSrcValueToDesValue(char *szSrcValue, char *szDesValue)
{
	CString str, strDes;
	int     nLen = 0, nVal=0, nCount = 0;
	char    buf[10] = {0,};
	int     bFlag = FALSE;

	if (szSrcValue == NULL)
	{
		return FALSE;
	}

	if (strlen(szSrcValue) == 0)
	{
		return FALSE;
	}

	str = szSrcValue;
	str.TrimLeft();
	str.TrimRight();
	
	nLen = str.GetLength();

	if (nLen <= 4)
	{
		strcpy(buf, str.GetBuffer(0));
		if ( (buf[0] == 'D') || (buf[0] == 'd') )
		{
			nVal = atoi( (char*)(buf+1) );
			if (nVal >= 1)
			{
				nCount = g_pDataArray->GetCount();
				if(nVal>=1 && nVal<=nCount)
				{
					strDes = g_pDataArray->GetAt(nVal-1).Data;
					strcpy(szDesValue, strDes.GetBuffer(0));
					bFlag = TRUE;
				}
				
			}			
		}
	}

	return bFlag;
}