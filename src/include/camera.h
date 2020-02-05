#ifndef _camera_h_
#define _camera_h_
#include "canvas.h"
#include "matrix.h"
#include "rays.h"
#include "tuples.h"
#include "world.h"
namespace ray_lib {

Matrix view_transform(Point from, Point to, Vector up);

class Camera {
  unsigned int _hsize;
  unsigned int _vsize;
  double _fov;
  Matrix _viewtransform;
  double _pixelSize;
  double _halfWidth;
  double _halfHeight;

 public:
  Camera(unsigned int hsize = 120, unsigned int vsize = 120, double fov = 90,
         Matrix transform = Matrix::Identity)
      : _hsize(hsize), _vsize(vsize), _fov(fov), _viewtransform(transform) {
    double half_view = tan(_fov / 2.0);
    double aspect = static_cast<double>(_hsize) / static_cast<double>(_vsize);
    if (aspect >= 1) {
      _halfWidth = half_view;
      _halfHeight = half_view / aspect;
    } else {
      _halfWidth = half_view * aspect;
      _halfHeight = half_view;
    }
    _pixelSize = (_halfWidth * 2) / _hsize;
  }
  unsigned int HSize() const { return _hsize; }
  unsigned int VSize() const { return _vsize; }
  unsigned int HSize(const unsigned int size) {
    _hsize = size;
    return size;
  }
  unsigned int VSize(const unsigned int size) {
    _vsize = size;
    return size;
  }

  double FOV() const { return _fov; }
  double FOV(const double fov) {
    _fov = fov;
    return _fov;
  }
  Matrix viewTransform() const { return _viewtransform; }
  Matrix viewTransform(Matrix intransform) {
    _viewtransform = intransform;
    return _viewtransform;
  }
  double pixelSize() { return _pixelSize; }
  Ray ray_for_pixel(const unsigned int px, const unsigned int py) const;
  Canvas Render(World w) const;
};
}  // namespace ray_lib
#endif  //_camera_h_
