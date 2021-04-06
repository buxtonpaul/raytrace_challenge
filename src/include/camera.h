#ifndef _camera_h_
#define _camera_h_
#include "canvas.h"
#include "matrix.h"
#include "rays.h"
#include "tuples.h"
#include "world.h"
namespace ray_lib {

Matrix view_transform(const Point &from, const Point &to, const Vector &up);

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
  unsigned int h_size() const { return _hsize; }
  unsigned int v_size() const { return _vsize; }
  unsigned int h_size(const unsigned int size) {
    _hsize = size;
    return size;
  }
  unsigned int v_size(const unsigned int size) {
    _vsize = size;
    return size;
  }

  double fov() const { return _fov; }
  double fov(const double fov) {
    _fov = fov;
    return _fov;
  }
  Matrix view_transform() const { return _viewtransform; }
  Matrix view_transform(Matrix intransform) {
    _viewtransform = intransform;
    return _viewtransform;
  }
  double pixel_size() { return _pixelSize; }
  Ray ray_for_pixel(const unsigned int px, const unsigned int py) const;
  Canvas render(const World &w) const;
};
}  // namespace ray_lib
#endif  //_camera_h_
