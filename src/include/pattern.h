#ifndef _pattern_h_
#define _pattern_h_
#include <memory>
#include <utility>
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
  explicit Pattern(const Matrix &transform = Matrix::Identity) : _transform(transform) {}
  Matrix getTransform() const { return _transform; }
  virtual std::unique_ptr<Pattern> clone() const = 0;
  virtual ~Pattern(){}
  bool operator==(const Pattern &other)const;
  virtual bool isEqual(const Pattern &other) const = 0;

protected:
  Matrix _transform;
};
class MultiColorPattern
{
public:
  MultiColorPattern(const Color &a, const Color &b) : _a{a}, _b{b} {}
  MultiColorPattern(const MultiColorPattern &other) : _a(other._a), _b(other._b) {}
  virtual ~MultiColorPattern() {}
  Color getColor_a() const;
  Color getColor_b() const;
  Color setColor_a(const Color &newcol);
  Color setColor_b(const Color &newcol);
  bool isEqual(const Pattern &other) const;

protected:
  Color _a = Color::White;
  Color _b = Color::White;
};

class StripePattern : public Pattern, MultiColorPattern
{
public:
  Color getColor(const Point &p) const;
  StripePattern(const Color &a, const Color &b, const Matrix &transform = Matrix::Identity);
  std::unique_ptr<Pattern> clone() const;
  bool isEqual(const Pattern &other) const;
};

class SolidPattern : public Pattern
{
  Color _a;

public:
  Color getColor(const Point &p) const;
  explicit SolidPattern(const Color &a = Color::White) : _a(a) {}
  SolidPattern(const SolidPattern &other) : _a(other._a) {}
  Color setColor(const Color &newcol);
  std::unique_ptr<Pattern> clone() const;
  bool isEqual(const Pattern &other) const;

  ~SolidPattern() {}
};

class TestPattern : public Pattern
{
public:
  Color getColor(const Point &p) const;
  explicit TestPattern(const Matrix &m) : Pattern(m) {}
  TestPattern() : Pattern(Matrix::Identity) {}
  std::unique_ptr<Pattern> clone() const;

  bool isEqual(const Pattern &other) const;
};

class GradientPattern : public Pattern, MultiColorPattern
{
public:
  Color getColor(const Point &p) const;
  GradientPattern(const Color &a, const Color &b, const Matrix &transform = Matrix::Identity);
  std::unique_ptr<Pattern> clone() const;
  bool isEqual(const Pattern &other) const;
};

class RingPattern : public Pattern, MultiColorPattern
{
public:
  Color getColor(const Point &p) const;
  RingPattern(const Color &a, const Color &b, const Matrix &transform = Matrix::Identity);
  std::unique_ptr<Pattern> clone() const;
  bool isEqual(const Pattern &other) const;
};

class CheckPattern3d : public Pattern, MultiColorPattern
{
public:
  Color getColor(const Point &p) const;
  CheckPattern3d(const Color &a, const Color &b, const Matrix &transform = Matrix::Identity);
  std::unique_ptr<Pattern> clone() const;
  bool isEqual(const Pattern &other) const;
};

} // namespace ray_lib
#endif // _pattern_h_
