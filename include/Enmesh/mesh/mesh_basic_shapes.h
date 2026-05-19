#ifndef BASIC_SHAPES_H
#define BASIC_SHAPES_H


#include "mesh/mesh.h"

namespace Enmesh {

/** 
 * @brief Generate a mesh grid of the specified dimensions and size
 * @param Nx Number of vertices in the x-direction
 * @param Ny Number of vertices in the y-direction
 * @param Lx The length of the grid in the x-direction
 * @param Ly The length of the grid in the y-direction
 * @return mesh grid
 */
template <typename ElementType>
Mesh<ElementType> generateGrid(int Nx, int Ny, float Lx, float Ly);


} // namespace Enmesh

#endif