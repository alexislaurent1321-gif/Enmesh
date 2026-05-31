#include <iostream>

#include "mesh/mesh.h"
#include "mesh/mesh_analysis.h"
#include "mesh/mesh_smoothing.h"
#include "io/exportToVTK.h"
#include "mesh/mesh_triangulation.h"

/** @file smoothing.cpp
 * @brief A simple demo to generate a grid mesh, perform Delaunay triangulation on it, analyze the resulting mesh, and export it to VTK format for visualization in tools like ParaView.
 */

void generateRandomPoints(Enmesh::Mesh<Enmesh::Triangle>& mesh, int N, float Lx, float Ly);

int main() {

    // Example of generating a grid mesh and exporting it
    Enmesh::Mesh<Enmesh::Triangle> irregularMesh;
    generateRandomPoints(irregularMesh, 25, 1.f, 1.f);

    Enmesh::triangulate(irregularMesh); // Perform Delaunay triangulation on the grid mesh

    Enmesh::smooth(irregularMesh, 100, 1.f); // Apply smoothing to improve triangle quality

    Enmesh::analyzeMesh(irregularMesh);
    Enmesh::exportToVTK("output.vtk", irregularMesh);

    return 0;
}

// Function to generate N random points within a specified rectangular domain defined by Lx and Ly
void generateRandomPoints(Enmesh::Mesh<Enmesh::Triangle>& mesh, int N, float Lx, float Ly) {
    for (int i = 0; i < N; ++i) {
        float x = static_cast<float>(rand()) / RAND_MAX * Lx;
        float y = static_cast<float>(rand()) / RAND_MAX * Ly;
        mesh.vertices.push_back({x, y});
    }
}

