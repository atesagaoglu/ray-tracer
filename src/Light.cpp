#include "Light.hpp"

namespace raytracer {

Light::Light() : intensity() {}
Light::Light(Vector intensity) : intensity(intensity) {}

} // namespace raytracer
