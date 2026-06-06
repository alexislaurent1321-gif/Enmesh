#include <numeric>
#include <algorithm>

#include "mesh/mesh_analysis.h"

namespace Enmesh {


template <>
inline std::vector<Edge> getBoundaries(const Mesh<Triangle>& mesh) {

    auto edgeCounts = getElementsValences(mesh);    // Get the valence counts for all edges
    std::vector<Edge> boundaryEdges;                // Collect edges that belong to only one triangle (valence = 1)
    
    for (auto const& [edge, count] : edgeCounts) {
        if (count == 1) boundaryEdges.push_back(edge);
    }
    
    return boundaryEdges;
}


template <>
inline std::vector<Edge> getBoundaries(const Mesh<Quad>& mesh) {

    auto edgeCounts = getElementsValences(mesh);    // Get the valence counts for all edges
    std::vector<Edge> boundaryEdges;                // Collect edges that belong to only one quad (valence = 1)
    
    for (auto const& [edge, count] : edgeCounts) {
        if (count == 1) boundaryEdges.push_back(edge);
    }
    
    return boundaryEdges;
}


inline std::vector<Triangle> getBoundaries(const Mesh<Tetra>& mesh) {

    auto triangleCounts = getElementsValences(mesh);    // Get the valence counts for all triangles
    std::vector<Triangle> boundaryTriangles;            // Collect triangles that belong to only one tetrahedron (valence = 1)
    
    for (auto const& [triangle, count] : triangleCounts) {
        if (count == 1) boundaryTriangles.push_back(triangle);
    }
    
    return boundaryTriangles;
}


inline std::vector<Quad> getBoundaries(const Mesh<Hexa>& mesh) {

    auto quadCounts = getElementsValences(mesh);    // Get the valence counts for all quads
    std::vector<Quad> boundaryQuads;                // Collect quads that belong to only one hexahedron (valence = 1)
    
    for (auto const& [quad, count] : quadCounts) {
        if (count == 1) boundaryQuads.push_back(quad);
    }
    
    return boundaryQuads;
}


} // namespace Enmesh