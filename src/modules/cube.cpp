#include <cmath>
#include <vector>
#include <algorithm>
#include "rays.h"
#include "shape.h"
#include "tuples.h"
#include "cube.h"

namespace ray_lib
{


  std::vector<Intersection> Cube::intersects(const Ray &r) const
  {
    std::vector<Intersection> results;
    Ray input_ray { r.Transform(Transform().inverse())};

    std::pair<double, double> xAxis{check_axis(input_ray.Origin().x(), input_ray.Direction().x())};
    std::pair<double, double> yAxis{check_axis(input_ray.Origin().y(), input_ray.Direction().y())};
    std::pair<double, double> zAxis{check_axis(input_ray.Origin().z(), input_ray.Direction().z())};

    double mins[] = {xAxis.first, yAxis.first, zAxis.first};
    double maxs[] = {xAxis.second, yAxis.second, zAxis.second};
    double tmax{*std::min_element(maxs, maxs + 3)};
    double tmin{*std::max_element(mins, mins + 3)};

    if (tmin > tmax)
      return results;

    results.push_back(Intersection(reinterpret_cast<const Shape *>(this), tmin));
    results.push_back(Intersection(reinterpret_cast<const Shape *>(this), tmax));
    return results;
  }

  const Vector Cube::local_normal_at(const Point &position) const
  {
    // Point object_point{Transform().inverse() * position};
    Point object_point{position};

    double maxc[]{fabs(object_point.x()), fabs(object_point.y()), fabs(object_point.z())};

    double maxval = *std::max_element(maxc, maxc + 3);

    if (maxval == fabs(object_point.x()))
      return Vector(object_point.x(), 0, 0).normalise();
    if (maxval == fabs(object_point.y()))
      return Vector(0, object_point.y(), 0).normalise();
    return Vector(0, 0, object_point.z()).normalise();
  }

} // namespace ray_lib
