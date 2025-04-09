#include <iostream>

#include "Vector.hpp"

int main(void) {

    raytracer::Vector v1(2, 3, 4);
    raytracer::Vector v2(1, -1, 5);

    raytracer::Vector v3 = v1 - v2;

    v3.print();
}
