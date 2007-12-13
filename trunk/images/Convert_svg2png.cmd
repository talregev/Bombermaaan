@echo off

set imgpath=C:\Users\Bernd\Documents\Bombermaaan\subversion_trunk\images

rem --export-area-drawing 
rem --export-dpi=150
"%ProgramFiles%\Inkscape\inkscape.exe" "%imgpath%\Title.svg" --export-png="%imgpath%\Title_convertedsvg.png"

