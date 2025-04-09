#include "Vector.hpp"
#include <cmath>
#include <iostream>

namespace raytracer {

Vector::Vector() : x(0), y(0), z(0) {}

Vector::Vector(double u, double v, double w) : x(u), y(v), z(w) {}

double Vector::getX() const { return x; }

double Vector::getY() const { return y; }

double Vector::getZ() const { return z; }

Vector& Vector::setX(double val) {
    x = val;
    return *this;
}

Vector& Vector::setY(double val) {
    y = val;
    return *this;
}

Vector& Vector::setZ(double val) {
    z = val;
    return *this;
}

void Vector::print() {
    std::cout << "U: " << static_cast<double>(x) << std::endl;
    std::cout << "V: " << static_cast<double>(y) << std::endl;
    std::cout << "W: " << static_cast<double>(z) << std::endl;
}

Vector Vector::cross(Vector& oth) {
    return Vector(y * oth.z - z * oth.y,
                  z * oth.x - x * oth.z,
                  x * oth.y - y * oth.x);
}

Vector Vector::normalize() const {
    double len = sqrt(x * x + y * y + z * z);
    if (len == 0)
        return *this;
    return Vector(x / len, y / len, z / len);
}

double Vector::dot(Vector& oth) { return x * oth.x + y * oth.y + z * oth.z; }

} // namespace raytracer
