#include <iostream>

#include "mesh.h"

// Main function to load a mesh from an OBJ file, analyze it, and print out basic statistics about the mesh quality
int main() {
    Mesh mesh;

    if (!mesh.loadObj("models/demi_sphere_broken.obj")) {
        std::cerr << "Error loading OBJ file." << std::endl;
        return 1;
    }

    mesh.analyzeMesh();

    std::cout << "Exporting mesh to VTK format..." << std::endl;
    mesh.exportToVTK("output.vtk");    
    
    return 0;
}

