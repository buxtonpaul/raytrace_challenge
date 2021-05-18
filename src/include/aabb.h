#ifndef _aabb_h
#define _aabb_h
#include "tuples.h"
// #include "rays.h"

namespace ray_lib
{
  class Ray;

  class aabb
  {
  public:
    aabb() {}
    aabb(const Point &a, const Point &b)
    {
      minimum = a;
      maximum = b;
    }

    Point min() const { return minimum; }
    Point max() const { return maximum; }

    bool hit(const Ray &r, double t_min, double t_max) const;

    Point minimum;
    Point maximum;
  };
}// namespace ray_lib
#endif //_aabb_h