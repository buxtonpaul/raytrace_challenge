#include <cmath>
#include <vector>
#include <algorithm>
#include "rays.h"
#include "shape.h"
#include "tuples.h"
#include "group.h"

namespace ray_lib
{

  std::vector<Intersection> Group::intersects(const Ray &r) const
  {
    std::vector<Intersection> results;
    Ray input_ray { r.Transform(Transform().inverse())};

    for (auto child : _children){
      auto tmp = child->intersects(input_ray);
      std::move(tmp.begin(), tmp.end(), std::back_inserter(results));
    }
    std::sort(results.begin(), results.end());

    return results;
  }

} // namespace ray_lib
