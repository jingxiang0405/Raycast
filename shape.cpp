#include <iostream>
#include "shape.hpp"

Sphere::Sphere(Vec3 c, float r):_center(c), _radius(r){}

float Sphere::intersect(const Ray& r) const {
    Vec3 O = r.origin();
    Vec3 d = r.direction();
    Vec3 OmC = O - this->_center;
    float b = 2 * dot(d, OmC);
    float e = dot(OmC, OmC) - this->_radius * this->_radius;
    float D = (b * b) - (4 * e);
    return (-b - sqrt(D) )/2;

}

Plane::Plane(float a, float b, float c, float d) : _coefficient(a, b, c), _d(d){}

float Plane::intersect(const Ray &r){
    float t = (_d - (dot(r.origin(), _coefficient))) / dot(r.direction(), _coefficient);
    return t;
}
