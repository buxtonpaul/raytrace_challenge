#include "pattern.h"
#include <cmath>
#include "tuples.h"
namespace ray_lib
{
  Color StripePattern::getColor(const ray_lib::Point &p, const Matrix &worldtransform) const
  {
    int c{static_cast<int>(floor(p.x()))};
    return ((c % 2) == 0 ? _a : _b);
  }

  Color SolidPattern::getColor(const ray_lib::Point &p, const Matrix &worldtransform) const
  {
    return (_a);
  }

  SolidPattern SolidWhite(Color::White);

} // namespace ray_lib
