#include "canvas.h"
#include <assert.h>
#include <iostream>
#include <string>
#include "color.h"
#include "utils.h"

Color Canvas::Pixel(const unsigned int x, const unsigned int y) const {
  assert(x < _width);
  assert(y < _height);

  unsigned int index = (y * _width + x) * 3;
  return Color(
      _canvasdata[index], _canvasdata[index + 1], _canvasdata[index + 2]);
}

void Canvas::Pixel(const unsigned int x, const unsigned int y,
                   const Color &toset) {
  if ((x >= _width) || (y >= _height)) return;
  unsigned int index = (y * _width + x) * 3;
  _canvasdata[index] = toset.red();
  _canvasdata[index + 1] = toset.green();
  _canvasdata[index + 2] = toset.blue();
}

std::string Canvas::ppm() const {
  std::string out;
  out += "P3\n";
  out += std::to_string(_width) + " " += std::to_string(_height) + "\n";
  out += "255\n";
  for (unsigned int j = 0; j < _height; ++j) {
    out += row_to_string(j);
  }
  return out;
}

unsigned int val_to_int(double val) {
  double output = val * 255;
  output = output > 255 ? 255 : output;
  output = output < 0 ? 0 : output;
  return (unsigned int)(output + 0.5);
}

std::string Canvas::row_to_string(const unsigned int row) const {
  std::string out;
  unsigned int start_index = row * _width * 3;
  std::string space = "";
  unsigned int count = 0;
  for (unsigned int i = 0; i < _width; ++i) {
    out += space,
        out += std::to_string(val_to_int(_canvasdata[start_index + i * 3]));
    out += " ";
    out += std::to_string(val_to_int(_canvasdata[start_index + i * 3 + 1]));
    out += " ";
    out += std::to_string(val_to_int(_canvasdata[start_index + i * 3 + 2]));
    space = std::string(" ");
  }
  out = limitlinelength(out, 70);
  out += "\n";
  return out;
}
