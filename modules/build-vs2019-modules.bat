@echo off
REM This script will compile all files with .cpp extension in current directory
REM Visual Studio 2019 (16.8) C++ modules version

set failures=0
for %%f in (*.cpp) do echo %%f... && cl /std:c++latest /EHsc /experimental:module /MD /DEOF=-1 %%f >nul 2>nul || echo Failed to compile %%f && set /A failures=failures+1
echo A total of %failures% files failed to compile.
