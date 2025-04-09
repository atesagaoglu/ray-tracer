#include "Scene.hpp"

namespace raytracer {

Scene::Scene() : maxDepth(0), backgroundColor(), camera(), lights() {}

Scene::~Scene() {
    for (uint64_t i = 0; i < lights.size(); i++) {
        delete lights[i];
    }
}

int8_t Scene::getMaxDepth() const { return maxDepth; }

Color Scene::getBackgroundColor() const { return backgroundColor; }

Camera Scene::getCamera() const { return camera; }

std::vector<Light*> Scene::getLights() const { return lights; }

std::vector<Material> Scene::getMaterials() const { return materials; }

std::vector<Vector> Scene::getVertexData() const { return vertexData; }

std::vector<Vector> Scene::getNormalData() const { return normalData; }

std::vector<Object> Scene::getObjects() const { return objects; }

Scene& Scene::setMaxDepth(int8_t val) {
    maxDepth = val;
    return *this;
}

Scene& Scene::setBackgroundColor(Color val) {
    backgroundColor = val;
    return *this;
}

Scene& Scene::setCamera(Camera val) {
    camera = val;
    return *this;
}

Scene& Scene::setLights(std::vector<Light*> val) {
    lights = val;
    return *this;
}

Scene& Scene::setMaterials(std::vector<Material> val) {
    materials = val;
    return *this;
}

Scene& Scene::setVertexData(std::vector<Vector> val) {
    vertexData = val;
    return *this;
}

Scene& Scene::setNormalData(std::vector<Vector> val) {
    normalData = val;
    return *this;
}

Scene& Scene::setObjects(std::vector<Object> val) {
    objects = val;
    return *this;
}

Scene& Scene::addLight(Light* val) {
    lights.push_back(val);
    return *this;
}

Scene& Scene::addMaterial(Material val) {
    materials.push_back(val);
    return *this;
}

Scene& Scene::addVertexData(Vector val) {
    vertexData.push_back(val);
    return *this;
}

Scene& Scene::addNormalData(Vector val) {
    normalData.push_back(val);
    return *this;
}

Scene& Scene::addObject(Object val) {
    objects.push_back(val);
    return *this;
}

} // namespace raytracer
