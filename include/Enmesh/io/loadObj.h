#ifndef LOAD_OBJ_H
#define LOAD_OBJ_H

#include "mesh/mesh.h"

namespace Enmesh {

/**
 * @brief  Load a mesh from an OBJ file using tinyobjloader
 * 
 * @param path Path to the OBJ file to load 
 * @return true 
 * @return false 
 */
template <typename T>
bool loadObj(Mesh<T>& mesh, const std::string& path);


} // namespace Enmesh

#endif

