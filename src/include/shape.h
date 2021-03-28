#ifndef _shape_h_
#define _shape_h_
#include <vector>
#include "material.h"
namespace ray_lib
{

class Ray;
class Intersection;
class Vector;
class Matrix;

class Shape
{
public:
  virtual std::vector<Intersection> intersects(const Ray &r) const = 0;
  virtual const Vector Normal(const Point &position) const = 0;

  const Matrix &Transform(const Matrix &m)
  {
    _m = m;
    return _m;
  }
  const Matrix &Transform() const { return _m; }
  Shape() : _m(Matrix::Identity) {}
  explicit Shape(const Matrix &m) : _m(m) {}
  const Material &Mat(const Material &m) {
    _mat = m;
    return _mat;
  }
  const Material &Mat() const { return _mat; }

protected:
  Matrix _m;
  Material _mat;

};
} // namespace ray_lib

#endif
