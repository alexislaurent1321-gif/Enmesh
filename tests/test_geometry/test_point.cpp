#include <catch2/catch_test_macros.hpp>
#include "geometry/point.h" 

using namespace Enmesh;

TEST_CASE("Point length - origin", "[point]") {
    Point point;
    REQUIRE(point.length() == 0);
}

TEST_CASE("Point length - non-zero", "[point]") {
    Point point(3, 4);
    REQUIRE(point.length() == 5);
}

TEST_CASE("Point distance - same point", "[point]") {
    Point point1(1, 2, 3);
    Point point2(1, 2, 3);
    REQUIRE(point1.distance(point2) == 0);
}

TEST_CASE("Point operators - addition", "[point]") {
    Point point1(1, 2, 3);
    Point point2(4, 5, 6);
    Point result = point1 + point2;
    REQUIRE(result.x == 5);
    REQUIRE(result.y == 7);
    REQUIRE(result.z == 9);
}

TEST_CASE("Point operators - subtraction", "[point]") {
    Point point1(4, 5, 6);
    Point point2(1, 2, 3);
    Point result = point1 - point2;
    REQUIRE(result.x == 3);
    REQUIRE(result.y == 3);
    REQUIRE(result.z == 3);
}

TEST_CASE("Point operators - scalar multiplication", "[point]") {
    Point point(1, 2, 3);
    Point result = point * 2;
    REQUIRE(result.x == 2);
    REQUIRE(result.y == 4);
    REQUIRE(result.z == 6);
}

TEST_CASE("Point operators - scalar division", "[point]") {
    Point point(2, 4, 6);
    Point result = point / 2;
    REQUIRE(result.x == 1);
    REQUIRE(result.y == 2);
    REQUIRE(result.z == 3);
}

TEST_CASE("Point operators - equality", "[point]") {
    Point point1(1, 2, 3);
    Point point2(1, 2, 3);
    Point point3(4, 5, 6);
    REQUIRE(point1 == point2);
    REQUIRE_FALSE(point1 == point3);
}

TEST_CASE("Point dot product", "[point]") {
    Point point1(1, 2, 3);
    Point point2(4, 5, 6);
    float result = point1.dot(point2);
    REQUIRE(result == 32);
}

TEST_CASE("Point cross product", "[point]") {
    Point point1(1, 2, 3);
    Point point2(4, 5, 6);
    Point result = point1.cross(point2);
    REQUIRE(result.x == -3);
    REQUIRE(result.y == 6);
    REQUIRE(result.z == -3);
}