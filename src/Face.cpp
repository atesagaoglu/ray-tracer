#include "Face.hpp"

namespace raytracer {

Face::Face()
    : vertex(TriIndex{0, 0, 0}), texture(TriIndex{0, 0, 0}),
      normal(TriIndex{0, 0, 0}) {}

Face::Face(TriIndex vertex, TriIndex texture, TriIndex normal)
    : vertex(vertex), texture(texture), normal(normal) {}

TriIndex Face::getVertex() const { return vertex; }
TriIndex Face::getTexture() const { return texture; }
TriIndex Face::getNormal() const { return normal; }

Face& Face::setVertex(uint32_t x, uint32_t y, uint32_t z) {
    vertex.x = x;
    vertex.y = y;
    vertex.z = z;
    return *this;
}

Face& Face::setTexture(uint32_t x, uint32_t y, uint32_t z) {
    texture.x = x;
    texture.y = y;
    texture.z = z;
    return *this;
}

Face& Face::setNormal(uint32_t x, uint32_t y, uint32_t z) {
    normal.x = x;
    normal.y = y;
    normal.z = z;
    return *this;
}

} // namespace raytracer
