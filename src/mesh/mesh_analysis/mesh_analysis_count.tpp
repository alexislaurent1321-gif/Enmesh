#include <numeric>
#include <algorithm>

#include "mesh/mesh_analysis.h"

/**
 * @file mesh_analysis_count.tpp
 * @brief Implementation of counting borders for different mesh elements
 */

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
    
    // Iterate through all quads and add their edges to the set
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
    
    // Iterate through all elements and add their borders to the set
    for (const auto& element : mesh.elements) {
        
        auto faces = element.getFaces();
        for (const auto& face : faces) {
            auto sortedFace = face; // Create a copy of the face to sort its vertices
            std::sort(sortedFace.v.begin(), sortedFace.v.end()); // Sort vertex indices to ensure consistent ordering
            uniqueTriangles.insert(sortedFace); 
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