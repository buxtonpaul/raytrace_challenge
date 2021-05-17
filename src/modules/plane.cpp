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

const Vector Plane::local_normal_at(const Point &position,const Intersection &i) const {
  Vector world_normal { Transform() * Vector(0, 1, 0)};
  return world_normal.normalise();
}

 const void Plane::getBounds(Bounds *bounds)const
  {
    bounds->mins.x(-INFINITY);
    bounds->mins.y(-INFINITY);
    bounds->mins.z(0);
    bounds->maxs.x(INFINITY);
    bounds->maxs.y(INFINITY);
    bounds->maxs.z(0);
  }


}  // namespace ray_lib
