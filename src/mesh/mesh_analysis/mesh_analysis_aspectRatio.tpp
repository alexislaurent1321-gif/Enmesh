#include <numeric>
#include <algorithm>

#include "mesh/mesh_analysis.h"


// Quality analysis

template <>
inline float calculateAspectRatio(const Mesh<Triangle>& mesh, const Triangle& element)  {
    // triangle lengths
    float a = mesh.vertices[element.v[0]].distance(mesh.vertices[element.v[1]]);
    float b = mesh.vertices[element.v[1]].distance(mesh.vertices[element.v[2]]);
    float c = mesh.vertices[element.v[2]].distance(mesh.vertices[element.v[0]]);

    // aspect ratio formula: (abc) / ((b+c-a)(c+a-b)(a+b-c))
    float num = a * b * c;
    float denom = (b+c - a) * (c+a - b) * (a+b - c);
    return num / denom;
}


template <>
inline float calculateAspectRatio(const Mesh<Tetrahedron>& mesh, const Tetrahedron& element)  {

    Point A = mesh.vertices[element.v[0]];
    Point B = mesh.vertices[element.v[1]];
    Point C = mesh.vertices[element.v[2]];
    Point D = mesh.vertices[element.v[3]];

    // triangle lengths
    float ab = A.distance(B);
    float ac = A.distance(C);
    float ad = A.distance(D);
    float bc = B.distance(C);
    float cd = C.distance(D);
    float da = D.distance(A);

    // aspect ratio formula
    float hMax = std::max({ab, ac, ad, bc, cd, da});
    float alpha = (B - A).dot((C - A).cross(D - A));

    Point normal_abc = (B - A).cross(C - A);
    Point normal_acd = (C - A).cross(D - A);
    Point normal_adb = (D - A).cross(B - A);
    Point normal_bcd = (C - B).cross(D - B);

    float r = std::abs(alpha) / (normal_abc.length() + normal_acd.length() + normal_adb.length() + normal_bcd.length());
    float quality = hMax / (2 * std::sqrt(6) * r);
    return quality;
}


template <typename T>
void calculateAspectRatios(Mesh<T>& mesh) {
    mesh.ratios.clear();

    // Calculate aspect ratio for each element and store in the ratios vector
    for (const auto& t : mesh.elements) {
        mesh.ratios.push_back(calculateAspectRatio<T>(mesh, t));
    }
}