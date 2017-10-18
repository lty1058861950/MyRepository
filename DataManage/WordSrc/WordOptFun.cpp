#include "stdafx.h"
#include "WordOptFun.h"
#include "WordOffice.h"

int WordOpt_MakeReportRowVarDemo(char *szSaveFileName) 
{
	// TODO: Add your control notification handler code here

	int		i, j, pos, nCnt, nPageCnt;
	int     nTabOrd, ret;
	int     nPicPos, nDataPos;
	CWordOffice wd;	//定义一个操作word的对象
		
	CString str;

	if (strlen(szSaveFileName) == 0)
	{
		str.Format("文件名不能为空!");
		AfxMessageBox(str);
		return FALSE;
	}

	ret = wd.Create(); //创建一个word应用程序增加一个文档
	if (ret == FALSE)
	{
		return FALSE;
	}

	nPageCnt = 1;
	for (i=1; i<=nPageCnt; i++)	  
	{
		wd.SetFont("宋体", 25 ,RGB(0, 0, 0), 0); //设置字体(字号，字体名，颜色)
		wd.SetFont(1,0,0);						//设置字体为粗体，不是斜体，没有下划线

		wd.SetParaphformat(1);					//设置文字为居中对齐

		str.Format(_T("%s"),g_pCurAttaInfo->szModeName);
		wd.WriteText(str);	//写文字
		wd.m_wdSel.TypeParagraph();				//回车换行

		wd.SetFont(0,0,0);
		wd.SetFont("宋体", 12 ,RGB(0, 0, 0), 0);
		wd.SetParaphformat(0);			//设置文字为[0.左对齐,1.居中，2.右对齐]

		str.Format(_T("产品代号:%-20s    产品编号:%s"),g_pCurAttaInfo->szProductNo,g_pCurAttaInfo->szProductCode);

		wd.WriteText(str);	//写文字
		wd.m_wdSel.TypeParagraph(); //回车换行

		//设置表格字体 
		wd.SetFont("宋体", 12, RGB(0,0,0)); 
		wd.SetFont(1,0,0);
 
		wd.SetParaphformat(1); //设置文字为LEFT对齐

		wd.SetFont(0,0,0);
		
		nTabOrd = i;
		
		wd.CreateTable(nTabOrd,2,6); //创建一个2行4列的表格

		wd.SetTableFont(1,1,1,0,0);
		wd.SetTableFont(1,2,1,0,0);
		wd.SetTableFont(1,3,1,0,0);
		wd.SetTableFont(1,4,1,0,0);	
		wd.SetTableFont(1,5,1,0,0);
		wd.SetTableFont(1,6,1,0,0);

		wd.WriteCellText(1,1,"序号"); //往1行1列单元写“学号”
		wd.WriteCellText(1,2,"图号"); //往1行2列单元写“姓名”
		wd.WriteCellText(1,3,"外观"); //...
		wd.WriteCellText(1,4,"导通");
		wd.WriteCellText(1,5,"绝缘");
		wd.WriteCellText(1,6,"抗电");

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
		wd.m_wdSel.MoveRight(&varUnit, &varCount, &varExtend);	//右移光标
   
		wd.WriteText("测试者:         检测验:            军代表:     "); //写文字
		wd.SetParaphformat(0);			//设置文字为[0.左对齐,1.居中，2.右对齐]
   
		//wd.m_wdSel.TypeParagraph();				//回车换行

		if (i != nPageCnt)
		{
			//wd.m_wdSel.TypeParagraph();				//回车换行
			wd.m_wdSel.InsertBreak(COleVariant((long)0));//插入分页符
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
		* 替换查找内容
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

	str.Format("WordOpt_MakeTabModeToTabData：%d", 1);
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));
	
	if ( (strlen(szSrcTabModeFileName) == 0) || (strlen(szOutTabDataFileName) == 0) )
	{
		str.Format("源文件或目标文件不能为空!");
		AfxMessageBox(str);
		return FALSE;
	}
	if ( (strcmp(szSrcTabModeFileName, szOutTabDataFileName) == 0) )
	{
		str.Format("源文件或目标文件不能相同!");
		AfxMessageBox(str);
		return FALSE;
	}

	//if (-1 == _taccess(szSrcTabModeFileName, 0)) 
	if (0 == PubFun_IsFileExist(szSrcTabModeFileName))
	{	
		str.Format(_T("源文件不存在, %s"), szSrcTabModeFileName);
		AfxMessageBox(str);
		return FALSE;
	}

	ret = CopyFile(szSrcTabModeFileName, szOutTabDataFileName, 0);

	if (ret == 0)
	{
		str.Format(_T("文件复制失败, 源文件:%s, 目标文件:%s"), 
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


	str.Format("WordOpt_MakeTabModeToTabData：%d", 2);
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

	str.Format("WordOpt_MakeTabModeToTabData：%d", 3);
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));

	wd.SaveDocument();

	str.Format("WordOpt_MakeTabModeToTabData：%d", 4);
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));

	//wd.CloseApp();
	str.Format("WordOpt_MakeTabModeToTabData：%d", 5);
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));


	return TRUE;
}


int WordOpt_MakeReportTabInfoDemo(char *szOutTabInfoFileName,char *szSrcTabDataFileName)
{
	int		i, j, pos, nCnt, nPageCnt;
	int     nTabOrd, ret;
	CWordOffice wd;	//定义一个操作word的对象
	//char    szSrcTabDataFileName[100]={0,}; 
	OfficeWord11:: _Document   DocAcitve;
	OfficeWord11:: PageSetup   pageSetup;
	
	CString str;

	//strcpy(szSrcTabDataFileName, _T("c:\\t_Mode2.doc") )
	
	str.Format("WordOpt_MakeReportTabInfoDemo：%d", 1);
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));
	
	if (strlen(szOutTabInfoFileName) == 0)
	{
		str.Format("文件名不能为空!");
		AfxMessageBox(str);
		return FALSE;
	}

	str.Format("WordOpt_MakeReportTabInfoDemo：%d", 2);
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));

	
	ret = wd.Create(); //创建一个word应用程序增加一个文档
	if (ret == FALSE)
	{
		return FALSE;
	}
	

	DocAcitve = wd.m_wdApp.GetActiveDocument();
	pageSetup = DocAcitve.GetPageSetup();
	pageSetup.SetOrientation(g_PaperDirection);     //页面方向：0.纵向, 1.横向



	nPageCnt = 1;
	for (i=1; i<=nPageCnt; i++)	  
	{
		wd.SetFont("宋体", TitleFontSize ,RGB(0, 0, 0), 0); //设置字体(字号，字体名，颜色)
		wd.SetFont(0,0,0);						//设置字体为粗体，不是斜体，没有下划线
		
		wd.SetParaphformat(1);					//设置文字为居中对齐
		str.Format(_T("%s"),g_pCurAttaInfo->szModeName);
		wd.WriteText(str);	//写文字
		wd.m_wdSel.TypeParagraph();				//回车换行
		
		wd.SetFont(0,0,0);
		wd.SetFont("宋体", 12 ,RGB(0, 0, 0), 0);
		wd.SetParaphformat(0);			//设置文字为[0.左对齐,1.居中，2.右对齐]

		str.Format(_T("产品代号:%-20s 产品编号:%s"),g_pCurAttaInfo->szProductNo,g_pCurAttaInfo->szProductCode);
		wd.WriteText(str);	//写文字
		//wd.m_wdSel.TypeParagraph(); //回车换行	
		
		wd.InsertFile(szSrcTabDataFileName);

		CComVariant varUnit(1), varCount(1), varExtend(0);
		//wd.m_wdSel.MoveLeft(&varUnit, &varCount, &varExtend);	//左移光标
		wd.m_wdSel.Delete(&varUnit, &varCount);
		
		wd.SetFont(0,0,0);
		wd.SetFont("宋体", 12 ,RGB(0, 0, 0), 0);
		wd.WriteText("测试者:         检测验:            军代表:     "); //写文字
		wd.SetParaphformat(0);			//设置文字为[0.左对齐,1.居中，2.右对齐]
		//wd.m_wdSel.TypeParagraph();				//回车换行
	}

	str.Format("WordOpt_MakeReportTabInfoDemo：%d", 3);
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));


	ret = wd.SaveDocumentAs( szOutTabInfoFileName );
	if (ret == FALSE)
	{
		return FALSE;
	}

	str.Format("WordOpt_MakeReportTabInfoDemo：%d", 4);
	g_pLogInfo->WriteLogFile(str.GetBuffer(0));


	return TRUE;
}


int WordOpt_MakeTestimonialDemo(char *szOutTabInfoFileName,CStringArray &szSrcTabDataFileName)
{
	int		i, j, pos, nCnt, nPageCnt;
	int     nTabOrd, ret;
	CWordOffice wd;	//定义一个操作word的对象
	//char    szSrcTabDataFileName[100]={0,}; 
	OfficeWord11:: _Document   DocAcitve;
	OfficeWord11:: PageSetup   pageSetup;

	CString str;

	//strcpy(szSrcTabDataFileName, _T("c:\\t_Mode2.doc") );

	if (strlen(szOutTabInfoFileName) == 0)
	{
		str.Format("文件名不能为空!");
		AfxMessageBox(str);
		return FALSE;
	}

	ret = wd.Create(); //创建一个word应用程序增加一个文档
	if (ret == FALSE)
	{
		return FALSE;
	}

	DocAcitve = wd.m_wdApp.GetActiveDocument();
	pageSetup = DocAcitve.GetPageSetup();
	pageSetup.SetOrientation(g_PaperDirection);     //页面方向：0.纵向, 1.横向


	nPageCnt = szSrcTabDataFileName.GetCount();
	for (i=0; i<nPageCnt; i++)	  
	{
		wd.InsertFile(szSrcTabDataFileName.GetAt(i));

		CComVariant varUnit(1), varCount(1), varExtend(0);
		//wd.m_wdSel.MoveLeft(&varUnit, &varCount, &varExtend);	//左移光标
		wd.m_wdSel.Delete(&varUnit, &varCount);

		if (i < nPageCnt-1)
		{
			//wd.m_wdSel.TypeParagraph();				//回车换行
			wd.m_wdSel.InsertBreak(COleVariant((long)0));//插入分页符
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