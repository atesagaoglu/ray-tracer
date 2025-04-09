#include "Math.hpp"
#include <cmath>
#include <iostream>

namespace raytracer {

bool intersect(Vector& origin,
               Vector& direction,
               Vector& v0,
               Vector& v1,
               Vector& v2,
               double& tOut,
               Vector& hitPointOut) {
    const double eps = 1e-8;
    Vector e1 = v1 - v0;
    Vector e2 = v2 - v0;
    Vector normal = e1.cross(e2).normalize();

    double denom = normal.dot(direction);
    if (fabs(denom) < eps)
        return false; // Ray is parallel to triangle

    double t = (v0 - origin).dot(normal) / denom;
    if (t < eps)
        return false; // Triangle is behind the ray

    Vector P = origin + direction * t;

    Vector C;

    Vector edge0 = v1 - v0;
    Vector vp0 = P - v0;
    C = edge0.cross(vp0);
    if (normal.dot(C) < 0)
        return false;

    Vector edge1 = v2 - v1;
    Vector vp1 = P - v1;
    C = edge1.cross(vp1);
    if (normal.dot(C) < 0)
        return false;

    Vector edge2 = v0 - v2;
    Vector vp2 = P - v2;
    C = edge2.cross(vp2);
    if (normal.dot(C) < 0)
        return false;

    // All good, intersection confirmed
    tOut = t;
    hitPointOut = P;
    return true;
}

raytracer::Color computePhongLighting(raytracer::Vector hitPoint,
                                      raytracer::Vector normal,
                                      raytracer::Vector viewDir,
                                      std::vector<raytracer::Light*> lights,
                                      raytracer::Vector ambientColor,
                                      raytracer::Vector diffuseColor,
                                      raytracer::Vector specularColor,
                                      double phongExponent) {
    Vector colorAccum(0, 0, 0);

    for (const Light* light : lights) {
        Vector intensity = light->getIntensity();

        if (light->isAmbient()) {
            Vector ambient = ambientColor * (intensity / 255.0);
            colorAccum = ambient + colorAccum;
        } else {
            Vector L = light->getDirectionToLight(hitPoint).normalize();
            Vector N = normal.normalize();
            Vector V = viewDir.normalize();
            Vector R = (2.0 * N.dot(L) * N - L).normalize();

            // Diffuse
            double diff = std::max(0.0, N.dot(L));
            Vector diffuse = diffuseColor * (intensity * diff / 255.0);

            // Specular
            double spec = std::pow(std::max(0.0, R.dot(V)), phongExponent);
            Vector specular = specularColor * (intensity * spec / 255.0);

            colorAccum = diffuse + specular + colorAccum;
        }
    }

    std::cout << colorAccum.getX() * 255 << std::endl;
    std::cout << colorAccum.getY() * 255 << std::endl;
    std::cout << colorAccum.getZ() * 255 << std::endl;

    return Color(colorAccum.getX() * 255,
                 colorAccum.getY() * 255,
                 colorAccum.getZ() * 255);
}

raytracer::Color raytraceRay(raytracer::Vector origin,
                             raytracer::Vector dir,
                             raytracer::Camera camera,
                             std::vector<raytracer::Object> objects,
                             raytracer::Scene scene,
                             int depth) {
    if (depth > scene.getMaxDepth())
        return raytracer::Color(0, 0, 0);

    double closestHit = 1e9;
    raytracer::Vector closestHitPoint, finalV0, finalV1, finalV2;
    raytracer::Material hitMaterial;
    raytracer::Vector normal;
    bool hit = false;

    const std::vector<raytracer::Material>& materials = scene.getMaterials();

    for (const auto& obj : objects) {
        const std::vector<raytracer::Face>& faces = obj.getFaces();
        int materialID = obj.getMaterialId();

        for (const auto& face : faces) {
            raytracer::TriIndex tri = face.getVertex();

            raytracer::Vector v0 = scene.getVertexData()[tri.x - 1];
            raytracer::Vector v1 = scene.getVertexData()[tri.y - 1];
            raytracer::Vector v2 = scene.getVertexData()[tri.z - 1];

            double tHit;
            raytracer::Vector hitPoint;

            if (raytracer::intersect(origin, dir, v0, v1, v2, tHit, hitPoint)) {
                if (tHit < closestHit) {
                    closestHit = tHit;
                    hit = true;
                    closestHitPoint = hitPoint;
                    finalV0 = v0;
                    finalV1 = v1;
                    finalV2 = v2;

                    for (const auto& mat : materials) {
                        if (mat.getId() == materialID) {
                            hitMaterial = mat;
                            break;
                        }
                    }

                    Vector diff = v2 - v0;
                    normal = (v1 - v0).cross(diff).normalize();
                }
            }
        }
    }

    Vector oppositeDir = dir * -1;

    if (hit) {
        raytracer::Color localColor =
            raytracer::computePhongLighting(closestHitPoint,
                                            normal,
                                            oppositeDir,
                                            scene.getLights(),
                                            hitMaterial.getAmbient(),
                                            hitMaterial.getDiffuse(),
                                            hitMaterial.getSpecular(),
                                            hitMaterial.getPhongeExp());

        // Recursive reflection
        raytracer::Vector mirror = hitMaterial.getMirrorReflectance();
        raytracer::Color reflectedColor(0, 0, 0);

        if (mirror.getX() > 0 || mirror.getY() > 0 || mirror.getZ() > 0) {
            raytracer::Vector reflectDir = dir - normal * 2.0 * dir.dot(normal);
            reflectDir = reflectDir.normalize();

            reflectedColor = raytraceRay(closestHitPoint + reflectDir * 1e-4,
                                         reflectDir,
                                         camera,
                                         objects,
                                         scene,
                                         depth + 1);
        }

        return localColor * (raytracer::Vector(1.0, 1.0, 1.0) - mirror) +
               reflectedColor * mirror;
    }

    return raytracer::Color(0, 0, 0); // background
}

} // namespace raytracer
