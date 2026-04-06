#include <iostream>

#include "geometry/mesh.h"
#include "visualization/exportToVTK.h"
#include "mesh_generation/triangulation.h"

void generateGrid(Mesh& mesh, int width, int height, float step) {
    mesh.vertices.clear();
    mesh.triangles.clear();

    // 1. Génération des sommets (Vertices)
    for (int j = 0; j <= height; ++j) {
        for (int i = 0; i <= width; ++i) {
            mesh.vertices.push_back({ (float)i * step, (float)j * step });
        }
    }

    // 2. Génération des triangles (Indices)
    int verticesPerRow = width + 1;
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            int root = i + (j * verticesPerRow);
            
            // Triangle 1 (Bas-Gauche)
            mesh.triangles.push_back({ root, root + 1, root + verticesPerRow });
            
            // Triangle 2 (Haut-Droite)
            mesh.triangles.push_back({ root + 1, root + verticesPerRow + 1, root + verticesPerRow });
        }
    }
}

// Main function to load a mesh from an OBJ file, analyze it, and print out basic statistics about the mesh quality
int main() {
    
    // Mesh mesh;

    // if (!mesh.loadObj("models/cube_high_res.obj")) {
    //     std::cerr << "Error loading OBJ file." << std::endl;
    //     return 1;
    // }

    // mesh.smooth(10, 1.f); 
    // mesh.analyzeMesh();

    // std::cout << "Exporting mesh to VTK format..." << std::endl;
    // exportToVTK("output.vtk", mesh);

    // Example of generating a grid mesh and exporting it
    Mesh gridMesh;
    generateGrid(gridMesh, 3, 3, 1.f, 1.f);

    Delaunay delaunay;
    delaunay.mesh = gridMesh;
    delaunay.mesh.triangles = delaunay.triangulate();
    // exportToVTK("output.vtk", delaunay.mesh);

    delaunay.mesh.analyzeMesh();
    
    return 0;
}

