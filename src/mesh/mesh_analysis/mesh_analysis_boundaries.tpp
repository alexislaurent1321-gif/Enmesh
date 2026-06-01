#include <numeric>
#include <algorithm>

#include "mesh/mesh_analysis.h"

namespace Enmesh {


// Get valence for 2D meshes

template <typename Element>
std::unordered_map<Edge, size_t, EdgeHash> getEdgeValences(const Mesh<Element>& mesh) {

    if(Element::type != 2 && Element::type != 3) {
        std::cerr << "Error: getEdgeValences only supports surface meshes" << std::endl;
        return {};
    }

    std::unordered_map<Edge, size_t, EdgeHash> counts;     // Use an unordered_map to count occurrences of each edge
    
    for (const auto& element : mesh.elements) {
        for (size_t i = 0; i < Element::numVertices; ++i) {
            size_t v0 = element.v[i];
            size_t v1 = element.v[(i + 1) % Element::numVertices];

            Edge e = {std::min(v0, v1), std::max(v0, v1)};  // Store edges in a consistent order
            counts[e]++;
        }
    }
    
    return counts;
}


template <typename Element>
std::vector<Edge> getBoundaryEdges(const Mesh<Element>& mesh) {

    if(Element::type != 2 && Element::type != 3) {
        std::cerr << "Error: getBoundaryEdges only supports surface meshes" << std::endl;
        return {};
    }

    auto edgeCounts = getEdgeValences(mesh);    // Get the valence counts for all edges
    std::vector<Edge> boundaryEdges;            // Collect edges that belong to only one triangle (valence = 1)
    
    for (auto const& [edge, count] : edgeCounts) {
        if (count == 1) boundaryEdges.push_back(edge);
    }
    
    return boundaryEdges;
}



// Get valence for tetrahedral meshes

std::unordered_map<Triangle, size_t, TriangleHash> getTriangleValences(const Mesh<Tetra>& mesh) {
    std::unordered_map<Triangle, size_t, TriangleHash> counts;     // Use an unordered_map to count occurrences of each triangle
    
    for (const auto& element : mesh.elements) {
        for (size_t i = 0; i < 4; ++i) {
            size_t v0 = element.v[i];
            size_t v1 = element.v[(i + 1) % 4];
            size_t v2 = element.v[(i + 2) % 4];

            Triangle triangle = {{std::min({v0, v1, v2}), std::min({std::max(v0, v1), std::max(v1, v2), std::max(v2, v0)}), std::max({v0, v1, v2})}};  // Store triangles in a consistent order
            counts[triangle]++;
        }
    }  
    
    return counts;
}


std::vector<Triangle> getBoundaryTriangles(const Mesh<Tetra>& mesh) {
    auto triangleCounts = getTriangleValences(mesh);    // Get the valence counts for all triangles
    std::vector<Triangle> boundaryTriangles;            // Collect triangles that belong to only one tetrahedron (valence = 1)
    
    for (auto const& [triangle, count] : triangleCounts) {
        if (count == 1) boundaryTriangles.push_back(triangle);
    }
    
    return boundaryTriangles;
}



// Get valence for hexahedral meshes

std::unordered_map<Quad, size_t, QuadHash> getQuadValences(const Mesh<Hexa>& mesh) {
    std::unordered_map<Quad, size_t, QuadHash> counts;     // Use an unordered_map to count occurrences of each quad
    
    for (const auto& element : mesh.elements) {
        for (size_t i = 0; i < 6; ++i) {
            size_t v0 = element.v[i];
            size_t v1 = element.v[(i + 1) % 4];
            size_t v2 = element.v[(i + 2) % 4];

            Quad quad = {{std::min({v0, v1, v2}), std::min({std::max(v0, v1), std::max(v1, v2), std::max(v2, v0)}), std::max({v0, v1, v2})}};  // Store quads in a consistent order
            counts[quad]++;
        }
    }  
    
    return counts;
}


std::vector<Quad> getBoundaryQuads(const Mesh<Hexa>& mesh) {
    auto quadCounts = getQuadValences(mesh);    // Get the valence counts for all quads
    std::vector<Quad> boundaryQuads;            // Collect quads that belong to only one hexahedron (valence = 1)
    
    for (auto const& [quad, count] : quadCounts) {
        if (count == 1) boundaryQuads.push_back(quad);
    }
    
    return boundaryQuads;
}

} // namespace Enmesh