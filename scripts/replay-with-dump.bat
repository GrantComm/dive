:: Copyright 2025 Google LLC
::
:: Licensed under the Apache License, Version 2.0 (the "License");
:: you may not use this file except in compliance with the License.
:: You may obtain a copy of the License at
::
:: http://www.apache.org/licenses/LICENSE-2.0
::
:: Unless required by applicable law or agreed to in writing, software
:: distributed under the License is distributed on an "AS IS" BASIS,
:: WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
:: See the License for the specific language governing permissions and
:: limitations under the License.

:: Usage: replay-with-dump.bat <GFXR_filename>.gfxr <GFXA_filename>.gfxa

@echo off
setlocal

IF "%~1"=="" (
    echo Usage: replay-with-dump.bat GFXR [GFXA]
    exit /b 1
)

SET GFXR=%~1

IF NOT "%GFXR:~-5%"==".gfxr" (
    echo Error: First argument GFXR must have a .gfxr extension.
    exit /b 1
)

FOR %%i IN ("%GFXR%") DO SET GFXR_BASENAME=%%~nxi
SET BUILD_DIR=../build
SET JSON_BASENAME=dump.json
SET JSON=%BUILD_DIR%/%JSON_BASENAME%
:: Fairly reliable directory on remote device, as long as app has MANAGE_EXTERNAL_STORAGE permissions.
:: /data/local/tmp doesn't work on all devices tested.
SET REMOTE_TEMP_DIR=/sdcard/Download
SET PUSH_DIR=%REMOTE_TEMP_DIR%/replay
SET DUMP_DIR=%REMOTE_TEMP_DIR%/dump

SET GFXR_BASE_PATH=%BUILD_DIR%/gfxr_dump_resources

IF NOT EXIST "%BUILD_DIR%" (
    echo Error: %BUILD_DIR% folder does not exist. Please build the project first.
    exit /b 1
)

IF EXIST "%GFXR_BASE_PATH%/Debug/gfxr_dump_resources.exe" (
    SET "GFXR_DUMP_RESOURCES=%GFXR_BASE_PATH%/Debug/gfxr_dump_resources.exe"
    GOTO :GFXR_DUMP_RESOURCES_FOUND
) ELSE IF EXIST "%GFXR_BASE_PATH%/Release/gfxr_dump_resources.exe" (
    SET "GFXR_DUMP_RESOURCES=%GFXR_BASE_PATH%/Release/gfxr_dump_resources.exe"
    GOTO :GFXR_DUMP_RESOURCES_FOUND
) ELSE IF EXIST "%GFXR_BASE_PATH%/gfxr_dump_resources.exe" (
    SET "GFXR_DUMP_RESOURCES=%GFXR_BASE_PATH%/gfxr_dump_resources.exe"
    GOTO :GFXR_DUMP_RESOURCES_FOUND
)
echo Error: gfxr_dump_resources.exe not found in %BUILD_DIR%
exit /b 1

:GFXR_DUMP_RESOURCES_FOUND
echo Debug: Found gfxr_dump_resources.exe at: "%GFXR_DUMP_RESOURCES%"

SET GFXRECON=../third_party/gfxreconstruct/android/scripts/gfxrecon.py
SET REPLAY_PACKAGE=com.lunarg.gfxreconstruct.replay

:: Uninstall first since install can fail if the APK has a different cert from the one installed (i.e. it was built on another machine)
adb shell pm path "%REPLAY_PACKAGE%" >nul
if %ERRORLEVEL% EQU 0 (
    adb uninstall "%REPLAY_PACKAGE%"
)
python "%GFXRECON%" install-apk ../install/gfxr-replay.apk
IF %ERRORLEVEL% NEQ 0 (
    echo Could not install replay APK.
    exit /b %ERRORLEVEL%
)

:: Currently, REMOTE_TEMP_DIR is /sdcard/Download. Ensure the app has permissions to use it
:: was not required on all devices tested but doesn't hurt.
adb shell appops set "%REPLAY_PACKAGE%" MANAGE_EXTERNAL_STORAGE allow

adb logcat -c

call "%GFXR_DUMP_RESOURCES%" --last_draw_only "%GFXR%" "%JSON%"
IF %ERRORLEVEL% NEQ 0 (
    echo Error running gfxr_dump_resources.
    exit /b %ERRORLEVEL%
)

:: Remove the previous folders if they already exist
adb shell rm -rf "%DUMP_DIR%"
adb shell rm -rf "%PUSH_DIR%"

adb shell mkdir -p "%PUSH_DIR%"
adb shell mkdir -p "%DUMP_DIR%"
adb push "%GFXR%" "%JSON%" "%PUSH_DIR%"
IF %ERRORLEVEL% NEQ 0 (
    echo Error pushing files to device.
    exit /b %ERRORLEVEL%
)

if "%~2"=="" (
    goto REPLAY
)

SET GFXA=%~2
adb push "%GFXA%" "%PUSH_DIR%"
IF %ERRORLEVEL% NEQ 0 (
    echo Error pushing GFXA to device.
    exit /b %ERRORLEVEL%
)

:REPLAY
:: This is to make sure pushing is finished
timeout /t 10 /nobreak >nul

python "%GFXRECON%" replay ^
    --dump-resources "%PUSH_DIR%/%JSON_BASENAME%" ^
    --dump-resources-dir "%DUMP_DIR%" ^
    "%PUSH_DIR%/%GFXR_BASENAME%"
IF %ERRORLEVEL% NEQ 0 (
    echo Error running gfxrecon replay.
    exit /b %ERRORLEVEL%
)

:: This is to make sure running pidof after the app starts.
timeout /t 10 /nobreak >nul

:WAIT_FOR_REPLAY
adb shell pidof "%REPLAY_PACKAGE%" >nul 2>&1
IF %ERRORLEVEL% EQU 0 (
    timeout /t 1 /nobreak >nul
    GOTO :WAIT_FOR_REPLAY
)

adb logcat -d -s gfxrecon

adb pull "%DUMP_DIR%"
IF %ERRORLEVEL% NEQ 0 (
    echo Error pulling replay dumped resources.
    exit /b %ERRORLEVEL%
)

adb shell rm -rf "%DUMP_DIR%"
adb shell rm -rf "%PUSH_DIR%"

endlocal
EXIT /b 0
