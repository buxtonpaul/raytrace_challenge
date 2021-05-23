#include <vector>
#include "rays.h"
#include "group.h"

namespace ray_lib
{

std::vector<Intersection> Group::intersects(const Ray &r) const
  {
    return intersects(r,-INFINITY,INFINITY);
  }

  bool Group::intersects(const Ray &r, const double tmin, const double tmax, Intersection *rec) const
  {
    

    return false;
  }

  std::vector<Intersection> Group::intersects(const Ray &r,const double tmin, const double tmax) const
  {
    std::vector<Intersection> results;
    Ray input_ray{r.Transform(Transform().inverse())};

    // given the bounds we  need to compute the bounding box for it
    std::pair<double, double> xAxis{check_axis(input_ray.Origin().x(), input_ray.Direction().x(), _bounds.mins.x(),_bounds.maxs.x())};
    std::pair<double, double> yAxis{check_axis(input_ray.Origin().y(), input_ray.Direction().y(), _bounds.mins.y(),_bounds.maxs.y())};
    std::pair<double, double> zAxis{check_axis(input_ray.Origin().z(), input_ray.Direction().z(), _bounds.mins.z(),_bounds.maxs.z())};

    double mins[] = {xAxis.first, yAxis.first, zAxis.first};
    double maxs[] = {xAxis.second, yAxis.second, zAxis.second};
    double t_max{*std::min_element(maxs, maxs + 3)};
    double t_min{*std::max_element(mins, mins + 3)};

    if (t_min > t_max){
      // std::cout<<" skipping group" <<std::endl;
      return results;
    }

    for (auto child : _children)
    {
      auto tmp = child->intersects(input_ray);
      std::move(tmp.begin(), tmp.end(), std::back_inserter(results));
    }
    std::sort(results.begin(), results.end());

    return results;
  }

  const Vector Group::local_normal_at(const Point &position,const Intersection &i) const
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

    Bounds childBounds = {{INFINITY, INFINITY, INFINITY}, {INFINITY * -1, INFINITY * -1, INFINITY * -1}};
    s->getBounds(&childBounds);



    // we shouldnot class things as min/max at this point! as the transform could completly reverse it!
    // we should turn this into all 8 corners, 
    // transform these and get the bounding box from that.
    /*
    something like
    c1 = childBounds.mins.x,childBounds.mins.y,childBounds.mins.z  *s->transofrm
    c2 = childBounds.mins.x,childBounds.maxs.y,childBounds.mins.z  *s->transofrm
    c3 = childBounds.mins.x,childBounds.mins.y,childBounds.maxs.z  *s->transofrm
    c4 = childBounds.mins.x,childBounds.maxs.y,childBounds.maxs.z  *s->transofrm
    c5 = childBounds.maxs.x,childBounds.mins.y,childBounds.mins.z  *s->transofrm
    c6 = childBounds.maxs.x,childBounds.maxs.y,childBounds.mins.z  *s->transofrm
    c7 = childBounds.maxs.x,childBounds.mins.y,childBounds.maxs.z  *s->transofrm
    c8 = childBounds.maxs.x,childBounds.maxs.y,childBounds.maxs.z  *s->transofrm

    // then find min x,y,x and max x,y,z in c1->c8
    

    // in order to allow groups to be transformed we ought to cache the data, dirty it if it changes
    // 
    */
    childBounds.mins  = (s->Transform()*childBounds.mins);
    childBounds.maxs  = (s->Transform()*childBounds.maxs);

    // at this point we have a traansformed bounding box defined by two transformed corners, which is no longer axis aligned.
    // to turn it into a AABB, we will need to 

    if (childBounds.mins.x() < _bounds.mins.x())
      _bounds.mins.x(childBounds.mins.x());
    if (childBounds.mins.y() < _bounds.mins.y())
      _bounds.mins.y(childBounds.mins.y());
    if (childBounds.mins.z() < _bounds.mins.z())
      _bounds.mins.z(childBounds.mins.z());

    if (childBounds.maxs.x() > _bounds.maxs.x())
      _bounds.maxs.x(childBounds.maxs.x());
    if (childBounds.maxs.y() > _bounds.maxs.y())
      _bounds.maxs.y(childBounds.maxs.y());
    if (childBounds.maxs.z() > _bounds.maxs.z())
      _bounds.maxs.z(childBounds.maxs.z());
    
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
  const bool Group::getBounds(Bounds *bounds) const
  {
    *bounds = _bounds;
    return true;
  }

 
} // namespace ray_lib
