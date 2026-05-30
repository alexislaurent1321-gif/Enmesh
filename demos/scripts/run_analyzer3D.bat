@echo off
setlocal

cd /d "%~dp0.."

echo --- Compilation in progress... ---

cmake -B build
cmake --build build --target analyzer3D --config Release

if exist "build\analyzer3D.exe" (
    "build\analyzer3D.exe"
) else if exist "build\Release\analyzer3D.exe" (
    "build\Release\analyzer3D.exe"
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