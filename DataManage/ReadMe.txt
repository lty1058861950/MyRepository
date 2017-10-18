========================================================================
       MICROSOFT FOUNDATION CLASS LIBRARY : DataManage
========================================================================


AppWizard has created this DataManage application for you.  This application
not only demonstrates the basics of using the Microsoft Foundation classes
but is also a starting point for writing your application.

This file contains a summary of what you will find in each of the files that
make up your DataManage application.

DataManage.dsp
    This file (the project file) contains information at the project level and
    is used to build a single project or subproject. Other users can share the
    project (.dsp) file, but they should export the makefiles locally.

DataManage.h
    This is the main header file for the application.  It includes other
    project specific headers (including Resource.h) and declares the
    CDataManageApp application class.

DataManage.cpp
    This is the main application source file that contains the application
    class CDataManageApp.

DataManage.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
	Visual C++.

DataManage.clw
    This file contains information used by ClassWizard to edit existing
    classes or add new classes.  ClassWizard also uses this file to store
    information needed to create and edit message maps and dialog data
    maps and to create prototype member functions.

res\DataManage.ico
    This is an icon file, which is used as the application's icon.  This
    icon is included by the main resource file DataManage.rc.

res\DataManage.rc2
    This file contains resources that are not edited by Microsoft 
	Visual C++.  You should place all resources not editable by
	the resource editor in this file.



/////////////////////////////////////////////////////////////////////////////

For the main frame window:

MainFrm.h, MainFrm.cpp
    These files contain the frame class CMainFrame, which is derived from
    CFrameWnd and controls all SDI frame features.

res\Toolbar.bmp
    This bitmap file is used to create tiled images for the toolbar.
    The initial toolbar and status bar are constructed in the CMainFrame
    class. Edit this toolbar bitmap using the resource editor, and
    update the IDR_MAINFRAME TOOLBAR array in DataManage.rc to add
    toolbar buttons.
/////////////////////////////////////////////////////////////////////////////

AppWizard creates one document type and one view:

DataManageDoc.h, DataManageDoc.cpp - the document
    These files contain your CDataManageDoc class.  Edit these files to
    add your special document data and to implement file saving and loading
    (via CDataManageDoc::Serialize).

DataManageView.h, DataManageView.cpp - the view of the document
    These files contain your CDataManageView class.
    CDataManageView objects are used to view CDataManageDoc objects.



/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named DataManage.pch and a precompiled types file named StdAfx.obj.

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Visual C++ reads and updates this file.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

If your application uses MFC in a shared DLL, and your application is 
in a language other than the operating system's current language, you
will need to copy the corresponding localized resources MFC42XXX.DLL
from the Microsoft Visual C++ CD-ROM onto the system or system32 directory,
and rename it to be MFCLOC.DLL.  ("XXX" stands for the language abbreviation.
For example, MFC42DEU.DLL contains resources translated to German.)  If you
don't do this, some of the UI elements of your application will remain in the
language of the operating system.

/////////////////////////////////////////////////////////////////////////////

                                        软件开发说明



1.产品模块：
	资源ID                      类名                     描述说明
	
	IDD_PRODMNG_DLG             CProdMng                 主父对话框
	IDD_PRODUCT_BTN_DLG         CProductFuction          功能操作对话框    增  删  改等
	IDD_PRODUCT_INFO_DLG        CProductInfo             用来显示产品的基础信息
	IDD_PRODUCT_PICNUM_DLG      CProductPicNum           产品的图号管理界面（目前已屏蔽）
	IDD_PRODUCT_SEARCH_DLG      CProductSearch           配置产品查询信息对话框
	IDD_SEL_DLG                 CSelDlg                  产品自定义配置对话框()
	IDD_SEL_PRODUCT_DLG         CSelProductDlg           产品选择对话框


2.模板模块：
	资源ID                      类名                     描述说明
	
	IDD_MODEMNG_DLG             CModeMng                 主父对话框 
	IDD_MODE_BTN_DLG            CModeFuction             功能操作对话框    增  删  改等
	IDD_MODE_SEARCH_BTN         CModeSearch              配置模板查询信息对话框
	IDD_SHOWMODEINFO_DLG        CShowModeInfo            用来显示模板的基础信息
	IDD_SHOWMODESTYLE_DLG       CShowModeStyle           显示模板的表格样式
	IDD_INPUT_NAME_DLG          CInPutName               树上右键添加模板，模板名称录入对话框
	IDD_MODE_LOAD_DLG           CDlgMdLoadIn             导入模板路径选择对话框(从PAD移植来)
	IDD_SHOWMODEPAR_DLG         CDlgParMng               模板参数配置对话(从PAD移植来，修改需要和PAD同步)
	
3.任务模块：
	资源ID                      类名                     描述说明
	
	IDD_TASK_MNG_DLG            CTaskMng                 主父对话框    
	IDD_TASK_BTN_DLG            CTaskFuction             功能操作对话框    增  删  改等
	IDD_TASK_SEARCH_DLG         CTaskSearch              配置任务查询信息对话框 
	IDD_SHOWTASKINFO_DLG        CShowTaskInfo            用来显示任务的基础信息
	IDD_TASK_CFG_DLG            CTaskCfg                 任务的配置信息的展示
	IDD_TASK_MODE_DLG           CTaskModeMng             任务所选模板的配置
	IDD_TASK_NUMBEL_DLG         CTaskNumbelMng           任务产品编号的配置
	IDD_TASK_PICNUM_DLG         CTaskPicNum              任务产品图号的配置
	IDD_SHOWTASKDATA_DLG        CShowTaskData            任务详细情况预览
	
	
4.任务下发和上传模块：
	资源ID                      类名                     描述说明
	
	IDD_TASK_OUT_IN_DLG         CTaskDownUpLoad          任务上传和下载主父对话框
	IDD_TASK_DOWNALL_DLG        CTaskDownLoadAll         任务下载个人的全部任务
	IDD_TASK_DOWNSEL_DLG        CTaskDownLoadSel         选择的预下载任务
	IDD_TASK_UPLOAD_DLG         CTaskUpLoad              任务上传对话框
	       无                   CBatchExportTask         任务批量下载(封的类)
	       无                   CBatchImportData         任务批量上传(封的类)

5.结果查询模块和产品报告生成：
	资源ID                      类名                     描述说明
	
	IDD_RESULT_SEARCH_DLG       CResultSearch            旧的结果查询界面(已屏蔽)
	IDD_RESULT_SEARCH_NEW_DLG   CResultSearchNew         最新的结果查询界面(主父框)
	IDD_RESULT_SEARCH_INFO_DLG  CResultSearchInfo        结果查询条件的配置界面
	IDD_RESULT_SHOW_DLG         CResultShow              结果展示的对话框

	IDD_ADJUSTMENT_DLG          CAdjustmentDlg           产品报告生成顺序调整 、
	    WordOptFun.h  WordOptFun.cpp                     产品报告生成的全局函数    
6.产品证明书模块：
	资源ID                      类名                     描述说明

	IDD_TESTIMONIAL_MNG_DLG     CTestimonialMng          生成证明书主父对话框
	IDD_TESTIMONIAL_PAGE1_DLG   CTestimonialPage1        第一页配置
	IDD_TESTIMONIAL_PAGE2_DLG   CTestimonialPage2        第二页配置
	IDD_TESTIMONIAL_PAGE3_DLG   CTestimonialPage3        第三页配置
	IDD_TESTIMONIAL_PAGE4_DLG   CTestimonialPage4        第四页配置
	IDD_TESTIMONIAL_PAGE5_DLG   CTestimonialPage5        第五页配置 
	IDD_TESTIMONIAL_PAGE6_DLG   CTestimonialPage6        第六页配置
	IDD_TESTIMONIAL_PAGE7_DLG   CTestimonialPage7        第七页配置
	IDD_TESTIMONIAL_PAGE8_DLG   CTestimonialPage8        第八页配置
	IDD_TESTIMONIAL_PAGE9_DLG   CTestimonialPage9        第九页配置
	IDD_TESTIMONIAL_PAGE10_DLG  CTestimonialPage10       第十页配置
	IDD_TESTIMONIAL_PAGE11_DLG  CTestimonialPage11       第十一页配置
	                                                     第十二页配置

