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

  typedef struct _Bounds_
  {
    Point mins{INFINITY, INFINITY, INFINITY};
    Point maxs{-INFINITY, -INFINITY, -INFINITY};
  } Bounds;

  class Shape
  {
  public:
    virtual std::vector<Intersection> intersects(const Ray &r) const = 0;
    virtual const Vector local_normal_at(const Point &position) const = 0;
    virtual const void getBounds(Bounds *bounds) const = 0;
    const Vector normal(const Point &position) const;
    const Matrix &Transform(const Matrix &m);
    const Matrix &Transform() const;
    Shape() : _m(Matrix::Identity) {}
    explicit Shape(const Matrix &m) : _m(m) {}
    const Material &material(const Material &m);
    const Material &material() const;
    Shape *parent();
    const Shape &parent(Shape *p);
    Point world_to_object(const Point &p) const;
    const Vector normal_to_world(const Vector &objectnormal) const;

  protected:
    Matrix _m;
    Material _material;
    Shape *_parent = nullptr;
  };
} // namespace ray_lib

#endif
