cd "$(dirname "$0")/.."

echo "Compilation in progress..."

cmake -B build
cmake --build build --target triangulation2 --config Release

if [ -f "./build/triangulation2" ]; then
    ./build/triangulation2
elif [ -f "./build/Release/triangulation2" ]; then
    ./build/Release/triangulation2
else
    echo "Error: Executable not found."
fi

paraview output.vtk