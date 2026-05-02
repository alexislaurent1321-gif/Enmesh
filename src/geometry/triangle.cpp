#include "geometry/triangle.h"

namespace Enmesh {

bool Triangle::containsEdge(size_t v1, size_t v2) const {
    return (v[0] == v1 && v[1] == v2) || (v[1] == v1 && v[0] == v2) ||
            (v[1] == v1 && v[2] == v2) || (v[2] == v1 && v[1] == v2) ||
            (v[2] == v1 && v[0] == v2) || (v[0] == v1 && v[2] == v2);
}


bool Triangle::containsPoint(const std::vector<Point>& vertices,const Point& point) {

    Point A = vertices[v[0]];
    Point B = vertices[v[1]];
    Point C = vertices[v[2]];

    // Translate points to the origin for better numerical stability
    float ax = A.x - point.x;
    float ay = A.y - point.y;
    float bx = B.x - point.x;
    float by = B.y - point.y;
    float cx = C.x - point.x;
    float cy = C.y - point.y;

    // Calculate the determinant of the matrix formed by the translated points
    float det = (ax*ax + ay*ay) * (bx*cy - cx*by) -
                (bx*bx + by*by) * (ax*cy - cx*ay) +
                (cx*cx + cy*cy) * (ax*by - bx*ay);

    return det < -1e-5; // Use a small epsilon to account for floating-point precision issues
}

} // namespace Enmesh