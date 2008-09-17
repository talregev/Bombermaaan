if exist "\Software\doxygen\bin\doxygen.exe" set doxygen="\Software\doxygen\bin\doxygen.exe"
if exist "%ProgramFiles%\doxygen\bin\doxygen.exe" set doxygen="%ProgramFiles%\doxygen\bin\doxygen.exe"
%doxygen% Doxyfile.txt
