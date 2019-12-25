#ifndef _rays_h
#define _rays_h
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
  friend std::ostream &operator<<(std::ostream &out, const Ray &r);
  Point Origin() const { return _origin; }
  Vector Direction() const { return _direction; }
  Point Position(double t) const { return _origin + _direction * t; }
  Ray Transform(const Matrix &transform_matrix) const {
    return Ray(transform_matrix * _origin, transform_matrix * _direction);
  }
};

class Intersection {
  const Shape *_obj_ptr;
  const double _t;
  const Ray &_ray;  // we may not need this...
 public:
  Intersection(const Shape *ptr, const double t, const Ray &ray)
      : _obj_ptr(ptr), _t(t), _ray(ray) {}
  double t() const { return _t; }
  const Shape *GetShape() const { return _obj_ptr; }
  const Ray &GetRay() const { return _ray; }
  bool operator==(const Intersection &obj) const {
    return ((_obj_ptr == obj._obj_ptr) && (_t == obj._t) &&
            (&_ray == &obj._ray));
  }
  bool operator<(const Intersection &obj) const {
    if (_t < obj._t)
      return true;
    else
      return false;
  }
  static const Intersection *GetHit(
      const std::vector<Intersection> &intersections);
};

std::ostream &operator<<(std::ostream &out, const Intersection &i);

}  // namespace ray_lib

#endif
