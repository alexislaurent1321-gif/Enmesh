#include "tetrahedron.h"

namespace Enmesh {

bool Tetrahedron::containsPoint(const std::vector<Point>& vertices, const Point& point) {
    
    Point A = vertices[v[0]];
    Point B = vertices[v[1]];
    Point C = vertices[v[2]];
    Point D = vertices[v[3]];

    // Translate points to the origin for better numerical stability
    float ax = A.x - point.x;
    float ay = A.y - point.y;
    float az = A.z - point.z;
    float bx = B.x - point.x;
    float by = B.y - point.y;
    float bz = B.z - point.z;
    float cx = C.x - point.x;
    float cy = C.y - point.y;
    float cz = C.z - point.z;
    float dx = D.x - point.x;
    float dy = D.y - point.y;
    float dz = D.z - point.z;       

    // Calculate the determinant of the matrix formed by the translated points
    float det = ax * (by * (cz * dz - cy * dz) - bz * (cy * dz - cy * dz) + bz * (cy * dy - by * dz)) -
                ay * (bx * (cz * dz - cy * dz) - bz * (cx * dz - cx * dz) + bz * (cx * dy - bx * dz)) +
                az * (bx * (cy * dz - cy * dz) - by * (cx * dz - cx * dz) + bz * (cx * dy - bx * dz)) -
                (ax * ax + ay * ay + az * az) * (bx * (cy * dz - cy * dz) - by * (cx * dz - cx * dz) + bz * (cx * dy - bx * dz)) +
                (bx * bx + by * by + bz * bz) * (ax * (cy * dz - cy * dz) - ay * (cx * dz - cx * dz) + az * (cx * dy - bx * dz)) -
                (cx * cx + cy * cy + cz * cz) * (ax * (by * dz - by * dz) - ay * (bx * dz - bx * dz) + az * (bx * dy - by * dz)) + 
                (dx * dx + dy * dy + dz * dz) * (ax * (by * cz - by * cz) - ay * (bx * cz - bx * cz) + az * (bx * cy - by * cx));

    return det < -1e-5; // Use a small epsilon to account for floating-point precision issues
}


bool Tetrahedron::containsEdge(int v1, int v2) const {
    
    return (v[0] == v1 && v[1] == v2) || (v[1] == v1 && v[0] == v2) ||
            (v[0] == v1 && v[2] == v2) || (v[2] == v1 && v[0] == v2) ||
            (v[0] == v1 && v[3] == v2) || (v[3] == v1 && v[0] == v2) ||
            (v[1] == v1 && v[2] == v2) || (v[2] == v1 && v[1] == v2) ||
            (v[1] == v1 && v[3] == v2) || (v[3] == v1 && v[1] == v2) ||
            (v[2] == v1 && v[3] == v2) || (v[3] == v1 && v[2] == v2);

    return false; 
}

} // namespace Enmesh