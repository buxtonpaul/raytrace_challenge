#include <fstream>
#include <iostream>
#include "camera.h"
#include "canvas.h"
#include "color.h"
#include "light.h"
#include "material.h"
#include "matrix.h"
#include "plane.h"
#include "rays.h"
#include "sphere.h"
#include "tuples.h"
#include "world.h"
#include "cube.h"

using namespace ray_lib;
int main(int argc, char *argv[])
{
  Camera c(640, 480, M_PI / 2);
  // c.viewTransform(view_transform(Point(0, 20, 0), Point(0, 0, 0),
  //                                Vector(0, 0, 1)));

  c.view_transform(view_transform(Point(0, 8, -20), Point(0, 1, 0),
                                          Vector(0, 1, 0)));

  World w;

  CheckPattern3d pat_floor{Color(0.9, 0.9, 0.9), Color(0.1, 0.1, 0.1), scale(.1, 1, .1)};
   Material mat_floor = Material(pat_floor).specular(0).reflectivity(0.3);

  Material m_walls {Material(SolidPattern(Color(0.0, 0.9, 0.9)))};

  Cube floor{scale(10, 1, 10).translate(0, -.5, 0) };
  floor.material(mat_floor);

  w.WorldShapes().push_back(&floor);

  StripePattern candy{Color(0.9, 0.1, 0.1), Color(.95, .95, .95), scale(0.25, 0.25, 0.25)};

  Material middle_mat;
  middle_mat.specular(0.3);
  middle_mat.diffuse(0.7);
  middle_mat.ambient(0.7);
  middle_mat.reflectivity(0);
  middle_mat.transparency(0);
  middle_mat.refractive_index(1.5);

  middle_mat.pattern(candy);

  // note use . operator can specify translations in order instead of reverse order required when multiplying
  Cube middle{rotation_x(0).rotate_y(0).translate(-1, 0.5, 0)};
  middle.material(middle_mat);

  Sphere left;
  left.Transform(scale(1.33, 1.33, 1.33).translate(-6.8, 1.33, 1));
  Material left_mat;
  CheckPattern3d p_leftmat{Color{1, 1, 1}, Color{0, .9, 0}, scale(0.2, 0.2, 0.2)};

  left_mat.pattern(p_leftmat);
  left_mat.specular(0.3);
  left_mat.diffuse(0.7);
  left.material(left_mat);

  Light l{Color(1.0, 1.0, 1.0), Point(-10, 10, -10)};

  w.WorldShapes().push_back(&middle);
  w.WorldShapes().push_back(&left);
  // w.WorldShapes().push_back(&right);
  w.WorldLights().push_back(&l);

  Canvas outimage{c.render(w)};

  std::ofstream outfile(genfilestring() + ".ppm");
  outfile << outimage.ppm();
  outfile.close();
}
