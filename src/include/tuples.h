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

class Tuple {
 private:
  std::vector<double> _vals;
  unsigned int _size;

 public:
  explicit Tuple(std::vector<double> a) : _vals(a), _size(a.size()) {}
  Tuple(const Tuple &r) : _vals(r._vals) {}
  bool isPoint() const { return (float_equals(_vals[3], 1.0) && (_size == 4)); }
  bool isVector() const { return ((!isPoint()) && (_size == 4)); }
  double magnitude() const;
  Tuple normalise() const { return (*this / this->magnitude()); }
  double dotproduct(const Tuple &r) const;
  Tuple crossproduct(const Tuple &r) const;

  bool operator==(const Tuple &obj) const {
    return (std::equal(begin(_vals), end(_vals), begin(obj._vals),
                       end(obj._vals), float_equals));
  }

  // Operators
  friend std::ostream &operator<<(std::ostream &out, const Tuple &c);
  friend Tuple operator*(const double &lhs, const Tuple &rhs);
  friend Tuple operator*(const Tuple &lhs, const double &rhs);
  friend Tuple operator*(const Tuple &lhs, const Tuple &rhs);
  friend Tuple operator/(const Tuple &lhs, const double &rhs);
  friend Tuple operator+(const Tuple &lhs, const Tuple &rhs);
  friend Tuple operator-(const Tuple &lhs, const Tuple &rhs);
  friend Tuple operator-(const Tuple &lhs);

  double x() const { return _vals[0]; }
  double y() const { return _vals[1]; }
  double z() const { return _vals[2]; }
  double w() const { return _vals[3]; }
  unsigned int size() const { return _size; }
  const std::vector<double> &Values() const { return (_vals); }
  double &operator[](int index) { return _vals[index]; }
};
// helper functions to create Vectors and Points, which are tuples
// of size 4 (x,y,z,w) with W being either 0 (Vector) or 1(point) depending on
Tuple Vector(double x, double y, double z);
Tuple Point(double x, double y, double z);

}  // namespace ray_lib
#endif
