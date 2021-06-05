#include "gtest/gtest.h"
#include "objparser.h"
using namespace ray_lib;

TEST(ObjParser, EmptyGroup)
{
  ObjParser p;
  std::string testfile{TEST_DATA_FOLDER};
  testfile.append("test1.obj");
  EXPECT_EQ(false, p.loadObject(testfile)) << (testfile);
}

TEST(ObjParser, VertexData)
{
  ObjParser p;
  std::string testfile{TEST_DATA_FOLDER};
  testfile.append("test2.obj");
  EXPECT_EQ(true, p.loadObject(testfile)) << (testfile);
  EXPECT_EQ(p.Vertices()[1], Point(-1, 1, 0));
  EXPECT_EQ(p.Vertices()[2], Point(-1, 0.5, 0));
  EXPECT_EQ(p.Vertices()[3], Point(1, 0, 0));
  EXPECT_EQ(p.Vertices()[4], Point(1, 1, 0));
}


TEST(ObjParser, TriangleFaces)
{
  ObjParser p;
  std::string testfile{TEST_DATA_FOLDER};
  testfile.append("test3.obj");
  EXPECT_EQ(true, p.loadObject(testfile)) << (testfile);
  Group &g{p.defaultGroup()};
  const Triangle * t1 = dynamic_cast<const Triangle *>(g.at(0));
  const Triangle * t2 = dynamic_cast<const Triangle *>(g.at(1));

  EXPECT_EQ(t1->p1(), p.Vertices()[1]);
  EXPECT_EQ(t1->p2(), p.Vertices()[2]);
  EXPECT_EQ(t1->p3(), p.Vertices()[3]);
  EXPECT_EQ(t2->p1(), p.Vertices()[1]);
  EXPECT_EQ(t2->p2(), p.Vertices()[3]);
  EXPECT_EQ(t2->p3(), p.Vertices()[4]);


}


TEST(ObjParser, Polygons)
{
  ObjParser p;
  std::string testfile{TEST_DATA_FOLDER};
  testfile.append("test4.obj");
  EXPECT_EQ(true, p.loadObject(testfile)) << (testfile);
  Group &g{p.defaultGroup()};
  const Triangle * t1 = dynamic_cast<const Triangle *>(g.at(0));
  const Triangle * t2 = dynamic_cast<const Triangle *>(g.at(1));
  const Triangle * t3 = dynamic_cast<const Triangle *>(g.at(2));

  EXPECT_EQ(t1->p1(), p.Vertices()[1]);
  EXPECT_EQ(t1->p2(), p.Vertices()[2]);
  EXPECT_EQ(t1->p3(), p.Vertices()[3]);
  EXPECT_EQ(t2->p1(), p.Vertices()[1]);
  EXPECT_EQ(t2->p2(), p.Vertices()[3]);
  EXPECT_EQ(t2->p3(), p.Vertices()[4]);
  EXPECT_EQ(t3->p1(), p.Vertices()[1]);
  EXPECT_EQ(t3->p2(), p.Vertices()[4]);
  EXPECT_EQ(t3->p3(), p.Vertices()[5]);


}


TEST(ObjParser, NamedGroup)
{
  ObjParser p;
  std::string testfile{TEST_DATA_FOLDER};
  testfile.append("triangles.obj");
  EXPECT_EQ(true, p.loadObject(testfile)) << (testfile);
  Group &g1{p.namedGroup("FirstGroup")};
  Group &g2{p.namedGroup("SecondGroup")};

  const Triangle * t1 = dynamic_cast<const Triangle *>(g1.at(0));
  const Triangle * t2 = dynamic_cast<const Triangle *>(g2.at(0));

  EXPECT_EQ(t1->p1(), p.Vertices()[1]);
  EXPECT_EQ(t1->p2(), p.Vertices()[2]);
  EXPECT_EQ(t1->p3(), p.Vertices()[3]);
  EXPECT_EQ(t2->p1(), p.Vertices()[1]);
  EXPECT_EQ(t2->p2(), p.Vertices()[3]);
  EXPECT_EQ(t2->p3(), p.Vertices()[4]);


}


TEST(ObjParser, Normals)
{
  ObjParser p;
  std::string testfile{TEST_DATA_FOLDER};
  testfile.append("test5.obj");
  EXPECT_EQ(true, p.loadObject(testfile)) << (testfile);
  Group &g{p.defaultGroup()};
  const SmoothTriangle * t1 = dynamic_cast<const SmoothTriangle *>(g.at(0));
  const SmoothTriangle * t2 = dynamic_cast<const SmoothTriangle *>(g.at(1));



  EXPECT_EQ(t1->p1(), p.Vertices()[1]);
  EXPECT_EQ(t1->p2(), p.Vertices()[2]);
  EXPECT_EQ(t1->p3(), p.Vertices()[3]);
  EXPECT_EQ(t1->n1(), p.Normals()[3]);
  EXPECT_EQ(t1->n2(), p.Normals()[1]);
  EXPECT_EQ(t1->n3(), p.Normals()[2]);

  EXPECT_EQ(t2,t2);

}

// The object parser need to support
// Groupt that provides access to triangles
// access to vertices
// objparser object owns the vertices (for now)
