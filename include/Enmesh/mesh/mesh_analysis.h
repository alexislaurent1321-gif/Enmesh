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
inline std::unordered_map<Edge, size_t, EdgeHash> getElementsValences(const Mesh<Triangle>& mesh);


 /**
 * @brief Get the Edge Valences object  
 * 
 * @return std::unordered_map<Edge, size_t, EdgeHash> 
 */
inline std::unordered_map<Edge, size_t, EdgeHash> getElementsValences(const Mesh<Quad>& mesh);


/** 
 * @brief Get the triangle valences of the mesh
 * @return A map containing the valence of each triangle
 */
inline std::unordered_map<Triangle, size_t, TriangleHash> getElementsValences(const Mesh<Tetra>& mesh);


/** 
 * @brief Get the triangle valences of the mesh
 * @return A map containing the valence of each triangle
 */
inline std::unordered_map<Quad, size_t, QuadHash> getElementsValences(const Mesh<Hexa>& mesh);





// Boundary analysis

 /** 
 * @brief Get the boundary edges of the mesh
 * @return A vector containing the boundary edges
 */
template <typename Element>
std::vector<Edge> getBoundaries(const Mesh<Element>& mesh);


 /**
 * @brief Count the number of unique edges in the 2D mesh (unique faces in the 3D mesh) by iterating through all elements and adding their borders to an unordered_set
 * 
 * @return number of unique edges in the mesh 
 */
template <typename Element>
size_t countAllBorders(const Mesh<Element>& mesh);




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
#include "../../src/mesh/mesh_analysis/mesh_analysis_valences.tpp"


#endif  