@echo off

set GEN=perl ..\..\scripts\gendoc.pl
set SRC_PATH=source
set OUT_PATH=output

rem %GEN% -o=%OUT_PATH% %SRC_PATH%/reflex-main.txt
%GEN% -o=%OUT_PATH% %SRC_PATH%/reflex-build-meta-data.txt

