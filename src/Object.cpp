#include "Object.hpp"

namespace raytracer {

Object::Object() : id(0), materialId(0), faces(std::vector<Face>()) {}

Object::Object(uint32_t id, uint32_t materialId, std::vector<Face> faces)
    : id(id), materialId(materialId), faces(faces) {}

uint32_t Object::getId() const { return id; }

uint32_t Object::getMaterialId() const { return materialId; }

std::vector<Face> Object::getFaces() const { return faces; }

Object& Object::setId(uint32_t val) {
    id = val;
    return *this;
}
Object& Object::setMaterialId(uint32_t val) {
    materialId = val;
    return *this;
}
Object& Object::setFaces(std::vector<Face> val) {
    faces = val;
    return *this;
}

Object& Object::addFace(Face val) {
    faces.push_back(val);
    return *this;
}

} // namespace raytracer
