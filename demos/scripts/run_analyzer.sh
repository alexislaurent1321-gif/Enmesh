cd "$(dirname "$0")/.."

echo "Compilation in progress..."

cmake -B build
cmake --build build --target analyzer --config Release

if [ -f "./build/analyzer" ]; then
    ./build/analyzer
elif [ -f "./build/Release/analyzer" ]; then
    ./build/Release/analyzer
else
    echo "Error: Executable not found."
fi

paraview output.vtk