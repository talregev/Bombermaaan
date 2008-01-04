@echo off

rem **********************************************
rem *** This file is part of Bombermaaan       ***
rem *** Copyright (C) 2007, 2008 Bernd Arnold  ***
rem **********************************************


rem Get the current directory
set imgpath=%CD%

rem --export-area-drawing 
rem --export-dpi=150
"%ProgramFiles%\Inkscape\inkscape.exe" "%imgpath%\backgrounds\background-title.svg" --export-png="%imgpath%\_generated\background-title.png"
convert -antialias -fill #00ff00 -opaque transparent PNG:"%imgpath%\_generated\background-title.png" PPM:- | convert PPM:- BMP:"%imgpath%\_generated\background-title.bmp"


