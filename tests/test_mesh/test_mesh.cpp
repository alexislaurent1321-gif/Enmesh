#include <catch2/catch_test_macros.hpp>
#include "mesh/mesh.h" 

using namespace Enmesh;

TEST_CASE("Empty mesh has zero vertices and elements", "[mesh]") {
    Mesh<Triangle> mesh;
    REQUIRE(mesh.getNumVertices() == 0);
    REQUIRE(mesh.getNumElements() == 0);
}

TEST_CASE("Mesh vertex count matches inserted vertices", "[mesh]") {
    Mesh<Triangle> mesh;
    mesh.vertices = {{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}};
    REQUIRE(mesh.getNumVertices() == 3);
}

TEST_CASE("Mesh element count matches inserted elements", "[mesh]") {
    Mesh<Triangle> mesh;
    mesh.elements = {{{0, 1, 2}}};
    REQUIRE(mesh.getNumElements() == 1);
}