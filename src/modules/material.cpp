#include "material.h"
#include <iostream>

namespace ray_lib
{
  SolidPattern SolidWhite(Color::White);
  std::ostream &operator<<(std::ostream &out, const Material &m)
  {
    out << "( ";
    // out << "Color = " << m._color << std::endl;
    out << "Ambient = " << m._ambient << std::endl;
    out << "Diffuse = " << m._diffuse << std::endl;
    out << "Specular= " << m._specular << std::endl;
    out << "Reflectiveness= " << m._reflectiveness << std::endl;
    out << "Shininess" << m._shininess << " )" << std::endl;
    return out;
  }

  Material::Material(const double a, const double d, const double spec, const double shin,
                     const double reflectiveness, const double transparency, const double ri, const Pattern &inpat)
      : _ambient{a},
        _diffuse{d},
        _specular{spec},
        _shininess{shin},
        _reflectiveness{reflectiveness},
        _transparency{transparency},
        _refractive_index{ri}

  {
    _pat = inpat.clone();
  }

  Material::Material(const Pattern &inpat)
  {
    _pat = inpat.clone();
  }

  Material::Material(const Material &other)
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

  Material Material::operator=(const Material &other)
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

  Material::Material(Material &&other)
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

  Material &Material::ambient(double n)
  {
    _ambient = n;
    return *this;
  }
  Material &Material::diffuse(double n)
  {
    _diffuse = n;
    return *this;
  }
  Material &Material::specular(double n)
  {
    _specular = n;
    return *this;
  }
  Material &Material::shininess(double n)
  {
    _shininess = n;
    return *this;
  }

  Material &Material::reflectivity(double n)
  {
    _reflectiveness = n;
    return *this;
  }

  Material &Material::transparency(double n)
  {
    _transparency = n;
    return *this;
  }
  Material &Material::refractive_index(double n)
  {
    _refractive_index = n;
    return *this;
  }

  // pass by unique ptr
  Material &Material::pattern(std::unique_ptr<Pattern> pattern)
  {
    _pat = std::move(pattern);
    return *this;
  }

  Material &Material::pattern(const Pattern &pattern)
  {
    _pat = std::move(pattern.clone());
    return *this;
  }

  Material::~Material() { _pat.reset(); }

  const Pattern &Material::pattern() const { return *_pat; }
  double Material::ambient() const { return _ambient; }
  double Material::diffuse() const { return _diffuse; }
  double Material::specular() const { return _specular; }
  double Material::shininess() const { return _shininess; }
  double Material::reflectivity() const { return _reflectiveness; }
  double Material::refractive_index() const { return _refractive_index; }
  double Material::transparency() const { return _transparency; }
  bool Material::operator==(const Material &rhs) const
  {
    // todo(Me): Implement pattern compare
    return (*_pat == *rhs._pat && float_equals(_ambient, rhs._ambient) &&
            float_equals(_diffuse, rhs._diffuse) &&
            float_equals(_specular, rhs._specular) &&
            float_equals(_transparency, rhs._transparency) &&
            float_equals(_refractive_index, rhs._refractive_index) &&
            float_equals(_reflectiveness, rhs._reflectiveness) &&
            float_equals(_shininess, rhs._shininess));
  }
  ray_lib::Material glass = Material().transparency(1).refractive_index(1.5);

} // namespace ray_lib
