#ifndef _cylinder_h
#define _cylinder_h
#include <vector>
#include "material.h"
#include "rays.h"
#include "shape.h"
#include "tuples.h"

namespace ray_lib {
class Cylinder : public Shape {

 public:
  Cylinder() : Shape(Matrix::Identity) {}
  explicit Cylinder(const Matrix &m) : Shape(m) {}
  std::vector<Intersection> intersects(const Ray &r) const;
    const Vector normal(const Point &position) const;
  Cylinder(double min, double max) : Shape(Matrix::Identity), _min{min}, _max{max} {}
  Cylinder(double min, double max, bool capped) : Shape(Matrix::Identity), _min{min}, _max{max}, _capped{capped} {}
  Cylinder(double min, double max, const Matrix &m) : Shape(m), _min{min}, _max{max} {}
  Cylinder(double min, double max, bool capped, const Matrix &m) : Shape(m), _min{min}, _max{max} , _capped{capped} {}
  double min()const {return _min;}
  double max()const {return _max;}
  bool capped()const {return _capped;}
  Cylinder & min(double min) {
    _min = min;
    return *this;
  }
  Cylinder & max(double max){
    _max = max;
    return *this;
  }

  Cylinder & capped(bool capped){
    _capped = capped;
    return *this;
  }

  private:
  double _min {-INFINITY};
  double _max {INFINITY};
  bool _capped = false;
  void intersect_caps(  std::vector<Intersection> &intersections, const Ray &r)const;
};
}  // namespace ray_lib

#endif  //_cylinder_h
