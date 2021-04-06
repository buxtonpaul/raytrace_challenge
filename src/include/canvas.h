#ifndef _canvas_h_
#define _canvas_h_
#include <string>
#include <vector>
#include "color.h"
class Canvas {
  unsigned int _width;
  unsigned int _height;
  std::vector<double> _canvasdata;
  std::string row_to_string(const unsigned int row) const;

 public:
  Canvas(unsigned int width, unsigned int height)
      : _width(width), _height(height), _canvasdata(width * height * 3, 0) {}
  Color pixel(const unsigned int x, const unsigned int y) const;
  void pixel(const unsigned int x, const unsigned int y, const Color &toset);
  std::string ppm() const;
  unsigned int width() const { return _width; }
  unsigned int height() const { return _height; }
};

#endif  //_canvas_h_
