#ifndef _sphere_h
#define _sphere_h
#include <vector>
#include "material.h"
#include "rays.h"
#include "shape.h"
#include "tuples.h"

namespace ray_lib {
class Sphere : public Shape {
  Material _mat;

 public:
  Sphere() : Shape(Matrix::Identity) {}
  explicit Sphere(const Matrix &m) : Shape(m) {}
  std::vector<Intersection> intersects(const Ray &r) const;
    const Vector Normal(const Point &position) const;

  const Material &Mat(const Material &m) {
    _mat = m;
    return _mat;
  }
  const Material &Mat() const { return _mat; }
};
}  // namespace ray_lib

#endif  //_sphere_h
