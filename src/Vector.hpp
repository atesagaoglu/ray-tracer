#ifndef RAYTRACER_VECTOR_HPP
#define RAYTRACER_VECTOR_HPP

namespace raytracer {

class Vector {

public:
    Vector();
    Vector(double x, double y, double z);

    double getX() const;
    double getY() const;
    double getZ() const;

    Vector& setX(double val);
    Vector& setY(double val);
    Vector& setZ(double val);

    void print();

    // Vector + Vector
    Vector operator+(const Vector& v) const {
        return Vector(x + v.x, y + v.y, z + v.z);
    }

    // Vector - Vector
    Vector operator-(const Vector& v) const {
        return Vector(x - v.x, y - v.y, z - v.z);
    }

    // Vector * scalar
    Vector operator*(double s) const { return Vector(x * s, y * s, z * s); }

    // Vector / scalar
    Vector operator/(double s) const { return Vector(x / s, y / s, z / s); }

    Vector operator*(const Vector& other) const {
        return Vector(x * other.x, y * other.y, z * other.z);
    }

    Vector cross(Vector& oth);
    double dot(Vector& dot);

    Vector normalize() const;

private:
    double x, y, z;
};

inline Vector operator*(double s, const Vector& v) {
    return Vector(v.getX() * s, v.getY() * s, v.getZ() * s);
}

} // namespace raytracer

#endif
