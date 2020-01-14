#ifndef _rays_h
#define _rays_h
#include <utility>
#include <vector>
#include "matrix.h"
#include "shape.h"
#include "tuples.h"
#include "utils.h"

namespace ray_lib {
class Shape;
class Intersection;
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

/**
 * @brief Class to contain the precomputed values for an intersection with an
 * object.
 *
 */
class IntersectionState {
  double _t;
  const Shape *_object;
  Point _position;
  Vector _eye;
  Vector _normal = Vector(0, 0, 0);
  bool _inside;

 public:
  const Shape *Object() const { return _object; }
  const double t() const { return _t; }
  const Vector &Normal() const { return _normal; }
  const Vector &Eye() const { return _eye; }
  const Point &Position() const { return _position; }
  const bool Inside() const { return _inside; }

  // Constructor with all params
  IntersectionState(const Point &p, const Vector &eyev, const Vector &Normal,
                    double t, Shape *object)
      : _position(p), _eye(eyev), _normal(Normal), _t(t), _object(object) {
    initInside();
  }
  // constructor that will derive the normal from the shape, less
  // efficient if the normal has already been calculated elsewhere.

  IntersectionState(const Intersection &i, const Ray &r)
      : _t(i.t()),
        _object(i.GetShape()),
        _eye(-r.Direction()),
        _position(r.Position(_t)),
        _normal(_object->Normal(_position)) {
    initInside();
  }

 private:
  void initInside() {
    if (_normal.dotproduct(_eye) < 0.0) {
      _inside = true;
      _normal = -_normal;
    } else {
      _inside = false;
    }
  }
  // To get the normal we would call the shape with the position
};

}  // namespace ray_lib

#endif
