@echo off
REM This script will compile all files with .cpp extension in the parent directory
REM Visual Studio 2022 (17.5) C++ modules version

REM See https://learn.microsoft.com/en-us/cpp/cpp/tutorial-import-stl-named-module?view=msvc-170
if not exist std.obj (
  echo Building Standard Library module objects, please wait...
  cl /std:c++latest /EHsc /nologo /W4 /MTd /c "%VCToolsInstallDir%\modules\std.ixx" "%VCToolsInstallDir%\modules\std.compat.ixx"
)

set failures=0
for %%f in (..\*.cpp) do echo %%f... && cl /std:c++latest /EHsc /MTd /W4 /DEOF=-1 %%f >nul 2>nul || echo Failed to compile %%f && set /A failures=failures+1
echo A total of %failures% files failed to compile.
