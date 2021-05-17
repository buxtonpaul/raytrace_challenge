#ifndef _objparser_h_
#define _objparser_h_
#include <vector>
#include <memory>
#include <string>
#include <tuple>
#include "triangle.h"
#include "tuples.h"
#include "group.h"

namespace ray_lib
{
class ObjParser
  {
  public:
    ObjParser();
    bool ParseFile(const std::string &inputfile);
    const std::vector<Point> &Vertices();
    const std::vector<Vector> &Normals();
    Group &defaultGroup();
    Group &namedGroup(const std::string groupName);
  private:
    std::vector<Point> _vertices;
    std::vector<Vector> _normals;
    std::vector<std::shared_ptr<Shape>> _faces;
    bool ParseLine(std::string const &line);
    bool addVertex(std::string const &line);
    bool addFace(std::string const &line);
    bool addGroup(std::string const &line);
    bool addVertexNormal(std::string const &line);
    Group _defaultGroup;
    Group *_newestGroup;
    std::vector<std::tuple<std::string, Group>> _namedGroups;
  };

} // namespace ray_lib
#endif //_objparser_h_
