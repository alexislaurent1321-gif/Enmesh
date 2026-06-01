#ifndef QUAD_H
#define QUAD_H

#include <vector>
#include <array>
#include <iostream>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>


#include "geometry/point.h"
#include "geometry/edge.h"

namespace Enmesh {

/**
 * @brief A struct representing a quad in the mesh
 * 
 */
struct Quad {

    static constexpr size_t type = 3;           ///< Gmsh element type for quads 
    static constexpr size_t dimension = 2;      ///< Dimension of the quad element
    static constexpr size_t numVertices = 4;    ///< Number of vertices in a quad

    static constexpr size_t boundaryType = 1;           ///< Gmsh element type for boundary edges
    static constexpr size_t boundaryDimension = 1;      ///< Dimension of the boundary element (edge)
    static constexpr size_t boundaryNumVertices = 2;    ///< Number of vertices in a boundary edge

    std::array<size_t, 4> v;   ///< Indices of the vertices that form the quad


    /**
     * @brief  Check if the quad contains a specific edge defined by two vertex indices
     * @param v1 index of the first vertex of the edge
     * @param v2 index of the second vertex of the edge
     */
    bool containsEdge(size_t v1, size_t v2) const;


    /**
    * @brief Overload the == operator to compare two quads based on their vertex indices
    * 
    * @param other The quad to compare with
    * @return true if the quads have the same vertex indices (regardless of order), false otherwise
    */
    bool operator==(const Quad& other) const {
        std::array<size_t, 4> sortedV1 = v;
        std::array<size_t, 4> sortedV2 = other.v;
        std::sort(sortedV1.begin(), sortedV1.end());
        std::sort(sortedV2.begin(), sortedV2.end());
        return sortedV1 == sortedV2;
    }

};


/** @brief A hash function for quads */
struct QuadHash {
    size_t operator()(const Quad& quad) const {
        // Combine the hashes of the four vertex indices to create a unique hash for the quad
        size_t h = std::hash<size_t>{}(quad.v[0]);
        h ^= std::hash<size_t>{}(quad.v[1]) + 0x9e3779b9 + (h << 6) + (h >> 2);  // Combine with the second vertex index
        h ^= std::hash<size_t>{}(quad.v[2]) + 0x9e3779b9 + (h << 6) + (h >> 2);  // Combine with the third vertex index
        h ^= std::hash<size_t>{}(quad.v[3]) + 0x9e3779b9 + (h << 6) + (h >> 2);  // Combine with the fourth vertex index
        return h;
    }
};

} // namespace Enmesh

#endif