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
#include "geometry/tetra.h"

/** @file
 * @brief Mesh class definition
 */

namespace Enmesh {

/**
 * @brief A class representing a 3D mesh
 * 
 */
template <typename Element>
struct Mesh {

    // Datas
    std::vector<Point> vertices;                    ///< List of vertices in the mesh
    std::vector<Element> elements;              ///< List of elements defined by vertex indices

    using BoundaryType = std::conditional_t<Element::dimension == 3, Triangle, Edge>;
    
    std::vector<BoundaryType> boundaryElements;       ///< List of boundary elements for surface and boundary surfaces for volumes
    std::vector<size_t> boundaryTags;               ///< List of boundary tags corresponding to the
    
    std::vector<float> ratios;                      ///< aspect ratios of elements (for quality analysis)


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
