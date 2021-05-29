#ifndef _camera_h_
#define _camera_h_
#include "canvas.h"
#include "matrix.h"
#include "rays.h"
#include "tuples.h"
#include "world.h"
namespace ray_lib
{

  Matrix view_transform(const Point &from, const Point &to, const Vector &up);

  class Camera
  {

  public:
    // Constructor
    Camera(unsigned int hsize = 120, unsigned int vsize = 120, double fov = 90,
           Matrix transform = Matrix::Identity);
    // getters and setters
    unsigned int h_size() const;
    unsigned int v_size() const;
    unsigned int h_size(const unsigned int size);
    unsigned int v_size(const unsigned int size);

    double fov() const;
    double fov(const double fov);
    Matrix view_transform() const;
    Matrix view_transform(Matrix intransform);
    double pixel_size();
    Ray ray_for_pixel(const unsigned int px, const unsigned int py) const;
    Canvas render(const WorldBase *w) const;

  private:
    unsigned int _hsize;
    unsigned int _vsize;
    double _fov;
    Matrix _viewtransform;
    double _pixelSize;
    double _halfWidth;
    double _halfHeight;
  };
} // namespace ray_lib
#endif //_camera_h_
