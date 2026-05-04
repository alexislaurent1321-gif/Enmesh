#include "geometry/quad.h"

namespace Enmesh {

bool Quad::containsEdge(size_t v1, size_t v2) const {
    return (v[0] == v1 && v[1] == v2) || (v[1] == v1 && v[0] == v2) ||
            (v[1] == v1 && v[2] == v2) || (v[2] == v1 && v[1] == v2) ||
            (v[2] == v1 && v[0] == v2) || (v[0] == v1 && v[2] == v2) ||
            (v[0] == v1 && v[3] == v2) || (v[3] == v1 && v[0] == v2) ||
            (v[1] == v1 && v[3] == v2) || (v[3] == v1 && v[1] == v2) ||
            (v[2] == v1 && v[3] == v2) || (v[3] == v1 && v[2] == v2);
}

} // namespace Enmesh