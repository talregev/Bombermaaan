@echo off

set imgpath=C:\Dokumente und Einstellungen\Bernd\Eigene Dateien\Bombermaaan\repository_trunk\images

rem --export-area-drawing 
rem --export-dpi=150
%ProgramFiles%\Inkscape\inkscape.exe "%imgpath%\Title.svg" --export-png="%imgpath%\Title_convertedsvg.png"

