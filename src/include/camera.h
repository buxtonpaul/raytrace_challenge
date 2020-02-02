#ifndef _camera_h_
#define _camera_h_
#include "matrix.h"
#include "tuples.h"
namespace ray_lib {

Matrix view_transform(Point from, Point to, Vector up);

class Camera {
  Camera(Matrix transform);
};
}  // namespace ray_lib
#endif