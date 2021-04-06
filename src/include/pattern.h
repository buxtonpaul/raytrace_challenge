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
  bool operator==(const Pattern &other) const
  {
    // If the derived types are the same then compare them
    return typeid(*this) == typeid(other) && isEqual(other);
  }
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
  Color getColor_a() const { return _a; }
  Color getColor_b() const { return _b; }
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
  bool isEqual(const Pattern &other) const
  {
    const MultiColorPattern b{dynamic_cast<const MultiColorPattern &>(other)};
    return (_a == b._a && _b == b._b);
  }

protected:
  Color _a = Color::White;
  Color _b = Color::White;
};

class StripePattern : public Pattern, MultiColorPattern
{
public:
  Color getColor(const Point &p) const;
  StripePattern(const Color &a, const Color &b, const Matrix &transform = Matrix::Identity) : Pattern(transform), MultiColorPattern{a, b} {}
  std::unique_ptr<Pattern> clone() const
  {
    return std::make_unique<StripePattern>(*this);
  }
  bool isEqual(const Pattern &other) const
  {
    const StripePattern b{static_cast<const StripePattern &>(other)};
    return (_a == b._a && _b == b._b);
  }
};

class SolidPattern : public Pattern
{
  Color _a;

public:
  Color getColor(const Point &p) const;
  explicit SolidPattern(const Color &a = Color::White) : _a(a) {}
  SolidPattern(const SolidPattern &other) : _a(other._a) {}
  Color setColor(const Color &newcol)
  {
    _a = newcol;
    return _a;
  }
  std::unique_ptr<Pattern> clone() const
  {
    return std::make_unique<SolidPattern>(SolidPattern(*this));
  }
  bool isEqual(const Pattern &other) const
  {
    const SolidPattern b{static_cast<const SolidPattern &>(other)};
    return (_a == b._a);
  }

  ~SolidPattern() {}
};

class TestPattern : public Pattern
{
public:
  Color getColor(const Point &p) const
  {
    Point patPoint{_transform.inverse() * p};
    return Color(patPoint.x(), patPoint.y(), patPoint.z());
  }
  explicit TestPattern(const Matrix &m) : Pattern(m) {}
  TestPattern() : Pattern(Matrix::Identity) {}
  std::unique_ptr<Pattern> clone() const
  {
    return std::make_unique<TestPattern>(*this);
  }

  bool isEqual(const Pattern &other) const
  {
    return true;
  }
};

class GradientPattern : public Pattern, MultiColorPattern
{
public:
  Color getColor(const Point &p) const;
  GradientPattern(const Color &a, const Color &b, const Matrix &transform = Matrix::Identity) : Pattern{transform}, MultiColorPattern(a, b) {}
  std::unique_ptr<Pattern> clone() const
  {
    return std::make_unique<GradientPattern>(*this);
  }
  bool isEqual(const Pattern &other) const
  {
    const GradientPattern b{static_cast<const GradientPattern &>(other)};
    return (_a == b._a && _b == b._b);
  }
};

class RingPattern : public Pattern, MultiColorPattern
{
public:
  Color getColor(const Point &p) const;
  RingPattern(const Color &a, const Color &b, const Matrix &transform = Matrix::Identity) : Pattern{transform}, MultiColorPattern(a, b) {}
  std::unique_ptr<Pattern> clone() const
  {
    return std::make_unique<RingPattern>(*this);
  }
  bool isEqual(const Pattern &other) const
  {
    const RingPattern b{static_cast<const RingPattern &>(other)};
    return (_a == b._a && _b == b._b);
  }
};

class CheckPattern3d : public Pattern, MultiColorPattern
{
public:
  Color getColor(const Point &p) const;
  CheckPattern3d(const Color &a, const Color &b, const Matrix &transform = Matrix::Identity) : Pattern{transform}, MultiColorPattern(a, b) {}
  std::unique_ptr<Pattern> clone() const
  {
    return std::make_unique<CheckPattern3d>(*this);
  }
  bool isEqual(const Pattern &other) const
  {
    const CheckPattern3d b{static_cast<const CheckPattern3d &>(other)};
    return (_a == b._a && _b == b._b);
  }
};

} // namespace ray_lib
#endif // _pattern_h_
