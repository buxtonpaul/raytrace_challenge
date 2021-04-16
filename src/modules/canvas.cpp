#include "canvas.h"
#include <assert.h>
#include <iostream>
#include <string>
#include <png.h>
#include "color.h"
#include "utils.h"

Color Canvas::pixel(const unsigned int x, const unsigned int y) const
{
  assert(x < _width);
  assert(y < _height);

  unsigned int index{(y * _width + x) * 3};
  return Color(
      _canvasdata[index], _canvasdata[index + 1], _canvasdata[index + 2]);
}

void Canvas::pixel(const unsigned int x, const unsigned int y,
                   const Color &toset)
{
  if ((x >= _width) || (y >= _height))
    return;
  unsigned int index{(y * _width + x) * 3};
  _canvasdata[index] = toset.red();
  _canvasdata[index + 1] = toset.green();
  _canvasdata[index + 2] = toset.blue();
}

std::string Canvas::ppm() const
{
  std::string out;
  out += "P3\n";
  out += std::to_string(_width) + " " += std::to_string(_height) + "\n";
  out += "255\n";
  for (unsigned int j = 0; j < _height; ++j)
  {
    out += row_to_string(j);
  }
  return out;
}

char clamp255(double colval)
{
  if (colval < 0)
    return 0;
  if (colval >= 1.0)
    return 255;
  return static_cast<char>(colval * 255);
}

void Canvas::png(const std::string &filename) const
{
  // png file sample uses 32bit ARGB
  png_bytep *row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * _height);
  for (int y = 0; y < _height; y++)
  {
    row_pointers[y] = (png_byte *)malloc(_width * 4);
  }
  unsigned long outbuf[_height][_width] = {0};

  for (int y = 0; y < _height; y++)
  {
    png_bytep row = row_pointers[y];
    for (int x = 0; x < _width; x++)
    {
      auto p{pixel(x, y)};
      char redval{clamp255(p.red())};
      char greenval{clamp255(p.green())};
      char blueval{clamp255(p.blue())};
      png_bytep px = &(row[x * 4]);
      px[0] = redval;
      px[1] = greenval;
      px[2] = blueval;
      px[3] = 0xff;
    }
  }

  FILE *fp = fopen(filename.data(), "wb");
  if (!fp)
    abort();

  png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png)
    abort();

  png_infop info = png_create_info_struct(png);
  if (!info)
    abort();

  if (setjmp(png_jmpbuf(png)))
    abort();

  png_init_io(png, fp);

  // Output is 8bit depth, RGBA format.
  png_set_IHDR(
      png,
      info,
      _width, _height,
      8,
      PNG_COLOR_TYPE_RGBA,
      PNG_INTERLACE_NONE,
      PNG_COMPRESSION_TYPE_DEFAULT,
      PNG_FILTER_TYPE_DEFAULT);
  png_write_info(png, info);

  // To remove the alpha channel for PNG_COLOR_TYPE_RGB format,
  // Use png_set_filler().
  //png_set_filler(png, 0, PNG_FILLER_AFTER);

  if (!row_pointers)
    abort();

  png_write_image(png, row_pointers);
  png_write_end(png, NULL);

  for (int y = 0; y < _height; y++)
  {
    free(row_pointers[y]);
  }
  free(row_pointers);

  fclose(fp);
  if (png && info)
    png_destroy_write_struct(&png, &info);
}

unsigned int val_to_int(double val)
{
  double output{val * 255};
  output = output > 255 ? 255 : output;
  output = output < 0 ? 0 : output;
  return (unsigned int)(output + 0.5);
}

std::string Canvas::row_to_string(const unsigned int row) const
{
  std::string out;
  unsigned int start_index = row * _width * 3;
  std::string space{""};
  unsigned int count{0};
  for (unsigned int i = 0; i < _width; ++i)
  {
    out += space, // TODO(me) should this be a ;  ?
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
