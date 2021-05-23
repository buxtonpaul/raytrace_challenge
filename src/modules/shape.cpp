#include "shape.h"
#include "rays.h"
namespace ray_lib
{

  const Vector Shape::normal(const Point &position, const Intersection &i) const
  {
    // transform the normal, then call local_normal_at
    // Transform().inverse() * position
    auto lp = world_to_object(position);
    auto ln = local_normal_at(lp, i);
    return normal_to_world(ln);
  }

  const Vector Shape::normal(const Point &position) const
  {
    // transform the normal, then call local_normal_at
    // Transform().inverse() * position
    Intersection i{this, 0, 0, 0};
    auto lp = world_to_object(position);
    auto ln = local_normal_at(lp, i);
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

  bool Shape::bounding_box(aabb *output_box) const
  {
    Bounds p;
    if (!getBounds(&p))
      return false;
    Shape const *ancestor = this;
    do
    {
      p.maxs = ancestor->_m * p.maxs;
      p.mins = ancestor->_m * p.mins;
      ancestor = ancestor->_parent;
    } while (ancestor);

    // we should now turn this into axis aligned points in case the min/max have moved as a result of transformation
    for (int a = 0; a < 3; ++a)
    {
      if (p.mins[a] > p.maxs.x())
      {
        auto tmp = p.mins[a];
        p.mins[a]=(p.maxs[a]);
        p.maxs[a]=(tmp);
      }
    }

    return true;
  }

}