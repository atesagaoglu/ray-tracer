#ifndef RAYTRACER_MATERIAL_HPP
#define RAYTRACER_MATERIAL_HPP

#include "Vector.hpp"

namespace raytracer {

class Material {
public:
    Material();
    Material(int id,
             Vector ambient,
             Vector diffuse,
             Vector specular,
             Vector mirrorReflectance,
             double phongeExp,
             double textureFactor);

    Vector getAmbient() const;
    Vector getDiffuse() const;
    Vector getSpecular() const;
    Vector getMirrorReflectance() const;

    double getPhongeExp() const;
    double getTextureFactor() const;

    int getId() const;

    Material& setAmbient(Vector val);
    Material& setDiffuse(Vector val);
    Material& setSpecular(Vector val);
    Material& setMirrorReflectance(Vector val);

    Material& setPhongeExp(double val);
    Material& setTextureFactor(double val);

    Material& setId(int val);

private:
    int id;
    Vector ambient;
    Vector diffuse;
    Vector specular;
    Vector mirrorReflectance;

    double phongeExp;
    double textureFactor;
};

} // namespace raytracer

#endif
