#include <iostream>
#include "tuples.h"

bool comparator(const double & left, const double & right)
{
  if (fabs(left - right) < 4 * EPSILON)
    return true;
  std::cout <<"Comparing " << left << " to " << right << " " <<std::endl;
  std::cout <<"fabs error =" << fabs(left - right)<< " epsilon = " << EPSILON << std::endl;
  return  false;
}

bool arraycomparator(const std::array<double, 4> & lhs, const std::array<double, 4> & rhs){
  return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), comparator);
}

bool   operator ==( const Raytuple &lhs, const Raytuple &rhs)   {return arraycomparator(lhs.Values(),  rhs.Values()); }
bool  operator !=( const Raytuple &lhs, const Raytuple &rhs)   {return !(arraycomparator(lhs.Values(),  rhs.Values())); }

Raytuple Vector(double x, double y, double z) {return Raytuple(x, y, z, 0.0);}
Raytuple Point(double x, double y, double z) {return Raytuple(x, y, z, 1.0);}

Raytuple  operator +(const Raytuple &lhs, const Raytuple &rhs) { return Raytuple::arrayadder(lhs, rhs);}
Raytuple  operator -(const Raytuple &lhs, const Raytuple &rhs) { return Raytuple::arraysub(lhs, rhs);}

Raytuple  operator *(const double &lhs, const Raytuple &rhs) { return Raytuple::arraymul(lhs, rhs);}
Raytuple  operator *(const Raytuple  &lhs, const double &rhs) { return Raytuple::arraymul(rhs, lhs);}
Raytuple  operator /(const Raytuple  &lhs, const double &rhs) { return Raytuple::arraymul(1.0 / rhs, lhs);}
Raytuple  operator -(const Raytuple &rhs) { return (Raytuple(0, 0, 0, 0) - rhs);}

std::ostream & operator << (std::ostream &out, const Raytuple &c)
{
    out <<"( ";
    for (auto a : c.Values() )
      out << a << ",";
    out << ")";
    return out;
}
