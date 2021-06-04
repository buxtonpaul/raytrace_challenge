#ifndef _shape_h_
#define _shape_h_
#include <vector>
#include <memory>
#include "material.h"
#include "hittable.h"
#include "aabb.h"
#include "hittable_list.h"
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

class Shape : public Hittable, public std::enable_shared_from_this<const Hittable>
{
public:
  virtual const Vector local_normal_at(const Point &position, const Intersection &i) const = 0;
  virtual const bool getBounds(Bounds *bounds) const = 0;
  bool worldTransformisDirty()const;
  const Vector normal(const Point &position, const Intersection &i) const;
  const Vector normal(const Point &position) const;
  const Matrix &Transform(const Matrix &m);
  const Matrix &Transform() const;
  const Matrix &WorldTransform() const;
  Shape() : _m(Matrix::Identity) , _worldTransform(Matrix::Identity){}
  explicit Shape(const Matrix &m) : _m(m), _worldTransform(m) {}
  const Material &material(const Material &m);
  const Material &material() const;
  Shape *parent();
  const Shape &parent(Shape *p);
  Point world_to_object(const Point &p) const;
  const Vector normal_to_world(const Vector &objectnormal) const;
  bool bounding_box(aabb *output_box) const;
  std::shared_ptr<const Hittable> ptr()const{
    return std::static_pointer_cast<const Hittable>(shared_from_this());
  }
  virtual void addObjects(hittable_list *list) const;
protected:
  Matrix _m;
  Material _material;
  Shape *_parent = nullptr;
 mutable Matrix _worldTransform;
 mutable bool _isDirty = true;
};


} // namespace ray_lib

#endif
