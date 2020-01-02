#include "world.h"
#include <algorithm>
#include <vector>
#include "light.h"
#include "matrix.h"
#include "rays.h"
#include "shape.h"
#include "sphere.h"
namespace ray_lib {
std::vector<Shape *> &World::WorldShapes() { return _shapes; }
std::vector<Light *> &World::WorldLights() { return _lights; }

std::vector<ray_lib::Intersection> World::WorldIntersections(
    const ray_lib::Ray &theray) const {
  std::vector<ray_lib::Intersection> outputs;

  // int const new_element = 33;
  // v.insert(std::lower_bound(v.begin(), v.end(), new_element), new_element);
  for (auto s : _shapes) {
    auto i = s->intersects(theray);
    if (i.size()) {
      // we have some intersections so add them
      for (std::vector<ray_lib::Intersection>::iterator it = i.begin();
           it != i.end(); ++it) {
        outputs.push_back(*it);
      }
    }
  }
  std::sort(outputs.begin(), outputs.end());
  return outputs;
}
}  // namespace ray_lib
