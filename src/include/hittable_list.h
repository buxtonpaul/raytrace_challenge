#ifndef _hittable_list_h_
#define _hittable_list_h
#include <vector>
#include <memory>
#include "shape.h"
#include "hittable.h"

namespace ray_lib
{

class hittable_list : Hittable
{
public:
  bool intersects(const Ray &r, const double tmin, const double tmax, Intersection *rec) const;
  virtual bool bounding_box(aabb *output_box) const;
  std::vector<std::shared_ptr<Hittable>> objects;
};
} // namespace ray_lib
#endif //_hittable_list_h_
