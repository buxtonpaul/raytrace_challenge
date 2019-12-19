#include <iostream>
#include "tuples.h"
#include "utils.h"

namespace ray_lib{
double tuple::dotproduct(const tuple &r)const{
  double sum = 0;
  for (unsigned int i = 0; i< this->Values().size(); ++i)
    sum+= (this->Values()[i]* r.Values()[i]);
   return sum;
}

bool arraycomparator(const std::valarray<double> & lhs, const std::valarray<double> & rhs){
  return std::equal(begin(lhs), end(lhs), begin(rhs), end(rhs), float_equals);
}

tuple tuple::crossproduct(const tuple &r)const
{
  return  Vector(this->y() * r.z() - this->z() * r.y(),
                    this->z() * r.x() - this->x() * r.z(),
                    this->x() * r.y() - this->y() * r.x());
}
bool  operator ==( const tuple &lhs, const tuple &rhs)   {return arraycomparator(lhs.Values(),  rhs.Values()); }
bool  operator !=( const tuple &lhs, const tuple &rhs)   {return !(arraycomparator(lhs.Values(),  rhs.Values())); }

tuple Vector(double x, double y, double z) {return tuple({x, y, z, 0.0});}
tuple Point(double x, double y, double z) {return tuple({x, y, z, 1.0});}

tuple  operator +(const tuple &lhs, const tuple &rhs) { return tuple(lhs.Values()+ rhs.Values());}
tuple  operator -(const tuple &lhs, const tuple &rhs) { return tuple(lhs.Values()- rhs.Values());}


tuple  operator *(const double &lhs, const tuple &rhs)  { return tuple(lhs * rhs.Values());}

tuple  operator *(const tuple  &lhs, const double &rhs) { return tuple(lhs.Values() * rhs );}

tuple  operator /(const tuple  &lhs, const double &rhs) { return tuple(lhs.Values() * (1.0/rhs) );}
tuple  operator -(const tuple &rhs) { return (tuple({0, 0, 0, 0}) - rhs);}

std::ostream & operator << (std::ostream &out, const tuple &c)
{
    out <<"( ";
    for (auto a : c.Values() )
      out << a << ",";
    out << ")";
    return out;
}
}