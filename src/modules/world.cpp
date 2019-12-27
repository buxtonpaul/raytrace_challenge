#include "world.h"
#include <vector>
#include "light.h"
#include "shape.h"
#include "sphere.h"
namespace ray_lib {
std::vector<Shape *> &World::WorldShapes()  { return _shapes; }
std::vector<Light *> &World::WorldLights()  { return _lights; }

}  // namespace ray_lib
