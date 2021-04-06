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

  Color GradientPattern::getColor(const ray_lib::Point &p) const
  {
    Point patPoint{_transform.inverse() * p};
    Color outcl{_a + (_b - _a) * (patPoint.x() - floor(patPoint.x()))};
    return outcl;
  }

  Color RingPattern::getColor(const ray_lib::Point &p) const
  {
    Point patPoint{_transform.inverse() * p};
    int c{static_cast<int>(floor(sqrt(patPoint.x() * patPoint.x() + patPoint.z() * patPoint.z())))};
    return ((c % 2) == 0 ? _a : _b);
  }

  Color CheckPattern3d::getColor(const ray_lib::Point &p) const
  {
    Point patPoint{_transform.inverse() * p};
    int c{static_cast<int>(floor(patPoint.x()) + floor(patPoint.y()) + floor(patPoint.z()))};
    return ((c % 2) == 0 ? _a : _b);
  }

} // namespace ray_lib
