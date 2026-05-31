#include <catch2/catch_test_macros.hpp>
#include "geometry/tetra.h"

using namespace Enmesh;

TEST_CASE("Tetra equality - same vertices", "[tetra]") {
    Tetra tetra1{{0, 1, 2, 3}};
    Tetra tetra2{{3, 0, 1, 2}}; 
    REQUIRE(tetra1 == tetra2);
}

TEST_CASE("Tetra equality - different vertices", "[tetra]") {
    Tetra tetra1{{0, 1, 2, 3}};
    Tetra tetra2{{0, 1, 2, 4}};
    REQUIRE_FALSE(tetra1 == tetra2);
}

TEST_CASE("Tetra containsEdge - existing edge", "[tetra]") {
    Tetra tetra{{0, 1, 2, 3}};
    REQUIRE(tetra.containsEdge(0, 1));
    REQUIRE(tetra.containsEdge(1, 2));
    REQUIRE(tetra.containsEdge(0, 2));
}

TEST_CASE("Tetra containsEdge - non existing edge", "[tetra]") {
    Tetra tetra{{0, 1, 2, 3}};
    REQUIRE_FALSE(tetra.containsEdge(0, 4));
}

TEST_CASE("Tetra containsPoint - point inside circumcircle", "[tetra]") {
    Tetra tetra{{0, 1, 2, 3}};
    std::vector<Point> vertices = {{0, 0}, {1, 0}, {0, 1}, {0, 0}};
    Point p{0.5, 0.5}; 
    REQUIRE(tetra.containsPoint(vertices, p));
}

TEST_CASE("Tetra containsPoint - point outside circumcircle", "[tetra]") {
    Tetra tetra{{0, 1, 2, 3}};
    std::vector<Point> vertices = {{0, 0}, {1, 0}, {0, 1}, {0, 0}};
    Point p{1.5, 1.5}; 
    REQUIRE_FALSE(tetra.containsPoint(vertices, p));
}