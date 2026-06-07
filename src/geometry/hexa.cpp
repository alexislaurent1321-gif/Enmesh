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


/** @brief Get the 6 faces of the hexahedron
 * @return An array of 6 quadrilateral faces
 */
std::array<Quad, 6> Hexa::getFaces() const {
    return {
        Quad{v[0], v[3], v[2], v[1]}, // down
        Quad{v[4], v[5], v[6], v[7]}, // top
        Quad{v[0], v[1], v[5], v[4]}, // front
        Quad{v[2], v[3], v[7], v[6]}, // back
        Quad{v[0], v[4], v[7], v[3]}, // left
        Quad{v[1], v[2], v[6], v[5]}  // right
    };
}

} // namespace Enmesh