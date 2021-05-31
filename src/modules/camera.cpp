#include <atomic>
#include <chrono>
#include <iomanip>
#include "omp.h"
#include "camera.h"
#include "canvas.h"
#include "matrix.h"
#include "world.h"

namespace ray_lib
{
  Matrix view_transform(const Point &from, const Point &to, const Vector &up)
  {
    Vector forward((to - from).normalise());
    Vector upn(up.normalise());
    Vector left(forward.crossproduct(upn));
    Vector true_up(left.crossproduct(forward));

    // std::cout << true_up << std::endl;
    Matrix orientation{{{left[0], left[1], left[2], 0},
                        {true_up[0], true_up[1], true_up[2], 0},
                        {-forward[0], -forward[1], -forward[2], 0},
                        {0, 0, 0, 1}}};

    return orientation * translation(-from[0], -from[1], -from[2]);
  }
  Ray Camera::ray_for_pixel(const unsigned int px, const unsigned int py) const
  {
    double xoffset{(px + 0.5) * _pixelSize};
    double yoffset{(py + 0.5) * _pixelSize};

    double world_x{_halfWidth - xoffset};
    double world_y{_halfHeight - yoffset};

    Point pixel{_viewtransform.inverse() * Point(world_x, world_y, -1)};
    Point origin{_viewtransform.inverse() * Point(0, 0, 0)};
    Vector direction{(pixel - origin).normalise()};

    return Ray(origin, direction);
  }
  Canvas Camera::render(const WorldBase *w) const
  {
    Canvas c{_hsize, _vsize};
    std::atomic<int> pixels_done{0};
    std::cout <<"Begin Rendering"<< std::endl;
    auto t_start = std::chrono::high_resolution_clock::now();


#pragma omp parallel for collapse(2) schedule(guided)
    for (unsigned int y = 0; y < _vsize; ++y)
    {
      for (unsigned int x = 0; x < _hsize; ++x)
      {
        Ray r{ray_for_pixel(x, y)};
        Color p{w->color_at(r)};
        c.pixel(x, y, p);
        pixels_done++;
        if (omp_get_thread_num() == 0)
        {
          // note that if thread finishes before others than printing will not update
          int done = pixels_done;
          std::cout << "\rPixels done: "  << pixels_done << "  " << static_cast<int> ((100.0 * done) / (_vsize*_hsize))  << "%"<< std::flush;
        }
      }
    }
    auto t_end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(t_end-t_start).count();

    std::cout << "\nRendering took " << std::fixed<< duration/1000 << "s\n";


    return c;
  }

  Camera::Camera(unsigned int hsize, unsigned int vsize, double fov,
                 Matrix transform)
      : _hsize(hsize), _vsize(vsize), _fov(fov), _viewtransform(transform)
  {
    double half_view = tan(_fov / 2.0);
    double aspect = static_cast<double>(_hsize) / static_cast<double>(_vsize);
    if (aspect >= 1)
    {
      _halfWidth = half_view;
      _halfHeight = half_view / aspect;
    }
    else
    {
      _halfWidth = half_view * aspect;
      _halfHeight = half_view;
    }
    _pixelSize = (_halfWidth * 2) / _hsize;
  }

  unsigned int Camera::h_size() const { return _hsize; }

  unsigned int Camera::v_size() const { return _vsize; }

  unsigned int Camera::h_size(const unsigned int size)
  {
    _hsize = size;
    return size;
  }

  unsigned int Camera::v_size(const unsigned int size)
  {
    _vsize = size;
    return size;
  }

  double Camera::fov() const { return _fov; }

  double Camera::fov(const double fov)
  {
    _fov = fov;
    return _fov;
  }

  Matrix Camera::view_transform() const { return _viewtransform; }

  Matrix Camera::view_transform(Matrix intransform)
  {
    _viewtransform = intransform;
    return _viewtransform;
  }
  double Camera::pixel_size() { return _pixelSize; }

} // namespace ray_lib
