#include <catch2/catch_test_macros.hpp>
#include "geometry/triangle.h"

using namespace Enmesh;

TEST_CASE("Triangle equality - same vertices", "[triangle]") {
    Triangle triangle1{{0, 1, 2}};
    Triangle triangle2{{2, 0, 1}}; 
    REQUIRE(triangle1 == triangle2);
}

TEST_CASE("Triangle equality - different vertices", "[triangle]") {
    Triangle triangle1{{0, 1, 2}};
    Triangle triangle2{{0, 1, 3}};
    REQUIRE_FALSE(triangle1 == triangle2);
}

TEST_CASE("Triangle containsEdge - existing edge", "[triangle]") {
    Triangle triangle{{0, 1, 2}};
    REQUIRE(triangle.containsEdge(0, 1));
    REQUIRE(triangle.containsEdge(1, 2));
    REQUIRE(triangle.containsEdge(0, 2));
}

TEST_CASE("Triangle containsEdge - non existing edge", "[triangle]") {
    Triangle triangle{{0, 1, 2}};
    REQUIRE_FALSE(triangle.containsEdge(0, 3));
}

TEST_CASE("Triangle containsPoint - point inside circumcircle", "[triangle]") {
    Triangle triangle{{0, 1, 2}};
    std::vector<Point> vertices = {{0, 0}, {1, 0}, {0, 1}};
    Point point{0.5, 0.5}; 
    REQUIRE(triangle.containsPoint(vertices, point));
}

TEST_CASE("Triangle containsPoint - point outside circumcircle", "[triangle]") {
    Triangle triangle{{0, 1, 2}};
    std::vector<Point> vertices = {{0, 0}, {1, 0}, {0, 1}};
    Point point{1.5, 1.5}; 
    REQUIRE_FALSE(triangle.containsPoint(vertices, point));
}