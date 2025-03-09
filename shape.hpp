#include "vec3.hpp"
#include "ray.hpp"

class Shape{
public:
    virtual float intersect(const Ray& r) const = 0;
    virtual Vec3 normalAtPoint(const Vec3& p) const = 0;
};

/*
    
*/
class Sphere : public Shape{

public:
    Sphere(Vec3 c, float r);
    float intersect(const Ray& r) const override;
    Vec3 normalAtPoint(const Vec3& p) const override;
private:
    Vec3 _center;
    float _radius;
};

/*
    
*/
class Cube : public Shape{

public:
    Cube(Vec3 v1, Vec3 v2);
    float intersect(const Ray& r) const override;
    Vec3 normalAtPoint(const Vec3& p) const override;
private:
    Vec3 _v1;
    Vec3 _v2;
};
