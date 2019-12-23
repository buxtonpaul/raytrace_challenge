#ifndef _sphere_h
#define _sphere_h
#include <vector>
#include "rays.h"
#include "tuples.h"
namespace ray_lib {
class Sphere : public Shape {
  Point _center;
  double _size;

 public:
  Sphere() : _center(0, 0, 0), _size(1) {}
  explicit Sphere(Point center, double size = 1.0)
      : _center(center), _size(size) {}
  std::vector<Intersection> intersects(const Ray &r) const;
};
};  // namespace ray_lib

#endif  //_sphere_h
