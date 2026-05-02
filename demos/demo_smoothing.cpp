#include <iostream>

#include "mesh/mesh.h"
#include "mesh/mesh_analysis.h"
#include "mesh/mesh_smoothing.h"
#include "io/exportToVTK.h"
#include "mesh/mesh_triangulation.h"


/** @file smoothing.cpp
 * @brief A simple demo to generate a grid mesh, perform Delaunay triangulation on it, analyze the resulting mesh, and export it to VTK format for visualization in tools like ParaView.
 */

int main() {
    
    // Triangulation test on a grid

    // Example of generating a grid mesh and exporting it
    Enmesh::Mesh<Enmesh::Triangle> irregularMesh;
    generateRandomPoints(irregularMesh, 25, 1.f, 1.f);

    Enmesh::triangulate(irregularMesh); // Perform Delaunay triangulation on the grid mesh

    Enmesh::smooth(irregularMesh, 100, 1.f); // Apply smoothing to improve triangle quality

    Enmesh::analyzeMesh<Enmesh::Triangle>(irregularMesh);
    Enmesh::exportToVTK("output.vtk", irregularMesh);

    return 0;
}

