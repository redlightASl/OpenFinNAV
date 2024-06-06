@REM Excute in Windows CMD
@echo off
setlocal

set "currentDir=%CD%"
echo %currentDir% | findstr /i "build\script" >nul
if %errorlevel% equ 0 (
    echo Excute this file in the root of the project.
    exit /b 1
)

make clean
make build
endlocal
