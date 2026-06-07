#include <numeric>
#include <algorithm>

#include "mesh/mesh_analysis.h"

/** @file mesh_analysis.tpp
 *  @brief Implementation of mesh analysis functions : counting unique edges/triangles and calculating aspect ratios for triangles, quads and tetrahedra.
 */
    
namespace Enmesh {

template <typename Element>
inline void analyzeMesh(Mesh<Element>& mesh) {
    // Basic info
    std::cout << "Vertices : " << mesh.vertices.size() << std::endl;
    std::cout << "Elements : " << mesh.elements.size() << std::endl;
    std::cout << "Intern + extern borders : " << countAllBorders(mesh) << std::endl;
    if(!mesh.boundaryElements.empty()) {
        std::cout << "Extern borders : " << mesh.boundaryElements.size() << std::endl;
    }

    // Aspect ratio analysis
    calculateAspectRatios(mesh);
    std::cout << "min aspect ratio : " << *std::min_element(mesh.ratios.begin(), mesh.ratios.end()) << std::endl;
    std::cout << "max aspect ratio : " << *std::max_element(mesh.ratios.begin(), mesh.ratios.end()) << std::endl;
    std::cout << "mean aspect ratio : " << std::accumulate(mesh.ratios.begin(), mesh.ratios.end(), 0.f) / mesh.ratios.size() << std::endl;
}

} // namespace Enmesh