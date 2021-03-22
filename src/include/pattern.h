#ifndef _pattern_h_
#define _pattern_h_
#include "color.h"
#include "tuples.h"

namespace ray_lib
{
class Pattern
{
public:
  virtual Color getColor(const Point p) const = 0;
  Pattern *asPattern() { return reinterpret_cast<Pattern *>(this); }
};

class StripePattern : public Pattern
{
  Color _a;
  Color _b;

public:
  Color getColor(const Point p) const;
  Color getColor_a() const { return _a; }
  Color getColor_b() const { return _b; }
  StripePattern(Color a, Color b) : _a(a), _b(b) {}
  Color setColor_a(const Color &newcol)
  {
    _a = newcol;
    return _a;
  }
  Color setColor_b(const Color &newcol)
  {
    _b = newcol;
    return _b;
  }
};

class SolidPattern : public Pattern
{
  Color _a;

public:
  Color getColor(const Point p) const;
  explicit SolidPattern(Color a = Color::White) : _a(a) {}
  Color setColor(const Color &newcol)
  {
    _a = newcol;
    return _a;
  }
};

extern SolidPattern SolidWhite;

} // namespace ray_lib
#endif // _pattern_h_
