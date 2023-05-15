@echo off

title Ianium_Build

:: Directory variables
set RESOURCES_DIR=%CURRENT_WORKING_DIR%\resources

set IANIUM_DIR=%CD%
set IANIUM_SRC_DIR=%IANIUM_DIR%\src
set IANIUM_DEPS_DIR=%IANIUM_DIR%\dependencies
set IANIUM_SOL_PATH=%IANIUM_DIR%\ianium.sln
set IANIUM_TEMP_OUT_PATH=%IANIUM_DIR%\ianium

:: Build all dependencies
if exist %IANIUM_DEPS_DIR% rmdir %IANIUM_DEPS_DIR% /s /q
mkdir %IANIUM_DEPS_DIR%

echo Extracting SDL2 library...
powershell Expand-Archive %RESOURCES_DIR%\SDL2.zip -DestinationPath %IANIUM_DEPS_DIR%
echo SDL2 succesfully extracted

echo Extracting OpenCV library...
powershell Expand-Archive %RESOURCES_DIR%\opencv.zip -DestinationPath %IANIUM_DEPS_DIR%
echo OpenCV succesfully extracted 

:: Compile plugin
echo Compiling ianium...

rmdir %IANIUM_DIR%\bin /s /q

msbuild %IANIUM_SOL_PATH% /t:ianium /p:platform=x64 /p:configuration=Debug
msbuild %IANIUM_SOL_PATH% /t:ianium /p:platform=x64 /p:configuration=Release

echo Ianium succesfully compiled

:: Structuring files to be moved to test project
echo Collecting plugin's essential files...

if exist %IANIUM_TEMP_OUT_PATH% rmdir %IANIUM_TEMP_OUT_PATH% /s /q
mkdir %IANIUM_TEMP_OUT_PATH%

copy %IANIUM_DIR%\bin\*.dll %IANIUM_TEMP_OUT_PATH%
for /r %IANIUM_DEPS_DIR% %%f in (*.dll) do copy "%%f" %IANIUM_TEMP_OUT_PATH%

mkdir %IANIUM_TEMP_OUT_PATH%\lib
copy %IANIUM_DIR%\bin\*.lib %IANIUM_TEMP_OUT_PATH%\lib

mkdir %IANIUM_TEMP_OUT_PATH%\include
xcopy /s %IANIUM_SRC_DIR% %IANIUM_TEMP_OUT_PATH%\include
for /r %IANIUM_TEMP_OUT_PATH%\include %%f in (*.cpp) do del "%%f"

echo Plugin files succesfully collected