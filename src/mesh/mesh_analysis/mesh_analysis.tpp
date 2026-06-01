#include <numeric>
#include <algorithm>

#include "mesh/mesh_analysis.h"

/** @file mesh_analysis.tpp
 *  @brief Implementation of mesh analysis functions : counting unique edges/triangles and calculating aspect ratios for triangles, quads and tetrahedra.
 */

namespace Enmesh {

template <>
void analyzeMesh(Mesh<Triangle>& mesh) {
    // Basic info
    std::cout << "Vertices : " << mesh.vertices.size() << std::endl;
    std::cout << "Elements : " << mesh.elements.size() << std::endl;
    std::cout << "Unique edges : " << countUniqueEdges<Triangle>(mesh) << std::endl;

    // Aspect ratio analysis
    calculateAspectRatios<Triangle>(mesh);
    std::cout << "min aspect ratio : " << *std::min_element(mesh.ratios.begin(), mesh.ratios.end()) << std::endl;
    std::cout << "max aspect ratio : " << *std::max_element(mesh.ratios.begin(), mesh.ratios.end()) << std::endl;
    std::cout << "mean aspect ratio : " << std::accumulate(mesh.ratios.begin(), mesh.ratios.end(), 0.f) / mesh.ratios.size() << std::endl;
}


template <>
void analyzeMesh(Mesh<Quad>& mesh) {
    // Basic info
    std::cout << "Vertices : " << mesh.vertices.size() << std::endl;
    std::cout << "Elements : " << mesh.elements.size() << std::endl;
    std::cout << "Unique edges : " << countUniqueEdges<Quad>(mesh) << std::endl;

    // Aspect ratio analysis
    calculateAspectRatios<Quad>(mesh);
    std::cout << "min aspect ratio : " << *std::min_element(mesh.ratios.begin(), mesh.ratios.end()) << std::endl;
    std::cout << "max aspect ratio : " << *std::max_element(mesh.ratios.begin(), mesh.ratios.end()) << std::endl;
    std::cout << "mean aspect ratio : " << std::accumulate(mesh.ratios.begin(), mesh.ratios.end(), 0.f) / mesh.ratios.size() << std::endl;
}


template <>
void analyzeMesh(Mesh<Tetra>& mesh) {
    // Basic info
    std::cout << "Vertices : " << mesh.vertices.size() << std::endl;
    std::cout << "Elements : " << mesh.elements.size() << std::endl;
    std::cout << "Unique triangles : " << countUniqueTriangles<Tetra>(mesh) << std::endl;

    // Aspect ratio analysis
    calculateAspectRatios<Tetra>(mesh);
    std::cout << "min aspect ratio : " << *std::min_element(mesh.ratios.begin(), mesh.ratios.end()) << std::endl;
    std::cout << "max aspect ratio : " << *std::max_element(mesh.ratios.begin(), mesh.ratios.end()) << std::endl;
    std::cout << "mean aspect ratio : " << std::accumulate(mesh.ratios.begin(), mesh.ratios.end(), 0.f) / mesh.ratios.size() << std::endl;
}


template <>
void analyzeMesh(Mesh<Tetra>& mesh) {
    // Basic info
    std::cout << "Vertices : " << mesh.vertices.size() << std::endl;
    std::cout << "Elements : " << mesh.elements.size() << std::endl;
    std::cout << "Unique triangles : " << countUniqueTriangles<Tetra>(mesh) << std::endl;

    // Aspect ratio analysis
    calculateAspectRatios<Tetra>(mesh);
    std::cout << "min aspect ratio : " << *std::min_element(mesh.ratios.begin(), mesh.ratios.end()) << std::endl;
    std::cout << "max aspect ratio : " << *std::max_element(mesh.ratios.begin(), mesh.ratios.end()) << std::endl;
    std::cout << "mean aspect ratio : " << std::accumulate(mesh.ratios.begin(), mesh.ratios.end(), 0.f) / mesh.ratios.size() << std::endl;
}

} // namespace Enmesh