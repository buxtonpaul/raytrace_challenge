#include "rays.h"
#include <vector>
#include "matrix.h"
#include "sphere.h"
#include "tuples.h"
#include "utils.h"
namespace ray_lib {

std::ostream &operator<<(std::ostream &out, const Ray &r) {
  out << "Ray Origin :" << r._origin << " Direction " << r._direction
      << std::endl;
  return out;
}

std::ostream &operator<<(std::ostream &out, const Intersection &i) {
  out << "Intersection distance t= :" << i.t() << std::endl;
  return out;
}

const Intersection *Intersection::GetHit(
    const std::vector<Intersection> &intersections) {
  const Intersection *min = nullptr;
  for (unsigned int i = 0; i < intersections.size(); ++i) {
    if (intersections[i].t() > 0) {
      if (min != nullptr) {
        if (intersections[i].t() < min->t()) min = &intersections[i];
      } else {
        min = &intersections[i];
      }
    }
  }
  return min;
}

}  // namespace ray_lib
