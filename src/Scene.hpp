#ifndef RAYTRACER_SCENE_HPP
#define RAYTRACER_SCENE_HPP

#include "Camera.hpp"
#include "Color.hpp"
#include "Light.hpp"
#include "Material.hpp"
#include "Object.hpp"

#include <vector>

namespace raytracer {

class Scene {

public:
    Scene();
    ~Scene();

    int8_t getMaxDepth() const;
    Color getBackgroundColor() const;
    Camera getCamera() const;
    std::vector<Light*> getLights() const;
    std::vector<Material> getMaterials() const;
    std::vector<Vector> getVertexData() const;
    std::vector<Vector> getNormalData() const;
    std::vector<Object> getObjects() const;

    Scene& setMaxDepth(int8_t val);
    Scene& setBackgroundColor(Color val);
    Scene& setCamera(Camera val);
    Scene& setLights(std::vector<Light*> val);
    Scene& setMaterials(std::vector<Material> val);
    Scene& setVertexData(std::vector<Vector> val);
    Scene& setNormalData(std::vector<Vector> val);
    Scene& setObjects(std::vector<Object> val);

    Scene& addLight(Light* val);
    Scene& addMaterial(Material val);
    Scene& addVertexData(Vector val);
    Scene& addNormalData(Vector val);
    Scene& addObject(Object val);

private:
    int8_t maxDepth;
    Color backgroundColor;
    Camera camera;
    std::vector<Light*> lights;
    std::vector<Material> materials;
    std::vector<Vector> vertexData;
    std::vector<Vector> normalData;
    std::vector<Object> objects;
};

} // namespace raytracer

#endif
