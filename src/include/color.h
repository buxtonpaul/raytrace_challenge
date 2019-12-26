#include <array>
#ifndef color_h
#define color_h

class Color {
 private:
  std::array<double, 3> _values;

 public:
  explicit Color(double red, double green, double blue)
      : _values({red, green, blue}) {}
  double red() const { return _values[0]; }
  double green() const { return _values[1]; }
  double blue() const { return _values[2]; }
  const std::array<double, 3> &Values() const { return _values; }
};

bool operator==(const Color &lhs, const Color &rhs);
Color operator+(const Color &lhs, const Color &rhs);
Color operator-(const Color &lhs, const Color &rhs);
Color operator*(const Color &color, const double scalar);
Color operator*(const double scalar, const Color &color);
Color operator*(const Color &lhs, const Color &rhs);
std::ostream &operator<<(std::ostream &out, const Color &c);

#endif  // color_h
