#ifndef _hittable_h
#define _hittable_h
#include <vector>
#include "aabb.h"
namespace ray_lib
{
class Intersection;
class Ray;
class Hittable
  {
  public:
    virtual std::vector<Intersection> intersects(const Ray &r, const double tmin, const double tmax) const = 0;
    virtual std::vector<Intersection> intersects(const Ray &r) const = 0;
    virtual bool intersects(const Ray &r, const double tmin, const double tmax, Intersection *rec) const = 0;
    virtual bool bounding_box(aabb *output_box) const = 0;
  };
}// namespace ray_lib
#endif // hittable_h_
