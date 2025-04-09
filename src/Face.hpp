#ifndef RAYTRACER_FACE_HPP
#define RAYTRACER_FACE_HPP

#include <cstdint>

namespace raytracer {

typedef struct {
    uint32_t x, y, z;
} TriIndex;

class Face {

public:
    Face();
    Face(TriIndex vertex, TriIndex texture, TriIndex normal);

    TriIndex getVertex() const;
    TriIndex getTexture() const;
    TriIndex getNormal() const;

    Face& setVertex(uint32_t x, uint32_t y, uint32_t z);
    Face& setTexture(uint32_t x, uint32_t y, uint32_t z);
    Face& setNormal(uint32_t x, uint32_t y, uint32_t z);

private:
    TriIndex vertex;
    TriIndex texture;
    TriIndex normal;
};

} // namespace raytracer

#endif
