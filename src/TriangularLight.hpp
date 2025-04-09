#ifndef RAYTRACER_TRIANGULAR_LIGHT_HPP
#define RAYTRACER_TRIANGULAR_LIGHT_HPP

#include "Light.hpp"

namespace raytracer {

class TriangularLight : public Light {
public:
    TriangularLight();
    TriangularLight(Vector intensity, Vector v0, Vector v1, Vector v2);

    Vector getIntensity() const override;
    Vector getDirectionToLight(Vector point) const override;
    bool isAmbient() const override;

private:
    Vector v0;
    Vector v1;
    Vector v2;
};

} // namespace raytracer

#endif
