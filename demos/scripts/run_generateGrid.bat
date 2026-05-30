@echo off
setlocal

echo --- Compilation in progress... ---

cmake -B build
cmake --build build --target generateGrid --config Release

if exist "build\generateGrid.exe" (
    "build\generateGrid.exe"
) else if exist "build\Release\generateGrid.exe" (
    "build\Release\generateGrid.exe"
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