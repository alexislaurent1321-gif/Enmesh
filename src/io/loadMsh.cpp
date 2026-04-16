#include "io/loadMsh.h"
#include <mshio/mshio.h>
#include <map>


bool loadMsh(Mesh<Triangle>& mesh, const std::string& path) {
    mshio::MshSpec spec = mshio::load_msh(path);
    
    mesh.vertices.clear();
    mesh.elements.clear();

    // create a mapping from node tags to vertex indices in the mesh
    std::map<size_t, int> tagToIndex;

    // Load nodes
    for (const auto& node_block : spec.nodes.entity_blocks) {
        for (size_t i = 0; i < node_block.num_nodes_in_block; ++i) {

            size_t tag = node_block.tags[i];                            // Get the tag for the current node
            tagToIndex[tag] = static_cast<int>(mesh.vertices.size());   // Map the node tag to the current vertex index in the mesh
            
            mesh.vertices.push_back({
                static_cast<float>(node_block.data[i * 3]),
                static_cast<float>(node_block.data[i * 3 + 1]),
                static_cast<float>(node_block.data[i * 3 + 2])
            });
        }
    }

    // Load elements (triangles)
    for (const auto& entity_block : spec.elements.entity_blocks) {
        // We are only interested in triangles, which have an element type of 2 in Gmsh.
        if (entity_block.element_type != 2) continue; 

        // Each element block has a specific format: the first value is the element tag, followed by the node tags that define the element.
        const size_t nodesPerElem = 3;
        const size_t stride = 1 + nodesPerElem; 

        for (size_t i = 0; i < entity_block.num_elements_in_block; ++i) {

            // Add the triangle to the mesh using the vertex indices from the tagToIndex mapping
            mesh.elements.push_back({
                tagToIndex[entity_block.data[i * stride + 1]],
                tagToIndex[entity_block.data[i * stride + 2]],
                tagToIndex[entity_block.data[i * stride + 3]]
            });
        }
    }

    return !mesh.elements.empty();
}


bool loadMsh(Mesh<Tetrahedron>& mesh, const std::string& path) {
    mshio::MshSpec spec = mshio::load_msh(path);
    
    mesh.vertices.clear();
    mesh.elements.clear();

    // create a mapping from node tags to vertex indices in the mesh
    std::map<size_t, int> tagToIndex;

    // Load nodes
    for (const auto& node_block : spec.nodes.entity_blocks) {
        for (size_t i = 0; i < node_block.num_nodes_in_block; ++i) {
            size_t tag = node_block.tags[i];
            tagToIndex[tag] = static_cast<int>(mesh.vertices.size());
            
            mesh.vertices.push_back({
                static_cast<float>(node_block.data[i * 3]),
                static_cast<float>(node_block.data[i * 3 + 1]),
                static_cast<float>(node_block.data[i * 3 + 2])
            });
        }
    }

    // Load elements (tetrahedrons)
    for (const auto& entity_block : spec.elements.entity_blocks) {
        // We are only interested in tetrahedrons, which have an element type of 4 in Gmsh.
        if (entity_block.element_type != 4) continue; 

        // Each element block has a specific format: the first value is the element tag, followed by the node tags that define the element.
        const size_t nodesPerElem = 4;
        const size_t stride = 1 + nodesPerElem; 

        for (size_t i = 0; i < entity_block.num_elements_in_block; ++i) {
            // Add the tetrahedron to the mesh using the vertex indices from the tagToIndex mapping
            mesh.elements.push_back({
                tagToIndex[entity_block.data[i * stride + 1]],
                tagToIndex[entity_block.data[i * stride + 2]],
                tagToIndex[entity_block.data[i * stride + 3]],
                tagToIndex[entity_block.data[i * stride + 4]]
            });
        }
    }

    return !mesh.elements.empty();
}



  