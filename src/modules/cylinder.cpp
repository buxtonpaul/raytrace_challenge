#include "cylinder.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include "rays.h"
#include "shape.h"
#include "tuples.h"
namespace ray_lib
{

  // utility function to check if a ray is radius 1 from the y axis
  bool check_caps(const Ray &r, double t)
  {
    auto x{r.Origin().x() + (r.Direction().x() * t)};
    auto z{r.Origin().z() + (r.Direction().z() * t)};

    if (x*x + z*z > 1)
      return false;
    return true;
  }


  // this assymes the input ray has already been transformed
  void Cylinder::intersect_caps(std::vector<Intersection> &intersections, const Ray &r)const{
    if (!_capped || fabs(r.Direction().y()) < __FLT_EPSILON__)
      return;

    auto t0 {(_min-r.Origin().y()) / r.Direction().y()};
    if (check_caps(r, t0))
        intersections.push_back(Intersection(reinterpret_cast<const Shape *>(this), t0));

    auto t1 {(_max-r.Origin().y()) / r.Direction().y()};
    if (check_caps(r ,t1))
        intersections.push_back(Intersection(reinterpret_cast<const Shape *>(this), t1));


  }


  std::vector<Intersection> Cylinder::intersects(const Ray &r) const
  {
    Ray input_ray{r.Transform(Transform().inverse())};
    std::vector<Intersection> results;

    auto a{input_ray.Direction().x()*input_ray.Direction().x() + input_ray.Direction().z()*input_ray.Direction().z()};
    auto b{2.0*input_ray.Origin().x() * input_ray.Direction().x() +
        2.0*input_ray.Origin().z()*input_ray.Direction().z()};
    auto c{(input_ray.Origin().x()*input_ray.Origin().x() + input_ray.Origin().z()*input_ray.Origin().z()) -1.0 };

    auto disc{b*b - 4*a*c};

    std::cout << disc;
    if (disc >=0){
        auto t0 {(-b - sqrt(disc)) / (2*a)};
        auto t1 {(-b + sqrt(disc)) / (2*a)};

        if (t0 > t1){
          auto ttmp{t1};
          t1 = t0;
          t0 = ttmp;
        }

        auto y0{input_ray.Origin().y()+(t0*input_ray.Direction().y())};
        if ((y0 >_min) && (y0 <_max))
          results.push_back(Intersection(reinterpret_cast<const Shape *>(this), t0));

        auto y1{input_ray.Origin().y()+(t1*input_ray.Direction().y())};
        if ((y1 >_min) && (y1 <_max))
          results.push_back(Intersection(reinterpret_cast<const Shape *>(this), t1));

        intersect_caps(results, input_ray);
    }
    return results;
  }

  const Vector Cylinder::local_normal_at(const Point &position) const
  {
    // Point object_point{Transform().inverse() * position};
    Point object_point{position};
    auto dist{(object_point.x()*object_point.x()) + (object_point.z()*object_point.z())};

    if ((dist < 1) && (object_point.y() >= (_max - __DBL_EPSILON__) ))
      return Vector(0, 1, 0);

    if ((dist < 1) && (object_point.y() <= (_min + __DBL_EPSILON__) ))
      return Vector(0, -1, 0);

    return Vector{object_point.x(), 0, object_point.z()};
  }

} // namespace ray_lib
