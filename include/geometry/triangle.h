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

/**
 * @brief A struct representing a triangle in the mesh
 * 
 */
struct Triangle {

    std::array<int, 3> v;   ///< Indices of the vertices that form the triangle
    bool isBad = false;     ///< Flag used in Delaunay triangulation to mark triangles that need to be removed
    
    /**<brief Check if the triangle contains a specific edge
     * @param v1 index of the first vertex of the edge
     * @param v2 index of the second vertex of the edge
     */
    bool containsEdge(int v1, int v2) const;
};