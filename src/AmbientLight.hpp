#ifndef RAYTRACER_AMBIENT_LIGHT_HPP
#define RAYTRACER_AMBIENT_LIGHT_HPP

#include "Light.hpp"

namespace raytracer {

class AmbientLight : public Light {
public:
    AmbientLight();
    AmbientLight(Vector intensity);

    Vector getIntensity() const override;
    Vector getDirectionToLight(Vector point) const override;
    bool isAmbient() const override;
};

} // namespace raytracer

#endif
