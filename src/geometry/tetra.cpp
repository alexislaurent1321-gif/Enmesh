#include "geometry/tetra.h"

namespace Enmesh {

bool Tetra::operator==(const Tetra& other) const {
    std::unordered_set<size_t> vertices(v.begin(), v.end());
    for (size_t vertex : other.v) {
        if (vertices.find(vertex) == vertices.end()) {
            return false; 
        }
    }
    return true; 
}


bool Tetra::containsEdge(size_t v1, size_t v2) const {
    
    return (v[0] == v1 && v[1] == v2) || (v[1] == v1 && v[0] == v2) ||
            (v[0] == v1 && v[2] == v2) || (v[2] == v1 && v[0] == v2) ||
            (v[0] == v1 && v[3] == v2) || (v[3] == v1 && v[0] == v2) ||
            (v[1] == v1 && v[2] == v2) || (v[2] == v1 && v[1] == v2) ||
            (v[1] == v1 && v[3] == v2) || (v[3] == v1 && v[1] == v2) ||
            (v[2] == v1 && v[3] == v2) || (v[3] == v1 && v[2] == v2);

    return false; 
}

} // namespace Enmesh