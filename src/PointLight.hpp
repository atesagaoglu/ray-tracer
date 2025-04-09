#ifndef RAYTRACER_POINTLIGHT_HPP
#define RAYTRACER_POINTLIGHT_HPP

#include "Light.hpp"

namespace raytracer {

class PointLight : public Light {

public:
    PointLight();
    PointLight(Vector intensity, Vector position);

    Vector getIntensity() const override;
    Vector getDirectionToLight(Vector point) const override;
    bool isAmbient() const override;

private:
    Vector position;
};

} // namespace raytracer

#endif
