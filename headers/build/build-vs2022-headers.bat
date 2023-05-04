@echo off
REM This script will compile all files with .cpp extension in the parent directory
REM Visual Studio 2022 (17.5) header files version

set failures=0
for %%f in (..\*.cpp) do echo %%f... && cl /std:c++latest /EHsc /DEOF=-1 %%f >nul 2>nul || echo Failed to compile %%f && set /A failures=failures+1
echo A total of %failures% files failed to compile.
