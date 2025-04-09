#include "Material.hpp"
#include <cstring>

namespace raytracer {

Material::Material() {}
Material::Material(int id,
                   Vector ambient,
                   Vector diffuse,
                   Vector specular,
                   Vector mirrorReflectance,
                   double phongeExp,
                   double textureFactor)
    : id(id), ambient(ambient), diffuse(diffuse), specular(specular),
      mirrorReflectance(mirrorReflectance), phongeExp(phongeExp),
      textureFactor(textureFactor) {}

Vector Material::getAmbient() const { return ambient; }

Vector Material::getDiffuse() const { return diffuse; }

Vector Material::getSpecular() const { return specular; }

Vector Material::getMirrorReflectance() const { return mirrorReflectance; }

double Material::getPhongeExp() const { return phongeExp; }
double Material::getTextureFactor() const { return textureFactor; }

int Material::getId() const { return id; }

Material& Material::setAmbient(Vector val) {
    ambient = val;
    return *this;
}

Material& Material::setDiffuse(Vector val) {
    diffuse = val;
    return *this;
}

Material& Material::setSpecular(Vector val) {
    specular = val;
    return *this;
}

Material& Material::setMirrorReflectance(Vector val) {
    mirrorReflectance = val;
    return *this;
}

Material& Material::setPhongeExp(double val) {
    phongeExp = val;
    return *this;
}
Material& Material::setTextureFactor(double val) {
    textureFactor = val;
    return *this;
}

Material& Material::setId(int val) {
    id = val;
    return *this;
}

} // namespace raytracer
