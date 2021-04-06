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

  m_floor.Specular(0);
  m_floor.Reflectivity(0.5);
  m_floor.Ambient(0.1);
  m_floor.Diffuse(0.25);
  m_floor.SetPattern(p_floor.asPattern());
  floor.material(m_floor);
  w.WorldShapes().push_back(&floor);

  Sphere middle;
  middle.Transform(Scale(.75, 1, 0.75) * Translation(-0.75, 1, 0.5) * Rotation_y(1.0) * Rotation_z(1.0));
  Material middle_mat;
  SolidPattern p_mat{Color(0.1, 1, 0.5)};
  middle_mat.SetPattern(p_mat.asPattern());
  middle_mat.Specular(0.3);
  middle_mat.Diffuse(0.7);
  middle_mat.Reflectivity(0.25);
  StripePattern candy{Color(0.9, 0.01, 0.01), Color(.99, .99, .99), Scale(0.25, 0.25, 0.25)};
  middle_mat.SetPattern(candy.asPattern());
  middle.material(middle_mat);

  Sphere right;
  right.Transform(Scale(0.5, 0.5, 0.5).Translate(1.5, 0.5, -0.5));
  Material right_mat;
  GradientPattern p_rightmat{Color(0.5, 1, 0.1), Color(0.2, 0, 0.8)};
  right_mat.SetPattern(p_rightmat.asPattern());
  right_mat.Specular(0.3);
  right_mat.Diffuse(0.7);
  right.material(right_mat);

  Sphere left;
  left.Transform(Scale(1.33, 1.33, 1.33).Translate(-3.8, 1.33, 1));
  Material left_mat;
  CheckPattern3d p_leftmat{Color{1, 1, 1}, Color{0, .9, 0}, Scale(0.2, 0.2, 0.2)};

  left_mat.SetPattern(p_leftmat.asPattern());
  left_mat.Specular(0.3);
  left_mat.Diffuse(0.7);
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
