@echo off
REM Run all test executables named test_*.exe in this directory (Windows)
for %%f in (test_*.exe) do (
    echo Running %%f...
    .\%%f
    echo.
    echo ----------------------
)
