#include "gtest/gtest.h"
#include "matrix.h"
#include "rays.h"
#include "group.h"
#include "tuples.h"
#include "sphere.h"
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


