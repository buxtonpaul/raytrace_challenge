#include "color.h"
#include <ostream>
#include "utils.h"

Color operator+(const Color &lhs, const Color &rhs)
{
  std::array<double, 3> vals;
  for (unsigned int i = 0; i < 3; ++i)
  {
    vals[i] = lhs.Values()[i] + rhs.Values()[i];
  }
  return Color(vals[0], vals[1], vals[2]);
}

Color operator-(const Color &lhs, const Color &rhs)
{
  std::array<double, 3> vals;
  for (unsigned int i = 0; i < 3; ++i)
  {
    vals[i] = lhs.Values()[i] - rhs.Values()[i];
  }
  return Color(vals[0], vals[1], vals[2]);
}

Color operator*(const Color &color, const double scalar)
{
  std::array<double, 3> vals;
  for (unsigned int i = 0; i < 3; ++i)
  {
    vals[i] = color.Values()[i] * scalar;
  }
  return Color(vals[0], vals[1], vals[2]);
}

Color operator*(const double scalar, const Color &color)
{
  std::array<double, 3> vals;
  for (unsigned int i = 0; i < 3; ++i)
  {
    vals[i] = color.Values()[i] * scalar;
  }
  return Color(vals[0], vals[1], vals[2]);
}

Color operator*(const Color &lhs, const Color &rhs)
{
  std::array<double, 3> vals;
  for (unsigned int i = 0; i < 3;
       ++i)
  { // multiplcation according to the hadamard product
    vals[i] = lhs.Values()[i] * rhs.Values()[i];
  }
  return Color(vals[0], vals[1], vals[2]);
}

bool operator==(const Color &lhs, const Color &rhs)
{
  return std::equal(lhs.Values().begin(), lhs.Values().end(),
                    rhs.Values().begin(), rhs.Values().end(), float_equals);
}

std::ostream &operator<<(std::ostream &out, const Color &c)
{
  out << "( ";
  for (auto a : c.Values())
    out << a << ",";
  out << ")";
  return out;
}

const Color Color::Black = Color(0.0, 0.0, 0.0);
const Color Color::White = Color(1.0, 1.0, 1.0);
