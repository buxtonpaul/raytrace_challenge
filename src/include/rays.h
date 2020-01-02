#ifndef _rays_h
#define _rays_h
#include <utility>
#include <vector>
#include "matrix.h"
#include "tuples.h"
#include "utils.h"

namespace ray_lib {

class Intersection;
class Shape;
class Ray {
 private:
  Point _origin;
  Vector _direction;

 public:
  Ray(Point origin, Vector direction)
      : _origin(origin), _direction(direction) {}
  Ray(const Ray &r) : _origin(r._origin), _direction(r._direction) {}

  friend std::ostream &operator<<(std::ostream &out, const Ray &r);
  Point Origin() const { return _origin; }
  Vector Direction() const { return _direction; }
  Point Position(double t) const { return _origin + _direction * t; }
  Ray Transform(const Matrix &transform_matrix) const {
    return Ray(transform_matrix * _origin, transform_matrix * _direction);
  }
};

class Intersection {
  Shape *_obj;
  double _t;

 public:
  Intersection(Shape *sp, const double t) : _obj(sp), _t(t) {}
  Intersection(const Intersection &i) : _obj(i._obj), _t(i._t) {}
  double t() const { return _t; }
  const Shape *GetShape() const { return _obj; }
  bool operator==(const Intersection &obj) const {
    return ((_obj == obj._obj) && (_t == obj._t));
  }
  bool operator<(const Intersection &obj) const { return (_t < obj._t); }
  static const Intersection *GetHit(
      const std::vector<Intersection> &intersections);
};  // namespace ray_lib

std::ostream &operator<<(std::ostream &out, const Intersection &i);

}  // namespace ray_lib

#endif
