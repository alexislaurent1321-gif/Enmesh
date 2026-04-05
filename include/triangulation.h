#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <algorithm>
#include <iostream>
#include <string_view>
 
#include "mesh.h"





/** 
 * @brief Class for performing Delaunay triangulation
 */
class Delaunay {
public:
    Mesh mesh;


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
        double ax = this->mesh.vertices[triangle.v[0]].x - P.x;
        double ay = this->mesh.vertices[triangle.v[0]].y - P.y;
        double bx = this->mesh.vertices[triangle.v[1]].x - P.x;
        double by = this->mesh.vertices[triangle.v[1]].y - P.y;
        double cx = this->mesh.vertices[triangle.v[2]].x - P.x;
        double cy = this->mesh.vertices[triangle.v[2]].y - P.y;

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
     * @brief Create a super-triangle that encompasses all vertices in the mesh
     * @return The super-triangle
     */
    Triangle createSuperTriangle() {
        // Create a super-triangle that encompasses all vertices in the mesh
        float minX = std::numeric_limits<float>::max();
        float minY = std::numeric_limits<float>::max();
        float maxX = std::numeric_limits<float>::lowest();
        float maxY = std::numeric_limits<float>::lowest();

        for (const auto& vertex : mesh.vertices) {
            minX = std::min(minX, vertex.x);
            minY = std::min(minY, vertex.y);
            maxX = std::max(maxX, vertex.x);
            maxY = std::max(maxY, vertex.y);
        }

        float dx = maxX - minX;
        float dy = maxY - minY;
        float deltaMax = std::max(dx, dy) * 10; // Scale factor to ensure the super-triangle is large enough

        Point p1 = {minX - deltaMax, minY - deltaMax};
        Point p2 = {minX + dx / 2, maxY + deltaMax};
        Point p3 = {maxX + deltaMax, minY - deltaMax};

        int index1 = mesh.vertices.size();
        int index2 = mesh.vertices.size() + 1;
        int index3 = mesh.vertices.size() + 2;

        mesh.vertices.push_back(p1);
        mesh.vertices.push_back(p2);
        mesh.vertices.push_back(p3);

        return {index1, index2, index3};
    }

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
            Edge edges[3] = {{triangle.v[0], triangle.v[1]}, {triangle.v[1], triangle.v[2]}, {triangle.v[2], triangle.v[0]}};
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

    /** 
     * @brief Perform Delaunay triangulation on the current set of vertices in the mesh
     * @return A vector of triangles representing the Delaunay triangulation
     */
    std::vector<Triangle> triangulate() {
        // Start with a super-triangle that encompasses all vertices
        Triangle superTriangle = createSuperTriangle();
        mesh.triangles.push_back(superTriangle);

        // Add each vertex to the triangulation
        for (const auto& vertex : mesh.vertices) {
            addPoint(vertex);
        }

        // Remove triangles that include the vertices of the super-triangle
        mesh.triangles.erase(std::remove_if(mesh.triangles.begin(), mesh.triangles.end(), 
        [this, superTriangle](const Triangle& triangle){ 
            return isPointInCircumcircle(triangle, mesh.vertices[superTriangle.v[0]]) || 
                isPointInCircumcircle(triangle, mesh.vertices[superTriangle.v[1]]) || 
                isPointInCircumcircle(triangle, mesh.vertices[superTriangle.v[2]]); 
        }), mesh.triangles.end());

        return mesh.triangles;
    }

    
};


void generateGrid(Mesh& mesh, int width, int height) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            mesh.vertices.push_back({static_cast<float>(x), static_cast<float>(y)});
        }
    }
}

#endif  