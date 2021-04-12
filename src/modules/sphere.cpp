#include "sphere.h"
#include <cmath>
#include <vector>
#include "rays.h"
#include "shape.h"
#include "tuples.h"
namespace ray_lib
{

  std::vector<Intersection> Sphere::intersects(const Ray &r) const
  {
    std::vector<Intersection> results;
    Ray input_ray{r.Transform(Transform().inverse())};
    Vector sphere_to_ray{input_ray.Origin() - Point(0, 0, 0)};

    double a{input_ray.Direction().dotproduct(input_ray.Direction())};
    double b{input_ray.Direction().dotproduct(sphere_to_ray) * 2.0};
    double c{sphere_to_ray.dotproduct(sphere_to_ray) - 1.0};
    double descriminant{b * b - 4 * a * c};

    if (descriminant >= 0)
    {
      double t1 = (-b - sqrt(descriminant)) / (2 * a);
      double t2 = (-b + sqrt(descriminant)) / (2 * a);
      if (t1 > t2)
      {
        results.push_back(Intersection(reinterpret_cast<const Shape *>(this), t2));
        results.push_back(Intersection(reinterpret_cast<const Shape *>(this), t1));
      }
      else
      {
        results.push_back(Intersection(reinterpret_cast<const Shape *>(this), t1));
        results.push_back(Intersection(reinterpret_cast<const Shape *>(this), t2));
      }
    }
    return results;
  }

  const Vector Sphere::local_normal_at(const Point &position) const
  {
    Vector object_normal{position - Point(0, 0, 0)};
    object_normal.w(0);
    return object_normal.normalise();
  }

} // namespace ray_lib
