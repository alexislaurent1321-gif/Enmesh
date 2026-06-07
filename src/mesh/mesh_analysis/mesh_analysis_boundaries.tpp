#include <numeric>
#include <algorithm>

#include "mesh/mesh_analysis.h"

namespace Enmesh {


template <typename Element>
void computeBoundaries(Mesh<Element>& mesh) {

    mesh.boundaryElements.clear(); // Clear any existing boundary elements before computing new ones

    using BoundaryType = typename Boundary<Element>::type;

    auto boundaryCounts = getElementsValences(mesh);    // Get the valence counts for all edges
    std::vector<BoundaryType> boundaryElements;         // Collect edges that belong to only one element (valence = 1)
    
    for (auto const& [border, count] : boundaryCounts) {
        if (count == 1) boundaryElements.push_back(border);
    }
    
    // Do something with the boundary edges, e.g., store them in the mesh object
    mesh.boundaryElements = std::move(boundaryElements);
}


} // namespace Enmesh