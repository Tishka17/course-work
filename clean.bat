@echo off
rem Removes all temp files
del /Q /F prj\VS6\*.ncb
del /Q /S /F prj\*.plg
del /Q /F bin\Release\TEMP\*.*
del /Q /F bin\Release\DLL\*.exp
del /Q /F bin\Release\DLL\*.lib
del /Q /F bin\Release\Plugins\*.exp
del /Q /F bin\Release\Plugins\*.lib
del /Q /F bin\Release\*log*.html
del /Q /F bin\Release\*.bsc

if -%1==-nodebug rmdir /Q /S bin\Debug\
del /Q /F bin\Debug\TEMP\*.*
del /Q /F bin\Debug\DLL\*.exp
del /Q /F bin\Debug\DLL\*.lib
del /Q /F bin\Debug\DLL\*.pdb
del /Q /F bin\Debug\DLL\*.ilk
del /Q /F bin\Debug\Plugins\*.exp
del /Q /F bin\Debug\Plugins\*.lib
del /Q /F bin\Debug\Plugins\*.pdb
del /Q /F bin\Debug\Plugins\*.ilk
del /Q /F bin\Debug\*log*.html
del /Q /F bin\Debug\*.bsc
del /Q /F bin\Debug\*.ilk
del /Q /F bin\Debug\*.pdb
echo on