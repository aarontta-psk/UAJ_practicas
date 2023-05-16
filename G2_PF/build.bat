@echo off

title Ianium_Build

:: Directory variables
set CURRENT_WORKING_DIR=%CD%
set RESOURCES_DIR=%CURRENT_WORKING_DIR%\resources

set TEST_PRJ_DIR=%CD%\test_sdl
set TEST_PRJ_DEPS_DIR=%TEST_PRJ_DIR%\dependencies

:: Building ianium
cd %CURRENT_WORKING_DIR%\ianium
call build.bat
cd %CURRENT_WORKING_DIR%

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

:: Moving assets and scripts to test project
echo Moving files

mkdir %TEST_PRJ_DIR%\exe\assets
mkdir %TEST_PRJ_DIR%\exe\scripts
xcopy /e /s /i %TEST_PRJ_DIR%\assets %TEST_PRJ_DIR%\exe\assets
xcopy /e /s /i %TEST_PRJ_DIR%\scripts %TEST_PRJ_DIR%\exe\scripts

echo Files succesfully moved

:: Moving assets and scripts to test project
echo Compiling project

msbuild %TEST_PRJ_DIR%\test_sdl.sln /t:test_sdl /p:platform=x64 /p:configuration=Debug
@REM msbuild %TEST_PRJ_DIR%\test_sdl.sln /t:test_sdl /p:platform=x64 /p:configuration=Release

echo Project compiled