#ifndef RAYTRACER_CAMERA_HPP
#define RAYTRACER_CAMERA_HPP

#include "Plane.hpp"
#include "Vector.hpp"

namespace raytracer {

class Camera {

public:
    Camera();
    Camera(Vector position,
           Vector gaze,
           Vector up,
           Plane nearPlane,
           double nearDistance,
           int32_t resX,
           int32_t resY);

    Vector getPosition() const;
    Vector getGaze() const;
    Vector getUp() const;
    Plane getNearPlane() const;
    double getNearDistance() const;
    int32_t getResX() const;
    int32_t getResY() const;

    Camera& setPosition(Vector val);
    Camera& setGaze(Vector val);
    Camera& setUp(Vector val);
    Camera& setNearPlane(Plane val);
    Camera& setNearDistance(double val);
    Camera& setResX(int32_t val);
    Camera& setResY(int32_t val);

private:
    Vector position;
    Vector gaze;
    Vector up;
    Plane nearPlane;
    int32_t nearDistance;
    int32_t resX;
    int32_t resY;
};

} // namespace raytracer

#endif
