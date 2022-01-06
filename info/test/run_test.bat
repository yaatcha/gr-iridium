



gr_satellites || if !ERRORLEVEL! LEQ 1 cmd /c "exit /b 0"
IF %ERRORLEVEL% NEQ 0 exit /B 1
jy1sat_ssdv || if !ERRORLEVEL! LEQ 1 cmd /c "exit /b 0"
IF %ERRORLEVEL% NEQ 0 exit /B 1
smog_p_spectrum || if !ERRORLEVEL! LEQ 1 cmd /c "exit /b 0"
IF %ERRORLEVEL% NEQ 0 exit /B 1
if not exist %PREFIX%\\Library\\include\\satellites\\api.h exit 1
IF %ERRORLEVEL% NEQ 0 exit /B 1
if not exist %PREFIX%\\Library\\bin\\gnuradio-satellites.dll exit 1
IF %ERRORLEVEL% NEQ 0 exit /B 1
if not exist %PREFIX%\\Library\\lib\\gnuradio-satellites.lib exit 1
IF %ERRORLEVEL% NEQ 0 exit /B 1
if not exist %PREFIX%\\Library\\share\\gnuradio\\grc\\blocks\\satellites_decode_rs.block.yml exit 1
IF %ERRORLEVEL% NEQ 0 exit /B 1
if not exist %PREFIX%\\Library\\share\\gnuradio\\grc\\blocks\\satellites_ax100_decode.block.yml exit 1
IF %ERRORLEVEL% NEQ 0 exit /B 1
if not exist %PREFIX%\\Library\\share\\gnuradio\\grc\\blocks\\satellites_check_crc.block.yml exit 1
IF %ERRORLEVEL% NEQ 0 exit /B 1
exit /B 0
