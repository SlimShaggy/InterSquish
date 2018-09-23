@echo off
rem SetCRC\SetCRC IS.exe suvi
rem zip iss1704 -r -9 IS*.exe *.diz *.txt *.cfg SCRIPTS\*.* DOC\RUS\*.* DOC\ENG\*.*
rem rar a iss -m5 -s IS*.exe *.diz *.txt *.cfg SCRIPTS\*.* DOC\RUS\*.* DOC\ENG\*.*
setlocal
set filename=iss.zip
if exist %filename% (del %filename%)
7z a -mx=9 %filename% IS*.exe *.diz *.txt *.cfg SCRIPTS\*.* DOC\RUS\*.* DOC\ENG\*.*
endlocal