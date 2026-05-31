#include <catch2/catch_test_macros.hpp>
#include "geometry/quad.h"

using namespace Enmesh;

TEST_CASE("Quad equality - same vertices", "[quad]") {
    Quad quad1{{0, 1, 2, 3}};
    Quad quad2{{3, 0, 1, 2}}; 
    REQUIRE(quad1 == quad2);
}

TEST_CASE("Quad equality - different vertices", "[quad]") {
    Quad quad1{{0, 1, 2, 3}};
    Quad quad2{{0, 1, 2, 4}};
    REQUIRE_FALSE(quad1 == quad2);
}

TEST_CASE("Quad containsEdge - existing edge", "[quad]") {
    Quad quad{{0, 1, 2, 3}};
    REQUIRE(quad.containsEdge(0, 1));
    REQUIRE(quad.containsEdge(1, 2));
    REQUIRE(quad.containsEdge(2, 3));
    REQUIRE(quad.containsEdge(0, 3));
}

TEST_CASE("Quad containsEdge - non existing edge", "[quad]") {
    Quad quad{{0, 1, 2, 3}};
    REQUIRE_FALSE(quad.containsEdge(0, 4));
}