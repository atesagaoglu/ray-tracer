#include "Parser.hpp"

#include "tinyxml/tinyxml2.h"
#include <algorithm>
#include <iostream>
#include <sstream>

#include "AmbientLight.hpp"
#include "Camera.hpp"
#include "Color.hpp"
#include "Light.hpp"
#include "Object.hpp"
#include "Plane.hpp"
#include "PointLight.hpp"
#include "Scene.hpp"
#include "Vector.hpp"

namespace raytracer {

Scene parse(const char* filename) {
    raytracer::Scene scene;

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError result = doc.LoadFile(filename);

    if (result != tinyxml2::XML_SUCCESS) {
        std::cerr << "Failed to load XML file" << doc.ErrorStr() << std::endl;
    }

    tinyxml2::XMLNode* sceneNode = doc.FirstChildElement("scene");
    if (!sceneNode) {
        std::cerr << "No <scene> found." << std::endl;
        exit(EXIT_FAILURE);
    }

    tinyxml2::XMLNode* mrtdNode =
        sceneNode->FirstChildElement("maxraytracedepth")->FirstChild();
    if (!mrtdNode) {
        std::cerr << "No <maxraytracedepth> found." << std::endl;
        exit(EXIT_FAILURE);
    }

    double mrtdValue = std::atof(mrtdNode->Value());
    scene.setMaxDepth(mrtdValue);

    tinyxml2::XMLNode* bgColorNode =
        sceneNode->FirstChildElement("backgroundColor")->FirstChild();
    if (!bgColorNode) {
        std::cerr << "No <backgroundColor> found." << std::endl;
        exit(EXIT_FAILURE);
    }

    unsigned int r, g, b = 0;
    sscanf(bgColorNode->Value(), "%u %u %u", &r, &g, &b);

    raytracer::Color bgColor(static_cast<uint8_t>(r),
                             static_cast<uint8_t>(g),
                             static_cast<uint8_t>(b));

    scene.setBackgroundColor(bgColor);

    tinyxml2::XMLNode* cameraNode = sceneNode->FirstChildElement("camera");
    if (!cameraNode) {
        std::cerr << "No <camera> found." << std::endl;
        exit(EXIT_FAILURE);
    }

    tinyxml2::XMLNode* positionNode = cameraNode->FirstChildElement("position");
    if (!positionNode) {
        std::cerr << "No <postion> found." << std::endl;
        exit(EXIT_FAILURE);
    }

    double x, y, z;
    sscanf(positionNode->FirstChild()->Value(), "%lf %lf %lf", &x, &y, &z);

    raytracer::Vector cameraPos(x, y, z);

    tinyxml2::XMLNode* gazeNode = cameraNode->FirstChildElement("gaze");
    if (!gazeNode) {
        std::cerr << "No <gaze> found." << std::endl;
        exit(EXIT_FAILURE);
    }

    sscanf(gazeNode->FirstChild()->Value(), "%lf %lf %lf", &x, &y, &z);
    raytracer::Vector gazeVector(x, y, z);

    tinyxml2::XMLNode* upNode = cameraNode->FirstChildElement("up");
    if (!upNode) {
        std::cerr << "No <up> found." << std::endl;
        exit(EXIT_FAILURE);
    }

    sscanf(upNode->FirstChild()->Value(), "%lf %lf %lf", &x, &y, &z);
    raytracer::Vector upVector(x, y, z);

    tinyxml2::XMLNode* planeNode = cameraNode->FirstChildElement("nearplane");
    if (!planeNode) {
        std::cerr << "No <nearplane> found." << std::endl;
        exit(EXIT_FAILURE);
    }

    double pt, pb, pr, pl;
    sscanf(planeNode->FirstChild()->Value(),
           "%lf %lf %lf %lf",
           &pl,
           &pr,
           &pb,
           &pt);
    raytracer::Plane nearPlane(pl, pr, pb, pt);

    tinyxml2::XMLNode* nearDistanceNode =
        cameraNode->FirstChildElement("neardistance");
    if (!nearDistanceNode) {
        std::cerr << "No <neardistance> found." << std::endl;
        exit(EXIT_FAILURE);
    }

    int32_t nearDistance = std::atoi(nearDistanceNode->FirstChild()->Value());

    tinyxml2::XMLNode* resNode =
        cameraNode->FirstChildElement("imageresolution");
    if (!resNode) {
        std::cerr << "No <imageresolution> found." << std::endl;
        exit(EXIT_FAILURE);
    }

    int32_t resx, resy;
    sscanf(resNode->FirstChild()->Value(), "%d %d", &resx, &resy);

    raytracer::Camera camera(cameraPos,
                             gazeVector,
                             upVector,
                             nearPlane,
                             nearDistance,
                             resx,
                             resy);

    scene.setCamera(camera);

    tinyxml2::XMLNode* lightsNode = sceneNode->FirstChildElement("lights");
    if (!lightsNode) {
        std::cerr << "No <lights> found." << std::endl;
        exit(EXIT_FAILURE);
    }

    for (tinyxml2::XMLNode* current = lightsNode->FirstChild();
         current != nullptr;
         current = current->NextSibling()) {
        const char* name = current->Value();

        raytracer::Light* light;

        // TODO: Add print functions for lights or debugging.
        if (strcmp(name, "ambientlight") == 0) {
            int32_t x, y, z;
            sscanf(current->FirstChild()->Value(), "%d %d %d", &x, &y, &z);

            light = new raytracer::AmbientLight(raytracer::Vector(x, y, z));
            std::cout << "Created AmbientLight" << std::endl;

            // raytracer::AmbientLight* aml =
            //     dynamic_cast<raytracer::AmbientLight*>(light);
            //
            // std::cout << static_cast<int>(aml->getR()) << std::endl;
            // std::cout << static_cast<int>(aml->getG()) << std::endl;
            // std::cout << static_cast<int>(aml->getB()) << std::endl;

        } else if (strcmp(name, "pointlight") == 0) {
            double x, y, z;
            int a, b, c;
            const char* id;

            id = current->ToElement()->Attribute("id");
            if (!id) {
                std::cout << "PointLight at " << current->GetLineNum()
                          << " has no id." << std::endl;
            }

            tinyxml2::XMLNode* posNode;
            tinyxml2::XMLNode* intNode;

            posNode = current->FirstChildElement("position");
            if (!posNode) {
                std::cerr << "No <postion> found at " << current->GetLineNum()
                          << std::endl;
                exit(EXIT_FAILURE);
            }

            sscanf(posNode->FirstChild()->Value(), "%lf %lf %lf", &x, &y, &z);

            intNode = current->FirstChildElement("intensity");
            if (!intNode) {
                std::cerr << "No <intensity> found at " << current->GetLineNum()
                          << std::endl;
                exit(EXIT_FAILURE);
            }

            sscanf(intNode->FirstChild()->Value(), "%d %d %d", &a, &b, &c);

            light = new raytracer::PointLight(raytracer::Vector(a, b, c),
                                              raytracer::Vector(x, y, z));
            std::cout << "Created PointLight" << std::endl;
        } else if (strcmp(name, "triangularlight") == 0) {

            continue;

            // double x, y, z;
            // int a, b, c;
            // const char* id;
            //
            // id = current->ToElement()->Attribute("id");
            // if (!id) {
            //     std::cout << "TriangularLight at " << current->GetLineNum()
            //               << " has no id." << std::endl;
            // }
            //
            // std::array<raytracer::Position, 3> vertices;
            //
            // tinyxml2::XMLNode* currVer = current->FirstChild();
            // for (size_t i = 0; i < 3; i++) {
            //     sscanf(currVer->FirstChild()->Value(),
            //            "%lf %lf %lf",
            //            &x,
            //            &y,
            //            &z);
            //     vertices[i] = raytracer::Position(x, y, z);
            //
            //     currVer = currVer->NextSibling();
            // }
            //
            // tinyxml2::XMLNode* intNode;
            //
            // intNode = current->FirstChildElement("intensity");
            // if (!intNode) {
            //     std::cerr << "No <intensity> found at " <<
            //     current->GetLineNum()
            //               << std::endl;
            //     exit(EXIT_FAILURE);
            // }
            //
            // sscanf(intNode->FirstChild()->Value(), "%d %d %d", &a, &b, &c);
            //
            // light =
            //     new raytracer::TriangularLight(x,
            //                                    y,
            //                                    z,
            //                                    raytracer::Intensity(a, b, c),
            //                                    vertices,
            //                                    id);
            // std::cout << "Created TriangularLight" << std::endl;
        }

        scene.addLight(light);

        light = nullptr;
    }

    tinyxml2::XMLNode* materialsNode =
        sceneNode->FirstChildElement("materials");
    if (!materialsNode) {
        std::cerr << "No <materials> found." << std::endl;
        exit(EXIT_FAILURE);
    }

    for (tinyxml2::XMLNode* current = materialsNode->FirstChild();
         current != nullptr;
         current = current->NextSibling()) {

        raytracer::Material material;
        const char* id;
        id = current->ToElement()->Attribute("id");

        // Iterate over attributes of selected material
        for (tinyxml2::XMLNode* currentAttr = current->FirstChild();
             currentAttr != nullptr;
             currentAttr = currentAttr->NextSibling()) {
            const char* attrName = currentAttr->Value();
            const char* attrVal = currentAttr->FirstChild()->Value();

            double x, y, z, d;
            if (strcmp(attrName, "ambient") == 0) {
                sscanf(attrVal, "%lf %lf %lf", &x, &y, &z);
                material.setAmbient(raytracer::Vector(x, y, z));

            } else if (strcmp(attrName, "diffuse") == 0) {
                sscanf(attrVal, "%lf %lf %lf", &x, &y, &z);
                material.setDiffuse(raytracer::Vector(x, y, z));

            } else if (strcmp(attrName, "specular") == 0) {
                sscanf(attrVal, "%lf %lf %lf", &x, &y, &z);
                material.setSpecular(raytracer::Vector(x, y, z));

            } else if (strcmp(attrName, "phongexponent") == 0) {
                sscanf(attrVal, "%lf", &d);
                material.setPhongeExp(d);
            } else if (strcmp(attrName, "mirrorreflactance") == 0) {
                sscanf(attrVal, "%lf %lf %lf", &x, &y, &z);
                material.setMirrorReflectance(raytracer::Vector(x, y, z));
            } else if (strcmp(attrName, "texturefactor") == 0) {
                sscanf(attrVal, "%lf", &d);
                material.setPhongeExp(d);
            }
        }
        material.setId(atoi(id));

        scene.addMaterial(material);
    }

    tinyxml2::XMLNode* verticesNode =
        sceneNode->FirstChildElement("vertexdata");
    if (!verticesNode) {
        std::cerr << "No <vertexdata> found." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::istringstream stream(verticesNode->FirstChild()->Value());
    std::string line;

    size_t i = 0;
    while (std::getline(stream, line)) {
        // Skip empty or whitespace-only lines
        if (std::all_of(line.begin(), line.end(), isspace)) {
            continue;
        }

        double x, y, z;
        sscanf(line.c_str(), "%lf %lf %lf", &x, &y, &z);
        scene.addVertexData(raytracer::Vector(x, y, z));

        i++;
    }

    // <testuredata>

    tinyxml2::XMLNode* normalNode = sceneNode->FirstChildElement("normaldata");
    if (!normalNode) {
        std::cerr << "No <normaldata> found.";
        exit(EXIT_FAILURE);
    }

    stream.clear();
    stream.str(std::string(normalNode->FirstChild()->Value()));

    i = 0;
    while (std::getline(stream, line)) {
        // Skip empty or whitespace-only lines
        if (std::all_of(line.begin(), line.end(), isspace)) {
            continue;
        }

        double x, y, z;
        sscanf(line.c_str(), "%lf %lf %lf", &x, &y, &z);

        scene.addNormalData(raytracer::Vector(x, y, z));

        i++;
    }

    tinyxml2::XMLNode* objectsNode = sceneNode->FirstChildElement("objects");
    if (!objectsNode) {
        std::cerr << "No <objects> found." << std::endl;
        exit(EXIT_FAILURE);
    }

    // TODO: add this to scene
    std::vector<raytracer::Object> objects;

    for (tinyxml2::XMLNode* current = objectsNode->FirstChild();
         current != nullptr;
         current = current->NextSibling()) {
        const char* meshId;
        meshId = current->ToElement()->Attribute("id");
        std::cout << "Mesh Id: " << meshId << std::endl;

        uint32_t materialId = atoi(
            current->FirstChildElement("materialid")->FirstChild()->Value());

        std::cout << "materialId: " << materialId << std::endl;

        std::istringstream stream(
            current->FirstChildElement("faces")->FirstChild()->Value());
        std::string line;

        size_t i = 0;
        while (std::getline(stream, line)) {
            // Skip empty or whitespace-only lines
            if (std::all_of(line.begin(), line.end(), isspace)) {
                continue;
            }

            std::cout << "[" << i << "]" << ": " << line << std::endl;

            uint32_t vx, vy, vz;
            uint32_t tx, ty, tz;
            uint32_t nx, ny, nz;

            // This can be done prettier
            sscanf(line.c_str(),
                   "%u/%u/%u %u/%u/%u %u/%u/%u",
                   &vx,
                   &tx,
                   &nx,
                   &vy,
                   &ty,
                   &ny,
                   &vz,
                   &tz,
                   &nz);

            std::cout << "vx: " << vx << std::endl;
            std::cout << "vy: " << vy << std::endl;
            std::cout << "vz: " << vz << std::endl;

            raytracer::Object obj;
            raytracer::Face face;

            face.setVertex(vx, vy, vz);
            face.setTexture(tx, ty, tz);
            face.setNormal(nx, ny, nz);

            obj.addFace(face);
            obj.setId(atoi(meshId));
            obj.setMaterialId(materialId);

            objects.push_back(obj);
            i++;
        }
    }

    scene.setObjects(objects);

    return scene;
}

} // namespace raytracer
