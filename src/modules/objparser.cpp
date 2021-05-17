#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "objparser.h"
#include "group.h"
#include "triangle.h"



#include <algorithm> 
#include <cctype>
#include <locale>

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s) {
    trim(s);
    return s;
}
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
    _normals.push_back({0, 0, 0});
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
    std::string trimmed{line};
    ltrim(trimmed);
    if(trimmed.size() ==0)
      return true;
    std::stringstream tmp(trimmed);
    std::string command;
    tmp >> command;
    if (command == "v")
      return addVertex(line);
    if (command == "vn")
      return addVertexNormal(line);

    if (command == "f")
      return addFace(line);
    if (command == "g")
      return addGroup(line);
    if (command == "#")
      return true;

    return false;
  }

  const std::vector<Point> &ObjParser::Vertices()
  {
    return _vertices;
  }

  const std::vector<Vector> &ObjParser::Normals()
  {
    return _normals;
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

  bool ObjParser::addVertexNormal(std::string const &line)
  {
    std::stringstream input(line);
    std::string tmp;
    double x, y, z;
    if (input >> tmp >> x >> y >> z)
    {
      if (tmp == "vn")
      {
        _normals.push_back(Vector(x, y, z));
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
    std::string a;

    // we need to get list of vertices as a list.
    // if the items have normals then we create a smooth triangle, else a regular one.

    std::vector<int> v_idx;
    std::vector<int> vn_idx;

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
      trim(a);
      int idx, texid, vnidx;
      if (a == "" || a.size() == 0)
        continue;
      if (sscanf(a.c_str(), "%d/%d/%d", &idx, &texid, &vnidx) == 3)
      {
        v_idx.push_back(idx);
        vn_idx.push_back(vnidx);
      }
      else if (sscanf(a.c_str(), "%d//%d", &idx, &vnidx) == 2)
      {
        v_idx.push_back(idx);
        vn_idx.push_back(vnidx);
      }
      else if (sscanf(a.c_str(), "%d", &idx) == 1)
      {
        v_idx.push_back(idx);
      }
      else
        return false;
    }
    if (vn_idx.size() == 0)
    {
      for (int index = 1; index < v_idx.size() - 1; ++index)
      {
        _faces.push_back(std::shared_ptr<Triangle>(new Triangle(_vertices[v_idx[0]], _vertices[v_idx[index]], _vertices[v_idx[index + 1]])));
        _newestGroup->add_child(static_cast<Shape *>(_faces.back().get()));
      }
    }
    else
    {
      for (int index = 1; index < v_idx.size() - 1; ++index)
      {
        _faces.push_back(std::shared_ptr<SmoothTriangle>(new SmoothTriangle(_vertices[v_idx[0]], _vertices[v_idx[index]], _vertices[v_idx[index + 1]], _normals[vn_idx[0]], _normals[vn_idx[index]], _normals[vn_idx[index + 1]])));
        _newestGroup->add_child(static_cast<Shape *>(_faces.back().get()));
      }
    }
    return (true);
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
