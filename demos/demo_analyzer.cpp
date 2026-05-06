#include <iostream>

#include "mesh/mesh.h"
#include "io/exportToVTK.h"
#include "mesh/mesh_triangulation.h"
#include "mesh/mesh_analysis.h"
#include "io/loadObj.h"


/** @file analyzer.cpp
 * @brief A simple demo to load a mesh from an OBJ file, analyze it, and print out basic statistics about the mesh quality. It also exports the mesh to VTK format for visualization in tools like ParaView.
 */

int main() {
    
    Enmesh::Mesh<Enmesh::Quad> mesh;

    if (!Enmesh::loadObj<Enmesh::Quad>(mesh, "models/frame_quad.obj")) {
        std::cerr << "Error loading OBJ file." << std::endl;
        return 1;
    }
    
    Enmesh::analyzeMesh<Enmesh::Quad>(mesh);

    std::cout << "Exporting mesh to VTK format..." << std::endl;
    Enmesh::exportToVTK<Enmesh::Quad>("output.vtk", mesh);
    
    return 0;
}

