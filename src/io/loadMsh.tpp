#include "io/loadMsh.h"
#include <mshio/mshio.h>
#include <map>

namespace Enmesh {

template <typename Element>
bool loadMsh(Mesh<Element>& mesh, const std::string& path) {
    mshio::MshSpec spec = mshio::load_msh(path);
    
    mesh.vertices.clear();
    mesh.elements.clear();
    mesh.boundaryElements.clear();
    mesh.boundaryTags.clear();

    // create a mapping from node tags to vertex indices in the mesh
    std::map<size_t, size_t> tagToIndex;


    // Load nodes
    for (const auto& node_block : spec.nodes.entity_blocks) {
        for (size_t i = 0; i < node_block.num_nodes_in_block; ++i) {

            size_t tag = node_block.tags[i];                                // Get the tag for the current node
            tagToIndex[tag] = static_cast<size_t>(mesh.vertices.size());    // Map the node tag to the current vertex index in the mesh
            
            mesh.vertices.push_back({
                static_cast<float>(node_block.data[i * 3]),
                static_cast<float>(node_block.data[i * 3 + 1]),
                static_cast<float>(node_block.data[i * 3 + 2])
            });
        }
    }


    // Load elements
    for (const auto& entity_block : spec.elements.entity_blocks) {

        if (entity_block.element_type == Element::type) { 
            // Each element block has a specific format: the first value is the element tag, followed by the node tags that define the element.
            const size_t nodesPerElem = Element::numVertices;     // Determine the number of nodes per element based on the mesh type
            const size_t stride = 1 + nodesPerElem; 

            for (size_t i = 0; i < entity_block.num_elements_in_block; ++i) {

                Element element;
                for (size_t j = 0; j < nodesPerElem; ++j) {
                    element.v[j] = tagToIndex[entity_block.data[i * stride + (j + 1)]];
                }

                mesh.elements.push_back(element);
            }
        }

        // Load boundary elements and tags
        if (entity_block.element_type == Element::boundaryType) { 
            using BoundaryType = typename Boundary<Element>::type;

            const size_t nodesPerElem = Element::boundaryNumVertices;     // Determine the number of nodes per element based on the mesh type
            const size_t stride = 1 + nodesPerElem; 

            for (size_t i = 0; i < entity_block.num_elements_in_block; ++i) {
                
                BoundaryType boundaryElement;
                for (size_t j = 0; j < nodesPerElem; ++j) {
                    boundaryElement.v[j] = tagToIndex[entity_block.data[i * stride + (j + 1)]];
                }

                mesh.boundaryElements.push_back(boundaryElement );
                mesh.boundaryTags.push_back(entity_block.entity_tag);
            }   
        }   
    }


    return !mesh.elements.empty();
}

} // namespace Enmesh