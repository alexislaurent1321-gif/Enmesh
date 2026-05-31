#include <catch2/catch_test_macros.hpp>
#include "mesh/mesh_triangulation.h" 

using namespace Enmesh;

TEST_CASE("Mesh triangulation - simple square", "[mesh_triangulation]") {
    Mesh<Triangle> mesh;
    mesh.vertices = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    
    triangulate(mesh);
    
    REQUIRE(mesh.getNumElements() == 2); // A square should be triangulated into 2 triangles
}

TEST_CASE("Mesh triangulation - collinear points", "[mesh_triangulation]") {
    Mesh<Triangle> mesh;
    mesh.vertices = {{0, 0}, {1, 0}, {2, 0}}; // Collinear points
    
    triangulate(mesh);
    
    REQUIRE(mesh.getNumElements() == 0); // Collinear points cannot form a triangle
}

TEST_CASE("Mesh triangulation - duplicate points", "[mesh_triangulation]") {
    Mesh<Triangle> mesh;
    mesh.vertices = {{0, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 0}}; // Duplicate point at (0, 0)
    
    triangulate(mesh);
    
    REQUIRE(mesh.getNumElements() == 2); // The duplicate point should not affect the triangulation
}

TEST_CASE("Mesh triangulation - random points", "[mesh_triangulation]") {
    Mesh<Triangle> mesh;
    mesh.vertices = {{0, 0}, {1, 0}, {1, 1}, {0, 1}, {0.5, 0.5}}; // Random point in the center of the square
    
    triangulate(mesh);
    
    REQUIRE(mesh.getNumElements() == 4); // The random point should create additional triangles
}