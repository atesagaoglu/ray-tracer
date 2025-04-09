#include "Intensity.hpp"

namespace raytracer {

Intensity::Intensity() : x(0.0), y(0.0), z(0.0) {}
Intensity::Intensity(double x, double y, double z) : x(x), y(y), z(z) {}

double Intensity::getX() const { return x; }

double Intensity::getY() const { return y; }

double Intensity::getZ() const { return z; }

Intensity& Intensity::setX(double val) {
    if (val < 0.0)
        x = 0;
    else if (val > 1.0)
        x = 1;
    else
        x = val;
    return *this;
}

Intensity& Intensity::setY(double val) {
    if (val < 0.0)
        y = 0;
    else if (val > 1.0)
        y = 1;
    else
        y = val;
    return *this;
}
Intensity& Intensity::setZ(double val) {
    if (val < 0.0)
        z = 0;
    else if (val > 1.0)
        z = 1;
    else
        z = val;
    return *this;
}

} // namespace raytracer
