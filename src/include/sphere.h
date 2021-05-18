#ifndef _sphere_h
#define _sphere_h
#include <vector>
#include "shape.h"

namespace ray_lib
{
  class Sphere : public Shape
  {
  public:
    Sphere() : Shape(Matrix::Identity) {}
    explicit Sphere(const Matrix &m) : Shape(m) {}
    std::vector<Intersection> intersects(const Ray &r) const;
    std::vector<Intersection> intersects(const Ray &r, const double tmin, const double tmax) const;
    bool intersects(const Ray &r, const double tmin, const double tmax, Intersection &rec) const;

    const Vector local_normal_at(const Point &position, const Intersection &i) const;
    const bool getBounds(Bounds *bounds) const;

  private:
    bool calchit(const Ray &r, const double tmin, const double tmax, double &t0, double &t1) const;
  };
} // namespace ray_lib

#endif //_sphere_h
