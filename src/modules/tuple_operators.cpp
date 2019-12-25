#include <algorithm>
#include <iostream>
#include <vector>
#include "tuples.h"
#include "utils.h"

namespace ray_lib {

Tuple operator*(const double &lhs, const Tuple &rhs) {
  std::vector<double> y(rhs._vals.size());
  std::transform(rhs._vals.begin(), rhs._vals.end(), y.begin(),
                 [lhs](double x) { return x * lhs; });
  return Tuple(y);
}

Tuple operator*(const Tuple &lhs, const double &rhs) {
  std::vector<double> y(lhs._vals.size());
  std::transform(lhs._vals.begin(), lhs._vals.end(), y.begin(),
                 [rhs](double x) { return x * rhs; });
  return Tuple(y);
}

Vector operator*(const Vector &lhs, const double &rhs) {
  std::vector<double> y(lhs._vals.size());
  std::transform(lhs._vals.begin(), lhs._vals.end(), y.begin(),
                 [rhs](double x) { return x * rhs; });
  return Vector(y);
}

Vector operator*(const double &lhs, const Vector &rhs) {
  std::vector<double> y(rhs._vals.size());
  std::transform(rhs._vals.begin(), rhs._vals.end(), y.begin(),
                 [lhs](double x) { return x * lhs; });
  return Vector(y);
}

Tuple operator*(const Tuple &lhs, const Tuple &rhs) {
  std::vector<double> z(lhs._vals.size());
  std::transform(lhs._vals.begin(), lhs._vals.end(), rhs._vals.begin(),
                 z.begin(), [](double x, double y) { return (x * y); });
  return Tuple(z);
}

Vector operator/(const Vector &lhs, const double &rhs) {
  std::vector<double> y(lhs._vals.size());
  std::transform(lhs._vals.begin(), lhs._vals.end(), y.begin(),
                 [rhs](double x) { return x / rhs; });
  return Vector(y);
}

Tuple operator/(const Tuple &lhs, const double &rhs) {
  std::vector<double> y(lhs._vals.size());
  std::transform(lhs._vals.begin(), lhs._vals.end(), y.begin(),
                 [rhs](double x) { return x / rhs; });
  return Tuple(y);
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