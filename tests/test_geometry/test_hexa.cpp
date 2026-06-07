#include <catch2/catch_test_macros.hpp>
#include "geometry/hexa.h"

using namespace Enmesh;

TEST_CASE("Hexa equality - same vertices", "[hexa]") {
    Hexa hexa1{{0, 1, 2, 3, 4, 5, 6, 7}};
    Hexa hexa2{{7, 6, 5, 4, 3, 2, 1, 0}};
    REQUIRE(hexa1 == hexa2);
}

TEST_CASE("Hexa equality - different vertices", "[hexa]") {
    Hexa hexa1{{0, 1, 2, 3, 4, 5, 6, 7}};
    Hexa hexa2{{0, 1, 2, 3, 4, 5, 6, 8}};
    REQUIRE_FALSE(hexa1 == hexa2);
}
