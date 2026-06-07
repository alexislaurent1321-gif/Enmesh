#ifndef ENMESH_BOUNDARY_H
#define ENMESH_BOUNDARY_H

#include "geometry/point.h"
#include "geometry/edge.h"
#include "geometry/triangle.h"
#include "geometry/quad.h"
#include "geometry/tetra.h"
#include "geometry/hexa.h"

namespace Enmesh {

/**
 * @brief Traits class to define the boundary element type for each mesh element type
 * 
 */
template <typename Element>
struct Boundary;

template <>
struct Boundary<Triangle> {
    using type = Edge;
};

template <>
struct Boundary<Quad> {
    using type = Edge;
};

template <>
struct Boundary<Tetra> {
    using type = Triangle;
};

template <>
struct Boundary<Hexa> {
    using type = Quad;
};

} // namespace Enmesh

#endif 