#include "mesh/mesh.h"
#include "io/exportToVTK.h"
#include "io/loadMsh.h"
#include "mesh/mesh_analysis.h"

/** @file demo_analyzer3D.cpp
 * @brief A simple demo to load a 3D mesh from a MSH file, analyze it, and print out basic statistics about the mesh quality. It also exports the mesh to VTK format for visualization in tools like ParaView.
 */

 int main() {
    Mesh<Tetrahedron> mesh;
    loadMsh<Tetrahedron>(mesh, "models/sphere.msh");
    // exportToVTK("output.vtk", mesh);
  
    size_t uniqueEdges = countUniqueEdges<Tetrahedron>(mesh);
    std::cout << "Number of unique edges: " << uniqueEdges << std::endl;

    // Mesh<Triangle> mesh;
    // loadMsh<Triangle>(mesh, "models/disk.msh");
    
    // size_t uniqueEdges = countUniqueEdges<Triangle>(mesh);
    // analyzeMesh<Triangle>(mesh);
    // std::cout << "Number of unique edges: " << uniqueEdges << std::endl;

    // exportToVTK("output.vtk", mesh);

   return 0;
 }