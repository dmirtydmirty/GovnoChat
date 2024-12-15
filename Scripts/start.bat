@echo off
setlocal enabledelayedexpansion

set INI_FILE=.ini

for /f "tokens=1,2 delims==" %%A in ('findstr /r "^[^;]" "%INI_FILE%"') do (
    set "%%A=%%B"
)

del %LOG_FILE%
start /b cmd /c  "docker run --name %CONTAINER_NAME% -p %PORT%:15001 --rm ghcr.io/dmirtydmirty/govnochat:%VERSION%" >> %LOG_FILE% 2>&1

endlocal
