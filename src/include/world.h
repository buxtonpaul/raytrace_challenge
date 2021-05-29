#ifndef _world_h_
#define _world_h_
#include <vector>
#include <memory>
#include "color.h"
#include "light.h"
#include "rays.h"
#include "shape.h"
#include "bvh.h"

namespace ray_lib {


  // todo refactor world to support bvh ray world intersection
  // instead of using worl_intersections it will search through the bvh tree usint the intersects function on the 
  // bvh node.

class WorldBase
{
  public:
  virtual void InitWorld();
  std::vector<ray_lib::Light *> &WorldLights();
  std::vector<std::shared_ptr<Shape>> &WorldShapes();
  virtual Color color_at(const Ray &theray, int depth = 4) const = 0;
  virtual bool is_shadowed(const Point &p) const = 0;
  Color shade_hit(const IntersectionState &precomps, int depth = 4) const;
  Color reflection_hit(const IntersectionState &precomps, int depth = 5) const;
  Color refracted_color(const IntersectionState &precomps, int depth = 5) const;
  std::vector<ray_lib::Intersection> WorldIntersections(const ray_lib::Ray &theray) const;

  protected:
  // cannot have an vector of references.. ro using pointers instead
  std::vector<std::shared_ptr<ray_lib::Shape>> _shapes;
  std::vector<ray_lib::Light *> _lights;

};
class World : public WorldBase {

 public:
  World() {}
  Color color_at(const Ray &theray, int depth = 4) const override;
  bool is_shadowed(const Point &p) const override;
};


class BVHWorld : public WorldBase{
 private:
  std::shared_ptr <bvh_node> _scene;
  hittable_list allshapes;

 public:
  BVHWorld() {}
  void InitWorld() override;
 
  Color color_at(const Ray &theray, int depth = 4) const;
  bool is_shadowed(const Point &p) const;
};


}  // namespace ray_lib
#endif
