#include <fstream>
#include <iostream>
#include "canvas.h"
#include "color.h"
#include "light.h"
#include "material.h"
#include "matrix.h"
#include "rays.h"
#include "sphere.h"
#include "tuples.h"

using ray_lib::Light;
using ray_lib::Material;
using ray_lib::Point;
using ray_lib::Sphere;
using ray_lib::Vector;

int main(int argc, char *argv[]) {
  // as described in the book we are using viewing along the z axis,
  // with  the sphere at our origin, and the viewpoint at 0,0,-5
  // and our detecting surface behind the sphere at z=10
  // we will iterate over the region -3.5->3.5
  Canvas c(1000, 1000);
  double xpos = -3.5;
  double ypos = -3.5;
  double step_size = 7.0 / c.height();

  Sphere s;
  Material m;
  m.SetColor(Color(1.0, 0.2, 1.0));
  s.Mat(m);

  Light l(Color(1.0, 1.0, 1.0), Point(-10, 10, -10));

  for (unsigned int i = 0; i < c.height(); ++i) {
    for (unsigned int j = 0; j < c.height(); ++j) {
      ray_lib::Ray r(Point(0, 0, -5),
                     ray_lib::Vector(xpos, ypos, 10).normalise());
      std::vector<ray_lib::Intersection> xs = s.intersects(r);
      if (xs.size() > 0) {  // we have hit the sphere
        const ray_lib::Intersection *intersection =
            ray_lib::Intersection::GetHit(xs);
        Point p = r.Position(intersection->t());
        const Vector normal = intersection->GetShape().Normal(p);
        Vector eye = Vector(0, 0, 0) - r.Direction();
        Color out = ray_lib::lighting(intersection->GetShape().Mat(), l, p, eye,
                                      normal);
        c.Pixel(j, c.height() - i, out);
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
