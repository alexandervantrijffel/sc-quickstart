# Microsoft Developer Studio Project File - Name="QuickStart" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=QuickStart - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "QuickStart.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "QuickStart.mak" CFG="QuickStart - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "QuickStart - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "QuickStart - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "QuickStart - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x413 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x413 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib delayimp.lib htmlhelp.lib /nologo /subsystem:windows /machine:I386 /out:"Release/SC-QuickStart.exe" /DELAYLOAD:COMDLG32.DLL /DELAYLOAD:OLEAUT32.DLL /DELAYLOAD:OLE32.DLL /DELAYLOAD:WINSPOOL.DRV /DELAYLOAD:WINMM.DLL
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "QuickStart - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x413 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x413 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib htmlhelp.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/SC-QuickStart.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "QuickStart - Win32 Release"
# Name "QuickStart - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AddQSO.cpp
# End Source File
# Begin Source File

SOURCE=.\AddQSODoc.cpp
# End Source File
# Begin Source File

SOURCE=.\AddQSOFolder.cpp
# End Source File
# Begin Source File

SOURCE=.\AddQSOHotKey.cpp
# End Source File
# Begin Source File

SOURCE=.\AddQSOHotKeyRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\AddQSOName.cpp
# End Source File
# Begin Source File

SOURCE=.\AddQSOProgram.cpp
# End Source File
# Begin Source File

SOURCE=.\AddQSOSum.cpp
# End Source File
# Begin Source File

SOURCE=.\AddQSOTask.cpp
# End Source File
# Begin Source File

SOURCE=.\AddQSOType.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\ATKit\ATFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\ATKit\ATReg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\ATKit\ATSecurity.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\ATKit\ATString.cpp
# End Source File
# Begin Source File

SOURCE=.\BtnST.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Crc.cpp
# End Source File
# Begin Source File

SOURCE=.\HyperLink.cpp
# End Source File
# Begin Source File

SOURCE=.\IconListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\Kb.cpp
# End Source File
# Begin Source File

SOURCE=.\PropPTemplate.cpp
# End Source File
# Begin Source File

SOURCE=.\QSBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\QSo.cpp
# End Source File
# Begin Source File

SOURCE=.\QSObjects.cpp
# End Source File
# Begin Source File

SOURCE=.\QuickStart.cpp
# End Source File
# Begin Source File

SOURCE=.\QuickStart.rc
# End Source File
# Begin Source File

SOURCE=.\QuickStartDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectProgramDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Settings.cpp
# End Source File
# Begin Source File

SOURCE=.\shRetr.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SystemTray.cpp
# End Source File
# Begin Source File

SOURCE=.\Tasks.cpp
# End Source File
# Begin Source File

SOURCE=.\Tips.cpp
# End Source File
# Begin Source File

SOURCE=.\TipsMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\VideoMode.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AddQSO.h
# End Source File
# Begin Source File

SOURCE=.\AddQSODoc.h
# End Source File
# Begin Source File

SOURCE=.\AddQSOFolder.h
# End Source File
# Begin Source File

SOURCE=.\AddQSOHotKey.h
# End Source File
# Begin Source File

SOURCE=.\AddQSOHotKeyRecord.h
# End Source File
# Begin Source File

SOURCE=.\AddQSOName.h
# End Source File
# Begin Source File

SOURCE=.\AddQSOProgram.h
# End Source File
# Begin Source File

SOURCE=.\AddQSOSum.h
# End Source File
# Begin Source File

SOURCE=.\AddQSOTask.h
# End Source File
# Begin Source File

SOURCE=.\AddQSOType.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\ATKit\ATReg.h
# End Source File
# Begin Source File

SOURCE=.\BtnST.h
# End Source File
# Begin Source File

SOURCE=.\ConfigDlg.h
# End Source File
# Begin Source File

SOURCE=.\Crc.h
# End Source File
# Begin Source File

SOURCE=.\HyperLink.h
# End Source File
# Begin Source File

SOURCE=.\IconListBox.h
# End Source File
# Begin Source File

SOURCE=.\Kb.h
# End Source File
# Begin Source File

SOURCE=.\PropPTemplate.h
# End Source File
# Begin Source File

SOURCE=.\QSBtn.h
# End Source File
# Begin Source File

SOURCE=.\QSo.h
# End Source File
# Begin Source File

SOURCE=.\QSObjects.h
# End Source File
# Begin Source File

SOURCE=.\qsoinfo.h
# End Source File
# Begin Source File

SOURCE=.\QuickStart.h
# End Source File
# Begin Source File

SOURCE=.\QuickStartDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h

!IF  "$(CFG)" == "QuickStart - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=SC-QuickStart
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	makehm ID_,IDH_,0x10000 IDM_,IDH_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	makehm IDP_,IDH_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	makehm IDR_,IDH_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	makehm IDD_,IDH_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	makehm IDW_,IDH_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	MakeIDH "hlp\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "QuickStart - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=SC-QuickStart
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	makehm ID_,IDH_,0x10000 IDM_,IDH_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	makehm IDP_,IDH_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	makehm IDR_,IDH_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	makehm IDD_,IDH_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	makehm IDW_,IDH_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	MakeIDH "hlp\$(TargetName).hm" 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SelectProgramDlg.h
# End Source File
# Begin Source File

SOURCE=.\Settings.h
# End Source File
# Begin Source File

SOURCE=.\shRetr.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SystemTray.h
# End Source File
# Begin Source File

SOURCE=.\Tasks.h
# End Source File
# Begin Source File

SOURCE=.\Tips.h
# End Source File
# Begin Source File

SOURCE=.\TipsMgr.h
# End Source File
# Begin Source File

SOURCE=.\VideoMode.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\add.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bg.bmp
# End Source File
# Begin Source File

SOURCE=.\res\browse.bmp
# End Source File
# Begin Source File

SOURCE=.\res\close.bmp
# End Source File
# Begin Source File

SOURCE=.\res\config.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\down.ico
# End Source File
# Begin Source File

SOURCE=.\res\downdis.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Hand.cur
# End Source File
# Begin Source File

SOURCE=.\res\help.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_down.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_up.ico
# End Source File
# Begin Source File

SOURCE=.\res\QuickStart.ico
# End Source File
# Begin Source File

SOURCE=.\res\QuickStart.rc2
# End Source File
# Begin Source File

SOURCE=.\res\sclogo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\up.bmp
# End Source File
# Begin Source File

SOURCE=.\res\up.ico
# End Source File
# Begin Source File

SOURCE=.\res\updis.bmp
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter "cnt;rtf"
# Begin Source File

SOURCE=.\hlp\AfxDlg.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\QuickStart.cnt

!IF  "$(CFG)" == "QuickStart - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Copying contents file...
OutDir=.\Release
InputPath=.\hlp\QuickStart.cnt
InputName=QuickStart

"$(OutDir)\$(InputName).cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "hlp\$(InputName).cnt" $(OutDir)

# End Custom Build

!ELSEIF  "$(CFG)" == "QuickStart - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Copying contents file...
OutDir=.\Debug
InputPath=.\hlp\QuickStart.cnt
InputName=QuickStart

"$(OutDir)\$(InputName).cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "hlp\$(InputName).cnt" $(OutDir)

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=..\DefCfg\DefCfg.dsp
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=".\hlp\SC-Quickstart.hhp"

!IF  "$(CFG)" == "QuickStart - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__SC_QU="hlp\$(TargetName).hm"	
# Begin Custom Build
OutDir=.\Release
TargetName=SC-QuickStart
InputPath=".\hlp\SC-Quickstart.hhp"
InputName=SC-Quickstart

"hlp\$(InputName).chm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	hhc.exe hlp\$(InputName).hhp 
	echo. 
	copy hlp\$(InputName).chm $(OutDir)\$(InputName).chm 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "QuickStart - Win32 Debug"

# PROP Ignore_Default_Tool 1

!ENDIF 

# End Source File
# End Target
# End Project
