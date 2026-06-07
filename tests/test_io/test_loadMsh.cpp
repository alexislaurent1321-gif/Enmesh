#include <catch2/catch_test_macros.hpp>
#include "io/loadMsh.h"
#include "mesh/mesh_analysis.h"

using namespace Enmesh;


TEST_CASE("Load MSH file with wrong path", "[loadMsh]") {
    Mesh<Quad> mesh;
    REQUIRE_FALSE(loadMsh(mesh, "demos/models/non_existent_file.msh"));
}


TEST_CASE("Load 2D MSH file", "[loadMsh]") {
    Mesh<Quad> mesh;
    loadMsh(mesh, "demos/models/grid_quad.msh");
    
    REQUIRE(mesh.vertices.size() == 121);
    REQUIRE(mesh.elements.size() == 100);
    REQUIRE(mesh.boundaryElements.size() == 40);
    REQUIRE(mesh.boundaryTags.size() == 40);
    REQUIRE(countAllBorders(mesh) == 220);
}


TEST_CASE("Load 3D MSH file", "[loadMsh]") {
    Mesh<Hexa> mesh;
    loadMsh(mesh, "demos/models/cube_hexa.msh");
    
    REQUIRE(mesh.vertices.size() == 729);
    REQUIRE(mesh.elements.size() == 512);
    REQUIRE(mesh.boundaryElements.size() == 384);
    REQUIRE(mesh.boundaryTags.size() == 384);
    REQUIRE(countAllBorders(mesh) == 1536);
}


