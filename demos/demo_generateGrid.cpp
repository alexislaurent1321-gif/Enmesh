#include <iostream>

#include "mesh/mesh.h"
#include "mesh/mesh_analysis.h"
#include "mesh/mesh_smoothing.h"
#include "io/exportToVTK.h"
#include "mesh/mesh_triangulation.h"

/** @file triangulation.cpp
 * @brief A simple demo to generate a grid mesh, perform Delaunay triangulation on it, analyze the resulting mesh, and export it to VTK format for visualization in tools like ParaView.
 */

int main() {

    Enmesh::Mesh<Enmesh::Quad> gridMesh = Enmesh::generateGrid<Enmesh::Quad>(5, 5, 1.f, 1.f);   // Generate a regular grid 

    Enmesh::analyzeMesh<Enmesh::Quad>(gridMesh);
    Enmesh::exportToVTK<Enmesh::Quad>("output.vtk", gridMesh);

    return 0;
}