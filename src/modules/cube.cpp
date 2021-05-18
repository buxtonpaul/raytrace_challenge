#include "rays.h"
#include "cube.h"

namespace ray_lib
{


  std::vector<Intersection> Cube::intersects(const Ray &r) const
  {
    return intersects(r, -INFINITY, INFINITY);
  }
  std::vector<Intersection> Cube::intersects(const Ray &r, const double tmin, const double tmax) const
  {
    std::vector<Intersection> results;
    double t1, t0;
    calchit(r, t0, t1);

    if (t0 > t1)
      return results;

    results.push_back(Intersection(reinterpret_cast<const Shape *>(this), t0));
    results.push_back(Intersection(reinterpret_cast<const Shape *>(this), t1));
    return results;
  }

  void Cube::calchit(const Ray &r, double &t0, double &t1)const
  {
    Ray input_ray { r.Transform(Transform().inverse())};

    std::pair<double, double> xAxis{check_axis(input_ray.Origin().x(), input_ray.Direction().x(), -1, 1)};
    std::pair<double, double> yAxis{check_axis(input_ray.Origin().y(), input_ray.Direction().y(), -1, 1)};
    std::pair<double, double> zAxis{check_axis(input_ray.Origin().z(), input_ray.Direction().z(), -1, 1)};

    double mins[] = {xAxis.first, yAxis.first, zAxis.first};
    double maxs[] = {xAxis.second, yAxis.second, zAxis.second};
    t1 = (*std::min_element(maxs, maxs + 3));
    t0 = (*std::max_element(mins, mins + 3));
  }

  bool Cube::intersects(const Ray &r, const double tmin, const double tmax, Intersection &rec) const
  {
    double t1, t0;
    calchit(r, t0, t1);

    if (t1 > t0)
      return false;

    // in this case we only care about the first hit that lies between our range
    if (t0 > tmin && t0 <= tmax){
      rec = Intersection(reinterpret_cast<const Shape *>(this), t0);
      return true;
    }
    if (t1 > tmin && t1 <= tmax){
      rec = Intersection(reinterpret_cast<const Shape *>(this), t1);
      return true;
    }

    return false;
  }

  const Vector Cube::local_normal_at(const Point &position, const Intersection &i) const
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


 const bool Cube::getBounds(Bounds *bounds)const
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
