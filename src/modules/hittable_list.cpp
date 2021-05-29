

#include "hittable_list.h"
#include "rays.h"

namespace ray_lib{
  bool hittable_list::intersects(const Ray &r, const double tmin, const double tmax, Intersection *rec) const
  {
    Intersection temp_rec{nullptr, INFINITY};
    auto hit_anything = false;
    auto closest_so_far = tmin;

    for (const auto &object : objects)
    {
      if (object->intersects(r, tmax, closest_so_far, &temp_rec))
      {
        hit_anything = true;
        closest_so_far = temp_rec.t();
        *rec = temp_rec;
      }
    }

    return hit_anything;
  }
  std::vector<Intersection> hittable_list::intersects(const Ray &r) const
  {
    return intersects(r, -INFINITY, INFINITY);
  }

  std::vector<Intersection> hittable_list::intersects(const Ray &r, const double tmin, const double tmax) const
  {
   // todo:Me implement this
  }


  bool hittable_list::bounding_box(aabb *output_box) const
  {
    if (objects.empty())
      return false;

    aabb temp_box;
    bool first_box = true;

    for (const auto &object : objects)
    {
      if (!object->bounding_box(&temp_box))
        return false;
      *output_box = first_box ? temp_box : surrounding_box(*output_box, temp_box);
      first_box = false;
    }

    return true;
  }
}// namespace ray_lib
