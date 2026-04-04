#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include "mesh.h"

/** 
 * @brief Check if a point is inside the circumcircle of a triangle
 * @param A First vertex of the triangle
 * @param B Second vertex of the triangle
 * @param C Third vertex of the triangle
 * @param P The point to check
 * @return true if P is inside the circumcircle, false otherwise
 */
bool isPointInCircumcircle(const Triangle& triangle, const Point& P) {

    // Shift the points so that P is at the origin
    double ax = mesh.vertices[triangle.v[0]].x - P.x;
    double ay = mesh.vertices[triangle.v[0]].y - P.y;
    double bx = mesh.vertices[triangle.v[1]].x - P.x;
    double by = mesh.vertices[triangle.v[1]].y - P.y;
    double cx = mesh.vertices[triangle.v[2]].x - P.x;
    double cy = mesh.vertices[triangle.v[2]].y - P.y;

    // Calculate the determinant of the matrix formed by the shifted points
    double det31 = ax * ax + ay * ay;
    double det32 = bx * bx + by * by;
    double det33 = cx * cx + cy * cy;

    // If the determinant is positive, P is inside the circumcircle of triangle ABC
    double det = ax * (by * det33 - cy * det32) -
                 ay * (bx * det33 - cx * det32) +
                 det31 * (bx * cy - cx * by);

    return det > 1e-9; // Use a small epsilon to account for floating-point precision issues
}



/** 
 * @brief Class for performing Delaunay triangulation
 */
class Delaunay {
public:
    Mesh mesh;

    /** 
     * @brief Add a point to the triangulation and update the mesh accordingly
     * @param point The point to add
     */
    void addPoint(const Point& point) {
        int pointIndex = mesh.vertices.size();
        mesh.vertices.push_back(point);

        // Find all triangles whose circumcircle contains the new point
        std::vector<Triangle> badTriangles;
        for (auto& triangle : mesh.triangles) {
            if (isPointInCircumcircle(triangle, point)) {
                triangle.isBad = true;
                badTriangles.push_back(triangle);
            }
        }

        // Find the boundary of the polygonal hole created by removing the bad triangles
        std::vector<Edge> polygon;
        for (const auto& triangle : badTriangles) {
            Edge edges[3] = {{triangle.v1, triangle.v2}, {triangle.v2, triangle.v3}, {triangle.v3, triangle.v1}};
            for (auto& edge : edges) {
                bool shared = false;
                for (const auto& other : badTriangles) {
                    if (&triangle == &other) continue;
                    if (other.containsEdge(edge.v1, edge.v2)) {
                        shared = true;
                        break;
                    }
                }
                if (!shared) polygon.push_back(edge);
            }
        }

        // Remove the bad triangles from the mesh
        mesh.triangles.erase(std::remove_if(mesh.triangles.begin(), mesh.triangles.end(), 
                       [](const Triangle& triangle){ return triangle.isBad; }), mesh.triangles.end());

        // Retriangulate the polygonal hole by connecting the new point to the vertices of the polygon
        for (const auto& edge : polygon) {
            mesh.triangles.push_back({edge.v1, edge.v2, pointIndex});
        }
    }

    
};

#endif  