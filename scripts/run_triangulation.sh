cd "$(dirname "$0")/.."

echo "Compilation in progress..."

cmake -B build
cmake --build build --target triangulation --config Release

if [ -f "./build/triangulation" ]; then
    ./build/triangulation
elif [ -f "./build/Release/triangulation" ]; then
    ./build/Release/triangulation
else
    echo "Error: Executable not found."
fi

paraview output.vtk