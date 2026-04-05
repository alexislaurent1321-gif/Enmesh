#include "mesh_generation/basic_shapes.h"

void generateGrid(Mesh& mesh, int width, int height) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            mesh.vertices.push_back({static_cast<float>(x), static_cast<float>(y)});
        }
    }
}