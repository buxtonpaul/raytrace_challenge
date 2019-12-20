#include <iostream>
#include <vector>
#include <algorithm>
#include "tuples.h"
#include "utils.h"

namespace ray_lib{
double tuple::dotproduct(const tuple &r)const{
  double sum = 0;
  for (unsigned int i = 0; i< this->Values().size(); ++i)
    sum+= (this->Values()[i]* r.Values()[i]);
   return sum;
}

tuple tuple::crossproduct(const tuple &r)const
{
  return  Vector(this->y() * r.z() - this->z() * r.y(),
                    this->z() * r.x() - this->x() * r.z(),
                    this->x() * r.y() - this->y() * r.x());
}

tuple  operator *(const double &lhs, const tuple &rhs)
{
  std::vector<double> y(rhs._vals.size());
  std::transform(rhs._vals.begin(), rhs._vals.end(), y.begin(),
                   [lhs](double x) { return x*lhs; } );
  return tuple(y);
}

tuple  operator *(const tuple &lhs, const double &rhs)
{
  std::vector<double> y(lhs._vals.size());
  std::transform(lhs._vals.begin(), lhs._vals.end(), y.begin(),
                   [rhs](double x) { return x*rhs; } );
  return tuple(y);
}

tuple  operator *(const tuple  &lhs, const tuple &rhs)
{
  std::vector<double> z(lhs._vals.size());
  std::transform(lhs._vals.begin(), lhs._vals.end(), rhs._vals.begin(), z.begin(),
                   [](double x, double y) { return (x * y); } );
  return tuple(z);
}

tuple  operator /(const tuple  &lhs, const double &rhs)
{
  std::vector<double> y(lhs._vals.size());
  std::transform(lhs._vals.begin(), lhs._vals.end(), y.begin(),
                   [rhs](double x) { return x/rhs; } );
  return tuple(y);
}

tuple  operator +(const tuple  &lhs, const tuple &rhs)
{
  std::vector<double> z(lhs._vals.size());
  std::transform(lhs._vals.begin(), lhs._vals.end(), rhs._vals.begin(), z.begin(),
                   [](double x, double y) { return (x + y); } );
  return tuple(z);
}

tuple  operator -(const tuple  &lhs, const tuple &rhs)
{
  std::vector<double> z(lhs._vals.size());
  std::transform(lhs._vals.begin(), lhs._vals.end(), rhs._vals.begin(), z.begin(),
                   [](double x, double y) { return (x - y); } );
  return tuple(z);
}

tuple  operator -(const tuple &lhs)
{
  std::vector<double> y(lhs._vals.size());
  std::transform(lhs._vals.begin(), lhs._vals.end(), y.begin(),
                   [](double x) { return 0-x; } );
  return tuple(y);
}


tuple Vector(double x, double y, double z) {return tuple({x, y, z, 0.0});}
tuple Point(double x, double y, double z) {return tuple({x, y, z, 1.0});}


std::ostream & operator << (std::ostream &out, const tuple &c)
{
    out <<"( ";
    for (auto a : c._vals)
      out << a << ",";
    out << ")";
    return out;
}

}//namespace ray_lib

