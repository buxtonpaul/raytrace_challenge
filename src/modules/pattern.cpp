#include "pattern.h"
#include <cmath>
#include "tuples.h"
namespace ray_lib {
Color StripePattern::getColor(ray_lib::Point p)const {
  int c = floor(p.x());
  return ((c % 2) == 0 ? _a : _b);
}

Color SolidPattern::getColor(ray_lib::Point p) const {
  return (_a);
}


}  // namespace ray_lib
