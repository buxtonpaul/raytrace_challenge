#include <iostream>
#include <vector>
#include <algorithm>
#include "tuples.h"
#include "utils.h"

namespace ray_lib
{
double Tuple::dotproduct(const Tuple &r) const
{
  double sum = 0;
  for (unsigned int i = 0; i < this->Values().size(); ++i)
    sum += (this->Values()[i] * r.Values()[i]);
  return sum;
}

Tuple Tuple::crossproduct(const Tuple &r) const
{
  return Vector(this->y() * r.z() - this->z() * r.y(),
                this->z() * r.x() - this->x() * r.z(),
                this->x() * r.y() - this->y() * r.x());
}

Tuple operator*(const double &lhs, const Tuple &rhs)
{
  std::vector<double> y(rhs._vals.size());
  std::transform(rhs._vals.begin(), rhs._vals.end(), y.begin(),
                 [lhs](double x) { return x * lhs; });
  return Tuple(y);
}

Tuple operator*(const Tuple &lhs, const double &rhs)
{
  std::vector<double> y(lhs._vals.size());
  std::transform(lhs._vals.begin(), lhs._vals.end(), y.begin(),
                 [rhs](double x) { return x * rhs; });
  return Tuple(y);
}

Tuple operator*(const Tuple &lhs, const Tuple &rhs)
{
  std::vector<double> z(lhs._vals.size());
  std::transform(lhs._vals.begin(), lhs._vals.end(), rhs._vals.begin(), z.begin(),
                 [](double x, double y) { return (x * y); });
  return Tuple(z);
}

Tuple operator/(const Tuple &lhs, const double &rhs)
{
  std::vector<double> y(lhs._vals.size());
  std::transform(lhs._vals.begin(), lhs._vals.end(), y.begin(),
                 [rhs](double x) { return x / rhs; });
  return Tuple(y);
}

Tuple operator+(const Tuple &lhs, const Tuple &rhs)
{
  std::vector<double> z(lhs._vals.size());
  std::transform(lhs._vals.begin(), lhs._vals.end(), rhs._vals.begin(), z.begin(),
                 [](double x, double y) { return (x + y); });
  return Tuple(z);
}

Tuple operator-(const Tuple &lhs, const Tuple &rhs)
{
  std::vector<double> z(lhs._vals.size());
  std::transform(lhs._vals.begin(), lhs._vals.end(), rhs._vals.begin(), z.begin(),
                 [](double x, double y) { return (x - y); });
  return Tuple(z);
}

Tuple operator-(const Tuple &lhs)
{
  std::vector<double> y(lhs._vals.size());
  std::transform(lhs._vals.begin(), lhs._vals.end(), y.begin(),
                 [](double x) { return 0 - x; });
  return Tuple(y);
}

Tuple Vector(double x, double y, double z) { return Tuple({x, y, z, 0.0}); }
Tuple Point(double x, double y, double z) { return Tuple({x, y, z, 1.0}); }

std::ostream &operator<<(std::ostream &out, const Tuple &c)
{
  out << "( ";
  for (auto a : c._vals)
    out << a << ",";
  out << ")";
  return out;
}

double Tuple::magnitude() const
{
  return sqrt(_vals[0] * _vals[0] +
              _vals[1] * _vals[1] +
              _vals[2] * _vals[2] +
              _vals[3] * _vals[3]);
}

} //namespace ray_lib
