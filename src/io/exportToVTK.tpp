#include <format>
#include <iostream>
#include <string>
#include <string_view>

#include "io/exportToVTK.h"
#include "mesh/mesh_analysis.h"

namespace Enmesh {

template <typename Element>
void exportToVTK(const std::string& filename, const Mesh<Element>& mesh) {

    std::ofstream file(filename);
    if (!file.is_open()) return;

    file << "# vtk DataFile Version 3.0\n";
    file << "Mesh Analysis Combo\nASCII\nDATASET UNSTRUCTURED_GRID\n";

    // Write vertices
    file << "POINTS " << mesh.vertices.size() << " float\n";
    for (const auto& vertex : mesh.vertices) 
        file << vertex.x << " " << vertex.y << " " << vertex.z << "\n";

    // Write cells (triangles + boundary edges)
    size_t numElements = mesh.elements.size();
    size_t numBoundaryElements = mesh.boundaryElements.size();
    file << "CELLS " << (numElements + numBoundaryElements) << " " << numElements * (Element::numVertices + 1) + numBoundaryElements * (Element::boundaryNumVertices + 1) << "\n";
    
    for (const auto& element : mesh.elements) {
        file << Element::numVertices << " ";
        for (size_t i = 0; i < Element::numVertices; ++i) {
            file << element.v[i] << " ";
        }
        file << "\n";
    }

    for (const auto& boundaryElement : mesh.boundaryElements) {
        file << Element::boundaryNumVertices << " ";
        for (size_t i = 0; i < Element::boundaryNumVertices; ++i) {
            file << boundaryElement.v[i] << " ";
        }
        file << "\n";
    }

    file << "CELL_TYPES " << (numElements + numBoundaryElements) << "\n";
    for (size_t i = 0; i < numElements; ++i) file << Element::VTKType << "\n";                  // Elements
    for (size_t i = 0; i < numBoundaryElements; ++i) file << Element::boundaryVTKType << "\n";  // Boundary elements


    // Write cell data (quality ratios and boundary flags)
    file << "CELL_DATA " << (numElements + numBoundaryElements) << "\n";


    file << "SCALARS Quality_Ratio float\nLOOKUP_TABLE default\n";
    for (float r : mesh.ratios) file << r << "\n";
    for (size_t i = 0; i < numBoundaryElements; ++i) file << "0.\n"; 


    // Boundary representation: 0 for triangles, 1 for boundary edges 
    file << "SCALARS Is_Boundary int\nLOOKUP_TABLE default\n";
    for (size_t i = 0; i < numElements; ++i) file << "0\n"; // Triangle = 0
    for (size_t i = 0; i < numBoundaryElements; ++i) file << std::format("{}\n", mesh.boundaryTags[i]); // BoundaryTag = tag

    file.close();
}

} // namespace Enmesh