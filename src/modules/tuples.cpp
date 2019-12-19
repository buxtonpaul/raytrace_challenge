#include <iostream>
#include "tuples.h"
#include "utils.h"


double Raytuple::dotproduct(const Raytuple &r)const{
  double sum = 0;
  for (unsigned int i = 0; i< this->Values().size(); ++i)
    sum+= (this->Values()[i]* r.Values()[i]);
   return sum;
}
bool arraycomparator(const std::valarray<double> & lhs, const std::valarray<double> & rhs){
  return std::equal(begin(lhs), end(lhs), begin(rhs), end(rhs), float_equals);
}

Raytuple Raytuple::crossproduct(const Raytuple &r)const
{
  return  Vector(this->y() * r.z() - this->z() * r.y(),
                    this->z() * r.x() - this->x() * r.z(),
                    this->x() * r.y() - this->y() * r.x());
}
bool  operator ==( const Raytuple &lhs, const Raytuple &rhs)   {return arraycomparator(lhs.Values(),  rhs.Values()); }
bool  operator !=( const Raytuple &lhs, const Raytuple &rhs)   {return !(arraycomparator(lhs.Values(),  rhs.Values())); }

Raytuple Vector(double x, double y, double z) {return Raytuple({x, y, z, 0.0});}
Raytuple Point(double x, double y, double z) {return Raytuple({x, y, z, 1.0});}

Raytuple  operator +(const Raytuple &lhs, const Raytuple &rhs) { return Raytuple(lhs.Values()+ rhs.Values());}
Raytuple  operator -(const Raytuple &lhs, const Raytuple &rhs) { return Raytuple(lhs.Values()- rhs.Values());}


Raytuple  operator *(const double &lhs, const Raytuple &rhs)  { return Raytuple(lhs * rhs.Values());}

Raytuple  operator *(const Raytuple  &lhs, const double &rhs) { return Raytuple(lhs.Values() * rhs );}

Raytuple  operator /(const Raytuple  &lhs, const double &rhs) { return Raytuple(lhs.Values() * (1.0/rhs) );}
Raytuple  operator -(const Raytuple &rhs) { return (Raytuple({0, 0, 0, 0}) - rhs);}

std::ostream & operator << (std::ostream &out, const Raytuple &c)
{
    out <<"( ";
    for (auto a : c.Values() )
      out << a << ",";
    out << ")";
    return out;
}
