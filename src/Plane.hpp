#ifndef RAYTRACER_PLANE_HPP
#define RAYTRACER_PLANE_HPP

#include <cstdint>

namespace raytracer {

class Plane {

public:
    Plane();
    Plane(double l, int32_t r, int32_t t, int32_t b);

    double getT() const;
    double getB() const;
    double getR() const;
    double getL() const;

    Plane& setT(double val);
    Plane& setB(double val);
    Plane& setR(double val);
    Plane& setL(double val);

private:
    double t, b, r, l;
};

} // namespace raytracer

#endif
