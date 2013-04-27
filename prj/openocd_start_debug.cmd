@echo on
rem @echo off
prompt=$g
call openocd_setup.cmd

rem start %OOCD_EXE% %OOCD_OPT% -f %OOCD_DBG_CONFIG%
rem %OOCD_EXE% %OOCD_OPT% -f %OOCD_DBG_CONFIG%
%OOCD_EXE% %OOCD_OPT% -f %OOCD_CONFIG%

pause

