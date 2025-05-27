@echo off
:: ========================================================
:: WaveKit Windows Build Helper Script
:: ========================================================
:: Usage: 
::   - From root:    .\Scripts\Setup-Windows.bat [options]
::   - From Scripts: .\Setup-Windows.bat [options]
:: Options:
::   --no-demo      Exclude Demo project
::   --no-tests     Exclude Test directory
:: ========================================================

:: -- Capture script path --
for %%i in ("%~dp0.") do set "CALLER_DIR=%%~fi"
set "SCRIPT_PATH=%~f0"

:: -- Root detection --
set "ROOT_DIR=."
:find_root
if exist "%ROOT_DIR%\Build.lua" goto root_found
if exist "%ROOT_DIR%\.git" goto root_found
if "%ROOT_DIR%"=="%CD%" goto root_not_found
set "ROOT_DIR=%ROOT_DIR%\.."
goto find_root

:root_not_found
echo ERROR: Cannot locate project root
echo Tried finding either:
echo   - Build.lua
echo   - .git directory
echo Please run from within the WaveKit project
pause
exit /b 1

:root_found
:: Convert to absolute path
for %%i in ("%ROOT_DIR%") do set "ROOT_DIR=%%~fi"

:: -- Path configuration --
:: 1. Try standard Premake location
set "PREMAKE_PATH=%ROOT_DIR%\Vendor\Binaries\Premake\Windows\premake5.exe"

:: 2. Fallback to searching for premake
if not exist "%PREMAKE_PATH%" (
    where /r "%ROOT_DIR%" premake5.exe >nul 2>&1
    if not errorlevel 1 (
        for /f "delims=" %%p in ('where /r "%ROOT_DIR%" premake5.exe') do (
            set "PREMAKE_PATH=%%p"
            goto premake_found
        )
    )
    echo ERROR: Premake not found at:
    echo %PREMAKE_PATH%
    echo And no alternative premake5.exe found in project
    pause
    exit /b 1
)
:premake_found

:: -- Compute relative paths for display --
setlocal enabledelayedexpansion
set "REL_SCRIPT_PATH=!SCRIPT_PATH:%ROOT_DIR%\=!"
set "REL_PREMAKE_PATH=!PREMAKE_PATH:%ROOT_DIR%\=!"
endlocal & set "REL_SCRIPT_PATH=WaveKit\%REL_SCRIPT_PATH%" & set "REL_PREMAKE_PATH=WaveKit\%REL_PREMAKE_PATH%"

:: -- Main execution --
echo.
echo [WaveKit] Generating solution...
echo Script: %REL_SCRIPT_PATH%
echo Premake: %REL_PREMAKE_PATH%
echo.

pushd "%ROOT_DIR%"
"%PREMAKE_PATH%" --file="Build.lua" %* vs2022
if errorlevel 1 (
    echo ERROR: Generation failed (see above)
    popd
    pause
    exit /b 1
)
popd