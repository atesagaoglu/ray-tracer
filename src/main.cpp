#include <fstream>
#include <iostream>

#include "Camera.hpp"
#include "Math.hpp"
#include "Object.hpp"
#include "Parser.hpp"
#include "Scene.hpp"
#include "Vector.hpp"

int main(int argc, char** argv) {

    if (argc != 2) {
        std::cerr << "No filename given." << std::endl;
        exit(EXIT_FAILURE);
    }

    raytracer::Scene scene = raytracer::parse(argv[1]);
    raytracer::Camera camera = scene.getCamera();
    raytracer::Vector cameraPos = camera.getPosition();

    std::vector<raytracer::Object> objects = scene.getObjects();

    int32_t width = scene.getCamera().getResX();
    int32_t height = scene.getCamera().getResY();

    raytracer::Vector w = camera.getGaze().normalize();        // forward
    raytracer::Vector u = camera.getUp().cross(w).normalize(); // right
    raytracer::Vector v = w.cross(u);

    double rl = scene.getCamera().getNearPlane().getL();
    double rr = scene.getCamera().getNearPlane().getR();
    double rt = scene.getCamera().getNearPlane().getT();
    double rb = scene.getCamera().getNearPlane().getB();

    double nearDist = scene.getCamera().getNearDistance();

    std::ofstream ofs("output.ppm");
    ofs << "P3\n" << width << " " << height << "\n255\n";

    // each pixel across y
    for (int y = 0; y < height; ++y) {

        // each pixel across x
        for (int x = 0; x < width; ++x) {
            double px = rl + (rr - rl) * (x + 0.5) / width;
            double py = rb + (rt - rb) * (y + 0.5) / height;

            raytracer::Vector pixelPos =
                camera.getPosition() + w * nearDist + u * px + v * py;
            raytracer::Vector dir = (pixelPos - cameraPos).normalize();

            double closestHit = 1e9;
            bool hit = false;

            raytracer::Vector closestHitPoint;
            raytracer::Vector finalV0, finalV1, finalV2;
            raytracer::Material hitMaterial;

            std::vector<raytracer::Material> materials = scene.getMaterials();

            for (uint64_t i = 0; i < objects.size(); i++) {
                std::vector<raytracer::Face> faces = objects[i].getFaces();
                int materialID = objects[i].getMaterialId();

                for (uint64_t j = 0; j < faces.size(); j++) {
                    raytracer::TriIndex tri = faces[j].getVertex();

                    // 1-indexed
                    raytracer::Vector v0 = scene.getVertexData()[tri.x - 1];
                    raytracer::Vector v1 = scene.getVertexData()[tri.y - 1];
                    raytracer::Vector v2 = scene.getVertexData()[tri.z - 1];

                    double tHit;
                    raytracer::Vector hitPoint;
                    if (raytracer::intersect(cameraPos,
                                             dir,
                                             v0,
                                             v1,
                                             v2,
                                             tHit,
                                             hitPoint)) {
                        if (tHit < closestHit) {
                            closestHit = tHit;
                            hit = true;
                            closestHitPoint = hitPoint;
                            finalV0 = v0;
                            finalV1 = v1;
                            finalV2 = v2;

                            for (uint64_t i = 0; i < materials.size(); i++) {
                                if (materials[i].getId() == materialID) {
                                    hitMaterial = materials[i];
                                }
                            }
                        }
                    }
                }
            }

            if (hit) {
                raytracer::Vector diff = finalV2 - finalV0;
                raytracer::Vector dist = cameraPos - closestHitPoint;
                raytracer::Vector normal =
                    (finalV1 - finalV0).cross(diff).normalize();
                raytracer::Color color =
                    raytracer::computePhongLighting(closestHitPoint,
                                                    normal,
                                                    dist,
                                                    scene.getLights(),
                                                    hitMaterial.getAmbient(),
                                                    hitMaterial.getDiffuse(),
                                                    hitMaterial.getSpecular(),
                                                    hitMaterial.getPhongeExp());

                ofs << (int32_t)color.getR() << " " << (int32_t)color.getG()
                    << " " << (int32_t)color.getB() << "\n";
            } else {
                ofs << "0 0 0\n";
            }
        }
    }
}
