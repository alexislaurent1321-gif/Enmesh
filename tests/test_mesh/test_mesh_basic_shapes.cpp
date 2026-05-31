#include <catch2/catch_test_macros.hpp>
#include "mesh/mesh_basic_shapes.h" 

using namespace Enmesh;

TEST_CASE("Mesh<Triangle> basic shapes - create square", "[mesh_basic_shapes]") {
    Mesh<Triangle> mesh = generateGrid<Triangle>(2, 2, 1.f, 1.f);
    
    REQUIRE(mesh.getNumVertices() == 4);
    REQUIRE(mesh.getNumElements() == 2); // A square should be triangulated into 2 triangles
}

TEST_CASE("Mesh<Quad> basic shapes - create square", "[mesh_basic_shapes]") {
    Mesh<Quad> mesh = generateGrid<Quad>(2, 2, 1.f, 1.f);
    
    REQUIRE(mesh.getNumVertices() == 4);
    REQUIRE(mesh.getNumElements() == 1); // A square should be represented as a single quad
}
