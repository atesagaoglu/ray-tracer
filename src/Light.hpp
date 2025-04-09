#ifndef RAYTRACER_LIGHT_HPP
#define RAYTRACER_LIGHT_HPP

#include <cstdint>

#include "Vector.hpp"

namespace raytracer {

class Light {
public:
    Light();
    Light(Vector intensity);

    virtual ~Light() = default;
    virtual Vector getIntensity() const = 0;
    virtual Vector getDirectionToLight(Vector point) const = 0;
    virtual bool isAmbient() const = 0;

protected:
    Vector intensity;
};

} // namespace raytracer

#endif
