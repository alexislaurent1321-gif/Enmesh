#include <catch2/catch_test_macros.hpp>
#include "geometry/triangle.h"

using namespace Enmesh;

TEST_CASE("Triangle equality - same vertices", "[triangle]") {
    Triangle t1{{0, 1, 2}};
    Triangle t2{{2, 0, 1}}; // même sommets, ordre différent
    REQUIRE(t1 == t2);
}

TEST_CASE("Triangle equality - different vertices", "[triangle]") {
    Triangle t1{{0, 1, 2}};
    Triangle t2{{0, 1, 3}};
    REQUIRE_FALSE(t1 == t2);
}

TEST_CASE("Triangle containsEdge - existing edge", "[triangle]") {
    Triangle t{{0, 1, 2}};
    REQUIRE(t.containsEdge(0, 1));
    REQUIRE(t.containsEdge(1, 2));
    REQUIRE(t.containsEdge(0, 2));
}

TEST_CASE("Triangle containsEdge - non existing edge", "[triangle]") {
    Triangle t{{0, 1, 2}};
    REQUIRE_FALSE(t.containsEdge(0, 3));