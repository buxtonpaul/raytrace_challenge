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
    Material(const double a, const double d, const double spec, const double shin,
      const double reflectiveness, const double transparency, const double ri, const Pattern &inpat);

    explicit Material(const Pattern &inpat);

    Material(const Material &other);

    Material operator=(const Material &other);

    Material(Material &&other);

    Material() {}
    Material &ambient(double n);
    Material &diffuse(double n);
    Material &specular(double n);
    Material &shininess(double n);

    Material &reflectivity(double n);

    Material &transparency(double n);
    Material &refractive_index(double n);

    // pass by unique ptr
    Material &pattern(std::unique_ptr<Pattern> pattern);
    Material &pattern(const Pattern &pattern);

    ~Material();
    const Pattern &pattern() const;
    double ambient() const;
    double diffuse() const;
    double specular() const;
    double shininess() const;
    double reflectivity() const;
    double refractive_index() const;
    double transparency() const;
    friend std::ostream &operator<<(std::ostream &out, const Material &m);
    bool operator==(const Material &rhs) const;
  };

  extern Material glass;
} // namespace ray_lib

#endif
