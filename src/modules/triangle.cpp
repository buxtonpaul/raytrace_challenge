#include <vector>
#include "rays.h"
#include "triangle.h"

namespace ray_lib
{

  std::vector<Intersection> Triangle::intersects(const Ray &r) const
  {
    return intersects(r, -INFINITY, INFINITY);
  }

  bool Triangle::intersects(const Ray &r, const double tmin, const double tmax, Intersection *rec) const
  {
    Ray input_ray{r.Transform(Transform().inverse())};

    auto dir_cross_e2{input_ray.Direction().crossproduct(_e2)};
    double det{_e1.dotproduct(dir_cross_e2)};
    if (fabs(det) < __FLT_EPSILON__)
      return false;

    auto f{1.0 / det};
    auto p1_to_origin{input_ray.Origin() - _p1};
    auto u{f * p1_to_origin.dotproduct(dir_cross_e2)};

    if ((u < 0) || (u > 1))
      return false;

    auto origin_cross_e1{p1_to_origin.crossproduct(_e1)};
    auto v{f * input_ray.Direction().dotproduct(origin_cross_e1)};

    if ((v < 0) || ((u + v) > 1))
      return false;
    auto t{f * _e2.dotproduct(origin_cross_e1)};

    *rec = Intersection(reinterpret_cast<const Shape *>(this), t);

    return true;
  }

  std::vector<Intersection> Triangle::intersects(const Ray &r, const double tmin, const double tmax) const
  {
    std::vector<Intersection> results;
    Intersection rec(nullptr, 0);
    if (intersects(r, tmin, tmax, &rec))
      results.push_back(rec);
    return results;
  }

  const Vector Triangle::local_normal_at(const Point &position, const Intersection &i) const
  {
    return _normal;
  }

  void Triangle::compute_derived_vals()
  {
    _e1 = _p2 - _p1;
    _e2 = _p3 - _p1;
    _normal = _e2.crossproduct(_e1).normalise();
  }

  const bool Triangle::getBounds(Bounds *bounds) const
  {
    Point mins = {INFINITY, INFINITY, INFINITY};
    Point maxs = {-INFINITY, -INFINITY, -INFINITY};

    for (auto a : std::vector<Point>{_p1, _p2, _p3})
    {
      if (a.x() < mins.x())
        mins.x(a.x());
      if (a.x() > maxs.x())
        maxs.x(a.x());

      if (a.y() < mins.y())
        mins.y(a.y());
      if (a.y() > maxs.y())
        maxs.y(a.y());

      if (a.z() < mins.z())
        mins.z(a.z());
      if (a.z() > maxs.z())
        maxs.z(a.z());
    }
    bounds->mins = mins;
    bounds->maxs = maxs;
    return true;
  }

  const Point Triangle::p1() const { return _p1; }
  const Point Triangle::p2() const { return _p2; }
  const Point Triangle::p3() const { return _p3; }
  const Vector Triangle::e1() const { return _e1; }
  const Vector Triangle::e2() const { return _e2; }
  const Vector Triangle::normal() const { return _normal; }
  const Vector Triangle::normal(const Point &p2) const { return Shape::normal(p2); }

  std::vector<Intersection> SmoothTriangle::intersects(const Ray &r) const
  {
    return intersects(r, -INFINITY, INFINITY);
  }

  bool SmoothTriangle::intersects(const Ray &r, const double tmin, const double tmax, Intersection *rec) const
  {
    Ray input_ray{r.Transform(Transform().inverse())};

    auto dir_cross_e2{input_ray.Direction().crossproduct(_e2)};
    double det{_e1.dotproduct(dir_cross_e2)};
    if (fabs(det) < __FLT_EPSILON__)
      return false;

    auto f{1.0 / det};
    auto p1_to_origin{input_ray.Origin() - _p1};
    auto u{f * p1_to_origin.dotproduct(dir_cross_e2)};

    if ((u < 0) || (u > 1))
      return false;

    auto origin_cross_e1{p1_to_origin.crossproduct(_e1)};
    auto v{f * input_ray.Direction().dotproduct(origin_cross_e1)};

    if ((v < 0) || ((u + v) > 1))
      return false;
    auto t{f * _e2.dotproduct(origin_cross_e1)};

    *rec = Intersection(reinterpret_cast<const Shape *>(this), t, u, v);

    return true;
  }

  std::vector<Intersection> SmoothTriangle::intersects(const Ray &r, const double tmin, const double tmax) const
  {
    std::vector<Intersection> results;
    Intersection rec(nullptr, 0);
    if (intersects(r, tmin, tmax, &rec))
      results.push_back(rec);
    return results;
  }

  const Vector SmoothTriangle::local_normal_at(const Point &position, const Intersection &i) const
  {
    return (_n2 * i.u() + _n3 * i.v() + _n1 * (1 - i.u() - i.v())).normalise();
  }

  void SmoothTriangle::compute_derived_vals()
  {
    _e1 = _p2 - _p1;
    _e2 = _p3 - _p1;
    // _normal = _e2.crossproduct(_e1).normalise();
  }

  const bool SmoothTriangle::getBounds(Bounds *bounds) const
  {
    Point mins = {INFINITY, INFINITY, INFINITY};
    Point maxs = {-INFINITY, -INFINITY, -INFINITY};

    for (auto a : std::vector<Point>{_p1, _p2, _p3})
    {
      if (a.x() < mins.x())
        mins.x(a.x());
      if (a.x() > maxs.x())
        maxs.x(a.x());

      if (a.y() < mins.y())
        mins.y(a.y());
      if (a.y() > maxs.y())
        maxs.y(a.y());

      if (a.z() < mins.z())
        mins.z(a.z());
      if (a.z() > maxs.z())
        maxs.z(a.z());
    }
    bounds->mins = mins;
    bounds->maxs = maxs;
    return true;
  }

  const Point SmoothTriangle::p1() const { return _p1; }
  const Point SmoothTriangle::p2() const { return _p2; }
  const Point SmoothTriangle::p3() const { return _p3; }
  const Vector SmoothTriangle::n1() const { return _n1; }
  const Vector SmoothTriangle::n2() const { return _n2; }
  const Vector SmoothTriangle::n3() const { return _n3; }
  const Vector SmoothTriangle::e1() const { return _e1; }
  const Vector SmoothTriangle::e2() const { return _e2; }

} // namespace ray_lib
