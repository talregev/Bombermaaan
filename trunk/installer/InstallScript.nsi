; Bombermaaan Installation Script
; Written by Bernd Arnold, 2007-12-04
;
; http://bombermaaan.sourceforge.net/
; 

; ----------------------------------------------------------------------------------
;    NOTE:
;    NSIS is not used any longer
;    The installation packages are built with InnoSetup now (http://www.jrsoftware.org/isinfo.php)
; ----------------------------------------------------------------------------------





!define BM_BUILD                "423"
!define BM_VERSION              "1.3.0.${BM_BUILD}"
!define PRODUCT_NAME            "Bombermaaan"
!define PRODUCT_VERSION         "${BM_VERSION}"
!define PRODUCT_PUBLISHER       "The Bombermaaan team"
!define BM_SRCDIR               ".\packages\Bombermaaan_1.3_2008-05-07"

SetCompressor lzma

 


;--------------------------------
;Include Modern UI

  !include "MUI2.nsh"




;--------------------------------
;General

  ;Name and file
  Name "Bombermaaan 1.3"
  OutFile ".\output\Bombermaaan_${BM_VERSION}_setup.exe"

  ;Default installation folder
  InstallDir "$PROGRAMFILES\Bombermaaan"

  ;Get installation folder from registry if available
  InstallDirRegKey HKLM "Software\Bombermaaan" ""

  ;Vista redirects $SMPROGRAMS to all users without this
  RequestExecutionLevel admin




;--------------------------------
;Version Information

  VIProductVersion "${BM_VERSION}"
  VIAddVersionKey "ProductName" "Bombermaaan"
  VIAddVersionKey "ProductVersion" "${BM_VERSION}"
  VIAddVersionKey "Comments" \
    "Bombermaaan is free software: you can redistribute it and/or modify \
    it under the terms of the GNU General Public License as published by \
    the Free Software Foundation, either version 3 of the License, or \
    (at your option) any later version. \
    This program is distributed in the hope that it will be useful, \
    but WITHOUT ANY WARRANTY; without even the implied warranty of \
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the \
    GNU General Public License for more details. \
    You should have received a copy of the GNU General Public License \
    along with this program.  If not, see <http://www.gnu.org/licenses/>."
  VIAddVersionKey "Website" "http://bombermaaan.sourceforge.net/"
;  VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalTrademarks" "..."
  VIAddVersionKey "LegalCopyright" "Copyright (C) Thibaut Tollemer, Bernd Arnold"
  VIAddVersionKey "FileDescription" "Installer for Bombermaaan"
  VIAddVersionKey "FileVersion" "${BM_VERSION}"

;ProductName
;Comments
;CompanyName
;LegalCopyright
;FileDescription
;FileVersion
;ProductVersion
;InternalName
;LegalTrademarks
;OriginalFilename
;PrivateBuild
;SpecialBuild





;--------------------------------
;Variables

  Var MUI_TEMP
  Var STARTMENU_FOLDER
  Var UNINSTALL_UNINSTALLBUTTON




;--------------------------------
;Interface Configuration

  !define MUI_HEADERIMAGE
  !define MUI_HEADERIMAGE_BITMAP "HeaderImage.bmp"
  !define MUI_ABORTWARNING





;--------------------------------
;Pages

  !insertmacro MUI_PAGE_WELCOME
  !define MUI_LICENSEPAGE_RADIOBUTTONS
  !insertmacro MUI_PAGE_LICENSE "..\COPYING.txt"
  
  Page custom PageUninstallOldVersion PageLeaveUninstallOldVersion
  
  !define MUI_COMPONENTSPAGE_SMALLDESC
  !insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY

  ;Start Menu Folder Page Configuration
  !define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKLM" 
  !define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\Bombermaaan" 
  !define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "Start Menu Folder"
  
  !insertmacro MUI_PAGE_STARTMENU Application $STARTMENU_FOLDER

  !insertmacro MUI_PAGE_INSTFILES
  
  !define MUI_FINISHPAGE_RUN Bombermaaan_32.exe
  !define MUI_FINISHPAGE_RUN_NOTCHECKED
  !define MUI_FINISHPAGE_SHOWREADME Readme.html
  !define MUI_FINISHPAGE_SHOWREADME_CHECKED
  !define MUI_FINISHPAGE_NOAUTOCLOSE
  !insertmacro MUI_PAGE_FINISH
  
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  



;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "English"
  ;!insertmacro MUI_LANGUAGE "French"
  ;!insertmacro MUI_LANGUAGE "German"




;--------------------------------
;Uninstall old version page

Function PageUninstallOldVersion

  ; This was set by installer of version 1.02:
  ReadRegStr $R0 HKLM "SOFTWARE\Bombermaaan" "Start Menu Folder"
  StrCmp $R0 "" done
 
  nsDialogs::Create /NOUNLOAD 1018
  Pop $0

  !insertmacro MUI_HEADER_TEXT "Already Installed" "Choose how you want to install Bombermaaan."
  nsDialogs::CreateItem /NOUNLOAD STATIC ${WS_VISIBLE}|${WS_CHILD}|${WS_CLIPSIBLINGS} 0 0 0 100% 40 "Bombermaaan has already been installed. It's recommended that you uninstall the current version before installing. Select the operation you want to perform and click Next to continue."
  Pop $R0
  nsDialogs::CreateItem /NOUNLOAD BUTTON ${BS_AUTORADIOBUTTON}|${BS_VCENTER}|${BS_MULTILINE}|${WS_VISIBLE}|${WS_CHILD}|${WS_CLIPSIBLINGS}|${WS_GROUP}|${WS_TABSTOP} 0 10 55 100% 30 "Uninstall before installing"
  Pop $UNINSTALL_UNINSTALLBUTTON
  nsDialogs::CreateItem /NOUNLOAD BUTTON ${BS_AUTORADIOBUTTON}|${BS_TOP}|${BS_MULTILINE}|${WS_VISIBLE}|${WS_CHILD}|${WS_CLIPSIBLINGS} 0 10 85 100% 50 "Do not uninstall"
  Pop $R0

  SendMessage $UNINSTALL_UNINSTALLBUTTON ${BM_SETCHECK} 1 0

  nsDialogs::Show

  done: 

FunctionEnd



Function PageLeaveUninstallOldVersion

  SendMessage $UNINSTALL_UNINSTALLBUTTON ${BM_GETCHECK} 0 0 $R0
  StrCmp $R0 "1" uninstall skipuninstall
  
  uninstall:
  Call RunUninstaller
  goto end
  
  skipuninstall:
  ; Nothing to do
  
  end:

FunctionEnd



Function RunUninstaller

  HideWindow
  
  ClearErrors
  ExecWait '"$INSTDIR\uninstall.exe" /S _?=$INSTDIR'
  IfErrors end
  
  ; Remove uninstaller and installation folder
  Delete "$INSTDIR\uninstall.exe"
  RMDir $INSTDIR
  
  end:

  ; Show window again
  BringToFront
  
FunctionEnd






;--------------------------------
;Installer Sections

Section "Common files (required)" SecCommonReq

  SectionIn RO

  SetOutPath "$INSTDIR"
  DetailPrint "Writing program files..."
  File "${BM_SRCDIR}\Bombermaaan.dll"
  File "${BM_SRCDIR}\Bombermaaan_16.exe"
  File "${BM_SRCDIR}\Bombermaaan_32.dll"
  File "${BM_SRCDIR}\Bombermaaan_32.exe"
  File "${BM_SRCDIR}\FMOD.DLL"
  File "${BM_SRCDIR}\Readme.html"
  File "${BM_SRCDIR}\COPYING.txt"
  File "${BM_SRCDIR}\CHANGELOG.txt"

  SetOutPath "$INSTDIR\Levels"
  DetailPrint "Writing level files..."
  File "${BM_SRCDIR}\Levels\L1.TXT"
  File "${BM_SRCDIR}\Levels\L2.TXT"
  File "${BM_SRCDIR}\Levels\L3.TXT"
  File "${BM_SRCDIR}\Levels\L4.TXT"
  File "${BM_SRCDIR}\Levels\L5.TXT"
  File "${BM_SRCDIR}\Levels\L6.TXT"
  File "${BM_SRCDIR}\Levels\L7.TXT"
  File "${BM_SRCDIR}\Levels\L8.TXT"

  
  DetailPrint "Writing registry keys..."

  ;Store installation folder
  WriteRegStr HKLM "Software\Bombermaaan" "" $INSTDIR
  
  ;Store installed version
  WriteRegStr HKLM "Software\Bombermaaan" "Version" "${BM_VERSION}"
  WriteRegStr HKLM "Software\Bombermaaan" "Build" "${BM_BUILD}"
  
  
  WriteRegExpandStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Bombermaaan" "UninstallString" "$INSTDIR\uninstall.exe"
  WriteRegExpandStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Bombermaaan" "InstallLocation" "$INSTDIR"
  WriteRegStr       HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Bombermaaan" "DisplayName" "${PRODUCT_NAME} ${BM_VERSION}"
  WriteRegStr       HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Bombermaaan" "DisplayIcon" "$INSTDIR\Bombermaaan.exe"
  WriteRegStr       HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Bombermaaan" "DisplayVersion" "${BM_VERSION}"
  WriteRegDWORD     HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Bombermaaan" "NoModify" "1"
  WriteRegDWORD     HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Bombermaaan" "NoRepair" "1"
  
  ;Needed for working dir of shortcut
  SetOutPath "$INSTDIR"
  
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"

  
  DetailPrint "Creating shortcuts..."

  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
    
    ; Try creating shortcuts for all users
    SetShellVarContext all
    CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER"
    ; ... if it failed (directory doesn't exist), do it for current user
    IfFileExists "$SMPROGRAMS\$STARTMENU_FOLDER" createShortcuts
      SetShellVarContext current
      CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER"
 
    createShortcuts:
      ;Create shortcuts
      CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\Bombermaaan (classic).lnk" "$INSTDIR\Bombermaaan_16.exe"
      CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\Bombermaaan (large size).lnk" "$INSTDIR\Bombermaaan_32.exe"
      CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\Readme.lnk" "$INSTDIR\Readme.html"
      CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\License (GPL).lnk" "$INSTDIR\COPYING.txt"
      CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\Uninstall.lnk" "$INSTDIR\Uninstall.exe"
  
  !insertmacro MUI_STARTMENU_WRITE_END

SectionEnd




;--------------------------------
;Descriptions

  ;Language strings
  LangString DESC_SecCommonReq ${LANG_ENGLISH} "Common files for Bombermaaan."
  ;LangString DESC_SecCommonReq ${LANG_GERMAN} "Gemeinsame Dateien für Bombermaaan."
  
  ;Assign language strings to sections
  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${SecCommonReq} $(DESC_SecCommonReq)
  !insertmacro MUI_FUNCTION_DESCRIPTION_END




;--------------------------------
;Uninstaller Section

Section "Uninstall"

  ; Fixed program files
  DetailPrint "Deleting program files..."
  Delete "$INSTDIR\Bombermaaan.dll"
  Delete "$INSTDIR\Bombermaaan_16.exe"
  Delete "$INSTDIR\Bombermaaan_32.dll"
  Delete "$INSTDIR\Bombermaaan_32.exe"
  Delete "$INSTDIR\FMOD.DLL"
  Delete "$INSTDIR\Readme.html"
  Delete "$INSTDIR\COPYING.txt"
  Delete "$INSTDIR\CHANGELOG.txt"

  ; Fixed level files
  DetailPrint "Deleting level files..."
  Delete "$INSTDIR\Levels\L1.TXT"
  Delete "$INSTDIR\Levels\L2.TXT"
  Delete "$INSTDIR\Levels\L3.TXT"
  Delete "$INSTDIR\Levels\L4.TXT"
  Delete "$INSTDIR\Levels\L5.TXT"
  Delete "$INSTDIR\Levels\L6.TXT"
  Delete "$INSTDIR\Levels\L7.TXT"
  Delete "$INSTDIR\Levels\L8.TXT"

  ; Dynamically created files
  Delete "$INSTDIR\Bombermaaan.cfg"
  Delete "$INSTDIR\log.txt"

  Delete "$INSTDIR\Uninstall.exe"

  RMDir "$INSTDIR\Levels"
  RMDir "$INSTDIR"

  !insertmacro MUI_STARTMENU_GETFOLDER Application $MUI_TEMP
  
  DetailPrint "Removing shortcuts..."
  
  ; Folder exists for all users -> delete start menu entries/folder for all users
  SetShellVarContext all
  IfFileExists "$SMPROGRAMS\$MUI_TEMP" deleteShortcuts
    ; Delete start menu entries/folder for current user
    SetShellVarContext current
  deleteShortcuts:
  Delete "$SMPROGRAMS\$MUI_TEMP\Bombermaaan (classic).lnk"
  Delete "$SMPROGRAMS\$MUI_TEMP\Bombermaaan (large size).lnk"
  Delete "$SMPROGRAMS\$MUI_TEMP\Readme.lnk"
  Delete "$SMPROGRAMS\$MUI_TEMP\License (GPL).lnk"
  Delete "$SMPROGRAMS\$MUI_TEMP\Uninstall.lnk"
  
  RMDir "$SMPROGRAMS\$MUI_TEMP"

  
  DetailPrint "Removing registry keys..."
  
  DeleteRegKey /ifempty HKLM "Software\Bombermaaan"

  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Bombermaaan"

SectionEnd



;--------------------------------
;Uninstaller Functions

;Function un.onInit

;  !insertmacro MUI_UNGETLANGUAGE
  
;FunctionEnd

