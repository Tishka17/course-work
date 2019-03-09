#this script is shell for inputting command from keyboard
@echo off
system cls
echo Fractals Analyzer by Tishka17
set Message = Input Command>
:begin
set /P Command = $(Message)
if ($(Command) == exit) goto end
logecho $resolve(Command)
$resolve(Command)
goto begin
:end
echo on