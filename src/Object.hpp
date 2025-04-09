#ifndef RAYTRACER_OBJECT_HPP
#define RAYTRACER_OBJECT_HPP

#include "Face.hpp"
#include <cstdint>
#include <vector>

namespace raytracer {

class Object {

public:
    Object();
    Object(uint32_t id, uint32_t materialId, std::vector<Face> faces);

    uint32_t getId() const;
    uint32_t getMaterialId() const;
    std::vector<Face> getFaces() const;

    Object& setId(uint32_t val);
    Object& setMaterialId(uint32_t val);
    Object& setFaces(std::vector<Face> val);

    Object& addFace(Face val);

private:
    uint32_t id;
    uint32_t materialId;
    std::vector<Face> faces;
};

} // namespace raytracer

#endif
