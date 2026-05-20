#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <vector>
#include <array>
#include <iostream>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <fstream>

#include "mesh/mesh.h"


namespace Enmesh {

// Quality analysis

/** 
 * @brief   Calculate the aspect ratio of a triangle defined by its vertex indices. An aspect ratio near to 1 indicates a more equilateral triangle
 * 
 * @param element 
 * @return float 
 */
template <typename Element>
float calculateAspectRatio(const Mesh<Element>& mesh, const Element& element);


/**
 * @brief  Calculate the aspect ratio for all triangles in the mesh and store them in the ratios vector
 * 
 */
template <typename Element>
void calculateAspectRatios(Mesh<Element>& mesh);



// Topology analysis

 /**
 * @brief Get the Edge Valences object  
 * 
 * @return std::unordered_map<Edge, size_t, EdgeHash> 
 */
template <typename Element>
std::unordered_map<Edge, size_t, EdgeHash> getEdgeValences(const Mesh<Element>& mesh);


/** 
 * @brief Get the triangle valences of the mesh
 * @return A map containing the valence of each triangle
 */
inline std::unordered_map<Triangle, size_t, TriangleHash> getTriangleValences(const Mesh<Tetra>& mesh);


 /** 
 * @brief Get the boundary edges of the mesh
 * @return A vector containing the boundary edges
 */
template <typename Element>
std::vector<Edge> getBoundaryEdges(const Mesh<Element>& mesh);


/** 
 * @brief Get the boundary triangles of the mesh
 * @return A vector containing the boundary triangles
 */
inline std::vector<Triangle> getBoundaryTriangles(const Mesh<Tetra>& mesh);


 /**
 * @brief Count the number of unique edges in the mesh by iterating through all triangles and adding their edges to an unordered_set
 * 
 * @return number of unique edges in the mesh 
 */
template <typename Element>
size_t countUniqueEdges(const Mesh<Element>& mesh);


/** 
 * @brief Count the number of unique triangles in the mesh by iterating through all tetrahedra and adding their triangles to an unordered_set
 * 
 * @return number of unique triangles in the mesh 
 */
template <typename Element>
size_t countUniqueTriangles(const Mesh<Element>& mesh);






// Display analysis

/**
 * @brief  Analyze the mesh by printing out the number of vertices, triangles, and unique edges. Optionally, it could also calculate and print the aspect ratio of each triangle for quality analysis.
 * 
 */
template <typename Element>
void analyzeMesh(Mesh<Element>& mesh);

} // namespace Enmesh

#include "../../src/mesh/mesh_analysis/mesh_analysis.tpp" 
#include "../../src/mesh/mesh_analysis/mesh_analysis_aspectRatio.tpp"
#include "../../src/mesh/mesh_analysis/mesh_analysis_count.tpp"
#include "../../src/mesh/mesh_analysis/mesh_analysis_boundaries.tpp"


#endif  