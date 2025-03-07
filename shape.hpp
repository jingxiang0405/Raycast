#include "vec3.hpp"
#include "ray.hpp"

class Sphere {

public:
    Sphere(Vec3 c, float r);
    float intersect(const Ray& r) const;
    inline Vec3& getCenter() { return _center; }
private:
    Vec3 _center;
    float _radius;
};

class Plane {
public:
    Plane(float a, float b, float c, float d);
    float intersect(Ray &r);

private:

    // plane function: ax + by + cz = d 
    Vec3 _coefficient; // (a, b, c)
    float _d;

};
