#include "tuples.h"

bool comparator(const double & left, const double & right){
                    // Lambda function to compare 2 strings in case insensitive manner
                    return  fabs(left - right) < EPSILON;
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
