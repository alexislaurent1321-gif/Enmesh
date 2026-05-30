echo "Compilation in progress..."

cmake -B build
cmake --build build --target generateGrid --config Release

if [ -f "./build/generateGrid" ]; then
    ./build/generateGrid
elif [ -f "./build/Release/generateGrid" ]; then
    ./build/Release/generateGrid
else
    echo "Error: Executable not found."
fi

paraview output.vtk