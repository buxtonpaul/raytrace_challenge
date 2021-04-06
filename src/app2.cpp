#include <fstream>
#include <iostream>
#include "canvas.h"
#include "color.h"
#include "matrix.h"
#include "tuples.h"

using namespace ray_lib;
int main(int argc, char *argv[])
{
  Canvas c{100, 100};
  // we will have the location transformations and the display ones

  Point Twelve{
      Matrix::Identity.translate(0, 1, 0) * Point(0, 0, 0)};

  for (unsigned int hour = 0; hour < 12; ++hour)
  {
    Point location{Matrix::Identity.rotate_z(hour * M_PI / 6.0)
                                .scale(40, 40, 40)
                                .translate(50, 50, 0) *
                            Twelve};
    c.Pixel(location.x(), c.height() - location.y(), Color(1, 0, 0));
    std::cout << location << std::endl;
  }

  std::ofstream outfile(genfilestring() + ".ppm");
  outfile << c.ppm();
  outfile.close();
}
