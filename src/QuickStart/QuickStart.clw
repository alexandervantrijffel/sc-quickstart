; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAddQSO
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "QuickStart.h"

ClassCount=18
Class1=CQuickStartApp
Class2=CQuickStartDlg
Class3=CAboutDlg

ResourceCount=25
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_QUICKSTART_DIALOG
Resource4=IDD_ADDQSO_TYPE (English (U.S.))
Resource5=IDR_QSOCONTEXT (English (U.K.))
Resource6=IDR_SYSTRAY
Resource7=IDD_SELECT_PROGRAM (English (U.S.))
Resource8=IDD_QUICKSTART_CONFIG (English (U.S.))
Resource9=IDD_TIP_MODIFYQSO (English (U.S.))
Resource10=IDD_ADDQSO_NAME (English (U.S.))
Resource11=IDD_ADDQSO_HOTKEY (English (U.S.))
Resource12=IDD_ADDQSO_HOTKEY_RECORD (English (U.S.))
Class4=CAddQSOFolder
Class5=CAddQSO
Class6=CAddQSOTask
Class7=CAddQSOType
Class8=CAddQSOSum
Class9=CAddQSOProgram
Class10=CAddQSOName
Resource13=IDD_REGISTER (English (U.S.))
Class11=CAddQSODoc
Resource14=IDD_ADDQSO_SUM (English (U.S.))
Class12=CAddQSOHotKey
Resource15=IDD_ABOUTBOX (English (U.S.))
Class13=CAddQSOHotKeyRecord
Resource16=IDD_TIP_DISPLAYRESOLUTION_TEST (English (U.S.))
Resource17=IDD_WELCOME (English (U.S.))
Class14=CConfigDlg
Resource18=IDD_ADDQSO_TASK (English (U.S.))
Resource19=IDD_ADDQSO_FOLDER (English (U.S.))
Class15=CSelectProgramDlg
Resource20=IDD_ADDQSO_PROGRAM (English (U.S.))
Class16=CWelcomeDlg
Resource21=IDD_TIP_DISPLAYRESOLUTION (English (U.S.))
Resource22=IDR_CTMENU (English (U.K.))
Class17=CTips
Class18=CRegisterDlg
Resource23=IDD_QUICKSTART_DIALOG (English (U.S.))
Resource24=IDD_ADDQSO_DOC (English (U.S.))
Resource25=IDR_ACCELERATOR

[CLS:CQuickStartApp]
Type=0
HeaderFile=QuickStart.h
ImplementationFile=QuickStart.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CQuickStartApp

[CLS:CQuickStartDlg]
Type=0
HeaderFile=QuickStartDlg.h
ImplementationFile=QuickStartDlg.cpp
Filter=D
LastObject=CQuickStartDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=QuickStartDlg.h
ImplementationFile=QuickStartDlg.cpp
Filter=D
LastObject=IDC_WEB_HOME
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_QUICKSTART_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CQuickStartDlg

[DLG:IDD_QUICKSTART_DIALOG (English (U.S.))]
Type=1
Class=CQuickStartDlg
ControlCount=16
Control1=IDC_BUTTON1,button,1342177280
Control2=IDC_BUTTON2,button,1342177280
Control3=IDC_BUTTON3,button,1342177280
Control4=IDC_BUTTON4,button,1342177280
Control5=IDC_BUTTON5,button,1342177280
Control6=IDC_BUTTON6,button,1342177280
Control7=IDC_BUTTON7,button,1342177280
Control8=IDC_BUTTON8,button,1342177280
Control9=IDC_UP,button,1342177280
Control10=IDC_DOWN,button,1342177280
Control11=IDC_ADDQSO,button,1342177280
Control12=IDC_CONFIG,button,1342177280
Control13=ID_HELP,button,1342177280
Control14=ID_HIDE,button,1342177280
Control15=IDC_STATIC,static,1342177297
Control16=IDC_STATIC,static,1342177297

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=10
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342177294
Control6=IDC_STATIC,static,1342177283
Control7=IDC_STATIC,static,1342308352
Control8=IDC_WEB_HOME,static,1342308352
Control9=IDC_WEB_SUPPORT,static,1342308352
Control10=IDC_STATIC,static,1342308352

[DLG:IDD_ADDQSO_PROGRAM (English (U.S.))]
Type=1
Class=CAddQSOProgram
ControlCount=8
Control1=IDC_ADDQSO_PROGRAM_PATH,edit,1350631552
Control2=IDC_BROWSE,button,1342242944
Control3=IDC_ADDQSO_PROGRAM_ARGUMENTS,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_ADDQSO_ICON,static,1342177283

[DLG:IDD_ADDQSO_TYPE (English (U.S.))]
Type=1
Class=CAddQSOType
ControlCount=6
Control1=IDC_ADDQSO_TYPE_PROGRAM,button,1342177289
Control2=IDC_ADDQSO_TYPE_TASK,button,1342177289
Control3=IDC_ADDQSO_TYPE_FOLDER,button,1342177289
Control4=IDC_ADDQSO_TYPE_DOC,button,1342177289
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[DLG:IDD_ADDQSO_NAME (English (U.S.))]
Type=1
Class=CAddQSOName
ControlCount=3
Control1=IDC_ADDQSO_NAME_NAME,edit,1350631552
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352

[DLG:IDD_ADDQSO_FOLDER (English (U.S.))]
Type=1
Class=CAddQSOFolder
ControlCount=6
Control1=IDC_ADDQSO_FOLDER_PATH,edit,1350631552
Control2=IDC_BROWSE,button,1342242944
Control3=IDC_ADDQSO_FOLDER_OPEN,button,1342177289
Control4=IDC_ADDQSO_FOLDER_EXPLORE,button,1342177289
Control5=65535,static,1342308352
Control6=65535,static,1342308352

[DLG:IDD_ADDQSO_TASK (English (U.S.))]
Type=1
Class=CAddQSOTask
ControlCount=11
Control1=IDC_ADDQSO_TASK_NAME,combobox,1344339971
Control2=IDC_CTP_OPEN,button,1073741833
Control3=IDC_REBOOT,button,1073741833
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_ADDQSO_TASK_DRIVES,combobox,1075904515
Control7=IDC_ADDQSO_TASK_DRIVE,static,1073872896
Control8=IDC_SHUTDOWN,button,1073741833
Control9=IDC_LOGOFF,button,1073741833
Control10=IDC_ADDQSO_TASK_TEST,button,1476460544
Control11=IDC_CTP_EXPLORE,button,1073741833

[MNU:IDR_QSOCONTEXT (English (U.K.))]
Type=1
CommandCount=0

[CLS:CAddQSOFolder]
Type=0
HeaderFile=AddQSOFolder.h
ImplementationFile=AddQSOFolder.cpp
BaseClass=CPropPTemplate
Filter=D
LastObject=CAddQSOFolder

[CLS:CAddQSO]
Type=0
HeaderFile=AddQSO.h
ImplementationFile=AddQSO.cpp
BaseClass=CPropertySheetEx
Filter=W
VirtualFilter=hWC
LastObject=CAddQSO

[CLS:CAddQSOTask]
Type=0
HeaderFile=AddQSOTask.h
ImplementationFile=AddQSOTask.cpp
BaseClass=CPropPTemplate
Filter=D
LastObject=CAddQSOTask

[CLS:CAddQSOType]
Type=0
HeaderFile=AddQSOType.h
ImplementationFile=AddQSOType.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CAddQSOType

[CLS:CAddQSOSum]
Type=0
HeaderFile=AddQSOSum.h
ImplementationFile=AddQSOSum.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=IDC_ADDQSO_SUM_SUM

[DLG:IDD_ADDQSO_SUM (English (U.S.))]
Type=1
Class=CAddQSOSum
ControlCount=3
Control1=IDC_ADDQSO_SUM_SUM2,edit,1476462596
Control2=IDC_ADDQSO_ICON,static,1342179331
Control3=IDC_ADDQSO_SUM_SUM,edit,1476462596

[CLS:CAddQSOProgram]
Type=0
HeaderFile=AddQSOProgram.h
ImplementationFile=AddQSOProgram.cpp
BaseClass=CPropPTemplate
Filter=D
LastObject=CAddQSOProgram

[CLS:CAddQSOName]
Type=0
HeaderFile=AddQSOName.h
ImplementationFile=AddQSOName.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CAddQSOName

[DLG:IDD_ADDQSO_DOC (English (U.S.))]
Type=1
Class=CAddQSODoc
ControlCount=8
Control1=IDC_ADDQSO_DOC_PATH,edit,1350631552
Control2=IDC_BROWSE,button,1342242944
Control3=IDC_ADDQSO_DOC_OPEN,button,1342177289
Control4=IDC_ADDQSO_DOC_PRINT,button,1342177289
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352

[CLS:CAddQSODoc]
Type=0
HeaderFile=AddQSODoc.h
ImplementationFile=AddQSODoc.cpp
BaseClass=CPropPTemplate
Filter=D
LastObject=CAddQSODoc

[DLG:IDD_ADDQSO_HOTKEY (English (U.S.))]
Type=1
Class=CAddQSOHotKey
ControlCount=6
Control1=IDC_ADDQSO_HOTKEY_HOTKEY,edit,1484849152
Control2=IDC_ADDQSO_HOTKEY_RECORD,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[CLS:CAddQSOHotKey]
Type=0
HeaderFile=AddQSOHotKey.h
ImplementationFile=AddQSOHotKey.cpp
BaseClass=CPropPTemplate
Filter=D
LastObject=CAddQSOHotKey

[DLG:IDD_ADDQSO_HOTKEY_RECORD (English (U.S.))]
Type=1
Class=CAddQSOHotKeyRecord
ControlCount=6
Control1=IDC_HOTKEY,edit,1350633600
Control2=IDOK,button,1476591617
Control3=IDC_RESET,button,1476591616
Control4=IDCANCEL,button,1342373888
Control5=65535,static,1342308480
Control6=ID_HELP,button,1342373888

[CLS:CAddQSOHotKeyRecord]
Type=0
HeaderFile=AddQSOHotKeyRecord.h
ImplementationFile=AddQSOHotKeyRecord.cpp
BaseClass=CDialog
Filter=D
LastObject=65535
VirtualFilter=dWC

[MNU:IDR_CTMENU (English (U.K.))]
Type=1
Class=?
Command1=IDM_CTMENU_MODIFY
Command2=IDM_CTMENU_MOVE_LEFT
Command3=IDM_CTMENU_MOVE_RIGHT
Command4=IDM_CTMENU_MOVE_UP
Command5=IDM_CTMENU_MOVE_DOWN
Command6=IDM_CTMENU_MOVE_BEGIN
Command7=IDM_CTMENU_MOVE_END
Command8=IDM_CTMENU_REMOVE
CommandCount=8

[MNU:IDR_SYSTRAY]
Type=1
Class=?
CommandCount=0

[DLG:IDD_QUICKSTART_CONFIG (English (U.S.))]
Type=1
Class=CConfigDlg
ControlCount=9
Control1=IDC_AUTOSTART,button,1342242819
Control2=IDC_SHOWSTART,button,1342242819
Control3=IDOK,button,1342242816
Control4=IDCANCEL,button,1342242816
Control5=IDC_CONFIG_REMOVEALLQS,button,1342242816
Control6=IDC_CONFIG_LOADDEFCFG,button,1342242816
Control7=ID_HELP,button,1342242816
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATIC,button,1342177287

[CLS:CConfigDlg]
Type=0
HeaderFile=ConfigDlg.h
ImplementationFile=ConfigDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_SHOWSTART
VirtualFilter=dWC

[ACL:IDR_ACCELERATOR]
Type=1
Class=?
Command1=IDC_ADDQSO
Command2=IDC_BUTTON1
Command3=IDC_BUTTON8
Command4=IDC_BUTTON2
Command5=IDC_BUTTON3
Command6=IDC_BUTTON4
Command7=IDC_BUTTON5
Command8=IDC_BUTTON6
Command9=IDC_BUTTON7
Command10=IDC_BUTTON8
Command11=IDC_DOWN
Command12=IDC_UP
CommandCount=12

[CLS:CSelectProgramDlg]
Type=0
HeaderFile=SelectProgramDlg.h
ImplementationFile=SelectProgramDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CSelectProgramDlg
VirtualFilter=dWC

[CLS:CWelcomeDlg]
Type=0
HeaderFile=WelcomeDlg.h
ImplementationFile=WelcomeDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CWelcomeDlg
VirtualFilter=dWC

[DLG:IDD_REGISTER (English (U.S.))]
Type=1
Class=CRegisterDlg
ControlCount=10
Control1=IDOK,button,1342242816
Control2=IDC_STATIC,static,1342177283
Control3=IDC_STATIC,button,1342177287
Control4=ID_HELP,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_REGISTER_NAME,edit,1350631552
Control9=IDC_REGISTER_NUMBER,edit,1350631552
Control10=IDCANCEL,button,1342242816

[DLG:IDD_WELCOME (English (U.S.))]
Type=1
Class=CWelcomeDlg
ControlCount=22
Control1=ID_BUY,button,1342242816
Control2=IDC_STATIC,static,1342177283
Control3=IDC_WELCOME_TITLE,static,1342308352
Control4=IDC_STATIC,button,1342177287
Control5=IDC_WELCOME_MSG,static,1342308352
Control6=IDC_WELCOME_DAYSLEFT,static,1342308352
Control7=ID_REGISTER,button,1342242817
Control8=IDCANCEL,button,1073807360
Control9=IDC_STATIC,button,1342177287
Control10=IDC_WELCOME_FUNC1,button,1342177287
Control11=IDC_WELCOME_FUNC2,static,1342308352
Control12=ID_HELP,button,1342242816
Control13=IDC_WELCOME_TIMEOUT1,static,1342308352
Control14=IDC_WELCOME_TIMEOUT,static,1342308352
Control15=IDC_WELCOME_TIMEOUT2,static,1342308352
Control16=IDC_WELCOME_TIMEOUT3,button,1342177287
Control17=IDC_STATIC,static,1342177287
Control18=IDC_WEB_HOME,static,1342308352
Control19=IDC_WEB_SUPPORT,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,button,1342177287

[DLG:IDD_TIP_MODIFYQSO (English (U.S.))]
Type=1
Class=CTips
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_TIP_SHOWAGAIN,button,1342242819
Control4=IDC_STATIC,button,1342177287

[CLS:CTips]
Type=0
HeaderFile=Tips.h
ImplementationFile=Tips.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_DOWN
VirtualFilter=dWC

[DLG:IDD_SELECT_PROGRAM (English (U.S.))]
Type=1
Class=CSelectProgramDlg
ControlCount=6
Control1=IDOK,button,1476460545
Control2=IDCANCEL,button,1342242816
Control3=IDC_SELECT_PROGRAM_OTHER,button,1342242816
Control4=IDC_CHOOSE_PROGRAM_LIST,listbox,1352728913
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[CLS:CRegisterDlg]
Type=0
HeaderFile=RegisterDlg.h
ImplementationFile=RegisterDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CRegisterDlg

[DLG:IDD_TIP_DISPLAYRESOLUTION (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_TIP_SHOWAGAIN,button,1342242819
Control4=IDC_STATIC,button,1342177287

[DLG:IDD_TIP_DISPLAYRESOLUTION_TEST (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_TIP_SHOWAGAIN,button,1342242819
Control4=IDC_STATIC,button,1342177287

