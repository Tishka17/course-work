@echo off
rem makes archiv of source and bin files
set  RarPath="H:\Program files\WinRar\rar.exe"
set  UPXPath="H:\Program files\UPX\upx.exe"
rem set  UPXParams=--best --all-methods --crp-ms=999999 --overlay=strip
set UPXParams=--ultra-brute
set  RARParams=a -m5
rem clean unnedeed files
call clean
rem packing bin files
%UPXPath% %UPXParams% ./bin/Release/*.exe ./bin/Release/DLL/*.dll ./bin/Release/Plugins/*.dll
rm ./bin/Release/*.upx
rem creating archivs
%RarPath% %RARParams% FRACTALS-SRC.RAR ./src ./doc ./prj
%RarPath% %RARParams% FRACTALS-EXE.RAR ./bin/Release ./doc

echo on