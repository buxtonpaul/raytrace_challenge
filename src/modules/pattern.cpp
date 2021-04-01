#include "pattern.h"
#include <cmath>
#include "tuples.h"
namespace ray_lib
{
  Color StripePattern::getColor(const ray_lib::Point &p) const
  {
    Point patPoint{_inverse * p};
    int c{static_cast<int>(floor(patPoint.x()))};
    return ((c % 2) == 0 ? _a : _b);
  }

  Color SolidPattern::getColor(const ray_lib::Point &p) const
  {
    return (_a);
  }

  Color GradientPattern::getColor(const ray_lib::Point &p) const
  {
    Point patPoint{_inverse * p};
   
    Color outcl{_a+ (_b-_a)*(patPoint.x()-floor(patPoint.x()))};
   
    return outcl;
  }

  SolidPattern SolidWhite(Color::White);


} // namespace ray_lib
