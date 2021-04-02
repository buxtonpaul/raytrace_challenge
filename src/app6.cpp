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

using ray_lib::Camera;
using ray_lib::Light;
using ray_lib::Material;
using ray_lib::Plane;
using ray_lib::Point;
using ray_lib::Sphere;
using ray_lib::Vector;
using ray_lib::World;
using ray_lib::default_matparams;
int main(int argc, char *argv[])
{
  Camera c(640, 480, M_PI / 2);
  c.viewTransform(ray_lib::view_transform(Point(0, 1.5, -5), Point(0, 1, 0),
                                          Vector(0, 1, 0)));

  World w;


  ray_lib::CheckPattern3d pat_floor{Color(0.9, 0.9, 0.9), Color(0.1, 0.1, 0.1), ray_lib::Scale(0.25, 0.25, 0.25)};
  Material mat_floor{default_matparams.ambient,
                     default_matparams.diffuse,
                     0,
                     default_matparams.shiny,
                     0.3,
                     default_matparams.transparency,
                     default_matparams.index,

                     pat_floor.asPattern()};

  mat_floor.Specular(0);

  ray_lib::SolidPattern wall_pattern{Color{0.9, 0.9, 0.9}};
  Material m_walls{default_matparams.ambient,
                   default_matparams.diffuse,
                   default_matparams.specular,
                   default_matparams.shiny,
                   default_matparams.reflect,
                   default_matparams.transparency,
                   default_matparams.index,
                   wall_pattern.asPattern()};

  Sphere floor{ray_lib::Scale(10, 0.01, 10)};
  floor.Mat(mat_floor);

  w.WorldShapes().push_back(&floor);

  Sphere left_wall{ray_lib::Scale(10, 0.01, 10)
                       .Rotate_x(M_PI / 2.0)
                       .Rotate_y(-M_PI / 4.0)
                       .Translate(0, 0, 5)};
  left_wall.Mat(m_walls);
  w.WorldShapes().push_back(&left_wall);

  Sphere right_wall{ray_lib::Scale(10, 0.01, 10)
                        .Rotate_x(M_PI / 2.0)
                        .Rotate_y(M_PI / 4.0)
                        .Translate(0, 0, 5)};
  right_wall.Mat(m_walls);
  w.WorldShapes().push_back(&right_wall);

  ray_lib::StripePattern candy{Color(0.9, 0.01, 0.01), Color(.99, .99, .99), ray_lib::Scale(0.25, 0.25, 0.25)};

  Material middle_mat;
  ray_lib::SolidPattern p_mat{Color(0.1, 1, 0.5)};
  middle_mat.SetPattern(p_mat.asPattern());
  middle_mat.Specular(0.3);
  middle_mat.Diffuse(0.7);
  middle_mat.Reflectivity(0.25);

  middle_mat.SetPattern(candy.asPattern());

  Sphere middle{ray_lib::Scale(.75, 1, 0.75) *
                ray_lib::Translation(-0.75, 1, 0.5) *
                ray_lib::Rotation_y(1.0) *
                ray_lib::Rotation_z(1.0)};
  middle.Mat(middle_mat);

  Sphere right;
  right.Transform(ray_lib::Scale(0.5, 0.5, 0.5).Translate(1.5, 0.5, -0.5));
  Material right_mat;
  ray_lib::GradientPattern p_rightmat{Color(0.5, 1, 0.1), Color(0.2, 0, 0.8)};
  right_mat.SetPattern(p_rightmat.asPattern());
  right_mat.Specular(0.3);
  right_mat.Diffuse(0.7);
  right.Mat(right_mat);

  Sphere left;
  left.Transform(ray_lib::Scale(1.33, 1.33, 1.33).Translate(-3.8, 1.33, 1));
  Material left_mat;
  ray_lib::CheckPattern3d p_leftmat{Color{1, 1, 1}, Color{0, .9, 0}, ray_lib::Scale(0.2, 0.2, 0.2)};

  left_mat.SetPattern(p_leftmat.asPattern());
  left_mat.Specular(0.3);
  left_mat.Diffuse(0.7);
  left.Mat(left_mat);

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