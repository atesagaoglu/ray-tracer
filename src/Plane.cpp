#include "Plane.hpp"

namespace raytracer {

Plane::Plane() : t(0), b(0), r(0), l(0) {}

Plane::Plane(double t, int32_t b, int32_t r, int32_t l)
    : t(t), b(b), r(r), l(l) {}

double Plane::getT() const { return t; }

double Plane::getB() const { return b; }

double Plane::getR() const { return r; }

double Plane::getL() const { return l; }

Plane& Plane::setT(double val) {
    t = val;
    return *this;
}

Plane& Plane::setB(double val) {
    b = val;
    return *this;
}

Plane& Plane::setR(double val) {
    r = val;
    return *this;
}

Plane& Plane::setL(double val) {
    l = val;
    return *this;
}

} // namespace raytracer
