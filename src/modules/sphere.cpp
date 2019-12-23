#include "sphere.h"
#include <cmath>
#include <vector>
#include "rays.h"
#include "tuples.h"
namespace ray_lib {

std::vector<Intersection> Sphere::intersects(const Ray &r) const {
  std::vector<Intersection> results;
  Vector sphere_to_ray = r.Origin() - _center;

  double a = r.Direction().dotproduct(r.Direction());
  double b = r.Direction().dotproduct(sphere_to_ray) * 2.0;
  double c = sphere_to_ray.dotproduct(sphere_to_ray) - 1.0;
  double descriminant = b * b - 4 * a * c;

  if (descriminant >= 0) {
    double t1 = (-b - sqrt(descriminant)) / (2 * a);
    double t2 = (-b + sqrt(descriminant)) / (2 * a);
    if (t1 > t2) {
      results.push_back(Intersection(this, t2, r));
      results.push_back(Intersection(this, t1, r));
    } else {
      results.push_back(Intersection(this, t1, r));
      results.push_back(Intersection(this, t2, r));
    }
  }
  return results;
}
}  // namespace ray_lib
