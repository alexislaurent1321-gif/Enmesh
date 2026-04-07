@echo off
setlocal

cd /d "%~dp0.."

echo --- Compilation in progress... ---

cmake -B build
cmake --build build --target analyzer --config Release

if exist "build\analyzer.exe" (
    "build\analyzer.exe"
) else if exist "build\Release\analyzer.exe" (
    "build\Release\analyzer.exe"
) else (
    echo Error: Executable not found.
    pause
    exit /b 1
)

if exist "output.vtk" (
    echo Opening ParaView...
    start paraview output.vtk
) else (
    echo Error: output.vtk not found.
)

pause