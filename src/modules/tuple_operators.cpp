#include <algorithm>
#include <iostream>
#include <vector>
#include "tuples.h"
#include "utils.h"

namespace ray_lib {


Tuple operator*(const Tuple &lhs, const Tuple &rhs) {
  std::vector<double> z(lhs._vals.size());
  std::transform(lhs._vals.begin(), lhs._vals.end(), rhs._vals.begin(),
                 z.begin(), [](double x, double y) { return (x * y); });
  return Tuple(z);
}


Tuple operator+(const Tuple &lhs, const Tuple &rhs) {
  std::vector<double> z(lhs._vals.size());
  std::transform(lhs._vals.begin(), lhs._vals.end(), rhs._vals.begin(),
                 z.begin(), [](double x, double y) { return (x + y); });
  return Tuple(z);
}

Point operator+(const Point &lhs, const Vector &rhs) {
  std::vector<double> z(lhs._vals.size());
  std::transform(lhs._vals.begin(), lhs._vals.end(), rhs._vals.begin(),
                 z.begin(), [](double x, double y) { return (x + y); });
  return Point(z);
}

Vector operator+(const Vector &lhs, const Vector &rhs) {
  std::vector<double> z(lhs._vals.size());
  std::transform(lhs._vals.begin(), lhs._vals.end(), rhs._vals.begin(),
                 z.begin(), [](double x, double y) { return (x + y); });
  return Vector(z);
}

Tuple operator-(const Tuple &lhs, const Tuple &rhs) {
  std::vector<double> z(lhs._vals.size());
  std::transform(lhs._vals.begin(), lhs._vals.end(), rhs._vals.begin(),
                 z.begin(), [](double x, double y) { return (x - y); });
  return Tuple(z);
}

Vector operator-(const Point &lhs, const Point &rhs) {
  std::vector<double> z(lhs._vals.size());
  std::transform(lhs._vals.begin(), lhs._vals.end(), rhs._vals.begin(),
                 z.begin(), [](double x, double y) { return (x - y); });
  return Vector(z);
}

Tuple operator-(const Tuple &lhs) {
  std::vector<double> y(lhs._vals.size());
  std::transform(lhs._vals.begin(), lhs._vals.end(), y.begin(),
                 [](double x) { return 0 - x; });
  return Tuple(y);
}

std::ostream &operator<<(std::ostream &out, const Tuple &c) {
  out << "( ";
  for (auto a : c._vals) out << a << ",";
  out << ")";
  return out;
}

std::ostream &operator<<(std::ostream &out, const Point &c) {
  out << "( ";
  for (auto a : c._vals) out << a << ",";
  out << ")";
  return out;
}

std::ostream &operator<<(std::ostream &out, const Vector &c) {
  out << "( ";
  for (auto a : c._vals) out << a << ",";
  out << ")";
  return out;
}

}  // namespace ray_lib
