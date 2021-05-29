#include <fstream>
#include <iostream>
#include <memory>
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
  c.view_transform(view_transform(Point(0, 1.5, -5), Point(0, 1, 0),
                                          Vector(0, 1, 0)));

  World w;


  CheckPattern3d pat_floor{Color(0.9, 0.9, 0.9), Color(0.1, 0.1, 0.1), scale(2.5, 2.5, 2.5)};
  Material mat_floor = Material().specular(0).reflectivity(0.3).pattern(pat_floor);

  SolidPattern wall_pattern{Color{0.9, 0.9, 0.9}};
  Material m_walls = Material().pattern(wall_pattern);

  std::shared_ptr<Plane> floor = std::make_shared<Plane>();
  floor->material(mat_floor);

  w.WorldShapes().push_back(floor);

  std::shared_ptr<Sphere> left_wall = std::make_shared<Sphere>(scale(10, 0.01, 10)
                       .rotate_x(M_PI / 2.0)
                       .rotate_y(-M_PI / 4.0)
                       .translate(0, 0, 5));
  
  left_wall->material(m_walls);
 // w.WorldShapes().push_back(&left_wall);

  std::shared_ptr<Sphere> right_wall = std::make_shared<Sphere>(scale(10, 0.01, 10)
                        .rotate_x(M_PI / 2.0)
                        .rotate_y(M_PI / 4.0)
                        .translate(0, 0, 5));
  
  right_wall->material(m_walls);
  //w.WorldShapes().push_back(&right_wall);

  StripePattern candy{Color(0.1, 0.01, 0.01), Color(.3, .3, .3), scale(0.25, 0.25, 0.25)};

  Material middle_mat;
  // SolidPattern p_mat{Color(0.1, 0, 0)};
  // middle_mat.SetPattern(p_mat.);
  middle_mat.specular(0.3);
  middle_mat.diffuse(0.7);
  middle_mat.reflectivity(0.25);
  middle_mat.transparency(0.9);
  middle_mat.refractive_index(1.5);

  middle_mat.pattern(candy);
  std::shared_ptr<Sphere> middle = std::make_shared<Sphere> (scale(.75, 1, 0.75) *
                translation(-0.75, 1, 0.5) *
                rotation_y(1.0) *
                rotation_z(1.0));

  
  middle->material(middle_mat);

  std::shared_ptr<Sphere> right = std::make_shared<Sphere> ();
  right->Transform(scale(0.5, 0.5, 0.5).translate(1.5, 0.5, -0.5));
  Material right_mat;
  GradientPattern p_rightmat{Color(0.5, 1, 0.1), Color(0.2, 0, 0.8)};
  right_mat.pattern(p_rightmat);
  right_mat.specular(0.3);
  right_mat.diffuse(0.7);
  right->material(right_mat);

  std::shared_ptr<Sphere> left = std::make_shared<Sphere> ();
  left->Transform(scale(1.33, 1.33, 1.33).translate(-3.8, 1.33, 1));
  Material left_mat;
  CheckPattern3d p_leftmat{Color{1, 1, 1}, Color{0, .9, 0}, scale(0.2, 0.2, 0.2)};

  left_mat.pattern(p_leftmat);
  left_mat.specular(0.3);
  left_mat.diffuse(0.7);
  left->material(left_mat);

  Light l{Color(1.0, 1.0, 1.0), Point(-10, 10, -10)};

  w.WorldShapes().push_back(middle);
  w.WorldShapes().push_back(left);
  w.WorldShapes().push_back(right);
  w.WorldLights().push_back(&l);

  Canvas outimage{c.render(&w)};

  std::ofstream outfile(genfilestring() + ".ppm");
  outfile << outimage.ppm();
  outfile.close();
}
