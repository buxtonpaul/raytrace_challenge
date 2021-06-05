#include <fstream>
#include <iostream>
#include <chrono>
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
#include "group.h"
#include "objparser.h"

using namespace ray_lib;
int main(int argc, char *argv[])
{
  const char *outfile;
  std::string defaultfile = genfilestring() + ".png";
  if (argc < 2)
  {
    outfile = defaultfile.data();
  }
  else
  {
    outfile = argv[1];
  }
  Camera c(1024, 768, M_PI / 2);
  // Camera c(100, 70, M_PI / 2);
  // c.viewTransform(view_transform(Point(0, 20, 0), Point(0, 0, 0),
  //                                Vector(0, 0, 1)));

  c.view_transform(view_transform(Point(0, 5, -9), Point(0, 1, 0),
                                  Vector(0, 1, 0)));
  // c.view_transform(view_transform(Point(0, 0, -5), Point(0, 0, 0),
  //                                 Vector(0, 1, 0)));

  // World w;
  BVHWorld w;

  CheckPattern3d pat_floor{Color(0.9, 0.9, 0.9), Color(0.1, 0.1, 0.1), scale(.1, 1, .1)};
  Material mat_floor = Material(pat_floor).specular(0).reflectivity(0.3);

  Material m_walls{Material(SolidPattern(Color(0.0, 0.9, 0.9)))};

  std::shared_ptr<Cube> floor = std::make_shared<Cube>(scale(10, 1, 10).translate(0, -.5, 0));

  floor->material(mat_floor);

  w.WorldShapes().push_back(floor);

  StripePattern candy{Color(0.9, 0.1, 0.1), Color(.95, .95, .95), scale(0.25, 0.25, 0.25)};

  Material middle_mat;
  middle_mat.specular(0.3);
  middle_mat.diffuse(0.7);
  middle_mat.ambient(0.7);
  middle_mat.reflectivity(0);
  middle_mat.transparency(0);
  middle_mat.refractive_index(1.5);

  middle_mat.pattern(candy);

  ObjParser p;
  std::string testfile{TEST_DATA_FOLDER};
  testfile.append("teapot.obj.txt");
  // testfile.append("smoothtriangle.obj");
  // testfile.append("teapot_low.obj");
  p.ParseFile(testfile);

  // note use . operator can specify translations in order instead of reverse order required when multiplying

  // Group g1;
  std::shared_ptr<Group> g1 = std::make_shared<Group>();


  Light l{Color(1.0, 1.0, 1.0), Point(5, 10, -10)};

  g1->Transform(Matrix::Identity.scale(1.0 / 4, 1.0 / 4, 1.0 / 4).rotate_x(-M_PI_2).translate(0.5, 0, 0));
  g1->add_child(&p.defaultGroup());
  w.WorldShapes().push_back(g1);
  w.WorldLights().push_back(&l);

  std::cout <<"Init world "<< std::endl;
  auto t_start = std::chrono::high_resolution_clock::now();
  w.InitWorld();
  auto t_end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration<double, std::milli>(t_end-t_start).count();

  std::cout << "Init World took " << std::fixed<< duration/1000 << "s\n";

  Canvas outimage{c.render(&w)};

  outimage.png(outfile);
}
