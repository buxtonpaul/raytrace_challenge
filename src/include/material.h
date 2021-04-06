#ifndef _material_h_
#define _material_h_
#include <memory>
#include <utility>
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
  double _transparency = 0;
  double _refractive_index = 1;
  std::unique_ptr<Pattern> _pat = ray_lib::SolidPattern(Color::White).clone();
public:
  Material(double a, double d, double spec, double shin, double reflectiveness, double transparency, double ri, Pattern *inpat)
      : _ambient{a},
        _diffuse{d},
        _specular{spec},
        _shininess{shin},
        _reflectiveness{reflectiveness},
        _transparency{transparency},
        _refractive_index{ri}

  {
    _pat = inpat->clone();
  }

  Material(const Material &other)
  {
    _ambient = other._ambient;
    _diffuse = other._diffuse;
    _specular = other._specular;
    _shininess = other._shininess;
    _reflectiveness = other._reflectiveness;
    _transparency = other._transparency;
    _refractive_index = other._refractive_index;
    _pat = other._pat->clone();
  }

  Material operator =(const Material &other)
  {
    _ambient = other._ambient;
    _diffuse = other._diffuse;
    _specular = other._specular;
    _shininess = other._shininess;
    _reflectiveness = other._reflectiveness;
    _transparency = other._transparency;
    _refractive_index = other._refractive_index;
    _pat = other._pat->clone();
    return *this;
  }

  Material(Material &&other)
  {
    _ambient = other._ambient;
    _diffuse = other._diffuse;
    _specular = other._specular;
    _shininess = other._shininess;
    _reflectiveness = other._reflectiveness;
    _transparency = other._transparency;
    _refractive_index = other._refractive_index;
    _pat = std::move(other._pat);
  }

  Material() {}
  Material &Ambient(double n)
  {
    _ambient = n;
    return *this;
  }
  Material &Diffuse(double n)
  {
    _diffuse = n;
    return *this;
  }
  Material &Specular(double n)
  {
    _specular = n;
    return *this;
  }
  Material &Shininess(double n)
  {
    _shininess = n;
    return *this;
  }

  Material &Reflectivity(double n)
  {
    _reflectiveness = n;
    return *this;
  }

  Material &Transparency(double n)
  {
    _transparency = n;
    return *this;
  }
  Material &RefractiveIndex(double n)
  {
    _refractive_index = n;
    return *this;
  }

  // pass by unique ptr
  Material &SetPattern(std::unique_ptr<Pattern> pattern)
  {
    _pat = std::move(pattern);
    return *this;
  }

  Material &SetPattern(const Pattern * pattern)
  {
    _pat = std::move(pattern->clone());
    return *this;
  }


  ~Material() {_pat.reset();}
  const Pattern &GetPat() const { return *_pat; }
  double Ambient() const { return _ambient; }
  double Diffuse() const { return _diffuse; }
  double Specular() const { return _specular; }
  double Shininess() const { return _shininess; }
  double Reflectivity() const { return _reflectiveness; }
  double RefractiveIndex() const { return _refractive_index; }
  double Transparency() const { return _transparency; }
  friend std::ostream &operator<<(std::ostream &out, const Material &m);
  bool operator==(const Material &rhs) const
  {
    // todo(Me): Implement pattern compare
    return ( *_pat == *rhs._pat && float_equals(_ambient, rhs._ambient) &&
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
