#include "PointLight.hpp"

namespace raytracer {

PointLight::PointLight() : Light() {}

PointLight::PointLight(Vector intensity, Vector position)
    : Light(intensity), position(position) {}

Vector PointLight::getIntensity() const { return this->intensity; }

Vector PointLight::getDirectionToLight(Vector point) const {
    return (position - point);
}

bool PointLight::isAmbient() const { return false; }

} // namespace raytracer
