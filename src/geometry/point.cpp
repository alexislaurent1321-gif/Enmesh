#include "geometry/point.h"

namespace Enmesh {

float Point::length() const { 
    return std::sqrt(x*x + y*y + z*z); 
}


float Point::distance(const Point& other) const {
    return (*this - other).length();
}


Point Point::operator-(const Point& other) const{
    return Point(x - other.x, y - other.y, z - other.z);
}

Point Point::operator+(const Point& other) const{
    return Point(x + other.x, y + other.y, z + other.z);
}

Point Point::operator*(float scalar) const {
    return Point(x * scalar, y * scalar, z * scalar);
}

Point Point::operator/(float scalar) const {
    return Point(x / scalar, y / scalar, z / scalar);
}

bool Point::operator==(const Point& other) const {
    return std::abs(x - other.x) < 1e-9 && std::abs(y - other.y) < 1e-9 && std::abs(z - other.z) < 1e-9;
}

void Point::operator+=(const Point& other) {
    x += other.x;
    y += other.y;
    z += other.z;
}

void Point::operator/=(float scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
}

void Point::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
}

float Point::dot(const Point& other) const {
    return x * other.x + y * other.y + z * other.z;
}

Point Point::cross(const Point& other) const {
    return Point(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}


std::ostream& operator<<(std::ostream& os, const Point& point) {
    os << "(" << point.x << ", " << point.y << ", " << point.z << ")";
    return os;
}

} // namespace Enmesh