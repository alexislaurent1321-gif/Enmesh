cd "$(dirname "$0")/.."

echo "Compilation in progress..."

cmake -B build
cmake --build build --target smoothing --config Release

if [ -f "./build/smoothing" ]; then
    ./build/smoothing
elif [ -f "./build/Release/smoothing" ]; then
    ./build/Release/smoothing
else
    echo "Error: Executable not found."
fi

paraview output.vtk