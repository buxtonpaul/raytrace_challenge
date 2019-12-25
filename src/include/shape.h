#ifndef _shape_h_
#define _shape_h_

namespace ray_lib{

class Shape {
 public:
  virtual std::vector<Intersection> intersects(const Ray &r) const = 0;
  virtual const Matrix &Transform(const Matrix &m) = 0;
  virtual const Matrix &Transform() const = 0;
};
}

#endif
