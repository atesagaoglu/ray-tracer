#include "Color.hpp"
#include <iostream>

namespace raytracer {

Color::Color() : r(0), g(0), b(0) {}

Color::Color(uint8_t r, int8_t g, int8_t b) : r(r), g(g), b(b) {}

uint8_t Color::getR() const { return r; }

uint8_t Color::getG() const { return g; }

uint8_t Color::getB() const { return b; }

Color& Color::setR(uint8_t val) {
    r = val;
    return *this;
}

Color& Color::setG(uint8_t val) {
    g = val;
    return *this;
}

Color& Color::setB(uint8_t val) {
    b = val;
    return *this;
}

void Color::print() {
    // Cast to int to prevent printing as char
    std::cout << "R: " << static_cast<int32_t>(r) << std::endl;
    std::cout << "G: " << static_cast<int32_t>(g) << std::endl;
    std::cout << "B: " << static_cast<int32_t>(b) << std::endl;
}

} // namespace raytracer
