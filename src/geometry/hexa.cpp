#include "geometry/hexa.h"

namespace Enmesh {

bool Hexa::operator==(const Hexa& other) const {
    std::unordered_set<size_t> vertices(v.begin(), v.end());
    for (size_t vertex : other.v) {
        if (vertices.find(vertex) == vertices.end()) {
            return false; 
        }
    }
    return true; 
}

} // namespace Enmesh