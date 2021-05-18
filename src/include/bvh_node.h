#ifndef _bvh_node_h
#define _bvh_node_h
#include <vector>
#include <memory>
#include "hittable.h"
#include "hittable_list.h"
#include "rays.h"

// namespace ray_lib
// {

//   class bvh_node : public Hittable
//   {
//   public:
//     bvh_node();

//     std::vector<Intersection> intersects(const Ray &r, const double tmin, const double tmax) const override;

//     bool bounding_box(aabb &output_box) const override;

//   public:
//     shared_ptr<Hittable> left;
//     shared_ptr<Hittable> right;
//     aabb box;
//   };

//   bool bvh_node::bounding_box(aabb &output_box) const
//   {
//     output_box = box;
//     return true;
//   }
// }
#endif //_ray_lib