@echo off

title Ianium_Build

:: Directory variables
set CURRENT_WORKING_DIR=%CD%

set RESOURCES_DIR=%CD%\resources

set IANIUM_DIR=%CD%\ianium
set IANIUM_SRC_DIR=%IANIUM_DIR%\src
set IANIUM_DEPS_DIR=%IANIUM_DIR%\dependencies
set IANIUM_SOL_PATH=%IANIUM_DIR%\ianium.sln
set IANIUM_TEMP_PATH=%IANIUM_DIR%\ianium

set TEST_PRJ_DIR=%CD%\test_sdl
set TEST_PRJ_DEPS_DIR=%TEST_PRJ_DIR%\dependencies

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

if exist %IANIUM_DIR%\ianium rmdir %IANIUM_DIR%\ianium /s /q
mkdir %IANIUM_DIR%\ianium

copy %IANIUM_DIR%\bin\*.dll %IANIUM_TEMP_PATH%
for /r %IANIUM_DEPS_DIR% %%f in (*.dll) do copy "%%f" %IANIUM_TEMP_PATH%

mkdir %IANIUM_TEMP_PATH%\lib
copy %IANIUM_DIR%\bin\*.lib %IANIUM_TEMP_PATH%\lib

mkdir %IANIUM_TEMP_PATH%\include
xcopy /s %IANIUM_SRC_DIR% %IANIUM_TEMP_PATH%\include

for /r %IANIUM_TEMP_PATH%\include %%f in (*.cpp) do del "%%f"

echo Plugin files succesfully collected

:: Moving plugin to test project
echo Moving plugin files...

if exist %TEST_PRJ_DEPS_DIR% rmdir %TEST_PRJ_DEPS_DIR% /s /q
mkdir %TEST_PRJ_DEPS_DIR%

powershell Expand-Archive %RESOURCES_DIR%\SDL2.zip -DestinationPath %TEST_PRJ_DEPS_DIR%
for /r %TEST_PRJ_DEPS_DIR%\SDL2 %%f in (*.dll) do del "%%f"

move %IANIUM_DIR%\ianium %TEST_PRJ_DEPS_DIR%
if exist %TEST_PRJ_DIR%\exe for /r %TEST_PRJ_DIR%\exe %%f in (*.dll) do del "%%f"
if not exist %TEST_PRJ_DIR%\exe mkdir %TEST_PRJ_DIR%\exe

xcopy %TEST_PRJ_DEPS_DIR%\ianium\*.dll %TEST_PRJ_DIR%\exe 

echo Plugin files succesfully moved