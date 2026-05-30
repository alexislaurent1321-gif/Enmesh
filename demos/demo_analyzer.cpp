#include <iostream>

#include "mesh/mesh.h"
#include "io/exportToVTK.h"
#include "mesh/mesh_analysis.h"
#include "io/loadMsh.h"

/** @file analyzer.cpp
 * @brief A simple demo to load a mesh from an MSH file, analyze it, and print out basic statistics about the mesh quality. It also exports the mesh to VTK format for visualization in tools like ParaView.
 */

int main() {
    
    Enmesh::Mesh<Enmesh::Quad> mesh;
    Enmesh::loadMsh(mesh, "models/grid_quad.msh");

    std::cout << "Boundary elements: ";
    for (const auto& element : mesh.boundaryElements) {
        std::cout << element.v1 << " " << element.v2 << std::endl;
    }
    std::cout << std::endl;


    std::cout << "Boundary tags: ";
    for (const auto& tag : mesh.boundaryTags) {
        std::cout << tag << " ";
    }
    std::cout << std::endl;
    
    Enmesh::analyzeMesh(mesh);
    Enmesh::exportToVTK("output.vtk", mesh);

    

    return 0;
}

