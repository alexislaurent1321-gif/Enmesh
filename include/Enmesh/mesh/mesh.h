#ifndef MESH_H
#define MESH_H

#include <vector>
#include <array>
#include <iostream>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>


#include "geometry/point.h"
#include "geometry/edge.h"
#include "geometry/triangle.h"
#include "geometry/quad.h"
#include "geometry/tetrahedron.h"

/** @file
 * @brief Mesh class definition
 */

namespace Enmesh {


template <typename ElementType>
struct Boundary{
    std::vector<int> coord;     ///< List of boundary elements defined by vertex indices
    int tag = 0;                ///< Physical tag for boundary condition application
};


/**
 * @brief A class representing a 3D mesh
 * 
 */
template <typename ElementType>
struct Mesh {

    // Datas
    std::vector<Point> vertices;                    ///< List of vertices in the mesh
    std::vector<ElementType> elements;              ///< List of elements defined by vertex indices
    std::vector<float> ratios;                      ///< aspect ratios of elements (for quality analysis)
    std::vector<Boundary<ElementType>> boundaries;  ///< List of boundary conditions

    // Methods

    /**
     * @brief Get the number of vertices in the mesh
     * 
     */
    std::size_t getNumVertices() const { return vertices.size(); } 

    /**
     * @brief Get the number of elements in the mesh
     * 
     */
    std::size_t getNumElements() const { return elements.size(); } 
};

} // namespace Enmesh

#endif
