@echo off
setlocal

cd /d "%~dp0.."

echo --- Compilation in progress... ---

cmake -B build
cmake --build build --target smoothing --config Release

if exist "build\smoothing.exe" (
    "build\smoothing.exe"
) else if exist "build\Release\smoothing.exe" (
    "build\Release\smoothing.exe"
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