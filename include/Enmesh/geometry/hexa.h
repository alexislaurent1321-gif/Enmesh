#ifndef HEXAHEDRON_H
#define HEXAHEDRON_H

#include <vector>
#include <array>
#include <iostream>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>


#include "geometry/point.h"
#include "geometry/edge.h"
#include "geometry/quad.h"


namespace Enmesh {

struct Hexa {

    static constexpr size_t type = 5;           ///< Gmsh element type for hexahedra
    static constexpr size_t dimension = 3;      ///< Dimension of the hexahedron element
    static constexpr size_t numVertices = 8;    ///< Number of vertices in a hexahedron

    static constexpr size_t boundaryType = 3;           ///< Gmsh element type for boundary quadrilaterals
    static constexpr size_t boundaryDimension = 2;      ///< Dimension of the boundary element (quadrilateral)
    static constexpr size_t boundaryNumVertices = 4;    ///< Number of vertices in a boundary quadrilateral

    std::array<size_t, 8> v;   ///< Indices of the vertices that form the hexahedron

    /**
     * @brief Check if this hexahedron is equal to another (same vertices, regardless of order)
     * @param other The other hexahedron to compare with
     * @return true if the hexahedra are equal, false otherwise
     */
    bool operator==(const Hexa& other) const;


    /** @brief Get the 6 faces of the hexahedron
     * @return An array of 6 quadrilateral faces
     */
    std::array<Quad, 6> getFaces() const;

};

} // namespace Enmesh

#endif 