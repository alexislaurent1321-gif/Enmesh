cmake_minimum_required(VERSION 3.20)
project(Enmesh LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(extern/mshio)
add_subdirectory(extern/Catch2)

add_library(Enmesh STATIC 
    src/geometry/triangle.cpp
    src/geometry/quad.cpp
    src/geometry/tetra.cpp
    src/geometry/hexa.cpp
    src/geometry/point.cpp

    src/mesh/mesh.cpp
    src/mesh/mesh_smoothing.cpp
    src/mesh/mesh_basic_shapes.cpp
    src/mesh/mesh_triangulation.cpp

    src/mesh/mesh_analysis/mesh_analysis_boundaries.tpp
    src/mesh/mesh_analysis/mesh_analysis_aspectRatio.tpp
    src/mesh/mesh_analysis/mesh_analysis_count.tpp
    src/mesh/mesh_analysis/mesh_analysis.tpp
    src/mesh/mesh_analysis/mesh_analysis_valences.tpp

    src/io/exportToVTK.tpp
    src/io/loadMsh.tpp
)

target_include_directories(Enmesh PUBLIC include/Enmesh)

target_link_libraries(Enmesh PUBLIC mshio Catch2)


# Demos

add_executable(analyzer demos/demo_analyzer.cpp)
target_link_libraries(analyzer PRIVATE Enmesh)

add_executable(analyzer3D demos/demo_analyzer3D.cpp)
target_link_libraries(analyzer3D PRIVATE Enmesh)

add_executable(smoothing demos/demo_smoothing.cpp)
target_link_libraries(smoothing PRIVATE Enmesh)

add_executable(triangulation demos/demo_triangulation.cpp)
target_link_libraries(triangulation PRIVATE Enmesh)

add_executable(generateGrid demos/demo_generateGrid.cpp)
target_link_libraries(generateGrid PRIVATE Enmesh)

# Tests

enable_testing()

add_executable(tests
    tests/test_geometry/test_triangle.cpp
    tests/test_geometry/test_quad.cpp
    tests/test_geometry/test_hexa.cpp
    tests/test_geometry/test_tetra.cpp
    tests/test_geometry/test_point.cpp

    tests/test_mesh/test_mesh.cpp
    tests/test_mesh/test_mesh_analysis.cpp
    tests/test_mesh/test_mesh_triangulation.cpp
    tests/test_mesh/test_mesh_basic_shapes.cpp
)

target_link_libraries(tests PRIVATE Enmesh Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(tests)