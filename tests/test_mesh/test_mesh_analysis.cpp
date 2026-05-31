#include <catch2/catch_test_macros.hpp>
#include "mesh/mesh_analysis.h" 

using namespace Enmesh;

TEST_CASE("Mesh analysis - empty mesh", "[mesh_analysis]") {
    Mesh<Tetra> mesh;
    REQUIRE(mesh.getNumVertices() == 0);
    REQUIRE(mesh.getNumElements() == 0);
}

TEST_CASE("Mesh analysis - aspect ratio of a single tetrahedron", "[mesh_analysis]") {
    Mesh<Tetra> mesh;
    mesh.vertices = {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    mesh.elements = {{{0, 1, 2, 3}}};
    
    // Assuming calculateAspectRatios is implemented and fills the ratios vector
    calculateAspectRatios(mesh);
    
    REQUIRE(mesh.ratios.size() == 1);
    REQUIRE(mesh.ratios[0] > 0); // Aspect ratio should be positive
}

TEST_CASE("Mesh analysis - aspect ratio of multiple tetrahedra", "[mesh_analysis]") {
    Mesh<Tetra> mesh;
    mesh.vertices = {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {1, 1, 1}};
    mesh.elements = {{{0, 1, 2, 3}}, {{1, 2, 3, 4}}};
    
    calculateAspectRatios(mesh);
    
    REQUIRE(mesh.ratios.size() == 2);
    REQUIRE(mesh.ratios[0] > 0);
    REQUIRE(mesh.ratios[1] > 0);
}

TEST_CASE("Mesh analysis - aspect ratio of degenerate tetrahedron", "[mesh_analysis]") {
    Mesh<Tetra> mesh;
    mesh.vertices = {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 0, 0}}; // Degenerate tetrahedron (last vertex is the same as the first)
    mesh.elements = {{{0, 1, 2, 3}}};
    
    calculateAspectRatios(mesh);
    
    REQUIRE(mesh.ratios.size() == 1);
    REQUIRE(mesh.ratios[0] == std::numeric_limits<float>::infinity()); // Aspect ratio should be infinite for degenerate tetrahedron
}

