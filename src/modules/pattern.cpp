#include "pattern.h"
#include <cmath>
#include "tuples.h"
namespace ray_lib
{
  Color StripePattern::getColor(const ray_lib::Point &p) const
  {
    Point patPoint{_transform.inverse() * p};
    int c{static_cast<int>(floor(patPoint.x()))};
    return ((c % 2) == 0 ? _a : _b);
  }

  Color SolidPattern::getColor(const ray_lib::Point &p) const
  {
    return (_a);
  }

  Color GradientPattern::getColor(const ray_lib::Point &p) const
  {
    Point patPoint{_transform.inverse() * p};
    Color outcl{_a + (_b - _a) * (patPoint.x() - floor(patPoint.x()))};
    return outcl;
  }

  Color RingPattern::getColor(const ray_lib::Point &p) const
  {
    Point patPoint{_transform.inverse() * p};
    int c{static_cast<int>(floor(sqrt(patPoint.x() * patPoint.x() + patPoint.z() * patPoint.z())))};
    return ((c % 2) == 0 ? _a : _b);
  }

  Color CheckPattern3d::getColor(const ray_lib::Point &p) const
  {
    Point patPoint{_transform.inverse() * p};
    int c{static_cast<int>(floor(patPoint.x()) + floor(patPoint.y()) + floor(patPoint.z()))};
    return ((c % 2) == 0 ? _a : _b);
  }

  bool Pattern::operator==(const Pattern &other) const
  {
    // If the derived types are the same then compare them
    return typeid(*this) == typeid(other) && isEqual(other);
  }

  Color MultiColorPattern::getColor_a() const { return _a; }
  Color MultiColorPattern::getColor_b() const { return _b; }
  Color MultiColorPattern::setColor_a(const Color &newcol)
  {
    _a = newcol;
    return _a;
  }
  Color MultiColorPattern::setColor_b(const Color &newcol)
  {
    _b = newcol;
    return _b;
  }
  bool MultiColorPattern::isEqual(const Pattern &other) const
  {
    const MultiColorPattern b{dynamic_cast<const MultiColorPattern &>(other)};
    return (_a == b._a && _b == b._b);
  }

  StripePattern::StripePattern(const Color &a, const Color &b, const Matrix &transform) : Pattern(transform), MultiColorPattern{a, b} {}
  std::unique_ptr<Pattern> StripePattern::clone() const
  {
    return std::make_unique<StripePattern>(*this);
  }
  bool StripePattern::isEqual(const Pattern &other) const
  {
    const StripePattern b{static_cast<const StripePattern &>(other)};
    return (_a == b._a && _b == b._b);
  }

  Color SolidPattern::setColor(const Color &newcol)
  {
    _a = newcol;
    return _a;
  }
  std::unique_ptr<Pattern> SolidPattern::clone() const
  {
    return std::make_unique<SolidPattern>(SolidPattern(*this));
  }
  bool SolidPattern::isEqual(const Pattern &other) const
  {
    const SolidPattern b{static_cast<const SolidPattern &>(other)};
    return (_a == b._a);
  }

  std::unique_ptr<Pattern> TestPattern::clone() const
  {
    return std::make_unique<TestPattern>(*this);
  }

  bool TestPattern::isEqual(const Pattern &other) const
  {
    return true;
  }
  Color TestPattern::getColor(const Point &p) const
  {
    Point patPoint{_transform.inverse() * p};
    return Color(patPoint.x(), patPoint.y(), patPoint.z());
  }

  GradientPattern::GradientPattern(const Color &a, const Color &b, const Matrix &transform) : Pattern{transform}, MultiColorPattern(a, b) {}
  std::unique_ptr<Pattern> GradientPattern::clone() const
  {
    return std::make_unique<GradientPattern>(*this);
  }
  bool GradientPattern::isEqual(const Pattern &other) const
  {
    const GradientPattern b{static_cast<const GradientPattern &>(other)};
    return (_a == b._a && _b == b._b);
  }

  RingPattern::RingPattern(const Color &a, const Color &b, const Matrix &transform) : Pattern{transform}, MultiColorPattern(a, b) {}
  std::unique_ptr<Pattern> RingPattern::clone() const
  {
    return std::make_unique<RingPattern>(*this);
  }
  bool RingPattern::isEqual(const Pattern &other) const
  {
    const RingPattern b{static_cast<const RingPattern &>(other)};
    return (_a == b._a && _b == b._b);
  }

  CheckPattern3d::CheckPattern3d(const Color &a, const Color &b, const Matrix &transform) : Pattern{transform}, MultiColorPattern(a, b) {}
  std::unique_ptr<Pattern> CheckPattern3d::clone() const
  {
    return std::make_unique<CheckPattern3d>(*this);
  }
  bool CheckPattern3d::isEqual(const Pattern &other) const
  {
    const CheckPattern3d b{static_cast<const CheckPattern3d &>(other)};
    return (_a == b._a && _b == b._b);
  }

} // namespace ray_lib
