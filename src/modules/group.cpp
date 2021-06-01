#include <vector>
#include "rays.h"
#include "group.h"
#include "hittable_list.h"

namespace ray_lib
{

std::vector<Intersection> Group::intersects(const Ray &r) const
  {
    return intersects(r, -INFINITY, INFINITY);
  }

  bool Group::intersects(const Ray &r, const double tmin, const double tmax, Intersection *rec) const
  {
    // todo: implement this
    return false;
  }

  std::vector<Intersection> Group::intersects(const Ray &r, const double tmin, const double tmax) const
  {
    aabb target;
    bounding_box(&target);
    std::vector<Intersection> results;
    if (!_box.hit(r, tmin, tmax))
      return results;

    for (auto child : _children)
    {
      auto tmp = child->intersects(r);
      std::move(tmp.begin(), tmp.end(), std::back_inserter(results));
    }
    std::sort(results.begin(), results.end());

    return results;
  }

  const Vector Group::local_normal_at(const Point &position, const Intersection &i) const
  {
    return {0, 0, 0};
  }

  bool Group::isEmpty() const
  {
    return (_children.size() == 0);
  }

  const Group &Group::add_child(Shape *s)
  {
    _children.push_back(s);
    s->parent(this);

    _dirty = true;
    if (_parent)
    {
      if (typeid(_parent) == typeid(Group))
      static_cast<Group*>(_parent)->isDirty();
    }
  }

  bool Group::includes(const Shape *s) const
  {
    return contains(_children, s);
  }

  Shape const *Group::at(int index)
  {
    if (index < _children.size())
      return _children[index];
    return nullptr;
  }

  bool Group::isDirty(){
    _dirty = true;
  }

  bool Group::bounding_box(aabb *output_box) const
  {
    aabb tempbox;
    if (_dirty){
      for (auto a : _children){
        aabb childbox;
        a->bounding_box(&childbox);
        tempbox = surrounding_box(childbox, tempbox);
      }
      _dirty = false;
      _box = tempbox;
    }
    *output_box = _box;
  }
  const bool Group::getBounds(Bounds *bounds) const
  {
    // Bounds localounds = {{INFINITY, INFINITY, INFINITY}, {INFINITY * -1, INFINITY * -1, INFINITY * -1}};
    // Bounds _bounds = {{INFINITY, INFINITY, INFINITY}, {INFINITY * -1, INFINITY * -1, INFINITY * -1}};
    // if(_dirty)
    // {
    //   for(auto a : _children)
    //   {
    //       a->getBounds(&localounds);


    //       localounds.mins  = (a->WorldTransform()*localounds.mins);
    //       localounds.maxs  = (a->WorldTransform()*localounds.maxs);


    //       if (localounds.mins.x() < _bounds.mins.x())
    //         _bounds.mins.x(localounds.mins.x());
    //       if (localounds.mins.y() < _bounds.mins.y())
    //         _bounds.mins.y(localounds.mins.y());
    //       if (localounds.mins.z() < _bounds.mins.z())
    //         _bounds.mins.z(localounds.mins.z());

    //       if (localounds.maxs.x() > _bounds.maxs.x())
    //         _bounds.maxs.x(localounds.maxs.x());
    //       if (localounds.maxs.y() > _bounds.maxs.y())
    //         _bounds.maxs.y(localounds.maxs.y());
    //       if (localounds.maxs.z() > _bounds.maxs.z())
    //         _bounds.maxs.z(localounds.maxs.z());

    //   }
    
    

    // }



    *bounds = _bounds;
    return true;
  }
  void Group::addObjects(hittable_list *list)const
  {
    for (auto a : _children)
      a->addObjects(list);
  }
} // namespace ray_lib

