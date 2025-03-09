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

Vec3 Sphere::normalAtPoint(const Vec3& p) const{
    Vec3 v = p;
    return unit(v - _center); 
}
//
//


//
//
Cube::Cube(Vec3 v1, Vec3 v2) : _v1(v1), _v2(v2) {}

float Cube::intersect(const Ray& r) const {
    float t_v1 = -INFINITY;
    float t_v2 = INFINITY;

    Vec3 inv_dir = Vec3(1.0f / r.direction().x(), 1.0f / r.direction().y(), 1.0f / r.direction().z());

    for (int i = 0; i < 3; ++i) {
        float t1 = (_v1.e[i] - r.origin().e[i]) * inv_dir.e[i];
        float t2 = (_v2.e[i] - r.origin().e[i]) * inv_dir.e[i];

        if (t1 > t2) std::swap(t1, t2);

        t_v1 = t1 > t_v1 ? t1 : t_v1;
        t_v2 = t2 < t_v2 ? t2 : t_v2;

        if (t_v1 > t_v2) return -1.0f;
    }

    if (t_v1 > 0.0f) {
        return t_v1;
    } else if (t_v2 > 0.0f) {
        return t_v2;
    }

    return -1.0f;
}

Vec3 Cube::normalAtPoint(const Vec3& p) const {
    Vec3 normal(0, 0, 0);

    if (fabs(p.x() - _v1.x()) < 1e-5) normal = Vec3(-1, 0, 0);
    else if (fabs(p.x() - _v2.x()) < 1e-5) normal = Vec3(1, 0, 0);
    else if (fabs(p.y() - _v1.y()) < 1e-5) normal = Vec3(0, -1, 0);
    else if (fabs(p.y() - _v2.y()) < 1e-5) normal = Vec3(0, 1, 0);
    else if (fabs(p.z() - _v1.z()) < 1e-5) normal = Vec3(0, 0, -1);
    else if (fabs(p.z() - _v2.z()) < 1e-5) normal = Vec3(0, 0, 1);

    return unit(normal);
}
