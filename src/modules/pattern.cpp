#include "pattern.h"
#include <cmath>
#include "tuples.h"
namespace ray_lib
{
  Color StripePattern::getColor(const ray_lib::Point &p) const
  {
    Point patPoint{_transform.inverse() * p};
    int c{static_cast<int>(floor(patPoint.x()))};
    return ((c % 2) == 0 ? _a : _b);
  }

  Color SolidPattern::getColor(const ray_lib::Point &p) const
  {
    return (_a);
  }

  SolidPattern SolidWhite(Color::White);

  Color PatternAtObject(const Pattern &pat, const Shape &s, const Point &p)
  {
    Point objpoint{  s.Transform().inverse() * p};

    return pat.getColor(objpoint);
  }

} // namespace ray_lib
