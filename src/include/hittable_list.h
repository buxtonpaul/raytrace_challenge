#ifndef _hittable_list_h_
#define _hittable_list_h
#include "shape.h"
#include "hittable.h"

namespace ray_lib
{

  class hittable_list : Hittable
  {
  public:
    // virtual bool hit(
    //     const ray& r, double t_min, double t_max, hit_record& rec) const override;
   bool intersects(const Ray &r, const double tmin, const double tmax,Intersection &rec) const;

    virtual bool bounding_box(
        aabb &output_box) const override;

    std::vector<Shape *> objects;
  };
}
#endif