#ifndef _hittable_list_h_
#define _hittable_list_h_
#include <vector>
#include <memory>
#include "hittable.h"

namespace ray_lib
{

class hittable_list : public Hittable
{
public:
  hittable_list() {}
  explicit hittable_list(std::shared_ptr<const Hittable> object) { add(object); }

  void clear() { objects.clear(); }
  void add(std::shared_ptr<const Hittable> object) { objects.push_back(object); }

  bool intersects(const Ray &r, const double tmin, const double tmax, Intersection *rec) const override;
  std::vector<Intersection> intersects(const Ray &r, const double tmin, const double tmax) const override;
  std::vector<Intersection> intersects(const Ray &r) const override;
  bool bounding_box(aabb *output_box) const override;
public:
  std::vector<std::shared_ptr<const Hittable>> objects;
};

} // namespace ray_lib
#endif //_hittable_list_h_
