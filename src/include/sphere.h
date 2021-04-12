#ifndef _sphere_h
#define _sphere_h
#include <vector>
#include "material.h"
#include "rays.h"
#include "shape.h"
#include "tuples.h"

namespace ray_lib {
class Sphere : public Shape {

 public:
  Sphere() : Shape(Matrix::Identity) {}
  explicit Sphere(const Matrix &m) : Shape(m) {}
  std::vector<Intersection> intersects(const Ray &r) const;
  const Vector local_normal_at(const Point &position) const;

};
}  // namespace ray_lib

#endif  //_sphere_h
