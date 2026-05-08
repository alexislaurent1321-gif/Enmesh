#include <iostream>

#include "mesh/mesh.h"
#include "io/exportToVTK.h"
#include "mesh/mesh_analysis.h"
#include "io/loadMsh.h"

using namespace Enmesh;

/** @file analyzer.cpp
 * @brief A simple demo to load a mesh from an MSH file, analyze it, and print out basic statistics about the mesh quality. It also exports the mesh to VTK format for visualization in tools like ParaView.
 */

int main() {
    
    Mesh<Quad> mesh;

    loadMsh<Quad>(mesh, "models/square.msh");
    
    analyzeMesh<Quad>(mesh);

    std::cout << "Exporting mesh to VTK format..." << std::endl;
    exportToVTK<Quad>("output.vtk", mesh);
    
    return 0;
}

