#include "sphere.h"
#include <cmath>
#include <vector>
#include "rays.h"
namespace ray_lib
{

  std::vector<Intersection> Sphere::intersects(const Ray &r) const
  {
    return intersects(r, -INFINITY, INFINITY);
  }

  bool Sphere::calchit(const Ray &r, const double tmin, const double tmax, double &t0, double &t1) const
  {
    Ray input_ray{r.Transform(Transform().inverse())};
    Vector sphere_to_ray{input_ray.Origin() - Point(0, 0, 0)};

    double a{input_ray.Direction().dotproduct(input_ray.Direction())};
    double b{input_ray.Direction().dotproduct(sphere_to_ray) * 2.0};
    double c{sphere_to_ray.dotproduct(sphere_to_ray) - 1.0};
    double descriminant{b * b - 4 * a * c};

    if (descriminant < 0)
      return false;
    t0 = (-b - sqrt(descriminant)) / (2 * a);
    t1 = (-b + sqrt(descriminant)) / (2 * a);
    if (t0 > t1)
      std::swap(t0, t1);
    return true;
  }

  bool Sphere::intersects(const Ray &r, const double tmin, const double tmax, Intersection &rec) const
  {

    return false;
  }

  std::vector<Intersection> Sphere::intersects(const Ray &r, const double tmin, const double tmax) const
  {
    std::vector<Intersection> results;
    double t0, t1;
    if (calchit(r, tmin, tmax, t0, t1))
    {
      results.push_back(Intersection(reinterpret_cast<const Shape *>(this), t0));
      results.push_back(Intersection(reinterpret_cast<const Shape *>(this), t1));
    }
    return results;
  }

  const Vector Sphere::local_normal_at(const Point &position, const Intersection &i) const
  {
    Vector object_normal{position - Point(0, 0, 0)};
    object_normal.w(0);
    return object_normal.normalise();
  }

  const bool Sphere::getBounds(Bounds *bounds) const
  {
    bounds->mins.x(-1);
    bounds->mins.y(-1);
    bounds->mins.z(-1);
    bounds->maxs.x(1);
    bounds->maxs.y(1);
    bounds->maxs.z(1);
    return true;
  }

} // namespace ray_lib
