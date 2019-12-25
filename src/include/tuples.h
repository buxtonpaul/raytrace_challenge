#ifndef tuples_h
#define tuples_h

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <limits>
#include <vector>
#include "utils.h"

namespace ray_lib {

class Point;
class Vector;
class Tuple {
 protected:
  std::vector<double> _vals;
  unsigned int _size;

 public:
  Tuple() : _vals({0.0, 0.0, 0.0, 0.0}), _size(4) {}
  explicit Tuple(std::vector<double> a) : _vals(a), _size(a.size()) {}
  Tuple(const Tuple &r) : _vals(r._vals) {}
  bool isPoint() const { return (float_equals(_vals[3], 1.0) && (_size == 4)); }
  bool isVector() const { return ((!isPoint()) && (_size == 4)); }

  bool operator==(const Tuple &obj) const {
    return (std::equal(begin(_vals), end(_vals), begin(obj._vals),
                       end(obj._vals), float_equals));
  }
  // scalar operators
  template <class T>
  friend T operator*(const double &lhs, const T &rhs);
  template <class T>
  friend T operator*(const T &lhs, const double &rhs);
  template <class T>
  friend T operator/(const T &lhs, const double &rhs);

  // IOstream Operators
  friend std::ostream &operator<<(std::ostream &out, const Tuple &c);
  friend std::ostream &operator<<(std::ostream &out, const Point &c);
  friend std::ostream &operator<<(std::ostream &out, const Vector &c);

  friend Tuple operator*(const Tuple &lhs, const Tuple &rhs);
  friend Tuple operator+(const Tuple &lhs, const Tuple &rhs);
  friend Tuple operator-(const Tuple &lhs, const Tuple &rhs);
  friend Tuple operator-(const Tuple &lhs);

  friend Vector operator-(const Point &lhs, const Point &rhs);
  friend Vector operator+(const Vector &lhs, const Vector &rhs);

  friend Point operator+(const Point &lhs, const Vector &rhs);

  friend double magnitude();
  double x() const { return _vals[0]; }
  double y() const { return _vals[1]; }
  double z() const { return _vals[2]; }
  double w() const { return _vals[3]; }

  double x(double x) {
    _vals[0] = x;
    return _vals[0];
  }
  double y(double y) {
    _vals[1] = y;
    return _vals[1];
  }
  double z(double z) {
    _vals[2] = z;
    return _vals[2];
  }
  double w(double w) {
    _vals[3] = w;
    return _vals[3];
  }

  double magnitude() const;
  unsigned int size() const { return _size; }
  const std::vector<double> &Values() const { return (_vals); }
  double &operator[](int index) { return _vals[index]; }
};

class Vector : public Tuple {
 public:
  explicit Vector(std::vector<double> a) : Tuple({a[0], a[1], a[2], 0.0}) {}
  Vector(const Vector &r) : Tuple(r.Values()) {}
  Vector(double x, double y, double z) : Tuple({x, y, z, 0.0}) {}
  friend Point operator+(const Point &lhs, const Vector &rhs);
  Vector normalise() const { return (*this / this->magnitude()); }
  double dotproduct(const Vector &r) const;
  Vector crossproduct(const Vector &r) const;
};

class Point : public Tuple {
 public:
  explicit Point(std::vector<double> a) : Tuple({a[0], a[1], a[2], 1.0}) {}
  Point(const Point &r) : Tuple(r.Values()) {}
  Point(double x, double y, double z) : Point({x, y, z, 0.0}) {}
  friend Point operator+(const Point &lhs, const Vector &rhs);
};

// The template operators.
// have to be in a header due to being compiled on demand
template <class T>
T operator*(const double &lhs, const T &rhs) {
  std::vector<double> y(rhs._vals.size());
  std::transform(rhs._vals.begin(), rhs._vals.end(), y.begin(),
                 [lhs](double x) { return x * lhs; });
  return T(y);
}

template <class T>
T operator*(const T &lhs, const double &rhs) {
  std::vector<double> y(lhs._vals.size());
  std::transform(lhs._vals.begin(), lhs._vals.end(), y.begin(),
                 [rhs](double x) { return x * rhs; });
  return T(y);
}

template <class T>
T operator/(const T &lhs, const double &rhs) {
  std::vector<double> y(lhs._vals.size());
  std::transform(lhs._vals.begin(), lhs._vals.end(), y.begin(),
                 [rhs](double x) { return x / rhs; });
  return T(y);
}

}  // namespace ray_lib
#endif
