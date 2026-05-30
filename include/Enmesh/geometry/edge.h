#ifndef EDGE_H
#define EDGE_H

#include <vector>
#include <array>
#include <iostream>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <string>


#include "geometry/point.h"

namespace Enmesh {

/**
 * @brief A struct representing an edge in the mesh
 * 
 */
struct Edge {

    static constexpr size_t type = 1;           ///< Gmsh element type for edges 
    static constexpr size_t numVertices = 2;    ///< Number of vertices in an edge
    static constexpr size_t dimension = 1;      ///< Dimension of the edge element

    std::array<size_t, 2> v;   ///< Indices of the vertices that form the edge
    bool operator==(const Edge& other) const {
        return (v[0] == other.v[0] && v[1] == other.v[1]) || (v[0] == other.v[1] && v[1] == other.v[0]);
    }
};

 /**
 * @brief A hash function for the Edge struct to allow it to be used in an unordered_set
 * 
 */
struct EdgeHash {
    size_t operator()(const Edge& e) const {
        return std::hash<size_t>{}(e.v[0]) ^ (std::hash<size_t>{}(e.v[1]) << 1); // Combine hashes of v[0] and v[1]
    }
};

} // namespace Enmesh

#endif  