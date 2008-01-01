# Microsoft Developer Studio Project File - Name="RES" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=RES - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RES.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RES.mak" CFG="RES - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RES - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RES - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RES - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\_Test_\Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RES_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RES_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"..\_Test_\Release/Bomberman.dat"

!ELSEIF  "$(CFG)" == "RES - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\_Test_\Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RES_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RES_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"..\_Test_\Debug/Bomberman.dat" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "RES - Win32 Release"
# Name "RES - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\RES.cpp
# End Source File
# Begin Source File

SOURCE=.\resource.rc
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Image\arena_bomber_death.bmp
# End Source File
# Begin Source File

SOURCE=.\Image\arena_bomber_lift.bmp
# End Source File
# Begin Source File

SOURCE=.\Image\arena_bomber_punch.bmp
# End Source File
# Begin Source File

SOURCE=.\Image\arena_bomber_stunt.bmp
# End Source File
# Begin Source File

SOURCE=.\Image\arena_bomber_throw.bmp
# End Source File
# Begin Source File

SOURCE=.\Image\arena_bomber_walk.bmp
# End Source File
# Begin Source File

SOURCE=.\Image\arena_bomber_walk_hold.bmp
# End Source File
# Begin Source File

SOURCE=.\Image\arena_fumes.bmp
# End Source File
# Begin Source File

SOURCE=.\Image\board_drawgame.bmp
# End Source File
# Begin Source File

SOURCE=.\Image\board_heads.bmp
# End Source File
# Begin Source File

SOURCE=.\Image\board_time.bmp
# End Source File
# Begin Source File

SOURCE=.\Sound\BOMB_BOUNCE.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\BOMB_DROP.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\BOMBER_DEATH.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\BOMBER_LOSE_ITEM.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\Bomber_punch.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\Bomber_throw.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\Break_1.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\Break_2.mp3
# End Source File
# Begin Source File

SOURCE=.\Image\controls_background.bmp
# End Source File
# Begin Source File

SOURCE=.\Image\controls_background_2.bmp
# End Source File
# Begin Source File

SOURCE=.\Image\controls_background_3.bmp
# End Source File
# Begin Source File

SOURCE=.\Sound\CONTROLS_MUSIC.S3M
# End Source File
# Begin Source File

SOURCE=.\Sound\DRAW_GAME.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\EXPLOSION_01_1.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\EXPLOSION_01_2.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\EXPLOSION_02_1.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\EXPLOSION_02_2.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\EXPLOSION_03_1.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\EXPLOSION_03_2.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\EXPLOSION_04_1.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\EXPLOSION_04_2.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\EXPLOSION_05_1.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\EXPLOSION_05_2.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\EXPLOSION_06_1.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\EXPLOSION_06_2.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\EXPLOSION_07_1.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\EXPLOSION_07_2.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\EXPLOSION_08_1.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\EXPLOSION_08_2.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\EXPLOSION_09_1.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\EXPLOSION_09_2.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\EXPLOSION_10_1.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\EXPLOSION_10_2.mp3
# End Source File
# Begin Source File

SOURCE=.\Image\hurry.bmp
# End Source File
# Begin Source File

SOURCE=.\Sound\Hurry.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\ITEM_FUMES.mp3
# End Source File
# Begin Source File

SOURCE=.\Image\level_mini_bombers.bmp
# End Source File
# Begin Source File

SOURCE=.\Image\level_mini_tiles.bmp
# End Source File
# Begin Source File

SOURCE=.\Sound\Match_music_1_fast.mod
# End Source File
# Begin Source File

SOURCE=.\Sound\Match_music_1_normal.mod
# End Source File
# Begin Source File

SOURCE=.\Image\menu_background.bmp
# End Source File
# Begin Source File

SOURCE=.\Image\menu_background_2.bmp
# End Source File
# Begin Source File

SOURCE=.\Image\menu_background_3.bmp
# End Source File
# Begin Source File

SOURCE=.\Sound\MENU_BEEP.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\MENU_ERROR.mp3
# End Source File
# Begin Source File

SOURCE=.\IMAGE\menu_frame.bmp
# End Source File
# Begin Source File

SOURCE=.\Image\menu_frame_2.bmp
# End Source File
# Begin Source File

SOURCE=.\Sound\Menu_music.s3m
# End Source File
# Begin Source File

SOURCE=.\Sound\MENU_NEXT.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\MENU_PREVIOUS.mp3
# End Source File
# Begin Source File

SOURCE=.\Image\pause.bmp
# End Source File
# Begin Source File

SOURCE=.\Sound\Pause.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\PICK_ITEM_1.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\PICK_ITEM_2.mp3
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\Sound\RING_DING.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\Sick_1.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\Sick_2.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\Sick_3.mp3
# End Source File
# Begin Source File

SOURCE=.\Image\title_backg.bmp
# End Source File
# Begin Source File

SOURCE=.\Image\title_bombers.bmp
# End Source File
# Begin Source File

SOURCE=.\Image\title_cloud_1.bmp
# End Source File
# Begin Source File

SOURCE=.\Image\title_cloud_2.bmp
# End Source File
# Begin Source File

SOURCE=.\Image\title_cloud_3.bmp
# End Source File
# Begin Source File

SOURCE=.\Image\title_menu_items.bmp
# End Source File
# Begin Source File

SOURCE=.\Sound\TITLE_MUSIC.S3M
# End Source File
# Begin Source File

SOURCE=.\Image\title_title.bmp
# End Source File
# Begin Source File

SOURCE=.\Sound\Victory.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\WALL_CLAP_1.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\WALL_CLAP_2.mp3
# End Source File
# Begin Source File

SOURCE=.\Sound\Winner.mp3
# End Source File
# Begin Source File

SOURCE=.\Image\winner_background.bmp
# End Source File
# Begin Source File

SOURCE=.\Image\winner_background_2.bmp
# End Source File
# Begin Source File

SOURCE=.\Image\winner_background_3.bmp
# End Source File
# End Group
# End Target
# End Project
