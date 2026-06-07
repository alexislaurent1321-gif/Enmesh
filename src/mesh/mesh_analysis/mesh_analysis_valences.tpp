#include <numeric>
#include <algorithm>

#include "mesh/mesh_analysis.h"

/**
 * @file mesh_analysis_valences.tpp
 * @brief Implementation of valence counting for different mesh elements
 */

namespace Enmesh {

// Get valence for triangle meshes
inline std::unordered_map<Edge, size_t, EdgeHash> getElementsValences(const Mesh<Triangle>& mesh) {

    std::unordered_map<Edge, size_t, EdgeHash> counts;     // Use an unordered_map to count occurrences of each edge
    
    for (const auto& element : mesh.elements) {
        for (size_t i = 0; i < Triangle::numVertices; ++i) {
            size_t v0 = element.v[i];
            size_t v1 = element.v[(i + 1) % Triangle::numVertices];

            Edge edge = {std::min(v0, v1), std::max(v0, v1)};  // Store edges in a consistent order
            counts[edge]++;
        }
    }
    
    return counts;
}


// Get valence for triangle meshes
inline std::unordered_map<Edge, size_t, EdgeHash> getElementsValences(const Mesh<Quad>& mesh) {

    std::unordered_map<Edge, size_t, EdgeHash> counts;     // Use an unordered_map to count occurrences of each edge
    
    for (const auto& element : mesh.elements) {
        for (size_t i = 0; i < Quad::numVertices; ++i) {
            size_t v0 = element.v[i];
            size_t v1 = element.v[(i + 1) % Quad::numVertices];

            Edge edge = {std::min(v0, v1), std::max(v0, v1)};  // Store edges in a consistent order
            counts[edge]++;
        }
    }
    
    return counts;
}


// Get valence for tetrahedral meshes
inline std::unordered_map<Triangle, size_t, TriangleHash> getElementsValences(const Mesh<Tetra>& mesh) {
    
    std::unordered_map<Triangle, size_t, TriangleHash> counts;     // Use an unordered_map to count occurrences of each triangle
    
    for (const auto& element : mesh.elements) {
        
        auto faces = element.getFaces();
        for (const auto& face : faces) {
            auto sortedFace = face; // Create a copy of the face to sort its vertices
            std::sort(sortedFace.v.begin(), sortedFace.v.end()); // Sort vertex indices to ensure consistent ordering
            counts[sortedFace]++;
        }
    }  
    
    return counts;
}


// Get valence for tetrahedral meshes
inline std::unordered_map<Quad, size_t, QuadHash> getElementsValences(const Mesh<Hexa>& mesh) {
    
    std::unordered_map<Quad, size_t, QuadHash> counts;     // Use an unordered_map to count occurrences of each quad
    
    for (const auto& element : mesh.elements) {
        
        auto faces = element.getFaces();
        for (const auto& face : faces) {
            auto sortedFace = face; // Create a copy of the face to sort its vertices
            std::sort(sortedFace.v.begin(), sortedFace.v.end()); // Sort vertex indices to ensure consistent ordering
            counts[sortedFace]++;
        }
    }  
    
    return counts;
}


} // namespace Enmesh