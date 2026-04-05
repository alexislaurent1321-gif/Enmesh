#include "geometry/triangle.h"

bool Triangle::containsEdge(int v1, int v2) const {
    return (v[0] == v1 && v[1] == v2) || (v[1] == v1 && v[0] == v2) ||
            (v[1] == v1 && v[2] == v2) || (v[2] == v1 && v[1] == v2) ||
            (v[2] == v1 && v[0] == v2) || (v[0] == v1 && v[2] == v2);
}