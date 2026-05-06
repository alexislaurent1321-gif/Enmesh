#include <numeric>
#include <algorithm>
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include "io/loadObj.h"

namespace Enmesh {

template <typename T>
bool loadObj(Mesh<T>& mesh, const std::string& path) {

    // Ensure that OBJ files typically represent surface meshes
    if(T::elementType != 2 && T::elementType != 3) {
        std::cerr << "Error: loadObj only supports surface meshes" << std::endl;
        return false;
    }

    mesh.vertices.clear();
    mesh.elements.clear();

    tinyobj::ObjReaderConfig reader_config; // Create a reader configuration object (optional)
    tinyobj::ObjReader reader;              // Create an ObjReader object to read the OBJ file

    if (!reader.ParseFromFile(path, reader_config)) return false;

    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();

    // Load vertices
    for (size_t v = 0; v < attrib.vertices.size(); v += 3) {
        mesh.vertices.push_back({
            attrib.vertices[v], 
            attrib.vertices[v + 1], 
            attrib.vertices[v + 2]
        });
    }

    
    // Load elements
    for (const auto& shape : shapes) {
        size_t index_offset = 0;
        for (size_t face = 0; face < shape.mesh.num_face_vertices.size(); ++face) {
            int fv = 4;   // Get the number of vertices for this face
            if (fv != T::numVertices) continue;         // Only support elements with the specified number of vertices

            // Create an element object and fill its vertex indices
            T element;
            for (size_t v = 0; v < fv; ++v) {
                element.v[v] = shape.mesh.indices[index_offset + v].vertex_index;
            }
            mesh.elements.push_back(element); // Add the element to the mesh

            index_offset += fv; // Move to the next face
        }
    }

    return true;
}

} // namespace Enmesh