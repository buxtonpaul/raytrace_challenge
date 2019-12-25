#ifndef _sphere_h
#define _sphere_h
#include <vector>
#include "rays.h"
#include "shape.h"
#include "tuples.h"

namespace ray_lib {
class Sphere : public Shape {
  Matrix _m;

 public:
  Sphere() : _m(Matrix::Identity) {}
  explicit Sphere(const Matrix &m) : _m(m) {}
  std::vector<Intersection> intersects(const Ray &r) const;
  const Matrix &Transform(const Matrix &m) {
    _m = m;
    return _m;
  }
  const Matrix &Transform() const { return _m; }
  const Vector Normal(const Point &position) const;
};
}  // namespace ray_lib

#endif  //_sphere_h
