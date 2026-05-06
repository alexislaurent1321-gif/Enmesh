#ifndef EXPORT_TO_VTK_H
#define EXPORT_TO_VTK_H

#include "mesh/mesh.h"

namespace Enmesh {

/** 
 * @brief Exports the mesh data to a VTK file for visualization in Paraview
 * @param filename The name of the output VTK file
 * @param mesh The mesh object containing vertices, triangles, and quality ratios
*/
template <typename T>
void exportToVTK(const std::string& filename, const Mesh<T>& mesh);

} // namespace Enmesh

#include "../../src/io/exportToVTK.tpp"

#endif
