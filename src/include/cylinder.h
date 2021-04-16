#ifndef _cylinder_h
#define _cylinder_h
#include <vector>
#include "shape.h"

namespace ray_lib
{
  class Cylinder : public Shape
  {
  public:
    Cylinder() : Shape(Matrix::Identity) {}
    explicit Cylinder(const Matrix &m) : Shape(m) {}
    std::vector<Intersection> intersects(const Ray &r) const;
    const Vector local_normal_at(const Point &position) const;
    Cylinder(double min, double max) : Shape(Matrix::Identity), _min{min}, _max{max} {}
    Cylinder(double min, double max, bool capped) : Shape(Matrix::Identity), _min{min}, _max{max}, _capped{capped} {}
    Cylinder(double min, double max, const Matrix &m) : Shape(m), _min{min}, _max{max} {}
    Cylinder(double min, double max, bool capped, const Matrix &m) : Shape(m), _min{min}, _max{max}, _capped{capped} {}
    double min() const;
    double max() const;
    bool capped() const;
    Cylinder &min(double min);
    Cylinder &max(double max);
    Cylinder &capped(bool capped);

  private:
    double _min{-INFINITY};
    double _max{INFINITY};
    bool _capped = false;
    void intersect_caps(std::vector<Intersection> *intersections, const Ray &r) const;
  };
} // namespace ray_lib

#endif //_cylinder_h
