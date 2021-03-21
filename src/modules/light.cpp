#include "light.h"
#include "color.h"
#include "material.h"
#include "tuples.h"

namespace ray_lib
{

  Color lighting(const Material &m, const Light &l, const Point &p,
                 const Vector &eye, const Vector &Normal, const bool inShadow) 
  {

    const Pattern   *pat = m.GetPat();
    Color effective_color(0, 0, 0);
    if (pat)
      effective_color = pat->getColor(p) * l.Intensity();
    else
      effective_color = m.GetColor() * l.Intensity();
    Vector lightv = (l.Position() - p).normalise();
    Color ambient = effective_color * m.Ambient();
    Color diffuse = Color(0, 0, 0);
    Color specular = Color(0, 0, 0);

    if (inShadow)
      return ambient;
    double light_dot_normal = lightv.dotproduct(Normal);

    if (light_dot_normal >= 0)
    {
      diffuse = effective_color * m.Diffuse() * light_dot_normal;

      Vector reflectv = (Vector(0, 0, 0) - lightv).reflect(Normal);
      double reflect_dot_eye = reflectv.dotproduct(eye);
      if (reflect_dot_eye >= 0)
      {
        double factor = pow(reflect_dot_eye, m.Shininess());
        specular = l.Intensity() * m.Specular() * factor;
      }
    }

    return ambient + diffuse + specular;
  }
} // namespace ray_lib
