#include <format>
#include <iostream>
#include <string>
#include <string_view>

#include "io/exportToVTK.h"
#include "mesh/mesh_analysis.h"

namespace Enmesh {

template <>
void exportToVTK<Triangle>(const std::string& filename, Mesh<Triangle>& mesh) {
    std::ofstream file(filename);
    if (!file.is_open()) return;

    file << "# vtk DataFile Version 3.0\n";
    file << "Mesh Analysis Combo\nASCII\nDATASET UNSTRUCTURED_GRID\n";

    // Write vertices
    file << "POINTS " << mesh.vertices.size() << " float\n";
    for (const auto& v : mesh.vertices) 
        file << v.x << " " << v.y << " " << v.z << "\n";

    // Write cells (triangles + boundary edges)
    size_t nT = mesh.elements.size();
    size_t nB = mesh.boundaryElements.size();
    file << "CELLS " << (nT + nB) << " " << (nT * 4 + nB * 3) << "\n";
    
    for (const auto& triangle : mesh.elements)
        file << "3 " << triangle.v[0] << " " << triangle.v[1] << " " << triangle.v[2] << "\n";
    for (const auto& element : mesh.boundaryElements)
        file << "2 " << element.v[0] << " " << element.v[1] << "\n";

    file << "CELL_TYPES " << (nT + nB) << "\n";
    for (size_t i = 0; i < nT; ++i) file << "5\n"; // Triangles
    for (size_t i = 0; i < nB; ++i) file << "3\n"; // Lines


    // Write cell data (quality ratios and boundary flags)
    file << "CELL_DATA " << (nT + nB) << "\n";


    file << "SCALARS Quality_Ratio float\nLOOKUP_TABLE default\n";
    for (float r : mesh.ratios) file << r << "\n";
    for (size_t i = 0; i < nB; ++i) file << "0.\n"; 


    // Boundary representation: 0 for triangles, 1 for boundary edges 
    file << "SCALARS Is_Boundary int\nLOOKUP_TABLE default\n";
    for (size_t i = 0; i < nT; ++i) file << "0\n"; // Triangle = 0
    for (size_t i = 0; i < nB; ++i) file << std::format("{}\n", mesh.boundaryTags[i]); // BoundaryTag = tag

    file.close();
}


template <>
void exportToVTK<Quad>(const std::string& filename, Mesh<Quad>& mesh) {
    std::ofstream file(filename);
    if (!file.is_open()) return;

    file << "# vtk DataFile Version 3.0\n";
    file << "Mesh Analysis Combo\nASCII\nDATASET UNSTRUCTURED_GRID\n";

    // Write vertices
    file << "POINTS " << mesh.vertices.size() << " float\n";
    for (const auto& v : mesh.vertices) 
        file << v.x << " " << v.y << " " << v.z << "\n";

    // Write cells (quads + boundary edges)
    size_t nQ = mesh.elements.size();
    size_t nB = mesh.boundaryElements.size();
    file << "CELLS " << (nQ + nB) << " " << (nQ * 5 + nB * 3) << "\n";
    
    for (const auto& quad : mesh.elements)
        file << "4 " << quad.v[0] << " " << quad.v[1] << " " << quad.v[2] << " " << quad.v[3] << "\n";
    for (const auto& element : mesh.boundaryElements)
        file << "2 " << element.v[0] << " " << element.v[1] << "\n";

    file << "CELL_TYPES " << (nQ + nB) << "\n";
    for (size_t i = 0; i < nQ; ++i) file << "5\n"; // Quads
    for (size_t i = 0; i < nB; ++i) file << "3\n"; // Lines


    // Write cell data (quality ratios and boundary flags)
    file << "CELL_DATA " << (nQ + nB) << "\n";


    file << "SCALARS Quality_Ratio float\nLOOKUP_TABLE default\n";
    for (float r : mesh.ratios) file << r << "\n";
    for (size_t i = 0; i < nB; ++i) file << "0.\n"; 


    // Boundary representation: 0 for quads, 1 for boundary edges 
    file << "SCALARS Is_Boundary int\nLOOKUP_TABLE default\n";
    for (size_t i = 0; i < nQ; ++i) file << "0\n"; // Quad = 0
    for (size_t i = 0; i < nB; ++i) file << std::format("{}\n", mesh.boundaryTags[i]); // BoundaryTag = tag

    file.close();
}


template <>
void exportToVTK<Tetra>(const std::string& filename, Mesh<Tetra>& mesh) {
    std::ofstream file(filename);
    if (!file.is_open()) return;

    file << "# vtk DataFile Version 3.0\n";
    file << "Mesh Analysis Combo\nASCII\nDATASET UNSTRUCTURED_GRID\n";

    // Write vertices
    file << "POINTS " << mesh.vertices.size() << " float\n";
    for (const auto& v : mesh.vertices) 
        file << v.x << " " << v.y << " " << v.z << "\n";

    // Write cells (tetrahedra + boundary edges)
    size_t nT = mesh.elements.size();
    size_t nB = mesh.boundaryElements.size();
    file << "CELLS " << (nT + nB) << " " << (nT * 5 + nB * 4) << "\n";
    
    for (const auto& tetra : mesh.elements)
        file << "4 " << tetra.v[0] << " " << tetra.v[1] << " " << tetra.v[2] << " " << tetra.v[3] << "\n";
    for (const auto& element : mesh.boundaryElements)
        file << "3 " << element.v[0] << " " << element.v[1] << " " << element.v[2] << "\n";

    file << "CELL_TYPES " << (nT + nB) << "\n";
    for (size_t i = 0; i < nT; ++i) file << "10\n"; // Tetrahedra
    for (size_t i = 0; i < nB; ++i) file << "5\n"; // Lines


    // Write cell data (quality ratios and boundary flags)
    file << "CELL_DATA " << (nT + nB) << "\n";


    file << "SCALARS Quality_Ratio float\nLOOKUP_TABLE default\n";
    for (float r : mesh.ratios) file << r << "\n";
    for (size_t i = 0; i < nB; ++i) file << "0.\n"; 


    // Boundary representation: 0 for tetrahedra, 1 for boundary edges 
    file << "SCALARS Is_Boundary int\nLOOKUP_TABLE default\n";
    for (size_t i = 0; i < nT; ++i) file << "0\n"; // Tetrahedron = 0
    for (size_t i = 0; i < nB; ++i) file << std::format("{}\n", mesh.boundaryTags[i]); // BoundaryTag = tag

    file.close();
}


template <>
void exportToVTK<Hexa>(const std::string& filename, Mesh<Hexa>& mesh) {
    std::ofstream file(filename);
    if (!file.is_open()) return;

    file << "# vtk DataFile Version 3.0\n";
    file << "Mesh Analysis Combo\nASCII\nDATASET UNSTRUCTURED_GRID\n";

    // Write vertices
    file << "POINTS " << mesh.vertices.size() << " float\n";
    for (const auto& v : mesh.vertices) 
        file << v.x << " " << v.y << " " << v.z << "\n";

    // Write cells (hexahedra + boundary edges)
    size_t nH = mesh.elements.size();
    size_t nB = mesh.boundaryElements.size();
    file << "CELLS " << (nH + nB) << " " << (nH * 9 + nB * 5) << "\n";
    
    for (const auto& hexa : mesh.elements)
        file << "8 " << hexa.v[0] << " " << hexa.v[1] << " " << hexa.v[2] << " " << hexa.v[3] << " " << hexa.v[4] << " " << hexa.v[5] << " " << hexa.v[6] << " " << hexa.v[7] << "\n";
    for (const auto& element : mesh.boundaryElements)
        file << "4 " << element.v[0] << " " << element.v[1] << " " << element.v[2] << " " << element.v[3] << "\n";

    file << "CELL_TYPES " << (nH + nB) << "\n";
    for (size_t i = 0; i < nH; ++i) file << "12\n"; // Hexahedra
    for (size_t i = 0; i < nB; ++i) file << "9\n";  // Quads


    // Write cell data (quality ratios and boundary flags)
    file << "CELL_DATA " << (nH + nB) << "\n";


    file << "SCALARS Quality_Ratio float\nLOOKUP_TABLE default\n";
    for (float r : mesh.ratios) file << r << "\n";
    for (size_t i = 0; i < nB; ++i) file << "0.\n"; 


    // Boundary representation: 0 for hexahedra, 1 for boundary edges 
    file << "SCALARS Is_Boundary int\nLOOKUP_TABLE default\n";
    for (size_t i = 0; i < nH; ++i) file << "0\n"; // Hexahedron = 0
    for (size_t i = 0; i < nB; ++i) file << std::format("{}\n", mesh.boundaryTags[i]); // BoundaryTag = tag

    file.close();
}


} // namespace Enmesh