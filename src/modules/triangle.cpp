#include <vector>
#include "rays.h"
#include "triangle.h"

namespace ray_lib
{

  std::vector<Intersection> Triangle::intersects(const Ray &r) const
  {
    std::vector<Intersection> results;

    Ray input_ray{r.Transform(Transform().inverse())};

    auto dir_cross_e2{input_ray.Direction().crossproduct(_e2)};
    double det{_e1.dotproduct(dir_cross_e2)};
    if (fabs(det) < __FLT_EPSILON__)
      return results;

    auto f{1.0 / det};
    auto p1_to_origin{input_ray.Origin() - _p1};
    auto u{f * p1_to_origin.dotproduct(dir_cross_e2)};

    if ((u < 0) || (u > 1))
      return results;

    auto origin_cross_e1{p1_to_origin.crossproduct(_e1)};
    auto v{f * input_ray.Direction().dotproduct(origin_cross_e1)};

    if ((v < 0) || ((u + v) > 1))
      return results;
    auto t{f * _e2.dotproduct(origin_cross_e1)};
    results.push_back(Intersection(reinterpret_cast<const Shape *>(this), t));

    return results;
  }

  const Vector Triangle::local_normal_at(const Point &position) const
  {
    return _normal;
  }

  void Triangle::compute_derived_vals()
  {
    _e1 = _p2 - _p1;
    _e2 = _p3 - _p1;
    _normal = _e2.crossproduct(_e1).normalise();
  }

  const void Triangle::getBounds(Bounds *bounds) const
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
  }

  const Point Triangle::p1() const { return _p1; }
  const Point Triangle::p2() const { return _p2; }
  const Point Triangle::p3() const { return _p3; }
  const Vector Triangle::e1() const { return _e1; }
  const Vector Triangle::e2() const { return _e2; }
  const Vector Triangle::normal() const { return _normal; }
  const Vector Triangle::normal(const Point &p2) const { return Shape::normal(p2); }

} // namespace ray_lib
