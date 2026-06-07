#ifndef TRIANGLE_H
#define TRIANGLE_H

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
 * @brief A struct representing a triangle in the mesh
 * 
 */
struct Triangle {

    static constexpr size_t type = 2;           ///< Gmsh element type for triangles 
    static constexpr size_t VTKType = 5;        ///< VTK element type for triangles
    static constexpr size_t dimension = 2;      ///< Dimension of the triangle element
    static constexpr size_t numVertices = 3;    ///< Number of vertices in a triangle

    static constexpr size_t boundaryType = 1;           ///< Gmsh element type for boundary edges
    static constexpr size_t boundaryVTKType = 3;        ///< VTK element type for boundary edges
    static constexpr size_t boundaryDimension = 1;      ///< Dimension of the boundary element (edge)
    static constexpr size_t boundaryNumVertices = 2;    ///< Number of vertices in a boundary edge

    std::array<size_t, 3> v;    ///< Indices of the vertices that form the triangle
    bool isBad = false;         ///< Flag used in Delaunay triangulation to mark triangles that need to be removed


    /**
     * @brief  Check if the circum circle of the triangle contains a specific edge defined by two vertex indices
     * @param v1 index of the first vertex of the edge
     * @param v2 index of the second vertex of the edge
     */
    bool containsEdge(size_t v1, size_t v2) const;


    /** 
     * @brief Check if the circum circle of the triangle contains a specific point
     * @param vertices The list of vertices in the mesh
     * @param point The point to check
     * @return true if point is inside the circum circle, false otherwise
     */
    bool containsPoint(const std::vector<Point>& vertices, const Point& point);

    /**
    * @brief Overload the == operator to compare two triangles based on their vertex indices
    * 
    * @param other The triangle to compare with
    * @return true if the triangles have the same vertex indices (regardless of order), false otherwise
    */
    bool operator==(const Triangle& other) const {
        std::array<size_t, 3> sortedV1 = v;
        std::array<size_t, 3> sortedV2 = other.v;
        std::sort(sortedV1.begin(), sortedV1.end());
        std::sort(sortedV2.begin(), sortedV2.end());
        return sortedV1 == sortedV2;
    }

};


/** @brief A hash function for triangles */
struct TriangleHash {
    size_t operator()(const Triangle& triangle) const {
        // Combine the hashes of the three vertex indices to create a unique hash for the triangle
        size_t h = std::hash<size_t>{}(triangle.v[0]);
        h ^= std::hash<size_t>{}(triangle.v[1]) + 0x9e3779b9 + (h << 6) + (h >> 2);  // Combine with the second vertex index
        h ^= std::hash<size_t>{}(triangle.v[2]) + 0x9e3779b9 + (h << 6) + (h >> 2);  // Combine with the third vertex index
        return h;
    }
};

} // namespace Enmesh

#endif