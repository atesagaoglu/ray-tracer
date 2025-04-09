#ifndef RAYTRACER_INTENSITY_HPP
#define RAYTRACER_INTENSITY_HPP

namespace raytracer {

class Intensity {
public:
    Intensity();
    Intensity(double x, double y, double z);

    double getX() const;
    double getY() const;
    double getZ() const;

    Intensity& setX(double val);
    Intensity& setY(double val);
    Intensity& setZ(double val);

private:
    double x, y, z;
};

} // namespace raytracer

#endif
