#include "hittable_list.h"
#include "aabb.h"

namespace ray_lib
{
  aabb surrounding_box(aabb box0, aabb box1)
  {
    Point small(fmin(box0.min().x(), box1.min().x()),
                fmin(box0.min().y(), box1.min().y()),
                fmin(box0.min().z(), box1.min().z()));

    Point big(fmax(box0.max().x(), box1.max().x()),
              fmax(box0.max().y(), box1.max().y()),
              fmax(box0.max().z(), box1.max().z()));

    return aabb(small, big);
  }

  bool hittable_list::bounding_box(aabb &output_box) const
  {
    if (objects.empty())
      return false;

    aabb temp_box;
    bool first_box = true;

    for (const auto &object : objects)
    {
      if (!object->bounding_box(temp_box))
        return false;
      output_box = first_box ? temp_box : surrounding_box(output_box, temp_box);
      first_box = false;
    }

    return true;
  }
}