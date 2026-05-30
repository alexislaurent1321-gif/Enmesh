@echo off
setlocal

cd /d "%~dp0.."

echo --- Compilation in progress... ---

cmake -B build
cmake --build build --target triangulation --config Release

if exist "build\triangulation.exe" (
    "build\triangulation.exe"
) else if exist "build\Release\triangulation.exe" (
    "build\Release\triangulation.exe"
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