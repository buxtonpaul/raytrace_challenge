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

using namespace ray_lib;

int main(int argc, char *argv[])
{
  Camera c(640, 480, M_PI / 2);
  c.viewTransform(view_transform(Point(0, 1.5, -5), Point(0, 1, 0),
                                          Vector(0, 1, 0)));

  World w;

  Plane floor;
  Material m_floor;
  CheckPattern3d p_floor{Color(0.9, 0.9, 0.9), Color(0.1, 0.1, 0.1)};

  m_floor.specular(0);
  m_floor.reflectivity(0.5);
  m_floor.ambient(0.1);
  m_floor.diffuse(0.25);
  m_floor.pattern(p_floor.asPattern());
  floor.material(m_floor);
  w.WorldShapes().push_back(&floor);

  Sphere middle;
  middle.Transform(scale(.75, 1, 0.75) * translation(-0.75, 1, 0.5) * rotation_y(1.0) * rotation_z(1.0));
  Material middle_mat;
  SolidPattern p_mat{Color(0.1, 1, 0.5)};
  middle_mat.pattern(p_mat.asPattern());
  middle_mat.specular(0.3);
  middle_mat.diffuse(0.7);
  middle_mat.reflectivity(0.25);
  StripePattern candy{Color(0.9, 0.01, 0.01), Color(.99, .99, .99), scale(0.25, 0.25, 0.25)};
  middle_mat.pattern(candy.asPattern());
  middle.material(middle_mat);

  Sphere right;
  right.Transform(scale(0.5, 0.5, 0.5).translate(1.5, 0.5, -0.5));
  Material right_mat;
  GradientPattern p_rightmat{Color(0.5, 1, 0.1), Color(0.2, 0, 0.8)};
  right_mat.pattern(p_rightmat.asPattern());
  right_mat.specular(0.3);
  right_mat.diffuse(0.7);
  right.material(right_mat);

  Sphere left;
  left.Transform(scale(1.33, 1.33, 1.33).translate(-3.8, 1.33, 1));
  Material left_mat;
  CheckPattern3d p_leftmat{Color{1, 1, 1}, Color{0, .9, 0}, scale(0.2, 0.2, 0.2)};

  left_mat.pattern(p_leftmat.asPattern());
  left_mat.specular(0.3);
  left_mat.diffuse(0.7);
  left.material(left_mat);

  Light l{Color(1.0, 1.0, 1.0), Point(-10, 10, -10)};

  w.WorldShapes().push_back(&middle);
  w.WorldShapes().push_back(&left);
  w.WorldShapes().push_back(&right);
  w.WorldLights().push_back(&l);

  Canvas outimage{c.Render(w)};

  std::ofstream outfile(genfilestring() + ".ppm");
  outfile << outimage.ppm();
  outfile.close();
}
