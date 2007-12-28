@echo off

rem ****************************************
rem *** This file is part of Bombermaaan ***
rem *** Copyright (C) 2007 Bernd Arnold  ***
rem ****************************************


rem This command file needs to be executed within a cmd /v:on context
rem Example:
rem cmd /v:on /c Convert_all_svg2png.cmd

if "%1"=="CalledWithVOn" goto ExecNow

cmd /v:on /c %0 CalledWithVOn
goto :EOF

:ExecNow

rem Get the current directory
set imgpath=%CD%

rem --export-area-drawing 
rem --export-dpi=150
rem "%ProgramFiles%\Inkscape\inkscape.exe" "%imgpath%\Title.svg" --export-png="%imgpath%\Title_convertedsvg.png"

for %%i in (*.svg) do (
	set newname=%%i
	set newname=!newname:~0,-4!.png
	echo Converting to !newname!
	"%ProgramFiles%\Inkscape\inkscape.exe" "%imgpath%\%%i" --export-png="%imgpath%\!newname!"
)

