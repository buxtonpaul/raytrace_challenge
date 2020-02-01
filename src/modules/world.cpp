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
  // it isn't clear if these should be clipped to only those >0...
}
Color World::shade_hit(const IntersectionState &precomps) const {
  // return Color(0, 0, 0);
  return ray_lib::lighting(precomps.Object()->Mat(), *_lights[0],
                           precomps.Position(), precomps.Eye(),
                           precomps.Normal());
}

Color World::color_at(const Ray &theray) const {
  std::vector<ray_lib::Intersection> intersections = WorldIntersections(theray);

  const Intersection *hit = ray_lib::Intersection::GetHit(intersections);
  if (hit == nullptr) return Color(0, 0, 0);
  ray_lib::IntersectionState i(*hit, theray);

  return shade_hit(i);
}
}  // namespace ray_lib
