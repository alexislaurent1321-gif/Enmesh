#include <catch2/catch_test_macros.hpp>
#include "mesh.h" 

using namespace Enmesh;

TEST_CASE("Empty mesh has zero vertices and elements", "[mesh]") {
    Mesh<Triangle> m;
    REQUIRE(m.getNumVertices() == 0);
    REQUIRE(m.getNumElements() == 0);
}

TEST_CASE("Mesh vertex count matches inserted vertices", "[mesh]") {
    Mesh<Triangle> m;
    m.vertices = {{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}};
    REQUIRE(m.getNumVertices() == 3);
}

TEST_CASE("Mesh element count matches inserted elements", "[mesh]") {
    Mesh<Triangle> m;
    m.elements = {{{0, 1, 2}}};
    REQUIRE(m.getNumElements() == 1);
}