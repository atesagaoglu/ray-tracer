#include "AmbientLight.hpp"

namespace raytracer {

AmbientLight::AmbientLight() : Light() {}
AmbientLight::AmbientLight(Vector intensity) : Light(intensity) {}

Vector AmbientLight::getIntensity() const { return this->intensity; }

Vector AmbientLight::getDirectionToLight(Vector point) const {
    (void)point;
    return Vector(0, 0, 0);
}

bool AmbientLight::isAmbient() const { return true; }

} // namespace raytracer
