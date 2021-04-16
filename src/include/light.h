#ifndef _light_h_
#define _light_h_
#include "color.h"
#include "light.h"
#include "material.h"
#include "tuples.h"
#include "shape.h"
namespace ray_lib
{
  class Light
  {
  protected:
    Color _intensity;
    Point _position;

  public:
    Light(Color c, Point p) : _intensity(c), _position(p) {}
    Light() : _intensity(Color(1, 1, 1)), _position(Point(0, 0, 0)) {}
    Color intensity() const;
    Color intensity(Color n);
    Point position() const;
    Point position(Point n);
  };

  Color lighting(const Material &m, const Light &l, const Point &p,
                 const Vector &eye, const Vector &Normal, const Shape &s,
                 const bool inShadow = false);
  Color PatternAtObject(const Pattern &pat, const Shape &s, const Point &p);

} // namespace ray_lib

#endif
