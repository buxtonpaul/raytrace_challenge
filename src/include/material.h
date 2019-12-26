#ifndef _material_h_
#define _material_h_
#include "color.h"
#include "utils.h"
namespace ray_lib {

class Material {
 protected:
  double _ambient;
  double _diffuse;
  double _specular;
  double _shininess;
  Color _color;

 public:
  Material(double a = 0.1, double d = 0.9, double spec = 0.9, double shin = 200,
           Color c = Color(1, 1, 1))
      : _ambient(a),
        _diffuse(d),
        _specular(spec),
        _shininess(shin),
        _color(c) {}

  double Ambient(double n) {
    _ambient = n;
    return n;
  }
  double Diffuse(double n) {
    _diffuse = n;
    return n;
  }
  double Specular(double n) {
    _specular = n;
    return n;
  }
  double Shininess(double n) {
    _shininess = n;
    return n;
  }
  Color SetColor(Color n) {
    _color = n;
    return n;
  }

  double Ambient() const { return _ambient; }
  double Diffuse() const { return _diffuse; }
  double Specular() const { return _specular; }
  double Shininess() const { return _shininess; }
  Color GetColor() const { return _color; }
  friend std::ostream &operator<<(std::ostream &out, const Material &m);
  bool operator==(const Material &rhs) const {
    return (_color == rhs._color && float_equals(_ambient, rhs._ambient) &&
            float_equals(_diffuse, rhs._diffuse) &&
            float_equals(_specular, rhs._specular) &&
            float_equals(_shininess, rhs._shininess));
  }
};

}  // namespace ray_lib

#endif
