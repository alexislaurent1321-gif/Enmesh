#ifndef TETRAHEDRON_H
#define TETRAHEDRON_H

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


namespace Enmesh {

struct Tetra {

    static constexpr size_t type = 4;           ///< Gmsh element type for tetrahedra 
    static constexpr size_t dimension = 3;      ///< Dimension of the tetrahedron element
    static constexpr size_t numVertices = 4;    ///< Number of vertices in a tetrahedron

    static constexpr size_t boundaryType = 2;           ///< Gmsh element type for boundary triangles
    static constexpr size_t boundaryDimension = 2;      ///< Dimension of the boundary element (triangle)
    static constexpr size_t boundaryNumVertices = 3;    ///< Number of vertices in a boundary triangle

    std::array<size_t, 4> v;   ///< Indices of the vertices that form the tetrahedron
    bool isBad = false;     ///< Flag used in Delaunay triangulation to mark tetrahedra that need to be removed

    /**
     * @brief Check if this tetrahedron is equal to another (same vertices, regardless of order)
     * @param other The other tetrahedron to compare with
     * @return true if the tetrahedra are equal, false otherwise
     */
    bool operator==(const Tetra& other) const;


    /**
     * @brief Check if the circumsphere of the tetrahedron contains a specific edge defined by two vertex indices
     * @param v1 index of the first vertex of the edge
     * @param v2 index of the second vertex of the edge
     */
    bool containsEdge(size_t v1, size_t v2) const;
};

} // namespace Enmesh

#endif 