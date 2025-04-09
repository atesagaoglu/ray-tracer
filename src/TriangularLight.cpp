#include "TriangularLight.hpp"

namespace raytracer {

TriangularLight::TriangularLight() : Light(), v0(), v1(), v2() {}
TriangularLight::TriangularLight(Vector intensity,
                                 Vector v0,
                                 Vector v1,
                                 Vector v2)
    : Light(intensity), v0(v0), v1(v1), v2(v2) {}

Vector TriangularLight::getIntensity() const { return this->intensity; }

Vector TriangularLight::getDirectionToLight(Vector point) const {
    // TODO: Learn how this should be done.
    return v0;
}

bool TriangularLight::isAmbient() const { return false; }
} // namespace raytracer
