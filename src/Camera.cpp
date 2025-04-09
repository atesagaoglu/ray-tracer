#include "Camera.hpp"

namespace raytracer {

Camera::Camera()
    : position(), gaze(), up(), nearDistance(0), resX(0), resY(0) {}

Camera::Camera(Vector position,
               Vector gaze,
               Vector up,
               Plane nearPlane,
               double nearDistance,
               int32_t resX,
               int32_t resY)
    : position(position), gaze(gaze), up(up), nearPlane(nearPlane),
      nearDistance(nearDistance), resX(resX), resY(resY) {}

Vector Camera::getPosition() const { return position; }

Vector Camera::getGaze() const { return gaze; }

Vector Camera::getUp() const { return up; }

Plane Camera::getNearPlane() const { return nearPlane; }

double Camera::getNearDistance() const { return nearDistance; }

int32_t Camera::getResX() const { return resX; }

int32_t Camera::getResY() const { return resY; }

Camera& Camera::setPosition(Vector val) {
    position = val;
    return *this;
}

Camera& Camera::setGaze(Vector val) {
    gaze = val;
    return *this;
}

Camera& Camera::setUp(Vector val) {
    up = val;
    return *this;
}

Camera& Camera::setNearPlane(Plane val) {
    nearPlane = val;
    return *this;
}

Camera& Camera::setNearDistance(double val) {
    nearDistance = val;
    return *this;
}

Camera& Camera::setResX(int32_t val) {
    resX = val;
    return *this;
}

Camera& Camera::setResY(int32_t val) {
    resY = val;
    return *this;
}

} // namespace raytracer
