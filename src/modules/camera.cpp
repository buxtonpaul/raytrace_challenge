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
  Canvas Camera::Render(const World &w) const
  {
    Canvas c{_hsize, _vsize};

#pragma omp parallel for collapse(2) schedule(guided)
    for (unsigned int y = 0; y < _vsize; ++y)
    {
      for (unsigned int x = 0; x < _hsize; ++x)
      {
        Ray r{ray_for_pixel(x, y)};
        Color p{w.color_at(r)};
        c.Pixel(x, y, p);
      }
    }
    return c;
  }
} // namespace ray_lib
