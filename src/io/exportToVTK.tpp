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

    // Identify boundary edges (edges that belong to only one triangle)
    if(mesh.boundaryElements.empty()) {
        mesh.boundaryElements = Enmesh::getBoundaryEdges<Triangle>(mesh);
        mesh.boundaryTags.resize(mesh.boundaryElements.size(), 1); 
    }

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
    for (const auto& e : mesh.boundaryElements)
        file << "2 " << e.v[0] << " " << e.v[1] << "\n";

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

    // Identify boundary edges (edges that belong to only one quad)
    if(mesh.boundaryElements.empty()) {
        mesh.boundaryElements = getBoundaryEdges<Quad>(mesh);
        mesh.boundaryTags.resize(mesh.boundaryElements.size(), 1); 
    }

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
    for (const auto& e : mesh.boundaryElements)
        file << "2 " << e.v[0] << " " << e.v[1] << "\n";

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
void exportToVTK<Tetra>(const std::string& filename, Mesh<Tetra>& mesh){
    std::ofstream file(filename);
    if (!file.is_open()){
        std::cerr << "export to VTK : Error opening file for writing: " << filename << std::endl;
        return;
    }

    file << "# vtk DataFile Version 3.0\n";
    file << "Mesh Analysis Combo\nASCII\nDATASET UNSTRUCTURED_GRID\n";

    // Write vertices
    file << "POINTS " << mesh.vertices.size() << " float\n";
    for (const auto& v : mesh.vertices) 
        file << v.x << " " << v.y << " " << v.z << "\n";

    // Write cells (tetrahedra)
    size_t nT = mesh.elements.size();
    file << "CELLS " << nT << " " << (nT * 5) << "\n";
    for (const auto& tetra : mesh.elements)
        file << "4 " << tetra.v[0] << " " << tetra.v[1] << " " << tetra.v[2] << " " << tetra.v[3] << "\n";
    file << "CELL_TYPES " << nT << "\n";
    for (size_t i = 0; i < nT; ++i) file << "10\n"; // Tetrahedra

    // Write cell data (quality ratios)
    file << "CELL_DATA " << nT << "\n";
    file << "SCALARS Quality_Ratio float\nLOOKUP_TABLE default\n";
    for (float r : mesh.ratios) file << r << "\n";

    file.close();
}

} // namespace Enmesh