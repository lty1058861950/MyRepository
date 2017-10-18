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

                                        �������˵��



1.��Ʒģ�飺
	��ԴID                      ����                     ����˵��
	
	IDD_PRODMNG_DLG             CProdMng                 �����Ի���
	IDD_PRODUCT_BTN_DLG         CProductFuction          ���ܲ����Ի���    ��  ɾ  �ĵ�
	IDD_PRODUCT_INFO_DLG        CProductInfo             ������ʾ��Ʒ�Ļ�����Ϣ
	IDD_PRODUCT_PICNUM_DLG      CProductPicNum           ��Ʒ��ͼ�Ź�����棨Ŀǰ�����Σ�
	IDD_PRODUCT_SEARCH_DLG      CProductSearch           ���ò�Ʒ��ѯ��Ϣ�Ի���
	IDD_SEL_DLG                 CSelDlg                  ��Ʒ�Զ������öԻ���()
	IDD_SEL_PRODUCT_DLG         CSelProductDlg           ��Ʒѡ��Ի���


2.ģ��ģ�飺
	��ԴID                      ����                     ����˵��
	
	IDD_MODEMNG_DLG             CModeMng                 �����Ի��� 
	IDD_MODE_BTN_DLG            CModeFuction             ���ܲ����Ի���    ��  ɾ  �ĵ�
	IDD_MODE_SEARCH_BTN         CModeSearch              ����ģ���ѯ��Ϣ�Ի���
	IDD_SHOWMODEINFO_DLG        CShowModeInfo            ������ʾģ��Ļ�����Ϣ
	IDD_SHOWMODESTYLE_DLG       CShowModeStyle           ��ʾģ��ı����ʽ
	IDD_INPUT_NAME_DLG          CInPutName               �����Ҽ����ģ�壬ģ������¼��Ի���
	IDD_MODE_LOAD_DLG           CDlgMdLoadIn             ����ģ��·��ѡ��Ի���(��PAD��ֲ��)
	IDD_SHOWMODEPAR_DLG         CDlgParMng               ģ��������öԻ�(��PAD��ֲ�����޸���Ҫ��PADͬ��)
	
3.����ģ�飺
	��ԴID                      ����                     ����˵��
	
	IDD_TASK_MNG_DLG            CTaskMng                 �����Ի���    
	IDD_TASK_BTN_DLG            CTaskFuction             ���ܲ����Ի���    ��  ɾ  �ĵ�
	IDD_TASK_SEARCH_DLG         CTaskSearch              ���������ѯ��Ϣ�Ի��� 
	IDD_SHOWTASKINFO_DLG        CShowTaskInfo            ������ʾ����Ļ�����Ϣ
	IDD_TASK_CFG_DLG            CTaskCfg                 �����������Ϣ��չʾ
	IDD_TASK_MODE_DLG           CTaskModeMng             ������ѡģ�������
	IDD_TASK_NUMBEL_DLG         CTaskNumbelMng           �����Ʒ��ŵ�����
	IDD_TASK_PICNUM_DLG         CTaskPicNum              �����Ʒͼ�ŵ�����
	IDD_SHOWTASKDATA_DLG        CShowTaskData            ������ϸ���Ԥ��
	
	
4.�����·����ϴ�ģ�飺
	��ԴID                      ����                     ����˵��
	
	IDD_TASK_OUT_IN_DLG         CTaskDownUpLoad          �����ϴ������������Ի���
	IDD_TASK_DOWNALL_DLG        CTaskDownLoadAll         �������ظ��˵�ȫ������
	IDD_TASK_DOWNSEL_DLG        CTaskDownLoadSel         ѡ���Ԥ��������
	IDD_TASK_UPLOAD_DLG         CTaskUpLoad              �����ϴ��Ի���
	       ��                   CBatchExportTask         ������������(�����)
	       ��                   CBatchImportData         ���������ϴ�(�����)

5.�����ѯģ��Ͳ�Ʒ�������ɣ�
	��ԴID                      ����                     ����˵��
	
	IDD_RESULT_SEARCH_DLG       CResultSearch            �ɵĽ����ѯ����(������)
	IDD_RESULT_SEARCH_NEW_DLG   CResultSearchNew         ���µĽ����ѯ����(������)
	IDD_RESULT_SEARCH_INFO_DLG  CResultSearchInfo        �����ѯ���������ý���
	IDD_RESULT_SHOW_DLG         CResultShow              ���չʾ�ĶԻ���

	IDD_ADJUSTMENT_DLG          CAdjustmentDlg           ��Ʒ��������˳����� ��
	    WordOptFun.h  WordOptFun.cpp                     ��Ʒ�������ɵ�ȫ�ֺ���    
6.��Ʒ֤����ģ�飺
	��ԴID                      ����                     ����˵��

	IDD_TESTIMONIAL_MNG_DLG     CTestimonialMng          ����֤���������Ի���
	IDD_TESTIMONIAL_PAGE1_DLG   CTestimonialPage1        ��һҳ����
	IDD_TESTIMONIAL_PAGE2_DLG   CTestimonialPage2        �ڶ�ҳ����
	IDD_TESTIMONIAL_PAGE3_DLG   CTestimonialPage3        ����ҳ����
	IDD_TESTIMONIAL_PAGE4_DLG   CTestimonialPage4        ����ҳ����
	IDD_TESTIMONIAL_PAGE5_DLG   CTestimonialPage5        ����ҳ���� 
	IDD_TESTIMONIAL_PAGE6_DLG   CTestimonialPage6        ����ҳ����
	IDD_TESTIMONIAL_PAGE7_DLG   CTestimonialPage7        ����ҳ����
	IDD_TESTIMONIAL_PAGE8_DLG   CTestimonialPage8        �ڰ�ҳ����
	IDD_TESTIMONIAL_PAGE9_DLG   CTestimonialPage9        �ھ�ҳ����
	IDD_TESTIMONIAL_PAGE10_DLG  CTestimonialPage10       ��ʮҳ����
	IDD_TESTIMONIAL_PAGE11_DLG  CTestimonialPage11       ��ʮһҳ����
	                                                     ��ʮ��ҳ����

