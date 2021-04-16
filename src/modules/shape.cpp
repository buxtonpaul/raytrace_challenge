#include "shape.h"

namespace ray_lib
{

  const Vector Shape::normal(const Point &position) const
  {
    // transform the normal, then call local_normal_at
    // Transform().inverse() * position
    auto lp = world_to_object(position);
    auto ln = local_normal_at(lp);
    return normal_to_world(ln);
  }

  const Matrix &Shape::Transform(const Matrix &m)
  {
    _m = m;
    return _m;
  }
  const Matrix &Shape::Transform() const
  {
    return _m;
  }
  const Material &Shape::material(const Material &m)
  {
    _material = m;
    return _material;
  }

  const Material &Shape::material() const
  {
    return _material;
  }

  Shape *Shape::parent() { return _parent; }
  const Shape &Shape::parent(Shape *p)
  {
    _parent = p;
    return *this;
  }

  Point Shape::world_to_object(const Point &p) const
  {
    Point result(p);
    if (_parent)
    {
      result = _parent->world_to_object(p);
    }
    return (_m.inverse() * result);
  }
  const Vector Shape::normal_to_world(const Vector &objectnormal) const
  {
    Vector norm{_m.inverse().transpose() * objectnormal};
    norm.w(0);
    auto a = norm.normalise();
    if (_parent)
    {
      return _parent->normal_to_world(a).normalise();
    }
    return a;
  }

}