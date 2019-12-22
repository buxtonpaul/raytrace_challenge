#ifndef _rays_h
#define _rays_h

#include "matrix.h"
#include "tuples.h"
#include "utils.h"

namespace ray_lib {

class Ray {
 private:
  Tuple _origin;
  Tuple _direction;

 public:
  Ray(Tuple origin, Tuple direction) : _origin(origin), _direction(direction) {}
  friend std::ostream &operator<<(std::ostream &out, const Ray &r);
  Tuple Origin() const { return _origin; }
  Tuple Direction() const { return _direction; }
};

}  // namespace ray_lib

#endif