@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by QUICKSTART.HPJ. >"hlp\QuickStart.hm"
echo. >>"hlp\QuickStart.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\QuickStart.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\QuickStart.hm"
echo. >>"hlp\QuickStart.hm"
echo // Prompts (IDP_*) >>"hlp\QuickStart.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\QuickStart.hm"
echo. >>"hlp\QuickStart.hm"
echo // Resources (IDR_*) >>"hlp\QuickStart.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\QuickStart.hm"
echo. >>"hlp\QuickStart.hm"
echo // Dialogs (IDD_*) >>"hlp\QuickStart.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\QuickStart.hm"
echo. >>"hlp\QuickStart.hm"
echo // Frame Controls (IDW_*) >>"hlp\QuickStart.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\QuickStart.hm"
REM -- Make help for Project QUICKSTART


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\QuickStart.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\QuickStart.hlp" goto :Error
if not exist "hlp\QuickStart.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\QuickStart.hlp" Debug
if exist Debug\nul copy "hlp\QuickStart.cnt" Debug
if exist Release\nul copy "hlp\QuickStart.hlp" Release
if exist Release\nul copy "hlp\QuickStart.cnt" Release
echo.
goto :done

:Error
echo hlp\QuickStart.hpj(1) : error: Problem encountered creating help file

:done
echo.
