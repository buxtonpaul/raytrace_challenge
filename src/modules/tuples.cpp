#include <iostream>
#include <valarray>
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

tuple  operator *(const double &lhs, const tuple &rhs)  { return tuple(lhs * rhs.Values());}
tuple  operator /(const tuple  &lhs, const double &rhs) { return tuple(lhs.Values() * (1.0/rhs) );}

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

