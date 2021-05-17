#ifndef _cube_h
#define _cube_h
#include <vector>
#include "shape.h"

namespace ray_lib {
class Cube : public Shape {

 public:
  Cube() : Cube(Matrix::Identity) {}
  explicit Cube(const Matrix &m) : Shape(m) {}
  std::vector<Intersection> intersects(const Ray &r) const;
  const Vector local_normal_at(const Point &position,const Intersection &i) const;
  const void getBounds(Bounds *bounds)const;


};
}  // namespace ray_lib

#endif  //_cube_h
