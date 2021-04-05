#include "plane.h"
#include <cmath>
#include <vector>
#include "rays.h"
#include "shape.h"
#include "tuples.h"
namespace ray_lib {

std::vector<Intersection> Plane::intersects(const Ray &r) const {
  std::vector<Intersection> results;
  Ray input_ray { r.Transform(Transform().inverse())};

  if (fabs(input_ray.Direction().y()) < __FLT_EPSILON__) {
    return results;
  }
  double t { -input_ray.Origin().y() / input_ray.Direction().y()};
  results.push_back(Intersection(reinterpret_cast<const Shape *>(this), t));
  return results;
}

const Vector Plane::Normal(const Point &position) const {
  Vector world_normal { Transform() * Vector(0, 1, 0)};
  return world_normal.normalise();
}

}  // namespace ray_lib
