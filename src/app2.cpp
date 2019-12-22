#include <fstream>
#include <iostream>
#include "canvas.h"
#include "color.h"
#include "matrix.h"
#include "tuples.h"

int main(int argc, char *argv[]) {
  Canvas c(100, 100);
  // we will have the location transformations and the display ones

  ray_lib::Point Twelve =
      ray_lib::identity_4.Translate(0, 1, 0) * ray_lib::Point(0, 0, 0);

  for (unsigned int hour = 0; hour < 12; ++hour) {
    ray_lib::Point location = ray_lib::identity_4.Rotate_z(hour * M_PI / 6.0)
                                  .Scale(40, 40, 40)
                                  .Translate(50, 50, 0) *
                              Twelve;
    c.Pixel(location.x(), c.height() - location.y(), Color({1, 0, 0}));
    std::cout << location << std::endl;
  }

  std::ofstream outfile(genfilestring() + ".ppm");
  outfile << c.ppm();
  outfile.close();
}
