#include <iostream>

#include "mesh/mesh.h"
#include "mesh/mesh_analysis.h"
#include "mesh/mesh_smoothing.h"
#include "io/exportToVTK.h"
#include "mesh/mesh_triangulation.h"

/** @file triangulation.cpp
 * @brief A simple demo to generate a grid mesh, perform Delaunay triangulation on it, analyze the resulting mesh, and export it to VTK format for visualization in tools like ParaView.
 */


void generateGridPoints(Enmesh::Mesh<Enmesh::Triangle>& mesh, int Nx, int Ny, float Lx, float Ly);


int main() {

    Enmesh::Mesh<Enmesh::Triangle> gridMesh;
    generateGridPoints(gridMesh, 5, 5, 1.f, 1.f);   // Generate a regular grid of points

    Enmesh::triangulate(gridMesh); // Perform Delaunay triangulation on the grid mesh

    // Display Boundaries (optionnal)
    gridMesh.boundaryElements = Enmesh::getBoundaryEdges(gridMesh);     // Extract boundary edges for visualization
    gridMesh.boundaryTags.resize(gridMesh.boundaryElements.size(), 1);  // Assign a boundary tag to all boundary edges for visualization

    Enmesh::analyzeMesh(gridMesh);

    Enmesh::exportToVTK("output.vtk", gridMesh);

    return 0;
}


// Function to generate a regular grid of points 
void generateGridPoints(Enmesh::Mesh<Enmesh::Triangle>& mesh, int Nx, int Ny, float Lx, float Ly) {
    float dx = Lx / (Nx - 1);
    float dy = Ly / (Ny - 1);

    for (int j = 0; j < Ny; ++j) {
        for (int i = 0; i < Nx; ++i) {
            mesh.vertices.push_back({i * dx, j * dy});
        }
    }
}

