#include "mesh/mesh_basic_shapes.h"
#include "mesh/mesh_analysis.h"

namespace Enmesh {

template <>
inline Mesh<Triangle> generateGrid(int Nx, int Ny, float Lx, float Ly) {
    Mesh<Triangle> mesh;
    float dx = Lx / (Nx - 1);
    float dy = Ly / (Ny - 1);

    // Generate vertices
    for (int j = 0; j < Ny; ++j) {
        for (int i = 0; i < Nx; ++i) {
            mesh.vertices.push_back({i * dx, j * dy});
        }
    }

    // Generate triangles
    for (int j = 0; j < Ny - 1; ++j) {
        for (int i = 0; i < Nx - 1; ++i) {
            size_t v0 = j * Nx + i;
            size_t v1 = v0 + 1;
            size_t v2 = v0 + Nx;
            size_t v3 = v2 + 1;

            mesh.elements.push_back({v0, v1, v2}); // First triangle
            mesh.elements.push_back({v1, v3, v2}); // Second triangle
        }
    }

    // Boundary conditions 
    Enmesh::computeBoundaries(mesh);

    for(auto& edge : mesh.boundaryElements) {
        if(edge.v[0] < Nx && edge.v[1] < Nx) { // Bottom boundary
            mesh.boundaryTags.push_back(1);
        } else if (edge.v[0] >= (Ny - 1) * Nx && edge.v[1] >= (Ny - 1) * Nx) { // Top boundary
            mesh.boundaryTags.push_back(2);
        } else if (edge.v[0] % Nx == 0 && edge.v[1] % Nx == 0) { // Left boundary
            mesh.boundaryTags.push_back(3);
        } else if (edge.v[0] % Nx == Nx - 1 && edge.v[1] % Nx == Nx - 1) { // Right boundary
            mesh.boundaryTags.push_back(4);
        }
    }

    return mesh;
}


template <>
inline Mesh<Quad> generateGrid(int Nx, int Ny, float Lx, float Ly) {
    Mesh<Quad> mesh;
    float dx = Lx / (Nx - 1);
    float dy = Ly / (Ny - 1);

    // Generate vertices
    for (int j = 0; j < Ny; ++j) {
        for (int i = 0; i < Nx; ++i) {
            mesh.vertices.push_back({i * dx, j * dy});
        }
    }

    // Generate quads
    for (int j = 0; j < Ny - 1; ++j) {
        for (int i = 0; i < Nx - 1; ++i) {
            size_t v0 = j * Nx + i;
            size_t v1 = v0 + 1;
            size_t v2 = v0 + Nx;
            size_t v3 = v2 + 1;

            mesh.elements.push_back({v0, v1, v3, v2}); // Quad
        }
    }

    // Boundary conditions 
    Enmesh::computeBoundaries(mesh);

    for(auto& edge : mesh.boundaryElements) {
        if(edge.v[0] < Nx && edge.v[1] < Nx) { // Bottom boundary
            mesh.boundaryTags.push_back(1);
        } else if (edge.v[0] >= (Ny - 1) * Nx && edge.v[1] >= (Ny - 1) * Nx) { // Top boundary
            mesh.boundaryTags.push_back(2);
        } else if (edge.v[0] % Nx == 0 && edge.v[1] % Nx == 0) { // Left boundary
            mesh.boundaryTags.push_back(3);
        } else if (edge.v[0] % Nx == Nx - 1 && edge.v[1] % Nx == Nx - 1) { // Right boundary
            mesh.boundaryTags.push_back(4);
        }
    }

    return mesh;
}


} // namespace Enmesh