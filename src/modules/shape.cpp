#include<memory>
#include "shape.h"
#include "rays.h"
#include "hittable_list.h"
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
    _worldTransform = _m;
    _isDirty = true;
    return _m;
  }
  const Matrix &Shape::Transform() const
  {
    return _m;
  }


   bool Shape::worldTransformisDirty()const {
    if (_isDirty)
      return true;
    if (_parent)
      return _parent->worldTransformisDirty();
    return false;

  }
  const Matrix &Shape::WorldTransform() const
  {
    if (worldTransformisDirty()){
      if(_parent)
        _worldTransform = _parent->WorldTransform()*_m;
      else
        _worldTransform = _m;
      _isDirty = false;
    }
    return _worldTransform;
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
    return (WorldTransform().inverse() * p);
  }

  const Vector Shape::normal_to_world(const Vector &objectnormal) const
  {
    Vector norm{WorldTransform().inverse().transpose() * objectnormal};
    norm.w(0);
    auto a = norm.normalise();
    return a;
  }

  bool Shape::bounding_box(aabb *output_box) const
  {
    Bounds p;
    if (!getBounds(&p))
      return false;
    
    p.maxs = WorldTransform() * p.maxs;
    p.mins = WorldTransform() * p.mins;
    // we should now turn this into axis aligned points in case the min/max have moved as a result of transformation
    for (int a = 0; a < 3; ++a)
    {
      if (p.mins[a] > p.maxs[a])
      {
        auto tmp = p.mins[a];
        p.mins[a]=(p.maxs[a]);
        p.maxs[a]=(tmp);
      }
    }
    output_box->minimum = p.mins;
    output_box->maximum = p.maxs;
    return true;
  }
  void Shape::addObjects(hittable_list *list) const
  {
    list->objects.push_back(ptr());
  }
}// namespace ray_lib
