@echo off
rem This script will compile all files with .cpp extension in current directory
rem Visual Studio 2022 (17.x) C++ modules version

set failures=0
for %%f in (*.cpp) do echo %%f... && cl /std:c++latest /EHsc /experimental:module /MD %%f >nul 2>nul || echo Failed to compile %%f && set /A failures=failures+1 
echo A total of %failures% files failed to compile.
