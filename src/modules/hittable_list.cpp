#include "hittable_list.h"
#include "aabb.h"

namespace ray_lib
{
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