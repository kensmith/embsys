
set OOCD_INSTALLDIR=C:\Program Files\openocd-2007re204\bin
set OOCD_CFGDIR=C:\Program Files\openocd-2007re204\bin\configs

set OOCD_EXE="%OOCD_INSTALLDIR%\openocd-ftd2xx.exe"
rem set OOCD_EXE=%OOCD_INSTALLDIR%\openocd-pp.exe

rem The used interface either FTDI(=WinARM-JTAG, JTAGKEY etc.) or PP(="Wiggler")
rem set OOCD_INTERFACE=ftdi
rem set OOCD_INTERFACE=pp
set OOCD_INTERFACE=armusbocd

set OOCD_TARGET=lpc2378
rem set OOCD_OPT=-d 2
set OOCD_OPT=

rem set OOCD_DBG_CONFIG=openocd_dbg_%OOCD_TARGET%_%OOCD_INTERFACE%.cfg
rem set OOCD_FLASH_CONFIG=openocd_flash_%OOCD_TARGET%_%OOCD_INTERFACE%.cfg
set OOCD_CONFIG="%OOCD_CFGDIR%\%OOCD_TARGET%_%OOCD_INTERFACE%.cfg"
