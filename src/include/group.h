#ifndef _group_h
#define _group_h
#include <vector>
#include "material.h"
#include "rays.h"
#include "shape.h"
#include "tuples.h"
#include "utils.h"

namespace ray_lib
{
  class Group : public Shape
  {

  public:
    Group() : Group(Matrix::Identity) {}
    explicit Group(const Matrix &m) : Shape(m) {}
    std::vector<Intersection> intersects(const Ray &r) const;
    const Vector local_normal_at(const Point &position) const;

    bool isEmpty() const;
    const Group &add_child(Shape *s);
    bool includes(const Shape *s) const;

  private:
    std::vector<ray_lib::Shape const *> _children;
  };
} // namespace ray_lib

#endif //_group_h
