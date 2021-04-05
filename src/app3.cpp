#include <fstream>
#include <iostream>
#include "canvas.h"
#include "color.h"
#include "matrix.h"
#include "rays.h"
#include "sphere.h"
#include "tuples.h"

using namespace ray_lib;

int main(int argc, char *argv[])
{
  // as described in the book we are using viewing along the z axis,
  // with  the sphere at our origin, and the viewpoint at 0,0,-5
  // and our detecting surface behind the sphere at z=10
  // we will iterate over the region -3.5->3.5
  Canvas c{1000, 1000};
  double xpos{-3.5};
  double ypos{-3.5};
  double step_size{7.0 / c.height()};
  Sphere s;
  for (unsigned int i = 0; i < c.height(); ++i)
  {
    for (unsigned int j = 0; j < c.height(); ++j)
    {
      Ray r(Point(0, 0, -5), Vector(xpos, ypos, 10));
      std::vector<Intersection> xs{s.intersects(r)};
      if (xs.size() > 0)
      { // we have hit the sphere
        c.Pixel(j, c.height() - i, Color(1, 0, 0));
      }
      xpos += step_size;
    }
    xpos = -3.5;
    ypos += step_size;
  }
  std::ofstream outfile(genfilestring() + ".ppm");
  outfile << c.ppm();
  outfile.close();
}
