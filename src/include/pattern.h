#ifndef _pattern_h_
#define _pattern_h_
#include "color.h"
#include "tuples.h"
#include "matrix.h"
namespace ray_lib
{
class Pattern
{
public:
  virtual Color getColor(const Point &p) const = 0;
  Pattern *asPattern() { return reinterpret_cast<Pattern *>(this); }
  explicit Pattern(const Matrix &transform = Matrix::Identity) : _transform(transform), _inverse(transform.inverse()) {}
  Matrix getTransform() const { return _transform; }

protected:
  Matrix _transform;
  Matrix _inverse;
};

class StripePattern : public Pattern
{
public:
  Color getColor(const Point &p) const;
  Color getColor_a() const { return _a; }
  Color getColor_b() const { return _b; }
  StripePattern(const Color &a, const Color &b, const Matrix &transform = Matrix::Identity) : Pattern(transform), _a(a), _b(b) {}
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

private:
  Color _a;
  Color _b;
};

class SolidPattern : public Pattern
{
  Color _a;

public:
  Color getColor(const Point &p) const;
  explicit SolidPattern(const Color &a = Color::White) : _a(a) {}
  Color setColor(const Color &newcol)
  {
    _a = newcol;
    return _a;
  }
};

class TestPattern : public Pattern
{
public:
  Color getColor(const Point &p) const
  {
    Point patPoint{_inverse * p};
    return Color(patPoint.x(), patPoint.y(), patPoint.z());
  }
  explicit TestPattern(const Matrix &m) : Pattern(m) {}
  TestPattern() : Pattern(Matrix::Identity) {}
};
  extern SolidPattern SolidWhite;

} // namespace ray_lib
#endif // _pattern_h_
