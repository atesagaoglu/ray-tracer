#ifndef RAYTRACER_MATH_HPP
#define RAYTRACER_MATH_HPP

#include <vector>

#include "Camera.hpp"
#include "Color.hpp"
#include "Light.hpp"
#include "Object.hpp"
#include "Scene.hpp"
#include "Vector.hpp"

namespace raytracer {

bool intersect(Vector& origin,
               Vector& direction,
               Vector& v0,
               Vector& v1,
               Vector& v2,
               double& tOut,
               Vector& hitPointOut);

Color computePhongLighting(raytracer::Vector hitPoint,
                           raytracer::Vector normal,
                           raytracer::Vector viewDir,
                           std::vector<raytracer::Light*> lights,
                           raytracer::Vector ambientColor,
                           raytracer::Vector diffuseColor,
                           raytracer::Vector specularColor,
                           double phongExponent);

Color raytraceRay(raytracer::Vector origin,
                  raytracer::Vector dir,
                  raytracer::Camera camera,
                  std::vector<raytracer::Object> objects,
                  raytracer::Scene scene,
                  int depth);

} // namespace raytracer

#endif
