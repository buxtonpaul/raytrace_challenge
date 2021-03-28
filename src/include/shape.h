#ifndef _shape_h_
#define _shape_h_
#include <vector>
namespace ray_lib
{

class Ray;
class Intersection;
class Material;
class Vector;
class Matrix;

class Shape
{
public:
  virtual std::vector<Intersection> intersects(const Ray &r) const = 0;
  virtual const Material &Mat() const = 0;
  virtual const Material &Mat(const Material &m) = 0;
  virtual const Vector Normal(const Point &position) const = 0;

  const Matrix &Transform(const Matrix &m)
  {
    _m = m;
    return _m;
  }
  const Matrix &Transform() const { return _m; }
  Shape() : _m(Matrix::Identity) {}
  Shape(const Matrix &m) : _m(m) {}

protected:
  Matrix _m;
};
} // namespace ray_lib

#endif
