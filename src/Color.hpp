#ifndef RAYTRACER_COLOR_HPP
#define RAYTRACER_COLOR_HPP

#include <cstdint>

#include "Vector.hpp"

namespace raytracer {

class Color {

public:
    Color();
    Color(uint8_t r, int8_t g, int8_t b);

    uint8_t getR() const;
    uint8_t getG() const;
    uint8_t getB() const;

    Color& setR(uint8_t val);
    Color& setG(uint8_t val);
    Color& setB(uint8_t val);

    void print();

    raytracer::Color operator*(const Vector& vec) const {
        return raytracer::Color(r * vec.getX(), g * vec.getY(), b * vec.getZ());
    }

    raytracer::Color operator+(const raytracer::Color& other) const {
        return raytracer::Color(r + other.r, g + other.g, b + other.b);
    }

private:
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

} // namespace raytracer

#endif
