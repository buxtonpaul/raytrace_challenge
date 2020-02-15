#ifndef _Plane_h
#define _Plane_h
#include <vector>
#include "material.h"
#include "rays.h"
#include "shape.h"
#include "tuples.h"

namespace ray_lib {
class Plane : public Shape {
  Matrix _m;
  Material _mat;

 public:
  Plane() : _m(Matrix::Identity) {}
  explicit Plane(const Matrix &m) : _m(m) {}
  std::vector<Intersection> intersects(const Ray &r) const;
  const Matrix &Transform(const Matrix &m) {
    _m = m;
    return _m;
  }
  const Matrix &Transform() const { return _m; }
  const Vector Normal(const Point &position) const;
  const Material &Mat(const Material m) {
    _mat = m;
    return _mat;
  }
  const Material &Mat() const { return _mat; }
};
}  // namespace ray_lib

#endif  //_Plane_h
