@echo off

rem ****************************************
rem *** This file is part of Bombermaaan ***
rem *** Copyright (C) 2007 Bernd Arnold  ***
rem ****************************************


rem Get the current directory
set imgpath=%CD%

rem --export-area-drawing 
rem --export-dpi=150
"%ProgramFiles%\Inkscape\inkscape.exe" "%imgpath%\Title.svg" --export-png="%imgpath%\Title_convertedsvg.png"

