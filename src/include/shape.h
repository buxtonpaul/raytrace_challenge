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
  const Vector normal(const Point &position)const
  {
    // transform the normal, then call local_normal_at
    // Transform().inverse() * position
    auto lp = world_to_object(position);
    auto ln = local_normal_at(lp);
    return normal_to_world(ln);

  }


  virtual const Vector local_normal_at(const Point &position) const = 0;

  const Matrix &Transform(const Matrix &m)
  {
    _m = m;
    return _m;
  }
  const Matrix &Transform() const { return _m; }
  Shape() : _m(Matrix::Identity) {}
  explicit Shape(const Matrix &m) : _m(m) {}
  const Material &material(const Material &m) {
    _material = m;
    return _material;
  }
  const Material &material() const { return _material; }
  Shape *parent(){return _parent;}
  const Shape &parent(Shape *p){
    _parent = p;
    return *this;
  }
  Point world_to_object(const Point&p)const{
    Point result(p);
    if (_parent)
    {
      result = _parent->world_to_object(p);
    }
    return (_m.inverse() * result);
  }
  const Vector normal_to_world(const Vector &objectnormal)const{
    Vector norm{_m.inverse().transpose()*objectnormal};
    norm.w(0);
    auto  a = norm.normalise();
    if (_parent)
    {
      return _parent->normal_to_world(a).normalise();
    }
    return a;
  }

protected:
  Matrix _m;
  Material _material;
  Shape *_parent = nullptr;
};
} // namespace ray_lib

#endif
