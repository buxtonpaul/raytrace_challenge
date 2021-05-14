#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "objparser.h"
#include "group.h"
#include "triangle.h"

namespace ray_lib
{

  ObjParser::ObjParser() {}

  bool ObjParser::ParseFile(const std::string &infile)
  {
    bool isValid{true};
    int lineno = 0;
    _vertices.clear();
    // add a single dummy point which fixes the vertex count index behaviour of objfiles, which are 1 based
    _vertices.push_back({0, 0, 0});
    std::ifstream input(infile);
    std::string str;
    _newestGroup = &_defaultGroup;
    while (std::getline(input, str))
    {
      ++lineno;
      isValid = ParseLine(str);
      if (!isValid)
        break;
    }
    input.close();
    return isValid;
  }

  bool ObjParser::ParseLine(std::string const &line)
  {
    if (line.size() > 0)
    {
      switch (line.at(0))
      {
      case 'v':
        return addVertex(line);
        break;
      case 'f':
        return addFace(line);
        break;

      case 'g':
        return addGroup(line);
        break;

      default:
        return false;
      }

      return false;
    }
    return true;
  }

  const std::vector<Point> &ObjParser::Vertices()
  {
    return _vertices;
  }

  bool ObjParser::addVertex(std::string const &line)
  {
    std::stringstream input(line);
    char tmp;
    double x, y, z;
    if (input >> tmp >> x >> y >> z)
    {
      if (tmp == 'v')
      {
        _vertices.push_back(Point(x, y, z));
        return true;
      }
    }
  }

  bool ObjParser::addGroup(std::string const &line)
  {
    std::stringstream input(line);
    char g;
    std::string name;
    if (input >> g >> name)
    {
      if (g == 'g')
      {
        _namedGroups.push_back(std::tuple<std::string, Group>(name, Group()));
        _newestGroup = &(std::get<1>(_namedGroups.back()));
        _defaultGroup.add_child(&std::get<1>(_namedGroups.back()));
        return true;
      }
    }
  }

  bool ObjParser::addFace(std::string const &line)
  {
    std::stringstream input(line);
    char tmp = ' ';
    int a, b, c;

    // we need to get list of vertices as a list.
    std::vector<int> v_idx;

    if (input >> tmp)
    {
      if (tmp != 'f')
        return false;
    }
    else
    {
      return false;
    }
    while (input >> a)
    {
      v_idx.push_back(a);
    }

    for (int index = 1; index < v_idx.size() - 1; ++index)
    {
      _faces.push_back(std::shared_ptr<Triangle>(new Triangle(_vertices[v_idx[0]], _vertices[v_idx[index]], _vertices[v_idx[index + 1]])));
      _newestGroup->add_child(static_cast<Shape *>(_faces.back().get()));
    }
    return (true);
    // if (input >> tmp >> a >> b >> c)
    // {
    //   if (tmp == 'f')
    //   {
    //     _faces.push_back(std::shared_ptr<Triangle>( new Triangle(_vertices[a], _vertices[b], _vertices[c])));
    //     _defaultGroup.add_child(static_cast< Shape *>(_faces.back().get()));
    //     return true;
    //   }
    // }
  }

  Group &ObjParser::defaultGroup()
  {
    return _defaultGroup;
  }

  Group &ObjParser::namedGroup(const std::string groupName)
  {
    auto it = std::find_if(_namedGroups.begin(), _namedGroups.end(),
     [groupName](const std::tuple<std::string, Group> &e) { return std::get<0>(e) == groupName; });
    if (it != _namedGroups.end())
      return std::get<1>(*it);
    throw("Named item not found");
  }

} // namespace ray_lib
