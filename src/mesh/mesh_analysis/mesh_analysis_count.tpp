#include <numeric>
#include <algorithm>

#include "mesh/mesh_analysis.h"

namespace Enmesh {

// Quality analysis

template <>
inline size_t countAllBorders(const Mesh<Triangle>& mesh) {
    std::unordered_set<Edge, EdgeHash> uniqueEdges; // Use an unordered_set to store unique edges
    
    // Iterate through all triangles and add their edges to the set
    for (const auto& element : mesh.elements) {
        for (size_t i = 0; i < Triangle::numVertices; ++i) {
            size_t v1 = element.v[i];
            size_t v2 = element.v[(i + 1) % Triangle::numVertices];

            // Store edges in a consistent order to avoid duplicates
            uniqueEdges.insert({std::min(v1, v2), std::max(v1, v2)}); 
        }
    }
    return uniqueEdges.size();
}


template <>
inline size_t countAllBorders(const Mesh<Quad>& mesh) {
    std::unordered_set<Edge, EdgeHash> uniqueEdges; // Use an unordered_set to store unique edges
    
    // Iterate through all triangles and add their edges to the set
    for (const auto& element : mesh.elements) {
        for (size_t i = 0; i < Quad::numVertices; ++i) {
            size_t v1 = element.v[i];
            size_t v2 = element.v[(i + 1) % Quad::numVertices];

            // Store edges in a consistent order to avoid duplicates
            uniqueEdges.insert({std::min(v1, v2), std::max(v1, v2)}); 
        }
    }
    return uniqueEdges.size();
}


template <>
inline size_t countAllBorders(const Mesh<Tetra>& mesh) {
    std::unordered_set<Triangle, TriangleHash> uniqueTriangles; // Use an unordered_set to store unique triangles   
    
    // Iterate through all tetrahedra and add their triangles to the set
    for (const auto& element : mesh.elements) {
        for (size_t i = 0; i < Tetra::numVertices; ++i) {
            size_t v0 = element.v[i];
            size_t v1 = element.v[(i + 1) % Tetra::numVertices];
            size_t v2 = element.v[(i + 2) % Tetra::numVertices];
            // Store triangles in a consistent order to avoid duplicates
            uniqueTriangles.insert({std::min({v0, v1, v2}), std::min({std::max(v0, v1), std::max(v1, v2), std::max(v2, v0)}), std::max({v0, v1, v2})}); 
        }
    }
    return uniqueTriangles.size();
}


template <>
inline size_t countAllBorders(const Mesh<Hexa>& mesh) {
    std::unordered_set<Quad, QuadHash> uniqueQuads; // Use an unordered_set to store unique quads
    
    // Iterate through all elements and add their borders to the set
    for (const auto& element : mesh.elements) {
        
        auto faces = element.getFaces();
        for (const auto& face : faces) {
            auto sortedFace = face; // Create a copy of the face to sort its vertices
            std::sort(sortedFace.v.begin(), sortedFace.v.end()); // Sort vertex indices to ensure consistent ordering
            uniqueQuads.insert(sortedFace); 
        }
    }
    return uniqueQuads.size();
}

} // namespace Enmesh