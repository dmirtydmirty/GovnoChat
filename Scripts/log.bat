@echo off
setlocal enabledelayedexpansion

set INI_FILE=.ini

for /f "tokens=1,2 delims==" %%A in ('findstr /r "^[^;]" "%INI_FILE%"') do (
    set "%%A=%%B"
)

powershell -command "Get-Content %LOG_FILE% -Wait -Tail 30"

endlocal


