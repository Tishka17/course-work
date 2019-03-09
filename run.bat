@echo off
set interface=GUI_.exe
set console=console.exe
set release=bin\Release\
set debug=bin\Debug\
set path=%release%
set exe=%interface%
set parent=..\..\
if -%1==- goto execute
if %1==debug set path=%debug%
if %1==console set exe=%console%
if -%2==- goto execute
if %2==debug set path=%debug%
if %2==console set exe=%console%
if %2==release set path=%release%
if %2==interface set exe=%interface%

:execute
cd %path%
call %exe%
cd %parent%

echo on