#ifndef _material_h_
#define _material_h_
#include "color.h"
#include "utils.h"
#include "pattern.h"
namespace ray_lib
{

// Structure for holding some default values for the struct, can be used by others as a helper
struct mat_params{
  double ambient, diffuse, specular, shiny, reflect, transparency, index;
};
extern mat_params default_matparams;
class Material
{
protected:
  double _ambient = default_matparams.ambient;
  double _diffuse = default_matparams.diffuse;
  double _specular = default_matparams.specular;
  double _shininess = default_matparams.shiny;
  double _reflectiveness = default_matparams.reflect;
  double _transparency = default_matparams.transparency;
  double _refractive_index = default_matparams.index;
  const Pattern *_pat = ray_lib::SolidWhite.asPattern();

public:
  Material(double a , double d, double spec , double shin , double reflectiveness, double transparency, double ri, Pattern *inpat )
      : _ambient{a},
        _diffuse{d},
        _specular{spec},
        _shininess{shin},
        _reflectiveness{reflectiveness},
        _transparency{transparency},
        _refractive_index{ri},
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


  double Transparency(double n)
  {
    _transparency = n;
    return n;
  }
  double RefractiveIndex(double n)
  {
    _refractive_index = n;
    return n;
  }

  void SetPattern(Pattern *const pattern) { _pat = pattern; }

  const Pattern *GetPat() const { return _pat; }
  double Ambient() const { return _ambient; }
  double Diffuse() const { return _diffuse; }
  double Specular() const { return _specular; }
  double Shininess() const { return _shininess; }
  double Reflectivity() const { return _reflectiveness; }
  double RefractiveIndex() const {return _refractive_index; }
  double Transparency() const {return _transparency;}
  friend std::ostream &operator<<(std::ostream &out, const Material &m);
  bool operator==(const Material &rhs) const
  {
    return (_pat == rhs._pat && float_equals(_ambient, rhs._ambient) &&
            float_equals(_diffuse, rhs._diffuse) &&
            float_equals(_specular, rhs._specular) &&
            float_equals(_transparency, rhs._transparency) &&
            float_equals(_refractive_index, rhs._refractive_index) &&
            float_equals(_reflectiveness, rhs._reflectiveness) &&
            float_equals(_shininess, rhs._shininess));
  }
};

extern Material glass;
} // namespace ray_lib

#endif
