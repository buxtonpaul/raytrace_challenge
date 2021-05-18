#include "tuples.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include "utils.h"

namespace ray_lib
{
  double Vector::dotproduct(const Vector &r) const
  {
    double sum{0};
    for (unsigned int i = 0; i < this->Values().size(); ++i)
      sum += (this->Values()[i] * r.Values()[i]);
    return sum;
  }

  Vector Vector::crossproduct(const Vector &r) const
  {
    return Vector(this->y() * r.z() - this->z() * r.y(),
                  this->z() * r.x() - this->x() * r.z(),
                  this->x() * r.y() - this->y() * r.x());
  }

  double Tuple::magnitude() const
  {
    return sqrt(_vals[0] * _vals[0] + _vals[1] * _vals[1] + _vals[2] * _vals[2] +
                _vals[3] * _vals[3]);
  }

  Vector Vector::reflect(const Vector &n) const
  {
    Vector a{*this - n * 2 * dotproduct(n)};
    return a;
  }

  bool Tuple::isPoint() const
  {
    return (float_equals(_vals[3], 1.0) && (_size == 4));
  }
  bool Tuple::isVector() const
  {
    return ((!isPoint()) && (_size == 4));
  }

  bool Tuple::operator==(const Tuple &obj) const
  {
    return (std::equal(begin(_vals), end(_vals), begin(obj._vals),
                       end(obj._vals), float_equals));
  }

  double Tuple::x() const
  {
    return _vals[0];
  }
  double Tuple::y() const
  {
    return _vals[1];
  }
  double Tuple::z() const
  {
    return _vals[2];
  }
  double Tuple::w() const
  {
    return _vals[3];
  }

  double Tuple::x(double x)
  {
    _vals[0] = x;
    return _vals[0];
  }
  double Tuple::y(double y)
  {
    _vals[1] = y;
    return _vals[1];
  }
  double Tuple::z(double z)
  {
    _vals[2] = z;
    return _vals[2];
  }
  double Tuple::w(double w)
  {
    _vals[3] = w;
    return _vals[3];
  }

  unsigned int Tuple::size() const
  {
    return _size;
  }
  const std::vector<double> &Tuple::Values() const
  {
    return (_vals);
  }

  const double &Tuple::operator[](int index)const
  {
    return _vals[index];
  }
double &Tuple::operator[](int index)
  {
    return _vals[index];
  }
  Vector Vector::normalise() const
  {
    return (*this / this->magnitude());
  }

} // namespace ray_lib
