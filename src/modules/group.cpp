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
    Ray input_ray{r.Transform(Transform().inverse())};

    for (auto child : _children)
    {
      auto tmp = child->intersects(input_ray);
      std::move(tmp.begin(), tmp.end(), std::back_inserter(results));
    }
    std::sort(results.begin(), results.end());

    return results;
  }

  const Vector Group::local_normal_at(const Point &position) const
  {
    return {0, 0, 0};
  }

  bool Group::isEmpty() const
  {
    return (_children.size() == 0);
  }

  const Group &Group::add_child(Shape *s)
  {
    _children.push_back(s);
    s->parent(this);
  }

  bool Group::includes(const Shape *s) const
  {
    return contains(_children, s);
  }
} // namespace ray_lib
