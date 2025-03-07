#ifndef RAY_H
#define RAY_H
#include "vec3.hpp"
class Ray
{
public:
  Ray() {}
  Ray(const Vec3 &a, const Vec3 &b)
  {
    O = a;
    D = b;
  }
  Vec3 origin() const { return O; }
  Vec3 direction() const { return D; }
  Vec3 point_at_parameter(float t) const
  {
        return t * D + O;
  }
  Vec3 O;
  Vec3 D;
};
#endif
