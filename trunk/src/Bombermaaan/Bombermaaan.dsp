# Microsoft Developer Studio Project File - Name="Bombermaaan" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Bombermaaan - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Bombermaaan.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Bombermaaan.mak" CFG="Bombermaaan - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Bombermaaan - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Bombermaaan - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Bombermaaan - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\_Test_\Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "../DXSDK/Include" /I "../STL" /I "../SDL/include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"STDAFX.H" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ws2_32.lib sdl.lib sdl_mixer.lib ddraw.lib dxguid.lib dinput.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /profile /machine:I386 /libpath:"../DXSDK/Lib" /libpath:"../SDL/lib"

!ELSEIF  "$(CFG)" == "Bombermaaan - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\_Test_\Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "../DXSDK/Include" /I "../SDL/Include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"STDAFX.H" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ws2_32.lib sdl.lib sdl_mixer.lib ddraw.lib dxguid.lib dinput.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /profile /map /debug /machine:I386 /libpath:"../DXSDK/Lib" /libpath:"../SDL/lib"

!ENDIF 

# Begin Target

# Name "Bombermaaan - Win32 Release"
# Name "Bombermaaan - Win32 Debug"
# Begin Group "Screens"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CBoard.cpp
# End Source File
# Begin Source File

SOURCE=.\CBoard.h
# End Source File
# Begin Source File

SOURCE=.\CClock.cpp
# End Source File
# Begin Source File

SOURCE=.\CClock.h
# End Source File
# Begin Source File

SOURCE=.\CCloudManager.cpp
# End Source File
# Begin Source File

SOURCE=.\CCloudManager.h
# End Source File
# Begin Source File

SOURCE=.\CCommandChunk.cpp
# End Source File
# Begin Source File

SOURCE=.\CCommandChunk.h
# End Source File
# Begin Source File

SOURCE=.\CControls.cpp
# End Source File
# Begin Source File

SOURCE=.\CControls.h
# End Source File
# Begin Source File

SOURCE=.\CDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\CDemo.h
# End Source File
# Begin Source File

SOURCE=.\CDrawGame.cpp
# End Source File
# Begin Source File

SOURCE=.\CDrawGame.h
# End Source File
# Begin Source File

SOURCE=.\CHurryMessage.cpp
# End Source File
# Begin Source File

SOURCE=.\CHurryMessage.h
# End Source File
# Begin Source File

SOURCE=.\CMatch.cpp
# End Source File
# Begin Source File

SOURCE=.\CMatch.h
# End Source File
# Begin Source File

SOURCE=.\CMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\CMenu.h
# End Source File
# Begin Source File

SOURCE=.\CMenuBase.cpp
# End Source File
# Begin Source File

SOURCE=.\CMenuBase.h
# End Source File
# Begin Source File

SOURCE=.\CMenuBomber.cpp
# End Source File
# Begin Source File

SOURCE=.\CMenuBomber.h
# End Source File
# Begin Source File

SOURCE=.\CMenuInput.cpp
# End Source File
# Begin Source File

SOURCE=.\CMenuInput.h
# End Source File
# Begin Source File

SOURCE=.\CMenuLevel.cpp
# End Source File
# Begin Source File

SOURCE=.\CMenuLevel.h
# End Source File
# Begin Source File

SOURCE=.\CMenuMatch.cpp
# End Source File
# Begin Source File

SOURCE=.\CMenuMatch.h
# End Source File
# Begin Source File

SOURCE=.\CMenuYesNo.cpp
# End Source File
# Begin Source File

SOURCE=.\CMenuYesNo.h
# End Source File
# Begin Source File

SOURCE=.\CModeScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\CModeScreen.h
# End Source File
# Begin Source File

SOURCE=.\CMosaic.cpp
# End Source File
# Begin Source File

SOURCE=.\CMosaic.h
# End Source File
# Begin Source File

SOURCE=.\CPauseMessage.cpp
# End Source File
# Begin Source File

SOURCE=.\CPauseMessage.h
# End Source File
# Begin Source File

SOURCE=.\CRandomMosaic.cpp
# End Source File
# Begin Source File

SOURCE=.\CRandomMosaic.h
# End Source File
# Begin Source File

SOURCE=.\CScroller.cpp
# End Source File
# Begin Source File

SOURCE=.\CScroller.h
# End Source File
# Begin Source File

SOURCE=.\CTitle.cpp
# End Source File
# Begin Source File

SOURCE=.\CTitle.h
# End Source File
# Begin Source File

SOURCE=.\CVictory.cpp
# End Source File
# Begin Source File

SOURCE=.\CVictory.h
# End Source File
# Begin Source File

SOURCE=.\CWinner.cpp
# End Source File
# Begin Source File

SOURCE=.\CWinner.h
# End Source File
# End Group
# Begin Group "System"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CConsole.cpp
# End Source File
# Begin Source File

SOURCE=.\CConsole.h
# End Source File
# Begin Source File

SOURCE=.\CDirectDraw.cpp
# End Source File
# Begin Source File

SOURCE=.\CDirectDraw.h
# End Source File
# Begin Source File

SOURCE=.\CDirectInput.cpp
# End Source File
# Begin Source File

SOURCE=.\CDirectInput.h
# End Source File
# Begin Source File

SOURCE=.\CLog.cpp
# End Source File
# Begin Source File

SOURCE=.\CLog.h
# End Source File
# Begin Source File

SOURCE=.\CTimer.h
# End Source File
# Begin Source File

SOURCE=.\CWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\CWindow.h
# End Source File
# End Group
# Begin Group "Game"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CDebug.cpp
# End Source File
# Begin Source File

SOURCE=.\CDebug.h
# End Source File
# Begin Source File

SOURCE=.\CDisplay.cpp
# End Source File
# Begin Source File

SOURCE=.\CDisplay.h
# End Source File
# Begin Source File

SOURCE=.\CFont.cpp
# End Source File
# Begin Source File

SOURCE=.\CFont.h
# End Source File
# Begin Source File

SOURCE=.\CGame.cpp
# End Source File
# Begin Source File

SOURCE=.\CGame.h
# End Source File
# Begin Source File

SOURCE=.\CInput.cpp
# End Source File
# Begin Source File

SOURCE=.\CInput.h
# End Source File
# Begin Source File

SOURCE=.\CMainInput.cpp
# End Source File
# Begin Source File

SOURCE=.\CMainInput.h
# End Source File
# Begin Source File

SOURCE=.\COptions.cpp
# End Source File
# Begin Source File

SOURCE=.\COptions.h
# End Source File
# Begin Source File

SOURCE=.\CPlayerInput.cpp
# End Source File
# Begin Source File

SOURCE=.\CPlayerInput.h
# End Source File
# Begin Source File

SOURCE=.\CScores.cpp
# End Source File
# Begin Source File

SOURCE=.\CScores.h
# End Source File
# Begin Source File

SOURCE=.\CSound.cpp
# End Source File
# Begin Source File

SOURCE=.\CSound.h
# End Source File
# End Group
# Begin Group "Arena"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CArena.cpp
# End Source File
# Begin Source File

SOURCE=.\CArena.h
# End Source File
# Begin Source File

SOURCE=.\CArenaCloser.cpp
# End Source File
# Begin Source File

SOURCE=.\CArenaCloser.h
# End Source File
# Begin Source File

SOURCE=.\CArenaSnapshot.cpp
# End Source File
# Begin Source File

SOURCE=.\CArenaSnapshot.h
# End Source File
# Begin Source File

SOURCE=.\CBomb.cpp
# End Source File
# Begin Source File

SOURCE=.\CBomb.h
# End Source File
# Begin Source File

SOURCE=.\CBomber.cpp
# End Source File
# Begin Source File

SOURCE=.\CBomber.h
# End Source File
# Begin Source File

SOURCE=.\CBomberMove.cpp
# End Source File
# Begin Source File

SOURCE=.\CBomberMove.h
# End Source File
# Begin Source File

SOURCE=.\CElement.cpp
# End Source File
# Begin Source File

SOURCE=.\CElement.h
# End Source File
# Begin Source File

SOURCE=.\CExplosion.cpp
# End Source File
# Begin Source File

SOURCE=.\CExplosion.h
# End Source File
# Begin Source File

SOURCE=.\CFloor.cpp
# End Source File
# Begin Source File

SOURCE=.\CFloor.h
# End Source File
# Begin Source File

SOURCE=.\CItem.cpp
# End Source File
# Begin Source File

SOURCE=.\CItem.h
# End Source File
# Begin Source File

SOURCE=.\CWall.cpp
# End Source File
# Begin Source File

SOURCE=.\CWall.h
# End Source File
# End Group
# Begin Group "Computer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CAiArena.cpp
# End Source File
# Begin Source File

SOURCE=.\CAiArena.h
# End Source File
# Begin Source File

SOURCE=.\CAiBomber.cpp
# End Source File
# Begin Source File

SOURCE=.\CAiBomber.h
# End Source File
# Begin Source File

SOURCE=.\CAiManager.cpp
# End Source File
# Begin Source File

SOURCE=.\CAiManager.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Bombermaaan.ico
# End Source File
# Begin Source File

SOURCE=.\Bombermaaan.rc
# End Source File
# Begin Source File

SOURCE=.\doc.txt
# End Source File
# Begin Source File

SOURCE=.\RESOURCE.H
# End Source File
# Begin Source File

SOURCE=.\STDAFX.CPP
# ADD CPP /Yc"STDAFX.H"
# End Source File
# Begin Source File

SOURCE=.\STDAFX.H
# End Source File
# Begin Source File

SOURCE=.\WinMain.cpp
# End Source File
# End Target
# End Project
