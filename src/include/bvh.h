#ifndef _bvh_node_h
#define _bvh_node_h
#include <vector>
#include <memory>
#include "hittable.h"
#include "hittable_list.h"
#include "rays.h"

namespace ray_lib
{

  class bvh_node : public Hittable
  {
  public:
    explicit bvh_node(const hittable_list &list)  : bvh_node(list.objects,  0,  list.objects.size())
    {
    }

    bvh_node(
        const std::vector<std::shared_ptr<const Hittable>> &src_objects,
        size_t start, size_t end);

    bool intersects(const Ray &r, const double tmin, const double tmax, Intersection *rec) const override;
    std::vector<Intersection> intersects(const Ray &r, const double tmin, const double tmax) const override;
    std::vector<Intersection> intersects(const Ray &r) const override;
    bool bounding_box(aabb *output_box) const override;

  public:
    std::shared_ptr<const Hittable> left;
    std::shared_ptr<const Hittable> right;
    aabb box;
  };

}

#endif //_ray_lib