cmake_minimum_required(VERSION 3.20)
project(Enmesh LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(extern/tinyobjloader)
add_subdirectory(extern/mshio)

add_library(Enmesh STATIC 
    src/geometry/triangle.cpp
    src/geometry/point.cpp

    src/mesh/mesh.cpp
    src/mesh/mesh_smoothing.cpp
    src/mesh/mesh_basic_shapes.cpp
    src/mesh/mesh_triangulation.cpp

    src/mesh/mesh_analysis/mesh_analysis_boundaries.cpp
    src/mesh/mesh_analysis/mesh_analysis_aspectRatio.tpp
    src/mesh/mesh_analysis/mesh_analysis_count.tpp
    src/mesh/mesh_analysis/mesh_analysis.tpp

    src/io/exportToVTK.cpp
    src/io/loadMsh.tpp
    src/io/loadObj.cpp
)

target_include_directories(Enmesh PUBLIC include/Enmesh)

target_link_libraries(Enmesh PUBLIC mshio tinyobjloader)


# Demos

add_executable(analyzer demos/demo_analyzer.cpp)
target_link_libraries(analyzer PRIVATE Enmesh)

add_executable(analyzer3D demos/demo_analyzer3D.cpp)
target_link_libraries(analyzer3D PRIVATE Enmesh)

add_executable(smoothing demos/demo_smoothing.cpp)
target_link_libraries(smoothing PRIVATE Enmesh)

add_executable(triangulation demos/demo_triangulation.cpp)
target_link_libraries(triangulation PRIVATE Enmesh)
