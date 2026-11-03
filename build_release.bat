@echo off
setlocal EnableExtensions
chcp 65001 >nul

rem ============================================================
rem  KickPot - one-click release build (Windows, VS 2022, Qt 6)
rem  1) Edit QT_DIR below if Qt is installed somewhere else.
rem  2) Double-click this file.
rem  Output: dist\KickPot-Windows.zip
rem ============================================================

if "%QT_DIR%"=="" set "QT_DIR=C:\Qt\6.8.1\msvc2022_64"

if not exist "%QT_DIR%\bin\windeployqt.exe" (
    echo [ERROR] Qt not found at: %QT_DIR%
    echo Edit QT_DIR in this file to match your Qt install folder.
    pause & exit /b 1
)

set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist "%VSWHERE%" (
    echo [ERROR] Visual Studio 2022 not found.
    pause & exit /b 1
)

set "VSPATH="
for /f "usebackq delims=" %%i in (`"%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set "VSPATH=%%i"
if "%VSPATH%"=="" (
    echo [ERROR] "Desktop development with C++" workload is not installed.
    pause & exit /b 1
)

call "%VSPATH%\VC\Auxiliary\Build\vcvars64.bat" || (pause & exit /b 1)

rem CMake and Ninja that ship with Visual Studio.
set "PATH=%VSPATH%\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin;%VSPATH%\Common7\IDE\CommonExtensions\Microsoft\CMake\Ninja;%PATH%"

cd /d "%~dp0"

echo.
echo === Configuring ===
cmake -S . -B build-release -G Ninja -DCMAKE_BUILD_TYPE=Release "-DCMAKE_PREFIX_PATH=%QT_DIR%" || (pause & exit /b 1)

echo.
echo === Building ===
cmake --build build-release || (pause & exit /b 1)

echo.
echo === Collecting files ===
if exist dist rmdir /s /q dist
mkdir dist\KickPot
copy /y build-release\KickPot.exe dist\KickPot\ >nul || (pause & exit /b 1)
"%QT_DIR%\bin\windeployqt.exe" --release --no-translations dist\KickPot\KickPot.exe || (pause & exit /b 1)

echo.
echo === Creating ZIP ===
powershell -NoProfile -Command "Compress-Archive -Path 'dist\KickPot' -DestinationPath 'dist\KickPot-Windows.zip' -Force" || (pause & exit /b 1)

echo.
echo DONE: %CD%\dist\KickPot-Windows.zip
echo Run: dist\KickPot\KickPot.exe
pause
