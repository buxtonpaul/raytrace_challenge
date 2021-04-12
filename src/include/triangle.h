#ifndef _triangle_h
#define _triangle_h

#include <vector>
#include "material.h"
#include "rays.h"
#include "shape.h"
#include "tuples.h"

namespace ray_lib
{
class Triangle : public Shape
{
  Point _p1 = {0, 0, 0};
  Point _p2 = {1, 0, 0};
  Point _p3 = {0, 1, 0};
  Vector _e1{0, 0, 0};
  Vector _e2{1, 1, 1};
  Vector _normal{0, 0, 0};
  void compute_derived_vals(){
    _e1 = _p2-_p1;
    _e2 = _p3-_p1;
    _normal = _e2.crossproduct(_e1).normalise();
  }

public:
  Triangle(const Point &p1, const Point &p2, const Point &p3) : Shape(Matrix::Identity), _p1{p1}, _p2{p2}, _p3{p3}
  {
    compute_derived_vals();
  }
  explicit Triangle(const Matrix &m) : Shape(m) {}
  std::vector<Intersection> intersects(const Ray &r) const;
  const Vector local_normal_at(const Point &position) const;
  const Point p1()const {return _p1;}
  const Point p2()const {return _p2;}
  const Point p3()const {return _p3;}
  const Vector e1()const {return _e1;}
  const Vector e2()const {return _e2;}
  const Vector normal()const {return _normal;}
  const Vector normal(const Point &p2)const {return Shape::normal(p2);}

};
} // namespace ray_lib

#endif //_triangle_h
