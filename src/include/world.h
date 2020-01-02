#ifndef _world_h_
#define _world_h_
#include <vector>
#include "light.h"
#include "shape.h"

namespace ray_lib {
class World {
 private:
  // cannot have an vector of references.. ro using pointers instead
  std::vector<ray_lib::Shape *> _shapes;
  std::vector<ray_lib::Light *> _lights;

 public:
  World() {}
  std::vector<ray_lib::Light *> &WorldLights();
  std::vector<ray_lib::Shape *> &WorldShapes();
  std::vector<ray_lib::Intersection> WorldIntersections(
      const ray_lib::Ray &theray) const;
};

}  // namespace ray_lib
#endif
