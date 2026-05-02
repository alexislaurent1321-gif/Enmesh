#include "mesh/mesh.h"
#include "io/exportToVTK.h"
#include "io/loadMsh.h"
#include "mesh/mesh_analysis.h"

/** @file demo_analyzer3D.cpp
 * @brief A simple demo to load a 3D mesh from a MSH file, analyze it, and print out basic statistics about the mesh quality. It also exports the mesh to VTK format for visualization in tools like ParaView.
 */

 int main() {
    Enmesh::Mesh<Enmesh::Tetrahedron> mesh;
    Enmesh::loadMsh<Enmesh::Tetrahedron>(mesh, "models/sphere.msh");
  
    Enmesh::analyzeMesh<Enmesh::Tetrahedron>(mesh);
    Enmesh::exportToVTK("output.vtk", mesh);

    std::cout << "boundaries tetrahedra : " << Enmesh::getBoundaryTriangles(mesh).size() << std::endl;


   return 0;
 }