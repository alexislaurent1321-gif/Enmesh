#include <numeric>
#include <algorithm>

#include "mesh/mesh_analysis.h"

namespace Enmesh {

// Quality analysis

template <typename Element>
size_t countUniqueEdges(const Mesh<Element>& mesh) {
    std::unordered_set<Edge, EdgeHash> uniqueEdges; // Use an unordered_set to store unique edges
    
    // Iterate through all triangles and add their edges to the set
    for (const auto& element : mesh.elements) {
        for (size_t i = 0; i < Element::numVertices; ++i) {
            size_t v1 = element.v[i];
            size_t v2 = element.v[(i + 1) % Element::numVertices];

            // Store edges in a consistent order to avoid duplicates
            uniqueEdges.insert({std::min(v1, v2), std::max(v1, v2)}); 
        }
    }
    return uniqueEdges.size();
}


template <typename Element>
size_t countUniqueTriangles(const Mesh<Element>& mesh) {
    std::unordered_set<Triangle, TriangleHash> uniqueTriangles; // Use an unordered_set to store unique triangles   
    
    // Iterate through all tetrahedra and add their triangles to the set
    for (const auto& element : mesh.elements) {
        for (size_t i = 0; i < Element::numVertices; ++i) {
            size_t v0 = element.v[i];
            size_t v1 = element.v[(i + 1) % Element::numVertices];
            size_t v2 = element.v[(i + 2) % Element::numVertices];
            // Store triangles in a consistent order to avoid duplicates
            uniqueTriangles.insert({std::min({v0, v1, v2}), std::min({std::max(v0, v1), std::max(v1, v2), std::max(v2, v0)}), std::max({v0, v1, v2})}); 
        }
    }
    return uniqueTriangles.size();
}


template <typename Element>
size_t countUniqueQuads(const Mesh<Element>& mesh) {
    std::unordered_set<Quad, QuadHash> uniqueQuads; // Use an unordered_set to store unique quads   
    
    // Iterate through all hexahedra and add their quads to the set
    for (const auto& element : mesh.elements) {
        for (size_t i = 0; i < Element::numVertices; ++i) {
            size_t v0 = element.v[i];
            size_t v1 = element.v[(i + 1) % Element::numVertices];
            size_t v2 = element.v[(i + 2) % Element::numVertices];
            size_t v3 = element.v[(i + 3) % Element::numVertices];
            // Store quads in a consistent order to avoid duplicates
            uniqueQuads.insert({std::min({v0, v1, v2, v3}), std::min({std::max(v0, v1), std::max(v1, v2), std::max(v2, v3), std::max(v3, v0)}), std::max({v0, v1, v2, v3})}); 
        }
    }
    return uniqueQuads.size();
}

} // namespace Enmesh