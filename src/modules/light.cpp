#include "light.h"
#include "color.h"
#include "material.h"
#include "tuples.h"

namespace ray_lib
{

  Color lighting(const Material &m, const Light &l, const Point &p,
                 const Vector &eye, const Vector &Normal, const Shape &s, const bool inShadow)
  {
    const Pattern &pat{m.pattern()};
    Color effective_color{PatternAtObject(pat, s, p) * l.intensity()};
    Vector lightv{(l.position() - p).normalise()};
    Color ambient{effective_color * m.ambient()};
    Color diffuse{Color(0, 0, 0)};
    Color specular{Color(0, 0, 0)};

    if (inShadow)
      return ambient;
    double light_dot_normal{lightv.dotproduct(Normal)};

    if (light_dot_normal >= 0)
    {
      diffuse = effective_color * m.diffuse() * light_dot_normal;

      Vector reflectv{(Vector(0, 0, 0) - lightv).reflect(Normal)};
      double reflect_dot_eye{reflectv.dotproduct(eye)};
      if (reflect_dot_eye >= 0)
      {
        double factor{pow(reflect_dot_eye, m.shininess())};
        specular = l.intensity() * m.specular() * factor;
      }
    }

    return ambient + diffuse + specular;
  }

  Color PatternAtObject(const Pattern &pat, const Shape &s, const Point &p)
  {
    return pat.getColor(s.world_to_object(p));
  }

  Color Light::intensity() const
  {
    return _intensity;
  }
  Color Light::intensity(Color n)
  {
    _intensity = n;
    return n;
  }
  Point Light::position() const
  {
    return _position;
  }
  Point Light::position(Point n)
  {
    _position = n;
    return n;
  }

} // namespace ray_lib
