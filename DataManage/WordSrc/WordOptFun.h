#if !defined(AFX_WORDOPTFUN_H__INCLUDED_)
#define AFX_WORDOPTFUN_H__INCLUDED_
#define TitleFontSize  14   


//功能: 生成行可变模板报告
//参数: szSaveFileName, 保存结果文件
//返回：操作是否成功
//备注: 根据此函数改写,具体报告函数		
int WordOpt_MakeReportRowVarDemo(char *szSaveFileName);		
					
//功能: 根据报告模板,生成报告数据
//参数: szSrcModeTabFileName,	输入表格模板文件
//		szOutTabFileName,		输出表格结果文件
//返回：操作是否成功
//备注: 源文件，与目标文件不能相同。
int WordOpt_MakeTabModeToTabData(char *szSrcTabModeFileName, char *szOutTabDataFileName);


//功能: 根据报告数据, 生成报告信息列表。
//参数: szOutFileName,			输出表格信息文件(报括表格名，表格前和后描述信息)
//返回：操作是否成功		
//备注: 根据此函数改写,具体报告函数	
int WordOpt_MakeReportTabInfoDemo(char *szOutTabInfoFileName,char *szSrcTabDataFileName);

int WordOpt_MakeTestimonialDemo(char *szOutTabInfoFileName,CStringArray &szSrcTabDataFileName);//lty Add 2017-02-15


//功能：根据模板配置值，生成目标数据值
//参数：szSrcValue,		原始值
//		szDesValue，	目标值
//返回：操作是否成功
int global_GetSrcValueToDesValue(char *szSrcValue, char *szDesValue);

#endif // !defined(AFX_WORDOPTFUN_H__INCLUDED_)
