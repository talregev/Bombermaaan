; Bombermaaan Installation Script
; Written by Bernd Arnold, 2007-12-04
;
; http://bombermaaan.sourceforge.net/
; 





!define VER_NUMBER "1.02"
!define PRODUCT_NAME "Bombermaaan"
!define PRODUCT_VERSION "1.02"
!define PRODUCT_PUBLISHER "The Bombermaaan team"

SetCompressor lzma

 


;--------------------------------
;Include Modern UI

  !include "MUI.nsh"




;--------------------------------
;General

  ;Name and file
  Name "Bombermaaan 1.02"
  OutFile "Bombermaaan_1.02-Setup.exe"

  ;Default installation folder
  InstallDir "$PROGRAMFILES\Bombermaaan"

  ;Get installation folder from registry if available
  InstallDirRegKey HKLM "Software\Bombermaaan" ""

  ;Vista redirects $SMPROGRAMS to all users without this
  RequestExecutionLevel admin




;--------------------------------
;Version Information

  VIProductVersion "1.0.2.0"
  VIAddVersionKey "ProductName" "Bombermaaan"
  VIAddVersionKey "ProductVersion" "1.0.2.0"
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
  VIAddVersionKey "LegalCopyright" "© Thibaut Tollemer"
  VIAddVersionKey "FileDescription" "Installer for Bombermaaan"
  VIAddVersionKey "FileVersion" "2"

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




;--------------------------------
;Interface Configuration

  !define MUI_HEADERIMAGE
  !define MUI_HEADERIMAGE_BITMAP "HeaderImage.bmp" ; optional
  !define MUI_ABORTWARNING





;--------------------------------
;Pages

  !insertmacro MUI_PAGE_WELCOME
  !insertmacro MUI_PAGE_LICENSE "..\COPYING.txt"
  !insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY

  ;Start Menu Folder Page Configuration
  !define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKLM" 
  !define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\Bombermaaan" 
  !define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "Start Menu Folder"
  
  !insertmacro MUI_PAGE_STARTMENU Application $STARTMENU_FOLDER

  !insertmacro MUI_PAGE_INSTFILES
  
  !define MUI_FINISHPAGE_RUN Bomberman.exe
  !define MUI_FINISHPAGE_RUN_NOTCHECKED
  !define MUI_FINISHPAGE_SHOWREADME Readme.html
  !define MUI_FINISHPAGE_SHOWREADME_CHECKED
  !insertmacro MUI_PAGE_FINISH
  
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  



;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "English"




;--------------------------------
;Installer Sections

Section "Common files (required)" SecCommonReq

  SectionIn RO

  SetOutPath "$INSTDIR"
  File ..\..\Bomberman\Bomberman.dat
  File ..\..\Bomberman\Bomberman.exe
  File ..\..\Bomberman\FMOD.DLL
  File ..\docs\Readme.html

  SetOutPath "$INSTDIR\Levels"
  File ..\..\Bomberman\Levels\L1.TXT
  File ..\..\Bomberman\Levels\L2.TXT
  File ..\..\Bomberman\Levels\L3.TXT
  File ..\..\Bomberman\Levels\L4.TXT
  File ..\..\Bomberman\Levels\L5.TXT
  File ..\..\Bomberman\Levels\L6.TXT

  ;Needed for working dir of shortcut
  SetOutPath "$INSTDIR"
  
  ;Store installation folder
  WriteRegStr HKLM "Software\Bombermaaan" "" $INSTDIR
  
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"

  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
    
    ;Create shortcuts
    CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER"
    CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\Bomberman.lnk" "$INSTDIR\Bomberman.exe"
    CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\Readme.lnk" "$INSTDIR\Readme.html"
    CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\Uninstall.lnk" "$INSTDIR\Uninstall.exe"
  
  !insertmacro MUI_STARTMENU_WRITE_END

SectionEnd




;--------------------------------
;Descriptions

  ;Language strings
  LangString DESC_SecCommonReq ${LANG_ENGLISH} "Common files for Bombermaaan."

  ;Assign language strings to sections
  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${SecCommonReq} $(DESC_SecCommonReq)
  !insertmacro MUI_FUNCTION_DESCRIPTION_END




;--------------------------------
;Uninstaller Section

Section "Uninstall"

  Delete "$INSTDIR\Bomberman.exe"
  Delete "$INSTDIR\Bomberman.dat"
  Delete "$INSTDIR\FMOD.DLL"
  Delete "$INSTDIR\Readme.html"
  Delete "$INSTDIR\Levels\L1.TXT"
  Delete "$INSTDIR\Levels\L2.TXT"
  Delete "$INSTDIR\Levels\L3.TXT"
  Delete "$INSTDIR\Levels\L4.TXT"
  Delete "$INSTDIR\Levels\L5.TXT"
  Delete "$INSTDIR\Levels\L6.TXT"

  Delete "$INSTDIR\Bomberman.cfg"
  Delete "$INSTDIR\log.txt"

  Delete "$INSTDIR\Uninstall.exe"

  RMDir "$INSTDIR\Levels"
  RMDir "$INSTDIR"

  !insertmacro MUI_STARTMENU_GETFOLDER Application $MUI_TEMP
    
  Delete "$SMPROGRAMS\$MUI_TEMP\Bomberman.lnk"
  Delete "$SMPROGRAMS\$MUI_TEMP\Readme.lnk"
  Delete "$SMPROGRAMS\$MUI_TEMP\Uninstall.lnk"
  
  RMDir "$SMPROGRAMS\$MUI_TEMP"

  DeleteRegKey /ifempty HKLM "Software\Bombermaaan"

SectionEnd
