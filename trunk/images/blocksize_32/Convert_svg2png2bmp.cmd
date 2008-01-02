@echo off

set imgpath=C:\Users\Bernd\Documents\Bombermaaan\subversion_all\branches\blocksize_32pixels\_images

rem --export-area-drawing 
rem --export-dpi=150
"%ProgramFiles%\Inkscape\inkscape.exe" "%imgpath%\backgrounds\background-title.svg" --export-png="%imgpath%\_generated\background-title.png"
convert "%imgpath%\_generated\background-title.png" "%imgpath%\_generated\background-title.bmp"


