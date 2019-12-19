#ifndef tuples_h
#define tuples_h

#include <array>
#include <functional>
#include <algorithm>
#include <limits>
#include <iostream>
#include <cmath>
#include "utils.h"



class Raytuple;

// A class to represent 4 element tuples used for ray tracing
// these are represented using 4 elements x,y,z,w
// where w==0 means it is a vector and w==1 means it is a point
// non class helpers
bool comparator(const double & left, const double & right);

bool arraycomparator(const std::array<double, 4> & lhs, const std::array<double, 4> & rhs);


bool  operator ==(const Raytuple &lhs, const Raytuple &rhs);
bool  operator !=(const Raytuple &lhs, const Raytuple &rhs);

Raytuple Vector(double x, double y, double z);
Raytuple Point(double x, double y, double z);

// Operators
Raytuple  operator +(const Raytuple &lhs, const Raytuple &rhs);
Raytuple  operator -(const Raytuple &lhs, const Raytuple &rhs);

Raytuple  operator *(const double &lhs, const Raytuple &rhs);
Raytuple  operator *(const Raytuple  &lhs, const double &rhs);
Raytuple  operator /(const Raytuple  &lhs, const double &rhs);
Raytuple  operator -(const Raytuple &rhs);

class Raytuple{
  private:
  std::array <double, 4> _vals;

  public:
  explicit Raytuple(std::array<double, 4> a): _vals(a) {}
  Raytuple(const Raytuple &r) : _vals(r._vals){}
  bool isPoint(){return float_equals(_vals[3], 1.0);}
  bool isVector(){return !isPoint();}
  double magnitude(){
    return sqrt(_vals[0] * _vals[0] +
                _vals[1] * _vals[1] +
                _vals[2] * _vals[2] +
                _vals[3] * _vals[3]);
  }

  Raytuple normalise(){ return ( *this / this->magnitude()) ;}
  double dotproduct(const Raytuple &r)const;
  Raytuple crossproduct(const Raytuple &r)const;


  static Raytuple arrayadder(const Raytuple & lhs, const Raytuple & rhs){
    return Raytuple({lhs.Values()[0] +rhs.Values()[0],
                    lhs.Values()[1] +rhs.Values()[1],
                    lhs.Values()[2] +rhs.Values()[2],
                    lhs.Values()[3] +rhs.Values()[3]});
  }
  static  Raytuple arraysub(const Raytuple & lhs, const Raytuple & rhs){
    return Raytuple({lhs.Values()[0] -rhs.Values()[0],
                    lhs.Values()[1] -rhs.Values()[1],
                    lhs.Values()[2] -rhs.Values()[2],
                    lhs.Values()[3] -rhs.Values()[3]});
  }
    static     Raytuple arraymul(const double & lhs, const Raytuple & rhs){
    return Raytuple({lhs * rhs.Values()[0],
                    lhs * rhs.Values()[1],
                    lhs * rhs.Values()[2],
                    lhs * rhs.Values()[3]});
  }

  double x() const {return _vals[0];}
  double y() const {return _vals[1];}
  double z() const {return _vals[2];}
  double w() const {return _vals[3];}
  const std::array <double, 4> &Values()const {return (_vals);}

};


std::ostream & operator << (std::ostream &out, const Raytuple &c);

#endif
