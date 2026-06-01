#include <numeric>
#include <algorithm>

#include "mesh/mesh_analysis.h"

namespace Enmesh {

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
inline float calculateAspectRatio(const Mesh<Quad>& mesh, const Quad& element)  {
    // midpoints of the diagonals
    Point mAB = { (mesh.vertices[element.v[0]].x + mesh.vertices[element.v[1]].x) / 2, (mesh.vertices[element.v[0]].y + mesh.vertices[element.v[1]].y) / 2 };
    Point mCD = { (mesh.vertices[element.v[2]].x + mesh.vertices[element.v[3]].x) / 2, (mesh.vertices[element.v[2]].y + mesh.vertices[element.v[3]].y) / 2 };
    Point mBC = { (mesh.vertices[element.v[1]].x + mesh.vertices[element.v[2]].x) / 2, (mesh.vertices[element.v[1]].y + mesh.vertices[element.v[2]].y) / 2 };
    Point mDA = { (mesh.vertices[element.v[3]].x + mesh.vertices[element.v[0]].x) / 2, (mesh.vertices[element.v[3]].y + mesh.vertices[element.v[0]].y) / 2 };

    // lengths of the diagonals
    float L1 = mAB.distance(mCD);
    float L2 = mBC.distance(mDA);

    if (L1 == 0 || L2 == 0) return 0; // Avoid division by zero for degenerate quads

    // aspect ratio formula
    return std::max(L1, L2) / std::min(L1, L2);
}


template <>
inline float calculateAspectRatio(const Mesh<Tetra>& mesh, const Tetra& element)  {

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


template <>
inline float calculateAspectRatio(const Mesh<Hexa>& mesh, const Hexa& element)  {

    Point m1 = {(mesh.vertices[element.v[0]].x + mesh.vertices[element.v[1]].x + mesh.vertices[element.v[2]].x + mesh.vertices[element.v[3]].x) / 4,
                (mesh.vertices[element.v[0]].y + mesh.vertices[element.v[1]].y + mesh.vertices[element.v[2]].y + mesh.vertices[element.v[3]].y) / 4,
                (mesh.vertices[element.v[0]].z + mesh.vertices[element.v[1]].z + mesh.vertices[element.v[2]].z + mesh.vertices[element.v[3]].z) / 4};
    Point m2 = {(mesh.vertices[element.v[4]].x + mesh.vertices[element.v[5]].x + mesh.vertices[element.v[6]].x + mesh.vertices[element.v[7]].x) / 4,
                (mesh.vertices[element.v[4]].y + mesh.vertices[element.v[5]].y + mesh.vertices[element.v[6]].y + mesh.vertices[element.v[7]].y) / 4,
                (mesh.vertices[element.v[4]].z + mesh.vertices[element.v[5]].z + mesh.vertices[element.v[6]].z + mesh.vertices[element.v[7]].z) / 4};
    Point m3 = {(mesh.vertices[element.v[0]].x + mesh.vertices[element.v[1]].x + mesh.vertices[element.v[5]].x + mesh.vertices[element.v[4]].x) / 4,
                (mesh.vertices[element.v[0]].y + mesh.vertices[element.v[1]].y + mesh.vertices[element.v[5]].y + mesh.vertices[element.v[4]].y) / 4,
                (mesh.vertices[element.v[0]].z + mesh.vertices[element.v[1]].z + mesh.vertices[element.v[5]].z + mesh.vertices[element.v[4]].z) / 4};
    Point m4 = {(mesh.vertices[element.v[2]].x + mesh.vertices[element.v[3]].x + mesh.vertices[element.v[7]].x + mesh.vertices[element.v[6]].x) / 4,
                (mesh.vertices[element.v[2]].y + mesh.vertices[element.v[3]].y + mesh.vertices[element.v[7]].y + mesh.vertices[element.v[6]].y) / 4,
                (mesh.vertices[element.v[2]].z + mesh.vertices[element.v[3]].z + mesh.vertices[element.v[7]].z + mesh.vertices[element.v[6]].z) / 4};
    Point m5 = {(mesh.vertices[element.v[0]].x + mesh.vertices[element.v[2]].x + mesh.vertices[element.v[4]].x + mesh.vertices[element.v[6]].x) / 4,
                (mesh.vertices[element.v[0]].y + mesh.vertices[element.v[2]].y + mesh.vertices[element.v[4]].y + mesh.vertices[element.v[6]].y) / 4,
                (mesh.vertices[element.v[0]].z + mesh.vertices[element.v[2]].z + mesh.vertices[element.v[4]].z + mesh.vertices[element.v[6]].z) / 4};
    Point m6 = {(mesh.vertices[element.v[1]].x + mesh.vertices[element.v[3]].x + mesh.vertices[element.v[5]].x + mesh.vertices[element.v[7]].x) / 4,
                (mesh.vertices[element.v[1]].y + mesh.vertices[element.v[3]].y + mesh.vertices[element.v[5]].y + mesh.vertices[element.v[7]].y) / 4,
                (mesh.vertices[element.v[1]].z + mesh.vertices[element.v[3]].z + mesh.vertices[element.v[5]].z + mesh.vertices[element.v[7]].z) / 4};

    float h1 = m1.distance(m2);
    float h2 = m3.distance(m4);
    float h3 = m5.distance(m6);

    return std::max({h1, h2, h3}) / std::min({h1, h2, h3}); 
}


template <typename Element>
void calculateAspectRatios(Mesh<Element>& mesh) {
    mesh.ratios.clear();

    // Calculate aspect ratio for each element and store in the ratios vector
    for (const auto& element : mesh.elements) {
        mesh.ratios.push_back(calculateAspectRatio<Element>(mesh, element));
    }
}

} // namespace Enmesh