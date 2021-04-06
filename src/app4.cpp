#include <fstream>
#include <iostream>
#include "camera.h"
#include "canvas.h"
#include "color.h"
#include "light.h"
#include "material.h"
#include "matrix.h"
#include "rays.h"
#include "sphere.h"
#include "tuples.h"
#include "world.h"
#include "pattern.h"

using namespace ray_lib;

int main(int argc, char *argv[])
{
  Camera c{640, 480, M_PI / 2};
  c.viewTransform(view_transform(Point(0, 1.5, -5), Point(0, 1, 0),
                                          Vector(0, 1, 0)));

  World w;

  Sphere floor;
  Material m_floor;
  SolidPattern mfloor_pat{Color(1.0, 0.9, 0.9)};
  m_floor.SetPattern(mfloor_pat.asPattern());
  floor.Transform(Scale(10, 0.01, 10));
  m_floor.Specular(0);
  floor.material(m_floor);
  w.WorldShapes().push_back(&floor);

  Sphere left_wall;
  left_wall.Transform(Scale(10, 0.01, 10)
                          .Rotate_x(M_PI / 2.0)
                          .Rotate_y(-M_PI / 4.0)
                          .Translate(0, 0, 5));
  left_wall.material(m_floor);
  w.WorldShapes().push_back(&left_wall);

  Sphere right_wall;
  right_wall.Transform(Scale(10, 0.01, 10)
                           .Rotate_x(M_PI / 2.0)
                           .Rotate_y(M_PI / 4.0)
                           .Translate(0, 0, 5));
  right_wall.material(m_floor);

  Sphere middle;
  middle.Transform(Translation(-0.5, 1, 0.5));
  Material middle_mat;
  SolidPattern middle_pat(Color(0.1, 1, 0.5));
  middle_mat.SetPattern(middle_pat.asPattern());

  middle_mat.Specular(0.3);
  middle_mat.Diffuse(0.7);
  middle.material(middle_mat);

  Sphere right;
  right.Transform(Scale(0.5, 0.5, 0.5).Translate(1.5, 0.5, -0.5));
  Material right_mat;

  SolidPattern right_pat(Color(0.5, 1, 0.1));
  right_mat.SetPattern(right_pat.asPattern());

  right_mat.Specular(0.3);
  right_mat.Diffuse(0.7);
  right.material(right_mat);

  Sphere left;
  left.Transform(Scale(0.33, 0.33, 0.33).Translate(-1.5, 0.33, -0.75));
  Material left_mat;
  SolidPattern left_pat(Color(1, 0.8, 0.1));
  left_mat.SetPattern(left_pat.asPattern());

  left_mat.Specular(0.3);
  left_mat.Diffuse(0.7);
  left.material(left_mat);

  Light l{Color(1.0, 1.0, 1.0), Point(-10, 10, -10)};

  w.WorldShapes().push_back(&right_wall);
  w.WorldShapes().push_back(&middle);
  w.WorldShapes().push_back(&left);
  w.WorldShapes().push_back(&right);
  w.WorldLights().push_back(&l);

  Canvas outimage{c.Render(w)};

  std::ofstream outfile(genfilestring() + ".ppm");
  outfile << outimage.ppm();
  outfile.close();
}
