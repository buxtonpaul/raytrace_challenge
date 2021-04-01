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
  double _ambient = 0.1;
  double _diffuse = 0.9;
  double _specular = 0.9;
  double _shininess = 200;
  double _reflectiveness = 0;
  const Pattern *_pat = ray_lib::SolidWhite.asPattern();

public:
  Material(double a , double d, double spec , double shin , double reflectiveness, Pattern *inpat )
      : _ambient{a},
        _diffuse{d},
        _specular{spec},
        _shininess{shin},
        _reflectiveness{reflectiveness},
        _pat{inpat}

  {
  }
  Material(){}
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

  double Reflectivity(double n)
  {
    _reflectiveness = n;
    return n;
  }

  void SetPattern(Pattern *const pattern) { _pat = pattern; }

  const Pattern *GetPat() const { return _pat; }
  double Ambient() const { return _ambient; }
  double Diffuse() const { return _diffuse; }
  double Specular() const { return _specular; }
  double Shininess() const { return _shininess; }
  double Reflectivity() const { return _reflectiveness; }
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
