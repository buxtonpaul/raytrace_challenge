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

  c.viewTransform(view_transform(Point(0, 8, -20), Point(0, 1, 0),
                                          Vector(0, 1, 0)));

  World w;

  CheckPattern3d pat_floor{Color(0.9, 0.9, 0.9), Color(0.1, 0.1, 0.1), Scale(.1, 1, .1)};
   Material mat_floor=Material().Specular(0).Reflectivity(0.3).SetPattern(pat_floor.asPattern());

  mat_floor.Specular(0);

  SolidPattern wall_pattern{Color{0.9, 0.9, 0.9}};
    Material m_walls = Material().SetPattern(wall_pattern.asPattern());

  Cube floor{Scale(10, 1, 10).Translate(0, -.5, 0) };
  floor.material(mat_floor);

  w.WorldShapes().push_back(&floor);

  StripePattern candy{Color(0.9, 0.1, 0.1), Color(.95, .95, .95), Scale(0.25, 0.25, 0.25)};

  Material middle_mat;
  middle_mat.Specular(0.3);
  middle_mat.Diffuse(0.7);
  middle_mat.Ambient(0.7);
  middle_mat.Reflectivity(0);
  middle_mat.Transparency(0);
  middle_mat.RefractiveIndex(1.5);

  middle_mat.SetPattern(candy.asPattern());

  // note use . operator can specify translations in order instead of reverse order required when multiplying
  Cube middle{Rotation_x(0).Rotate_y(0).Translate(-1, 0.5, 0)};
  middle.material(middle_mat);

  Sphere left;
  left.Transform(Scale(1.33, 1.33, 1.33).Translate(-6.8, 1.33, 1));
  Material left_mat;
  CheckPattern3d p_leftmat{Color{1, 1, 1}, Color{0, .9, 0}, Scale(0.2, 0.2, 0.2)};

  left_mat.SetPattern(p_leftmat.asPattern());
  left_mat.Specular(0.3);
  left_mat.Diffuse(0.7);
  left.material(left_mat);

  Light l{Color(1.0, 1.0, 1.0), Point(-10, 10, -10)};

  w.WorldShapes().push_back(&middle);
  w.WorldShapes().push_back(&left);
  // w.WorldShapes().push_back(&right);
  w.WorldLights().push_back(&l);

  Canvas outimage{c.Render(w)};

  std::ofstream outfile(genfilestring() + ".ppm");
  outfile << outimage.ppm();
  outfile.close();
}
