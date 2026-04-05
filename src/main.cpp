#include <iostream>

#include "geometry/mesh.h"
#include "exportToVTK.h"
#include "triangulation.h"

// Main function to load a mesh from an OBJ file, analyze it, and print out basic statistics about the mesh quality
int main() {
    
    Mesh mesh;

    if (!mesh.loadObj("models/cube_high_res.obj")) {
        std::cerr << "Error loading OBJ file." << std::endl;
        return 1;
    }

    mesh.smooth(10, 1.f); 
    mesh.analyzeMesh();

    std::cout << "Exporting mesh to VTK format..." << std::endl;
    exportToVTK("output.vtk", mesh);

    // // Example of generating a grid mesh and exporting it
    // Mesh gridMesh;
    // generateGrid(gridMesh, 10, 10);

    // Delaunay delaunay;
    // delaunay.mesh = gridMesh;
    // gridMesh.triangles = delaunay.triangulate();
    // exportToVTK("output.vtk", gridMesh);

    
    return 0;
}

