#include <numeric>
#include <algorithm>

#include "mesh/mesh_analysis.h"

namespace Enmesh {

// Quality analysis

template <typename T>
size_t countUniqueEdges(const Mesh<T>& mesh) {
    std::unordered_set<Edge, EdgeHash> uniqueEdges; // Use an unordered_set to store unique edges
    
    std::cout << "numVertices : " << T::numVertices << std::endl;
    // Iterate through all triangles and add their edges to the set
    for (const auto& element : mesh.elements) {
        for (size_t i = 0; i < T::numVertices; ++i) {
            size_t v1 = element.v[i];
            size_t v2 = element.v[(i + 1) % T::numVertices];

            // Store edges in a consistent order to avoid duplicates
            uniqueEdges.insert({std::min(v1, v2), std::max(v1, v2)}); 
        }
    }
    return uniqueEdges.size();
}


template <typename T>
size_t countUniqueTriangles(const Mesh<T>& mesh) {
    std::unordered_set<Triangle, TriangleHash> uniqueTriangles; // Use an unordered_set to store unique triangles   
    // Iterate through all tetrahedra and add their triangles to the set
    for (const auto& element : mesh.elements) {
        for (size_t i = 0; i < T::numVertices; ++i) {
            size_t v1 = element.v[i];
            size_t v2 = element.v[(i + 1) % T::numVertices];
            size_t v3 = element.v[(i + 2) % T::numVertices];
            // Store triangles in a consistent order to avoid duplicates
            uniqueTriangles.insert({std::min({v1, v2, v3}), std::min({std::max(v1, v2), std::max(v2, v3), std::max(v3, v1)}), std::max({v1, v2, v3})}); 
        }
    }
    return uniqueTriangles.size();
}

} // namespace Enmesh