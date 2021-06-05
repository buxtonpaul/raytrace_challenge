#include "gtest/gtest.h"
#include "matrix.h"
#include "rays.h"
#include "group.h"
#include "tuples.h"
#include "sphere.h"
#include "triangle.h"
#include "world.h"
#include "objparser.h"
using namespace ray_lib;



TEST(Group, EmptyGroup)
{
  Group g;

  EXPECT_EQ(g.Transform(), Matrix::Identity);
  EXPECT_EQ(g.isEmpty(), true);
}

TEST(Group, Shape_emptyparent)
{
  Sphere s;

  EXPECT_EQ(s.parent(), nullptr);
}


TEST(Group, AddChildtoGroup)
{
  Sphere s;
  Group g;
  g.add_child(&s);
  EXPECT_EQ(s.parent(), &g);
  EXPECT_EQ(g.includes(&s), true);
}


TEST(Group, RayIntersectsEmptyGroup)
{
  Ray r{Point{0, 0, 0}, Vector{0, 0, 1}};
  Group g;

  std::vector<Intersection> intersections{g.intersects(r)};
  EXPECT_EQ(intersections.empty(), true);
}

TEST(Group, RayIntersectsNonEmptyGroup)
{
  Group g;
  Sphere s1{};
  Sphere s2{translation(0 , 0, -3)};
  Sphere s3{translation(5, 0, 0)};
  g.add_child(&s1);
  g.add_child(&s2);
  g.add_child(&s3);
  Ray r{Point{0, 0, -5}, Vector{0, 0, 1}};

  std::vector<Intersection> intersections{g.intersects(r)};
  EXPECT_EQ(intersections.size(), 4);
  EXPECT_EQ(intersections[0].GetShape(), &s2);
  EXPECT_EQ(intersections[1].GetShape(), &s2);
  EXPECT_EQ(intersections[2].GetShape(), &s1);
  EXPECT_EQ(intersections[3].GetShape(), &s1);
}

TEST(Group, RayIntersectsTransformedGroup)
{
  Group g{scale(2, 2, 2)};
  Sphere s{translation(5, 0, 0)};
  g.add_child(&s);
  Ray r{Point{10, 0, -10}, Vector{0, 0, 1}};

  std::vector<Intersection> intersections{g.intersects(r)};
  EXPECT_EQ(intersections.size(), 2);
}

TEST(Group, WorldToObjectSpace)
{
  Group g1{rotation_y(M_PI_2)};
  Group g2{scale(2, 2, 2)};
  Sphere s{translation(5, 0, 0)};
  g1.add_child(&g2);
  g2.add_child(&s);

  EXPECT_EQ(Point(0, 0, -1), s.world_to_object({-2, 0, -10}));
}

TEST(Group, NormalWorldToObject)
{
  Group g1{rotation_y(M_PI_2)};
  Group g2{scale(1, 2, 3)};
  Sphere s{translation(5, 0, 0)};
  g1.add_child(&g2);
  g2.add_child(&s);
  double rt3over3 = sqrt(3.0) / 3.0;
  EXPECT_EQ(s.normal_to_world(Vector{rt3over3, rt3over3, rt3over3}), Vector(0.2857, 0.4286, -0.8571));
}

TEST(Group, ObjGroupNormal)
{
  Group g1{rotation_y(M_PI_2)};
  Group g2{scale(1, 2, 3)};
  Sphere s{translation(5, 0, 0)};
  g1.add_child(&g2);
  g2.add_child(&s);
  EXPECT_EQ(s.normal(Point{1.7321, 1.1547, -5.5774}), Vector(0.2857, 0.4286, -0.8571));
}



TEST(Group, RayIntersectsTriangle)
{
  double sqrt3over2{ sqrt(3.0)/2.0};
 Triangle t{Point{0, 1, 0},
                     Point{-1, 0, 0},
                     Point{1, 0, 0}
  };
  Ray r{Point(-0.2, 0.3, -2), Vector(0, 0, 1)};


  Intersection isection(nullptr, 0);
  auto a = t.intersects(r, 0.0, 12.0, &isection);
  EXPECT_EQ(a, true);
  EXPECT_EQ(isection.t(), 2.0);
}



TEST(Group, RayIntersectsTriangleNorm)
{
  double sqrt3over2{ sqrt(3.0)/2.0};
 Triangle t{Point{0, 1, 0},
                     Point{-1, 0, 0},
                     Point{1, 0, 0}
  };
  Ray r{Point(-0.2, 0.3, -2), Vector(0, 0, 1)};


  Intersection isection(nullptr, 0);
  auto a = t.intersects(r, 0.0, 12.0, &isection);

  auto norm = t.normal({0 , 0, 0.0});

  EXPECT_EQ(a, true);
  EXPECT_EQ(isection.t(), 2.0);
  EXPECT_EQ(norm, Vector(0, 0, -1));
}

TEST(Group, RayIntersectsSmoothTriangle)
{
  SmoothTriangle t{Point{0, 1, 0},
                     Point{-1, 0, 0},
                     Point{1, 0, 0},
                     {0, 0, -1},
                     {0, 0, -1},
                     {0, 0, -1}
  };
  Ray r{Point(-0.2, 0.3, -2), Vector(0, 0, 1)};


  Intersection isection(nullptr, 0);
  auto a = t.intersects(r, 0.0, 12.0, &isection);

  auto norm = t.normal({-0.2 , 0.3, 0.0});

  EXPECT_EQ(a, true);
  EXPECT_EQ(isection.t(), 2.0);
  EXPECT_EQ(norm, Vector(0, 0, -1));
}


TEST(Group, RayIntersectsRotatedTriangle)
{
  Group g1{rotation_y(M_PI_4)};
  SmoothTriangle t1{Point{0, 1, 0},
                     Point{-1, 0, 0},
                     Point{1, 0, 0},
                     {0, 0, -1},
                     {0, 0, -1},
                     {0, 0, -1}
  };
   Triangle t2{Point{0, 1, 0},
                     Point{-1, 0, 0},
                     Point{1, 0, 0}
  };
  Ray r{Point(-0.2, 0.3, -2), Vector(0, 0, 1)};


  g1.add_child(&t1);
  g1.add_child(&t2);
  Intersection isection1(nullptr, 0);
  auto a1 = t1.intersects(r, 0.0, 12.0, &isection1);
  auto norm1 = t1.normal({-0.2 , 0.3, 0.0});

  Intersection isection2(nullptr, 0);
  auto a2 = t2.intersects(r, 0.0, 12.0, &isection2);
  auto norm2 = t2.normal({-0.2 , 0.3, 0.0});


  IntersectionState xs1{isection1, r};
  IntersectionState xs2{isection2, r};

  EXPECT_EQ(a1, true);
  EXPECT_EQ(a2, true);
  EXPECT_FLOAT_EQ(isection1.t(), 2.2);
  EXPECT_FLOAT_EQ(isection2.t(), 2.2);
  EXPECT_EQ(norm1, Vector(-sqrt(2.0)/2.0, 0, -sqrt(2.0)/2.0));
  EXPECT_EQ(norm2, Vector(-sqrt(2.0)/2.0, 0, -sqrt(2.0)/2.0));
  EXPECT_EQ(xs1.Normal(), norm1);
  EXPECT_EQ(xs2.Normal(), norm2);
}


TEST(Group, RayIntersectsRotatedTriangle_BVHWorld)
{

  Light l;
  World w;
  BVHWorld bww;


  l.position(Point(-10, 10, -10));
  l.intensity(Color(1, 1, 1));

  std::shared_ptr<Group> g1 = std::make_shared<Group>(rotation_y(M_PI_4));
  Ray r{Point(-0.2, 0.3, -2), Vector(0, 0, 1)};

  // std::shared_ptr<SmoothTriangle> t1 =  std::shared_ptr<SmoothTriangle>(new SmoothTriangle({0, 1, 0},
  //                    {-1, 0, 0},
  //                    {1, 0, 0},
  //                    {0, 0, -1},
  //                    {0, 0, -1},
  //                    {0, 0, -1}));
  // g1->add_child(t1.get());

  ObjParser p;
  std::string testfile{TEST_DATA_FOLDER};
  testfile.append("smoothtriangle.obj");
  EXPECT_EQ(true, p.loadObject(testfile)) << (testfile);
  Group &g{p.defaultGroup()};
  const SmoothTriangle * t1 = dynamic_cast<const SmoothTriangle *>(g.at(0));
  g1->add_child(&p.defaultGroup());

  Intersection isection1(nullptr, 0);
  auto a1 = t1->intersects(r, 0.0, 12.0, &isection1);
  auto norm1 = t1->normal({-0.2 , 0.3, 0.0});


  IntersectionState xs1{isection1, r};
  bww.WorldShapes().push_back(g1);
  bww.WorldLights().push_back(&l);
  bww.InitWorld();
  auto c = bww.shade_hit(xs1, 4);

  w.WorldShapes().push_back(g1);
  w.WorldLights().push_back(&l);
  w.InitWorld();

  EXPECT_EQ(a1, true);
  EXPECT_FLOAT_EQ(isection1.t(), 2.2);
  EXPECT_EQ(norm1, Vector(-sqrt(2.0)/2.0, 0, -sqrt(2.0)/2.0));
  EXPECT_EQ(xs1.Normal(), norm1);

  EXPECT_EQ( w.shade_hit(xs1, 4), bww.shade_hit(xs1, 4));

  Bounds tribounds;
  aabb tribox;
  t1->getBounds(&tribounds);
  t1->bounding_box(&tribox);
// so it looks like bounding boxes may be a bit screwed.






  EXPECT_EQ( w.color_at(r, 4), bww.color_at(r, 4));


}
