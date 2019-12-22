#include "rays.h"
#include "matrix.h"
#include "tuples.h"
#include "utils.h"

namespace ray_lib {

std::ostream &operator<<(std::ostream &out, const Ray &r) {
  out << "Ray Origin :" << r._origin << " Direction " << r._direction
      << std::endl;
  return out;
}

}  // namespace ray_lib
