#ifndef _cube_h
#define _cube_h
#include <vector>
#include "material.h"
#include "rays.h"
#include "shape.h"
#include "tuples.h"

namespace ray_lib {
class Cube : public Shape {

 public:
  Cube() : Cube(Matrix::Identity) {}
  explicit Cube(const Matrix &m) : Shape(m) {}
  std::vector<Intersection> intersects(const Ray &r) const;
    const Vector Normal(const Point &position) const;

};
}  // namespace ray_lib

#endif  //_cube_h
