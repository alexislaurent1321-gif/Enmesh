#include "tetrahedron.h"


bool tetrahedron::containsPoint(const std::vector<Point>& vertices, const Point& P) {
    
    Point A = vertices[v[0]];
    Point B = vertices[v[1]];
    Point C = vertices[v[2]];
    Point D = vertices[v[3]];

    // Translate points to the origin for better numerical stability
    float ax = A.x - P.x;
    float ay = A.y - P.y;
    float az = A.z - P.z;
    float bx = B.x - P.x;
    float by = B.y - P.y;
    float bz = B.z - P.z;
    float cx = C.x - P.x;
    float cy = C.y - P.y;
    float cz = C.z - P.z;
    float dx = D.x - P.x;
    float dy = D.y - P.y;
    float dz = D.z - P.z;       

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


bool tetrahedron::containsEdge(int v1, int v2) const {
    
    return (v[0] == v1 && v[1] == v2) || (v[1] == v1 && v[0] == v2) ||
            (v[0] == v1 && v[2] == v2) || (v[2] == v1 && v[0] == v2) ||
            (v[0] == v1 && v[3] == v2) || (v[3] == v1 && v[0] == v2) ||
            (v[1] == v1 && v[2] == v2) || (v[2] == v1 && v[1] == v2) ||
            (v[1] == v1 && v[3] == v2) || (v[3] == v1 && v[1] == v2) ||
            (v[2] == v1 && v[3] == v2) || (v[3] == v1 && v[2] == v2);

    return false; 
}