#include <numeric>
#include <algorithm>

#include "mesh/mesh_analysis.h"

namespace Enmesh {

// Display analysis

template <typename T>
inline void analyzeMesh(Mesh<T>& mesh) {
    // Basic info
    std::cout << "Vertices : " << mesh.vertices.size() << std::endl;
    std::cout << "Elements : " << mesh.elements.size() << std::endl;
    std::cout << "Unique edges : " << countUniqueEdges<T>(mesh) << std::endl;

    // Aspect ratio analysis
    calculateAspectRatios<T>(mesh);
    std::cout << "min aspect ratio : " << *std::min_element(mesh.ratios.begin(), mesh.ratios.end()) << std::endl;
    std::cout << "max aspect ratio : " << *std::max_element(mesh.ratios.begin(), mesh.ratios.end()) << std::endl;
    std::cout << "mean aspect ratio : " << std::accumulate(mesh.ratios.begin(), mesh.ratios.end(), 0.f) / mesh.ratios.size() << std::endl;
}


template <>
inline void analyzeMesh(Mesh<Tetrahedron>& mesh) {
    // Basic info
    std::cout << "Vertices : " << mesh.vertices.size() << std::endl;
    std::cout << "Elements : " << mesh.elements.size() << std::endl;
    std::cout << "Unique triangles : " << countUniqueTriangles<Tetrahedron>(mesh) << std::endl;

    // Aspect ratio analysis
    calculateAspectRatios<Tetrahedron>(mesh);
    std::cout << "min aspect ratio : " << *std::min_element(mesh.ratios.begin(), mesh.ratios.end()) << std::endl;
    std::cout << "max aspect ratio : " << *std::max_element(mesh.ratios.begin(), mesh.ratios.end()) << std::endl;
    std::cout << "mean aspect ratio : " << std::accumulate(mesh.ratios.begin(), mesh.ratios.end(), 0.f) / mesh.ratios.size() << std::endl;
}

} // namespace Enmesh