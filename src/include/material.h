#ifndef _material_h_
#define _material_h_
#include "color.h"
#include "utils.h"
#include "pattern.h"
namespace ray_lib
{

  class Material
  {
  protected:
    double _ambient;
    double _diffuse;
    double _specular;
    double _shininess;
    const Pattern *_pat;

  public:
    Material(double a = 0.1, double d = 0.9, double spec = 0.9, double shin = 200, Pattern *inpat = ray_lib::SolidWhite.asPattern())
        : _ambient(a),
          _diffuse(d),
          _specular(spec),
          _shininess(shin),
          _pat(inpat)

    {
    }
    double Ambient(double n)
    {
      _ambient = n;
      return n;
    }
    double Diffuse(double n)
    {
      _diffuse = n;
      return n;
    }
    double Specular(double n)
    {
      _specular = n;
      return n;
    }
    double Shininess(double n)
    {
      _shininess = n;
      return n;
    }

    void SetPattern(Pattern *const pattern) { _pat = pattern; }

    const Pattern *GetPat() const { return _pat; }
    double Ambient() const { return _ambient; }
    double Diffuse() const { return _diffuse; }
    double Specular() const { return _specular; }
    double Shininess() const { return _shininess; }
    friend std::ostream &operator<<(std::ostream &out, const Material &m);
    bool operator==(const Material &rhs) const
    {
      return (_pat == rhs._pat && float_equals(_ambient, rhs._ambient) &&
              float_equals(_diffuse, rhs._diffuse) &&
              float_equals(_specular, rhs._specular) &&
              float_equals(_shininess, rhs._shininess));
    }
  };

} // namespace ray_lib

#endif
