#ifndef _group_h
#define _group_h
#include <vector>
#include "material.h"
#include "rays.h"
#include "shape.h"
#include "tuples.h"
#include "utils.h"

namespace ray_lib {
class Group : public Shape {

 public:
  Group() : Group(Matrix::Identity) {}
  explicit Group(const Matrix &m) : Shape(m) {}
  std::vector<Intersection> intersects(const Ray &r) const;
  const Vector local_normal_at(const Point &position) const
  {
    return {0,0,0};
  }

  bool isEmpty()const {return ( _children.size() == 0);}
  const Group& add_child(Shape *s){
    _children.push_back(s);
    s->parent(this);
  }
  bool includes(const Shape *s)const{
    return contains(_children,s);
  }
  private:
    std::vector<ray_lib::Shape const *> _children;
};
}  // namespace ray_lib

#endif  //_group_h
