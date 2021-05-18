#ifndef _Plane_h
#define _Plane_h
#include <vector>
#include "shape.h"

namespace ray_lib {
class Plane : public Shape {
  Material _mat;

 public:
  Plane() : Shape(Matrix::Identity) {}
  explicit Plane(const Matrix &m) : Shape(m) {}
  std::vector<Intersection> intersects(const Ray &r) const;
  std::vector<Intersection> intersects(const Ray &r,const double tmin, const double tmax) const;
   bool intersects(const Ray &r, const double tmin, const double tmax,Intersection &rec) const;

  const Vector local_normal_at(const Point &position,const Intersection &i) const;
  const bool getBounds(Bounds *bounds)const;

};
}  // namespace ray_lib

#endif  //_Plane_h
